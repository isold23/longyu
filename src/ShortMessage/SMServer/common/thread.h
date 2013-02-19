#ifndef _THREAD_H_
#define _THREAD_H_
#include "..\..\common\defines.h"
#include "process.h"

typedef unsigned (WINAPI *PTHREADFUNC)(LPVOID lpThreadParameter);

class CThreadBase
{
public:
	CThreadBase(void):m_hThread(NULL), m_nThreadId(0) {}
	~CThreadBase(void) {}

	bool Start(void);
	bool WaitForEnd(int nTime = 1000);
	static DWORD WINAPI ThreadFun(LPVOID param);
	virtual DWORD WorkItem(LPVOID param) = 0;

protected:
	HANDLE m_hThread;
	int m_nThreadId;
};

__inline bool CThreadBase::Start(void)
{
	assert(m_hThread == NULL);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, 
		(PTHREADFUNC)ThreadFun, (LPVOID)this, 0, (unsigned int*)&m_nThreadId);
	if (m_hThread == NULL)
		return false;
	return true;
}

__inline DWORD WINAPI CThreadBase::ThreadFun(LPVOID param)
{
	CThreadBase *p = (CThreadBase*)param;
	p->WorkItem(param);
	return 0;
}

__inline bool CThreadBase::WaitForEnd(int nTime)
{
	if (NULL != m_hThread)
	{
		if(WaitForSingleObject(m_hThread, nTime) == WAIT_OBJECT_0)
		{
			CloseHandle(m_hThread);
			m_hThread = NULL;
			m_nThreadId = 0;
		}
	}
	return true;
}
#endif //_THREAD_H_