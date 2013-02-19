/*! @hj_http.cpp
* *****************************************************************************
* @n</PRE>
* @n模块名       ：Http解析相关库函数接口定义
* @n文件名       ：hj_http.cpp
* @n相关文件     ：hj_http.h
* @n文件实现功能 ：Http解析相关库函数接口定义
* @n作者         ：huangjun - 新浪技术(中国)
* @n版本         ：1.0.1
* @n-----------------------------------------------------------------------------
* @n备注：
* @n-----------------------------------------------------------------------------
* @n修改记录：
* @n日期        版本        修改人      修改内容
* @n20080731    1.0.0       Huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//

#include "hj_macro.h"
#include "hj_http.h"

/*!
* 功能：替换字符串pSrcMsg中的所有strOrgMsg为strReplaceMsg
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_ReplaceInfo(char *pSrcMsg, const string &strOrgMsg, const string &strReplaceMsg)
{
    assert(pSrcMsg);

    string strSrcMsg = pSrcMsg;
    int nOrgLen = strOrgMsg.length();
    int nReplaceLen = strReplaceMsg.length();
    int findarea = 0;
    while ((findarea = strSrcMsg.find(strOrgMsg, findarea)) != -1)
    {
        strSrcMsg.replace(findarea, nOrgLen, strReplaceMsg.c_str());
        findarea += nReplaceLen;
    }

    memcpy(pSrcMsg, strSrcMsg.c_str(), strSrcMsg.length());
    pSrcMsg[strSrcMsg.length()] = 0;

    return 0;
}

int HJ_ReplaceInfo(string &strSrcMsg, const string &strOrgMsg, const string &strReplaceMsg)
{
    int nOrgLen = strOrgMsg.length();
    int nReplaceLen = strReplaceMsg.length();
    int findarea = 0;
    while ((findarea = strSrcMsg.find(strOrgMsg, findarea)) != -1)
    {
        strSrcMsg.replace(findarea, nOrgLen, strReplaceMsg.c_str());
        findarea += nReplaceLen;
    }

    return 0;
}

/*!
* 功能：转换what开头的两个字节编码串为一个字节二进制
* @n作者：huangjun
* @n日期：2008-07-31
*/
char x2c(char *what)
{
    assert(what);

    unsigned char digit;

    digit = ((what[0] >= 'A')? ((what[0] & 0xdf) - 'A') + 10 : (what[0] - '0'));
    // digit *= 16;
    digit <<= 4;
    digit += ((what[1] >= 'A')? ((what[1] & 0xdf) - 'A') + 10 : (what[1] - '0'));
    return (digit);
}

/*!
* 功能：转换浏览器的编码字符串为二进制数组
* @n作者：huangjun
* @n日期：2008-07-31
*/
void HJ_unescape_url(char *url)
{
    assert(url);

    register int x, y;

    for (x=0, y=0; url[y]; ++x, ++y)
    {
        if ((url[x] = url[y]) == '%')
        {
            url[x] = x2c(&url[y + 1]);
            y += 2;
        }
        else if (url[x] == '+')
        {
            url[x] = ' ';
        }
    }
    url[x] = '\0';
}

/*!
* 功能：从HTTP报文中取出请求行部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetRequestLine(string &strRequestLine, const char *sPkg)
{
    assert(sPkg);

    strRequestLine = "";

    char *pLinePos = NULL;
    if ((pLinePos = strchr(sPkg, '\r')) || (pLinePos = strchr(sPkg, '\n')))
    {
        strRequestLine = string(sPkg, (pLinePos - sPkg));
        return 0;
    }
    else
    {
        return -1;
    }
}

/*!
* 功能：从HTTP报文中定位报头部分位置
* @n作者：huangjun
* @n日期：2008-07-31
*/
char* HJ_GetPkgHeadPos(const char *sPkg)
{
    assert(sPkg);

    char *pFindPos = NULL;
    // 跳过请求行
    if ((NULL != (pFindPos = strchr(sPkg, '\r'))) && (pFindPos[1] == '\n'))
    {
        pFindPos += 2;
    }
    else if (NULL != (pFindPos = strchr(sPkg, '\n')))
    {
        pFindPos += 1;
    }

    return pFindPos;
}

/*!
* 功能：从HTTP报文中取出报头部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPkgHead(string &strHead, const char *sPkg)
{
    assert(sPkg);

    strHead = "";

    char *pBeginPos = HJ_GetPkgHeadPos(sPkg);
    if (!pBeginPos)
    {
        return -1;
    }

    char *pDblLinePos = NULL;
    if ((pDblLinePos = strstr(pBeginPos, "\r\n\r\n")) || (pDblLinePos = strstr(pBeginPos, "\n\n")))
    {
        strHead = string(pBeginPos, (pDblLinePos - pBeginPos));
        return 0;
    }
    else
    {
        return -1;
    }
}

/*!
* 功能：从HTTP报文中定位报体部分位置
* @n作者：huangjun
* @n日期：2008-07-31
*/
char* HJ_GetPkgBodyPos(const char *sPkg)
{
    assert(sPkg);

    char *pDblLinePos = NULL;
    if (NULL != (pDblLinePos = strstr(sPkg, "\r\n\r\n")))
    {
        pDblLinePos += 4;
    }
    else if (NULL != (pDblLinePos = strstr(sPkg, "\n\n")))
    {
        pDblLinePos += 2;
    }

    return pDblLinePos;
}

/*!
* 功能：从HTTP报文中取出报体部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPkgBody(string &strBody, const char *sPkg)
{
    assert(sPkg);

    strBody = "";

    char *pDblLinePos = HJ_GetPkgBodyPos(sPkg);
    if (!pDblLinePos)
    {
        return -1;
    }

    strBody = string(pDblLinePos);
    return 0;
}

/*!
* 功能：从HTTP报头中查找名称为symbol字段的相应值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_FindHeadItem(string &strValue, const char *sHttpHead, const char *symbol)
{
    assert(sHttpHead && symbol);

    strValue = "";
    string strSymbol = string(symbol) + ":";

    char *pBeginPos = strstr(sHttpHead, strSymbol.c_str());
    if (!pBeginPos)
    {
        return -1;
    }
    pBeginPos += strSymbol.length();

    char *pEndPos = NULL;
    if ((pEndPos = strchr(pBeginPos, '\r')) || (pEndPos = strchr(pBeginPos, '\n')))
    {
        strValue = string(pBeginPos, (pEndPos - pBeginPos));
    }
    else
    {
        strValue = string(pBeginPos);
    }

    return 0;
}

/*!
* 功能：从某行字符串里查找名称为symbol字段的值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_FindItemValue(string &strValue, const char *sLineBuffer, const char *symbol)
{
    assert(sLineBuffer && symbol);

    strValue = "";
    string strSymbol = string(" ") + symbol + "=";

    char *pBeginPos = strstr(sLineBuffer, strSymbol.c_str());
    if (!pBeginPos)
    {
        return -1;
    }
    pBeginPos += strSymbol.length();

    char *pEndPos = NULL;
    if ((pEndPos = strchr(pBeginPos, ';')) || (pEndPos = strchr(pBeginPos, '\r'))
        || (pEndPos = strchr(pBeginPos, '\n')))
    {
        strValue = string(pBeginPos, (pEndPos - pBeginPos));
    }
    else
    {
        strValue = string(pBeginPos);
    }

    return 0;
}

/*!
* 功能：从源字符串msg中查找名称为symbol字段的相应值
* @n作者：huangjun
* @n日期：2008-07-31
*/
string HJ_FindSymbol(const string &msg, const char *symbol)
{
    assert(symbol);

    int loc;

    int ibegin = 0;
    char c;
    while (true)
    {
        ibegin =  msg.find(symbol, ibegin);
        if (ibegin == -1)
        {
            return "";
        }

        if (ibegin != 0)
        {
            c = msg[ibegin-1];
            if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z'))
                || ((c >= 'A') && (c <= 'Z')))
            {
                ibegin++;
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    loc = ibegin;
    if (loc == -1)
    {
        return "";
    }
    int head = msg.find("=", loc);
    if (head == -1)
    {
        return "";
    }

    int tail = msg.find_first_of("&", head);
    if (tail == -1)
    {
        tail = msg.find_first_of(" ", head);
    }

    string strTmp;
    if (tail != -1)
    {
        strTmp = string(msg.begin() + head + 1, msg.begin() + tail);
    }
    else
    {
        strTmp = string(msg.begin() + head + 1, msg.end());
    }

    if (!strTmp.empty())
    {
        char szTemp[8192];
        snprintf(szTemp, sizeof(szTemp), "%s", strTmp.c_str());
        HJ_unescape_url(szTemp);
        return string(szTemp);
    }

    return "";
}

/*!
* 功能：从html消息缓冲区中获取Content-Length字段的值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPageLength(const char *caTempBuffer)
{
    static const char szContentLength[] = "Content-Length: ";

    assert(caTempBuffer);

    // 移动开始指针到报头部分，不包括请求行
    char *pBeginPos = HJ_GetPkgHeadPos(caTempBuffer);
    if (!pBeginPos)
    {
        return -1;
    }

    if (((pBeginPos = strstr(pBeginPos, szContentLength)) == NULL))
    {
        // DEBUG_PRINT(LM_DEBUG, "NOT FOUND %s\n", szContentLength);
        return -1;
    }
    pBeginPos += (sizeof(szContentLength) - 1);

    char *pEndPos = NULL;
    if (((pEndPos = strchr(pBeginPos, '\n')) == NULL) 
        && ((pEndPos = strchr(pBeginPos, '\r')) == NULL))
    {
        // DEBUG_PRINT(LM_DEBUG, "NOT FOUND ENTER\n");
        return -1;
    }

    int iLength = pEndPos - pBeginPos;
    if ((iLength > 5) || (iLength < 1))
    {
        // DEBUG_PRINT(LM_DEBUG, "string length is illegal!\n");
        return -1;
    }

    char szBuffer[16];
    strncpy(szBuffer, pBeginPos, iLength);
    szBuffer[iLength] = '\0';

    // DEBUG_PRINT(LM_DEBUG, "length string is: %s\n", szBuffer);
    return atoi(szBuffer);
}
