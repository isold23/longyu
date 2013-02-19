/*! @hj_str.h
*******************************************************************************
</PRE>
模块名       ：字符串处理相关库函数申明
文件名       ：hj_str.h
相关文件     ：hj_str.cpp
文件实现功能 ：字符串处理相关库函数申明
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

#ifndef __HJ_STR_H__
#define __HJ_STR_H__

#define HJ_STR_STRING_LIST_ERROR_INVALID_POINTER   (HJ_STR_ERROR_BASE-1)
#define HJ_STR_STRING_LIST_ERROR_FAIL_TO_ALLOC_MEM (HJ_STR_ERROR_BASE-2)

typedef struct _HJ_STR_STRING_LIST_ITEM
{
    char *pszItem;
    struct _HJ_STR_STRING_LIST_ITEM *pstNext;
} HJ_STR_STRING_LIST_ITEM;

typedef struct _HJ_STR_STRING_LIST
{
    HJ_STR_STRING_LIST_ITEM *pstItem;
    HJ_STR_STRING_LIST_ITEM *pstItemTail;
    HJ_STR_STRING_LIST_ITEM *pstItemCur;
} HJ_STR_STRING_LIST;

HJ_STR_STRING_LIST* HJ_Str_StringListCreate(void);
int HJ_Str_StringListAdd(HJ_STR_STRING_LIST *pstStringList, char *pszItem);
void HJ_Str_StringListFree(HJ_STR_STRING_LIST *pstStringList);
char* HJ_Str_StringListGetFirst(HJ_STR_STRING_LIST *pstStringList);
char* HJ_Str_StringListGetNext(HJ_STR_STRING_LIST *pstStringList);
////////////////////////////////////////////////////////////////////

char* HJ_Str_Trim(char *s);
char* HJ_Str_StrUppercase(char *s);
char* HJ_Str_StrLowercase(char *s);
int HJ_Str_StrCmp(char *s1, char *s2);
int HJ_Str_StrNCCmp(char *s1, char *s2);
char *HJ_Str_StrReplaceChar(char *pStrSrc, char cOld, char cNew);
char *HJ_Str_StrCat(char *s, const char *pszFormat, ...);

char* HJ_Str_Strcpy(char *pszDest, char *pszSrc);
char* HJ_Str_Strncpy(char *pszDest, char *pszSrc, int iMaxChar);

char* HJ_Str_Quote(char *pszDest, char *pszSrc);
char* HJ_Str_QuoteWild(char *pszDest, char *pszSrc);

char* HJ_Str_CutHZString(char *pszSrc);

char* HJ_Str_Short(const char *pszSrc,char *pszDest,int len);

#endif
