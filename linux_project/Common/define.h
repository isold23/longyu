

#ifndef _DEFINE_H_
#define _DEFINE_H_

typedef int BOOL;

typedef int int32;
typedef short int16;
typedef char int8;

#ifdef COMPILER_MSVC
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef __int64 int64;
#else
#ifndef x86_64
typedef unsigned long long uint64;
typedef long long int64;
typedef long long INT64;
#else
typedef unsigned long uint64;
typedef long int64;
typedef long INT64;
#endif
#endif /* COMPILER_MSVC */
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#define SUCCEEDED 1
#define FAILED 0
#define ERROR 0
#define SOCKET_ERROR -1
#define CH_USER_NAME "wackey"
//∞Ê±æ∂®“Â

#endif //_DEFINE_H_





