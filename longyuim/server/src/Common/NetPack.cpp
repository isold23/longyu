
#include "NetPack.h"

CNetPackHead::CNetPackHead()
{
	miFlag = DEF_NET_PACK_HEAD_PREFIX;
	miVersion = 0;
	miID = 0;
	miTime = 0;
	mszIfEncry = 0;
	mszIfCompress = 0;
	miErrorCode = 0;
	miLength = 0;
}

CNetPackHead::~CNetPackHead()
{


}

int CNetPackHead::Pack(char* buffer, int &length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::STORE);
		memset(buffer, 0, length);
		if(Serialize(loSerialize) == -1)
			return -1;
		return loSerialize.getDataLen();
		
	}
	catch (...)
	{
		return false;
	}
	return true;
}

int CNetPackHead::Unpack(char *buffer, int length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::LOAD);
		if(Serialize(loSerialize) == -1)
			return -1;
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}

int CNetPackHead::Serialize(CStandardSerialize &aoStandardSerialize)
{
	try
	{
		aoStandardSerialize.Serialize(miFlag);
		aoStandardSerialize.Serialize(miVersion);
		aoStandardSerialize.Serialize(miID);
		aoStandardSerialize.Serialize(miTime);
		aoStandardSerialize.Serialize(mszIfEncry);
		aoStandardSerialize.Serialize(mszIfCompress);
		aoStandardSerialize.Serialize(miErrorCode);
		aoStandardSerialize.Serialize(miLength);
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}


int CNetPackLogin::Pack(char* buffer, int &length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::STORE);
		memset(buffer, 0, length);
		if(Serialize(loSerialize) == -1)
			return -1;
		return loSerialize.getDataLen();

	}
	catch (...)
	{
		return false;
	}
	return true;
}

int CNetPackLogin::Unpack(char *buffer, int length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::LOAD);
		if(Serialize(loSerialize) == -1)
			return -1;
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}

int CNetPackLogin::Serialize(CStandardSerialize &aoStandardSerialize)
{
	try
	{
		aoStandardSerialize.Serialize(miId);
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}

int CNetPackLogout::Pack(char* buffer, int &length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::STORE);
		memset(buffer, 0, length);
		if(Serialize(loSerialize) == -1)
			return -1;
		return loSerialize.getDataLen();

	}
	catch (...)
	{
		return false;
	}
	return true;
}

int CNetPackLogout::Unpack(char *buffer, int length)
{
	try
	{
		CStandardSerialize loSerialize(buffer,length, CStandardSerialize::LOAD);
		if(Serialize(loSerialize) == -1)
			return -1;
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}

int CNetPackLogout::Serialize(CStandardSerialize &aoStandardSerialize)
{
	try
	{
		aoStandardSerialize.Serialize(miId);
		return 1;
	}
	catch(...)
	{
		return -1;
	}
}