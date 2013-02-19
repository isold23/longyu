#include "StdAfx.h"
#include ".\httpdownload.h"
#include "..\..\..\..\include\common\common.h"

///////////////////////////////////////////////////////////////////////////////////////////////

CHttpDownload::CHttpDownload(void)
{
	m_thread = NULL;
	m_strFilePath =  "";
	m_hHandle = NULL;
	m_nHttpError = HTTP_FAIL;
	m_nFlag = METHOD_DOWNLOAD;
}

CHttpDownload::~CHttpDownload(void)
{

}

bool CHttpDownload::DownloadFile(std::string strUrl, std::string strFilePath)
{
	m_nFlag = METHOD_DOWNLOAD;
	SetUrl(strUrl);
	CDownload::AnalyseUrl(strUrl, CDownload::m_strServer, CDownload::m_strFileName);
	m_strFilePath = strFilePath;
	ReadInternetFile();
	return true;
}

bool CHttpDownload::UploadFile(std::string strUrl, std::string strFilePath)
{
	m_nFlag = METHOD_UPLOAD;
	SetUrl(strUrl);
	CDownload::AnalyseUrl(strUrl, CDownload::m_strServer, CDownload::m_strFileName);
	m_strFilePath = strFilePath;
	WriteInternetFile();
	return true;
}

bool CHttpDownload::ReadInternetFile(void)
{
	//在线程中下载
	if (Start())
	{
		//设置超时
		int nReturn = WaitForEnd(INFINITE);
		Stop();
#ifdef NEED_LOG
		strstream strlog;
		strlog<<"error = "<<m_nHttpError<<ends<<endl;
		log::printlog(strlog.str());
#endif
		//cout<<"error : "<<m_nHttpError<<endl;
		if (nReturn == 0)
		{
			return true;
		}
		else if(nReturn == 1)
		{
#ifdef NEED_LOG
			log::printlog("Download file timeout!!!!");
#endif
			return false;
		}
	}
	return false;
}

bool CHttpDownload::WriteInternetFile(void)
{
	//在线程中下载
	if (Start())
	{
		//设置超时
		int nReturn = WaitForEnd(INFINITE);
		Stop();
#ifdef NEED_LOG
		strstream strlog;
		strlog<<"error = "<<m_nHttpError<<ends<<endl;
		log::printlog(strlog.str());
#endif
		//cout<<"error : "<<m_nHttpError<<endl;
		if (nReturn == 0)
		{
			return true;
		}
		else if(nReturn == 1)
		{
#ifdef NEED_LOG
			log::printlog("Download file timeout!!!!");
#endif
			return false;
		}
	}
	return false;
}


bool CHttpDownload::Connect(void)
{
	if (!OnConnect())
	{
		return false;
	}
	return true;
}

bool CHttpDownload::Close(void)
{
	OnClose();
	return true;
}

bool CHttpDownload::ReadInternetFileFun(CHttpDownload *pHttpDownload)
{
	char *buffer = new char[HTTP_MAX_BUFFER + 1024];
	string strFileName(pHttpDownload->m_strFilePath);
	code_common::CPathName path(pHttpDownload->GetUrl());
	strFileName += "s.gif";
	CFileBase file(strFileName.c_str());
	const std::string strMark = "\r\n\r\n";
	std::string strHttpRequest = "";

	int nFileSize = file.GetFileSize();
	if (!pHttpDownload->Connect())
	{
		file.Close();
		pHttpDownload->Close();
		delete [] buffer;
		buffer = NULL;
		pHttpDownload->m_nHttpError =  HTTP_CONNECT_ERROR;
		return 0;
	}

	int nReadFileSize = 0;
	int nInternetFileSize = 0;
	bool bIsFirst = true;

	strHttpRequest.clear();

	//文件断点续传
	m_nRangeStart = nFileSize;

	int length = pHttpDownload->HttpRequest(strHttpRequest);
	if (pHttpDownload->OnSend(strHttpRequest.c_str(), length))
	{
		MSG msg;
		while(true)
		{
			BOOL MsgReturn = ::PeekMessage(&msg, NULL, 0, 0,PM_REMOVE);
			if (MsgReturn)
			{
				switch (msg.message)
				{
				case THREAD_RETURN:
					{
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}

			memset(buffer, 0, HTTP_MAX_BUFFER + 1024);
			int length = HTTP_MAX_BUFFER;
			if (pHttpDownload->OnRecv(buffer, length))
			{
				if (bIsFirst)
				{
					char *iter = search(buffer, buffer + length, strMark.begin(), strMark.end());
					std::string strHttpResponse(buffer, iter + 4);
					int len = static_cast<int>(strHttpResponse.length());
					int nReturn = pHttpDownload->HttpResponse(strHttpResponse);
					if (nReturn == -1)
					{
#ifdef NEED_LOG
						log::printlog("Download file error!!!\n");
#endif
						pHttpDownload->m_nHttpError = HTTP_REQUEST_ERROR;
						break;
					}
					else if(nReturn == 416)
					{
						pHttpDownload->m_nHttpError = 416;
						break;
					}
					file.Write(iter + 4, length - len);
					nReadFileSize += length - len;
					bIsFirst = false;
				}
				else
				{
					file.Write(buffer, length);
					nReadFileSize += length;

				}

				if (m_nIternetFileSize == nReadFileSize)
				{
					pHttpDownload->m_nHttpError = HTTP_SUCCESS;
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				//网络中断的还没有考虑
#ifdef NEED_LOG
				log::printlog("Receive file from server error!!!");
#endif
				break;
			}
		}
	}
	else
	{
#ifdef NEED_LOG
		log::printlog("Send http request failed!!!");
#endif
		pHttpDownload->m_nHttpError = HTTP_SEND_REQUEST_ERROR;
	}

	file.Close();
	pHttpDownload->Close();
	delete [] buffer;
	buffer = NULL;
	return 0;
}

bool CHttpDownload::WriteInternetFileFun(CHttpDownload *pHttpUpload)
{
	char *buffer = new char[HTTP_MAX_BUFFER + 1024];
	CFileBase file(pHttpUpload->m_strFilePath);
	const std::string strMark = "\r\n\r\n";
	std::string strHttpRequest = "";

	int nFileSize = file.GetFileSize();
	//char *buffer = new char[1024 * 10];
	int length = 1024 * 10;
	file.Read(buffer, length);
	if (!pHttpUpload->Connect())
	{
		file.Close();
		pHttpUpload->Close();
		delete [] buffer;
		buffer = NULL;
		pHttpUpload->m_nHttpError =  HTTP_CONNECT_ERROR;
		return 0;
	}

	int nReadFileSize = 0;
	int nInternetFileSize = 0;
	bool bIsFirst = true;

	strHttpRequest.clear();

	//文件断点续传
	m_nRangeStart = nFileSize;

	length = pHttpUpload->HttpRequest(strHttpRequest, METHOD_POST, buffer, length);
	if (pHttpUpload->OnSend(strHttpRequest.c_str(), length))
	{
		MSG msg;
		while(true)
		{
			BOOL MsgReturn = ::PeekMessage(&msg, NULL, 0, 0,PM_REMOVE);
			if (MsgReturn)
			{
				switch (msg.message)
				{
				case THREAD_RETURN:
					{
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}

			memset(buffer, 0, HTTP_MAX_BUFFER + 1024);
			int length = HTTP_MAX_BUFFER;
			if (pHttpUpload->OnRecv(buffer, length))
			{
				if (bIsFirst)
				{
					char *iter = search(buffer, buffer + length, strMark.begin(), strMark.end());
					std::string strHttpResponse(buffer, iter + 4);
					int len = static_cast<int>(strHttpResponse.length());
					int nReturn = pHttpUpload->HttpResponse(strHttpResponse);
					if (nReturn == -1)
					{
#ifdef NEED_LOG
						log::printlog("Download file error!!!\n");
#endif
						pHttpUpload->m_nHttpError = HTTP_REQUEST_ERROR;
						break;
					}
					else if(nReturn == 416)
					{
						pHttpUpload->m_nHttpError = 416;
						break;
					}
					file.Write(iter + 4, length - len);
					nReadFileSize += length - len;
					bIsFirst = false;
				}
				else
				{
					file.Write(buffer, length);
					nReadFileSize += length;

				}

				if (m_nIternetFileSize == nReadFileSize)
				{
					pHttpUpload->m_nHttpError = HTTP_SUCCESS;
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				//网络中断的还没有考虑
#ifdef NEED_LOG
				log::printlog("Receive file from server error!!!");
#endif
				continue;
			}
		}
	}
	else
	{
#ifdef NEED_LOG
		log::printlog("Send http request failed!!!");
#endif
		pHttpUpload->m_nHttpError = HTTP_SEND_REQUEST_ERROR;
	}

	file.Close();
	pHttpUpload->Close();
	delete [] buffer;
	buffer = NULL;
	return 0;
}

DWORD WINAPI CHttpDownload::ThreadWorkItem(void* parameter)
{
	CHttpDownload *pHttpDownload = reinterpret_cast<CHttpDownload*>(parameter);

	if (pHttpDownload->m_nFlag == METHOD_DOWNLOAD)
	{
		pHttpDownload->ReadInternetFileFun(pHttpDownload);
	}
	else if (pHttpDownload->m_nFlag == METHOD_UPLOAD)
	{
		pHttpDownload->WriteInternetFileFun(pHttpDownload);
	}
	return 0;
}