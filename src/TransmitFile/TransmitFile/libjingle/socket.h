/********************************************************************
	created:	2008/08/29
	created:	29:8:2008   16:39
	filename: 	socket.h
	file base:	socket
	file ext:	h
	author:		王立伟
	
	purpose:	网络接口类
*********************************************************************/
#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32")
#else
#include <arpa/inet.h>
#endif

#include "sigslot.h"

namespace ns_pseudo_tcp
{
	class CSocket
	{
	public:
		CSocket();
		~CSocket();
	
		int Open();
		int Close();

		int SendData();
		int RecvData();

	private:
  sigslot::signal1<TransportChannel*> SignalDestroyed;

	};

}//ns_pseduo_tcp
#endif//_SOCKET_H_