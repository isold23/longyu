#include <string.h>
#include <strings.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cgi-lib.h"
#include "cgi-llist.h"
#include "string-lib.h"

#include "hj_cgi.h"

static int iHJ_Cgi_Initialized = 0;
static llist stHJ_Cgi_Entries;
static llist stHJ_Cookie_Entries;

void HJ_Cgi_ReInit(void)
{
    iHJ_Cgi_Initialized = 0;
}

void HJ_Cgi_Init(void)
{
    if (iHJ_Cgi_Initialized != 0)
    {
        return;
    }

    read_cgi_input(&stHJ_Cgi_Entries);
    parse_cookies(&stHJ_Cookie_Entries);

    iHJ_Cgi_Initialized = 1;
}

char* HJ_Cgi_Value(char *sParam)
{
    HJ_Cgi_Init();

    char *p = cgi_val(stHJ_Cgi_Entries, sParam);
    if (p == NULL)
    {
        return "";
    }
    else
    {
        return p;
    }
}

char* HJ_Cgi_Cookie(char *key)
{
    HJ_Cgi_Init();

    return (char*)cgi_val(stHJ_Cookie_Entries, key);
}

char** HJ_Cgi_Value_Multi(char *sParam)
{
    HJ_Cgi_Init();

    return (char**)cgi_val_multi(stHJ_Cgi_Entries, sParam);
}

void HJ_Cgi_GetClientInfo(HJ_CGI_CLIENT_INFO *pstHostInfo)
{
    bzero(pstHostInfo, sizeof(HJ_CGI_CLIENT_INFO));

    if (getenv("REMOTE_ADDR") != NULL)
    {
        strcpy(pstHostInfo->sRemoteAddress, getenv("REMOTE_ADDR"));
    }
    if (getenv("REMOTE_PORT") != NULL)
    {
        strcpy(pstHostInfo->sRemotePort, getenv("REMOTE_PORT"));
    }
}

void HJ_Cgi_SetUploadOption(char *sPath, int iMaxSize)
{
    sUploadFilePath = sPath;
    iUploadFileMaxSize = iMaxSize;
}

int HJ_Cgi_IsUploadOverSize(void)
{
    return iUploadFileOverSize;
}

void HJ_Cgi_FreeEntries()
{
    list_clear(&stHJ_Cgi_Entries);
    list_clear(&stHJ_Cookie_Entries);
    iHJ_Cgi_Initialized = 0;
}

// 获取包
unsigned char* HJ_Cgi_GetPostValue(int *iLen)
{
    unsigned char *buffer = NULL;
    if (CONTENT_LENGTH != NULL)
    {
        *iLen = atoi(CONTENT_LENGTH);
        buffer = (unsigned char*)malloc(sizeof(char) * (*iLen) + 1);
        if ((int)fread(buffer, sizeof(char), *iLen, stdin) != *iLen)
        {
            free(buffer);
            return NULL;
        }
        buffer[*iLen] = '\0';
    }
    return buffer;
}

// 获取文件流
int HJ_Cgi_GetFormValue(unsigned char *sBuf, int *iLen, char *sName, char *sValue)
{
    /*
    long content_length;
    if (CONTENT_LENGTH != NULL)
    {
        content_length = atol(CONTENT_LENGTH);
    }
    else
    {
        return 0;
    }
    */

    /* get boundary */
    char *tempstr = newstr(CONTENT_TYPE);
    char *boundary = strstr(tempstr, "boundary=");
    boundary += (sizeof(char) * 9);
    /* ignore first boundary; this isn't so robust; improve it later */

    char *buffer = (char *)malloc(sizeof(char) * BUFSIZ + 1);
    cgigetline(buffer, BUFSIZ);
    /* now start parsing */
    int bytesread = cgigetline(buffer, BUFSIZ);
    if (bytesread == 0)
    {
        return -1;
    }
    buffer[bytesread] = '\0';

    tempstr = newstr(buffer);
    tempstr += (sizeof(char) * 38); /* 38 is header up to name */
    sName = tempstr;
    sValue = (char *)malloc(sizeof(char) * BUFSIZ + 1);
    strcpy(sValue, "");

    while (*tempstr != '"')
    {
        tempstr++;
    }
    *tempstr = '\0';

    if (strstr(buffer,"filename=\"") != NULL)
    {
        tempstr = newstr(buffer);
        tempstr =strstr(tempstr,"filename=\"");
        tempstr += (sizeof(char) * 10);
        if (strlen(tempstr) >= BUFSIZ)
            sValue = (char *) realloc(sValue, sizeof(char) * strlen(tempstr)+1);
        sValue = tempstr;
        while (*tempstr != '"')
        {
            tempstr++;
        }
        *tempstr = '\0';
    }

    while (cgigetline(buffer, BUFSIZ) > 1)
    {
        /* DOS style blank line? */
        if ((buffer[0] == '\r') && (buffer[1] == '\n'))
        {
            break;
        }
    }

    int iTotalLen = *iLen;
    *iLen = 0;
    int i, j = 0;
    short done = 0;
    while (!done)
    {
        bytesread = cgigetline(buffer, BUFSIZ);
        buffer[bytesread] = '\0';
        if (bytesread && (strstr(buffer,boundary) == NULL))
        {
            i = 0;
            for (i = 0; i < bytesread; i++)
            {
                if ((j > iTotalLen) && (iTotalLen != 0))
                {
                    break;
                }
                sBuf[j] = buffer[i];
                j++;
            }
        }
        else
        {
            *iLen = j - 2;
            done = 1;
        }
    }

    return 0;
}
