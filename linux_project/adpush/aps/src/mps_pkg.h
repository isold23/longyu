#ifndef __MPS_PKG_H__
#define __MPS_PKG_H__

#include <sys/types.h>

#define STX 0x03
#define ETX 0x07

typedef u_int8_t  UINT8;
typedef u_int16_t UINT16;
typedef u_int32_t UINT32;
typedef u_int64_t UINT64;

// 用户私有属性所占字节长度
#define PRIVATE_ATTR_SIZE 16

// 消息内容编码
typedef enum
{
    CHARSET_UTF8    = 0,
    CHARSET_GB2312  = 1,
    CHARSET_GBK     = 2
} ENUM_ENCODING_TYPE;

// 消息类型
typedef enum
{
    // 客户登录服务器的请求消息
    LOGIN_REQ               =       0x0001,

    // 服务器下发给客户端的消息请求
    PUSH_MSG_REQ            =       0x0002,

    // 后台推送消息请求
    DISPATCH_MSG_REQ        =       0x0003,

    // 客户登录服务器的应答消息
    LOGIN_ACK               =       0x8001,

    // 服务器下发给客户端的消息应答
    PUSH_MSG_ACK            =       0x8002,

    // 后台推送消息应答
    DISPATCH_MSG_ACK        =       0x8003,

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

// 推送消息应答包返回码
typedef enum
{
    // 推送成功
    PUSH_SUCCESS            =       0,
    // 数据包非法
    PUSH_ILLEGAL            =       1,
    // 推送参数非法或者不支持
    PUSH_UNALLOW            =       2,
    // 其他错误
    PUSH_UNKNOWN            =       3
} PUSH_MSG_RET_VALUE;

#pragma pack(1)

// 推送系统相关消息包报头结构
typedef struct
{
    // 数据报总长度，包括起始标志、报头、报体总长度
    UINT16      u16PkgLen;
    // 版本号，首次为0100
    UINT16      u16Verion;
    // 消息类型
    UINT16      u16MsgType;
    // 消息流水号
    UINT32      u32Seq;
    // 消息发送时间戳
    UINT32      u32Timestamp;
} STRU_MSGPUSH_PKG_HEAD;

// 推送系统相关消息包结构
typedef struct
{
    // 起始标志
    UINT8       u8Stx;
    // 报头
    STRU_MSGPUSH_PKG_HEAD stHead;
    // 报体，变长
    char        szBody[0];
    // 结束标志
    UINT8       u8Etx;
} STRU_MSGPUSH_PKG;

// 客户端登录接入服务器的请求报体信息，存放在上述消息报报体中
typedef struct
{
    // 用户Id
    UINT64      u64UsrId;
    // 业务Id
    UINT16      u16SvcId;
    // 通用属性
    UINT32      u32CommAttr;
    // 业务私有属性
    char        chPrivateAttr[PRIVATE_ATTR_SIZE];
} STRU_REG_MSG;

// 接入服务器上报客户信息结构体，存放在上述消息报报体中
typedef struct
{
    // 用户Id
    UINT64      u64UsrId;
    // 业务Id
    UINT16      u16SvcId;
    // 操作码，目前最低位做增删用户之用，0-删除、1-增加
    UINT16      u16CtlMask;
} STRU_RPT_USRINFO;

// 推送消息报体结构，存放在上述消息报报体中
typedef struct
{
    //////////////////////////////////////////////////////////////////////////
    // begin of 后台推送过滤头信息，不下发到客户端
    // 用户Id，如果不指定具体用户则置为0
    UINT64      u64UsrId;
    // 业务Id，如果全员推送，不指定业务，则置为0
    UINT16      u16SvcId;
    // 通用属性，采用置相应位为1进行过滤
    UINT32      u32CommAttr;
    // 业务私有属性，采用置相应位为1进行过滤
    char        chPrivateAttr[PRIVATE_ATTR_SIZE];
    // end of 后台推送过滤头信息，不下发到客户端
    //////////////////////////////////////////////////////////////////////////

    // 推送消息编码类型
    UINT8       u8MsgEncoding;
    // 推送消息长度
    UINT16      u16MsgLen;
    // 推送消息内容
    char        szMsg[0];
} STRU_PUSH_MSG;

// 应答报体结构，存放在应答报报体中
typedef struct
{
    // 返回的请求车处理结果代码，0-成功，other-失败代码
    UINT16      u16RetCode;
    // 返回消息的内容编码
    UINT8       u8ErrMsgEncoding;
    // 错误消息内容长度
    UINT16      u16ErrMsgLen;
    // 错误消息内容
    char        szErrMsg[0];
} STRU_ACK_MSG;

#pragma pack()

#endif
