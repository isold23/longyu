#include <assert.h>
#include <string.h>

#include "mps_usrinfo_acs.h"

STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId)
{
    assert(pRoot);

    struct HJ_RB_node *pNode = pRoot->pRBNode;
    STRU_USERINFO_ACS *pUserInfo = NULL;

    while (pNode)
    {
        pUserInfo = HJ_RB_Entery(pNode, STRU_USERINFO_ACS, rbNode);
        if (pUserInfo->u64UsrId < u64UsrId)
        {
            pNode = pNode->pRight;
        }
        else if (pUserInfo->u64UsrId > u64UsrId)
        {
            pNode = pNode->pLeft;
        }
        else
        {
            return pUserInfo;
        }
    }

    return NULL;
}

STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket)
{
    assert(pRoot);

    struct HJ_RB_node *pNode = pRoot->pRBNode;
    STRU_USERINFO_ACS *pUserInfo = NULL;

    while (pNode)
    {
        pUserInfo = HJ_RB_Entery(pNode, STRU_USERINFO_ACS, rbNode);
        if (pUserInfo->u64UsrId < u64UsrId)
        {
            pNode = pNode->pRight;
        }
        else if (pUserInfo->u64UsrId > u64UsrId)
        {
            pNode = pNode->pLeft;
        }
        else
        {
            while (pUserInfo && (pUserInfo->usCommSocket != usSocket))
            {
                pUserInfo = pUserInfo->pNext;
            }
            return pUserInfo;
        }
    }

    return NULL;
}

int Insert_Userinfo(struct HJ_RB_root *pRoot, STRU_USERINFO_ACS *pNewUserinfo
    , unsigned short usSocket)
{
    assert(pRoot && pNewUserinfo);

    pNewUserinfo->pNext = NULL;

    struct HJ_RB_node **ppNew = &(pRoot->pRBNode), *pParent = NULL;
    STRU_USERINFO_ACS *pUserinfo = NULL;

    while (*ppNew)
    {
        pParent = *ppNew;

        pUserinfo = HJ_RB_Entery(*ppNew, STRU_USERINFO_ACS, rbNode);
        if (pUserinfo->u64UsrId < pNewUserinfo->u64UsrId)
        {
            ppNew = &((*ppNew)->pRight);
        }
        else if (pUserinfo->u64UsrId > pNewUserinfo->u64UsrId)
        {
            ppNew = &((*ppNew)->pLeft);
        }
        else
        {
            STRU_USERINFO_ACS *pPrev = NULL;

            while (pUserinfo)
            {
                pPrev = pUserinfo;
                if (pUserinfo->usCommSocket == usSocket)
                {
                    // 绝对重复，无需再插入
                    return -1;
                }
                pUserinfo = pUserinfo->pNext;
            }

            // 串接在相应树节点为根的链表下
            pPrev->pNext = pNewUserinfo;
            pNewUserinfo->pNext = NULL;

            return 0;
        }
    }

    HJ_RB_link_node(&pNewUserinfo->rbNode, pParent, ppNew);
    HJ_RB_insert_color(&pNewUserinfo->rbNode, pRoot);

    return 0;
}

STRU_USERINFO_ACS* Remove_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket)
{
    assert(pRoot);

    STRU_USERINFO_ACS *pUserInfo = Search_Userinfo(pRoot, u64UsrId);
    if (pUserInfo)
    {
        STRU_USERINFO_ACS *pPrev = pUserInfo, *pTemp = pUserInfo;
        while (pTemp && (pTemp->usCommSocket != usSocket))
        {
            pPrev = pTemp;
            pTemp = pTemp->pNext;
        }
        if (!pTemp)
        {
            return NULL;
        }

        // 如果删除的是首节点
        if (pTemp == pUserInfo)
        {
            // 如果链表只有一个节点
            if (!pTemp->pNext)
            {
                HJ_RB_erase(&pTemp->rbNode, pRoot);
                // 把此指针返回让调用者释放
                return pTemp;
            }
            else
            {
                //////////////////////////////////////////////////////////////////////////
                // 交换首节点和次节点，以便直接从非首节点移除，而不用考虑RB树删除
                // 交换两个连接指针
                pTemp = pTemp->pNext;

                // u16SvcId
                pUserInfo->u16SvcId ^= pTemp->u16SvcId;
                pTemp->u16SvcId ^= pUserInfo->u16SvcId;
                pUserInfo->u16SvcId ^= pTemp->u16SvcId;
                // u32CommAttr
                pUserInfo->u32CommAttr ^= pTemp->u32CommAttr;
                pTemp->u32CommAttr ^= pUserInfo->u32CommAttr;
                pUserInfo->u32CommAttr ^= pTemp->u32CommAttr;
                // chPrivateAttr
                char szPrivateAttr[PRIVATE_ATTR_SIZE] = {0};
                memcpy(szPrivateAttr, pUserInfo->chPrivateAttr, sizeof(szPrivateAttr));
                memcpy(pUserInfo->chPrivateAttr, pTemp->chPrivateAttr, sizeof(pUserInfo->chPrivateAttr));
                memcpy(pTemp->chPrivateAttr, szPrivateAttr, sizeof(pTemp->chPrivateAttr));
                // usCommSocket
                pUserInfo->usCommSocket ^= pTemp->usCommSocket;
                pTemp->usCommSocket ^= pUserInfo->usCommSocket;
                pUserInfo->usCommSocket ^= pTemp->usCommSocket;
                // pNext
                pUserInfo->pNext = pTemp->pNext;

                // pTemp->usCommSocket = usSocket;
                // 把此指针返回让调用者释放
                return pTemp;
            }
        }
        else
        {
            pPrev->pNext = pTemp->pNext;
            // 把此指针返回让调用者释放
            return pTemp;
        }
    }

    return NULL;
}
