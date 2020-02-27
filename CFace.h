#pragma once
#ifndef CFACE_H
#define CFACE_H
#include "CPoint3D.h"
#include "Math.h"
class CFace
{
public :
	CFace();
	virtual ~CFace();
	void SetNum(int vN);
	void SetFaceNormal(CPoint3D &P1,CPoint3D &P2,CPoint3D &P3);//设置小面法式量
public:
	int vN;//小面的定点数
	int* vI;//小面的顶点索引
	CPoint3D fNormal;//小面的法式量
};


#endif // !CFACE_H

