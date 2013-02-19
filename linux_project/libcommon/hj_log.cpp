/*! @hj_log.cpp
*******************************************************************************
</PRE>
模块名       ：写日志相关库函数定义
文件名       ：hj_log.cpp
相关文件     ：hj_log.h
文件实现功能 ：写日志相关库函数定义
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

#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>

#include "hj_string.h"
#include "hj_log.h"

time_t CHJ_Log::GetCurTimeBase()
{
    time_t tm_temp = time(NULL);
    struct tm stru_now = *localtime(&tm_temp);
    stru_now.tm_hour = stru_now.tm_min = stru_now.tm_sec = 0; // 置时间为今天0点0时0秒
    tm_temp = mktime(&stru_now);

    return tm_temp;
}

CHJ_Log::CHJ_Log()
{
    bzero(&m_Logfile, sizeof(m_Logfile));
}

CHJ_Log::~CHJ_Log()
{
    if (m_Logfile.pLogFile != NULL)
    {
        fclose(m_Logfile.pLogFile);
        m_Logfile.pLogFile = NULL;
    }
}

long CHJ_Log::InitLogFile(char *sLogBaseName, long iMaxLogNum, long iMAX)
{
    assert(sLogBaseName);

    char sLogFileName[80], sCurDate[16];

    if (m_Logfile.pLogFile)
    {
        fclose(m_Logfile.pLogFile);
        m_Logfile.pLogFile = NULL;
    }

    snprintf(sLogFileName, sizeof(sLogFileName), "%s_%s.log"
        , sLogBaseName, HJ_GetCurDateShortStr(sCurDate, sizeof(sCurDate)));

    /*
    if ((m_Logfile.pLogFile = fopen(sLogFileName, "a+")) == NULL)
    {
        return -1;
    }
    */
    m_Logfile.pLogFile = NULL;
    snprintf(m_Logfile.sLogFileName, sizeof(m_Logfile.sLogFileName), "%s", sLogFileName);
    snprintf(m_Logfile.sBaseFileName, sizeof(m_Logfile.sBaseFileName), "%s", sLogBaseName);

    m_Logfile.iMaxLogNum = iMaxLogNum;
    m_Logfile.lMaxSize   = iMAX;
    // m_Logfile.lMaxCount  = iMAX;
    m_Logfile.lLogCount  = 0;
    m_Logfile.lCurTimeBase = GetCurTimeBase();
    m_Logfile.lLastFlush = m_Logfile.lCurTimeBase;

    return ShiftFiles();
}

int CHJ_Log::Log(char *sFormat, ...)
{
    assert(sFormat);

    if ((m_Logfile.pLogFile == NULL)
        && ((m_Logfile.pLogFile = fopen(m_Logfile.sLogFileName, "a+")) == NULL))
    {
        return -1;
    }

    va_list ap;
    va_start(ap, sFormat);

    struct timeval stLogTv;
    gettimeofday(&stLogTv, NULL);

    char szLogBuf[1024];

    char szCurDateTime[30];
    HJ_GetCurDateTimeStr(szCurDateTime, sizeof(szCurDateTime));

    snprintf(szLogBuf, sizeof(szLogBuf), "[%s.%.6ld] "
        , szCurDateTime, stLogTv.tv_usec);

    size_t s_len = strlen(szLogBuf);
    vsnprintf((szLogBuf + s_len), (sizeof(szLogBuf) - s_len - 1), sFormat, ap);

    s_len += strlen(szLogBuf + s_len);
    szLogBuf[s_len++] = '\n';

    va_end(ap);

    fwrite(szLogBuf, 1, s_len, m_Logfile.pLogFile);

    time_t tm_now = time(NULL);
    if ((abs(tm_now - m_Logfile.lLastFlush) > 3)
        || (++m_Logfile.lLogCount > 300))
    {
        /*
        fflush(m_Logfile.pLogFile);
        m_Logfile.lLastFlush = tm_now;
        m_Logfile.lLogCount = 0;
        */
        fclose(m_Logfile.pLogFile);
        m_Logfile.pLogFile = NULL;
        m_Logfile.lLogCount = 0;
        m_Logfile.lLastFlush = tm_now;
    }
    return ShiftFiles();
}

int CHJ_Log::ShiftFiles()
{
    bool bNewDay = false;
    time_t tm_CurTimeBase = GetCurTimeBase();

    do 
    {
        if (tm_CurTimeBase != m_Logfile.lCurTimeBase)
        {
            bNewDay = true;
            break;
        }

        struct stat stStat;
        if (stat(m_Logfile.sLogFileName, &stStat) < 0) 
        {
            return -1;
        }
        if (stStat.st_size >= m_Logfile.lMaxSize) 
        {
            break;
        }
        return 0;
    } while (false);

    if (m_Logfile.pLogFile)
    {
        fclose(m_Logfile.pLogFile);
        m_Logfile.pLogFile = NULL;
        m_Logfile.lLogCount = 0;
        m_Logfile.lLastFlush = time(NULL);
    }

    char sTempLogFile[MAXNAMLEN + 1];
    snprintf(sTempLogFile, sizeof(sTempLogFile), "%s", m_Logfile.sLogFileName);
    char *pTemp = strrchr(sTempLogFile, '.');
    if (pTemp)
    {
        *pTemp = '\0';
    }

    char sOldLogFile[MAXNAMLEN + 1], sNewLogFile[MAXNAMLEN + 1];
    for (int i = m_Logfile.iMaxLogNum - 2; i >= 0; i--)
    {
        if (i != 0)
        {
            snprintf(sOldLogFile, sizeof(sOldLogFile), "%s_%d.log", sTempLogFile, i);
        }
        else
        {
            snprintf(sOldLogFile, sizeof(sOldLogFile), "%s.log", sTempLogFile);
        }

        if (access(sOldLogFile, F_OK) != 0)
        {
            continue;
        }

        snprintf(sNewLogFile, sizeof(sNewLogFile), "%s_%d.log", sTempLogFile, i + 1);
        if (rename(sOldLogFile, sNewLogFile) < 0)
        {
            continue;
        }
    }

    if (bNewDay)
    {
        m_Logfile.lCurTimeBase = tm_CurTimeBase;
        char sCurDate[16];
        snprintf(m_Logfile.sLogFileName, sizeof(m_Logfile.sLogFileName)
            , "%s_%s.log", m_Logfile.sBaseFileName
            , HJ_GetCurDateShortStr(sCurDate, sizeof(sCurDate)));
    }

    return 0;
}
