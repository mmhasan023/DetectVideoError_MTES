#include "stdafx.h"


//#ifdef _LOGDATA
#if ( defined(_LOGDATA) || defined(PIPE_LOG) || defined(_LOGLEAK) )

#include "tchar.h"
#include "log.h"
#include <shlobj.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
static int   g_nSema = 1;
static DWORD g_t0    = 0;
static TCHAR g_szFolder          [MAX_PATH ]={0};
static TCHAR g_szLogFilePath     [MAX_PATH2]={0};
static TCHAR g_szSendLogFilePath [MAX_PATH2]={0};
static TCHAR g_szRsvLogFilePath  [MAX_PATH2]={0};
static TCHAR g_szAliveLogFilePath[MAX_PATH2]={0};
static TCHAR g_szLogFileMainPath [MAX_PATH2]={0};



//BOOL DEBUG_MAKE_NAME(IN LPCTSTR szName, OUT LPTSTR lpFullPath, int nSize);
//int MakeLogFilePath( void );
//int g_nLogFilePath = MakeLogFilePath();



BOOL _CreateFullDir(LPCTSTR lpSrcPath, BOOL bIsFilePath)
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

BOOL GetThisProcessPath( LPTSTR lpPath, const int& nSize )
{
	TCHAR cPath    [MAX_PATH2]={0};
	TCHAR cFileName[MAX_PATH ]={0};
	TCHAR cDriver  [MAX_PATH ]={0};
	TCHAR cDir     [MAX_PATH2]={0};
	TCHAR cEx      [MAX_PATH ]={0};

	DWORD dwResult = GetModuleFileName(NULL, cPath, MAX_PATH2);
	//if(  dwResult != S_OK )
	//	return FALSE;

	_tsplitpath( cPath, cDriver, cDir, cFileName, cEx ); 
	_stprintf_s( lpPath, nSize, _T("%s%s"), cDriver, cDir);

	size_t i   = _tcslen( lpPath ) - 1;
	TCHAR cTmp = lpPath[i];
	while(cTmp=='\\' && i )
	{
		lpPath[i] = 0;
		cTmp = lpPath[--i];
	}

	return TRUE;
}

BOOL GetSysUserDataPath( LPTSTR lpPath, int nSize )
{
	TCHAR	szPath[MAX_PATH2]={0};

	if (::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;

	if (_tcslen(szPath) == 0)
	{
		if ( ::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;
	}

	_tcscpy( lpPath, szPath);
	return TRUE;
}

BOOL _GetUserDataPath(LPTSTR lpPath, int nSize)
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

void SET_SUBFOLDER( IN LPCTSTR lpFolderName )
{
	memset ( g_szFolder, 0, sizeof(TCHAR)*MAX_PATH );
	_tcscpy( g_szFolder, lpFolderName );
}

TCHAR* GETLOGPATH( void )
{
	if( _tcslen(g_szLogFileMainPath)!=0 )
		return g_szLogFileMainPath;

	TCHAR szPath[MAX_PATH2]={0};
	_GetUserDataPath( szPath, MAX_PATH2 );

	_tcscat( szPath, g_szFolder );

	int nLength = (int)_tcslen( szPath ) -1;
	if( szPath[nLength] != '\\' )
		_tcscat( szPath, _T("\\") );

	_CreateFullDir(szPath,FALSE);
	_tcscpy(g_szLogFileMainPath, szPath);

	return g_szLogFileMainPath;
}

BOOL DEBUG_MAKE_NAME(IN LPCTSTR szName, OUT LPTSTR lpFullPath, int nSize)
{
	TCHAR szPath[MAX_PATH2]={0};
	_GetUserDataPath( szPath, MAX_PATH2 );

	_tcscat( szPath, g_szFolder );

	int nLength = (int)_tcslen( szPath ) -1;
	if( szPath[nLength] != '\\' )
		_tcscat( szPath, _T("\\") );

	_CreateFullDir(szPath,FALSE);

	SYSTEMTIME st;
	GetLocalTime(&st);
//	GetSystemTime(&st);
	TCHAR szFileName[MAX_PATH]={0};

#ifdef _SHORT_TERM_PROCESS_LOG
	_stprintf( szFileName, _T("%04d%02d%02d_%02d%02d%02d_%s.txt"), 
		st.wYear, st.wMonth , st.wDay   , 
		st.wHour, st.wMinute, st.wSecond, szName );
#else
	_stprintf( szFileName, _T("%04d_%02d_%02d_%s.txt"), st.wYear, st.wMonth, st.wDay, szName );
#endif

	_tcscat( szPath, szFileName );
	_tcscpy( lpFullPath, szPath);

//	memset(szPath, 0, sizeof(szPath));
//	_GetUserDataPath( szPath, MAX_PATH2 );
//	_tcscat( szPath, _T("CheckProfile") );
//	_CreateFullDir(szPath,FALSE);

	return TRUE;
}


void LOGOUT(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	while( g_nSema==0 ) Sleep(10);
	g_nSema--;

	FILE *fFile = NULL;

#ifdef _SHORT_TERM_PROCESS_LOG
	if( _tcslen(g_szLogFilePath) == 0 )
		DEBUG_MAKE_NAME( _T("log"), g_szLogFilePath, MAX_PATH2 );
	if( (fFile = _tfopen(g_szLogFilePath, _T("a+") )) == NULL )
		return;
#else
	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("log"), szFullPath, MAX_PATH2 );
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
#endif

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

	g_nSema++;
}

void LOGSEND(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

#ifdef _SHORT_TERM_PROCESS_LOG
	if( _tcslen(g_szSendLogFilePath) == 0 )
		DEBUG_MAKE_NAME( _T("send"), g_szSendLogFilePath, MAX_PATH2 );
	
	if( (fFile = _tfopen(g_szSendLogFilePath, _T("a+") )) == NULL )
		return;
#else
	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("send"), szFullPath, MAX_PATH2 );
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
#endif
	
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

}

void LOGRSV(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

#ifdef _SHORT_TERM_PROCESS_LOG
	if( _tcslen(g_szRsvLogFilePath) == 0 )
		DEBUG_MAKE_NAME( _T("receive"), g_szRsvLogFilePath, MAX_PATH2 );
	
	if( (fFile = _tfopen(g_szRsvLogFilePath, _T("a+") )) == NULL )
		return;
#else
	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("receive"), szFullPath, MAX_PATH2 );
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
#endif
	
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
//	fwrite("\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);
}

void LOGALIVE(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

	if( _tcslen(g_szAliveLogFilePath) == 0 )
		DEBUG_MAKE_NAME( _T("alive"), g_szAliveLogFilePath, MAX_PATH2 );
//	TCHAR szFullPath[MAX_PATH2]={0};
//	DEBUG_MAKE_NAME( _T("alive"), szFullPath, MAX_PATH2 );
	
	if( (fFile = _tfopen(g_szAliveLogFilePath, _T("a+") )) == NULL )
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
}

/*
void LOGLEAK(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("leak"), szFullPath, MAX_PATH2 );

	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;

	SYSTEMTIME st;
	GetLocalTime(&st);

	_ftprintf( fFile,_T("%02d:%02d:%02d - "),
		st.wHour, st.wMinute, st.wSecond );

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
}
*/

DWORD GetLastErrorString( LPTSTR lpszMsg, size_t nSize ) 
{ 
	DWORD dwError = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	size_t nStrSize = _tcslen( (LPCTSTR)lpMsgBuf );
	nStrSize = min( nStrSize, nSize );
	_tcsncpy( lpszMsg, (LPCTSTR)lpMsgBuf, nStrSize );
	LocalFree( lpMsgBuf );

	return dwError;
}

void CheckPointerAddress( LPVOID lpvoid , const char *pFileName, int nLineNumber)
{
	if( lpvoid==NULL )
		LOGOUT( _T("Pointer Error  %s, %d"), pFileName, nLineNumber);
}


#endif
