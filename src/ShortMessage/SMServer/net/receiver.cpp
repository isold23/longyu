#include "stdafx.h"
#include "receiver.h"

CReceiver::CReceiver()
{
	Init();
}

CReceiver::CReceiver(HANDLE h)
{
	Init();
	m_hHandle = h;
}

CReceiver::~CReceiver()
{
	Init();
}

int CReceiver::OnLogin(const CMsgBuffer &msg)
{
	return 0;
}

int CReceiver::OnLogout(const CMsgBuffer &msg)
{
	return 0;
}

int CReceiver::OnRecvMsg(const protocol::CMsgBuffer &msg)
{
	return 0;
}

CReceiver& CReceiver::operator =(const CReceiver &recv)
{
	if (this != &recv)
	{
		m_hHandle = recv.m_hHandle;
	}
	return *this;
}