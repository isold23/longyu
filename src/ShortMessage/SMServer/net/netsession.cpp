#include "stdafx.h"
#include "netsession.h"

net::CWinInit g_WinInit;

CNetSession::CNetSession(void)
{
	Init();
}

CNetSession::~CNetSession(void)
{
	Init();
}

bool CNetSession::StartServer(void)
{
	PrintLog(_LOG_LEVEL_DEBUG, "开始监听网络\n");
	assert(!m_bListen);
	assert(m_nThreadId);
	BOOL bRet = PostThreadMessage(m_nThreadId, WM_START, 0, 0);
#ifdef NEED_LOG
	PrintLog(_LOG_LEVEL_DEBUG, "Start server listen.............");
#endif 
	if (bRet)return true;
	return false;
}

bool CNetSession::StopServer(void)
{
	PrintLog(_LOG_LEVEL_DEBUG, "结束监听网络\n");
	assert(m_bListen);
	assert(m_nThreadId);
	BOOL bRet = PostThreadMessage(m_nThreadId, WM_STOP, 0, 0);
#ifdef NEED_LOG
	PrintLog(_LOG_LEVEL_DEBUG, "Stop server listen.............");
#endif
	if (bRet) return true;
	return false;
}

bool CNetSession::StartServerListen(void)
{
	string ip = "";
	short port = 0;

	m_XmlConfig.GetServerInfo(ip, port);
	PrintLog(_LOG_LEVEL_DEBUG, "网络监听端口：%d\n", port);

	net::CSocketAddr addr(ADDR_ANY, port);
	bool nRet = m_sock.Create(addr);
	if (!nRet) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "CREATE SOCKET FAILED\n");
		return false;
	}
	nRet = m_sock.Bind();
	if (!nRet) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "BIND SOCKET FAILED\n");
		return false;
	}
	nRet = m_sock.Listen();
	if (!nRet) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "LISTEN FAILED\n");
		return false;
	}
	m_Event = m_sock;
	return true;
}

bool CNetSession::StopServerListen(void)
{
	m_Event.CloseAllEvent();
	return true;
}

bool CNetSession::RecvMsg(void)
{
	//static char buf = new char [];
	return true;
}

DWORD CNetSession::WorkItem(LPVOID param)
{
	assert(param != NULL);
	PrintLog(_LOG_LEVEL_DEBUG, "监听线程ID =  %d\n", ::GetCurrentThreadId());

	CNetSession *pNetSession = static_cast<CNetSession*>(param);
	MSG msg;
	try
	{
		while(true)
		{
			BOOL bRet = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			if (bRet)
			{
				switch (msg.message)
				{
				case WM_START:
					{
						if (pNetSession->StartServerListen())
						{
							pNetSession->m_bListen = true;
							break;
						}
						else
							throw "Start server error";
					}
				case WM_STOP:
					{
						pNetSession->m_bListen = false;
						pNetSession->StopServerListen();
						throw "Stop server";
					}
				default:
					{
						throw "Has unknow thread message";
						break;
					}
				}
			}


			//处理网络事件
			if (pNetSession->m_bListen)
			{
			int nRet = pNetSession->m_Event.DoNetEvent();
			if (nRet == net::CNetEvent::READ)
				pNetSession->RecvMsg();

			//线程池发送数据包

			}
			Sleep(100);
		}
	}
	catch (char *exception)
	{
		PrintLog(_LOG_LEVEL_DEBUG, exception);
	}
	catch(...)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "Server thread has exception");
	}
	pNetSession->StopServerListen();
	return 0;
}