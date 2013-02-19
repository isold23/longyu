#include "stdafx.h"
#include "stun.h"
using namespace stun;


StunMsg::StunMsg()
{


}

StunMsg::~StunMsg()
{
}

void StunMsg::Encode(uint8 *buffer, uint32 length)
{

}

void StunMsg::Decode(const uint8 *buffer, const uint32 length)
{

}

CStun::CStun()
:m_StunTestCount(10)
{
}

CStun::~CStun()
{

}

NatType CStun::StunNatType(code_net::CSocketAddr &addr)
{
	CSocketAddr addr1 = addr;
	CSocketAddr addr2(addr.ip2str().c_str(), addr.ip2h() + 1);

	for(int i = 0; i < m_StunTestCount; i++)
	{
		m_NetSelect.SocketSet(&m_StunFd1);
		m_NetSelect.SocketSet(&m_StunFd2);
		m_NetSelect.SocketSet(&m_StunFd3);
		m_NetSelect.SocketSet(&m_StunFd4);

		int nRet = m_NetSelect.NetSelectFun(5);
		if (nRet)
		{
			if (!m_RequestI)
			{

				//SendRequest(m_StunFd1, addr1, )
				m_RequestI = true;
			}

			if (!m_RequestII && m_RequestI)
			{
				m_RequestII = true;
			}
		}

	}
	return m_NatType;
}


uint32 CStun::SendRequest(CUdpSocket &sock, const CSocketAddr & addr, const StunMsg &msg)
{
	uint8 *buffer = new uint8[STUN_MAX_BUFFER_SIZE];
	memset(buffer, 0, STUN_MAX_BUFFER_SIZE*sizeof(uint8));
	uint32 length = STUN_MAX_BUFFER_SIZE;
	StunMsg.Encode(buffer, length);
	int nRet = sock.Sendto((const char*)buffer, (int)length, addr);
	if (nRet < 0)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "SendRequest error");
	}

	delete buffer;
	buffer = NULL;
	return 0;
}

stun::StunMsg CStun::RecvResponse(CUdpSocket &sock)
{
	uint8 *buffer = new uint8[STUN_MAX_BUFFER_SIZE];
	memset(buffer, 0, STUN_MAX_BUFFER_SIZE*sizeof(uint8));
	uint32 length = STUN_MAX_BUFFER_SIZE;

	CSocketAddr addr;

	int nRet = sock.Recvfrom((char*)buffer, length, addr);
	if (nRet < 0)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "RecvResponse error");
	}
	StunMsg msg;
	msg.Decode(buffer, length);

	delete buffer;
	buffer = NULL;
	return msg;
}