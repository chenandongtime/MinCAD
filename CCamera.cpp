#include "pch.h"
#include "CCamera.h"
#include <math.h>
#define PI  3.14159 //圆周率
#define eps 0.0000001 //无穷小

double CCamera::ZDistance = 300; //和Camera 初始化的值一样
double CCamera::angle = 45;
arma::Mat<double>  CCamera::CameraMat({ {1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,CCamera::ZDistance,1} }); // 世界参考系到相机参考系的变换矩阵
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
	////测试绕X轴旋转
	//arma::Mat<double> matRoateX(4, 4, arma::fill::eye);
	//double theta = 45 * PI / 180;
	//matRoateX(1, 1) = cos(theta);
	//matRoateX(2, 2) = cos(theta);
	//matRoateX(2, 1) = -sin(theta);
	//matRoateX(1, 2) = sin(theta);

	////测试绕Y轴旋转
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
	//计算视口的大小
	double rateWH = screenWidth / screenHeight;
	double viewHeight = tan(PI * angle / 180) * (ZDistance) / 2;//视口也就是成像面的位置在相机与世界参考系原点的中间
	double viewWidth = viewHeight * rateWH;
	double rateScreenView = screenHeight / viewHeight;//视口大小和屏幕大小的比例
	
	if ((abs(viewPoint.y) < abs(viewHeight)) && (abs(viewPoint.x)<abs(viewWidth)))//点在视口内，则可以投影到屏幕上
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
	//将坐标值标准化到0-1之间
	startPoint /= (screenWidth*1.414);
	endPoint /= (screenWidth * 1.414);

	//根据轨迹球原理获取屏幕上两个点投影在轨迹球上的Z值
	double startPointZ = sqrt(1 - startPoint.x * startPoint.x - startPoint.y * startPoint.y);
	double endPointZ = sqrt(1 - endPoint.x * endPoint.x - endPoint.y * endPoint.y);

	//构建叉乘的起始向量和终点向量
	arma::vec startVec = { startPoint.x,startPoint.y,startPointZ };
	arma::vec endVec = { endPoint.x,endPoint.y,endPointZ };

	//叉乘获得旋转轴，注意这里是右手定则叉乘
	rotateVec = arma::cross(startVec, endVec);

	if (! _finite(rotateVec[0]))
		int a = 1;;


	//arccos获得两个向量之间的夹角
	rotateTheta = acos(arma::dot(startVec, endVec));
}

void CCamera::getLocalRotateAxis(arma::mat &localRotateAxis, arma::vec RotateAxis)
{
	//向量可以当作七点在原点的点，所以把相机坐标系内的向量转化到局部坐标系中只有做到把这个点，乘以没有平移变换的camera逆矩阵和model你矩阵即可
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
	//绕任意轴旋转theta角是非常复杂的，需要做多个级联变换，线把任意轴旋转到
	//某个坐标轴上，然后对这个坐标轴旋转theta角，最后再把任意轴旋转回去

	//把任意轴旋转到xoz平面内
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

	//绕y轴旋转，与z轴重合
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

	//绕z轴旋转rotateTheta
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
	// 获得相机坐标系下的选装轴和旋转角
	double theta;
	arma::vec cameraAxisVec;
	getRotateAxisTheta(theta, cameraAxisVec, startPoint, endPoint, screenWidth);

	//获得局部坐标系下的旋转轴
	arma::mat localAxis;
	getLocalRotateAxis(localAxis, cameraAxisVec);

	//在局部坐标系下旋转，也就是改变局部坐标变换矩阵
	rotateInLocal(localAxis, theta
	);//减慢旋转的速度
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
//	//调用windows GDI 画直线
//	//先画Z轴
//	CPen MyPen, * OldPen;
//	MyPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//红色
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2ZAxis.x, D2ZAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//
//	//画y轴
//	MyPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));//绿色
//	OldPen = pDC->SelectObject(&MyPen);
//	pDC->MoveTo(D2Origin.x, D2Origin.y);
//	pDC->LineTo(D2YAxis.x, D2YAxis.y);
//	pDC->SelectObject(OldPen);
//	MyPen.DeleteObject();
//
//	//画X轴
//	MyPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));//蓝色
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
//	//调用windows GDI 画直线
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
