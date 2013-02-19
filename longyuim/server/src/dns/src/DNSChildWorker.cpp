
#include "DNSChildWorker.h"
#include "dcs_dns.h"
#include "dns_crs.h"

CDNSChildWorker::CDNSChildWorker()
{
	m_pDnsConfig = NULL;
	m_pDnsListenFd = NULL;
	uint64 time_now = CTimeBase::get_current_time();
	m_i64LastKeepLive = time_now;
	m_i64LastLogTime = time_now;
	m_i64LastDumpTime = time_now;
	m_i64LastCheckTimeOut = time_now;
}

CDNSChildWorker::~CDNSChildWorker()
{
	m_ThreadManager.StopAll();
	m_DnsServer.RecvFrom.disconnect(this);
	m_DnsServer.OnErrorNotice.disconnect(this);
}

void CDNSChildWorker::SetDnsListenFd(CNetSocket *apDnsListenFd)
{
	ASSERT(apDnsListenFd != NULL);
	m_pDnsListenFd = apDnsListenFd;
}

void CDNSChildWorker::SetConfig(CDNSConfig *apDnsConfig)
{
	ASSERT(apDnsConfig != NULL);
	m_pDnsConfig = apDnsConfig;
	//预留100作为其他用
	m_iMaxFd = m_pDnsConfig->max_file_size - 100;
	//设置最大文件句柄数
	CCommon::SetOpenFiles(m_pDnsConfig->max_file_size);
}

bool CDNSChildWorker::InitDnsServer()
{
	bool bRet = m_DnsServer.Init();
	if(!bRet)
	{
		TRACE(1, "CDNSChildWorker::Run EPOLL初始化失败。");
		return false;
	}
	bRet = m_DnsServer.Addfd(m_pDnsListenFd);
	if(!bRet)
	{
		TRACE(1, "CDNSChildWorker::Run 添加监听端口到EPOLL中失败。");
		m_DnsServer.Destroy();
		return false;
	}
	m_DnsServer.mbHasListenFd = true;
	m_DnsServer.RecvFrom.connect(this, &CDNSChildWorker::DealNetData);
	m_DnsServer.OnErrorNotice.connect(this, &CDNSChildWorker::OnDealErrorFd);
	m_DnsServer.SetMaxFdNumber(m_iMaxFd);
	return true;
}

bool CDNSChildWorker::InitDcsNode()
{
	//连接DCS服务
	bool lbCreate = false;
	lbCreate = m_DcsNodeFd.CreateSocket();
	if(!lbCreate)
	{
		TRACE(1, "CDNSChildWorker::InitDcsNode 创建SOCKET失败。");
		return false;
	}

	bool lbConnect = false;
	int liConnectCount = 0;
	while(m_DcsNodeFd.moNetStat != TCP_CONNECTED)
	{
		struct sockaddr_in addr;
		addr.sin_addr.s_addr = htonl(m_pDnsConfig->dcs_ip);
		lbConnect = m_DcsNodeFd.ConnectServer(inet_ntoa(addr.sin_addr), 
			m_pDnsConfig->dcs_port);
		if(!lbConnect)
		{
			if(++liConnectCount >= m_pDnsConfig->max_connect_time)
			{
				TRACE(1, "CDNSChildWorker::InitDcsNode 连接DCS失败。");
				m_DcsNodeFd.Close();
				return false;
			}
			else
			{
				usleep(1000*1000*3);
				continue;
			}
		}
	}
	
	m_DcsNodeFd.mbClientSocket = true;
	m_DcsNodeFd.SetNoBlock();
	bool bRet = m_DnsServer.Addfd(&m_DcsNodeFd);
	if(!bRet)
	{
		TRACE(1, "CDNSChildWorker::Run 添加DCSNodeFd到EPOLL中失败。");
		m_DnsServer.Destroy();
		return false;
	}
	TRACE(1, "CDNSChildWorker::InitDcsNode DcsNode Fd = "<<m_DcsNodeFd.miSocket);
	return true;
}

unsigned int CDNSChildWorker::CheckNetEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDNSChildWorker* p = reinterpret_cast<CDNSChildWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			if(p->m_DnsServer.GetConnectedSize() >= p->m_iMaxFd)
			{
				TRACE(1, "CDNSChildWorker::Run 超过最大个数。当前连接数: "<<
					p->m_DnsServer.GetConnectedSize()<<" 最大连接个数: "<<p->m_iMaxFd);
				if(p->m_DnsServer.mbHasListenFd)
				{
					p->m_DnsServer.Delfd(p->m_pDnsListenFd);
					p->m_DnsServer.mbHasListenFd = false;
				}
			}

			if(p->m_DnsServer.GetConnectedSize() < p->m_iMaxFd)
			{
				if(!p->m_DnsServer.mbHasListenFd)
				{
					p->m_DnsServer.Addfd(p->m_pDnsListenFd);
					p->m_DnsServer.mbHasListenFd = true;
				}
			}

			int nRet = p->m_DnsServer.CheckEpollEvent(-1);
			p->m_DnsServer.ProcessEpollEvent(nRet);
		}
	}
	catch (...)
	{
		TRACE(1, "CDNSChildWorker::CheckCrsNetEvent 出现异常。");
	}
	return 0;
}

unsigned int CDNSChildWorker::DealSendEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDNSChildWorker* p = reinterpret_cast<CDNSChildWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			bool bSendEmpty = true;
			bSendEmpty = p->m_DnsServer.SendData();
			if(bSendEmpty)
			{
				p->m_DnsServer.WaitSendEvent();
			}
		}
	}
	catch (...)
	{
		TRACE(1, "CDNSChildWorker::DealSendEvent 出现异常。");
	}
	return 0;
}

unsigned int CDNSChildWorker::DealRecvEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDNSChildWorker* p = reinterpret_cast<CDNSChildWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			bool bRecvEmpty = true;
			bRecvEmpty = p->m_DnsServer.RecvData();
			TRACE(1, "-----------------CDNSChildWorker::DealRecvEvent-----------------");
			if(bRecvEmpty)
			{
				p->m_DnsServer.WaitRecvEvent();
			}
		}
	}
	catch (...)
	{
		TRACE(1, "CDNSChildWorker::DealRecvEvent 出现异常。");
	}
	return 0;
}

void CDNSChildWorker::Run()
{
	ASSERT(m_pDnsConfig != NULL);
	try
	{
		//设置数据处理完毕的回调函数
		m_DNSDealData.DealCrsDataComplete.connect(this, &CDNSChildWorker::DealCrsDataComplete);
		m_DNSDealData.DealDcsDataComplete.connect(this, &CDNSChildWorker::DealDcsDataComplete);

		//建立本地监听服务
		int liParentId = getppid();
		if(1 == liParentId)
		{
			TRACE(1, "CDNSChildWorker::Run 父进程退出了。父进程ID = "<<liParentId);
			exit(0);
		}

		bool bDnsServerInitRet = InitDnsServer();
		if(!bDnsServerInitRet)
		{
			TRACE(1, "CDNSChildWorker::Run DNS Server 初始化失败。");
			exit(0);
		}

		bool bDcsNodeInitRet = InitDcsNode();
		if(!bDcsNodeInitRet)
		{
			TRACE(1, "CDNSChildWorker::Run DCS Node 初始化失败。");
			exit(0);
		}

		if (0 == m_ThreadManager.Start(CheckNetEvent, this, 1, "dns_check_net_event")) 
		{
			TRACE(1,"CDCSWorker::Run: DNS Server网络事件线程启动失败。进程退出。");
			exit(0);
		}

		if (0 == m_ThreadManager.Start(DealSendEvent, this, 1, "dns_send_data")) 
		{
			TRACE(1,"CDCSWorker::Run: DNS Server 数据发送线程启动失败。进程退出。");
			exit(0);
		}

		if (0 == m_ThreadManager.Start(DealRecvEvent, this, 1, "dns_recv_data")) 
		{
			TRACE(1,"CDCSWorker::Run: DNS Server 数据接收线程启动失败。进程退出。");
			exit(0);
		}

		//向DCS注册
		Login();

		//uint64 still_time = CTimeBase::get_current_time();
		for(;;)
		{
			int liCurrentParentId = getppid();
			if((liParentId != liCurrentParentId) || (1 == liCurrentParentId))
			{
				TRACE(1, "CDNSChildWorker::Run 父进程退出了。ID = "<<liParentId<<
					" CurrentId = "<<liCurrentParentId);
				break;
			}

			TimeOutWork();

			usleep(1000*1000);

			//uint64 time_now = CTimeBase::get_current_time();
			//if(time_now > still_time + 1000*60*5)
			//{
			//	break;
			//}
		}

		Logout();

		m_DnsServer.Delfd(m_pDnsListenFd->miSocket);
		m_DnsServer.Delfd(m_DcsNodeFd.miSocket);
		m_DnsServer.Destroy();
	}
	catch (...)
	{
		TRACE(1, "CDNSChildWorker::Run 出现异常。");
	}
	return;
}

void CDNSChildWorker::TimeOutWork()
{
	//检测和DCS的链接状态
	if(m_DcsNodeFd.moNetStat == TCP_CLOSED)
	{
		TRACE(1, "CDNSChildWorker::TimeOutWork 和DCS链接断开了。");
	}
	uint64 time_now = CTimeBase::get_current_time();
	//发送存活
	if(time_now > m_i64LastKeepLive + KEEP_LIVE_TIME_OUT * 1000)
	{
		KeepLive();
		m_i64LastKeepLive = time_now;
	}

	//dump
	if(time_now > m_i64LastDumpTime + m_pDnsConfig->dump_info_time * 1000)
	{
		Dump();
		m_i64LastDumpTime = time_now;
	}

	//log
	if(time_now > m_i64LastLogTime + m_pDnsConfig->log_file_update_time*1000)
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

	if(time_now > m_i64LastCheckTimeOut + CRS_DNS_TIMEOUT * 1000)
	{
		CheckTimeOut();
		//test();
		m_i64LastCheckTimeOut = time_now;
	}
}

void CDNSChildWorker::Dump()
{

}

void CDNSChildWorker::KeepLive()
{
	char buffer[DCS_DNS_BUFFER_LEN] = {0};
	stru_DCS_DNS_KEEP_LIVE_RQ rq;
	rq.m_iDnsIp = htonl(m_pDnsConfig->server_ip);
	rq.m_iDnsId = getpid();
	int len = rq.Pack(buffer,DCS_DNS_BUFFER_LEN);
	m_DnsServer.SendData(m_DcsNodeFd.miSocket, buffer, len);
}

void CDNSChildWorker::Login()
{
	char buffer[DCS_DNS_BUFFER_LEN] = {0};
	stru_DCS_DNS_LOGIN_RQ rq;
	rq.m_iDnsIp = htonl(m_pDnsConfig->server_ip);
	rq.m_iDnsId = getpid();
	int len = rq.Pack(buffer,DCS_DNS_BUFFER_LEN);
	m_DnsServer.SendData(m_DcsNodeFd.miSocket, buffer, len);
	TRACE(1, "CDNSChildWorker::Login  PID ="<<getpid());
}

void CDNSChildWorker::Logout()
{
	char buffer[DCS_DNS_BUFFER_LEN] = {0};
	stru_DCS_DNS_LOGOUT_RQ rq;
	rq.m_iDnsIp = htonl(m_pDnsConfig->server_ip);
	rq.m_iDnsId = getpid();
	int len = rq.Pack(buffer,DCS_DNS_BUFFER_LEN);
	m_DnsServer.SendData(m_DcsNodeFd.miSocket, buffer, len);
}

void CDNSChildWorker::OnDealErrorFd(int fd)
{
	if(fd == m_DcsNodeFd.miSocket)
	{
		TRACE(1, "CDNSChildWorker::OnDealErrorFd dcs error");
		m_DcsNodeFd.moNetStat = TCP_CLOSED;
	}
	TRACE(1, "CDNSChildWorker::OnDealErrorFd fd error : fd = "<<fd);
}
void CDNSChildWorker::DealNetData(int fd, char *buffer, int length)
{
	if(fd == m_DcsNodeFd.miSocket)
	{
		DealDcsData(buffer, length);
	}
	else
	{
		DealCrsData(fd, buffer, length);
	}
}
void CDNSChildWorker::DealCrsData(int fd, char *buffer, int length)
{
	uint16 lui16type = 0;
	memcpy(&lui16type,buffer,sizeof(uint16));
	char pack_buffer[DNS_CRS_BUFFER_LEN*2] = {0};
	int pack_length = 0;
	switch(lui16type)
	{
	case PACK_DNS_CRS_LOGIN_RQ:
		{
			stru_DNS_CRS_LOGIN_RQ rq;
			stru_DNS_CRS_LOGIN_RS rs;
			rq.UnPack(buffer,length);
			PSTRU_DNS_NODE_INFO  pHall_info = new STRU_DNS_NODE_INFO;
			pHall_info->fd = fd;
			pHall_info->m_i32NodeId = rq.m_i32NodeId;
			pHall_info->m_i32GroupId = rq.m_i32GroupId;
			pHall_info->m_iTimeStamp = CTimeBase::get_current_time();
			SetAlive(rq.m_i32NodeId,pHall_info);
			rs.m_i32NodeId = rq.m_i32NodeId;
			rs.m_iDnsId = getpid();
			pack_length = rs.Pack(pack_buffer,DNS_CRS_BUFFER_LEN*2);
			m_DnsServer.SendData(fd,pack_buffer,pack_length);
			break;
		}
	case PACK_DNS_CRS_KEEP_LIVE_RQ:
		{
			stru_DNS_CRS_KEEP_LIVE_RQ rq;
			stru_DNS_CRS_KEEP_LIVE_RS rs;
			rq.UnPack(buffer,length);
			rs.m_i32NodeId = rq.m_i32NodeId;
			rs.m_iDnsId = getpid();
			SetAlive(rq.m_i32NodeId);
			pack_length = rs.Pack(pack_buffer,DNS_CRS_BUFFER_LEN*2);
			m_DnsServer.SendData(fd,pack_buffer,pack_length);
			break;
		}
	case PACK_DNS_CRS_LOGOUT_RQ:
		{
			stru_DNS_CRS_LOGOUT_RQ rq;
			stru_DNS_CRS_LOGOUT_RS rs;
			rq.UnPack(buffer,length);
			rs.m_i32NodeId = rq.m_i32NodeId;
			rs.m_iDnsId = getpid();
			RemoveHall(rq.m_i32NodeId);
			pack_length = rs.Pack(pack_buffer,DNS_CRS_BUFFER_LEN*2);
			m_DnsServer.SendData(fd,pack_buffer,pack_length);
			break;
		}
	case PACK_DNS_CRS_MESSAGE:
		{
			int toFd = 0;
			stru_DNS_CRS_MESSAGE rq;
			stru_DCS_DNS_MESSAGE msg;
			rq.UnPack(buffer,length);
			SetAlive(rq.m_i32NodeId);

			msg.m_iDnsIp = htonl(m_pDnsConfig->server_ip);
			msg.m_iDnsId = getpid();
			msg.m_iDatalen = length;
			memcpy(msg.m_cDataBuf,buffer,length);
			pack_length = msg.Pack(pack_buffer,DNS_CRS_BUFFER_LEN*2);
			if(rq.m_i32TargetNode >0)
			{
				toFd = GetFDByHallId(rq.m_i32TargetNode);
			}
			if(toFd > 0)
			{
				m_DnsServer.SendData(toFd,msg.m_cDataBuf,msg.m_iDatalen);
				//TRACE(3, "CDNSChildWorker::DealCrsData transfer message from "<<rq.m_i32NodeId<<" to "<<rq.m_i32TargetNode);
			}
			else
			{
				m_DnsServer.SendData(m_DcsNodeFd.miSocket, pack_buffer,pack_length);
				//TRACE(3, "CDNSChildWorker::DealCrsData transfer message from "<<rq.m_i32NodeId <<" to dcs");
			}	

			break;
		}
	default:
		{
			TRACE(3, "CDNSChildWorker::DealCrsData unkonw message type type = "<<lui16type);
		}
	}

	//TRACE(5, "CDNSChildWorker::DealCrsData fd = "<<fd);
}

void CDNSChildWorker::DealDcsData(char *buffer, int length)
{
	uint16 lui16type = 0;
	memcpy(&lui16type,buffer,sizeof(uint16));
	switch(lui16type)
	{
	case PACK_DCS_DNS_LOGIN_RS :
		{
			TRACE(1, "CDNSChildWorker::DealDcsData PACK_DCS_DNS_LOGIN_RS");
			break;
		}
	case PACK_DCS_DNS_KEEP_LIVE_RS :
		{
			//TRACE(5, "CDNSChildWorker::DealDcsData PACK_DCS_DNS_KEEP_LIVE_RS");
			break;
		}
	case PACK_DCS_DNS_LOGOUT_RS :
		{
			TRACE(1, "CDNSChildWorker::DealDcsData PACK_DCS_DNS_LOGOUT_RS");
			break;
		}
	case PACK_DCS_DNS_MESSAGE :
		{
			stru_DCS_DNS_MESSAGE rq;
			stru_DNS_CRS_MESSAGE msg;
			rq.UnPack(buffer,length);

			msg.UnPack(rq.m_cDataBuf,rq.m_iDatalen);
			if(msg.m_i32TargetNode != 0)
			{
				int fd = GetFDByHallId(msg.m_i32TargetNode);
				if(fd >0)
				{
					m_DnsServer.SendData(fd, rq.m_cDataBuf,rq.m_iDatalen);

				}
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message buffer length "<<length);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message from "<<msg.m_i32NodeId<<" To HallId "<<msg.m_i32TargetNode);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message len "<<msg.m_iDataLen);
			}
			else if( msg.m_i32TargetGroup != 0)
			{
				SendByChatRootType(msg.m_i32TargetGroup,rq.m_cDataBuf,rq.m_iDatalen);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message buffer length "<<length);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message from "<<msg.m_i32NodeId<<" To ChatRoomType "<<msg.m_i32TargetGroup);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message len "<<msg.m_iDataLen);

			}
			else
			{
				m_DnsServer.SendAllData(rq.m_cDataBuf,rq.m_iDatalen);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message buffer length "<<length);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message from "<<msg.m_i32NodeId<<" To ChatRoomType "<<msg.m_i32TargetGroup);
				//TRACE(3, "CDNSChildWorker::DealDcsData recv message len "<<msg.m_iDataLen);
			}

			break;
		}
	default:
		{
			TRACE(1, "CDNSChildWorker::DealDcsData 未知包ID : "<<lui16type);
			break;
		}
	}
	//TRACE(1, "CDNSChildWorker::DealDcsData");
}

int CDNSChildWorker::SetAlive(uint32 hallId ,PSTRU_DNS_NODE_INFO phall)
{

	int liRet = -1;
	CAutoLock lock(mSection);
	std::map<uint32,PSTRU_DNS_NODE_INFO>::iterator it = mHallList.find(hallId);
	try{
		if(it != mHallList.end())
		{
			it->second->m_iTimeStamp = CTimeBase::get_current_time();
			liRet = 0;

			if(phall != NULL)
			{
				it->second->fd = phall->fd;
				delete phall;
			}
		}
		else
		{
			if(phall != NULL)
			{
				it = mHallList.begin();
				while(it != mHallList.end())
				{
					//
					if(it->second->fd == phall->fd)
					{
						mHallList.erase(it);
						break;
					}
					it++;
				}
				mHallList[hallId] = phall;
				liRet = 0;
			}
		}
	}
	catch(...)
	{
		liRet = -1;
		TRACE(1, "CDNSChildWorker::SetAlive catch ");
	}

	return liRet;
}

int CDNSChildWorker::GetFDByHallId(uint32 hallId)
{
	int liRet = -1;
	CAutoLock lock(mSection);
	std::map<uint32,PSTRU_DNS_NODE_INFO>::iterator it = mHallList.find(hallId);
	if(it != mHallList.end())
	{

		liRet = it->second->fd;

	}
	return liRet;
}

int CDNSChildWorker::RemoveHall(uint32 hallid)
{
	int liRet = -1;
	CAutoLock lock(mSection);
	std::map<uint32,PSTRU_DNS_NODE_INFO>::iterator it = mHallList.find(hallid);
	try
	{
		if(it != mHallList.end())
		{
			delete it->second;
			mHallList.erase(it);
			liRet = 0;
		}
	}
	catch(...)
	{
		liRet = -1;
	}
	return liRet;

}

int CDNSChildWorker::CheckTimeOut()
{
	int liRet = -1;
	uint64 time_now = CTimeBase::get_current_time();
	CAutoLock lock(mSection);
	std::map<uint32,PSTRU_DNS_NODE_INFO>::iterator it = mHallList.begin();
	while(it != mHallList.end())
	{
		if(time_now > it->second->m_iTimeStamp + CRS_DNS_TIMEOUT*1000)
		{
			delete it->second;
			TRACE(1, "CDNSChildWorker::CheckTimeOut hallId "<<it->first<<" Timeout");
			mHallList.erase(it++);
			continue;
		}
		it++;
	}
	return liRet;
}

int CDNSChildWorker::SendByChatRootType(uint32 type,const char *buffer, const uint32 length)
{
	int liRet = 0;
	CAutoLock lock(mSection);
	std::map<uint32,PSTRU_DNS_NODE_INFO>::iterator it = mHallList.begin();
	while(it != mHallList.end())
	{
		if(it->second->m_i32GroupId == type)
		{
			m_DnsServer.SendData(it->second->fd, buffer,length);
			//TRACE(3, "CDNSChildWorker::SendByChatRootType hallId "<<it->first<<" ChatRootType " <<it->second->m_i32GroupId);
		}
		it++;
	}
	return liRet;
}

void CDNSChildWorker::DealDcsDataComplete(int rtn_op, int fd, CBasePack* pack)
{

}
void CDNSChildWorker::DealCrsDataComplete(int rtn_op, int fd, CBasePack* pack)
{

}