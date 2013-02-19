#ifndef _NET_ADDRESS_H_
#define _NET_ADDRESS_H_

#include "include.h"

#define INET_IP_STRLEN   (sizeof("255.255.255.255") - 1)
#define INET_ADDR_STRLEN  (sizeof("255.255.255.255:65535") - 1)

struct StructNetAddr{
	unsigned int ip;
	unsigned short port;
};

class CNetAddress{
public:
	//从int型的IP地址得到字符串类型的IP地址
	inline static char* GetStrIp(unsigned int ip){
		sockaddr_in addr;
		addr.sin_addr.s_addr = htonl(ip);
		return inet_ntoa(addr.sin_addr);
	}
};

#endif //_NET_ADDRESS_H_


