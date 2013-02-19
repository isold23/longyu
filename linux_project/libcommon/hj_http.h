/*! @sfl_http.h
* *****************************************************************************
* @n</PRE>
* @n模块名       ：Http解析相关库函数接口申明
* @n文件名       ：sfl_http.h
* @n相关文件     ：sfl_http.cpp
* @n文件实现功能 ：Http解析相关库函数接口申明
* @n作者         ：huangjun - 新浪技术(中国)
* @n版本         ：1.0.1
* @n-----------------------------------------------------------------------------
* @n备注：
* @n-----------------------------------------------------------------------------
* @n修改记录：
* @n日期        版本        修改人      修改内容
* @n20080713    1.0.0       huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#ifndef __HJ_HTTP_H__
#define __HJ_HTTP_H__

#include <string>

using namespace std;

/*!
* 功能：替换字符串pSrcMsg中的所有strOrgMsg为strReplaceMsg
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_ReplaceInfo(char *pSrcMsg, const string &strOrgMsg, const string &strReplaceMsg);
int HJ_ReplaceInfo(string &strSrcMsg, const string &strOrgMsg, const string &strReplaceMsg);

/*!
* 功能：转换浏览器的编码字符串为二进制数组
* @n作者：huangjun
* @n日期：2008-07-31
*/
void HJ_unescape_url(char *url);

/*!
* 功能：从HTTP报文中定位报头部分位置
* @n作者：huangjun
* @n日期：2008-07-31
*/
char* HJ_GetPkgHeadPos(const char *sPkg);

/*!
* 功能：从HTTP报文中取出报头部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPkgHead(string &strHead, const char *sPkg);

/*!
* 功能：从HTTP报文中取出请求行部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetRequestLine(string &strRequestLine, const char *sPkg);

/*!
* 功能：从HTTP报文中定位报体部分位置
* @n作者：huangjun
* @n日期：2008-07-31
*/
char* HJ_GetPkgBodyPos(const char *sPkg);

/*!
* 功能：从HTTP报文中取出报体部分
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPkgBody(string &strBody, const char *sPkg);

/*!
* 功能：从HTTP报头中查找名称为symbol字段的相应值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_FindHeadItem(string &strValue, const char *sHttpHead, const char *symbol);

/*!
* 功能：从某行字符串里查找名称为symbol字段的值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_FindItemValue(string &strValue, const char *sLineBuffer, const char *symbol);

/*!
* 功能：从源字符串msg中查找名称为symbol字段的相应值
* @n作者：huangjun
* @n日期：2008-07-31
*/
string HJ_FindSymbol(const string &msg, const char *symbol);

/*!
* 功能：从html消息缓冲区中获取Content-Length字段的值
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_GetPageLength(const char *caTempBuffer);

#endif
