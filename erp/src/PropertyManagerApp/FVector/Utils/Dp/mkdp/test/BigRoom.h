#ifndef ____BIG_ROOM__
#define ____BIG_ROOM__
#include "Dp.h"

struct _d_struct stLoginAppearance
{
	_d_serializable_impl(stLoginAppearance)

	_d_id(-) uint64_t	userId;
	_d_id(-) Dp::String<NICK_NAME_LEN> nick;
	_d_id(-) uint16_t	photoIndex;
	_d_id(-) uint8_t	grade;										//用户级别   
	_d_id(-) uint32_t	redTime;								//秀星资格
	_d_id(-) Dp::String<DEF_USER_MOOD_LEN> mood;				//用户心情
	_d_id(-) Dp::String<URL_LINK_LEN> headUrl;	
	_d_id(-) uint8_t	sex; 									//用户性别
	_d_id(-) uint32_t 	charm;									//用户魅力值
	_d_id(-) uint32_t	wealth;									//用户财富值
	_d_id(-) uint32_t	activity;								//用户活跃度
	_d_id(-) uint32_t	vipRoomId;									//用户是否是VIP房
	_d_id(-) uint32_t	tycoon;										//大亨
	_d_id(-) uint32_t	seller;										//官方销售
	_d_id(-) uint8_t	weekStar;									//是否周星
};

void copy(const STRU_HALL_USER_INFO &hallUser,stLoginAppearance &userInfo)
{
	userInfo.userId = hallUser.mi64UserId;
	userInfo.nick.assign(hallUser.macNickName);
	userInfo.photoIndex = hallUser.mwPhotoIndex;
	userInfo.grade = hallUser.mbyGrade;
	userInfo.redTime = hallUser.miRedMemTime;
	userInfo.mood.assign(hallUser.mstrUserMood);
	userInfo.headUrl.assign(hallUser.mstrUserImageURL);
	userInfo.sex = hallUser.mbyUserSex;
	userInfo.charm = hallUser.miUserCharm;
	userInfo.wealth = hallUser.miUserWealth;
	userInfo.activity = hallUser.miUserActivity;
	userInfo.vipRoomId = hallUser.mlVipRooomID;
	userInfo.tycoon = hallUser.miTycoon;
	userInfo.seller = hallUser.miSeller;
	userInfo.weekStar = hallUser.mbyWeekStar;
}


//struct _f_struct stOverRoomAppearance
//{
//	_d_serializable_impl(stOverRoomAppearance)
//
//	_f_f uint32_t	hallId;
//	_f_d stLoginAppearance userInfo;;
//};

// 旁观客户端登录请求
#define UC_CL_CRS_WATCH_LOGIN_HALL_RQ 
struct stCrsWatchLoginReq : public STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007
{
	int Pack(char *buf,int len);
	int UnPack(char *buf,int len);
}
 				//用户语言类型

// 旁观登录回复
#define UC_CL_CRS_WATCH_LOGIN_HALL_RS
struct stCrsWatchLoginRet : public STRU_UC_CL_CRS_LOGIN_HALL_RS_2009
{
	int Pack(char *buf,int len);
	int UnPack(char *buf,int len);
};


// 旁观登录请求用户列表
#define UC_CL_CRS_WATCH_USERLIST_RQ
struct _f_struct tagCrsWatchUserListReq
{
	_d_serializable_impl(tagCrsWatchUserListReq)
	
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USERLIST_RQ);
	_f_f uint64_t userId;
};



// 返回列表
#define	UC_CL_CRS_WATCH_USERLIST_RS
struct tagCrsWatchUserListRet
{
	_d_serializable_impl(tagCrsWatchUserListRet)
	
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USERLIST_RS);
	_f_f uint32_t hallId;
	_f_a Dp::Array<stLoginAppearance> users;
};

// 新用户进入
#define UC_CL_CRS_WATCH_USER_ENTER_NOTIFY
struct _f_struct tagCrsWatchUserEnterNotify
{
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_ENTER_NOTIFY);
	_f_f uint32_t hallId;
	_f_d stLoginAppearance userInfo;
};

// 用户退出
#define UC_CL_CRS_WATCH_USER_LEFT_NOTIFY
struct tagCrsWatchUserLeftNotify
{ 
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_LEFT_NOTIFY);
	_f_f uint32_t hallId;
	_f_f uint64_t userId;
};

// 旁观私聊发送
typedef STRU_UC_CL_CRS_DATA_ID_350 tagWatchPrivateChatReq;

// 服务器通知旁观私聊验证码
// 该包格式与普通验证码通知格式相同

// 旁观私聊接收方
// 旁观私聊时目标用户收到的包格式如下
#define UC_CL_CRS_WATCH_USER_PRIVATE_CHAT
struct tagCrsWatchPrivateChatDest
{
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_PRIVATE_CHAT);	
	_f_f Dp::String<1024> message;
};

// 发送虚拟物请求
// 旁观发送虚拟物请求包格式与普通发送虚拟物格式相同
typedef STRU_UC_CL_CRS_USE_PROPS_RQ tagCrsWatchUserPropsReq;

// 虚拟物处理回应

#include "BigRoom.inl";
#endif

