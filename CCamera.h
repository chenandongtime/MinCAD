#pragma once

#ifndef CCAMERA_H
#define CCAMERA_H

#include "CPoint3D.h"
#include "CPoint2D.h"
#include "math.h"
#include <armadillo> //���������
#include "pch.h"


class CCamera
{
public:
	CCamera();
	~CCamera() {};
	int a;

public:
	static double ZDistance;//��Z������������������ĵľ���
	static double angle;

	//�ܵ�����任���������Գɹ���ʾ����Ļ���򷵻�true,���ҽ���Ļ���ص�λ�ø�ScreenPoint ���������򷵻�false
	bool transCoordinate(CPoint2D &ScreenPoint,CPoint3D &worldPoint,double screenHeight,double screenWidth);

	// ����arcBallԭ���ھֲ�����ϵ����ת���壬ʵ���ϸı���localRotateMat�ľ�������
	void arcBallRotate(CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth);

	arma::Mat<double> getCameraMat();
	arma::Mat<double> getModelMat();
	arma::Mat<double> getRotateMat();
	////�Ѿֲ�����ϵ�������ử����
	//void drawLocalCoord(double screenHeight, double screenWidth, CDC *pDC);

	//void drawLocalRotateAxis(CPoint2D& startPoint, CPoint2D& endPoint, double screenHeight, double screenWidth, CDC* pDC);

	//bool transLocalCoordinate(CPoint2D& ScreenPoint, CPoint3D& worldPoint, double screenHeight, double screenWidth);

private:

	arma::mat localRotateAxis;	//ģ������ϵ���ֲ�����ϵ������ת��
	static arma::Mat<double> CameraMat; // ����ο�ϵ������ο�ϵ�ı任��֤
	static arma::Mat<double> perspectiveMat; //͸��ͶӰ���󣬽���ά����䵽��ά����ƽ����
	arma::Mat<double> ModelMat; //�ֲ��ο�ϵ������ο�ϵ�ı任����
	arma::Mat<double> localRotateMat; //�ھֲ�����ϵ�µ���ת

	void initModelMat();
	void initLocalRotateMat();

	//���ڴ��ڷ�Χ�ڵĵ�ת������Ļ���꣬����㲻�ڴ����ڣ��򷵻�false
	bool viewToScreen(CPoint2D& ScreenPoint, CPoint2D& viewPoint, double angle, double screenHeight, double screenWidth);
	
	// arcBall ��켣��ת�������ת��������ת��
	void getRotateAxisTheta(double& rotateTheta, arma::vec& rotateVec, CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth);

	//����ת��ת�����ֲ�����ϵ��
	void getLocalRotateAxis(arma::mat& localRotateAxis, arma::vec RotateAxis);

	//�ھֲ�����ϵ����ת
	void rotateInLocal(arma::mat raotateAxis, double rotateTheta);
};

#endif // !CCAMERA_H




