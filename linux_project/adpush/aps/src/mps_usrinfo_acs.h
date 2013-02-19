#ifndef __MPS_USRINFO_ACS_H__
#define __MPS_USRINFO_ACS_H__

#include <sys/types.h>

#include "mps_pkg.h"
#include "hj_rbtree.h"

// 接入端存储的用户信息结构信息
typedef struct _STRU_USERINFO_ACS
{
    // 用于RB树的连接，用于按用户Id索引
    struct HJ_RB_node rbNode;

    // 用户Id
    UINT64 u64UsrId;
    // 业务Id
    UINT16 u16SvcId;
    // 通用属性
    UINT32 u32CommAttr;
    // 业务私有属性
    char chPrivateAttr[PRIVATE_ATTR_SIZE];
    // 用户连接SocketId
    unsigned short usCommSocket;

    // 指向同Id同业务Id不同连接socket的用户（解决重复用户登陆情形）
    struct _STRU_USERINFO_ACS *pNext;
} STRU_USERINFO_ACS;

STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId);
STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket);
int Insert_Userinfo(struct HJ_RB_root *pRoot, STRU_USERINFO_ACS *pNewUserinfo
    , unsigned short usSocket);
STRU_USERINFO_ACS* Remove_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket);

#endif
