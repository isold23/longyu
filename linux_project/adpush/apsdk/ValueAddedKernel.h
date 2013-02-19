#ifndef _VALUE_ADDED_KERNEL_H_
#define _VALUE_ADDED_KERNEL_H_

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"

class CValueAddedKernel :public IRoomKernel, public IValueAddedKernel
{
private:
	//发送礼物给某人
	virtual void  SendGift(int64_t ai64UserID, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount);

	//发送喇叭
	virtual void  SendLoudSpeaker(uint8_t abyType, char* apszContent, char* apszControl);
};
#endif //_VALUE_ADDED_KERNEL_H_
