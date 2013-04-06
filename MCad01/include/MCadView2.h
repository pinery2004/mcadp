// この MFC サンプル ソース コードでは、MFC Microsoft Office Fluent ユーザー インターフェイス 
// ("Fluent UI") の使用方法を示します。このコードは、MFC C++ ライブラリ ソフトウェアに 
// 同梱されている Microsoft Foundation Class リファレンスおよび関連電子ドキュメントを
// 補完するための参考資料として提供されます。
// Fluent UI を複製、使用、または配布するためのライセンス条項は個別に用意されています。
// Fluent UI ライセンス プログラムの詳細については、Web サイト
// http://msdn.microsoft.com/ja-jp/office/aa973809.aspx を参照してください。
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MCadView2.h : CMCadView2 クラスのインターフェイス
//

#pragma once

class CMCadView2 : public CView
{
public:
	CMCadView2();
	virtual ~CMCadView2();
protected: // シリアル化からのみ作成します。
	DECLARE_DYNCREATE(CMCadView2)

// 属性
public:
	CMCadDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:
//    BOOL RenderScene( void );
private:
//    BOOL SetDCPixelFormat( HDC hdc);
//    BOOL InitializeOpenGL( void);
//    void ShowError(int e);

    CDC*	m_pDC;
	HGLRC   m_GLRC  ;   // OpenGL Rendering Context

	CPoint	m_iPtLast;											// 最終指示座標

	MC::M3View	m_M3View;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // MCadView2.cpp のデバッグ バージョン
inline CMCadDoc* CMCadView2::GetDocument() const
   { return reinterpret_cast<CMCadDoc*>(m_pDocument); }
#endif

