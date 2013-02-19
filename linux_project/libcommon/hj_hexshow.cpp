#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "hj_hexshow.h"

using namespace std;

void HJ_hex_show(const char *acBuff, int iLen, int isHtml)
{
    const unsigned char *sStr = (const unsigned char*)acBuff;

    int i = 0;
    int iPos = 0, jPos = 0;
    char chTmp = '\0';
    char acASCII[256] = "";
    char acHexBuf[256] = "";

    for (register int iCount = 0; iCount < iLen; iCount++)
    {
        i = iCount % 16;

        if ((sStr[iCount] >= ' ') && (sStr[iCount] <= '~')) // || ((unsigned char)sStr[iCount] > 128 && (unsigned char)sStr[iCount] < 255)) 
        {
            chTmp = sStr[iCount];
        }
        else
        {
            chTmp = '*';
        }

        if (i == 8)
        {
            jPos += sprintf(acHexBuf+jPos, " -- ");
            iPos += sprintf(acASCII+iPos, "  -- ");
        }

        if (i == 0)
        {
            /*
            acASCII[iPos] = '\0' ;
            acHexBuf[jPos] = '\0' ;
            */

            if (iCount != 0)
            {
                printf("%s", acHexBuf);
                printf("  |   %s", acASCII);
            }

            if (isHtml)
            {
                if (iCount != 0)
                {
                    printf("<br />");
                }
                printf("line: %06x:", iCount / 16);
            }
            else
            {
                if (iCount != 0)
                {
                    putchar ('\n');
                }
                printf("line: %06x:", iCount / 16);
            }

            iPos = 0;
            jPos = 0;
        }

        jPos += sprintf(acHexBuf + jPos, " %.2x ", (unsigned char)sStr[iCount]);
        iPos += sprintf(acASCII + iPos, " %c", chTmp);
    }

    if (jPos != 0)
    {
        memset(acHexBuf + jPos, ' ', 68 - jPos);
        acHexBuf[68] = '\0';
        printf("%s", acHexBuf);
        printf("  |   %s", acASCII);
    }

    if (isHtml)
    {
        printf ("<br />");
    }
    else
    {
        printf ("\n");
    }
}
