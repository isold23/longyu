#include <assert.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "hj_rpt_api.h"
#include "hj_shm.h"

static STRU_RPT_LIST *gs_pRptList = NULL;
/****************************************************************************
* 功能：获取上报代理API的版本号
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
unsigned short HJ_Rpt_GetVer()
{
    return RPT_API_VERSION;
}

/****************************************************************************
* 功能：查找相应上报Id所在共享内存中的数组位置索引
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
static int HJ_Rpt_SearchRptId(STRU_RPT_LIST *pstRptLst, unsigned long ulRptId
    , int &nPosIndex)
{
    nPosIndex = 0;

    int index;
    for (index = 0; pstRptLst->stRptNodeArr[index].byIsUse; index++)
    {
        if (pstRptLst->stRptNodeArr[index].ulRptId == ulRptId)
        {
            nPosIndex = index;
            return 1;
        }
    }

    if (index >= MAX_ATTR_ITEM_CNT)
    {
        return -1;
    }
    else
    {
        nPosIndex = index;
        return 0;
    }
}

/****************************************************************************
* 功能：累计上报相应ID的计数，上报的计数将会累加
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Rpt_API(unsigned long ulRptId, unsigned long ulValue)
{
    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (!nRet)
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].byIsUse = 1;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulRptId = ulRptId;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }
    else if (nRet == -1)
    {
        return -2;
    }
    else
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue += ulValue;
    }

    return 0;
}

/****************************************************************************
* 功能：全量上报相应ID的计数，上报的计数将会更新为最新值
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Rpt_API_Set(unsigned long ulRptId, unsigned long ulValue)
{
    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (!nRet)
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].byIsUse = 1;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulRptId = ulRptId;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }
    else if (nRet == -1)
    {
        return -2;
    }
    else
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }

    return 0;
}

/****************************************************************************
* 功能：获取某上报ID的最新计数
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Get_Rpt_Value(unsigned long ulRptId, unsigned long &ulValue)
{
    ulValue = 0;

    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (nRet > 0)
    {
        ulValue = gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue;
        return 0;
    }
    else
    {
        return -2;
    }
}
