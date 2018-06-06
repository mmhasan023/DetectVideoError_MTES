//by Kiok ahn
//12bit의 bin크기를 가지는 RGB 히스토그램
#ifndef _HISTOGRAM_RGB_12Bit_BIN_H_INCLUDE_
#define _HISTOGRAM_RGB_12Bit_BIN_H_INCLUDE_

#include "iplDefine.h"

#define HIST_COLOR_COMPONENT_COUNT		3		/* RGB */
#define HIST_COMPONENT_BIT_SIZE			4
#define HIST_COMPONENT_SHIFT_BIT		(8 - HIST_COMPONENT_BIT_SIZE)
#define HIST_COMPONENT_SIZE				(1 << HIST_COMPONENT_BIT_SIZE)
#define HIST_BIN_COUNT					(1 << (HIST_COMPONENT_BIT_SIZE * HIST_COLOR_COMPONENT_COUNT))

#ifdef _OPENMP
#include <omp.h>
#endif

class CHistoRGB12bitBin
{
public:
	CHistoRGB12bitBin();
	CHistoRGB12bitBin(const CHistoRGB12bitBin & obj);
	virtual ~CHistoRGB12bitBin();

public:
	UINT	m_nHist[HIST_BIN_COUNT];

public:
	// 히스토그램사이 거리 계산
	UINT  Distance(CHistoRGB12bitBin * pOther);

	// RGB비트맵자료로부터 Histogram 을 계산한다.
	void  CalcHistFromBitmap   ( LPBYTE pByte, LPBITMAPINFOHEADER pBih );
	void  CalcHistFromBitmapRGB( LPBYTE pByte, LPBITMAPINFOHEADER pBih 
#ifdef _OPENMP
//											  ,omp_lock_t*   pLck=NULL
#endif
		);

	void  CalcHistFromBitmap   ( LPBYTE pByte, DWORD dwWidth, DWORD dwHeight, DWORD dwBitCount );
	UINT  GetBinCount          ( void ){return HIST_BIN_COUNT;};
	UINT* GetBinData           ( void ){return m_nHist;       };

public:
	virtual void operator= (const CHistoRGB12bitBin & op);

public:
	// 히스토그램간 유사도를 계산한다.
	UINT Similarity(CHistoRGB12bitBin* pOther);
};

#endif//_HISTOGRAM_RGB_12Bit_BIN_H_INCLUDE_