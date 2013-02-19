/********************************************************************
	created:	2009/09/21
	created:	21:9:2009   16:41
	filename: 	\Test\TaskProcessorTest.cpp
	file path:	\TaskProcessor\Test
	file base:	TaskProcessorTest
	file ext:	cpp
	author:		isold
	
	purpose:	
*********************************************************************/
#include <iostream>
using namespace std;

#include "include.h"
#include "NetPack.h"
#include "NetSocket.h"
#include "FileStream.h"
#include "debugtrace.h"
#include "../src/TaskProcessorConfig.h"

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
	strcpy(strrchr(lszLogFileName,'/'),"//TaskProcessorTest_log"); //增加"log"路径
	CFileStream::CreatePath(lszLogFileName);

	//生成TRACE文件名
	char lszFileDate[30] = "";
	time_t loSystemTime;
	time(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime);
	sprintf(lszFileDate, "//TaskProcessorTest%4d%02d%02d%02d%02d.log",\
		1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, lptm->tm_hour, lptm->tm_min);

	strcat(lszLogFileName,lszFileDate);
	SET_LOG_FILENAME(lszLogFileName);

	TRACE(1,"\n\n*******************TaskProcessorTest调试日志VERSION:" 
		<<gstrTaskProcessorVersion.c_str() << "*******************");

	CTaskProcessorConfig loConfig;
	loConfig.set_conf_file_name("TaskProcessor.conf");
	loConfig.load();

	CNetSocket moHallTrans;
	bool lbCreate = false;
	lbCreate = moHallTrans.CreateSocket(NULL, 9000);
	if(!lbCreate)
	{
		cout<<"create socket error"<<endl;
		return 0;
	}

	int liConnectCount = 0;

	while(moHallTrans.moNetStat != TCP_CONNECTED)
	{
		struct sockaddr_in addr;
		addr.sin_addr.s_addr = loConfig.tps_ip;
		bool lbConnet = moHallTrans.ConnectServer(inet_ntoa(addr.sin_addr), loConfig.tps_port);
		if(lbConnet)
		{
			moHallTrans.moNetStat = TCP_CONNECTED;
		}
		else
		{
			if(++liConnectCount >= 100)
			{
				moHallTrans.Close();
				cout<<"连接服务器失败。"<<endl;
				return 0;
			}
			else
			{
				usleep(1000*1000*3);
				continue;
			}
		}
	}

	moHallTrans.SetNoBlock();

	//CNetPackLogin loLogin;
	//loLogin.miId = 1000;
	//char *lpSendBuffer = new char[DEF_BUFFER_LEN];
	//memset(lpSendBuffer, 0, DEF_BUFFER_LEN);
	//int liSendLen = DEF_BUFFER_LEN;
	//int nRet = loLogin.Pack(lpSendBuffer, liSendLen);
	string str = "1000";
	moHallTrans.SendData(str.c_str(), str.length());
	//cout<<"SendLogint = "<<1000<<endl;
	//delete [] lpSendBuffer;
	//lpSendBuffer = NULL;

	for(;;)
	{
		moHallTrans.SendData();
		if(!moHallTrans.RecvData())
		{
			cout<<"recv data error"<<endl;
			break;
		}
		char buffer[DEF_BUFFER_LEN];
		memset(buffer, 0, DEF_BUFFER_LEN);
		int length = 0;
		bool bRecvData = moHallTrans.RecvData(buffer, length);
		bool lbProcessExit = false;
		if(bRecvData)
		{
			cout<<"client length = "<<length<<" buffer = "<<buffer<<endl;
			//CNetPackLogout loLogout;
			//loLogout.Unpack(buffer, length);
			//cout<<"RecvLogout = "<<loLogout.miId<<endl;
			break;
		}
	}
	moHallTrans.Close();
	return 0;
}