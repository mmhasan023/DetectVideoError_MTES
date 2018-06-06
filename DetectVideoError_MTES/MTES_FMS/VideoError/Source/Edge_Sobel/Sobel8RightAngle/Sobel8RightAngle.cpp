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
#include "Sobel8RightAngle.h"

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

void ErrorMessage(char *msg, char *functionName)
{
	char errorName[128];
	sprintf(errorName, "%s Function Error", functionName);
	MessageBox(NULL, msg, errorName, MB_OK|MB_ICONERROR);
}


// �Լ��� ���� �κ�
int CDECL Sobel8RightAngle(
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
	iplSobel8RightAngle( pSourceArray, pDstMagnitudeArray, pPhaseArray, dx, dy, *pThreshold );

	char comment[1024];
	sprintf(comment, "After Sobel for %s",
		pSrcImage->GetName());
	pDstMagnitude->AppendComment(comment);
	pDstPhase->AppendComment(comment);

	return TRUE;
}
