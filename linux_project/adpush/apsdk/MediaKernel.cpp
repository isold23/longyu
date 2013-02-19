
#include "MediaKernel.h"

void  CMediaKernel::ApplyMic()
{
	STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ lStru;
	lStru.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	AutoSendPack(lStru);
}

void  CMediaKernel::ManageMic(int64_t ai64UserID, uint8_t byType, uint8_t byIndex)
{
	STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ lStru;
	lStru.mi64ManagerID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DesUserID = ai64UserID;
	lStru.mwType = byType;
	lStru.mbyMicIndex = byIndex;
	AutoSendPack(lStru);
}

void  CMediaKernel::InsertMic(int64_t ai64UserID, uint8_t byIndex)
{
	STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64UserId = ai64UserID;
	lStru.miInsertIndex = byIndex;
	AutoSendPack(lStru);
}

void  CMediaKernel::StopSpeak()
{
	STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID lStru;
	lStru.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	AutoSendPack(lStru);
};

void  CMediaKernel::ChangeMicTime(uint8_t byIndex, uint8_t byTime)
{
	STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ lStru;
	lStru.mi64ManagerId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mbyMicIndex = byIndex;
	lStru.mbyMinute = byTime;
	AutoSendPack(lStru);
}

void  CMediaKernel::ManageMicState(uint8_t byType, uint8_t byIndex, bool abValue)
{
	STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID lStru;
	lStru.mi64ManagerID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mbOperateType = byType;
	lStru.mbyMicIndex = byIndex;
	lStru.mwValue = uint16_t(abValue);	
	AutoSendPack(lStru);
}

void  CMediaKernel::ChangeRecvState(uint8_t byType, uint8_t byIndex, bool abState)
{
	STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID lStru;
	lStru.mi64UserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mbyMediaType = byType;
	lStru.mbyMicIndex = byIndex;
	lStru.mbyState = abState;
	AutoSendPack(lStru);
}	

void  CMediaKernel::UserStateRQ(int64_t ai64Dest)
{
	STRU_UC_CL_CRS_USER_STATE_RQ lStru;
	lStru.mi64UserId = ai64Dest;
	AutoSendPack(lStru);
}

void  CMediaKernel::UserChangeState(uint16_t wType, uint8_t byValue)
{
	STRU_UC_CL_CRS_USER_STATE_CHG_ID_390 lStru;
	lStru.mi64UserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mwChgType = wType;
	lStru.mbyChgVal = byValue;
	AutoSendPack(lStru);
}

void  CMediaKernel::SendSpeakerInfo(PRKN_STRU_SPEAKER_INFO apSpeakerInfo)
{
	STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID lStru;
	lStru.mbySpeakerNum = 1;

	lStru.mpSpeakerUserInfo = new STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::STRU_UC_CL_CRS_SPEAKER_INFO;

	lStru.mpSpeakerUserInfo->mbyMicIndex = apSpeakerInfo->mbyMicIndex;
	lStru.mpSpeakerUserInfo->mi64SpeakerUserID = apSpeakerInfo->mi64SpeakerUserID ;
	lStru.mpSpeakerUserInfo->mi64DstUserID = apSpeakerInfo->mi64DstUserID;
	lStru.mpSpeakerUserInfo->mbContainAudioInfo = apSpeakerInfo->mbContainAudioInfo;
	if(lStru.mpSpeakerUserInfo->mbContainAudioInfo)
	{
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mbyCodecType = apSpeakerInfo->mstrAudioInfo.mbyCodecType;
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mlSamplesPerSec = apSpeakerInfo->mstrAudioInfo.mlSamplesPerSec;
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mwKBitsPerSec = apSpeakerInfo->mstrAudioInfo.mwKBitsPerSec;
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mbyChannels = apSpeakerInfo->mstrAudioInfo.mbyChannels;
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mbyBitsPerSample = apSpeakerInfo->mstrAudioInfo.mbyBitsPerSample;
		lStru.mpSpeakerUserInfo->mstrAudioInfo.mulChannelID = apSpeakerInfo->mstrAudioInfo.mulChannelID;
	}
	lStru.mpSpeakerUserInfo->mbContainVideoInfo = apSpeakerInfo->mbContainVideoInfo;
	if(lStru.mpSpeakerUserInfo->mbContainVideoInfo)
	{
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mbyCodecType = apSpeakerInfo->mstrVideoInfo.mbyCodecType;
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mbyFramePerSecond = apSpeakerInfo->mstrVideoInfo.mbyFramePerSecond;
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mwFrameWidth = apSpeakerInfo->mstrVideoInfo.mwFrameWidth;
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mwFrameHeight = apSpeakerInfo->mstrVideoInfo.mwFrameHeight;
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mwBitCount = apSpeakerInfo->mstrVideoInfo.mwBitCount;
		lStru.mpSpeakerUserInfo->mstrVideoInfo.mulChannelID = apSpeakerInfo->mstrVideoInfo.mulChannelID;
	}

	AutoSendPack(lStru);	
	delete lStru.mpSpeakerUserInfo;
	lStru.mpSpeakerUserInfo = NULL;
	AutoSendPack(lStru);
}

void  CMediaKernel::VoiceChatRQ(int64_t ai64UserID)
{
	STRU_CL_CRS_VOICE_CHAT_RQ lStru;
	lStru.mi64SelfUserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DestUserId = ai64UserID;
	AutoSendPack(lStru);
}	

void  CMediaKernel::VoiceChatRS(int64_t ai64UserID)
{
	STRU_CL_CRS_VOICE_CHAT_RS lStru;
	lStru.mi64SelfUserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DestUserId = ai64UserID;
	AutoSendPack(lStru);
}	

void  CMediaKernel::StopVoiceChat(int64_t ai64UserID)
{
	STRU_CL_CRS_VOICE_CHAT_STOP_ID lStru;
	lStru.mi64SelfUserId = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DestUserId = ai64UserID;
	AutoSendPack(lStru);
}

void  CMediaKernel::ChangeAvsNodify(uint32_t aulAvsIP, uint16_t awAvsPort)
{
	STRU_UC_CL_CRS_USER_AVS_CHANGE_ID lStru;
	lStru.mi64UserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.muAvsIp = aulAvsIP;
	lStru.muVoicePort = awAvsPort;
	AutoSendPack(lStru);
}