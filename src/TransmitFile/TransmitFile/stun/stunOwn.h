#ifndef _STUN_H_
#define _STUN_H_

#include "..\..\..\..\include\net\net.h"
#include "..\..\..\..\include\defines.h"
using namespace code_net;

namespace stun
{
	typedef struct
	{
		uint32 ip;
		uint16 port;
	}StunAddress4;

	typedef enum 
	{
		StunTypeUnknown = 0,
		StunTypeOpen,
		StunTypeConeNat,
		StunTypeRestrictedNat,
		StunTypePortRestrictedNat,
		StunTypeSymNat,
		StunTypeSymFirewall,
		StunTypeBlocked,
	} NatType;

	typedef enum
	{
		StunCmdUnknown = 0,
		
		//client port1 -> server1 port1
		StunCmd1,
		//server1 port1 -> client port1
		StunCmd2,

		//client port1 -> server1 port2
		StunCmd3,
		//server1 port2 -> client port1
		StunCmd4,
		
		//client port2 -> server1 port1
		StunCmd5,
		//server1 port1 -> client port2
		StunCmd6,

		//client port1 -> server2 port1
		StunCmd7,
		//server2 port1 -> client port1
		StunCmd8,

		StunCmd9,
		StunCmdA,

		StunCmdB,
		StunCmdC,

	}NatMsgCmd;

	static const uint32 STUN_MAX_BUFFER_SIZE = 3 * 1024;

	class StunMsg
	{
	public:
		StunMsg();
		~StunMsg();

		void Encode(uint8 *buffer, uint32 length);
		void Decode(const uint8 *buffer, const uint32 length);

	private:
		uint32 m_msgType;
		uint32 m_msgLen;
		uint32 m_id;
		StunAddress4 m_localAddr;
		StunAddress4 m_InternetAddr;
		StunAddress4 m_server1Addr;
		StunAddress4 m_server2Addr;
	};

	class CStun
	{
	public:
		CStun();
		~CStun();

		//测试NAT类型
		NatType StunNatType(code_net::CSocketAddr &addr);
	
	private:
		uint32 SendRequest(CUdpSocket &sock, const CSocketAddr & addr, const StunMsg &msg);
		stun::StunMsg RecvResponse(CUdpSocket &sock)
		void Init();

	private:

		//发送到第一个服务器的第一个端口
		code_net::CUdpSocket m_StunFd1;
		//发送到第一个服务器的第二个端口
		code_net::CUdpSocket m_StunFd2;
		//发送到第二个服务器的第一个端口
		code_net::CUdpSocket m_StunFd3;
		//发送到第一个服务器的第二个端口
		code_net::CUdpSocket m_StunFd4;
		bool m_RequestI;
		bool m_ResponseI;

		bool m_RequestII;
		bool m_ResponseII;

		bool m_RequestIII;
		bool m_ResponseIII;

		code_net::CNetSelect m_NetSelect;
		NatType m_NatType;

		const uint32 m_StunTestCount;
	};

	inline void CStun::Init()
	{
		m_RequestI = false;
		m_ResponseI = false;

		m_RequestII = false;
		m_ResponseII = false;

		m_RequestIII = false;
		m_ResponseIII = false;
		m_NatType = stun::StunTypeUnknown;

	}
};

#endif//_STUN_H_