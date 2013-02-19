#include "StdAfx.h"
#include "URLCodec.h"


inline char lowChar(unsigned char c) {
	return c & 0x0f;
}

inline char highChar(unsigned char c) { 
	return c >> 4;
}

inline char makeChar(unsigned char high,unsigned char low) {
	return low | (high << 4);
}

inline char charToHex(unsigned char c) {
	return c>9 ? c+'A'-10 : c+'0'; 
}

inline char hexToChar(unsigned char h) {
	return (h>64 ? h-('A'-10) : h-'0');
}

CStringA URLEncode(const char *str,size_t size)
{
	CStringA ret; 
	for (size_t i = 0; i<size; i++)
	{
		unsigned char c = str[i];
		if ((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
			ret += c;
		}
		else if (c == ' ')
		{                       
			ret += '+';                        
		}       
		else
		{
			ret += '%';
			ret += charToHex(highChar(c));
			ret += charToHex(lowChar(c));
		}
	}
	return ret;
}


CStringA URLDecode(const char *str,size_t size)
{
	CStringA ret;

	for (size_t i = 0; i< size; i++)
	{
		unsigned char c = str[i];
		if ((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
			ret += c;
		}
		else if (c == '+')
		{                       
			ret += ' ';                        
		}       
		else if(c == '%')
		{
			i++;
			unsigned char high = hexToChar(str[i++]);
			unsigned char low = hexToChar(str[i]);
			ret += makeChar(high,low);
		}
	}
	return ret;
}

CString URLEncode(const CString &str)
{
#ifndef _UNICODE 
	return URLEncode(str.GetString(),str.GetLength());
#else
	CStringA mbstr(CComVariant(str.GetString()));
	return CComVariant(URLEncode(mbstr.GetString(),mbstr.GetLength()));
#endif
}

CString URLDecode(const CString &str)
{
#ifndef _UNICODE
	return URLDecode(str.GetString(),str.GetLength());
#else
	CStringA mbstr(CComVariant(str.GetString()));
	return CComVariant(URLDecode(mbstr.GetString(),mbstr.GetLength()));
#endif
}
