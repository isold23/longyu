#include "StdAfx.h"
#include ".\tcp.h"

CTcpSocket::CTcpSocket(void)
{
	Init();
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

CTcpSocket::~CTcpSocket(void)
{
	WSACleanup();
}

bool CTcpSocket::OnClose(void)
{
	if (m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
		//Init();
	}
	return true;
}

SOCKADDR_IN CTcpSocket::GetSocketAddr(std::string &strIp, short sPort)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(strIp.c_str());

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(strIp.c_str());
		if (lphost != NULL)
		{
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		}
		else
		{
			int nError = GetLastError();
			WSASetLastError(WSAEINVAL);
			memset(&sockAddr,0,sizeof(sockAddr));
			return sockAddr;
		}
	}

	sockAddr.sin_port = htons(sPort);
	return sockAddr;
}

bool CTcpSocket::OnConnect(std::string strServer, short sPort)
{
	if (m_bConnect)
		return true;

	if (!m_strServer.empty())
	{
		m_strIp = m_strServer;
		m_sPort = m_sServerPort;
	}

	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (m_sock == INVALID_SOCKET)
	{
#ifdef NEED_LOG
		m_nSocketError = GetLastError();
		std::strstream error;
		error<<"Create socket error: "<<m_nSocketError<<ends<<endl;
		log::printlog(error);
#endif
		return false;
	}

	if (m_ProxyInfo.IsNeedProxy())
	{
		m_ProxyInfo.GetProxyServerInfo(m_strIp, m_sPort);

		if (ConnectProxy() == false)
		{
#ifdef NEED_LOG
			log::printlog("Connect proxy server failed!!!\n");
#endif
			return false;
		}

		if (m_ProxyInfo.GetProxyType() == PROXY_HTTP || m_ProxyInfo.GetProxyType() == PROXY_HTTP11)
		{
			if(ConnectHttpProxy())
			{
#ifdef NEED_LOG
				log::printlog("Connect http proxy server successful!!!\n");
#endif
			}
		}
		else if (m_ProxyInfo.GetProxyType() == PROXY_SOCKET4)
		{
			if(ConnectSocket4Proxy())
			{
#ifdef NEED_LOG
				log::printlog("Connect http socket4 server successful!!!\n");
#endif
			}
		}
		else if(m_ProxyInfo.GetProxyType() == PROXY_SOCKET5)
		{
			if(ConnectSocket5Proxy())
			{
#ifdef NEED_LOG
				log::printlog("Connect http socket4 server successful!!!\n");
#endif
			}
		}
	}
	else
	{
		if (m_strIp.empty())
		{
#ifdef NEED_LOG
			log::printlog("Server is empty!!!\n");
#endif
			return false;
		}

		SOCKADDR_IN sockAddr = GetSocketAddr(m_strIp, m_sPort);

		int nRet = connect(m_sock, (struct sockaddr*)(&sockAddr), sizeof(SOCKADDR_IN));
		int nError = WSAGetLastError();
		if(nRet == SOCKET_ERROR)
			return false;
		if (nError != 0)
		{
			if(nError != WSAEWOULDBLOCK)
				return false;
		}
	}
	m_bConnect = true;
	return true;
}

bool CTcpSocket::ConnectProxy(void)
{
	if (m_strIp.empty())
	{
#ifdef NEED_LOG
		log::printlog("Proxy server is empty!!!\n");
#endif
		return false;
	}

	SOCKADDR_IN sockAddrProxy = GetSocketAddr(m_strIp, m_sPort);

	u_long dwMode = 0;
	if(SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &dwMode))
		return false;
	
	int nReturn = connect(m_sock, (LPSOCKADDR)&sockAddrProxy, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == nReturn)
	{
#ifdef NEED_LOG
		m_nSocketError = GetLastError();
		std::strstream error;
		error<<"Connect proxy server error: "<<m_nSocketError<<ends<<endl;
		log::printlog(error);
#endif
		return false;
	}
	return true;
}

bool CTcpSocket::ConnectHttpProxy(void)
{
	std::string strProxyProtocol = "HTTP";
	std::string strServerInfo = m_ProxyInfo.GetProxyServerInfo();
		if (stricmp(strProxyProtocol.c_str(), "HTTPS") == 0 || stricmp(strProxyProtocol.c_str(), "HTTP") == 0 )
		{
			std::strstream strConnect;
			if (!(m_ProxyInfo.IsNeedHttpDomain()))
			{
				if (m_ProxyInfo.GetProxyType() == PROXY_HTTP)
				{
					strConnect<<"CONNECT "<<m_strServer<<":"<<m_sServerPort<<" HTTP/1.0\r\n";
				}
				else if (m_ProxyInfo.GetProxyType() == PROXY_HTTP11)
				{
					strConnect<<"CONNECT "<<m_strServer<<":"<<m_sServerPort<<" HTTP/1.1\r\n";
				}
			}
			else
			{
				if (m_ProxyInfo.GetProxyType() == PROXY_HTTP)
				{
					strConnect<<"CONNECT "<<m_strServer<<"."<<m_ProxyInfo.GetDomain()<<":"<<m_sServerPort<<" HTTP/1.0\r\n";
				}
				else if (m_ProxyInfo.GetProxyType() == PROXY_HTTP11)
				{
					strConnect<<"CONNECT "<<m_strServer<<"."<<m_ProxyInfo.GetDomain()<<":"<<m_sServerPort<<" HTTP/1.1\r\n";
				}
				
			}

			strConnect<<"Host: "<<m_strServer<<":"<<m_sServerPort<<"\r\n";
			if (m_ProxyInfo.IsNeedAuthorization())
			{
				char szAuth[100 + 1] = {""};
				std::string strAuthorizationInfo = m_ProxyInfo.GetProxyAuthorizationInfo();
				CBase64::Encode(szAuth, (char*)strAuthorizationInfo.c_str(), strAuthorizationInfo.length());
				strConnect<<"Proxy-Authorization: Basic "<<szAuth<<"\r\n";
			}
			strConnect<<"\r\n"<<ends;

			try
			{
				int num = send(m_sock, strConnect.str(), strConnect.pcount(), 0);
				if (num == SOCKET_ERROR)
				{
#ifdef NEED_LOG
					m_nSocketError = GetLastError();
					std::strstream error;
					error<<"Send date to http proxy server error: "<<m_nSocketError<<ends<<endl;
					log::printlog(error);
#endif
					return false;
				}
				char chRec[1024];
				num = recv(m_sock, chRec, 1024, 0);
				if (num == SOCKET_ERROR)
				{
#ifdef NEED_LOG
					m_nSocketError = GetLastError();
					std::strstream error;
					error<<"Receive date from http proxy server error: "<<m_nSocketError<<ends<<endl;
					log::printlog(error);
#endif
					return false;
				}
				char* pettt = strstr(chRec, "200");
				return (pettt != NULL);
			}
			catch(...)
			{
#ifdef NEED_LOG
				log::printlog("Connect http proxy has exception!!!\n");
#endif
				return false;
			}
		}
		return true;
}

bool CTcpSocket::ConnectSocket4Proxy(void)
{
	int nError = 0;
	char command[9];
	memset(command, 0, 9);
	command[0] = 4;
	command[1] = 1;
	SOCKADDR_IN sockAddr = GetSocketAddr(m_strServer, m_sServerPort);
	memcpy(&command[2], &sockAddr.sin_port, 2);
	memcpy(&command[4], &sockAddr.sin_addr.S_un.S_addr, 4);

	try
	{
		int num = send(m_sock,	command, 9,	0);
		if (num == SOCKET_ERROR) 
		{
#ifdef NEED_LOG
			m_nSocketError = GetLastError();
			std::strstream error;
			error<<"Send date to socket4 proxy server error: "<<m_nSocketError<<ends<<endl;
			log::printlog(error);
#endif
			return false;
		}

		num = recv(m_sock, command, 8, 0);
		if (num != 8)
		{
#ifdef NEED_LOG
			m_nSocketError = GetLastError();
			std::strstream error;
			error<<"Receive date from socket4 proxy server error: "<<m_nSocketError<<ends<<endl;
			log::printlog(error);
#endif
			return false;
		}
	}
	catch(...)
	{
#ifdef NEED_LOG
		log::printlog("Connect socket4 proxy server has exception!!!\n");
#endif
		return false;
	}

	if (command[1] != 90)
	{
#ifdef NEED_LOG
		m_nSocketError = GetLastError();
		std::strstream error;
		error<<"Data error by receive from socket4 proxy server: "<<m_nSocketError<<ends<<endl;
		log::printlog(error);
#endif
		return false;
	}

	return true;
}

bool CTcpSocket::ConnectSocket5Proxy(void)
{
	char command[1024] = {0};
	try
	{
		int nSizeToSend = 0;
		int nLen = 0;
		if (m_ProxyInfo.IsNeedAuthorization())
		{
			command[0] = 5;
			command[1] = 2;//后面还有2个字节
			command[2] = 0;
			command[3] = 2;
			nSizeToSend = 4;
			send(m_sock, command, nSizeToSend, 0);
			nLen = 2;
			recv(m_sock, command, nLen, 0);
			if(command[0] == 5)
			{//need auth							
				if(command[1] == 2)
				{
					std::string name = "";
					std::string password = "";
					m_ProxyInfo.GetProxyAuthorizationInfo(name, password);
					command[0] = 1;
					nLen = static_cast<int>(name.length());
					command[1] = nLen;
					strcpy(command + 2, name.c_str());
					nLen += 2;
					command[nLen] = password.length();
					strcpy(command + nLen + 1, password.c_str());
					nLen = nLen + 1 + password.length();
					send(m_sock, command, nLen, 0);
					nLen = 2;
					recv(m_sock, command, nLen, 0);
				}
				if(command[1] != 0)
				{
#ifdef NEED_LOG
					log::printlog("Data error by receive data from socket5 server with authorization!!!\n");
#endif
					return false;
				}
			}
			else
			{
#ifdef NEED_LOG
				log::printlog("Data error by receive data from socket5 server!!!\n");
#endif
				return false;
			}
		}
		else
		{
			command[0] = 5;
			command[1] = 1;//后面还有1个字节
			command[2] = 0;
			nSizeToSend = 3;
			send(m_sock, command, nSizeToSend, 0);
			nLen = 2;
			recv(m_sock, command, nLen, 0);
			if(command[0] != 5 || command[1] != 0)
			{
#ifdef NEED_LOG
				log::printlog("Data error by receive data from socket5 server without authorization!!!\n");
#endif
				return false;
			}
		}

		memset(command, 0, 10);
		command[0] = 5;
		command[1] = 1;//CONNECT01，BIND02
		command[2] = 0;//RESERVED
		command[3] = 1;//ADDRESS TYPE
		SOCKADDR_IN sockAddr = GetSocketAddr(m_strServer, m_sServerPort);
		memcpy(&command[4],  &sockAddr.sin_addr.S_un.S_addr, 4);
		memcpy(&command[8],  &sockAddr.sin_port, 2);

		int num = send(m_sock, command, 10, 0);
		if(num == SOCKET_ERROR)
		{
			m_nSocketError = GetLastError();
			return false;
		}

		num = recv(m_sock, command, 10, 0);
		if(num == SOCKET_ERROR) 
		{
			m_nSocketError = GetLastError();
			return false;
		}

		if(command[0] != 5 || command[1] != 0)
		{
			return false;
		}
	}
	catch(...)
	{
#ifdef NEED_LOG
		log::printlog("Connect socket5 proxy server has exception!!!\n");
#endif
		return false;
	}
	return true;
}

bool CTcpSocket::OnRecv(char *buffer, int &length)
{
	//
	assert(buffer != NULL);
	int nRecvLen = 0;
	int nRecvTotalLen = 0;
	if (m_sock != INVALID_SOCKET)
	{
		do
		{
			nRecvLen = recv(m_sock, buffer + nRecvTotalLen, length - nRecvTotalLen, 0);
			if (nRecvLen == SOCKET_ERROR)
			{
#ifdef NEED_LOG
				m_nSocketError = GetLastError();
				std::strstream error;
				error<<"recv data error: "<<m_nSocketError<<ends<<endl;
				log::printlog(error);
#endif
				return false;
			}
			else if (nRecvLen == 0)
			{
				break;
			}
			else
			{
				nRecvTotalLen += nRecvLen;
			}
		}while(nRecvTotalLen <= length);

		length = nRecvTotalLen;
		return true;
	}
	return false;
}
bool CTcpSocket::OnSend(const char *buffer, const int length)
{
	//未发送完的数据没有缓存
	assert(buffer != NULL);
	int nSendLen = 0;
	int nSendTotalLen = 0;
	if (m_sock != INVALID_SOCKET)
	{
		do
		{
			nSendLen = send(m_sock, buffer + nSendTotalLen, length - nSendTotalLen, 0);
			if (nSendLen == SOCKET_ERROR)
			{
#ifdef NEED_LOG
				m_nSocketError = GetLastError();
				std::strstream error;
				error<<"send data error: "<<m_nSocketError<<ends<<endl;
				log::printlog(error);
#endif
				return false;
			}
			else
			{
				nSendTotalLen += nSendLen;
			}
		}while(nSendTotalLen < length);
		return true;
	}
	return false;
}