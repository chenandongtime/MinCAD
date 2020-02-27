#include "pch.h"
#include "CLine.h"
#include "CCamera.h"

void CLine::drawLine(double screenHeight, double screenWidth, CCamera& camera,CDC* pDC)
{
	CPoint2D ScreenStart;
	CPoint2D ScreenEnd;

	if(camera.transCoordinate(ScreenStart, this->startP, screenHeight, screenWidth)
		&& (camera.transCoordinate(ScreenEnd, this->endP, screenHeight, screenWidth)))//只有当两个点都在屏幕内才画线
	{
		//调用windows GDI 画直线
		CPen MyPen, * OldPen;
		MyPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		OldPen = pDC->SelectObject(&MyPen);
		pDC->MoveTo(ScreenStart.x, ScreenStart.y);
		pDC->LineTo(ScreenEnd.x, ScreenEnd.y);
		pDC->SelectObject(OldPen);
		MyPen.DeleteObject();
	}
	else {
		try { if (true) throw std::runtime_error(" out of screen"); }
		catch (std::runtime_error err) { std::cout << err.what() << std::endl; }
	}

}
