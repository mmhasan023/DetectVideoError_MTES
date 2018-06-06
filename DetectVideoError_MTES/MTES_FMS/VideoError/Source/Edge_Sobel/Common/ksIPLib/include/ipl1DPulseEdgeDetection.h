//ipl1DPulseEdgeDetection.h
#ifndef _1D_SIGNAL_PULSE_EDGE_DETECTION_
#define _1D_SIGNAL_PULSE_EDGE_DETECTION_

#include "ipl1DImpulseEdgeDetection.h"

class C1DPulseEdgeDetection : public C1DImpulseEdgeDetection
{
protected:
	UINT m_nPrevShotBoundary;

protected:
	UINT DetectBoundary(int nCurrent);

public:
	int SetValue(int val, int currentFrameNum, int& nTargetFrame);


public:
	C1DPulseEdgeDetection(const int& nWindowSize, const int& nTotalCount, const /*T&*/int& tInitVariance);
	//nWindowSize   : process window size
	//nTotalCount   : signal total count, 차후에는 전체 신호를 넣을 건지, 원형 큐를 쓸건지 선택. 원형 큐의 크리는 입력.
	//tInitVarience : Initialize Variance

	~C1DPulseEdgeDetection(void);

};

#endif //_1D_SIGNAL_PULSE_EDGE_DETECTION_
