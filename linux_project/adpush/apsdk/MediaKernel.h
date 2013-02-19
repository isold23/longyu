#ifndef MediaKernel_h__
#define MediaKernel_h__

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"
#include "base/pack/crs_cl_strudef.h"

class CMediaKernel: public IRoomKernel, public IMediaKernel
{
private:
	//排麦
	virtual void  ApplyMic();	

	//麦管理请求
	/*
	#define DEF_MIC_MGR_TYPE_LOOT		1//夺麦
	#define DEF_MIC_MGR_TYPE_GET		2//收麦
	#define DEF_MIC_MGR_TYPE_SET		3//递麦
	#define DEF_MIC_MGR_TYPE_PREPARE	4//准备接麦
	*/
	virtual void  ManageMic(int64_t ai64UserID, uint8_t byType, uint8_t byIndex);

	//把某人插到指定麦序位置
	virtual void  InsertMic(int64_t ai64UserID, uint8_t byIndex);

	//停止发言
	virtual void  StopSpeak();

	//修改麦时长
	virtual void  ChangeMicTime(uint8_t byIndex, uint8_t byTime);

	//管理员管理麦请求
	/*
	#define DEF_ADMINCTRL_MIC_SWITCH		1//麦开关切换
	#define DEF_ADMINCTRL_VIDEO_SWITCH		2//视频关切换
	#define DEF_ADMINCTRL_MGR_SWITCH		3//管麦理切换
	*/
	virtual void  ManageMicState(uint8_t byType, uint8_t byIndex, bool abValue);

	//用户对麦操作请求
	/*
	#define DEF_AUDIO_OPERATOR				0		//音频操作
	#define DEF_VIDEO_OPERATOR				1		//视频操作
	*/
	virtual void  ChangeRecvState(uint8_t byType, uint8_t byIndex, bool abState);	

	//用户状态请求 在录音、录像前调用查看目标用户是否允许该操作
	virtual void  UserStateRQ(int64_t ai64Dest);

	//用户状态变更请求
	/*
	#define DEF_SEND_AUDIO					1//发送语音
	#define DEF_RECV_AUDIO					2//接收语音
	#define DEF_SEND_VIDEO					3//发送视频
	#define DEF_ALLOW_RECORD_AUDIO			5//允许录音
	#define DEF_ALLOW_RECORD_VIDEO			6//允许录像
	*/
	virtual void  UserChangeState(uint16_t wType, uint8_t byValue);	

	//发言人信息  上麦发言时发送本地语音视频配置信息
	virtual void  SendSpeakerInfo(PRKN_STRU_SPEAKER_INFO apSpeakerInfo); 

	//对聊请求
	virtual void  VoiceChatRQ(int64_t ai64UserID);	

	//同意对聊应答  不同意时不用发送
	virtual void  VoiceChatRS(int64_t ai64UserID);	

	//停止对聊
	virtual void  StopVoiceChat(int64_t ai64UserID);

	//变更AVS通知
	virtual void  ChangeAvsNodify(uint32_t aulAvsIP, uint16_t awAvsPort);
};
#endif // MediaKernel_h__