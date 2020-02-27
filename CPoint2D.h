#pragma oncec
#ifndef CPOINT2D
#define CPOINT2D

class CPoint2D
{
public:
	double x;
	double y;

public:
	CPoint2D() = default;
	~CPoint2D() {};
	CPoint2D(double a, double b) :x(a), y(b) {};
	CPoint2D(CPoint2D& p) :x(p.x), y(p.y) {};

	friend CPoint2D operator+(const CPoint2D&, const CPoint2D&);
	friend CPoint2D operator-(const CPoint2D&, const CPoint2D&);

	friend CPoint2D operator*(const CPoint2D& ,double);
	friend CPoint2D operator*(double, const CPoint2D&);
	friend CPoint2D operator/(const CPoint2D&, double);

	friend CPoint2D operator+=(CPoint2D&, const CPoint2D&);
	friend CPoint2D operator-=(CPoint2D&, const CPoint2D&);
	friend CPoint2D operator*=(CPoint2D&, double);
	friend CPoint2D operator/=(CPoint2D&, double);

	friend bool operator==(const CPoint2D&, const CPoint2D&);
	friend bool operator!=(const CPoint2D&, const CPoint2D&);

	
};
#endif // !CPOINT2D



