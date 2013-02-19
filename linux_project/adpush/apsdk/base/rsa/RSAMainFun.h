#ifndef RSAMainFun_h__
#define RSAMainFun_h__

#include "MyCryptLib.h"
#include "Rijndael.h"


class CRSAMainFun
{
public:
	CRSAMainFun(void);
	~CRSAMainFun(void);

public:
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAGetPublicKey
	// 函数参数： 
	// 返 回 值： 
	// 函数说明： 获得初始公钥
	// $_FUNCTION_END ********************************
	int fnRSAGetPublicKey(/*OUT*/uint32_t ** pPublicKey,/*OUT*/uint32_t & nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAClientMakePassWord
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 设定客户端密钥, 同时返回一个新的密钥给服务器
	// $_FUNCTION_END ********************************
	int fnRSAClientMakePassWord(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAServerMakePassWord
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 设定服务器端密钥, 同时返回数字签名给客户端以便验证可靠性
	// $_FUNCTION_END ********************************
	int fnRSAServerMakePassWord(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAVerifyKey
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 数字签名认证, 同时返回给服务器
	// $_FUNCTION_END ********************************
	int fnRSAVerifyKey(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAStartHash
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 开始HASH计算
	// $_FUNCTION_END ********************************
	void fnRSAStartHash(void);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnRSAFinishHash
	// 函数参数：
	// 返 回 值： 
	// 函数说明： HASH完成
	// $_FUNCTION_END ********************************
	bool fnRSAFinishHash(const uint32_t *pKey,uint32_t nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnDeCryptBuffer
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 加密
	// $_FUNCTION_END ********************************
	char* fnEnCryptBuffer(const char *pBuff, int & nBufSize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnDeCryptBuffer
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 解密
	// $_FUNCTION_END ********************************
	char* fnDeCryptBuffer(const char *pBuff,int & nBufSize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnReleaseKey
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 回收key的空间
	// $_FUNCTION_END ********************************
	void fnReleaseKey(uint32_t *pKey);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： fnGetKeyLength
	// 函数参数：
	// 返 回 值： 密钥长度
	// 函数说明： 
	// $_FUNCTION_END ********************************
	int fnGetKeyLength();
private:
	//Function to convert unsigned char to string of length 2
	void Char2Hex(unsigned char ch, char* szHex);
	//Function to convert string of length 2 to unsigned char
	void Hex2Char(char const* szHex, unsigned char& rch);
	//Function to convert string of unsigned chars to string of chars
	void  CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
	//Function to convert string of chars to string of unsigned chars
	void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： ComputeAndSendPublicKey
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 计算并生成公钥
	// $_FUNCTION_END ********************************
	int ComputeAndSendPublicKey(/*OUT*/uint8_t** pPublicKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： ComputeAndSetSessionKey
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 计算并且生成一个动态的key, 设定到加解密模块
	// $_FUNCTION_END ********************************
	bool ComputeAndSetSessionKey(const uint32_t *pKey,uint32_t nSize);
	// $_FUNCTION_BEGIN ******************************
	// 函数名称： ComputeAndSendSignature
	// 函数参数：
	// 返 回 值： 
	// 函数说明： 计算并且返回数字签名
	// $_FUNCTION_END ********************************
	int ComputeAndSendSignature(/*IN*/uint8_t** pSignature, /*OUT*/uint32_t & nSizeKey);

private:
	MyCryptLib m_cCryptLib;
	CRijndael m_cCryptor;
	SHA1_STATETYPE m_csha1Hash;
	uint32_t* m_pPublicKey;
	uint32_t m_Privatekey[_PRIVATEKEYSIZE_];
};
#endif // RSAMainFun_h__