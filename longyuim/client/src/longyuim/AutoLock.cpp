#include "stdafx.h"
#include "AutoLock.h"

namespace _LONGYU_COMMON
{
	CCriticalSection::CCriticalSection()
	{
		InitializeCriticalSection(&moSection);
	}
	//析构函数
	CCriticalSection::~CCriticalSection()
	{
		DeleteCriticalSection(&moSection);
	}
	//进入临界区
	void CCriticalSection::Enter()
	{
		EnterCriticalSection(&moSection);
	}
	//离开临界区
	void CCriticalSection::Leave()
	{
		LeaveCriticalSection(&moSection);
	}

	//构造函数
	CAutoLock::CAutoLock(CCriticalSection& aoSection):moSection(aoSection)
	{
		moSection.Enter();
	}

	//析构函数
	CAutoLock::~CAutoLock()
	{
		moSection.Leave();
	}

};//end _LONGYU_COMMON