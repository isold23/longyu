#include "StdAfx.h"
#include ".\http.h"
/////////////////////////////////////////////////////////////////////////////////////
CHttpHeader::CHttpHeader(void)
{
	m_strRequestLine = "";
	m_strAccept = "*/*";
	m_strAcceptEncoding = "gzip, deflate";
	m_strAcceptLanguage = "zh-cn";
	m_strConnection = HTTP_DEFAULT_CONNECTION;
	m_strHost = "";
	m_strReferer = "";
	m_strUserAgent = "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)";
	m_strCookie = "GoogleAccountsLocale_session=zh_CN; GALX=38V9uweywGs";
	m_strIfModifySince = "";
	m_strXFlashVersion = "";
	m_strProxyConnection = HTTP_DEFAULT_CONNECTION;
	m_nRangeStart = 0;
	m_nRangeEnd = 0;
	/////////////////////////////////////////////////////
	m_strStatusLine = "";
	m_strAcceptRanges = "";
	m_strConnection = "";
	m_nContentLength = 0;
	m_strContentType = "";
	m_strData = "";
	m_strLastModify = "";
	//m_strServer = "";
	m_strSetCookie = "";
	m_strXCache = "";
	m_nIternetFileSize = 0;
}

CHttpHeader::~CHttpHeader(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////
CHttp::CHttp(void)
{
	m_strUrl = "";
	if (m_sServerPort == 0)
	{
		m_sServerPort = DEFAULT_HTTP_PORT;
	}
}

CHttp::CHttp(const std::string &strUrl)
{
	m_strUrl = strUrl;
	if (m_sServerPort == 0)
	{
		m_sServerPort = DEFAULT_HTTP_PORT;
	}
}

CHttp::~CHttp(void)
{

}

void CHttp::SetUrl(const char *pUrl)
{
	m_strUrl = pUrl;
}

void CHttp::SetUrl(const std::string &strUrl)
{
	m_strUrl = strUrl;
}

int CHttp::HttpRequest(std::string &strHttpRequest, std::string strMethod, const char *buf, const int len)
{
	int nRequestLen = 0;
	std::string strHostName = "";
	std::string strFileName = "";

	strHostName = m_strServer;
	strFileName = m_strFileName;

	std::strstream strRequest;
	strRequest<<strMethod<<" "<<strFileName<<" "<<HTTP_VERSION_INFO<<HTTP_POSTFIX;

	if (!m_strAccept.empty())
	{
		strRequest<<"Accept: "<<m_strAccept<<HTTP_POSTFIX;
	}

	strRequest<<"Host: "<<strHostName<<":"<<m_sServerPort<<HTTP_POSTFIX;

	if (!m_strReferer.empty())
	{
		strRequest<<"Referer: "<<m_strReferer<<HTTP_POSTFIX;
	}

	if (m_ProxyInfo.IsNeedProxy())
	{
		strRequest<<"Proxy-Connection: "<<HTTP_DEFAULT_CONNECTION<<HTTP_POSTFIX;
	}
	else
	{
		strRequest<<"Connection: "<<HTTP_DEFAULT_CONNECTION<<HTTP_POSTFIX;
	}

	if (!m_strContentType.empty())
	{
		strRequest<<"Content-Type: "<<m_strContentType<<HTTP_POSTFIX;
	}

	if (!m_strAcceptLanguage.empty())
	{
		strRequest<<"Accept-Language: "<<m_strAcceptLanguage<<HTTP_POSTFIX;
	}

	if (!m_strAcceptEncoding.empty())
	{
		strRequest<<"Accept-Encoding: "<<m_strAcceptEncoding<<HTTP_POSTFIX;
	}

	if (!m_strCookie.empty())
	{
		strRequest<<"Cookie: "<<m_strCookie<<HTTP_POSTFIX;
	}

	if (!m_strUserAgent.empty())
	{
		strRequest<<"User-Agent: "<<m_strUserAgent<<HTTP_POSTFIX;
	}

	if (m_ProxyInfo.IsNeedAuthorization())
	{
		std::string strAuthorization = m_ProxyInfo.GetProxyAuthorizationInfo();
		char *out = new char[1024];
		memset(out, 0, 1024);
		CBase64::Encode(out, (char*)strAuthorization.c_str(), strAuthorization.length());
		strRequest<<"Proxy-Authorization: Basic "<<out<<HTTP_POSTFIX;
		delete [] out;
		out = NULL;
	}

	if (m_nRangeStart > 0)
	{
		//if ((m_nRangeStart == 0 && m_nRangeEnd > 0) || (m_nRangeStart > 0))
		//{
			strRequest<<"Range: bytes="<<m_nRangeStart<<"-";
			if (m_nRangeEnd > 0 && m_nRangeEnd > m_nRangeStart)
			{
				strRequest<<m_nRangeEnd;
			}
			strRequest<<HTTP_POSTFIX;
		//}
	}

	if (strMethod == METHOD_POST)
	{
		assert((buf != NULL) && (len != 0));

		if (m_nContentLength != 0)
		{
			strRequest<<"Content-Length: "<<len<<HTTP_POSTFIX;
		}

		strRequest<<HTTP_POSTFIX<<buf<<HTTP_POSTFIX;
	}

	strRequest<<HTTP_POSTFIX<<ends;
	strHttpRequest = strRequest.str();
	nRequestLen = strRequest.pcount();
	return nRequestLen;
}

void CHttp::ParseHttpResponse(std::string &strHttpResponse)
{
	int length = 0;
	while(length < strHttpResponse.length())
	{
		int position = static_cast<int>(strHttpResponse.find_first_of("\r\n", length));
		if (position == string::npos)break;
		string str = strHttpResponse.substr(length, position - length);
		m_HttpResponse.push_back(strHttpResponse.substr(length, position - length));
		length = position + 2;
	}
}

//分析HTTP协议回复的头信息
int CHttp::HttpResponse(std::string &strHttpResponse)
{
	if (strHttpResponse.empty())return 0;
	ParseHttpResponse(strHttpResponse);
	std::vector<string>::iterator iter = m_HttpResponse.begin();
	bool bIsOK = false;
	for(; iter != m_HttpResponse.end(); iter++)
	{
		std::string strLine = *iter;
		if (iter == m_HttpResponse.begin())
		{
			m_strStatusLine = *iter;
			if ((strstr(strLine.c_str(), "200 OK") == NULL) && (strstr(strLine.c_str(), "206 Partial Content") == NULL))
			{
				if (strstr(strLine.c_str(), "416") != NULL)
				{
					return 416;
				}
				//HTTP返回有错误
#ifdef NEED_LOG
				std::string strError("HTTP error: ");
				strError += m_strStatusLine;
				strError += "\n";
				log::printlog(strError);
#endif
				return -1;
			}
		}

		if (strstr(strLine.c_str(), "Content-Length: ") != NULL)
		{		
				int position = static_cast<int>(strlen("Content-Length: "));
				m_nIternetFileSize = atoi(strLine.substr(position, strLine.length()).c_str());
		}

		if (strstr(strLine.c_str(), "Content-Range: ") != NULL)
		{

		}
	}
	return 0;
}

int CHttp::HttpResponse(const char* pHttpResponse)
{
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////