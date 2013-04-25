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
#include "MhDefParts.h"
#include "MsBasic.h"
#include "MtMCadApi.h"
#include "MhGp.h"
#include "MhPartsSpec.h"
#include "MhInpAttr.h"
#include "MnInpAttr.h"
#include "MmCmdMsg.h"
#include "MgLine.h"
#include "MmLib.h"
#include "MhLib.h"
#include "MnInpAttr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void	MmMainFrame( CMainFrame *pMainFrame);

//S CMainFrame *z_pMainFrame;										// メインフレームポインタ(Global) 

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(IDC_CMBK_BZI1, &CMainFrame::OnCbnSelchangeCombo1)
	ON_COMMAND(IDC_CMBK_BZI2, &CMainFrame::OnCbnSelchangeCombo2)
	ON_COMMAND(IDC_CMB_Inp1, &CMainFrame::OnCbnSelchangeCombo11)
	ON_COMMAND(IDC_CMB_Inp2, &CMainFrame::OnCbnSelchangeCombo12)
	ON_COMMAND(IDC_CMB_Inp3, &CMainFrame::OnCbnSelchangeCombo13)
	ON_COMMAND(IDC_COMBOPANELNO, &CMainFrame::OnCbnSelchangeComboPanelNo)
	ON_COMMAND(IDC_CMBK_ATTR1, &CMainFrame::OnCbnSelchangeComboAttr1)
	ON_COMMAND(IDC_CMBK_ATTR2, &CMainFrame::OnCbnSelchangeComboAttr2)
	ON_COMMAND(IDC_CMBK_ATTR3, &CMainFrame::OnCbnSelchangeComboAttr3)
	ON_COMMAND(IDC_CMBK_ATTR4, &CMainFrame::OnCbnSelchangeComboAttr4)
	ON_COMMAND(IDC_CMBK_ATTR5, &CMainFrame::OnCbnSelchangeComboAttr5)
	ON_COMMAND(IDC_CMBK_ATTR6, &CMainFrame::OnCbnSelchangeComboAttr6)
	ON_COMMAND_RANGE(IDC_RIBBON_A, IDC_RIBBON_Z, OnDummy)
	ON_COMMAND(IDC_VIEW1OPEN, &CMainFrame::OnView1open)
	ON_COMMAND(IDC_VIEW2OPEN, &CMainFrame::OnView2open)
	ON_COMMAND(IDC_VIEW3OPEN, &CMainFrame::OnView3open)
	ON_COMMAND(IDC_VIEW4OPEN, &CMainFrame::OnView4open)
	ON_COMMAND(IDC_VIEW5OPEN, &CMainFrame::OnView5open)

	ON_MESSAGE( WM_MYMESSAGERIBBONIO , OnRibbonIO)

	ON_WM_CLOSE()
END_MESSAGE_MAP()

// User Msg

LRESULT CMainFrame::OnRibbonIO( UINT wParam, LONG lParam)
{
	int ist = 0;

	switch( MC::z_mnIA.m_iComboTp)
	{
	case MSET_RIBBON_BAR:
		ist = MC::z_mnIA.SetRibbonBar( MC::z_mnIA.m_iRBKosei, MC::z_mnIA.m_iRBBunrui,
									   MC::z_mnIA.m_sRBBuhin, MC::z_mnIA.m_sRBMbr);
		break;
	case MSET_INPUT_KUBUN_CD:
		MC::z_mnIA.SelectComboInpKbnByInpKbnCd( MC::z_mnIA.m_iCdArg1);
		break;
	case MSET_INPUT_MARUME_CD:
		MC::z_mnIA.SelectComboMarumeByMarumeCd( MC::z_mnIA.m_iCdArg1);
		break;
	case MSET_COMBO_ATTRR:
		MC::z_mnIA.SetComboAttrR( MC_CMB_HAIZ, MC::z_mnIA.m_rCdArg2);
		break;
	case MGET_COMBO_ATTRA:
		MC::z_mnIA.GetComboAttrA();
		break;
	case MSET_COMBO_PARTS:
		MC::z_mnIA.InitComboParts();
		break;
	case MSET_COMBO_PANELNO:
		MC::z_mnIA.SetComboPanelNo( MC::z_mnIA.m_iCdArg1);
		break;
	case MINIT_COMBO_ATTR:
		MC::z_mnIA.InitComboAttr( MC::z_mnIA.m_iCdArg1);
		MC::z_mmIA.InitComboAttr( MC::z_mnIA.m_iCdArg1);
		break;
	}
//S	MC::z_mnIA.InitComboAttr( MP_AT_AUTO);						// 部材入力種類に合った属性入力コンボボックスを表示
	MC::z_mnIA.m_iSts = ist;
	return 0;
}

// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバー初期化コードをここに追加してください。
	z_MCadApp.m_nAppLook = z_MCadApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

	z_MCadApp.m_pMainFrame = this;

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
	OnApplicationLook(z_MCadApp.m_nAppLook);

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
	//cs.x  = -GetSystemMetrics( SM_CXSIZEFRAME);
	//cs.y  = -GetSystemMetrics( SM_CYSIZEFRAME);
	//cs.cx = GetSystemMetrics( SM_CXMAXIMIZED);
	//cs.cy = GetSystemMetrics( SM_CYMAXIMIZED);
	cs.x  = 0;
	cs.y  = 0;
	cs.cx = min( GetSystemMetrics( SM_CXMAXIMIZED), 1280);
	cs.cy = min( GetSystemMetrics( SM_CYMAXIMIZED), 1060);

	int i11 = ::GetSystemMetrics( SM_CXBORDER);				// 1
	int i12 = ::GetSystemMetrics( SM_CYBORDER);				// 1
	int i13 = ::GetSystemMetrics( SM_CXEDGE);				// 2
	int i14 = ::GetSystemMetrics( SM_CYEDGE);				// 2
	int i15 = ::GetSystemMetrics( SM_CXFIXEDFRAME);			// 3
	int i16 = ::GetSystemMetrics( SM_CYFIXEDFRAME);			// 3
	int i17 = ::GetSystemMetrics( SM_CXFULLSCREEN);			// 1280
	int i18 = ::GetSystemMetrics( SM_CYFULLSCREEN);			// 968
	int i19 = ::GetSystemMetrics( SM_CXMAXIMIZED);			// 1288
	int i20 = ::GetSystemMetrics( SM_CYMAXIMIZED);			// 1002
	int i21 = ::GetSystemMetrics( SM_CXMAXTRACK);			// 1292
	int i22 = ::GetSystemMetrics( SM_CYMAXTRACK);			// 1036
	int i23 = ::GetSystemMetrics( SM_CXSCREEN);				// 1280
	int i24 = ::GetSystemMetrics( SM_CYSCREEN);				// 1024
	int i25 = ::GetSystemMetrics( SM_CXSIZEFRAME);			// 4
	int i26 = ::GetSystemMetrics( SM_CYSIZEFRAME);			// 4
	int i27 = ::GetSystemMetrics( SM_CYMENU);				// 20
	int i28 = ::GetSystemMetrics( SM_CYCAPTION);			// 26
	int i29 = ::GetSystemMetrics( SM_CYSMCAPTION);			// 18

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

	z_MCadApp.m_nAppLook = id;

	switch (z_MCadApp.m_nAppLook)
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
		switch (z_MCadApp.m_nAppLook)
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

	z_MCadApp.WriteInt(_T("ApplicationLook"), z_MCadApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(z_MCadApp.m_nAppLook == pCmdUI->m_nID);
}

CMDIChildWnd* CMainFrame::OpenView(CDocTemplate *pTemplate)
{
	CDocument* pDoc = MDIGetActive()->GetActiveDocument();
	CMDIChildWnd* pNewFrame = (CMDIChildWnd*)pTemplate->CreateNewFrame(pDoc, NULL);
	if( pNewFrame )
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
	return pNewFrame;
}

// PARTS リボンバー　部材名

void CMainFrame::SelectCombo1( MINT i_iCombo1)
{
	m_iCombo1 = i_iCombo1;
//U	((CComboBox*)(m_wndDlgBar3.GetDlgItem(IDC_CMBK_BZI1)))->SetCurSel( m_iCombo1);
	CMFCRibbonComboBox* pComboBuzai = mmpComboBuzai();
	pComboBuzai->SelectItem( i_iCombo1);
}

void CMainFrame::SelectCombo2( MINT i_iCombo2)
{
	m_iCombo2 = i_iCombo2;
//U	((CComboBox*)(m_wndDlgBar3.GetDlgItem(IDC_CMBK_BZI2)))->SetCurSel( m_iCombo2);
	CMFCRibbonComboBox* pComboMbr = mmpComboMbr();
	pComboMbr->SelectItem( i_iCombo2);
}


void CMainFrame::SelectComboInp1( MINT i_iCombo11)
{
	m_iComboInp1 = i_iCombo11;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp1)))->SetCurSel( m_iComboInp1);
	CMFCRibbonComboBox* pComboInpTp = mmpComboInpTp();
	pComboInpTp->SelectItem( i_iCombo11);
}

void CMainFrame::SelectComboInp2( MINT iCombo12)
{
	m_iComboInp2 = iCombo12;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp2)))->SetCurSel( m_iComboInp2);
}

void CMainFrame::SelectComboInp3( MINT iCombo13)
{
	m_iComboInp3 = iCombo13;
//U	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( m_iComboInp3);
}


//-------------------------------------------------------

void CMainFrame::OnDummy(UINT /*id*/)
{
}

// PARTS リボンバー　部材名
void CMainFrame::OnCbnSelchangeCombo1()
{
//E	m_iCombo1 = ((CComboBox*)(m_wndDlgBar3.GetDlgItem(IDC_CMBK_BZI1)))->GetCurSel();	// 部品ID
	CMFCRibbonComboBox* pCmbBox = mmpComboBuzai();
	m_iCombo1 = pCmbBox->GetCurSel();											// 部品ID

	MC::z_mmIA.SelectComboPartsNmByKmId( m_iCombo1);
	MC::z_mmIA.InitComboPartsMbr();

	MC::z_mnIA.SelectComboPartsNmByKmId( m_iCombo1);
	MC::z_mnIA.InitComboPartsMbr();

	MC::Window::CurWndFocus();
	MC::mhPartsSpec* pPartsSpec	= MC::BuzaiCode::MhGetpPartsSpec( MC::z_mnIA.GetCurPartsNmId());
	if ( pPartsSpec->GetPTCdBr() >= MP_BR_SENBUN || MC::z_mnIA.GetMode() == MP_MD_DELETE)
		MC::WindowCtrl::MmWndKCmdXqt( IDC_PARTSCREATE);							//	部材入力コマンド
	else 
		MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


// PARTS リボンバー　寸法型式
void CMainFrame::OnCbnSelchangeCombo2()
{
	MC::z_mmIA.MmDialogKAttrInp( this);

	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboMbr();
	m_iCombo2 = pCmbBox->GetCurSel();											// 寸法型式ID

	MC::z_mmIA.SelectComboPartsMbrByKmId( m_iCombo2);

	MC::z_mnIA.SelectComboPartsMbrByKmId( m_iCombo2);
	MC::Window::CurWndFocus();
	MC::WindowCtrl::MmWndKCmdXqt( IDC_PARTSCREATE);								//	部品入力
}

// INPUT リボンバー　入力点区分
void CMainFrame::OnCbnSelchangeCombo11()
{
	CMFCRibbonComboBox *pCmbBox;
	pCmbBox = mmpComboInpTp();
	m_iComboInp1 = pCmbBox->GetCurSel();
	MC::z_mnIA.SelectComboInpKbnByInpKbnCd( m_iComboInp1);
	MC::Window::CurWndFocus();
}

// INPUT リボンバー　丸めコード
void CMainFrame::OnCbnSelchangeCombo12()
{
	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboMarume();
	m_iComboInp2 = pCmbBox->GetCurSel();										// 丸めコード
	MC::z_mnIA.SelectComboMarumeByMarumeCd( m_iComboInp2);
	MC::Window::CurWndFocus();
}

//void CMainFrame::OnCbnSelchangeCombo13()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//}
// INPUT リボンバー　配置コード
void CMainFrame::OnCbnSelchangeCombo13()
{
	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboPlcCd();
	m_iComboInp3 = pCmbBox->GetCurSel();										// 配置コード
	MC::z_mnIA.SelectComboPlcCdByPlcCd( m_iComboInp3);
	MC::Window::CurWndFocus();
}

// PANEL リボンバー　パネル番号
void CMainFrame::OnCbnSelchangeComboPanelNo()
{
	int ic1 = 1;
}

// ATTR リボンバー　長さ補正値1
void CMainFrame::OnCbnSelchangeComboAttr1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

// ATTR リボンバー　長さ補正値2
void CMainFrame::OnCbnSelchangeComboAttr2()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

// ATTR リボンバー　材軸芯ずれ量
void CMainFrame::OnCbnSelchangeComboAttr3()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

// ATTR リボンバー　配置点ずれ量
void CMainFrame::OnCbnSelchangeComboAttr4()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

// ATTR リボンバー　取り付け高さ
void CMainFrame::OnCbnSelchangeComboAttr5()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
}

// ATTR リボンバー　開口部高さ(ROH)
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
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
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
	pChildWnd2 = OpenView( z_MCadApp.m_pDocTemplate2);
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
	pChildWnd3 = OpenView( z_MCadApp.m_pDocTemplate3);
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
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
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
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 5, pChildWnd1);
}
