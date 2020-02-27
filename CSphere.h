#pragma once

#ifndef CSPHERE_H
#define CSPHERE_H
#include <vector>
#include "CPoint3D.h"
#include "CFace.h"
#include "CLine.h"
#include "CCamera.h"
#include <armadillo> //矩阵运算库

class CSphere
{
private:
	double R; //球的半径
	double theta;//球的维度分辨率
	double beta;//球的经度分辨率

	//std::vector<CPoint3D> point3DList;//顶点数组
	//std::vector<CFace> faceList;//面数组
	CPoint3D *point3DList;
	CFace* faceList;

public:
	CSphere(double r,double theta,double beta);
	~CSphere() ;



	void createPointList();//创建顶点数组
	void creatFaceList();

	bool checkIfShow(CFace &face,CCamera &camera);
	void noHideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);
	void hideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);
};

#endif 


