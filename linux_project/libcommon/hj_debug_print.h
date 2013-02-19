#ifndef __HJ_DEBUG_PRINT_H__
#define __HJ_DEBUG_PRINT_H__

#include <stdio.h>

#define LM_DEBUG    0x01    // 调试输出级
#define LM_TRACE    0x02    // 函数跟踪级
#define LM_INFO     0x04    // 信息输出级
#define LM_ERROR    0x08    // 错误输出级
#define LM_EXCEPT   0x10    // 程序异常级

/*!
* DEBUG_LEVEL : 日志输出级别位掩码
* @n从低位至高位每位依次为
* @n0x00-不显示任何消息，0x01-显示异常或错误，0x02-显示调试输出，0x04-函数跟踪消息
* @n0x08-显示测试输出消息
*/
// #ifndef DEBUG_LEVEL
// #define DEBUG_LEVEL (LM_DEBUG|LM_INFO|LM_ERROR|LM_EXCEPT)
// #endif

#if DEBUG_LEVEL
#define DEBUG_PRINT(level, fmt, args...) \
do{ \
    if (DEBUG_LEVEL & level) \
    { \
        printf("%s-%s-[%d:%d]-%s: " fmt, #level, __FILE__, getpid(), __LINE__, __FUNCTION__ , ##args); \
    } \
}while(false)
#else
#define DEBUG_PRINT(level, fmt, args...)
#endif

#endif
