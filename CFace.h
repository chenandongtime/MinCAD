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
	void SetFaceNormal(CPoint3D &P1,CPoint3D &P2,CPoint3D &P3);//����С�淨ʽ��
public:
	int vN;//С��Ķ�����
	int* vI;//С��Ķ�������
	CPoint3D fNormal;//С��ķ�ʽ��
};


#endif // !CFACE_H

