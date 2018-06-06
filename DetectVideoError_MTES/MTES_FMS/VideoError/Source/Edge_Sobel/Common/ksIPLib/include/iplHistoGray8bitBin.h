//iplHistoGray8bitBin.h
//by Kiok ahn
//
//8bit의 bin크기를 가지는 Gray 히스토그램
#ifndef _HISTOGRAM_GRAY_8Bit_BIN_H_INCLUDE_
#define _HISTOGRAM_GRAY_8Bit_BIN_H_INCLUDE_

#include "iplDefine.h"

#define HIST_GRAY_8BIT_BIN_SIZE	 0xFF

#ifdef _OPENMP
#include <omp.h>
#endif

class CHistoGray8bitBin
{
public:
	CHistoGray8bitBin();
	CHistoGray8bitBin(const CHistoGray8bitBin & obj);
	virtual ~CHistoGray8bitBin();

public:
	UINT*	m_pHist                ;
	UINT    m_nBinSize             ;

public:
	// 히스토그램사이 거리 계산
	UINT  Distance        ( CHistoGray8bitBin * pOther);
	void  CalcHistFromBuf ( LPBYTE pGrayBuf, const int& nSize);
	UINT  GetBinCount     ( void ){return m_nBinSize;}
	UINT* GetBinData      ( void ){return m_pHist   ;};

public:
	virtual void operator= (const CHistoGray8bitBin & op);

public:
	// 히스토그램간 유사도를 계산.
	UINT Similarity(CHistoGray8bitBin* pOther);
};

#endif//_HISTOGRAM_GRAY_8Bit_BIN_H_INCLUDE_