#ifndef _MC_IPL_DEFINITION_H_INCLUDE_
#define _MC_IPL_DEFINITION_H_INCLUDE_

#ifdef _OPENMP
#include <omp.h>
#endif

#if defined(_IPL_API_EXPORT)
#define _IPL_API __declspec(dllexport)
#elif defined(_MSC_VER)&&(_MSC_VER<1200)
#define _IPL_API __declspec(dllimport)
#else
#define _IPL_API 
#endif

#if defined(CALL_CDECL)
#define _IPL_CALL 
#else
#define _IPL_CALL __stdcall
#endif


#define          ipl_PI                3.14159265f//3.1415926535897932384626433832795
#define          ipl_PIBY2_FLOAT       1.5707963f

const   float    ipl_RADIANS2DEGREES = 180.0f/ipl_PI;
const   float    ipl_DEGREES2RADIANS = ipl_PI/180.0f;

#define TO_RADIAN(degree)    ((degree)*ipl_DEGREES2RADIANS)
#define TO_DEGREE(radian)    ((radian)*ipl_RADIANS2DEGREES)

#define THRESOLD_VARIENCE_WEIGHT		1
#define THRESOLD_VARIENCE				0.1
#define THRESOLD_SHOT_INTERVAL			5
#define THRESOLD_ATTRATION_RATIO		1

//REFERENCE_TIME
//100 nanoseconds,100*10^(-9)
//10(-7) = 0.0000001
//10000000
#define UINT_REFERENCE_TIME              10000000


#define MAX_MACRO_BLOCK_SIZE             64


#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef far
#define far
#endif

#ifndef near
#define near
#endif

#ifndef FAR
#define FAR                 far
#endif

#ifndef NEAR
#define NEAR                near
#endif

#ifndef CONST
#define CONST               const
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#define INVALID_DATA_VALUE  0xFFFFFFFF

#ifndef BOOL
typedef int                 BOOL;
#endif

#ifndef WORD
typedef unsigned short      WORD, *LPWORD;
#endif

#ifndef FLOAT
typedef float               FLOAT, *LPFLOAT;
#endif

#ifndef INT
typedef int                 INT, *LPINT;
#endif

#ifndef UINT
typedef unsigned int        UINT, *LPUINT;
#endif

#ifndef BYTE
typedef unsigned char       BYTE, *LPBYTE;
#endif

#ifndef LONG
typedef long                LONG, *LPLONG;
#endif

#ifndef DWORD
typedef unsigned long       DWORD, *LPDWORD;
#endif

#ifndef VOID
typedef void                VOID, *LPVOID;
#endif

#ifndef LONGLONG
typedef __int64             LONGLONG;
#endif

#ifndef REFERENCE_TIME
typedef LONGLONG            REFERENCE_TIME;
#endif

#ifndef DOUBLE
typedef double DOUBLE;
#endif

#ifdef _LIB
typedef struct tagBITMAPINFOHEADER{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


enum eSCAN_DIRECTION { _eHORIZONTAL, _eVERTICAL, _eBOTH };
enum eDETEC_DIRECTION{ _eDETEC_NONE, _eDETEC_SMALL, _eDETEC_LARGE, _eDETEC_BOTH };
//enum { IPL1D_NONE, IPL1D_DETECT, IPL1D_SMALL, IPL1D_CONTINUE };
enum { IPL1D_NONE, IPL1D_DETECT, IPL1D_SMALL, IPL1D_CONTINUE, IPL1D_DETECT_LOW, IPL1D_DETECT_HIGH };
//IPL1D_FAIL      : 변화없음.
//IPL1D_DETECT    : Edge 검출.
//IPL1D_SMALL     : 현재 신호가 지정 크기 보다 작음.
//IPL1D_CONTINUE  : 계속 진행.


typedef struct iplPOINT
{
	LONG  x;
	LONG  y;
} IPLPOINT, *LPIPLPOINT;

typedef struct iplPOINTLABEL
{
	LONG  x     ;
	LONG  y     ;
	INT   nLabel ;
} IPLPOINTLABEL, *LPIPLPOINTLABEL;

typedef struct iplFPOINT
{
	float  x;
	float  y;
} IPLFPOINT, *LPIPLFPOINT;

typedef struct iplSIZE
{
	LONG        cx;
	LONG        cy;
} IPLSIZE, *LPIPLSIZE;

typedef struct iplRECT
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} IPLRECT, *LPIPLRECT;

typedef const IPLRECT* LPCIPLRECT;    // pointer to read/only RECT


typedef struct iplLINE
{
	iplPOINT p1;
	iplPOINT p2;
} IPLLINE, *LPIPLLINE;



//ipl_ApplyFilters3x3Gray() flags
#define _IPL_FILTER_ALL         0xFFFFFFFF
#define _IPL_FILTER_LOWPASS     0x00000001
#define _IPL_FILTER_SOBEL_MAG   0x00000002
#define _IPL_FILTER_SOBEL_PHASE 0x00000004
typedef struct iplFilterResult
{
	LPBYTE lpLowPass       ;
	LPBYTE lpSobelMagnitude;
	LPWORD lpSobelPhase    ;
}IPLFILTERRESULT,*LPIPLFILTERRESULT;


typedef struct tagCornerDetect
{
	int        nWidth           ;
	int        nHeight          ;
	int        nBarrier         ;
	int	       arPointer_dir[16];
	int*       nRow_start       ;//= new int[nHeight];
//	int*       nScores          ;//= new int[numcorners];
	int	       nRsize           ;//= 512 
	IPLPOINT*  pRet             ;//= new IPLPOINT[rsize];

#ifdef _OPENMP
//	omp_lock_t lck              ;//OPEN MP 사용시 검출되는 코너 수가 1.5배가량 많아짐
#endif

	int*      pScores           ;

}CORNERDETECT, *LPCORNERDETECT;

typedef VOID* HCORNERDETECT;



/////////////////////////////////////////////////////////////////////////////////////////////////
//Video Common Processing Flag
#define IPL_VCM_GRAY            0x00000001
#define IPL_VCM_HISTO12RGB      0x00000002
#define IPL_VCM_HISTO8GRAY      0x00000004
#define IPL_VCM_3X3LOWPASS      0x00000008

#define IPL_VCM_GRAY_DPN        0x00000009//연산에 대한 의존성을 고려한 Flag (IPL_VCM_GRAY | IPL_VCM_3X3LOWPASS)
                                          //IPL_VCM_3X3LOWPASS는 전처리로서 IPL_VCM_GRAY를 필요로 한다.
#define IPL_VCM_FULL            0xFFFFFFFF
//Video Common Processing Flag
/////////////////////////////////////////////////////////////////////////////////////////////////




#ifdef _LOGDATA
#include <stdio.h>
#include <stdarg.h>
#include "tchar.h"
extern TCHAR g_szKsIplLogPath[256];
int _IPL_API _IPL_CALL ipl_SetLogPath          (IN const TCHAR* lpPath);
#endif

#endif//_MC_IPL_DEFINITION_H_INCLUDE_
