//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "EraseAreaPhase.h"
#include "iplapi.h"

// DLL을 만들기 위한 부분
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

// 함수의 정의 부분
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

