#pragma once
 
CStringA URLEncode(const char *str,size_t size);
CStringA URLDecode(const char *str,size_t size);

CString URLEncode(const CString &str);
CString URLDecode(const CString &str);
