#include "pch.h"
#include "CPoint2D.h"
#include <stdexcept>
#include <iostream>


CPoint2D operator+(const CPoint2D& first, const CPoint2D& second)
{
	return CPoint2D(first.x + second.x, first.y + second.y);
}

CPoint2D operator-(const CPoint2D& first, const CPoint2D& second)
{
	return CPoint2D(first.x+second.x,first.y+second.y);
}

CPoint2D operator*(const CPoint2D& first, double b)
{
	return CPoint2D(first.x *b,first.y *b);
}

CPoint2D operator*(double b, const CPoint2D& first)
{
	return (first * b);
}

CPoint2D operator/(const CPoint2D& first , double b)
{
	try { if (b == 0) throw std::runtime_error("the / number can't be 0"); }
	catch (std::runtime_error err) { std::cout << err.what() << std::endl; b = 1; }

	return CPoint2D(first.x / b,first.y /b);
}

CPoint2D operator+=(CPoint2D&first, const CPoint2D& second)
{
	first = first + second;
	return first;
}

CPoint2D operator-=(CPoint2D&first, const CPoint2D& second)
{
	first = first - second;
	return first;
}

CPoint2D operator*=(CPoint2D& first, double b)
{
	first = first * b;
	return first;
}

CPoint2D operator/=(CPoint2D& first, double b)
{
	first = first / b;
	return first;
}

bool operator==(const CPoint2D& first, const CPoint2D& second)
{
	return ((first.x == second.x) && (first.y == second.y));
}

bool operator!=(const CPoint2D& first, const CPoint2D& second)
{
	return !(first == second);
}

