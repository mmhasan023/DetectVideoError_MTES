//Memory Trace
//by Kiok ahn, 20101110

#ifdef _DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>
#include "tchar.h"
#include "mem_trace.h"

#include "Windows.h"

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef LPCTSTR
#define LPCTSTR   const TCHAR*
#endif

#ifndef LPTSTR
#define LPTSTR    TCHAR*
#endif

#ifndef MAX_PATH2
#define MAX_PATH2 520
#endif

#include "mem_trace_log.h"
using namespace std;

#pragma warning(disable:4995)
#pragma warning(disable:4996)

int g_init_SET_SUBFOLDER = _memtrace_SET_SUBFOLDER( _T("MEM_TRACE") );

// Tracing Utility 

typedef struct {
	void*	pAddress             ;
	size_t	nSize                ;
	char	szFileName[MAX_PATH2];
	int     nLineNumber          ;
} ALLOCATED_INFO, *LPALLOCATED_INFO;

typedef list<LPALLOCATED_INFO> AllocatedList;

AllocatedList *g_pAllocatedList;

void AddTrace(void* pAddress,  size_t nSize,  const char *pFileName, int nLineNumber)
{
	ALLOCATED_INFO *pInfo = NULL;

	if(!g_pAllocatedList) {
		g_pAllocatedList = new(AllocatedList);
	}

	pInfo = new(ALLOCATED_INFO);
	memset( pInfo, 0, sizeof( ALLOCATED_INFO) );

	pInfo->pAddress     = pAddress;
	pInfo->nLineNumber  = nLineNumber;
	pInfo->nSize        = nSize;
	strcpy(pInfo->szFileName, pFileName);
	cout<<pInfo->szFileName<<":"<<pInfo->nLineNumber<<endl;
	g_pAllocatedList->insert(g_pAllocatedList->begin(), pInfo);
};

void RemoveTrace( void* pAddress )
{
	AllocatedList::iterator i;

	if(!g_pAllocatedList)
		return;
	for(i = g_pAllocatedList->begin(); i != g_pAllocatedList->end(); i++)
	{
		LPALLOCATED_INFO lpInfo = (LPALLOCATED_INFO)(*i);
		if( lpInfo->pAddress == pAddress )
		{
			g_pAllocatedList->remove(lpInfo);
			delete lpInfo;
			break;
		}
	}
};

void* __cdecl operator new(size_t nSize, const char *pFileName, int nLineNumber)
{
	void *ptr = (void *)malloc(nSize);
	AddTrace( ptr, nSize, pFileName, nLineNumber);
	return(ptr);
};

void __cdecl operator delete(void *p)
{
	RemoveTrace( p );
	free(p);
};

void __cdecl operator delete[](void* p)
{
	RemoveTrace( p );
	free(p);
};

void LOG( char* pData )
{
	TCHAR szData[MAX_PATH2]={0};

#ifdef _UNICODE
	MultiByteToWideChar( CP_ACP, 0, pData, -1, szData, MAX_PATH2 );
#else
	strcpy(szData, pData);
#endif
	_memtrace_LOGOUT( szData );
}

void mem_trace_dump( void )
{
	AllocatedList::iterator i;
	size_t nTotalSize       = 0;
	char   szBuf[MAX_PATH2] ={0};

	if( !g_pAllocatedList )
	{
		LOG( ("Never allocation") );
		return;
	}

	for(i = g_pAllocatedList->begin(); i != g_pAllocatedList->end(); i++) 
	{
		LPALLOCATED_INFO lpInfo = (LPALLOCATED_INFO)(*i);
#ifdef WIN64
		DWORD dwFirst  = ((__int64)lpInfo->pAddress)>>32;
		DWORD dwSecond = ((__int64)lpInfo->pAddress)&0x00000000FFFFFFFF;
		sprintf(szBuf, ("%s : \t\tLINE %d,\t\tADDRESS 0x%08x%08x\t%d NOTFREED\r\n"),
			lpInfo->szFileName, lpInfo->nLineNumber, dwFirst, dwSecond, lpInfo->nSize);
#else
		sprintf(szBuf, ("%s : \t\tLINE %d,\t\tADDRESS 0x%08x\t%d NOTFREED\r\n"),
			lpInfo->szFileName, lpInfo->nLineNumber, (DWORD)(lpInfo->pAddress), lpInfo->nSize);
#endif
		LOG( szBuf );
		nTotalSize += lpInfo->nSize;
	}
	sprintf(szBuf, ("----------------------------------------------------------------------------------------------\r\n"));
	LOG( szBuf );
	if(!nTotalSize) 
	{
		sprintf(szBuf,("There are no MEMORY LEAKS\r\n") );
		LOG( szBuf );
	}
	else
	{
		sprintf(szBuf, ("Total UNFREED MEMORY: %d bytes\r\n"), nTotalSize);
		LOG( szBuf );
	}
};

/*
#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif

void main()
{
	char *ptr1;
	ptr1 = new char;
	delete ptr1;

	char *ptr;
	ptr = new char[10+1];
	//delete ptr;   // remove comments to find the memory leak.
	mem_trace_dump();
}
*/

#endif //_DEBUG