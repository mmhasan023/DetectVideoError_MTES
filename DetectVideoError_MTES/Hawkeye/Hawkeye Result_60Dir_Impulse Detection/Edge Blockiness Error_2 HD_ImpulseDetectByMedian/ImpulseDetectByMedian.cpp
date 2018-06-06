#include "ImpulseDetectByMedian.h"
#include <algorithm>
#include "iplDefine.h"

CImpulseDetectByMedian::CImpulseDetectByMedian(const size_t& nWindowSize, const float& fDetectRatio)
{
	m_nWindowSize  = nWindowSize ;
	m_fDetectRatio = fDetectRatio;
	m_nHalfWindow  = nWindowSize / 2;
}

CImpulseDetectByMedian::~CImpulseDetectByMedian()
{
}

int CImpulseDetectByMedian::SetData( const int& nData )
{
	m_listDatas.push_back( nData );

	if( m_listDatas.size() > m_nWindowSize )
		m_listDatas.pop_front();

	if( m_listDatas.size() < m_nWindowSize )
		return IPL1D_SMALL;

	LIST_INT listTmp;
	listTmp = m_listDatas;
	listTmp.sort();

	LIST_INTItor itorMedian = listTmp.begin();
	LIST_INTItor itorTarget = m_listDatas.begin();

	for( size_t i=0 ; i<m_nHalfWindow ; i++ )
	{
		itorMedian++;
		itorTarget++;
	}

	if( float(*itorMedian) * m_fDetectRatio < float(*itorTarget) )
		return IPL1D_DETECT_HIGH;

	return IPL1D_CONTINUE;
}

