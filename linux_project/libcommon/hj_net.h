/*! @hj_net.h
*******************************************************************************
</PRE>
模块名       ：网络相关库函数定义
文件名       ：hj_net.h
相关文件     ：hj_net.cpp
文件实现功能 ：网络相关库函数申明
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

#ifndef __HJ_NET_H__
#define __HJ_NET_H__

#include <errno.h>
#include <sys/types.h>
#include <sys/epoll.h>

#include <endian.h>
#include <byteswap.h>

#if __BYTE_ORDER == __BIG_ENDIAN
/* The host byte order is the same as network byte order,
so these functions are all just identity.  */
// 64位网络字节序转主机字节序
#define ntohq(neti64)   (neti64)
// 64位主机字节序转网络字节序
#define htonq(hosti64)  (hosti64)
#else
#if __BYTE_ORDER == __LITTLE_ENDIAN
// 64位网络字节序转主机字节序
#define ntohq(neti64)  __bswap_64(neti64)
// 64位主机字节序转网络字节序
#define htonq(hosti64) __bswap_64(hosti64)
#endif
#endif

/****************************************************************************
* 功能：创建监听Socket
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_CreateListenSock(int iSocketType, const char *pszHost
    , const u_short usPort, int *iListener);

/****************************************************************************
* 功能：创建Udp侦听Socket
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_UDP_Server(const char *pszHost, u_int16_t nPort);

/****************************************************************************
* 功能：将指定Socket设置非阻塞模式
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
int HJ_SetNoBlock(int iSocket);

/****************************************************************************
* 功能：阻塞模式下发送数据
* 返回值：<0 - 发送失败或参数有误，=0 - 超时或者已关闭，>0 - 发送的字节数
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_SingleSend(int iEpfd, int iSocket, struct msghdr &stMsg);

/****************************************************************************
* 功能：UDP数据报的发送
* 返回值：<0 - 发送失败或参数有误，=0 - 超时或者已关闭，>0 - 发送的字节数
* 作者：Huangjun
* 日期：2008-07-14
***************************************************************************/
int HJ_SendData(int iSocket, char *szToIp, short iToPort, char *pDataBuf
    , int iSendLen);

// 添加epoll事件监听
inline int HJ_register_epoll_event(int epfd, int iSocket, unsigned long ulEvent)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = ulEvent;

    return epoll_ctl(epfd, EPOLL_CTL_ADD, iSocket, &ev);
}

// 移除epoll事件监听
inline int HJ_unregister_epoll_event(int epfd, int iSocket)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = 0;
    // ev.events = EPOLLIN | EPOLLOUT | EPOLLET;

    return epoll_ctl(epfd, EPOLL_CTL_DEL, iSocket, &ev);
}

// 修改epoll事件监听
inline int HJ_modify_epoll_event(int epfd, int iSocket, unsigned long ulEvent)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = ulEvent;

    if (epoll_ctl(epfd, EPOLL_CTL_MOD, iSocket, &ev) < 0)
    {
        if (errno != ENOENT)
        {
            return epoll_ctl(epfd, EPOLL_CTL_ADD, iSocket, &ev);
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

/*!
 * 功能: 设置TcpSocket的keepalive相关时间间隔值
 * 参数: nSocket-要设置的Socket id, nKeepAlive-设置或者清除keepalive属性
 * @n    nKeepIdle-多长时间无数据收发, 则探测, nKeepInterval-探测发包时间间隔
 * @n    nKeepCnt-探测尝试次数
 * @n作者: huangjun
 * @n日期: 2009-01-06
 */
int HJ_SetTcpSockKeepAlive(int nSocket, int nKeepAlive, int nKeepIdle, int nKeepInterval, int nKeepCnt);

#endif
