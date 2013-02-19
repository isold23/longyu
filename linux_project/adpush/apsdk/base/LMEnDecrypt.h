
#ifndef _LMEnDecrypt_H_
#define _LMEnDecrypt_H_

#define N               16

#include <stdint.h>

class LMEnDecrypt
{
public:
    LMEnDecrypt();
    LMEnDecrypt(char * apKey, int aiNum);
    ~LMEnDecrypt();
    void InitPassword(char * apKey, int aiNum);
    int LmEncrypt(char * apInData,uint16_t aiInDataLen, char * apOutData,uint16_t& aiOutDataLen);
    int LmDecrypt(char * apInData,uint16_t aiInDataLen, char * apOutData,uint16_t& aiOutDataLen);
private:
    unsigned int F(unsigned int x);
    void Blowfish_encipher(unsigned int *xl, unsigned int *xr);
    void Blowfish_decipher(unsigned int *xl, unsigned int *xr);
private:
    //成员变量
    unsigned int P[N + 2];
    unsigned int S[4][256];
};
#endif //_LMEnDecrypt_H_
