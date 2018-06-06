#ifndef _IPL_EDGE_SOBEL_H_INCLUDE_
#define _IPL_EDGE_SOBEL_H_INCLUDE_
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sobel Edge
int ipl_FilterSobelMagnitude3x3Gray ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pDst );
int ipl_FilterSobelPhase3x3Gray     ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPWORD pDst );
int ipl_FilterSobel3x3Gray          ( IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT short* pGx, OUT short* pGy );
int ipl_FilterSobelDevide3x3Gray    ( IN const LPBYTE pSrc , IN int nWidth, IN int nHeight, OUT LPFLOAT pDest );
int ipl_FilterSobelMagNPhase3x3Gray ( IN const LPBYTE pSrc , IN int nSrcWidth, IN int nSrcHeight, OUT LPBYTE pMagnitude, OUT LPWORD pPhase );

int iplSobel8Hypotenuse             ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel8Hypotenuse             ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel8RightAngle             ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel8RightAngle             ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int iplSobel60Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel60Hypotenuse            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel60RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
int iplSobel60RightAngle            ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);

int iplSobelMagNPhase60Gray         ( IN const LPBYTE pSrc , OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold = 20 );
int iplSobelMagNPhase60Gray         ( IN const LPBYTE pSrc , OUT LPBYTE pDstMagnitude, OUT LPBYTE pDstPhase, IN int nSrcWidth, IN int nSrcHeight, IN int nThreshold=20);
//Sobel Edge
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif//_IPL_EDGE_SOBEL_H_INCLUDE_