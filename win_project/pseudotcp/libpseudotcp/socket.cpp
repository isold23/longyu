#include "stdafx.h"
#include "socket.h"
#include <netinet/tcp.h>
#include <sys/ioctl.h>

using namespace wzy;

CSocket::CSocket()
{

}

CSocket::~CSocket()
{

}

int CSocket::Open(const char* src_ip, const unsigned short src_port,
				  const char* dst_ip, const unsigned short dst_port)
{
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock < 0)
	{
		return -1;
	}

	src_addr.sin_family = AF_INET;
	src_addr.sin_port = htons(src_port);
	src_addr.sin_addr.s_addr = inet_addr(src_ip);

	int nRet = bind(sock, (sockaddr*)(&src_addr), sizeof(sockaddr_in));
	if(nRet < 0)
	{
		int error = GetLastError();
		return -1;
	}

	dst_addr.sin_family = AF_INET;
	dst_addr.sin_addr.s_addr = inet_addr(dst_ip);
	dst_addr.sin_port = htons(dst_port);
		
	//int iFlags=1;
	//ioctl(sock, FIONBIO, &iFlags);

	return 0;
}

int CSocket::Close()
{
	shutdown(sock, 2);
#ifdef WIN32
	closesocket(sock);
#else		
	close(sock);
#endif//WIN32
	return 0;
}

int CSocket::RecvData(char* buffer, size_t &len)
{
	sockaddr_in recv_addr;
	memset(&recv_addr, 0, sizeof(sockaddr_in));
	char memcache[MAX_PACKET_SIZE];
	memset(memcache, 0, MAX_PACKET_SIZE);
	int length = MAX_PACKET_SIZE;
		
#ifdef WIN32
	int addr_size = sizeof(sockaddr_in);
#else		
	socklen_t addr_size = sizeof(sockaddr_in);
#endif//WIN32
	
	int nRet  = recvfrom(sock, memcache, length, 0, (sockaddr*)&recv_addr, &addr_size);
	if(nRet < 0)
	{
		int error = GetLastError();
		return -1;
	}


#ifdef WIN32
	if(recv_addr.sin_addr.S_un.S_addr != dst_addr.sin_addr.S_un.S_addr || 
		recv_addr.sin_port != dst_addr.sin_port)
	{
		return -2;
	}
#else		
	if(recv_addr.sin_addr.s_addr != dst_addr.sin_addr.s_addr || 
		recv_addr.sin_port != dst_addr.sin_port)
	{
		return -2;
	}
#endif//WIN32
	

	memcpy(buffer, memcache, nRet);
	len = nRet;
	
	return 0;
}

int CSocket::SendData(const char *buffer, size_t len)
{
	if(len > MAX_PACKET_SIZE)
		return -2;
	int addr_size = sizeof(sockaddr);
	int nRet = sendto(sock, buffer, len, 0, (sockaddr*)&dst_addr, addr_size);
	if(nRet < 0)
	{
		return -1;
	}
	return 0;
}

