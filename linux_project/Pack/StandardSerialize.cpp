#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StandardSerialize.h"

CStandardSerialize::CStandardSerialize(char * apBuffer,int alBufLen, ENUM_TYPE abyType)
{
	mpBuffer = apBuffer;
	mbyType  = abyType;
	mlBufLen = alBufLen;
	mlDataLen = 0;
}

CStandardSerialize::~CStandardSerialize()
{
}

int CStandardSerialize::getDataLen()
{
	return mlDataLen;
}

int CStandardSerialize::Serialize(bool&	abValue)
{
	if (mlBufLen < (mlDataLen+1))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&abValue,mpBuffer + mlDataLen, 1);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &abValue, 1);
	}
	mlDataLen += 1;

	return 1;
}


long CStandardSerialize::Serialize(long&	aiValue)
{
	if (mlBufLen < (mlDataLen+4))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&aiValue,mpBuffer + mlDataLen, 4);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &aiValue, 4);
	}
	mlDataLen += 4;
	return 1;
}

int CStandardSerialize::Serialize(uint8&	abyValue)
{
	if (mlBufLen < (mlDataLen+1))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&abyValue,mpBuffer + mlDataLen, 1);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &abyValue, 1);
	}
	mlDataLen += 1;
	return 1;	
}

int	CStandardSerialize::Serialize(short& asValue)
{
	if (mlBufLen < (mlDataLen+2))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&asValue,mpBuffer + mlDataLen, 2);
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &asValue, 2);
	}
	mlDataLen += 2;
	return 1;

}

int CStandardSerialize::Serialize(uint16&	awValue)
{
	if (mlBufLen < (mlDataLen+2))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&awValue,mpBuffer + mlDataLen, 2);
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &awValue, 2);
	}
	mlDataLen += 2;
	return 1;
}

int CStandardSerialize::Serialize(int&	alValue)
{
	if (mlBufLen < (mlDataLen+4))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&alValue,mpBuffer + mlDataLen, 4);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &alValue, 4);
	}
	mlDataLen += 4;
	return 1;
}

int CStandardSerialize::Serialize(unsigned int&	aulValue)
{
	if (mlBufLen < (mlDataLen+4))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&aulValue,mpBuffer + mlDataLen, 4);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &aulValue, 4);
	}
	mlDataLen += 4;

	return 1;
}

int CStandardSerialize::Serialize(int64& aiValue)
{	
	if (mlBufLen < (mlDataLen+8))
		throw(-1);

	if (mbyType == LOAD)//读取
	{   
		memcpy(&aiValue,mpBuffer + mlDataLen, 8);		        
	}
	else                //存储
	{
		memcpy(mpBuffer + mlDataLen, &aiValue, 8);
	}
	mlDataLen += 8;

	return 1;
}

int CStandardSerialize::Serialize(char * apValue,uint16 awMaxLen)
{
	if (mlBufLen < (mlDataLen+2))
		throw(-1);

	uint16	lwLen = 0;
	if (mbyType == LOAD)    //读取
	{
		//首先读取长度
		memcpy(&lwLen,mpBuffer + mlDataLen, 2);
		mlDataLen += 2;

		//读取数据本身
		if ((lwLen >= awMaxLen) || ((mlDataLen+lwLen) > mlBufLen))
		{
			throw(-1);
		}
		memcpy(apValue, mpBuffer + mlDataLen, lwLen);
		apValue[lwLen] = '\0';
		mlDataLen += lwLen;                
	}
	else    //存储
	{        
		//首先存储长度
		lwLen = strlen(apValue);
		if ((lwLen >= awMaxLen) || (lwLen+mlDataLen+2 > mlBufLen))
			throw(-1);

		memcpy(mpBuffer+mlDataLen, &lwLen, 2);
		mlDataLen += 2;

		//存储数据本身
		memcpy(mpBuffer+mlDataLen, apValue, lwLen);
		mlDataLen += lwLen;            
	}		
	return 1;	
}

int CStandardSerialize::Serialize(char * apValue, uint16 awLen,uint16 aiBufferLen)
{
	if ((awLen > aiBufferLen) || (mlBufLen < (mlDataLen+awLen)))
	{
		throw (-1);
	}

	if (mbyType == LOAD)    //读取
	{			
		//因为外部制定了读取长度，所以不需要对数据长度进行序列化
		memcpy(apValue, mpBuffer + mlDataLen, awLen);
	}
	else    //存储数据本身
	{            
		memcpy(mpBuffer+mlDataLen, apValue, awLen);
	}	
	mlDataLen += awLen;
	return 1;	
}

int	CStandardSerialize::Serialize(uint8 *apValue, uint16 awLen)
{
	if (mlBufLen < (mlDataLen+awLen))
		throw (-1);

	if (mbyType == LOAD)    //读取
	{			
		//因为外部制定了读取长度，所以不需要对数据长度进行序列化
		memcpy(apValue, mpBuffer + mlDataLen, awLen);            
	}
	else    //存储数据本身
	{            
		memcpy(mpBuffer+mlDataLen, apValue, awLen);                        
	}	

	mlDataLen += awLen;
	return 1;
}


