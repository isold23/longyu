
/*********************************************************************************
版本声明：	Copyright(C)2004-sina Co.Ltd
文件名：	StandardSerialize.cpp
版本号：	1.00.000
创 建 人：	靳国文
说明：		标准序列化实现类，用来序列化通用的数据类型

修改记录：  2004-02-13 张宏涛 整理了该类，防止内存越界

张亚伟 修改	2006-11-24
目的：适应跨平台使用
***********************************************************************************/

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

#ifndef x86_64
int CStandardSerialize::Serialize(int64& aiValue)
{	
    if (mlBufLen < (mlDataLen+sizeof(int64)))
        throw(-1);

    if (mbyType == LOAD)//读取
    {   
        memcpy(&aiValue,mpBuffer + mlDataLen, sizeof(int64));		        
    }
    else                //存储
    {
        memcpy(mpBuffer + mlDataLen, &aiValue, sizeof(int64));
    }
    mlDataLen += sizeof(int64);

    return 1;
}
#endif

//*****************************************************************************
//  函数：  序列化以0结尾的字符串数据
//  参数：  char * apValue		字符串数据
//			uint16_t awBufferLen	容纳此字符串数据的缓存区大小
//  返回值：int  1= 成功； -1 = 失败
//  用法：	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue,uint16_t awMaxLen)
{
    if (mlBufLen < (mlDataLen+2))
        throw(-1);

    uint16_t	lwLen = 0;
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

//*****************************************************************************
//  函数：  序列化数据
//  参数：  char * apValue		数据
//			uint16_t& awLen			此数据的真正长度
//			uint16_t awBufferLen	容纳此数据的缓存区大小
//  返回值：int  1= 成功； -1 = 失败
//  用法：	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue, uint16_t awLen,uint16_t aiBufferLen)
{
    if ((awLen > aiBufferLen) || (mlBufLen < (mlDataLen+awLen)))
	{
		TRACE(1, "CStandardSerialize::Serialize  <awLen>："<<awLen<<" <aiBufferLen>："<<aiBufferLen<<"<mlBufLen>："<<mlBufLen<<"<mlDataLen>："<<mlDataLen);
        throw (-1);
	}

    if (mbyType == LOAD)    //读取
    {			
        //因为外部制定了读取长度，所以不需要对数据长度进行序列化
        memcpy(apValue, mpBuffer + mlDataLen, awLen);
		//TRACE(1,"CStandardSerialize::Serialize LOAD：  apValue："<<apValue<<" mpBuffer："<<mpBuffer<<" mlDataLen："<<mlDataLen<<" awLen："<<awLen);//add by tanwei 20081216
    }
    else    //存储数据本身
    {            
        memcpy(mpBuffer+mlDataLen, apValue, awLen);
		//TRACE(1,"CStandardSerialize::Serialize ：  mpBuffer："<<mpBuffer<<" mlDataLen："<<mlDataLen<<" apValue："<<apValue<<" awLen："<<awLen);//add by tanwei 20081216
    }	
    mlDataLen += awLen;
    return 1;	
}
//add by yanghannong 090508
//RSA 加解密需要
int	CStandardSerialize::Serialize(uint8_t *apValue, uint16_t awLen)
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


