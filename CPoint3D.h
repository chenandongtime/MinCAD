#pragma once
#ifndef CPOINT3D_H
#define CPOINT3D_H


class CPoint3D
{
public:
	double x;
	double y;
	double z;

public:
	CPoint3D() = default;
	~CPoint3D() {};
	CPoint3D(double a, double b, double c) :x(a), y(b), z(c) {};
	CPoint3D(CPoint3D& p) :x(p.x), y(p.y), z(p.z) {};

	friend CPoint3D operator+(const CPoint3D&, const CPoint3D&);
	friend CPoint3D operator-(const CPoint3D&, const CPoint3D&);

	friend CPoint3D operator*(const CPoint3D&, double);
	friend CPoint3D operator*(double, const CPoint3D&);
	friend CPoint3D operator/(const CPoint3D&, double);

	friend CPoint3D& operator+=(CPoint3D&, const CPoint3D&);
	friend CPoint3D& operator-=(CPoint3D&, const CPoint3D&);
	friend CPoint3D& operator*=(CPoint3D&, double);
	friend CPoint3D& operator/=(CPoint3D&, double);

	friend bool operator==(const CPoint3D&, const CPoint3D&);
	friend bool operator!=(const CPoint3D&, const CPoint3D&);

};



#endif // !CPOINT3D_H
