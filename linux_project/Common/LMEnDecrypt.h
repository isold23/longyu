#ifndef _LMEnDecrypt_H_
#define _LMEnDecrypt_H_

#define N               16


class LMEnDecrypt
{
public:
    LMEnDecrypt();
    LMEnDecrypt(char * apKey, int aiNum);
    ~LMEnDecrypt();
    void InitPassword(char * apKey, int aiNum);
    int LmEncrypt(char * apInData,unsigned short aiInDataLen, char * apOutData,unsigned short& aiOutDataLen);
    int LmDecrypt(char * apInData,unsigned short aiInDataLen, char * apOutData,unsigned short& aiOutDataLen);
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
