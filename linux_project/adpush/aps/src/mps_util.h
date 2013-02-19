#ifndef __MPS_UTIL_H__
#define __MPS_UTIL_H__

#include <assert.h>
#include <sys/types.h>
#include <stdio.h>

#include "hj_misc.h"

class CAutoLock
{
public:
    CAutoLock(volatile long *plLock)
        : m_plLock(plLock)
    {
        while (HJ_xchg(plLock, 1))
        {
        }
    }
    virtual ~CAutoLock()
    {
        HJ_xchg(m_plLock, 0);
    }

private:
    volatile long *m_plLock;
};

/*!
 * 功能: 把当前要连接的Socket上下文加入到队列里
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
template<class STRU_SOCKET_CONTEXT>
int conn_add_list(int nSockFd, STRU_SOCKET_CONTEXT *pSocketContent, int &queue_root)
{
    assert((nSockFd >= 0) && pSocketContent);

    pSocketContent[nSockFd].nPrevIndex = -1;
    pSocketContent[nSockFd].nNextIndex = queue_root;

    if (queue_root != -1)
    {
        pSocketContent[queue_root].nPrevIndex = nSockFd;
    }

    queue_root = nSockFd;

    return 0;
}

/*!
 * 功能: 把当前要关闭的Socket上下文从队列中删除
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
template<class STRU_SOCKET_CONTEXT>
int conn_rmv_list(int nSockFd, STRU_SOCKET_CONTEXT *pSocketContent, int &queue_root)
{
    assert((nSockFd >= 0) && pSocketContent);

    int &nPrev = pSocketContent[nSockFd].nPrevIndex;
    int &nNext = pSocketContent[nSockFd].nNextIndex;
    if (nNext != -1)
    {
        pSocketContent[nNext].nPrevIndex = nPrev;
    }
    if (nPrev != -1)
    {
        pSocketContent[nPrev].nNextIndex = nNext;
    }

    if (nSockFd == queue_root)
    {
        queue_root = nNext;
    }
    nPrev = nNext = -1;

    return 0;
}

/*!
 * 功能: 把当前用户信息加入到双向链表头
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
template<class STRU_ELEMENT>
int user_add_list(STRU_ELEMENT *pEle, STRU_ELEMENT* &pEle_Root)
{
    assert(pEle);

    pEle->pRight = pEle_Root;
    pEle->pLeft = NULL;

    if (pEle_Root)
    {
        pEle_Root->pLeft = pEle;
    }

    pEle_Root = pEle;

    return 0;
}

/*!
 * 功能: 把指定用户信息从双向链表中删除
 * @n作者: huangjun
 * @n日期: 2008-12-02
 */
template<class STRU_ELEMENT>
int user_rmv_list(STRU_ELEMENT *pEle, STRU_ELEMENT* &pEle_Root)
{
    assert(pEle && pEle_Root);

    STRU_ELEMENT* &pLeft = pEle->pLeft;
    STRU_ELEMENT* &pRight = pEle->pRight;

    if (pRight)
    {
        pRight->pLeft = pLeft;
    }

    if (pLeft)
    {
        pLeft->pRight = pRight;
    }

    if (pEle == pEle_Root)
    {
        pEle_Root = pRight;
    }

    pLeft = pRight = NULL;

    return 0;
}

#endif
