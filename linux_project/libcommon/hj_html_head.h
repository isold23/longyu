#ifndef __HJ_HTML_HEAD_H__
#define __HJ_HTML_HEAD_H__

void html_header_encode(const char *other_encode);
void html_no_cache();
void mime_header(const char *mime);
void status_header(const char *status);
void redirect_url_page(const char *location);
void pragma(const char *msg);
void set_cookie(const char *name, const char *value, const char *expires
    , const char *path, const char *domain, short secure);

#endif
