#include "stdafx.h"
#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")
 

static LONG WINAPI CrashHandlerExceptionFilter(EXCEPTION_POINTERS* pExPtrs)
{
	TCHAR szFilePath[MAX_PATH];
	::GetModuleFileName(NULL,szFilePath,MAX_PATH);
	*_tcsrchr(szFilePath,'.') = _T('\0');

	SYSTEMTIME t;
	::GetLocalTime(&t);

	TCHAR szDumpFile[MAX_PATH];
	wsprintf(szDumpFile,_T("%s.%d_%d_%d-%d_%d_%d_%d.dmp"),szFilePath,
		(int)t.wYear,(int)t.wMonth,(int)t.wDay,(int)t.wHour,
		(int)t.wMinute,(int)t.wSecond,(int)t.wMilliseconds);
	HANDLE hFile = CreateFile(szDumpFile, GENERIC_READ|GENERIC_WRITE,
		0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION eInfo;
		eInfo.ThreadId = GetCurrentThreadId();  
		eInfo.ExceptionPointers = pExPtrs;
		eInfo.ClientPointers = FALSE;

		MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hFile,MiniDumpNormal,
			pExPtrs ? &eInfo : NULL,
			NULL,NULL);
		CloseHandle(hFile);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void InstallCrashGenerator(void)
{
	SetUnhandledExceptionFilter(CrashHandlerExceptionFilter); 
}
