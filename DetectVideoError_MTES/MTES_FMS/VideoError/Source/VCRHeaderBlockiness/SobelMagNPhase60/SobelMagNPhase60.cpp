
#include <windows.h>
#include "SobelMagNPhase60.h"
#include "DegreeIndex.h"

int SobelMagNPhase60Gray( IN  const   LPBYTE* pSourceArray, 
						  OUT LPBYTE* ppDstMagnitudeArray ,
						  OUT LPBYTE* pPhaseArray         ,
						  IN  int     nSrcWidth           , 
						  IN  int     nSrcHeight          ,
						  IN  int     nThreshold    =   20);
int iplSobelMagNPhase60Gray( IN  const  LPBYTE pSrc    , 
						     OUT LPBYTE pDstMagnitude  ,
						     OUT LPBYTE pDstPhase      ,
						     IN  int    nSrcWidth      , 
						     IN  int    nSrcHeight     ,
							 IN  int    nThreshold = 20);


BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

void ErrorMessage(char *msg, char *functionName)
{
	char errorName[128];
	sprintf(errorName, "%s Function Error", functionName);
	MessageBox(NULL, msg, errorName, MB_OK|MB_ICONERROR);
}

int CDECL SobelMagNPhase60(
	int*                   pThreshold   ,
	KScScalarImage2dUint8* pSrcImage    ,
	KScScalarImage2dUint8* pDstMagnitude,
	KScScalarImage2dUint8* pDstPhase    )
{
    int dx = pSrcImage->GetMainXSize();
    int dy = pSrcImage->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Sobel", MB_OK);
        return FALSE;
	}

	if (pSrcImage->IsRoi())
	{
		
		if (dx != pDstMagnitude->GetMainXSize() ||
			dy != pDstMagnitude->GetMainYSize())
		{
			
			pDstMagnitude->Free();
			
			if (pDstMagnitude->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate  pDstMagnitude output buffer.",
					"Sobel", MB_OK);
				return FALSE;
			}
		}
		
		pSrcImage->CopyToObject(pDstMagnitude);

		
		if (dx != pDstPhase->GetMainXSize() ||
			dy != pDstPhase->GetMainYSize())
		{
			
			pDstPhase->Free();
			
			if (pDstPhase->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate Phase output buffer.",
					"Sobel", MB_OK);
				return FALSE;
			}
		}
		
		pSrcImage->CopyToObject(pDstPhase);

		
		dx = pSrcImage->GetXSize();
		dy = pSrcImage->GetYSize();

		
		if (pDstMagnitude->IsRoi())
			pDstMagnitude->ResetRoiRect();

		
		pDstMagnitude->SetRoiRect(pSrcImage->GetRoiRect());

		if (pDstPhase->IsRoi())
			pDstPhase->ResetRoiRect();

		pDstPhase->SetRoiRect(pSrcImage->GetRoiRect());

		
	}
	
	else
	{
		
		dx = pSrcImage->GetXSize();
		dy = pSrcImage->GetYSize();

		
		if (dx != pDstMagnitude->GetXSize() ||
			dy != pDstMagnitude->GetYSize())
		{
			
			pDstMagnitude->Free();
			
			if (pDstMagnitude->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate pDstMagnitude output buffer.",
					"Sobel", MB_OK);
				return FALSE;
			}
		}
		
		else
			
			pDstMagnitude->InitTo(0);

		if (dx != pDstPhase->GetXSize() ||
			dy != pDstPhase->GetYSize())
		{
			pDstPhase->Free();
			if (pDstPhase->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate Phase output buffer.",
					"Sobel", MB_OK);
				return FALSE;
			}
		}
		else
			pDstPhase->InitTo(0);
	}


//by MD. Hasan
//	KSdUint8 **pSourceArray        = pSrcImage    ->Get2dArray();
//	KSdUint8 **ppDstMagnitudeArray = pDstMagnitude->Get2dArray();
//	KSdUint8 **pPhaseArray         = pDstPhase  ->Get2dArray();
//	SobelMagNPhase60Gray( pSourceArray, ppDstMagnitudeArray, pPhaseArray, dx, dy, *pThreshold );


//by kiok ahn
	KSdUint8 *pSourceArray        = pSrcImage    ->GetBuffer();
	KSdUint8 *pDstMagnitudeArray  = pDstMagnitude->GetBuffer();
	KSdUint8 *pPhaseArray         = pDstPhase  ->GetBuffer();
	iplSobelMagNPhase60Gray( pSourceArray, pDstMagnitudeArray, pPhaseArray, dx, dy, *pThreshold );

	char comment[1024];
	sprintf(comment, "After Sobel for %s",
		pSrcImage->GetName());
	pDstMagnitude->AppendComment(comment);
	pDstPhase->AppendComment(comment);

	return TRUE;
}


//by MD. Hasan
int SobelMagNPhase60Gray( IN  const   LPBYTE* pSourceArray, 
						  OUT LPBYTE* ppDstMagnitudeArray ,
						  OUT LPBYTE* pPhaseArray         ,
						  IN  int     nSrcWidth           , 
						  IN  int     nSrcHeight          ,
						  IN  int     nThreshold          )
{
	int   gx, gy;
	float cc;
	register int x = nSrcWidth - 1, y = nSrcHeight - 1;


	for (register int i = 1, j ; i < y ; i++)
	{
		for (j = 1 ; j < x ; j++)
		{	
			gx = pSourceArray[i - 1][j + 1] - pSourceArray[i + 1][j - 1];
			gy = pSourceArray[i + 1][j + 1] - pSourceArray[i - 1][j - 1];

			if ((abs(gx) + abs(gy)) >= nThreshold)
			{
				gx += gy + 2 * (pSourceArray[i    ][j + 1] - pSourceArray[i    ][j - 1]);

				gy =            pSourceArray[i + 1][j - 1] - pSourceArray[i - 1][j - 1]	 +
					       2 * (pSourceArray[i + 1][j    ] - pSourceArray[i - 1][j    ]) +
					            pSourceArray[i + 1][j + 1] - pSourceArray[i - 1][j + 1];


				if (gx >= 0)  // [-90, 90] or [270,90]
				{
					if (gx)  // (-90,90)
					{
						cc = (float)gy / (float)gx;

						if     ( cc > 9.5 ) pPhaseArray[i][j] = 14;
						else if( cc > 4.7 ) pPhaseArray[i][j] = 13;
						else if( cc > 3.1 ) pPhaseArray[i][j] = 12;
						else if( cc > 2.25) pPhaseArray[i][j] = 11;
						else if( cc > 1.73) pPhaseArray[i][j] = 10;
						else if( cc > 1.38) pPhaseArray[i][j] = 9 ;
						else if( cc > 1.11) pPhaseArray[i][j] = 8 ;
						else if( cc > 0.9 ) pPhaseArray[i][j] = 7 ;
						else if( cc > 0.73) pPhaseArray[i][j] = 6 ;
						else if( cc > 0.58) pPhaseArray[i][j] = 5 ;
						else if( cc > 0.45) pPhaseArray[i][j] = 4 ; 
						else if( cc > 0.33) pPhaseArray[i][j] = 3 ;
						else if( cc > 0.21) pPhaseArray[i][j] = 2 ;
						else if( cc > 0.11) pPhaseArray[i][j] = 1 ;
						else if( cc > 0   ) pPhaseArray[i][j] = 0 ;
						else if( cc >-0.11) pPhaseArray[i][j] = 59;
						else if( cc >-0.21) pPhaseArray[i][j] = 58;
						else if( cc >-0.33) pPhaseArray[i][j] = 57;
						else if( cc >-0.45) pPhaseArray[i][j] = 56;
						else if( cc >-0.58) pPhaseArray[i][j] = 55;
						else if( cc >-0.73) pPhaseArray[i][j] = 54;
						else if( cc >-0.9 ) pPhaseArray[i][j] = 53;
						else if( cc >-1.11) pPhaseArray[i][j] = 52;
						else if( cc >-1.38) pPhaseArray[i][j] = 51;
						else if( cc >-1.73) pPhaseArray[i][j] = 50;
						else if( cc >-2.25) pPhaseArray[i][j] = 49;
						else if( cc >-3.1 ) pPhaseArray[i][j] = 48;
						else if( cc >-4.7 ) pPhaseArray[i][j] = 47;
						else if( cc >-9.5 ) pPhaseArray[i][j] = 46;
						else                pPhaseArray[i][j] = 45;					
					}
					else
					{
						if (gy>0)			// 90
							pPhaseArray[i][j] = 14;//1
						else				// -90
							pPhaseArray[i][j] = 44;//5
					}
				}
				else		// gx<0, (90,270)
				{
					cc = (float)gy / (float)gx;

					if     ( cc > 9.5 ) pPhaseArray[i][j] = 44;
					else if( cc > 4.7 ) pPhaseArray[i][j] = 43;
					else if( cc > 3.1 ) pPhaseArray[i][j] = 42;
					else if( cc > 2.25) pPhaseArray[i][j] = 41;
					else if( cc > 1.73) pPhaseArray[i][j] = 40;
					else if( cc > 1.38) pPhaseArray[i][j] = 39;
					else if( cc > 1.11) pPhaseArray[i][j] = 38;
					else if( cc > 0.9 ) pPhaseArray[i][j] = 37;
					else if( cc > 0.73) pPhaseArray[i][j] = 36;
					else if( cc > 0.58) pPhaseArray[i][j] = 35;
					else if( cc > 0.45) pPhaseArray[i][j] = 34;
					else if( cc > 0.33) pPhaseArray[i][j] = 33;
					else if( cc > 0.21) pPhaseArray[i][j] = 32;
					else if( cc > 0.11) pPhaseArray[i][j] = 31;
					else if( cc > 0   ) pPhaseArray[i][j] = 30;
					else if( cc >-0.11) pPhaseArray[i][j] = 29;
					else if( cc >-0.21) pPhaseArray[i][j] = 28;
					else if( cc >-0.33) pPhaseArray[i][j] = 27;
					else if( cc >-0.45) pPhaseArray[i][j] = 26;
					else if( cc >-0.58) pPhaseArray[i][j] = 25;
					else if( cc >-0.73) pPhaseArray[i][j] = 24;
					else if( cc >-0.9 ) pPhaseArray[i][j] = 23;
					else if( cc >-1.11) pPhaseArray[i][j] = 22;
					else if( cc >-1.38) pPhaseArray[i][j] = 21;
					else if( cc >-1.73) pPhaseArray[i][j] = 20;
					else if( cc >-2.25) pPhaseArray[i][j] = 19;
					else if( cc >-3.1 ) pPhaseArray[i][j] = 18;
					else if( cc >-4.7 ) pPhaseArray[i][j] = 17;
					else if( cc >-9.5 ) pPhaseArray[i][j] = 16;
					else                pPhaseArray[i][j] = 15;
				}

				gx = (abs(gx) + abs(gy)) / 3;
				if (gx > 255)
					gx = 255;

				ppDstMagnitudeArray[i][j] = gx;

			}
			else 
			{
				pPhaseArray        [i][j] = 255;
				ppDstMagnitudeArray[i][j] = 0;
			}
		}
	}
	return 0;
}


//by kiok ahn
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

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

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

				nGy = nGy    - WN  -     NN  -    NE
						  //(0*WW) + ( 0*CC) + (0*EE)
							 + SW  +     SS  +    ES;

				nGx = nGx -    WN /*+ (0*NN)*/ +  NE
						  -    WW /*+ (0*CC)*/ +  EE
						  -    SW /*+ (0*SS)*/ +  ES;

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
