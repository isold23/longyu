#ifndef _LOG_H_
#define _LOG_H_
#include <string>
#include <strstream>
#include <fstream>
using namespace std;

#define NEED_LOG

class log
{
public:
	log(void){}
	~log(void){}

	static void printlog(const char* log)
	{
		ofstream out("c:\\downloadfile_wangliwei.log", ios::out | ios::binary | ios::app);
		out.write(log, static_cast<std::streamsize>(strlen(log)));
		out.write("\n", 1);
		out.close();
	}
	static void printlog(const std::string &log)
	{
		ofstream out("c:\\downloadfile_wangliwei.log", ios::out | ios::binary | ios::app);
		out.write(log.c_str(), static_cast<std::streamsize>(log.length()));
		out.write("\n", 1);
		out.close();
	}
	static void printlog(std::strstream &log)
	{
		ofstream out("c:\\downloadfile_wangliwei.log", ios::out | ios::binary | ios::app);
		out.write(log.str(), static_cast<std::streamsize>(log.pcount()));
		out.write("\n", 1);
		out.close();
	}
};

#endif //_LOG_H_