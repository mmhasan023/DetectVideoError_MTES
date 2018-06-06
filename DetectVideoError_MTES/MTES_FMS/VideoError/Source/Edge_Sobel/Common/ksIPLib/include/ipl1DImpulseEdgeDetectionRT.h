//ipl1DImpulseEdgeDetection.h
#ifndef _1D_SIGNAL_IMPULSE_EDGE_DETECTION_RELA_TIME_H_INCLUDE_
#define _1D_SIGNAL_IMPULSE_EDGE_DETECTION_RELA_TIME_H_INCLUDE_

#include "iplDefine.h"


//#define _SIZE_VERTICAL_   0
//#define _SIZE_HORIZONTAL_ 1




//T is only base type, int, long , float, double
//상기 기본 형으로 template를 강제 할 수있는지.
//template <class T>, template class로 교체.
class _IPL_API C1DImpulseEdgeDetectionRT
{
public:
	C1DImpulseEdgeDetectionRT();
	C1DImpulseEdgeDetectionRT(const int& nWindowSize);
	//nWindowSize   : process window size
	//nTotalCount   : signal total count, 차후에는 전체 신호를 넣을 건지, 원형 큐를 쓸건지 선택. 원형 큐의 크리는 입력.
	//tInitVarience : Initialize Variance

	~C1DImpulseEdgeDetectionRT();

protected:
	int   m_nWindowSize    ;
	int   m_nWindowHalfSize;
	UINT  m_nSubSum        ;
	int   m_nTargetFrame   ;

	unsigned char m_nCurPointer;
	unsigned char m_nStartPointer;
	unsigned char m_nUsingNum;
	unsigned char m_nCurNum;

	/*T**/UINT* m_pValue;			// i 째 신호와 i-1 째 신호 사이 거리
	/*T**/UINT* m_pConv;			// i 째 신호에서 window에서의 평균값
	/*T**/UINT* m_pVariance;		// i 째 신호에서 window에서의 표준분산

protected:
	BOOL CalcVarience(int nFrame);
protected:
	UINT DetectBoundary(int nUpperRate, int nLowestRate);
	void Reset(const int& nWindowSize);


public:
	void SetWindowSize(int nWindowSize);
	//경계에서 IPL1D_DETECT return.
	int SetValue(int nVal, int nUpperRate=400/* =400 */, int nLowestRate=25/* =25 */);

//	void GetShiftingValue(unsigned int nSize, unsigned int nHori_orVerti, unsigned int* nShiftVal);

	//각각 함수에 대한 설명 보충.
	//필요치 않으면 제거.
	UINT GetDistance(int index);
	UINT GetConv    (int index);
	UINT GetVarience(int index);
	//UINT GetBoundary();

	void GetCurrentValue(UINT* pnBoundary, double*  pdfirstValue, double* pdsecondeValue);
	UINT GetTargetValue (int nIndex=0);//abs(nIndex)<=m_nWindowHalfSize

protected:

	UINT   m_nBoundary;
	double m_dfirstValue;
	double m_dsecondeValue;
};

#endif//_1D_SIGNAL_IMPULSE_EDGE_DETECTION_RELA_TIME_H_INCLUDE_