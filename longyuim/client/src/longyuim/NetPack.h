#ifndef _NET_PACK_H_
#define _NET_PACK_H_

#include "stdafx.h"
#include "StandardSerialize.h"

#define DEF_NET_PACK_HEAD_PREFIX 0x99
#define DEF_BUFFER_LEN 3000

class CNetPackHead
{
public:
	CNetPackHead();
	~CNetPackHead();

	int Pack(char* buffer, int &length);
	int Unpack(char *buffer, int length);

	bool CheckHead()
	{
		if((miFlag == DEF_NET_PACK_HEAD_PREFIX) && 
			(miLength <= DEF_BUFFER_LEN-32) && 
			(miLength >= 2))
		{
			return true;
		}
		else
		{
//			TRACE(1, "CNetPackHead::CheckHead –≠“ÈºÏ≤‚ ß∞‹°£FLAG = "<<
	//			miFlag<<" Length = "<<miLength);
			return false;
		}
	}
private:
	int Serialize(CStandardSerialize & aoStandardSerialize);

public:
	int miFlag;
	int miVersion;
	int miID;
	int miTime;
	int mszIfEncry;
	int mszIfCompress;
	int miErrorCode;
	int miLength;
};


const int NET_PACK_HEAD_SIZE = sizeof(CNetPackHead);

class CNetPackLogin
{
public:
	CNetPackLogin();
	~CNetPackLogin();
	
	int Pack(char* buffer, int &length);
	int Unpack(char *buffer, int length);
private:
	int Serialize(CStandardSerialize & aoStandardSerialize);

public:
	int miId;
};

class CNetPackKeepLive
{
public:
	CNetPackKeepLive();
	~CNetPackKeepLive();

	int Pack(char* buffer, int &length);
	int Unpack(char *buffer, int length);
private:
	int Serialize(CStandardSerialize & aoStandardSerialize);

public:
	int miId;
};

class CNetPackLogout
{
public:
	CNetPackLogout();
	~CNetPackLogout();
	int Pack(char* buffer, int &length);
	int Unpack(char *buffer, int length);
private:
	int Serialize(CStandardSerialize & aoStandardSerialize);
public:
	int miId;
};
#endif //_NET_PACK_H_











