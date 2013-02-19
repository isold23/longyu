/*********************************************************************************
版本声明：	Copyright(C)2004-sina Co.Ltd
文件名：	StandardSerialize.h
版本号：	1.00.000
说明：		标准序列化实现类，用来序列化通用的数据类型

修改记录：  2004-02-13 张宏涛 整理了该类，防止内存越界

张亚伟 修改	2006-11-24 目的：适应跨平台使用
**********************************************************************************/

#ifndef DEF_SINA_STANDARD_SERIALIZE_H
#define DEF_SINA_STANDARD_SERIALIZE_H

#include "include.h"

//用来序列化通讯包的类
class CStandardSerialize
{
public:
	enum ENUM_TYPE{LOAD,STORE};	

public:
	//构造和析构
	CStandardSerialize(char * apBuffer,int alBufLen, ENUM_TYPE abyType);
	~CStandardSerialize();

	template<class T>
	inline int Serialize(T& value)
	{
		if (mlBufLen < (mlDataLen+(int)sizeof(T)))
			throw(-1);
		if (mbyType == LOAD)//读取
		{   
			memcpy(&value,mpBuffer + mlDataLen, sizeof(T));		        
		}
		else                //存储
		{
			memcpy(mpBuffer + mlDataLen, &value, sizeof(T));
		}
		mlDataLen += sizeof(T);
		return 1;
	}

    /****************************************************************
	函 数 名：int	Serialize(unsigned int&	alValue);
	功能描述：序列化int类型的值
	输入参数：int alValue
	输出参数：
	返 回 值：int 1=成功；－1＝失败(throw，有外部捕获)
	创建日期：2002-5-27
	创 建 者：靳国文
	****************************************************************/
#ifndef x86_64
	int	Serialize(int64& ai64Value);
#endif

	/****************************************************************
	函 数 名：int	Serialize(char * apValue);
	功能描述：序列化串类型的值
	输入参数：char * apValue :串值(既可以作为输入参数，也可以作为输出参数)			  			  
	返 回 值：int 1=成功；－1＝失败(throw，需要有外部捕获)
	创建日期：2002-5-27
	创 建 者：靳国文
	****************************************************************/
	int	Serialize(char * apValue,uint16_t awMaxLen);

	/****************************************************************
	函 数 名：int	Serialize(char * apValue, uint16_t& awLen);
	功能描述：序列化字符数组类型的值
	输入参数：char * apValue :串值(既可以作为输入参数，也可以作为输出参数)			  
			  uint16_t & awLen : 串长度(既可以作为输入参数，也可以作为输出参数)			 			  
	返 回 值：int 1=成功；－1＝失败(throw，需要有外部捕获)
	创建日期：2002-5-27
	创 建 者：靳国文
	****************************************************************/
	int	Serialize(char * apValue, uint16_t awLen,uint16_t aiBufferLen);


	//add by yanghannong 
	int	Serialize(uint8_t *apValue, uint16_t awLen);

	//取得属性
	int	getDataLen();
	
	ENUM_TYPE	mbyType;		//序列化类型
private:	
	int		mlDataLen;		//数据长度
	char *		mpBuffer;
    int        mlBufLen;       //buffer长度
};

#endif //DEF_SINA_STANDARD_SERIALIZE_H
