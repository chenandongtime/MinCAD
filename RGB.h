#pragma once
#ifndef CRGB_C
#define CRGB_C

class CRGB
{

public:
	//construct and deconstruct
	CRGB() = default;
	CRGB(double R, double G, double B);
	virtual~CRGB();

	//拷贝构造函数和赋值运算符
	CRGB(const CRGB&);
	CRGB operator=(const CRGB&);
	
	//运算符重载
	friend CRGB operator+(const CRGB&, const CRGB&);
	friend CRGB operator-(const CRGB&, const CRGB&);
	
	//friend CRGB operator*(const CRGB&, const CRGB&);
	friend CRGB operator*(const CRGB&, double);
	friend CRGB operator*(double, const CRGB&);

	friend CRGB operator/(const CRGB&, double);
	//friend CRGB operator / (const CRGB&, const CRGB&);

	friend CRGB operator+=(CRGB&, const CRGB&);
	friend CRGB operator-=(CRGB&, const CRGB&);

	friend CRGB operator *=(CRGB&,  double);
	friend CRGB operator /=(CRGB&,  double);

	friend bool operator ==(const CRGB&, const CRGB&);
	friend bool operator != (const CRGB&, const CRGB&);

	// operation
	void Normalize();//归一化

	//attribution
	double red;
	double green;
	double blue;

};
#endif // !CRGB_C



