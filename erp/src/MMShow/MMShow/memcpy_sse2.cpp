#include "StdAfx.h"

void *memcpy_sse2(void *dst, const void *src, int nBytes)
{
	__asm
	{
		// Copyright (C) 2009  Jan Boon (Kaetemi)
		// optimized on Intel Core 2 Duo T7500

		mov         ecx, nBytes
		mov         edi, dst
		mov         esi, src
		add         ecx, edi

		prefetchnta [esi]
		prefetchnta [esi+32]
		prefetchnta [esi+64]
		prefetchnta [esi+96]

		// handle nBytes lower than 128
		cmp         nBytes, 512
		jge         fast
slow:
		mov         bl, [esi]
		mov         [edi], bl
		inc         edi
		inc         esi
		cmp         ecx, edi
		jnz         slow
		jmp         end

fast:
		// align dstEnd to 128 bytes
		and         ecx, 0xFFFFFF80

			// get srcEnd aligned to dstEnd aligned to 128 bytes
		mov         ebx, esi
		sub         ebx, edi
		add         ebx, ecx

			// skip unaligned copy if dst is aligned
		mov         eax, edi
		and         edi, 0xFFFFFF80
		cmp         eax, edi
		jne         first
		jmp         more

first:
		// copy the first 128 bytes unaligned
		movdqu      xmm0, [esi]
		movdqu      xmm1, [esi+16]
		movdqu      xmm2, [esi+32]
		movdqu      xmm3, [esi+48]

		movdqu      xmm4, [esi+64]
		movdqu      xmm5, [esi+80]
		movdqu      xmm6, [esi+96]
		movdqu      xmm7, [esi+112]

		movdqu      [eax], xmm0
		movdqu      [eax+16], xmm1
		movdqu      [eax+32], xmm2
		movdqu      [eax+48], xmm3

		movdqu      [eax+64], xmm4
		movdqu      [eax+80], xmm5
		movdqu      [eax+96], xmm6
		movdqu      [eax+112], xmm7

			// add 128 bytes to edi aligned earlier
		add         edi, 128

			// offset esi by the same value
		sub         eax, edi
		sub         esi, eax

			// last bytes if dst at dstEnd
		cmp         ecx, edi
		jnz         more
		jmp         last

more:
		// handle equally aligned arrays
		mov         eax, esi
		and         eax, 0xFFFFFF80
		cmp         eax, esi
		jne         unaligned4k

aligned4k:
		mov         eax, esi
		add         eax, 4096
		cmp         eax, ebx
		jle         aligned4kin
		cmp         ecx, edi
		jne         alignedlast
		jmp         last

aligned4kin:
		prefetchnta [esi]
		prefetchnta [esi+32]
		prefetchnta [esi+64]
		prefetchnta [esi+96]

		add         esi, 128

		cmp         eax, esi
		jne         aligned4kin

		sub         esi, 4096

alinged4kout:
		movdqa      xmm0, [esi]
		movdqa      xmm1, [esi+16]
		movdqa      xmm2, [esi+32]
		movdqa      xmm3, [esi+48]

		movdqa      xmm4, [esi+64]
		movdqa      xmm5, [esi+80]
		movdqa      xmm6, [esi+96]
		movdqa      xmm7, [esi+112]

		movntdq     [edi], xmm0
		movntdq     [edi+16], xmm1
		movntdq     [edi+32], xmm2
		movntdq     [edi+48], xmm3

		movntdq     [edi+64], xmm4
		movntdq     [edi+80], xmm5
		movntdq     [edi+96], xmm6
		movntdq     [edi+112], xmm7

		add         esi, 128
		add         edi, 128

		cmp         eax, esi
		jne         alinged4kout
		jmp         aligned4k

alignedlast:
		mov         eax, esi

alignedlastin:
		prefetchnta [esi]
		prefetchnta [esi+32]
		prefetchnta [esi+64]
		prefetchnta [esi+96]

		add         esi, 128

		cmp         ebx, esi
		jne         alignedlastin

		mov         esi, eax

alignedlastout:
		movdqa      xmm0, [esi]
		movdqa      xmm1, [esi+16]
		movdqa      xmm2, [esi+32]
		movdqa      xmm3, [esi+48]

		movdqa      xmm4, [esi+64]
		movdqa      xmm5, [esi+80]
		movdqa      xmm6, [esi+96]
		movdqa      xmm7, [esi+112]

		movntdq     [edi], xmm0
		movntdq     [edi+16], xmm1
		movntdq     [edi+32], xmm2
		movntdq     [edi+48], xmm3

		movntdq     [edi+64], xmm4
		movntdq     [edi+80], xmm5
		movntdq     [edi+96], xmm6
		movntdq     [edi+112], xmm7

		add         esi, 128
		add         edi, 128

		cmp         ecx, edi
		jne         alignedlastout
		jmp         last

unaligned4k:
		mov         eax, esi
		add         eax, 4096
		cmp         eax, ebx
		jle         unaligned4kin
		cmp         ecx, edi
		jne         unalignedlast
		jmp         last

unaligned4kin:
		prefetchnta [esi]
		prefetchnta [esi+32]
		prefetchnta [esi+64]
		prefetchnta [esi+96]

		add         esi, 128

		cmp         eax, esi
		jne         unaligned4kin

		sub         esi, 4096

unalinged4kout:
		movdqu      xmm0, [esi]
		movdqu      xmm1, [esi+16]
		movdqu      xmm2, [esi+32]
		movdqu      xmm3, [esi+48]

		movdqu      xmm4, [esi+64]
		movdqu      xmm5, [esi+80]
		movdqu      xmm6, [esi+96]
		movdqu      xmm7, [esi+112]

		movntdq     [edi], xmm0
		movntdq     [edi+16], xmm1
		movntdq     [edi+32], xmm2
		movntdq     [edi+48], xmm3

		movntdq     [edi+64], xmm4
		movntdq     [edi+80], xmm5
		movntdq     [edi+96], xmm6
		movntdq     [edi+112], xmm7

		add         esi, 128
		add         edi, 128

		cmp         eax, esi
		jne         unalinged4kout
		jmp         unaligned4k

unalignedlast:
		mov         eax, esi

unalignedlastin:
		prefetchnta [esi]
		prefetchnta [esi+32]
		prefetchnta [esi+64]
		prefetchnta [esi+96]

		add         esi, 128

		cmp         ebx, esi
		jne         unalignedlastin

		mov         esi, eax

unalignedlastout:
		movdqu      xmm0, [esi]
		movdqu      xmm1, [esi+16]
		movdqu      xmm2, [esi+32]
		movdqu      xmm3, [esi+48]

		movdqu      xmm4, [esi+64]
		movdqu      xmm5, [esi+80]
		movdqu      xmm6, [esi+96]
		movdqu      xmm7, [esi+112]

		movntdq     [edi], xmm0
		movntdq     [edi+16], xmm1
		movntdq     [edi+32], xmm2
		movntdq     [edi+48], xmm3

		movntdq     [edi+64], xmm4
		movntdq     [edi+80], xmm5
		movntdq     [edi+96], xmm6
		movntdq     [edi+112], xmm7

		add         esi, 128
		add         edi, 128

		cmp         ecx, edi
		jne         unalignedlastout
		jmp         last

last:
		// get the last 128 bytes
		mov         ecx, nBytes
		mov         edi, dst
		mov         esi, src
		add         edi, ecx
		add         esi, ecx
		sub         edi, 128
		sub         esi, 128

			// copy the last 128 bytes unaligned
		movdqu      xmm0, [esi]
		movdqu      xmm1, [esi+16]
		movdqu      xmm2, [esi+32]
		movdqu      xmm3, [esi+48]

		movdqu      xmm4, [esi+64]
		movdqu      xmm5, [esi+80]
		movdqu      xmm6, [esi+96]
		movdqu      xmm7, [esi+112]

		movdqu      [edi], xmm0
		movdqu      [edi+16], xmm1
		movdqu      [edi+32], xmm2
		movdqu      [edi+48], xmm3

		movdqu      [edi+64], xmm4
		movdqu      [edi+80], xmm5
		movdqu      [edi+96], xmm6
		movdqu      [edi+112], xmm7

end:
	}
	return dst;
}
