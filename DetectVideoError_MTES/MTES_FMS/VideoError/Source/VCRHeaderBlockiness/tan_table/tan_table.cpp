// tan_table.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tan_table.h"
#include <math.h>
#include "log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define          ipl_PI                3.14159265f//3.1415926535897932384626433832795

#define TO_RADIAN(degree)    ((degree)*(ipl_PI/180.0f))
#define TO_DEGREE(radian)    ((radian)*(180.0f/ipl_PI))
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		SET_SUBFOLDER(_T("tan_table"));

		float fDegree = 0;
		float fValue  = 0;
		int   nIndex  = 0; 
		for( ; fDegree<=360 ; fDegree+=22.5, nIndex++ )
		{
			fValue = tan( TO_RADIAN(fDegree) );

			_tprintf(_T("%02d	%f	%f\n"),nIndex,fDegree,fValue);
			LOGOUT  (_T("%02d	%f	%f"  ),nIndex,fDegree,fValue);
		}
	}

	return nRetCode;
}

