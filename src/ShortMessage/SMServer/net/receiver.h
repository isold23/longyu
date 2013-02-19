#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "..\..\common\defines.h"
#include "../protocol/protocol.h"
using namespace protocol;

class CReceiver
{
public:
	friend class CNetSession;
	CReceiver(void);
	CReceiver(HANDLE h);
	~CReceiver(void);
	CReceiver& operator = (const CReceiver &recv);
private:
	int OnLogin(const CMsgBuffer &msg);
	int OnLogout(const CMsgBuffer &msg);
	int OnRecvMsg(const CMsgBuffer &msg);
	void Init(void);
private:
	HANDLE m_hHandle;
};

__inline void CReceiver::Init()
{
	m_hHandle = NULL;
}
#endif //_RECEIVER_H_