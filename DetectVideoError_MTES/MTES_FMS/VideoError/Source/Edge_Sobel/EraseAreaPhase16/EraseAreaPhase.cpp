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
#include "EraseAreaPhase.h"
#include "iplapi.h"

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

// �Լ��� ���� �κ�
int CDECL EraseAreaPhase16(
	float* pRatioThreshold,
	int*   pPixelCountThreshold,
	KScScalarImage2dUint8* pSrcImage,
	KScScalarImage2dUint8* pDstImage)
{
    int dx = pSrcImage->GetMainXSize();
    int dy = pSrcImage->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"EraseAreaPhase", MB_OK);
        return FALSE;
	}

	if (pSrcImage->IsRoi())
	{
		
		if (dx != pDstImage->GetMainXSize() ||
			dy != pDstImage->GetMainYSize())
		{
			
			pDstImage->Free();
			
			if (pDstImage->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate  pDstMagnitude output buffer.",
					"EraseAreaPhase", MB_OK);
				return FALSE;
			}
		}
		
		pSrcImage->CopyToObject(pDstImage);
		
		dx = pSrcImage->GetXSize();
		dy = pSrcImage->GetYSize();

		
		if (pDstImage->IsRoi())
			pDstImage->ResetRoiRect();

		
		pDstImage->SetRoiRect(pSrcImage->GetRoiRect());

		if (pDstImage->IsRoi())
			pDstImage->ResetRoiRect();

		pDstImage->SetRoiRect(pSrcImage->GetRoiRect());
	}
	
	else
	{
		dx = pSrcImage->GetXSize();
		dy = pSrcImage->GetYSize();

		
		if (dx != pDstImage->GetXSize() ||
			dy != pDstImage->GetYSize())
		{
			
			pDstImage->Free();
			
			if (pDstImage->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate pDstMagnitude output buffer.",
					"EraseAreaPhase", MB_OK);
				return FALSE;
			}
		}
		else
			pDstImage->InitTo(0);
	}

//by kiok ahn
	KSdUint8 *pSourceArray = pSrcImage->GetBuffer();
	KSdUint8 *pDstArray    = pDstImage->GetBuffer();
	KSdUint8 *pTmp         = new KSdUint8[dx*dy];

	memset( pDstArray, 0xFF,sizeof(KSdUint8)*dx*dy );
	memcpy( pTmp, pSourceArray, sizeof(KSdUint8)*dx*dy );
	iplEraseAreaPhase16( pTmp, pDstArray, dx, dy, *pRatioThreshold, *pPixelCountThreshold );

	delete[] pTmp;

	char comment[1024];
	sprintf(comment, "After EraseAreaPhase for %s",
		pSrcImage->GetName());
	pDstImage->AppendComment(comment);

	return TRUE;
}

