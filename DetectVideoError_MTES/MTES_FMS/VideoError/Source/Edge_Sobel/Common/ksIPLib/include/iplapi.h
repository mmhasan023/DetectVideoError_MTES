#ifndef _IPL_API_H_INCLUDE_
#define _IPL_API_H_INCLUDE_

#include <vector>
#include <list>
#include "iplDefine.h"
#include "iplTypes.h"
#include "iplMemory.h"

//#include "iplHistoRGB12bitBin.h"
//#include "iplHistoGray8bitBin.h"

#include "ipl1DPulseEdgeDetection.h"
#include "ipl1DImpulseEdgeDetection.h"
#include "ipl1DImpulseEdgeDetectionRT.h"
#include "iplBlockElement.h"

//#include "iplFrame.h"
//#include "iplFrameEx.h"

#ifdef _OPENMP
	#include "omp.h"
#endif

using namespace std;


typedef vector<CIplPoint> VECTOR_POINT, *LPVECTOR_POINT;
typedef VECTOR_POINT::iterator VECTOR_POINTItor;

typedef vector<VECTOR_POINT> VECTOR_POINT_GROUP, *LPVECTOR_POINT_GROUP;
typedef VECTOR_POINT_GROUP::iterator VECTOR_POINT_GROUPItor;

typedef vector<CIplPointLabel> VECTOR_POINTLABEL, *LPVECTOR_POINTLABEL;
typedef VECTOR_POINTLABEL::iterator VECTOR_POINTLABELItor;

typedef vector<CIplfPoint> VECTOR_FPOINT, *LPVECTOR_FPOINT;
typedef VECTOR_FPOINT::iterator VECTOR_FPOINTItor;

typedef VECTOR_POINT VECTOR_EDGESEGMENT, *LPVECTOR_EDGESEGMENT;
typedef VECTOR_EDGESEGMENT::iterator VECTOR_EDGESEGMENTItor;

typedef vector<VECTOR_EDGESEGMENT> VECTOR_EDGE, *LPVECTOR_EDGE;
typedef VECTOR_EDGE::iterator VECTOR_EDGEItor;

typedef vector<CIplLine> VECTOR_LINE, *LPVECTOR_LINE;
typedef VECTOR_LINE::iterator VECTOR_LINEItor;

typedef vector<VECTOR_LINE> VECTOR_LINE_GROUP, *LPVECTOR_LINE_GROUP;
typedef VECTOR_LINE_GROUP::iterator VECTOR_LINE_GROUPItor;

typedef vector<CIplLineExtension> VECTOR_LINEEX, *LPVECTOR_LINEEX;
typedef VECTOR_LINEEX::iterator VECTOR_LINEEXItor;


typedef vector<CIplRect> VECTOR_RECT, *LPVECTOR_RECT;
typedef VECTOR_RECT::iterator VECTOR_RECTItor;

/*
#if !defined(_LIB) && !defined(_IPL_25CFA3BB_4E3B_433b_9FFB_A8A53FE6C610)
#ifndef WIN64
	#if defined(_DEBUG)
		#pragma comment(lib,"ksIPLibD.lib")
	#else
		#pragma comment(lib,"ksIPLibR.lib")
	#endif
#else
	#if defined(_DEBUG)
		#pragma comment(lib,"ksIPLib64D.lib")
	#else
		#pragma comment(lib,"ksIPLib64R.lib")
	#endif
#endif
#endif
*/

int           _IPL_API _IPL_CALL iplGetVersion         ( int* pnFirst, int* pnSecond, int* pnThird );

#ifdef _OPENMP
void          _IPL_API _IPL_CALL iplSetNumberOfThreasds( IN const int& nNumberOfThreasds );
int           _IPL_API _IPL_CALL iplSetOptimalThreasds ( IN const int& nHeight );
#endif

float         _IPL_API _IPL_CALL fast_atan2f           ( float y, float x );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Conner detect
HCORNERDETECT _IPL_API _IPL_CALL iplCornerDetectOpen   ( int nWidth, int nHeight, int nBarrier );
int           _IPL_API _IPL_CALL iplCornerDetect       ( HCORNERDETECT  hCorner, const BYTE* pBuffer, VECTOR_POINT& vectorPOINT );
int           _IPL_API _IPL_CALL iplCornerDetectBlock  ( HCORNERDETECT  hCorner, const BYTE* pBuffer, VECTOR_POINT& vectorPOINT );
BOOL          _IPL_API _IPL_CALL iplCornerDetectClose  ( HCORNERDETECT& hCorner );

int _IPL_API _IPL_CALL ipl_corner_detect               ( IN const BYTE* pBuffer, int nWidth, int nHeight, VECTOR_POINT& vectorLPPOINT, int nBarrier=30);
//Conner detect
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _IPL_API _IPL_CALL ipl_RGBToGray                   ( OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight, int nBytes=3);
int _IPL_API _IPL_CALL ipl_RGBToGrayAverage            ( OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight, int nBytes=3);
int _IPL_API _IPL_CALL ipl_RGBToGrayRGB                ( OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes=3);
int _IPL_API _IPL_CALL ipl_RGBToGrayBGR                ( OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes=3);
int _IPL_API _IPL_CALL ipl_IsBlack                     ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, int nBytes=3);
int _IPL_API _IPL_CALL ipl_FilterLowPass3x3Gray        ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pDst );
int _IPL_API _IPL_CALL ipl_Flip                        ( IN const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes);
int _IPL_API _IPL_CALL ipl_ApplyFilters3x3Gray         ( IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, IN DWORD dwFilterFlag, OUT LPIPLFILTERRESULT lpResult );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sobel Edge
int _IPL_API _IPL_CALL ipl_FilterSobelMagnitude3x3Gray ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pDst );
int _IPL_API _IPL_CALL ipl_FilterSobelPhase3x3Gray     ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPWORD pDst );
int _IPL_API _IPL_CALL ipl_FilterSobel3x3Gray          ( IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT short* pGx, OUT short* pGy );
int _IPL_API _IPL_CALL ipl_FilterSobelDevide3x3Gray    ( IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT LPFLOAT pDest );
int _IPL_API _IPL_CALL ipl_FilterSobelMagNPhase3x3Gray ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pMagnitude, OUT LPWORD pPhase );

int _IPL_API _IPL_CALL iplSobel8Hypotenuse             ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel8Hypotenuse             ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel8RightAngle             ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel8RightAngle             ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int _IPL_API _IPL_CALL iplSobel60Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel60Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel60RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel60RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int _IPL_API _IPL_CALL iplSobel16Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel16Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel16RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int _IPL_API _IPL_CALL iplSobel16RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int _IPL_API _IPL_CALL iplSobelMagNPhase60Gray         ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold = 20 );
int _IPL_API _IPL_CALL iplSobelMagNPhase60Gray         ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int _IPL_API _IPL_CALL iplEraseAreaPhase16             ( IN OUT LPBYTE lpData, int nWidth, int nHeight, float fRatioThreshold, int nPixelCountThreshold );
int _IPL_API _IPL_CALL iplEraseAreaPhase16             ( IN OUT LPBYTE lpSource, LPBYTE lpDestination, int nWidth, int nHeight, float fRatioThreshold, int nPixelCountThreshold );

//Sobel Edge
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _IPL_API _IPL_CALL iplGetDifferCountGray           ( IN const LPBYTE lpBuf1, IN const LPBYTE lpBuf2, IN int nWidth, IN int nHeight, IN int nNoiseLevel);
int _IPL_API _IPL_CALL ipl_GenerateLBPGray             ( IN const LPBYTE pSrc, int nWidth, int nHeight, OUT LPBYTE pLBPBuffer, int nBarrier=30);
int _IPL_API _IPL_CALL ipl_BlockCornerFilter           ( IN LPVECTOR_POINT vInPoints, OUT LPVECTOR_POINT vOutPoints, IN int nFilterSize=50, eSCAN_DIRECTION eDir=_eBOTH);
int _IPL_API _IPL_CALL ipl_GenerateLineLBPGray         ( IN const LPBYTE pSrc, int nWidth, int nHeight, OUT LPBYTE pLBPBuffer);

//pCopyedSrc에는 255를 254로 변환하여 입력 한다.
int _IPL_API _IPL_CALL ipl_BlockDetect                 ( IN LPBYTE pCopyedSrc, int nWidth, int nHeight, OUT LPLIST_BLOCK lpListBlock, IN BYTE byteBarrier=30, IN INT nMaxBlockSize=32 );
int _IPL_API _IPL_CALL iplGetLBPCount5X5Diagonal       ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 50 );
int _IPL_API _IPL_CALL iplGetLBPCount5X5Diagonal       ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, BYTE nBarrier = 50 );
int _IPL_API _IPL_CALL iplGetLBPCount5X5_H_V           ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 200 );
int _IPL_API _IPL_CALL iplGetLBPCount5X5_H_V           ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, BYTE nBarrier = 200 );

int _IPL_API _IPL_CALL iplImageSubtraction             ( IN const LPBYTE pSrc1, IN const LPBYTE pSrc2, OUT LPBYTE pDst, INT nSize, const INT& nWidth, const INT& nHeight );
int _IPL_API _IPL_CALL iplImageBitAnd                  ( IN const LPBYTE pSrc1, IN const LPBYTE pSrc2, OUT LPBYTE lpDst, INT nSize, const INT& nWidth, const INT& nHeight );
int _IPL_API _IPL_CALL iplGetDCTCodeBlockCount5X5      ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrierHigh=200, BYTE nBarrierLow=50 );
int _IPL_API _IPL_CALL iplGetDCTCodeBlockCount5X5      ( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, BYTE nBarrierHigh=200, BYTE nBarrierLow=50 );
int _IPL_API _IPL_CALL ipl_GetLBPInterlaceCountGray    ( IN const LPBYTE pSrcGray, int nWidth, int nHeight, int nBarrier=30);
int _IPL_API _IPL_CALL iplGetHorizontalLine            ( const LPBYTE  lpSubtractImg          ,
														 const int&    nWidth                 ,
														 const int&    nHeight                ,
														 LPVECTOR_LINE lpvLines               ,//OUT
														 FLOAT         fMinLenghtRate   = 0.5f,
														 BYTE          byteHeighBarrier = 70  , 
														 BYTE          byteLowBarrier   = 10  , 
														 int           nSeedCount       = 6   );
void _IPL_API _IPL_CALL iplStripeLetterboxFilter       ( IN const LPBYTE lpSrcRGB, IN OUT LPVECTOR_LINE lpvLines, const int& nWidth, const int& nHeight );
void _IPL_API _IPL_CALL iplStripeSingleColorLineFilter ( IN const LPBYTE lpSrcRGB, IN OUT LPVECTOR_LINE lpvLines, const int& nWidth, const int& nHeight );


float _IPL_API _IPL_CALL iplSkinColorDetectRemainSkin  (       BYTE* pSrcBGR, const int& nWidth, const int& nHeight, const int& nBytes );//Must Input Straight Image.
																																		 //Backgroung Marking 0.
																																		 //Max return value is 100
float _IPL_API _IPL_CALL iplSkinColorDetectGetScore    ( const BYTE* pSrcBGR, const int& nWidth, const int& nHeight, const int& nBytes );//Must Input Straight Image.
																																		 //Max return value is 100



#ifdef _OPENMP
int _IPL_API _IPL_CALL ipl_FilterLowPass3x3GrayOMP    (IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pDst );
#endif

void _IPL_API _IPL_CALL iplEdgeVertical_2x1  ( const LPBYTE lpSrcGray, LPBYTE lpDst, const INT& nWidth, const INT& nHeight, const INT& nSize );
void _IPL_API _IPL_CALL iplEdgeHorizontal_1x2( const LPBYTE lpSrcGray, LPBYTE lpDst, const INT& nWidth, const INT& nHeight, const INT& nSize );

//Low contrast
int  _IPL_API _IPL_CALL iplGetLowContrastCount( IN  LPBYTE lpRGB, 
												OUT int*   pnLowCount, int* pnHeighCount,
												IN  int    nWidth, int nHeight, int nBytes = 3, 
												double dLowThreshold = 40.0, double dHighThreshold = 200.0 );
//Freeze Frame
int  _IPL_API _IPL_CALL iplGetDifferCount     ( LPBYTE lpBufCurImg    ,//Applied lowpass filter gray image
											    LPBYTE lpBufBeforeImg ,//Applied lowpass filter gray image
											    const  INT&  nInWidth ,
											    const  INT&  nInHeight,
											    const  BYTE& byteNoise=12 );

//Block Stripe
int  _IPL_API _IPL_CALL iplDeteceStripe       ( const LPBYTE  lpSrc           ,//Applied bit and gray image
											    const int&    nWidth          ,
												const int&    nHeight         ,
												LPVECTOR_LINE lpvLines        ,
												int           nLowBarrier = 10,
												int           nHighBarrier= 40,
												int           nMaxValley  = 30);
void _IPL_API _IPL_CALL iplMergeNearHorizontalLine( IN LPVECTOR_LINE lpvLine, 
												    OUT LPVECTOR_LINE_GROUP lpvLineGroup, 
													INT nLineThickness =2 );


#endif//_IPL_API_H_INCLUDE_
