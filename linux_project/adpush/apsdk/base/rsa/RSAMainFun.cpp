#include "RSAMainFun.h"


CRSAMainFun::CRSAMainFun(void)
{
	m_pPublicKey = NULL;
}

CRSAMainFun::~CRSAMainFun(void)
{
	if (m_pPublicKey)
	{
		delete [] m_pPublicKey;
		m_pPublicKey = NULL;
	}
}



//////////////////////////////////////////////////////////////////////////
const uint32_t m_DSAKeypubN[32] = {
0xd93be485, 0x9936a337, 0xbd49e021, 0x856ca134, 0xafcfe6d7, 0xe404aa01, 
0x1ecfbbbb, 0x99137ff4, 0x6b41a1f1, 0xd344cabf, 0x31e47340, 0x317e1f3d, 
0x979adcf4, 0x447117bc, 0x9a58e465, 0xa5061d5c, 0x4e24438e, 0x79045212, 
0x7ffa4369, 0xed8d751a, 0x3b451823, 0xec76485e, 0xadc3fbfa, 0x9c69dbd2, 
0xddd5bc5f, 0x965d907a, 0xcb85871b, 0x3073239c, 0x980c0916, 0xd3b46e03, 
0xa2dfba57, 0x9e66f5a6, };

const uint32_t m_DSAKeypubD[32] = {
	0x06082373, 0x3ec34a4c, 0x9f44280c, 0x80ff0ce5, 0x5643e806, 0xd950f5c3, 
	0x97e85a63, 0x8890ac63, 0xef7e457c, 0x8a13d522, 0x67c248be, 0xdad660d2, 
	0x06780a45, 0xc187f1be, 0xd29ac11a, 0x0be7709b, 0x896d825e, 0xa602e161, 
	0xaaa6d79b, 0x9e5e4e11, 0x7cd8bac2, 0x484edae9, 0xc92d52a7, 0xbd9be7e1, 
	0xe939283f, 0x643e6051, 0x87ae5a12, 0x204cc268, 0x655d5b64, 0x8d22f402, 
	0xc1ea7c3a, 0x6999f919, };

const uint32_t m_DSAKeypubE = 3;
//////////////////////////////////////////////////////////////////////////

//Function to convert unsigned char to string of length 2
void CRSAMainFun::Char2Hex(unsigned char ch, char* szHex)
{
	unsigned char byte[2];
	byte[0] = ch/16;
	byte[1] = ch%16;
	for(int i=0; i<2; i++)
	{
		if(byte[i] >= 0 && byte[i] <= 9)
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	}
	szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void CRSAMainFun::Hex2Char(char const* szHex, unsigned char& rch)
{
	rch = 0;
	for(int i=0; i<2; i++)
	{
		if(*(szHex + i) >='0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}

//Function to convert string of unsigned chars to string of chars
void  CRSAMainFun::CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize)
{
	int i;
	char szHex[3];
	pszHexStr[0] = 0;
	for(i=0; i<iSize; i++)
	{
		Char2Hex(pucCharStr[i], szHex);
		//strcat_s(pszHexStr,sizeof(char), szHex);
		strcat(pszHexStr, szHex);
	}
}

//Function to convert string of chars to string of unsigned chars
void CRSAMainFun::HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	for(i=0; i<iSize; i++)
	{
		Hex2Char(pszHexStr+2*i, ch);
		pucCharStr[i] = ch;
	}
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： ComputeAndSendPublicKey
// 函数参数：
// 返 回 值： 
// 函数说明： 计算并生成公钥
// $_FUNCTION_END ********************************
int CRSAMainFun::ComputeAndSendPublicKey(uint8_t** pPublicKey, uint32_t &nKeySize)
{
	// Be safe or no need to do the work 
	if (!m_pPublicKey)
		return NULL;

	uint32_t bnPublicKeyAB[_PRIVATEKEYSIZE_];
	uint32_t bnG[_PRIVATEKEYSIZE_];
	uint32_t nPublicKeySize=_PRIVATEKEYSIZE_;

	m_cCryptLib.BNSetEqualdw(bnG,5,_PRIVATEKEYSIZE_);
	// A= g^ a mod(p). 
	m_cCryptLib.BNModExp(bnPublicKeyAB, bnG, m_Privatekey, m_pPublicKey,nPublicKeySize);
	// Hash it for Digital Signing (later on)..
	m_cCryptLib.SHA1_Hash((uint8_t*)bnPublicKeyAB,_PRIVATEKEYSIZE_*4,&m_csha1Hash);

	* pPublicKey = new uint8_t[nPublicKeySize*4];
	memset(* pPublicKey, 0, nPublicKeySize*4);
	memcpy(* pPublicKey, (uint8_t*)bnPublicKeyAB, nPublicKeySize*4);
	// Send the public key. 
	nKeySize = nPublicKeySize*4;

	return 0;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： ComputeAndSetSessionKey
// 函数参数：
// 返 回 值： 
// 函数说明： 计算并且生成一个动态的key, 设定到加解密模块
// $_FUNCTION_END ********************************
bool CRSAMainFun::ComputeAndSetSessionKey(const uint32_t *pKey,uint32_t nSize)
{
	uint32_t  nKeySize=nSize;
	uint32_t bnSessionKey[_PRIVATEKEYSIZE_];

	// Hash PublicKeyA or B for Digital Signing (later on).. 
	m_cCryptLib.SHA1_Hash((uint8_t*)pKey,nKeySize*4,&m_csha1Hash);
	// S= A^ b mod(p). 
	m_cCryptLib.BNModExp(bnSessionKey, pKey, m_Privatekey, m_pPublicKey,nKeySize);

	// Use the Session key.. (we do not trust it until we check the signature.)

	m_cCryptor.MakeKey((const char * )bnSessionKey,(const char * )(bnSessionKey+8),16,16);

	return true;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： ComputeAndSendSignature
// 函数参数：
// 返 回 值： 
// 函数说明： 计算并且返回数字签名
// $_FUNCTION_END ********************************
int CRSAMainFun::ComputeAndSendSignature(uint8_t** pSignature, uint32_t & nSizeKey)
{
	// FIXME: Change later. 
	const uint32_t nSize=sizeof(m_DSAKeypubD)/4;

	uint32_t S[nSize];
	int iRet=0;

	// Finish the Hash of public key A and key B. 
	uint32_t aHashValue[_HASHSIZE_/4];

	m_cCryptLib.BNSetZero(aHashValue,_HASHSIZE_/4);
	m_cCryptLib.BNSetZero(S,nSize);

	m_cCryptLib.SHA1_Finish((unsigned char*)aHashValue,&m_csha1Hash);

	// FIXME: REMOVE LATER: 

	//  Compute hash^d mod n
	iRet=m_cCryptLib.BNModExp(S,aHashValue,m_DSAKeypubD,m_DSAKeypubN,nSize);

	*pSignature = new uint8_t[nSize*4];
	memset(*pSignature, 0, nSize*4);
	memcpy(*pSignature, (uint8_t*)S, nSize*4);
	// Send the public key. 
	nSizeKey = nSize*4;

	return 0;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAGetPublicKey
// 函数参数： 
// 返 回 值： 
// 函数说明： 获得初始公钥
// $_FUNCTION_END ********************************
int CRSAMainFun::fnRSAGetPublicKey(uint32_t ** pPublicKey,uint32_t & nKeySize)
{
	// Generate a new Public key if you did not have it or whant to use the old one
	// Delete the m_pBublicKey 
	if ( m_pPublicKey )
	{
		delete[] m_pPublicKey;
		m_pPublicKey =NULL;
	}

	nKeySize = 4;
	m_pPublicKey = new uint32_t[nKeySize];
	memset(m_pPublicKey, 0, nKeySize);

	// be safe. 
	if ( !m_pPublicKey )
	{
		return -1;
	}

	uint32_t nSize = m_cCryptLib.BNMakePrime(m_pPublicKey,nKeySize);

	if ( nSize > 0 )
	{
		* pPublicKey = new uint32_t[nKeySize];
		memset(* pPublicKey, 0, nKeySize);
		memcpy(* pPublicKey, m_pPublicKey, nKeySize*sizeof(uint32_t));

		return 0;
	}
	else
	{ 
		return -1;
	}

}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAClientMakePassWord
// 函数参数：
// 返 回 值： 
// 函数说明： 设定客户端密钥, 同时返回一个新的密钥给服务器
// $_FUNCTION_END ********************************
int CRSAMainFun::fnRSAClientMakePassWord(const uint32_t *pKey, uint8_t** pOutKey, uint32_t &nKeySize)
{
	// Be safe
	if ( !pKey )
		return NULL;

	// Generate private key.. (just a Random nr) 
	m_cCryptLib.BNMakeRandomNr(m_Privatekey,_PRIVATEKEYSIZE_);

	if ( ComputeAndSetSessionKey(pKey,nKeySize) )
	{

		// Compute And Send Public Key B. 
		// FIXME : Should post this part into the 
		// IOCP for fair cpu clock distribution.
		// Takes about ~40ms.. 
		int nRet = ComputeAndSendPublicKey(pOutKey, nKeySize);

		return 0;	
	}else
		return -1;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAServerMakePassWord
// 函数参数：
// 返 回 值： 
// 函数说明： 设定服务器端密钥, 同时返回数字签名给客户端以便验证可靠性
// $_FUNCTION_END ********************************
int CRSAMainFun::fnRSAServerMakePassWord(const uint32_t *pKey, uint8_t** pOutKey, uint32_t &nKeySize)
{
	ComputeAndSetSessionKey(pKey,nKeySize);
	int nRet = ComputeAndSendSignature(pOutKey , nKeySize);
	return nRet;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAVerifyKey
// 函数参数：
// 返 回 值： 
// 函数说明： 数字签名认证, 同时返回给服务器
// $_FUNCTION_END ********************************
int CRSAMainFun::fnRSAVerifyKey(const uint32_t *pKey, uint8_t** pOutKey, uint32_t &nKeySize)
{
	// Make sure that the Public key P is accepted for year 2005, _MINPUBLICKEYPSIZE_ = 1024 bits. 
	// FIXME:  What if the public key P is not prime ? is the security broken ? 
	uint32_t nPubKeyBitLength= m_cCryptLib.BNBitLength(pKey,nKeySize);

	if (  nPubKeyBitLength < _MINPUBLICKEYPSIZE_)
	{
		return -1; 
	}

	// We must make a copy of the public key P. 
	// FIXME: allocate data on the heap is bad (hmm change later) 
	uint32_t* pPublicKeyP=NULL;
	pPublicKeyP= new uint32_t[nKeySize];
	if ( pPublicKeyP )
	{
		memcpy(pPublicKeyP,pKey,nKeySize*sizeof(uint32_t));
	}else
	{
		return -1;
	}

	// allocate data on the heap is bad (hmm change later) 
	if ( m_pPublicKey )
		delete[] m_pPublicKey;

	m_pPublicKey = pPublicKeyP;

	// Generate private key.. (just a Random nr) 
	m_cCryptLib.BNMakeRandomNr(m_Privatekey,_PRIVATEKEYSIZE_);


	// Compute And Send Public Key A. 
	// FIXME : Should post this part into the 
	// IOCP for fair cpu clock distribution.
	// Takes about ~40ms.. 
	int nRet = ComputeAndSendPublicKey(pOutKey, nKeySize);

	return nRet;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAStartHash
// 函数参数：
// 返 回 值： 
// 函数说明： 开始HASH计算
// $_FUNCTION_END ********************************
void CRSAMainFun::fnRSAStartHash(void)
{
	memset(&(m_csha1Hash),0,sizeof(m_csha1Hash));
	m_cCryptLib.SHA1_Start(&(m_csha1Hash));
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnRSAFinishHash
// 函数参数：
// 返 回 值： 
// 函数说明： HASH完成
// $_FUNCTION_END ********************************
bool CRSAMainFun::fnRSAFinishHash(const uint32_t *pKey,uint32_t nKeySize)
{
	// Be safe
	if (!m_pPublicKey)
		return false;

	// FIXME: Change later. Size of is BAD can give different answer (depends on compilation)
	const uint32_t nPubkeySize=sizeof(m_DSAKeypubN)/4;
	uint32_t aRefHashValue[nPubkeySize];
	uint32_t aPubKeyE[nPubkeySize];
	int iRet=0;

	// Finish the Hash of public key A and key B. 
	uint32_t aHashValue[_HASHSIZE_/4];

	m_cCryptLib.BNSetZero(aRefHashValue,nPubkeySize);
	m_cCryptLib.BNSetEqualdw(aPubKeyE,m_DSAKeypubE,nPubkeySize);

	// Compute the hash value. 
	m_cCryptLib.SHA1_Finish((unsigned char*)aHashValue,&m_csha1Hash);

	//  Compute y=(S)^e mod n ptmp2=e=3. 
	iRet=m_cCryptLib.BNModExp(aRefHashValue,pKey,aPubKeyE,m_DSAKeypubN,nPubkeySize);

	// Check if signature was correct..
	if ( iRet >= 0 && m_cCryptLib.BNIsEqual(aRefHashValue,aHashValue,_HASHSIZE_/4))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnDeCryptBuffer
// 函数参数：
// 返 回 值： 
// 函数说明： 加密
// $_FUNCTION_END ********************************
char* CRSAMainFun::fnEnCryptBuffer(const char *pBuff, int & nBufSize)
{
	if (pBuff == NULL)
	{
		return NULL;
	}

	int liTemp = nBufSize%16;
	nBufSize = liTemp == 0?nBufSize:nBufSize + 16- liTemp;
	char * pCrypBuff = new char[nBufSize];
	memset(pCrypBuff, 0, nBufSize);
	m_cCryptor.Encrypt(pBuff, pCrypBuff, nBufSize);

	// 	char * szHex = new char[nBufSize];
	// 	CharStr2HexStr((unsigned char*)pCrypBuff, szHex, nBufSize);

	return pCrypBuff;
}
// $_FUNCTION_BEGIN ******************************
// 函数名称： fnDeCryptBuffer
// 函数参数：
// 返 回 值： 
// 函数说明： 解密
// $_FUNCTION_END ********************************
char* CRSAMainFun::fnDeCryptBuffer(const char *pBuff,int & nBufSize)
{
	if ( pBuff == NULL)
		return NULL;


	// 	char * pHex = new char[nBufSize];
	// 	HexStr2CharStr(pBuff, (unsigned char *)pHex, strlen(pBuff));

	int liTemp = nBufSize%16;
	nBufSize = liTemp == 0?nBufSize:nBufSize + 16- liTemp;
	char * pCrypBuff = new char[nBufSize];
	memset(pCrypBuff, 0, nBufSize);
	//m_cCryptor.DecryptBlock(pBuff, pCrypBuff);
	m_cCryptor.Decrypt(pBuff, pCrypBuff, nBufSize);

	return pCrypBuff;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称： fnReleaseKey
// 函数参数：
// 返 回 值： 
// 函数说明： 回收key的空间
// $_FUNCTION_END ********************************
void CRSAMainFun::fnReleaseKey(uint32_t *pKey)
{
	delete [] pKey;
	pKey = NULL;
}

int CRSAMainFun::fnGetKeyLength()
{
	return m_cCryptor.GetKeyLength();
}