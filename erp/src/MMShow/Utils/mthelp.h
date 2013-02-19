#pragma once

#include <afxmt.h>
class CGuard
{
public:
	CGuard(CCriticalSection &cs)
		:m_cs(cs) {
			m_cs.Lock();
	}

	~CGuard(void) {
		m_cs.Unlock();
	}

private:
	CCriticalSection &m_cs;
};
