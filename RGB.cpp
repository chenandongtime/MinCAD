#include "pch.h"
#include "RGB.h"
#include <stdexcept>
#include <iostream>

CRGB::CRGB(double R, double G, double B)
{
	try {
		if ((R < 0)|| (R > 255) ||(G < 0)|| (G > 255) ||(B < 0)|| (B > 255)) { throw std::runtime_error("RGB value must between 0 to 255."); }
	}
	catch (std::runtime_error err) { std::cerr << err.what() << std::endl; }
	
	this->red = R;
	this->green = G;
	this->blue = B;

}

CRGB::CRGB(const CRGB& rgb)
{
	try {
		if ((rgb.red < 0) || (rgb.red > 255) || (rgb.green < 0) 
			|| (rgb.green > 255) || (rgb.blue < 0) || (rgb.blue > 255)) 
		{ throw std::runtime_error("RGB value must between 0 to 255."); }
	}
	catch (std::runtime_error err) { std::cerr << err.what() << std::endl; }

	this->red = rgb.red;
	this->green = rgb.green;
	this->blue = rgb.blue;
}

CRGB CRGB::operator=(const CRGB& rgb)
{
	// TODO: 在此处插入 return 语句
	try {
		if ((rgb.red < 0) || (rgb.red > 255) || (rgb.green < 0) 
			|| (rgb.green > 255) || (rgb.blue < 0) || (rgb.blue > 255))
		{ throw std::runtime_error("RGB value must between 0 to 255."); }
	}
	catch (std::runtime_error err) { std::cerr << err.what() << std::endl; }

	this->red = rgb.red;
	this->green = rgb.green;
	this->blue = rgb.blue;

	return *this;

}

CRGB::~CRGB()
{
}

void CRGB::Normalize()
{
	this->red /= 255;
	this->green /= 255;
	this->blue /= 255;

}

CRGB operator+(const CRGB& first, const CRGB& second)
{

	return CRGB(first.red + second.red,first.green+second.green,first.blue+second.blue);
}

CRGB operator-(const CRGB& first, const CRGB& second)
{
	return CRGB(first.red - second.red, first.green - second.green, first.blue - second.blue);
}

CRGB operator*(const CRGB& first, double b)
{
	return CRGB(first.red*b,first.green * b,first.blue*b);
}

CRGB operator*(double a, const CRGB& second)
{
	return CRGB(a*second.red,a*second.green,a*second.blue);
}

CRGB operator/(const CRGB& first , double b)
{
	return CRGB(first.red / b,first.green / b,first.blue / b);
}

CRGB operator+=(CRGB&first, const CRGB& second)
{
	first = first + second;
	return first;
}

CRGB operator-=(CRGB&first, const CRGB& second)
{
	first = first - second;
	return first;
}

CRGB operator*=(CRGB& first,  double b)
{
	first = first * b;
	return first;
}

CRGB operator/=(CRGB& first , double b)
{
	first = first / b;
	return first;
}

bool operator==(const CRGB&first, const CRGB&second)
{
	return ((first.red == second.red) && (first.green == second.green) && (first.blue == second.blue));
}

bool operator!=(const CRGB& first, const CRGB& second)
{
	return (!(first == second));
}


