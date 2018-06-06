//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "LengthHistogramRECT.h"

// DLL�� ����� ���� �κ�
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


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//������
int SearchVerticalDirection  ( 
	LPCTSTR    lpPhase     , 
	const int& nWidth      , 
	const int& nMinLength  , 
	const int& nMaxLength  , 
	const int& nLimitation )
{
	int nLength = 0;

	return nLength;
}

//����
int SearchHorizontalDirection( 
	LPBYTE     lpPhase     , 
	const int& nLimitation )
{
	LPBYTE  lpItor       = lpPhase ;
	int     nLength      = 0       ;
	BYTE    byteCurValue = *lpPhase;

	while( byteCurValue == *lpItor )
	{
		*lpItor = 255;

		nLength++;
		lpItor ++;

		if( nLength > nLimitation )
			break;
	}

	return nLength;
}


int iplGetLengthHistogramRECT( 
	      LPBYTE lpIndexedPhase8         ,//IN OUT, Modified
	OUT   LPLONG lpLengthHistogram       ,
	const int&   nWidth                  ,
	const int&   nHeight                 ,
	const int&   nLengthThresholdLow =  4,
	const int&   nLengthThresholdHigh= 80)
{
	int    nLimitation = 0;
	int    nLength     = 0;
	LPBYTE lpSrc       = lpIndexedPhase8;
	for( int nX,nY = 0 ; nY<nHeight ; nY++ )
	{
		for( nX=0 ; nX<nWidth ; nX++ )
		{
			switch( *lpSrc )
			{
				case 0:
				case 4:
					break;
				case 2:
				case 6:
					nLimitation = nWidth-nX;
					nLength = SearchHorizontalDirection( lpSrc, nLimitation );
					if( nLengthThresholdLow <= nLength &&
						nLength <= nLengthThresholdHigh )
					{
						lpLengthHistogram[nLength]++;
					}
					break;
			}

			lpSrc++;
		}
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


// �Լ��� ���� �κ�
int CDECL LengthHistogramRECT(
	KScScalarImage2dUint8* pIndexedPhase8       ,
	KScHistogram1d*        pLengthHistogram     ,
	int*                   pnLengthThresholdLow ,//2
	int*                   pnLengthThresholdHigh)//80
{

	int nLengthThresholdLow  = *pnLengthThresholdLow ;
	int nLengthThresholdHigh = *pnLengthThresholdHigh;

	int   nWidth  = pIndexedPhase8->GetXSize ();
	int   nHeight = pIndexedPhase8->GetYSize ();
	BYTE* pBuf    = pIndexedPhase8  ->GetBuffer();

	if( nWidth<=0 || nHeight<=0 || pBuf==NULL )
		return FALSE;

	if (!pLengthHistogram->GetBucketNumber() || pLengthHistogram->GetBucketNumber() != 256)
	{
		pLengthHistogram->Free();
		
		if (pLengthHistogram->Alloc(256))
		{
			MessageBox(NULL, "Fail to allocate output buffer.",
				"iGetHistogramUint8", MB_OK);
			return FALSE;
		}
	}
	else
		pLengthHistogram->InitTo();

    long* pHisto  = pLengthHistogram->GetBuffer();
	BYTE* pTmp    = new BYTE[nWidth*nHeight];
	memcpy( pTmp, pBuf, sizeof(BYTE)*nWidth*nHeight );

	iplGetLengthHistogramRECT( pTmp, pHisto, nWidth, nHeight, nLengthThresholdLow, nLengthThresholdHigh );


	return TRUE;
}

