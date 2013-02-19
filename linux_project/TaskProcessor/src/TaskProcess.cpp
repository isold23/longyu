/********************************************************************
	created:	2009/09/21
	created:	21:9:2009   11:11
	filename: 	\TaskProcessor\src\TaskProcess.cpp
	file path:	\TaskProcessor\src
	file base:	TaskProcess
	file ext:	cpp
	author:		isold
	
	purpose:	
*********************************************************************/
#include <sstream>
#include <string>
using namespace std;
#include "TaskProcess.h"

CTaskProcess::CTaskProcess()
{

}

CTaskProcess::~CTaskProcess()
{


}

void CTaskProcess::TaskProcessFun(const char *buffer, const int length, char *rtn, int &rtn_len)
{
	try
	{
		int pid = getpid();
		TRACE(1, "server pid = "<<pid<<" server length = "<<length<<" buffer = "<<buffer);
		stringstream str;
		str<<pid<<ends;
		string strPid = str.str();
		memcpy(rtn, strPid.c_str(), strPid.length());
		rtn_len = strPid.length();
		//CNetPackLogin loLogin;
		//loLogin.Unpack((char*)buffer, length);
		//TRACE(1, "CTaskProcess::TaskProcessFun login id = "<<loLogin.miId);
		//
		//CNetPackLogout loLogout;
		//loLogout.miId = loLogin.miId;
		//int liSendLen = 3000;
		//int nRet = loLogout.Pack(rtn, liSendLen);
		//rtn_len = nRet;
	}
	catch (...)
	{
		
	}
}




