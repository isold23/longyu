#ifndef _DCS_DNS_H_
#define _DCS_DNS_H_

#include "include.h"
#include "BasePack.h"

#define PACK_DCS_DNS_BASE			0x100
#define PACK_DCS_DNS_HEAD			PACK_DCS_DNS_BASE+0
#define PACK_DCS_DNS_LOGIN_RQ		PACK_DCS_DNS_BASE+1
#define PACK_DCS_DNS_LOGIN_RS		PACK_DCS_DNS_BASE+2
#define PACK_DCS_DNS_KEEP_LIVE_RQ	PACK_DCS_DNS_BASE+3
#define PACK_DCS_DNS_KEEP_LIVE_RS	PACK_DCS_DNS_BASE+4
#define PACK_DCS_DNS_LOGOUT_RQ		PACK_DCS_DNS_BASE+5
#define PACK_DCS_DNS_LOGOUT_RS		PACK_DCS_DNS_BASE+6
#define PACK_DCS_DNS_MESSAGE		PACK_DCS_DNS_BASE+7

#define DCS_DNS_BUFFER_LEN			(3000-32)
#pragma  pack(1)
struct stru_DCS_DNS_LOGIN_RQ : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_LOGIN_RQ()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_LOGIN_RQ;
	}
	virtual ~stru_DCS_DNS_LOGIN_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_LOGIN_RS : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_LOGIN_RS()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_LOGIN_RS;
	}
	virtual ~stru_DCS_DNS_LOGIN_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_KEEP_LIVE_RQ : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_KEEP_LIVE_RQ()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_KEEP_LIVE_RQ;
	}
	virtual ~stru_DCS_DNS_KEEP_LIVE_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_KEEP_LIVE_RS : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_KEEP_LIVE_RS()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_KEEP_LIVE_RS;
	}
	virtual ~stru_DCS_DNS_KEEP_LIVE_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_LOGOUT_RQ : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_LOGOUT_RQ()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_LOGOUT_RQ;
	}
	virtual ~stru_DCS_DNS_LOGOUT_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_LOGOUT_RS : public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	stru_DCS_DNS_LOGOUT_RS()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_LOGOUT_RS;
	}
	virtual ~stru_DCS_DNS_LOGOUT_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DCS_DNS_HEAD: public CBasePack
{
	uint16 m_iDatalen;
	char  m_cDataBuf[DCS_DNS_BUFFER_LEN];
	stru_DCS_DNS_HEAD()
	{
		mui16PackType = PACK_DCS_DNS_HEAD;
		memset(m_cDataBuf,0,DCS_DNS_BUFFER_LEN);
	}
	virtual ~stru_DCS_DNS_HEAD()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};
struct stru_DCS_DNS_MESSAGE: public CBasePack
{
	uint32 m_iDnsIp;
	uint32 m_iDnsId;
	uint16 m_iDatalen;
	char  m_cDataBuf[DCS_DNS_BUFFER_LEN];
	stru_DCS_DNS_MESSAGE()
		:m_iDnsIp(0)
	{
		mui16PackType = PACK_DCS_DNS_MESSAGE;
		memset(m_cDataBuf,0,DCS_DNS_BUFFER_LEN);
	}
	virtual ~stru_DCS_DNS_MESSAGE()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

#pragma  pack()

#endif //_DCS_DNS_H_



