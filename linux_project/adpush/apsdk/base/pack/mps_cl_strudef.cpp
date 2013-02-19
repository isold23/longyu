#include "mps_cl_strudef.h"

#include <android/log.h>

int STRU_CL_TCP_MPS_PKG_BASE::Pack(char* apBuffer, int alLen)
{
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );													
	if(Serialize(loSerialize) == -1) 													
	{ 																					
		return -1; 																	
	} 

	return loSerialize.getDataLen(); 
}

int STRU_CL_TCP_MPS_PKG_BASE::UnPack(char* apBuffer, int alLen)
{
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );												
	if (Serialize(loSerialize) == -1) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 
}

STRU_CL_TCP_MPS_PKG_BASE::STRU_CL_TCP_MPS_PKG_BASE()
{
	u32Timestamp = htonl((u_long)time(NULL));
}

int STRU_CL_TCP_MPS_PKG_BASE::Serialize(CStandardSerialize& aoStandardSerialize)
{
	if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		aoStandardSerialize.Serialize(u16MsgType);
		u16MsgType = ntohs(u16MsgType);
	}
	else
	{	
		aoStandardSerialize.Serialize(u16MsgType);
	}
	aoStandardSerialize.Serialize(u32Seq);
	aoStandardSerialize.Serialize(u32Timestamp);
	return 1;
}

STRU_CL_TCP_MPS_PKG_LOGIN_RQ::STRU_CL_TCP_MPS_PKG_LOGIN_RQ()
{
	u16MsgType = htons(LOGIN_REQ); 
}

int STRU_CL_TCP_MPS_PKG_LOGIN_RQ::Serialize(CStandardSerialize& aoStandardSerialize)
{
	if(STRU_CL_TCP_MPS_PKG_BASE::Serialize(aoStandardSerialize))
	{
		if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
		{
			aoStandardSerialize.Serialize(u64UsrId);
			aoStandardSerialize.Serialize(u16SvcId);
			aoStandardSerialize.Serialize(u32CommAttr);
			aoStandardSerialize.Serialize(chPrivateAttr, PRIVATE_ATTR_SIZE, PRIVATE_ATTR_SIZE);

			u64UsrId = CCommon::_ntohq(u64UsrId);
			u16SvcId = ntohs(u16SvcId);
			u32CommAttr = ntohl(u32CommAttr);
		}
		else
		{
						__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::DealPack:PUSH_MSG_REQ","user_id2 = %llx", u64UsrId);
			u64UsrId = CCommon::_htonq(u64UsrId);
							__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::DealPack:PUSH_MSG_REQ","user_id3 = %llx", u64UsrId);
			u16SvcId = htons(u16SvcId);
			u32CommAttr = htonl(u32CommAttr);

			aoStandardSerialize.Serialize(u64UsrId);
			
			__android_log_print(ANDROID_LOG_INFO,"CMpsKernel::DealPack:PUSH_MSG_REQ","user_id1 = %llx", u64UsrId);
			aoStandardSerialize.Serialize(u16SvcId);
			aoStandardSerialize.Serialize(u32CommAttr);
			aoStandardSerialize.Serialize(chPrivateAttr, PRIVATE_ATTR_SIZE, PRIVATE_ATTR_SIZE);
		}
		
		return 1;
	}
	else
		return -1;
}

STRU_CL_TCP_MPS_PKG_LOGIN_ACK::STRU_CL_TCP_MPS_PKG_LOGIN_ACK()
{
	u16MsgType = htons(LOGIN_ACK); 
	szErrMsg = NULL;
}

STRU_CL_TCP_MPS_PKG_LOGIN_ACK::~STRU_CL_TCP_MPS_PKG_LOGIN_ACK()
{
	if(szErrMsg != NULL)
	{
		delete [] szErrMsg;
	}
}

int STRU_CL_TCP_MPS_PKG_LOGIN_ACK::Serialize(CStandardSerialize& aoStandardSerialize)
{
	if(STRU_CL_TCP_MPS_PKG_BASE::Serialize(aoStandardSerialize))
	{
		if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
		{
			aoStandardSerialize.Serialize(u16RetCode);
			aoStandardSerialize.Serialize(u8ErrMsgEncoding);
			aoStandardSerialize.Serialize(u16ErrMsgLen);

			u16RetCode = ntohs(u16RetCode);
			u16ErrMsgLen = ntohs(u16ErrMsgLen);
			szErrMsg = new char[u16ErrMsgLen+1];
			szErrMsg[u16ErrMsgLen] = '\0';
			aoStandardSerialize.Serialize(szErrMsg, u16ErrMsgLen, u16ErrMsgLen);
		}
		else
		{
			u16RetCode = htons(u16RetCode);
			uint16_t lu16ErrMsgLen = htons(u16ErrMsgLen);

			aoStandardSerialize.Serialize(u16RetCode);
			aoStandardSerialize.Serialize(u8ErrMsgEncoding);
			aoStandardSerialize.Serialize(lu16ErrMsgLen);
			aoStandardSerialize.Serialize(szErrMsg, u16ErrMsgLen, u16ErrMsgLen);
		}

		return 1;
	}
	else
		return -1;
}

STRU_CL_TCP_MPS_PKG_PUSH_MSG::STRU_CL_TCP_MPS_PKG_PUSH_MSG()
{
	u16MsgType = htons(PUSH_MSG_REQ); 
	szMsg = NULL;
}

STRU_CL_TCP_MPS_PKG_PUSH_MSG::~STRU_CL_TCP_MPS_PKG_PUSH_MSG()
{
	if(szMsg != NULL)
	{
		delete [] szMsg;
	}
}

int STRU_CL_TCP_MPS_PKG_PUSH_MSG::Serialize(CStandardSerialize& aoStandardSerialize)
{
	if(STRU_CL_TCP_MPS_PKG_BASE::Serialize(aoStandardSerialize))
	{
		if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
		{
			aoStandardSerialize.Serialize(u8MsgEncoding);
			aoStandardSerialize.Serialize(u16MsgLen);
			
			u16MsgLen = ntohs(u16MsgLen);
			szMsg = new char[u16MsgLen + 1];
			szMsg[u16MsgLen] = '\0';
			aoStandardSerialize.Serialize(szMsg, u16MsgLen, u16MsgLen);
		}
		else
		{
			uint16_t lu16MsgLen = htons(u16MsgLen);
			aoStandardSerialize.Serialize(u8MsgEncoding);
			aoStandardSerialize.Serialize(lu16MsgLen);
			aoStandardSerialize.Serialize(szMsg, u16MsgLen, u16MsgLen);
		}

		return 1;
	}
	else
		return -1;
}