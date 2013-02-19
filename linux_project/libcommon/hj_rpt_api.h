#ifndef __HJ_RPT_API_H__
#define __HJ_RPT_API_H__

// 上报代理数据所存的共享内存Key
#define RPT_SHM_KEY 51234
// 当前上报代理可以支持的最大上报项种数
#define MAX_ATTR_ITEM_CNT 1000
// 当前上报代理版本号
#define RPT_API_VERSION 0x0101

#pragma pack(1)

typedef struct
{
    unsigned char byIsUse;
    unsigned long ulRptId;
    unsigned long ulCurValue;
} STRU_RPT_NODE;

typedef struct
{
    STRU_RPT_NODE stRptNodeArr[MAX_ATTR_ITEM_CNT];
} STRU_RPT_LIST;

#pragma pack()

/****************************************************************************
* 功能：获取上报代理API的版本号
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
unsigned short HJ_Rpt_GetVer();

/****************************************************************************
* 功能：累计上报相应ID的计数，上报的计数将会累加
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Rpt_API(unsigned long ulRptId, unsigned long ulValue);

/****************************************************************************
* 功能：全量上报相应ID的计数，上报的计数将会更新为最新值
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Rpt_API_Set(unsigned long ulRptId, unsigned long ulValue);

/****************************************************************************
* 功能：获取某上报ID的最新计数
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_Get_Rpt_Value(unsigned long ulRptId, unsigned long &ulValue);

#endif
