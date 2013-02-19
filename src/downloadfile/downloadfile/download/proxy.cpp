#include "StdAfx.h"
#include ".\proxy.h"

CProxy::CProxy(void)
{
	Init();
}

CProxy::~CProxy(void)
{
}

void CProxy::Init(void)
{
	m_strProxyServer = "";
	m_sProxyServerPort = 0;

	m_strProxyServerName = "";
	m_strProxyServerPassword = "";
	
	m_strHttpDomain = "";

	m_bNeedProxy = false;
	m_bProxyNeedAuthorization = false;
}

std::string CProxy::GetProxyServerInfo(void) const
{
	std::string strServer = "";
	std::strstream strInfo;
	if (m_bNeedProxy)
	{
		strInfo<<m_strProxyServer<<":"<<m_sProxyServerPort<<ends;
		strServer = strInfo.str();
	}
	return strServer;
}

std::string CProxy::GetProxyServerInfoWithDomain(void) const
{
	std::string strServer = "";
	std::strstream strInfo;
	if (m_bNeedProxy)
	{
		if (IsNeedHttpDomain())
		{
		strInfo<<m_strProxyServer<<"."<<m_strHttpDomain<<":"<<m_sProxyServerPort<<ends;
		strServer = strInfo.str();
		}
	}
	return strServer;
}

bool CProxy::GetProxyServerInfo(std::string &strServer, short &sPort)const
{
	if (m_bNeedProxy)
	{
		strServer = m_strProxyServer;
		sPort = m_sProxyServerPort;
		return true;
	}
	else
	{
		return false;
	}
}

std::string CProxy::GetProxyAuthorizationInfo(void)const
{
	std::strstream strInfo;
	std::string strAuthorization = "";
	if (m_bProxyNeedAuthorization)
	{
		strInfo<<m_strProxyServerName<<":"<<m_strProxyServerPassword<<ends;
		strAuthorization = strInfo.str();
	}
	return strAuthorization;
}

bool CProxy::GetProxyAuthorizationInfo(std::string &strName, std::string &strPassword) const
{
	if (m_bProxyNeedAuthorization)
	{
		strName = m_strProxyServerName;
		strPassword = m_strProxyServerPassword;
		return true;
	}
	else
	{
		return false;
	}
}

void CProxy::SetProxyInfo(short type, const std::string strProxyServer, const short sProxyServerPort,
						  const std::string strProxyServerName, const std::string strProxyServerPassword)
{
	if (!strProxyServer.empty())
	{
		m_strProxyServer = strProxyServer;
		m_sProxyServerPort = sProxyServerPort;
		m_bNeedProxy =  true;
		if (!strProxyServerName.empty())
		{
			m_strProxyServerName = strProxyServerName;
			m_strProxyServerPassword = strProxyServerPassword;
			m_bProxyNeedAuthorization = true;
		}
		m_nProxyType = type;
	}
}

void CProxy::SetProxyInfo(void)
{

}