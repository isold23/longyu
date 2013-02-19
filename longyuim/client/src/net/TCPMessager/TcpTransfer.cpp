#include "stdafx.h"
#include "TcpTransfer.h"
#include <process.h>

CTcpTransfer::CTcpTransfer()
{
	miErrorCode = 0;
	mbInitlized = false;
	miEventTotal = 0;
	mhThread = NULL;
	mhExitEvent = NULL;

	memset(SocketArray, 0, sizeof(SocketArray));
}

CTcpTransfer::~CTcpTransfer()
{
	if(mhThread != NULL)
	{
		if(mhExitEvent != NULL)
		{
			SetEvent(mhExitEvent);
		}		

		if(WaitForSingleObject(mhThread, 1000) == WAIT_TIMEOUT)
		{
			TerminateThread(mhThread, 0);	
		}
		CloseHandle(mhThread);
		mhThread = NULL;
	}

	if(mhExitEvent != NULL)
	{
		CloseHandle(mhExitEvent);
		mhExitEvent = NULL;
	}

	for (int i = miEventTotal-1; i >= 0; i--)
	{
		FreeSocketInformation(i);
	}

	if(mbInitlized)
	{
		WSACleanup();
	}
}

bool CTcpTransfer::Init()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD( 2, 2 );

	mbInitlized = (WSAStartup( wVersionRequested, &wsaData ) == 0);
	if(!mbInitlized)
	{
		miErrorCode = WSAGetLastError();
	}

	mhExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    return mbInitlized;
}

bool CTcpTransfer::ConnectToSever(const char* apszIPAddr, WORD awPort, IPackManager* apPackManager)
{
	if(!mbInitlized && !Init())
	{
		return false;
	}
	//..
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		miErrorCode = WSAGetLastError();
		return false;
	}

	struct sockaddr_in server;
	struct hostent    *host = NULL;
	server.sin_family = AF_INET;
	server.sin_port = htons(awPort);
	server.sin_addr.s_addr = inet_addr(apszIPAddr);

	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(apszIPAddr);
		if (host == NULL)
		{
			return false;
		}
		CopyMemory(&server.sin_addr, host->h_addr_list[0],
			host->h_length);
	}
	if (connect(s, (struct sockaddr *)&server, 
		sizeof(server)) == SOCKET_ERROR)
	{
		miErrorCode = WSAGetLastError();;
		return false;
	}

	return CreateSocketInformation(s, apPackManager);
}	

bool CTcpTransfer::CloseTcpSeesion(IPackManager* apPackManager)
{
	CAutoLock Lock(m_CriticalSection);
	for (int i = miEventTotal-1; i >= 0; i--)
	{
		LPSOCKET_INFORMATION SI = SocketArray[i];	
		if(SI->mpPackManager == apPackManager)
		{
			FreeSocketInformation(i);
			return true;
		}
	}
	return false;
}

int CTcpTransfer::GetLastErr()
{
	return miErrorCode;
}

bool CTcpTransfer::CreateSocketInformation(SOCKET s, IPackManager* apPackManager)
{
	LPSOCKET_INFORMATION SI;
	CAutoLock Lock(m_CriticalSection);
	if ((EventArray[miEventTotal] = WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		miErrorCode = WSAGetLastError();
		return false;
	}

	if ((SI = (LPSOCKET_INFORMATION) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFORMATION))) == NULL)
	{
		miErrorCode = GetLastError();
		return false;
	}
	SI->Socket = s;
	SI->mpPackManager = apPackManager;
	SI->mbCanSend = false;

	SocketArray[miEventTotal] = SI;

	miEventTotal++;
	if(WSAEventSelect(s,EventArray[miEventTotal - 1], FD_READ | FD_WRITE | FD_CLOSE ) == SOCKET_ERROR)
	{
		miErrorCode = WSAGetLastError();
		return false;
	}
	
	if(mhThread == NULL)
	{
		mhThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, NULL);
	}

	return true;
}

void CTcpTransfer::FreeSocketInformation(DWORD Event)
{
	CAutoLock Lock(m_CriticalSection);

	LPSOCKET_INFORMATION SI = SocketArray[Event];
	if(SI == NULL)
		return;

	shutdown(SI->Socket, 2);
	closesocket(SI->Socket);

	GlobalFree(SI);

	SocketArray[Event] = NULL;

	WSACloseEvent(EventArray[Event]);
	
	DWORD i;
	for (i = Event; i < miEventTotal; i++)
	{
		EventArray[i] = EventArray[i + 1];
		SocketArray[i] = SocketArray[i + 1];
	}

	miEventTotal--;
}

void CTcpTransfer::SendData()
{
	CAutoLock Lock(m_CriticalSection);
	for (int i = 0; i < miEventTotal; i++)
	{
		LPSOCKET_INFORMATION SocketInfo = SocketArray[i];
		if(SocketInfo->mbCanSend)
		{
			if (SocketInfo->BytesRECV > SocketInfo->BytesSEND)
			{
				SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
				SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;
			}
			else 
			{
				SocketInfo->DataBuf.buf = SocketInfo->Buffer;
				WORD lwLen = DATA_BUFSIZE;
				SocketInfo->DataBuf.len = SocketInfo->mpPackManager->GetSendData(SocketInfo->DataBuf.buf, lwLen);
				SocketInfo->BytesRECV = lwLen;
			}

			if(SocketInfo->BytesRECV > 0)
			{
				DWORD SendBytes;
				if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0,
					NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						miErrorCode = WSAGetLastError();
						SocketInfo->mpPackManager->SocketError(miErrorCode);
						FreeSocketInformation(i);
					}
					else
					{
						SocketInfo->mbCanSend = false;
					}
				}
				else
				{
					SocketInfo->BytesSEND += SendBytes;
					if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
					{
						SocketInfo->BytesSEND = 0;
						SocketInfo->BytesRECV = 0;
					}
				}
			}
		}
	}
}

unsigned __stdcall CTcpTransfer::ThreadProc(void* param)
{
	CTcpTransfer* pthis = reinterpret_cast<CTcpTransfer*>(param);
	if(pthis == NULL)
	{
		_endthreadex(1);
		return 1;
	}

	WSANETWORKEVENTS NetworkEvents;
	DWORD Event;
	while (true)
	{
		DWORD Event = WaitForSingleObject(pthis->mhExitEvent, 0); 
		if(Event == WAIT_OBJECT_0)
		{
			break;
		}
		if(pthis->miEventTotal <= 0)
		{
			Sleep(10);
			continue;
		}
		DWORD ldwTime = 1;
		CAutoLock Lock(pthis->m_CriticalSection);
		Event = WSAWaitForMultipleEvents(pthis->miEventTotal, pthis->EventArray, FALSE,
			ldwTime, FALSE);
		if(Event == WSA_WAIT_FAILED)
		{
			continue;
		}
		else if (Event == WSA_WAIT_TIMEOUT)
		{
			pthis->miErrorCode = WSAGetLastError();
			/*_endthreadex(2);
			return 2;*/
			pthis->SendData();
			continue;
		}
		if (WSAEnumNetworkEvents(pthis->SocketArray[Event - WSA_WAIT_EVENT_0]->Socket, pthis->EventArray[Event -
			WSA_WAIT_EVENT_0], &NetworkEvents) == SOCKET_ERROR)
		{
			pthis->miErrorCode = WSAGetLastError();
			_endthreadex(3);
			return 3;
		}

		if(NetworkEvents.lNetworkEvents & FD_READ)
		{
			if(NetworkEvents.lNetworkEvents & FD_READ && NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				pthis->miErrorCode = NetworkEvents.iErrorCode[FD_READ_BIT];
				break;
			}

			if(NetworkEvents.lNetworkEvents & FD_WRITE && NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				pthis->miErrorCode = NetworkEvents.iErrorCode[FD_WRITE_BIT];
				break;
			}

			LPSOCKET_INFORMATION SocketInfo = pthis->SocketArray[Event - WSA_WAIT_EVENT_0];

			SocketInfo->DataBuf.buf = SocketInfo->Buffer;
			SocketInfo->DataBuf.len = DATA_BUFSIZE;
			
			DWORD RecvBytes;
			DWORD Flags = 0;
			if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes,
				&Flags, NULL, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					pthis->miErrorCode = WSAGetLastError();
					SocketInfo->mpPackManager->SocketError(pthis->miErrorCode);
					pthis->FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
					//_endthreadex(4);
					//return 4;
					continue;
				}
			}
			else
			{
				SocketInfo->mpPackManager->AddRecvData(SocketInfo->Buffer, RecvBytes);
			}
		}
		
		if(NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			LPSOCKET_INFORMATION SocketInfo = pthis->SocketArray[Event - WSA_WAIT_EVENT_0];
			SocketInfo->mbCanSend = true; 
		}

		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
			{
				pthis->miErrorCode = NetworkEvents.iErrorCode[FD_CLOSE_BIT];
				//break;
			}
			else
				pthis->miErrorCode = WSAGetLastError();
			LPSOCKET_INFORMATION SocketInfo = pthis->SocketArray[Event - WSA_WAIT_EVENT_0];
			if(SocketInfo)
			{
				SocketInfo->mpPackManager->SocketClose();
				pthis->FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
			}			
			//break;
		}
	}

	pthis->miErrorCode = 0;
	pthis->mhThread = NULL;
	_endthreadex(0);	
	return 0;
}