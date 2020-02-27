#include "pch.h"
#include "CPoint3D.h"

CPoint3D operator+(const CPoint3D& first, const CPoint3D& second)
{
	return CPoint3D(first.x+second.x,first.y+second.y,first.z+second.z);
}

CPoint3D operator-(const CPoint3D& first, const CPoint3D& second)
{
	return CPoint3D(first.x-second.x,first.y-second.y,first.z-second.z);
}

CPoint3D operator*(const CPoint3D& first, double b)
{
	return CPoint3D(first.x * b,first.y*b,first.z*b);
}

CPoint3D operator*(double b, const CPoint3D& first)
{
	return (first * b);
}

CPoint3D operator/(const CPoint3D& first, double b)
{
	return CPoint3D(first.x / b,first.y / b,first.z / b);
}

CPoint3D& operator+=( CPoint3D& first, const CPoint3D&second)
{
	// TODO: �ڴ˴����� return ���
	first = first + second;
	return first;

}

CPoint3D& operator-=(CPoint3D&first, const CPoint3D&second)
{
	// TODO: �ڴ˴����� return ���
	first = first - second;
	return first;
}

CPoint3D& operator*=(CPoint3D& first, double b)
{
	// TODO: �ڴ˴����� return ���
	first = first * b;
	return first;
}

CPoint3D& operator/=(CPoint3D& first, double b)
{
	// TODO: �ڴ˴����� return ���
	first = first / b;
	return first;
}

bool operator==(const CPoint3D& first, const CPoint3D& second)
{
	return ((first.x == second.x)&&(first.y == second.y)&&(first.z == second.z));
}

bool operator!=(const CPoint3D& first, const CPoint3D& second)
{
	return !(first == second);
}
