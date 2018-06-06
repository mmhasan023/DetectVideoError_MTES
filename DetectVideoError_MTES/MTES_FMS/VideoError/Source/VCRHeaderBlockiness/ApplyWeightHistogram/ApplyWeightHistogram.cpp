
#include <windows.h>
#include "ApplyWeightHistogram.h"

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

#define PHASE_SIZE 60
int g_nWeight[] = { 
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7 //14__________
};

int CDECL ApplyWeightHistogram( float           fWeight      ,//Reserved 
							    KScHistogram1d* pSrcHistogram,//Input
								KScHistogram1d* pDstHistogram)//Output
{
	if( !pSrcHistogram )
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"ApplyWeightHistogram", MB_OK);
        return FALSE;
	}

	int nSize = pSrcHistogram->GetBucketNumber();
	if( !nSize )
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"ApplyWeightHistogram", MB_OK);
        return FALSE;
	}

	if (!pDstHistogram->GetBucketNumber() || pDstHistogram->GetBucketNumber() != 256)
	{
		pDstHistogram->Free();
		
		if (pDstHistogram->Alloc(nSize))
		{
			MessageBox(NULL, "Fail to allocate output buffer.",
				"ApplyWeightHistogram", MB_OK);
			return FALSE;
		}
	}
	else
		pDstHistogram->InitTo();

	int*  pWeight      = g_nWeight;
	long* pSrcHisto    = pSrcHistogram->GetBucketBuffer();
	long* pDstHisto    = pDstHistogram->GetBucketBuffer();
	long* pSrcHistoEnd = pSrcHisto + PHASE_SIZE;

	while( pSrcHisto<pSrcHistoEnd )
	{
		*pDstHisto++ = *pSrcHisto++ * *pWeight++;
	}

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


