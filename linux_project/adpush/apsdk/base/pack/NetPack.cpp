/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:12
	file base:	NetPack
	file ext:	cpp
	author:		王立卫
	
	purpose:	TCP协议应用数据包结构
*********************************************************************/
#include "NetPack.h"

#define TCP_PACK_VERSION		1		//TCP包版本

/*TCP包结构(括号内为长度):
包头(3)+包长度(2)+版本(1)+时间戳(2)+包数据(n)+包尾(3)+包长度(2)
TCP包固定结构长度为13，总长为13+n	*/
#define TCP_PACK_STRUCT_LEN		13		//TCP包固定结构长度

static char macPackHeader[] = "\01\02\03\0";
static char macPackTail[] = "\04\05\06\0";

static uint8_t STX = 0x03;
static uint8_t ETX = 0x07;

CNetPackCRS::CNetPackCRS(){
	_min_pack_size = TCP_PACK_STRUCT_LEN;
	_max_pack_size = DEF_MAX_BUFFER_LEN;
}

CNetPackCRS::~CNetPackCRS(){

}


int	CNetPackCRS::Pack(const char * in_buffer, const int in_length, char * out_buffer, int &out_length)
{
	if (in_length > out_length || in_length > DEF_MAX_BUFFER_LEN)  //不足以容纳包内容
		return -1;

	uint16_t lwDecryptLen = in_length;

#ifdef LM_ENCRYPT	//加密
	//改变成8的倍数
	//lwDecryptLen = 8-(in_length+2)%8 + in_length + 2;
	char lpcEncrypt[DEF_MAX_BUFFER_LEN];
	if (moEnDecrypt.LmEncrypt((char*)in_buffer, in_length, lpcEncrypt, lwDecryptLen) == -1) //加密失败
	{
		return -3;
	}
	assert(lwDecryptLen <= DEF_MAX_BUFFER_LEN);
	//加密过长
	if (lwDecryptLen > out_length)
		return -2;
#endif

	uint8_t lbyVersion = TCP_PACK_VERSION;
	int liResult = 0;

	CStandardSerialize loStdSerialize(out_buffer,out_length, CStandardSerialize::STORE);

	loStdSerialize.Serialize(macPackHeader,3,out_length);	//包头
	loStdSerialize.Serialize(lwDecryptLen);					//包长
	loStdSerialize.Serialize(lbyVersion);					//版本
	uint16_t lwPackSerial = GetPackSerial();
	loStdSerialize.Serialize(lwPackSerial);					//时间戳

	//序列化数据
#ifdef LM_ENCRYPT
	loStdSerialize.Serialize(lpcEncrypt,lwDecryptLen,DEF_MAX_BUFFER_LEN);
#else
	loStdSerialize.Serialize(in_buffer,in_length,in_length);
#endif
	loStdSerialize.Serialize(macPackTail,3,3);				//包尾
	loStdSerialize.Serialize(lwDecryptLen);					//包长

	liResult = loStdSerialize.getDataLen();					//得到打包后总长

	out_length = liResult;
	return liResult;
}

int CNetPackCRS::Unpack(const char *in_buffer, const int in_length, 
	char * out_buffer, int &out_length, int &out_data_length){
		if (in_length ==0)
			return 0;

		uint16_t lwTcpPackLen = DEF_MAX_BUFFER_LEN;

		//TCP通讯包解包长度不够
		if(in_length < TCP_PACK_STRUCT_LEN)
			return 0;


		CStandardSerialize loStdSerialize((char*)in_buffer,in_length, CStandardSerialize::LOAD);

		//判断包头
		char lacPackTag[4];
		loStdSerialize.Serialize(lacPackTag,3,4);	//包头
		if(memcmp(lacPackTag,macPackHeader,3)!=0)
		{
			return -3;  //头不对
		}

		//判断是否可以容纳包内容
		uint16_t lwPacklenHeader=0;
		loStdSerialize.Serialize(lwPacklenHeader);	//包长
		if(lwPacklenHeader > (in_length - TCP_PACK_STRUCT_LEN)){
			return 0;
		}
		assert(lwPacklenHeader <= out_length);
		//得到版本
		uint8_t lbyVersion = 0;
		loStdSerialize.Serialize(lbyVersion);		//版本
		uint16_t awtimestamp = 0;
		loStdSerialize.Serialize(awtimestamp);		//时间戳

		//拷贝内容
#ifdef LM_ENCRYPT
		char lpRawData[DEF_MAX_BUFFER_LEN];
		loStdSerialize.Serialize(lpRawData,lwPacklenHeader,DEF_MAX_BUFFER_LEN);
		uint16_t  inlen = lwPacklenHeader;
		uint16_t outlen = 0;
		if (moEnDecrypt.LmDecrypt(lpRawData, inlen, out_buffer, outlen) == -1) //解密失败
		{
			return -7;	//解密错误
		}
		out_length = outlen;
#else
		loStdSerialize.Serialize(out_buffer,lwPacklenHeader,out_length);
#endif
		//判断包尾
		loStdSerialize.Serialize(lacPackTag,3,4);   //包尾
		if (memcmp(lacPackTag,macPackTail,3) != 0)
		{
			return -5;
		}

		//判断包前后长度
		uint16_t lwPacklenTail  =0;
		loStdSerialize.Serialize(lwPacklenTail);	//包长
		if (lwPacklenTail != lwPacklenHeader)
		{
			return -6; //前后长度不一致
		}
		out_data_length = lwPacklenHeader + 13;
		return 1;
}


uint16_t CNetPackCRS::GetPackSerial()
{
	CAutoLock loLock(mCriSection);
	return mwSendTimestamp++;
}

CNetPackMPS::CNetPackMPS(){
	_min_pack_size = TCP_PACK_STRUCT_LEN;
	_max_pack_size = DEF_MAX_BUFFER_LEN;
}

int CNetPackMPS::Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length)
{
	if (in_length > out_length || in_length > DEF_MAX_BUFFER_LEN)  //不足以容纳包内容
		return -1;

	CStandardSerialize loStdSerialize(out_buffer,out_length, CStandardSerialize::STORE);

	loStdSerialize.Serialize(STX);							//包头
	uint16_t u16PackLen = in_length + 2*sizeof(uint8_t) + 2*sizeof(uint16_t);
	u16PackLen = htons(u16PackLen);
	loStdSerialize.Serialize(u16PackLen);				//包长
	uint16_t  u16Verion = 0;
	loStdSerialize.Serialize(u16Verion);					//版本号
	loStdSerialize.Serialize((char*)in_buffer,in_length, in_length);
	loStdSerialize.Serialize(ETX);							//包尾

	int liResult = loStdSerialize.getDataLen();			 //得到打包后总长
	out_length = liResult;
	return liResult;
}

int CNetPackMPS::Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length)
{
	if (in_length ==0)
		return 0;

	uint16_t lwTcpPackLen = DEF_MAX_BUFFER_LEN;

	CStandardSerialize loStdSerialize((char*)in_buffer, in_length, CStandardSerialize::LOAD);

	//判断包头
	uint8_t u8PackTag;
	loStdSerialize.Serialize(u8PackTag);	//包头
	if(u8PackTag != STX)
	{
		return -3;  //头不对
	}
	uint16_t u16PackLen;
	loStdSerialize.Serialize(u16PackLen);	//包长
	u16PackLen = ntohs(u16PackLen);

	if(u16PackLen > in_length)
		return 0;

	uint16_t  u16Verion = 0;
	loStdSerialize.Serialize(u16Verion);	//版本号
	
	out_buffer_length = u16PackLen - 2*sizeof(uint8_t) - 2*sizeof(uint16_t);
	loStdSerialize.Serialize(out_buffer, out_buffer_length, out_buffer_length);

	//判断包尾
	loStdSerialize.Serialize(u8PackTag);   //包尾
	if (u8PackTag != ETX)
	{
		return -5;
	}
	
	out_data_length = u16PackLen;
	return 1;
}