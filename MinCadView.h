
// MinCadView.h: CMinCadView 类的接口
//

#pragma once
#include "CPoint2D.h"
#include "CCamera.h"
#include "CSphere.h"

class CMinCadView : public CView
{

public:
	bool testAxisCal;
	CCamera acube;
	bool firstRbuttonDown;
	CPoint2D startPoint;
	CPoint2D endPoint;
	bool rButtonDown;
	bool drawSpherHide;

	bool drawCube;
	bool drawSphere;
	void drawIDCCube();

protected: // 仅从序列化创建
	CMinCadView() noexcept;
	DECLARE_DYNCREATE(CMinCadView)

// 特性
public:
	CMinCadDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMinCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// //双缓冲就是，有两款内存区域，交互着使用，防止屏幕画图时闪烁
	void DoubleBuffer(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSphere();
	afx_msg void OnSpherehide();
};

#ifndef _DEBUG  // MinCadView.cpp 中的调试版本
inline CMinCadDoc* CMinCadView::GetDocument() const
   { return reinterpret_cast<CMinCadDoc*>(m_pDocument); }
#endif

