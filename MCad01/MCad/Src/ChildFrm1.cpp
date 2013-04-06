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

// ChildFrm1.cpp : CChildFrame1 クラスの実装
//

#include "stdafx.h"
#include "MCad.h"
#include "MmWnd.h"

#include "MCadDoc.h"
#include "MCadView1.h"
#include "ChildFrm1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame1

IMPLEMENT_DYNCREATE(CChildFrame1, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame1, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame1::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame1::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame1::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame1::OnUpdateFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CChildFrame1 コンストラクション/デストラクション

CChildFrame1::CChildFrame1()
{
	// TODO: メンバー初期化コードをここに追加してください。
}

CChildFrame1::~CChildFrame1()
{
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::~CChildFrame1(%x)\n", this);
#endif
}


BOOL CChildFrame1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::PreCreateWindow(%x)\n", this);
#endif

	cs.x  = 0;									//- GetSystemMetrics(SM_CXSIZEFRAME);
	cs.y  = 0;									//- GetSystemMetrics(SM_CXSIZEFRAME);

	int	iCXMAXIMIZED =	GetSystemMetrics(SM_CXMAXIMIZED);	//1936
	int	iCXSIZEFRAME =	GetSystemMetrics(SM_CXSIZEFRAME);	// 8
	int	iCXEDGE =		GetSystemMetrics(SM_CXEDGE);		// 2
	int	iCYMAXIMIZED =	GetSystemMetrics(SM_CYMAXIMIZED);	// 1096
	int	iCYMENU =		GetSystemMetrics(SM_CYMENU);		// 21
	int	iCYCAPTION =	GetSystemMetrics(SM_CYCAPTION);		// 22
	int	iCYSIZEFRAME =	GetSystemMetrics(SM_CYSIZEFRAME);	// 8

	cs.cx = min( iCXMAXIMIZED, 1280) - 
				 iCYMENU/* 20 */ -
				 iCXSIZEFRAME/* 4 */ * 4;
	cs.cy = min( iCYMAXIMIZED, 1060) -
				 ( iCYMENU/* 20 */ + iCXEDGE/* 2 */) * 5 -
				 iCYCAPTION/* 26 */ * 1 -
				 iCYSIZEFRAME/* 4 */ * 4 + iCXEDGE/* 2 */ * 3;


	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

// CChildFrame1 診断

#ifdef _DEBUG
void CChildFrame1::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame1::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame1 メッセージ ハンドラー

void CChildFrame1::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame1::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 印刷プレビュー モードを強制的に終了する
	}
}

void CChildFrame1::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

BOOL CChildFrame1::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect ,
						  CMDIFrameWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	MC::WindowCtrl::MmWndSetFrameC( 1, this);

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

int CChildFrame1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ここに特定な作成コードを追加してください。
//E	// フレームのクライアント領域全体を占めるビューを作成します。
//	if (!m_wndView1.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
//	{
//		TRACE0("ビュー ウィンドウを作成できませんでした。\n");
//		return -1;
//	}

	return 0;
}

void CChildFrame1::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindFrm( this);
	MC::WindowCtrl::MmWndKDelete( pWndInfo);

	CMDIChildWndEx::OnClose();
}

void CChildFrame1::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWndEx::OnSetFocus(pOldWnd);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::OnSetFocus(%x)\n", this);
#endif
	CMDIChildWnd::OnSetFocus(pOldWnd);

	ms_pMainFrame->m_pCurFrame = this;

//	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();

//E	m_wndView1.SetFocus();
}
