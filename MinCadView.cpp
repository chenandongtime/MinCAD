
// MinCadView.cpp: CMinCadView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MinCad.h"
#endif

#include "MinCadDoc.h"
#include "MinCadView.h"

// include my class
#include"CLine.h"
#include"CPoint3D.h"
#include "CQuad.h"
#include "CCube.h"
#include "CCamera.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMinCadView

IMPLEMENT_DYNCREATE(CMinCadView, CView)

BEGIN_MESSAGE_MAP(CMinCadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMinCadView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CUBE, drawIDCCube)// 画cube的响应函数
	ON_COMMAND(ID_Sphere, &CMinCadView::OnSphere)
	ON_COMMAND(ID_SphereHide, &CMinCadView::OnSpherehide)
END_MESSAGE_MAP()

// CMinCadView 构造/析构


CMinCadView::CMinCadView() noexcept
{
	// TODO: 在此处添加构造代码
	rButtonDown = false;
	
	startPoint.x = 0;
	startPoint.y = 0;
	
	endPoint.x = 0;
	endPoint.y = 0;

	firstRbuttonDown = true;

	testAxisCal = true;

	drawCube = false;
	drawSphere = false;
	drawSpherHide = false;

}

CMinCadView::~CMinCadView()
{
}

BOOL CMinCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMinCadView 绘图

void CMinCadView::OnDraw(CDC* pDC)
{
	CMinCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DoubleBuffer(pDC);
}


// CMinCadView 打印


void CMinCadView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMinCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMinCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMinCadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMinCadView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	rButtonDown = false;
	firstRbuttonDown = true;
	//endPoint.x = point.x;
	//endPoint.y = point.y;

	ClientToScreen(&point);
	//
	//OnContextMenu(this, point);

	//Invalidate(FALSE);
}

void CMinCadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMinCadView 诊断

#ifdef _DEBUG
void CMinCadView::AssertValid() const
{
	CView::AssertValid();
}

void CMinCadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMinCadDoc* CMinCadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMinCadDoc)));
	return (CMinCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMinCadView 消息处理程序


//双缓冲就是，有两款内存区域，交互着使用，防止屏幕画图时闪烁
void CMinCadView::DoubleBuffer(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);// 自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//客户区中心为原点
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC 
	CBitmap NewBitmap, * pOldBitmap;//内存中承载的临时位图	
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC 
	memDC.FillSolidRect(rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);

	////更新局部旋转坐标
	if ((startPoint != endPoint))
	{
		CPoint2D startP;
		CPoint2D endP;
		startP.x = startPoint.x - rect.Width() / 2;
		startP.y = startPoint.y - rect.Height() / 2;
		startP.y = - startP.y;

		endP.x = endPoint.x - rect.Width() / 2;
		endP.y = endPoint.y - rect.Height() / 2;
		endP.y = -endP.y;

		acube.arcBallRotate(startP, endP, rect.Width() / 2);

	}

	if (this->drawCube) {
		CPoint3D bLeftBottom(-20, -20, -20);
		CPoint3D bLeftUp(-20, -20, 20);
		CPoint3D bRightBottom(-20, 20, -20);
		CPoint3D bRightUP(-20, 20, 20);

		CPoint3D fLeftBottom(20, -20, -20);
		CPoint3D fLeftUp(20, -20, 20);
		CPoint3D fRightBottom(20, 20, -20);
		CPoint3D fRightUP(20, 20, 20);
		CCube cube(bLeftBottom, bRightBottom, bRightUP, bLeftUp, fLeftBottom, fRightBottom, fRightUP, fLeftUp);

		cube.drawCube(rect.Height(), rect.Width(), acube, &memDC);
	}
	else if (this->drawSpherHide) {
		CSphere csPhere(40, 12, 6);
		csPhere.hideDraw(rect.Height(), rect.Width(), acube, &memDC);
	}
	else if (this->drawSphere) {
		CSphere csPhere(40, 12, 6);
		csPhere.noHideDraw(rect.Height(), rect.Width(), acube, &memDC);
	}


	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
}


void CMinCadView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	rButtonDown = true;
	startPoint.x = point.x;
	startPoint.y = point.y;

	CView::OnRButtonDown(nFlags, point);
}


void CMinCadView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (rButtonDown)
	{
		if (firstRbuttonDown)
		{
			if ((abs(point.x - startPoint.x) + abs(point.y - startPoint.y) > 10)) {
				firstRbuttonDown = false;
				endPoint.x = point.x;
				endPoint.y = point.y;
				Invalidate(FALSE);
			}
		}
		else {
			startPoint = endPoint;
			if ((abs(point.x - startPoint.x) + abs(point.y - startPoint.y) > 10)) {
				endPoint.x = point.x;
				endPoint.y = point.y;
				Invalidate(FALSE);
			}
		}
	}
	else {
		endPoint = startPoint;
	}
	CView::OnMouseMove(nFlags, point);
}


void CMinCadView::OnSphere()
{
	// TODO: 在此添加命令处理程序代码
	this->drawSphere ? this->drawSphere = false : this->drawSphere =true;
	drawCube = false;
	drawSpherHide = false;
	Invalidate(FALSE);
}

void CMinCadView::drawIDCCube()
{
	this->drawCube ? this->drawCube = false : this->drawCube = true;
	drawSphere = false;
	drawSpherHide = false;
	Invalidate(FALSE);
}


void CMinCadView::OnSpherehide()
{
	// TODO: 在此添加命令处理程序代码
	this->drawSpherHide ? this->drawSpherHide = false : this->drawSpherHide = true;
	drawSphere = false;
	drawCube = false;
	Invalidate(FALSE);
}
