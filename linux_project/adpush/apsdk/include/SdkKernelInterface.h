#ifndef RoomKernelInterface_h__
#define RoomKernelInterface_h__

#include "SdkKernelDef.h"


const uint32_t UID_BASE_PROCESS = 100;

const uint32_t UID_MEDIA_PROCESS = 200;

const uint32_t UID_VALUE_ADDED_PROCESS = 300;

const uint32_t UID_MPS_PROCESS = 400;


const uint32_t UID_BASE_KERNEL = 100;

const uint32_t UID_MEDIA_KERNEL = 200;

const uint32_t UID_VALUE_ADDED_KERNEL = 300;

const uint32_t UID_MPS_KERNEL = 400;

//外部基础业务处理接口
struct IBaseProcess
{
	//连接终止			
	virtual void  OnConnetAborted() = 0;

	//登录成功
	virtual void  OnLoginSucc(uint32_t ulToken, int32_t alRoomState, int64_t i64RoomProperty,
										char* pszTopic, char* pszSalutatory, char* pszRoomPsw) = 0;

	//登录失败
	virtual void  OnLoginFailed(uint8_t byError, char* pszError) = 0;

	//如果是游客登录的话 这里用来返回用户信息
	virtual void  OnVisitorUserInfo(int64_t ai64VisitorID, char* apszNickName, uint16_t ausPhotoNumber) = 0;

	//用户进入
	virtual void  OnUserEnter(PRKN_STRU_USER_INFO pUser) = 0;

	//用户离开
	virtual void  OnUserLeave(int64_t ai64UserID, uint8_t byLeaveType, char* pszReason) = 0;

	//用户列表
	virtual void  OnUserList(PRKN_STRU_USER_INFO ppUser, uint16_t usCount) = 0;

	//献花
	virtual void  OnFlower(int64_t ai64From, int64_t ai64To, int32_t alFlowerIndex) = 0;

	//聊天信息
	virtual void  OnChatMessage(uint8_t byChatType, int64_t ai64From, int64_t ai64To, char* apszMood, char* apszContrl, char* apszContent) = 0;

	//广播
	virtual void  OnBroadCast(int64_t ai64UserID, char* apsCastContent) = 0;

	//聊天验证码
	virtual void OnChatVerifyCode(char* apszURL) = 0;

	//用户被处理通知
	virtual void  OnUserBeOperatedNotify(int64_t ai64ManagerID, int64_t ai64UserID, uint8_t byOpType, char* apszDescribe) = 0;

	//聊天室主题等属性修改通知
	virtual void  OnRoomPropertyChangedNotify(int64_t ai64ManagerID, char* apszTopic, char* apszSalutatory, char* apszExtPassWord, bool abExtLocked, bool abExtEnabled) = 0;

	//房间背景
	virtual void  OnRoomBackGroundBmp(char* apszBmp) = 0;

	//黑名单列表
	virtual void  OnBlackList(uint16_t ausCount, PRKN_STRU_BLACK_USER apBlackList) = 0;

	//黑IP列表
	virtual void  OnBlackIPList(uint16_t ausCount, PRKN_STRU_BLACK_IP_USER apBlackList) = 0;

	//房间状态修改通知
	/*
	#define DEF_ALLOW_FLOWER				0//允许献花
	#define DEF_ALLOW_PUBCHAT				1//允许公聊
	*/
	virtual void  OnRoomStateChangedNotify(int64_t ai64ManagerID, uint16_t ausPropType, bool abValue) = 0;

	//用户隐身状态改变通知
	virtual void  OnUserHermitStateChanged(int64_t ai64UserID, bool abHermit) = 0;

	//用户信息修改通知
	virtual void  OnUserInfoChanged(PRKN_STUR_MD_USER_INFO apMdInfo) = 0;

	//用户一般信息 服务器透明转发
	/*
	const uint16_t REFUSE_PRIVATE 		= 0x1006;		//拒绝接收私聊信息
	const uint16_t REFUSE_CHAT			= 0x1007;		//拒绝任何聊天信息
	const uint16_t REFUSE_PUBLIC		= 0x100D;		//屏蔽公聊提示对方
	const uint16_t REFUSE_PRICHAT		= 0x1010;		//拒绝对聊
	*/
	virtual void  OnUserGeneralInfo(int64_t ai64UserID, uint16_t ausType) = 0;

	//丢包率应答
	virtual void  OnLostRateRs(int64_t ai64UserID, int32_t aiLostRate) = 0;

	//周星通知 aiGiftID:礼物ID  aiCount：连续几周星 bNewUser：表示用户是新进房间还是已经在房间的 abEnd：后面是否还有通知  当双料周星 三料周星时 会有多次通知
	virtual void  OnWeekStarNotify(int64_t ai64UserID, int32_t aiGiftID, int32_t aiCount, bool bNewUser, bool abEnd) = 0;

	//贵族通知
	virtual void  OnPeerNotify(int64_t ai64UserID, int32_t aiPeerLevel, bool bNewUser) = 0;

	//官方销售
	virtual void  OnSellerNotify(int64_t ai64UserID, bool bNewUser) = 0;	

	/*-------------------------
	函数名称：管理用户应答
	参数说明：ai64UserID:目标用户id aiOpType:操作类型  DEF_ADMIN_OP_UPGRADE-DEF_ADMIN_OP_UNFORBID
				aiResult:操作结果 0表示成功 反之失败   pszDescription:操作说明
	返回值：无
	-------------------------*/
	virtual void OnManageUserResult(int64_t ai64UserID, int8_t aiOpType, int8_t aiResult, char* pszDescription) = 0;
};

//外部媒体业务处理接口
struct IMediaProcess
{
	//麦序列表
	virtual void  OnMicOrderList(int64_t* apList, uint16_t usCount) = 0;

	//麦列表
	virtual void  OnMicList(PRKN_STRU_MIC_INFO apMicList, uint16_t usCount) = 0;

	//发言人列表
	virtual void  OnSpeakerList(PRKN_STRU_SPEAKER_INFO apSpeakerList, uint16_t usCount) = 0;

	//排麦应答
	virtual void  OnApplyMicRs(uint8_t abyMicIndex) = 0;

	//开始发言通知
	virtual void  OnBeginSpeak(uint8_t abyMicIndex) = 0;

	//对聊请求
	virtual void  OnVoiceChatRQ(int64_t ai64UserID) = 0;

	//对聊应答
	virtual void  OnVoiceChatRS(uint8_t abyResult, int64_t ai64SrcUserID, int64_t ai64DestUserID) = 0;

	//对聊停止通知
	virtual void  OnVoiceChatStop(int64_t ai64UserID) = 0;

	//插麦通知
	virtual void  OnInsertMicNotify(int64_t ai64ManagerID, int64_t ai64DestUserID, uint8_t abyIndex) = 0;

	//递麦通知
	virtual void  OnGiveMic(int64_t ai64ManagerID, int64_t aiUserID) = 0;

	//管理员修改了麦时
	virtual void  OnMicTimeChanged(int64_t ai64ManagerID, uint8_t abyIndex, uint8_t abyMinute) = 0;

	//用户状态应答
	virtual void  OnUserStateRS(int64_t ai64UserID, int32_t alState) = 0;

	//管理员管麦通知
	virtual void  OnManageMicStateNotify(int64_t ai64ManagerID, uint8_t abyIndex, uint8_t abyOpType, bool abState) = 0;

	//用户语音状态改变通知
	virtual void  OnUserVocieStateChanged(int64_t ai64UserID, uint8_t abyState) = 0;

	//AVS通知 aiType 0：变更AVS  不为0：变更AVS的同时指定最优项
	virtual void  OnAVSChanged(int32_t aiType, uint16_t ausCount, PRKN_STRU_AVS_INFO pAvsList) = 0;
};

//外部增值业务处理接口
struct IValueAddedProcess
{
	//发送礼物结果  /*abyResult: DEF_CHECK_PROP_AVAILABLE_FAILD ~ DEF_CHECK_PROP_AVAILABLE_POOL*/
	virtual void OnSendGiftResult(uint8_t abyResult, int64_t ai64UserID, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount) = 0;

	//礼物广播								//发送人					接收人      礼物ID           礼物名称			赠送总数
	virtual void OnGiftNotify(int64_t ai64UserFrom, int64_t ai64UserTo, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount,
											  //分包标识        本次开始             本次数目           收到总数
											int32_t aiPackMark, int32_t aiPackBeginNum, int32_t aiPackUseNum, int32_t aiRecvCount) = 0;

	//大礼物广播
	virtual void OnBigGiftNotify(PRKN_STRU_BIG_GIFT_NOTIFY apBigGiftNotify) = 0;	

	//虚拟币余额通知
	virtual void OnBalanceNotify(int64_t ai64Balance) = 0;	

	//发送喇叭结果
	virtual void OnLoudSpeakerResult(uint8_t abyResult, char* apszReason) = 0;

	//喇叭通知
	virtual void OnLoudSpeakerNotify(PRKN_STRU_LOUDSPEAKER_NOTIFY apLoudSpeakerNotify) = 0;

	//幸运道具通知	
	//说明 aiPackMark就是方法OnGiftNotify里面的aiPackMark  仅用于输出同步 
									   //分包标识          用户ID				用户昵称			礼物ID            最大倍数 
	virtual void OnAwardPropNotify(int32_t aiPackMark, int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiMaxTimes,
						//扩展数据数组长度			扩展数据数组
						int32_t aiExtraDataCount, PRKN_STRU_AWARD_EXTRA_DATA apExtraDataArray) = 0;

	//幸运道具统计	
	//说明 aiPackMark就是方法OnGiftNotify里面的aiPackMark  仅用于输出同步		此通知只会在自己中奖时收到
	//此通知中PRKN_STRU_AWARD_EXTRA_DATA中的m_i64GainPoint无效
								    //分包标识          用户ID				用户昵称			  礼物ID            最大倍数 
	virtual void OnAwardPropInfo(int32_t aiPackMark, int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiMaxTimes,
		//扩展数据数组长度			扩展数据数组
		int32_t aiExtraDataCount, PRKN_STRU_AWARD_EXTRA_DATA2 apExtraDataArray) = 0;


	//烟花通知						发送用户ID				发送用户昵称      礼物ID			使用数量           自己分到的U点数
	virtual void OnFireWorksNotify(int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiUseCount, int64_t ai64GainPoint) = 0;
};

struct IMpsProcess
{
	/*-------------------------
	函数名称：MPS通知
	参数说明：u8MsgEncoding:编码格式（CHARSET_UTF8 = 0,	CHARSET_GB2312 = 1, CHARSET_GBK = 2）
			pDataBuf:数据内容
			<msg_root>
				<msg_header>
					<msg_type></msg_type>
				</msg_header>
				<msg_body>
				</msg_body>
			</msg_root>
	返回值：无
	-------------------------*/
	virtual void OnMpsNotify(uint8_t u8MsgEncoding, const char *pDataBuf) = 0;
};

struct ISdkProcess
{
	//请求接口
	virtual bool  QueryInterface(uint32_t uID, void** ppVoid) = 0;

	/*线程同步方法 这是唯一不在上层调用线程回调的方法
	此通知上层在主线程调用SolveTask
	以保证其它回调都在调用线程（通常是主线程）里*/
	virtual void  NewTaskEvent() = 0; 
};

struct IBaseKernel
{
	//初始化                   客户端版本号      是否有摄像头       登录来源客户端标识
	virtual void  Initialize(char* apszVersion, bool abHaveVideo, uint8_t abyLoginSource) = 0;

	//登录房间
	virtual void  LoginRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort, const char* pszRoomPsw, const char* pszMachineCode ) = 0;

	//退出房间
	virtual void  LogOut(int32_t alRoomId) = 0;	

	//献花
	virtual void  SendFlower(int64_t ai64SendTo, uint8_t abyFlowerIndex) = 0; 

	//发送聊天信息
	virtual void  SendChat(uint8_t byChatType, int64_t ai64SendTo, char* apszMood, char* apszContrl, char* apszContent) = 0;

	//隐身
	virtual void  ChangeHermitState(bool bHermit) = 0;  

	//管理用户
	virtual void  ManageUser(int64_t ai64UserID, uint8_t byType, int32_t otherParam, char* strText) = 0;

	//请求用户黑名单 限管理员
	virtual void  GetBlackList() = 0;	

	//请求IP黑名单  限管理员
	virtual void  GetBlackIPList() = 0;	

	//更改房间状态请求
	/*
	#define DEF_ALLOW_FLOWER				0//允许献花
	#define DEF_ALLOW_PUBCHAT				1//允许公聊
	*/
	virtual void  ModifyRoomStateRQ(uint16_t wProperty, bool abValue) = 0;

	//房间广播 限管理员
	virtual void  SendBroadCast(char* astrText) = 0;

	//修改房间属性 加锁、密码、主题、欢迎词
	virtual void  ModifyRoomProperty(bool bLocked, char* strPSW, char* strTopic, char* strSalutatory) = 0;	

	//用户一般信息 服务器透明转发
	/*
	const uint16_t REFUSE_PRIVATE 		= 0x1006;		//拒绝接收私聊信息
	const uint16_t REFUSE_CHAT			= 0x1007;		//拒绝任何聊天信息
	const uint16_t REFUSE_PUBLIC		= 0x100D;		//屏蔽公聊提示对方
	const uint16_t REFUSE_PRICHAT		= 0x1010;		//拒绝对聊
	*/
	virtual void  SendGeneralInfo(int64_t ai64UserID, uint16_t wType) = 0;

	//更改用户信息
	virtual void  ModifyUserInfo(PRKN_STRU_MD_USER_INFO_ITEM apItemList, uint8_t abyItemCount) = 0;		
};

struct IMediaKernel
{
	//排麦
	virtual void  ApplyMic() = 0;	

	//麦管理请求
	/*
	#define DEF_MIC_MGR_TYPE_LOOT		1//夺麦
	#define DEF_MIC_MGR_TYPE_GET		2//收麦
	#define DEF_MIC_MGR_TYPE_SET		3//递麦
	#define DEF_MIC_MGR_TYPE_PREPARE	4//准备接麦
	*/
	virtual void  ManageMic(int64_t ai64UserID, uint8_t byType, uint8_t byIndex) = 0;

	//把某人插到指定麦序位置
	virtual void  InsertMic(int64_t ai64UserID, uint8_t byIndex) = 0;

	//停止发言
	virtual void  StopSpeak() = 0;

	//修改麦时长
	virtual void  ChangeMicTime(uint8_t byIndex, uint8_t byTime) = 0;

	//管理员管理麦请求
	/*
	#define DEF_ADMINCTRL_MIC_SWITCH		1//麦开关切换
	#define DEF_ADMINCTRL_VIDEO_SWITCH		2//视频关切换
	#define DEF_ADMINCTRL_MGR_SWITCH		3//管麦理切换
	*/
	virtual void  ManageMicState(uint8_t byType, uint8_t byIndex, bool abValue) = 0;

	//用户对麦操作请求
	/*
	#define DEF_AUDIO_OPERATOR				0		//音频操作
	#define DEF_VIDEO_OPERATOR				1		//视频操作
	*/
	virtual void  ChangeRecvState(uint8_t byType, uint8_t byIndex, bool abState) = 0;	

	//用户状态请求 在录音、录像前调用查看目标用户是否允许该操作
	virtual void  UserStateRQ(int64_t ai64Dest) = 0;

	//用户状态变更请求
	/*
	#define DEF_SEND_AUDIO					1//发送语音
	#define DEF_RECV_AUDIO					2//接收语音
	#define DEF_SEND_VIDEO					3//发送视频
	#define DEF_ALLOW_RECORD_AUDIO			5//允许录音
	#define DEF_ALLOW_RECORD_VIDEO			6//允许录像
	*/
	virtual void  UserChangeState(uint16_t wType, uint8_t byValue) = 0;	

	//发言人信息  上麦发言时发送本地语音视频配置信息
	virtual void  SendSpeakerInfo(PRKN_STRU_SPEAKER_INFO apSpeakerInfo) = 0; 

	//对聊请求
	virtual void  VoiceChatRQ(int64_t ai64UserID) = 0;	

	//同意对聊应答  不同意时不用发送
	virtual void  VoiceChatRS(int64_t ai64UserID) = 0;	

	//停止对聊
	virtual void  StopVoiceChat(int64_t ai64UserID) = 0;

	//变更AVS通知
	virtual void  ChangeAvsNodify(uint32_t aulAvsIP, uint16_t awAvsPort) = 0;
};

struct IValueAddedKernel
{
	//发送礼物给某人
	virtual void  SendGift(int64_t ai64UserID, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount) = 0;

	//发送喇叭
	virtual void  SendLoudSpeaker(uint8_t abyType, char* apszContent, char* apszControl) = 0;
};

struct IMpsKernel 
{
	//调用此方法之前必须先调用SetUserInfo  如果是游客的话，此方法不执行任何操作
	virtual void ConnectMps(char* szAddr, uint16_t usPort) = 0;

	virtual void CloseMpsConnection() = 0;
    
    virtual void SetServerID ( uint16_t ) = 0;
};

struct ISdkKernel
{
	//获取错误码
	virtual uint32_t  GetLastError() = 0;

	//请求接口
	virtual bool  QueryInterface(uint32_t uID, void** ppVoid) = 0;

	//设置IRoomProcess接口
	virtual void  SetProcess(ISdkProcess* pSdkProcess) = 0;

	/*********************************************************
	* 同步方法 
	* SDK在内部有新任务要通知上层时，会把所有回调动作缓存起来 
	* 同时调用NewTaskEvent通知上层，转到主线程调用此方法
	*   当调用线程调用此方法时，SDK一次性执行所有缓存的动作
	*   达到让所有回调执行在调用线程的目的
	**********************************************************/
	virtual void  SolveTask() = 0;

	//设置用户信息
	virtual void  SetUserInfo(int64_t ai64UserID, const char* apszNick, const char* apszPsw, uint16_t usPhotoNm) = 0;

	//设置网络信息
	virtual void  SetNetInfo(int32_t netType,const char* proxyIP, int32_t proxyPort,const char* proxyUser,const char* proxyPwd) = 0;
};

#if defined(_WIN32)
extern "C" void __stdcall CreateObject(ISdkKernel** ppSdkKernel);
#else
extern "C" void CreateObject(ISdkKernel** ppSdkKernel);
#endif

#endif // RoomKernelInterface_h__