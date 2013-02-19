#ifndef __HJ_HTML_H__
#define __HJ_HTML_H__

#include <stdio.h>

#define HJ_HTML_MAX_SHIFT_SET  200

////////////////////////////////////////////////////////////////
typedef struct
{
    char *pcBuffer;
    char *pcCurPos;
} HJ_HTML_TEMPLATE;

typedef struct
{
    char *pcHeader;
    char *pcBuffer;
} HJ_HTML_TEMPLATE_PART;

typedef struct _HJ_HTML_PARAM
{
    char *sName;
    char *sValue;
    struct _HJ_HTML_PARAM *pstNext;
} HJ_HTML_PARAM;

////////////////////////////////////////////////////////////////

// exam: sPath='/usr/local/evs/htdocs', sFileName = /admin/login.htm
char* HJ_Html_Load(char *sPath, char *sFileName);
char* HJ_Html_Load_New(char *sPath, char *sFileName, char *sErrMsg);
void HJ_Html_File(char *pBuffer, char *start_token, char *end_token);
void HJ_Html_Free(char *pBuffer);

char* HJ_Html_GetTemplate(char *sBuffer, char *sMarkBegin, char *sMarkEnd);

int HJ_Html_SelectBox(char *sFieldName, char *sValue, char *sOption);
int HJ_Html_RadioBox(char *sFieldName, char *sValue, char *sOption);
int HJ_Html_Password(char *sFieldName, char *sValue);
int HJ_Html_TextBox(char *sFieldName, char *sValue);
int HJ_Html_TextArea(char *sFieldName, char *sValue, int iRow, int iCol);

void HJ_Html_UrlBack(void);
void HJ_Html_MessageBox(char *sMsg);
void HJ_Html_Redirect(char *sURL);

char* HJ_Html_UrlEncode(char *sDest, char *sSrc);
char* HJ_Html_TextEncode(char *sDest, char *sSrc);
char* HJ_Html_TextEncode2(char *sDest, char *sSrc);
char* HJ_Html_TextEncode4(char *sDest, char *sSrc);

/////////////////////////////////////////////////////////////
int HJ_Html_ExLoad(char *sPath, char *sFileName, HJ_HTML_TEMPLATE *pstTemplate, char *sErrMsg);
void HJ_Html_ExFree(HJ_HTML_TEMPLATE *pstTemplate);
int HJ_Html_ExGetFirstTemplatePart(HJ_HTML_TEMPLATE *pstTemplate, HJ_HTML_TEMPLATE_PART *pstTemplatePart, char *sErrMsg);
int HJ_Html_ExGetNextTemplatePart(HJ_HTML_TEMPLATE *pstTemplate, HJ_HTML_TEMPLATE_PART *pstTemplatePart, char *sErrMsg);
void HJ_Html_ExFreePart(HJ_HTML_TEMPLATE_PART *pstTemplatePart);

int HJ_Html_ParamInit(HJ_HTML_PARAM *pstParam, char *sErrMsg);
int HJ_Html_ParamAppendNode(HJ_HTML_PARAM *pstParam, char *sErrMsg, char *sName, char *sValue);
int HJ_Html_ParamAppend(HJ_HTML_PARAM *pstParam, char *sErrMsg, ...);
void HJ_Html_ParamMark(HJ_HTML_PARAM *pstSubParam, HJ_HTML_PARAM *pstParam);
void HJ_Html_ParamTruncTo(HJ_HTML_PARAM *pstParam, HJ_HTML_PARAM *pstSubParam);
void HJ_Html_ParamFree(HJ_HTML_PARAM *pstParam);

int HJ_Html_FillTemplateDef(char *sOutputBuffer, int iOutputBufferSize, FILE *pstStr
    , char *sErrMsg, char *sTemplate, HJ_HTML_PARAM *pstParam);
int HJ_Html_FillTemplateFile(FILE *pstStr, char *sErrMsg, char *sTemplate, ...);
int HJ_Html_FillTemplateStr(char *sOutputBuffer, int iOutputBufferSize, char *sErrMsg, char *sTemplate, ...);
void HJ_Html_FillTemplate(char *sTemplate, ...);

#endif
