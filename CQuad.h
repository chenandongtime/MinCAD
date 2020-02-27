#pragma once
#ifndef CQUAD_H
#define CQUAD_H

#include "CPoint3D.h"
#include "CLine.h"
#include "pch.h"

class CQuad
{

private :
	CPoint3D leftUp;
	CPoint3D rightUp;
	CPoint3D leftBottom;
	CPoint3D rightBottom;

	CLine bottomLine;
	CLine rightLine;
	CLine upLine;
	CLine leftLine;


public:
	CQuad() = default; //��������һ���������ڵ���
	~CQuad() {};
	CQuad(CPoint3D& lb, CPoint3D& rb, CPoint3D& ru, CPoint3D& lu);
	CQuad(CLine& bL, CLine& rL, CLine& uL, CLine& lL);

	//���忽�����캯��
	CQuad(CQuad&);

	//���嶥���޸ĺ���
	//ͬʱ���¶�����ߵ���Ϣ
	void setLeftUp(CPoint3D& P);
	void setLeftBottom(CPoint3D& P);
	void setRightBottom(CPoint3D& P);
	void setRightUp(CPoint3D& P);

	//��ȡ������߱�
	CPoint3D getLeftUp();
	CPoint3D getLeftBottom();
	CPoint3D getRightUp();
	CPoint3D getRightBottom();

	CLine getBottomLine();
	CLine getRightLine();
	CLine getUpLine();
	CLine getLeftLine();

	//draw ���������
	void drawQuad(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);
};


#endif // !CQUAD_H


