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
#include "HistogramCalculateUint8.h"

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

// 
int CDECL HistogramCalculateUint8(
	int                    nApplyStart   ,//Delete all value before this value in output histogram. 
	int                    nApplyEnd     ,//Delete all value after this value in output histogram. 
	KScScalarImage2dUint8* pSrcImage     ,//Input Image 
	KScHistogram1d*        pDstHistogram )//Output Histogram
{

	if (pSrcImage->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"iGetHistogramUint8", MB_OK);
        return FALSE;
	}

    
    if (pDstHistogram->GetId() != KS_HISTOGRAM_1D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"iGetHistogramUint8", MB_OK);
        return FALSE;
	}

    
    int nWidth  = pSrcImage->GetMainXSize();
    int nHeight = pSrcImage->GetMainYSize();
    if (!nWidth || !nHeight)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"iGetHistogramUint8", MB_OK);
        return FALSE;
	}

	nWidth  = pSrcImage->GetXSize();
	nHeight = pSrcImage->GetYSize();

	if (!pDstHistogram->GetBucketNumber() || pDstHistogram->GetBucketNumber() != 256)
	{
		pDstHistogram->Free();
		
		if (pDstHistogram->Alloc(256))
		{
			MessageBox(NULL, "Fail to allocate output buffer.",
				"iGetHistogramUint8", MB_OK);
			return FALSE;
		}
	}
	else
		pDstHistogram->InitTo();


    KSdUint8 *pSrcBuffer          = pSrcImage->GetBuffer();
    KSdUint8 *pEndBuffer          = pSrcBuffer + nWidth*nHeight;
    long     *pDstHistogramBuffer = pDstHistogram->GetBuffer();

//	for (register int i = 0, j ; i < nHeight ; i++)
//		for (j = 0 ; j < nWidth ; j++)
//			pDstHistogramBuffer[pSrcImageArray[i][j]]++;

	while( pSrcBuffer < pEndBuffer )
		pDstHistogramBuffer[*pSrcBuffer++]++;

	pDstHistogramBuffer = pDstHistogram->GetBuffer();
	memset( pDstHistogramBuffer, 0, sizeof(long) * nApplyStart );
	memset( pDstHistogramBuffer + nApplyEnd, 0, sizeof(long) * (pDstHistogram->GetBucketNumber()-nApplyEnd) );

	char comment[1024];
	sprintf(comment, "After iGetHistogramUint8 for %s",
		pSrcImage->GetName());
	pDstHistogram->AppendComment(comment);

	return TRUE;

}


