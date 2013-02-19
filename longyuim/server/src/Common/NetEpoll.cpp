
#include "NetEpoll.h"

CNetEpoll::CNetEpoll()
{
	memset(&mstruEvent, 0, sizeof(epoll_event)*DEF_EPOLL_SIZE);
	miEpfd = -1;
	mbHasListenFd = false;
	mbKeepAlive = true;
	miMaxFdNumber = 102400;
}

CNetEpoll::~CNetEpoll()
{

}

bool CNetEpoll::Init(unsigned int aiMaxSocketSize /* = DEF_EPOLL_SIZE */)
{
	miEpfd = epoll_create(aiMaxSocketSize);
	if(miEpfd == -1)
	{
		TRACE(1, "CNetEpoll::Init epoll_creat 失败。 ");
		return false;
	}

	mSendEvent.Create();
	mRecvEvent.Create();

	return true;
}

bool CNetEpoll::Destroy()
{
	CAutoLock lock(moFdSection);
	while(moNetSocketList.size() != 0)
	{
		NET_SOCKET_LIST_ITER iter = moNetSocketList.begin();
		int fd = iter->first;
		Delfd(fd);
	}
	if(miEpfd != -1)
	{
		close(miEpfd);
	}

	mSendEvent.Close();
	mRecvEvent.Close();
	return true;
}

bool CNetEpoll::WaitSendEvent()
{
	int nRet = mSendEvent.WaitForEvent(-1);
}

bool CNetEpoll::WaitRecvEvent()
{
	int nRet = mRecvEvent.WaitForEvent(-1);
}

bool CNetEpoll::Addfd(CNetSocket* apNetSocket)
{
	ASSERT(apNetSocket != NULL);
	CAutoLock lock(moFdSection);
	if(apNetSocket != NULL)
	{
		moNetSocketList[apNetSocket->miSocket] = apNetSocket;
	}
	if(AddEpollEvent(apNetSocket->miSocket, EPOLLIN | EPOLLET) < 0)
	{
		TRACE(1, "CNetEpoll::Addfd * 失败。 errno = "<<errno);
		return false;
	}
	return true;
}

bool CNetEpoll::Addfd(int fd)
{
	CAutoLock lock(moFdSection);
	CNetSocket *lpNetSocket = new CNetSocket;
	lpNetSocket->miSocket = fd;
	lpNetSocket->moNetStat = COMMON_TCP_ESTABLISHED;
	lpNetSocket->mbListenSocket = false;
	moNetSocketList[fd] = lpNetSocket;

	if(AddEpollEvent(fd, EPOLLIN | EPOLLET) < 0)
	{
		TRACE(1, "CNetEpoll::Addfd 失败。 errno = "<<errno);
		return false;
	}
	return true;
}

bool CNetEpoll::Delfd(int fd)
{
	CAutoLock lock(moFdSection);
	CNetSocket *lpNetSocket = NULL;
	NET_SOCKET_LIST_ITER iter = moNetSocketList.find(fd);
	if(iter != moNetSocketList.end())
	{
		lpNetSocket = iter->second;
	}
	if(NULL == lpNetSocket)
	{
		return true;
	}
	if(DelEpollEvent(lpNetSocket->miSocket) < 0)
	{
		TRACE(1, "CNetEpoll::Delfd 失败。 errno = "<<errno);
	}
	if(!lpNetSocket->mbListenSocket && !lpNetSocket->mbClientSocket)
	{
		delete lpNetSocket;
		lpNetSocket = NULL;
	}
	moNetSocketList.erase(fd);
	return true;
}

bool CNetEpoll::Delfd(CNetSocket* apNetSocket)
{
	CAutoLock lock(moFdSection);
	if(NULL == apNetSocket)
	{
		return true;
	}
	if(DelEpollEvent(apNetSocket->miSocket) < 0)
	{
		TRACE(1, "CNetEpoll::Delfd 失败。 errno = "<<errno);
	}
	if(!apNetSocket->mbListenSocket && !apNetSocket->mbClientSocket)
	{
		delete apNetSocket;
		apNetSocket = NULL;
	}

	moNetSocketList.erase(apNetSocket->miSocket);
	return true;
}

bool CNetEpoll::Delfd(NET_SOCKET_LIST_ITER iter)
{
	CAutoLock lock(moFdSection);
	CNetSocket *lpNetSocket = NULL;

	lpNetSocket = iter->second;
	if(NULL == lpNetSocket)
	{
		return true;
	}
	if(DelEpollEvent(lpNetSocket->miSocket && !lpNetSocket->mbClientSocket) < 0)
	{
		TRACE(1, "CNetEpoll::Delfd NET_SOCKET_LIST_ITER 失败。 errno = "<<errno);
	}
	if(!lpNetSocket->mbListenSocket)
	{
		delete lpNetSocket;
		lpNetSocket = NULL;
	}
	moNetSocketList.erase(iter);
	return true;
}

bool CNetEpoll::Findfd(int fd)
{
	CAutoLock lock(moFdSection);
	NET_SOCKET_LIST_ITER iter = moNetSocketList.find(fd);
	if(iter != moNetSocketList.end())
	{
		return true;
	}
	return false;
}

int CNetEpoll::AddEpollEvent(int iSocket, unsigned int ulEvent)
{    
	struct epoll_event ev;
	ev.data.fd = iSocket;
	ev.events = ulEvent;
	return epoll_ctl(miEpfd, EPOLL_CTL_ADD, iSocket, &ev);
}

int CNetEpoll::ModifyEpollEvent(int iSocket, unsigned int ulEvent)
{
	struct epoll_event ev;
	ev.data.fd = iSocket;
	ev.events = ulEvent;

	if (epoll_ctl(miEpfd, EPOLL_CTL_MOD, iSocket, &ev) < 0)
	{
		if (errno != ENOENT)
		{
			return epoll_ctl(miEpfd, EPOLL_CTL_ADD, iSocket, &ev);
		}
		else
		{
			return -1;
		}
	}

	return 0;
}

int CNetEpoll::DelEpollEvent(int iSocket)
{
	struct epoll_event ev;
	ev.data.fd = iSocket;
	ev.events = 0;

	return epoll_ctl(miEpfd, EPOLL_CTL_DEL, iSocket, &ev);
}

int CNetEpoll::CheckEpollEvent(int time_out/* =0 */)
{
	memset(&mstruEvent, 0, sizeof(epoll_event)*DEF_EPOLL_SIZE);
	int nRet = 0;
	nRet = epoll_wait(miEpfd, &mstruEvent[0],DEF_EPOLL_SIZE, time_out);
	if(nRet == -1)
	{
		if(EINTR != errno)
		{
			TRACE(1, "CNetEpoll::CheckEpollEvent 出错。errno = "<<errno);
		}
		return 0;
	}
	return nRet;
}

int CNetEpoll::ProcessEpollEvent(int aiEventSize)
{
	for(int i = 0; i < aiEventSize; i++)
	{
		CAutoLock lock(moFdSection);
		int fd = mstruEvent[i].data.fd;
		CNetSocket *lpNetFd  = NULL;
		NET_SOCKET_LIST_ITER iter = moNetSocketList.find(fd);
		if(iter != moNetSocketList.end())
		{
			lpNetFd = iter->second;
		}
		else
		{
			continue;
		}

		if(NULL == lpNetFd)
		{
			continue;
		}

		if(lpNetFd->mbListenSocket)
		{
			if (mstruEvent[i].events & (EPOLLERR | EPOLLHUP))
			{
				TRACE(1, "CNetEpoll::ProcessEpollEvent 监听SOCKET出现错误。errno = "<<errno);
				continue;
			}

			if (mstruEvent[i].events & EPOLLIN)
			{
				while(true)
				{
					int ip = 0;
					short port = 0;
					int _fd  =  lpNetFd->Accept(ip, port);
					if(0 == _fd)
					{
						break;
					}
					else
					{
						Addfd(_fd);
						unsigned int liCurrentFdNumber = GetConnectedSize();
						if(liCurrentFdNumber > miMaxFdNumber)
						{
							break;
						}
					}
					//TRACE(1, "CNetEpoll::ProcessEpollEvent ACCEPT fd = "<<_fd);
				}

			}
		}
		else
		{
			if (mstruEvent[i].events & (EPOLLERR | EPOLLHUP))
			{
				TRACE(1, "CNetEpoll::ProcessEpollEvent 出现错误。errno = "<<errno
					<<" fd = "<<lpNetFd->miSocket<<" aiEventSize = "<<aiEventSize);
				OnErrorNotice(lpNetFd->miSocket);
				Delfd(lpNetFd->miSocket);
				continue;
			}
			if(mstruEvent[i].events & EPOLLIN)
			{
				if(!lpNetFd->RecvData())
				{
					OnErrorNotice(lpNetFd->miSocket);
					Delfd(lpNetFd->miSocket);
				}
				mRecvEvent.SetEvent();
			}
			if(mstruEvent[i].events & EPOLLOUT)
			{
				lpNetFd->mbCanSend = true;
				ModifyEpollEvent(lpNetFd->miSocket, EPOLLIN | EPOLLET);
				mSendEvent.SetEvent();
			}
		}
	}
	return 0;
}

bool CNetEpoll::SendData(int fd, const char* buffer, const int length)
{
	if(fd == 0)
	{
		return false;
	}
	CAutoLock lock(moFdSection);
	CNetSocket *lpNetSocket = NULL;
	NET_SOCKET_LIST_ITER iter = moNetSocketList.find(fd);
	if(iter != moNetSocketList.end())
	{
		lpNetSocket = iter->second;
	}
	if(NULL == lpNetSocket)
	{
		TRACE(1, "CNetEpoll::SendData 未查到该用户， fd = "<<fd);
		return false;
	}
	lpNetSocket->SendData(buffer, length);
	mSendEvent.SetEvent();
	return true;
}

bool CNetEpoll::SendAllData(const char* buffer, const int length)
{
	CAutoLock lock(moFdSection);
	NET_SOCKET_LIST_ITER iter = moNetSocketList.begin();
	for(;iter != moNetSocketList.end();++iter)
	{
		CNetSocket *lpNetSocket = NULL;
		lpNetSocket = iter->second;
		if(NULL == lpNetSocket)
		{
			continue;
		}
		if(!lpNetSocket->mbListenSocket && !lpNetSocket->mbClientSocket)
		{
			lpNetSocket->SendData(buffer, length);
		}
	}
	mSendEvent.SetEvent();
	return true;
}

bool CNetEpoll::SendData()
{
	bool isEmpty = true;
	CAutoLock lock(moFdSection);
	NET_SOCKET_LIST_ITER iter = moNetSocketList.begin();
	for(;iter != moNetSocketList.end();)
	{
		CNetSocket *lpNetSocket = NULL;
		lpNetSocket = iter->second;
		if(NULL == lpNetSocket)
		{
			iter++;
			continue;
		}
		if(!lpNetSocket->mbListenSocket)
		{
			int nRet = lpNetSocket->SendData();
			if(-1 == nRet)
			{
				OnErrorNotice(lpNetSocket->miSocket);
				Delfd(iter++);
				isEmpty &= false;
			}
			else if(1 == nRet)
			{
				ModifyEpollEvent(lpNetSocket->miSocket, EPOLLIN |EPOLLOUT | EPOLLET);
				isEmpty &= false;
			}
			//else if (2 == nRet)
			//{
			//	TRACE(1, "CNetEpoll::SendData() 发送列表已经为空。");
			//}
		}
		iter++;
	}
	return isEmpty;
}

bool CNetEpoll::RecvData()
{
	bool isEmpty = true;
	CAutoLock lock(moFdSection);
	NET_SOCKET_LIST_ITER iter = moNetSocketList.begin();
	for(;iter != moNetSocketList.end();iter++)
	{
		CNetSocket *lpNetSocket = NULL;
		lpNetSocket = iter->second;
		if(NULL == lpNetSocket)
		{
			continue;
		}
		if(!lpNetSocket->mbListenSocket)
		{
			//每个连接数据包全部处理完
			for(;;)
			{
				char buffer[DEF_BUFFER_LEN];
				memset(buffer, 0, DEF_BUFFER_LEN);
				int length = DEF_BUFFER_LEN;
				int nRet = lpNetSocket->RecvData(buffer, length);
				if(nRet)
				{
					RecvFrom(lpNetSocket->miSocket, buffer, length);
					isEmpty &= false;
				}
				else
				{
					//TRACE(1, "CNetEpoll::RecvData() 接收列表已经空。");
					break;
				}
			}

		}
	}
	return isEmpty;
}

unsigned int CNetEpoll::GetConnectedSize()
{
	CAutoLock lock(moFdSection);
	unsigned int luiSize = moNetSocketList.size();
	return luiSize;
}

bool CNetEpoll::CloseConnect()
{
	CAutoLock lock(moFdSection);
	NET_SOCKET_LIST_ITER iter = moNetSocketList.begin();
	for(;iter != moNetSocketList.end();iter++)
	{
		CNetSocket *lpNetSocket = NULL;
		lpNetSocket = iter->second;
		if(NULL == lpNetSocket)
		{
			continue;
		}
		if(!lpNetSocket->mbListenSocket)
		{
			if(lpNetSocket->moSendStat == SENDED)
			{
				Delfd(lpNetSocket->miSocket);
			}
		}
	}
	return true;
}

void CNetEpoll::Dump()
{

}

void CNetEpoll::TimeOutWork()
{

}



















