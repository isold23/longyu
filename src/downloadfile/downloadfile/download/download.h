#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_
#pragma once

#include <string>
#include <strstream>
using namespace std;

#include "proxy.h"

#define PROTOCOL_TYPE_HTTPS "https://"
#define PROTOCOL_TYPE_HTTP "http://"
#define PROTOCOL_TYPE_FTP "ftp://"

enum{ HTTP_PROTOCOL = 0, FTP_PROTOCOL = 1, };

class CDownload
{
public:
	CDownload(void);
	 ~CDownload(void);

	virtual bool DownloadFile(std::string strUrl, std::string strFilePath) = 0;
	virtual bool UploadFile(std::string strUrl, std::string strFilePath) = 0;
	void SetServerInfo(std::string strServer, short sPort, const std::string strServerName = "", const std::string strServerPassword = "");
	void SetProxyInfo(int type, std::string strServer, short sPort, std::string strName = "", std::string strPassword = "");
	void SetProtocolType(int type);

protected:
	bool AnalyseUrl(std::string strUrl, std::string &strHostName, std::string &strFileName);

protected:
	CProxy m_ProxyInfo;
	std::string m_strServer;
	short m_sServerPort;
	bool m_bNeedAuthorization;
	std::string m_strServerName;
	std::string m_strServerPassword;
	std::string m_strFileName;
	std::string m_strProtocolType;
};
#endif //_DOWNLOAD_H_