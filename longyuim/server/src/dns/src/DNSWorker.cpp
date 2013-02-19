
#include "DNSWorker.h"

CDNSWorker::CDNSWorker()
{
	m_pDnsConfig = NULL;
	uint64 time_now = CTimeBase::get_current_time();
	m_i64LastDumpTime = time_now;
	m_i64LastLogTime = time_now;
}

CDNSWorker::~CDNSWorker()
{

}

void CDNSWorker::SetConfig(CDNSConfig *apDnsConfig)
{
	ASSERT(apDnsConfig != NULL);
	m_pDnsConfig = apDnsConfig;
}

void CDNSWorker::Run()
{
	ASSERT(m_pDnsConfig != NULL);
	try
	{
		bool lbBind = false;
		unsigned short lusBindPort = m_pDnsConfig->server_port;
		struct sockaddr_in addr;
		addr.sin_addr.s_addr = htonl(m_pDnsConfig->server_ip);
		for(int i = 0; i < m_pDnsConfig->max_bind_time;++i)
		{
			bool bRet = m_DnsListenFd.CreateSocket(inet_ntoa(addr.sin_addr), 
				lusBindPort);
			if(bRet)
			{
				lbBind = true;
				break;
			}
		}

		if(!lbBind)
		{
			TRACE(1, "CDNSWorker::Run 绑定端口失败。");
			return;
		}

		bool bRet = m_DnsListenFd.SetNoBlock();
		if(!bRet)
		{
			m_DnsListenFd.Close();
			TRACE(1, "CDNSWorker::Run 设置非阻塞属性失败。");
			return;
		}
		bRet = m_DnsListenFd.Listen();
		if(!bRet)
		{
			m_DnsListenFd.Close();
			TRACE(1, "CDNSWorker::Run 监听端口失败。");
			return;
		}
		m_DnsListenFd.moNetStat = TCP_LISTEN;
		m_DnsListenFd.mbListenSocket = true;

		for(int i = 0; i < m_pDnsConfig->max_process_size; ++i)
		{
			pid_t nPid;
			if ((nPid = fork()) < 0)
			{
				TRACE(1, "CDNSWorker::Run 创建子进程失败。 ");
				kill(0, SIGKILL);
				return;
			}
			else if (nPid == 0)
			{
				ChildProcess(this);
			}
			else
			{
				TRACE(1, "CDNSWorker::Run Child PID: "<<nPid<<" PID: "<<getpid());
			}
		}

		while(true)
		{
			TimeOutWork();

			pid_t pt;
			int status = 0;
			pt = waitpid(-1, &status, WNOHANG);
			if(-1 == pt)
			{
				if(errno != ECHILD)
				{
					TRACE(1, "CDNSWorker::Run wait_pid 出现错误。errno = "<<errno);
				}
			}
			else if(pt > 0)
			{
				pid_t nPid;
				if ((nPid = fork()) < 0)
				{
					TRACE(1, "CDNSWorker::Run 创建子进程失败。 ");
					kill(0, SIGKILL);
				}
				else if (nPid == 0)
				{
					ChildProcess(this);
				}
				else
				{
					TRACE(1, "CDNSWorker::Run Child PID: "<<nPid<<" PID: "<<getpid());
				}
			}
			usleep(1000*100);
		}
	}
	catch (...)
	{
		TRACE(1, "CDNSWorker::Run 出现异常。");
	}
}


void CDNSWorker::ChildProcess(void *parameter)
{
	ASSERT(parameter != NULL);
	if(parameter == NULL)
		return;
	CDNSWorker *p = (CDNSWorker*)parameter;

	goDebugTrace = new CDebugTrace;

	char lszLogFileName[255];
	memset(lszLogFileName, 0, 255);
	CFileStream::GetAppPath(lszLogFileName,255);

	unsigned int process_id = CCommon::GetProcessId();

	//设置日志文件信息
	SET_TRACE_LEVEL(5);
	unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel
		& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile);
	SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

	strcpy(strrchr(lszLogFileName,'/'),"//DNS_log");
	CFileStream::CreatePath(lszLogFileName);
	char lszFileDate[50];
	memset(lszFileDate, 0, 50);
	time_t loSystemTime;
	time(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime);
	sprintf(lszFileDate, "//DNS-%u-%4d%02d%02d%02d%02d.log", process_id,
		1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, lptm->tm_hour, lptm->tm_min);
	strcat(lszLogFileName,lszFileDate);
	SET_LOG_FILENAME(lszLogFileName);
	TRACE(1,"\n\n*******************DNS调试日志VERSION:" <<
		gstrDNSWorkerVersion.c_str() << "*******************");

	//加载配置文件
	CDNSConfig loDNSConfig;
	loDNSConfig.set_conf_file_name(p->m_pDnsConfig->get_conf_file_name().c_str());
	
	TRACE(1, "配置文件信息: "<<loDNSConfig.get_conf_file_name().c_str());

	bool bRet = loDNSConfig.load();
	if(!bRet)
	{
		TRACE(1, "ERROR: 加载配置文件失败。");
		exit(0);
	}

	CDNSChildWorker dns_child_worker;
	dns_child_worker.SetConfig(&loDNSConfig);
	dns_child_worker.SetDnsListenFd(&p->m_DnsListenFd);
	dns_child_worker.Run();
	exit(0);
}


void CDNSWorker::Dump()
{

}

void CDNSWorker::TimeOutWork()
{
	//Dump
	uint64 time_now = CTimeBase::get_current_time();
	if(time_now > m_i64LastDumpTime + m_pDnsConfig->dump_info_time * 1000)
	{
		Dump();
		m_i64LastDumpTime = time_now;
	}

	//log
	if(time_now > m_i64LastLogTime + m_pDnsConfig->log_file_update_time * 1000)
	{
		unsigned int process_id = CCommon::GetProcessId();

		char lszLogFileName[255];
		memset(lszLogFileName, 0, 255);
		CFileStream::GetAppPath(lszLogFileName,255);

		//设置日志文件信息
		SET_TRACE_LEVEL(5);
		unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel
			& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile);
		SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

		strcpy(strrchr(lszLogFileName,'/'),"//DNS_log");
		CFileStream::CreatePath(lszLogFileName);
		char lszFileDate[50];
		memset(lszFileDate, 0, 50);
		time_t loSystemTime;
		time(&loSystemTime);
		struct tm* lptm = localtime(&loSystemTime);
		sprintf(lszFileDate, "//DNS-%u-%4d%02d%02d%02d%02d.log", process_id,
			1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, lptm->tm_hour, lptm->tm_min);
		strcat(lszLogFileName,lszFileDate);
		SET_LOG_FILENAME(lszLogFileName);
		m_i64LastLogTime = time_now;
	}
}




