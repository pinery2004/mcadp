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

// MCadView2.cpp : CMCadView2 クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MCad.h"
#endif
#include "M3View.h"
#include "MCadDoc.h"
#include "MCadView2.h"
#include "MmWnd.h"

namespace MC
{
void ShowError( int e);
} // namespace MC

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCadView2

IMPLEMENT_DYNCREATE(CMCadView2, CView)

BEGIN_MESSAGE_MAP(CMCadView2, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCadView2::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMCadView2 コンストラクション/デストラクション

CMCadView2::CMCadView2()
{
}

CMCadView2::~CMCadView2()
{
}

BOOL CMCadView2::PreCreateWindow(CREATESTRUCT& cs)
{
	MINT	ist;
//E	if ( !CWnd::PreCreateWindow( cs))
//E		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor( NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);


	MC::WindowCtrl::MmWndSetWndC( 2, this);										// ウィンドウ管理
	ist = MC::WindowCtrl::MmWndKAddC();											// ウィンドウ管理
	_ASSERTE( ist == 0);														// ウィンドウ管理

//E	return TRUE;
	return CView::PreCreateWindow(cs);
}

void CMCadView2::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	SetWindowPos(&wndTopMost , 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE | SWP_NOZORDER);

//	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFind( this);					// ウィンドウ管理
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);	// ウィンドウ管理
	(pWndInfo->GetFrame())->SetWindowText(Mstr( "WINDOW_02"));	// ウィンドウ管理

	// 描画メッセージで CWnd::OnPaint() を呼び出さないでください。

#if( DEBUG1)
	MoGlLib::DrawGLobject();
	SwapBuffers( m_pDC->m_hDC);    // Double buffer
#else

	m_M3View.OnPaint();
	if( FALSE == SwapBuffers( m_pDC->GetSafeHdc())) MC::ShowError(7);	// Orig
//	SwapBuffers( m_pDC->m_hDC);    // Double buffer
#endif
}


BOOL CMCadView2::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CMCadView2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MC::MgPoint3D	PtCtr;						// 中心座標

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//	DCの生成
	m_pDC = new CClientDC( this);
	if( NULL == m_pDC ){
		MC::ShowError( 1);
		return FALSE;
	}
	m_M3View.OnCreate( m_pDC->m_hDC);

#if( DEBUG1)
	MoGlLib::SetDCPixelFormat( m_pDC->m_hDC);					// OpenGL用にPixel Formatを指定
	m_GLRC = wglCreateContext( m_pDC->m_hDC);					// Rendering contextの生成
	wglMakeCurrent( m_pDC->m_hDC, m_GLRC);						// 現在のcontext設定

	MoGlLib::InitializeOpenGL();								//3Dシーンを初期化する関数を用意する
	MoGlLib::MakeGLObject();									//3Dオブジェクトを生成する
#endif

	return 0;
}

void CMCadView2::OnDestroy()
{
	CView::OnDestroy();

	m_M3View.OnDestroy();

	if( m_pDC ) delete m_pDC;
}


BOOL CMCadView2::OnEraseBkgnd(CDC* pDC)
{
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CMCadView2::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

#if( DEBUG1)
	MoGlLib::ViewSetting(cx, cy);
#endif

	m_M3View.OnSize( nType, cx, cy);
}


void CMCadView2::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_iPtLast = point;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMCadView2::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CMCadView2::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint	iPtD;												// マウス移動量	
	CRect	iRcWin;												// ウィンドウ領域 (描画領域)
	CPoint	iSzWin;												// ウィンドウの幅と高さ
	MC::MgVect3D	PtD( 0., 0., 0.);
	MC::MgVect3D	RtD( 0., 0., 0.);
	MREAL	SclD = 0.;

	if (!(nFlags & MK_LBUTTON) && !( nFlags & MK_RBUTTON))
		MQUIT;													// マウスの左または右ボタンが押されていない場合は無視

	GetClientRect( iRcWin);
	
	iPtD.x = ( point.x - m_iPtLast.x) * 2;						// マウス移動量	
	iPtD.y = (LONG)MMDIRY * ( m_iPtLast.y - point.y) * 2;		// Yは上が正方向である(例: 1024:上 ～　0:下)

	if ( ( MGABS( iPtD.x) < 5) && ( MGABS( iPtD.y) < 5)) 
		MQUIT;													// 判定移動量未満の場合は無視

	iSzWin = CPoint( iRcWin.right - iRcWin.left,
					 iRcWin.bottom - iRcWin.top);  

	//	Ctrl + Left Button:   左右移動、上下移動
	if ( nFlags & MK_CONTROL && nFlags & MK_LBUTTON) {
		PtD.x = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		PtD.y = (MREAL)iPtD.y / (MREAL)iSzWin.y;

	//	Ctrl + Right Button:   ____、前後移動
	} else if ( nFlags & MK_CONTROL && nFlags & MK_RBUTTON) {
		PtD.z = (MREAL)iPtD.y / (MREAL)iSzWin.y;

	//	Left Button:   Ｙ軸回転、Ｘ軸回転
	} else 	if ( nFlags & MK_LBUTTON) {
		RtD.x = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		RtD.y = (MREAL)iPtD.y / (MREAL)iSzWin.y;

		RtD.z = ((MREAL)iPtD.y * ((MREAL)point.x / (MREAL)iSzWin.x * 2 - 1) +		// 外側の方のＸ軸回転とＹ軸回転はＺ軸回転
				(MREAL)iPtD.x * ((MREAL)point.y / (MREAL)iSzWin.y * 2 -1)) /		// にも影響を及ぼす様にする
				(MREAL)iSzWin.x;;													// 下は (正方向:Ｚ軸に対して右回転)

	//	Right Button:   Ｚ回転、拡大縮小
	} else if ( nFlags & MK_RBUTTON) {
		RtD.z = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		SclD  = (MREAL)iPtD.y / (MREAL)iSzWin.y;

		if ( point.y < (iRcWin.top + iRcWin.bottom)/2)								// Ｚ軸回転角　画面中央より
			RtD.z = - RtD.z;														// 上は (正方向:Ｚ軸に対して左回転) で、
																					//			   (Ｚ軸から見て右回転)
																					// 下は (正方向:Ｚ軸に対して右回転)
																					//			   (Ｚ軸から見て左回転)
	}

	static bool bFirst = true;										// １度目はマウスの移動量が未定のためスキップ
	if ( !bFirst) {
		m_M3View.OnMouseMove( nFlags, PtD, RtD, SclD);				
	}
	bFirst = false;

	m_iPtLast = point;

	PostMessage(WM_PAINT);										// 再表示のメッセージを送り処理の終了を待たずに次へ移る
exit:
	CView::OnMouseMove(nFlags, point);
}


void CMCadView2::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_iPtLast = point;
	SetCapture();

	CView::OnRButtonDown(nFlags, point);
}

void CMCadView2::OnRButtonUp(UINT nFlags, CPoint point)
{
//E	ClientToScreen(&point);
//E	OnContextMenu(this, point);

	ReleaseCapture();

	CWnd::OnRButtonUp(nFlags, point);

}

void CMCadView2::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_M3View.m_iFWire++;
	if (m_M3View.m_iFWire >= 5 || (nFlags != 24 && m_M3View.m_iFWire >= 3))
		m_M3View.m_iFWire = 0;
	PostMessage(WM_PAINT);										// 再表示のメッセージを送り処理の終了を待たずに次へ移る

	CView::OnMButtonDown(nFlags, point);
}


void CMCadView2::OnMButtonUp(UINT nFlags, CPoint point)
{
	CView::OnMButtonUp(nFlags, point);
}

// CMCadView2 診断

#ifdef _DEBUG
void CMCadView2::AssertValid() const
{
	CView::AssertValid();
}

void CMCadView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCadDoc* CMCadView2::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCadDoc)));
	return (CMCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCadView2 メッセージ ハンドラー

void CMCadView2::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CView::OnClose();
}

// CMCadView2 描画

void CMCadView2::OnDraw(CDC* /*pDC*/)
{
	CMCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

// CMCadView2 印刷

void CMCadView2::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCadView2::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMCadView2::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMCadView2::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CMCadView2::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	z_MCadApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

