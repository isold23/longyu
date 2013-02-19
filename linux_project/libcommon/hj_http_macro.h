/*! @hj_http_macro.h
* *****************************************************************************
* @n</PRE>
* @n模块名       ：Http相关宏定义
* @n文件名       ：hj_http_macro.h
* @n相关文件     ：
* @n文件实现功能 ：Http相关宏定义
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
#ifndef __HJ_HTTP_MACRO_H__
#define __HJ_HTTP_MACRO_H__

const char HTTP_STATUS_OK[] = "HTTP/1.1 200 OK\r\n";
const char HTTP_STATUS_PARTIAL[] = "HTTP/1.1 206 Partial Content\r\n";
const char HTTP_STATUS_MOVED[] = "HTTP/1.1 301 Moved Permanently\r\n";
const char HTTP_STATUS_FOUND[] = "HTTP/1.1 302 Found\r\n";
const char HTTP_STATUS_NO_MODIFIED[] = "HTTP/1.1 304 Not Modified\r\n";
const char HTTP_STATUS_NOT_FOUND[] = "HTTP/1.1 404 Not Found\r\n";
const char HTTP_STATUS_LOW_VERSION[] = "HTTP/1.1 505 HTTP Version Not Supported \r\n";

const char HTTP_SERVER_VERSION[] = "Server: SZS_Web_Server\r\n";

const char HTTP_ENCODE_GZIP[] = "Content-Encoding: gzip\r\nVary: Accept-Encoding\r\n";

const char HTTP_NO_CACHE[] = "Pragma: no-cache\r\nCache-Control: no-cache\r\n";
const char HTTP_CACHE_CONTROL[] = "Cache-Control: max-age=%lu\r\nExpire: %s\r\nLast-Modified: %s\r\n";

const char HTTP_REDIRECT_LOCATION[] = "Location: %s\r\n";

const char HTTP_DATE[] = "Date: %s\r\n";

const char HTTP_ACCEPT_RANGES[] = "Accept-Ranges: bytes\r\n";
const char HTTP_CONTENT_RANGE[] = "Content-Range: bytes %d-%d/%d\r\n";
const char HTTP_CONTENT_LENGTH[] = "Content-Length: %d\r\n";

const char HTTP_SET_COOKIE_STR[] = "Set-Cookie: %s=%s; PATH=/; DOMAIN=%s\r\n";
const char HTTP_SET_COOKIE_UL[] = "Set-Cookie: %s=%lu; PATH=/; DOMAIN=%s\r\n";

const char HTTP_CONNECTION[] = "Connection: %s\r\n";
const char HTTP_CONNECTION_CLOSE[] = "Connection: close\r\n";
const char HTTP_CONNECTION_KEEPALIVE[] = "Keep-Alive: timeout=%d, max=%d\r\nConnection: keep-alive\r\n";

const char IF_MODIFYED_SINCE[] = "If-Modified-Since";

//////////////////////////////////////////////////////////////////////////

// ContentType索引
enum CONTENT_TYPE_INDEX
{
    HTML_CONTENT_TYPE = 0,
    CSS_CONTENT_TYPE  = 1,
    JSP_CONTENT_TYPE  = 2,
    GIF_CONTENT_TYPE  = 3,
    JPG_CONTENT_TYPE  = 4,
    ICO_CONTENT_TYPE  = 5,
    XML_CONTENT_TYPE  = 6
};
// 编码索引，对应于下面的HTTP_CONTENT_TYPE_ARR数组
enum ENCODE_TYPE_INDEX
{
    DEFAULT_ENCODE_TYPE = 0,
    UTF8_ENCODE_TYPE = 1,
    GB2312_ENCODE_TYPE = 2
};

typedef struct
{
    unsigned long ulMimeType;
    char szMimeType[4];
} MIME_TYPE_STRU;

const MIME_TYPE_STRU MIME_TYPE_ARR[] =
{
    {CSS_CONTENT_TYPE, "css"},
    {JSP_CONTENT_TYPE, "js"},
    {GIF_CONTENT_TYPE, "gif"},
    {JPG_CONTENT_TYPE, "jpg"},
    {ICO_CONTENT_TYPE, "ico"},
    {XML_CONTENT_TYPE, "xml"}
};
const char HTTP_CONTENT_TYPE_ARR[][7][64] =
{
    {
        "Content-Type: text/html\r\n",      // html类或者其它
        "Content-Type: text/css\r\n",                      // css文件
        "Content-Type: application/x-javascript\r\n",      // jsp文件
        "Content-Type: image/gif\r\n",                     // gif文件
        "Content-Type: image/jpeg\r\n",                    // jpg文件
        "Content-Type: image/x-icon\r\n",                  // ico文件
        "Content-Type: text/xml\r\n"        // xml文件
    },
    {
        "Content-Type: text/html; charset=utf-8\r\n",      // html类或者其它
        "Content-Type: text/css\r\n",                      // css文件
        "Content-Type: application/x-javascript; charset=utf-8\r\n",      // jsp文件
        "Content-Type: image/gif\r\n",                     // gif文件
        "Content-Type: image/jpeg\r\n",                    // jpg文件
        "Content-Type: image/x-icon\r\n",                  // ico文件
        "Content-Type: text/xml; charset=utf-8\r\n"        // xml文件
    },
    {
        "Content-Type: text/html; charset=gb2312\r\n",      // html类或者其它
        "Content-Type: text/css\r\n",                      // css文件
        "Content-Type: application/x-javascript; charset=gb2312\r\n",      // jsp文件
        "Content-Type: image/gif\r\n",                     // gif文件
        "Content-Type: image/jpeg\r\n",                    // jpg文件
        "Content-Type: image/x-icon\r\n",                  // ico文件
        "Content-Type: text/xml; charset=gb2312\r\n"        // xml文件
    }
};

#endif
