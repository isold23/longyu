#ifndef _TCP_H_
#define _TCP_H_
#pragma once

#include <cassert>
using namespace std;

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32")
#include "download.h"
#include "log.h"
#include "base64.h"

class CTcpSocket:virtual public CDownload
{
public:
	CTcpSocket(void);
	CTcpSocket(std::string strServer, short sPort);
	 ~CTcpSocket(void);

	bool OnConnect(std::string strServer = "", short sPort = 0);
	bool OnRecv(char *buffer, int &length);
	bool OnSend(const char *buffer, const int length);
	bool OnClose(void);

private:
	void Init(void);
	bool ConnectProxy(void);
	bool ConnectHttpProxy(void);
	bool ConnectSocket4Proxy(void);
	bool ConnectSocket5Proxy(void);
	SOCKADDR_IN GetSocketAddr(std::string &strIp, short sPort);

private:
	SOCKET m_sock;
	int m_nSocketError;
	std::string m_strIp;
	short m_sPort;
	bool m_bConnect;
};

inline void CTcpSocket::Init(void)
{
	m_strIp = "";
	m_sPort = 0;
	m_sock = INVALID_SOCKET;
	m_nSocketError = 0;
	m_bConnect = false;
}

#endif //_TCP_H_