#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "hj_html_head.h"

/* HTTP headers */
void html_header_encode(const char *other_encode)
{
    if (!other_encode)
    {
        printf("Content-type: text/html\r\n\r\n");
    }
    else
    {
        printf("Content-type: text/html; charset=%s\r\n\r\n"
            , other_encode);
    }
}

void html_no_cache()
{
    printf("Pragma: no-cache\r\nCache-Control: no-cache\r\n");
}

/* char *mime = valid mime type */
void mime_header(const char *mime)
{
    assert(mime);

    printf("Content-type: %s\r\n\r\n", mime);
}

void status_header(const char *status)
{
    assert(status);

    printf("HTTP/1.1 %s\r\n", status);
    printf("Server: ShenZhouStar_HTTP_SERVER\r\n");
}

void redirect_url_page(const char *location)
{
    assert(location);

    printf("Location: %s\r\n\r\n", location);
}

void pragma(const char *msg)
{
    assert(msg);

    printf("Pragma: %s\r\n", msg);
}

void set_cookie(const char *name, const char *value, const char *expires
    , const char *path, const char *domain, short secure)
{
    assert(name && value);

    printf("Set-Cookie: %s=%s;", name, value);

    if (expires != NULL)
    {
        printf(" EXPIRES=%s;", expires);
    }

    if (path != NULL)
    {
        printf(" PATH=%s;", path);
    }

    if (domain != NULL)
    {
        printf(" DOMAIN=%s;", domain);
    }

    if (secure)
    {
        printf(" SECURE");
    }

    printf("\r\n");
}
