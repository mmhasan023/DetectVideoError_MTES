//ipl1DImpulseEdgeDetection.h
#ifndef _1D_SIGNAL_IMPULSE_EDGE_DETECTION_
#define _1D_SIGNAL_IMPULSE_EDGE_DETECTION_

#include "iplDefine.h"

//#define THRESOLD_VARIENCE_WEIGHT		1
//#define THRESOLD_VARIENCE				0.1
//#define THRESOLD_SHOT_INTERVAL			5
//#define THRESOLD_ATTRATION_RATIO		1


//T is only base type, int, long , float, double
//상기 기본 형으로 template를 강제 할 수있는지.
//template <class T>, template class로 교체.
class _IPL_API C1DImpulseEdgeDetection
{
protected:
	int        m_nWindowSize;
	UINT       m_nSubSum;
	UINT       m_nStartGradientShot;
	UINT       m_nThresoldVarience;	
	UINT       m_nGradientMean;
	//UINT     m_nPrevShotBoundary;
	int        m_nTargetFrame;
	/*T*/int   m_nCurrentNum;
	UINT       m_nTotalCount;

	/*T**/UINT* m_pValue;			// i 째 신호와 i-1 째 신호 사이 거리
	/*T**/UINT* m_pConv;			// i 째 신호에서 window에서의 평균값
	/*T**/UINT* m_pVariance;		// i 째 신호에서 window에서의 표준분산

	eDETEC_DIRECTION m_eDirection;

protected:
	BOOL CalcVarience(int nFrame);
protected:
	UINT DetectBoundary(int nFrame, int nUpperRate, int nLowestRate, int& nFailFrame);

public:
	//경계에서 IPL1D_DETECT return.
	int SetValue(int val, int currentFrameNum, int& nTargetFrame, int& nFailFrame, int nUpperRate=400, int nLowestRate=25);

	//각각 함수에 대한 설명 보충.
	//필요치 않으면 제거.
	UINT GetValue   (int index);
	UINT GetDistance(int index);
	UINT GetConv    (int index);
	UINT GetVarience(int index);
	UINT GetBoundary();

public:
	C1DImpulseEdgeDetection(  const int& nWindowSize, 
		                      const int& nTotalCount, 
							  const /*T&*/int& tInitVariance,
							  eDETEC_DIRECTION eDirection=_eDETEC_BOTH);
	//nWindowSize   : process window size
	//nTotalCount   : signal total count, 차후에는 전체 신호를 넣을 건지, 원형 큐를 쓸건지 선택. 원형 큐의 크리는 입력.
	//tInitVarience : Initialize Variance

	~C1DImpulseEdgeDetection(void);
};

#endif//_1D_SIGNAL_IMPULSE_EDGE_DETECTION_