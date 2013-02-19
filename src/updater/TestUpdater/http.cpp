#include "http.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

CProxyInfo::CProxyInfo()
{
}
CProxyInfo::~CProxyInfo()
{

}

void CProxyInfo::GetIEProxyInfo()
{
	DWORD length = 4096;
	char buffer[4096] = {0};

	INTERNET_PROXY_INFO *pInfo = (INTERNET_PROXY_INFO*)buffer;
	if (!::InternetQueryOption(NULL, INTERNET_OPTION_PROXY, pInfo, &length))
	{
		PrintLog(_LOG_LEVEL_DEBUG, ("%s(%d) 查询IE代理失败"), __FILE__, __LINE__);
		return;
	}

	//获取代理设置
	if (pInfo->dwAccessType != INTERNET_OPEN_TYPE_DIRECT)
	{
		char *p = (char*)pInfo->lpszProxy;
		assert(p != NULL);
		std::string strInfo = p;
		if (strInfo.empty())
		{
			PrintLog(_LOG_LEVEL_DEBUG, "%s(%d) IE没有代理信息", __FILE__, __LINE__);
			return;
		}

		int start = 0;
		int end = 0;
		int CurrentLen = 0;

		end = (int)strInfo.find_first_of(':');
		m_ip = strInfo.substr(start, end);
		m_port = atoi((strInfo.substr(end + 1, strInfo.length() - end + 1)).c_str());
		PrintLog(_LOG_LEVEL_DEBUG, "%s(%d), proxy info ip = %s, port = %d", __FILE__, __LINE__, m_ip.c_str(), m_port);
	}

	//获取代理用户名,密码
	GetIEProxyPassword();
}

void CProxyInfo::GetIEProxyPassword()
{
	typedef HRESULT (WINAPI *tPStoreCreateInstance)(IPStore **, DWORD, DWORD, DWORD);
	HMODULE hpsDLL; 
	hpsDLL = LoadLibrary(_T("pstorec.dll"));

	tPStoreCreateInstance pPStoreCreateInstance;
	pPStoreCreateInstance = (tPStoreCreateInstance)GetProcAddress(hpsDLL, ("PStoreCreateInstance"));

	IPStorePtr PStore; 
	HRESULT hRes = pPStoreCreateInstance(&PStore, 0, 0, 0); 

	IEnumPStoreTypesPtr EnumPStoreTypes;
	hRes = PStore->EnumTypes(0, 0, &EnumPStoreTypes);
	if (!FAILED(hRes))
	{
		GUID TypeGUID;
		char szItemName[512];       
		char szItemData[512];
		char szResName[1512];
		char szResData[512];
		char szItemGUID[50];
		while(EnumPStoreTypes->raw_Next(1,&TypeGUID,0) == S_OK)
		{
			sprintf((szItemGUID),("%x"),TypeGUID);

			IEnumPStoreTypesPtr EnumSubTypes;
			hRes = PStore->EnumSubtypes(0, &TypeGUID, 0, &EnumSubTypes);

			GUID subTypeGUID;
			while(EnumSubTypes->raw_Next(1,&subTypeGUID,0) == S_OK)
			{
				IEnumPStoreItemsPtr spEnumItems;
				HRESULT hRes = PStore->EnumItems(0, &TypeGUID, &subTypeGUID, 0, &spEnumItems);//用来获取项 

				LPWSTR itemName;
				while(spEnumItems->raw_Next(1,&itemName,0) == S_OK)
				{
					sprintf(szItemName,("%ws"),itemName);
					char chekingdata[200];
					unsigned long psDataLen = 0;
					unsigned char *psData = NULL;
					_PST_PROMPTINFO *pstiinfo = NULL;
					hRes = PStore->ReadItem(0,&TypeGUID,&subTypeGUID,itemName,&psDataLen,&psData,pstiinfo,0);
					if (lstrlen(((char*)psData)) < (int)(psDataLen - 1))
					{
						int i = 0;
						for(int m = 0; m < (int)psDataLen; m+=2)
						{
							if (psData[m] == 0)
								szItemData[i] = ',';
							else
								szItemData[i] = psData[m];
							i++;
						}
						szItemData[i-1] = 0;
					}
					else
					{
						sprintf(szItemData,"%s",psData);
					}
					lstrcpy(szResName,_T(""));
					lstrcpy(szResData,_T(""));
					if(lstrcmp(szItemGUID,_T("5e7e8100")) == 0)
					{ 
						lstrcpy(chekingdata,""); 
						if(strstr(szItemData,":") != 0) 
						{ 
							lstrcpy(chekingdata,strstr(szItemData,":") + 1); 
							*(strstr(szItemData,":")) = 0; 
						}
						std::strstream ss;
						ss<<m_port<<ends;
						if (strstr(szItemName, m_ip.c_str()) != 0 && strstr(szItemName, ss.str()) != 0)
						{
							m_user = szItemData;
							m_password = chekingdata;
						}
					} 
					ZeroMemory(szItemName,sizeof(szItemName));
					ZeroMemory(szItemData,sizeof(szItemData));
					if (!m_user.empty())
					{
						PrintLog(_LOG_LEVEL_DEBUG, "%s:%s", m_user.c_str(), m_password.c_str());
						break;
					}
				}
			}
		}
	}
}


bool CProxyInfo::IsValidProxy() const
{
	return !m_ip.empty();	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

CHttpBase::CHttpBase(WINNET_STATE_FUN fun, HTTP_METHOD method /*= HTTP_GET*/)
:m_hSession(NULL), m_hConnect(NULL), m_hRequest(NULL)
{
	m_pStateFun = fun;
	m_hEvent = NULL;
	m_hEventRead = NULL;
	m_hThread = NULL;
	m_dwThreadId = 0;
	m_strHost = "";
	m_strReferer = "";
	if (method == HTTP_GET)
		m_strMethod = "GET";
	else if (method == HTTP_POST)
		m_strMethod = "POST";
}


CHttpBase::~CHttpBase()
{
	if (m_dwThreadId != 0)
	{
		assert(m_hThread != NULL);
		//::PostThreadMessage(m_dwThreadId, WM_THREAD_RTN, NULL, NULL);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

void CHttpBase::SetReferer(std::string &referer)
{
	m_strReferer = referer;
}

bool CHttpBase::Add(const char* pcszUrl, const char* pcszFilePath)
{
	FileInfo Info;
	Info.path = pcszFilePath;
	std::string strUrlFile = "";
	HttpGetName(pcszUrl, m_strHost, strUrlFile);

	Info.url = strUrlFile;
	m_FileListLock.lock();
	m_FileList.push_back(Info);
	m_FileListLock.unlock();

	if (m_hThread == NULL)
	{
		m_hThread = ::CreateThread(NULL, 0, ExecuteFun, this, 0, &m_dwThreadId);
		if (m_hThread == NULL)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "创建下载线程失败");
			return false;
		}
	}
	/*
	std::strstream str;
	str<<strUrlFile<<"  加入下载队列"<<" 本地地址 "<<pcszFilePath<<ends;
	m_pStateFun((void*)str.str());*/

	return true;
}

DWORD CHttpBase::ExecuteFun(void *p)
{
	CHttpBase *pHttpBase = (CHttpBase*)p;
	if (pHttpBase->ConnectServer())
	{
		pHttpBase->Execute();
	}
	pHttpBase->Close();
	return 0;
}
bool CHttpBase::Execute(void)
{
	try
	{
		m_FileListLock.lock();
		bool bFlag = m_FileList.empty();
		m_FileListLock.unlock();
		if (bFlag) return true;

		FILE_ITER iter;
		bFlag = false;
		while(true)
		{
			MSG msg;
			::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
			//if (msg.message == WM_THREAD_RTN)
			//	break;

			m_FileListLock.lock();
			iter = m_FileList.begin();
			m_FileListLock.unlock();

			FileInfo info = (FileInfo)(*iter);
			//INTERNET_FLAG_SECURE  ----设置标志为HTTPS
			//https://url.....
			DWORD dwOpenFlags = INTERNET_FLAG_NEED_FILE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION;
			LPCSTR szAcceptType[]= { "*/*", 0 };
			m_hRequest = ::HttpOpenRequest(m_hConnect, (m_strMethod.c_str()), 
				(info.url.c_str()), _T("HTTP/1.1"), m_strReferer.empty() ? NULL : m_strReferer.c_str(), 
				szAcceptType, dwOpenFlags, (DWORD_PTR)this);
			if (m_hRequest == NULL)
			{
				PrintLog(_LOG_LEVEL_DEBUG, "HttpOpenRequest error code = %d", GetLastError());
				return false;
			}

			ResetEvent(m_hEvent);
			BOOL bRet = ::HttpSendRequest(m_hRequest, NULL, 0, 0, 0);
			if (!bRet)
			{
				DWORD dwErrorCode = GetLastError();
				if (dwErrorCode != ERROR_IO_PENDING)
				{
					PrintLog(_LOG_LEVEL_DEBUG, "HttpSendRequest error code = %d, Info ERROR_FILE_NOT_FOUND", dwErrorCode);
					return false;
				}
			}

			if (!WaitForEnd(m_hEvent)) return false;
			ResetEvent(m_hEvent);


			char buffer[MAX_PACK_SIZE + 1];

			int nInternetFileSize = 0;
			HttpGetFileInfo(nInternetFileSize);
			PrintLog(_LOG_LEVEL_DEBUG, "下载文件大小：%d", nInternetFileSize);
			int nReadedSize = 0;

			//如果文件已经存在就直接删除
			remove(info.path.c_str());
			ofstream out(info.path.c_str(), ios::app|ios::binary|ios::out);

			::ResetEvent(m_hEventRead);
			while(nReadedSize < nInternetFileSize)
			{
				memset(buffer, 0, (MAX_PACK_SIZE + 1) * sizeof(char));
				DWORD dwReadSize = 0;
				//DWORD dwHttpFilePos = ::InternetSetFilePointer(m_hRequest, nReadedSize, NULL, FILE_BEGIN, 0);
				//if(nReadedSize != dwHttpFilePos)
				//{
				//	PrintLog(_LOG_LEVEL_DEBUG, "设置下载位置失败");
				//	continue;
				//}

				assert(m_hRequest != NULL);
				bRet = ::InternetReadFile(m_hRequest, buffer, MAX_PACK_SIZE, &dwReadSize);
				if (!bRet)
				{
					bRet = GetLastError();
					if (bRet != ERROR_IO_PENDING)
					{
						PrintLog(_LOG_LEVEL_DEBUG, "InternetReadFile error code = %d", bRet);
						break;
					}
				}

				if  (dwReadSize > 0)
				{
					out.write(buffer, dwReadSize);
					nReadedSize += dwReadSize;
					PrintLog(_LOG_LEVEL_DEBUG, "下载数据包总大小: %d", nReadedSize);
				}
				//assert(dwReadSize != 0);
				//if (!WaitForEnd(m_hEventRead, 1000)) break;
				//if (WaitForEnd(m_hEventRead, 100)) break;
			}

			out.close();

			m_FileListLock.lock();
			m_FileList.erase(iter);
			if (m_FileList.empty())
				bFlag = true;
			m_FileListLock.unlock();

			if (bFlag) break;
			Sleep(100);
		}

	}
	catch (...)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "异常");
		return false;
	}
	return true;
}


bool CHttpBase::ConnectServer(void)
{
	DWORD dwAccessType = 0;
	char *name = NULL;
	char *password = NULL;

	if (m_ProxyInfo.IsValidProxy())
	{
		dwAccessType = INTERNET_OPEN_TYPE_PROXY;
		password = const_cast<char*>(m_ProxyInfo.m_password.c_str());
	} 
	else 
	{
		dwAccessType = INTERNET_OPEN_TYPE_DIRECT;
		name =  const_cast<char*>(m_ProxyInfo.m_user.c_str());
	}

	m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_hEvent != NULL);

	m_hEventRead = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_hEventRead != NULL);

	assert(m_hSession == NULL);
	m_hSession = ::InternetOpen(_T("_xnt_download_"), dwAccessType, (name), (password), INTERNET_FLAG_ASYNC);
	if (m_hSession == NULL)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "InetnetOpen error code = %d", GetLastError());
		return false;
	}

	//MSDN: 回调函数必须执行的时间很短，不然就会将连接关闭。
	//建议：回调函数和创建函数在不同线程
	INTERNET_STATUS_CALLBACK Rtn = ::InternetSetStatusCallback(m_hSession, 
		(INTERNET_STATUS_CALLBACK)CHttpBase::InternetCallback);
	if (Rtn == INTERNET_INVALID_STATUS_CALLBACK)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "InternetSetStatusCallback error");
		return false;
	}

	m_hConnect = ::InternetConnect(m_hSession, m_strHost.c_str(), 
		INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, (DWORD_PTR)this);

	if (m_hConnect == NULL)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "InternetConnect error code = %d", GetLastError());
		return false;
	}
	if (!WaitForEnd(m_hEvent)) return false;
	::ResetEvent(m_hEvent);

	return true;
}

bool CHttpBase::Close(void)
{
	m_FileListLock.lock();
	int nSize = (int)m_FileList.size();
	m_FileListLock.unlock();
	if (nSize != 0) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "文件没有下载完,还剩余%d个文件", nSize);
		return false;
	}

	assert(m_hEvent != NULL);
	::CloseHandle(m_hEvent);

	assert(m_hEventRead != NULL);
	::CloseHandle(m_hEventRead);

	assert(m_hSession != NULL);
	//注销回调函数
	::InternetSetStatusCallback(m_hSession, NULL);

	//释放句柄和相关的资源
	::InternetCloseHandle(m_hSession);
	m_hSession = NULL;

	//释放句柄和相关的资源
	if (m_hConnect != NULL)
	{
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
	}

	//释放句柄和相关的资源
	if (m_hRequest != NULL)
	{
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
	}

	return true;
}


void CALLBACK CHttpBase::InternetCallback(HINTERNET hInternet, DWORD_PTR dwContext, 
										  DWORD dwInternetStatus, LPVOID lpvStatusInformation, 
										  DWORD dwStatusInformationLength)
{
	CHttpBase *pHttpBase = (CHttpBase*)(dwContext);
	switch(dwInternetStatus)
	{
	case INTERNET_STATUS_CLOSING_CONNECTION:
		{
			assert(lpvStatusInformation == NULL);
			break;
		}
	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		{
			SOCKADDR_IN *pAddr = static_cast<SOCKADDR_IN*>(lpvStatusInformation);
			PrintLog(_LOG_LEVEL_DEBUG, "成功连接%s:%d", inet_ntoa(pAddr->sin_addr), ntohs(pAddr->sin_port));
			break;
		}
	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		{
			SOCKADDR_IN *pAddr = static_cast<SOCKADDR_IN*>(lpvStatusInformation);
			PrintLog(_LOG_LEVEL_DEBUG, "正在连接%s:%d", inet_ntoa(pAddr->sin_addr), ntohs(pAddr->sin_port));
			break;
		}
	case INTERNET_STATUS_CONNECTION_CLOSED:
		{
			assert(lpvStatusInformation == NULL);
			PrintLog(_LOG_LEVEL_DEBUG, "已经断开和服务器的连接");
			break;
		}
		//cookie 暂不用
	case INTERNET_STATUS_COOKIE_HISTORY:
		{
			break;
		}
	case INTERNET_STATUS_COOKIE_RECEIVED:
		{
			break;
		}
	case INTERNET_STATUS_COOKIE_SENT:
		{
			break;
		}
		//?
	case INTERNET_STATUS_CTL_RESPONSE_RECEIVED:
		{

			break;
		}
	case INTERNET_STATUS_DETECTING_PROXY:
		{
			PrintLog(_LOG_LEVEL_DEBUG, "已经检测到代理服务器");
			break;
		}
	case INTERNET_STATUS_HANDLE_CLOSING:
		{
			//哪个句柄
			PrintLog(_LOG_LEVEL_DEBUG, "句柄已经关闭");
			break;
		}
	case INTERNET_STATUS_HANDLE_CREATED:
		{
			//InternetConnect成功返回,在句柄创建地方不要忘记调用InternetCloseHandle关闭句柄
			LPINTERNET_ASYNC_RESULT pRet = static_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
			//if (pRet->dwError != ERROR_SUCCESS)
			//{
			//	PrintLog(_LOG_LEVEL_DEBUG, "创建句柄失败, 错误码是%d", pRet->dwError);
			//}
			//else
			//{
			::SetEvent(pHttpBase->m_hEvent);
			//}

			break;
		}
		//?
	case INTERNET_STATUS_INTERMEDIATE_RESPONSE:
		{
			break;
		}
		//成功找到服务器地址
	case INTERNET_STATUS_NAME_RESOLVED:
		{
			SOCKADDR_IN *pAddr = static_cast<SOCKADDR_IN*>(lpvStatusInformation);
			PrintLog(_LOG_LEVEL_DEBUG, "服务器地址%s:%d", inet_ntoa(pAddr->sin_addr), ntohs(pAddr->sin_port));
			break;
		}
		//未用
	case INTERNET_STATUS_P3P_HEADER:
		{

			break;
		}
		//Not implemented.
	case INTERNET_STATUS_P3P_POLICYREF:
		{
			break;
		}
		//Not implemented.
	case INTERNET_STATUS_PREFETCH:
		{
			break;
		}
		//Not implemented.
	case INTERNET_STATUS_PRIVACY_IMPACTED:
		{
			break;
		}
	case INTERNET_STATUS_RECEIVING_RESPONSE:
		{
			assert(lpvStatusInformation == NULL);
			//PrintLog(_LOG_LEVEL_DEBUG, "等待服务器回复");
			break;
		}
		//URL连接地址改变通知
		//在这个类中不会改变服务器地址，只从一个服务器里下载数据，
		//如果想从其他服务器下栽数据重新创建一个CHttpBase实例
		//理解错误。。。。。。。。。。。
		//改变URL地址
	case INTERNET_STATUS_REDIRECT:
		{
			break;
		}
		//完成异步操作
	case INTERNET_STATUS_REQUEST_COMPLETE:
		{
			LPINTERNET_ASYNC_RESULT pRet = static_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
			//if (pRet->dwError != ERROR_SUCCESS)
			//{
			//	PrintLog(_LOG_LEVEL_DEBUG, "完成异步操作失败, 错误码是%d", pRet->dwError);
			//}
			//else
			//{
			//pHttpBase->m_hRequest = HINTERNET(LPINTERNET_ASYNC_RESULT(lpvStatusInformation)->dwResult);
			SetEvent(pHttpBase->m_hEvent);
			//}
			break;
		}
	case INTERNET_STATUS_REQUEST_SENT:
		{
			PrintLog(_LOG_LEVEL_DEBUG, "成功发送数据给服务器，数据个数%d", *(DWORD*)(lpvStatusInformation));
			break;
		}
	case INTERNET_STATUS_RESOLVING_NAME:
		{
			SOCKADDR_IN *pAddr = static_cast<SOCKADDR_IN*>(lpvStatusInformation);
			PrintLog(_LOG_LEVEL_DEBUG, "查找服务器地址%s:%d", inet_ntoa(pAddr->sin_addr), ntohs(pAddr->sin_port));
			break;
		}
	case INTERNET_STATUS_RESPONSE_RECEIVED:
		{
			static int a;
			a += *(DWORD*)(lpvStatusInformation);
			PrintLog(_LOG_LEVEL_DEBUG, "从服务器接受数据，数据个数%d %d", *(DWORD*)(lpvStatusInformation), a);
			::SetEvent(pHttpBase->m_hEventRead);
			break;
		}
	case INTERNET_STATUS_SENDING_REQUEST:
		{
			assert(lpvStatusInformation == NULL);
			PrintLog(_LOG_LEVEL_DEBUG, "发送请求信息到服务器");
			break;
		}
	case INTERNET_STATUS_STATE_CHANGE:
		{
			break;
		}
	default:
		{
			PrintLog(_LOG_LEVEL_DEBUG, "未知状态");
			assert(false);
			break;
		}
	}
}


int CHttpBase::WaitForEnd(HANDLE &handle, DWORD timeout /* = 30*1000 */)
{
	//所有事件超时为1秒
	DWORD dwTimeOut = timeout;
	DWORD dwRet = 0;

	dwRet = ::WaitForSingleObject(handle, dwTimeOut);
	if (dwRet == WAIT_OBJECT_0)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "下载等待事件被激活");
		return 1;
	}
	else if (dwRet == WAIT_TIMEOUT)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "下载等待事件超时");
		return 0;
	}
	else if (dwRet == WAIT_FAILED)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "下载等待事件错误: %d", GetLastError());
		return 0;
	}
	return 0;
}

void CHttpBase::HttpGetName(string strURL, string &strHostName, string &strFileName) const
{
	int pos = static_cast<int>(strURL.find("http://"));
	if (pos != -1)
	{
		strURL.erase(pos, 7);
		pos = static_cast<int>(strURL.find_first_of('/'));
		strHostName = strURL.substr(0, pos);
		strFileName = strURL.substr(pos, strURL.size());
	}
}
BOOL CHttpBase::HttpGetFileInfo(int &nFileSize)
{
	const int nFileInfoLen = MAX_PACK_SIZE;
	char *pszFileInfo = new char[nFileInfoLen];
	memset(reinterpret_cast<void*>(pszFileInfo), 0, nFileInfoLen);
	DWORD dwBufLength = MAX_PACK_SIZE;
	DWORD dwIndex = 0;

	BOOL iRet = HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_LENGTH, reinterpret_cast<void*>(pszFileInfo), &dwBufLength, &dwIndex);
	if(!iRet)
	{
		delete [] pszFileInfo;
		pszFileInfo = NULL;
		return FALSE;
	}
	//获取文件大小
	nFileSize = StrToInt(pszFileInfo);
	delete [] pszFileInfo;
	pszFileInfo = NULL;
	return TRUE;
}