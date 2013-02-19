/********************************************************************
	created:	2009/12/09
	created:	9:12:2009   10:58
	filename: 	PackBase.h
	file path:	\PackDefine
	file base:	PackBase
	file ext:	h
	author:		isold
	
	purpose:	
*********************************************************************/
#ifndef _BASE_PACK_H_
#define _BASE_PACK_H_

#include "include.h"
#include "StandardSerialize.h"

class CBasePack
{
public:
	CBasePack(void):type(0){}
	virtual ~CBasePack(void){}
	uint32 Pack(char* buffer, uint32 length);
	uint32 UnPack(const char* buffer, const uint32 length);
	void SetPackType(uint16 pack_type){ type = pack_type; }
	uint16 GetPackType(void){ return type; }
protected:
	virtual uint32 Serialize(CStandardSerialize &ser) = 0;
private:
	uint16 type;
};
#endif //_BASE_PACK_H_













