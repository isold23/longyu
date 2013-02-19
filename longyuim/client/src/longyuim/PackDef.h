#ifndef _PACK_DEF_H_
#define _PACK_DEF_H_

#include "stdafx.h"
#include "StandardSerialize.h"
#include "BasePack.h"

#define PASSWORD_LEN 20

#define PACK_BASE			0x100
#define PACK_LOGIN_RQ		PACK_BASE+1
#define PACK_LOGIN_RS      PACK_BASE+2

#define PACK_KEEPALIVE_RQ		PACK_BASE+3
#define PACK_KEEPALIVE_RS      PACK_BASE+4

#define PACK_LOGOUT_RQ		PACK_BASE+5
#define PACK_LOGOUT_RS      PACK_BASE+6

class CPackLoginRQ : public CBasePack
{
	uint32 miUserID;
	char mszUserPassword[PASSWORD_LEN];

	CPackLoginRQ():miUserID(0)
	{
		memset(mszUserPassword, 0, PASSWORD_LEN);
		mui16PackType = PACK_LOGIN_RQ;
	}
	virtual ~CPackLoginRQ(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

class CPackLoginRS : public CBasePack
{
	uint32 miUserID;
	uint32 miReturn;

	CPackLoginRS():miUserID(0),miReturn(0)
	{
		mui16PackType = PACK_LOGIN_RS;
	}
	virtual ~CPackLoginRS(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};


class CPackKeepAliveRQ : public CBasePack
{
	uint32 miUserID;

	CPackKeepAliveRQ():miUserID(0)
	{
		mui16PackType = PACK_KEEPALIVE_RQ;
	}
	virtual ~CPackKeepAliveRQ(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

class CPackKeepAliveRS : public CBasePack
{
	uint32 miUserID;

	CPackKeepAliveRS():miUserID(0)
	{
		mui16PackType = PACK_KEEPALIVE_RS;
	}
	virtual ~CPackKeepAliveRS(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};


class CPackLogoutRQ : public CBasePack
{
	uint32 miUserID;

	CPackLogoutRQ():miUserID(0)
	{
		mui16PackType = PACK_LOGOUT_RQ;
	}
	virtual ~CPackLogoutRQ(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

class CPackLogoutRS : public CBasePack
{
	uint32 miUserID;

	CPackLogoutRS():miUserID(0)
	{
		mui16PackType = PACK_LOGOUT_RS;
	}
	virtual ~CPackLogoutRS(){}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

#endif //_PACK_DEF_H_