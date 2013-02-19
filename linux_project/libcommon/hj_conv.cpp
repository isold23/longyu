#include <assert.h>
#include <cstring>

#include "hj_conv.h"

CHJCodeConverter::CHJCodeConverter(char *pFrom_code_name, char *pTo_code_name)
    : m_conv_fd(reinterpret_cast<iconv_t>(static_cast<intptr_t>(-1)))
{
    m_conv_fd = iconv_open(pTo_code_name, pFrom_code_name);
}

CHJCodeConverter::~CHJCodeConverter()
{
    if (m_conv_fd != reinterpret_cast<iconv_t>(static_cast<intptr_t>(-1)))
    {
        iconv_close(m_conv_fd);
        m_conv_fd = reinterpret_cast<iconv_t>(static_cast<intptr_t>(-1));
    }
}

int CHJCodeConverter::Convert(char **ppTarget, size_t *pTarget_len, char **ppSrc, size_t *pSrc_len)
{
    assert(ppTarget && *ppTarget && pTarget_len && ppSrc && *ppSrc && pSrc_len);

    size_t uTargetMaxLen = *pTarget_len;

    if (m_conv_fd !=  reinterpret_cast<iconv_t>(static_cast<intptr_t>(-1)))
    {
        int nResult = static_cast<int>(iconv(m_conv_fd, ppSrc, pSrc_len, ppTarget, pTarget_len));
        if (nResult > -1)
        {
            *pTarget_len = uTargetMaxLen - *pTarget_len;
            return nResult;
        }
    }

    if (*pTarget_len > *pSrc_len)
    {
        *pTarget_len = *pSrc_len;
    }
    memcpy(*ppTarget, *ppSrc, *pTarget_len);
    return static_cast<int>(*pTarget_len);
}
