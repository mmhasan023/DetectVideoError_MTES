//#if defined(WIN32)
//#include "stdafx.h"
//#endif

#include "./../include/iplApi.h"
#include "./../include/iplMemory.h"
#include <math.h>
#include "omp_thread.h"

#include "xmmintrin.h"
//#include "./../include/AMaths.h"


#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif


//오류가 있으므로 누적하여 사용하면 오차가 누적되어 치명적인 에러를 발생시킬 수도 있음.
float fast_atan2f( float y, float x )
{
	return 0.0f;
	if ( x == 0.0f )
	{
		if ( y > 0.0f ) return ipl_PIBY2_FLOAT;
		if ( y == 0.0f ) return 0.0f;
		return -ipl_PIBY2_FLOAT;
	}
	float atan;
	float z = y/x;
	if ( fabsf( z ) < 1.0f )
	{
		atan = z/(1.0f + 0.28f*z*z);
		if ( x < 0.0f )
		{
			if ( y < 0.0f ) return atan - ipl_PI;
			return atan + ipl_PI;
		}
	}
	else
	{
		atan = ipl_PIBY2_FLOAT - z/(z*z + 0.28f);
		if ( y < 0.0f ) return atan - ipl_PIBY2_FLOAT;
	}
	return atan;
}

int ipl_ApplyFilters3x3Gray(IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, IN DWORD dwFilterFlag, OUT LPIPLFILTERRESULT lpResult )
{
	int    nHeightScan = nHeight-1;
	int    nWidthScan  = nWidth -1;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	register int     x,y;

	int     nGyValue;   
	int     nGxValue; 
	int     nValue;
//	float   fValue;


	BOOL bLOWPASS     = FALSE;
	BOOL bSOBEL_MAG   = FALSE;
	BOOL bSOBEL_PHASE = FALSE;
	if( dwFilterFlag&_IPL_FILTER_LOWPASS      ) bLOWPASS     = TRUE;
	if( dwFilterFlag&_IPL_FILTER_SOBEL_MAG    ) bSOBEL_MAG   = TRUE;
	if( dwFilterFlag&_IPL_FILTER_SOBEL_PHASE  ) bSOBEL_PHASE = TRUE;


	LPBYTE  lpDstLowPass    = lpResult->lpLowPass        + nWidth;
	LPBYTE  lpDstSobelMag   = lpResult->lpSobelMagnitude + nWidth;
	LPWORD  lpDstSobelPhase = lpResult->lpSobelPhase     + nWidth;

#ifdef _OPENMP
#pragma omp parallel for private(lpDstLowPass,lpDstSobelMag,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nValue) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nWidth);
		lpSrcUp = lpSrc - nWidth;
		lpSrcDn = lpSrc + nWidth;
		lpDstLowPass       = lpResult->lpLowPass         + (y*nWidth);
		lpDstSobelMag      = lpResult->lpSobelMagnitude  + (y*nWidth);
		//lpDstSobelPhase  = lpResult->lpSobelPhase      + (y*nWidth);

		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

//			if( bLOWPASS )
//			{
				nValue =(int)((WN+NN+NE+WW+CC+EE+SW+SS+ES)/9) ;
				if(nValue>255)nValue=255;
				*lpDstLowPass++ = (BYTE)(nValue);
//			}

			nGyValue = WN+NN+NN+NE-SW-SS-SS-ES;
			nGxValue = WN-NE+WW+WW-EE-EE+SW-ES;
//			if( bSOBEL_MAG )
//			{
				nValue = abs(nGyValue) + abs(nGxValue);
				if(nValue>255)nValue=255;
				*lpDstSobelMag++ = (BYTE)(nValue);
//			}

/*			if( bSOBEL_PHASE )
			{
				fValue = fast_atan2f((float)nGyValue,(float)nGxValue)*ipl_RADIANS2DEGREES;
				if(fValue>255)fValue=255;
				*lpDstSobelPhase++ = (BYTE)(fValue);
			}
*/
			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}

#else
//	lpDstLowPass   = lpResult->lpLowPass  ;
//	lpDstSobelMag  = lpResult->lpSobelMagnitude;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpDstLowPass++;lpDstSobelMag++;//lpDstSobelPhase++;
		for( x=1; x<nWidthScan ; x++ )
		{
			lpSrc   = pSrc  + (y*nWidth) + x;
			lpSrcUp = lpSrc - nWidth + x;
			lpSrcDn = lpSrc + nWidth + x;
//			lpDstLowPass   = lpResult->lpLowPass  + (y*nWidth) + x;
//			lpDstSobelMag  = lpResult->lpSobelMagnitude +(y*nWidth) + x;

			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			/////////////////////////////////////////////////////////////////////////
			//low pass filter
//			if( bLOWPASS )
//			{
				nValue =(int)((WN+NN+NE+WW+CC+EE+SW+SS+ES)/9) ;
				if(nValue>255)nValue=255;
				*lpDstLowPass++ = (BYTE)(nValue);
//			}
			//low pass filter
			/////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////
			//sobel edge detector
			nGyValue = WN+NN+NN+NE-SW-SS-SS-ES;
			nGxValue = WN-NE+WW+WW-EE-EE+SW-ES;
//			if( bSOBEL_MAG )
//			{
				nValue = abs(nGyValue) + abs(nGxValue);
				if(nValue>255)nValue=255;
				*lpDstSobelMag++ = (BYTE)(nValue);
//			}
/*
			if( bSOBEL_PHASE )
			{
				fValue = fast_atan2f((float)nGyValue,(float)nGxValue)*ipl_RADIANS2DEGREES;
				if(fValue>255)fValue=255;
				*lpDstSobelPhase++ = (BYTE)(fValue);
			}
*/
			//sobel edge detector
			/////////////////////////////////////////////////////////////////////////

		}
		lpDstLowPass++;lpDstSobelMag++;//lpDstSobelPhase++;
	}

#endif

	return 0;

}

int iplGetDifferCountGray(IN const LPBYTE lpBuf1, IN const LPBYTE lpBuf2, IN int nWidth, IN int nHeight, IN int nNoiseLevel)
{
	LPBYTE lpCur          = lpBuf1;
	LPBYTE lpBefore       = lpBuf2;
	int    nDiffCount     = 0;
	BYTE   byteResult     = 0;
	BYTE   byteTmpCur     = 0;
	BYTE   byteTmpBefore  = 0;
/*
#ifdef _OPENMP
	//4core 2.33GHz cpu : 1.42ms
	register int    x,y;
	register int nPos;
	register int iHeight = nHeight;
	register int iWidth  = nWidth ;
	omp_lock_t lck;
	omp_init_lock(&lck);

#pragma omp parallel for private(x,y,nPos,lpCur,lpBefore,byteResult)
	for( y=0 ; y<iHeight ; y++ )
	{
		nPos      = y*iWidth;
		lpCur     = lpBuf1 + nPos;
		lpBefore  = lpBuf2 + nPos;

		for( x=0; x<iWidth ; x++ )
		{
			byteResult = (abs(*lpCur++ - *lpBefore++))>>nNoiseLevel;
			if(byteResult) 
			{
				omp_set_lock(&lck);
				nDiffCount++;
				omp_unset_lock(&lck);
			}
		}
	}

	omp_destroy_lock(&lck);
#else
*/
	//3.78ms
	int    nSize    = nWidth*nHeight;
	LPBYTE lpEnd    = lpBuf1 + nSize;

	for( ; lpCur<lpEnd ; lpCur++,lpBefore++ )
	{
		byteTmpCur    = *lpCur   ;
		byteTmpBefore = *lpBefore;

		byteResult = (abs(byteTmpCur-byteTmpBefore))>>nNoiseLevel;
		if(byteResult) 
			nDiffCount++;
	}
//#endif

	return nDiffCount;
}

int ipl_BlockCornerFilter(IN LPVECTOR_POINT vInPoints, OUT LPVECTOR_POINT vOutPoints, IN int nFilterSize, eSCAN_DIRECTION eDir)
{
//	int nRange = 0;

	VECTOR_POINTItor itor     = vInPoints->begin();

	VECTOR_POINTItor itorScan    ;

	//loop 
	int X,Y;
	int nScanX, nScanY;
	int nAllowableStartX = 0; 
	int nAllowableStartY = 0;
	int nAllowableEndX   = 0;
	int nAllowableEndY   = 0;

	int nCount = 0;

	switch( eDir )
	{
	case _eBOTH:
		{
			while( itor != vInPoints->end() )
			{
				LPIPLPOINT lpPoint = &(*itor);

				X = lpPoint->x;
				Y = lpPoint->y;
				nAllowableStartX = X - nFilterSize; 
				if(nAllowableStartX<0)nAllowableStartX=0;
				nAllowableStartY = Y - nFilterSize;
				if(nAllowableStartY<0)nAllowableStartY=0;
				nAllowableEndX = X + nFilterSize;
				nAllowableEndY = Y + nFilterSize;

				nCount = 0;
				itorScan = vInPoints->begin();
				while( itorScan != vInPoints->end() )
				{
					LPIPLPOINT lpScanPoint = &(*itorScan);

					nScanX = lpScanPoint->x;
					nScanY = lpScanPoint->y;
					
					if     ( nScanX == X                && nScanY == Y                ) {itorScan++; continue;}
					else if( nScanX <  nAllowableStartX || nScanY <  nAllowableStartY ) {itorScan++; continue;}
					else if( nScanX >  nAllowableEndX   && nScanY >  nAllowableEndY   ) {            break   ;} 
					else if( nScanX >  nAllowableEndX   || nScanY >  nAllowableEndY   ) {itorScan++; continue;}

					//if( X-nRange<=nScanX && nScanX<=X+nRange || //need range
					//	Y-nRange<=nScanY && nScanY<=Y+nRange  )
					else if( X==nScanX || Y==nScanY )
					{
						nCount++;
						vOutPoints->push_back(*lpScanPoint);
						itorScan = vInPoints->erase(itorScan);
					}
					else
						itorScan++;
				}

				if( nCount )
					vOutPoints->push_back(*itor);

				itor = vInPoints->erase(itor);
			}
		}
		break;
	case _eHORIZONTAL:
		{
			while( itor != vInPoints->end() )
			{
				LPIPLPOINT lpPoint = &(*itor);

				X = lpPoint->x;
				Y = lpPoint->y;
				nAllowableStartX = X - nFilterSize; 
				if(nAllowableStartX<0)nAllowableStartX=0;
				nAllowableStartY = Y - nFilterSize;
				if(nAllowableStartY<0)nAllowableStartY=0;
				nAllowableEndX = X + nFilterSize;
				nAllowableEndY = Y + nFilterSize;

				nCount = 0;
				itorScan = vInPoints->begin();
				while( itorScan != vInPoints->end() )
				{
					LPIPLPOINT lpScanPoint = &(*itorScan);

					nScanX = lpScanPoint->x;
					nScanY = lpScanPoint->y;
					
					if     ( nScanX == X                && nScanY == Y                ) {itorScan++; continue;}
					else if( nScanX <  nAllowableStartX || nScanY <  nAllowableStartY ) {itorScan++; continue;}
					else if( nScanX >  nAllowableEndX   && nScanY >  nAllowableEndY   ) {            break   ;} 
					else if( nScanX >  nAllowableEndX   || nScanY >  nAllowableEndY   ) {itorScan++; continue;}

					//if( X-nRange<=nScanX && nScanX<=X+nRange || //need range
					//	Y-nRange<=nScanY && nScanY<=Y+nRange  )
					else if( Y==nScanY )
					{
						nCount++;
						vOutPoints->push_back(*lpScanPoint);
						itorScan = vInPoints->erase(itorScan);
					}
					else
						itorScan++;
				}

				if( nCount )
					vOutPoints->push_back(*itor);

				itor = vInPoints->erase(itor);
			}
		}
		break;
	case _eVERTICAL:
		{
			while( itor != vInPoints->end() )
			{
				LPIPLPOINT lpPoint = &(*itor);

				X = lpPoint->x;
				Y = lpPoint->y;
				nAllowableStartX = X - nFilterSize; 
				if(nAllowableStartX<0)nAllowableStartX=0;
				nAllowableStartY = Y - nFilterSize;
				if(nAllowableStartY<0)nAllowableStartY=0;
				nAllowableEndX = X + nFilterSize;
				nAllowableEndY = Y + nFilterSize;

				nCount = 0;
				itorScan = vInPoints->begin();
				while( itorScan != vInPoints->end() )
				{
					LPIPLPOINT lpScanPoint = &(*itorScan);

					nScanX = lpScanPoint->x;
					nScanY = lpScanPoint->y;
					
					if     ( nScanX == X                && nScanY == Y                ) {itorScan++; continue;}
					else if( nScanX <  nAllowableStartX || nScanY <  nAllowableStartY ) {itorScan++; continue;}
					else if( nScanX >  nAllowableEndX   && nScanY >  nAllowableEndY   ) {            break   ;} 
					else if( nScanX >  nAllowableEndX   || nScanY >  nAllowableEndY   ) {itorScan++; continue;}

					//if( X-nRange<=nScanX && nScanX<=X+nRange || //need range
					//	Y-nRange<=nScanY && nScanY<=Y+nRange  )
					else if( X==nScanX )
					{
						nCount++;
						vOutPoints->push_back(*lpScanPoint);
						itorScan = vInPoints->erase(itorScan);
					}
					else
						itorScan++;
				}

				if( nCount )
					vOutPoints->push_back(*itor);

				itor = vInPoints->erase(itor);
			}
		}
		break;

	}
	return 0;
}

int iplImageSubtraction( IN const LPBYTE pSrc1, IN const LPBYTE pSrc2, OUT LPBYTE pDst, INT nSize, const INT& nWidth, const INT& nHeight )
{
	int x=0,y=0;

	register LPBYTE lpSrc1   = pSrc1;
	register LPBYTE lpSrc2   = pSrc2;
	register LPBYTE lpDst    = pDst ;

#ifdef _OPENMP
	int nPos = 0;
#pragma omp parallel for private(nPos,x,lpDst,lpSrc1,lpSrc2) num_threads( g_nIplNumberOfThreasds )
	for( y=0 ; y<nHeight ; y++ )
	{
		nPos    = y*nWidth;
		lpSrc1  = pSrc1 + nPos;
		lpSrc2  = pSrc2 + nPos;
		lpDst   = pDst  + nPos;
		for( x=0; x<nWidth ; x++ )
		{
			*lpDst = (BYTE)( abs( (int)(*lpSrc1) - (int)(*lpSrc2) ) );

			lpSrc1++;lpSrc2++;lpDst++;
		}
	}
#else
	for( y=0 ; y<nHeight ; y++ )
	{
		for( x=0; x<nWidth ; x++ )
		{
			*lpDst = (BYTE)( abs( (int)(*lpSrc1) - (int)(*lpSrc2) ) );

			lpSrc1++;lpSrc2++;lpDst++;
		}
	}
#endif

	return 1;
}

int iplImageBitAnd( IN const LPBYTE pSrc1, IN const LPBYTE pSrc2, OUT LPBYTE lpDst, INT nSize, const INT& nWidth, const INT& nHeight )
{
	BYTE* pSubt01Itor = pSrc1;
	BYTE* pSubt12Itor = pSrc2;
	BYTE* pAnd012Itor = lpDst;

#ifdef _OPENMP
	int x=0,y=0;
	int nPos = 0;
#pragma omp parallel for private(nPos,x,pSubt01Itor,pSubt12Itor,pAnd012Itor) num_threads( g_nIplNumberOfThreasds )
	for( y=0 ; y<nHeight ; y++ )
	{
		nPos         = y*nWidth;
		pSubt01Itor  = pSrc1 + nPos;
		pSubt12Itor  = pSrc2 + nPos;
		pAnd012Itor  = lpDst + nPos;
		for( x=0; x<nWidth ; x++ )
		{
			*pAnd012Itor = (*pSubt12Itor) & (*pSubt01Itor) ;

			pSubt01Itor++;
			pSubt12Itor++;
			pAnd012Itor++;
		}
	}
#else
	BYTE* pSubtEnd    = pSrc1 + nSize;

	while( pSubt01Itor<pSubtEnd ) 
	{
		*pAnd012Itor = (*pSubt12Itor) & (*pSubt01Itor) ;

		pSubt01Itor++;
		pSubt12Itor++;
		pAnd012Itor++;
	}
#endif

	return 1;
}

