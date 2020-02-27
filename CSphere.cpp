#include "pch.h"
#include "CSphere.h"
#define PI 3.14159

CSphere::CSphere(double r, double theta, double beta)
{
	this->R = r;
	this->beta = beta;
	this->theta = theta;
	this->createPointList();
	this->creatFaceList();
}

CSphere::~CSphere()
{
	delete[] point3DList; 
	delete[] faceList; 
}

//********************************************指针版**********************************************//
void CSphere::createPointList()
{
	int NBeta = (int) (180 / this->beta);
	int NTheta = (int)(360 / this->theta);
	//+2是南北极的点 -1是纬度线只有中间的线，两极点没有线,沿纬度线一圈把七点和终点都保存下来，虽然两点位置一样
	this->point3DList = new CPoint3D[(NTheta+1) * (NBeta-1)+ 2];
	//创建北极点
	point3DList[0].x = 0;
	point3DList[0].y = 0;
	point3DList[0].z = this->R;
	//for循环不能从0开始
	for(int NB = 1;NB < NBeta;NB++)
		for (int NT = 1; NT <= (NTheta+1); NT++) {
			point3DList[(NB - 1) * (NTheta + 1) + NT ].x = (this->R * sin(NB * beta*PI/180)) * cos((NT-1) * theta * PI / 180);
			point3DList[(NB - 1) * (NTheta + 1) + NT ].y = (this->R * sin(NB * beta * PI / 180)) * sin((NT-1) * theta * PI / 180);
			point3DList[(NB - 1) * (NTheta + 1) + NT ].z = this->R * cos(NB * beta * PI / 180);
		}
	//创建南极点
	point3DList[(NTheta + 1) * (NBeta - 1) + 1].x = 0;
	point3DList[(NTheta + 1) * (NBeta - 1) + 1].y = 0;
	point3DList[(NTheta + 1) * (NBeta - 1) + 1].z = -(this->R);
}

void CSphere::creatFaceList()
{
	int NBeta = (int)(180 / this->beta);
	int NTheta = (int)(360 / this->theta);

	faceList = new CFace[(NBeta - 1)* NTheta * 2+1];//三角形面片的个数,+1的原因是没有使用第一个内存存储三角形面
	for(int NB = 1;NB < NBeta;NB++)
		for (int NT = 1; NT <= NTheta ; NT = NT + 1) {
			//按照纬度线划分三角形，每一个纬度线上的两个点与上下的两点分别形成两个三角形
			//创建第一个三角形，上三角形
			faceList[(NB-1) * NTheta * 2 + 2*NT - 1].SetNum(3);
			faceList[(NB-1) * NTheta * 2 + 2 * NT - 1].vI[0] = ((NB-1) * (NTheta+1) + NT );//当前纬度线三角形的起点
			faceList[(NB - 1) * NTheta * 2 + 2 * NT - 1].vI[1] = ((NB - 1) * (NTheta+1) + NT+1);//当前纬度线的另一个点
			if (NB == 1)
				faceList[(NB - 1) * NTheta * 2 + 2 * NT - 1].vI[2] = 0;//最上方的纬度线的三角形的顶点在北极上
			else
				faceList[(NB - 1) * NTheta * 2 + 2 * NT - 1].vI[2] = ((NB - 2) * (NTheta+1) + NT + 1);//其他纬度线的三角形上顶点在上一条纬度线上
			//创建第二个三角形，下三角形
			faceList[(NB - 1) * NTheta * 2 + 2 * NT].SetNum(3);
			faceList[(NB - 1) * NTheta * 2 + 2 * NT].vI[0] = ((NB - 1) * (NTheta + 1) + NT + 1);
			faceList[(NB - 1) * NTheta * 2 + 2 * NT].vI[1] = ((NB - 1) * (NTheta + 1) + NT);
			if (NB == (NBeta - 1))
				faceList[(NB - 1) * NTheta * 2 + 2 * NT ].vI[2] = (NTheta + 1) * (NBeta - 1) + 1;//最下方的纬度线的三角形的顶点在南极上
			else
				faceList[(NB - 1) * NTheta * 2 + 2 * NT ].vI[2] = (NB * (NTheta + 1) + NT);//其他纬度线的三角形上顶点在下一条纬度线上
		}
}
//********************************************指针版**********************************************//


//void CSphere::createPointList()
//{
//	int NBeta = (int) (180 / this->beta);
//	int NTheta = (int)(360 / this->theta);
//	CPoint3D NorthPoint(0, 0, 0);
//	point3DList.push_back(NorthPoint);
//	for(int NB = 0; NB < (NBeta-1);NB++)
//		for (int NT = 1; NT <= (NTheta + 1); NT++)
//		{
//			CPoint3D middlePoint;
//			middlePoint.x = (this->R * sin(NB * beta)) * cos((NT - 1) * theta);
//			middlePoint.y = (this->R * sin(NB * beta)) * sin((NT - 1) * theta);
//			middlePoint.z = this->R * cos(NB * beta);
//		}
//}

bool CSphere::checkIfShow(CFace &face, CCamera& camera)
{
	//获取面上三个点的坐标
	CPoint3D P0 = (this->point3DList[face.vI[0]]);
	CPoint3D P1 = (this->point3DList[face.vI[1]]);
	CPoint3D P2 = (this->point3DList[face.vI[2]]);
	//把顶点坐标信息转换到相机参考系
	arma::mat P0mat ({ P0.x,P0.y,P0.z,1 });
	arma::mat P1mat ({ P1.x,P1.y,P1.z,1 });
	arma::mat P2mat({ P2.x,P2.y,P2.z,1 });

	P0mat = P0mat * camera.getRotateMat() * camera.getModelMat() * camera.getCameraMat();
	P1mat = P1mat * camera.getRotateMat() * camera.getModelMat() * camera.getCameraMat();
	P2mat = P2mat * camera.getRotateMat() * camera.getModelMat() * camera.getCameraMat();

	//当前顶点信息变成了相机参考系下的位置
	P0.x = P0mat[0]; P0.y = P0mat[1]; P0.z = P0mat[2];
	P1.x = P1mat[0]; P1.y = P1mat[1]; P1.z = P1mat[2];
	P2.x = P2mat[0]; P2.y = P2mat[1]; P2.z = P2mat[2];

	//获取两个向量
	arma::vec P01{ P1.x - P0.x, P1.y - P0.y, P1.z - P0.z };
	arma::vec P02{ P2.x - P0.x, P2.y - P0.y, P2.z - P0.z };
	
	//获取这个面的法向量 //右手定则
	arma::vec PNormal = arma::cross(P01, P02);
	
	//获取视点在相机坐标系中的位置，这里视点是平面的中心
	CPoint3D PCenter((P0.x + P1.x + P2.x) / 3, (P0.y + P1.y + P2.y) / 3, (P0.z + P1.z + P2.z) / 3);
	//获取（视矢量）视点到相机位置的向量
	arma::vec PCamera{ 0 - PCenter.x,0 - PCenter.y,0 - PCenter.z };

	//判断视矢量和法式量的点乘是否大于等于0，是则返回true,表示平面可以显示
	if (arma::dot(PCamera, PNormal) >= 0)
		return true;
	return false;
}

void CSphere::noHideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC)
{
	int NBeta = (int)(180 / this->beta);
	int NTheta = (int)(360 / this->theta);

	int faceNum = (NBeta - 1) * NTheta * 2 + 1;

	for (int i = 1; i < faceNum; i++) {
		CLine line1(point3DList[faceList[i].vI[0]], point3DList[faceList[i].vI[1]]);
		CLine line2(point3DList[faceList[i].vI[0]], point3DList[faceList[i].vI[2]]);
		CLine line3(point3DList[faceList[i].vI[1]], point3DList[faceList[i].vI[2]]);
		line1.drawLine(screenHeight, screenWidth, camera, pDC);
		line2.drawLine(screenHeight, screenWidth, camera, pDC);
		line3.drawLine(screenHeight, screenWidth, camera, pDC);
	}
}

void CSphere::hideDraw(double screenHeight, double screenWidth, CCamera& camera, CDC* pDC)
{
	int NBeta = (int)(180 / this->beta);
	int NTheta = (int)(360 / this->theta);

	int faceNum = (NBeta - 1) * NTheta * 2 + 1;

	for (int i = 1; i < faceNum; i++) {
		if (checkIfShow(faceList[i], camera)) {
			CLine line1(point3DList[faceList[i].vI[0]], point3DList[faceList[i].vI[1]]);
			CLine line2(point3DList[faceList[i].vI[0]], point3DList[faceList[i].vI[2]]);
			CLine line3(point3DList[faceList[i].vI[1]], point3DList[faceList[i].vI[2]]);
			line1.drawLine(screenHeight, screenWidth, camera, pDC);
			line2.drawLine(screenHeight, screenWidth, camera, pDC);
			line3.drawLine(screenHeight, screenWidth, camera, pDC);
		}
	}
}
