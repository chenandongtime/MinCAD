#include "pch.h"
#include "CCube.h"

CCube::CCube(P3D& bLB, P3D& bRB, P3D& bRU, P3D& bLU, P3D& fLB, P3D& fRB, P3D& fRU, P3D& fLU)
	:bLeftBottom(bLB), bLeftUp(bLU),bRightBottom(bRB),bRightUP(bRU),
	fLeftBottom(fLB), fLeftUp(fLU), fRightBottom(fRB),fRightUP(fRU),
	frontQ(fLB,fRB,fRU,fLU),
	backQ(bLB, bRB, bRU, bLU),
	upQ(fLU, fRU, bRU, bLU),
	bottomQ(bLB, bRB, fRB, fLB),
	rightQ(fRB,bRB,bRU,fRU),
	leftQ(bLB, fLB, fLU, bLU)
{
	
}

void CCube::drawCube(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC)
{
	//调用面对象的绘画函数
	frontQ.drawQuad(screenHeight, screenWidth, camera, pDC);
	backQ.drawQuad(screenHeight, screenWidth, camera, pDC);
	upQ.drawQuad(screenHeight, screenWidth, camera, pDC);
	bottomQ.drawQuad(screenHeight, screenWidth, camera, pDC);
	leftQ.drawQuad(screenHeight, screenWidth, camera, pDC);
	rightQ.drawQuad(screenHeight, screenWidth, camera, pDC);
}
