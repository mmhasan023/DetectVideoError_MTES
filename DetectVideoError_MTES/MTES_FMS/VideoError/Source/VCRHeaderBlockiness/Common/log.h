//log.h
//by kiok ahn
///////////////////////////////////////////////////////
//      사용법
///////////////////////////////////////////////////////
//1. 저장 폴더 초기화
//    Win7의 경우 다음 경로에 저장 : C:\Users\"사용자 ID"\AppData\Local\Hawkeye\
//#if ( defined(_LOGDATA) || defined(PIPE_LOG) )
//	SET_SUBFOLDER( _T("CheckSvr") );
//#endif
//
//2. 실제 로그를 남긴다. 
//#ifdef _LOGDATA
//	LOGOUT( _T("Log check = %s"), szResultTmpPath  );
//#endif

#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_

#ifndef MAX_PATH2
	#define MAX_PATH2 520
#endif


#if ( defined(_LOGDATA) || defined(PIPE_LOG) )

extern void   LOGOUT  (TCHAR *szMsg, ...);
extern void   LOGSEND (TCHAR *szMsg, ...);
extern void   LOGRSV  (TCHAR *szMsg, ...);
extern void   LOGALIVE(TCHAR *szMsg, ...);
extern TCHAR* GETLOGPATH(void);

//extern void LOGLEAK(TCHAR *szMsg, ...);
extern void SET_SUBFOLDER( IN LPCTSTR lpFolderName );//저장 될 하위 폴더 이름 지정, CApp::InitInstance등에서 한번만 수행 한다.

extern BOOL CreateFullDir     ( LPCTSTR lpSrcPath, BOOL bIsFilePath);
extern BOOL GetUserDataPath   ( LPTSTR lpPath, int nSize);
extern BOOL GetSysUserDataPath( LPTSTR lpPath, int nSize);
extern BOOL GetThisProcessPath( LPTSTR lpPath, const int& nSize );

extern DWORD GetLastErrorString( LPTSTR lpszMsg, size_t nSize );
extern void CheckPointerAddress( LPVOID lpvoid , const char *pFileName, int nLineNumber);


#endif//#if ( defined(_LOGDATA) || defined(PIPE_LOG) )


#if ( defined(_LOGDATA) || defined(PIPE_LOG) )
	#define CHECK_POINTER_N_LOG(lpvoid) CheckPointerAddress(lpvoid, __FILE__, __LINE__)
#else
	#define CHECK_POINTER_N_LOG(lpvoid)
#endif//#if ( defined(_LOGDATA) || defined(PIPE_LOG) )


#endif//_LOG_INCLUDE_H_