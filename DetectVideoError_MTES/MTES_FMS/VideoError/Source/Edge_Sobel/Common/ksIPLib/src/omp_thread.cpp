#ifdef _OPENMP

#include "omp.h"
#include "iplDefine.h"
#include "iplapi.h"
#include "omp_thread.h"

int g_nIplNumberOfThreasds =  min( 8, omp_get_num_procs() );

void iplSetNumberOfThreasds( IN const int& nNumberOfThreasds )
{
	g_nIplNumberOfThreasds = nNumberOfThreasds;
}

int  iplSetOptimalThreasds ( IN const int& nHeight )
{
	int nNumOfOMPThread = omp_get_num_procs();

	if     ( nHeight >= 960 )
		nNumOfOMPThread = min( 8, nNumOfOMPThread ) ;
	else if( nHeight >= 720 )
		nNumOfOMPThread = min( 4, nNumOfOMPThread ) ;
	else if( nHeight >= 480 )
		nNumOfOMPThread = min( 2, nNumOfOMPThread ) ;
	else 
		nNumOfOMPThread = 1 ;

	iplSetNumberOfThreasds( nNumOfOMPThread );
	return nNumOfOMPThread;
}

#endif
