#ifndef DEF_SINA_RSACOMDEF_H
#define DEF_SINA_RSACOMDEF_H

#include "../include.h"

//////////////////////////////////////////////////////////////////////////
// typedef unsigned int uint32_t;
// typedef unsigned char uint8_t;
// typedef uint8_t* PBYT
//////////////////////////////////////////////////////////////////////////
#define _MINPUBLICKEYPSIZE_ 128//512 //1024 
#define _PRIVATEKEYSIZE_ 4//16
#define _HASHSIZE_ 20
#define MINIMUMPACKAGESIZE sizeof(uint32_t)
#define _POOL_SIZE_ 624*4
//////////////////////////////////////////////////////////////////////////

#endif
