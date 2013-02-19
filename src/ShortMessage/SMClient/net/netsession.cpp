#include "stdafx.h"
#include "netsession.h"

CNetSession::CNetSession(void)
{
	Init();
}

CNetSession::~CNetSession(void)
{
	Init();
}

void CNetSession::SetRecvHandle(CReceiver &recv)
{
	m_hRecv = recv;
}

bool CNetSession::SendMsgBuffer(const CSendMsg &msg)
{
	if (!m_bConnect)return false;
	if (m_hThread == NULL) return false;
	CMsgBuffer *p = new CMsgBuffer();

	BOOL bRet = ::PostThreadMessage(m_nThreadId, WM_SEND, (WPARAM)(p), 0);
	if (!bRet)return false;
	return true;
}

bool CNetSession::SendMsgBuffer(const char *buf, const int len)
{
	assert(buf != NULL);
	if (!m_bConnect)return false;
	int nRet = m_sock.SendMsg(buf, len);
	if (nRet < 0) return false;
	return true;
}

bool CNetSession::DoReceive(void)
{
	try
	{
		int nRet = m_Event.DoEvent();
		if (nRet == CNetEvent::READ)
		{
			static char szTempBuffer[PACKLEN];
			static int nCurrentLen;
			CSocketAddr addr;
			while(true)
			{
				nRet = m_sock.RecvMsg(szTempBuffer + nCurrentLen, 
					PACKLEN - nCurrentLen, &addr);
				if (nRet == 0)
					return true;
				if (nRet > 0)
				{
					char *pStart = szTempBuffer;
					nCurrentLen += nRet;
					CHeader header;
					memcpy(&header, szTempBuffer, sizeof(CHeader));
					if (header.prefix != PREFIX)
						throw "Receive bad pack";
					int nLen = header.length;
					if (nLen > PACKLEN)
						throw "Receive pack too big";
					nRet = m_hRecv.OnRecvMsg(CMsgBuffer(szTempBuffer, nLen));
					memmove(szTempBuffer, pStart + nLen, (PACKLEN - nLen));
					nCurrentLen -= nLen;
					assert(nCurrentLen >= 0);
				}
			}
		}
		else if (nRet == CNetEvent::CLOSE)
		{
			throw "Receive close event";
		}
		else if (nRet == CNetEvent::CONNECT)
		{
			return true;
		}
		else 
		{
			throw "Do event has exception";
		}
	}
	catch(char *error)
	{
		PrintLog(_LOG_LEVEL_DEBUG, error);
		return false;
	}
	catch(...)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "Has exception when do receive");
		return false;
	}
	return true;
}

bool CNetSession::Connect()
{
	if (m_bConnect)return true;
	if (m_hThread == NULL) return false;
	BOOL bRet = ::PostThreadMessage(m_nThreadId, WM_CONNECT, 0, 0);
	if (!bRet) return false;
	return true;
}

bool CNetSession::Connect(string ip, short port)
{
	bool bRet = m_sock.Create(CSocketAddr(ip, port));
	m_sock.Setopt();
	m_Event = m_sock;
	bRet = m_sock.Connect();
	return true;
}

bool CNetSession::Disconnect()
{
	if (!m_bConnect)return true;
	if (m_hThread == NULL) return false;
	BOOL bRet = ::PostThreadMessage(m_nThreadId, WM_DISCONNECT, 0, 0);
	if (!bRet) return false;
	return true;
}

bool CNetSession::Disconnect(bool IsReconnect)
{
	if (!IsReconnect)
	{
		m_sock.Close();
		m_Event.DelSockeInfo(m_sock);
	}
	else
	{

	}
	return true;
}

DWORD CNetSession::WorkItem(LPVOID param)
{
	assert(param != NULL);
	CNetSession *pNet = (CNetSession*)(param);
	MSG msg;
	try
	{
		while (true) 
		{
			BOOL bRet = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			if (bRet)
			{
				switch (msg.message)
				{
				case WM_CONNECT:
					{
						pNet->m_XmlConfig.GetServerInfo(pNet->m_UserInfo.m_ServerIp, 
							pNet->m_UserInfo.m_sServerPort);
						pNet->Connect(pNet->m_UserInfo.m_ServerIp, pNet->m_UserInfo.m_sServerPort);
						break;
					}
				case WM_DISCONNECT:
					{
						bool bRet = pNet->Disconnect(true);
						return 1;
					}
				case WM_SEND:
					{
						CSendMsg *SendMsg = (CSendMsg*)(msg.wParam);
						break;
					}
				case WM_RECONNECT:
					{
						break;
					}
				default:
					{
						break;
					}
				}
			}

			//处理接受数据包
			if (!pNet->DoReceive())
			{
				throw "Receive message failed";
			}
		}
	}
	catch(char *exception)
	{
		PrintLog(_LOG_LEVEL_DEBUG, exception);
	}
	catch(...)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "NetSession::WorkItem has exception");
	}
	pNet->m_sock.Close();
	return 0;
}