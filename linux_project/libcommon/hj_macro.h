/*! @hj_macro.h
*******************************************************************************
</PRE>
模块名       ：库相关通用宏定义
文件名       ：hj_macro.h
相关文件     ：hj_macro.cpp
文件实现功能 ：库相关通用宏定义
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

#ifndef __HJ_MACRO_H__
#define __HJ_MACRO_H__

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#define MIN(a,b) ((a>b)?b:a)
#define MAX(a,b) ((a>b)?a:b)

// Uncomment this line under unix/linux
#define HJ_UNIX

#ifdef HJ_UNIX

#define O_BINARY    0
#define O_DENYNONE  0

#else

#include <io.h>

#endif

#define HJ_STR_ERROR_BASE    -1000
#define HJ_INI_ERROR_BASE    -2000

#endif
