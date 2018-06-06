//iplFrameEx.h
#ifndef _IPL_FRAME_EXTENSION_H_INCLUDE_
#define _IPL_FRAME_EXTENSION_H_INCLUDE_

#include "iplFrame.h"

class CIplFrameEx : public CIplFrame
{
public:
	CIplFrameEx(void);
	CIplFrameEx(const CIplFrameEx& op);
	CIplFrameEx(LPBITMAPINFOHEADER lpBih, LPBYTE lpData, INT nDataSize);
	CIplFrameEx(LPBITMAPINFOHEADER lpBih, LPBYTE lpData, INT nDataSize, CHistoRGB12bitBin* pHistogram);
	CIplFrameEx(INT nWidth, INT nHeight , LPBYTE lpData, INT nDataSize);
	CIplFrameEx(INT nWidth, INT nHeight , INT nBytes=3);
	virtual ~CIplFrameEx(void);

public:

	void operator=(const CIplFrameEx& op);

	void SetData       ( 
		LPBITMAPINFOHEADER lpBih             , 
		LPBYTE             lpData            , 
		INT                nDataSize         , 
		CHistoRGB12bitBin* pHistogram        ,
		double             dblSampleTime     ,
		int                nFrameNo          ,
		LPBYTE             lpGray            ,
		LPBYTE             lpGrayLowPass     ,
//		LPBYTE             lpGraySobelMag    ,
//		LPWORD             lpGraySobelPhs    ,
		DWORD              dwGraySize        ,
		DWORD              dwGrayLowPassSize );


//	BOOL   ComputeBaseInfo   ( void );//기본 연산, 히스토그램, 그레이 이미지.
	BOOL   ComputeBaseInfo   ( const DWORD& dwProcessingFlag = 0xFFFFFFFF );//기본 연산, 히스토그램, 그레이 이미지.

	LPBYTE GetGrayBuffer           ( void ){return m_lpGray           ;};// 프레임의 흑백 영상 데이터 획득
	LPBYTE GetGrayLowPassBuffer    ( void ){return m_lpGrayLowPass    ;};// 프레임의 Lowpass Filter 적용 영상 획득
	DWORD  GetGrayBufferSize       ( void ){return m_dwGraySize       ;};// 프레임의 흑백 영상 데이터 크기 획득
//	LPBYTE GetGraySobelMagnitude   ( void ){return m_lpGraySobelMag   ;};//magnitude
//	LPWORD GetGraySobelDirection   ( void ){return m_lpGraySobelPhs   ;};//direction

protected:
	inline void GrayBufferAlloc         ( const DWORD& dwSize );
	inline void GrayLowPassBufferAlloc  ( const DWORD& dwSize );
	inline void GrayBufferInit          ( void );
	inline void GrayBufferRelease       ( void );
	inline void GrayLowPassBufferRelease( void );

protected:
	DWORD         m_dwGraySize       ;
	DWORD         m_dwGrayLowPassSize;

	LPBYTE        m_lpGray           ;
	LPBYTE        m_lpGrayLowPass    ;
//	LPBYTE        m_lpGraySobelMag;//magnitude
//	LPWORD        m_lpGraySobelPhs;//direction

////////////////////////////////////////////////////////////////////
//Support Letterbox
protected:
	IPLRECT       m_rectLetterbox;
public:
	void   SetLetterbox( const IPLRECT& letterbox );
	void   GetLetterbox( LPIPLRECT lpLetterbox );
//Support Letterbox
////////////////////////////////////////////////////////////////////

protected:
	void Release       ( void                );
};

#endif //_IPL_FRAME_EXTENSION_H_INCLUDE_