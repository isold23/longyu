/*! @hj_log.h
*******************************************************************************
</PRE>
模块名       ：写日志相关库函数申明
文件名       ：hj_log.h
相关文件     ：hj_log.cpp
文件实现功能 ：写日志相关库函数申明
作者         ：huangjun - 神州星国际
版本         ：1.0.1
-------------------------------------------------------------------------------
备注：
-------------------------------------------------------------------------------
修改记录：
日期        版本        修改人      修改内容
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/

#ifndef __HJ_LOG_H__
#define __HJ_LOG_H__

#include <stdio.h>
#include <assert.h>

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif
#include <time.h>

typedef struct
{
    FILE    *pLogFile;
    char    sBaseFileName[80];
    char    sLogFileName[80];

    int     iMaxLogNum;
    long    lMaxSize;
    // long    lMaxCount;
    long    lLogCount;
    time_t  lCurTimeBase;
    time_t  lLastFlush;
} stLogFile;

class CHJ_Log
{
public:
    CHJ_Log();
    virtual ~CHJ_Log();
    long InitLogFile(char *sLogBaseName, long iMaxLogNum, long iMAX);
    int Log(char *sFormat, ...);
private:
    int ShiftFiles();
    time_t GetCurTimeBase();
    stLogFile m_Logfile;
};

#endif
