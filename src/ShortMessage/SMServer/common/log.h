#ifndef _LOG_H_
#define _LOG_H_

#include "..\..\common\defines.h"
#define LOG "c:/log.txt"

class log
{
public:
	log(){}
	~log(){}
	static void printlog(const char* strlog, bool flag = false)
	{
		//check file exceit or not
		//ofstream out(LOG, ios::app | ios::out | ios::binary);
		//out<<currenttime()<<"---->"<<strlog<<endl;
		//out.close();
		TRACE("%s--->%s\n", currenttime().c_str(), strlog);
	}

	static string currenttime(void)
	{
		string strCurrentTime = "";
		struct tm *ptm = NULL;
		time_t tme;
		tme = time(NULL);
		ptm = localtime(&tme);
		char szTime[256];
		memset(szTime, 0, 256);
		sprintf(szTime, "%d-%02d-%02d %02d:%02d:%02d", (ptm->tm_year + 1900),
			ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
		strCurrentTime = szTime;
		return strCurrentTime;
	}

private:
};
#endif _LOG_H_