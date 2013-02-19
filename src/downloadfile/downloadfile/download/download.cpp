#include "StdAfx.h"
#include ".\download.h"

CDownload::CDownload(void)
{
	m_strServer = "";
	m_sServerPort = 0;
	m_bNeedAuthorization = false;
	m_strServerName = "";
	m_strServerPassword = "";
	m_strFileName = "";
	m_strProtocolType = PROTOCOL_TYPE_HTTPS;
}

CDownload::~CDownload(void)
{
}

void CDownload::SetProtocolType(int type)
{
	if (type = HTTP_PROTOCOL)
	{
		m_strProtocolType = PROTOCOL_TYPE_HTTP;
	}
	else if (type == FTP_PROTOCOL)
	{
		m_strProtocolType = PROTOCOL_TYPE_FTP;
	}
}

void CDownload::SetProxyInfo(int type, std::string strServer, short sPort, std::string strName, std::string strPassword)
{
	m_ProxyInfo.SetProxyInfo(type, strServer, sPort, strName, strPassword);
}


void CDownload::SetServerInfo(std::string strServer, short sPort, std::string strServerName, std::string strServerPassword)
{
	if (!strServer.empty())
	{
		m_strServer = strServer;
		m_sServerPort = sPort;
		if (!strServerName.empty())
		{
			m_strServerName = strServerName;
			m_strServerPassword = strServerPassword;
			m_bNeedAuthorization = true;
		}
	}
}

bool CDownload::AnalyseUrl(std::string strUrl, std::string &strHostName, std::string &strFileName)
{
	size_t pos = strUrl.find_first_of(m_strProtocolType.c_str());
	if (pos != string::npos)
	{
		strUrl.erase(pos, m_strProtocolType.length());
		pos = strUrl.find_first_of('/');
		if (pos != string::npos)
		{
			strHostName = strUrl.substr(0, pos);
			strFileName = strUrl.substr(pos, strUrl.length());
			m_strServer = strHostName;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
