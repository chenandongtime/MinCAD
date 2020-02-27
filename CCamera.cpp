#include "pch.h"
#include "CCamera.h"
#include <math.h>
#define PI  3.14159 //Բ����
#define eps 0.0000001 //����С

double CCamera::ZDistance = 300; //��Camera ��ʼ����ֵһ��
double CCamera::angle = 45;
arma::Mat<double>  CCamera::CameraMat({ {1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,CCamera::ZDistance,1} }); // ����ο�ϵ������ο�ϵ�ı任����
arma::Mat<double>  CCamera::perspectiveMat({ {1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,2 / CCamera::ZDistance,1} });

CCamera::CCamera()
{
	initModelMat(); 
	initLocalRotateMat(); 
}

void CCamera::initModelMat()
{
	arma::Mat<double> mat(4, 4, arma::fill::eye);
	ModelMat = mat;
}

void CCamera::initLocalRotateMat()
{
	////������X����ת
	//arma::Mat<double> matRoateX(4, 4, arma::fill::eye);
	//double theta = 45 * PI / 180;
	//matRoateX(1, 1) = cos(theta);
	//matRoateX(2, 2) = cos(theta);
	//matRoateX(2, 1) = -sin(theta);
	//matRoateX(1, 2) = sin(theta);

	////������Y����ת
	//arma::Mat<double> matRoateY(4, 4, arma::fill::eye);
	//matRoateY(0, 0) = cos(-theta);
	//matRoateY(0, 2) = -sin(-theta);
	//matRoateY(2, 0) = sin(-theta);
	//matRoateY(2, 2) = cos(-theta);

	arma::Mat<double> mat(4, 4, arma::fill::eye);

	localRotateMat = mat;
	

}

bool CCamera::viewToScreen(CPoint2D& ScreenPoint, CPoint2D& viewPoint, double angle,double screenHeight,double screenWidth)
{
	//�����ӿڵĴ�С
	double rateWH = screenWidth / screenHeight;
	double viewHeight = tan(PI * angle / 180) * (ZDistance) / 2;//�ӿ�Ҳ���ǳ������λ�������������ο�ϵԭ����м�
	double viewWidth = viewHeight * rateWH;
	double rateScreenView = screenHeight / viewHeight;//�ӿڴ�С����Ļ��С�ı���
	
	if ((abs(viewPoint.y) < abs(viewHeight)) && (abs(viewPoint.x)<abs(viewWidth)))//�����ӿ��ڣ������ͶӰ����Ļ��
	{
		ScreenPoint.x = viewPoint.x * rateScreenView;
		ScreenPoint.y = viewPoint.y * rateScreenView;

		return true;
	}

	return false;
}

bool CCamera::transCoordinate(CPoint2D& ScreenPoint, CPoint3D& worldPoint, double screenHeight, double screenWidth)
{
	arma::Mat<double> point3DMat({ worldPoint.x,worldPoint.y,worldPoint.z,1 });
	arma::Mat<double> point2DMat = point3DMat * localRotateMat * ModelMat * CameraMat * perspectiveMat;

	CPoint2D viewPoint(point2DMat(0), point2DMat(1));

	if (viewToScreen(ScreenPoint, viewPoint, angle, screenHeight, screenWidth))
		return true;
	return false;
}

void CCamera::getRotateAxisTheta(double& rotateTheta, arma::vec& rotateVec, CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth)
{
	//������ֵ��׼����0-1֮��
	startPoint /= (screenWidth*1.414);
	endPoint /= (screenWidth * 1.414);

	//���ݹ켣��ԭ���ȡ��Ļ��������ͶӰ�ڹ켣���ϵ�Zֵ
	double startPointZ = sqrt(1 - startPoint.x * startPoint.x - startPoint.y * startPoint.y);
	double endPointZ = sqrt(1 - endPoint.x * endPoint.x - endPoint.y * endPoint.y);

	//������˵���ʼ�������յ�����
	arma::vec startVec = { startPoint.x,startPoint.y,startPointZ };
	arma::vec endVec = { endPoint.x,endPoint.y,endPointZ };

	//��˻����ת�ᣬע�����������ֶ�����
	rotateVec = arma::cross(startVec, endVec);

	if (! _finite(rotateVec[0]))
		int a = 1;;


	//arccos�����������֮��ļн�
	rotateTheta = acos(arma::dot(startVec, endVec));
}

void CCamera::getLocalRotateAxis(arma::mat &localRotateAxis, arma::vec RotateAxis)
{
	//�������Ե����ߵ���ԭ��ĵ㣬���԰��������ϵ�ڵ�����ת�����ֲ�����ϵ��ֻ������������㣬����û��ƽ�Ʊ任��camera������model����󼴿�
	arma::mat matAxis({ RotateAxis[0], RotateAxis[1], RotateAxis[2], 1 });
	arma::mat invCameraMat = this->CameraMat;
	arma::mat invModelMat = this->ModelMat;

	invCameraMat(3, 0) = 0;
	invCameraMat(3, 1) = 0;
	invCameraMat(3, 2) = 0;

	invModelMat(3, 0) = 0; 
	invModelMat(3, 1) = 0;
	invModelMat(3, 2) = 0;

	localRotateAxis = matAxis * inv(invCameraMat) * inv(invModelMat);
	this->localRotateAxis = localRotateAxis;
}

void CCamera::rotateInLocal(arma::mat rotateAxis, double rotateTheta)
{
	//����������תtheta���Ƿǳ����ӵģ���Ҫ����������任���߰���������ת��
	//ĳ���������ϣ�Ȼ��������������תtheta�ǣ�����ٰ���������ת��ȥ

	//����������ת��xozƽ����
	arma::mat rotateXOZ(4, 4, arma::fill::eye);
	double u = sqrt(rotateAxis(2) * rotateAxis(2) + rotateAxis(1) * rotateAxis(1));
	double cosA;
	double sinA;
	if (u < eps) {
		cosA = 1.0;
		sinA = 0;
	}
	else {
		cosA = rotateAxis(2) / (u);
		sinA = rotateAxis(1) / (u);
	}
	rotateXOZ(1, 1) = cosA;
	rotateXOZ(2, 2) = cosA;
	rotateXOZ(1, 2) = sinA;
	rotateXOZ(2, 1) = -sinA;

	//��y����ת����z���غ�
	arma::mat rotateY(4, 4, arma::fill::eye);
	double v = sqrt(rotateAxis(2) * rotateAxis(2) + rotateAxis(1) * rotateAxis(1) + rotateAxis(0) * rotateAxis(0));
	double cosB;
	double sinB;
	if (v < eps) {
		cosB = 1.0;
		sinB = 0.0;
	}
	else {
		cosB = u / (v + eps);
		sinB = rotateAxis(0) / (v + eps);
	}
	rotateY(0, 0) = cosB;
	rotateY(0, 2) = sinB;
	rotateY(2, 0) = -sinB;
	rotateY(2, 2) = cosB;

	//��z����תrotateTheta
	arma::mat rotateZ(4, 4, arma::fill::eye);
	rotateZ(0, 0) = cos(rotateTheta);
	rotateZ(0, 1) = sin(rotateTheta);
	rotateZ(1, 0) = -sin(rotateTheta);
	rotateZ(1, 1) = cos(rotateTheta);

	arma::mat invRotateY = inv(rotateY);
	arma::mat invRotateXOZ = inv(rotateXOZ);

	localRotateMat = localRotateMat * rotateXOZ * rotateY * rotateZ * invRotateY * invRotateXOZ;
}

void CCamera::arcBallRotate(CPoint2D& startPoint, CPoint2D& endPoint, double screenWidth)
{
	// ����������ϵ�µ�ѡװ�����ת��
	double theta;
	arma::vec cameraAxisVec;
	getRotateAxisTheta(theta, cameraAxisVec, startPoint, endPoint, screenWidth);

	//��þֲ�����ϵ�µ���ת��
	arma::mat localAxis;
	getLocalRotateAxis(localAxis, cameraAxisVec);

	//�ھֲ�����ϵ����ת��Ҳ���Ǹı�ֲ�����任����
	rotateInLocal(localAxis, theta
	);//������ת���ٶ�
}

arma::Mat<double> CCamera::getCameraMat()
{
	return this->CameraMat;
}

arma::Mat<double> CCamera::getModelMat()
{
	return this->ModelMat;
}

arma::Mat<double> CCamera::getRotateMat()
{
	return this->localRotateMat;
}

//void CCamera::drawLocalCoord(double screenHeight, double screenWidth,CDC* pDC)
//{
//	CPoint3D origin(0, 0, 0);
//	CPoint3D ZAxis(0, 0, 10);
//	CPoint3D YAxis(0, 10, 0);
//	CPoint3D XAxis(10, 0, 0);
//
//	CPoint2D D2Origin;
//	CPoint2D D2ZAxis;
//	CPoint2D D2YAxis;
//	CPoint2D D2XAxis;
//
//	//transLocalCoordinate(D2Origin, origin, screenHeight, screenWidth);
//	//transLocalCoordinate(D2ZAxis, ZAxis, screenHeight, screenWidth);
//	//transLocalCoordinate(D2YAxis, YAxis, screenHeight, screenWidth);
//	//transLocalCoordinate(D2XAxis, XAxis, screenHeight, screenWidth);
//
//	transCoordinate(D2Origin, origin, screenHeight, screenWidth);
//	transCoordinate(D2ZAxis, ZAxis, screenHeight, screenWidth);
//	transCoordinate(D2YAxis, YAxis, screenHeight, screenWidth);
//	transCoordinate(D2XAxis, XAxis, screenHeight, screenWidth);
//	//����windows GDI ��ֱ��
//	//�Ȼ�Z��
//	CPen MyPen, * OldPen;
//	MyPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//��ɫ
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2ZAxis.x, D2ZAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//
//	//��y��
//	MyPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));//��ɫ
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2YAxis.x, D2YAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//
//	//��X��
//	MyPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));//��ɫ
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2XAxis.x, D2XAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//
//}

//
//void CCamera::drawLocalRotateAxis(CPoint2D& startPoint, CPoint2D& endPoint,double screenHeight, double screenWidth, CDC* pDC)
//{
//	CPoint3D origin(0,0,0);
//
//	CPoint3D localAxisP(this->localRotateAxis(0),this->localRotateAxis(1),this->localRotateAxis(2));
//	CPoint2D D2Origin;
//	CPoint2D D2localAxis;
//	transLocalCoordinate(D2Origin, origin, screenHeight, screenWidth);
//	transLocalCoordinate(D2localAxis, localAxisP*10, screenHeight, screenWidth);
//
//	//����windows GDI ��ֱ��
//	CPen MyPen, * OldPen;
//	MyPen.CreatePen(PS_SOLID, 8, RGB(125, 125, 0));
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2localAxis.x, D2localAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//}
//
//bool CCamera::transLocalCoordinate(CPoint2D& ScreenPoint, CPoint3D& worldPoint, double screenHeight, double screenWidth)
//{
//	arma::Mat<double> point3DMat({ worldPoint.x,worldPoint.y,worldPoint.z,1 });
//	arma::Mat<double> point2DMat = point3DMat * ModelMat * CameraMat * perspectiveMat;
//
//	CPoint2D viewPoint(point2DMat(0), point2DMat(1));
//
//	if (viewToScreen(ScreenPoint, viewPoint, angle, screenHeight, screenWidth))
//		return true;
//	return false;
//}
