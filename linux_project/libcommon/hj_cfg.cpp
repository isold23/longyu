/*! @hj_cfg.cpp
*******************************************************************************
</PRE>
模块名       ：读配置文件相关库函数定义
文件名       ：hj_cfg.cpp
相关文件     ：hj_cfg.h
文件实现功能 ：读配置文件相关库函数定义
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

#include "hj_macro.h"
#include "hj_str.h"
#include "hj_cfg.h"

#define MAX_CONFIG_LINE_LEN 255

static void InitDefault(va_list ap)
{
    char *pszParam = va_arg(ap, char*);

    int iType;
    long lSize;
    int *piVal = NULL, iDefault;
    char *pszVal = NULL, *pszDefault = NULL;
    long *plVal = NULL, lDefault;
    double *pdVal = NULL, dDefault;

    while (pszParam != NULL)
    {
        iType = va_arg(ap, int);
        switch (iType)
        {
        case CFG_STRING :
            pszVal = va_arg(ap, char*);
            pszDefault = va_arg(ap, char*);
            lSize = va_arg(ap, long);
            strncpy(pszVal, pszDefault, (int)(lSize - 1));
            pszVal[lSize - 1] = 0;
            break;
        case CFG_LONG :
            plVal = va_arg(ap, long*);
            lDefault = va_arg(ap, long);
            *plVal = lDefault;
            break;
        case CFG_INT :
            piVal = va_arg(ap, int*);
            iDefault = va_arg(ap, int);
            *piVal = iDefault;
            break;
        case CFG_DOUBLE :
            pdVal = va_arg(ap, double*);
            dDefault = va_arg(ap, double);
            *pdVal = dDefault;
            break;
        }
        pszParam = va_arg(ap, char*);
    }
}

static void SetVal(va_list ap, char *pszP, char *pszV)
{
    char *pszParam = va_arg(ap, char*);

    int iType=0, *piVal=NULL, iDefault = 0;
    char *pszVal = NULL, *pszDefault = NULL;
    long lSize=0;
    long *plVal = NULL, lDefault;
    double *pdVal = NULL, dDefault;

    while (pszParam != NULL)
    {
        iType = va_arg(ap, int);
        switch (iType)
        {
        case CFG_STRING :
            pszVal = va_arg(ap, char*);
            pszDefault = va_arg(ap, char*);
            lSize = va_arg(ap, long);
            break;
        case CFG_LONG :
            plVal = va_arg(ap, long*);
            lDefault = va_arg(ap, long);
            if (strcmp(pszP, pszParam) == 0)
            {
                *plVal = atol(pszV);
            }
            break;
        case CFG_INT :
            piVal = va_arg(ap, int*);
            iDefault = va_arg(ap, int);
            if (strcmp(pszP, pszParam) == 0)
            {
                *piVal = iDefault;
            }
            break;
        case CFG_DOUBLE :
            pdVal = va_arg(ap, double *);
            dDefault = va_arg(ap, double);
            *pdVal = dDefault;
            break;
        }

        if (strcmp(pszP, pszParam) == 0)
        {
            switch (iType)
            {
            case CFG_STRING :
                strncpy(pszVal, pszV, (int)(lSize - 1));
                pszVal[lSize - 1] = 0;
                break;
            case CFG_LONG:
                *plVal = atol(pszV);
                break;
            case CFG_INT :
                *piVal = atoi(pszV);
                break;
            case CFG_DOUBLE :
                *pdVal = atof(pszV);
                break;
            }
            return;
        }

        pszParam = va_arg(ap, char*);
    }
}

static int GetParamVal(char *pszLine, char *pszParam, char *pszVal)
{
    char *p = pszLine;
    while (*p != '\0')
    {
        if ((*p != ' ') && (*p != '\t') && (*p != '\n'))
        {
            break;
        }
        p++;
    }

    char *pszP = pszParam;
    while (*p != '\0')
    {
        if ((*p == ' ') || (*p == '\t') || (*p == '\n'))
        {
            break;
        }

        *pszP = *p;
        p++;
        pszP++;
    }
    *pszP = '\0';

    strcpy(pszVal, p);
    HJ_Str_Trim(pszVal);

    if (pszParam[0] == '#')
    {
        return 1;
    }

    return 0;
}

void HJ_Cfg_GetConfig(const char *pszConfigFilePath, ...)
{
    va_list ap;

    va_start(ap, pszConfigFilePath);
    InitDefault(ap);
    va_end(ap);

    FILE *pstFile = fopen(pszConfigFilePath, "r");
    if (pstFile == NULL)
    {
        return;
    }

    char pszLine[MAX_CONFIG_LINE_LEN+1], pszParam[MAX_CONFIG_LINE_LEN+1], pszVal[MAX_CONFIG_LINE_LEN+1];
    while (1)
    {
        strcpy(pszLine, "");

        fgets(pszLine, sizeof(pszLine), pstFile);
        if (pszLine[0] != '\0')
        {
            if (GetParamVal(pszLine, pszParam, pszVal) == 0)
            {
                va_start(ap, pszConfigFilePath);
                SetVal(ap, pszParam, pszVal);
                va_end(ap);
            }
        }

        if (feof(pstFile))
        {
            break;
        }
    }
    fclose(pstFile);
}
