#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_

#ifndef MAX_PATH2
	#define MAX_PATH2 520
#endif

#if defined(_DEBUG)

extern void _memtrace_LOGOUT (TCHAR *szMsg, ...);
extern int  _memtrace_SET_SUBFOLDER( const TCHAR* lpSubFolderName );//저장 될 하위 폴더 이름 지정, CApp::InitInstance등에서 한번만 수행 한다.

#endif


#endif//_LOG_INCLUDE_H_