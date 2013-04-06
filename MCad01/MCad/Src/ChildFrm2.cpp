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

// ChildFrm2.cpp : CChildFrame2 クラスの実装
//

#include "stdafx.h"
#include "MCad.h"
#include "MmWnd.h"
#include "M3View.h"
#include "MCadDoc.h"
#include "MCadView2.h"
#include "ChildFrm2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame2

IMPLEMENT_DYNCREATE(CChildFrame2, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame2, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame2::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame2::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame2::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame2::OnUpdateFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_CLOSE, &CChildFrame2::OnFileClose)
END_MESSAGE_MAP()

// CChildFrame2 コンストラクション/デストラクション

CChildFrame2::CChildFrame2()
{
}

CChildFrame2::~CChildFrame2()
{
}


BOOL CChildFrame2::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	// ディスプレイ画面サイズの取得
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	HDC hdc = ::GetDC( NULL);
	int Width = GetDeviceCaps(hdc, HORZRES);
	int Height = GetDeviceCaps(hdc, VERTRES);

	::ReleaseDC(NULL, hdc);

	// 表示ウィンドウサイズの設定
	if ( Width >= 0x500) {
		cs.x = 500; cs.cx = 700;					// 実行直後のウィンドウのサイズ 1280x??? 
	} else {
		cs.x = 200; cs.cx = 580; 					// 実行直後のウィンドウのサイズ 1024x???
	}
	if ( Height >= 0x400) {
		cs.y = 0;	cs.cy = 700;					// 実行直後のウィンドウのサイズ ????x1024
	} else {
		cs.y = 0;	cs.cy = 580;					// 実行直後のウィンドウのサイズ ????x768
	}

	return TRUE;
}

// CChildFrame2 診断

#ifdef _DEBUG
void CChildFrame2::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame2::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame2 メッセージ ハンドラー

void CChildFrame2::OnFileClose()
{
	// このフレームを閉じるには、WM_CLOSE を送ります。このメッセージは、
	// システム メニューの [閉じる] を選択した場合と同じです。
	SendMessage(WM_CLOSE);
}

int CChildFrame2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)							// view2 Create
		return -1;

//E	// フレームのクライアント領域全体を占めるビューを作成します。
//	if (!m_wndView2.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,						// 
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
//	{
//		TRACE0("ビュー ウィンドウを作成できませんでした。\n");
//		return -1;
//	}

	return 0;
}

void CChildFrame2::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWndEx::OnSetFocus(pOldWnd);

//E	m_wndView2.SetFocus();
}

void CChildFrame2::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame2::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 印刷プレビュー モードを強制的に終了する
	}
}

void CChildFrame2::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

BOOL CChildFrame2::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect ,
						  CMDIFrameWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	MC::WindowCtrl::MmWndSetFrameC( 2, this);

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

void CChildFrame2::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindFrm( this);
	MC::WindowCtrl::MmWndKDelete( pWndInfo);

	CMDIChildWndEx::OnClose();
}
