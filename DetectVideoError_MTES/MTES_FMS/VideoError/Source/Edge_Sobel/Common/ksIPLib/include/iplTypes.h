#ifndef _IPL_TYPES_H_INCLUDE_
#define _IPL_TYPES_H_INCLUDE_

class CIplSize;
class CIplPoint;
class CIplPointLabel;
class CIplRect;
class CIplLine;

class CIplSize : public iplSIZE
{
public:

// Constructors
	// construct an uninitialized size
	CIplSize();
	// create from two integers
	CIplSize(int initCX, int initCY);
	// create from another size
	CIplSize(const IPLSIZE initSize);
	// create from a point
	CIplSize(IPLPOINT initPt);

// Operations
	BOOL operator==(IPLSIZE size) const;
	BOOL operator!=(IPLSIZE size) const;
	VOID operator+=(IPLSIZE size);
	VOID operator-=(IPLSIZE size);

// Operators returning CIplSize values
	CIplSize operator+(IPLSIZE size) const;
	CIplSize operator-(IPLSIZE size) const;
	CIplSize operator-() const;

// Operators returning CIplPoint values
	CIplPoint operator+(IPLPOINT point) const;
	CIplPoint operator-(IPLPOINT point) const;

// Operators returning CIplRect values
//	CIplRect operator+(const LPIPLRECT lpRect) const;
//	CIplRect operator-(const LPIPLRECT lpRect) const;
};

/////////////////////////////////////////////////////////////////////////////
// CIplPoint - A 2-D point, similar to Windows IPLPOINT structure.

class CIplPoint : public iplPOINT
{
public:
// Constructors

	// create an uninitialized point
	CIplPoint();
	// create from two integers
	CIplPoint(int initX, int initY);
	// create from another point
	CIplPoint(const IPLPOINT initPt);
	// create from a size
	CIplPoint(IPLSIZE initSize);

// Operations

public:
// translate the point
	void Offset(int xOffset, int yOffset);
	void Offset(IPLPOINT point);
	void Offset(IPLSIZE size);
public:
	float GetDistance(const IPLPOINT& p2);
	float GetDegree  (const IPLPOINT& p2);

public:
	BOOL operator==(IPLPOINT point) const;
	BOOL operator!=(IPLPOINT point) const;
	void operator+=(IPLSIZE size);
	void operator-=(IPLSIZE size);
	void operator+=(IPLPOINT point);
	void operator-=(IPLPOINT point);
//	BOOL operator>(IPLPOINT point) const; 기준이 모호 하므로 제거
//	BOOL operator<(IPLPOINT point) const;
//	BOOL operator>=(IPLPOINT point) const;
//	BOOL operator<=(IPLPOINT point) const;

// Operators returning CIplPoint values
	CIplPoint operator+(IPLSIZE size) const;
	CIplPoint operator-(IPLSIZE size) const;
	CIplPoint operator-() const;
	CIplPoint operator+(IPLPOINT point) const;

// Operators returning CIplSize values
	CIplSize operator-(IPLPOINT point) const;


	void operator=(const IPLPOINTLABEL& point);
	void operator=(const CIplPointLabel& point);

// Operators returning CIplRect values
//	CIplRect operator+(const LPIPLRECT lpRect) const;
//	CIplRect operator-(const LPIPLRECT lpRect) const;

/*
	//아래 함수 구현 필요.
	double Distance(const IPLPOINT& point); 
	double Distance(const IPLLINE&  line ); 
*/
};

class CIplPointLabel : public IPLPOINTLABEL
{
public:
// Constructors

	// create an uninitialized point
	CIplPointLabel();

	// create from two integers
	CIplPointLabel( int initX, int initY );

	CIplPointLabel( int initX, int initY, int nLabel );

	// create from another point
	CIplPointLabel( const IPLPOINT& initPt );

	CIplPointLabel( const IPLPOINTLABEL& initPt );

	CIplPointLabel( const CIplPointLabel& point ); 

// Operations
public:
	float GetDistance(const IPLPOINT& p2);
	float GetDistance(const IPLPOINTLABEL& p2);

public:
	BOOL operator==(IPLPOINTLABEL point) const;
	BOOL operator!=(IPLPOINTLABEL point) const;
	void operator+=(IPLPOINTLABEL point);
	void operator-=(IPLPOINTLABEL point);
	void operator+=(IPLPOINT point);
	void operator-=(IPLPOINT point);

// Operators returning CIplPoint values
	CIplPointLabel operator+(IPLPOINT point) const;
	CIplPointLabel operator-(IPLPOINT point) const;
	CIplPointLabel operator-() const;
	CIplPointLabel operator+(IPLPOINTLABEL point) const;


/*
	//아래 함수 구현 필요.
	double Distance(const IPLPOINT& point); 
	double Distance(const IPLLINE&  line ); 
*/
};

class CIplfPoint : public iplFPOINT
{
public:
	// Constructors

	// create an uninitialized point
	CIplfPoint();
	// create from two integers
	CIplfPoint(int   initX, int   initY);
	CIplfPoint(float initX, float initY);
	// create from another point
	CIplfPoint(const IPLFPOINT initPt);
	CIplfPoint(const IPLPOINT  initPt);
	// create from a size
	CIplfPoint(IPLSIZE initSize);

	// Operations

public:
	// translate the point
	void Offset(float xOffset, float yOffset);
	void Offset(int   xOffset, int   yOffset);
	void Offset(IPLPOINT  point);
	void Offset(IPLFPOINT point);
	void Offset(IPLSIZE   size );
public:
	float GetDistance(const IPLPOINT&  p2);
	float GetDistance(const IPLFPOINT& p2);

public:
	BOOL operator==(IPLPOINT  point) const;
	BOOL operator==(IPLFPOINT point) const;
	BOOL operator!=(IPLPOINT  point) const;
	BOOL operator!=(IPLFPOINT point) const;
	void operator+=(IPLSIZE   size );
	void operator-=(IPLSIZE   size );
	void operator+=(IPLPOINT  point);
	void operator+=(IPLFPOINT point);
	void operator-=(IPLPOINT  point);
	void operator-=(IPLFPOINT point);

	// Operators returning CIplPoint values
	CIplfPoint operator+(IPLSIZE size) const;
	CIplfPoint operator-(IPLSIZE size) const;
	CIplfPoint operator-() const;
	CIplfPoint operator+(IPLPOINT  point) const;
	CIplfPoint operator+(IPLFPOINT point) const;

	// Operators returning CIplSize values
	CIplSize operator-(IPLPOINT  point) const;
	CIplSize operator-(IPLFPOINT point) const;

	// Operators returning CIplRect values
	//	CIplRect operator+(const LPIPLRECT lpRect) const;
	//	CIplRect operator-(const LPIPLRECT lpRect) const;

	/*
	//아래 함수 구현 필요.
	double Distance(const IPLPOINT& point); 
	double Distance(const IPLLINE&  line ); 
	*/
};

class CIplLine : public iplLINE
{
public:
	CIplLine();
	// from (x1, y1), (x2, y2)
	CIplLine(int x1, int y1, int x2, int y2);
	// from two points
	CIplLine(IPLPOINT p1, IPLPOINT p2); 
	// copy constructor
	CIplLine(const IPLLINE& initLine);

public:
	// translate the line
	virtual void OffsetX( int xOffset );
	virtual void OffsetY( int yOffset );
public:
	float     GetLength ( void );


public:
	void operator=(const IPLLINE& line);
	void operator=(const CIplLine& line);
	BOOL operator==(IPLLINE line) const;
	BOOL operator!=(IPLLINE line) const;
};


class CIplLineExtension : public CIplLine
{
public:
	CIplLineExtension        ();
	// from (x1, y1), (x2, y2)
	CIplLineExtension        (int x1, int y1, int x2, int y2);
	// from two points
	CIplLineExtension        (IPLPOINT p1, IPLPOINT p2); 
	// copy constructor
	CIplLineExtension        (const IPLLINE& initLine);
protected:
	void   SolveAttribute    (void);

public:
	// translate the line
	virtual void OffsetX(int xOffset);
	virtual void OffsetY(int yOffset);

public:
	float GetGradient       (void);
	float GetOriginDistance (void);
	float GetPointDistance  (void);
	float GetYIntercept     (void);
public:
	float     GetDistance    (const IPLPOINT& point); 
	CIplPoint GetCrossPoint  (const IPLLINE& line) const;
	CIplPoint GetCrossPoint  (const CIplLineExtension& line) const;

public:
	BOOL operator==(IPLLINE line) const;
	BOOL operator!=(IPLLINE line) const;
	BOOL operator==(const CIplLineExtension& line) const;
	BOOL operator!=(const CIplLineExtension& line) const;

protected:
	float m_fGradient      ;
	float m_fYIntercept    ;
	float m_fPointDistance ;
};


/////////////////////////////////////////////////////////////////////////////
// CIplRect - A 2-D rectangle, similar to Windows RECT structure.
class CIplRect : public iplRECT
{
public:
	// Constructors

	// uninitialized rectangle
	CIplRect();
	// from left, top, right, and bottom
	CIplRect(int left, int top, int right, int bottom);
	// copy constructor
	CIplRect(const IPLRECT& srcRect);
	// from a pointer to another rect
	CIplRect(LPCIPLRECT lpSrcRect);
	// from a point and size
	CIplRect(IPLPOINT point, IPLSIZE size);
	// from two points
	CIplRect(IPLPOINT topLeft, IPLPOINT bottomRight);

	// Attributes (in addition to RECT members)

	// retrieves the width
	int Width() const;
	// returns the height
	int Height() const;
	// returns the size
	CIplSize Size() const;
	// reference to the top-left point
	CIplPoint& TopLeft();
	// reference to the bottom-right point
	CIplPoint& BottomRight();
	// const reference to the top-left point
	const CIplPoint& TopLeft() const;
	// const reference to the bottom-right point
	const CIplPoint& BottomRight() const;
	// the geometric center point of the rectangle
	CIplPoint CenterPoint() const;
	// swap the left and right
	void SwapLeftRight();
	static void SwapLeftRight(LPIPLRECT lpRect);

	// convert between CIplRect and LPRECT/LPCIPLRECT (no need for &)
	operator LPIPLRECT();
	operator LPCIPLRECT() const;

	// returns TRUE if rectangle has no area
//	BOOL IsRectEmpty() const;
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const;
	// returns TRUE if point is within rectangle
	BOOL PtInRect(IPLPOINT point) const;

	// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(int x1, int y1, int x2, int y2);
	void SetRect(IPLPOINT topLeft, IPLPOINT bottomRight);
	// empty the rectangle
	void SetRectEmpty();
	// copy from another rectangle
	void CopyRect ( LPCIPLRECT lpSrcRect);
	// TRUE if exactly the same as another rectangle
	BOOL EqualRect( LPCIPLRECT lpRect   ) const;

	// inflate rectangle's width and height without
	// moving its top or left
//	void InflateRect(int x, int y);
//	void InflateRect(IPLSIZE size);
//	void InflateRect(LPCIPLRECT lpRect);
//	void InflateRect(int l, int t, int r, int b);
	// deflate the rectangle's width and height without
	// moving its top or left
//	void DeflateRect(int x, int y);
//	void DeflateRect(IPLSIZE size);
//	void DeflateRect(LPCIPLRECT lpRect);
//	void DeflateRect(int l, int t, int r, int b);

	// translate the rectangle by moving its top and left
//	void OffsetRect(int x, int y);
//	void OffsetRect(IPLSIZE size);
//	void OffsetRect(IPLPOINT point);
//	void NormalizeRect();

	// set this rectangle to intersection of two others
//	BOOL IntersectRect(LPCIPLRECT lpRect1, LPCIPLRECT lpRect2);

	// set this rectangle to bounding union of two others
//	BOOL UnionRect(LPCIPLRECT lpRect1, LPCIPLRECT lpRect2);

	// set this rectangle to minimum of two others
//	BOOL SubtractRect(LPCIPLRECT lpRectSrc1, LPCIPLRECT lpRectSrc2);

	// Additional Operations
	void operator=(const IPLRECT& srcRect);
	BOOL operator==(const IPLRECT& rect) const;
	BOOL operator!=(const IPLRECT& rect) const;
/*
	void operator+=(IPLPOINT point);
	void operator+=(IPLSIZE size);
	void operator+=(LPCIPLRECT lpRect);
	void operator-=(IPLPOINT point);
	void operator-=(IPLSIZE size);
	void operator-=(LPCIPLRECT lpRect);
	void operator&=(const IPLRECT& rect);
	void operator|=(const IPLRECT& rect);

	// Operators returning CIplRect values
	CIplRect operator+(IPLPOINT point) const;
	CIplRect operator-(IPLPOINT point) const;
	CIplRect operator+(LPCIPLRECT lpRect) const;
	CIplRect operator+(IPLSIZE size) const;
	CIplRect operator-(IPLSIZE size) const;
	CIplRect operator-(LPCIPLRECT lpRect) const;
	CIplRect operator&(const IPLRECT& rect2) const;
	CIplRect operator|(const IPLRECT& rect2) const;
	CIplRect MulDiv(int nMultiplier, int nDivisor) const;
*/
};





#endif //_IPL_TYPES_H_INCLUDE_
