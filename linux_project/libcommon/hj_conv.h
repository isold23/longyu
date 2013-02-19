#ifndef __CODE_CONVERT_H__
#define __CODE_CONVERT_H__

#include <stdint.h>
#include <iconv.h>

class CHJCodeConverter
{
public:
    CHJCodeConverter(char *pFrom_code_name, char *pTo_code_name);
    virtual ~CHJCodeConverter();

    int Convert(char **ppTarget, size_t *pTarget_len, char **ppSrc, size_t *pSrc_len);

private:
    CHJCodeConverter() : m_conv_fd(reinterpret_cast<iconv_t>(static_cast<intptr_t>(-1))) {};

    iconv_t m_conv_fd;
};

#endif
