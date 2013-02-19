#include "HttpClient.h"
#include <sstream>
#include "libnet.h"
#include "TcpStream.h"

CHostIpCache CHttpClient::moHostIpCache;

CHttpClient::CHttpClient(void){
}

CHttpClient::~CHttpClient(void){
}

bool CHttpClient::GetHttpRequest(const string& astrUrl,string& astrRet,int liTimeout){
	return GetHttpRequestEx(astrUrl,astrRet,liTimeout) == EHTTP_SUCCESS;	
} 

int CHttpClient::GetHttpRequestEx(const string& astrUrl,string& astrRet,int liTimeout,bool abUseHostIpCache){
	string lstrHost,lstrPage,lstrParams;
	if(!CHttpClient::ParseUrl(astrUrl,lstrHost,lstrPage,lstrParams)){
		return EHTTP_URL_ERROR;
	}

	//format http request header
	stringstream lstrHttpHeader;
	lstrHttpHeader<<"GET " << lstrPage;
	if("" != lstrParams){
		lstrHttpHeader<<"?" << lstrParams;
	}
	lstrHttpHeader<<" HTTP/1.0\r\n" 
		<<"Accept: */*\r\n"
		<<"Accept-Language: zh-cn\r\n"
		<<"User-Agent: Mozilla/4.0\r\n"
		<<"Host: "<<lstrHost<<"\r\n"
		<<"Connection: close\r\n" 
		<<"\r\n";

	unsigned short lusHttpPort = 80;	
	string::size_type lPos = lstrHost.find(':');
	if(string::npos != lPos){
		lusHttpPort = atoi(lstrHost.substr(lPos+1).c_str());
		lstrHost = lstrHost.substr(0,lPos);
	}

	//TRACE(5,"begin parse host ip:"<<lstrHost);
	string lstrHostIp = lstrHost; 
	if(abUseHostIpCache) //use host ip cache
	{
		if(!moHostIpCache.GetHostIp(lstrHost,lstrHostIp)){
			if(GetIpByHostName(lstrHost,lstrHostIp)){
				moHostIpCache.SetHostIp(lstrHost,lstrHostIp);
			}else{
				return EHTTP_GET_HOST_IP_FAIL;
			}
		}
	}else{
		if(!GetIpByHostName(lstrHost,lstrHostIp)){
			return EHTTP_GET_HOST_IP_FAIL;
		}
	}

	//TRACE(5,"http host ip:"<<lstrHostIp);
	CTcpStream loTcpStream(liTimeout);	
	int liSocket = loTcpStream.GetSocket();
	if(loTcpStream.GetSocket() <= 0){
		return EHTTP_CRATE_SOCKET_FAIL;
	}
	//connect to http server
	if(!loTcpStream.Connect(lstrHostIp.c_str(),lusHttpPort,liTimeout)){
		return EHTTP_CONNECT_HOST_FAIL;
	}	

	//TRACE(5,"connect to host:"<<lstrHostIp<<" success!,fd:"<<liSocket);
	//send request
	if(!loTcpStream.SendData(lstrHttpHeader.str().c_str(),(unsigned short)lstrHttpHeader.str().size())){
		return EHTTP_SEND_DATA_FAIL;
	}

	//TRACE(5,"send data to host:"<<lstrHostIp<<" success!,fd:"<<liSocket);

	//recv http response
	/*char lszRecvBuff[8192] = {0};
	int liRecv = loTcpStream.RecvData(lszRecvBuff,8192,liTimeout);
	if(liRecv <= 0)
	{
		return EHTTP_RECV_ERROR;
	}	*/

	char lszRecvBuff[1024] = {0};
	int liRecv = 0;
	astrRet = "";
	int liError = 0;
	do 
	{
		memset(lszRecvBuff,0,1024);
		liRecv = loTcpStream.RecvData(lszRecvBuff,1023);
		if(liRecv > 0)
		{			
			astrRet += lszRecvBuff;			
			//TRACE(5,"recv htmp res data from fd:"<<liSocket<<",len:"<<liRecv);
		}
		/*else
		{
			TRACE(5,"recv htmp res data error from fd:"<<liSocket
				<<",ret:"<<liRecv<<",error:"<<GetNetError());
		}*/

	} while(liRecv > 0);

	//TRACE(5,"recv data from host:"<<lstrHostIp<<" success!,fd:"<<liSocket<<",len:"<<astrRet.size());

	if(string::npos == astrRet.find("200 OK"))
	{
		return EHTTP_NO_200_OK;
	}

	return EHTTP_SUCCESS;
} 

bool CHttpClient::PostHttpRequest(const string& astrUrl,const string& astrPostContent,string& astrRet)
{
	string lstrHost,lstrPage,lstrParams;
	if(!CHttpClient::ParseUrl(astrUrl,lstrHost,lstrPage,lstrParams))
	{
		return false;
	}

	//format http request header
	stringstream lstrHttpHeader;
	lstrHttpHeader<<"POST " << lstrPage;	
	lstrHttpHeader<<" HTTP/1.0\r\n" 
		<<"Accept: */*\r\n"
		<<"Accept-Language: zh-cn\r\n"
		<<"User-Agent: Mozilla/4.0\r\n"
		<<"Host: "<<lstrHost<<"\r\n"
		<<"Connection: Keep-Alive\r\n" 
		<<"Content-Length:"<<astrPostContent.size()<<"\r\n"
		<<"\r\n"
		<<astrPostContent;

	unsigned short lusHttpPort = 80;	
	string::size_type lPos = lstrHost.find(':');
	if(string::npos != lPos)
	{
		lusHttpPort = atoi(lstrHost.substr(lPos+1).c_str());
		lstrHost = lstrHost.substr(0,lPos);
	}

	string lstrHostIp = lstrHost; 
	//if(inet_addr(lstrHost.c_str()) == 0)
	{
		if(!GetIpByHostName(lstrHost,lstrHostIp))
		{
			return false;
		}
	}


	CTcpStream loTcpStream(10000);	//10 second
	//connect to http server
	if(!loTcpStream.Connect(lstrHostIp.c_str(),lusHttpPort))
	{
		return false;
	}

	//send request
	if(!loTcpStream.SendData(lstrHttpHeader.str().c_str(),(unsigned short)lstrHttpHeader.str().size()))
	{
		return false;
	}

	//recv http response
	char lszRecvBuff[8192] = {0};
	int liRecv = loTcpStream.RecvData(lszRecvBuff,8192);
	if(lszRecvBuff <= 0)
	{
		return false;
	}	

	astrRet = lszRecvBuff;
	if(string::npos == astrRet.find("200 OK"))
	{
		return false;
	}

	return true;
}

unsigned char CHttpClient::CharToHex(const unsigned char &abyChValue)
{
        if(abyChValue > 9)
        { 
                return abyChValue + ('A' - 10);
        }
        else
        {
                return abyChValue + '0';
        }
}

unsigned char CHttpClient::HexToChar(const unsigned char &abyChValue)
{
        if(abyChValue > 64)
        {
                return abyChValue - ('A' - 10);
        }
        else
        {
                return abyChValue - '0';
        }
}

string CHttpClient::UrlEncode(const string& astrData)
{
        std::string lstrData;
        unsigned char ch = 0;
        const char* pszSrc = astrData.c_str();
        for (int i = 0; i < (int)astrData.size(); i++)
        {
                ch = pszSrc[i];

                
                if ( (ch >= '0' && ch <='9')
                        || (ch >= 'a' && ch <= 'z')
                        || (ch >= 'A' && ch <= 'Z'))
                {
                        lstrData += ch;
                }
                else if (' ' == ch)
                {                       
                        lstrData += "+";                        
                }       
                else
                {
                        lstrData += "%";
                        lstrData += CharToHex((ch>>4)&0x0F);
                        lstrData += CharToHex(ch%16);

                }
        }
        return lstrData;
}
string CHttpClient::UrlDecode(const string& astrData)
{
        std::string lstrData = "";
        for (int i = 0; i < (int)astrData.size(); i++)
        {
                if ((astrData.at(i) >= '0' && astrData.at(i) <='9')
                        || (astrData.at(i) >= 'a' && astrData.at(i) <= 'z')
                        || (astrData.at(i) >= 'A' && astrData.at(i) <= 'Z'))
                {
                        lstrData += astrData.at(i);
                }
                else if ('+' == astrData.at(i))
                {                       
                        lstrData += " ";                        
                }       
                else if('%' == astrData.at(i))
                {
                        i++;
                        char ch = HexToChar(astrData.at(i++));
                        ch = ch<<4;
                        ch += HexToChar(astrData.at(i));
                        lstrData += ch;
                }else{
					lstrData += astrData.at(i);
				}
        }
        return lstrData;
}
bool CHttpClient::ParseParams(const string& astrParams,URL_PARAMS& amapParams,
							  const string& astrParamsSep,const string& astrParamValueSep)
{
	string lstrParam,lstrParamName,lstrParamValue;
	string::size_type lStartPos = 0,lValuePos = 0;
	string::size_type lPos = astrParams.find(astrParamsSep);
	while(string::npos != lPos)
	{
		lstrParam = astrParams.substr(lStartPos,lPos - lStartPos);
		lValuePos = lstrParam.find(astrParamValueSep);
		if(string::npos != lValuePos)
		{
			lstrParamName = lstrParam.substr(0,lValuePos);
			lstrParamValue = lstrParam.substr(lValuePos+astrParamValueSep.size());
		}
		else
		{
			lstrParamName = lstrParam;
			lstrParamValue = "";
		}
		amapParams[lstrParamName] = lstrParamValue;
		lStartPos = lPos + astrParamsSep.size();
		lPos = astrParams.find(astrParamsSep,lStartPos);
	}
	if(lStartPos < astrParams.size())
	{
		lstrParam = astrParams.substr(lStartPos);
		lValuePos = lstrParam.find('=');
		if(string::npos != lValuePos)
		{
			lstrParamName = lstrParam.substr(0,lValuePos);
			lstrParamValue = lstrParam.substr(lValuePos+astrParamValueSep.size());
		}
		else
		{
			lstrParamName = lstrParam;
			lstrParamValue = "";
		}
		amapParams[lstrParamName] = lstrParamValue;
	}
	return !amapParams.empty();
}

bool CHttpClient::SplitParams(const string& astrParams,vector<string>& avecParams,const string& astrSep)
{
	string lstrParam;
	string::size_type lStartPos = 0,lValuePos = 0;
	string::size_type lPos = astrParams.find(astrSep);
	while(string::npos != lPos)
	{
		lstrParam = astrParams.substr(lStartPos,lPos - lStartPos);		
		avecParams.push_back(lstrParam);
		lStartPos = lPos + astrSep.size();
		lPos = astrParams.find(astrSep,lStartPos);
	}
	if(lStartPos < astrParams.size())
	{
		lstrParam = astrParams.substr(lStartPos);
		avecParams.push_back(lstrParam);
	}
	return true;
}

string CHttpClient::GetParam(const URL_PARAMS& amapParams,const string& astrParamName)
{
	URL_PARAMS::const_iterator lPos = amapParams.find(astrParamName);
	if(amapParams.end()!= lPos)
	{
		return lPos->second;
	}
	return "";
}
bool CHttpClient::GetHtmlData(const string& astrHtmlRes,string& astrHtmlData)
{
	unsigned int liDataLen = 0;
	string::size_type lPos = astrHtmlRes.find("Content-Length:");
	if(string::npos != lPos)
	{
		string::size_type lLineEndPos = astrHtmlRes.find("\r\n",lPos + strlen("Content-Length:"));
		if(string::npos != lLineEndPos)
		{
			liDataLen = atoi(astrHtmlRes.substr(lPos + strlen("Content-Length:"),lLineEndPos - lPos - strlen("Content-Length:")).c_str());

			lPos = astrHtmlRes.find("\r\n\r\n",lLineEndPos);
			if(astrHtmlRes.size() - liDataLen >= lPos + strlen("\r\n\r\n"))
			{
				astrHtmlData = astrHtmlRes.substr(lPos + strlen("\r\n\r\n"),liDataLen);
				return true;
			}		
		}
	}
	else
	{
		lPos = astrHtmlRes.find("\r\n\r\n");
		if(string::npos != lPos)
		{
			astrHtmlData = astrHtmlRes.substr(lPos + strlen("\r\n\r\n"));
			return true;
		}
	}

	return false;
}

bool CHttpClient::ParseUrl(const string& astrUrl,string& astrHost,string& astrPagePath,string& astrParams)
{
	if(astrUrl.find("http://") != 0)
	{
		return false;
	}
	string::size_type lPos = astrUrl.find('/',7);
	if(string::npos == lPos)
	{
		return false;
	}
	astrHost = astrUrl.substr(7,lPos - 7);
	
	string::size_type lParamPos = astrUrl.find('?',lPos+1);
	if(string::npos == lParamPos)
	{
		astrPagePath = astrUrl.substr(lPos);
		astrParams = "";
	}
	else
	{
		astrPagePath = astrUrl.substr(lPos,lParamPos - lPos);
		astrParams = astrUrl.substr(lParamPos+1);
	}
	
	return true;
}

bool CHttpClient::ParseJsonParams(const string& astrParams,URL_PARAMS& amapParams)
{
	if(astrParams.at(0) == '{' && astrParams.at(astrParams.size()-1) == '}')
	{
		string lstrParamName,lstrParamValue;
	}
	return true;
}

char CHttpClient::Hex2Char(unsigned char abyChValue){
	if(abyChValue < 10){
		return '0' + abyChValue;
	}else{
		return 'A' + abyChValue - 10;
	}        
}

unsigned char CHttpClient::Char2Hex(unsigned char abyChValue){
	if(abyChValue < 'A'){
		return abyChValue - '0';            
	}else{
		return abyChValue - 'A' + 10;
	}
}

string CHttpClient::Raw2HexStr(const char* apData,unsigned int auiDataLen){
	string lstr;
	for(unsigned int i = 0; i < auiDataLen; ++i){
		lstr += Hex2Char((apData[i]>>4)&0x0F);
		lstr += Hex2Char(apData[i]&0x0F);
	}
	return lstr;
}

string CHttpClient::HexStr2Raw(const string& astrData){
	if(astrData.size() % 2 != 0)
		return "";
	string lstr;
	char ch;
	for(unsigned int i = 0; i < astrData.size(); i+=2){
		ch = Char2Hex(astrData[i])<<4;
		ch |= Char2Hex(astrData[i+1]);
		lstr += ch; 
	}
	return lstr;
}
