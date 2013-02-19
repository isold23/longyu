#ifndef ____TOOL______
#define ____TOOL______


#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../Bs.h"
#include "dtool.h"
#include "ftool.h"

#ifndef _countof
#define _countof(x) (sizeof(x)/sizeof(x[0]))
#endif

#define cstr_len(str) (_countof(str)-1) 


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define s_l(x) #x,cstr_len(#x)
#define s_l_null() "",0

#define id_s(x) x,#x

#define kw_default "_def"
#define kw_default_len (cstr_len(kw_default))
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
inline bool isblank(char c) {
	return (c==' ' || c=='\r' || c=='\n' || c=='\t');
}

inline bool isNumerical(char c) {
	return (c>='0' && c<='9');
}

inline char* skipBlank(char *str) { 
	while (*str!='\0' && isblank(*str)) ++str;
	return str;
}

inline char* skipNoNumerical(char *str) {
	while (*str!='\0' && !isNumerical(*str)) ++str;
	return str;
}

inline char *skipWord(char *str) {
	while (*str!='\0' && !isblank(*str)) ++str;
	return str;
}

#endif


void printVersion(void);
bool makeDp(const char *src);
bool makeDp(const char *src,char *inl,char *cpp);

