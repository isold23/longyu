#ifndef _BASE_ENCRYPT_H_
#define _BASE_ENCRYPT_H_

#include <openssl/aes.h>
#include "include.h"

class CBaseEncrypt{
public:
	CBaseEncrypt(){}
	virtual ~CBaseEncrypt(){}

	virtual bool Encrypt(const string& astrData,const string& astrKey,string& astrResult) = 0;
	virtual bool Decrypt(const string& astrData,const string& astrKey,string& astrResult) = 0;
};

class CAESEncrypt : public CBaseEncrypt{
public:
	CAESEncrypt(){}
	virtual ~CAESEncrypt(){}

	bool Encrypt(const string& astrData,const string& astrKey,string& astrResult){
		if(astrKey.size() != AES_BLOCK_SIZE) return false;
		AES_KEY key;
		AES_set_encrypt_key((const unsigned char*)astrKey.c_str(), 128, &key);
		int liLen = astrData.size();
		int liOutLen = liLen;
		if((liLen % AES_BLOCK_SIZE) != 0){
			liOutLen = ((liLen / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
		}
		unsigned char* lpOutBuff = new unsigned char[liOutLen];
		unsigned char iv[16] = {0};
		AES_cbc_encrypt((const unsigned char*)astrData.c_str(), lpOutBuff, liOutLen,&key,iv,AES_ENCRYPT);
		astrResult = string((char*)lpOutBuff,liOutLen);               
		delete[] lpOutBuff;
		lpOutBuff = NULL;
		return true;
	}

	bool Decrypt(const string& astrData,const string& astrKey,string& astrResult){
		if(astrKey.size() != AES_BLOCK_SIZE) return false;
		AES_KEY key;
		AES_set_decrypt_key((const unsigned char*)astrKey.c_str(), 128, &key);
		int liLen = astrData.size();
		int liOutLen = liLen;
		if((liLen % AES_BLOCK_SIZE) != 0){
			liOutLen = ((liLen / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
		}
		unsigned char* lpOutBuff = new unsigned char[liOutLen+1];
		memset(lpOutBuff,0,liOutLen+1);
		unsigned char iv[16] = {0};
		AES_cbc_encrypt((const unsigned char*)astrData.c_str(), lpOutBuff,liOutLen, &key,iv,AES_DECRYPT);
		astrResult = string((char*)lpOutBuff,liOutLen);
		delete[] lpOutBuff;
		lpOutBuff = NULL;
		return true;
	}

private:	
};
#endif //_BASE_ENCRYPT_H_