/********************************************************************
created:	2009/09/21
created:	21:9:2009   10:13
filename: 	\TaskProcessor\src\TaskProcessor.cpp
file path:	\TaskProcessor\src
file base:	TaskProcessor
file ext:	cpp
author:		isold

purpose:	
*********************************************************************/
#include "TaskProcessor.h"

CTaskProcessor::CTaskProcessor()
{
	m_pConfig = NULL;
	m_pTaskProcess = NULL;
}

CTaskProcessor::~CTaskProcessor()
{
	if(m_Listener.moNetStat == TCP_LISTEN)
		m_Listener.Close();
}

void CTaskProcessor::SetConfigInfo(CTaskProcessorConfig *apConfig)
{
	ASSERT(apConfig);
	m_pConfig = apConfig;
}

int CTaskProcessor::Run()
{
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = m_pConfig->tps_ip;
	bool bRet = m_Listener.CreateSocket(inet_ntoa(addr.sin_addr), m_pConfig->tps_port);
	if(!bRet)
	{
		return FAILED;
	}

	bRet = m_Listener.SetNoBlock();
	if(!bRet)
	{
		m_Listener.Close();
		return FAILED;
	}
	bRet = m_Listener.Listen();
	if(!bRet)
	{
		m_Listener.Close();
		return FAILED;
	}
	m_Listener.moNetStat = TCP_LISTEN;
	m_Listener.mbListenSocket = true;

	TRACE(5, "CTaskProcessor::Run 子进程个数: "<<m_pConfig->max_processor);

	for(uint32 i = 0; i < m_pConfig->max_processor; i++)
	{
		pid_t nPid;
		if ((nPid = fork()) < 0)
		{
			TRACE(1, "CTaskProcessor::Run 创建子进程失败。 ");
			kill(0, SIGKILL);
			return FAILED;
		}
		else if (nPid == 0)
		{
			ChildProcess(this);
		}
		else
		{
			TRACE(1, "CTaskProcessor::Run Child PID: "<<nPid<<" PID: "<<getpid());
		}
	}

	for(;;)
	{
		pid_t pt;
		int status = 0;
		pt = waitpid(-1, &status, WNOHANG);
		if(-1 == pt)
		{
			if(errno != ECHILD)
			{
				TRACE(1, "CTaskProcessor::Run wait_pid 出现错误。errno = "<<errno);
			}
		}
		else if(pt > 0)
		{
			pid_t nPid;
			if ((nPid = fork()) < 0)
			{
				TRACE(1, "CTaskProcessor::Run 创建子进程失败。 ");
				kill(0, SIGKILL);
			}
			else if (nPid == 0)
			{
				ChildProcess(this);
			}
			else
			{
				TRACE(1, "CTaskProcessor::ChildProcessFun Child PID: "<<nPid<<" PID: "<<getpid());
			}

		}
		usleep(1000*100);
	}
	return SUCCEEDED;
}
void CTaskProcessor::ChildProcess(void *parameter)
{
	ASSERT(parameter != NULL);
	if(parameter == NULL)
		return;
	CTaskProcessor *p = (CTaskProcessor*)parameter;
	p->ChildProcessFun();
}

void CTaskProcessor::ChildProcessFun()
{
	try
	{
		int liParentId = getppid();
		if(1 == liParentId)
		{
			TRACE(1, "CTaskProcessor::ChildProcessFun 父进程退出了。父进程ID = "<<liParentId);
			exit(0);
		}

		CNetEpoll loNetEpoll;
		bool bRet = loNetEpoll.Init();
		if(!bRet)
		{
			TRACE(1, "CTaskProcessor::ChildProcessFun EPOLL初始化失败。");
			exit(0);
		}
		bRet = loNetEpoll.Addfd(&m_Listener);
		if(!bRet)
		{
			TRACE(1, "CTaskProcessor::ChildProcessFun 添加监听端口到EPOLL中失败。");
			loNetEpoll.Destroy();
			exit(0);
		}
		loNetEpoll.mbHasListenFd = true;
		loNetEpoll.RecvFrom.connect(this, &CTaskProcessor::DealData);
		for(;;)
		{
			int liCurrentParentId = getppid();
			if((liParentId != liCurrentParentId) || (1 == liCurrentParentId))
			{
				TRACE(1, "CTaskProcessor::ChildProcessFun 父进程退出了。ID = "<<liParentId<<
					" CurrentId = "<<liCurrentParentId);
				break;
			}

			if(loNetEpoll.GetConnectedSize() > m_pConfig->max_connected)
			{
				TRACE(1, "CTaskProcessor::ChildProcessFun 超过最大个数。当前连接数: "<<
					loNetEpoll.GetConnectedSize()<<" 最大连接个数: "<<m_pConfig->max_connected);
				loNetEpoll.Delfd(&m_Listener);
				loNetEpoll.mbHasListenFd = false;
			}

			if(loNetEpoll.GetConnectedSize() < m_pConfig->max_connected)
			{
				if(!loNetEpoll.mbHasListenFd)
				{
					loNetEpoll.Addfd(&m_Listener);
					loNetEpoll.mbHasListenFd = true;
				}
			}

			int nRet = loNetEpoll.CheckEpollEvent();
			loNetEpoll.ProcessEpollEvent(nRet);
			loNetEpoll.SendData();
			loNetEpoll.RecvData();
			if(!m_pConfig->keep_alive)
			{
				loNetEpoll.CloseConnect();
			}
			usleep(1000*100);
		}
	}
	catch (...)
	{
		TRACE(1, "CTaskProcessor::ChildProcessFun 出现异常。");
	}
	exit(0);
}

void CTaskProcessor::DealData(CNetSocket* fd, char *buffer, int length)
{
	try
	{
		char rtn[DEF_BUFFER_LEN];
		memset(rtn, 0, DEF_BUFFER_LEN);
		int rtn_len = 0;
		m_pTaskProcess->TaskProcessFun(buffer, length, rtn, rtn_len);
		fd->SendData(rtn, rtn_len);
		fd->moSendStat = SENDINT;
	}
	catch (...)
	{
		TRACE(1, "CTaskProcessor::DealData 出现异常。");
	}
}

void CTaskProcessor::SetDealDataPtr(ITaskProcess *apTaskProcessPtr)
{
	ASSERT(apTaskProcessPtr != NULL);
	m_pTaskProcess = apTaskProcessPtr;
}

