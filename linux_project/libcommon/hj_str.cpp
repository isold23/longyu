/*! @hj_str.cpp
*******************************************************************************
</PRE>
模块名       ：字符串处理相关库函数定义
文件名       ：hj_str.cpp
相关文件     ：hj_str.h
文件实现功能 ：字符串处理相关库函数定义
作者         ：huangjun - 神州星国际(http://www.shenzhoustar.com)
版本         ：1.0.1
-------------------------------------------------------------------------------
备注：
-------------------------------------------------------------------------------
修改记录：
日期        版本        修改人      修改内容
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/

#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <new>

#include "hj_macro.h"
#include "hj_str.h"

using namespace std;

HJ_STR_STRING_LIST* HJ_Str_StringListCreate(void)
{
    // HJ_STR_STRING_LIST *pstStringList = (HJ_STR_STRING_LIST*)malloc(sizeof(HJ_STR_STRING_LIST));
    HJ_STR_STRING_LIST *pstStringList = new HJ_STR_STRING_LIST;
    if (pstStringList)
    {
        bzero(pstStringList, sizeof(HJ_STR_STRING_LIST));
    }
    // memset(pstStringList, 0, sizeof(HJ_STR_STRING_LIST));

    return pstStringList;
}

int HJ_Str_StringListAdd(HJ_STR_STRING_LIST *pstStringList, char *pszItem)
{
    if ((pstStringList == NULL) || (pszItem == NULL))
    {
        return HJ_STR_STRING_LIST_ERROR_INVALID_POINTER;
    }

    // HJ_STR_STRING_LIST_ITEM *pstStringListItem = (HJ_STR_STRING_LIST_ITEM*)malloc(sizeof(HJ_STR_STRING_LIST_ITEM));
    HJ_STR_STRING_LIST_ITEM *pstStringListItem = new HJ_STR_STRING_LIST_ITEM;
    if (pstStringListItem == NULL)
    {
        return HJ_STR_STRING_LIST_ERROR_FAIL_TO_ALLOC_MEM;
    }

    // pstStringListItem->pszItem = (char *)malloc(strlen(pszItem)+1);
    pstStringListItem->pszItem = new char[strlen(pszItem) + 1];
    if (pstStringListItem->pszItem == NULL)
    {
        // free(pstStringListItem);
        delete pstStringListItem;
        return HJ_STR_STRING_LIST_ERROR_FAIL_TO_ALLOC_MEM;
    }
    strcpy(pstStringListItem->pszItem, pszItem);

    if (pstStringList->pstItem == NULL)
    {
        pstStringList->pstItem = pstStringListItem;
    }

    if (pstStringList->pstItemTail != NULL)
    {
        pstStringList->pstItemTail->pstNext = pstStringListItem;
    }
    pstStringList->pstItemTail = pstStringListItem;
    pstStringListItem->pstNext = NULL;

    return 0;
}

void HJ_Str_StringListFree(HJ_STR_STRING_LIST *pstStringList)
{

    if (pstStringList == NULL)
    {
        return;
    }

    HJ_STR_STRING_LIST_ITEM *pstStringListItem = pstStringList->pstItem;
    while (pstStringListItem != NULL)
    {
        pstStringList->pstItem = pstStringList->pstItem->pstNext;
        // free(pstStringListItem->pszItem);
        delete []pstStringListItem->pszItem;
        // free(pstStringListItem);
        delete pstStringListItem;
        pstStringListItem = pstStringList->pstItem;
    }
    // free(pstStringList);
    delete pstStringList;
    return;
}

char* HJ_Str_StringListGetFirst(HJ_STR_STRING_LIST *pstStringList)
{
    if (pstStringList == NULL)
    {
        return NULL;
    }

    pstStringList->pstItemCur = pstStringList->pstItem;
    if (pstStringList->pstItemCur == NULL)
    {
        return NULL;
    }

    return pstStringList->pstItemCur->pszItem;
}

char* HJ_Str_StringListGetNext(HJ_STR_STRING_LIST *pstStringList)
{
    if ((pstStringList == NULL) || (pstStringList->pstItemCur == NULL))
    {
        return NULL;
    }

    pstStringList->pstItemCur = pstStringList->pstItemCur->pstNext;
    if (pstStringList->pstItemCur == NULL)
    {
        return NULL;
    }

    return pstStringList->pstItemCur->pszItem;
}

////////////////////////////////////////////////////////////////////

char *HJ_Str_Trim(char *s)
{
    // if (strcmp(s, "") == 0) 
    if (!s || (s[0] == '\0'))
    {
        return s;
    }

    char *pb = s;
    while (((*pb == ' ') || (*pb == '\t') || (*pb == '\n') || (*pb == '\r')) && (*pb != 0))
    {
        pb++;
    }

    char *pe = s;
    while (*pe != 0)
    {
        pe ++;
    }
    pe--;
    while ((pe >= s) && ((*pe == ' ') || (*pe == '\t') || (*pe == '\n') || (*pe == '\r')))
    {
        pe--;
    }

    char *ps = pb;
    char *pd = s;
    while (ps <= pe)
    {
        *pd = *ps;
        ps ++;
        pd ++;
    }
    *pd = 0;

    return s;
}

char* HJ_Str_StrUppercase(char *s)
{
    char *p = s;
    while (*p != 0)
    {
        *p = toupper(*p);
        p++;
    }

    return s;
}

char* HJ_Str_StrLowercase(char *s)
{
    char *p = s;
    while (*p != 0)
    {
        *p = tolower(*p);
        p++;
    }

    return s;
}

int HJ_Str_StrCmp(char *s1, char *s2)
{
    if (s1 == NULL)
    {
        if (s2 == NULL)
        {
            return 0;
        }

        if (*s2 == 0)
        {
            return 0;
        }
        return -1;
    }

    if (s2 == NULL)
    {
        if (*s1 == 0)
        {
            return 0;
        }
        return 1;
    }


    char *p1 = s1;
    char *p2 = s2;

    while (1)
    {
        if (*p1 > *p2)
        {
            return 1;
        }

        if (*p1 < *p2)
        {
            return -1;
        }

        if (*p1 == 0)
        {
            return 0;
        }

        p1++;
        p2++;
    }
}

int HJ_Str_StrNCCmp(char *s1, char *s2)
{
    if (s1 == NULL)
    {
        if (s2 == NULL)
        {
            return 0;
        }
        if (*s2 == 0)
        {
            return 0;
        }
        return -1;
    }

    if (s2 == NULL)
    {
        if (*s1 == 0)
        {
            return 0;
        }
        return 1;
    }

    char *p1 = s1;
    char *p2 = s2;
    char c1, c2;

    while (1)
    {
        c1 = toupper(*p1);
        c2 = toupper(*p2);

        if (c1 > c2)
        {
            return 1;
        }

        if (c1 < c2)
        {
            return -1;
        }

        if (c1 == 0)
        {
            return 0;
        }

        p1++;
        p2++;
    }
}

char* HJ_Str_StrReplaceChar(char *pStrSrc, char cOld, char cNew)
{
    char *pChar = pStrSrc;
    while (*pChar)
    {
        if (*pChar == cOld)
        {
            *pChar = cNew;
        }
        pChar++;
    }
    return pStrSrc;
}

char* HJ_Str_StrCat(char *s, const char *pszFormat, ...)
{
    va_list ap;

    va_start(ap, pszFormat);
    (void) vsprintf(s+strlen(s), pszFormat, ap);
    va_end(ap);
    return (s);
}


char* HJ_Str_Strcpy(char *pszDest, char *pszSrc)
{
    if (pszSrc == NULL)
    {
        *pszDest = 0;
        return pszDest;
    }
    return strcpy(pszDest, pszSrc);
}

char* HJ_Str_Strncpy(char *pszDest, char *pszSrc, int iMaxChar)
{
    if (pszSrc == NULL)
    {
        *pszDest = 0;
        return pszDest;
    }
    return strncpy(pszDest, pszSrc, iMaxChar);
}

char* HJ_Str_Quote(char *pszDest, char *pszSrc)
{
    register int i = 0, j = 0;

    while (pszSrc[i])
    {
        switch ((unsigned char)pszSrc[i])
        {
            case '\n' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'n';
                break;
            case '\t' :
                pszDest[j++] = '\\';
                pszDest[j++] = 't';
                break;
            case '\r' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'r';
                break;
            case '\b' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'b';
                break;
            case '\'' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\'';
                break;
            case '\"' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\"';
                break;
            case '\\' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\\';
                break;
            default:
                pszDest[j++] = pszSrc[i];
                break;
        }
        i++;
    }
    pszDest[j] = 0;
    return pszDest;
}

char* HJ_Str_QuoteWild(char *pszDest, char *pszSrc)
{
    register int i = 0, j = 0;

    while (pszSrc[i])
    {
        switch ((unsigned char)pszSrc[i])
        {
            case '\n' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'n';
                break;
            case '\t' :
                pszDest[j++] = '\\';
                pszDest[j++] = 't';
                break;
            case '\r' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'r';
                break;
            case '\b' :
                pszDest[j++] = '\\';
                pszDest[j++] = 'b';
                break;
            case '\'' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\'';
                break;
            case '\"' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\"';
                break;
            case '\\' :
                pszDest[j++] = '\\';
                pszDest[j++] = '\\';
                break;
            case '%' :
                pszDest[j++] = '\\';
                pszDest[j++] = '%';
                break;
            case '_' :
                pszDest[j++] = '\\';
                pszDest[j++] = '_';
                break;
            default :
                pszDest[j++] = pszSrc[i];
                break;
        }
        i++;
    }
    pszDest[j] = 0;
    return pszDest;
}

char* HJ_Str_CutHZString(char *pszSrc)
{
    unsigned char *pcSrc = (unsigned char*)pszSrc;
    int iLength = strlen(pszSrc);
    int i = 1;

    while (*pcSrc)
    {
        if ((*pcSrc > 127) && (i<iLength))
        {
            pcSrc += 2;
            i += 2;
        }
        else if (*pcSrc <= 127)
        {
            pcSrc++;
            i++;
        }
        else
        {
            *pcSrc = 0;
        }
    }
    return pszSrc;
}

/**********************************************************************************
Function:    :从字符流中取得一行
input:        buf
output:       pszLine
return        sbuf
lastmodify:   1999.11.17
written by    dy
**********************************************************************************/
char *GetOneLineFromBuf(char *pszLine, char *pszBuf, int iMaxCount)
{
    int i = 0;

    while ((pszBuf[i] != '\n') && (pszBuf[i] != '\0') && (i < iMaxCount))
    {
        pszLine[i] = pszBuf[i];
        i++;
    }

    pszLine[i] = '\0';

    if (pszBuf[i] == '\n')
    {
        pszBuf = (char*)(pszBuf + i + 1);
    }
    else if (pszBuf[i] == '\0')
    {
        pszBuf[0] = '\0';
    }

    return pszBuf;
}

/**********************************************************************************
Function:    去掉字符串中的空格
input:       buf
output:      buf
lastmodify:  1999.11.17
written by   dy
**********************************************************************************/
char* trim(char *s)
{
    register int i = strlen(s);
    while ((i > 0) && ((s[i - 1] == ' ') || (s[i - 1] == '\t') || (s[i - 1] == '\n')))
    {
        i--;
    }
    s[i] = 0;

    i = 0;
    while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n'))
    {
        i++;
    }

    register int j;
    if (i != 0)
    {
        j = 0;
        while (s[i] != 0)
        {
            s[j] = s[i];
            j++;
            i++;
        }
        s[j] = 0;
    }
    return s;
}

/**********************************************************************************
Function:    :从一行中取得以空格分开的一个单词, 
input:        pszLine,pszWord
output:       pszWord
return        pszLine; 
lastmodify:   1999.11.17
written by    dy
**********************************************************************************/
char* GetOneWordFromLine(char *pszWord, char *pszLine, int iMaxCount)
{
    pszLine = trim(pszLine);

    int i = 0;
    while ((pszLine[i] != ' ') && (pszLine[i] != '\0') && (i < iMaxCount))
    {
        pszWord[i] = pszLine[i];
        i++;
    }

    pszWord[i] = '\0';
    if (pszLine[i] == ' ')
    {
        pszLine = (char*)(pszLine + i);
    }
    else if (pszLine[i] == '\0')
    {
        pszLine[0] = '\0';
    }

    return pszLine;
}

char* HJ_Str_Short(const char *pszSrc, char *pszDest, int len)
{
    int start = 0, clen = 0, i = 0, slen = strlen(pszSrc);
    unsigned char co;
    for(i = 0; i < slen; clen++)
    {
        co = pszSrc[i];
        if (co> 0xA0)
        {
            if (clen >= (start + len - 1))
            {
                break;
            }

            if (clen >= start)
            {
                pszDest[i] = pszSrc[i];
                i++;
                clen++;
                pszDest[i] = pszSrc[i];
            }
        }
        else
        {
            if (clen >= start + len)
            {
                break;
            }

            if (clen >= start)
            {
                pszDest[i] = pszSrc[i];
            }
        }
        i++;
    }
    pszDest[i] = 0;

    return pszDest;
}
