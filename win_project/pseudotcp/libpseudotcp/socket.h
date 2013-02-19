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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#define SOCKET int
#endif//_WIN32

#include "../common/sigslot.h"

namespace wzy
{

	class CNet
	{
	public:
		CNet()
		{
			#ifdef WIN32
			WSADATA wsaData;
			// Initialize Winsock
			WSAStartup(MAKEWORD(2,2), &wsaData);
			#endif//_WIN32
		}
		~CNet()
		{			
			#ifdef WIN32
			WSACleanup();
			#endif//_WIN32
		}
	private:

	};
	const size_t MAX_PACKET_SIZE = 64 * 1024;

	class CSocket
	{
	public:
		CSocket();
		~CSocket();
	
		int Open(const char* ip, const unsigned short port,
			const char* dst_ip, const unsigned short dst_port);
		int Close();

		int SendData(const char *buffer, size_t len);
		int RecvData(char* buffer, size_t &len);
		
#ifndef WIN32
		int GetLastError(){ return errno; };
#endif//WIN32


	private:
		sockaddr_in src_addr;
		sockaddr_in dst_addr;
		SOCKET sock;
	};

}//wzy


#endif//_SOCKET_H_