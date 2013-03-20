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

// ChildFrm3.cpp : CChildFrame3 クラスの実装
//

#include "stdafx.h"
#include "MCad.h"

#include "ChildFrm3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame3

IMPLEMENT_DYNCREATE(CChildFrame3, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame3, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame3::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame3::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame3::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame3::OnUpdateFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame3 コンストラクション/デストラクション

CChildFrame3::CChildFrame3()
{
	// TODO: メンバー初期化コードをここに追加してください。
}

CChildFrame3::~CChildFrame3()
{
}


BOOL CChildFrame3::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame3 診断

#ifdef _DEBUG
void CChildFrame3::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame3::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame3 メッセージ ハンドラー

void CChildFrame3::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame3::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 印刷プレビュー モードを強制的に終了する
	}
}

void CChildFrame3::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

BOOL CChildFrame3::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect ,
						  CMDIFrameWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

int CChildFrame3::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ここに特定な作成コードを追加してください。

	return 0;
}
