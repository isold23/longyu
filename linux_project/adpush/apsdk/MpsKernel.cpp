#include "MpsKernel.h"
#include "base/task/task_queue.h"


#include <android/log.h>

#define SETBIT(x,y)  x|=(1<<y) //将X的第Y位置1 
#define CLRBIT(x,y)  x&=~(1<<y) //将X的第Y位清0

CMpsKernel::CMpsKernel()
{
	m_pKernelService = 0;
	m_pMpsProcess = 0;
	m_ui16Port= 0;
    m_ui16SvrID = DEF_PROPSMPS_SRVID;
}

CMpsKernel::~CMpsKernel()
{

}

void CMpsKernel::SetProcess(ISdkProcess* pSdkProcess)
{
	if(pSdkProcess)
	{
		pSdkProcess->QueryInterface(UID_MPS_PROCESS, (void**)&m_pMpsProcess);
	}
}

//请求接口
bool CMpsKernel::QueryInterface(uint32_t uID, void** ppVoid)
{
	*ppVoid = NULL;

	switch (uID)
	{
	case UID_MPS_KERNEL:
		*ppVoid = static_cast<IMpsKernel*>(this);
		break;
	}

	return (*ppVoid) != NULL;
}

void CMpsKernel::OnConnectError()
{
	m_pKernelService->CloseMpsConnection();
	//重连
	m_pKernelService->ConnectMps(m_strAddr.c_str(), m_ui16Port);	
}

void CMpsKernel::OnConnected()
{
	SendLoginRQ();
}

void CMpsKernel::SolveMsg(char * apPackData, uint16_t awPackDataLen)
{
	ScopedRunnableMethodFactory<CMpsKernel> t(this);
	char* date = new char[awPackDataLen];
	memcpy(date, apPackData, awPackDataLen);

	Task* pTask = t.NewRunnableMethod(&CMpsKernel::DealPack, date, awPackDataLen);
	m_pKernelService->AddTask(pTask);

	DeleteTask<char>* pDelTask = new DeleteTask<char>(date);
	m_pKernelService->AddTask(pDelTask);

}

void CMpsKernel::DealPack(char* pDate, uint16_t wDataLen)
{
	uint16_t lwPackType	 = 0;
	memcpy(&lwPackType, pDate, 2);
	lwPackType = ntohs(lwPackType);
	switch (lwPackType)
	{
	case LOGIN_ACK:
		{
			STRU_CL_TCP_MPS_PKG_LOGIN_ACK lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				DealLoginRS(&lstru);
			}
		}
		break;
	case PUSH_MSG_REQ:
		{
			STRU_CL_TCP_MPS_PKG_PUSH_MSG lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::DealPack:PUSH_MSG_REQ","msg_len = %d", lstru.u16MsgLen);
				if(m_pMpsProcess)
					m_pMpsProcess->OnMpsNotify(lstru.u8MsgEncoding, lstru.szMsg);
			}	
		}
		break;
	}
}

void CMpsKernel::ConnectMps(char* szAddr, uint16_t usPort)
{
	struct hostent *pSrvHost = NULL;
	if (isalpha(szAddr[0]))
	{
		struct sockaddr_in stAddrSrv;
		pSrvHost = gethostbyname(szAddr);
		memcpy (&stAddrSrv.sin_addr.s_addr, pSrvHost->h_addr_list[0], pSrvHost->h_length); 
		m_strAddr = inet_ntoa(stAddrSrv.sin_addr);
	}
	else
	{
		m_strAddr = szAddr;
	}
	
	m_ui16Port = usPort;

	if(m_pKernelService->GetUserInfo().m_i64UserID != 0)
	{
		m_pKernelService->ConnectMps(m_strAddr.c_str(), m_ui16Port);	
	}
}

void CMpsKernel::CloseMpsConnection()
{
	if( m_pKernelService != NULL )
	{
		m_pKernelService->CloseMpsConnection();
	}
}

void CMpsKernel::SetServerID( uint16_t sid )
{
    m_ui16SvrID = sid;
}

void CMpsKernel::SendLoginRQ()
{
	char byPrivateAttr[PRIVATE_ATTR_SIZE] = {0};
	uint32_t liCommAttr = 0;
	MakeMPSAttr(0, byPrivateAttr, liCommAttr);
	STRU_CL_TCP_MPS_PKG_LOGIN_RQ struLogin;
	struLogin.u64UsrId = m_pKernelService->GetUserInfo().m_i64UserID;
	__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::SendLoginRQ","user_id = %llx", m_pKernelService->GetUserInfo().m_i64UserID);
	__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::SendLoginRQ","user_id = %llx", struLogin.u64UsrId);
    // Server ID
    struLogin.u16SvcId = m_ui16SvrID;
  __android_log_print(ANDROID_LOG_INFO,"CMpsKernel::SendLoginRQ","svr_id = %d",m_ui16SvrID);
	struLogin.u32CommAttr = liCommAttr;
	memcpy(struLogin.chPrivateAttr, byPrivateAttr, sizeof(struLogin.chPrivateAttr));

	char lszPack[WHOLE_PACK_DATA_LEN];
	uint16_t lwDataLen = struLogin.Pack(lszPack, WHOLE_PACK_DATA_LEN);
	if(lwDataLen > 0 && m_pKernelService)
	{
		m_pKernelService->SendMpsData(lszPack, lwDataLen);
	}
}

void CMpsKernel::MakeMPSAttr(int32_t lRedTime, char *byPrivateAttr, uint32_t &uCommAttr)
{
	memset(byPrivateAttr, 0x00, PRIVATE_ATTR_SIZE);
	uCommAttr &= 0;
	uint8_t byAge = 32;
	uint8_t byGender = 2;

	//年龄
	byAge &= 0xFF;//清空末尾8位之前的所有位
	uCommAttr = byAge;
	uCommAttr = uCommAttr << 8;
	//性别
	byGender &= 0x03;//清空末尾8位之前的所有位
	uCommAttr |= byGender;

	//版本号
	byPrivateAttr[1] = SINA_SHOW_MPS_VERSION;

	SETBIT(byPrivateAttr[0],0);

	//是否是秀星
	if (lRedTime > 0)
	{//是秀星
		SETBIT(byPrivateAttr[0],1);
	} 
	else
	{//不是秀星
		CLRBIT(byPrivateAttr[0],1);
	}
}

void CMpsKernel::DealLoginRS(STRU_CL_TCP_MPS_PKG_LOGIN_ACK* pStru)
{
	__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::DealLoginRS","user_id = %d", pStru->u16RetCode);
	int nOptStatus = 0; // 低1位表示登录成功，低2位表示是否需要退出连接
	switch (pStru->u16RetCode)
	{
	case LOGIN_SUCCESS :
		{
			nOptStatus |= 0x01;
		}
		break;
	case LOGIN_REDIRECT :
		{
 			m_strAddr  = *((uint32_t*)&pStru->szErrMsg[0]);
 			m_ui16Port = *((uint16_t*)&pStru->szErrMsg[sizeof(uint32_t)]);
 
 			// 断开服务器使得重连到新的服务器IP
			m_pKernelService->CloseMpsConnection();
			//重连
			m_pKernelService->ConnectMps(m_strAddr.c_str(), m_ui16Port);	
		}
		break;
	case LOGIN_UNALLOW :
		{
			nOptStatus |= 0x02;
		}
		break;
	case LOGIN_SYSERROR :
	default :
		{
		}
		break;
	}

	if (nOptStatus & 0x02) // 出现非法登录请求则退出线程
	{
		m_pKernelService->CloseMpsConnection();
	}
	else if (!(nOptStatus & 0x01)) // 如果没有登录成功，则断掉连接触发重连机制
	{
		m_pKernelService->CloseMpsConnection();
		//重连
		m_pKernelService->ConnectMps(m_strAddr.c_str(), m_ui16Port);	
	}
}