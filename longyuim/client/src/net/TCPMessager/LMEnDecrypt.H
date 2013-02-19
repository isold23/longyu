/*****************************************************************************

                  file name :EncryptLib.h
				  Describe  :Encryption Libarary encrpyt the data using 
				             the Blowfish algorithm
				  Author    :
				  Data      :2002/5/30
				  Place     :Longmaster corporation,Yuanchenxin Building

  //zhangyawei 2007-3-9 
  添加生成密钥的函数
 ****************************************************************************/
#define N               16

class LMEnDecrypt
{
public:
    LMEnDecrypt::LMEnDecrypt();
    LMEnDecrypt(char * apKey, int aiNum);
    ~LMEnDecrypt();

	//创建密钥，密钥的长度为8个字节，定长
	void CreatePassword(char * apKey, int & aiNum);

    void InitPassword(char * apKey, int aiNum);
    int LmEncrypt(char * apInData,unsigned short aiInDataLen, char * apOutData,unsigned short& aiOutDataLen);
    int LmDecrypt(char * apInData,unsigned short aiInDataLen, char * apOutData,unsigned short& aiOutDataLen);
private:
    unsigned long F(unsigned long x);
    void Blowfish_encipher(unsigned long *xl, unsigned long *xr);
    void Blowfish_decipher(unsigned long *xl, unsigned long *xr);
private:
    //成员变量
    unsigned long P[N + 2];
    unsigned long S[4][256];
};
