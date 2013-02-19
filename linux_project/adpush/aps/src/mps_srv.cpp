/*! @file mps_srv.cpp
 * *****************************************************************************
 * @n</PRE>
 * @n模块名       : mps_srv主网络程序架构实现
 * @n文件名       : mps_srv.cpp
 * @n相关文件     : mps_srv.h
 * @n文件实现功能 : 实现Msg push服务
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
#include <arpa/inet.h>
#include <fcntl.h>
#include <fstream>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <new>

// #include "hj_log.h"
#include "hj_cfg.h"
#include "hj_misc.h"
#include "hj_net.h"
#include "hj_rpt_api.h"
#include "hj_hexshow.h"
#include "hj_mempool.h"
// #include "hj_hash_map.h"

#undef  DEBUG_LEVEL
#define DEBUG_LEVEL (LM_DEBUG|LM_TRACE|LM_INFO|LM_ERROR|LM_EXCEPT)
#include "hj_debug_print.h"

#include "mps_srv.h"
#include "mps_pkg.h"
#include "mps_util.h"

#if USE_LOAD_BALANCE
const char szSrvAddrs[][16] = {"123.103.66.50", "123.103.66.51", "123.103.66.52"};
#endif

// 全局变量定义
// CHJ_Log         g_sh_log;
STRU_CONFIG          g_stConfig;

// 用户信息内存池
CHJMemPool g_UsrInfoMempool;

typedef struct
{
    // 当前进程的次序ID
    size_t uProcessId;
    // 当前进程监听内网消息的udp socket句柄
    int    nUdpSocket;

    // 当前每个进程最大支持的套结字句柄大小
    size_t uMaxSocketNum;

    // epoll句柄
    int    nEpfd;
    struct epoll_event *pEvents;

    int    nConn_Queue_Root;

    STRU_SOCKET_CONTEXT *pSocketContext;
    // 监听的Socket
    int    nListen_Socket;
    bool   bListen_Epoll_Added;

    // 按业务分放的用户信息数组
    // 当前支持的最大业务数
    size_t uMaxServiceNum;
    struct HJ_RB_root *pstUserListRoot;
#ifdef TRACE_USER
    // 当前在线用户数
    size_t uOnlineUserNum;
    // 当前登录用户数
    size_t uLoginUserNum;
#endif
} STRU_RUNTIME;

STRU_RUNTIME g_stRuntime = {0, -1, 0, -1, NULL, -1, NULL, -1, false, 0, NULL
#ifdef TRACE_USER
, 0, 0
#endif
};

using namespace std;

/*!
 * 功能: 复位指定socket的连接状态信息
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int ResetSocketContext(STRU_SOCKET_CONTEXT &stSocketContext)
{
    HJ_xchg(&stSocketContext.lSendLock, 0);
    stSocketContext.tm_LoginTime = stSocketContext.tm_LastActive = time(NULL);
    stSocketContext.bCloseOnSendAll = false;
    stSocketContext.lPkgLen = 0;
    stSocketContext.pUserinfo = NULL;
    stSocketContext.lRecvBytes = 0;
    stSocketContext.lToSendBytes = 0;

    return 0;
}

/*!
 * 功能: 关闭指定socket的连接
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int CloseSocket(int nSocket)
{
    assert((nSocket >= 0) && (nSocket < (int)g_stRuntime.uMaxSocketNum)
        && g_stRuntime.pSocketContext && (ACCEPTED == g_stRuntime.pSocketContext[nSocket].nSocketType));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];

#ifdef TRACE_IP
    if (stSocketContext.bTrace)
    {
        // DEBUG_PRINT(LM_INFO, "nSocket: %d\n", nSocket);
    }
#endif

    // 从连接队列里删除当前的Socket上下文
    conn_rmv_list(nSocket, g_stRuntime.pSocketContext, g_stRuntime.nConn_Queue_Root);

    // 移除epoll事件监听
    if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, nSocket) < 0)
    {
        DEBUG_PRINT(LM_ERROR, "Call HJ_unregister_epoll_event() failed\n");
    }

    //////////////////////////////////////////////////////////////////////////
    // 清理与此连接相关的用户信息
    if (stSocketContext.pUserinfo)
    {
        STRU_USERINFO_ACS *pUserinfoTmp = Remove_Userinfo(&g_stRuntime.pstUserListRoot[stSocketContext.pUserinfo->u16SvcId]
            , stSocketContext.pUserinfo->u64UsrId, (unsigned short)nSocket);
        if (pUserinfoTmp != stSocketContext.pUserinfo)
        {
            assert(pUserinfoTmp->usCommSocket < (unsigned short)g_stRuntime.uMaxSocketNum);
            g_stRuntime.pSocketContext[stSocketContext.pUserinfo->usCommSocket].pUserinfo = stSocketContext.pUserinfo;
            DEBUG_PRINT(LM_INFO, "！！！由于同用户多次登录，所以移除节点与会话保存的节点不一致！\n");
        }

        g_UsrInfoMempool.Free(pUserinfoTmp);
        stSocketContext.pUserinfo = NULL;
#ifdef TRACE_USER
        g_stRuntime.uLoginUserNum--;
#endif
    }
    //////////////////////////////////////////////////////////////////////////

    close(nSocket);
    stSocketContext.nSocketType = NOT_USED;
    HJ_xchg(&stSocketContext.lSendLock, 0);

    g_stConfig.uCurSocketNum--;
#ifdef TRACE_USER
    g_stRuntime.uOnlineUserNum--;
#endif

    if (!g_stRuntime.bListen_Epoll_Added)
    {
        if (HJ_register_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket, EPOLLIN | EPOLLET) == 0)
        {
            g_stRuntime.bListen_Epoll_Added = true;
        }
    }

    return -1;
}

/*!
 * 功能: 检查所有的Socket事件
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int CheckConnStatus(void)
{
    int iRet = epoll_wait(g_stRuntime.nEpfd, g_stRuntime.pEvents, (int)g_stRuntime.uMaxSocketNum, -1);
    if (iRet > 0)
    {
        return iRet;
    }
    else
    {
        return -1;
    }
}

/*!
* 功能: 检查并接受客户端的Socket连接
* @n作者: huangjun
* @n日期: 2008-12-02
*/
int CheckAndAcceptConns(int nListenSocket)
{
    // DEBUG_PRINT(LM_INFO, "Enter...\n");

    struct sockaddr_in stSockAddr;
    int nNewSocket = 0;
    socklen_t uSockAddrLen;
#if 0
    char *pClientIP = NULL;
#endif
    const size_t uMaxAcptSocketNum = g_stRuntime.uMaxSocketNum - RESERVE_OTHER_SOCKET_NUM;
    size_t &uCurSocketNum = g_stConfig.uCurSocketNum;

    while (true)
    {
        // 如果本进程网络连接已经接收满了, 则保留让给其他进程去接收连接
        if (uCurSocketNum >= uMaxAcptSocketNum)
        {
            // DEBUG_PRINT(LM_EXCEPT, "！！！uCurSocketNum(%u)>=uMaxAcptSocketNum(%u)\n"
            //     , uCurSocketNum, uMaxAcptSocketNum);
            if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, nListenSocket) >= 0)
            {
                g_stRuntime.bListen_Epoll_Added = false;
            }
            return -1;
        }

        uSockAddrLen = sizeof(stSockAddr);
        nNewSocket = accept(nListenSocket, (struct sockaddr *)&stSockAddr
            , (socklen_t*)&uSockAddrLen);
        // DEBUG_PRINT(LM_DEBUG, "After accept, iNewSocket:%d\n", iNewSocket);
        if (nNewSocket < 0)
        {
            // if ((errno == EAGAIN) || (errno == EINTR))
            // {
            //     DEBUG_PRINT(LM_DEBUG, "In NOBLOCK mode, Command can't complete immediately\n");
            // }
            break;
        }

        if (nNewSocket >= (int)g_stRuntime.uMaxSocketNum)
        {
            DEBUG_PRINT(LM_EXCEPT, "！！！nNewSocket(%d)>=g_stRuntime.uMaxSocketNum(%Zu)\n"
                , nNewSocket, g_stRuntime.uMaxSocketNum);
            close(nNewSocket);
            break;
        }

#if 0
        // unsigned long ulClientIP = stSockAddr.sin_addr.s_addr;
        pClientIP = inet_ntoa(*(struct in_addr*)&stSockAddr.sin_addr);
        if (pClientIP == NULL)
        {
            DEBUG_PRINT(LM_ERROR, "Call inet_ntoa() failed\n");
            close(nNewSocket);
            break;
        }
#endif

        HJ_SetNoBlock(nNewSocket);
        HJ_SetTcpSockKeepAlive(nNewSocket, 1, 120, 20, 3);
        // HJ_SetTcpSockKeepAlive(nNewSocket, 1, 0, 0, 0);
        // int nKeepAlive = 1;
        // setsockopt(nNewSocket, SOL_SOCKET, SO_KEEPALIVE, (void*)&nKeepAlive, sizeof(nKeepAlive));

        if (HJ_register_epoll_event(g_stRuntime.nEpfd, nNewSocket, EPOLLIN | EPOLLET) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Call HJ_register_epoll_event() for adding the new connect socket failed\n");
            close(nNewSocket);
            continue;
        }

#ifdef TRACE_IP
        if (true) // (strcmp(TRACE_IP, pClientIP) == 0)
        {
            g_stRuntime.pSocketContext[nNewSocket].bTrace = true;
            // DEBUG_PRINT(LM_INFO, "Accept a new connection!\n");
        }
        else
        {
            g_stRuntime.pSocketContext[nNewSocket].bTrace = false;
        }
#endif

        // 初始化客户连接信息
        g_stRuntime.pSocketContext[nNewSocket].nPrevIndex   = g_stRuntime.pSocketContext[nNewSocket].nNextIndex = -1;
        g_stRuntime.pSocketContext[nNewSocket].nSocketType  = ACCEPTED;
        g_stRuntime.pSocketContext[nNewSocket].lClientIP    = stSockAddr.sin_addr.s_addr;
        g_stRuntime.pSocketContext[nNewSocket].usClientPort = ntohs(stSockAddr.sin_port);
#if 0
        snprintf(g_stRuntime.pSocketContext[nNewSocket].sClientAddr
            , sizeof(g_stRuntime.pSocketContext[nNewSocket].sClientAddr), "%s", pClientIP);
#endif

        ResetSocketContext(g_stRuntime.pSocketContext[nNewSocket]);
#ifdef TRACE_USER
        g_stRuntime.uOnlineUserNum++;
#endif

        // 将新连接的Socket加入到连接队列
        conn_add_list(nNewSocket, g_stRuntime.pSocketContext, g_stRuntime.nConn_Queue_Root);

        uCurSocketNum++;
    } // end while (true)

    return 0;
}

/*!
 * 功能: 发送数据包
 * 参数: nSocket为要发送数据的socket, pPkg指向数据包, uPkgLen为数据长度(不能超过MAX_SEND_BUF_SIZE个字节)
 *       bCloseOnSendAll-是否在发送完数据后就进行关闭
 * 返回: 0 - 成功; <0 - 失败, >0-本次发送失败
 */
int SendPkg(int nSocket, const char *pPkg, size_t uPkgLen, bool bCloseOnSendAll = false)
{
    assert(g_stRuntime.pSocketContext && (nSocket >= 0)
        && ((size_t)nSocket < g_stRuntime.uMaxSocketNum) && pPkg);
    assert(uPkgLen != 0);

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];
    CAutoLock AutoLock(&stSocketContext.lSendLock);
    if (ACCEPTED != stSocketContext.nSocketType)
    {
        DEBUG_PRINT(LM_ERROR, "uPkgLen(%Zu) - nSocketType(%d)\n"
            , uPkgLen, stSocketContext.nSocketType);
        return -1;
    }

    if (bCloseOnSendAll)
    {
        stSocketContext.bCloseOnSendAll = bCloseOnSendAll;
    }
    if (stSocketContext.lToSendBytes > 0)
    {
        if ((stSocketContext.lToSendBytes + uPkgLen) > sizeof(stSocketContext.szSendBuffer))
        {
            DEBUG_PRINT(LM_ERROR, "发送缓冲区已满，发送失败！\n");
            return 1;
        }
        // DEBUG_PRINT(LM_DEBUG, "填充进发送缓冲区!\n");
        memcpy(stSocketContext.szSendBuffer + stSocketContext.lToSendBytes, pPkg, uPkgLen);
        stSocketContext.lToSendBytes += uPkgLen;

        return 0;
    }

    int nBytesSent = send(nSocket, pPkg, uPkgLen, 0);
    // DEBUG_PRINT(LM_DEBUG, "Call send: %d\n", nBytesSent);
    stSocketContext.tm_LastActive = time(NULL);
    if (nBytesSent <= 0)
    {
        if ((nBytesSent < 0) && ((EAGAIN == errno) || (EINTR == errno)))
        {
            nBytesSent = 0; // 下一轮循环将继续发送
        }
        else
        {
            return -3;
        }
    }

    if (nBytesSent >= (int)uPkgLen)
    {
        if (stSocketContext.bCloseOnSendAll)
        {
            return -4;
        }
        return 0;
    }

    if (0 != HJ_modify_epoll_event(g_stRuntime.nEpfd, nSocket, EPOLLIN | EPOLLOUT | EPOLLET))
    {
        return -5;
    }

    stSocketContext.lToSendBytes = uPkgLen - nBytesSent;
    memcpy(stSocketContext.szSendBuffer, (char*)pPkg + nBytesSent, stSocketContext.lToSendBytes);

    return 0;
}

/*!
 * 功能: 解析请求报头, 获取包总长度
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int HandlePkgHead(STRU_SOCKET_CONTEXT &stSocketContext, size_t &uPkgLen)
{
#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    uPkgLen = 0;

    const long &lRecvBytes = stSocketContext.lRecvBytes;
    if (lRecvBytes < long(sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD)))
    {
        return 1;
    }

    if (stSocketContext.szRecvBuffer[0] != STX)
    {
        return -1;
    }

    STRU_MSGPUSH_PKG_HEAD *pstMsgpushPkgHead
        = (STRU_MSGPUSH_PKG_HEAD*)(stSocketContext.szRecvBuffer + sizeof(UINT8));

    UINT16 u16MsgType = ntohs(pstMsgpushPkgHead->u16MsgType);
    if (u16MsgType != LOGIN_REQ)
    {
        DEBUG_PRINT(LM_ERROR, "业务类型不正确(%u)！\n", u16MsgType);
        return -2;
    }

    uPkgLen = ntohs(pstMsgpushPkgHead->u16PkgLen);
    if (uPkgLen != (2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + sizeof(STRU_REG_MSG)))
    {
        return -3;
    }

    return 0;
}

/*!
 * 功能: 处理客户端的提交请求
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int HandlePkg(int nSocket, STRU_SOCKET_CONTEXT &stSocketContext)
{
    // DEBUG_PRINT(LM_INFO, "Enter...\n");
#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    // HJ_hex_show(stSocketContext.szRecvBuffer, stSocketContext.lPkgLen);

    if (stSocketContext.szRecvBuffer[stSocketContext.lPkgLen - 1] != ETX)
    {
        DEBUG_PRINT(LM_ERROR, "数据结尾标识非法！\n");
        return -1;
    }
    stSocketContext.szRecvBuffer[stSocketContext.lPkgLen - 1] = '\0';

    STRU_MSGPUSH_PKG *pstMsgpush_Pkg = (STRU_MSGPUSH_PKG*)stSocketContext.szRecvBuffer;

    //////////////////////////////////////////////////////////////////////////
    STRU_REG_MSG *pstRegMsg = (STRU_REG_MSG*)pstMsgpush_Pkg->szBody;
    pstRegMsg->u64UsrId = ntohq(pstRegMsg->u64UsrId);
    pstRegMsg->u16SvcId = ntohs(pstRegMsg->u16SvcId);
    pstRegMsg->u32CommAttr = ntohl(pstRegMsg->u32CommAttr);

#if USE_LOAD_BALANCE
    // 增加按用户ID分配服务器
    size_t uServerId = pstRegMsg->u64UsrId % (sizeof(szSrvAddrs) / sizeof(szSrvAddrs[0]));
#endif

#ifdef TRACE_USER
    bool bLogined = !!(stSocketContext.pUserinfo);
#endif

    int nRetCode = 0;
    do
    {
        if (pstRegMsg->u16SvcId >= g_stRuntime.uMaxServiceNum)
        {
            DEBUG_PRINT(LM_ERROR, "u16SvcId(%u) above g_stRuntime.uMaxServiceNum(%Zu)!\n"
                , pstRegMsg->u16SvcId, g_stRuntime.uMaxServiceNum);
            nRetCode = -1;
            break;
        }

        // DEBUG_PRINT(LM_DEBUG, "%ld - %u - %u\n", pstRegMsg->u64UsrId
        //     , pstRegMsg->u16SvcId, pstRegMsg->u32CommAttr);

        //////////////////////////////////////////////////////////////////////////
#if USE_LOAD_BALANCE
        // 增加按用户ID分配服务器
        if (uServerId != g_stConfig.uServerId)
        {
            nRetCode = -2;
            break;
        }
#endif
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        bool bUpdateUserinfo = false;
        STRU_USERINFO_ACS* &pUserinfo = stSocketContext.pUserinfo;
        if (pUserinfo)
        {
            DEBUG_PRINT(LM_EXCEPT, "重复登录！\n");
            if ((pUserinfo->u64UsrId == pstRegMsg->u64UsrId)
                && (pUserinfo->u16SvcId == pstRegMsg->u16SvcId))
            {
                pUserinfo->u32CommAttr = pstRegMsg->u32CommAttr;
                memcpy(pUserinfo->chPrivateAttr, pstRegMsg->chPrivateAttr
                    , sizeof(pUserinfo->chPrivateAttr));
                bUpdateUserinfo = true;
            }
            else
            {
                // 从RB树中移除以前插入位置，但不释放节点，重用节点以便避免节点频繁分配
                STRU_USERINFO_ACS *pUserinfoTmp = Remove_Userinfo(&g_stRuntime.pstUserListRoot[pUserinfo->u16SvcId]
                    , pUserinfo->u64UsrId, (unsigned short)nSocket);
                if (pUserinfoTmp != pUserinfo)
                {
                    DEBUG_PRINT(LM_EXCEPT, "！！！删除的用户信息节点和当前会话保存的不一致！\n");
                    pUserinfo = pUserinfoTmp;
                }
            }
        }
        //////////////////////////////////////////////////////////////////////////

        if (!bUpdateUserinfo)
        {
            if (!pUserinfo)
            {
                // 创建用户信息
                pUserinfo = (STRU_USERINFO_ACS*)g_UsrInfoMempool.Alloc();
                if (!pUserinfo)
                {
                    DEBUG_PRINT(LM_ERROR, "g_UsrInfoMempool.Alloc for %" PRIu64 " failed!\n"
                        , pstRegMsg->u64UsrId);
                    nRetCode = -3;
                    break;
                }
            }

            //////////////////////////////////////////////////////////////////////////
            // 初始化用户信息，切记各个变量都要初始化
            bzero(&pUserinfo->rbNode, sizeof(pUserinfo->rbNode));
            pUserinfo->u64UsrId = pstRegMsg->u64UsrId;
            pUserinfo->u16SvcId = pstRegMsg->u16SvcId;
            pUserinfo->u32CommAttr = pstRegMsg->u32CommAttr;
            memcpy(pUserinfo->chPrivateAttr, pstRegMsg->chPrivateAttr
                , sizeof(pUserinfo->chPrivateAttr));
            pUserinfo->usCommSocket = (unsigned short)nSocket;
            pUserinfo->pNext = NULL;
            //////////////////////////////////////////////////////////////////////////

            if (0 != Insert_Userinfo(&g_stRuntime.pstUserListRoot[pUserinfo->u16SvcId], pUserinfo
                , (unsigned short)nSocket))
            {
                DEBUG_PRINT(LM_ERROR, "Insert_Userinfo %" PRIu64 " failed!\n"
                    , pUserinfo->u64UsrId);
                g_UsrInfoMempool.Free(pUserinfo);
                pUserinfo = NULL;
                nRetCode = -4;
                break;
            }
#ifdef TRACE_USER
            if (!bLogined)
            {
                assert(stSocketContext.pUserinfo);
                g_stRuntime.uLoginUserNum++;
            }
#endif
        }
    } while(false);

    //////////////////////////////////////////////////////////////////////////
    // 注意：这部分会修改接收缓冲区数据，由于设计时可以保证不会覆盖下一个包的
    //       数据，所以不会有问题
    pstMsgpush_Pkg->stHead.u16MsgType = htons(LOGIN_ACK);
    STRU_ACK_MSG *pstAckMsg = (STRU_ACK_MSG*)pstMsgpush_Pkg->szBody;
    //////////////////////////////////////////////////////////////////////////

    size_t uSendLen = 0;

    pstAckMsg->u8ErrMsgEncoding = CHARSET_GB2312;
    switch (nRetCode)
    {
    case 0 :
        {
            pstAckMsg->u16RetCode = htons(LOGIN_SUCCESS);
            uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + sizeof(UINT16);
        }
        break;
    case -1 :
        {
            DEBUG_PRINT(LM_EXCEPT, "LOGIN_UNALLOW and u16SvcId is: %u****************************\n"
                , pstRegMsg->u16SvcId);
            pstAckMsg->u16RetCode = htons(LOGIN_UNALLOW);
            const char *pSrvParamErr = "请求业务参数非法！";
            int nSrvParamErrLen = snprintf(pstAckMsg->szErrMsg, sizeof(pstAckMsg->szErrMsg), "%s", pSrvParamErr);
            if (nSrvParamErrLen <= 0)
            {
                return -2;
            }
            pstAckMsg->u16ErrMsgLen = htons((unsigned short)nSrvParamErrLen);
            uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + 3 * sizeof(UINT16) + (size_t)nSrvParamErrLen;
        }
        break;
#if USE_LOAD_BALANCE
    case -2 :             // 返回重定向到新的服务器指令
        {
            pstAckMsg->u16RetCode = htons(LOGIN_REDIRECT);
            *((UINT32*)&pstAckMsg->szErrMsg[0]) = inet_addr(szSrvAddrs[uServerId]);
            *((UINT16*)&pstAckMsg->szErrMsg[sizeof(UINT32)]) = htons(g_stConfig.usServerPort);
            pstAckMsg->u16ErrMsgLen = htons(sizeof(UINT32) + sizeof(UINT16));
            uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + 3 * sizeof(UINT16) + sizeof(UINT32);
        }
        break;
#endif
    case -3 :
    case -4 :
#if 0
        {
            pstAckMsg->u16RetCode = htons(LOGIN_UNKNOWN);
            const char *pSysErr = "系统繁忙！";
            int nSysErrLen = snprintf(pstAckMsg->szErrMsg, sizeof(pstAckMsg->szErrMsg), "%s", pSysErr);
            if (nSysErrLen <= 0)
            {
                return -2;
            }
            pstAckMsg->u16ErrMsgLen = htons((unsigned short)nSysErrLen);
            uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + 3 * sizeof(UINT16) + size_t(nSysErrLen);
        }
        break;
#endif
    default : // 不会走到这里，防止修改代码错误导致上面没有处理
        {
            DEBUG_PRINT(LM_EXCEPT, "nRetCode: %d, Login exist exception!\n", nRetCode);
        }
        return -3;
    }
    pstMsgpush_Pkg->stHead.u16PkgLen = htons((unsigned short)uSendLen);
    stSocketContext.szRecvBuffer[uSendLen - 1] = ETX;

    if (0 != SendPkg(nSocket, stSocketContext.szRecvBuffer, uSendLen, (nRetCode < 0)))
    {
        return -4;
    }

    return 0;
}

/*!
 * 功能: 发送数据到连接的客户端
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int HandleSend(int nSocket)
{
    assert(g_stRuntime.pSocketContext && (nSocket >= 0) && ((size_t)nSocket < g_stRuntime.uMaxSocketNum));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];
    CAutoLock AutoLock(&stSocketContext.lSendLock);
    if (ACCEPTED != stSocketContext.nSocketType)
    {
        return -1;
    }

    // 需要发送的剩余字节数
    if (stSocketContext.lToSendBytes < 0)
    {
        return -1;
    }
    else if (stSocketContext.lToSendBytes == 0)
    {
        return 1;
    }

    int nBytesSent = send(nSocket, stSocketContext.szRecvBuffer, stSocketContext.lToSendBytes, 0);
    if (nBytesSent <= 0)
    {
        if ((nBytesSent < 0) && ((EAGAIN == errno) || (EINTR == errno)))
        {
            // nBytesSent = 0; // 下一轮循环将继续发送
            return 0;
        }
        else
        {
            return -1;
        }
    }

    stSocketContext.tm_LastActive = time(NULL);
    if (nBytesSent >= stSocketContext.lToSendBytes)
    {
        stSocketContext.lToSendBytes = 0;

        // 如果是已经设置了发送完就关闭连接，则立即返回并关闭连接
        if (stSocketContext.bCloseOnSendAll)
        {
            return -1;
        }

        // 重新设置读事件监听
        if (HJ_modify_epoll_event(g_stRuntime.nEpfd, nSocket, EPOLLIN | EPOLLET) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Call HJ_modify_epoll_event() for read failed:(nSocket is:%d)!\n"
                , nSocket);
            return -1;
        }
    }
    else
    {
        stSocketContext.lToSendBytes -= nBytesSent;
        memmove(stSocketContext.szSendBuffer, stSocketContext.szSendBuffer + nBytesSent
            , stSocketContext.lToSendBytes);
    }

    return 0;
}

/*!
 * 功能: 从指定Socket读入数据
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int HandleRecv(int nSocket)
{
    // DEBUG_PRINT(LM_TRACE, "iSocket is: %d\n", iSocket);
    assert(g_stRuntime.pSocketContext
        && (nSocket >= 0) && (nSocket < (int)g_stRuntime.uMaxSocketNum));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];

#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    bool bRecvFull, bRecvable;

    int nRetCode;
    ssize_t nBytesReceived;
    size_t uPkgLen;

    for (;;)
    {
        // 当前接收缓冲区空闲大小
        nBytesReceived = recv(nSocket, stSocketContext.szRecvBuffer + stSocketContext.lRecvBytes
            , sizeof(stSocketContext.szRecvBuffer) - stSocketContext.lRecvBytes - 1, 0);
        stSocketContext.tm_LastActive = time(NULL);
        if (nBytesReceived <= 0)
        {
            if ((nBytesReceived < 0)
                && ((errno == EAGAIN) || (errno == EINTR))) // 读Socket发生软中断或者非阻塞没读完, 需要继续读
            {
                // 下次继续读
                return 1;
            }
            else // 读失败, Socket已断开
            {
                // DEBUG_PRINT(LM_ERROR, "nBytesReceived: %Zd and errno: %d\n", nBytesReceived, errno);
                return -1;
            }
        }
        stSocketContext.lRecvBytes += nBytesReceived;
        stSocketContext.szRecvBuffer[stSocketContext.lRecvBytes] = '\0';

        // 当前接收缓冲区是否已满
        bRecvFull = ((sizeof(stSocketContext.szRecvBuffer) - stSocketContext.lRecvBytes - 1) == 0);

        for (;;)
        {
            bRecvable = ((sizeof(stSocketContext.szRecvBuffer) - stSocketContext.lRecvBytes - 1) != 0);

            // 如果还未解析当前报头, 则首先进行解析
            if (stSocketContext.lPkgLen == 0)
            {
                nRetCode = HandlePkgHead(stSocketContext, uPkgLen);
                // DEBUG_PRINT(LM_DEBUG, "Call HandlePkgHead: %d, lRecivedBytes: %ld, uPkgLen: %u, bFirstProcess: %s\n"
                //     , nRetCode, stSocketContext.lRecvBytes, uPkgLen, bFirstProcess? "first" : "nofirst");
                if (nRetCode > 0)          // 还未接收完整
                {
                    if (bRecvFull)
                    {
                        // 如果上次接收满了，但是当前未接收完整并且缓冲区也满了，则视为非法请求，断开连接
                        if (!bRecvable)
                        {
                            nRetCode = -1;
                        }
                        else               // 继续接收
                        {
                            break;
                        }
                    }
                    else
                    {
                        return 1;          // 下次继续接收
                    }
                }
                else if (nRetCode == 0)      // 解析成功
                {
                    // 如果包头指示的包长大于缓冲区则直接断开连接
                    if (uPkgLen >= sizeof(stSocketContext.szRecvBuffer))
                    {
                        nRetCode = -2;
                    }
                    else
                    {
                        stSocketContext.lPkgLen = uPkgLen;
                    }
                }

                if (nRetCode < 0)           // 报数据有误
                {
                    DEBUG_PRINT(LM_ERROR, "接受到的数据头格式有误！\n");
                    // HJ_hex_show(stSocketContext.szRecvBuffer, stSocketContext.lRecvBytes);
                    return -1;
                }
            }

            // 包还未接收完整
            if (stSocketContext.lRecvBytes < stSocketContext.lPkgLen)
            {
                // 如果接收系统缓冲区还有消息并且当前为非首次子循环则跳出到上层循环继续接受
                if (bRecvFull && bRecvable)
                {
                    break;
                }
                return 1; // 报体未接收完整
            }

            // 报文已经接收完整
            nRetCode = HandlePkg(nSocket, stSocketContext);
            if (nRetCode < 0)
            {
                DEBUG_PRINT(LM_DEBUG, "Call HandlePkg failured!\n");
                return -1;
            }

            // 当前报文已经处理完, 初始化下一个报文位置
            stSocketContext.lRecvBytes -= stSocketContext.lPkgLen;
            if (stSocketContext.lRecvBytes < 0)
            {
                DEBUG_PRINT(LM_ERROR, "stSocketContext.RecvBytes: %ld\n", stSocketContext.lRecvBytes);
                return -1;
            }
            // 如果接收缓冲区还有未解析的消息
            if (stSocketContext.lRecvBytes > 0)
            {
                memmove(stSocketContext.szRecvBuffer, (stSocketContext.szRecvBuffer + stSocketContext.lPkgLen)
                    , stSocketContext.lRecvBytes);
                stSocketContext.szRecvBuffer[stSocketContext.lRecvBytes] = '\0';
            }
            stSocketContext.lPkgLen = 0;

            if (stSocketContext.lRecvBytes == 0)
            {
                if (bRecvFull)
                {
                    break;
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    return 0;
}

// 按业务批量推送消息
int Batch_PushMsg_2_SrvId(struct HJ_RB_node *pUserinfo_RBRoot, const char *pSendBuffer, size_t uSendLen
    , STRU_PUSH_MSG *pPushMsg
#ifdef TRACE_USER
    , size_t &uSendCnt
#endif
    )
{
    assert(pSendBuffer && pPushMsg);

    if (pUserinfo_RBRoot)
    {
        Batch_PushMsg_2_SrvId(pUserinfo_RBRoot->pLeft, pSendBuffer, uSendLen, pPushMsg
#ifdef TRACE_USER
            , uSendCnt
#endif
            );

        //////////////////////////////////////////////////////////////////////////
        STRU_USERINFO_ACS *pUserinfo = HJ_RB_Entery(pUserinfo_RBRoot, STRU_USERINFO_ACS, rbNode);
        while (pUserinfo)
        {
            if ((pPushMsg->u32CommAttr == 0) || (pUserinfo->u32CommAttr & pPushMsg->u32CommAttr))
            {
                SendPkg(pUserinfo->usCommSocket, pSendBuffer, uSendLen);
#ifdef TRACE_USER
                uSendCnt++;
#endif
            }
            pUserinfo = pUserinfo->pNext;
        }
        //////////////////////////////////////////////////////////////////////////

        Batch_PushMsg_2_SrvId(pUserinfo_RBRoot->pRight, pSendBuffer, uSendLen, pPushMsg
#ifdef TRACE_USER
            , uSendCnt
#endif
            );
    }

    return 0;
}

// 处理接收业务消息然后分发的线程
void* Dispatch_Msg_Thread(void *pThreadId)
{
    assert(pThreadId);

    // int nThreadId = *((int*)pThreadId);

    struct sockaddr_in stAddrFrom;
    socklen_t uAddrLen = sizeof(stAddrFrom);

    char szRecvBuffer[MAX_PUSH_PKG_LEN] = {0}, szSendBuffer[MAX_PUSH_PKG_LEN] = {0};
    int nRecvLen = 0;
    size_t uSendLen = 0;
    UINT16 u16PkgLen = 0, u16PkgBodyLen = 0;

    STRU_MSGPUSH_PKG *pstRecvPkg = (STRU_MSGPUSH_PKG*)szRecvBuffer;
    STRU_MSGPUSH_PKG *pstSendPkg = (STRU_MSGPUSH_PKG*)szSendBuffer;
    // 解析推送消息时用
    STRU_PUSH_MSG *pPushMsg = (STRU_PUSH_MSG*)pstRecvPkg->szBody;
#if 0
    // 返回应答时使用
    STRU_ACK_MSG *pstAckMsg = (STRU_ACK_MSG*)pstRecvPkg->szBody;
#endif

    //////////////////////////////////////////////////////////////////////////
    // 初始化发送报固定数据段
    pstSendPkg->u8Stx = STX;
    pstSendPkg->stHead.u16MsgType = htons(PUSH_MSG_REQ);
    pstSendPkg->stHead.u16Verion = htons(0x0100);
    //////////////////////////////////////////////////////////////////////////

    size_t uSocketId = 0;
    int nNextIndex = 0, nRetCode = 0;

    for (;;)
    {
        // 读请求
        nRecvLen = recvfrom(g_stRuntime.nUdpSocket, szRecvBuffer, sizeof(szRecvBuffer)
            , 0, (struct sockaddr*)&stAddrFrom, &uAddrLen);
        if (nRecvLen <= 0)
        {
            continue;
        }
        szRecvBuffer[nRecvLen] = '\0';

        // HJ_hex_show(szRecvBuffer, nRecvLen);

        if ((szRecvBuffer[0] != STX)
            || (szRecvBuffer[nRecvLen - 1] != ETX))
        {
            DEBUG_PRINT(LM_ERROR, "Push消息首尾标识有误！\n");
            continue;
        }

        nRetCode = 0;
        do
        {
            if (ntohs(pstRecvPkg->stHead.u16MsgType) != DISPATCH_MSG_REQ)
            {
                DEBUG_PRINT(LM_ERROR, "Push消息类型有误！\n");
                nRetCode = -1;
                break;
            }

            u16PkgLen = ntohs(pstRecvPkg->stHead.u16PkgLen);
            if ((u16PkgLen != (UINT16)nRecvLen)
                || (u16PkgLen < (sizeof(STRU_MSGPUSH_PKG_HEAD) + 2 * sizeof(UINT8))))
            {
                DEBUG_PRINT(LM_ERROR, "Push消息长度有误！\n");
                nRetCode = -1;
                break;
            }

            u16PkgBodyLen = u16PkgLen - sizeof(STRU_MSGPUSH_PKG_HEAD) - 2 * sizeof(UINT8);
            // DEBUG_PRINT(LM_DEBUG, "u16PkgLen: %lu, u16PkgBodyLen: %lu\n"
            //     , u16PkgLen, u16PkgBodyLen);
            if (u16PkgBodyLen < sizeof(STRU_PUSH_MSG))
            {
                DEBUG_PRINT(LM_ERROR, "u16PkgBodyLen长度有误: (%u)！\n", u16PkgBodyLen);
                nRetCode = -1;
                break;
            }

            //////////////////////////////////////////////////////////////////////////
            pPushMsg->u16MsgLen = ntohs(pPushMsg->u16MsgLen);
            if (pPushMsg->u16MsgLen != (u16PkgBodyLen - sizeof(STRU_PUSH_MSG)))
            {
                DEBUG_PRINT(LM_ERROR, "u16MsgLen长度有误: (%u)！\n", pPushMsg->u16MsgLen);
                nRetCode = -1;
                break;
            }

            pPushMsg->u64UsrId = ntohq(pPushMsg->u64UsrId);
            pPushMsg->u16SvcId = ntohs(pPushMsg->u16SvcId);
            pPushMsg->u32CommAttr = ntohl(pPushMsg->u32CommAttr);

            if (pPushMsg->u16SvcId >= g_stRuntime.uMaxServiceNum)
            {
                DEBUG_PRINT(LM_ERROR, "u16SvcId超过最大值: (%u - %Zu)！\n", pPushMsg->u16SvcId, g_stRuntime.uMaxServiceNum);
                nRetCode = -2;
                break;;
            }

            //////////////////////////////////////////////////////////////////////////
            // DEBUG_PRINT(LM_INFO, "UsrId: %" PRIu64 ",SrvId: %u,CommAttr: %u,Msg: %s\n"
            //    , pPushMsg->u64UsrId, pPushMsg->u16SvcId, pPushMsg->u32CommAttr, pPushMsg->szMsg);

            uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + sizeof(UINT8) + sizeof(UINT16) + pPushMsg->u16MsgLen;
            pstSendPkg->stHead.u16PkgLen = htons(uSendLen);
            // DEBUG_PRINT(LM_DEBUG, "MsgEncoding: %u-\n", pPushMsg->u8MsgEncoding);
            // 拷贝消息内容编码类型
            *((UINT8*)(&pstSendPkg->szBody[0])) = pPushMsg->u8MsgEncoding;
            // 拷贝消息内容长度
            *((UINT16*)(&pstSendPkg->szBody[sizeof(UINT8)])) = htons(pPushMsg->u16MsgLen);
            // 拷贝消息内容
            memcpy((pstSendPkg->szBody + sizeof(UINT8) + sizeof(UINT16)), pPushMsg->szMsg, pPushMsg->u16MsgLen);
            szSendBuffer[uSendLen - 1] = ETX;
            // DEBUG_PRINT(LM_DEBUG, "%uBytes\n", pPushMsg->u16MsgLen);

            if (pPushMsg->u16SvcId != 0)
            {
                if (pPushMsg->u64UsrId != 0)
                {
#ifdef TRACE_USER
                    size_t uSendCnt = 0;
#endif

                    // 单独发给指定用户
                    STRU_USERINFO_ACS* pUserinfo = Search_Userinfo(&g_stRuntime.pstUserListRoot[pPushMsg->u16SvcId]
                        , pPushMsg->u64UsrId);
                    while (pUserinfo)
                    {
                        // DEBUG_PRINT(LM_DEBUG, "SendPkg to %ld - %s\n"
                        //     , pPushMsg->u64UsrId, pPushMsg->szMsg);
                        uSocketId = pUserinfo->usCommSocket;
                        if ((uSocketId < g_stConfig.uMaxSocketNum)
                            && (g_stRuntime.pSocketContext[uSocketId].nSocketType == ACCEPTED))
                        {
                            SendPkg((int)uSocketId, (const char*)szSendBuffer, uSendLen);
#ifdef TRACE_USER
                            uSendCnt++;
#endif
                        }
                        pUserinfo = pUserinfo->pNext;
                    }
#ifdef TRACE_USER
                    DEBUG_PRINT(LM_DEBUG, "TotalOnlineUser: %Zu, TotalLoginUser: %Zu, Send %ZuUsers\n"
                        , g_stRuntime.uOnlineUserNum, g_stRuntime.uLoginUserNum, uSendCnt);
                    // printf("%Zu+\n", uSendCnt);
#endif
                }
                else
                {
                    // 按业务发送
#ifdef TRACE_USER
                    size_t uSendCnt = 0;
#endif
                    Batch_PushMsg_2_SrvId(g_stRuntime.pstUserListRoot[pPushMsg->u16SvcId].pRBNode
                        , (const char*)szSendBuffer, uSendLen, pPushMsg
#ifdef TRACE_USER
                        , uSendCnt
#endif
                        );
#ifdef TRACE_USER
                    DEBUG_PRINT(LM_DEBUG, "TotalOnlineUser: %Zu, TotalLoginUser: %Zu, Send %ZuUsers\n"
                        , g_stRuntime.uOnlineUserNum, g_stRuntime.uLoginUserNum, uSendCnt);
                    // printf("%Zu+\n", uSendCnt);
#endif
                }
            }
            else
            {
                // 全员推送
#ifdef TRACE_USER
                size_t uSendCnt = 0;
#endif
                for (int i = g_stRuntime.nConn_Queue_Root; i != -1; i = nNextIndex)
                {
                    nNextIndex = g_stRuntime.pSocketContext[i].nNextIndex;

                    if ((g_stRuntime.pSocketContext[i].nSocketType != ACCEPTED)
                        || !g_stRuntime.pSocketContext[i].pUserinfo
                        || ((pPushMsg->u32CommAttr != 0)
                        && (g_stRuntime.pSocketContext[i].pUserinfo->u32CommAttr & pPushMsg->u32CommAttr == 0))
                        )
                    {
                        continue;
                    }
                    SendPkg(i, (const char*)szSendBuffer, uSendLen);
#ifdef TRACE_USER
                    uSendCnt++;
#endif
                }
#ifdef TRACE_USER
                DEBUG_PRINT(LM_DEBUG, "TotalOnlineUser: %Zu, TotalLoginUser: %Zu, Send %ZuUsers\n"
                    , g_stRuntime.uOnlineUserNum, g_stRuntime.uLoginUserNum, uSendCnt);
#endif
                // printf("%Zu+\n", uSendCnt);
            }
        } while (false);

        // 返回发送应答
#if 0
        //////////////////////////////////////////////////////////////////////////
        // 注意：这部分会修改接收缓冲区数据，由于设计时可以保证不会覆盖下一个包的
        //       数据，所以不会有问题
        pstRecvPkg->stHead.u16MsgType = htons(PUSH_MSG_ACK);
        uSendLen = 0;

        pstAckMsg->u8ErrMsgEncoding = CHARSET_GB2312;
        switch (nRetCode)
        {
        case 0 :
            {
                pstAckMsg->u16RetCode = htons(PUSH_SUCCESS);
                uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + sizeof(UINT16);
            }
            break;
        case -1 :
            {
                pstAckMsg->u16RetCode = htons(PUSH_ILLEGAL);
                const char *pFormatErr = "推送消息格式有误！";
                int nFormatErrLen = snprintf(pstAckMsg->szErrMsg, sizeof(pstAckMsg->szErrMsg), "%s", pFormatErr);
                if (nFormatErrLen <= 0)
                {
                    break;
                }
                pstAckMsg->u16ErrMsgLen = htons((unsigned short)nFormatErrLen);
                uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + 3 * sizeof(UINT16) + size_t(nFormatErrLen);
            }
            break;
        case -2 :
            {
                pstAckMsg->u16RetCode = htons(PUSH_UNALLOW);
                const char *pSysParamErr = "推送业务参数非法！";
                int nSysParamErrLen = snprintf(pstAckMsg->szErrMsg, sizeof(pstAckMsg->szErrMsg), "%s", pSysParamErr);
                if (nSysParamErrLen <= 0)
                {
                    break;
                }
                pstAckMsg->u16ErrMsgLen = htons((unsigned short)nSysParamErrLen);
                uSendLen = 2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD) + 3 * sizeof(UINT16) + size_t(nSysParamErrLen);
            }
            break;
        default :
            break;
        }

        if (uSendLen > 0)
        {
            pstRecvPkg->stHead.u16PkgLen = htons((unsigned short)uSendLen);
            szRecvBuffer[uSendLen - 1] = ETX;

            sendto(g_stRuntime.nUdpSocket, szRecvBuffer, uSendLen, 0
                , (const struct sockaddr*)&stAddrFrom, sizeof(stAddrFrom));
        }
#endif
        //////////////////////////////////////////////////////////////////////////
    }

    return NULL;
}

/*!
 * 功能: 根据Socket的状态检查结果开始处理各个Socket数据发送和接收
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int CheckAndProcessOnSockets(int nSocketNum)
{
    // DEBUG_PRINT(LM_TRACE, "iSocketNum is:%d\n", iSocketNum);

    int nRetCode, nSocket;
    for (int i = 0; i < nSocketNum; i++)
    {
        nSocket = g_stRuntime.pEvents[i].data.fd;
        if ((nSocket < 0) || (nSocket >= (int)g_stRuntime.uMaxSocketNum)
            || (g_stRuntime.pSocketContext[nSocket].nSocketType == NOT_USED))
        {
            continue;
        }

        if (g_stRuntime.pSocketContext[nSocket].nSocketType == LISTENER)
        {
            if (g_stRuntime.pEvents[i].events & (EPOLLERR | EPOLLHUP))
            {
                DEBUG_PRINT(LM_ERROR, "Listen socket meet error\n");
                continue;
            }

            if (g_stRuntime.pEvents[i].events & EPOLLIN)
            {
                CheckAndAcceptConns(nSocket);
            }
        }
        else
        {
            if (g_stRuntime.pEvents[i].events & (EPOLLERR | EPOLLHUP))
            {
                DEBUG_PRINT(LM_ERROR, "Socket error and CloseSocket!\n");
                CloseSocket(nSocket);
                continue;
            }

            if (g_stRuntime.pEvents[i].events & EPOLLIN)
            {
                nRetCode = HandleRecv(nSocket);
                if (nRetCode < 0)
                {
                    // DEBUG_PRINT(LM_ERROR, "Socket Recv failure and CloseSocket\n");
                    CloseSocket(nSocket);
                    continue;
                }
            }

            if (g_stRuntime.pEvents[i].events & EPOLLOUT)
            {
                nRetCode = HandleSend(nSocket);
                if (nRetCode < 0)
                {
                    DEBUG_PRINT(LM_DEBUG, "Call HandleSend failure and CloseSocket\n");
                    CloseSocket(nSocket);
                    continue;
                }
            }
        }
    }

    return 0;
}

/*!
 * 功能: 初始化子进程
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int InitializeChildProcess(void)
{
    bool bInitFailed = true;

    do
    {
        if (g_UsrInfoMempool.Init(sizeof(STRU_USERINFO_ACS), g_stRuntime.uMaxSocketNum) != 0)
        {
            printf("CHJ_Mempool:Call Init failed!\n");
            break;
        }

        g_stRuntime.nUdpSocket = HJ_UDP_Server(g_stConfig.szLocalIp
            , (g_stConfig.usUdpPort + g_stRuntime.uProcessId));
        if (g_stRuntime.nUdpSocket < 0)
        {
            printf("Call HJ_UDP_Server(%s-%u) failed!\n"
                , g_stConfig.szLocalIp, (unsigned short)(g_stConfig.usUdpPort + g_stRuntime.uProcessId));
            break;
        }

        // 初始化创建连接Socket状态数组
        g_stRuntime.pSocketContext = new(nothrow) STRU_SOCKET_CONTEXT[g_stRuntime.uMaxSocketNum];
        if (!g_stRuntime.pSocketContext)
        {
            printf("new g_stRuntime.pSocketContext[%Zu] failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }
        bzero(g_stRuntime.pSocketContext, (g_stRuntime.uMaxSocketNum * sizeof(STRU_SOCKET_CONTEXT)));

        // 初始化与监听套接字相关的状态
        g_stRuntime.pSocketContext[g_stRuntime.nListen_Socket].nSocketType = LISTENER;

        // 初始化创建epoll监听事件数组
        g_stRuntime.pEvents = new(nothrow) struct epoll_event[g_stRuntime.uMaxSocketNum];
        if (!g_stRuntime.pEvents)
        {
            printf("new g_pEvent[%Zu] failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }
        bzero(g_stRuntime.pEvents, (g_stRuntime.uMaxSocketNum * sizeof(struct epoll_event)));

        // 初始化创建业务RB树根节点数组
        g_stRuntime.pstUserListRoot = new(nothrow) struct HJ_RB_root[g_stRuntime.uMaxServiceNum];
        if (!g_stRuntime.pstUserListRoot)
        {
            printf("new g_stRuntime.pstUserListRoot[%Zu] failed!\n", g_stRuntime.uMaxServiceNum);
            break;
        }

        g_stRuntime.nEpfd = epoll_create(g_stRuntime.uMaxSocketNum);
        if (g_stRuntime.nEpfd < 0)
        {
            printf("Call epoll_create(%Zu) failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }

        if (HJ_register_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket, EPOLLIN | EPOLLET) < 0)
        {
            printf("Call HJ_register_epoll_event() for adding listen socket failed!\n");
            break;
        }
        g_stRuntime.bListen_Epoll_Added = true;

        bInitFailed = false;
    } while (false);

    if (bInitFailed)
    {
        g_UsrInfoMempool.Destroy();

        if (g_stRuntime.nEpfd >= 0)
        {
            if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket) >= 0)
            {
                g_stRuntime.bListen_Epoll_Added = false;
            }
            close(g_stRuntime.nEpfd);
            g_stRuntime.nEpfd = -1;
        }

        if (g_stRuntime.pstUserListRoot)
        {
            delete []g_stRuntime.pstUserListRoot;
            g_stRuntime.pstUserListRoot = NULL;
        }

        if (g_stRuntime.pEvents)
        {
            delete []g_stRuntime.pEvents;
            g_stRuntime.pEvents = NULL;
        }

        if (g_stRuntime.pSocketContext)
        {
            delete []g_stRuntime.pSocketContext;
            g_stRuntime.pSocketContext = NULL;
        }

        if (g_stRuntime.nUdpSocket >= 0)
        {
            close(g_stRuntime.nUdpSocket);
            g_stRuntime.nUdpSocket = -1;
        }

        return -1;
    }

    char szLogFilePath[MAXNAMLEN];
    snprintf(szLogFilePath, sizeof(szLogFilePath), "%s_%03Zu"
        , g_stConfig.szLogFilePath, g_stRuntime.uProcessId);
    // g_sh_log.InitLogFile(szLogFilePath, g_stConfig.nMaxLogNum, g_stConfig.lMaxLogSize);

    printf("End initialize Child Process %Zu\n", g_stRuntime.uProcessId);

    return 0;
}

/*!
 * 功能: 接口机进程
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int InterfaceProcess(void)
{
    close(g_stRuntime.nListen_Socket);

    g_stRuntime.nUdpSocket = HJ_UDP_Server(g_stConfig.szLocalIp, g_stConfig.usUdpPort);
    if (g_stRuntime.nUdpSocket < 0)
    {
        DEBUG_PRINT(LM_ERROR, "Call HJ_UDP_Server(%s-%u) failed!\n"
            , g_stConfig.szLocalIp, g_stConfig.usUdpPort);
        kill(0, SIGKILL);
        return -1;
    }

    struct sockaddr_in stAddrFrom, stAddrTo;
    socklen_t uAddrLen = sizeof(stAddrFrom);
    char szRecvBuffer[MAX_PUSH_PKG_LEN];
    int nRecvLen = 0;

    bzero(&stAddrTo, sizeof(stAddrTo));
    stAddrTo.sin_family = AF_INET;
    stAddrTo.sin_addr.s_addr = inet_addr(g_stConfig.szLocalIp);
    // stAddrTo.sin_port = htons((unsigned short)(g_stConfig.usUdpPort + g_stRuntime.uProcessId));

    STRU_MSGPUSH_PKG *pstMsgpushPkg = (STRU_MSGPUSH_PKG*)szRecvBuffer;
    UINT16 u16PkgLen = 0;

    for (;;)
    {
        // 读请求
        nRecvLen = recvfrom(g_stRuntime.nUdpSocket, szRecvBuffer, sizeof(szRecvBuffer)
            , 0, (struct sockaddr*)&stAddrFrom, &uAddrLen);
        if (nRecvLen <= 0)
        {
            continue;
        }

        // HJ_hex_show(szRecvBuffer, nRecvLen);

        if ((szRecvBuffer[0] != STX)
            || (szRecvBuffer[nRecvLen - 1] != ETX))
        {
            DEBUG_PRINT(LM_ERROR, "Push消息首尾标识有误！\n");
            continue;
        }

        if (ntohs(pstMsgpushPkg->stHead.u16MsgType) != DISPATCH_MSG_REQ)
        {
            DEBUG_PRINT(LM_ERROR, "Push消息类型有误！(%u)\n", ntohs(pstMsgpushPkg->stHead.u16MsgType));
            continue;
        }

        u16PkgLen = ntohs(pstMsgpushPkg->stHead.u16PkgLen);
        if ((u16PkgLen != (UINT16)nRecvLen)
            || (u16PkgLen < (sizeof(STRU_MSGPUSH_PKG_HEAD) + 2 * sizeof(UINT8))))
        {
            DEBUG_PRINT(LM_ERROR, "Push消息长度有误！\n");
            continue;
        }

        for (size_t i = 0; i < g_stConfig.uProcessNum; i++)
        {
            stAddrTo.sin_port = htons((unsigned short)(g_stConfig.usUdpPort + 1 + i));
            sendto(g_stRuntime.nUdpSocket, szRecvBuffer, nRecvLen, 0
                , (const struct sockaddr*)&stAddrTo, sizeof(stAddrTo));
        }
    }

    return 0;
}

/*!
 * 功能: 子进程处理
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int ChildProcess(void)
{
    int iRetCode = InitializeChildProcess();
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    pthread_t pid = 0;
    int nThreadId = 1;
    if (0 != pthread_create(&pid, NULL, Dispatch_Msg_Thread, (void*)&nThreadId))
    {
        return -1;
    }

    while (true)
    {
        iRetCode = CheckConnStatus();
        if (iRetCode < 0)
        {
            continue;
        }

        CheckAndProcessOnSockets(iRetCode);
    }

    return 0;
}

/*!
 * 功能: 初始化侦听端口
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int InitListenPort(void)
{
    //////////////////////////////////////////////////////////////////////////
    putchar('\n');
    //////////////////////////////////////////////////////////////////////////

    int iSocket = HJ_CreateListenSock(SOCK_STREAM, NULL
        , g_stConfig.usServerPort, NULL);
    if (iSocket < 0)
    {
        printf("Initiate Listening  Port Failed: (Port=%u)\n"
            , g_stConfig.usServerPort);
        return -1;
    }
    else
    {
        HJ_SetNoBlock(iSocket); // 设置Socket为非阻塞模式

        // 记录监听套接字ID（注意: 不能加入连接队列, 故用一个全局变量来保存）
        g_stRuntime.nListen_Socket = iSocket;

        printf("Initiate Listening  Port OK: (Port=%u) and (Socket=%d)\n"
            , g_stConfig.usServerPort, iSocket);
    }

    return 0;
}

/*!
 * 功能: 主进程中的初始化相应运行时参数
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int InitializeMainProcess(char *pConfigFile)
{
    assert(pConfigFile);

    bzero(&g_stConfig, sizeof(g_stConfig));

    struct stat stFileStat;
    if (stat(pConfigFile, &stFileStat) < 0)
    {
        printf("配置文件:  %s 不存在！\n", pConfigFile);
        return -1;
    }

    int nServerId, nUdpPort, nServerPort, nProcessNum, nMaxSocketNum, nMaxServiceNum;

    printf("Initializing...\nUse config file: %s\n", pConfigFile);

    HJ_Cfg_GetConfig(pConfigFile
        , "LocalIp", CFG_STRING, g_stConfig.szLocalIp, DEFAULT_LOCAL_IP
            , sizeof(g_stConfig.szLocalIp)
        , "ServerId", CFG_INT, &nServerId, (int)0

        , "ServerPort", CFG_INT, &nServerPort, (int)DEFAULT_SERVER_PORT
        , "UdpPort", CFG_INT, &nUdpPort, (int)DEFAULT_UDP_PORT
        , "ProcessNum", CFG_INT, &nProcessNum, (int)DEFAULT_PROCESS_NUM
        , "PidFilePath", CFG_STRING, g_stConfig.szPidFilePath, DEFAULT_PID_FILE
            , sizeof(g_stConfig.szPidFilePath)

        , "MaxSocketNum", CFG_INT, &nMaxSocketNum, (int)DEFAULT_MAX_SOCKET_NUM

        , "ConnTimeout", CFG_LONG, &(g_stConfig.lConnTimeout), (long)DEFAULT_CONN_TIMEOUT

        , "MaxServiceNum", CFG_INT, &nMaxServiceNum, (int)DEFAULT_MAX_SERVICE_NUM

        , "LogFilePath", CFG_STRING, g_stConfig.szLogFilePath, DEFAULT_LOG_FILE
            , sizeof(g_stConfig.szLogFilePath)
        , "MaxLogSize", CFG_LONG, &(g_stConfig.lMaxLogSize), (long)MAX_LOG_SIZE
        , "MaxLogNum", CFG_INT, &(g_stConfig.nMaxLogNum), (int)MAX_LOG_NUM

        , NULL
        );
    g_stConfig.uServerId = (size_t)nServerId;
    g_stConfig.usServerPort = (unsigned short)nServerPort;
    g_stConfig.usUdpPort = (unsigned short)nUdpPort;
    g_stConfig.uProcessNum = (size_t)nProcessNum;
    g_stConfig.uMaxSocketNum = (size_t)nMaxSocketNum;
    g_stConfig.uMaxServiceNum = (size_t)nMaxServiceNum;

    if (g_stConfig.uMaxSocketNum < RESERVE_OTHER_SOCKET_NUM)
    {
        printf("MaxSocketNum: %Zu is illegal!\n", g_stConfig.uMaxSocketNum);
        return -2;
    }

    //////////////////////////////////////////////////////////////////////////
    printf("*************************************************************\n");
    printf("Startup paremeters is as following:\n\n");
    printf("LocalIp: %s\n\n", g_stConfig.szLocalIp);
    printf("ServerId: %Zu\n",g_stConfig.uServerId);
    printf("ServerPort: %u\n", g_stConfig.usServerPort);
    printf("UdpPort: %u\n", g_stConfig.usUdpPort);
    printf("ProcessNum: %Zu\n", g_stConfig.uProcessNum);
    printf("PidFilePath: %s\n\n", g_stConfig.szPidFilePath);
    printf("MaxSocketNum: %Zu\n\n", g_stConfig.uMaxSocketNum);
    printf("ConnTimeout: %ld\n", g_stConfig.lConnTimeout);
    printf("MaxServiceNum: %Zu\n\n", g_stConfig.uMaxServiceNum);
    printf("LogFilePath: %s\n", g_stConfig.szLogFilePath);
    printf("MaxLogSize: %ld\n", g_stConfig.lMaxLogSize);
    printf("MaxLogNum: %d\n\n", g_stConfig.nMaxLogNum);
    printf("*************************************************************\n");
    //////////////////////////////////////////////////////////////////////////

    // g_sh_log.InitLogFile(g_stConfig.sLogFilePath, g_stConfig.iMaxLogNum, g_stConfig.lMaxLogSize);

    // 扩展系统的一些限制参数
    // HJ_SetRLimit();

    rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim);
    rlim.rlim_max = rlim.rlim_cur = g_stConfig.uMaxSocketNum;

    if (setrlimit(RLIMIT_NOFILE, &rlim))
    {
        DEBUG_PRINT(LM_ERROR, "Call setrlimit for RLIMIT_NOFILE failed!\n");
        return -3;
    }
    getrlimit(RLIMIT_NOFILE, &rlim);
    g_stRuntime.uMaxSocketNum = rlim.rlim_max;

    g_stRuntime.uMaxServiceNum = g_stConfig.uMaxServiceNum;

    HJ_CreatePIDFile(g_stConfig.szPidFilePath);

    printf("Initializing as a daemon...\n");
    HJ_InitDaemon();

    return 0;
}

/*!
 * 功能: 启动子进程
 * @n返回值: 0 - 父进程,  > 0 - 子进程
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
int ForkChildProcesses(size_t &uProcessId, size_t uProcessNum)
{
    pid_t iPid;

    uProcessId = 0;
    for (size_t i = 1; i <= uProcessNum; i++)
    {
        if ((iPid = fork()) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Fork the %Zust child process failed!\n", i);
            kill(0, SIGKILL);
            return -1;
        }
        else if (iPid == 0)
        {
            uProcessId = i;
            return uProcessId;
        }
    }

    return uProcessId;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s ConfigFile\n", argv[0]);
        return -1;
    }

    int nRet = InitializeMainProcess(argv[1]);
    if (nRet < 0)
    {
        printf("Call InitializeMainProcess() failed!\n");
        return -1;
    }

    nRet = InitListenPort();
    if (nRet < 0)
    {
        printf("Call InitListenPort() failed!\n");
        return -1;
    }

    if (ForkChildProcesses(g_stRuntime.uProcessId, g_stConfig.uProcessNum) < 0)
    {
        printf("Call ForkChildProcesses() failed!\n");
        return -1;
    }

    if (g_stRuntime.uProcessId == 0)
    {
        InterfaceProcess();
    }
    else
    {
        ChildProcess();
    }

    printf("！！！Exception: Call ChildProcess() failed!\n");

    return 0;
}
