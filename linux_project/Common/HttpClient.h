#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_
#include <string>
#include <map>
#include <vector>
#include "HostIpCache.h"

using namespace std;


typedef map<string,string> URL_PARAMS;

class CHttpClient
{
public:

	enum ENUM_HTTP_ERROR
	{
		EHTTP_NO_ERROR,
		EHTTP_SUCCESS,
		EHTTP_URL_ERROR,
		EHTTP_GET_HOST_IP_FAIL,
		EHTTP_CRATE_SOCKET_FAIL,
		EHTTP_CONNECT_HOST_FAIL,
		EHTTP_CONNECT_TIMEOUT,
		EHTTP_SEND_DATA_FAIL,
		EHTTP_RECV_TIMEOUT,
		EHTTP_RECV_ERROR,
		EHTTP_NO_200_OK,
	};
	CHttpClient(void);
	~CHttpClient(void);
	static bool GetHttpRequest(const string& astrUrl,string& astrRet,int liTimeout = 3000);
	static int GetHttpRequestEx(const string& astrUrl,string& astrRet,int liTimeout = 3000,bool abUseHostIpCache = false);
	static bool PostHttpRequest(const string& astrUrl,const string& astrPostContent,string& astrRet);
	static string UrlEncode(const string& astrData);
	static string UrlDecode(const string& astrData);
	static bool ParseParams(const string& astrParams,URL_PARAMS& amapParams,
		const string& astrParamsSep = "&",const string& astrParamValueSep = "=");
	static bool SplitParams(const string& astrParams,vector<string>& avecParams,const string& astrSep = ",");
	static string GetParam(const URL_PARAMS& amapParams,const string& astrParamName);
	static bool GetHtmlData(const string& astrHtmlRes,string& astrHtmlData);
	static bool ParseUrl(const string& astrUrl,string& astrHost,string& astrPagePath,string& astrParams);
        static unsigned char CharToHex(const unsigned char &abyChValue);
        static unsigned char HexToChar(const unsigned char &abyChValue);
		static char Hex2Char(unsigned char abyChValue);
		static unsigned char Char2Hex(unsigned char abyChValue);
		static string Raw2HexStr(const char* apData,unsigned int auiDataLen);
		static string HexStr2Raw(const string& astrData);

	static bool ParseJsonParams(const string& astrParams,URL_PARAMS& amapParams);





public:
	static CHostIpCache moHostIpCache;
};
#endif //_HTTP_CLIENT_H_
