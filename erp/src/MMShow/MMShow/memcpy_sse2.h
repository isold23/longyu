#pragma once

#if 1
	#define fast_memcpy memcpy_sse2
	void *memcpy_sse2(void *dst, const void *src, int nBytes);
#endif