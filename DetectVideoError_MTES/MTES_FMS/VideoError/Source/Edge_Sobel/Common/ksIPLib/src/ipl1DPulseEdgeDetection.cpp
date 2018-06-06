//#include "stdafx.h"
#include "ipl1DPulseEdgeDetection.h"

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif



//nWindowSize   : process window size
//nTotalCount   : signal total count, 차후에는 전체 신호를 넣을 건지, 원형 큐를 쓸건지 선택. 원형 큐의 크리는 입력.
//tInitVarience : Initialize Variance
C1DPulseEdgeDetection::C1DPulseEdgeDetection(const int& nWindowSize, const int& nTotalCount, const /*T&*/int& tInitVariance)
:C1DImpulseEdgeDetection(nWindowSize, nTotalCount, tInitVariance)
{
	m_nPrevShotBoundary = 0;
}

C1DPulseEdgeDetection::~C1DPulseEdgeDetection(void)
{

}

int C1DPulseEdgeDetection::SetValue(int val, int currentFrameNum, int& nTargetFrame)
{
	//거리 차이를 저장한다.
	m_pValue[currentFrameNum] = val;
	m_nCurrentNum=currentFrameNum;
	m_nTargetFrame = currentFrameNum - m_nWindowSize / 2;
	nTargetFrame=m_nTargetFrame;

	//입력받은 프레임 값보다 작으면
	if (  currentFrameNum < m_nWindowSize )
	{
		m_nSubSum += val;	
		//평균값을 구하고 저장한다.
		m_pConv[currentFrameNum] = m_nSubSum / (currentFrameNum + 1);

		return IPL1D_SMALL;
	}

	//사용자가 지정한 프레임이 지나면 첫번째 더했던 값을 지우고
	m_nSubSum -= m_pValue[currentFrameNum - m_nWindowSize];
	//새로구한 차를 더한다
	m_nSubSum += val;

	//분산을 구한다
	CalcVarience(m_nTargetFrame);

	// 샷 경계 검출
	if(m_nTargetFrame == 0)
		return IPL1D_NONE;//IPL1D_DETECT;

	int nShotBoundary= DetectBoundary(m_nTargetFrame - 1);

	//검출된 경우 IPL1D_NONE 반환
	if( nShotBoundary > 0 )
		return IPL1D_DETECT;//IPL1D_NONE;

	return IPL1D_CONTINUE;
}

UINT C1DPulseEdgeDetection::DetectBoundary(int nFrame)
{
	UINT nThreshold = 0;
	UINT nBoundary = 0;

	//타겟프레임-1의 임계값
	nThreshold = m_pConv[nFrame] + THRESOLD_VARIENCE_WEIGHT * m_pVariance[nFrame];

	// 급격한 경계 검출
	if(m_pValue[nFrame] > nThreshold)
	{
		//		if(m_pConv[nFrame - 1] <= m_pConv[nFrame] &&
		//		m_pConv[nFrame + 1] <= m_pConv[nFrame])
		{
			m_nStartGradientShot = 0;
			nBoundary = nFrame;
		}
	}
	else
	{
		if(m_nStartGradientShot > 0)
		{
			if(m_pConv[nFrame] < m_nGradientMean && 
				m_pVariance[nFrame] < m_nThresoldVarience &&
				m_pConv[nFrame - 1] > m_pConv[nFrame + 1])
			{
				//				nFrame = (m_nStartGradientShot + nFrame) / 2;
				m_nStartGradientShot = 0;
				m_nGradientMean = 0;
				nBoundary = nFrame;
			}
		}
		else
		{
			if(m_nGradientMean > 0)
			{
				if(m_pConv[nFrame] < m_nGradientMean)
					m_nGradientMean = 0;
			}
			else if(m_pVariance[nFrame] > m_nThresoldVarience && 
				m_pConv[nFrame - 1] < m_pConv[nFrame + 1])
			{
				m_nStartGradientShot = nFrame;
				m_nGradientMean = m_pConv[nFrame];
			}
		}
	}

	if(nBoundary == 0)
		return 0;

	if(nBoundary - m_nPrevShotBoundary < THRESOLD_SHOT_INTERVAL)
	{
		m_nPrevShotBoundary = nBoundary;
		return 0;
	}

	m_nPrevShotBoundary = nBoundary;
	return nBoundary;
}
