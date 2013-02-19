#ifndef _HTTP_H_
#define _HTTP_H_

#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <strstream>
using namespace std;

#include "download.h"
#include "base64.h"

#define DEFAULT_HTTP_PORT	443

#define METHOD_GET			"GET"
#define METHOD_POST			"POST"

#define HTTP_VERSION_INFO        "HTTP/1.1"
#define HTTP_POSTFIX             "\r\n"
#define HTTP_DEFAULT_CONNECTION  "Keep_Alive"

class CHttpHeader
{
public:
	CHttpHeader();
	~CHttpHeader();
public:
	std::string m_strRequestLine;
	std::string m_strAccept;
	std::string m_strAcceptEncoding;
	std::string m_strAcceptLanguage;
	std::string m_strConnection;
	std::string m_strHost;
	std::string m_strReferer;
	std::string m_strUserAgent;
	std::string m_strCookie;
	std::string m_strIfModifySince;
	std::string m_strXFlashVersion;
	std::string m_strProxyConnection;
	int m_nRangeStart;
	int m_nRangeEnd;
	//////////////////////////////////
	std::string m_strStatusLine;
	std::string m_strAcceptRanges;
	std::string m_strContentType;
	std::string m_strData;
	std::string m_strLastModify;
	//std::string m_strServer;
	std::string m_strSetCookie;
	std::string m_strXCache;
	int m_nContentLength;
	int m_nContentRangeStart;
	int m_nContentRangeEnd;
	int m_nIternetFileSize;
};

class CHttp : public CHttpHeader,
	virtual public CDownload
{
public:
	CHttp(void);
	CHttp(const std::string &strUrl);
	 ~CHttp(void);

	void SetUrl(const std::string &strUrl);
	const std::string GetUrl(void) const { return m_strUrl; }
	void SetUrl(const char *pUrl);

protected:
	int HttpRequest(std::string &strHttpRequest, std::string strMethod = METHOD_GET, const char* buf = NULL, const int len = 0);
	int HttpResponse(std::string &strHttpResponse);
	int HttpResponse(const char* pHttpResponse);

private:
	void ParseHttpResponse(std::string &strHttpResponse);

private:
	std::vector<std::string> m_HttpResponse;
	std::string m_strUrl;
};

#endif //_HTTP_H_
