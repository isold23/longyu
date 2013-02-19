
#include "DNSWorker.h"

//日志对象
CDebugTrace *goDebugTrace = NULL;

void help_info()
{
	cout<<"SinaShow Dispatch Node Server Help Infomation:"<<endl;
	cout<<"./dns -f config_file_name(运行程序)"<<endl;
	cout<<"./dns -v(查看程序版本)"<<endl;
	cout<<"./dns -h(查看帮助信息)"<<endl;
	cout<<"Copyright (C) Beijing Sina Information Technology Co.,Ltd 2009-2010"<<endl;
};

int main(int argc, char* argv[])
{
	if(argc > 1 && strcmp(argv[1], "-v") == 0)
	{
		cout<<"SinaShow DNS Version Infomation:"<<endl;
		cout<<"CrsTrans Version: "<<gstrDNSWorkerVersion.c_str()<<endl;
		cout<<"Copyright (C) Beijing Sina Information Technology Co.,Ltd 2003-2009"<<endl;
		return 0;
	}

	if(argc > 1 && strcmp(argv[1], "-h") == 0)
	{
		help_info();
		return 0;
	}

	if(argc > 1 && strcmp(argv[1], "-f") != 0)
	{
		help_info();
		return 0;
	}

	string lstrConfigName = "";
	if(argc > 1 && strcmp(argv[1], "-f") == 0)
	{
		lstrConfigName = argv[2];
		if(lstrConfigName.empty())
		{
			help_info();
			return 0;
		}
	}

	char lszLogFileName[255];
	memset(lszLogFileName, 0, 255);
	CFileStream::GetAppPath(lszLogFileName,255);

	string lstrAppPath = lszLogFileName;
	string lstrApp = lstrAppPath.substr(0, lstrAppPath.find_last_of('/'));
	if (chdir(lstrApp.c_str()))
	{
		cout<<"crs_trans error: chdir error."<<lszLogFileName<<endl;
		return 0;
	}

	goDebugTrace = new CDebugTrace;

	unsigned int process_id = CCommon::GetProcessId();

	//设置日志文件信息
	SET_TRACE_LEVEL(5);
	unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel
		& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile);
	SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

	strcpy(strrchr(lszLogFileName,'/'),"//DNS_log");
	CFileStream::CreatePath(lszLogFileName);
	char lszFileDate[50];
	memset(lszFileDate, 0, 50);
	sprintf(lszFileDate, "//DNS-%u", process_id);
	strcat(lszLogFileName,lszFileDate);
	SET_LOG_FILENAME(lszLogFileName);
	TRACE(1,"\n\n*******************DNS调试日志VERSION:" <<
		gstrDNSWorkerVersion.c_str() << "*******************");

	TRACE(1, "配置文件信息: "<<lstrConfigName.c_str());

	//加载配置文件
	CDNSConfig loDNSConfig;
	loDNSConfig.set_conf_file_name(lstrConfigName.c_str());
	bool bRet = loDNSConfig.load();
	if(!bRet)
	{
		TRACE(1, "ERROR: 加载配置文件失败。");
		return 0;
	}

	CDNSWorker worker;
	worker.SetConfig(&loDNSConfig);
	worker.Run();

	return 0;
}












