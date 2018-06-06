//iplBlockElement.h
//Block for x times Macro block size.
//2010.02.22
//by kiok ahn
//kiokahn@mediachorus.com

#ifndef _BLOCK_ELEMENT_H_INCLUDE_
#define _BLOCK_ELEMENT_H_INCLUDE_

#include <list>
#include <math.h>
using namespace std;

#define _MACRO_BLOCK_SIZE    8
#define _MAX_GRAY         0xFF
#define _LESS_ALLOWABLE      2//모자람에 대한 허용 오차, 3 pixel


#define _IS_MAX_L(pX) (*pX!=_MAX_GRAY && *(pX-1)!=_MAX_GRAY && *(pX+1)!=_MAX_GRAY)
#define _IS_MAX_R(pX) (*pX!=_MAX_GRAY && *(pX+1)!=_MAX_GRAY)

#define _ABS_POS_SUB_L(pX) abs( (int)(*(pX+1)) - (int)(*(pX-1)) )
#define _ABS_POS_SUB_R(pX) abs( (int)(*(pX-1)) - (int)(*(pX+1)) )

#define _ABS_POS_SUB_U(pX,nWidth) abs( (int)(*(pX+nWidth)) - (int)(*(pX-nWidth)) )
#define _ABS_POS_SUB_D(pX,nWidth) abs( (int)(*(pX-nWidth)) - (int)(*(pX+nWidth)) )

#define _CHECK_BOUNDARY(nMin,nMax,nValue) if(nMax<nValue || nValue<nMin )break;

enum ePOSITION_TYPE{
	T_UNKNOW = 0,
	LEFT_TOP = 1,
	LINE_TOP    ,
	RIGHT_TOP   ,
	LINE_RIGHT  ,
	RIGHT_BOTTOM,
	LINE_BOTTOM ,
	LEFT_BOTTOM ,
	LINE_LEFT
};

typedef struct tagPositionInfo
{
	INT              nX   ;
	INT              nY   ;
	ePOSITION_TYPE   eType;//1:left_top, 2:line_top, 3:right_top, 4:line_right, 5:right_bottom, 6:line_bottom, 7:left_bottom, 8:line_left
	BYTE*            pData;
}POSITIONINFO, *LPPOSITIONINFO;

class CPositionInfo : public tagPositionInfo
{
public:
	CPositionInfo(                           ) { nX=0;nY=0;eType=T_UNKNOW;pData=NULL; };
	CPositionInfo( const POSITIONINFO & info ) { (*this)=info;                 };
	CPositionInfo( const CPositionInfo& info ) { (*this)=(POSITIONINFO)(info); };
	CPositionInfo( INT _X, INT _Y, ePOSITION_TYPE _Type, BYTE* _Data ){ nX=_X;nY=_Y;eType=_Type;pData=_Data; };
	~CPositionInfo(){};

//operator
public:
	void operator=( const POSITIONINFO& info )
	{
		memcpy( (void*)this, (void*)&info, sizeof(POSITIONINFO) );
	};

	void operator=( const CPositionInfo& info )
	{
		(*this)=(POSITIONINFO)(info);
	};

	BOOL operator==(POSITIONINFO info) const throw()
	{
		return ( nX==info.nX && nY==info.nY )? TRUE : FALSE;
	};

	BOOL operator!=(POSITIONINFO info) const throw()
	{
		return !( *this==info );
	};


public:
	BYTE* GetUpper ( const INT& nWidth, const INT& nBytes = 1 ){ return ( pData + nWidth*nBytes); };
	BYTE* GetDown  ( const INT& nWidth, const INT& nBytes = 1 ){ return ( pData + nWidth*nBytes); };
	BYTE* GetBuffer( void                                     ){ return   pData; };

	INT   GetX     ( void ) {return nX;};
	INT   GetY     ( void ) {return nY;};

	void  SetType  ( const ePOSITION_TYPE& _Type ){ eType=_Type; };
};

typedef list<CPositionInfo> LIST_POSITIONINFO, *LPLIST_POSITIONINFO;
typedef LIST_POSITIONINFO::iterator LIST_POSITIONINFOItor;


class CBlockElement
{//MAX RIO영역을 _MACRO_BLOCK_SIZE 안쪽으로만 잡는다.

public:
	CBlockElement( const INT& nWidth );
	CBlockElement( const CBlockElement& block );
	~CBlockElement();

//operator
public:
	void operator=( const CBlockElement& block );

protected:
	BOOL  CheckConner( void );

public:
	size_t  GetSize     ( void ) ;
	size_t  GetSizeLeft ( void ) ;
	size_t  GetSizeRight( void ) ;
	size_t  GetSizeUp   ( void ) ;
	size_t  GetSizeDown ( void ) ;
	float   GetDistance ( const INT& x1, const INT& x2, const INT& y1, const INT& y2 );
	BOOL    IsBlock     ( void ) ;


	LPLIST_POSITIONINFO GetListLeft ( void );
	LPLIST_POSITIONINFO GetListRight( void );
	LPLIST_POSITIONINFO GetListUp   ( void );
	LPLIST_POSITIONINFO GetListDown ( void );


	void  AddLeftLine ( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData );
	void  AddRightLine( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData );

protected:
	LIST_POSITIONINFO m_listLeft ;
	LIST_POSITIONINFO m_listRight;
	LIST_POSITIONINFO m_listUp   ;
	LIST_POSITIONINFO m_listDown ;

	INT               m_nWidth   ;
};

typedef list<CBlockElement>  LIST_BLOCK, *LPLIST_BLOCK;
typedef LIST_BLOCK::iterator LIST_BLOCKItor;

//pCopyedSrc는 내부에서 값이 변경 된다.
//For Gray Image
//int ipl_BlockDetect( IN LPBYTE pCopyedSrc, int nWidth, int nHeight, OUT LPLIST_BLOCK lpListBlock, IN BYTE byteBarrier=30, IN INT nMaxBlockSize=32 );

#endif//_BLOCK_ELEMENT_H_INCLUDE_