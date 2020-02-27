#include "pch.h"
#include "CQuad.h"

CQuad::CQuad(CPoint3D& lb, CPoint3D& rb, CPoint3D& ru, CPoint3D& lu) :
	leftUp(lu), rightUp(ru), leftBottom(lb), rightBottom(rb) {
	
	//用四个点初始化四条线
	bottomLine.startP = leftBottom;
	bottomLine.endP = rightBottom;

	rightLine.startP = rightBottom;
	rightLine.endP = rightUp;

	upLine.startP = rightUp;
	upLine.endP = leftUp;

	leftLine.startP = leftUp;
	leftLine.endP = leftBottom;
}
CQuad::CQuad(CLine& bL, CLine& rL, CLine& uL, CLine& lL):bottomLine(bL),rightLine(rL),upLine(uL),leftLine(lL)
{
	leftBottom = bottomLine.startP;
	rightBottom = bottomLine.endP;
	rightUp = upLine.startP;
	leftUp = upLine.endP;
}
CQuad::CQuad(CQuad& quad)
{
	this->setLeftUp(quad.getLeftUp());
	this->setLeftBottom(quad.getLeftBottom());
	this->setRightUp(quad.getRightUp());
	this->setRightBottom(quad.getRightBottom());
}
void CQuad::setLeftUp(CPoint3D& P)
{
	//同时更新顶点和线的信息

	leftUp = P;
	upLine.endP = P;
	leftLine.startP = P;
}
void CQuad::setLeftBottom(CPoint3D& P)
{
	//同时更新顶点和线的信息
	leftBottom = P;
	bottomLine.startP = P;
	leftLine.endP = P;
}
void CQuad::setRightBottom(CPoint3D& P)
{
	rightBottom = P;
	bottomLine.endP = P;
	rightLine.startP = P;
}
void CQuad::setRightUp(CPoint3D& P)
{
	rightUp = P;
	upLine.startP = P;
	rightLine.endP = P;
}
CPoint3D CQuad::getLeftUp()
{
	return leftUp;
}
CPoint3D CQuad::getLeftBottom()
{
	return leftBottom;
}
CPoint3D CQuad::getRightUp()
{
	return rightUp;
}
CPoint3D CQuad::getRightBottom()
{
	return rightBottom;
}
CLine CQuad::getBottomLine()
{
	return bottomLine;
}
CLine CQuad::getRightLine()
{
	return rightLine;
}
CLine CQuad::getUpLine()
{
	return upLine;
}
CLine CQuad::getLeftLine()
{
	return leftLine;
}
void CQuad::drawQuad(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC)
{
	bottomLine.drawLine(screenHeight, screenWidth,camera,pDC);
	rightLine.drawLine(screenHeight, screenWidth, camera, pDC);
	upLine.drawLine(screenHeight, screenWidth, camera, pDC);
	leftLine.drawLine(screenHeight, screenWidth, camera, pDC);
}
;