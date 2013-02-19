/********************************************************************
	created:	2009/09/19
	created:	19:9:2009   7:54
	filename: 	TaskProcessor.cpp
	file path:	TaskProcessor\src
	file base:	TaskProcessor
	file ext:	cpp
	author:		wangzeyu
	purpose:	
*********************************************************************/

#include "include.h"
#include "TaskProcessorConfig.h"
#include "TaskProcessor.h"
#include "TaskProcess.h"
#include "FileStream.h"
#include "debugtrace.h"

const string gstrTaskProcessorVersion = "1.0.0.1";

int main(int argc, char* argv[])
{
	//设置初始时日志输出级别和选项
	SET_TRACE_LEVEL(5);
	unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel\
		& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile\
		| CDebugTrace::PrintToConsole);

	//设置日志选项和日志文件名
	SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

	char lszLogFileName[255];
	CFileStream::GetAppPath(lszLogFileName,255);	
	strcpy(strrchr(lszLogFileName,'/'),"//TaskProcessor_log"); //增加"log"路径
	CFileStream::CreatePath(lszLogFileName);

	//生成TRACE文件名
	char lszFileDate[30] = "";
	time_t loSystemTime;
	time(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime);
	sprintf(lszFileDate, "//TaskProcessor%4d%02d%02d%02d%02d.log",\
		1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, lptm->tm_hour, lptm->tm_min);

	strcat(lszLogFileName,lszFileDate);
	SET_LOG_FILENAME(lszLogFileName);

	TRACE(1,"\n\n*******************TaskProcessor调试日志VERSION:" 
		<<gstrTaskProcessorVersion.c_str() << "*******************");

	CTaskProcessorConfig loConfig;
	loConfig.set_conf_file_name("TaskProcessor.conf");
	loConfig.load();

	CTaskProcess loProcess;

	CTaskProcessor loTaskProcessor;
	loTaskProcessor.SetConfigInfo(&loConfig);
	loTaskProcessor.SetDealDataPtr(&loProcess);
	loTaskProcessor.Run();
	return 0;
}


