#ifndef _LOCAL_BINARY_PATTERN_H_INCLUDE_
#define _LOCAL_BINARY_PATTERN_H_INCLUDE_


/////////////////////////////////
//CORNER
//  111    111    100    001
//  100    001    100    001
//  100    001    111    111
//-----  -----  -----  -----
//0x1E4  0x1C9  0x127  0x04F
/////////////////////////////////

/////////////////////////////////
//  110    011    100    001
//  100    001    100    001
//  100    001    110    011
//-----  -----  -----  -----
//0x1A4  0X0C9  0x126  0x04B 
/////////////////////////////////

/////////////////////////////////
//  111    111    000    000
//  100    001    100    001
//  000    000    111    111
//-----  -----  -----  -----
//0x1E0  0x1C8  0x027  0x00F
/////////////////////////////////

/////////////////////////////////
//  110    011    000    000
//  100    001    100    001
//  000    000    110    011
//-----  -----  -----  -----
//0x1A0  0x0C8  0x026  0x00B
/////////////////////////////////


/////////////////////////////////
//INTERACE
//  111
//  000
//  111
//-----
//0x1C7
/////////////////////////////////
/*
enum _eLBP_CODE_SEQ{
	eCONNER_LEFT_UP     = 0,
	eCONNER_RIGHT_UP    ,
	eCONNER_LEFT_DN     ,
	eCONNER_RIGHT_DN    ,

	eCONNER_LEFTSH_UP   , //sub horizontal
	eCONNER_RIGHTSH_UP  ,
	eCONNER_LEFTSH_DN   ,
	eCONNER_RIGHTSH_DN  ,

	eCONNER_LEFTSV_UP   , //sub vertical
	eCONNER_RIGHTSV_UP  ,
	eCONNER_LEFTSV_DN   ,
	eCONNER_RIGHTSV_DN  ,

	eCONNER_LEFTS_UP    , //sub
	eCONNER_RIGHTS_UP   ,
	eCONNER_LEFTS_DN    ,
	eCONNER_RIGHTS_DN   ,

	eLINE_INTERLACE     ,

	eLBP_CODE_BACKGROUND,
	eLBP_CODE_COUNT
};
*/

#define TYPE_CONNER_LEFT_UP     0x01E4
#define TYPE_CONNER_RIGHT_UP	0x01C9
#define TYPE_CONNER_LEFT_DN		0x0127
#define TYPE_CONNER_RIGHT_DN	0x004F

#define TYPE_CONNER_LEFTSH_UP	0x01A4//sub horizontal
#define TYPE_CONNER_RIGHTSH_UP	0x00C9
#define TYPE_CONNER_LEFTSH_DN	0x0126
#define TYPE_CONNER_RIGHTSH_DN	0x004B

#define TYPE_CONNER_LEFTSV_UP	0x01E0//sub vertical
#define TYPE_CONNER_RIGHTSV_UP	0x01C8
#define TYPE_CONNER_LEFTSV_DN	0x0027
#define TYPE_CONNER_RIGHTSV_DN	0x000F

#define TYPE_CONNER_LEFTS_UP	0x01A0//sub
#define TYPE_CONNER_RIGHTS_UP	0x00C8
#define TYPE_CONNER_LEFTS_DN	0x0026
#define TYPE_CONNER_RIGHTS_DN	0x000B

/////////////////////////////////
//WALL : 자기자신은 0
//  111    000    100    001
//  000    000    100    001
//  000    111    100    001
//-----  -----  -----  -----
//0x1C0  0x007  0x124  0x049
/////////////////////////////////
#define TYPE_WALL_UP	        0x01C0
#define TYPE_WALL_DOWN	        0x0007
#define TYPE_WALL_LEFT	        0x0124
#define TYPE_WALL_RIGHT	        0x0049


/////////////////////////////////
//CORNER Inverse : 자기자신은 0
//  000    000    011    110
//  001    100    001    100
//  011    110    000    000
//-----  -----  -----  -----
//0x00B  0x026  0x0C8  0x1A0
/////////////////////////////////
#define TYPE_CONNER_LEFT_UP_I   0x000B//Inverse
#define TYPE_CONNER_RIGHT_UP_I  0x0026
#define TYPE_CONNER_LEFT_DN_I   0x00C8
#define TYPE_CONNER_RIGHT_DN_I  0x01A0

/////////////////////////////////
//WALL : 자기자신은 0
//  000    000    100    001
//  101    000    100    001
//  111    111    100    001
//-----  -----  -----  -----
//0x1C0  0x007  0x124  0x049
/////////////////////////////////
#define TYPE_WALL_UP_I	        0x002F
#define TYPE_WALL_DOWN_I        0x01F8
#define TYPE_WALL_LEFT_I        0x00DB
#define TYPE_WALL_RIGHT_I       0x01B6

#define TYPE_LINE_INTERLACE     0x01C7
#define TYPE_LINE_INTERLACE_I   0x0028



/////////////////////////////////////////////////////
// CORNER VALUE //
//
//  12223
//  8   4
//  8   4
//  8   4
//  76665
//
/////////////////////////////////////////////////////
#define VALUE_CONNER_LEFT_UP       1 
#define VALUE_CONNER_RIGHT_UP	   3 
#define VALUE_CONNER_LEFT_DN	   7 	
#define VALUE_CONNER_RIGHT_DN	   5 

#define VALUE_WALL_UP	           2
#define VALUE_WALL_DOWN	           6 
#define VALUE_WALL_LEFT	           8 
#define VALUE_WALL_RIGHT	       4 

#define VALUE_CONNER_LEFTSH_UP	   1 
#define VALUE_CONNER_RIGHTSH_UP	   3 
#define VALUE_CONNER_LEFTSH_DN	   5 
#define VALUE_CONNER_RIGHTSH_DN	   7 

#define VALUE_CONNER_LEFTSV_UP	   1 
#define VALUE_CONNER_RIGHTSV_UP	   3 
#define VALUE_CONNER_LEFTSV_DN	   5 
#define VALUE_CONNER_RIGHTSV_DN	   7 

#define VALUE_CONNER_LEFTS_UP	   1 
#define VALUE_CONNER_RIGHTS_UP	   3 
#define VALUE_CONNER_LEFTS_DN	   5 
#define VALUE_CONNER_RIGHTS_DN	   7 

#define VALUE_LINE_INTERLACE	0x40// 	


#define VALUE_BACKGROUND         0xFF

/*
#define GET_LBP_CODE(WN, NN, NE, WW, CC, EE, SW, SS, ES, nBarrier) (\
	(((WN-CC>0)?1:0)<<8) |\
	(((NN-CC>0)?1:0)<<7) |\
	(((NE-CC>0)?1:0)<<6) |\
	(((WW-CC>0)?1:0)<<5) |\
	(((EE-CC>0)?1:0)<<3) |\
	(((SW-CC>0)?1:0)<<2) |\
	(((SS-CC>0)?1:0)<<1) |\
	(((ES-CC>0)?1:0)   )  )
*/
#define GET_LBP_CODE(WN, NN, NE, WW, CC, EE, SW, SS, ES, nBarrier) (\
	(((WN-CC>nBarrier)?1:0)<<8) |\
	(((NN-CC>nBarrier)?1:0)<<7) |\
	(((NE-CC>nBarrier)?1:0)<<6) |\
	(((WW-CC>nBarrier)?1:0)<<5) |\
	(((EE-CC>nBarrier)?1:0)<<3) |\
	(((SW-CC>nBarrier)?1:0)<<2) |\
	(((SS-CC>nBarrier)?1:0)<<1) |\
	(((ES-CC>nBarrier)?1:0)   )  )



//WN, NN, NE;
//WW, CC, EE;
#define CMP_BACK(A,B)((A==B)?1:VALUE_BACKGROUND)
#define CMP_CODE(A,B)((A==B)?1:0)
#define SUB_CODE(A,B)((A-B>0)?1:0)
#define GET_LBP_LINE(WN, NN, NE, WW, CC, EE) ( \
	CMP_BACK(\
		CMP_CODE(\
			SUB_CODE(WN,WW),\
			SUB_CODE(NN,CC)\
		),\
		SUB_CODE(NE,EE)\
	)\
)

/*
typedef struct tagLBP_CODE
{
	WORD wCodeType;
	BYTE byteValue;
}LBP_CODE,* LPLBP_CODE;

extern LBP_CODE g_LBP_CODE[];
*/

#define GET_RELATION_LBP_HORIZONTAL(a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier) (\
	( (abs(a-b)>nBarrier)?1:0 )<<19 |\
	( (abs(b-c)>nBarrier)?1:0 )<<18 |\
	( (abs(c-d)>nBarrier)?1:0 )<<17 |\
	( (abs(d-e)>nBarrier)?1:0 )<<16 |\
\
	( (abs(f-g)>nBarrier)?1:0 )<<15 |\
	( (abs(g-h)>nBarrier)?1:0 )<<14 |\
	( (abs(j-i)>nBarrier)?1:0 )<<13 |\
	( (abs(i-j)>nBarrier)?1:0 )<<12 |\
\
	( (abs(k-l)>nBarrier)?1:0 )<<11 |\
	( (abs(l-m)>nBarrier)?1:0 )<<10 |\
	( (abs(m-n)>nBarrier)?1:0 )<< 9 |\
	( (abs(n-o)>nBarrier)?1:0 )<< 8 |\
\
	( (abs(p-q)>nBarrier)?1:0 )<< 7 |\
	( (abs(q-r)>nBarrier)?1:0 )<< 6 |\
	( (abs(r-s)>nBarrier)?1:0 )<< 5 |\
	( (abs(s-t)>nBarrier)?1:0 )<< 4 |\
\
	( (abs(u-v)>nBarrier)?1:0 )<< 3 |\
	( (abs(v-w)>nBarrier)?1:0 )<< 2 |\
	( (abs(w-x)>nBarrier)?1:0 )<< 1 |\
	( (abs(x-y)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_HORIZONTAL_C3X3(a,b,c,d,e,\
	                                     f,g,h,i,j,\
									     k,l,m,n,o,\
									     p,q,r,s,t,\
									     u,v,w,x,y,nBarrier) (\
	( (abs(g-h)>nBarrier)?1:0 )<< 5 |\
	( (abs(j-i)>nBarrier)?1:0 )<< 4 |\
\
	( (abs(l-m)>nBarrier)?1:0 )<< 3 |\
	( (abs(m-n)>nBarrier)?1:0 )<< 2 |\
\
	( (abs(q-r)>nBarrier)?1:0 )<< 1 |\
	( (abs(r-s)>nBarrier)?1:0 )<< 0 )


#define GET_RELATION_LBP_VERTICAL(  a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier)(\
	( (abs(a-f)>nBarrier)?1:0 )<<19 |\
	( (abs(f-k)>nBarrier)?1:0 )<<18 |\
	( (abs(k-p)>nBarrier)?1:0 )<<17 |\
	( (abs(p-u)>nBarrier)?1:0 )<<16 |\
\
	( (abs(b-g)>nBarrier)?1:0 )<<15 |\
	( (abs(g-l)>nBarrier)?1:0 )<<14 |\
	( (abs(l-q)>nBarrier)?1:0 )<<13 |\
	( (abs(q-v)>nBarrier)?1:0 )<<12 |\
\
	( (abs(c-h)>nBarrier)?1:0 )<<11 |\
	( (abs(h-m)>nBarrier)?1:0 )<<10 |\
	( (abs(m-r)>nBarrier)?1:0 )<< 9 |\
	( (abs(r-w)>nBarrier)?1:0 )<< 8 |\
\
	( (abs(d-i)>nBarrier)?1:0 )<< 7 |\
	( (abs(i-n)>nBarrier)?1:0 )<< 6 |\
	( (abs(n-s)>nBarrier)?1:0 )<< 5 |\
	( (abs(s-x)>nBarrier)?1:0 )<< 4 |\
\
	( (abs(e-j)>nBarrier)?1:0 )<< 3 |\
	( (abs(j-o)>nBarrier)?1:0 )<< 2 |\
	( (abs(o-t)>nBarrier)?1:0 )<< 1 |\
	( (abs(t-y)>nBarrier)?1:0 )<< 0 )


#define GET_RELATION_LBP_CROSS_LEFT(a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier)(\
	( (abs(b-f)>nBarrier)?1:0 )<<15 |\
\
	( (abs(c-g)>nBarrier)?1:0 )<<14 |\
	( (abs(g-k)>nBarrier)?1:0 )<<13 |\
\
	( (abs(d-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-l)>nBarrier)?1:0 )<<11 |\
	( (abs(l-p)>nBarrier)?1:0 )<<10 |\
\
	( (abs(e-i)>nBarrier)?1:0 )<< 9 |\
	( (abs(i-m)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-q)>nBarrier)?1:0 )<< 7 |\
	( (abs(q-u)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(j-n)>nBarrier)?1:0 )<< 5 |\
	( (abs(n-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-v)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(o-s)>nBarrier)?1:0 )<< 2 |\
	( (abs(s-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(t-x)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_LEFT4BIT(a,b,c,d,e,\
	                                    f,g,h,i,j,\
									    k,l,m,n,o,\
									    p,q,r,s,t,\
									    u,v,w,x,y,nBarrier)(\
	( (abs(e-i)>nBarrier)?1:0 )<< 3 |\
	( (abs(i-m)>nBarrier)?1:0 )<< 2 |\
	( (abs(m-q)>nBarrier)?1:0 )<< 1 |\
	( (abs(q-u)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_LEFT8BIT(a,b,c,d,e,\
	                                    f,g,h,i,j,\
									    k,l,m,n,o,\
									    p,q,r,s,t,\
									    u,v,w,x,y,nBarrier)(\
	( (abs(c-g)>nBarrier)?1:0 )<< 7 |\
	( (abs(g-k)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(e-i)>nBarrier)?1:0 )<< 5 |\
	( (abs(i-m)>nBarrier)?1:0 )<< 4 |\
	( (abs(m-q)>nBarrier)?1:0 )<< 3 |\
	( (abs(q-u)>nBarrier)?1:0 )<< 2 |\
\
	( (abs(o-s)>nBarrier)?1:0 )<< 1 |\
	( (abs(s-w)>nBarrier)?1:0 )<< 0 )



#define GET_RELATION_LBP_CROSS_RIGHT(a,b,c,d,e,\
	                                 f,g,h,i,j,\
									 k,l,m,n,o,\
									 p,q,r,s,t,\
									 u,v,w,x,y,nBarrier)(\
	( (abs(d-j)>nBarrier)?1:0 )<<15 |\
\
	( (abs(c-i)>nBarrier)?1:0 )<<14 |\
	( (abs(i-o)>nBarrier)?1:0 )<<13 |\
\
	( (abs(b-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-n)>nBarrier)?1:0 )<<11 |\
	( (abs(n-t)>nBarrier)?1:0 )<<10 |\
\
	( (abs(a-g)>nBarrier)?1:0 )<< 9 |\
	( (abs(g-m)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 7 |\
	( (abs(s-y)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(f-l)>nBarrier)?1:0 )<< 5 |\
	( (abs(l-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-x)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(k-q)>nBarrier)?1:0 )<< 2 |\
	( (abs(q-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(p-v)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_RIGHT4BIT(a,b,c,d,e,\
	                                     f,g,h,i,j,\
									     k,l,m,n,o,\
									     p,q,r,s,t,\
									     u,v,w,x,y,nBarrier)(\
	( (abs(a-g)>nBarrier)?1:0 )<< 3 |\
	( (abs(g-m)>nBarrier)?1:0 )<< 2 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 1 |\
	( (abs(s-y)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_RIGHT8BIT(a,b,c,d,e,\
	                                     f,g,h,i,j,\
									     k,l,m,n,o,\
									     p,q,r,s,t,\
									     u,v,w,x,y,nBarrier)(\
	( (abs(c-i)>nBarrier)?1:0 )<< 7 |\
	( (abs(i-o)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(a-g)>nBarrier)?1:0 )<< 5 |\
	( (abs(g-m)>nBarrier)?1:0 )<< 4 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 3 |\
	( (abs(s-y)>nBarrier)?1:0 )<< 2 |\
\
	( (abs(k-q)>nBarrier)?1:0 )<< 1 |\
	( (abs(q-w)>nBarrier)?1:0 )<< 0 )


//탑형태의 화소 변화를 예외처리
#define GET_RELATION_LBP_TOWER8BIT(a,b,c,d,e,\
	                               f,g,h,i,j,\
								   k,l,m,n,o,\
								   p,q,r,s,t,\
								   u,v,w,x,y,nBarrier)(\
	( ((m-g)>nBarrier)?1:0 )<< 7 |\
	( ((g-a)>nBarrier)?1:0 )<< 6 |\
\
	( ((m-i)>nBarrier)?1:0 )<< 5 |\
	( ((i-e)>nBarrier)?1:0 )<< 4 |\
\
	( ((m-q)>nBarrier)?1:0 )<< 3 |\
	( ((q-u)>nBarrier)?1:0 )<< 2 |\
\
	( ((m-s)>nBarrier)?1:0 )<< 1 |\
	( ((s-y)>nBarrier)?1:0 )<< 0  )



/////////////////////////////////////
//  MMMMM
//  MLMHM
//  MMMMM
//  MHMLM
//  MMMMM
//  M:Middle pixel vlaue
//  H:High     "
//  L:Low      "
// 상기 예제의 경우 아래 코드로 검출.
// abs함수를 쓰는것에 비하여 속도 개선.

//  MMMMM
//  MLMLM
//  MMMMM
//  MHMHM
//  MMMMM
// 상기 형태도 있음.
/*
#define GET_RELATION_LBP_CROSS_LEFT(a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier)(\
	( ((b-f)>nBarrier)?1:0 )<<15 |\
\
	( ((c-g)>nBarrier)?1:0 )<<14 |\
	( ((k-g)>nBarrier)?1:0 )<<13 |\
\
	( ((d-h)>nBarrier)?1:0 )<<12 |\
	( ((h-l)>nBarrier)?1:0 )<<11 |\
	( ((l-p)>nBarrier)?1:0 )<<10 |\
\
	( ((i-e)>nBarrier)?1:0 )<< 9 |\
	( ((i-m)>nBarrier)?1:0 )<< 8 |\
	( ((q-m)>nBarrier)?1:0 )<< 7 |\
	( ((q-u)>nBarrier)?1:0 )<< 6 |\
\
	( ((j-n)>nBarrier)?1:0 )<< 5 |\
	( ((n-r)>nBarrier)?1:0 )<< 4 |\
	( ((r-v)>nBarrier)?1:0 )<< 3 |\
\
	( ((o-s)>nBarrier)?1:0 )<< 2 |\
	( ((w-s)>nBarrier)?1:0 )<< 1 |\
\
	( ((t-x)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_RIGHT(a,b,c,d,e,\
	                                 f,g,h,i,j,\
									 k,l,m,n,o,\
									 p,q,r,s,t,\
									 u,v,w,x,y,nBarrier)(\
	( (abs(d-j)>nBarrier)?1:0 )<<15 |\
\
	( (abs(i-c)>nBarrier)?1:0 )<<14 |\
	( (abs(i-o)>nBarrier)?1:0 )<<13 |\
\
	( (abs(b-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-n)>nBarrier)?1:0 )<<11 |\
	( (abs(n-t)>nBarrier)?1:0 )<<10 |\
\
	( (abs(a-g)>nBarrier)?1:0 )<< 9 |\
	( (abs(m-g)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 7 |\
	( (abs(y-s)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(f-l)>nBarrier)?1:0 )<< 5 |\
	( (abs(l-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-x)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(q-k)>nBarrier)?1:0 )<< 2 |\
	( (abs(q-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(p-v)>nBarrier)?1:0 )<< 0 )
*/

#endif//_LOCAL_BINARY_PATTERN_H_INCLUDE_