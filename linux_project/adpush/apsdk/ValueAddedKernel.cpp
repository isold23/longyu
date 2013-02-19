
#include "ValueAddedKernel.h"
#include "base/pack/crs_cl_strudef.h"


void  CValueAddedKernel::SendGift(int64_t ai64UserID, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount)
{
	STRU_UC_CL_CRS_GIFT_PROP_USE_RQ lStru;
	lStru.mi64UserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;
	lStru.mi64DestID = ai64UserID;
	lStru.miContentID = aiGiftID;
	lStru.miUseCount = aiUseCount;
	strncpy(lStru.mszContentName, apszGiftName, sizeof(lStru.mszContentName));
	AutoSendPack(lStru);
}

void  CValueAddedKernel::SendLoudSpeaker(uint8_t abyType, char* apszContent, char* apszControl)
{
	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY lStru;
	lStru.mbyType = abyType;
	lStru.mi64FromUserID = m_pRoomKernelService->GetUserInfo().m_i64UserID;

	lStru.mChatInfo.mi64FromId = m_pRoomKernelService->GetUserInfo().m_i64UserID;

	strncpy(lStru.mChatInfo.mstrContent, apszContent, sizeof(lStru.mChatInfo.mstrContent));
	strncpy(lStru.mChatInfo.mstrControl, apszControl, sizeof(lStru.mChatInfo.mstrControl));

	lStru.mChatInfo.mwContentLen = (uint16_t)strlen(lStru.mChatInfo.mstrContent);
	lStru.mChatInfo.mwControlLen = (uint16_t)strlen(lStru.mChatInfo.mstrControl);
	lStru.mChatInfo.mwMoodLen = 0;
	lStru.mwMessageLen = lStru.mChatInfo.mwContentLen + lStru.mChatInfo.GetSubLen();

	AutoSendPack(lStru);
}