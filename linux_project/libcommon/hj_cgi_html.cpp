#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "hj_str.h"
#include "hj_cgi_html.h"

#define HJ_HTML_PMARK_COMMENT         "#"

#define HJ_HTML_PMARK_BEGIN           "$"
#define HJ_HTML_PMARK_END             "$"

#define HJ_HTML_PMARK_BEGIN_FILLER    "<%"
#define HJ_HTML_PMARK_END_FILLER      "%>"

#define HJ_HTML_PART_BEGIN_FILLER     "<%!"
#define HJ_HTML_PART_END_FILLER       "!%>"

char* HJ_Html_Load(char *sPath, char *sFileName)
{
    char html_file[200];
    strcpy(html_file, sPath);
    strcat(html_file, sFileName);

    if ((html_file[0] != '/') && (html_file[0] != '.'))
    {
        printf("html_file must start with '/' or '../'!\n");
        return NULL;
    }

    FILE *fp = NULL;
    if ((fp = fopen(html_file, "r")) == NULL)
    {
        printf("HJ_Html_Load():fopen fail:%s!\n", html_file);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *pBuffer = (char*)malloc(size + 1);
    fread(pBuffer, size, 1, fp);

    pBuffer[size] = 0;

    fclose(fp);
    return pBuffer;
}

char *HJ_Html_Load_New(char *sPath, char *sFileName, char *sErrMsg)
{
    char html_file[200];

    strcpy(html_file, sPath);
    strcat(html_file, sFileName);

    if ((html_file[0] != '/') && (html_file[0] != '.'))
    {
        if(sErrMsg != NULL)
        {
            sprintf(sErrMsg, "html_file must start with '/' or '../'!");
        }

        return NULL;
    }

    FILE *fp = NULL;
    if ((fp = fopen(html_file, "r")) == NULL)
    {
        if (sErrMsg != NULL)
        {
            sprintf(sErrMsg, "HJ_Html_Load():fopen fail:%s!", html_file);
        }

        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *pBuffer = (char*)malloc(size+1);
    fread(pBuffer, size, 1, fp);

    pBuffer[size] = 0;

    fclose(fp);
    return pBuffer;
}

void HJ_Html_File(char *pBuffer, char *start_token, char *end_token)
{
    char *p1 = NULL;
    if (strlen(start_token) == 0)
    {
        p1 = pBuffer;
    }
    else
    {
        p1 = strstr(pBuffer, start_token);
        if (p1 == NULL)
        {
            printf("HJ_Html_File():start_token[%s] not found in html file.\n"
                , start_token);
            return;
        }
        p1 = p1 + strlen(start_token);
    }

    char *p2 = NULL;
    if (strlen(end_token) == 0)
    {
        p2 = pBuffer + strlen(pBuffer) - 1;
    }
    else
    {
        p2 = strstr(pBuffer, end_token);
        if (p2 == NULL)
        {
            printf("HJ_Html_File():end_token[%s] not found in html file.\n"
                , end_token);
            return;
        }
    }

    if (p1 >= p2)
    {
        printf("HJ_Html_File():start_token must before end_token\n");
        return;
    }

    long output_size = p2 - p1;
    char *temp = (char*)malloc(output_size + 1);
    strncpy(temp, p1, output_size);
    temp[output_size] = '\0';
    printf("%s", temp);
    free(temp);
}

void HJ_Html_Free(char *pBuffer)
{
    if (pBuffer != NULL)
    {
        free(pBuffer);
    }
    pBuffer = NULL;
}

////////////////////////////////////////////////////////////////////////////////////

char* HJ_Html_GetTemplate(char *sBuffer, char *sMarkBegin, char *sMarkEnd)
{
    char *pcBegin = NULL;
    if (strlen(sMarkBegin) == 0)
    {
        pcBegin = sBuffer;
    }
    else
    {
        pcBegin = strstr(sBuffer, sMarkBegin);
        if (pcBegin == NULL)
        {
            printf("html_file():start_token[%s] not found in html file.\n", sMarkBegin);
            return NULL;
        }
        pcBegin = pcBegin + strlen(sMarkBegin);
    }

    char *pcEnd = NULL;
    if (strlen(sMarkEnd) == 0)
    {
        pcEnd = sBuffer + strlen(sBuffer);
    }
    else
    {
        //pcEnd = strstr(sBuffer, sMarkEnd);
        pcEnd = strstr(pcBegin, sMarkEnd);
        if (pcEnd == NULL)
        {
            printf("html_file():end_token[%s] not found in html file.\n", sMarkEnd);
            return NULL;
        }
    }

    if (pcBegin >= pcEnd)
    {
        printf("html_file():start_token must before end_token\n");
        return NULL;
    }

    long lSize = pcEnd - pcBegin;
    char *sTemplate = (char*)malloc(lSize + 1);
    strncpy(sTemplate, pcBegin, lSize);
    sTemplate[lSize] = '\0';
    return sTemplate;
}

char *HJ_Html_TextEncode2(char *sDest, char *sSrc) // 有处理回车符
{
    char *pcDest = sDest;
    *pcDest = 0;
    char *pcSrc = sSrc;

    while (1)
    {
        if (*pcSrc == 0)
        {
            break;
        }
        else if (*pcSrc == '\n')
        {
            strcpy(pcDest, "<br>");
        }
        else if (*pcSrc == '<')
        {
            strcpy(pcDest, "&lt;");
        }
        else if (*pcSrc == '>')
        {
            strcpy(pcDest, "&gt;");
        }
        else if (*pcSrc == '&')
        {
            strcpy(pcDest, "&amp;");
        }
        else if (*pcSrc == ' ')
        {
            if (*(pcSrc+1) == ' ')
            {
                strcpy(pcDest, "&nbsp;");
            }
            else
            {
                if ((pcSrc == sSrc) || (*(pcSrc-1) == '\n'))
                {
                    strcpy(pcDest, "&nbsp;");
                }
                else
                {
                    strcpy(pcDest, " ");
                }
            }
        }
        else
        {
            *pcDest = *pcSrc;
            pcDest ++;
            *pcDest = 0;
        }

        pcDest = pcDest + strlen(pcDest);
        pcSrc ++;
    }

    return sDest;
}


char *HJ_Html_TextEncode(char *sDest, char *sSrc) //不处理回车符
{
    char *pcDest = sDest;
    *pcDest = 0;
    char *pcSrc = sSrc;

    while (1)
    {
        if (*pcSrc == 0)
        {
            break;
        }
        else if (*pcSrc == '<')
        {
            strcpy(pcDest, "&lt;");
        }
        else if (*pcSrc == '>')
        {
            strcpy(pcDest, "&gt;");
        }
        else if (*pcSrc == '&')
        {
            strcpy(pcDest, "&amp;");
        }
        else if (*pcSrc == '\"')
        {
            strcpy(pcDest, "&quot;");
        }
        else if (*pcSrc == ' ')
        {
            if (*(pcSrc+1) == ' ')
            {
                strcpy(pcDest, "&nbsp;");
            }
            else
            {
                if ((pcSrc == sSrc) || (*(pcSrc-1) == '\n'))
                {
                    strcpy(pcDest, "&nbsp;");
                }
                else
                {
                    strcpy(pcDest, " ");
                }
            }
        }
        else
        {
            *pcDest = *pcSrc;
            pcDest ++;
            *pcDest = 0;
        }
        pcDest = pcDest + strlen(pcDest);
        pcSrc ++;
    }

    return sDest;
}

char *HJ_Html_UrlEncode(char *sDest, char *sSrc)
{
    sDest[0] = '\0';
    size_t i;
    for (i = 0; i < strlen(sSrc); i++)
    {
        switch (sSrc[i])
        {
            case '&': strcat(sDest, "%26"); break;
            case '=': strcat(sDest, "%3D"); break;
            case '%': strcat(sDest, "%25"); break;
            case '+': strcat(sDest, "%2B"); break;
            case '?': strcat(sDest, "%3F"); break;
            case ' ': strcat(sDest, "+");   break;
            default: sprintf(sDest, "%s%c", sDest, sSrc[i]);
        }
    }
    return sDest;
}

void HJ_Html_MessageBox(char *sMsg)
{
    char sBuffer[1024];
    strncpy(sBuffer, sMsg, sizeof(sBuffer) - 1);
    sBuffer[sizeof(sBuffer) - 1] = 0;

    size_t i;
    for (i = 0; i < strlen(sBuffer); i++) 
    {
        if ((sBuffer[i] == '\r') || (sBuffer[i] == '\n')
            || (sBuffer[i] == '\t') || ((unsigned)sBuffer[i] < 0x20))
        {
            sBuffer[i] = ' ';
        }
        else if (sBuffer[i] == '\'')
        {
            sBuffer[i] = '`';
        }
    }

    printf("<script text='text/javascript'>");
    printf("\n<!--");
    printf("\nalert('%s');", sBuffer);
    printf("\n//--></script>");
}

void HJ_Html_UrlBack(void)
{
    printf("<script text='text/javascript'>");
    printf("\n<!--");
    printf("\nhistory.back();");
    printf("\n//--></script>");
}

void HJ_Html_Redirect(char *sURL)
{
    /*
    HTTP/1.1 302 Object moved
    Server: Microsoft-IIS/4.0
    Date: Sun, 17 Oct 1999 09:23:21 GMT
    Location: http://www.oicq.com
    Content-Type: text/html
    Set-Cookie: ASPSESSIONIDQGGQGQAZ=OCHBOKFBHPFEPNJDJDOJDEBM; path=/
    Cache-control: private
    */

    //改用直接输出ＪＡＶＡ脚本刷新，因为下面原来的方法用后会导致ＣＧＩ执行不正常。 
    //注意被刷新的页面应避免被CACHE，如在页头加入<meta http-equiv="pragma" content="no-cache"> (Agong)
    //在所导向的URL后面加上一个按时间生成的唯一参数， 形成不同的URL，避免浏览器读CACHE。 （AGONG 2000-1-17）

    time_t ltime;
    time(&ltime);

    char url[500];
    strncpy(url, sURL, 500);

    if (strstr(url, "?") == NULL)
    {
        strcat(url, "?");
    }
    else
    {
        strcat(url, "&");
    }

    printf("<script type='text/javascript'>\n");
    printf("window.location='%sPcacheTime=%ld';\n", url, ltime);
    printf("</script>\n");

    // printf("Location: %s", sURL);
    // printf("\nCache-control: private");
    // printf("\n\n\n\n");

}

int HJ_Html_TextArea(char *sFieldName, char *sValue, int iRow, int iCol)
{
    return printf("<textarea name='%s' rows='%d' cols='%d'>%s</textarea>\n", sFieldName, iRow, iCol, sValue);
}

int HJ_Html_TextBox(char *sFieldName, char *sValue)
{
    return printf("<input type='text' size='30' name='%s' value='%s'>\n", sFieldName, sValue);
}

int HJ_Html_Password(char *sFieldName, char *sValue)
{
    return printf("<input type='password' size='30' name='%s' value='%s'>\n", sFieldName, sValue);
}

static char *GetToken(char *sToken, char *sSrc, char cFilter)
{
    char *pb = sSrc;
    char *pe = strchr(pb, cFilter);
    if (pe == NULL)
    {
        strcpy(sToken, pb);
        return sSrc + strlen(sSrc);
    }
    else
    {
        int i = 0;
        while ((pb + i) < pe)
        {
            sToken[i] = *(pb + i);
            i ++;
        }
        sToken[i] = 0;
        return sSrc + i + 1;
    }
}

int HJ_Html_RadioBox(char *sFieldName, char *sValue, char *sOption)
{
    char sVal[100];
    char sName[100];
    char *pb = sOption;
    while (*pb != 0)
    {
        pb = GetToken(sVal, pb, ',');
        pb = GetToken(sName, pb, ';');

        if (strcmp(sVal, sValue) == 0)
        {
            printf("<input type='radio' name='%s' checked value='%s'>%s\n"
                , sFieldName, sVal, sName);
        }
        else
        {
            printf("<input type='radio' name='%s' value='%s'>%s\n"
                , sFieldName, sVal, sName);
        }
    }
    return 0;
}

int HJ_Html_SelectBox(char *sFieldName, char *sValue, char *sOption)
{

    printf("<select name='%s'>\n", sFieldName);
    char sVal[100];
    char sName[100];
    char *pb = sOption;
    while (*pb != 0)
    {
        pb = GetToken(sVal, pb, ',');
        pb = GetToken(sName, pb, ';');

        if (strcmp(sVal, sValue) == 0)
        {
            printf("<option selected value='%s'>%s</option>\n"
                , sVal, sName);
        }
        else
        {
            printf("<option value='%s'>%s</option>\n"
                , sVal, sName);
        }
    }
    printf("</select>\n");
    return 0;
}

/////////////////////////////////////////////////////////////////////////

int HJ_Html_ExLoad(char *sPath, char *sFileName, HJ_HTML_TEMPLATE *pstTemplate, char *sErrMsg)
{
    char html_file[200];

    strcpy(html_file, sPath);
    strcat(html_file, sFileName);

    if (html_file[0] != '/') 
    {
        strcpy(sErrMsg, "Template File Name Must Start With '/'");
        return 1;
    }

    FILE *fp = NULL;
    if ((fp = fopen(html_file, "r")) == NULL) 
    {
        sprintf(sErrMsg, "Fail To Open Template File:%s", html_file);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    pstTemplate->pcBuffer = (char*)malloc(size+1);
    if (pstTemplate->pcBuffer == NULL)
    {
        sprintf(sErrMsg, "HJ_Html_Load():Fail To Alloc Memory");
        return -1;
    }

    if (fread(pstTemplate->pcBuffer, size, 1, fp) < 0)
    {
        sprintf(sErrMsg, "Fail To Read Template File:%s", html_file);
        return -1;
    }

    pstTemplate->pcBuffer[size] = 0;

    fclose(fp);

    pstTemplate->pcCurPos = pstTemplate->pcBuffer;
    return 0;
}

void HJ_Html_ExFree(HJ_HTML_TEMPLATE *pstTemplate)
{
    free(pstTemplate->pcBuffer);
}

int HJ_Html_ExGetFirstTemplatePart(HJ_HTML_TEMPLATE *pstTemplate, HJ_HTML_TEMPLATE_PART *pstTemplatePart, char *sErrMsg)
{
    pstTemplate->pcCurPos = pstTemplate->pcBuffer;

    return HJ_Html_ExGetNextTemplatePart(pstTemplate, pstTemplatePart, sErrMsg);
}

char *HJ_Html_NewStr(char *s)
{
    int iSize = strlen(s);
    char *p = (char*)malloc(iSize+1);
    if (p == NULL)
    {
        return NULL;
    }

    strcpy(p, s);
    return p;
}

char *HJ_Html_NewSubStr(char *pcBegin, char *pcEnd)
{
    char cTemp = *pcEnd;
    *pcEnd = 0;
    char *p = HJ_Html_NewStr(pcBegin);
    *pcEnd = cTemp;

    return p;
}

int HJ_Html_ExGetNextTemplatePart(HJ_HTML_TEMPLATE *pstTemplate, HJ_HTML_TEMPLATE_PART *pstTemplatePart
    , char *sErrMsg)
{
    pstTemplatePart->pcHeader = NULL;
    pstTemplatePart->pcBuffer = NULL;

    if (pstTemplate->pcCurPos[0] == 0)
    {
        return 1;
    }

    char *pc = strstr(pstTemplate->pcCurPos, HJ_HTML_PART_BEGIN_FILLER);
    if (pc == NULL)
    {
        pstTemplatePart->pcHeader = HJ_Html_NewStr("");
        pstTemplatePart->pcBuffer = HJ_Html_NewStr(pstTemplate->pcCurPos);

        if ((pstTemplatePart->pcHeader == NULL) || (pstTemplatePart->pcBuffer == NULL))
        {
            sprintf(sErrMsg, "Fail To Alloc Template Part Mem");
            return -1;
        }
        pstTemplate->pcCurPos = pstTemplate->pcBuffer + strlen(pstTemplate->pcBuffer);
        return 0;
    }

    if (pc != pstTemplate->pcCurPos)
    {
        pstTemplatePart->pcHeader = HJ_Html_NewStr("");
        pstTemplatePart->pcBuffer = HJ_Html_NewSubStr(pstTemplate->pcCurPos, pc);

        if ((pstTemplatePart->pcHeader == NULL) || (pstTemplatePart->pcBuffer == NULL))
        {
            sprintf(sErrMsg, "Fail To Alloc Template Part Mem");
            return -1;
        }
        pstTemplate->pcCurPos = pc;
        return 0;
    }

    pc = pc + strlen(HJ_HTML_PART_BEGIN_FILLER);
    char *pc1 = strstr(pc, HJ_HTML_PART_END_FILLER);
    if (pc1 == NULL)
    {
        sprintf(sErrMsg, "Invalid Template Format: Part End Filler Needed");
        return -1;
    }

    pstTemplatePart->pcHeader = HJ_Html_NewSubStr(pc, pc1);

    pc = pc1 + strlen(HJ_HTML_PART_END_FILLER);
    pc1 = strstr(pc, HJ_HTML_PART_BEGIN_FILLER);

    if (pc1 == NULL)
    {
        pstTemplatePart->pcBuffer = HJ_Html_NewStr(pc);
    }
    else
    {
        pstTemplatePart->pcBuffer = HJ_Html_NewSubStr(pc, pc1);
    }

    if ((pstTemplatePart->pcHeader == NULL) || (pstTemplatePart->pcBuffer == NULL))
    {
        sprintf(sErrMsg, "Fail To Alloc Template Part Mem");
        return -1;
    }

    if (pc1 == NULL)
    {
        pstTemplate->pcCurPos = pstTemplate->pcCurPos+strlen(pstTemplate->pcCurPos);
    }
    else
    {
        pstTemplate->pcCurPos = pc1;
    }
    return 0;
}

void HJ_Html_ExFreePart(HJ_HTML_TEMPLATE_PART *pstTemplatePart)
{
    if (pstTemplatePart->pcHeader != NULL)
    {
        free(pstTemplatePart->pcHeader);
    }

    if (pstTemplatePart->pcBuffer != NULL)
    {
        free(pstTemplatePart->pcBuffer);
    }

    pstTemplatePart->pcHeader = NULL;
    pstTemplatePart->pcBuffer = NULL;
}

int HJ_Html_FillTemplateDef(char *sOutputBuffer, int iOutputBufferSize, FILE *pstStr
    , char *sErrMsg, char *sTemplate, HJ_HTML_PARAM *pstParam)
{
    char *sNextOutput = NULL;
    int iLen = 0, iOutputSizeLeft = 0;
    if (sOutputBuffer == NULL)
    {
        sNextOutput = NULL;
    }
    else
    {
        iLen = strlen(sOutputBuffer);
        sNextOutput = sOutputBuffer + iLen;
        iOutputSizeLeft = iOutputBufferSize - iLen - 1;
    }

    char cTemp;
    int iTemp;
    char *pcCommentParam = NULL;
    HJ_HTML_PARAM *pstCurParam = NULL;

    char *pcOutputBegin = sTemplate, *pcOutputEnd = NULL;
    int iInCommentRange = 0;
    char *pcMarkBegin = NULL, *pcParamBegin = NULL, *pcParamEnd = NULL;
    while (1)
    {
        if (*pcOutputBegin == 0)
        {
            return 0;
        }

        pcMarkBegin = strstr(pcOutputBegin, HJ_HTML_PMARK_BEGIN);
        if (pcMarkBegin == NULL)
        {
            pcOutputEnd = pcOutputBegin + strlen(pcOutputBegin);
        }
        else
        {
            pcOutputEnd = pcMarkBegin;
            if ((pcMarkBegin - pcOutputBegin) >= (int)strlen(HJ_HTML_PMARK_BEGIN_FILLER))
            {
                if (strncmp(pcMarkBegin - strlen(HJ_HTML_PMARK_BEGIN_FILLER)
                    , HJ_HTML_PMARK_BEGIN_FILLER, strlen(HJ_HTML_PMARK_BEGIN_FILLER)) == 0)
                {
                    pcOutputEnd = pcMarkBegin - strlen(HJ_HTML_PMARK_BEGIN_FILLER);
                }
            }
        }

        if (iInCommentRange == 0)
        {
            cTemp = *pcOutputEnd;
            *pcOutputEnd = 0;
            if (sNextOutput != NULL)
            {
                iLen = strlen(pcOutputBegin);
                if (iOutputSizeLeft < iLen)
                {
                    strcpy(sErrMsg, "Output Buffer Out Of Size");
                    return 1;
                }
                strcpy(sNextOutput, pcOutputBegin);
                sNextOutput += iLen;
                iOutputSizeLeft -= iLen;
            }
            else if (pstStr != NULL)
            {
                fprintf(pstStr, "%s", pcOutputBegin);
            }
            else
            {
                printf("%s", pcOutputBegin);
            }
            *pcOutputEnd = cTemp;
        }

        if (*pcOutputEnd == 0)
        {
            return 0;
        }

        pcParamBegin = pcMarkBegin + strlen(HJ_HTML_PMARK_BEGIN);
        pcParamEnd = strstr(pcParamBegin, HJ_HTML_PMARK_END);
        if (pcParamEnd == NULL)
        {
            strcpy(sErrMsg, "HJ_Html_ExFillTemplate():HJ_HTML_PMARK_END not found");
            return 1;
        }

        if (iInCommentRange == 0)
        {
            pstCurParam = pstParam->pstNext;
            while (pstCurParam != NULL)
            {
                // if (strncmp(pstCurParam->sName, pcParamBegin, pcParamEnd-pcParamBegin) == 0)
                cTemp = *pcParamEnd;
                *pcParamEnd = 0;
                iTemp = HJ_Str_StrCmp(pcParamBegin, pstCurParam->sName);
                *pcParamEnd = cTemp;

                if (iTemp == 0)
                {
                    if (sNextOutput != NULL)
                    {
                        iLen = strlen(pstCurParam->sValue);
                        if (iOutputSizeLeft < iLen)
                        {
                            strcpy(sErrMsg, "Output Buffer Out Of Size");
                            return 1;
                        }
                        strcpy(sNextOutput, pstCurParam->sValue);
                        sNextOutput += iLen;
                        iOutputSizeLeft -= iLen;
                    }
                    else if (pstStr != NULL)
                    {
                        fprintf(pstStr, "%s", pstCurParam->sValue);
                    }
                    else
                    {
                        printf("%s", pstCurParam->sValue);
                    }
                    break;
                }
                pstCurParam = pstCurParam->pstNext;
            }

            if (strncmp(HJ_HTML_PMARK_COMMENT, pcParamBegin, strlen(HJ_HTML_PMARK_COMMENT)) == 0)
            {
                iInCommentRange = 1;
                pcCommentParam = pcParamBegin;
            }
        }
        else if (strncmp(pcCommentParam, pcParamBegin, pcParamEnd - pcParamBegin) == 0)
        {
            iInCommentRange = 0;
        }

        pcOutputBegin = pcParamEnd + strlen(HJ_HTML_PMARK_END);
        if (strncmp(pcOutputBegin, HJ_HTML_PMARK_END_FILLER, strlen(HJ_HTML_PMARK_END_FILLER)) == 0)
        {
            pcOutputBegin = pcOutputBegin + strlen(HJ_HTML_PMARK_END_FILLER);
        }
    }

    return 0;
}

int HJ_Html_ParamInit(HJ_HTML_PARAM *pstParam, char *sErrMsg)
{
    pstParam->pstNext = NULL;
    return 0;
}

int HJ_Html_ParamAppendNode(HJ_HTML_PARAM *pstParam, char *sErrMsg, char *sName, char *sValue)
{
    HJ_HTML_PARAM *pstNewParam = (HJ_HTML_PARAM*)malloc(sizeof(HJ_HTML_PARAM));
    if (pstNewParam == NULL)
    {
        strcpy(sErrMsg, "Fail To Alloc Memory For Param Node");
        return -1;
    }

    pstNewParam->sName = HJ_Html_NewStr(sName);
    if (pstNewParam->sName == NULL)
    {
        strcpy(sErrMsg, "Fail To Alloc Memory For Param Node");
        free(pstNewParam);
        return -1;
    }

    pstNewParam->sValue = HJ_Html_NewStr(sValue);
    if (pstNewParam->sValue == NULL)
    {
        strcpy(sErrMsg, "Fail To Alloc Memory For Param Node");
        free(pstNewParam->sName);
        free(pstNewParam);
        return -1;
    }

    pstNewParam->pstNext = pstParam->pstNext;
    pstParam->pstNext = pstNewParam;

    return 0;
}

int HJ_Html_VParamAppend(HJ_HTML_PARAM *pstParam, char *sErrMsg, va_list ap)
{
    int iRetCode;
    char *sParam = va_arg(ap, char *);
    char *sVal;
    while (sParam != NULL)
    {
        sVal = va_arg(ap, char *);

        iRetCode = HJ_Html_ParamAppendNode(pstParam, sErrMsg, sParam, sVal);
        if (iRetCode != 0)
        {
            return iRetCode;
        }

        sParam = va_arg(ap, char *);
    }
    return 0;
}

int HJ_Html_ParamAppend(HJ_HTML_PARAM *pstParam, char *sErrMsg, ...)
{
    va_list ap;

    va_start(ap, sErrMsg);
    int iRetCode = HJ_Html_VParamAppend(pstParam, sErrMsg, ap);
    va_end(ap);

    return iRetCode;
}

void HJ_Html_ParamFreeNode(HJ_HTML_PARAM *pstParam)
{
    free(pstParam->sName);
    free(pstParam->sValue);
    free(pstParam);
}

void HJ_Html_ParamMark(HJ_HTML_PARAM *pstSubParam, HJ_HTML_PARAM *pstParam)
{
    pstSubParam->pstNext = pstParam->pstNext;
}

void HJ_Html_ParamTruncTo(HJ_HTML_PARAM *pstParam, HJ_HTML_PARAM *pstSubParam)
{
    HJ_HTML_PARAM *pstParamEnd = NULL;
    if (pstSubParam == NULL)
    {
        pstParamEnd = NULL;
    }
    else
    {
        pstParamEnd = pstSubParam->pstNext;
    }

    HJ_HTML_PARAM *pstParamNext = NULL;
    HJ_HTML_PARAM *pstParamCur = pstParam->pstNext;

    while ((pstParamCur != NULL) && (pstParamCur != pstParamEnd))
    {
        pstParamNext = pstParamCur->pstNext;
        HJ_Html_ParamFreeNode(pstParamCur);
        pstParamCur = pstParamNext;
    }

    pstParam->pstNext = pstParamCur;
}

void HJ_Html_ParamFree(HJ_HTML_PARAM *pstParam)
{
    HJ_Html_ParamTruncTo(pstParam, NULL);
}

int HJ_Html_VFillTemplateDef(char *sOutputBuffer, int iOutputBufferSize, FILE *pstStr
    , char *sErrMsg, char *sTemplate, va_list ap)
{
    HJ_HTML_PARAM stParam;
    int iRetCode = HJ_Html_ParamInit(&stParam, sErrMsg);
    if (iRetCode != 0)
    {
        return iRetCode;
    }

    iRetCode = HJ_Html_VParamAppend(&stParam, sErrMsg, ap);
    if (iRetCode != 0)
    {
        return iRetCode;
    }

    iRetCode = HJ_Html_FillTemplateDef(sOutputBuffer, iOutputBufferSize, pstStr, sErrMsg, sTemplate, &stParam);

    HJ_Html_ParamFree(&stParam);

    return iRetCode;

}

int HJ_Html_FillTemplateFile(FILE *pstStr, char *sErrMsg, char *sTemplate, ...)
{
    va_list ap;

    va_start(ap, sTemplate);
    int iRetCode = HJ_Html_VFillTemplateDef(NULL, 0, pstStr, sErrMsg, sTemplate, ap);
    va_end(ap);

    return iRetCode;
}

int HJ_Html_FillTemplateStr(char *sOutputBuffer, int iOutputBufferSize, char *sErrMsg, char *sTemplate, ...)
{
    va_list ap;

    va_start(ap, sTemplate);
    int iRetCode = HJ_Html_VFillTemplateDef(sOutputBuffer, iOutputBufferSize, NULL, sErrMsg, sTemplate, ap);
    va_end(ap);

    return iRetCode;
}

void HJ_Html_FillTemplate(char *sTemplate, ...)
{
    va_list ap;
    char sErrMsg[300];

    va_start(ap, sTemplate);
    int iRetCode = HJ_Html_VFillTemplateDef(NULL, 0, NULL, sErrMsg, sTemplate, ap);
    va_end(ap);

    if (iRetCode != 0)
    {
        printf("File Template Error: %s\n", sErrMsg);
    }
}

char *HJ_Html_TextEncode4(char *sDest, char *sSrc) //不处理回车符，处理双引号
{
    char *p = (char*)malloc(strlen(sSrc) + 1);
    strcpy(p,sSrc);

    char *pcDest = sDest;
    *pcDest = 0;
    char *pcSrc = p;

    while (1)
    {
        if (*pcSrc == 0)
        {
            break;
        }
        else if (*pcSrc == '<')
        {
            strcpy(pcDest, "&lt;");
        }
        else if (*pcSrc == '>')
        {
            strcpy(pcDest, "&gt;");
        }
        else if (*pcSrc == '&')
        {
            strcpy(pcDest, "&amp;");
        }
        else if (*pcSrc == '\"')
        {
            strcpy(pcDest, "&quot;");
        }
        else if (*pcSrc == ' ')
        {
            if ((*(pcSrc + 1) == ' ') && (*(pcSrc+9) != ' '))
            {
                strcpy(pcDest, "&nbsp;");
            }
            else
            {
                if ((pcSrc == p) || (*(pcSrc-1) == '\n'))
                {
                    strcpy(pcDest, "&nbsp;");
                }
                else
                {
                    strcpy(pcDest, " ");
                }
            }
        }
        else
        {
            *pcDest = *pcSrc;
            pcDest ++;
            *pcDest = 0;
        }
        pcDest = pcDest + strlen(pcDest);
        pcSrc ++;
    }

    free(p);
    return sDest;
}
