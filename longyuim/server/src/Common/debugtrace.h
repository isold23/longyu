/***********************************************************
版权声明：	Copyright (C) 2003 - LongMaster Co.Ltd
文 件 名：	DebugTrace.h
创 建 人：	张宏涛
创建日期：	2003-09-15
说    明：	用于程序调试的日志输出
版 本 号：	0.0003

张亚伟	2006-11-13 修改
目的是适应跨平台应用
***********************************************************/

#ifndef DEF_SINA_DEBUGTRACE_HEAD_
#define DEF_SINA_DEBUGTRACE_HEAD_

#define SINA_UC_INFORMATION_OUTPUT		//定义输出日志的标记
#define DEF_MAX_BUFF_LEN 2048			//定义每行日志最大缓冲长度

//zyw 2007-4-19	外网测试需要时时输出日志
#ifdef _DEBUG
#define LOG_OUTPUT_TO_FILE_DIRECT 		//在调试状态直接输出到文件
#endif //_DEBUG

#ifdef WIN32
#include <windows.h>
#else
#include <stdarg.h>
#endif

#include <sstream>
#include <string>
using namespace std;

#include "CriticalSection.h"
#include "sigslot.h"
class CDebugTrace;
extern CDebugTrace	*goDebugTrace;       //打印日志的DebugTrace对象
//////////////////////////////////////////////////////////////////////
//有关ASSERT的定义

#undef ASSERT		//取消ASSERT宏

//  重新定义ASSERT宏  
#ifdef _DEBUG		//调试版本使用此宏
#define ASSERT(f)               \
	if(f)							\
	;							\
	else                            \
	goDebugTrace->AssertFail(#f,__FILE__, __LINE__)
#else			
#define ASSERT(f)
#endif//_DEBUG


//////////////////////////////////////////////////////////////////////
//有关TRACE的定义
#define SET_TRACE_LEVEL		goDebugTrace->SetTraceLevel
#define SET_LOG_FILENAME	goDebugTrace->SetLogFileName
 #define SET_TRACE_OPTIONS	goDebugTrace->SetTraceOptions
#define GET_TRACE_OPTIONS	goDebugTrace->GetTraceOptions

//取消TRACE定义
#undef TRACE

//重新定义TRACE语句
//记录日志:如果级别足够高才打印日志,否则不打
#ifdef SINA_UC_INFORMATION_OUTPUT			
#define TRACE(level, args) \
	if (!goDebugTrace->CanTrace(level)) 	;  else\
	{\
		goDebugTrace->Lock();\
		try\
		{\
			(goDebugTrace->BeginTrace(level,__FILE__,__LINE__) << args << '\n').EndTrace();\
		}\
		catch (...)\
		{\
		}\
		goDebugTrace->UnLock();\
	}


		

#else					//发行版
#define TRACE ;
#endif //SINA_UC_INFORMATION_OUTPUT

//////////////////////////////////////////////////////////////////////
//针对指定的用户进行追踪
extern int64	gi64TraceUserId;	//追踪的用户ID

#define SET_TRACE_USER_ID(userid)  (gi64TraceUserId=(userid));\
{\
	goDebugTrace->Lock();\
	try\
	{\
		(goDebugTrace->BeginTrace(0,__FILE__,__LINE__) << "更改追踪的用户ID:" << userid << '\n').EndTrace();\
	}\
	catch (...)\
	{\
	}\
	goDebugTrace->UnLock();\
}

#define TraceUserEvent(userid, args) \
{\
	goDebugTrace->Lock();\
	try\
	{\
		if ((userid) == gi64TraceUserId)\
		(goDebugTrace->BeginTrace(0,__FILE__,__LINE__) << args << '\n').EndTrace();\
	}\
	catch (...)\
	{\
	}\
	goDebugTrace->UnLock();\
}



//////////////////////////////////////////////////////////////////////
//日志实现类声明
typedef CDebugTrace& (* DebugTraceFunc)(CDebugTrace &aoDebugTrace);

class CDebugTrace
{
public:
	char		mszPrintBuff[DEF_MAX_BUFF_LEN+1];	 //打印数据缓存
	int		mlDataLen;			 //数据长度
	int			mnLogLevel;			 //日志等级
	char		mszLogFileName[512]; //日志文件名称
	//日志文件前缀
	char mszLogFileNamePre[450];
	unsigned    muTraceOptions;		 //打印日志选项	

	CCriticalSection moCriticalSection;     //打印日志同步临界区
	struct timeb moSystemTime;				//某次会话的时间
	int	 miLogLevel;						//某次会话的日志等级
	//日志文件最大字节
	unsigned int muiLogFileSize;

public:
	//打印选项
	enum Options 
	{
		/// 打印时间
		Timestamp = 1,
		/// 打印日志级别
		LogLevel = 2,
		/// 打印源文件名和行号
		FileAndLine = 4,
		/// 把日志追加到文件中
		AppendToFile = 8,
		///输出日志到控制台
		PrintToConsole = 16
	};    	

public:
	//构造函数	
	CDebugTrace(unsigned asTraceOptions = Timestamp | AppendToFile);
	//析够函数
	~CDebugTrace();
public:
	//设置日志级别(0级最高,1其次,依次类推,小于该等级的日志不打印)
	void SetTraceLevel(int aiTraceLevel);

	//设置日志文件最大字节数
	void SetLogFileSize(unsigned int aiSize);

	//设置日志文件名
	void SetLogFileName(char *aszLogFile);

	// 设置TRACE选项 .注意函数可以 OR 各选项
	void SetTraceOptions(unsigned options /** New level for trace */ );

	//取得TRACE选项
	unsigned GetTraceOptions(void);

	//判断给定级别是否可以打印
	bool CanTrace(int aiLogLevel);					

	//开始打印
	CDebugTrace& BeginTrace(int aiLogLevel,char *apSrcFile,int aiSrcLine);	

	//结束打印
	void EndTrace();

	//断言失败处理函数
	void AssertFail(char * strCond,char *strFile, unsigned uLine);

	//按照函数printf的类似格式打印日志
	void TraceFormat(const char * pFmt,...);	

	//打印当前堆栈
	void TraceStack(void);

	//结束输出
	CDebugTrace& endl(CDebugTrace& _outs);

	template <class T>
	inline CDebugTrace& operator<<(T value)
	{
		stringstream str;
		str<<value;
		string ss = "";
		ss = str.str();
		if (mlDataLen < DEF_MAX_BUFF_LEN - (int)ss.length())
		{
			memcpy((void*)(mszPrintBuff + mlDataLen), ss.c_str(), ss.length());
			mlDataLen += ss.length();
		}
		return *this;
	}

	//以下分别输出各种数据类型
	CDebugTrace& operator << (unsigned char acCharVal);
	CDebugTrace& operator << (bool abBoolVal);

#ifndef x86_64
	CDebugTrace& operator << (int64 aiInt64Val);
#endif
	CDebugTrace& operator << (const char *apStrVal);	
	CDebugTrace& operator << (DebugTraceFunc _f) { (*_f)(*this); return *this; }	

	//输出和清空临时缓冲区
	int Flush();
	void Lock()
	{
		 moCriticalSection.Enter();
	}
	void UnLock()
	{
		moCriticalSection.Leave();
	}

private:
	unsigned int GetFileSize( FILE *fp )
	{
		unsigned int cur_pos = 0;
		unsigned int len = 0;
		cur_pos = ftell( fp );
		//将文件流的读取位置设为文件末尾
		fseek( fp, 0, SEEK_END );
		//获取文件末尾的读取位置,即文件大小
		len = ftell( fp );
		//将文件流的读取位置还原为原先的值
		fseek( fp, cur_pos, SEEK_SET );
		return len;
	}


#ifndef LOG_OUTPUT_TO_FILE_DIRECT
	enum{ LOG_BUFFER_LEN = 1024 * 512 };

private:
	char	macMark[20];
	//已经使用的缓冲区长度
	int    mlBufDataLen;
	//缓冲区
	char    mszLogBuffer[ LOG_BUFFER_LEN + 1 ];
private:
	//将数据添加到临时缓冲区
	bool    AddToLogBuffer();
#endif
};


#endif	//DEF_SINA_DEBUGTRACE_HEAD_
