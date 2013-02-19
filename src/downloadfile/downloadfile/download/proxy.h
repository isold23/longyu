#ifndef _PROXY_H_
#define _PROXY_H_
#pragma once

#include <strstream>
#include <string>
using namespace std;

enum PROXY_TYPE
{
	PROXY_ERROR = -1,
	PROXY_HTTP = 0,
	PROXY_SOCKET4 = 1,
	PROXY_SOCKET5 = 2,
	PROXY_HTTP11 = 3,
	PROXY_HTTP10 = 4,
};

class CProxy
{
public:
	CProxy(void);
	~CProxy(void);

	void SetProxyInfo(short type, const std::string strProxyServer, const short sProxyServerPort,
		const std::string strProxyServerName = "", const std::string strProxyServerPassword = "");

	int GetProxyType(void) const{ return m_nProxyType; }
	std::string GetProxyServerInfo(void)const;
	std::string GetProxyServerInfoWithDomain(void) const;
	std::string GetDomain(void)const{ return m_strHttpDomain; }
	bool GetProxyServerInfo (std::string &strServer, short &sPort)const;
	std::string GetProxyAuthorizationInfo(void)const;
	bool GetProxyAuthorizationInfo(std::string &strName, std::string &strPassword) const;
	bool IsNeedHttpDomain(void)const { return !(m_strHttpDomain.empty()); }
	bool IsNeedProxy(void) const { return m_bNeedProxy; }
	bool IsNeedAuthorization(void) const { return m_bProxyNeedAuthorization; }

private:
	void Init();
	void SetProxyInfo(void);

private:
	int m_nProxyType;
	std::string m_strProxyServer;
	short m_sProxyServerPort;

	std::string m_strHttpDomain;
	std::string m_strProxyServerName;
	std::string m_strProxyServerPassword;

	bool m_bNeedProxy;
	bool m_bProxyNeedAuthorization;
};

#endif //_PROXY_H_
