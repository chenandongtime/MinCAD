#pragma once
#ifndef  CCube_H
#define CCube_H
#include "pch.h"
#include "CPoint3D.h"
#include "CQuad.h"
#include <array>

//根据 孔林德计算机图形学 基础教程P205页 立方体边表法 编号
class CCube
{
private:
	
	//std::array <CPoint3D,8> pointList;//顶点列表
	CPoint3D bLeftBottom;
	CPoint3D bLeftUp;
	CPoint3D bRightBottom;
	CPoint3D bRightUP;

	CPoint3D fLeftBottom;
	CPoint3D fLeftUp;
	CPoint3D fRightBottom;
	CPoint3D fRightUP;

	CQuad frontQ;
	CQuad backQ;
	CQuad upQ;
	CQuad bottomQ;
	CQuad rightQ;
	CQuad leftQ;

public:
	typedef CPoint3D P3D;

	~CCube() {};
	CCube(P3D& bLB, P3D& bRB, P3D& bRU, P3D& bLU, P3D& fLB, P3D& fRB, P3D& fRU, P3D& fLU);
	//没有定义拷贝构造函数，不要轻易使用它

	void drawCube(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);

};

#endif // ! CCube_H




