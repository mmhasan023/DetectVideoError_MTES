//ImpulseDetectByMedian.h
//1D Impulse Signal Detect By Median Value
//by Kiok Ahn , 2012.02.17

#ifndef IMPULSE_DETECT_BY_MEDIAN_H_INCLUDE
#define IMPULSE_DETECT_BY_MEDIAN_H_INCLUDE

//#include "iplApi.h"
#include <list>

using namespace std;
typedef list<int> LIST_INT, *LPLIST_INT;
typedef LIST_INT::iterator LIST_INTItor;

class CImpulseDetectByMedian
{
public:
	CImpulseDetectByMedian(const size_t& nWindowSize, const float& fDetectRatio=2.f);
	~CImpulseDetectByMedian();

public:
	int SetData( const int& nData );

protected:
	size_t   m_nWindowSize  ;
	size_t   m_nHalfWindow  ;
	LIST_INT m_listDatas    ;
	float    m_fDetectRatio;
};

#endif//IMPULSE_DETECT_BY_MEDIAN_H_INCLUDE