#ifndef _THREAD_H_
#define _THREAD_H_
#include <process.h>

typedef unsigned (WINAPI *PTHREADFUN)(LPVOID lpParameter);
#define THREAD_RETURN WM_USER + 1000

class CThread 
{ 
public: 
	CThread(void):m_hThread(NULL),m_dwThreadID(0) {} 
	 ~CThread(void) {}

	bool Start(void); 
	int WaitForEnd(DWORD dwTimeOut = INFINITE); 
	virtual DWORD WINAPI ThreadWorkItem(void *parameter) = 0; 
	void Stop(void);

private: 
	static DWORD WINAPI ThreadFun(LPVOID lpParameter); 
	HANDLE m_hThread; 
	DWORD m_dwThreadID; 
}; 

inline bool CThread::Start(void) 
{ 
	m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, NULL, (PTHREADFUN) ThreadFun, this, 0, (unsigned*) &m_dwThreadID)); 
	if (m_hThread == NULL) 
	{ 
		return false; 
	} 
	return true;
} 

inline void CThread::Stop(void)
{
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

inline DWORD WINAPI CThread::ThreadFun(LPVOID lpParameter) 
{ 
	CThread *pThread = reinterpret_cast<CThread*> (lpParameter); 
	pThread->ThreadWorkItem(lpParameter); 
	return 0; 
} 

inline int CThread::WaitForEnd(DWORD dwTimeOut /* = INFINITE */) 
{ 
	DWORD dwRet = WaitForSingleObject(m_hThread, dwTimeOut); 
	if (dwRet == WAIT_OBJECT_0) 
	{ 
		return 0;
	} 
	else if (dwRet == WAIT_TIMEOUT) 
	{ 
		PostThreadMessage(m_dwThreadID, THREAD_RETURN, 0, 0);
		return 1;
	}
	return -1;
}
#endif //_THREAD_H_