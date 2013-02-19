#ifndef __HJ_CGI_H__
#define __HJ_CGI_H__

typedef struct
{
    char sRemoteAddress[50];
    char sRemotePort[10];
} HJ_CGI_CLIENT_INFO;

void HJ_Cgi_ReInit(void);
void HJ_Cgi_Init(void);
char* HJ_Cgi_Value(char *sParam);
char* HJ_Cgi_Cookie(char *key);
char** HJ_Cgi_Value_Multi(char *sParam);

void HJ_Cgi_GetClientInfo(HJ_CGI_CLIENT_INFO *pstHostInfo);
void HJ_Cgi_SetUploadOption(char *sPath, int iMaxSize);
int HJ_Cgi_IsUploadOverSize(void);

void HJ_Cgi_FreeEntries();

int HJ_Cgi_GetFormValue(unsigned char *sBuf, int *iLen, char *sName, char *sValue);
unsigned char* HJ_Cgi_GetPostValue(int *iLen);

#endif
