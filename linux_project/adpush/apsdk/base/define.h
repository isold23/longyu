#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>

#if defined(__linux__) || defined(__APPLE__)

#define SUCCEEDED 1
#define FAILED 0
#define ERROR 0
#define SOCKET_ERROR -1

#endif


/*typedef int int32;
typedef short int16;
typedef char int8;

typedef unsigned int unsigned int;
typedef uint16_t uint16_t;
typedef uint8_t uint8;

#ifdef COMPILER_MSVC
typedef int64_t int64_t;
typedef unsigned int64_t uint64_t;
typedef int64_t int64_t;
#else
#ifndef x86_64
typedef unsigned int int uint64_t;
typedef int int int64_t;
#else
typedef unsigned int uint64_t;
typedef int int64_t;
#endif
#endif
*/




#endif //_DEFINE_H_





