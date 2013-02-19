#ifndef _BASE_ENCRYPT_H_
#define _BASE_ENCRYPT_H_

#include "include.h"

class CBaseEncrypt
{
public:
	CBaseEncrypt(){}
	virtual ~CBaseEncrypt(){}

	virtual Encrypt(const char* in_buffer, uint32 in_length, char* out_buffer, uint32 &out_length) = 0;
	virtual Decrypt(const char* in_buffer, uint32 in_length, char* out_buffer, uint32 &out_length) = 0;
};
#endif //_BASE_ENCRYPT_H_