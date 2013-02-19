#ifndef _DNS_CRS_H_
#define _DNS_CRS_H_

#include "include.h"
#include "BasePack.h"

#define PACK_DNS_CRS_BASE			0x200
#define PACK_DNS_CRS_HEAD			PACK_DNS_CRS_BASE+0
#define PACK_DNS_CRS_LOGIN_RQ		PACK_DNS_CRS_BASE+1
#define PACK_DNS_CRS_LOGIN_RS		PACK_DNS_CRS_BASE+2
#define PACK_DNS_CRS_KEEP_LIVE_RQ	PACK_DNS_CRS_BASE+3
#define PACK_DNS_CRS_KEEP_LIVE_RS	PACK_DNS_CRS_BASE+4
#define PACK_DNS_CRS_LOGOUT_RQ		PACK_DNS_CRS_BASE+5
#define PACK_DNS_CRS_LOGOUT_RS		PACK_DNS_CRS_BASE+6
#define PACK_DNS_CRS_MESSAGE		PACK_DNS_CRS_BASE+7


#define DNS_CRS_BUFFER_LEN			2900

#pragma  pack(1)

struct stru_DNS_CRS_LOGIN_RQ : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_i32GroupId;
	stru_DNS_CRS_LOGIN_RQ()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_LOGIN_RQ;
	}
	virtual ~stru_DNS_CRS_LOGIN_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_LOGIN_RS : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_iDnsId;
	stru_DNS_CRS_LOGIN_RS()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_LOGIN_RS;
	}
	virtual ~stru_DNS_CRS_LOGIN_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_KEEP_LIVE_RQ : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_i32GroupId;
	stru_DNS_CRS_KEEP_LIVE_RQ()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_KEEP_LIVE_RQ;
	}
	virtual ~stru_DNS_CRS_KEEP_LIVE_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_KEEP_LIVE_RS : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_iDnsId;
	stru_DNS_CRS_KEEP_LIVE_RS()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_KEEP_LIVE_RS;
	}
	virtual ~stru_DNS_CRS_KEEP_LIVE_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_LOGOUT_RQ : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_i32GroupId;
	stru_DNS_CRS_LOGOUT_RQ()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_LOGOUT_RQ;
	}
	virtual ~stru_DNS_CRS_LOGOUT_RQ()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_LOGOUT_RS : public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_iDnsId;
	stru_DNS_CRS_LOGOUT_RS()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_LOGOUT_RS;
	}
	virtual ~stru_DNS_CRS_LOGOUT_RS()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

struct stru_DNS_CRS_MESSAGE: public CBasePack
{
	uint32 m_i32NodeId;
	uint32 m_i32GroupId;
	uint32 m_i32TargetNode;
	uint32 m_i32TargetGroup;
	uint32 m_iDnsId;
	uint16 m_iDataLen;
	char  m_DataBuffer[DNS_CRS_BUFFER_LEN];
	stru_DNS_CRS_MESSAGE()
		:m_i32NodeId(0)
	{
		mui16PackType = PACK_DNS_CRS_MESSAGE;
		memset(m_DataBuffer,0,DNS_CRS_BUFFER_LEN);
	}
	virtual ~stru_DNS_CRS_MESSAGE()
	{

	}
	virtual int Serialize(CStandardSerialize &aoStandardSerialize);
};

#pragma  pack()

#endif //_DNS_CRS_H_


















