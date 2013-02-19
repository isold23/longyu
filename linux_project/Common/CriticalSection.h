#ifndef _CRITICAL_SECTION_H_
#define _CRITICAL_SECTION_H_

#ifdef WIN32

#else
#include <pthread.h>
#include <sys/time.h>
#include <errno.h> 
#endif
#include "define.h"
#include <string>

using namespace std;

typedef	unsigned long	timeout_t;

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

public:
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
	CEvent(const char* apName = "");
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
	string	mstrName;
	bool	mbCreated;
};


#ifndef WIN32
/**
* A conditional variable synchcronization object for one to one and
* one to many signal and control events between processes.
* Conditional variables may wait for and receive signals to notify
* when to resume or perform operations.  Multiple waiting threads may
* be woken with a broadcast signal.
*
* @warning While this class inherits from Mutex, the methods of the
* class Conditional just handle the system conditional variable, so
* the user is responsible for calling enterMutex and leaveMutex so as
* to avoid race conditions. Another thing to note is that if you have
* several threads waiting on one condition, not uncommon in thread
* pools, each thread must take care to manually unlock the mutex if
* cancellation occurs. Otherwise the first thread cancelled will
* deadlock the rest of the thread.
*
* @author David Sugar
* @short conditional.
* @todo implement in win32
*/
class  Conditional
{
private:
	pthread_cond_t _cond;
	pthread_mutex_t _mutex;
	int miDataCount;

public:
	/**
	* Create an instance of a conditional.
	*
	* @param id name of conditional, optional for deadlock testing.
	*/
	Conditional(const char *id = NULL);

	/**
	* Destroy the conditional.
	*/
	virtual ~Conditional();

	/**
	* Signal a conditional object and a waiting threads.
	*
	* @param broadcast this signal to all waiting threads if true.
	*/
	void signal(bool broadcast);

	/**
	* Wait to be signaled from another thread.
	*
	* @param timer time period to wait.
	* @param locked flag if already locked the mutex.
	*/
	bool wait(timeout_t timer = 0, bool locked = false);

	/**
	* Locks the conditional's mutex for this thread.  Remember
	* that Conditional's mutex is NOT a recursive mutex!
	*
	* @see #leaveMutex
	*/
	void enterMutex(void);

	/**
	* In the future we will use lock in place of enterMutex since
	* the conditional composite is not a recursive mutex, and hence
	* using enterMutex may cause confusion in expectation with the
	* behavior of the Mutex class.
	*
	* @see #enterMutex
	*/
	inline void lock(void)
	{enterMutex();};

	/**
	* Tries to lock the conditional for the current thread.
	* Behaves like #enterMutex , except that it doesn't block the
	* calling thread.
	*
	* @return true if locking the mutex was succesful otherwise false
	*
	* @see enterMutex
	* @see leaveMutex
	*/
	bool tryEnterMutex(void);

	inline bool test(void)
	{return tryEnterMutex();};

	/**
	* Leaving a mutex frees that mutex for use by another thread.
	*
	* @see #enterMutex
	*/
	void leaveMutex(void);

	inline void unlock(void)
	{return leaveMutex();};

	timespec *getTimeoutEx(struct timespec *spec, timeout_t timer)
	{
		static	struct timespec myspec;

		if(spec == NULL)
			spec = &myspec;

#ifdef	PTHREAD_GET_EXPIRATION_NP
		struct timespec offset;

		offset.tv_sec = timer / 1000;
		offset.tv_nsec = (timer % 1000) * 1000000;
		pthread_get_expiration_np(&offset, spec);
#else
		struct timeval current;

		gettimeofday(&current,NULL);
		spec->tv_sec = current.tv_sec + ((timer + current.tv_usec / 1000) / 1000);
		spec->tv_nsec = ((current.tv_usec / 1000 + timer) % 1000) * 1000000;

#endif
		return spec;
	}
};
#endif

#endif //_CRITICAL_SECTION_H_
