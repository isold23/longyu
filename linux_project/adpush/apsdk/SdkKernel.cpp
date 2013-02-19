#include "SdkKernel.h"


static CKernel gSdkKernel;

#if defined(_WIN32)
void __stdcall CreateObject(ISdkKernel** ppSdkKernel)
#else
void CreateObject(ISdkKernel** ppSdkKernel)
#endif
{
	*ppSdkKernel = &gSdkKernel;
}


unsigned int __stdcall NetWorkThreadFun(STRU_THREAD_CONTEXT &aoContext)
{
	CKernel *lpInterface = reinterpret_cast<CKernel*>(aoContext.mpWorkContext);
	lpInterface->NetWork(&aoContext);
	return 1;
}

void OnErrorNotify(void* param, uint32_t fd)
{
	CKernel* pThis = (CKernel*)param;
	if(pThis)
		pThis->OnErrorNotify(fd);
}
void OnConnectNotify(void* param, uint32_t fd)
{
	CKernel* pThis = (CKernel*)param;
	if(pThis)
		pThis->OnConnectNotify(fd);
}


void OnRecvDataNotify(void* param, uint32_t fd, char *buffer, uint32_t length)
{
	CKernel* pThis = (CKernel*)param;
	if(pThis)
		pThis->OnRecvDataNotify(fd, buffer, length);
}

CKernel::CKernel()
{
	mNetSelect.SetCallBackFun(::OnErrorNotify, ::OnConnectNotify, ::OnRecvDataNotify, this);

	m_RoomKernel.SetKernelService(this);
	m_MpsKernel.SetKernelService(this);

	m_uiErrorCode = 0;

	m_bNetThreadWait = true;

	mbNetThreadExit = false;

	mi64LastKeepLiveTime = CCommon::get_current_time();

	mNetSelect.Init();

	mpTcpSession.SetNetPack(&m_objCrsNetPack);
	m_mpsFd.SetNetPack(&m_objMpssNetPack);

	mNetThreadEvent.Create();
	mNetThreadExitEvent.Create();
	//启动线程
	thread_group.Start(NetWorkThreadFun, this, 1, "NetWorkThread");
}

CKernel::~CKernel()
{
	mNetThreadEvent.SetEvent();

	mbNetThreadExit = true;

	mNetThreadExitEvent.WaitForEvent(-1);

	mNetThreadExitEvent.Close();

	mNetThreadEvent.Close();

	mNetSelect.Destroy();
}

void CKernel::AddTask(Task* pTask)
{
	m_TaskQueue.Push(pTask);

	m_pSdkProcess->NewTaskEvent();
}

void CKernel::SendRoomData(char* data, uint16_t wLen)
{
	mpTcpSession.SendData(data, wLen);
}

uint32_t CKernel::GetLastError()
{
	return m_uiErrorCode;
}

void CKernel::ConnectRoom(const char* aspszServerAddr, uint16_t awServerPort)
{
	mpTcpSession.CreateSocket();
	mpTcpSession.SetNoBlock();
	mNetSelect.Addfd(&mpTcpSession);
	mNetThreadEvent.SetEvent();
	mpTcpSession.ConnectServer(aspszServerAddr, awServerPort);
}

void CKernel::CloseRoom()
{
	mNetSelect.Delfd(&mpTcpSession);
	mpTcpSession.Close(2);

	if(mNetSelect.m_currentFdNum <= 0)
	{
		mNetThreadEvent.ResetEvent();
		m_bNetThreadWait = true;
	}
}

void CKernel::SendMpsData(char* data, uint16_t wLen)
{
	m_mpsFd.SendData(data, wLen);
}

void CKernel::ConnectMps(const char* aspszServerAddr, uint16_t awServerPort)
{
	if(m_mpsFd.moNetStat == COMMON_TCP_CLOSED)
	{
		m_mpsFd.CreateSocket();
		m_mpsFd.SetNoBlock();
		mNetSelect.Addfd(&m_mpsFd);
		mNetThreadEvent.SetEvent();
		m_mpsFd.ConnectServer(aspszServerAddr, awServerPort);
	}
}

void CKernel::CloseMpsConnection()
{
	mNetSelect.Delfd(&m_mpsFd);
	m_mpsFd.Close(2);

	if(mNetSelect.m_currentFdNum <= 0)
	{
		mNetThreadEvent.ResetEvent();
		m_bNetThreadWait = true;
	}
}

bool CKernel::QueryInterface(uint32_t uID, void** ppVoid)
{
	*ppVoid = NULL;

	m_RoomKernel.QueryInterface(uID, ppVoid);
	if(*ppVoid == NULL)
		m_MpsKernel.QueryInterface(uID, ppVoid);

	return (*ppVoid) != NULL;
}

void CKernel::SetProcess(ISdkProcess* pSdkProcess)
{
	m_pSdkProcess = pSdkProcess;
	m_RoomKernel.SetProcess(pSdkProcess);
	m_MpsKernel.SetProcess(pSdkProcess);
}

void CKernel::SolveTask()
{
	m_TaskQueue.Run();
}

void CKernel::SetUserInfo(int64_t ai64UserID, const char* apszNick, const char* apszPsw, uint16_t usPhotoNm)
{
	m_struUserInfo.m_i64UserID = ai64UserID;
	m_struUserInfo.m_strUserNick = apszNick;
	m_struUserInfo.m_strUserPsw = apszPsw;
	m_struUserInfo.m_wPhotoNm = usPhotoNm;

	char lacEnPwd[33];
	CCommon::MakeMD5WithBuffer32((uint8_t*)(apszPsw), strlen(apszPsw), (uint8_t*)lacEnPwd);
	lacEnPwd[29] = '\0';
	m_struUserInfo.m_strPswMd5 = lacEnPwd+5;
}

void  CKernel::SetNetInfo(int32_t netType,const char* proxyIP, int proxyPort,const char* proxyUser,const char* proxyPwd)
{
	//mpTcpSession->SetNetInfo(netType, proxyIP, proxyPort, proxyUser, proxyPwd);
}

void CKernel::OnErrorNotify(uint32_t fd)
{
	if(fd == mpTcpSession.miSocket)
	{
		mNetSelect.Delfd(&mpTcpSession);
		mpTcpSession.Close(2);
		m_RoomKernel.OnErrTCPSession(0, m_RoomKernel.GetCurrRoomID());
	}
	else if(fd == m_mpsFd.miSocket)
	{
		//处理mps连接异常
		mNetSelect.Delfd(&m_mpsFd);
		m_mpsFd.Close(2);
		m_MpsKernel.OnConnectError();
	}

	if(mNetSelect.m_currentFdNum <= 0)
	{
		mNetThreadEvent.ResetEvent();
		m_bNetThreadWait = true;
	}
}

void CKernel::OnConnectNotify(uint32_t fd)
{
	if(fd == mpTcpSession.miSocket)
	{
		m_RoomKernel.OnOpenTCPSession(m_RoomKernel.GetCurrRoomID());
	}
	else if(fd == m_mpsFd.miSocket)
	{
		 //处理mps连接异常
		m_MpsKernel.OnConnected();
	}
}

void CKernel::OnRecvDataNotify(uint32_t fd, char *buffer, uint32_t length)
{
	if(fd == mpTcpSession.miSocket)
	{
		m_RoomKernel.SolveMsg(buffer, length);
	}
 	else if(fd == m_mpsFd.miSocket)
 	{
 		//处理mps数据包
		m_MpsKernel.SolveMsg(buffer, length);
 	}
}

unsigned int CKernel::NetWork(STRU_THREAD_CONTEXT *aoContext){
	while(true){
		if(m_bNetThreadWait){
			mNetThreadEvent.WaitForEvent(-1);
			m_bNetThreadWait = false;
		}

		if(mbNetThreadExit){
			mNetThreadExitEvent.SetEvent();
			return 0;
		}

		int nRet = mNetSelect.CheckEvent();
		mNetSelect.ProcessEvent(nRet);

		//发送存活,取消存活发送，有底层来维持连接。
		int64_t time_now = CCommon::get_current_time();
		if(time_now > mi64LastKeepLiveTime + 30*1000){
			m_RoomKernel.KeepLive();
			mi64LastKeepLiveTime = time_now;
		}
		CCommon::thread_sleep(20);
	}
	return 0;
}