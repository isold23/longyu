#pragma once

namespace _LONGYU_COMMON
{
	class CCriticalSection
	{
	public:
		//构造函数
		CCriticalSection();
		//析构函数
		~CCriticalSection();

		//进入临界区
		void Enter();
		//离开临界区
		void Leave();
	private:
		CRITICAL_SECTION moSection;
	};

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

}; //end _LONGYU_COMMON