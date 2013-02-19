#include "BaseKernel.h"

void CBaseKernel::LoginRoom()
{
	if(m_pRoomKernelService->GetUserInfo().m_i64UserID == 0)
	{
		STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ lStru;
		strcpy(lStru.macVersion, "1.01");
		AutoSendPack(lStru);
		return;
	}
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007 lstruLogin;
	lstruLogin.mlHallID = m_pRoomKernelService->GetCurrRoomID();
	lstruLogin.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	strncpy(lstruLogin.macNickName, m_pRoomKernelService->GetUserInfo().m_strUserNick.c_str(),  sizeof(lstruLogin.macNickName));
	strncpy(lstruLogin.macUserPwd, m_pRoomKernelService->GetUserInfo().m_strPswMd5.c_str(), sizeof(lstruLogin.macUserPwd));
	strncpy(lstruLogin.macPassword, m_strPsw.c_str(), sizeof(lstruLogin.macPassword));
	lstruLogin.mwPhotoNum = m_pRoomKernelService->GetUserInfo().m_wPhotoNm;
	strncpy(lstruLogin.macVersion, m_strVersion.c_str(),sizeof(lstruLogin.macVersion));
	if(m_bHaveVideo)
		lstruLogin.mlUserState = 1;

	lstruLogin.mbySource = m_byLoginSource;
	lstruLogin.mbyAttributeCount = STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO::ATTRIBUTETYPE_MAX;
	lstruLogin.mpAttributeInfo = new STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO[lstruLogin.mbyAttributeCount];

	for (int i = 0; i < lstruLogin.mbyAttributeCount; i++)
	{
        switch (i) {
            case STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO::AT_PCHAR_MACHINE_CODE:
            {
                lstruLogin.mpAttributeInfo[i].menumAttributeType = i;
                lstruLogin.mpAttributeInfo[i].mPbVal = (char*)m_strMachineCode.c_str();
                lstruLogin.mpAttributeInfo[i].mnDateLen = m_strMachineCode.size();
            }
                break;
                
            default:
            {
                lstruLogin.mpAttributeInfo[0].menumAttributeType = i;
                lstruLogin.mpAttributeInfo[i].mPbVal = "";
                lstruLogin.mpAttributeInfo[i].mnDateLen = 1;
            }
                break;
        }
	}

	AutoSendPack(lstruLogin);
}

void  CBaseKernel::Initialize(char* apszVersion, bool abHaveVideo, uint8_t abyLoginSource)
{
	m_strVersion = apszVersion;

	m_bHaveVideo = abHaveVideo;

	m_byLoginSource = abyLoginSource;
}

void  CBaseKernel::LoginRoom( int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort, const char* pszRoomPsw, const char* pszMachineCode )
{
	m_strPsw = pszRoomPsw;

    m_strMachineCode = pszMachineCode;
    
	if(m_pRoomKernelService)
	{
		if(m_pRoomKernelService->GetCurrRoomID() != alRoomId)
		{
			m_pRoomKernelService->ConnectRoom(alRoomId, aspszServerAddr, awServerPort);
		}
	}
}

void  CBaseKernel::LogOut(int32_t alRoomId)
{
	if(m_pRoomKernelService)
	{
		m_pRoomKernelService->CloseRoom(alRoomId);	
	}
}

void  CBaseKernel::SendFlower( int64_t ai64SendTo, uint8_t abyFlowerIndex )
{
	STRU_UC_CL_CRS_FLOWERS_ID lStru;
	lStru.mi64SrcUserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DstUserID = ai64SendTo;
	lStru.mlFlowerType = abyFlowerIndex;

	AutoSendPack(lStru);
}

void  CBaseKernel::SendChat( uint8_t byChatType, int64_t ai64SendTo, char* apszMood, char* apszContrl, char* apszContent )
{
	STRU_UC_CL_CRS_DATA_ID_350 lStru;
	lStru.mChatInfo.mbyChatType = byChatType;
	lStru.mChatInfo.mi64FromId	= m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mChatInfo.mi64ToId	= ai64SendTo;

 	strncpy(lStru.mChatInfo.mstrContent, apszContent, sizeof(lStru.mChatInfo.mstrContent));
 	strncpy(lStru.mChatInfo.mstrControl, apszContrl, sizeof(lStru.mChatInfo.mstrControl));
 	strncpy(lStru.mChatInfo.mstrMood, apszMood, sizeof(lStru.mChatInfo.mstrMood));

	lStru.mChatInfo.mwContentLen = (uint16_t)strlen(lStru.mChatInfo.mstrContent);
	lStru.mChatInfo.mwControlLen = (uint16_t)strlen(lStru.mChatInfo.mstrControl);
	lStru.mChatInfo.mwMoodLen = (uint16_t)strlen(lStru.mChatInfo.mstrMood);

	lStru.mwDataLen = lStru.mChatInfo.mwContentLen + lStru.mChatInfo.GetSubLen();

	lStru.mi64SrcUserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	if(byChatType == 0)
		lStru.mi64DstUserID = 0;
	else
		lStru.mi64DstUserID = ai64SendTo;
	lStru.mlChatroomID = m_pRoomKernelService->GetCurrRoomID();

	AutoSendPack(lStru);
}

void  CBaseKernel::ChangeHermitState( bool bHermit )
{
	STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID lStru;
	lStru.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mbyState = 1;
	lStru.mbNewVal = bHermit;
	AutoSendPack(lStru);
}

void  CBaseKernel::ManageUser( int64_t ai64UserID, uint8_t byType, int32_t otherParam, char* strText )
{
	STRU_CL_CRS_OPERATION_ON_USER_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64UserId = ai64UserID;

	lStru.mbyType = byType;
	lStru.mlOtherParam = otherParam;
	if(strText != NULL && strlen(strText) > 0)
		strncpy(lStru.mstrDescribe, strText, sizeof(lStru.mstrDescribe));
	AutoSendPack(lStru);
}

void  CBaseKernel::GetBlackList()
{
	STRU_UC_CL_CRS_BLACK_QUERY_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	AutoSendPack(lStru);
}

void  CBaseKernel::GetBlackIPList()
{
	STRU_UC_CL_CRS_BLACKIP_LIST_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	AutoSendPack(lStru);
}

void  CBaseKernel::ModifyRoomStateRQ( uint16_t wProperty, bool abValue )
{
	STRU_UC_CL_CRS_HALL_STAT_CHG_ID lStru;
	lStru.mi64ManagerID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mlChatHallID = m_pRoomKernelService->GetCurrRoomID();
	lStru.mlNewValue = int32_t(abValue);
	lStru.mwProperty = wProperty;
	AutoSendPack(lStru);
}

void  CBaseKernel::SendBroadCast( char* astrText )
{
	STRU_CL_CRS_CHATROOM_BROADCAST_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	strncpy(lStru.macBroadcaseMsg, astrText, sizeof(lStru.macBroadcaseMsg));
	lStru.mwDataLen =  (uint16_t)strlen(lStru.macBroadcaseMsg) + 1;
	AutoSendPack(lStru);	
}

void  CBaseKernel::ModifyRoomProperty( bool bLocked, char* strPSW, char* strTopic, char* strSalutatory )
{
	STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mbIsLockHall = bLocked;
	strncpy(lStru.macPassword,strPSW, sizeof(lStru.macPassword));
	strncpy(lStru.macSalutatory, strSalutatory, sizeof(lStru.macSalutatory));
	strncpy(lStru.macTopic, strTopic, sizeof(lStru.macTopic));
	AutoSendPack(lStru);
}

void  CBaseKernel::SendGeneralInfo( int64_t ai64UserID, uint16_t wType )
{
	STRU_UC_CL_CRS_GENERAL_PACK_350 lStru;
	lStru.mlChatRoomID = m_pRoomKernelService->GetCurrRoomID();
	lStru.mGENERALInfo.mi64ToId = lStru.mi64DstUserID = ai64UserID;
	lStru.mGENERALInfo.mi64FromId = lStru.mi64SrcUserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mGENERALInfo.mwType = wType;
	lStru.mwDataLen = lStru.mGENERALInfo.GetSubLen()+lStru.mGENERALInfo.mwContentLen;
	AutoSendPack(lStru);
}

void  CBaseKernel::ModifyUserInfo( PRKN_STRU_MD_USER_INFO_ITEM apItemList, uint8_t abyItemCount )
{
	uint8_t lbyFiled = 0;
	PSTRU_MODIFIED_USER_INFO_FIELD pList = new STRU_MODIFIED_USER_INFO_FIELD[abyItemCount];
	for(int i = 0; i < abyItemCount; i++)
	{
		pList[lbyFiled].mbyFieldName = apItemList[i].m_byMdType;
		strncpy(pList[lbyFiled].macValue, apItemList[i].mpszMdValue, sizeof(pList[lbyFiled].macValue));
	}

	STRU_UC_CL_CRS_CHG_USER_INFO_ID lStru;
	lStru.mbyCount = abyItemCount;
	lStru.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mpModifyList = pList;
	AutoSendPack(lStru);

}