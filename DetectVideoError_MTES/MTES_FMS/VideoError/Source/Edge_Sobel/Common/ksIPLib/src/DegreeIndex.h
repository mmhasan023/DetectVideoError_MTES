//Applied 3x3 mask operator
//by Kiok Ahn, 2010.10.30
//
// 2011.12.30 Add 60 index Functions
//
//

//Example - Sobel operator
//
// Gx =  |-1  0  +1|
//       |-2  0  +2|     * ( Input image )
//       |-1  0  +1|
//
// Gy =  |-1 -2  +1|
//       | 0  0   0|     * ( Input image )
//       |+1 +2  +1|

#ifndef _DEGREE_INDEX_H_INCLUDE_
#define _DEGREE_INDEX_H_INCLUDE_


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Phase index is like under chart
//   \ 2 /
//  4  X  0
//   / 6 \
//
int GetDegreeIndex8Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
int GetDegreeIndex8Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex );

// Phase index is like under chart
//   \ 15 /
//  30 X  0
//   / 45 \
//
int GetDegreeIndex60Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex );
int GetDegreeIndex60Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Phase index is like under chart
//  2 | 1
//  __|__
//    |
//  3 | 4
int GetDegreeIndex8RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
int GetDegreeIndex8RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex );

// Phase index is like under chart
//  2 | 1
//  __|__
//    |
//  3 | 4
int GetDegreeIndex60RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex );
int GetDegreeIndex60RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Phase index is like under chart
//   \ 4 /
//  8  X  0
//  / 12 \
//
int GetDegreeIndex16Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
int GetDegreeIndex16Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex );

// Phase index is like under chart
//  2 | 1
//  __|__
//    |
//  3 | 4
int GetDegreeIndex16RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex );
int GetDegreeIndex16RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif//_DEGREE_INDEX_H_INCLUDE_