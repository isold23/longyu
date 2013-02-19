// TCPMessager.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "TCPManager.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

CTCPManager* gpTCPManager = NULL;
extern "C" ITCPMessager *__stdcall GetTCPInstance()
{
	if(gpTCPManager == NULL)
	{
		gpTCPManager = new CTCPManager();
	}
	return gpTCPManager;
}