//#if defined(WIN32)
//#include "stdafx.h"
//#endif

#include "iplDefine.h"
#include "edge_sobel.h"
//#include ".iplMemory.h"
#include <math.h>
#include "omp_thread.h"
#include "DegreeIndex.h"

#include "xmmintrin.h"

//#ifdef _DEBUG
//#include "mem_trace.h"
//#define new DBG_NEW
//#endif

//#include "./../include/AMaths.h"

/*
int ipl_FilterSobelMagnitude3x3Gray(IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT LPBYTE pDst )
{
//	register unsigned int nHeightScan = nHeight-1;
//	register unsigned int nWidthScan  = nWidth -1;
	unsigned int fnWidth, fnHeight;
	register unsigned int fnRow, fnCol, fnSum, fnLocOne, fnLocTwo;

	int nGxValue, nGyValue;

	nGxValue = nGyValue = fnSum = fnLocOne = fnLocTwo = 0;
	fnWidth = nWidth; fnHeight = nHeight;

//	LPBYTE lpDst = pDst+fnWidth;

	for(fnRow=1; fnRow<fnHeight-1; fnRow++)
	{
//		lpDst++;
		for(fnCol=1; fnCol<fnWidth-1;  fnCol++)
		{

			fnLocOne = (fnWidth*fnRow + (fnCol+1));
			fnLocTwo = fnLocOne - 2;

			nGxValue = ( *(pSrc+(fnLocOne - fnWidth)) + 
				*(pSrc+(fnLocOne)) + 
				*(pSrc+(fnLocOne)) + 
				*(pSrc+(fnLocOne + fnWidth)) ) - 

				( *(pSrc+(fnLocTwo - fnWidth)) + 
				*(pSrc+(fnLocTwo)) + 
				*(pSrc+(fnLocTwo)) + 
				*(pSrc+(fnLocTwo + fnWidth)) ); 


			fnLocOne = (fnWidth*(fnRow-1) + fnCol);
			fnLocTwo = fnLocOne + (fnWidth*2);

			// Sobel_Filter Masking 
			nGyValue = ( *(pSrc+(fnLocOne-1)) + 
				*(pSrc+fnLocOne) + 
				*(pSrc+fnLocOne) + 
				*(pSrc+(fnLocOne+1)) ) - 

				( *(pSrc+(fnLocTwo-1)) + 
				*(pSrc+fnLocTwo) + 
				*(pSrc+fnLocTwo) + 
				*(pSrc+(fnLocTwo+1)) ); 


			// Sobel_Filter Masking 
			fnSum=abs(nGxValue)+abs(nGyValue);
			if(fnSum>255)fnSum=255; // White Value 

			*(pDst+((fnRow*fnWidth) + fnCol)) = fnSum;
//			*lpDst++ = fnSum;

			nGxValue=nGyValue=fnSum=0;
		}
//		lpDst++;
	}

	return 0;
}
*/

//max 31ms : single core 3.0GHz PC
int ipl_FilterSobelMagnitude3x3Gray(IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pDst )
{
	register int    nHeight = nSrcHeight;
	register int    nWidth  = nSrcWidth ;
	register int    x,y;

	LPBYTE lpDst   = pDst + nWidth;

	LPBYTE lpSrc   = pSrc;
	LPBYTE lpSrcUp = NULL;
	LPBYTE lpSrcDn = NULL;

	register BYTE    WN, NN, NE;
	register BYTE    WW, CC, EE;
	register BYTE    SW, SS, ES; 
	register int     fGyValue;   
	register int     fGxValue; 
	int              fsmValue;

#ifdef _OPENMP
	int              nPos;

#pragma omp parallel for private(nPos,x,lpDst,lpSrc,lpSrcUp,lpSrcDn, WN,\
	NN, NE,WW, CC, EE, SW, SS, ES, fsmValue) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeight-1 ; y++ )
	{
		nPos    = y*nWidth + 1;
		lpSrc   = pSrc  + nPos;
		lpSrcUp = lpSrc - nWidth;
		lpSrcDn = lpSrc + nWidth;
		lpDst   = pDst  + nPos;

		for( x=1; x<nWidth-1 ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			fGyValue =   WN  + NN+NN  +    NE 
				       - SW  -(SS+SS) -    ES;

			fGxValue =    WN  -     NE 
				     +(WW+WW) - (EE+EE)  
				     +    SW  -     ES;

			fsmValue = abs(fGyValue) + abs(fGxValue);
			//fsmValue = sqrt( fGyValue*fGyValue + fGxValue*fGxValue ) + 0.5f;

			if(fsmValue>255)fsmValue=255;
			*lpDst++ = (BYTE)(fsmValue);
			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc          ;
	lpSrc   = pSrc  + nWidth;
	lpSrcDn = lpSrc + nWidth;
	for( y=1 ; y<nHeight-1 ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDst++;
		for( x=1; x<nWidth-1 ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

//			fGyValue =   WN  + NN+NN  +    NE 
//				       - SW  -(SS+SS) -    ES;
//			fGxValue =    WN  -     NE 
//				     +(WW+WW) - (EE+EE)  
//				     +    SW  -     ES;

			fGyValue = WN+NN+NN+NE-SW-SS-SS-ES;
			fGxValue = WN+WW+WW+SW-NE-EE-EE-ES;

			fsmValue = abs(fGyValue) + abs(fGxValue);

			if(fsmValue>255)fsmValue=255;
			*lpDst++ = (BYTE)(fsmValue);
			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDst++;
	}

#endif
	return 0;
}


int ipl_FilterSobelPhase3x3Gray(IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPWORD pDst )
{
	int    nHeightScan = nSrcHeight-1;
	int    nWidthScan  = nSrcWidth -1;
	register LPWORD lpDst   = pDst + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     fGyValue;
	int     fGxValue;
	float   fsdValue;
	register int     x,y;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDst,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, fsdValue) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDst   = pDst  + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			fGyValue =     WN  + (NN+NN) +    NE 
				      //(0*WW) + ( 0*CC) + (0*EE)  
				         - SW  - (SS+SS) -    ES;

			fGxValue =      WN /*+ (0*NN)*/ -     NE 
				       +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
				       +    SW /*+ (0*SS)*/ -     ES;

			fsdValue = atan((float)fGyValue/(float)fGxValue)*ipl_RADIANS2DEGREES;
			if(fsdValue<0) fsdValue = 360.0f-fsdValue;
			while(fsdValue>360)fsdValue-=360;
			*lpDst++ = (WORD)(fsdValue + 0.5f);

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDst++;
		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			fGyValue =     WN  + (NN+NN) +    NE 
					  //(0*WW) + ( 0*CC) + (0*EE)  
				         - SW  - (SS+SS) -    ES;

			fGxValue =      WN /*+ (0*NN)*/ -     NE 
				       +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
				       +    SW /*+ (0*SS)*/ -     ES;

			fsdValue = fast_atan2f((float)fGyValue,(float)fGxValue)*ipl_RADIANS2DEGREES;
			fsdValue = atan((float)fGyValue/(float)fGxValue)*ipl_RADIANS2DEGREES;
			if(fsdValue<0) fsdValue = 360.0f-fsdValue;
			while(fsdValue>360)fsdValue-=360;
			*lpDst++ = (WORD)fsdValue;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDst++;
	}

#endif
	return 0;
}

int ipl_FilterSobel3x3Gray(IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT short* pGx, OUT short* pGy )
{
	int    nHeightScan = nSrcHeight-1;
	int    nWidthScan  = nSrcWidth -1;
	register short* lpDstGx   = pGx + nWidthScan;
	register short* lpDstGy   = pGy + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	register int     x,y;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstGx,lpDstGy,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstGy = pGy  + (y*nSrcWidth) + 1;
		lpDstGx = pGx  + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			*lpDstGy++ =     WN  + (NN+NN) +    NE 
 						//(0*WW) + ( 0*CC) + (0*EE)  
   						   - SW  - (SS+SS) -    ES;

			*lpDstGx++ =      WN /*+ (0*NN)*/ -     NE 
						 +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
						 +    SW /*+ (0*SS)*/ -     ES;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else

	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDstGx++;lpDstGy++;
		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			*lpDstGy++ =     WN  + (NN+NN) +    NE 
 						//(0*WW) + ( 0*CC) + (0*EE)  
   						   - SW  - (SS+SS) -    ES;

			*lpDstGx++ =      WN /*+ (0*NN)*/ -     NE 
						 +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
						 +    SW /*+ (0*SS)*/ -     ES;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDstGx++;lpDstGy++;
	}

#endif
	return 0;
}

int ipl_FilterSobelDevide3x3Gray   (IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT LPFLOAT pDest )
{
	int    nHeightScan = nHeight-1;
	int    nWidthScan  = nWidth -1;
	register LPFLOAT lpDst   = pDest + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	int     fGyValue;
	int     fGxValue;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	register int     x,y;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDst,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, fGyValue,fGxValue) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nWidth) + 1;
		lpSrcUp = lpSrc - nWidth;
		lpSrcDn = lpSrc + nWidth;
		lpDst   = pDest + (y*nWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			fGyValue =     WN  + (NN+NN) +    NE 
					  //(0*WW) + ( 0*CC) + (0*EE)  
					     - SW  - (SS+SS) -    ES;

			fGxValue =      WN /*+ (0*NN)*/ -     NE 
					   +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
				       +    SW /*+ (0*SS)*/ -     ES;

			if(fGxValue==0) *lpDst++ = 99999;
			*lpDst++ = (float)fGyValue/(float)fGxValue;
			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nWidth;
	lpSrcDn = lpSrc + nWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDst++;
		for( x=1; x<nWidthScan ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			fGyValue =     WN  + (NN+NN) +    NE 
					  //(0*WW) + ( 0*CC) + (0*EE)  
					     - SW  - (SS+SS) -    ES;

			fGxValue =      WN /*+ (0*NN)*/ -     NE 
					   +(WW+WW)/*+ (0*CC)*/ - (EE+EE)  
				       +    SW /*+ (0*SS)*/ -     ES;

			if(fGxValue==0) *lpDst++ = 99999;
			*lpDst++ = (float)fGyValue/(float)fGxValue;
			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDst++;
	}

#endif
	return 0;

}

int ipl_FilterSobelMagNPhase3x3Gray(IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pMagnitude, OUT LPWORD pPhase )
{
	register int    nHeight   = nSrcHeight;
	register int    nWidth    = nSrcWidth ;
	register int    x, y     ;

	register LPBYTE lpSrc     = pSrc;
	register LPBYTE lpSrcUp   = NULL;
	register LPBYTE lpSrcDn   = NULL;
	register int    nGyValue ;   
	register int    nGxValue ; 
	register int    nMagValue;
	register float  fPhValue ;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 

#ifdef _OPENMP
	register LPBYTE lpDstMag  ;
	register LPWORD lpDstPh   ;

#pragma omp parallel for private(x,lpDstMag,lpDstPh,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGyValue,nGxValue,nMagValue,fPhValue) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeight-1 ; y++ )
	{
		int pos   = y          * nWidth + 1;
		lpSrc     = pSrc       + pos       ;
		lpSrcUp   = lpSrc      - nWidth    ;
		lpSrcDn   = lpSrc      + nWidth    ;
		lpDstPh   = pPhase     + pos       ;
		lpDstMag  = pMagnitude + pos       ;

		for( x=1; x<nWidth-1 ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			nGyValue = WN+NN+NN+NE-SW-SS-SS-ES;
			nGxValue = WN-NE+WW+WW-EE-EE+SW-ES;

			nMagValue = abs(nGyValue) + abs(nGxValue);
			if(nMagValue>255)nMagValue=255;
			*lpDstMag++ = nMagValue;

			//fPhValue  = atan2f((float)nGyValue,(float)nGxValue);
			fPhValue  = fast_atan2f((float)nGyValue,(float)nGxValue);

			if(fPhValue<0) while(fPhValue<  0) fPhValue+=360;
			else           while(fPhValue>360) fPhValue-=360;

			*lpDstPh++ = (int)fPhValue;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	register LPBYTE lpDstMag  = pMagnitude + nWidth -1;
	register LPWORD lpDstPh   = pPhase     + nWidth -1;

	lpSrcUp = pSrc          ;
	lpSrc   = pSrc  + nWidth;
	lpSrcDn = lpSrc + nWidth;

	for( y=1 ; y<nHeight-1 ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDstMag++;lpDstPh++;
		for( x=1; x<nWidth-1 ; x++ )
		{
			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 

			nGyValue = WN+NN+NN+NE-SW-SS-SS-ES;
			nGxValue = WN-NE+WW+WW-EE-EE+SW-ES;

			nMagValue = abs(nGyValue) + abs(nGxValue);
			if(nMagValue>255)nMagValue=255;
			*lpDstMag++ = nMagValue;

			//fPhValue  = atan2f((float)nGyValue,(float)nGxValue);
			fPhValue  = fast_atan2f((float)nGyValue,(float)nGxValue);

			if(fPhValue<0) while(fPhValue<  0) fPhValue+=360;
			else           while(fPhValue>360) fPhValue-=360;

			*lpDstPh++ = (int)fPhValue;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;
		lpDstMag++;lpDstPh++;
	}

#endif
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Sobel phase index 8 functions
int iplSobel8Hypotenuse( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstMagnitude  ,
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstM  = pDstMagnitude + nWidthScan;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nMagnitude, nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstM,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nMagnitude, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex8Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex8Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel8Hypotenuse( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex8Hypotenuse( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex8Hypotenuse( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel8RightAngle( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstMagnitude  ,
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstM  = pDstMagnitude + nWidthScan;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nMagnitude, nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstM,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nMagnitude, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex8RightAngle( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex8RightAngle( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel8RightAngle( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex8RightAngle( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex8RightAngle( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
	}

#endif
	return 0;
}
// Sobel phase index 8 functions
///////////////////////////////////////////////////////////////////////////////////////


int iplSobelMagNPhase60Gray( IN  const  LPBYTE pSrc    , 
						     OUT LPBYTE pDstMagnitude  ,
						     OUT LPBYTE pDstPhase      ,
						     IN  int    nSrcWidth      , 
						     IN  int    nSrcHeight     ,
							 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstM  = pDstMagnitude + nWidthScan;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nMagnitude, nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstM,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nMagnitude, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
	}

#endif
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////
// Sobel phase index 60 functions
int iplSobel60Hypotenuse( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstMagnitude  ,
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstM  = pDstMagnitude + nWidthScan;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nMagnitude, nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstM,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nMagnitude, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel60Hypotenuse( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex60Hypotenuse( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel60RightAngle( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstMagnitude  ,
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstM  = pDstMagnitude + nWidthScan;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nMagnitude, nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstM,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nMagnitude, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60RightAngle( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy +    WN  +     NN  +    NE 
						  //(0*WW) + ( 0*CC) + (0*EE)  
							 - SW  -     SS  -    ES;

				nGx = nGx +    WN /*+ (0*NN)*/ -  NE 
						  +    WW /*+ (0*CC)*/ -  EE  
						  +    SW /*+ (0*SS)*/ -  ES;

				GetDegreeIndex60RightAngle( nGx, nGy, &nMagnitude, &nPhase );

				*lpDstM++ = (BYTE)nMagnitude;
				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstM++ = (BYTE)  0;
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstM++;lpDstP++;
	}

#endif
	return 0;
}

int iplSobel60RightAngle( IN  const  LPBYTE pSrc    , 
						 OUT LPBYTE pDstPhase      ,
						 IN  int    nSrcWidth      , 
						 IN  int    nSrcHeight     ,
						 IN  int    nThreshold     )
{
	int      nHeightScan    = nSrcHeight-1;
	int      nWidthScan     = nSrcWidth -1;
	register LPBYTE lpDstP  = pDstPhase     + nWidthScan;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	BYTE    WN, NN, NE;
	BYTE    WW, CC, EE;
	BYTE    SW, SS, ES; 
	int     nGy       ;
	int     nGx       ;
	register int  x, y;

	int     nPhase;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpDstP,lpSrc,lpSrcUp,lpSrcDn,\
	WN, NN, NE,WW, CC, EE, SW, SS, ES, nGx, nGy, nPhase) num_threads( g_nIplNumberOfThreasds )
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nSrcWidth) + 1;
		lpSrcUp = lpSrc - nSrcWidth;
		lpSrcDn = lpSrc + nSrcWidth;
		lpDstM  = pDstMagnitude  + (y*nSrcWidth) + 1;
		lpDstP  = pDstPhase      + (y*nSrcWidth) + 1;

		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex60RightAngle( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nSrcWidth;
	lpSrcDn = lpSrc + nSrcWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
		for( x=1; x<nWidthScan ; x++ )
		{
//			WN = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
//			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
//			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); ES = *(lpSrcDn+1); 
			                   NN = *(lpSrcUp  ); 
			WW = *(lpSrc  -1);                    EE = *(lpSrc  +1); 
			                   SS = *(lpSrcDn  ); 
			nGx = EE - WW;
			nGy = SS - NN;

			if ((abs(nGx) + abs(nGy)) >= nThreshold)
			{
				WN = *(lpSrcUp-1);                  ; NE = *(lpSrcUp+1); 
				                   CC = *(lpSrc    ); 
				SW = *(lpSrcDn-1);                    ES = *(lpSrcDn+1); 

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

				GetDegreeIndex60RightAngle( nGx, nGy, &nPhase );

				*lpDstP++ = (BYTE)nPhase    ;
			}
			else
			{
				*lpDstP++ = (BYTE)255;
			}

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;lpDstP++;
	}

#endif
	return 0;
}
// Sobel phase index 60 functions
///////////////////////////////////////////////////////////////////////////////////////
