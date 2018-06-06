//Memory Trace
//by Kiok ahn, 20101110

#ifdef _DEBUG

void* __cdecl   operator new(size_t nSize, const char *pFileName, int nLineNumber);
#define DBG_NEW new(__FILE__, __LINE__)

void __cdecl operator delete( void *p );
void __cdecl operator delete[](void* p);

extern void mem_trace_dump( void );

#endif//_DEBUG