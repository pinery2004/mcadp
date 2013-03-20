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

// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "MCad.h"
#include "MsDefMCad.h"

#include "MCad.h"

#include "MainFrm.h"
#include "MmWnd.h"
#include "MsBasic.h"
#include "MtMCadApi.h"
#include "MtInpAttr.h"
#include "MgLine.h"
#include "MmLib.h"
#include "MhLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void	MmMainFrame( CMainFrame *pMainFrame);

CMainFrame *ms_pMainFrame;										// メインフレームポインタ(Global) 

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(IDC_CMB_BZI1, &CMainFrame::OnCbnSelchangeCombo1)
	ON_COMMAND(IDC_CMB_BZI2, &CMainFrame::OnCbnSelchangeCombo2)
	ON_COMMAND(IDC_CMB_Inp1, &CMainFrame::OnCbnSelchangeCombo11)
	ON_COMMAND(IDC_CMB_Inp2, &CMainFrame::OnCbnSelchangeCombo12)
	ON_COMMAND(IDC_CMB_Inp3, &CMainFrame::OnCbnSelchangeCombo13)
	ON_COMMAND(IDC_COMBOPANELNO, &CMainFrame::OnCbnSelchangeComboPanelNo)
	ON_COMMAND(IDC_CMB_ATTR1, &CMainFrame::OnCbnSelchangeComboAttr1)
	ON_COMMAND(IDC_CMB_ATTR2, &CMainFrame::OnCbnSelchangeComboAttr2)
	ON_COMMAND(IDC_CMB_ATTR3, &CMainFrame::OnCbnSelchangeComboAttr3)
	ON_COMMAND(IDC_CMB_ATTR4, &CMainFrame::OnCbnSelchangeComboAttr4)
	ON_COMMAND(IDC_CMB_ATTR5, &CMainFrame::OnCbnSelchangeComboAttr5)
	ON_COMMAND(IDC_CMB_ATTR6, &CMainFrame::OnCbnSelchangeComboAttr6)
	ON_COMMAND_RANGE(IDC_RIBBON_A, IDC_RIBBON_Z, OnDummy)
	ON_COMMAND(IDC_VIEW1OPEN, &CMainFrame::OnView1open)
	ON_COMMAND(IDC_VIEW2OPEN, &CMainFrame::OnView2open)
	ON_COMMAND(IDC_VIEW3OPEN, &CMainFrame::OnView3open)
	ON_COMMAND(IDC_VIEW4OPEN, &CMainFrame::OnView4open)
	ON_COMMAND(IDC_VIEW5OPEN, &CMainFrame::OnView5open)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバー初期化コードをここに追加してください。
	g_theApp.m_nAppLook = g_theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

	ms_pMainFrame = this;
	MC::System::SetpMainFrame( this);

//	MtInit( GetSafeHwnd(), 1);
	MC::MtCmdOpen();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 固定値に基づいてビジュアル マネージャーと visual スタイルを設定します
	OnApplicationLook(g_theApp.m_nAppLook);

	// タブ型式のウィンドウ表示
	if (TAB_WINDOW) {
		CMDITabInfo mdiTabParams;
		mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 使用可能なその他の視覚スタイル...
		mdiTabParams.m_bActiveTabCloseButton = TRUE;      // タブ領域の右部に [閉じる] ボタンを配置するには、FALSE に設定します
		mdiTabParams.m_bTabIcons = FALSE;    // MDI タブでドキュメント アイコンを有効にするには、TRUE に設定します
		mdiTabParams.m_bAutoColor = TRUE;    // MDI タブの自動色設定を無効にするには、FALSE に設定します
		mdiTabParams.m_bDocumentMenu = TRUE; // タブ領域の右端にあるドキュメント メニューを有効にします
		EnableMDITabbedGroups(TRUE, mdiTabParams);
	}

//	m_wndRibbonBar.Create(this);
//	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("ステータス バーの作成に失敗しました。\n");
		return -1;      // 作成できない場合
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 スタイルのドッキング ウィンドウ動作を有効にします
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 スタイルのドッキング ウィンドウの自動非表示動作を有効にします
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 拡張ウィンドウ管理ダイアログ ボックスを有効にします
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ウィンドウ タイトル バーでドキュメント名とアプリケーション名の順序を切り替えます。これにより、
	// ドキュメント名をサムネイルで表示できるため、タスク バーの使用性が向上します。
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

void CMainFrame::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MINT	ist1;
	if (MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( Mstr( "終了しますか"), Mstr( "終了確認"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}
	MC::MtCmdClose();
	MC::WindowCtrl::MmWndKDeleteAll();

	CMDIFrameWndEx::OnClose();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return TRUE;
}

// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize (CSize (16, 16));
	m_PanelImages.Load (IDR_RIBBON);

	return m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
}

// CMainFrame メッセージ ハンドラー

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	g_theApp.m_nAppLook = id;

	switch (g_theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (g_theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	g_theApp.WriteInt(_T("ApplicationLook"), g_theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(g_theApp.m_nAppLook == pCmdUI->m_nID);
}

CMDIChildWnd* CMainFrame::OpenView(CDocTemplate *pTemplate)
{
	CDocument* pDoc = MDIGetActive()->GetActiveDocument();
	CMDIChildWnd* pNewFrame = (CMDIChildWnd*)pTemplate->CreateNewFrame(pDoc, NULL);
	if( pNewFrame )
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
	return pNewFrame;
}

// PARTS ダイアログバー　部材名

void CMainFrame::SetCombo1( MINT iCombo1)
{
	m_iCombo1 = iCombo1;
//U	((CComboBox*)(m_wndDlgBar3.GetDlgItem(IDC_CMB_BZI1)))->SetCurSel( m_iCombo1);
}

void CMainFrame::SetCombo2( MINT iCombo2)
{
	m_iCombo2 = iCombo2;
//U	((CComboBox*)(m_wndDlgBar3.GetDlgItem(IDC_CMB_BZI2)))->SetCurSel( m_iCombo2);
}


void CMainFrame::SetComboInp1( MINT iCombo11)
{
	m_iComboInp1 = iCombo11;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp1)))->SetCurSel( m_iComboInp1);
}

void CMainFrame::SetComboInp2( MINT iCombo12)
{
	m_iComboInp2 = iCombo12;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp2)))->SetCurSel( m_iComboInp2);
}

void CMainFrame::SetComboInp3( MINT iCombo13)
{
	m_iComboInp3 = iCombo13;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( m_iComboInp3);
}


//-------------------------------------------------------

void CMainFrame::OnDummy(UINT /*id*/)
{
}

void CMainFrame::OnCbnSelchangeCombo1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo2()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo11()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_iComboInp1 = ((CComboBox*)(m_wndRibbonBar.GetDlgItem(IDC_CMB_Inp1)))->GetCurSel();
	MC::mtInpMode::SetComboInpKb( m_iComboInp1);
	MC::Window::CurWndFocus();
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo12()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo13()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboPanelNo()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeComboAttr1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboAttr2()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboAttr3()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboAttr4()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboAttr5()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CMainFrame::OnCbnSelchangeComboAttr6()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

void CMainFrame::OnView1open()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
//S	CChildFrame1 *pChildFrm1 = new CChildFrame1;
//	TRACE( "new CChildFrame1(%x)\n", pChildFrm1);
//	MC::WindowCtrl::MmWndSetFrameC( 1, pChildFrm1);
//	if (!pChildFrm1->Create( NULL, _T("Window1"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 1, pChildWnd1);
}


void CMainFrame::OnView2open()
{
//S	// TODO: ここにコマンド ハンドラー コードを追加します。
//	CChildFrame2 *pChildFrm2 = new CChildFrame2;
//	MC::WindowCtrl::MmWndSetFrameC( 2, pChildFrm2);
//	if (!pChildFrm2->Create( NULL, _T("Window2"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd2;
	pChildWnd2 = OpenView( g_theApp.m_pDocTemplate2);
	MC::WindowCtrl::MmWndSetFrameC( 2, pChildWnd2);
}


void CMainFrame::OnView3open()
{
//S	// TODO: ここにコマンド ハンドラー コードを追加します。
//	CChildFrame3 *pChildFrm3 = new CChildFrame3;
//	MC::WindowCtrl::MmWndSetFrameC( 3, pChildFrm3);
//	if (!pChildFrm3->Create( NULL, _T("Window3"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd3;
	pChildWnd3 = OpenView( g_theApp.m_pDocTemplate3);
	MC::WindowCtrl::MmWndSetFrameC( 3, pChildWnd3);
}


void CMainFrame::OnView4open()
{
//S	// TODO: ここにコマンド ハンドラー コードを追加します。
//	CChildFrame4 *pChildFrm4 = new CChildFrame4;
//	MC::WindowCtrl::MmWndSetFrameC( 4, pChildFrm4);
//	if (!pChildFrm4->Create( NULL, _T("Window4"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 4, pChildWnd1);
}


void CMainFrame::OnView5open()
{
//S	// TODO: ここにコマンド ハンドラー コードを追加します。
//	CChildFrame5 *pChildFrm5 = new CChildFrame5;
//	MC::WindowCtrl::MmWndSetFrameC( 5, pChildFrm5);
//	if (!pChildFrm5->Create( NULL, _T("Window5"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 5, pChildWnd1);
}
