/********************************************************************
	created:	2009/12/09
	created:	9:12:2009   11:22
	filename: 	PackBase.cpp
	file path:	\Pack
	file base:	PackBase
	file ext:	cpp
	author:		isold
	
	purpose:	
*********************************************************************/
#include "BasePack.h"

uint32 CBasePack::Pack(char* buffer, uint32 length)
{
	try
	{
		CStandardSerialize loSerialize(buffer, length, CStandardSerialize::STORE);
		memset(buffer,0,length);
		loSerialize.Serialize(type);	
		if(Serialize(loSerialize) == -1)
			return 0;
		return loSerialize.getDataLen();
	}
	catch(...)
	{
		return 0;
	}
}

uint32 CBasePack::UnPack(const char* buffer, const uint32 length)
{
	try
	{
		CStandardSerialize loSerialize(buffer, length, CStandardSerialize::LOAD);
		uint16 lui16Type = 0;
		loSerialize.Serialize(lui16Type);
		if(lui16Type != type)
			return 0;
		if(Serialize(loSerialize) == -1)
			return 0;
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}