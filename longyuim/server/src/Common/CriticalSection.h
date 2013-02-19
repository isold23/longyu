

#ifndef _CRITICAL_SECTION_H_
#define _CRITICAL_SECTION_H_

#ifdef WIN32

#else
#include <pthread.h>
#include <sys/time.h>
#include <errno.h> 
#endif
#include "define.h"

class CCriticalSection
{
public:
	CCriticalSection();
	~CCriticalSection();

	//进入临界区
	inline void Enter()
	{
#ifdef WIN32
		EnterCriticalSection(&moSection);
#else
		pthread_mutex_lock(&mMutex);
#endif
	}
	//离开临界区
	inline void Leave()
	{
#ifdef WIN32
		LeaveCriticalSection(&moSection);
#else
		pthread_mutex_unlock(&mMutex);
#endif
	}

private:
#ifdef WIN32
	//Windows平台临界区对象
	CRITICAL_SECTION moSection;
#else
	//Linux平台互斥结构体对象
	pthread_mutex_t mMutex;
#endif
};

//自动临界区锁实现类
class CAutoLock
{
public:
	//构造函数
	CAutoLock(CCriticalSection& aoSection);
	//析构函数
	~CAutoLock();
private:
	CCriticalSection& moSection;
};

class CEvent
{
public:
	CEvent();
	~CEvent();

public:
	//创建事件
	bool Create(bool bManualReset = false, bool bInitialState = false);
	//等待事件
	int WaitForEvent(uint32 dwMilliseconds);
	//设置事件为有信号
	void SetEvent();
	//重新设置事件为无信号
	void ResetEvent();
	//关闭事件
	void Close();

private:
#ifdef WIN32
	//事件句柄
	void*				mhEventHandle;
#else
	//为了防止竞争，条件变量的使用总是和一个互斥锁结合在一起。
	//Linux平台互斥结构体对象
	pthread_mutex_t		mhMutex;
	//Linux条件变量结构体对象
	pthread_cond_t		mhCond_t;
#endif
};
#endif //_CRITICAL_SECTION_H_
