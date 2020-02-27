#pragma once

#ifndef CSPHERE_H
#define CSPHERE_H
#include <vector>
#include "CPoint3D.h"
#include "CFace.h"
#include "CLine.h"
#include "CCamera.h"
#include <armadillo> //���������

class CSphere
{
private:
	double R; //��İ뾶
	double theta;//���ά�ȷֱ���
	double beta;//��ľ��ȷֱ���

	//std::vector<CPoint3D> point3DList;//��������
	//std::vector<CFace> faceList;//������
	CPoint3D *point3DList;
	CFace* faceList;

public:
	CSphere(double r,double theta,double beta);
	~CSphere() ;



	void createPointList();//������������
	void creatFaceList();

	bool checkIfShow(CFace &face,CCamera &camera);
	void noHideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);
	void hideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC);
};

#endif 


