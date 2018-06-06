//#if defined(WIN32)
//	#include "stdafx.h"
//#endif
#include <memory.h>
#include "iplMemory.h"


typedef void *(*memcpyPtr )(void *,const void*, size_t);
typedef void *(*memzeroPtr)(void *, size_t);

static void	*memcpySSE (void *dts, const void *src, size_t nbytes);
static void	*memcpyMMX (void *dts, const void *src, size_t nbytes);
static void	*memzeroMMX(void *dts, size_t nbytes);

static inline void	*_memcpySSE(void *dts, const void *src, size_t nbytes);
static inline void	*_memcpyMMX(void *dts, const void *src, size_t nbytes);
static inline void	*_memcpyOrg(void *dts, const void *src, size_t nbytes);

static inline void	*_memzeroMMX(void *dts, size_t nbytes);
static inline void	*_memzeroOrg(void *dts, size_t nbytes);

//static inline void	*_memsetMMX(void *dts, unsigned int nbytes);
//static inline void	*_memsetOrg(void *dts, unsigned int nbytes);


memcpyPtr  findBestmemCpy (void);
memzeroPtr findBestmemZero(void);

static BOOL DetectMMX(void);
static BOOL DetectSSE(void);


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//extren functions 

void* (*iplmemcpy )(void *dts, const void *src, size_t nbytes) = findBestmemCpy();
void* (*iplmemzero)(void *dts, size_t nbytes) = findBestmemZero();

//extren functions 
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////



#ifndef WIN64
static BOOL DetectMMX(void)
{
	BOOL	result = FALSE;
	_asm
	{
		mov		eax,		1
		cpuid
		test	edx,		0x800000	// bit 23
		je		noMMX
		mov		result,		TRUE
	noMMX:
	}

	return (result);
}

static BOOL DetectSSE(void)
{
	int	result = FALSE;
	_asm
	{
		mov		eax,		1
		cpuid
		test	edx,		0x002000000	// bit 25
		je		noSSE
		mov		result,		TRUE
	noSSE:
	}

	if( result == TRUE )
	{
		// check OS support for SSE
		try
		{
			_asm
			{
				xorps		xmm0,	xmm0
			}
		}
		catch(...)
		{
			return FALSE;
		}

		return TRUE;
	}

	return FALSE;
}
#endif

static int g_CPU = 0xFFFFFFFF;

memcpyPtr findBestmemCpy(void)
{
//	if( DetectSSE() == TRUE )
//		return memcpySSE;

#ifndef WIN64
	if( DetectMMX() == TRUE )
	{
		g_CPU = 1;
		return _memcpyMMX;
	}

	g_CPU = 0;
#endif
	return _memcpyOrg;
}

memzeroPtr findBestmemZero(void)
{
#ifndef WIN64
	switch(g_CPU)
	{
	case 0xFFFFFFFF:
		if( DetectMMX() == TRUE )
		{
			g_CPU = 1;
			return _memzeroMMX;
		}
		break;
	case 0:
		return _memzeroOrg;
		break;
	case 1:
		return _memzeroMMX;
		break;
	}
#endif
	return _memzeroOrg;
}

inline void* _memcpyOrg(void *dts, const void *src, size_t nbytes)
{
	return memcpy(dts,src,nbytes);
}
inline void	*_memzeroOrg(void *dts, size_t nbytes)
{
	return memset(dts,0,nbytes);
}

#ifndef WIN64

inline void	*_memcpySSE(void *dts, const void *src, size_t nbytes)
{
	return memcpySSE(dts,src,nbytes);
}

inline void	*_memcpyMMX(void *dts, const void *src, size_t nbytes)
{
	return memcpyMMX(dts,src,nbytes);
}

inline void	*_memzeroMMX(void *dts, size_t nbytes)
{
	return memzeroMMX(dts,nbytes);
}


//2006 08 30 
//by kiok ahn, sse copy
//아래 코드를 쓰면 "/"연산자에서 오류 발생. ㅜㅜ
//빠르지 않다.
//(1024*1024*16)byte * (10)count 
//memcpy      - 28.2ms
//mmx old version - 23.7ms
//mmx new version - 14.2ms
//아래 코드       - 22.5ms
//movups
void* memcpySSE(void *dts, const void *src, size_t nbytes)
{
	__asm
	{
		push    edi
		push    esi
		
		mov		ecx,		nbytes
		mov		esi,		src
		mov		edi,		dts
		push    ecx
	  
		and     ecx,        0x7F //0000 0000 0111 1111(b), 7bit 하위 크기 
		push    ecx
		and     ecx,        63
		rep     movsb
		pop     ecx
		shr		ecx,        6
		cmp		ecx,        0
		je		_mmx_copy_end

_mmx_copy://7bit 하위 크기에 대해 mmx copy 
		movq	mm0,		[esi+0]
		movq	mm1,		[esi+8]
		movq	[edi+0],	mm0
		movq	[edi+8],	mm1
		movq	mm2,		[esi+16]
		movq	mm3,		[esi+24]
		movq	[edi+16],	mm2
		movq	[edi+24],	mm3
		movq	mm0,		[esi+32]
		movq	mm1,		[esi+40]
		movq	[edi+32],	mm0
		movq	[edi+40],	mm1
		movq	mm2,		[esi+48]
		movq	mm3,		[esi+56]
		movq	[edi+48],	mm2
		movq	[edi+56],	mm3

		add		esi,		64
		add		edi,		64
		dec		ecx
		jnz		_mmx_copy
_mmx_copy_end:

		pop     ecx
		shr     ecx,        7
		cmp     ecx,        0
		je      _sse_copy_end
		mov		eax,		128
_sse_copy:
		movups	xmm0,		[esi]
		movups	xmm1,		[esi+16]
		movups	xmm2,		[esi+32]
		movups	xmm3,		[esi+48]
		movups	xmm4,		[esi+64]
		movups	xmm5,		[esi+80]
		movups	xmm6,		[esi+96]
		movups	xmm7,		[esi+112]

		movups	[edi],		xmm0
		movups	[edi+16],	xmm1
		movups	[edi+32],	xmm2
		movups	[edi+48],	xmm3
		movups	[edi+64],	xmm4
		movups	[edi+80],	xmm5
		movups	[edi+96],	xmm6
		movups	[edi+112],	xmm7

		add		esi,		eax
		add		edi,		eax
		dec		ecx

		jnz		_sse_copy
_sse_copy_end:
		pop esi
		pop edi
	}
	return 0;
}

//2006 08 30 
//by kiok ahn, mmx copy
//밴치 결과 sse, sse2 등 한번에 복사 되는 메모리 크기가 커진다고 해서 빨라지지 않음.
//sse도 결국 mmx와 비슷한 결과를 낸다.
//따라서 fast copy는 mmx만으로도 충분.
void* memcpyMMX(void *dest, const void *src, size_t nbytes)
{
	__asm
	{
		mov		edi,		dest
		mov		esi,		src
		mov		ecx,		nbytes
		push	ecx
		
		// align 64 byte, 63byte 아하 크기에 대한 처리
		and		ecx,		63
		rep		movsb
		pop		ecx
		shr		ecx,		6
		cmp		ecx,		0
		je		_mmx_copy_end
			
_mmx_copy:
		
		movq	mm0,		[esi+0]
		movq	mm1,		[esi+8]
		movntq	[edi+0],	mm0
		movntq	[edi+8],	mm1
		movq	mm2,		[esi+16]
		movq	mm3,		[esi+24]
		movntq	[edi+16],	mm2
		movntq	[edi+24],	mm3
		movq	mm0,		[esi+32]
		movq	mm1,		[esi+40]
		movntq	[edi+32],	mm0
		movntq	[edi+40],	mm1
		movq	mm2,		[esi+48]
		movq	mm3,		[esi+56]
		movntq	[edi+48],	mm2
		movntq	[edi+56],	mm3
		
		add		esi,		64
		add		edi,		64
		dec		ecx
		jnz		_mmx_copy
			
_mmx_copy_end:
		emms
	}
	return 0;
}


//2006 09 05 
//by kiok ahn, mmx zero momory
//bench 1024*1024*16*10 
//memset -> 17.7ms
//this   ->  5.9ms 
void	*memzeroMMX(void *dts, size_t nbytes)
{
	__asm
	{
		xor     eax,        eax//make 0, eax
		mov		edi,		dts
		mov		ecx,		nbytes
		push	ecx
		
		// align 64 byte, 63byte 아하 크기에 대한 처리
		and		ecx,		63
		rep		stosb
		pop		ecx
		shr		ecx,		6
		cmp		ecx,		0
		je		_mmx_zero_end


		pxor	mm0,		mm0//make 0, mm0
_mmx_zero:
		movntq	[edi+0],	mm0
		movntq	[edi+8],	mm0
		movntq	[edi+16],	mm0
		movntq	[edi+24],	mm0
		movntq	[edi+32],	mm0
		movntq	[edi+40],	mm0
		movntq	[edi+48],	mm0
		movntq	[edi+56],	mm0
		
		add		esi,		64
		add		edi,		64
		dec		ecx
		jnz		_mmx_zero
			
_mmx_zero_end:
		emms
	}

	return 0;
}

#endif


