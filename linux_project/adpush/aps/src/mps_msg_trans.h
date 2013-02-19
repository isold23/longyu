/*! @file mps_msg_trans.h
 * *****************************************************************************
 * @n</PRE>
 * @n模块名       : mps_msg_trans相关宏以及结构体申明
 * @n文件名       : mps_msg_trans.h
 * @n相关文件     : mps_msg_trans.cpp
 * @n文件实现功能 : 申明一些相关宏以及结构体
 * @n作者         : huangjun - 新浪技术(中国)
 * @n版本         : 1.0.1
 * @n---------------------------------------------------------------------------
 * @n备注:
 * @n---------------------------------------------------------------------------
 * @n修改记录:
 * @n日期        版本        修改人      修改内容
 * @n20081202    1.0.0       huangjun    Created
 * @n</PRE>
 ******************************************************************************/
#ifndef __MPS_SRV_H__
#define __MPS_SRV_H__

#include <dirent.h>

// 连接状态
typedef enum
{
    NOT_USED    =   0,
    LISTENER    =   1,
    ACCEPTED    =   2
} SOCK_STATUS;

// 针对特定IP跟踪输出, 适用于大容量用户访问的运营环境跟踪debug
#define TRACE_IP               "127.0.0.1"

// 默认本地内网IP
#define DEFAULT_LOCAL_IP       "127.0.0.1"

// 每个进程最大支持的套结字句柄大小
#define DEFAULT_MAX_SOCKET_NUM 5000

// 推送消息数据报最大大小
#define MAX_PUSH_PKG_LEN       8192

// 接收缓冲区最大大小
#define MAX_RECV_BUF_SIZE      MAX_PUSH_PKG_LEN
// 发送缓冲区最大大小
#define MAX_SEND_BUF_SIZE      MAX_PUSH_PKG_LEN

// 默认的服务监听Tcp端口
#define DEFAULT_SERVER_PORT    6000
// 默认的服务监听内网消息的Udp端口
#define DEFAULT_UDP_PORT       18000

// 默认的pid文件存放目录
#define DEFAULT_PID_FILE       "/home/mps_srv/var/mps_msg_trans.pid"

// 默认的日志文件存放路径名
#define DEFAULT_LOG_FILE       "/home/mps_srv/logs/mps_msg_trans"
// 默认日志单个文件最大大小
#define MAX_LOG_SIZE           10000000
// 默认日志文件最大递增个数
#define MAX_LOG_NUM            10

// 默认tcp连接超时值, 以秒为单位
#define DEFAULT_CONN_TIMEOUT   90

// 默认服务启动时fork的进程数
#define DEFAULT_PROCESS_NUM    2

#define RESERVE_OTHER_SOCKET_NUM 20    // 为进程打开的其他文件句柄保留的个数

// 默认最大支持业务数
#define DEFAULT_MAX_SERVICE_NUM        1024

// 当前可以支持的最大服务器数
#define MAX_SRV_NUM            500

typedef struct
{
    size_t uServerId;                   // 用以在多台同域名不同Server间来标识自己

    char szLocalIp[16];                 // 本地内网IP地址
    unsigned short usServerPort;        // 服务进程所监听的Tcp端口
    size_t uProcessNum;                 // 服务启动时fork的进程数
    char szPidFilePath[MAXNAMLEN];      // PID文件存放路径

    size_t uMaxSocketNum;               // 每个进程可以处理的最大套接字句柄值
    size_t uCurSocketNum;               // 本进程当前已经接受的句柄数

    long lConnTimeout;                  // 每个连接中生存的超时时间, 超时直接断开

    size_t uMaxServiceNum;              // 每个进程可以支持的最大业务数

    char szLogFilePath[MAXNAMLEN - 32]; // 日志文件的路径名
    long lMaxLogSize;                   // 单个日志文件的最大大小
    int  nMaxLogNum;                    // 日志文件的最大递增个数
} STRU_CONFIG;

typedef struct
{
#ifdef TRACE_IP
    bool bTrace;                        // 标识是否对当前连接进行跟踪
#endif

    int nPrevIndex;                     // 连接对列的前向索引
    int nNextIndex;                     // 连接队列的后向索引

    int  nSocketType;                   // Socket连接状态
    time_t tm_LoginTime;                // 此连接登录的时间
    time_t tm_LastActive;               // 此连接最近活动时间

    unsigned long lClientIP;            // 客户端IP
    unsigned short usClientPort;        // 客户端连接的端口号
    // char sClientAddr[30];            // 连接上的字符串格式的客户端地址

    long lPkgLen;                       // 用户请求包长度

    long lRecvBytes;                    // 当前已经接收到的字节数
    char szRecvBuffer[MAX_RECV_BUF_SIZE]; // 接受缓冲区

    long lToSendBytes;                  // 发送缓冲区需要发送的总字节数
    char szSendBuffer[MAX_SEND_BUF_SIZE]; // 发送数据缓冲区
} STRU_SOCKET_CONTEXT;

#endif
