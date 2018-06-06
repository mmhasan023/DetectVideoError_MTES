#include "./../include/iplApi.h"
#include "omp_thread.h"

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif


void iplEdgeVertical_2x1( const LPBYTE lpSrcGray, LPBYTE lpDst, const INT& nWidth, const INT& nHeight, const INT& nSize )
{
	int x=0,y=0;
	BYTE* pSrcIter = lpSrcGray;
	BYTE* pDstIter = lpDst    ;

#ifdef _OPENMP
	int nPos = 0;
//	iplmemzero( pDstIter, sizeof(BYTE)*nWidth );

#pragma omp parallel for private(nPos,x,pSrcIter,pDstIter) num_threads( g_nIplNumberOfThreasds )
	for( y=0 ; y<nHeight ; y++ )
	{

		nPos         = y*nWidth;
		pSrcIter  = lpSrcGray + nPos;
		pDstIter  = lpDst     + nPos;
		*pDstIter = 0;

		pSrcIter++;
		pDstIter++;

		for( x=1; x<nWidth ; x++ )
		{
			*pDstIter = abs( *pSrcIter - *(pSrcIter-1))  ;

			pSrcIter++;
			pDstIter++;
		}
	}
#else
	for( y=0 ; y<nHeight ; y++ )
	{
		*pDstIter = 0;
		pSrcIter++;
		pDstIter++;

		for( x=1; x<nWidth ; x++ )
		{
			*pDstIter = abs( *pSrcIter - *(pSrcIter-1))  ;

			pSrcIter++;
			pDstIter++;
		}
	}
#endif
}

void iplEdgeHorizontal_1x2( const LPBYTE lpSrcGray, LPBYTE lpDst, const INT& nWidth, const INT& nHeight, const INT& nSize )
{
	int x=0,y=0;
	BYTE* pSrcIterUp  = lpSrcGray       ;
	BYTE* pSrcIterCur = lpSrcGray+nWidth;
	BYTE* pDstIter    = lpDst    +nWidth;
	iplmemzero( lpDst, sizeof(BYTE)*nWidth );

#ifdef _OPENMP
	int nPos = 0;
#pragma omp parallel for private(nPos,x,pSrcIterUp,pSrcIterCur,pDstIter) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeight ; y++ )
	{
		nPos         = y*nWidth;
		pSrcIterUp   = lpSrcGray  + nPos  ;
		pSrcIterCur  = pSrcIterUp + nWidth;
		pDstIter     = lpDst     + nPos;

		for( x=0; x<nWidth ; x++ )
		{
			*pDstIter = abs( *pSrcIterCur - *pSrcIterUp );

			pSrcIterUp ++;
			pSrcIterCur++;
			pDstIter   ++;
		}
	}
#else
	for( y=1 ; y<nHeight ; y++ )
	{
		for( x=0; x<nWidth ; x++ )
		{
			*pDstIter = abs( *pSrcIterCur - *pSrcIterUp );

			pSrcIterUp ++;
			pSrcIterCur++;
			pDstIter   ++;
		}
	}
#endif
}
