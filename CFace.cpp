#include "pch.h"
#include "CFace.h"

CFace::CFace():
fNormal(0,0,0){
	vI = NULL;
}

CFace::~CFace()
{
	if (vI != NULL)
	{
		delete[]vI;
		vI = NULL;
	}
}

void CFace::SetNum(int vN)
{
	this->vN = vN;
	vI = new int[vN];
}

void CFace::SetFaceNormal(CPoint3D& P1, CPoint3D& P2, CPoint3D& P3)
{
	CPoint3D v0(P2 - P1);
	CPoint3D v1(P3 - P1);
	fNormal.x = v0.y * v1.z - v0.z * v1.y;
	fNormal.y = v0.z * v1.x - v0.x * v1.z;
	fNormal.z = v0.x * v1.y - v0.y * v1.x;

}
