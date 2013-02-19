#pragma once
#include "interface.h"
#include "sigslot.h"

class CNetInfterface :
	public IPackManager
{
public:
	CNetInfterface(void);
	~CNetInfterface(void);
	virtual void SocketClose();
	virtual void SocketError(int ErrorCode);
	virtual void AddRecvData(const char* apszBuffer, WORD awDataLen);
	virtual int GetSendData(const char* apszBuffer, WORD& awDataLen);

	int SendData(const char *apszBuffer, WORD awDataLen);

public:
	sigslot::signal3<unsigned int, char*, unsigned int> OnRecv;



};

