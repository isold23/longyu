#pragma once
#include "Interface.h"
#include "AutoLock.h"

#define DATA_BUFSIZE 8192


typedef struct _SOCKET_INFORMATION {
	CHAR Buffer[DATA_BUFSIZE];
	WSABUF DataBuf;
	SOCKET Socket;
	bool mbCanSend;
	DWORD BytesSEND;
	DWORD BytesRECV;
	IPackManager* mpPackManager;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;


class CTcpTransfer
{
public:
	CTcpTransfer();
	~CTcpTransfer();
	bool ConnectToSever(const char* apszIPAddr, WORD awPort, IPackManager* apPackManager);

	bool CloseTcpSeesion(IPackManager* apPackManager);

	int GetLastErr();

	static unsigned __stdcall ThreadProc(void* param);
private:
	//初始化
	bool Init();
	bool CreateSocketInformation(SOCKET, IPackManager*);
	void FreeSocketInformation(DWORD);
	void SendData();
private:
	int miErrorCode;
	//是否初始化
	bool mbInitlized;

	int miEventTotal;

	HANDLE mhThread;
	
	HANDLE mhExitEvent;

	_LONGYU_COMMON::CCriticalSection m_CriticalSection;

	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	LPSOCKET_INFORMATION SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
};