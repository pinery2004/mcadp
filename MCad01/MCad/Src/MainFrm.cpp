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
#include "MnIoPartsAttr.h"
#include "MmCmdMsg.h"
#include "MgLine.h"
#include "MmLib.h"
#include "MhLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void	MmMainFrame( CMainFrame *pMainFrame);

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(IDC_CMBK_BZI1, &CMainFrame::OnCbnSelchangeComboPartsNm)
	ON_COMMAND(IDC_CMBK_BZI2, &CMainFrame::OnCbnSelchangeComboMbr)
	ON_COMMAND(IDC_CMB_Inp1, &CMainFrame::OnCbnSelchangeComboInpKbn)
	ON_COMMAND(IDC_CMB_Inp2, &CMainFrame::OnCbnSelchangeComboMarume)
	ON_COMMAND(IDC_CMB_Inp3, &CMainFrame::OnCbnSelchangeComboPlcIzon)
	ON_COMMAND(IDC_COMBOPANELNO, &CMainFrame::OnCbnSelchangeComboPanelNo)
	ON_COMMAND_RANGE(IDC_RIBBON_A, IDC_RIBBON_Z, OnDummy)
	ON_COMMAND(IDC_VIEW1OPEN, &CMainFrame::OnView1open)
	ON_COMMAND(IDC_VIEW2OPEN, &CMainFrame::OnView2open)
	ON_COMMAND(IDC_VIEW3OPEN, &CMainFrame::OnView3open)
	ON_COMMAND(IDC_VIEW4OPEN, &CMainFrame::OnView4open)
	ON_COMMAND(IDC_VIEW5OPEN, &CMainFrame::OnView5open)

	ON_MESSAGE(WM_MYMESSAGE_RIBBONIO , OnRibbonIO)
	ON_MESSAGE(WM_MYMESSAGE_RIBBONCATEGORYCHANGED , OnRibbonCategoryChanged)
	ON_MESSAGE(WM_MYMESSAGE_WINDOW, OnWindow)

	// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
	ON_MESSAGE(AFX_WM_ON_CHANGE_RIBBON_CATEGORY, &mnMFCRibbonBar::OnAfxWmOnChangeRibbonCategory)

	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
// User Msgで起動されるリボンIOのUI関数実行用ディスパッチャ

LRESULT CMainFrame::OnRibbonIO( UINT wParam, LONG lParam)
{
	int ist = 0;

	switch( MC::z_mnIA.m_iComboTp)
	{
	case MSET_RIBBON_BAR:
		// リボンバーの部品選択用項目を設定する( 組、分類、部品タイプ、寸法型式)
		ist = MC::z_mnIA.SetRibbonBarXqt( MC::z_mnIA.m_iRBKosei, MC::z_mnIA.m_iRBBunrui,
									   MC::z_mnIA.m_sRBBuhin, MC::z_mnIA.m_sRBMbr);
		break;

	case MSET_INPUT_KUBUN_CD:
		//	リボンバーの入力点区分コード選択用コンボボックスの入力点区分コードを選択する
		MC::z_mnIA.SelectComboInpKbnByInpKbnCdXqt( MC::z_mnIA.m_iCdArg1);
		break;

	case MSET_INPUT_MARUME_CD:
		//	リボンバーの丸めコード選択用コンボボックスの丸めコードを選択する
		MC::z_mnIA.SelectComboMarumeByMarumeCdXqt( MC::z_mnIA.m_iCdArg1);
		break;

	case MSET_INPUT_PLACE_CD:
		//	リボンバーの配置依存コード選択用コンボボックスの配置依存コードを選択する
		MC::z_mnIA.SelectComboPlcIzonCdByPlaceCdXqt( MC::z_mnIA.m_iCdArg1);
		break;

	case MSET_COMBO_ATTRR:
		MC::z_mmIA.SetComboAttrRXqt( (MCCMBATTR)MC::z_mnIA.m_iCdArg1, MC::z_mnIA.m_rCdArg2);
		break;

	case MGET_PARTS_ATTRA:
		//	部品仕様と寸法形式を部品配置入力データに取り込む
		MC::z_mnIA.GetPartsSpec();
		//	属性値入力用コンボボックスの値を取り込む
		MC::z_mmIA.GetComboAttrAXqt();
		break;

//S	case MSET_COMBO_PARTS:
//		MC::z_mnIA.InitComboPartsXqt();
//		break;
//
	case MSET_COMBO_PANELNO:
		MC::z_mnIA.SetComboPanelNoXqt( MC::z_mnIA.m_iCdArg1);
		break;

	case MINIT_COMBO_ATTR:
		MC::z_mmIA.InitComboAttrXqt( MC::z_mnIA.m_iCdArg1);
		break;
	}
	MC::z_mnIA.m_iSts = ist;
	return 0;
}

LRESULT CMainFrame::OnRibbonCategoryChanged( UINT wParam, LONG lParam)
{
	MC::z_mnIA.SetCurCategory( wParam - 1);
	if( wParam == 2) {
		int i1 = 2;
		// 意匠カテゴリ選択
		if( MC::z_mmIA.GetDispFlg()) {
			MC::z_mmIA.SendMessage(WM_CLOSE);
		}
	} else if( wParam == 3) {
		int i2 = 3;
		// 構造カテゴリ選択
		MC::z_mmIA.MmDialogKAttrDisp( this);						// 部材属性ダイアログ表示
		MC::z_mmIA.InitComboParts();								// 全項目設定
		MC::z_mmIA.SelectComboPartsNmByKmId(m_iComboPartsNm);		// 部品名を設定
		MC::z_mmIA.SelectComboMbrByKmId( m_iComboMbr);				// 寸法形式を設定
		MC::z_mnIA.SelectComboMbrByKmId( m_iComboMbr);
	}
	return 0;
}

LRESULT CMainFrame::OnWindow( UINT wParam, LONG lParam)
{
	int ist = 0;
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::GetWndInfoBySyu( 1, MTYUKAFUSEZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	z_MCadApp.CreateWnd( 1, MTYUKAFUSEZU, 1, 1);
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
	if ( TAB_WINDOW) {
		CMDITabInfo mdiTabParams;
		mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;	// 使用可能なその他の視覚スタイル...
		mdiTabParams.m_bActiveTabCloseButton = TRUE;			// タブ領域の右部に [閉じる] ボタンを配置するには、FALSE に設定します
		mdiTabParams.m_bTabIcons = FALSE;						// MDI タブでドキュメント アイコンを有効にするには、TRUE に設定します
		mdiTabParams.m_bAutoColor = TRUE;						// MDI タブの自動色設定を無効にするには、FALSE に設定します
		mdiTabParams.m_bDocumentMenu = TRUE;					// タブ領域の右端にあるドキュメント メニューを有効にします
		EnableMDITabbedGroups(TRUE, mdiTabParams);
	}

//	m_wndRibbonBar.Create(this);
//	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if ( !CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}

	if ( !m_wndStatusBar.Create(this))
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
	if ( MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( Mstr( "終了しますか"), Mstr( "終了確認"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}
	MC::MtCmdClose();
	MC::WindowCtrl::DeleteAllWnd();

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

	int i11 = ::GetSystemMetrics( SM_CXBORDER);					// 1
	int i12 = ::GetSystemMetrics( SM_CYBORDER);					// 1
	int i13 = ::GetSystemMetrics( SM_CXEDGE);					// 2
	int i14 = ::GetSystemMetrics( SM_CYEDGE);					// 2
	int i15 = ::GetSystemMetrics( SM_CXFIXEDFRAME);				// 3
	int i16 = ::GetSystemMetrics( SM_CYFIXEDFRAME);				// 3
	int i17 = ::GetSystemMetrics( SM_CXFULLSCREEN);				// 1920
	int i18 = ::GetSystemMetrics( SM_CYFULLSCREEN);				// 1058
	int i19 = ::GetSystemMetrics( SM_CXMAXIMIZED);				// 1936
	int i20 = ::GetSystemMetrics( SM_CYMAXIMIZED);				// 1096
	int i21 = ::GetSystemMetrics( SM_CXMAXTRACK);				// 3852
	int i22 = ::GetSystemMetrics( SM_CYMAXTRACK);				// 1092
	int i23 = ::GetSystemMetrics( SM_CXSCREEN);					// 1920
	int i24 = ::GetSystemMetrics( SM_CYSCREEN);					// 1080
	int i25 = ::GetSystemMetrics( SM_CXSIZEFRAME);				// 8
	int i26 = ::GetSystemMetrics( SM_CYSIZEFRAME);				// 8
	int i27 = ::GetSystemMetrics( SM_CYMENU);					// 21
	int i28 = ::GetSystemMetrics( SM_CYCAPTION);				// 22
	int i29 = ::GetSystemMetrics( SM_CYSMCAPTION);				// 21

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
	if ( !m_wndRibbonBar.Create(this))
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

	switch ( z_MCadApp.m_nAppLook)
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

void CMainFrame::SelectComboPartsNm( MINT i_iComboPartsNm)
{
	m_iComboPartsNm = i_iComboPartsNm;
	CMFCRibbonComboBox* pComboBuzai = mmpComboBuzai();
	pComboBuzai->SelectItem( i_iComboPartsNm);
}

void CMainFrame::SelectComboMbr( MINT i_iComboMbr)
{
	m_iComboMbr = i_iComboMbr;
	CMFCRibbonComboBox* pComboMbr = mmpComboMbr();
	pComboMbr->SelectItem( i_iComboMbr);
}

void CMainFrame::SelectComboInp1( MINT i_iComboInpKbn)
{
	m_iComboInpKbn = i_iComboInpKbn;
	CMFCRibbonComboBox* pComboInpTp = mmpComboInpTp();
	pComboInpTp->SelectItem( i_iComboInpKbn);
}

void CMainFrame::SelectComboInp2( MINT i_iComboMarume)
{
	m_iComboMarume = i_iComboMarume;
	CMFCRibbonComboBox* pComboInpTp = mmpComboMarume();
	pComboInpTp->SelectItem( i_iComboMarume);
}

void CMainFrame::SelectComboInp3( MINT i_iComboPlcIzon)
{
	m_iComboPlcIzon = i_iComboPlcIzon;
	CMFCRibbonComboBox* pComboInpTp = mmpComboPlcIzonCd();
	pComboInpTp->SelectItem( i_iComboPlcIzon);
}

//-------------------------------------------------------

void CMainFrame::OnDummy(UINT /*id*/)
{
}

// PARTS リボンバー　部品名
void CMainFrame::OnCbnSelchangeComboPartsNm()
{
	MC::z_mnIA.SetCurCategory( MP_SENTAKU_KOUZOU);

	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboBuzai();
	m_iComboPartsNm = pCmbBox->GetCurSel();						// 選択された部品名

	MC::z_mnIA.SelectComboPartsNmByKmId( m_iComboPartsNm);
	MC::z_mnIA.InitComboMbr();

	MC::z_mmIA.MmDialogKAttrDisp( this);						// 部材属性ダイアログ表示
	MC::z_mmIA.InitComboParts();								// 全項目設定
	MC::z_mmIA.SelectComboPartsNmByKmId( m_iComboPartsNm);

	MC::mhPartsSpec* pPartsSpec;
	pPartsSpec = MC::BuzaiCode::MhGetpPartsSpec( MC::z_mnIA.GetCurPartsNmId());
	if ( pPartsSpec->GetPTCdBr() >= MP_BR_SENBUN || MC::z_mnIA.GetMode() == MP_MD_DELETE)
		MC::CmdCtrl::XqtMenuCmd( IDC_PARTSCREATE);				//	部材入力コマンド
	else 
		MC::CmdCtrl::XqtMenuCmd( IDC_CANCELCMD);				//	コマンドキャンセル
}

// PARTS リボンバー　寸法型式
void CMainFrame::OnCbnSelchangeComboMbr()
{
	MC::z_mnIA.SetCurCategory( MP_SENTAKU_KOUZOU);

	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboMbr();
	m_iComboMbr = pCmbBox->GetCurSel();							// 選択された寸法型式ID

	MC::z_mmIA.MmDialogKAttrDisp( this);						// 部材属性ダイアログ表示
	MC::z_mmIA.InitComboParts();								// 全項目設定
	MC::z_mmIA.SelectComboPartsNmByKmId(m_iComboPartsNm);		// 部品名を設定
	MC::z_mmIA.SelectComboMbrByKmId( m_iComboMbr);				// 寸法形式を設定

	MC::z_mnIA.SelectComboMbrByKmId( m_iComboMbr);
	MC::CmdCtrl::XqtMenuCmd( IDC_PARTSCREATE);					//	部品入力
}

// INPUT リボンバー　入力点区分
void CMainFrame::OnCbnSelchangeComboInpKbn()
{
	CMFCRibbonComboBox *pCmbBox;
	pCmbBox = mmpComboInpTp();
	m_iComboInpKbn = pCmbBox->GetCurSel();
	MC::z_mnIA.SelectComboInpKbnByInpKbnCdXqt( m_iComboInpKbn);
	MC::Window::CurWndFocus();
}

// INPUT リボンバー　丸めコード
void CMainFrame::OnCbnSelchangeComboMarume()
{
	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboMarume();
	m_iComboMarume = pCmbBox->GetCurSel();						// 丸めコード
	MC::z_mnIA.SelectComboMarumeByMarumeCdXqt( m_iComboMarume);
	MC::Window::CurWndFocus();
}

// INPUT リボンバー　配置依存コード
void CMainFrame::OnCbnSelchangeComboPlcIzon()
{
	CMFCRibbonComboBox* pCmbBox;
	pCmbBox = mmpComboPlcIzonCd();
	m_iComboPlcIzon = pCmbBox->GetCurSel();										// 配置依存コード
	MC::z_mnIA.SelectComboPlcIzonCdByPlaceCdXqt( m_iComboPlcIzon);
	MC::Window::CurWndFocus();
}

// PANEL リボンバー　パネル番号
void CMainFrame::OnCbnSelchangeComboPanelNo()
{
	MC::z_mnIA.SetCurCategory( MP_SENTAKU_KOUZOU);

	int ic1 = 1;
}

void CMainFrame::OnView1open()
{
	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
	MC::WindowCtrl::SetCurWndFrame( 1, pChildWnd1);
}

void CMainFrame::OnView2open()
{
	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd2;
	pChildWnd2 = OpenView( z_MCadApp.m_pDocTemplate2);
	MC::WindowCtrl::SetCurWndFrame( 2, pChildWnd2);
}

void CMainFrame::OnView3open()
{
	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd3;
	pChildWnd3 = OpenView( z_MCadApp.m_pDocTemplate3);
	MC::WindowCtrl::SetCurWndFrame( 3, pChildWnd3);
}

void CMainFrame::OnView4open()
{
	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
	MC::WindowCtrl::SetCurWndFrame( 4, pChildWnd1);
}

void CMainFrame::OnView5open()
{
	// ウィンドウのオープン
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( z_MCadApp.m_pDocTemplate1);
	MC::WindowCtrl::SetCurWndFrame( 5, pChildWnd1);
}

// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
afx_msg LRESULT CMainFrame::OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
