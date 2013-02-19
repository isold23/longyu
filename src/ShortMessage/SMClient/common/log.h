#ifndef _LOG_H_
#define _LOG_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <strstream>
#include <ctime>
#include <fstream>
using namespace std;


//#define LOG "c:/log.txt"

////////////////////////////////////////////////////////////////////////////////////
enum _LOG_LEVEL //LOG级别
{
	_LOG_LEVEL_ERROR = 0,
	_LOG_LEVEL_DEBUG,
	_LOG_LEVEL_RELEASE,
};
////////////////////////////////////////////////////////////////////////////////////
class CTimeBase
{
public:
	static string GetCurrentTime()//获取当前时间
	{
		string strTime = "";
		struct tm *ptm = NULL;
		time_t tme;
		tme = time(NULL);
		ptm = localtime(&tme);
		char szTime[256];
		memset(szTime, 0, 256);
		sprintf(szTime, "%d-%02d-%02d %02d:%02d:%02d", (ptm->tm_year + 1900),
			ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
		strTime = szTime;
		return strTime;
	}
public:
};
////////////////////////////////////////////////////////////////////////////////////
static void __Log(size_t nLogLevel, char *pszFmt, va_list argptr)
{
	assert(pszFmt != NULL);
	assert(strlen(pszFmt) < 1024);

	switch(nLogLevel)
	{
	case _LOG_LEVEL_DEBUG:
		{

			char szLogLine[1000];
			memset(szLogLine, 0, 1000);
			if (_vsntprintf(szLogLine, sizeof(szLogLine), pszFmt, argptr) == -1)
				szLogLine[sizeof(szLogLine) - 1] = _T('\0');
			char szFullLogLine[1024];
			memset(szFullLogLine, 0, 1024);
			int iLen = _sntprintf(&szFullLogLine[0], sizeof(szFullLogLine), 
				_T("%s: %s\r\n"), CTimeBase::GetCurrentTime().c_str(), pszFmt);
			TRACE(szFullLogLine);
			break;
		}
	case _LOG_LEVEL_RELEASE:
		{
			break;
		}
	default:
		{
			break;
		}
	};
}

//调用此函数打印LOG 如：PrintLog(_LOG_LEVEL_DEBUG, _LOG_LEVEL_DEBUG, "%s, %d", "ErrorCode = ", 2000);

static void PrintLog(size_t nLogLevel, char *pszFmt, ...)
{
	assert(pszFmt != NULL);

	va_list argp;
	va_start(argp, pszFmt);
	__Log(nLogLevel, pszFmt, argp);
	va_end(argp);
} 
///////////////////////////////////////////////////////////////////////////////////
#endif _LOG_H_