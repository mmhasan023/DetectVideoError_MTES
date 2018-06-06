//#if defined(WIN32)
//	#include "stdafx.h"
//#endif
#include "iplDefine.h"
#include "iplTypes.h"
#include "iplMemory.h"
#include <math.h>

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#ifdef malloc
#undef malloc
#endif
#define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef calloc
#undef calloc
#endif
#define calloc(c, s) (_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef realloc
#undef realloc
#endif
#define realloc(p, s) (_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef _expand
#undef _expand
#endif
#define _expand(p, s) (_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__  ))
#ifdef free
#undef free
#endif
#define free(p) (_free_dbg(p, _NORMAL_BLOCK))
#ifdef _msize
#undef _msize
#endif
#define _msize(p) (_msize_dbg(p, _NORMAL_BLOCK))

#endif
*/

// CIplSize
CIplSize::CIplSize()
{ /* random filled */ }
CIplSize::CIplSize(int initCX, int initCY)
{ cx = initCX; cy = initCY; }
CIplSize::CIplSize(IPLSIZE initSize)
{ *(IPLSIZE*)this = initSize; }
CIplSize::CIplSize(IPLPOINT initPt)
{ *(IPLPOINT*)this = initPt; }
BOOL CIplSize::operator==(IPLSIZE size) const
{ return (cx == size.cx && cy == size.cy); }
BOOL CIplSize::operator!=(IPLSIZE size) const
{ return (cx != size.cx || cy != size.cy); }
void CIplSize::operator+=(IPLSIZE size)
{ cx += size.cx; cy += size.cy; }
void CIplSize::operator-=(IPLSIZE size)
{ cx -= size.cx; cy -= size.cy; }
CIplSize CIplSize::operator+(IPLSIZE size) const
{ return CIplSize(cx + size.cx, cy + size.cy); }
CIplSize CIplSize::operator-(IPLSIZE size) const
{ return CIplSize(cx - size.cx, cy - size.cy); }
CIplSize CIplSize::operator-() const
{ return CIplSize(-cx, -cy); }
CIplPoint CIplSize::operator+(IPLPOINT point) const
{ return CIplPoint(cx + point.x, cy + point.y); }
CIplPoint CIplSize::operator-(IPLPOINT point) const
{ return CIplPoint(cx - point.x, cy - point.y); }
/*
CIplRect CIplSize::operator+(const LPIPLRECT lpRect) const
{ return CIplRect(lpRect) + *this; }
CIplRect CIplSize::operator-(const LPIPLRECT lpRect) const
{ return CIplRect(lpRect) - *this; }
*/


// CIplPoint
CIplPoint::CIplPoint()
{ x = 0; y = 0;  }
CIplPoint::CIplPoint(int initX, int initY)
{ x = initX; y = initY; }
CIplPoint::CIplPoint(IPLPOINT initPt)
{ 
	*(IPLPOINT*)this = initPt; 
}
CIplPoint::CIplPoint(IPLSIZE initSize)
{ *(IPLSIZE*)this = initSize; }
void CIplPoint::Offset(int xOffset, int yOffset)
{ x += xOffset; y += yOffset; }
void CIplPoint::Offset(IPLPOINT point)
{ x += point.x; y += point.y; }
void CIplPoint::Offset(IPLSIZE size)
{ x += size.cx; y += size.cy; }
BOOL CIplPoint::operator==(IPLPOINT point) const
{ return (x == point.x && y == point.y); }
BOOL CIplPoint::operator!=(IPLPOINT point) const
{ return (x != point.x || y != point.y); }
void CIplPoint::operator+=(IPLSIZE size)
{ x += size.cx; y += size.cy; }
void CIplPoint::operator-=(IPLSIZE size)
{ x -= size.cx; y -= size.cy; }
void CIplPoint::operator+=(IPLPOINT point)
{ x += point.x; y += point.y; }
void CIplPoint::operator-=(IPLPOINT point)
{ x -= point.x; y -= point.y; }
CIplPoint CIplPoint::operator+(IPLSIZE size) const
{ return CIplPoint(x + size.cx, y + size.cy); }
CIplPoint CIplPoint::operator-(IPLSIZE size) const
{ return CIplPoint(x - size.cx, y - size.cy); }
CIplPoint CIplPoint::operator-() const
{ return CIplPoint(-x, -y); }
CIplPoint CIplPoint::operator+(IPLPOINT point) const
{ return CIplPoint(x + point.x, y + point.y); }
CIplSize CIplPoint::operator-(IPLPOINT point) const
{ return CIplSize(x - point.x, y - point.y); }
float CIplPoint::GetDistance(const IPLPOINT& p2)
{
	return sqrt( (float)((p2.x-x)*(p2.x-x) + (float)(p2.y-y)*(p2.y-y)) );
}
void CIplPoint::operator=(const IPLPOINTLABEL& point)
{ x=point.x; y=point.y; }
void CIplPoint::operator=(const CIplPointLabel& point)
{ x=point.x; y=point.y; }
float CIplPoint::GetDegree(const IPLPOINT& p2)
{
	
//	if( p2.x == x )
//		return 90.0f;

	return atan2( float(p2.y-y), float(p2.x - x) )*ipl_RADIANS2DEGREES;
}

/*
BOOL CIplPoint::operator>(IPLPOINT point) const
{ return (x > point.x && y > point.y); }
BOOL CIplPoint::operator<(IPLPOINT point) const
{ return (x < point.x && y < point.y); }
BOOL CIplPoint::operator>=(IPLPOINT point) const
{ return (x >= point.x && y >= point.y); }
BOOL CIplPoint::operator<=(IPLPOINT point) const
{ return (x <= point.x && y <= point.y); }
*/

// CIplPointLabel
CIplPointLabel::CIplPointLabel()
{ x = 0; y = 0; nLabel = -1; }
CIplPointLabel::CIplPointLabel(int initX, int initY)
{ x = initX; y = initY; nLabel = -1; }
CIplPointLabel::CIplPointLabel(int initX, int initY, int nInLabel)
{ x = initX; y = initY; nLabel = nInLabel; }
CIplPointLabel::CIplPointLabel(const IPLPOINT& initPt)
{ x = initPt.x; y = initPt.y; }
CIplPointLabel::CIplPointLabel(const IPLPOINTLABEL& initPt)
{ 
	*(IPLPOINTLABEL*)this = initPt; 
}
CIplPointLabel::CIplPointLabel( const CIplPointLabel& point )
{ *this = point; }
float CIplPointLabel::GetDistance(const IPLPOINT& p2)
{
	return sqrt( (float)((p2.x-x)*(p2.x-x) + (float)(p2.y-y)*(p2.y-y)) );
}
float CIplPointLabel::GetDistance(const IPLPOINTLABEL& p2)
{
	return sqrt( (float)((p2.x-x)*(p2.x-x) + (float)(p2.y-y)*(p2.y-y)) );
}
BOOL CIplPointLabel::operator==(IPLPOINTLABEL point) const
{ return (x == point.x && y == point.y); }
BOOL CIplPointLabel::operator!=(IPLPOINTLABEL point) const
{ return (x != point.x || y != point.y); }

void CIplPointLabel::operator+=(IPLPOINTLABEL point)
{ x += point.x; y += point.y; }
void CIplPointLabel::operator-=(IPLPOINTLABEL point)
{ x -= point.x; y -= point.y; }
void CIplPointLabel::operator+=(IPLPOINT point)
{ x += point.x; y += point.y; }
void CIplPointLabel::operator-=(IPLPOINT point)
{ x -= point.x; y -= point.y; }
CIplPointLabel CIplPointLabel::operator+(IPLPOINT point) const
{ return CIplPointLabel(x + point.x, y + point.y); }
CIplPointLabel CIplPointLabel::operator-(IPLPOINT point) const
{ return CIplPointLabel(x - point.x, y - point.y); }
CIplPointLabel CIplPointLabel::operator-() const
{ return CIplPointLabel(-x, -y); }
CIplPointLabel CIplPointLabel::operator+(IPLPOINTLABEL point) const
{ return CIplPointLabel(x + point.x, y + point.y); }


// CIplPoint
CIplfPoint::CIplfPoint()
{ x = 0.f; y = 0.f;  }
CIplfPoint::CIplfPoint(int initX, int initY)
{ x = (float)initX; y = (float)initY; }
CIplfPoint::CIplfPoint(float initX, float initY)
{ x = initX; y = initY; }
CIplfPoint::CIplfPoint(IPLPOINT initPt)
{ x = (float)initPt.x; y = (float)initPt.y; }
CIplfPoint::CIplfPoint(IPLFPOINT initPt)
{ *(IPLFPOINT*)this = initPt; }
CIplfPoint::CIplfPoint(IPLSIZE initSize)
{ x = (float)initSize.cx; y = (float)initSize.cy; }
void CIplfPoint::Offset(int xOffset, int yOffset)
{ x += (float)xOffset; y += (float)yOffset; }
void CIplfPoint::Offset(float xOffset, float yOffset)
{ x += xOffset; y += yOffset; }
void CIplfPoint::Offset(IPLPOINT point)
{ x += (float)point.x; y += (float)point.y; }
void CIplfPoint::Offset(IPLFPOINT point)
{ x += point.x; y += point.y; }
void CIplfPoint::Offset(IPLSIZE size)
{ x += (float)size.cx; y += (float)size.cy; }
BOOL CIplfPoint::operator==(IPLPOINT point) const
{ return (x == (float)point.x && y == (float)point.y); }
BOOL CIplfPoint::operator==(IPLFPOINT point) const
{ return (x == point.x && y == point.y); }
BOOL CIplfPoint::operator!=(IPLPOINT point) const
{ return (x != (float)point.x || y != (float)point.y); }
BOOL CIplfPoint::operator!=(IPLFPOINT point) const
{ return (x != point.x || y != point.y); }
void CIplfPoint::operator+=(IPLSIZE size)
{ x += (float)size.cx; y += (float)size.cy; }
void CIplfPoint::operator-=(IPLSIZE size)
{ x -= (float)size.cx; y -= (float)size.cy; }
void CIplfPoint::operator+=(IPLPOINT point)
{ x += (float)point.x; y += (float)point.y; }
void CIplfPoint::operator+=(IPLFPOINT point)
{ x += point.x; y += point.y; }
void CIplfPoint::operator-=(IPLPOINT point)
{ x -= (float)point.x; y -= (float)point.y; }
void CIplfPoint::operator-=(IPLFPOINT point)
{ x -= point.x; y -= point.y; }
CIplfPoint CIplfPoint::operator+(IPLSIZE size) const
{ return CIplfPoint(x + (float)size.cx, y + (float)size.cy); }
CIplfPoint CIplfPoint::operator-(IPLSIZE size) const
{ return CIplfPoint(x - (float)size.cx, y - (float)size.cy); }
CIplfPoint CIplfPoint::operator-() const
{ return CIplfPoint(-x, -y); }
CIplfPoint CIplfPoint::operator+(IPLPOINT point) const
{ return CIplfPoint(x + (float)point.x, y + (float)point.y); }
CIplfPoint CIplfPoint::operator+(IPLFPOINT point) const
{ return CIplfPoint(x + point.x, y + point.y); }
CIplSize CIplfPoint::operator-(IPLPOINT point) const
{ return CIplSize((int)(x - point.x), (int)(y - point.y)); }
CIplSize CIplfPoint::operator-(IPLFPOINT point) const
{ return CIplSize( (int)(x - point.x), (int)(y - point.y)); }
float CIplfPoint::GetDistance(const IPLPOINT& p2)
{
	return sqrt( (float)((p2.x-x)*(p2.x-x) + (float)(p2.y-y)*(p2.y-y)) );
}
float CIplfPoint::GetDistance(const IPLFPOINT& p2)
{
	return sqrt( (p2.x-x)*(p2.x-x) + (p2.y-y)*(p2.y-y) );
}

/*
CIplRect CIplPoint::operator+(const LPIPLRECT lpRect) const
{ return CIplRect(lpRect) + *this; }
CIplRect CIplPoint::operator-(const LPIPLRECT lpRect) const
{ return CIplRect(lpRect) - *this; }
*/


// CIplRect
CIplRect::CIplRect()
{ left = 0; top = 0; right = 0; bottom = 0; }
CIplRect::CIplRect(int l, int t, int r, int b)
{ left = l; top = t; right = r; bottom = b; }
CIplRect::CIplRect(const IPLRECT& srcRect)
{ iplmemcpy(this, &srcRect, sizeof(IPLRECT)); }
CIplRect::CIplRect(LPCIPLRECT lpSrcRect)
{ iplmemcpy(this, lpSrcRect, sizeof(IPLRECT)); }
CIplRect::CIplRect(IPLPOINT point, IPLSIZE size)
{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
CIplRect::CIplRect(IPLPOINT topLeft, IPLPOINT bottomRight)
{ left = topLeft.x; top = topLeft.y;
right = bottomRight.x; bottom = bottomRight.y; }
int CIplRect::Width() const
{ return right - left; }
int CIplRect::Height() const
{ return bottom - top; }
CIplSize CIplRect::Size() const
{ return CIplSize(right - left, bottom - top); }
CIplPoint& CIplRect::TopLeft()
{ return *((CIplPoint*)this); }
CIplPoint& CIplRect::BottomRight()
{ return *((CIplPoint*)this+1); }
const CIplPoint& CIplRect::TopLeft() const
{ return *((CIplPoint*)this); }
const CIplPoint& CIplRect::BottomRight() const
{ return *((CIplPoint*)this+1); }
CIplPoint CIplRect::CenterPoint() const
{ return CIplPoint((left+right)/2, (top+bottom)/2); }
void CIplRect::SwapLeftRight()
{ SwapLeftRight(LPIPLRECT(this)); }
void CIplRect::SwapLeftRight(LPIPLRECT lpRect)
{ LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
CIplRect::operator LPIPLRECT()
{ return this; }
CIplRect::operator LPCIPLRECT() const
{ return this; }
//BOOL CIplRect::IsRectEmpty() const
//{ return ::IsRectEmpty(this); }
BOOL CIplRect::IsRectNull() const
{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
BOOL CIplRect::PtInRect(IPLPOINT point) const
{ return ( (left<=point.x)&&(point.x<=right)&&(top<=point.y)&&(point.y<=bottom) ); }
void CIplRect::SetRect(int x1, int y1, int x2, int y2)
{ left = min(x1,x2); top =min(y1,y2) ; right = max(x1,x2); bottom = max(y1,y2); }
void CIplRect::SetRect(IPLPOINT topLeft, IPLPOINT bottomRight)
{ left = topLeft.x, top =topLeft.y, right = bottomRight.x, bottom = bottomRight.y; }
void CIplRect::SetRectEmpty()
{ left = 0; top = 0; right = 0; bottom = 0; }
void CIplRect::CopyRect(LPCIPLRECT lpSrcRect)
{ left = lpSrcRect->left; top = lpSrcRect->top; right = lpSrcRect->right; bottom = lpSrcRect->bottom; }
BOOL CIplRect::EqualRect(LPCIPLRECT lpRect) const
{ return ( (left ==lpRect->left ) && (top   ==lpRect->top   ) &&
           (right==lpRect->right) && (bottom==lpRect->bottom)   ); }
//void CIplRect::InflateRect(int x, int y)
//{ ::InflateRect(this, x, y); }
//void CIplRect::InflateRect(IPLSIZE size)
//{ ::InflateRect(this, size.cx, size.cy); }
//void CIplRect::DeflateRect(int x, int y)
//{ ::InflateRect(this, -x, -y); }
//void CIplRect::DeflateRect(IPLSIZE size)
//{ ::InflateRect(this, -size.cx, -size.cy); }
//void CIplRect::OffsetRect(int x, int y)
//{ ::OffsetRect(this, x, y); }
//void CIplRect::OffsetRect(IPLPOINT point)
//{ ::OffsetRect(this, point.x, point.y); }
//void CIplRect::OffsetRect(IPLSIZE size)
//{ ::OffsetRect(this, size.cx, size.cy); }
//BOOL CIplRect::IntersectRect(LPCIPLRECT lpRect1, LPCIPLRECT lpRect2)
//{ return ::IntersectRect(this, lpRect1, lpRect2);}
//BOOL CIplRect::UnionRect(LPCIPLRECT lpRect1, LPCIPLRECT lpRect2)
//{ return ::UnionRect(this, lpRect1, lpRect2); }
void CIplRect::operator=(const IPLRECT& srcRect)
{ CopyRect(&srcRect); }
BOOL CIplRect::operator==(const IPLRECT& rect) const
{ return EqualRect(&rect); }
BOOL CIplRect::operator!=(const IPLRECT& rect) const
{ return !EqualRect(&rect); }
/*
void CIplRect::operator+=(IPLPOINT point)
{ ::OffsetRect(this, point.x, point.y); }
void CIplRect::operator+=(IPLSIZE size)
{ ::OffsetRect(this, size.cx, size.cy); }
void CIplRect::operator+=(LPCIPLRECT lpRect)
{ InflateRect(lpRect); }
void CIplRect::operator-=(IPLPOINT point)
{ ::OffsetRect(this, -point.x, -point.y); }
void CIplRect::operator-=(IPLSIZE size)
{ ::OffsetRect(this, -size.cx, -size.cy); }
void CIplRect::operator-=(LPCIPLRECT lpRect)
{ DeflateRect(lpRect); }
void CIplRect::operator&=(const IPLRECT& rect)
{ ::IntersectRect(this, this, &rect); }
void CIplRect::operator|=(const IPLRECT& rect)
{ ::UnionRect(this, this, &rect); }
CIplRect CIplRect::operator+(IPLPOINT pt) const
{ CIplRect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
CIplRect CIplRect::operator-(IPLPOINT pt) const
{ CIplRect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
CIplRect CIplRect::operator+(IPLSIZE size) const
{ CIplRect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
CIplRect CIplRect::operator-(IPLSIZE size) const
{ CIplRect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
CIplRect CIplRect::operator+(LPCIPLRECT lpRect) const
{ CIplRect rect(this); rect.InflateRect(lpRect); return rect; }
CIplRect CIplRect::operator-(LPCIPLRECT lpRect) const
{ CIplRect rect(this); rect.DeflateRect(lpRect); return rect; }
CIplRect CIplRect::operator&(const IPLRECT& rect2) const
{ CIplRect rect; ::IntersectRect(&rect, this, &rect2);
return rect; }
CIplRect CIplRect::operator|(const IPLRECT& rect2) const
{ CIplRect rect; ::UnionRect(&rect, this, &rect2);
return rect; }
BOOL CIplRect::SubtractRect(LPCIPLRECT lpRectSrc1, LPCIPLRECT lpRectSrc2)
{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }
*/


// CIplLine
CIplLine::CIplLine()
{}
CIplLine::CIplLine(int x1, int y1, int x2, int y2)
{p1.x = x1; p1.y=y1; p2.x=x2; p2.y=y2;}
CIplLine::CIplLine(IPLPOINT initp1, IPLPOINT initp2)
{
	iplmemcpy( &p1, &initp1, sizeof(IPLPOINT) );
	iplmemcpy( &p2, &initp2, sizeof(IPLPOINT) );
}
CIplLine::CIplLine(const IPLLINE& initLine)
{*(IPLLINE*)this = initLine;}
void CIplLine::OffsetX(int xOffset)
{p1.x += xOffset; p2.x += xOffset;}
void CIplLine::OffsetY(int yOffset)
{p1.y += yOffset; p2.y += yOffset;}
BOOL CIplLine::operator==(IPLLINE line) const
{
	float fGradient1   = (float)(p2.y-p1.y)/(float)(p2.x-p1.x);
	float fYIntercept1 = (float)p1.y - fGradient1*(float)p1.x;

	float fGradient2   = (float)(line.p2.y-line.p1.y)/(float)(line.p2.x-line.p1.x);
	float fYIntercept2 = (float)line.p1.y - fGradient2*(float)line.p1.x;

	return ( fGradient1==fGradient2 && fYIntercept1==fYIntercept2 );
}

BOOL CIplLine::operator!=(IPLLINE line) const
{
	float fGradient1   = (float)(p2.y-p1.y)/(float)(p2.x-p1.x);
	float fYIntercept1 = (float)p1.y - fGradient1*(float)p1.x;

	float fGradient2   = (float)(line.p2.y-line.p1.y)/(float)(line.p2.x-line.p1.x);
	float fYIntercept2 = (float)line.p1.y - fGradient2*(float)line.p1.x;

	return ( fGradient1!=fGradient2 || fYIntercept1!=fYIntercept2 );
}

void CIplLine::operator=(const IPLLINE& line)
{
	iplmemcpy( &p1, &line.p1, sizeof(IPLPOINT) );
	iplmemcpy( &p2, &line.p2, sizeof(IPLPOINT) );
}

void CIplLine::operator=(const CIplLine& line)
{
	iplmemcpy( &p1, &line.p1, sizeof(IPLPOINT) );
	iplmemcpy( &p2, &line.p2, sizeof(IPLPOINT) );
}

float CIplLine::GetLength ( void )
{
	return CIplPoint(p1).GetDistance(p2);
}


//CIplLineExtension
CIplLineExtension::CIplLineExtension():CIplLine()
{}
CIplLineExtension::CIplLineExtension(int x1, int y1, int x2, int y2):CIplLine(x1,y1,x2,y2)
{ SolveAttribute(); }
CIplLineExtension::CIplLineExtension(IPLPOINT p1, IPLPOINT p2):CIplLine(p1,p2)
{ SolveAttribute(); }
CIplLineExtension::CIplLineExtension(const IPLLINE& initLine):CIplLine(initLine)
{ SolveAttribute(); }
void   CIplLineExtension::SolveAttribute(void)
{
	m_fGradient      = (float)(p2.y-p1.y)/(float)(p2.x-p1.x);
	m_fYIntercept    = (float)p1.y - m_fGradient*(float)p1.x;
	m_fPointDistance = CIplPoint(p1).GetDistance(p2);
}
void CIplLineExtension::OffsetX(int xOffset)
{
	CIplLine::OffsetX(xOffset);
	SolveAttribute();
}
void CIplLineExtension::OffsetY(int yOffset)
{
	CIplLine::OffsetY(yOffset);
	SolveAttribute();
}
float CIplLineExtension::GetGradient(void)
{ return m_fGradient;}
float CIplLineExtension::GetOriginDistance(void)
{ return GetDistance(CIplPoint(0,0));}
float CIplLineExtension::GetPointDistance(void)
{ return m_fPointDistance;}
float CIplLineExtension::GetYIntercept(void)
{ return m_fYIntercept; }
BOOL CIplLineExtension::operator==(IPLLINE line) const
{
	float fGradient2   = (float)(line.p2.y-line.p1.y)/(float)(line.p2.x-line.p1.x);
	float fYIntercept2 = (float)line.p1.y - fGradient2*(float)line.p1.x;

	return ( m_fGradient==fGradient2 && m_fYIntercept==fYIntercept2 );
}
BOOL CIplLineExtension::operator!=(IPLLINE line) const
{
	float fGradient2   = (float)(line.p2.y-line.p1.y)/(float)(line.p2.x-line.p1.x);
	float fYIntercept2 = (float)line.p1.y - fGradient2*(float)line.p1.x;

	return ( m_fGradient!=fGradient2 || m_fYIntercept!=fYIntercept2 );
}
BOOL CIplLineExtension::operator==(const CIplLineExtension& line) const
{ return ( m_fGradient==line.m_fGradient && m_fYIntercept==line.m_fYIntercept);}
BOOL CIplLineExtension::operator!=(const CIplLineExtension& line) const
{ return ( m_fGradient!=line.m_fGradient || m_fYIntercept!=line.m_fYIntercept);}

float CIplLineExtension::GetDistance(const IPLPOINT& point)
{
	float fPerpendicularityGradient   = (float)(p2.x-p1.x)/(float)(p2.y-p1.y);
	float fPerpendicularityYIntercept = point.y - fPerpendicularityGradient*point.x;

	CIplLineExtension PerpendicularityLine( point, CIplPoint(0,(int)(fPerpendicularityYIntercept+0.5)));

	CIplPoint crossPoint = GetCrossPoint(PerpendicularityLine);

	return crossPoint.GetDistance(point);
}

CIplPoint CIplLineExtension::GetCrossPoint  (const IPLLINE& line) const
{
//	CIplLineExtension eline(line);
	return GetCrossPoint( CIplLineExtension(line) );
}

CIplPoint CIplLineExtension::GetCrossPoint(const CIplLineExtension& line) const
{
	line.m_fGradient;
	float y = (line.m_fGradient*m_fYIntercept - m_fGradient*line.m_fYIntercept) / (line.m_fGradient-m_fGradient);
	float x = (y-m_fYIntercept)/m_fGradient;

	return CIplPoint((long)(y+0.5),(long)(x+0.5));
}

