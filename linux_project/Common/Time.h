#ifndef _TIME_H_
#define _TIME_H_

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "include.h"

class CTimeBase
{
public:
	static uint64 get_current_time(void);
	static uint64 escape_time(uint64 last_time);

	//获取当前时间 2009-12-02 12:02:30:234
	static string get_now(void);
};

#endif //_TIME_H_




