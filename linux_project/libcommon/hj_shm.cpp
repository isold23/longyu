/*! @hj_shm.cpp
*******************************************************************************
</PRE>
模块名       ：共享内存操作相关库函数定义
文件名       ：hj_shm.cpp
相关文件     ：hj_shm.h
文件实现功能 ：共享内存操作相关库函数定义
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
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "hj_shm.h"

/****************************************************************************
* 功能：初始化共享内存
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
char* HJ_GetShm(int iKey, int iSize, int iFlag)
{
    int iShmID = shmget(iKey, iSize, iFlag);
    if (iShmID < 0)
    {
        char szErrMsg[64];
        snprintf(szErrMsg, sizeof(szErrMsg), "shmget key(%d) size(%d)"
            , iKey, iSize);
        perror(szErrMsg);
        return NULL;
    }

    char *pShm = (char*)shmat(iShmID, NULL, 0);
    if (pShm == (char*)-1)
    {
        perror("shmat");
        return NULL;
    }

    return pShm;
}

/****************************************************************************
* 功能：初始化共享内存，如果是第一次创建则做清零初始化
* 返回值：-1-创建失败，0-创建成功
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_GetShm_Zero(char **ppShm, int iShmID, int iSize, int iFlag)
{
    assert(ppShm);

    *ppShm = NULL;
    char *pShm = HJ_GetShm(iShmID, iSize, iFlag & (~IPC_CREAT));
    if (!pShm)
    {
        if (!(iFlag & IPC_CREAT))
        {
            return -1;
        }

        pShm = HJ_GetShm(iShmID, iSize, iFlag);
        if (!pShm)
        {
            return -1;
        }

        bzero(pShm, iSize);
    }

    *ppShm = pShm;
    return 0;
}

/****************************************************************************
* 功能：初始化共享内存，但不做首次创建时初始化操作
* 返回值：-1-创建失败，0-创建成功，1-首次创建
* 作者：Huangjun
* 日期：2008-09-22
***************************************************************************/
int HJ_GetShm_NZero(char **ppShm, int iShmID, int iSize, int iFlag)
{
    assert(ppShm);

    *ppShm = NULL;
    char *pShm = HJ_GetShm(iShmID, iSize, iFlag & (~IPC_CREAT));
    if (!pShm)
    {
        if (!(iFlag & IPC_CREAT))
        {
            return -1;
        }

        pShm = HJ_GetShm(iShmID, iSize, iFlag);
        if (!pShm)
        {
            return -1;
        }

        *ppShm =pShm;
        return 1;
    }

    *ppShm = pShm;
    return 0;
}
