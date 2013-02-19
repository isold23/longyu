/*! @hj_net.cpp
*******************************************************************************
</PRE>
模块名       ：网络相关库函数定义
文件名       ：hj_net.cpp
相关文件     ：hj_net.h
文件实现功能 ：网络相关库函数定义
作者         ：huangjun - 神州星国际(http://www.shenzhoustar.com)
版本         ：1.0.1
-------------------------------------------------------------------------------
备注：
-------------------------------------------------------------------------------
修改记录：
日期        版本        修改人      修改内容
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "hj_net.h"

/****************************************************************************
* 功能：创建监听Socket
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_CreateListenSock(int iSocketType, const char *pszHost
    , const u_short usPort, int *pListener)
{
    int iListenSocket = socket(AF_INET, iSocketType, 0);
    if (iListenSocket < 0)
    {
        perror("socket");
        return -1;
    }

    if (pListener != NULL)
    {
        *pListener = iListenSocket;
    }

    int iReuseAddr = 1;
    setsockopt(iListenSocket, SOL_SOCKET, SO_REUSEADDR, (void*)(&(iReuseAddr))
        , sizeof(iReuseAddr));

    struct sockaddr_in stAddr;

    bzero((char*)&stAddr, sizeof(stAddr));
    stAddr.sin_family = AF_INET;
    if (pszHost)
    {
        stAddr.sin_addr.s_addr = inet_addr(pszHost);
    }
    else
    {
        stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    stAddr.sin_port = htons(usPort);

    if (bind(iListenSocket, (struct sockaddr *)&stAddr, sizeof(stAddr)) < 0)
    {
        perror("bind");
        close(iListenSocket);
        return -1;
    }

    if (iSocketType == SOCK_STREAM)
    {
        // Queue up to 1024 connections before having them automatically rejected.
        listen(iListenSocket, 1024);
    }
    return iListenSocket;
}

/****************************************************************************
* 功能：创建Udp侦听Socket
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_UDP_Server(const char *pszHost, u_int16_t nPort)
{
    int iUdpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (iUdpSock < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in stAddr;

    bzero(&stAddr, sizeof(stAddr));
    stAddr.sin_family = AF_INET;
    if (pszHost)
    {
        stAddr.sin_addr.s_addr = inet_addr(pszHost);
    }
    else
    {
        stAddr.sin_addr.s_addr = INADDR_ANY;
    }
    stAddr.sin_port = htons(nPort);

    if ((bind(iUdpSock, (struct sockaddr *)&stAddr, sizeof(stAddr))) == -1)
    {
        close(iUdpSock);
        perror("bind");
        return -1;
    }

    return iUdpSock;
}

/****************************************************************************
* 功能：将指定Socket设置非阻塞模式
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
int HJ_SetNoBlock(int iSocket)
{
    int iFlags = 1; // nonblock reusaddr

    ioctl(iSocket, FIONBIO, &iFlags);

    iFlags = fcntl(iSocket, F_GETFL, 0);
    fcntl(iSocket, F_SETFL, iFlags | O_NONBLOCK | O_NDELAY);

#if 1
    int iBufLen = 30 * 1024;
    //设置TCP的接收缓冲
    if(setsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
    {
        perror("setsockopt and set SO_RCVBUF");
    }

    //设置TCP的发送缓冲
    if(setsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
    {
        perror("setsockopt and set SO_SNDBUF");
    }
#endif
    return 0;
}

/****************************************************************************
* 功能：阻塞模式下发送数据
* 返回值：<0 - 发送失败或参数有误，=0 - 超时或者已关闭，>0 - 发送的字节数
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_SingleSend(int iEpfd, int iSocket, struct msghdr &stMsg)
{
    if ((iEpfd < 0) || (iSocket < 0))
    {
        printf("传入的iEpfd或者Socket句柄非法(iEpfd:%d,iSocket:%d)！\n"
            , iEpfd, iSocket);
        return -1;
    }

    struct epoll_event stEv, stEvents[2];

    bzero(&stEv, sizeof(stEv));
    stEv.data.fd = iSocket;
    stEv.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(iEpfd, EPOLL_CTL_ADD, stEv.data.fd, &stEv) < 0)
    {
        perror("epoll_ctl");
        return -1;
    }

    int iRet = epoll_wait(iEpfd, stEvents, 1, 0);
    epoll_ctl(iEpfd, EPOLL_CTL_DEL, stEv.data.fd, &stEv);

    if (iRet > 0)
    {
        if (stEvents[0].events & (EPOLLERR | EPOLLHUP))
        {
            return -1;
        }
        return sendmsg(iSocket, &stMsg, 0);
    }
    else
    {
        return iRet;
    }

    return 0;
}

/****************************************************************************
* 功能：UDP数据报的发送
* 返回值：<0 - 发送失败或参数有误，=0 - 超时或者已关闭，>0 - 发送的字节数
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_SendData(int iSocket, char *szToIp, short iToPort, char *pDataBuf, int iSendLen)
{
    assert(szToIp && pDataBuf);

    struct sockaddr_in stToAddr;

    bzero(&stToAddr, sizeof(stToAddr));
    stToAddr.sin_family = AF_INET;
    stToAddr.sin_addr.s_addr = inet_addr(szToIp);
    stToAddr.sin_port   = htons((unsigned short)iToPort);
    int iSendbytes = sendto(iSocket, pDataBuf, iSendLen, 0
        , (struct sockaddr *)&stToAddr, sizeof(struct sockaddr_in));

    return iSendbytes;
}

/*!
 * 功能: 设置TcpSocket的keepalive相关时间间隔值
 * 参数: nSocket-要设置的Socket id, nKeepAlive-设置或者清除keepalive属性
 * @n    nKeepIdle-多长时间无数据收发, 则探测, nKeepInterval-探测发包时间间隔
 * @n    nKeepCnt-探测尝试次数
 * @n作者: huangjun
 * @n日期: 2009-01-06
 */
int HJ_SetTcpSockKeepAlive(int nSocket, int nKeepAlive, int nKeepIdle, int nKeepInterval, int nKeepCnt)
{
    if (setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (void*)&nKeepAlive, sizeof(nKeepAlive)))
    {
        return -1;
    }

    if (nKeepAlive)
    {
        if (nKeepIdle > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&nKeepIdle, sizeof(nKeepIdle)))
            {
                return -2;
            }
        }

        if (nKeepInterval > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPINTVL, (void*)&nKeepInterval, sizeof(nKeepInterval)))
            {
                return -3;
            }
        }

        if (nKeepCnt > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPCNT, (void*)&nKeepCnt, sizeof(nKeepCnt)))
            {
                return -4;
            }
        }
    }

    return 0;
}
