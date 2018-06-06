#include "DegreeIndex.h"
#include "stdlib.h"
#include "iplDefine.h"
#include <math.h>

/*
// Phase index is like under chart
//   \ 2 /
//   4 X 0
//   / 7 \

index degree    tan

06      292.500000      -2.414212
07      337.500000      -0.414214

00      22.500000        0.414214
01      67.500000        2.414214

02      112.500000      -2.414214
03      157.500000      -0.414214

04      202.500000       0.414214
05      247.500000       2.414212

*/
int GetDegreeIndex8Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex = 2;// 90
		else	       nDegreeIndex = 6;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 6;//-90==270
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 7;

		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex = 0;
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex = 1;
		else                              nDegreeIndex = 2;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 2;//90
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 3;
									   
		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex = 4;//180
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex = 5;
		else                              nDegreeIndex = 6;//270==-90
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex;

	return 0;
}

int GetDegreeIndex8Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex = 2;// 90
		else	       nDegreeIndex = 6;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 6;//-90==270
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 7;

		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex = 0;
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex = 1;
		else                              nDegreeIndex = 2;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 2;//90
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 3;
									   
		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex = 4;//180
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex = 5;
		else                              nDegreeIndex = 6;//270==-90
	}

	*pPhaseIndex  = nDegreeIndex;

	return 0;
}


/*
// Phase index is like under chart
//  2 | 1
//  __|__
//    |
//  3 | 4

index degree    tan
06      270.000000      -83858280.000000
07      315.000000      -1.000000

00      0.000000        0.000000
01      45.000000       1.000000

02      90.000000       -22877332.000000
03      135.000000      -1.000000

04      180.000000      0.000000
05      225.000000      1.000000
*/

int GetDegreeIndex8RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex = 2;// 90
		else	       nDegreeIndex = 6;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -1.0 ) nDegreeIndex = 6;//
		else if( fGyDivdeGx <  0.0 ) nDegreeIndex = 7;

		else if( fGyDivdeGx <  1.0 ) nDegreeIndex = 0;
		else                         nDegreeIndex = 1;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -1.0 ) nDegreeIndex = 2;
		else if( fGyDivdeGx <  0.0 ) nDegreeIndex = 3;
												   
		else if( fGyDivdeGx <  1.0 ) nDegreeIndex = 4;
		else                         nDegreeIndex = 5;
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex;

	return 0;
}


int GetDegreeIndex8RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex = 2;// 90
		else	       nDegreeIndex = 6;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -1.0 ) nDegreeIndex = 6;//
		else if( fGyDivdeGx <  0.0 ) nDegreeIndex = 7;

		else if( fGyDivdeGx <  1.0 ) nDegreeIndex = 0;
		else                         nDegreeIndex = 1;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -1.0 ) nDegreeIndex = 2;
		else if( fGyDivdeGx <  0.0 ) nDegreeIndex = 3;
												   
		else if( fGyDivdeGx <  1.0 ) nDegreeIndex = 4;
		else                         nDegreeIndex = 5;
	}


	*pPhaseIndex  = nDegreeIndex;

	return 0;
}

/*
int GetDegreeIndex60Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int nDegreeIndex60 = 0;
	int nMaginitude = int( sqrt( double(nGx*nGx + nGy*nGy) ) + 0.5 );
	if (nMaginitude > 255)
		nMaginitude = 255;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 = 15;// 90
		else	       nDegreeIndex60 = 45;//-90
	}
	else
	{
		double dbTheta = TO_DEGREE( atan( double(nGy)/double(nGx) ) );
		if( dbTheta<0 ) dbTheta + 360;

		nDegreeIndex60 = int( (60.0*dbTheta/360.0) + 0.5 );
	}

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex60;

	return 0;
}
*/

// Phase index is like under chart
//   \ 2 /
//   3 X 1
//   / 4 \
//
/*
45	273.000000	-19.081066
46	279.000000	- 6.313748
47	285.000000	- 3.732051
48	291.000000	- 2.605090
49	297.000000	- 1.962612
50	303.000000	- 1.539865
51	309.000000	- 1.234897
52	315.000000	- 1.000000
53	321.000000	- 0.809784
54	327.000000	- 0.649407
55	333.000000	- 0.509525
56	339.000000	- 0.383864
57	345.000000	- 0.267949
58	351.000000	- 0.158384
59	357.000000	- 0.052408

00	  3.000000	  0.052408
01	  9.000000	  0.158384
02	 15.000000	  0.267949
03	 21.000000	  0.383864
04	 27.000000	  0.509525
05	 33.000000	  0.649408
06	 39.000000	  0.809784
07	 45.000000	  1.000000
08	 51.000000	  1.234897
09	 57.000000	  1.539865
10	 63.000000	  1.962610
11	 69.000000	  2.605089
12	 75.000000	  3.732050
13	 81.000000	  6.313751
14	 87.000000	 19.081131

15	 93.000000	-19.081142
16	 99.000000	- 6.313752
17	105.000000	- 3.732051
18	111.000000	- 2.605089
19	117.000000	- 1.962611
20	123.000000	- 1.539865
21	129.000000	- 1.234897
22	135.000000	- 1.000000
23	141.000000	- 0.809784
24	147.000000	- 0.649408
25	153.000000	- 0.509526
26	159.000000	- 0.383864
27	165.000000	- 0.267949
28	171.000000	- 0.158384
29	177.000000	- 0.052408

30	183.000000	  0.052408
31	189.000000	  0.158384
32	195.000000	  0.267949
33	201.000000	  0.383864
34	207.000000	  0.509525
35	213.000000	  0.649408
36	219.000000	  0.809784
37	225.000000	  1.000000
38	231.000000	  1.234897
39	237.000000	  1.539865
40	243.000000	  1.962610
41	249.000000	  2.605090
42	255.000000	  3.732052
43	261.000000	  6.313749
44	267.000000	 19.081076
*/
int GetDegreeIndex60Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 = 15;// 90??
		else	       nDegreeIndex60 = 45;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -19.081066 ) nDegreeIndex60 = 45;//-90==270
		else if( fGyDivdeGx < - 6.313748 ) nDegreeIndex60 = 46;
		else if( fGyDivdeGx < - 3.732051 ) nDegreeIndex60 = 47;
		else if( fGyDivdeGx < - 2.605090 ) nDegreeIndex60 = 48;
		else if( fGyDivdeGx < - 1.962612 ) nDegreeIndex60 = 49;
		else if( fGyDivdeGx < - 1.539865 ) nDegreeIndex60 = 50;
		else if( fGyDivdeGx < - 1.234897 ) nDegreeIndex60 = 51;
		else if( fGyDivdeGx < - 1.0      ) nDegreeIndex60 = 52;
		else if( fGyDivdeGx < - 0.809784 ) nDegreeIndex60 = 53;
		else if( fGyDivdeGx < - 0.649407 ) nDegreeIndex60 = 54;
		else if( fGyDivdeGx < - 0.509525 ) nDegreeIndex60 = 55;
		else if( fGyDivdeGx < - 0.383864 ) nDegreeIndex60 = 56;
		else if( fGyDivdeGx < - 0.267949 ) nDegreeIndex60 = 57;
		else if( fGyDivdeGx < - 0.158384 ) nDegreeIndex60 = 58;
		else if( fGyDivdeGx < - 0.052408 ) nDegreeIndex60 = 59;

		else if( fGyDivdeGx <   0.052408 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <   0.158384 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <   0.267949 ) nDegreeIndex60 =  2;
		else if( fGyDivdeGx <   0.383864 ) nDegreeIndex60 =  3;
		else if( fGyDivdeGx <   0.509525 ) nDegreeIndex60 =  4;
		else if( fGyDivdeGx <   0.649408 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx <   0.809784 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx <   1.0      ) nDegreeIndex60 =  7;
		else if( fGyDivdeGx <   1.234897 ) nDegreeIndex60 =  8;
		else if( fGyDivdeGx <   1.539865 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <   1.962610 ) nDegreeIndex60 = 10;
		else if( fGyDivdeGx <   2.605089 ) nDegreeIndex60 = 11;
		else if( fGyDivdeGx <   3.732050 ) nDegreeIndex60 = 12;
		else if( fGyDivdeGx <   6.313751 ) nDegreeIndex60 = 13;
		else if( fGyDivdeGx <  19.081131 ) nDegreeIndex60 = 14;
		else                               nDegreeIndex60 = 15;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -19.081066 ) nDegreeIndex60 = 15;//90
		else if( fGyDivdeGx < - 6.313748 ) nDegreeIndex60 = 16;
		else if( fGyDivdeGx < - 3.732051 ) nDegreeIndex60 = 17;
		else if( fGyDivdeGx < - 2.605090 ) nDegreeIndex60 = 18;
		else if( fGyDivdeGx < - 1.962612 ) nDegreeIndex60 = 19;
		else if( fGyDivdeGx < - 1.539865 ) nDegreeIndex60 = 20;
		else if( fGyDivdeGx < - 1.234897 ) nDegreeIndex60 = 21;
		else if( fGyDivdeGx < - 1.0      ) nDegreeIndex60 = 22;
		else if( fGyDivdeGx < - 0.809784 ) nDegreeIndex60 = 23;
		else if( fGyDivdeGx < - 0.649407 ) nDegreeIndex60 = 24;
		else if( fGyDivdeGx < - 0.509525 ) nDegreeIndex60 = 25;
		else if( fGyDivdeGx < - 0.383864 ) nDegreeIndex60 = 26;
		else if( fGyDivdeGx < - 0.267949 ) nDegreeIndex60 = 27;
		else if( fGyDivdeGx < - 0.158384 ) nDegreeIndex60 = 28;
		else if( fGyDivdeGx < - 0.052408 ) nDegreeIndex60 = 29;
												   
		else if( fGyDivdeGx <   0.052408 ) nDegreeIndex60 = 30;//180
		else if( fGyDivdeGx <   0.158384 ) nDegreeIndex60 = 31;
		else if( fGyDivdeGx <   0.267949 ) nDegreeIndex60 = 32;
		else if( fGyDivdeGx <   0.383864 ) nDegreeIndex60 = 33;
		else if( fGyDivdeGx <   0.509525 ) nDegreeIndex60 = 34;
		else if( fGyDivdeGx <   0.649408 ) nDegreeIndex60 = 35;
		else if( fGyDivdeGx <   0.809784 ) nDegreeIndex60 = 36;
		else if( fGyDivdeGx <   1.0      ) nDegreeIndex60 = 37;
		else if( fGyDivdeGx <   1.234897 ) nDegreeIndex60 = 38;
		else if( fGyDivdeGx <   1.539865 ) nDegreeIndex60 = 39;
		else if( fGyDivdeGx <   1.962610 ) nDegreeIndex60 = 40;
		else if( fGyDivdeGx <   2.605089 ) nDegreeIndex60 = 41;
		else if( fGyDivdeGx <   3.732050 ) nDegreeIndex60 = 42;
		else if( fGyDivdeGx <   6.313751 ) nDegreeIndex60 = 43;
		else if( fGyDivdeGx <  19.081131 ) nDegreeIndex60 = 44;
		else                               nDegreeIndex60 = 45;//270==-90
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex60;

	return 0;
}

int GetDegreeIndex60Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 = 15;// 90??
		else	       nDegreeIndex60 = 45;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -19.081066 ) nDegreeIndex60 = 45;//-90==270
		else if( fGyDivdeGx < - 6.313748 ) nDegreeIndex60 = 46;
		else if( fGyDivdeGx < - 3.732051 ) nDegreeIndex60 = 47;
		else if( fGyDivdeGx < - 2.605090 ) nDegreeIndex60 = 48;
		else if( fGyDivdeGx < - 1.962612 ) nDegreeIndex60 = 49;
		else if( fGyDivdeGx < - 1.539865 ) nDegreeIndex60 = 50;
		else if( fGyDivdeGx < - 1.234897 ) nDegreeIndex60 = 51;
		else if( fGyDivdeGx < - 1.0      ) nDegreeIndex60 = 52;
		else if( fGyDivdeGx < - 0.809784 ) nDegreeIndex60 = 53;
		else if( fGyDivdeGx < - 0.649407 ) nDegreeIndex60 = 54;
		else if( fGyDivdeGx < - 0.509525 ) nDegreeIndex60 = 55;
		else if( fGyDivdeGx < - 0.383864 ) nDegreeIndex60 = 56;
		else if( fGyDivdeGx < - 0.267949 ) nDegreeIndex60 = 57;
		else if( fGyDivdeGx < - 0.158384 ) nDegreeIndex60 = 58;
		else if( fGyDivdeGx < - 0.052408 ) nDegreeIndex60 = 59;

		else if( fGyDivdeGx <   0.052408 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <   0.158384 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <   0.267949 ) nDegreeIndex60 =  2;
		else if( fGyDivdeGx <   0.383864 ) nDegreeIndex60 =  3;
		else if( fGyDivdeGx <   0.509525 ) nDegreeIndex60 =  4;
		else if( fGyDivdeGx <   0.649408 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx <   0.809784 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx <   1.0      ) nDegreeIndex60 =  7;
		else if( fGyDivdeGx <   1.234897 ) nDegreeIndex60 =  8;
		else if( fGyDivdeGx <   1.539865 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <   1.962610 ) nDegreeIndex60 = 10;
		else if( fGyDivdeGx <   2.605089 ) nDegreeIndex60 = 11;
		else if( fGyDivdeGx <   3.732050 ) nDegreeIndex60 = 12;
		else if( fGyDivdeGx <   6.313751 ) nDegreeIndex60 = 13;
		else if( fGyDivdeGx <  19.081131 ) nDegreeIndex60 = 14;
		else                               nDegreeIndex60 = 15;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -19.081066 ) nDegreeIndex60 = 15;//90
		else if( fGyDivdeGx < - 6.313748 ) nDegreeIndex60 = 16;
		else if( fGyDivdeGx < - 3.732051 ) nDegreeIndex60 = 17;
		else if( fGyDivdeGx < - 2.605090 ) nDegreeIndex60 = 18;
		else if( fGyDivdeGx < - 1.962612 ) nDegreeIndex60 = 19;
		else if( fGyDivdeGx < - 1.539865 ) nDegreeIndex60 = 20;
		else if( fGyDivdeGx < - 1.234897 ) nDegreeIndex60 = 21;
		else if( fGyDivdeGx < - 1.0      ) nDegreeIndex60 = 22;
		else if( fGyDivdeGx < - 0.809784 ) nDegreeIndex60 = 23;
		else if( fGyDivdeGx < - 0.649407 ) nDegreeIndex60 = 24;
		else if( fGyDivdeGx < - 0.509525 ) nDegreeIndex60 = 25;
		else if( fGyDivdeGx < - 0.383864 ) nDegreeIndex60 = 26;
		else if( fGyDivdeGx < - 0.267949 ) nDegreeIndex60 = 27;
		else if( fGyDivdeGx < - 0.158384 ) nDegreeIndex60 = 28;
		else if( fGyDivdeGx < - 0.052408 ) nDegreeIndex60 = 29;
												   
		else if( fGyDivdeGx <   0.052408 ) nDegreeIndex60 = 30;//180
		else if( fGyDivdeGx <   0.158384 ) nDegreeIndex60 = 31;
		else if( fGyDivdeGx <   0.267949 ) nDegreeIndex60 = 32;
		else if( fGyDivdeGx <   0.383864 ) nDegreeIndex60 = 33;
		else if( fGyDivdeGx <   0.509525 ) nDegreeIndex60 = 34;
		else if( fGyDivdeGx <   0.649408 ) nDegreeIndex60 = 35;
		else if( fGyDivdeGx <   0.809784 ) nDegreeIndex60 = 36;
		else if( fGyDivdeGx <   1.0      ) nDegreeIndex60 = 37;
		else if( fGyDivdeGx <   1.234897 ) nDegreeIndex60 = 38;
		else if( fGyDivdeGx <   1.539865 ) nDegreeIndex60 = 39;
		else if( fGyDivdeGx <   1.962610 ) nDegreeIndex60 = 40;
		else if( fGyDivdeGx <   2.605089 ) nDegreeIndex60 = 41;
		else if( fGyDivdeGx <   3.732050 ) nDegreeIndex60 = 42;
		else if( fGyDivdeGx <   6.313751 ) nDegreeIndex60 = 43;
		else if( fGyDivdeGx <  19.081131 ) nDegreeIndex60 = 44;
		else                               nDegreeIndex60 = 45;//270==-90
	}

	*pPhaseIndex  = nDegreeIndex60;

	return 0;
}



// Phase index is under chart
//  2 | 1
//  __|__
//    |
//  3 | 4
/*
45	270.000000	-83858280.000000
46	276.000000	-9.514374
47	282.000000	-4.704635
48	288.000000	-3.077682
49	294.000000	-2.246037
50	300.000000	-1.732051
51	306.000000	-1.376382
52	312.000000	-1.110612
53	318.000000	-0.900404
54	324.000000	-0.726543
55	330.000000	-0.577351
56	336.000000	-0.445228
57	342.000000	-0.324920
58	348.000000	-0.212557
59	354.000000	-0.105104
00  360.000000   0.000000

00	  0.000000	 0.000000
01	  6.000000	 0.105104
02	 12.000000	 0.212557
03	 18.000000	 0.324920
04	 24.000000	 0.445229
05	 30.000000	 0.577350
06	 36.000000	 0.726543
07	 42.000000	 0.900404
08	 48.000000	 1.110613
09	 54.000000	 1.376382
10	 60.000000	 1.732051
11	 66.000000	 2.246037
12	 72.000000	 3.077684
13	 78.000000	 4.704631
14	 84.000000	 9.514368

15	 90.000000	-22877332.000000
16	 96.000000	-9.514360
17	102.000000	-4.704632
18	108.000000	-3.077684
19	114.000000	-2.246037
20	120.000000	-1.732051
21	126.000000	-1.376382
22	132.000000	-1.110612
23	138.000000	-0.900404
24	144.000000	-0.726542
25	150.000000	-0.577350
26	156.000000	-0.445229
27	162.000000	-0.324920
28	168.000000	-0.212556
29	174.000000	-0.105104

30	180.000000	 0.000000
31	186.000000	 0.105104
32	192.000000	 0.212557
33	198.000000	 0.324920
34	204.000000	 0.445229
35	210.000000	 0.577350
36	216.000000	 0.726542
37	222.000000	 0.900404
38	228.000000	 1.110612
39	234.000000	 1.376381
40	240.000000	 1.732051
41	246.000000	 2.246037
42	252.000000	 3.077682
43	258.000000	 4.704625
44	264.000000	 9.514377
*/
int GetDegreeIndex60RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 = 15;// 90<<
		else	       nDegreeIndex60 = 45;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -9.514374 ) nDegreeIndex60 = 45;//-90==270
		else if( fGyDivdeGx < -4.704635 ) nDegreeIndex60 = 46;
		else if( fGyDivdeGx < -3.077682 ) nDegreeIndex60 = 47;
		else if( fGyDivdeGx < -2.246037 ) nDegreeIndex60 = 48;
		else if( fGyDivdeGx < -1.732051 ) nDegreeIndex60 = 49;
		else if( fGyDivdeGx < -1.376382 ) nDegreeIndex60 = 50;
		else if( fGyDivdeGx < -1.110612 ) nDegreeIndex60 = 51;
		else if( fGyDivdeGx < -0.900404 ) nDegreeIndex60 = 52;
		else if( fGyDivdeGx < -0.726543 ) nDegreeIndex60 = 53;
		else if( fGyDivdeGx < -0.577351 ) nDegreeIndex60 = 54;
		else if( fGyDivdeGx < -0.445228 ) nDegreeIndex60 = 55;
		else if( fGyDivdeGx < -0.324920 ) nDegreeIndex60 = 56;
		else if( fGyDivdeGx < -0.212557 ) nDegreeIndex60 = 57;
		else if( fGyDivdeGx < -0.105104 ) nDegreeIndex60 = 58;
		else if( fGyDivdeGx <  0.0      ) nDegreeIndex60 = 59;

		else if( fGyDivdeGx <  0.105104 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <  0.212557 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <  0.324920 ) nDegreeIndex60 =  2;
		else if( fGyDivdeGx <  0.445229 ) nDegreeIndex60 =  3;
		else if( fGyDivdeGx <  0.577350 ) nDegreeIndex60 =  4;
		else if( fGyDivdeGx <  0.726543 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx <  0.900404 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx <  1.110613 ) nDegreeIndex60 =  7;
		else if( fGyDivdeGx <  1.376382 ) nDegreeIndex60 =  8;
		else if( fGyDivdeGx <  1.732051 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <  2.246037 ) nDegreeIndex60 = 10;
		else if( fGyDivdeGx <  3.077684 ) nDegreeIndex60 = 11;
		else if( fGyDivdeGx <  4.704631 ) nDegreeIndex60 = 12;
		else if( fGyDivdeGx <  9.514368 ) nDegreeIndex60 = 13;
		else                              nDegreeIndex60 = 14;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -9.514360 ) nDegreeIndex60 = 15;//90
		else if( fGyDivdeGx < -4.704632 ) nDegreeIndex60 = 16;
		else if( fGyDivdeGx < -3.077684 ) nDegreeIndex60 = 17;
		else if( fGyDivdeGx < -2.246037 ) nDegreeIndex60 = 18;
		else if( fGyDivdeGx < -1.732051 ) nDegreeIndex60 = 19;
		else if( fGyDivdeGx < -1.376382 ) nDegreeIndex60 = 20;
		else if( fGyDivdeGx < -1.110612 ) nDegreeIndex60 = 21;
		else if( fGyDivdeGx < -0.900404 ) nDegreeIndex60 = 22;
		else if( fGyDivdeGx < -0.726542 ) nDegreeIndex60 = 23;
		else if( fGyDivdeGx < -0.577350 ) nDegreeIndex60 = 24;
		else if( fGyDivdeGx < -0.445229 ) nDegreeIndex60 = 25;
		else if( fGyDivdeGx < -0.324920 ) nDegreeIndex60 = 26;
		else if( fGyDivdeGx < -0.212556 ) nDegreeIndex60 = 27;
		else if( fGyDivdeGx < -0.105104 ) nDegreeIndex60 = 28;
		else if( fGyDivdeGx <  0.0      ) nDegreeIndex60 = 29;
												   
		else if( fGyDivdeGx <  0.105104 ) nDegreeIndex60 = 30;//180
		else if( fGyDivdeGx <  0.212557 ) nDegreeIndex60 = 31;
		else if( fGyDivdeGx <  0.324920 ) nDegreeIndex60 = 32;
		else if( fGyDivdeGx <  0.445229 ) nDegreeIndex60 = 33;
		else if( fGyDivdeGx <  0.577350 ) nDegreeIndex60 = 34;
		else if( fGyDivdeGx <  0.726542 ) nDegreeIndex60 = 35;
		else if( fGyDivdeGx <  0.900404 ) nDegreeIndex60 = 36;
		else if( fGyDivdeGx <  1.110612 ) nDegreeIndex60 = 37;
		else if( fGyDivdeGx <  1.376381 ) nDegreeIndex60 = 38;
		else if( fGyDivdeGx <  1.732051 ) nDegreeIndex60 = 39;
		else if( fGyDivdeGx <  2.246037 ) nDegreeIndex60 = 40;
		else if( fGyDivdeGx <  3.077682 ) nDegreeIndex60 = 41;
		else if( fGyDivdeGx <  4.704625 ) nDegreeIndex60 = 42;
		else if( fGyDivdeGx <  9.514377 ) nDegreeIndex60 = 43;
		else                              nDegreeIndex60 = 44;
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex60;
	return 0;
}

int GetDegreeIndex60RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 = 15;// 90??
		else	       nDegreeIndex60 = 45;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -9.514374 ) nDegreeIndex60 = 45;//-90==270
		else if( fGyDivdeGx < -4.704635 ) nDegreeIndex60 = 46;
		else if( fGyDivdeGx < -3.077682 ) nDegreeIndex60 = 47;
		else if( fGyDivdeGx < -2.246037 ) nDegreeIndex60 = 48;
		else if( fGyDivdeGx < -1.732051 ) nDegreeIndex60 = 49;
		else if( fGyDivdeGx < -1.376382 ) nDegreeIndex60 = 50;
		else if( fGyDivdeGx < -1.110612 ) nDegreeIndex60 = 51;
		else if( fGyDivdeGx < -0.900404 ) nDegreeIndex60 = 52;
		else if( fGyDivdeGx < -0.726543 ) nDegreeIndex60 = 53;
		else if( fGyDivdeGx < -0.577351 ) nDegreeIndex60 = 54;
		else if( fGyDivdeGx < -0.445228 ) nDegreeIndex60 = 55;
		else if( fGyDivdeGx < -0.324920 ) nDegreeIndex60 = 56;
		else if( fGyDivdeGx < -0.212557 ) nDegreeIndex60 = 57;
		else if( fGyDivdeGx < -0.105104 ) nDegreeIndex60 = 58;
		else if( fGyDivdeGx <  0.0      ) nDegreeIndex60 = 59;

		else if( fGyDivdeGx <  0.105104 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <  0.212557 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <  0.324920 ) nDegreeIndex60 =  2;
		else if( fGyDivdeGx <  0.445229 ) nDegreeIndex60 =  3;
		else if( fGyDivdeGx <  0.577350 ) nDegreeIndex60 =  4;
		else if( fGyDivdeGx <  0.726543 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx <  0.900404 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx <  1.110613 ) nDegreeIndex60 =  7;
		else if( fGyDivdeGx <  1.376382 ) nDegreeIndex60 =  8;
		else if( fGyDivdeGx <  1.732051 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <  2.246037 ) nDegreeIndex60 = 10;
		else if( fGyDivdeGx <  3.077684 ) nDegreeIndex60 = 11;
		else if( fGyDivdeGx <  4.704631 ) nDegreeIndex60 = 12;
		else if( fGyDivdeGx <  9.514368 ) nDegreeIndex60 = 13;
		else                              nDegreeIndex60 = 14;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -9.514360 ) nDegreeIndex60 = 15;//90
		else if( fGyDivdeGx < -4.704632 ) nDegreeIndex60 = 16;
		else if( fGyDivdeGx < -3.077684 ) nDegreeIndex60 = 17;
		else if( fGyDivdeGx < -2.246037 ) nDegreeIndex60 = 18;
		else if( fGyDivdeGx < -1.732051 ) nDegreeIndex60 = 19;
		else if( fGyDivdeGx < -1.376382 ) nDegreeIndex60 = 20;
		else if( fGyDivdeGx < -1.110612 ) nDegreeIndex60 = 21;
		else if( fGyDivdeGx < -0.900404 ) nDegreeIndex60 = 22;
		else if( fGyDivdeGx < -0.726542 ) nDegreeIndex60 = 23;
		else if( fGyDivdeGx < -0.577350 ) nDegreeIndex60 = 24;
		else if( fGyDivdeGx < -0.445229 ) nDegreeIndex60 = 25;
		else if( fGyDivdeGx < -0.324920 ) nDegreeIndex60 = 26;
		else if( fGyDivdeGx < -0.212556 ) nDegreeIndex60 = 27;
		else if( fGyDivdeGx < -0.105104 ) nDegreeIndex60 = 28;
		else if( fGyDivdeGx <  0.0      ) nDegreeIndex60 = 29;
												   
		else if( fGyDivdeGx <  0.105104 ) nDegreeIndex60 = 30;//180
		else if( fGyDivdeGx <  0.212557 ) nDegreeIndex60 = 31;
		else if( fGyDivdeGx <  0.324920 ) nDegreeIndex60 = 32;
		else if( fGyDivdeGx <  0.445229 ) nDegreeIndex60 = 33;
		else if( fGyDivdeGx <  0.577350 ) nDegreeIndex60 = 34;
		else if( fGyDivdeGx <  0.726542 ) nDegreeIndex60 = 35;
		else if( fGyDivdeGx <  0.900404 ) nDegreeIndex60 = 36;
		else if( fGyDivdeGx <  1.110612 ) nDegreeIndex60 = 37;
		else if( fGyDivdeGx <  1.376381 ) nDegreeIndex60 = 38;
		else if( fGyDivdeGx <  1.732051 ) nDegreeIndex60 = 39;
		else if( fGyDivdeGx <  2.246037 ) nDegreeIndex60 = 40;
		else if( fGyDivdeGx <  3.077682 ) nDegreeIndex60 = 41;
		else if( fGyDivdeGx <  4.704625 ) nDegreeIndex60 = 42;
		else if( fGyDivdeGx <  9.514377 ) nDegreeIndex60 = 43;
		else                              nDegreeIndex60 = 44;
	}

	*pPhaseIndex  = nDegreeIndex60;
	return 0;
}



// Phase index is like under chart
//   \ 2 /
//   3 X 1
//   / 4 \
//
/*
12      281.250000      -5.027337
13      303.750000      -1.496606
14      326.250000      -0.668179
15      348.750000      -0.198912

00       11.250000       0.198912
01       33.750000       0.668179
02       56.250000       1.496606
03       78.750000       5.027339

04      101.250000      -5.027339
05      123.750000      -1.496606
06      146.250000      -0.668178
07      168.750000      -0.198912

08      191.250000       0.198912
09      213.750000       0.668179
10      236.250000       1.496605
11      258.750000       5.027338
*/
int GetDegreeIndex16Hypotenuse ( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 =  4;// 90
		else	       nDegreeIndex60 = 12;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -5.027337 ) nDegreeIndex60 = 12;//-90==270
		else if( fGyDivdeGx < -1.496606 ) nDegreeIndex60 = 13;
		else if( fGyDivdeGx < -0.668179 ) nDegreeIndex60 = 14;
		else if( fGyDivdeGx < -0.198912 ) nDegreeIndex60 = 15;

		else if( fGyDivdeGx <  0.198912 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <  0.668179 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <  1.496606 ) nDegreeIndex60 =  2;
		else if( fGyDivdeGx <  5.027339 ) nDegreeIndex60 =  3;
		else                              nDegreeIndex60 =  4;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -5.027339 ) nDegreeIndex60 =  4;//90
		else if( fGyDivdeGx < -1.496606 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx < -0.668178 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx < -0.198912 ) nDegreeIndex60 =  7;
												   
		else if( fGyDivdeGx <  0.198912 ) nDegreeIndex60 =  8;//180
		else if( fGyDivdeGx <  0.668179 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <  1.496605 ) nDegreeIndex60 = 10;
		else if( fGyDivdeGx <  5.027338 ) nDegreeIndex60 = 11;
		else                              nDegreeIndex60 = 12;//270==-90
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex60;

	return 0;
}

int GetDegreeIndex16Hypotenuse ( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex60 = 0;
	float fGyDivdeGx     = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex60 =  4;// 90??
		else	       nDegreeIndex60 = 12;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -5.027337 ) nDegreeIndex60 = 12;//-90==270
		else if( fGyDivdeGx < -1.496606 ) nDegreeIndex60 = 13;
		else if( fGyDivdeGx < -0.668179 ) nDegreeIndex60 = 14;
		else if( fGyDivdeGx < -0.198912 ) nDegreeIndex60 = 15;

		else if( fGyDivdeGx <  0.198912 ) nDegreeIndex60 =  0;//0
		else if( fGyDivdeGx <  0.668179 ) nDegreeIndex60 =  1;
		else if( fGyDivdeGx <  1.496606 ) nDegreeIndex60 =  2;
		else                              nDegreeIndex60 =  3;//90
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -5.027339 ) nDegreeIndex60 =  4;//90
		else if( fGyDivdeGx < -1.496606 ) nDegreeIndex60 =  5;
		else if( fGyDivdeGx < -0.668178 ) nDegreeIndex60 =  6;
		else if( fGyDivdeGx < -0.198912 ) nDegreeIndex60 =  7;
												   
		else if( fGyDivdeGx <  0.198912 ) nDegreeIndex60 =  8;//180
		else if( fGyDivdeGx <  0.668179 ) nDegreeIndex60 =  9;
		else if( fGyDivdeGx <  1.496605 ) nDegreeIndex60 = 10;
		else                              nDegreeIndex60 = 11;//270==-90
	}

	*pPhaseIndex  = nDegreeIndex60;

	return 0;
}




/*
// Phase index is like under chart
//  2 | 1
//  __|__
//    |
//  3 | 4

index degree    tan
12      270.000000      -83858280.000000
13      292.500000      -2.414212
14      315.000000      -1.000000
15      337.500000      -0.414214
16      360.000000       0.000000

00        0.000000       0.000000
01       22.500000       0.414214
02       45.000000       1.000000
03       67.500000       2.414214

04       90.000000      -22877332.000000
05      112.500000      -2.414214
06      135.000000      -1.000000
07      157.500000      -0.414214

08      180.000000       0.000000
09      202.500000       0.414214
10      225.000000       1.000000
11      247.500000       2.414212

*/

int GetDegreeIndex16RightAngle( const int& nGx, const int& nGy, int* pMaginitude, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex =  4;// 90
		else	       nDegreeIndex = 12;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 12;//
		else if( fGyDivdeGx < -1.000000 ) nDegreeIndex = 13;
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 14;//
		else if( fGyDivdeGx <  0.000000 ) nDegreeIndex = 15;

		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex =  0;
		else if( fGyDivdeGx <  1.000000 ) nDegreeIndex =  1;
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex =  2;
		else                              nDegreeIndex =  3;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414214 ) nDegreeIndex =  4;
		else if( fGyDivdeGx < -1.000000 ) nDegreeIndex =  5;
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex =  6;
		else if( fGyDivdeGx <  0.000000 ) nDegreeIndex =  7;
												   
		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex =  8;
		else if( fGyDivdeGx <  1.000000 ) nDegreeIndex =  9;
		else if( fGyDivdeGx <  2.414212 ) nDegreeIndex = 10;
		else                              nDegreeIndex = 11;
	}

	int nMaginitude = ( abs(nGx) + abs(nGy) ) / 3;
	if (nMaginitude > 255)
		nMaginitude = 255;

	*pMaginitude  = nMaginitude;
	*pPhaseIndex  = nDegreeIndex;

	return 0;
}


int GetDegreeIndex16RightAngle( const int& nGx, const int& nGy, int* pPhaseIndex )
{
	int   nDegreeIndex = 0;
	float fGyDivdeGx   = 0;

	if( nGx == 0 )
	{
		if  ( nGy<=0 ) nDegreeIndex =  4;// 90
		else	       nDegreeIndex = 12;//-90
	}
	else if ( nGx < 0 )  // [-90, 90]
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414212 ) nDegreeIndex = 12;//
		else if( fGyDivdeGx < -1.000000 ) nDegreeIndex = 13;
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex = 14;//
		else if( fGyDivdeGx <  0.000000 ) nDegreeIndex = 15;

		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex =  0;
		else if( fGyDivdeGx <  1.000000 ) nDegreeIndex =  1;
		else if( fGyDivdeGx <  2.414214 ) nDegreeIndex =  2;
		else                              nDegreeIndex =  3;
	}
	else// if( nGx > 0 )//(90,270)
	{
		fGyDivdeGx = (float)nGy / (float)nGx;

		if     ( fGyDivdeGx < -2.414214 ) nDegreeIndex =  4;
		else if( fGyDivdeGx < -1.000000 ) nDegreeIndex =  5;
		else if( fGyDivdeGx < -0.414214 ) nDegreeIndex =  6;
		else if( fGyDivdeGx <  0.000000 ) nDegreeIndex =  7;
												   
		else if( fGyDivdeGx <  0.414214 ) nDegreeIndex =  8;
		else if( fGyDivdeGx <  1.000000 ) nDegreeIndex =  9;
		else if( fGyDivdeGx <  2.414212 ) nDegreeIndex = 10;
		else                              nDegreeIndex = 11;
	}


	*pPhaseIndex  = nDegreeIndex;

	return 0;
}