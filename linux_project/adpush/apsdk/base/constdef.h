#ifndef _CONST_DEF_H_
#define _CONST_DEF_H_

#include <stdint.h>

//=======================================公共常量=========================================================

//1.0Beta:							2.01.000
//1.0Release:						2.01.190
//1.1:								2.05.190
//1.1.1:							2.06.190
//1.2:								2.08.190
//1.2.1								2.09.190
//1.3:                              2.12.190
//1.3正式版:                        2.13.190
//蝴蝶版                            2.15.190
//1.3SP1：                          2.16.190
//蝴蝶版1.2.1：                     2.17.190
const char SINA_SHOW_VERSION[]	 = "2.27.190";		//版本号
const uint8_t SINA_SHOW_MPS_VERSION = 1;   //Show对应MPS的版本号，客户端版本号每升一次，
										   //对应MPS版本号值应加1，并同步到对应MPS的版本文件中。
										   //取值范围：SINA_SHOW_MPS_VERSION = (0~254),共支持255个线上版本。
#define WHOLE_PACK_DATA_LEN   1024*6
#define ROOM_PACK_DATA_LEN	  10240	

const uint8_t LOGIN_RESULT_OK              = 0;
const uint8_t LOGIN_RESULT_ERROR           = 1;
const uint8_t LOGIN_RESULT_FORBID          = 2;
const uint8_t LOGIN_RESULT_MEMBERROOMFULL  = 3;
const uint8_t LOGIN_RESULT_MEMBERFULL      = 4;
const uint8_t LOGIN_CHG_ROOM				= 5;//切换房间

#define DEF_MAX_ACTION_DESCRIPTION_LEN	 	512     //活动描述最大长度


//用户信息状态类别
const uint8_t	CONST_USER_STATUS_HIDDE			=	0;//隐藏
const uint8_t	CONST_USER_STATUS_REFUSECHAT	=	1;//拒绝接收消息
const uint8_t	CONST_USER_STATUS_ATTENTION		=	2;//关注此用户
const uint8_t	CONST_USER_STATUS_FORBIDTALK	=	3;//禁止发言
const uint8_t	CONST_USER_STATUS_HAVEVIDEO		=	4;//是否有视频
const uint8_t	CONST_USER_STATUS_SENDVOICE		=	5;//是否发送语音
const uint8_t	CONST_USER_STATUS_RECVVOICE		=	6;//是否接收语音
const uint8_t	CONST_USER_STATUS_SENDVIDEO		=	7;//是否发送视频
const uint8_t	CONST_USER_STATUS_RECVVIDEO		=	8;//是否接收视频
const uint8_t	CONST_USER_STATUS_RECORD		=	9;//是否允许录音
const uint8_t	CONST_USER_STATUS_KINESCOPE		=	10;//是否允许录像
const uint8_t	CONST_USER_STATUS_PUBCHAT		=	11;//是否允许公聊
const uint8_t	CONST_USER_STATUS_PRIVATECHAT	=	12;//是否允许私聊
const uint8_t	CONST_USER_STATUS_FLOWER		=	13;//是否允许鲜花

const uint16_t DEF_USE_IE_PROXY_SET		= 0;	//使用IE代理设置
const uint16_t DEF_CONNECTION_DIRECT	= 1;	//拔号或直连
const uint16_t DEF_CONNECTION_NAT		= 2;	//局域网无代理
const uint16_t DEF_USE_SOCKS_PROXY		= 3;	//使用SOCKS代理
const uint16_t DEF_USE_HTTP_PROXY		= 4;	//使用HTTP代理

const uint16_t IP_ADDR_STR_LEN			= 15;	//IP长度
const uint16_t PROXY_NAME_LEN			= 15;	//代理用户名长度
const uint16_t PROXY_PASSWORD_LEN		= 15;	//代理密码长度

//用户信息
const uint16_t NICK_NAME_LEN			= 20;	//用户名称长度
const uint16_t USER_CUSTOMEMOTION_LEN	= 400; //最多100个中文字
const uint16_t USER_NAME_LEN			= 30;	//本地用户名称长度
const uint16_t USER_ID_LEN				= 20;	//用户ID长度
const uint16_t USER_PWD_LEN				= 16;	//用户密码长度

const uint16_t GROUP_NAME_LEN			= 40;
const uint16_t USER_EMOTION_LEN			= 20;  //用户表情长度
const uint16_t COMMUNITY_NAME_LEN		= 200;

const uint16_t HALL_NAME_LEN			= 30;	//房间名称长度
const uint16_t CHATROOM_TYPE_NAME_LEN	= 30;	//类型名称长度
const uint16_t ACT_NAME_LEN				= 30;	//节目名称长度
const uint16_t	DATA_LEN				= 2048;
const uint16_t	FILE_NAME_LEN			= 256;	//文件名长度
const uint16_t	SYNOPSIS_LEN			= 256;	//简介长度

const uint16_t FIND_NAME_LEN			= 14;	//查找聊天室关键字长度


const uint16_t NODE_TYPE_CRTYPE_ID_ROOT				= 0;		//顶级

const uint16_t NODE_TYPE_CRTYPE_TYPE_OFFICIAL		= 1;		//官方
const uint16_t NODE_TYPE_CRTYPE_TYPE_COOPERATE		= 2;		//合作

const uint16_t NODE_TYPE_CRTYPE_CHILD_TYPE_ROOM		= 0;		//子节点为聊天室
const uint16_t NODE_TYPE_CRTYPE_CHILD_TYPE_AREA	    = 1;		//区


const uint16_t MD5_LEN						= 32;		// MD5密文长度

#define CHATROOM_BMP_NAME_LEN		50
//----------------------------------------------------------------------
#define	CHG_TYPE_DELETE				2		//麦属性信息序列化

//MsgModule
#define UC_CHATROOM_TOPIC_LEN					512					//主题的长度
#define UC_CHATROOM_SALUTATORY_LEN				512					//欢迎词的长度
#define UC_HALL_PWD_LEN			128					//聊天室密码长度
#define REASON_LEN					500		// 操作原因长度
#define CHATROOM_IMV_NAME_LEN		20		//聊天室场景名称长度
#define DEF_TC_CONTENT_LEN_380      1024	//文本聊天增容包内容长度
#define CRS_DATA_LEN				1024	//聊天室数据长度
#define INFO_LEN					512		//一般信息长度
#define SONG_NAME_LEN				40		//参赛歌曲名字长度
#define	ERR_BUF_LEN					256		//登录错误
#define HOMEPAGE_DISPLAY_LEN		40		//地址链接长度
#define URL_LINK_LEN				100		//地址链接长度
#define DEF_USER_MOOD_LENGTH	    40		//用户心情长度
#define DEF_USER_UNINAME_LEN		60		//统一会员名称长度
#define DEF_USER_BIRTHDAY_LEN   15  //用户生日 
#endif //_CONST_DEF_H_



