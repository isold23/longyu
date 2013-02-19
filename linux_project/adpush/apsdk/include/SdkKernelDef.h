#ifndef RoomKernelDef_h__
#define RoomKernelDef_h__

//--------------------------------MPS_DEF_BEGIN----------------------------------
// 消息内容编码
typedef enum
{
	CHARSET_UTF8    = 0,
	CHARSET_GB2312  = 1,
	CHARSET_GBK     = 2
} ENUM_ENCODING_TYPE;

////////////////////////////////////////////////////////////
//对应MPS推送通用消息格式中的msg_type字段。
const int OP_MPS_MSG_WEB_TYPE			        =	0;//WEB形式MPS系统消息
const int OP_MPS_MSG_PROP_TYPE			        =	1;//道具购买MPS系统消息
const int OP_MPS_MSG_SHOWBAR_TYPE		     	=	2;//秀吧相关的MPS系统消息
const int OP_MPS_MSG_USR_INF_CHG_TYPE			=	3;//用户信息修改通知MPS消息
const int OP_MPS_MSG_PAY_NOTIFY_TYPE			=	4;//用户充值通知MPS消息
const int OP_MPS_MSG_WAGE_NOTIFY_TYPE			=	5;//用户领取工资通知MPS消息
//////////////////////////////////////////////////////////////////////////

//--------------------------------MPS_DEF_END----------------------------------


//登录错误
const uint8_t CBY_UNKNOW_ERROR  = 1;			//未知错误
const uint8_t CBY_GENERAL_ERROR = 2;			//一般错误 返回错误信息
const uint8_t CBY_ROOM_FULL	 = 3;			//人数已满
const uint8_t CBY_MEMBER_FULL   = 4;			//会员已满

//用户权限级别
const uint8_t DEF_LEVEL_NORAM       = 0;           //普通用户
const uint8_t DEF_LEVEL_TEMP        = 4;           //临管
const uint8_t DEF_LEVEL_MANAGER     = 6;           //管理员
const uint8_t DEF_LEVEL_ROOM_OWENER = 7;           //室主
const uint8_t DEF_LEVEL_TITLE       = 8;           //主题管理员
const uint8_t DEF_LEVEL_PATROL      = 254;         //巡察
const uint8_t DEF_LEVEL_SUPER       = 255;         //超管 

//麦操作
#define DEF_MIC_MGR_TYPE_LOOT		1//夺麦
#define DEF_MIC_MGR_TYPE_GET		2//收麦
#define DEF_MIC_MGR_TYPE_SET		3//递麦
#define DEF_MIC_MGR_TYPE_PREPARE	4//准备接麦


#define DEF_ADMINCTRL_MIC_SWITCH		1//麦开关切换
#define DEF_ADMINCTRL_VIDEO_SWITCH		2//视频关切换
#define DEF_ADMINCTRL_MGR_SWITCH		3//管麦理切换

#define DEF_AUDIO_OPERATOR				0		//音频操作
#define DEF_VIDEO_OPERATOR				1		//视频操作

#define DEF_SEND_AUDIO					1//发送语音
#define DEF_RECV_AUDIO					2//接收语音
#define DEF_SEND_VIDEO					3//发送视频
#define DEF_ALLOW_RECORD_AUDIO			5//允许录音
#define DEF_ALLOW_RECORD_VIDEO			6//允许录像

#define DEF_ALLOW_FLOWER				0//允许献花
#define DEF_ALLOW_PUBCHAT				1//允许公聊

const uint16_t REFUSE_PRIVATE 		= 0x1006;		//拒绝接收私聊信息
const uint16_t REFUSE_CHAT			= 0x1007;		//拒绝任何聊天信息
const uint16_t REFUSE_PUBLIC		= 0x100D;		//屏蔽公聊提示对方
const uint16_t REFUSE_PRICHAT		= 0x1010;		//拒绝对聊


//管理员操作
#define DEF_ADMIN_OP_UPGRADE		10//任命管理员
#define DEF_ADMIN_OP_UNUPGRADE		11//解除管理员

#define DEF_ADMIN_OP_FORBID_TALK	12//禁止发言
#define DEF_ADMIN_OP_UNFORBID_TALK	13//解禁发言

#define DEF_ADMIN_OP_KICK_NORMAL	14//临时踢出
#define DEF_ADMIN_OP_KICK_LIMIT		15//限时踢出
#define DEF_ADMIN_OP_KICK_FOREVER	16//永久踢出
#define DEF_ADMIN_OP_UNKICK_LIMIT	17//解除限时踢出

#define DEF_ADMIN_OP_FORBID_LIMIT	29//限时禁止IP
#define DEF_ADMIN_OP_FORBID_FOREVER	30//永久禁止IP
#define DEF_ADMIN_OP_UNFORBID		31//恢复禁止IP

//发送礼物结果
#define DEF_CHECK_PROP_AVAILABLE_FAILD                  0//服务器验证失败
#define DEF_CHECK_PROP_AVAILABLE_SUCCESS                1//验证成功
#define DEF_CHECK_PROP_AVAILABLE_CHECK_TIMEOUT          2//道具使用检查超时
#define DEF_CHECK_PROP_AVAILABLE_FULL                   3//队列已满
#define DEF_CHECK_PROP_AVAILABLE_DOWNLOADING            4//本地素材下载中
#define DEF_CHECK_PROP_AVAILABLE_DL_FAILD               5//道具下载失败
#define DEF_CHECK_PROP_AVAILABLE_UNKNOW_EXCPTION		6//未知错误
#define DEF_CHECK_PROP_AVAILABLE_VERSION_TOO_LOW		7//版本过低
#define DEF_PROPS_CHECK_RESULT_NOT_EXIST                8 //道具不存在
#define DEF_PROPS_CHECK_RESULT_SERVER_ERROR             9 //道具商城错误
#define DEF_PROPS_CHECK_RESULT_HTTP_ERROR               10 //HTTP库错误

#define DEF_CHECKPROPS_AVAILABLE_GETINFOFAILED         	14 //获取道具信息失败
#define DEF_CHECK_PROP_AVAILABLE_REDUEC                 15 //减少用户余额失败
#define DEF_CHECK_PROP_AVAILABLE_INCREASE               16 //增加收礼人金额失败
#define DEF_CHECK_PROP_AVAILABLE_POOL                   17 //增加资金池金额失败

//----------------------------------
typedef struct RKN_STRU_USER_INFO
{
	int64_t	m_i64UserID; 			//用户ID
	char* 	mpszNickName;			//用户昵称
	uint16_t 	mwPhotoNum;			//用户头像
	uint8_t 	mbyPower;			//用户权限
	int32_t 	mlUserState;		//用户状态
	int32_t  	miVipLevel;			//VIP级别
	uint8_t	mbyVoiceState;			//语音状态
	uint8_t    mbyLoginSource;		//登录来源
	bool       mbVisitor;			//是否游客  
}*PRKN_STRU_USER_INFO;

//----------------------------------
typedef struct RKN_STRU_BLACK_USER
{
	int64_t mi64UserID;			//用户ID
	int32_t   mlLimitedTime;		//限制时间
	int32_t   mlResidualTime;		//剩余时间
}*PRKN_STRU_BLACK_USER;

//----------------------------------
typedef struct RKN_STRU_BLACK_IP_USER
{
	int64_t mi64UserID;			//用户ID
	uint32_t mulIP;	    //IP
	int   mlLimitedTime;		//限制时间
	int32_t   mlResidualTime;		//剩余时间
}*PRKN_STRU_BLACK_IP_USER;

//----------------------------------
const uint8_t CBY_MD_PHOTO_NUMBER = 0;
const uint8_t CBY_MD_NICK_NAME    = 1;

typedef struct RKN_STRU_MD_USER_INFO_ITEM
{
	uint8_t m_byMdType;
	char* mpszMdValue;
}*PRKN_STRU_MD_USER_INFO_ITEM;

typedef struct RKN_STUR_MD_USER_INFO 
{
	int64_t mi64UserID;
	uint8_t mbyItemCount;
	PRKN_STRU_MD_USER_INFO_ITEM mpItemList;
}*PRKN_STUR_MD_USER_INFO;

//------------------------------------
typedef struct RKN_STRU_AVS_INFO 
{
	char* mpszAvsName;
	uint32_t	mulAvsIp;
	uint16_t	musVoicePort;
}*PRKN_STRU_AVS_INFO;

//----------------------------------
//麦的音频配置信息
struct RKN_STRU_AUDIO_CONFIG
{
	uint8_t	mbyCodecType;				//使用的编解码类型
	int	mlSamplesPerSec;   			//采样频率
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t musKBitsPerSec;        		//输出带宽(kbps)
	uint8_t    mbyChannels;				//声音通道数(1为单声道,2为立体声)
	uint8_t    mbyBitsPerSample;   		//采样大小(位)
};

//麦的视频配置信息
struct RKN_STRU_VIDEO_CONFIG
{
	uint8_t	mbyCodecType;				//视频编码类型
	uint8_t	mbySizeType;				//视频大小类型
	uint32_t mulBandWidth;				//视频占用带宽（单位kbits）
	uint8_t	mbyFramePerSecond;			//视频帧率（0为动态调整，1－15为实际设置帧率）	
};

typedef struct RKN_STRU_MIC_INFO
{
	uint8_t	mbyMicIndex;
	bool				mbSupportVideo;		//支持视频
	RKN_STRU_AUDIO_CONFIG	mstruAudioConfig;	//音频配置信息
	RKN_STRU_VIDEO_CONFIG	mstruVideoConfig;	//视频配置信息

	uint16_t	mwMicStatue;    				//麦克状态
	//第2位:麦是否打开 第3位:是否关闭视频 第4位:是否被管理 第6位:是否允许放歌
	//(运行/停止 是否支持视频 是否处于管理状态) 
	uint16_t	mwMicTimeLen;  					//麦序时长
	int64_t mi64ManagerID;  					//管理员ID
	int	mlDeltaSpeakTime;				//与麦时的差值

}*PRKN_STRU_MIC_INFO;

//发言人的视频信息
struct RKN_STRU_VIDEO_INFO
{
	uint8_t	mbyCodecType;			//视频编码类型
	uint8_t	mbyFramePerSecond;			//视频帧率（0为动态调整，1－15为实际设置帧率）

	uint16_t	mwFrameWidth;				//图像宽度
	uint16_t	mwFrameHeight;				//图像高度
	uint16_t	mwBitCount;					//位图颜色深度
	uint32_t	mulChannelID;				//视频通道ID
};

//发言人的视频信息
struct RKN_STRU_AUDIO_INFO
{
	uint8_t	mbyCodecType;				//使用的编解码类型
	int	mlSamplesPerSec;   			//采样频率
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t    mwKBitsPerSec;        		//输出带宽(kbps)
	uint8_t    mbyChannels;				//声音通道数(1为单声道,2为立体声)
	uint8_t    mbyBitsPerSample;   		//采样大小(位)
	uint32_t	mulChannelID;				//音频通道ID
};

typedef struct RKN_STRU_SPEAKER_INFO
{
	//		私聊的用户ID
	int64_t			mi64DstUserID;				//0		所有用户
	int64_t			mi64SpeakerUserID;			//发言用户ID
	uint8_t 			mbyMicIndex;				//使用的MicIncex
	bool			mbContainAudioInfo;			//包含音频格式
	bool			mbContainVideoInfo;			//包含视频信息
	RKN_STRU_AUDIO_INFO	mstrAudioInfo;				//上面的标识为假跳过，音频格式
	RKN_STRU_VIDEO_INFO	mstrVideoInfo;				//上面的标识为假跳过，视频格式信息
}*PRKN_STRU_SPEAKER_INFO;

typedef struct RKN_STRU_BIG_GIFT_NOTIFY 
{
	int64_t mi64FromID;
	char* mpszFromNick;
	uint8_t mbyFromVipLevel;		//VIP级别，1~6级，0为非秀星
	uint8_t mbyFromPeerLevel;		//贵族级别，1~5级，0为非贵族
	uint8_t mbyFromPowerLevel;		//管理员级别
	uint8_t mbyFromWeekStar;		//周星， 0为非周星
	uint8_t mbyFromSeller;			//官方销售，0不是销售，1是销售

	int64_t mi64ToID;
	char* mpszToNick;
	uint8_t mbyToVipLevel;		//VIP级别，1~6级，0为非秀星
	uint8_t mbyToPeerLevel;		//贵族级别，1~5级，0为非贵族
	uint8_t mbyToPowerLevel;		//管理员级别
	uint8_t mbyToWeekStar;		//周星， 0为非周星
	uint8_t mbyToSeller;			//官方销售，0不是销售，1是销售

	int32_t miGiftID;	//礼物ID
	int32_t miCount;	//礼物数量
	char* mpszGiftName;//礼物名称
	int32_t mstrTimeStamp; //00:00:00 UTC, January 1, 1970

}*PRKN_STRU_BIG_GIFT_NOTIFY;

typedef struct RKN_STRU_LOUDSPEAKER_NOTIFY
{
	int64_t mi64FromID;
	char* mpszFromNick;
	uint8_t mbyFromVipLevel;		//VIP级别，1~6级，0为非秀星
	uint8_t mbyFromPeerLevel;		//贵族级别，1~5级，0为非贵族
	uint8_t mbyFromPowerLevel;		//管理员级别
	uint8_t mbyFromWeekStar;		//周星， 0为非周星
	uint8_t mbyFromSeller;			//官方销售，0不是销售，1是销售

	uint8_t mbyType;			//喇叭类型 4:小喇叭 5:大喇叭，11:Html格式喇叭  1~3未使用
	char* mpszControl;		   //控制串  带字体、表情信息
	char* mpszContent;		   //内容串

}*PRKN_STRU_LOUDSPEAKER_NOTIFY;

typedef struct RKN_STRU_AWARD_EXTRA_DATA
{
	int32_t m_nIndex;          // 中奖道具所处的索引
	int32_t m_nTimes;          // 当前中奖倍数
	int64_t m_i64GainPoint;    // 奖励的U点值	
}*PRKN_STRU_AWARD_EXTRA_DATA;

typedef struct RKN_STRU_AWARD_EXTRA_DATA2
{
	int32_t miMultiple;          //倍数
	int32_t miTimes;             //次数	
}*PRKN_STRU_AWARD_EXTRA_DATA2;

#endif // RoomKernelDef_h__