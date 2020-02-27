#pragma once

#ifndef CCAMERA_H
#define CCAMERA_H

#include "CPoint3D.h"
#include "CPoint2D.h"
#include "math.h"
#include <armadillo> //矩阵运算库
#include "pch.h"


class CCamera
{
public:
	CCamera();
	~CCamera() {};
	int a;

public:
	static double ZDistance;//沿Z轴相机到世界坐标中心的距离
	static double angle;

	//总的坐标变换函数，可以成功显示在屏幕上则返回true,并且将屏幕像素的位置给ScreenPoint 参数，否则返回false
	bool transCoordinate(CPoint2D &ScreenPoint,CPoint3D &worldPoint,double screenHeight,double screenWidth);

	// 利用arcBall原理，在局部坐标系内旋转物体，实际上改变了localRotateMat的矩阵内容
	void arcBallRotate(CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth);

	arma::Mat<double> getCameraMat();
	arma::Mat<double> getModelMat();
	arma::Mat<double> getRotateMat();
	////把局部坐标系的坐标轴画出来
	//void drawLocalCoord(double screenHeight, double screenWidth, CDC *pDC);

	//void drawLocalRotateAxis(CPoint2D& startPoint, CPoint2D& endPoint, double screenHeight, double screenWidth, CDC* pDC);

	//bool transLocalCoordinate(CPoint2D& ScreenPoint, CPoint3D& worldPoint, double screenHeight, double screenWidth);

private:

	arma::mat localRotateAxis;	//模型坐标系（局部坐标系）的旋转轴
	static arma::Mat<double> CameraMat; // 世界参考系到相机参考系的变换举证
	static arma::Mat<double> perspectiveMat; //透视投影矩阵，将三维坐标变到二维成像平面上
	arma::Mat<double> ModelMat; //局部参考系到世界参考系的变换矩阵
	arma::Mat<double> localRotateMat; //在局部坐标系下的旋转

	void initModelMat();
	void initLocalRotateMat();

	//将在窗口范围内的点转化到屏幕坐标，如果点不在窗口内，则返回false
	bool viewToScreen(CPoint2D& ScreenPoint, CPoint2D& viewPoint, double angle, double screenHeight, double screenWidth);
	
	// arcBall 球轨迹旋转法获得旋转向量和旋转角
	void getRotateAxisTheta(double& rotateTheta, arma::vec& rotateVec, CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth);

	//将旋转轴转化到局部坐标系中
	void getLocalRotateAxis(arma::mat& localRotateAxis, arma::vec RotateAxis);

	//在局部坐标系中旋转
	void rotateInLocal(arma::mat raotateAxis, double rotateTheta);
};

#endif // !CCAMERA_H




