/*! @hj_string.cpp
*******************************************************************************
</PRE>
模块名       ：字符串处理、生成以及转换相关库函数定义
文件名       ：hj_string.cpp
相关文件     ：hj_string.h
文件实现功能 ：字符串处理、生成以及转换相关库函数定义
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

#include "hj_string.h"

/****************************************************************************
* 功能：把16进制文本转换成二进制,长度为原来的1/2
* 作者：huangjun
* 日期：2008-07-31
* 注意：在改进此算法时要尤其重视算法的性能
***************************************************************************/
int HJ_Hex_Str2Bin(BYTE *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn)
{
    assert(pszOut && pszIn);

    nOutLen = 0;

    int  nInLen = strlen(pszIn);
    if ((nInLen & 0X01 != 0)
        || (nInLen > (nMaxOutLen << 1)))
    {
        // DEBUG_PRINT(LM_ERROR, "传入的指针参数为空或输入长度不合法或缓冲区过小！\n");
        return -1;
    }

    char szChar[5];
    bzero(pszOut, nMaxOutLen);

    nOutLen = nInLen >> 1;
    for (register int i = 0; i < nOutLen; i++)
    {
        szChar[0] = '\0';
        strncat(szChar, (pszIn + int(i << 1)), 2);
        sscanf(szChar, "%x", (unsigned int*)(pszOut + i));
    }

    return 0;
}

/****************************************************************************
* 功能：把二进制值转换成16进制字符串，转换后的字符串长度为输入长度的两倍
* 作者：huangjun
* 日期：2008-07-31
* 注意：在改进此算法时要尤其重视算法的性能
***************************************************************************/
int HJ_Hex_Bin2Str(char *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn, const int nInLen)
{
    assert(pszOut && pszIn);

    nOutLen = 0;

    bzero(pszOut, nMaxOutLen);

    if ((nInLen << 1) > (nMaxOutLen - 1))
    {
        // DEBUG_PRINT(LM_ERROR, "存放转换后的缓冲区太小！\n");
        return -1;
    }

    for (register int i = 0; i < nInLen; i++)
    {
        sprintf((pszOut + int(i << 1)), "%02x", *((unsigned char *)(pszIn + i)));
    }
    nOutLen = nInLen << 1;

    return 0;
}

/****************************************************************************
* 功能：把字符串值转换成4个字节的Hash值
* 作者：huangjun
* 日期：2008-07-31
***************************************************************************/
unsigned long HJ_Str2Hash(const char *pszIn)
{
    assert(pszIn);

    unsigned long ulHashValue = 0, ulTemp;
    int nLen = strlen(pszIn);
    char *pszPos = const_cast<char*>(pszIn);
    const char *pszEnd = pszIn + nLen;

    while (pszPos < pszEnd)
    {
        ulHashValue = (ulHashValue << 4) + tolower(*pszPos++);
        if ((ulTemp = (ulHashValue & 0xF0000000)) != 0)
        {
            ulHashValue ^= (ulTemp >> 24);
            ulHashValue ^= ulTemp;
        }
    }
    return ulHashValue;
}

/****************************************************************************
* 功能：获取当前日期的精简格式字符串
* 作者：huangjun
* 日期：2008-07-31
* 输出：例如：20060325
* 备注：解决了TLib库中的那个同等函数不可重入的问题
***************************************************************************/
char* HJ_GetCurDateShortStr(char *pszDest, const int &nMaxOutSize)
{
    assert(pszDest);

    time_t tm_now = time(NULL);
    struct tm strc_now = *localtime(&tm_now);

    if (strc_now.tm_year > 50)
    {
        snprintf(pszDest, nMaxOutSize, "%04d%02d%02d"
            , strc_now.tm_year + 1900, strc_now.tm_mon + 1, strc_now.tm_mday);
    }
    else
    {
        snprintf(pszDest, nMaxOutSize, "%04d%02d%02d"
            , strc_now.tm_year + 2000, strc_now.tm_mon + 1, strc_now.tm_mday);
    }

    return pszDest;
}

/****************************************************************************
* 功能：获取当前日期时间格式字符串
* 作者：huangjun
* 日期：2008-07-31
* 输出：例如：2008-07-31 00:00:00
***************************************************************************/
char* HJ_GetCurDateTimeStr(char *pszDest, const int &nMaxOutSize)
{
    assert(pszDest);

    time_t tm_now = time(NULL);
    struct tm strc_now = *localtime(&tm_now);

    if (strc_now.tm_year > 50)
    {
        snprintf(pszDest, nMaxOutSize, "%04d-%02d-%02d %02d:%02d:%02d"
            , strc_now.tm_year + 1900, strc_now.tm_mon + 1, strc_now.tm_mday
            , strc_now.tm_hour, strc_now.tm_min, strc_now.tm_sec);
    }
    else
    {
        snprintf(pszDest, nMaxOutSize, "%04d-%02d-%02d %02d:%02d:%02d"
            , strc_now.tm_year + 2000, strc_now.tm_mon + 1, strc_now.tm_mday
            , strc_now.tm_hour, strc_now.tm_min, strc_now.tm_sec);
    }

    return pszDest;
}

/****************************************************************************
* 功能：格式化字符串的连接
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
char* HJ_Format_StrCat(char *pszDest, size_t uDestMaxLen
    , const char *szFormat, ...)
{
    assert(pszDest && szFormat);

    va_list ap;

    va_start(ap, szFormat);
    size_t uDestLen = strlen(pszDest);
    assert(uDestLen <= uDestMaxLen);
    (void)vsnprintf(pszDest + uDestLen, (uDestMaxLen - uDestLen), szFormat, ap);
    va_end(ap);

    return pszDest;
}
