#pragma once
#ifndef  CLINE_H
#define CLINE_H

#include "CPoint3D.h"
#include "CPoint2D.h"
#include "pch.h"
#include "CCamera.h"
//#include "CCamera.h"

class CLine
{
public:
	CPoint3D startP;
	CPoint3D endP;

	CLine() = default;
	~CLine() {};

	CLine(CPoint3D& start, CPoint3D& end) :startP(start), endP(end) {};
	CLine(CLine& line) :startP(line.startP), endP(line.endP) {};

	void drawLine(double screenHeight,double screenWidth,CCamera & camera,CDC *pDC);
};

#endif // ! CLINE_H



