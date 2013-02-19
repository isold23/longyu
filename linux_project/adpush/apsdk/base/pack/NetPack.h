/********************************************************************
created:	2011/03/08
created:	8:3:2011   10:11
file base:	NetPack
file ext:	h
author:		王立卫

purpose:	TCP协议应用数据包结构
*********************************************************************/
#ifndef _NET_PACK_H_
#define _NET_PACK_H_

#include "../include.h"
#include "StandardSerialize.h"
#include "../LMEnDecrypt.h"

#define DEF_NET_PACK_HEAD_PREFIX 0x99
#define DEF_BUFFER_LEN 3000

class CNetPack{
public:
	CNetPack(){}
	virtual ~CNetPack(){}
	virtual bool CheckPack() = 0;
	virtual int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length) = 0;
	//0 包长度不够 1 解出一个包 -1 解包失败
	virtual int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length) = 0;

public:
	int _min_pack_size;
	int _max_pack_size;
};

/***************************************************************************************************************
  old protocol
  *************************************************************************************************************/

#define DEF_MAX_BUFFER_LEN    2560
#define LM_ENCRYPT

class CNetPackCRS : public CNetPack{
public:
	CNetPackCRS();
	virtual ~CNetPackCRS();

	int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length);
	int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length);

	bool CheckPack(){ return true; }

private:
	uint16_t GetPackSerial();

public:
	CCriticalSection mCriSection;
	uint16_t  mwSendTimestamp;
	LMEnDecrypt moEnDecrypt;
};

class CNetPackMPS : public CNetPack{
public:
	CNetPackMPS();

	virtual ~CNetPackMPS(){

	}

	int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length);

	int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length);

	bool CheckPack(){ return true; }

public:

};
#endif //_NET_PACK_H_











