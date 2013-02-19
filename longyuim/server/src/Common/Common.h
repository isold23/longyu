#ifndef _COMMON_H_
#define _COMMON_H_

#include <sys/time.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <execinfo.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

#include "define.h"
#include "debugtrace.h"

class CCommon
{
public:
	static uint32 GetProcessId();
	static uint32 GetProcessParentId();
	static void SetOpenFiles(uint32 max_file_opens_number);
	static void GetAppPath(char* apPath, int aiLen);
	static void CreatePath(char* apPath);
	static uint64 get_current_time(void);
	static uint64 escape_time(uint64 last_time);

	//获取当前时间 2009-12-02 12:02:30:234
	static string get_now(void);
	//检测是否超时
	static bool CheckTimeOut(const INT64 &ai64LastTime,const INT64 &ai64TimeInterval);
	
	//根据IP地址和包序号计算主键
	static INT64 MakeIpPortKey(const sockaddr_in& addr, const uint16_t awPackSerial);
	static unsigned int GetSocketAddr(const sockaddr_in& addr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr, unsigned short alPort);
	static char* GetIPAddr(unsigned int alAddr);
	static char* Getctime(time_t *apTime);
	//封装输出调用堆栈的功能
	static void DumpStack();
};

#endif //_COMMON_H_

