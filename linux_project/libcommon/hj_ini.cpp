/*! @hj_ini.cpp
*******************************************************************************
</PRE>
模块名       ：读取ini文件相关功能定义
文件名       ：hj_ini.cpp
相关文件     ：hj_ini.h
文件实现功能 ：读取ini文件相关功能定义
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

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>

#include "hj_macro.h"
#include "hj_str.h"
#include "hj_ini.h"

using namespace std;

#define HJ_INI_MAX_LINE_LENGTH    1024

#define HJ_INI_ANALYZE_SECTION    1
#define HJ_INI_ANALYZE_VALUE      2
#define HJ_INI_ANALYZE_COMMENT    3
#define HJ_INI_ANALYZE_UNKNOWN    4

typedef struct _HJ_INI_VALUE
{
    char *sIdent;
    char *sValue;
    int iRemoved;
    int iWritten;
    struct _HJ_INI_VALUE *pstNext;
} HJ_INI_VALUE;

typedef struct _HJ_INI_SECTION
{
    char *sSection;
    HJ_INI_VALUE *pstValue;
    HJ_INI_VALUE *pstValueTail;
    int iRemoved;
    int iWritten;
    struct _HJ_INI_SECTION *pstNext;
} HJ_INI_SECTION;

typedef struct _HJ_INI
{
    HJ_INI_SECTION *pstSection;
    HJ_INI_SECTION *pstSectionTail;
} HJ_INI, *P_HJ_INI;

static P_HJ_INI apstIni[HJ_INI_MAX_OPENED_NUM];

/*****************************************************************/

static int HJ_Ini_CheckInitiated(void)
{
    static int iInitiated = 0;

    if (iInitiated == 0)
    {
        for (int i = 0; i < HJ_INI_MAX_OPENED_NUM; i++)
        {
            apstIni[i] = NULL;
        }

        iInitiated = 1;
    }

    return 0;
}

static int HJ_Ini_GetHandle(void)
{
    for (int i = 0; i < HJ_INI_MAX_OPENED_NUM; i++)
    {
        if (apstIni[i] == NULL)
        {
            // apstIni[i] = (P_HJ_INI)malloc(sizeof(HJ_INI));
            apstIni[i] = new HJ_INI;
            if (apstIni[i] == NULL)
            {
                return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
            }
            bzero(apstIni[i], sizeof(HJ_INI));
            return i;
        }
    }

    return HJ_INI_ERROR_NO_FREE_HANDLE;
}

static int HJ_Ini_ReadLine(int iFileHandle, char *sLine, int iMaxLineLen)
{
    assert(sLine);

    int i, iRetCode;

    for (i = 0; i < iMaxLineLen - 1; i++)
    {
        iRetCode = read(iFileHandle, sLine + i, 1);
        if (iRetCode < 0)
        {
            return HJ_INI_ERROR_FAIL_TO_READ_FILE;
        }

        if ((iRetCode == 0) && (i == 0))
        {
            return 1;
        }

        if ((iRetCode == 0) || (sLine[i] == '\n'))
        {
            sLine[i] = 0;
            return 0;
        }

        if  (sLine[i] == '\r')
        {
            i --;
        }
    }

    sLine[i] = 0;
    return 0;
}

static int HJ_Ini_ShmReadLine(char *p, char *sLine, int iMaxLineLen, int* iPoint, int iShmLen)
{
    assert(p && sLine && iPoint);

    int i;

    for (i = 0; i < iMaxLineLen;i++)
    {
        sLine[i] = *p;
        p ++;
        // printf("%d:%d\n",i,sLine[i]);

        if (iShmLen == *iPoint)
        {
            return 1;
        }

        if (sLine[i] == '\n')
        {
            sLine[i] = 0;
            p++;
            (*iPoint)++;
            // printf("%d:%s\n",*iPoint, sLine);
            return 0;
        }
        (*iPoint)++;
    }

    sLine[i] = 0;
    return 0;
}

static int HJ_Ini_AnalyzeLine(char *sLine, char *sSection, char *sIdent, char *sValue)
{
    assert(sLine && sSection && sIdent && sValue);

    char s[HJ_INI_MAX_LINE_LENGTH + 1];
    strcpy(s, sLine);
    HJ_Str_Trim(s);

    int iLen = strlen(s);
    if (iLen < 1)
    {
        return HJ_INI_ANALYZE_UNKNOWN;
    }

    if ((s[0] == '[') && (s[iLen - 1] == ']'))
    {
        strncpy(sSection, s + 1, iLen - 2);
        sSection[iLen - 2] = 0;
        HJ_Str_Trim(sSection);
        return HJ_INI_ANALYZE_SECTION;
    }

    if (s[0] == ';')
    {
        return HJ_INI_ANALYZE_COMMENT;
    }

    char *p = strchr(s, '=');
    if (p != NULL)
    {
        strncpy(sIdent, s, p - s);
        sIdent[p - s] = 0;

        strcpy(sValue, p + 1);

        HJ_Str_Trim(sIdent);
        HJ_Str_Trim(sValue);
        return HJ_INI_ANALYZE_VALUE;
    }

    return HJ_INI_ANALYZE_UNKNOWN;
}

static int HJ_Ini_CheckHandle(int iIniHandle)
{
    if ((iIniHandle < 0) || (iIniHandle >= HJ_INI_MAX_OPENED_NUM))
    {
        return HJ_INI_ERROR_INVALID_HANDLE;
    }

    if (apstIni[iIniHandle] == NULL)
    {
        return HJ_INI_ERROR_INVALID_HANDLE;
    }

    return 0;
}

/*****************************************************************/

void HJ_Ini_Free(int iIniHandle)
{
    HJ_Ini_CheckInitiated();

    if ((iIniHandle < 0) || (iIniHandle >= HJ_INI_MAX_OPENED_NUM))
    {
        return;
    }

    if (apstIni[iIniHandle] == NULL)
    {
        return;
    }

    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while (pstSection != NULL)
    {
        pstValue = pstSection->pstValue;
        while (pstValue != NULL)
        {
            pstSection->pstValue = pstValue->pstNext;
            if (pstValue->sIdent != NULL)
            {
                // free(pstValue->sIdent);
                delete []pstValue->sIdent;
            }
            if (pstValue->sValue != NULL)
            {
                // free(pstValue->sValue);
                delete []pstValue->sValue;
            }
            // free(pstValue);
            delete pstValue;
            pstValue = pstSection->pstValue;
        }

        apstIni[iIniHandle]->pstSection = pstSection->pstNext;
        if (pstSection->sSection != NULL)
        {
            // free(pstSection->sSection);
            delete []pstSection->sSection;
        }
        // free(pstSection);
        delete pstSection;
        pstSection = apstIni[iIniHandle]->pstSection;
    }

    // free(apstIni[iIniHandle]);
    delete apstIni[iIniHandle];
    apstIni[iIniHandle] = NULL;

    return;
}

int HJ_Ini_Load(char *sIniFileName, int iMode)
{
    HJ_Ini_CheckInitiated();

    int iIniHandle = HJ_Ini_GetHandle();
    if (iIniHandle < 0)
    {
        return iIniHandle;
    }

    if ((sIniFileName == NULL) || (sIniFileName[0] == 0))
    {
        return iIniHandle;
    }

    int iOpenMode = O_BINARY | O_DENYNONE | O_RDONLY;

    int iFileHandle = open(sIniFileName, iOpenMode);
    if (iFileHandle == -1)
    {
        if (iMode != HJ_INI_OPEN_FAIL_IGNORE)
        {
            HJ_Ini_Free(iIniHandle);
            return HJ_INI_ERROR_FAIL_TO_OPEN_FILE;
        }
        else
        {
            return iIniHandle;
        }
    }

    char sSection[HJ_INI_MAX_LINE_LENGTH+1];
    strcpy(sSection, "");

    int iRetCode;
    char sLine[HJ_INI_MAX_LINE_LENGTH + 1];
    char sIdent[HJ_INI_MAX_LINE_LENGTH + 1];
    char sValue[HJ_INI_MAX_LINE_LENGTH + 1];

    while (1)
    {
        iRetCode = HJ_Ini_ReadLine(iFileHandle, sLine, sizeof(sLine));
        if (iRetCode < 0)
        {
            close(iFileHandle);
            HJ_Ini_Free(iIniHandle);
            return iRetCode;
        }
        else if (iRetCode > 0)
        {
            break;
        }

        iRetCode = HJ_Ini_AnalyzeLine(sLine, sSection, sIdent, sValue);
        if (iRetCode == HJ_INI_ANALYZE_VALUE)
        {
            iRetCode = HJ_Ini_WriteString(iIniHandle, sSection, sIdent, sValue);
            if (iRetCode < 0)
            {
                close(iFileHandle);
                HJ_Ini_Free(iIniHandle);
                return iRetCode;
            }
        }
    }

    close(iFileHandle);
    return iIniHandle;
}

int HJ_Ini_ShmLoad(char *sShm, int iMode)
{
    assert(sShm);

    char sLine[HJ_INI_MAX_LINE_LENGTH+1];
    char sSection[HJ_INI_MAX_LINE_LENGTH+1];
    char sIdent[HJ_INI_MAX_LINE_LENGTH+1];
    char sValue[HJ_INI_MAX_LINE_LENGTH+1];

    HJ_Ini_CheckInitiated();

    int iIniHandle = HJ_Ini_GetHandle();
    if (iIniHandle < 0)
    {
        return iIniHandle;
    }

    char *p = sShm + 2;
    int iShmLen = sShm[0] * 256 + sShm[1];
    int i = 0, iRetCode;

    strcpy(sSection, "");
    while (1)
    //for (j=1;j<10;j++)
    {
        iRetCode = HJ_Ini_ShmReadLine(p, sLine, sizeof(sLine), &i, iShmLen);
        p = sShm + i + 2;
        //printf("ii:%d\n",i);
        if (iRetCode < 0)
        {
            HJ_Ini_Free(iIniHandle);
            return iRetCode;
        }
        else if (iRetCode > 0)
        {
            break;
        }

        iRetCode = HJ_Ini_AnalyzeLine(sLine, sSection, sIdent, sValue);

        if (iRetCode == HJ_INI_ANALYZE_VALUE)
        {
            iRetCode = HJ_Ini_WriteString(iIniHandle, sSection, sIdent, sValue);
            if (iRetCode < 0)
            {
                HJ_Ini_Free(iIniHandle);
                return iRetCode;
            }
        }
    }

    return 0;
}

int HJ_Ini_WriteString(int iIniHandle, char *sSection, char *sIdent, char *sValue)
{
    assert(sSection && sIdent && sValue);

    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    while (pstSection != NULL)
    {
        if (HJ_Str_StrCmp(sSection, pstSection->sSection) == 0)
        {
            break;
        }
        pstSection = pstSection->pstNext;
    }

    if (pstSection == NULL)
    {
        // pstSection = (HJ_INI_SECTION*) malloc(sizeof(HJ_INI_SECTION));
        pstSection = new HJ_INI_SECTION;
        if (pstSection == NULL)
        {
            return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
        }
        bzero(pstSection, sizeof(HJ_INI_SECTION));

        // pstSection->sSection = (char*)malloc(strlen(sSection)+1);
        pstSection->sSection = new char[strlen(sSection) + 1];
        if (pstSection->sSection == NULL)
        {
            // free(pstSection);
            delete pstSection;
            return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
        }
        strcpy(pstSection->sSection, sSection);

        pstSection->pstNext = NULL;
        if (apstIni[iIniHandle]->pstSectionTail != NULL)
        {
            apstIni[iIniHandle]->pstSectionTail->pstNext = pstSection;
        }
        apstIni[iIniHandle]->pstSectionTail = pstSection;
        if (apstIni[iIniHandle]->pstSection == NULL)
        {
            apstIni[iIniHandle]->pstSection = pstSection;
        }
    }

    HJ_INI_VALUE *pstValue = pstSection->pstValue;
    while (pstValue != NULL)
    {
        if (HJ_Str_StrCmp(sIdent, pstValue->sIdent) == 0)
        {
            break;
        }
        pstValue = pstValue->pstNext;
    }

    if (pstValue != NULL)
    {
        // free(pstValue->sValue);
        delete []pstValue->sValue;
        pstValue->sValue = NULL;
    }
    else
    {
        // pstValue = (HJ_INI_VALUE*)malloc(sizeof(HJ_INI_VALUE));
        pstValue = new HJ_INI_VALUE;
        if (pstValue == NULL)
        {
            return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
        }
        bzero(pstValue, sizeof(HJ_INI_VALUE));

        // pstValue->sIdent = (char*)malloc(strlen(sIdent)+1);
        pstValue->sIdent = new char[strlen(sIdent) + 1];
        if (pstValue->sIdent == NULL)
        {
            return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
        }
        strcpy(pstValue->sIdent, sIdent);

        pstValue->pstNext = NULL;
        if (pstSection->pstValueTail != NULL)
        {
            pstSection->pstValueTail->pstNext = pstValue;
        }
        pstSection->pstValueTail = pstValue;
        if (pstSection->pstValue == NULL)
        {
            pstSection->pstValue = pstValue;
        }
    }

    // pstValue->sValue = (char*)malloc(strlen(sValue)+1);
    pstValue->sValue = new char[strlen(sValue) + 1];
    if (pstValue->sValue == NULL)
    {
        return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
    }
    strcpy(pstValue->sValue, sValue);
    pstValue->iRemoved = 0;

    return 0;
}

int HJ_Ini_Dump(int iIniHandle)
{
    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while (pstSection != NULL)
    {
        printf("\n[%s]\n", pstSection->sSection);
        pstValue = pstSection->pstValue;
        while (pstValue != NULL)
        {
            printf("%s=%s\n", pstValue->sIdent, pstValue->sValue);
            pstValue = pstValue->pstNext;
        }

        pstSection = pstSection->pstNext;
    }

    return 0;
}

int HJ_Ini_ReadString(int iIniHandle, char *sSection, char *sIdent
    , char *sDefault, char *sValue, int iSize)
{
    assert(sSection && sIdent && sDefault && sValue);

    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    char *p = sDefault;
    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while (pstSection != NULL)
    {
        if (HJ_Str_StrCmp(pstSection->sSection, sSection) == 0)
        {
            pstValue = pstSection->pstValue;
            while (pstValue != NULL)
            {
                if (HJ_Str_StrCmp(pstValue->sIdent, sIdent) == 0)
                {
                    if (pstValue->iRemoved == 0)
                    {
                        p = pstValue->sValue;
                    }
                    break;
                }
                pstValue = pstValue->pstNext;
            }
            break;
        }

        pstSection = pstSection->pstNext;
    }

    strncpy(sValue, p, iSize - 1);
    sValue[iSize - 1] = 0;

    return 0;
}

int HJ_Ini_RemoveSection(int iIniHandle, char *sSection)
{
    assert(sSection);

    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while (pstSection != NULL)
    {
        if (HJ_Str_StrCmp(pstSection->sSection, sSection) == 0)
        {
            pstSection->iRemoved = 1;
            pstValue = pstSection->pstValue;
            while (pstValue != NULL)
            {
                pstValue->iRemoved = 1;
                pstValue = pstValue->pstNext;
            }
            break;
        }

        pstSection = pstSection->pstNext;
    }

    return 0;
}

int HJ_Ini_RemoveKey(int iIniHandle, char *sSection, char *sIdent)
{
    assert(sSection && sIdent);

    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    HJ_INI_SECTION *pstSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while (pstSection != NULL)
    {
        if (HJ_Str_StrCmp(pstSection->sSection, sSection) == 0)
        {
            pstValue = pstSection->pstValue;
            while (pstValue != NULL)
            {
                if (HJ_Str_StrCmp(pstValue->sIdent, sIdent) == 0)
                {
                    pstValue->iRemoved = 1;
                    break;
                }
                pstValue = pstValue->pstNext;
            }
            break;
        }

        pstSection = pstSection->pstNext;
    }

    return 0;
}

int HJ_Ini_Save(int iIniHandle, char *sIniFileName)
{
    HJ_Ini_CheckInitiated();

    int iRetCode = HJ_Ini_CheckHandle(iIniHandle);
    if (iRetCode < 0)
    {
        return iRetCode;
    }

    if ((sIniFileName == NULL) || (sIniFileName[0] == 0))
    {
        return iIniHandle;
    }

    HJ_STR_STRING_LIST *pstStringList = HJ_Str_StringListCreate();
    if (pstStringList == NULL)
    {
        return HJ_INI_ERROR_FAIL_TO_ALLOC_MEM;
    }

    int iOpenMode = O_BINARY | O_DENYNONE | O_RDWR | O_CREAT;

    int iFileHandle = open(sIniFileName, iOpenMode);
    if (iFileHandle == -1)
    {
        HJ_Str_StringListFree(pstStringList);
        return HJ_INI_ERROR_FAIL_TO_OPEN_FILE;
    }

    HJ_INI_SECTION *pstCurSection = apstIni[iIniHandle]->pstSection;
    HJ_INI_VALUE *pstValue;
    while(pstCurSection != NULL)
    {
        pstValue = pstCurSection->pstValue;
        while(pstValue != NULL)
        {
            pstValue->iWritten = 0;
            pstValue = pstValue->pstNext;
        }
        pstCurSection->iWritten = 0;
        pstCurSection = pstCurSection->pstNext;
    }

    pstCurSection = NULL;
    int iValueRemoved;
    char sLine[HJ_INI_MAX_LINE_LENGTH+1];
    char sSection[HJ_INI_MAX_LINE_LENGTH+1];
    char sIdent[HJ_INI_MAX_LINE_LENGTH+1];
    char sValue[HJ_INI_MAX_LINE_LENGTH+1];

    while (1)
    {
        iRetCode = HJ_Ini_ReadLine(iFileHandle, sLine, sizeof(sLine));
        if (iRetCode < 0)
        {
            HJ_Str_StringListFree(pstStringList);
            close(iFileHandle);
            return iRetCode;
        }
        else if (iRetCode > 0)
        {
            break;
        }

        iRetCode = HJ_Ini_AnalyzeLine(sLine, sSection, sIdent, sValue);
        if (iRetCode == HJ_INI_ANALYZE_SECTION)
        {
            if (pstCurSection != NULL)
            {
                if (pstCurSection->iRemoved == 0)
                {
                    pstValue = pstCurSection->pstValue;
                    while (pstValue != NULL)
                    {
                        if ((pstValue->iRemoved == 0) && (pstValue->iWritten == 0))
                        {
                            snprintf(sLine, sizeof(sLine), "%s=%s", pstValue->sIdent, pstValue->sValue);
                            iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                            if (iRetCode < 0)
                            {
                                HJ_Str_StringListFree(pstStringList);
                                close(iFileHandle);
                                return iRetCode;
                            }
                            pstValue->iWritten = 1;
                        }
                        pstValue = pstValue->pstNext;
                    }
                }
            }

            pstCurSection = apstIni[iIniHandle]->pstSection;
            while (pstCurSection != NULL)
            {
                if (HJ_Str_StrCmp(pstCurSection->sSection, sSection) == 0)
                {
                    break;
                }
                pstCurSection = pstCurSection->pstNext;
            }

            if ((pstCurSection == NULL)
                || ((pstCurSection != NULL) && (pstCurSection->iRemoved == 0)))
            {
                snprintf(sLine, sizeof(sLine), "[%s]", sSection);
                iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                if (iRetCode < 0)
                {
                    HJ_Str_StringListFree(pstStringList);
                    close(iFileHandle);
                    return iRetCode;
                }

                if (pstCurSection != NULL)
                {
                    pstCurSection->iWritten = 1;
                }
            }
        }
        else if (iRetCode == HJ_INI_ANALYZE_VALUE)
        {
            iValueRemoved = 0;
            if (pstCurSection != NULL)
            {
                if (pstCurSection->iRemoved != 0)
                {
                    iValueRemoved = 1;
                }
                else
                {
                    pstValue = pstCurSection->pstValue;
                    while (pstValue != NULL)
                    {
                        if (HJ_Str_StrCmp(pstValue->sIdent, sIdent) == 0)
                        {
                            if (pstValue->iRemoved != 0)
                            {
                                iValueRemoved = 1;
                            }
                            else
                            {
                                snprintf(sLine, sizeof(sLine), "%s=%s", pstValue->sIdent, pstValue->sValue);
                                pstValue->iWritten = 1;
                            }
                            break;
                        }
                        pstValue = pstValue->pstNext;
                    }
                }
            }

            if (iValueRemoved == 0)
            {
                iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                if (iRetCode < 0)
                {
                    HJ_Str_StringListFree(pstStringList);
                    close(iFileHandle);
                    return iRetCode;
                }
            }
        }
        else
        {
            if ((pstCurSection == NULL)
                || ((pstCurSection != NULL) && (pstCurSection->iRemoved == 0)))
            {
                iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                if (iRetCode < 0)
                {
                    HJ_Str_StringListFree(pstStringList);
                    close(iFileHandle);
                    return iRetCode;
                }
            }
        }
    }

    if (pstCurSection != NULL)
    {
        if (pstCurSection->iRemoved == 0)
        {
            pstValue = pstCurSection->pstValue;
            while (pstValue != NULL)
            {
                if ((pstValue->iRemoved == 0) && (pstValue->iWritten == 0))
                {
                    snprintf(sLine, sizeof(sLine), "%s=%s", pstValue->sIdent, pstValue->sValue);
                    iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                    if (iRetCode < 0)
                    {
                        HJ_Str_StringListFree(pstStringList);
                        close(iFileHandle);
                        return iRetCode;
                    }
                    pstValue->iWritten = 1;
                }
                pstValue = pstValue->pstNext;
            }
        }
    }

    pstCurSection = apstIni[iIniHandle]->pstSection;
    while (pstCurSection != NULL)
    {
        if ((pstCurSection->iRemoved == 0) && (pstCurSection->iWritten == 0))
        {
            snprintf(sLine, sizeof(sLine), "[%s]", pstCurSection->sSection);
            iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
            if (iRetCode < 0)
            {
                HJ_Str_StringListFree(pstStringList);
                close(iFileHandle);
                return iRetCode;
            }
            pstCurSection->iWritten = 1;
        }

        pstValue = pstCurSection->pstValue;
        while (pstValue != NULL)
        {
            if ((pstValue->iRemoved == 0) && (pstValue->iWritten == 0))
            {
                if (pstCurSection->iWritten == 0)
                {
                    snprintf(sLine, sizeof(sLine), "[%s]", pstCurSection->sSection);
                    iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                    if (iRetCode < 0)
                    {
                        HJ_Str_StringListFree(pstStringList);
                        close(iFileHandle);
                        return iRetCode;
                    }
                    pstCurSection->iWritten = 1;
                }

                snprintf(sLine, sizeof(sLine), "%s=%s", pstValue->sIdent, pstValue->sValue);
                iRetCode = HJ_Str_StringListAdd(pstStringList, sLine);
                if (iRetCode < 0)
                {
                    HJ_Str_StringListFree(pstStringList);
                    close(iFileHandle);
                    return iRetCode;
                }
                pstValue->iWritten = 1;
            }
            pstValue = pstValue->pstNext;
        }
        pstCurSection = pstCurSection->pstNext;
    }

#ifndef HJ_UNIX
    if (chsize(iFileHandle, 0L) != 0)
#else
    if (ftruncate(iFileHandle, 0L) != 0)
#endif
    {
        HJ_Str_StringListFree(pstStringList);
        close(iFileHandle);
        return HJ_INI_ERROR_FAIL_TO_WRITE;
    }
    if (lseek(iFileHandle, 0, 0) < 0)
    {
        return HJ_INI_ERROR_FAIL_TO_SEEK;
    }


    char *p = HJ_Str_StringListGetFirst(pstStringList);
    int iLen;
    while (p != NULL)
    {
        iLen = strlen(p);
        if (iLen > 0)
        {
            if (write(iFileHandle, p, iLen) != iLen)
            {
                return HJ_INI_ERROR_FAIL_TO_WRITE;
            }
        }

        if (write(iFileHandle, "\r\n", 2) != 2)
        {
            return HJ_INI_ERROR_FAIL_TO_WRITE;
        }
        p = HJ_Str_StringListGetNext(pstStringList);
    }

    HJ_Str_StringListFree(pstStringList);
    close(iFileHandle);
    return 0;
}

void HJ_Ini_FreeAll(void)
{
    for (int i = 0; i < HJ_INI_MAX_OPENED_NUM; i++)
    {
        HJ_Ini_Free(i);
    }

    return;
}
