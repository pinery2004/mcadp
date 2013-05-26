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

// MCadView1.cpp : CMCadView1 クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MCad.h"
#endif

#include "MCadDoc.h"
#include "MCadView1.h"

#include "MmWnd.h"

#include "MhDefParts.h"
#include "MmLib.h"

#include "MmCmd.h"
#include "resource.h"

#include "MsBitSet.h"

#include "MmCmdMsg.h"
#include "MrCmd.h"

#include "MmInp.h"
#include "MmDialogKAttr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CPoint			z_ptCurCursorD;							// 現在カーソル移動位置(表示座標)

// CMCadView1

IMPLEMENT_DYNCREATE(CMCadView1, CView)

BEGIN_MESSAGE_MAP(CMCadView1, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCadView1::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SHOWWINDOW()
    ON_MESSAGE(WM_MYMESSAGEPARTSEDIT, OnMyMessagePtsEdit)			// 1
    ON_MESSAGE(WM_MYMESSAGEGRIDNUM, OnMyMessageGridNum)				// 1
    ON_MESSAGE(WM_MYMESSAGESTATUSBAR, OnMyMessageStatusBar)			// 1
    ON_MESSAGE(WM_MYMESSAGEOPTION, OnMyMessageOpt)					// 1
    ON_MESSAGE(WM_MYMESSAGEHIST, OnMyMessageHist)					// 1
	ON_MESSAGE(WM_MYMESSAGETENKAI, OnMyMessageTenkai)				// 1
	ON_MESSAGE(WM_MYMESSAGEKATTR, OnMyMessageKAttr)					// 1
	
END_MESSAGE_MAP()

// CMCadView1 コンストラクション/デストラクション

CMCadView1::CMCadView1()
{
	// TODO: 構築コードをここに追加します。

}

CMCadView1::~CMCadView1()
{
}

BOOL CMCadView1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	if (!CView::PreCreateWindow(cs))
		return false;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER | WS_MAXIMIZE;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		NULL,reinterpret_cast<HBRUSH>(COLOR_WINDOW+1),NULL); 

	MC::WindowCtrl::SetCurWnd( 1, this);
	MINT ist = MC::WindowCtrl::AddCurWnd();
	_ASSERTE(ist == 0);
	return TRUE;
}

void CMCadView1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::GetWndInfoObWnd( this);

	pWndInfo->GetFrame()->SetWindowText( Mstr( "WINDOW_01"));			// ウィンドウタイトル表示

	// クロスヘアーカーソルの初期化
	MC::Window::InitCrossHair();
	// ドラッギングの初期化
	MC::Window::InitDragging();
	// 部材ヒット表示の初期化
	MC::Window::InitHitBuzai();

	//	マップモードを設定
	MINT iOldMM = pWndInfo->SetMapMode( NULL);

	// メモリーＤＣの内容を画面に表示
	MC::WindowCtrl::DrawWnd( pWndInfo);

	// クロスヘアーカーソル表示
	MC::Window::ReDrawCrossHair();

	//	ラバーバンド図形を再表示する
	MC::Window::ReDrawDragging();
	
	//	ヒット部材を再表示する
	MC::Window::ReDrawHitBzi();
	
	//	マップモードを戻す
	pWndInfo->m_pMemDC->SetMapMode( iOldMM);
	// 描画メッセージで CView::OnPaint() を呼び出さないでください。
}

// CMCadView1 描画

void CMCadView1::OnDraw(CDC* /*pDC*/)
{
	CMCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


void CMCadView1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::LButtonDown( this, nFlags, point);

	CView::OnLButtonDown(nFlags, point);
}

void CMCadView1::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::LButtonUp( this, nFlags, point);

	CView::OnLButtonUp(nFlags, point);
}

void CMCadView1::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::RButtonDown( this, nFlags, point);

	CView::OnRButtonDown(nFlags, point);
}

void CMCadView1::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::RButtonUp( this, nFlags, point);

	CView::OnRButtonUp(nFlags, point);
}

void CMCadView1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	z_ptCurCursorD = point;
	
	MC::ViewInp::MouseMove( this, nFlags,  point);

	CView::OnMouseMove(nFlags, point);
}


void CMCadView1::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::MButtonDown( this, nFlags, point);

	CView::OnMButtonDown(nFlags, point);
}


void CMCadView1::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::MButtonUp( this, nFlags, point);

	CView::OnMButtonUp(nFlags, point);
}


BOOL CMCadView1::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::MouseWheel( this, nFlags, zDelta, z_ptCurCursorD);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMCadView1::OnSize(UINT nType, int cx, int cy)
{
	MINT	iMM_sv;
	CView::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラー コードを追加します。

	if (cx > 0 && cy > 0) {
		CPoint	ptMouthD( cx, cy);							// 画面サイズ(表示座標)
		CPoint	ptMouthL = ptMouthD;

		CClientDC dc( this);

		iMM_sv = dc.SetMapMode( MMAPMODE);
		dc.DPtoLP( &ptMouthL);								// 画面サイズ(論理座標)
		dc.SetMapMode( iMM_sv);

		MC::ViewInp::Size( this, ptMouthD, ptMouthL);		// ウィンドウサイズ設定
	}
}

LRESULT CMCadView1::OnMyMessageStatusBar(WPARAM wParam, LPARAM lParam)
{
	MC::Msg::DispStatusBar();
	return 0;
}	

LRESULT CMCadView1::OnMyMessagePtsEdit(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdPartsEditInp( this);
	return 0;
}	


LRESULT CMCadView1::OnMyMessageGridNum(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdGridNumInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageOpt(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdOptInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageHist(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdHistInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageTenkai(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdTenkaiInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageKAttr(WPARAM wParam, LPARAM lParam)
{
	MC::z_mmIA.MmDialogKAttrDisp( this);
	return 0;
}	

// CMCadView1 印刷


void CMCadView1::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCadView1::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMCadView1::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMCadView1::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

//void CMCadView1::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CMCadView1::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	z_MCadApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMCadView1 診断

#ifdef _DEBUG
void CMCadView1::AssertValid() const
{
	CView::AssertValid();
}

void CMCadView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCadDoc* CMCadView1::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCadDoc)));
	return (CMCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCadView1 メッセージ ハンドラー


BOOL CMCadView1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::Window::SetCursor( this);

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CMCadView1::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


void CMCadView1::OnCancelMode()
{
	CView::OnCancelMode();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


void CMCadView1::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	z_MCadApp.m_pMainFrame->m_pCurView = this;
}


int CMCadView1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ここに特定な作成コードを追加してください。

	return 0;
}


void CMCadView1::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CView::OnClose();
}


void CMCadView1::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::Char( this, nChar, nRepCnt, nFlags);

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMCadView1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::KeyDown( this, nChar, nRepCnt, nFlags);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMCadView1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::ViewInp::KeyUp( this, nChar, nRepCnt, nFlags);

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


int CMCadView1::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	SetFocus();

	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CMCadView1::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CView::OnShowWindow(bShow, nStatus);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}
