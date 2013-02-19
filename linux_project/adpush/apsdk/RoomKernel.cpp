#include "RoomKernel.h"
#include "base/task/task_queue.h"

#ifdef _WIN32

#include <process.h>

#endif

#include <assert.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

unsigned int __stdcall threadCreateKey_SEH(STRU_THREAD_CONTEXT& aoContext)
{
	CRoomKernel *pRoomKernel = reinterpret_cast<CRoomKernel*>(aoContext.mpWorkContext);
	pRoomKernel->threadCreateKey();
	return 1;
}


CRoomKernel::CRoomKernel()
{
	m_BaseKernel.SetRoomKernelService(this);
	m_MediaKernel.SetRoomKernelService(this);
	m_ValueAddedKernel.SetRoomKernelService(this);

	m_pBaseProcess = NULL;
	m_pMediaProcess = NULL;
	m_pValueAddedProcess = NULL;

	m_lCurrRoomID = 0;

	m_PublicKey.mpContent = NULL;

	m_pRsaFun = new CRSAMainFun();

	//启动线程
	thread_group.Start(threadCreateKey_SEH, this, 1, "NetWorkThread");

	//AllocConsole();
	//freopen("CONOUT$", "a+", stdout);
}

CRoomKernel::~CRoomKernel()
{
	if (m_PublicKey.mpContent != NULL)
	{
		delete [] m_PublicKey.mpContent;
		m_PublicKey.mpContent = NULL;
	}

	if(m_pRsaFun)
	{
		delete m_pRsaFun;
		m_pRsaFun = NULL;
	}
}

void CRoomKernel::SetProcess(ISdkProcess* pSdkProcess)
{
	if(pSdkProcess)
	{
		pSdkProcess->QueryInterface(UID_BASE_PROCESS, (void**)&m_pBaseProcess);
		pSdkProcess->QueryInterface(UID_MEDIA_PROCESS, (void**)&m_pMediaProcess);
		pSdkProcess->QueryInterface(UID_VALUE_ADDED_PROCESS, (void**)&m_pValueAddedProcess);
	}
}

void CRoomKernel::ConnectRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort)
{

	if(m_lCurrRoomID != alRoomId)
	{
		m_lCurrRoomID = alRoomId;
		m_pKernelService->ConnectRoom(aspszServerAddr, awServerPort);
	}
}

void CRoomKernel::CloseRoom(int32_t alRoomId)
{
	if(m_lCurrRoomID == alRoomId)
	{
		m_lCurrRoomID = 0;
		m_pKernelService->CloseRoom();	
	}
}

void CRoomKernel::RSAEncrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen)
{
	int len = inLen;
	//outData = m_pRsaFun->fnEnCryptBuffer(inData, len);
	outLen = len;
}

void CRoomKernel::RSADecrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen)
{
	int nlen = inLen;
	//outData = m_pRsaFun->fnDeCryptBuffer(inData , nlen);
	outLen = nlen;
}

bool CRoomKernel::QueryInterface(uint32_t uID, void** ppVoid)
{
	*ppVoid = NULL;

 	switch (uID)
 	{
 	case UID_BASE_KERNEL:
 		*ppVoid = static_cast<IBaseKernel*>(&m_BaseKernel);
 		break;
 	case UID_MEDIA_KERNEL:
 		*ppVoid = static_cast<IMediaKernel*>(&m_MediaKernel);
 		break;
 	case UID_VALUE_ADDED_KERNEL:
 		*ppVoid = static_cast<IValueAddedKernel*>(&m_ValueAddedKernel);
 		break;
 	}

	return (*ppVoid) != NULL;
}

void CRoomKernel::SolveMsg(char * apPackData, uint16_t awPackDataLen)
{
	//if(alHallID == m_lCurrRoomID)
	{
		uint16_t lwPackType	 = 0;
		memcpy(&lwPackType,apPackData,2);
		if(lwPackType == UC_CL_CRS_DATA_HEAD)
		{
			STRU_UC_CL_TCP_CRS_DATA_HEAD lStru;
			if(lStru.UnPack(apPackData,awPackDataLen) > 0)
			{
				ScopedRunnableMethodFactory<CRoomKernel> t(this);
				char* date = new char[lStru.mwDataLen];
				memcpy(date, lStru.mpData, lStru.mwDataLen);

				Task* pTask = t.NewRunnableMethod(&CRoomKernel::DealPack,  m_lCurrRoomID, date, lStru.mwDataLen);
				m_pKernelService->AddTask(pTask);

				DeleteTask<char>* pDelTask = new DeleteTask<char>(date);
				m_pKernelService->AddTask(pDelTask);
			}
		}
	}
}

void CRoomKernel::OnOpenTCPSession( const int32_t &alHallID )
{
	if(m_lCurrRoomID == alHallID)
	{
		m_BaseKernel.LoginRoom();
	}
	else
	{
		m_pKernelService->CloseRoom();
	}
}

void CRoomKernel::OnCloseTCPSession( const int32_t &alHallID )
{
	m_lCurrRoomID = 0;
}

void CRoomKernel::OnErrTCPSession( const uint8_t &abyErrType,const int32_t &alHallID )
{
	if(m_lCurrRoomID == alHallID)
	{
		ScopedRunnableMethodFactory<IBaseProcess> t(m_pBaseProcess);

		Task* pTask = t.NewRunnableMethod(&IBaseProcess::OnConnetAborted);
		m_pKernelService->AddTask(pTask);

		m_lCurrRoomID = 0;
	}
}

void CRoomKernel::DealPack(const int32_t &alHallID,char * pDate, uint16_t wDataLen)
{
	if(alHallID != this->m_lCurrRoomID)
		return;

	uint16_t lwPackType	 = 0;
	memcpy(&lwPackType,pDate,2);
	switch (lwPackType)
	{
	case UC_COM_GAS_VISITOR_INFO_RS:		//游客ID应答
		{
			STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				DealVisitorIDRs(&lstru);
			}
		}
		break;
	case UC_CL_CRS_LOGIN_HALL_RS_2009:
		{
			STRU_UC_CL_CRS_LOGIN_HALL_RS_2009 lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				DealLoginRs(&lstru);
			}
		}
		break;
	case UC_CL_CRS_ENTRY_OTHERUSER_ID_2009: //用户进入
		{
			STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009 lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				DealUserEnter(&lstru);
			}
		}
		break;
	case UC_CL_CRS_USER_INFO_ID_2009:		//用户列表
		{
			STRU_UC_CL_CRS_USER_INFO_ID_2009 lstru;
			if(lstru.UnPack(pDate, wDataLen) > 0)
			{
				DealUserList(&lstru);
			}
		}
		break;
	case UC_CL_CRS_LEAVE_OTHERUSER_ID_350:	//用户离开
		{
			STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350 lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnUserLeave(lstru.mi64UserID, lstru.mbyCancelType, lstru.macReason);
			}
		}
		break;;
	case UC_CL_CRS_DATA_ID_350:			    //聊天消息
		{
			STRU_UC_CL_CRS_DATA_ID_350 lstru;
			if (lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnChatMessage(lstru.mChatInfo.mbyChatType, lstru.mChatInfo.mi64FromId, lstru.mChatInfo.mi64ToId, 
													lstru.mChatInfo.mstrMood, lstru.mChatInfo.mstrControl, lstru.mChatInfo.mstrContent);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID: //麦序通知包
		{
			STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID lstru;
			if (lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnMicOrderList(lstru.mpUserIdList, lstru.mbyCount);
			}
		}
		break;
	case UC_CL_CRS_FLOWERS_ID:		//喝彩
		{
			STRU_UC_CL_CRS_FLOWERS_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnFlower(lstru.mi64SrcUserID, lstru.mi64DstUserID, lstru.mlFlowerType);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_BROADCAST_RQ:	//广播
		{
			STRU_CL_CRS_CHATROOM_BROADCAST_RQ lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
				{
					char* strFind  = strstr(lstru.macBroadcaseMsg, "http://client.show.sina.com.cn/identify/");
					if(strFind == NULL)
						m_pBaseProcess->OnBroadCast(lstru.mi64ManagerId, lstru.macBroadcaseMsg);
					else
					{
						int i = 0;
						while (strFind[i] != '\0')
						{
							if(strFind[i] == '\'')
							{
								strFind[i] = '\0';
								break;
							}
							i++;
						}
						//聊天验证码接口
						m_pBaseProcess->OnChatVerifyCode(strFind);
					}
				}
			}
		}
		break;
	case UC_CL_CRS_MIC_INFO_LIST_ID:	//麦列表
		{
			STRU_UC_CL_CRS_MIC_INFO_LIST_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealMicList(&lstru);
			}
		}
		break;
	case UC_CL_CRS_SPEAKER_INFO_LIST_ID: //发言人列表
		{
			STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealSpeakUserList(&lstru);
			}
		}
		break;
	case UC_CL_CRS_BEGIN_SPEAK_ID:		//开始发言
		{
			STRU_UC_CL_CRS_BEGIN_SPEAK_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess && lstru.mi64UserID == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pMediaProcess->OnBeginSpeak(lstru.mbyMicIndex);
			}
		}
		break;
	case UC_CL_CRS_INSERT_MIC_ID:	//插麦通知
		{
			STRU_UC_CL_CRS_INSERT_MIC_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnInsertMicNotify(lstru.mi64ManagerID, lstru.mi64UserId, lstru.mbyIndex);
			}
		}
		break;
	case UC_CL_VIP_ENTER_NOTIFY_EX:	//VIP用户通知
		{
			STRU_UC_CL_VIP_ENTER_NOTIFY_EX lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealVipUserNotify(&lstru);
			}
		}
		break;
	case UC_CRS_CL_USER_LOSTRATE_RS:	//丢包率应答
		{
			STRU_USER_LOSTRATE_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnLostRateRs(lstru.mi64UserID, lstru.miLostRate);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS:	//要麦应答
		{
			STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess && lstru.mi64UserId == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pMediaProcess->OnApplyMicRs(lstru.mwSpeakOrder);		
			}
		}
		break;
	case UC_CL_CRS_VOICE_CHAT_RQ:				//对聊请求
		{
			STRU_CL_CRS_VOICE_CHAT_RQ lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess && lstru.mi64DestUserId == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pMediaProcess->OnVoiceChatRQ(lstru.mi64SelfUserId);	
			}
		}
		break;
	case UC_CL_CRS_VOICE_CHAT_SERVER_RS:		//对聊应答
		{
			STRU_CL_CRS_VOICE_CHAT_SERVER_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnVoiceChatRS(lstru.mbyResult, lstru.mi64RQUserId, lstru.mi64RSUserId);	
			}
		}
		break;
	case UC_CL_CRS_VOICE_CHAT_STOP_ID:		//对聊停止通知
		{
			STRU_CL_CRS_VOICE_CHAT_STOP_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnVoiceChatStop(lstru.mi64SelfUserId);	
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID:	//递麦通知
		{
			STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess && lstru.mi64UserId == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pMediaProcess->OnGiveMic(lstru.mi64ManagerId, lstru.mi64UserId);
			}
		}
		break;
	case UC_CL_CRS_MICROPHONE_MANAGER_RS:			//递麦结果
		{
			STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess && lstru.mi64ManagerID == m_pKernelService->GetUserInfo().m_i64UserID && lstru.mwType == DEF_MIC_MGR_TYPE_SET && lstru.mbyResult == 0)
					m_pMediaProcess->OnGiveMic(lstru.mi64ManagerID, lstru.mi64DesUserID);
			}
		}
		break;
	case UC_CL_CRS_USER_BE_OPERATED_ID:		//用户被处理通知
		{
			STRU_CL_CRS_USER_BE_OPERATED_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnUserBeOperatedNotify(lstru.mi64ManagerId, lstru.mi64UserId, lstru.mbyType, lstru.mstrDescribe);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_TOPIC_ID:		//房间主题修改通知
		{
			STRU_CL_CRS_CHATROOM_TOPIC_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnRoomPropertyChangedNotify(lstru.mi64ManagerId, lstru.macTopic, lstru.macWelcome, NULL, false, false);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_PROPERTY_ID:	//房间属性修改通知
		{
			STRU_CL_CRS_CHATROOM_PROPERTY_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnRoomPropertyChangedNotify(lstru.mi64ManagerId, lstru.macTopic, lstru.macSalutatory, lstru.macPassword, lstru.mbIsLocked, true);
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID:		//修改麦时通知
		{
			STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnMicTimeChanged(lstru.mi64ManagerId, lstru.mbyMicIndex, lstru.mbyMinute);		
			}
		}
		break;
	case UC_CL_CRS_USER_STATE_RS:			//用户状态应答
		{
			STRU_UC_CL_CRS_USER_STATE_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnUserStateRS(lstru.mi64UserId, lstru.mlState);
			}
		}
		break;
	case UC_CL_CRS_HOST_INFO_ID600:		//房间背景
		{
			STRU_UC_CL_CRS_HOST_INFO_ID600 lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnRoomBackGroundBmp(lstru.macBgBmpName);		
			}
		}
		break;
	case UC_CL_CRS_TIME_BLACK_LIST:		//房间背景
		{
			STRU_UC_CL_CRS_TIME_BLACK_LIST lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(lstru.mi64ManagerId == m_pKernelService->GetUserInfo().m_i64UserID)
					DealBlackList(&lstru);
			}
		}
		break;
	case UC_CL_CRS_BLACKIP_LIST_RS:
		{
			STRU_UC_CL_CRS_BLACKIP_LIST_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(lstru.mi64ManagerId == m_pKernelService->GetUserInfo().m_i64UserID)
					DealBlackIPList(&lstru);
			}
		}
		break;
	case UC_CL_CRS_MIC_STATE_CONTROL_ID:
		{
			STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnManageMicStateNotify(lstru.mi64ManagerID, lstru.mbyMicIndex, lstru.mbOperateType, bool(lstru.mwValue));
			}
		}
		break;
	case UC_CL_CRS_HALL_STAT_CHG_ID:
		{
			STRU_UC_CL_CRS_HALL_STAT_CHG_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess)
					m_pBaseProcess->OnRoomStateChangedNotify(lstru.mi64ManagerID, lstru.mwProperty, bool(lstru.mlNewValue));
			}
		}
		break;
	case UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID:
		{
			STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess && lstru.mbyState == 1)
					m_pBaseProcess->OnUserHermitStateChanged(lstru.mi64UserId, lstru.mbNewVal);	
			}
		}
		break;
	case UC_CL_CRS_CHG_USER_INFO_ID:
		{
			STRU_UC_CL_CRS_CHG_USER_INFO_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealModifyUserInfoID(&lstru);
			}	
		}
		break;
	case UC_CL_CRS_GENERAL_PACK_350:	//
		{
			STRU_UC_CL_CRS_GENERAL_PACK_350 lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess && lstru.mGENERALInfo.mi64ToId == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pBaseProcess->OnUserGeneralInfo(lstru.mGENERALInfo.mi64FromId, lstru.mGENERALInfo.mwType);		
			}
		}
		break;
	case UC_CL_CRS_VOICE_STATE_CHG_ID:	//用户语音状态变更通知
		{
			STRU_CL_CRS_VOICE_STATE_CHG_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pMediaProcess)
					m_pMediaProcess->OnUserVocieStateChanged(lstru.mi64UserId, lstru.mbyState);
			}
		}
		break;
	case UC_CRS_CL_USER_AVS_INFO_ID:	//AVS通知
		{
			STRU_UC_CRS_CL_USER_AVS_INFO_ID lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealAvsChanged(&lstru);
			}
		}
		break;
	case UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS:	//管理用户结果
		{
			STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pBaseProcess && lstru.mi64ManagerId == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pBaseProcess->OnManageUserResult(lstru.mi64UserId, lstru.mbyType, lstru.mbyResult, lstru.mstrDescribe);
			}
		}
		break;
	case UC_CL_CRS_GIFT_PROP_USE_RS:		//礼物使用结果
		{
			STRU_UC_CL_CRS_GIFT_PROP_USE_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pValueAddedProcess && lstru.mi64UserID == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pValueAddedProcess->OnSendGiftResult(lstru.mbyResult, lstru.mi64DestID, lstru.miContentID, lstru.mszContentName, lstru.miUseCount);
			}
		}
		break;
	case UC_CL_CRS_GIFT_PROP_USE_NOTIFY:	//礼物通知
		{
			STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pValueAddedProcess)
					m_pValueAddedProcess->OnGiftNotify(lstru.mi64UserID, lstru.mi64DestID, lstru.miContentID, lstru.mszContentName, lstru.miUseCount, lstru.miPackMark, lstru.miPackBeginNum, lstru.miPackUseNum, lstru.miRecvCount);
			}
		}
		break;
	case UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY:		//跑道礼物通知
		{
			STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealBigGiftNotify(&lstru);
			}
		}
		break;
	case UC_CRS_CL_BALANCE_NOTIFY:		//余额通知
		{
			STRU_UC_CRS_CL_BALANCE_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pValueAddedProcess && lstru.mi64UserID == m_pKernelService->GetUserInfo().m_i64UserID)
					m_pValueAddedProcess->OnBalanceNotify(lstru.miResidualValue);
			}
		}
		break;
	case UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS:		//喇叭发送结果
		{
			STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pValueAddedProcess)
					m_pValueAddedProcess->OnLoudSpeakerResult(lstru.mbyResult, "");
			}
		}
		break;
	case UC_CRS_CL_LOUDSPEAKER_NOTIFY:			//喇叭通知
		{
			STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealLoudSpeakerNotify(&lstru);
			}
		}
		break;
	case UC_CL_CRS_AWARD_USE_NOTIFY:		//幸运道具通知
		{
			STRU_UC_CL_CRS_AWARD_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealAwardPropNotify(&lstru);
			}
		}
		break;
	case UC_CL_CRS_LUCK_PROP_USE_INFO:		//幸运道具通知  本人
		{
			 STRU_UC_CL_CRS_AWARD_INFO lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				DealAwardPropInfo(&lstru);
			}
		}
		break;
	case UC_CL_CRS_FIREWORKS_USE_NOTIFY:	//烟共道具通知
		{	
			STRU_UC_CL_CRS_FIREWORKS_NOTIFY lstru;
			if(lstru.UnPack(pDate, wDataLen))
			{
				if(m_pValueAddedProcess)
					m_pValueAddedProcess->OnFireWorksNotify(lstru.m_i64UserID, lstru.m_szUserName, lstru.m_nContentID, lstru.m_nUseCount, lstru.m_i64GainPoint);
			}
		}
		break;
	case UC_COM_RAS_APPLY_KEY_RS:		//RSA加密流程 密钥交互
		{
 			STRU_RSA_INFO_RS lStru;	
 			if(lStru.UnPack(pDate, wDataLen))
 			{
				DealApplyRsaKeyRS(&lStru);
 			}
		}
		break;
	case UC_ENDECRYPT_FUN:			//RSA解密包
		{
 			STRU_ENDECRYPT_FUN lStru;
 			if(lStru.UnPack(pDate, wDataLen))
 			{
 				DealRASDecrypt(&lStru);
 			}
		}
		break;
	}	
}

void CRoomKernel::DealVisitorIDRs(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS* pStru)
{
	if(m_pBaseProcess)
		m_pBaseProcess->OnVisitorUserInfo(pStru->mi64VisitorID, pStru->macVisitorName, pStru->mwPhotoNum);	

	m_pKernelService->GetUserInfo().m_i64UserID = pStru->mi64VisitorID;
	m_pKernelService->GetUserInfo().m_strUserNick = pStru->macVisitorName;
	m_pKernelService->GetUserInfo().m_strUserPsw = "";
	m_pKernelService->GetUserInfo().m_wPhotoNm = pStru->mwPhotoNum;
	
	m_BaseKernel.LoginRoom();
}

void CRoomKernel::DealLoginRs(STRU_UC_CL_CRS_LOGIN_HALL_RS_2009* pstruLoginRs)
{
	switch(pstruLoginRs->mbyResult)
	{
	case LOGIN_RESULT_OK:  //登录成功
		{
			if(m_pBaseProcess)
				m_pBaseProcess->OnLoginSucc(pstruLoginRs->mulToken, pstruLoginRs->mlHallState, pstruLoginRs->mi64HallProperty,
											pstruLoginRs->macTopic, pstruLoginRs->macSalutatory, pstruLoginRs->macPwd);

			SendRSAKeyRQ();
		}
		return;
	case LOGIN_RESULT_ERROR:
	case LOGIN_RESULT_FORBID:
		{
			if(m_pBaseProcess)
				m_pBaseProcess->OnLoginFailed(CBY_GENERAL_ERROR, pstruLoginRs->macErrInfo);
		}
		break;
	case LOGIN_RESULT_MEMBERROOMFULL:
		{
			if(m_pBaseProcess)
				m_pBaseProcess->OnLoginFailed(CBY_ROOM_FULL, pstruLoginRs->macErrInfo);
		}
		break;
	case LOGIN_RESULT_MEMBERFULL:
		{
			if(m_pBaseProcess)
				m_pBaseProcess->OnLoginFailed(CBY_MEMBER_FULL, pstruLoginRs->macErrInfo);
		}
		break;
	default:
		if(m_pBaseProcess)
			m_pBaseProcess->OnLoginFailed(CBY_UNKNOW_ERROR, pstruLoginRs->macErrInfo);
		break;
	}

}

void CRoomKernel::DealUserEnter(STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009* pstruUserEnter)
{
	RKN_STRU_USER_INFO roomUser;
	roomUser.m_i64UserID = pstruUserEnter->mi64UserID;
	char szNick[NICK_NAME_LEN+1] = {0};
	if(strlen(pstruUserEnter->macNickName) > 0)
		strncpy(szNick, pstruUserEnter->macNickName, sizeof(szNick));
	else
	{
		stringstream ss;
		ss<<pstruUserEnter->mi64UserID<<ends;
		strncpy(szNick, ss.str().c_str(), sizeof(szNick));
	}
	
	roomUser.mpszNickName = szNick;
	roomUser.mwPhotoNum = pstruUserEnter->mwPhotoNum;
	roomUser.mbyPower = pstruUserEnter->mbyPower;
	roomUser.mlUserState = pstruUserEnter->mlUserState;
	roomUser.miVipLevel = pstruUserEnter->miRedMemTime;
	roomUser.mbyVoiceState = 1;
	roomUser.mbyLoginSource = 0xFF;
	roomUser.mbyLoginSource = roomUser.mbyLoginSource & (roomUser.mlUserState >> 24);
	roomUser.mbVisitor = (((roomUser.mlUserState >> 2)&0x3)==2);
	if(m_pBaseProcess)
		m_pBaseProcess->OnUserEnter(&roomUser);
}

void CRoomKernel::DealUserList(STRU_UC_CL_CRS_USER_INFO_ID_2009* pstruUserList)
{
	PRKN_STRU_USER_INFO ppUser = new RKN_STRU_USER_INFO[pstruUserList->mwUserCount];
	char* buffer = new char[pstruUserList->mwUserCount*(NICK_NAME_LEN+1)];
	for(int i = 0; i < pstruUserList->mwUserCount; i++)
	{
		
		if(strlen(pstruUserList->mpUserIDList[i].macNickName) == 0)
		{
			stringstream ss;
			ss<<pstruUserList->mpUserIDList[i].mi64UserId<<ends;
			strncpy(pstruUserList->mpUserIDList[i].macNickName, ss.str().c_str(), sizeof(pstruUserList->mpUserIDList[i].macNickName));
		}
		ppUser[i].mpszNickName = buffer + (NICK_NAME_LEN+1)*i;
		strncpy(ppUser[i].mpszNickName, pstruUserList->mpUserIDList[i].macNickName, sizeof(pstruUserList->mpUserIDList[i].macNickName));
		ppUser[i].mbyPower = pstruUserList->mpUserIDList[i].mbyPower;
		ppUser[i].m_i64UserID = pstruUserList->mpUserIDList[i].mi64UserId;
		ppUser[i].miVipLevel = pstruUserList->mpUserIDList[i].miRedMemTime;
		ppUser[i].mlUserState = pstruUserList->mpUserIDList[i].mlUserState;
		ppUser[i].mbyVoiceState = pstruUserList->mpUserIDList[i].mbyVoiceState;
		ppUser[i].mwPhotoNum = pstruUserList->mpUserIDList[i].mwPhotoNum;
		ppUser[i].mbyLoginSource = 0xFF;
		ppUser[i].mbyLoginSource = ppUser[i].mbyLoginSource & (ppUser[i].mlUserState >> 24);
		ppUser[i].mbVisitor = (((ppUser[i].mlUserState >> 2)&0x3)==2);
	}
	if(m_pBaseProcess)
		m_pBaseProcess->OnUserList(ppUser, pstruUserList->mwUserCount);

	delete [] buffer;
	delete [] ppUser;
}

void CRoomKernel::DealMicList(STRU_UC_CL_CRS_MIC_INFO_LIST_ID* pStru)
{
	PRKN_STRU_MIC_INFO pMicList = new RKN_STRU_MIC_INFO[pStru->mwMicCount]; 
	for (int i = 0; i < pStru->mwMicCount; i++)
	{
		pMicList[i].mbSupportVideo = pStru->mpMicInfoList[i].mbSupportVideo;
		pMicList[i].mbyMicIndex = pStru->mpMicInfoList[i].mbyMicIndex;
		pMicList[i].mi64ManagerID = pStru->mpMicInfoList[i].mi64ManagerID;
		pMicList[i].mlDeltaSpeakTime = pStru->mpMicInfoList[i].mlDeltaSpeakTime;
		pMicList[i].mwMicStatue = pStru->mpMicInfoList[i].mwMicStatue;
		pMicList[i].mwMicTimeLen = pStru->mpMicInfoList[i].mwMicTimeLen;
		pMicList[i].mstruAudioConfig.mbyBitsPerSample = pStru->mpMicInfoList[i].mstruAudioConfig.mbyBitsPerSample;
		pMicList[i].mstruAudioConfig.mbyChannels = pStru->mpMicInfoList[i].mstruAudioConfig.mbyChannels;
		pMicList[i].mstruAudioConfig.mbyCodecType = pStru->mpMicInfoList[i].mstruAudioConfig.mbyCodecType;
		pMicList[i].mstruAudioConfig.mlSamplesPerSec = pStru->mpMicInfoList[i].mstruAudioConfig.mlSamplesPerSec;
		pMicList[i].mstruAudioConfig.musKBitsPerSec = pStru->mpMicInfoList[i].mstruAudioConfig.mwKBitsPerSec;

		pMicList[i].mstruVideoConfig.mbyCodecType = pStru->mpMicInfoList[i].mstruVideoConfig.mbyCodecType;
		pMicList[i].mstruVideoConfig.mbyFramePerSecond = pStru->mpMicInfoList[i].mstruVideoConfig.mbyFramePerSecond;
		pMicList[i].mstruVideoConfig.mbySizeType = pStru->mpMicInfoList[i].mstruVideoConfig.mbySizeType;
		pMicList[i].mstruVideoConfig.mulBandWidth = pStru->mpMicInfoList[i].mstruVideoConfig.mdwBandWidth;
	}

	if(m_pMediaProcess)
		m_pMediaProcess->OnMicList(pMicList, pStru->mwMicCount);

	delete [] pMicList;
}

void CRoomKernel::DealSpeakUserList(STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID* pStru)
{
	PRKN_STRU_SPEAKER_INFO pSpeaker = new RKN_STRU_SPEAKER_INFO[pStru->mbySpeakerNum];
	for (int i = 0; i < pStru->mbySpeakerNum; i++)
	{
		pSpeaker[i].mbContainAudioInfo = pStru->mpSpeakerUserInfo[i].mbContainAudioInfo;
		pSpeaker[i].mbContainVideoInfo = pStru->mpSpeakerUserInfo[i].mbContainVideoInfo;
		pSpeaker[i].mbyMicIndex = pStru->mpSpeakerUserInfo[i].mbyMicIndex;
		pSpeaker[i].mi64DstUserID = pStru->mpSpeakerUserInfo[i].mi64DstUserID;
		pSpeaker[i].mi64SpeakerUserID = pStru->mpSpeakerUserInfo[i].mi64SpeakerUserID;

		pSpeaker[i].mstrAudioInfo.mbyBitsPerSample = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mbyBitsPerSample;
		pSpeaker[i].mstrAudioInfo.mbyChannels = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mbyChannels;
		pSpeaker[i].mstrAudioInfo.mbyCodecType = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mbyCodecType;
		pSpeaker[i].mstrAudioInfo.mlSamplesPerSec = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mlSamplesPerSec;
		pSpeaker[i].mstrAudioInfo.mulChannelID = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mulChannelID;
		pSpeaker[i].mstrAudioInfo.mwKBitsPerSec = pStru->mpSpeakerUserInfo[i].mstrAudioInfo.mwKBitsPerSec;

		pSpeaker[i].mstrVideoInfo.mbyCodecType = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mbyCodecType;
		pSpeaker[i].mstrVideoInfo.mbyFramePerSecond = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mbyFramePerSecond;
		pSpeaker[i].mstrVideoInfo.mulChannelID = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mulChannelID;
		pSpeaker[i].mstrVideoInfo.mwBitCount = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mwBitCount;
		pSpeaker[i].mstrVideoInfo.mwFrameHeight = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mwFrameHeight;
		pSpeaker[i].mstrVideoInfo.mwFrameWidth = pStru->mpSpeakerUserInfo[i].mstrVideoInfo.mwFrameWidth;
	}

	if(m_pMediaProcess)
		m_pMediaProcess->OnSpeakerList(pSpeaker, pStru->mbySpeakerNum);

	delete [] pSpeaker;	
}

void CRoomKernel::DealBlackList(STRU_UC_CL_CRS_TIME_BLACK_LIST* pStru)
{
	PRKN_STRU_BLACK_USER ppUser = new RKN_STRU_BLACK_USER[pStru->msUserCount];
	for(int i = 0; i < pStru->msUserCount; i++)
	{
		ppUser[i].mi64UserID = pStru->mpBlackList[i].mi64UserID;
		ppUser[i].mlLimitedTime = pStru->mpBlackList[i].mlNoComeInTime;
		ppUser[i].mlResidualTime = pStru->mpBlackList[i].mlResidualTime;
	}
	if(m_pBaseProcess)
		m_pBaseProcess->OnBlackList(pStru->msUserCount, ppUser);

	delete [] ppUser;
}

void CRoomKernel::DealBlackIPList(STRU_UC_CL_CRS_BLACKIP_LIST_RS* pStru)
{
	PRKN_STRU_BLACK_IP_USER ppUser = new RKN_STRU_BLACK_IP_USER[pStru->msCount];
	for(int i = 0; i < pStru->msCount; i++)
	{
		ppUser[i].mi64UserID = pStru->mpBlackList[i].mi64UserID;
		ppUser[i].mulIP = pStru->mpBlackList[i].mulIP;
		ppUser[i].mlLimitedTime = pStru->mpBlackList[i].mlNoComeInTime;
		ppUser[i].mlResidualTime = pStru->mpBlackList[i].mlResidualTime;
	}
	if(m_pBaseProcess)
		m_pBaseProcess->OnBlackIPList(pStru->msCount, ppUser);

	delete [] ppUser;
}

void CRoomKernel::DealModifyUserInfoID(STRU_UC_CL_CRS_CHG_USER_INFO_ID* pStru)
{
	PRKN_STUR_MD_USER_INFO pMdUserInfo = new RKN_STUR_MD_USER_INFO;
	pMdUserInfo->mbyItemCount = pStru->mbyCount;
	pMdUserInfo->mi64UserID = pStru->mi64UserId;
	pMdUserInfo->mpItemList = new RKN_STRU_MD_USER_INFO_ITEM[pMdUserInfo->mbyItemCount];
	char* buffer = new char[pStru->mbyCount*(USER_INTRO_LEN+1)];
	for(int i = 0; i < pStru->mbyCount; i++)
	{
		pMdUserInfo->mpItemList[i].mpszMdValue = buffer + (USER_INTRO_LEN+1)*i;
		pMdUserInfo->mpItemList[i].m_byMdType = pStru->mpModifyList[i].mbyFieldName;
		strncpy(pMdUserInfo->mpItemList[i].mpszMdValue, pStru->mpModifyList[i].macValue, sizeof(pMdUserInfo->mpItemList[i].mpszMdValue));
	}
	if(m_pBaseProcess)
		m_pBaseProcess->OnUserInfoChanged(pMdUserInfo);
	
	delete [] buffer;
	delete [] pMdUserInfo->mpItemList;
	delete pMdUserInfo;
}

void CRoomKernel::DealAvsChanged(STRU_UC_CRS_CL_USER_AVS_INFO_ID* pStru)
{
	PRKN_STRU_AVS_INFO pAvsList = new RKN_STRU_AVS_INFO[pStru->miAvsCount];
	char* buffer = new char[(UC_HALL_AVS_NAME_LEN+1)*pStru->miAvsCount];
	for (int i = 0; i < pStru->miAvsCount; i++)
	{
		pAvsList[i].mpszAvsName = buffer + (UC_HALL_AVS_NAME_LEN+1)*i;
		pAvsList[i].mulAvsIp = pStru->miAvsInfoList[i].miAvsIp;
		pAvsList[i].musVoicePort = pStru->miAvsInfoList[i].miVoicePort;	
		strncpy(pAvsList[i].mpszAvsName, pStru->miAvsInfoList[i].mszAvsName, sizeof(pAvsList[i].mpszAvsName));
	}
	if(m_pMediaProcess)
		m_pMediaProcess->OnAVSChanged(pStru->miAvsId, pStru->miAvsCount, pAvsList);

	delete [] buffer;
	delete [] pAvsList;
}

void CRoomKernel::DealVipUserNotify(STRU_UC_CL_VIP_ENTER_NOTIFY_EX* pstru)
{
	switch(pstru->mui8VIPType)
	{
	case 0:     //贵族
		{
			if(pstru->mui32Reserve <= 0 || pstru->mui32Reserve > 5)
				return;

			if(m_pBaseProcess)
				m_pBaseProcess->OnPeerNotify(pstru->mi64UserID, pstru->mui32Reserve, pstru->mui8NotifyType == 0);
		}
		break;
	case 1:     //周星
		{
			if(m_pBaseProcess)
				m_pBaseProcess->OnWeekStarNotify(pstru->mi64UserID, pstru->mui32Reserve, pstru->mui32Reserve3, pstru->mui8NotifyType == 0, pstru->mui32Reserve2 <= 0);
		}
		break;
	case 2:     //官方销售
		if(m_pBaseProcess)
			m_pBaseProcess->OnSellerNotify(pstru->mi64UserID, pstru->mui8NotifyType == 0);
		break;
	default:
		return;
	}
}

void CRoomKernel::DealBigGiftNotify(STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY* pstru)
{
	RKN_STRU_BIG_GIFT_NOTIFY struBitGiftInfo;
	struBitGiftInfo.mi64FromID = pstru->mi64UserID;
	char szFromNick[NICK_NAME_LEN+1] = {0};
	strncpy(szFromNick, pstru->mszUserName, sizeof(szFromNick));
	struBitGiftInfo.mpszFromNick = szFromNick; 
	struBitGiftInfo.mbyFromVipLevel = pstru->mbyShowStar;
	struBitGiftInfo.mbyFromPeerLevel = pstru->mbyNobleman;
	struBitGiftInfo.mbyFromPowerLevel = pstru->mbyManager;
	struBitGiftInfo.mbyFromWeekStar = pstru->mbyWeekStar;
	struBitGiftInfo.mbyFromSeller = pstru->mbySell;

	struBitGiftInfo.mi64ToID = pstru->mi64DestID;
	char szToNick[NICK_NAME_LEN+1] = {0};
	strncpy(szToNick, pstru->mszDestName, sizeof(szToNick));
	struBitGiftInfo.mpszToNick = szToNick;
	struBitGiftInfo.mbyToVipLevel = pstru->mbyDstShowStar;
	struBitGiftInfo.mbyToPeerLevel = pstru->mbyDstNobleman;
	struBitGiftInfo.mbyToPowerLevel = pstru->mbyDstManager;
	struBitGiftInfo.mbyToWeekStar = pstru->mbyDstWeekStar;
	struBitGiftInfo.mbyToSeller = pstru->mbyDstSell;

	struBitGiftInfo.miGiftID = pstru->miContentID;
	struBitGiftInfo.miCount = pstru->miUseCount;
	char szGiftName[DEF_CONTENT_NAME_LEN+1] = {0};
	strncpy(szGiftName, pstru->mszContentName, sizeof(szGiftName));
	struBitGiftInfo.mpszGiftName = szGiftName;
	struBitGiftInfo.mstrTimeStamp = pstru->mstruTimeStamp;

	if(m_pValueAddedProcess)
		m_pValueAddedProcess->OnBigGiftNotify(&struBitGiftInfo);
}

void CRoomKernel::DealLoudSpeakerNotify(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY* pstru)
{
	RKN_STRU_LOUDSPEAKER_NOTIFY struLoudSpeakerInfo;
	struLoudSpeakerInfo.mi64FromID = pstru->mi64FromUserID;
	char szFromNick[NICK_NAME_LEN+1] = {0};
	strncpy(szFromNick, pstru->mszUserName, sizeof(szFromNick));
	struLoudSpeakerInfo.mpszFromNick = szFromNick; 
	struLoudSpeakerInfo.mbyFromVipLevel = pstru->mbyShowStar;
	struLoudSpeakerInfo.mbyFromPeerLevel = pstru->mbyNobleman;
	struLoudSpeakerInfo.mbyFromPowerLevel = pstru->mbyManager;
	struLoudSpeakerInfo.mbyFromWeekStar = pstru->mbyWeekStar;
	struLoudSpeakerInfo.mbyFromSeller = pstru->mbySell;

	char szControl[CRS_DATA_LEN+1] = {0};
	strncpy(szControl, pstru->mChatInfo.mstrControl, sizeof(szControl));
	struLoudSpeakerInfo.mpszControl = szControl;

	char szContent[CRS_DATA_LEN+1] = {0};
	strncpy(szContent, pstru->mChatInfo.mstrContent, sizeof(szContent));
	struLoudSpeakerInfo.mpszContent = szContent;

	struLoudSpeakerInfo.mbyType = pstru->mbyType;

	if(m_pValueAddedProcess)
		m_pValueAddedProcess->OnLoudSpeakerNotify(&struLoudSpeakerInfo);
}

void CRoomKernel::DealAwardPropNotify(STRU_UC_CL_CRS_AWARD_NOTIFY* pstru)
{
	char szFromNick[NICK_NAME_LEN+1] = {0};
	strncpy(szFromNick, pstru->m_szUserName, sizeof(szFromNick));

	PRKN_STRU_AWARD_EXTRA_DATA pAwardExtraDataList = new RKN_STRU_AWARD_EXTRA_DATA[pstru->m_nExtraDataCount];
	for (int i = 0; i< pstru->m_nExtraDataCount; i++)
	{
		pAwardExtraDataList[i].m_i64GainPoint = pstru->m_pExtraData[i].m_i64GainPoint;
		pAwardExtraDataList[i].m_nIndex = pstru->m_pExtraData[i].m_nIndex;
		pAwardExtraDataList[i].m_nTimes = pstru->m_pExtraData[i].m_nTimes;
	}

	if(m_pValueAddedProcess)
		m_pValueAddedProcess->OnAwardPropNotify(pstru->m_nPackMark, pstru->m_i64UserID, szFromNick, pstru->m_nContentID, pstru->m_nMaxTimes,
				pstru->m_nExtraDataCount, pAwardExtraDataList);
	delete [] pAwardExtraDataList;
}

void CRoomKernel::DealAwardPropInfo(STRU_UC_CL_CRS_AWARD_INFO* pstru)
{
	char szFromNick[NICK_NAME_LEN+1] = {0};
	strncpy(szFromNick, pstru->mszUserName, sizeof(szFromNick));

	PRKN_STRU_AWARD_EXTRA_DATA2 pAwardExtraDataList = new RKN_STRU_AWARD_EXTRA_DATA2[pstru->miExtraDataCount];
	for (int i = 0; i< pstru->miExtraDataCount; i++)
	{
		pAwardExtraDataList[i].miMultiple = pstru->m_pExtraData[i].miMultiple;
		pAwardExtraDataList[i].miTimes = pstru->m_pExtraData[i].miTimes;
	}

	if(m_pValueAddedProcess)
		m_pValueAddedProcess->OnAwardPropInfo(pstru->miPackMark, pstru->mi64UserID, szFromNick, pstru->miContentID, pstru->miMaxTimes,
		pstru->miExtraDataCount, pAwardExtraDataList);

	delete [] pAwardExtraDataList;
}

void CRoomKernel::DealApplyRsaKeyRS(STRU_RSA_INFO_RS* pStru)
{
	if(pStru->nType == 1)
	{
		uint32_t nKeySize = 4;
		uint8_t* dwTempPubKey = NULL;
		m_pRsaFun->fnRSAClientMakePassWord((uint32_t*)pStru->mszPublicKey, &dwTempPubKey, nKeySize);

		STRU_RSA_INFO_RQ lStru;
		lStru.mi64UserID = m_PublicKey.mi64UserID;
		lStru.mszPublicKey = dwTempPubKey;
		lStru.nLen = nKeySize;
		lStru.nSize = 4;
		lStru.nType = 2;

		char lszPack[WHOLE_PACK_DATA_LEN];
		uint16_t lwDataLen = lStru.Pack(lszPack, WHOLE_PACK_DATA_LEN);
		if(lwDataLen > 0)
		{
			SendData(lszPack, lwDataLen);
		}
		delete [] dwTempPubKey;
		dwTempPubKey = NULL;
	}
}

void CRoomKernel::DealRASDecrypt(STRU_ENDECRYPT_FUN* pStru)
{
	char * pPack = (char *)pStru->mszEncrypt;
	int nLen = pStru->nLen;

	char * pszDeRet= m_pRsaFun->fnDeCryptBuffer(pPack , nLen);

	DealPack(m_lCurrRoomID, pszDeRet, nLen);

	delete [] pszDeRet;
	pszDeRet = NULL;
}

uint32_t CRoomKernel::threadCreateKey()
{
	m_pRsaFun->fnRSAStartHash();
	uint32_t nKeySize = 0;
	uint32_t * dwTemp = NULL;
	m_pRsaFun->fnRSAGetPublicKey(&dwTemp, nKeySize);
	SetPublicKey(dwTemp, nKeySize*4, nKeySize);
	return 0;
}

void CRoomKernel::SetPublicKey(uint32_t * pKey, int nLen, int nSize)
{
	if (m_PublicKey.mpContent != NULL)
	{
		delete [] m_PublicKey.mpContent;
		m_PublicKey.mpContent = NULL;
	}

	m_PublicKey.mpContent = new unsigned int[nLen];
	memset(m_PublicKey.mpContent, 0, nLen);
	memcpy(m_PublicKey.mpContent, pKey, nLen);	

	m_PublicKey.nLen = nLen;
	m_PublicKey.nSize = nSize;

	m_pRsaFun->fnReleaseKey(pKey);
}

void CRoomKernel::SendRSAKeyRQ()
{
	STRU_RSA_INFO_RQ lStru;
	lStru.mi64UserID = m_PublicKey.mi64UserID = m_pKernelService->GetUserInfo().m_i64UserID;
	lStru.mszPublicKey = (uint8_t*)m_PublicKey.mpContent;
	lStru.nLen = m_PublicKey.nLen;
	lStru.nSize = m_PublicKey.nSize;
	lStru.nType = 1;

	char lszPack[WHOLE_PACK_DATA_LEN];
	uint16_t lwDataLen = lStru.Pack(lszPack, WHOLE_PACK_DATA_LEN);
	if(lwDataLen > 0)
	{
		SendData(lszPack, lwDataLen);
	}
}

void CRoomKernel::KeepLive()
{
	if(GetCurrRoomID() != 0)
	{
		STRU_UC_CL_CRS_ALIVE_RQ lStru;
		lStru.mi64UserID = GetUserInfo().m_i64UserID;
		lStru.mlHallID = GetCurrRoomID();

		char lszPack[WHOLE_PACK_DATA_LEN];
		uint16_t lwDataLen = lStru.Pack(lszPack, WHOLE_PACK_DATA_LEN);
		if(lwDataLen > 0)
		{
			SendData(lszPack, lwDataLen);
		}
	}
}