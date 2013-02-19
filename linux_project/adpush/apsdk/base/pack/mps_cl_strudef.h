#ifndef mps_cl_strudef_h__
#define mps_cl_strudef_h__

#include "../include.h"
#define DEF_PROPSMPS_SRVID_DEFAULT  3
#define DEF_PROPSMPS_SRVID_ANDROID  25
#define DEF_PROPSMPS_SRVID_IOS      26

#define PRIVATE_ATTR_SIZE	16

#if defined (__linux__)
#if defined (__ANDROID__)
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_ANDROID
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif
#elif defined (__APPLE__)
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_IOS
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif
#elif defined (_MSC_VER)
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif


// 消息类型
typedef enum
{
	// 客户登录服务器的请求消息
	LOGIN_REQ               =       0x0001,

	// 服务器下发给客户端的消息请求
	PUSH_MSG_REQ            =       0x0002,
#if IS_SRV_MODE // 客户端不需要
	// 后台推送消息请求
	DISPATCH_MSG_REQ        =       0x0003,
#endif

	// 客户登录服务器的应答消息
	LOGIN_ACK               =       0x8001,

	// 服务器下发给客户端的消息应答
	PUSH_MSG_ACK            =       0x8002,

#if IS_SRV_MODE // 客户端不需要
	// 后台推送消息应答
	DISPATCH_MSG_ACK        =       0x8003,
#endif

	// 接入端到用户管理端注册/注销客户信息
	USER_CTL                =       0x5001
} MPS_MSG_TYPE;

// 登录应答包返回码
typedef enum
{
	// 操作成功
	LOGIN_SUCCESS           =       0,
	// 登录时的需要重定向到新的服务器
	LOGIN_REDIRECT          =       1,
	// 登录请求参数非法或者不支持
	LOGIN_UNALLOW           =       2,
	// 系统繁忙或者系统错误
	LOGIN_SYSERROR          =       3,
	// 其他错误
	LOGIN_UNKNOWN           =       4
} LOGIN_RET_VALUE;


struct STRU_CL_TCP_MPS_PKG_BASE
{
	// 消息类型
	uint16_t     u16MsgType;
	// 消息流水号
	uint32_t     u32Seq;
	// 消息发送时间戳
	uint32_t       u32Timestamp;

	int Pack(char* apBuffer, int alLen);
	int UnPack(char* apBuffer, int alLen);
	STRU_CL_TCP_MPS_PKG_BASE();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_LOGIN_RQ:public STRU_CL_TCP_MPS_PKG_BASE
{
	// 用户Id
	uint64_t       u64UsrId;
	// 业务Id
	uint16_t       u16SvcId;
	// 通用属性
	uint32_t       u32CommAttr;
	// 业务私有属性
	char         chPrivateAttr[PRIVATE_ATTR_SIZE];

	STRU_CL_TCP_MPS_PKG_LOGIN_RQ();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_LOGIN_ACK:public STRU_CL_TCP_MPS_PKG_BASE
{
	// 返回的请求处理结果代码，0-成功，other-失败代码
	uint16_t       u16RetCode;
	// 返回消息的内容编码
	uint8_t       u8ErrMsgEncoding;
	// 错误消息内容长度
	uint16_t       u16ErrMsgLen;
	// 错误消息内容
	char*         szErrMsg;

	STRU_CL_TCP_MPS_PKG_LOGIN_ACK();
	~STRU_CL_TCP_MPS_PKG_LOGIN_ACK();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_PUSH_MSG:public STRU_CL_TCP_MPS_PKG_BASE
{
	// 推送消息编码类型
	uint8_t        u8MsgEncoding;
	// 推送消息长度
	uint16_t       u16MsgLen;
	// 推送消息内容
	char*         szMsg;

	STRU_CL_TCP_MPS_PKG_PUSH_MSG();
	~STRU_CL_TCP_MPS_PKG_PUSH_MSG();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

#endif // mps_cl_strudef_h__