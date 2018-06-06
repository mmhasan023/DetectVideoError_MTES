//#ifdef _LOGDATA
#if defined(_DEBUG)

#include "tchar.h"
#include "mem_trace_log.h"
#include <shlobj.h>
#include <stdio.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


#pragma warning(disable:4995)
#pragma warning(disable:4996)

static DWORD g_t0 = 0;
static TCHAR _memtrace_g_szFolder  [MAX_PATH ]={0};
static TCHAR _memtrace_g_szFullParh[MAX_PATH2]={0};
static int _memtrace_g_nSema = 1;

BOOL _memtrace_CreateFullDir(const TCHAR* lpSrcPath, BOOL bIsFilePath)
{
	TCHAR szPath[MAX_PATH2]={0};
	_tcscpy( szPath, lpSrcPath);

	int     nSize     = (int)_tcslen(szPath);
	TCHAR*  lpItor    = szPath         ;
	TCHAR*  lpItorEnd = szPath+nSize   ;

	if(bIsFilePath)
	{
		while( *lpItorEnd != '\\' && lpItorEnd!=lpItor )
			*lpItorEnd-- = NULL;
	}
	lpItorEnd = szPath+nSize   ;

	TCHAR szResult[MAX_PATH2]={0};
	TCHAR szTmp   [MAX_PATH2]={0};

	while( (lpItor<lpItorEnd) && *lpItor!='\0' )
	{
		memset( szTmp, 0, sizeof(TCHAR)*MAX_PATH2 );
		TCHAR* pTmpItor = szTmp;
		while( *lpItor!='\\' && *lpItor!='\0')
		{
			*pTmpItor++ = *lpItor++;
		}

		if(*lpItor!='\0')
			_tcscat( szTmp, _T("\\") );

		_tcscat( szResult, szTmp );
		if( ::GetFileAttributes(szResult)==INVALID_FILE_ATTRIBUTES )
		{
			if (CreateDirectory(szResult, NULL) == FALSE)
			{
				return FALSE;
			}
		}

		while( *lpItor=='\\' && *lpItor!='\0')
		{
			lpItor++;
		}
	}

	return TRUE;
}

BOOL _memtrace_GetUserDataPath(TCHAR* lpPath, int nSize)
{
	TCHAR	szPath[MAX_PATH2]={0};

	if (::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;

	if (_tcslen(szPath) == 0)
	{
		if ( ::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;
	}
	_tcscat( szPath, _T("\\Hawkeye\\") );

	if(::GetFileAttributes(szPath)==INVALID_FILE_ATTRIBUTES)
		::CreateDirectory(szPath,NULL);


	_tcscpy( lpPath, szPath);

	return TRUE;
}

int _memtrace_SET_SUBFOLDER( const TCHAR* lpFolderName )
{
	memset ( _memtrace_g_szFolder, 0, sizeof(TCHAR)*MAX_PATH );
	_tcscpy( _memtrace_g_szFolder, lpFolderName );
	return 0;
}



BOOL _memtrace_DEBUG_MAKE_NAME(const TCHAR* szName, TCHAR* lpFullPath, int nSize)
{
	TCHAR szPath[MAX_PATH2]={0};
	_memtrace_GetUserDataPath( szPath, MAX_PATH2 );

	_tcscat( szPath, _memtrace_g_szFolder );

	int nLength = (int)_tcslen( szPath ) -1;
	if( szPath[nLength] != '\\' )
		_tcscat( szPath, _T("\\") );

	_memtrace_CreateFullDir(szPath,FALSE);

	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR szFileName[MAX_PATH]={0};
//	_stprintf( szFileName, _T("%04d_%02d_%02d_%s.txt"), st.wYear, st.wMonth, st.wDay, _memtrace_g_szFolder );		//체크서버로그를 한파일에 다 남기는 경우.,
	_stprintf( szFileName, _T("%04d_%02d_%02d_%s.txt"), st.wYear, st.wMonth, st.wDay, szName );

	_tcscat( szPath, szFileName );
	_tcscpy( lpFullPath, szPath);

//	memset(szPath, 0, sizeof(szPath));
//	_memtrace_GetUserDataPath( szPath, MAX_PATH2 );
//	_tcscat( szPath, _T("CheckProfile") );
//	_memtrace_CreateFullDir(szPath,FALSE);

	return TRUE;
}

void _memtrace_LOGOUT(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	while( _memtrace_g_nSema==0 ) Sleep(10);
	_memtrace_g_nSema--;

	FILE *fFile = NULL;

	TCHAR *pPath=NULL;
	TCHAR szFullPath[MAX_PATH2]={0};

	if( _tcslen(_memtrace_g_szFullParh) )
		pPath = _memtrace_g_szFullParh;
	else
	{
		_memtrace_DEBUG_MAKE_NAME( _T("log"), szFullPath, MAX_PATH2 );
		pPath = szFullPath;
	}
	if( (fFile = _tfopen( pPath, _T("a+") )) == NULL )
		return;
	
	SYSTEMTIME st;
	GetLocalTime(&st);

	_ftprintf( fFile,_T("%02d:%02d:%02d:%03d - "),
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
	fseek(fFile,0,SEEK_END);

	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	char szMessage[2048]={0};
#ifdef _UNICODE
	int AnsiStrSize = WideCharToMultiByte(CP_ACP, 0, szTmp, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, szTmp, -1, szMessage, AnsiStrSize, 0, 0);
#else
	strcpy(szMessage, szTmp);
#endif
	fseek(fFile,0,SEEK_END);
	fwrite(szMessage,strlen(szMessage),1,fFile);
	fwrite("\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);

	_memtrace_g_nSema++;
}


#endif
