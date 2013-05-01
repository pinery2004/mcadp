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

// MCad.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MCad.h"
#include "MainFrm.h"
#include "M3View.h"

#include "MCadDoc.h"
#include "MCadView1.h"
#include "MCadView2.h"
#include "MCadForm3.h"
#include "ChildFrm1.h"
#include "ChildFrm2.h"
#include "ChildFrm3.h"

#include "MainFrm.h"
#include "MhDefParts.h"
#include "MmCmdMsg.h"

#include "MmWnd.h"
#include "Mmlib.h"
#include "MhPlcParts.h"
#include "MhInpPlcParts.h"
#include "MhLib.h"
#include "MsDefFunc.h"
#include "MnIoPartsAttr.h"
#include "MmCmd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCadApp

BEGIN_MESSAGE_MAP(CMCadApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMCadApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CMCadApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMCadApp::OnFileOpen)

ON_COMMAND_RANGE(IDC_P0010, IDC_P0360, OnMainMenuP)
ON_UPDATE_COMMAND_UI_RANGE(IDC_P0010, IDC_P0360, OnUpdateMainMenuP)
ON_COMMAND_RANGE(IDP_P0010, IDP_P0340, OnSubMenuP)
ON_UPDATE_COMMAND_UI_RANGE(IDP_P0010, IDP_P0340, OnUpdateSubMenuP)

ON_COMMAND(IDC_RADIO1F, &CMCadApp::OnBnClickedRadio1f)
ON_UPDATE_COMMAND_UI(IDC_RADIO1F, &CMCadApp::OnUpdateRadio1f)
ON_COMMAND(IDC_RADIO2F, &CMCadApp::OnBnClickedRadio2f)
ON_UPDATE_COMMAND_UI(IDC_RADIO2F, &CMCadApp::OnUpdateRadio2f)
ON_COMMAND(IDC_RADIO3F, &CMCadApp::OnBnClickedRadio3f)
ON_UPDATE_COMMAND_UI(IDC_RADIO3F, &CMCadApp::OnUpdateRadio3f)

ON_COMMAND(IDC_RADIOKYANE, &CMCadApp::OnBnClickedRadioYane)
ON_UPDATE_COMMAND_UI(IDC_RADIOKYANE, &CMCadApp::OnUpdateRadioYane)
ON_COMMAND(IDC_RADIOKTENJO, &CMCadApp::OnBnClickedRadioTenjo)
ON_UPDATE_COMMAND_UI(IDC_RADIOKTENJO, &CMCadApp::OnUpdateRadioTenjo)
ON_COMMAND(IDC_RADIOKTAIRYOKU, &CMCadApp::OnBnClickedRadioTairyoku)
ON_UPDATE_COMMAND_UI(IDC_RADIOKTAIRYOKU, &CMCadApp::OnUpdateRadioTairyoku)
ON_COMMAND(IDC_RADIOKKABE, &CMCadApp::OnBnClickedRadioKabe)
ON_UPDATE_COMMAND_UI(IDC_RADIOKKABE, &CMCadApp::OnUpdateRadioKabe)
ON_COMMAND(IDC_RADIOKYUKA, &CMCadApp::OnBnClickedRadioYuka)
ON_UPDATE_COMMAND_UI(IDC_RADIOKYUKA, &CMCadApp::OnUpdateRadioYuka)
ON_COMMAND(IDC_RADIOKKOYA, &CMCadApp::OnBnClickedRadioKoya)
ON_UPDATE_COMMAND_UI(IDC_RADIOKKOYA, &CMCadApp::OnUpdateRadioKoya)
ON_COMMAND(IDC_RADIOKDODAI, &CMCadApp::OnBnClickedRadioDodai)
ON_UPDATE_COMMAND_UI(IDC_RADIOKDODAI, &CMCadApp::OnUpdateRadioDodai)
ON_COMMAND(IDC_RADIOKKISO, &CMCadApp::OnBnClickedRadioKiso)
ON_UPDATE_COMMAND_UI(IDC_RADIOKKISO, &CMCadApp::OnUpdateRadioKiso)

ON_COMMAND(IDC_RADIOSYANE, &CMCadApp::OnBnClickedRadioYane)
ON_UPDATE_COMMAND_UI(IDC_RADIOSYANE, &CMCadApp::OnUpdateRadioYane)
ON_COMMAND(IDC_RADIOSTENJO, &CMCadApp::OnBnClickedRadioTenjo)
ON_UPDATE_COMMAND_UI(IDC_RADIOSTENJO, &CMCadApp::OnUpdateRadioTenjo)
ON_COMMAND(IDC_RADIOSTAIRYOKU, &CMCadApp::OnBnClickedRadioTairyoku)
ON_UPDATE_COMMAND_UI(IDC_RADIOSTAIRYOKU, &CMCadApp::OnUpdateRadioTairyoku)
ON_COMMAND(IDC_RADIOSKABE, &CMCadApp::OnBnClickedRadioKabe)
ON_UPDATE_COMMAND_UI(IDC_RADIOSKABE, &CMCadApp::OnUpdateRadioKabe)
ON_COMMAND(IDC_RADIOSYUKA, &CMCadApp::OnBnClickedRadioYuka)
ON_UPDATE_COMMAND_UI(IDC_RADIOSYUKA, &CMCadApp::OnUpdateRadioYuka)
ON_COMMAND(IDC_RADIOSKOYA, &CMCadApp::OnBnClickedRadioKoya)
ON_UPDATE_COMMAND_UI(IDC_RADIOSKOYA, &CMCadApp::OnUpdateRadioKoya)
ON_COMMAND(IDC_RADIOSDODAI, &CMCadApp::OnBnClickedRadioDodai)
ON_UPDATE_COMMAND_UI(IDC_RADIOSDODAI, &CMCadApp::OnUpdateRadioDodai)
ON_COMMAND(IDC_RADIOSKISO, &CMCadApp::OnBnClickedRadioKiso)
ON_UPDATE_COMMAND_UI(IDC_RADIOSKISO, &CMCadApp::OnUpdateRadioKiso)

ON_COMMAND(IDC_RADIOKBUZAI, &CMCadApp::OnBnClickedRadioBuzai)
ON_UPDATE_COMMAND_UI(IDC_RADIOKBUZAI, &CMCadApp::OnUpdateRadioBuzai)
ON_COMMAND(IDC_RADIOKKANAGU, &CMCadApp::OnBnClickedRadioKanagu)
ON_UPDATE_COMMAND_UI(IDC_RADIOKKANAGU, &CMCadApp::OnUpdateRadioKanagu)
ON_COMMAND(IDC_RADIOKPANEL, &CMCadApp::OnBnClickedRadioPanel)
ON_UPDATE_COMMAND_UI(IDC_RADIOKPANEL, &CMCadApp::OnUpdateRadioPanel)
ON_COMMAND(IDC_RADIOKOTHER, &CMCadApp::OnBnClickedRadioOther)
ON_UPDATE_COMMAND_UI(IDC_RADIOKOTHER, &CMCadApp::OnUpdateRadioOther)

ON_COMMAND(IDC_RADIOSBUZAI, &CMCadApp::OnBnClickedRadioBuzai)
ON_UPDATE_COMMAND_UI(IDC_RADIOSBUZAI, &CMCadApp::OnUpdateRadioBuzai)
ON_COMMAND(IDC_RADIOSKANAGU, &CMCadApp::OnBnClickedRadioKanagu)
ON_UPDATE_COMMAND_UI(IDC_RADIOSKANAGU, &CMCadApp::OnUpdateRadioKanagu)
ON_COMMAND(IDC_RADIOSPANEL, &CMCadApp::OnBnClickedRadioPanel)
ON_UPDATE_COMMAND_UI(IDC_RADIOSPANEL, &CMCadApp::OnUpdateRadioPanel)
ON_COMMAND(IDC_RADIOSOTHER, &CMCadApp::OnBnClickedRadioOther)
ON_UPDATE_COMMAND_UI(IDC_RADIOSOTHER, &CMCadApp::OnUpdateRadioOther)

ON_COMMAND(IDC_RADIOSEL1, &CMCadApp::OnBnClickedRadioSel1)
ON_UPDATE_COMMAND_UI(IDC_RADIOSEL1, &CMCadApp::OnUpdateRadioSel1)
ON_COMMAND(IDC_RADIOSEL2, &CMCadApp::OnBnClickedRadioSel2)
ON_UPDATE_COMMAND_UI(IDC_RADIOSEL2, &CMCadApp::OnUpdateRadioSel2)
ON_COMMAND(IDC_RADIOSEL3, &CMCadApp::OnBnClickedRadioSel3)
ON_UPDATE_COMMAND_UI(IDC_RADIOSEL3, &CMCadApp::OnUpdateRadioSel3)
ON_COMMAND(IDC_CHUKIDELETE, &CMCadApp::OnBnClickedChukiDelete)
ON_UPDATE_COMMAND_UI(IDC_CHUKIDELETE, &CMCadApp::OnUpdateChukiDelete)
ON_COMMAND(IDC_CHUKIMOVE, &CMCadApp::OnBnClickedChukiMove)
ON_UPDATE_COMMAND_UI(IDC_CHUKIMOVE, &CMCadApp::OnUpdateChukiMove)
ON_COMMAND(IDC_CHUKICHANGE, &CMCadApp::OnBnClickedChukiChange)
ON_UPDATE_COMMAND_UI(IDC_CHUKICHANGE, &CMCadApp::OnUpdateChukiChange)
ON_COMMAND(IDC_CHECKBUZAI, &CMCadApp::OnBnClickedCheckBuzai)
ON_UPDATE_COMMAND_UI(IDC_CHECKBUZAI, &CMCadApp::OnUpdateCheckBuzai)
ON_COMMAND(IDC_CHECKKANAGU, &CMCadApp::OnBnClickedCheckKanagu)
ON_UPDATE_COMMAND_UI(IDC_CHECKKANAGU, &CMCadApp::OnUpdateCheckKanagu)
ON_COMMAND(IDC_CHECKGOHAN, &CMCadApp::OnBnClickedCheckGohan)
ON_UPDATE_COMMAND_UI(IDC_CHECKGOHAN, &CMCadApp::OnUpdateCheckGohan)
ON_COMMAND(IDC_CHECKATTR1, &CMCadApp::OnBnClickedCheckAttr1)
ON_UPDATE_COMMAND_UI(IDC_CHECKATTR1, &CMCadApp::OnUpdateCheckAttr1)
ON_COMMAND(IDC_CHECKATTR2, &CMCadApp::OnBnClickedCheckAttr2)
ON_UPDATE_COMMAND_UI(IDC_CHECKATTR2, &CMCadApp::OnUpdateCheckAttr2)
ON_COMMAND(IDC_CHECKATTR3, &CMCadApp::OnBnClickedCheckAttr3)
ON_UPDATE_COMMAND_UI(IDC_CHECKATTR3, &CMCadApp::OnUpdateCheckAttr3)
ON_COMMAND(IDC_CHECKATTR4, &CMCadApp::OnBnClickedCheckAttr4)
ON_UPDATE_COMMAND_UI(IDC_CHECKATTR4, &CMCadApp::OnUpdateCheckAttr4)
ON_COMMAND(IDC_PANELBEFORE, &CMCadApp::OnBnClickedPanelBefore)
ON_UPDATE_COMMAND_UI(IDC_PANELBEFORE, &CMCadApp::OnUpdatePanelBefore)
ON_COMMAND(IDC_PANELNEXT, &CMCadApp::OnBnClickedPanelNext)
ON_UPDATE_COMMAND_UI(IDC_PANELNEXT, &CMCadApp::OnUpdatePanelNext)
ON_COMMAND(IDC_PANELALL, &CMCadApp::OnBnClickedPanelAll)
ON_UPDATE_COMMAND_UI(IDC_PANELALL, &CMCadApp::OnUpdatePanelAll)
ON_COMMAND(IDC_RADIO_S_JYUUKO, &CMCadApp::OnBnClickedRadioJyuuko)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_JYUUKO, &CMCadApp::OnUpdateRadioJyuuko)
ON_COMMAND(IDC_RADIO_S_JYUUTO, &CMCadApp::OnBnClickedRadioJyuuto)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_JYUUTO, &CMCadApp::OnUpdateRadioJyuuto)
ON_COMMAND(IDC_RADIO_S_BUKKEN, &CMCadApp::OnBnClickedRadioBukken)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_BUKKEN, &CMCadApp::OnUpdateRadioBukken)
ON_COMMAND(IDC_RADIO_S_YANE, &CMCadApp::OnBnClickedRadioSYane)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_YANE, &CMCadApp::OnUpdateRadioSYane)
ON_COMMAND(IDC_RADIO_S_SIKITI, &CMCadApp::OnBnClickedRadioSikiti)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_SIKITI, &CMCadApp::OnUpdateRadioSikiti)
ON_COMMAND(IDC_RADIO_S_HEKIRYOU, &CMCadApp::OnBnClickedRadioHekiryou)
ON_UPDATE_COMMAND_UI(IDC_RADIO_S_HEKIRYOU, &CMCadApp::OnUpdateRadioHekiryou)
END_MESSAGE_MAP()


// CMCadApp コンストラクション

CMCadApp::CMCadApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// アプリケーションが共通言語ランタイム サポート (/clr) を使用して作成されている場合:
	//     1) この追加設定は、再起動マネージャー サポートが正常に機能するために必要です。
	//     2) 作成するには、プロジェクトに System.Windows.Forms への参照を追加する必要があります。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 下のアプリケーション ID 文字列を一意の ID 文字列で置換します。推奨される
	// 文字列の形式は CompanyName.ProductName.SubProduct.VersionInformation です
	SetAppID(_T("MCad.AppID.NoVersion"));

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

// 唯一の CMCadApp オブジェクトです。

CMCadApp z_MCadApp;


// CMCadApp 初期化

BOOL CMCadApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit コントロールを使用するには AfxInitRichEdit2() が必要です	
	// AfxInitRichEdit2();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(4);  // 標準の INI ファイルのオプションをロードします (MRU を含む)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	z_MCadApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	m_pDocTemplate1 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
		RUNTIME_CLASS(CChildFrame1), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CMCadView1));
	if (!m_pDocTemplate1)
		return FALSE;
	AddDocTemplate(m_pDocTemplate1);

	m_pDocTemplate2 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
//E		RUNTIME_CLASS(CChildFrame1), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CChildFrame2), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CMCadView2));
	if (!m_pDocTemplate2)
		return FALSE;
	AddDocTemplate(m_pDocTemplate2);

	m_pDocTemplate3 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
//E		RUNTIME_CLASS(CChildFrame1), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CChildFrame3), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CMCadForm3));
	if (!m_pDocTemplate3)
		return FALSE;
	AddDocTemplate(m_pDocTemplate3);

	// メイン MDI フレーム ウィンドウを作成します。
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	m_pMainFrame = pMainFrame;

//-----------------------------------------------------------------------------

	MC::System::MmInitialize();

	MC::z_mnIA.SetInpKai( MP_KAI1);
	MC::mtPlcInp::SetInpKai( MC::z_mnIA.GetInpKai());
	MC::z_mnIA.SetMode( MP_MD_CREATE);

	MC::z_mnIA.SetSCdGp( MP_GP_JYUKO);

	MC::z_mnIA.SetKCdGp( MP_GP_KABE);
	MC::z_mnIA.SetKCdBr( MP_BR_BUZAI);
	MC::z_mnIA.SetKSel( MP_SEL1);
	m_bPartsListBuzai	= false;
	m_bPartsListKanagu = false;
	m_bPartsListGohan	= false;
	m_bPartsAttr1 = false;
	m_bPartsAttr2 = false;
	m_bPartsAttr3 = false;
	m_bPartsAttr4 = false;

//-----------------------------------------------------------------------------

	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出します。
	//  MDI アプリケーションでは、この呼び出しは、m_pMainWnd を設定した直後に発生しなければなりません。
	// ドラッグ/ドロップ オープンを許可します。
	m_pMainWnd->DragAcceptFiles();

	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine( cmdInfo);

	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	RegisterShellFileTypes( TRUE);

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	MC::WindowCtrl::MmWndSetSyubetsuC( 1, MTHEIMENZU, 1, 1);

	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if ( !ProcessShellCommand(cmdInfo))
		return FALSE;

	MC::z_mnIA.InitComboPartsNm();												// 組、分類に対応する部品を選択可能項目として設定する
//S	MC::z_mnIA.InitComboAttr( MP_AT_HRZ_PARTS);									// 属性入力用コンボボックスを初期化する

	//// ウィンドウのオープン
	MC::WindowCtrl::MmWndSetSyubetsuC( 2, MTHEIMENZU, 1, 1);
	pMainFrame->OpenView( m_pDocTemplate2);
	MC::WindowCtrl::MmWndSetSyubetsuC( 3, MTHEIMENZU, 1, 1);
	pMainFrame->OpenView( m_pDocTemplate3);
	return TRUE;
}

int CMCadApp::ExitInstance()
{
	//TODO: 追加したリソースがある場合にはそれらも処理してください
	MC::System::MmTerminate();

	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMCadApp メッセージ ハンドラー


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CMCadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMCadApp のカスタマイズされた読み込みメソッドと保存メソッド

void CMCadApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMCadApp::LoadCustomState()
{
}

void CMCadApp::SaveCustomState()
{
}

// CMCadApp メッセージ ハンドラー
void CMCadApp::OnFileNew() 
{
	// 新しい MDI 子ウィンドウを作成します

	MINT				ist1;

	if ( MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( NULL, Mstr( "初期化しますか"), Mstr( "初期化確認"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}

	//　３次元表示は一旦消す
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if ( pWndInfo) 
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	//	モデルを初期化し表示する
	ist1 = MC::IeModel::MhMdlLoad( NULL);
	MC::WindowCtrl::MmWndKReDrawAll();
}

void CMCadApp::OnFileOpen()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
//	MINT		Ist1;
	MCHAR		PathI[MAX_PATH];
	MCHAR		PathO[MAX_PATH];
//	CWnd*		ViewId;															// ﾋﾞｭｰのｲﾝｽﾀﾝｽ
	MINT		ist1;

//		Mstrcpy( TablePath, MC::MmSystemProperty::GetStr( MM_STR_MODEL_DIR));
//		Mstrcat( TablePath, _T("構成.csv"));
//
//	Ist1 = MsGetRegistryPath( PathI);													// ﾚｼﾞｽﾄﾘよりﾊﾟｽを取得
	Mstrcpy_s( PathI, Mstr("D:\\MCAD_32\\マスタ\\データ\\"));
	ist1 = MC::IeModel::MhFileDialog( true, PathI, PathO, MAX_PATH);					// ﾌｧｲﾙﾀﾞｲｱﾛｸﾞの表示

	if ( ist1 == 1) {																	// OKの場合読み込み
		//　３次元表示は一旦消す
		MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
		if ( pWndInfo) 
			pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

		//	モデルを読み込み表示する
		ist1 = MC::IeModel::MhMdlLoad( PathO);
		MC::WindowCtrl::MmWndKReDrawAll();

		//　３次元表示がされていた場合は新しいデータで再度表示する
		if ( pWndInfo) 
			OnView2On();
	}
}


void CMCadApp::OnView1On()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 1, MTHEIMENZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 1, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView2On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo) {
//		pWndInfo->GetWnd()->SetWindowPos(&CWnd::wndTopMost , 0, 0, 0, 0,		// 前面に表示し直そうとしたが失敗し
//		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE | SWP_NOZORDER);					// 仮に一旦削除後に再表示した
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	}
	CreateWnd( 2, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView3On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 3, MTHEIMENZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 3, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView4On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 4, MTHEIMENZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 4, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView5On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 5, MTHEIMENZU, 1, 1);		// ウィンドウ管理
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 5, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView1Off()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 1, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView2Off()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView3Off()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 3, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
//		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView4Off()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 4, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView5Off()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 5, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnMainMenuP( UINT nID)
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	// コマンドキュー
	if ( nID == IDC_DISP_3D) {
		OnView2On();
	} else {
		if ( nID == IDC_ZOOMINIT) {
			MC::WindowCtrl::MmGridNumSet( NULL);								// 初期設定
			MC::WindowCtrl::MmGridNumXqt();
		}
		MC::WindowCtrl::MmWndKCmdXqt( nID);										//	メニューコマンド
	}
}

void CMCadApp::OnUpdateMainMenuP( CCmdUI *pCmdUI)
{
	// TODO : ここにコマンド更新 UI ハンドラ コードを追加します。
	if ( pCmdUI->m_nID == IDC_UNDO) {
		pCmdUI->Enable( MC::HaitiCmd::MmUndoIsNotEmpty());
	} else if ( pCmdUI->m_nID == IDC_REDO) {
		pCmdUI->Enable( MC::HaitiCmd::MmRedoIsNotEmpty());
	}
}

void CMCadApp::OnSubMenuP( UINT nID)
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	// コマンドキュー
	MC::WindowCtrl::MmWndKCmdXqt( nID);											//	メニューコマンド

}

void CMCadApp::OnUpdateSubMenuP( CCmdUI *pCmdUI)
{
	// TODO : ここにコマンド更新 UI ハンドラ コードを追加します。
}

void CMCadApp::CreateWnd(
				const	MINT		iWndSyu,		// (I  ) ウィンドウ種類
				const	MINT		iZuSyu,			// (I  ) 図種類
				const	MINT		iKai,			// (I  ) 階
				const	MINT		iZuNum			// (I  ) 図番号
				) 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	MC::WindowCtrl::MmWndSetSyubetsuC( iWndSyu, iZuSyu, iKai, iZuNum);

	// 新しい MDI 子ウィンドウを作成します
	switch (iWndSyu)
	{
	default:
		ASSERT(FALSE);
		break;

	case 1:
		pFrame->OnView1open();
		break;

	case 2:
		pFrame->OnView2open();
		break;

	case 3:
		pFrame->OnView3open();
		break;

	case 4:
		pFrame->OnView4open();
		break;

	case 5:
		pFrame->OnView5open();
		break;
	}
}

void CMCadApp::OnBnClickedRadio1f()
{
	MC::z_mnIA.SetInpKai( MP_KAI1);										// １階
	MC::mtPlcInp::SetInpKai( MC::z_mnIA.GetInpKai());
//E	MC::Window::CurWndFocus();
	MC::WindowCtrl::MmWndKReDraw();
}


void CMCadApp::OnUpdateRadio1f(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetInpKai() == MP_KAI1);
}


void CMCadApp::OnBnClickedRadio2f()
{
	MC::z_mnIA.SetInpKai( MP_KAI2);										// ２階
	MC::mtPlcInp::SetInpKai( MC::z_mnIA.GetInpKai());
//E	MC::Window::CurWndFocus();
	MC::WindowCtrl::MmWndKReDraw();
}


void CMCadApp::OnUpdateRadio2f(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetInpKai() == MP_KAI2);
}


void CMCadApp::OnBnClickedRadio3f()
{
	MC::z_mnIA.SetInpKai( MP_KAI3);										// ３階
	MC::mtPlcInp::SetInpKai( MC::z_mnIA.GetInpKai());
//E	MC::Window::CurWndFocus();
	MC::WindowCtrl::MmWndKReDraw();
}


void CMCadApp::OnUpdateRadio3f(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetInpKai() == MP_KAI3);
}


void CMCadApp::OnBnClickedRadioYane()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_YANE);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioYane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_YANE);
}


void CMCadApp::OnBnClickedRadioTenjo()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_TENJO);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioTenjo(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_TENJO);
}


void CMCadApp::OnBnClickedRadioTairyoku()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_TAIRYOKU);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioTairyoku(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_TAIRYOKU);
}


void CMCadApp::OnBnClickedRadioKabe()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_KABE);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioKabe(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_KABE);
}


void CMCadApp::OnBnClickedRadioYuka()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_YUKA);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioYuka(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_YUKA);
}


void CMCadApp::OnBnClickedRadioKoya()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_KOYA);
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioKoya(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_KOYA);
}


void CMCadApp::OnBnClickedRadioDodai()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_DODAI);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioDodai(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_DODAI);
}


void CMCadApp::OnBnClickedRadioKiso()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdGp( MP_GP_KISO);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioKiso(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdGp() == MP_GP_KISO);
}


void CMCadApp::OnBnClickedRadioBuzai()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdBr( MP_BR_BUZAI);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioBuzai(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdBr() == MP_BR_BUZAI);
}


void CMCadApp::OnBnClickedRadioKanagu()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdBr( MP_BR_KANAGU);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioKanagu(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdBr() == MP_BR_KANAGU);
}


void CMCadApp::OnBnClickedRadioPanel()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdBr( MP_BR_PANEL);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioPanel(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdBr() == MP_BR_PANEL);
}


void CMCadApp::OnBnClickedRadioOther()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	MC::z_mnIA.SetKCdBr( MP_BR_OTHER);
	MC::z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
	// ダイアログの項目を設定する
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	コマンドキャンセル
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	コマンドキャンセル
}


void CMCadApp::OnUpdateRadioOther(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetKCdBr() == MP_BR_OTHER);
}


void CMCadApp::OnBnClickedRadioSel1()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	m_iKInpSel = MP_SEL1;
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateRadioSel1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_iKInpSel == MP_SEL1);
}


void CMCadApp::OnBnClickedRadioSel2()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	m_iKInpSel = MP_SEL2;
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateRadioSel2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_iKInpSel == MP_SEL2);
}


void CMCadApp::OnBnClickedRadioSel3()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

	m_iKInpSel = MP_SEL3;
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateRadioSel3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_iKInpSel == MP_SEL3);
}


void CMCadApp::OnBnClickedChukiDelete()
{
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateChukiDelete(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}


void CMCadApp::OnBnClickedChukiMove()
{
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateChukiMove(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}


void CMCadApp::OnBnClickedChukiChange()
{
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateChukiChange(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}

void CMCadApp::OnBnClickedCheckBuzai()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsListBuzai = !m_bPartsListBuzai;

//E	MCHAR sTitle[] =Mstr( "テスト");
//	CButton* pCheckBuzai = (CButton*)(MC::System::GetpMainFrame()->m_wndRibbonBar.GetDlgItem(IDC_CHECKBUZAI));
//	pCheckBuzai->SetWindowText( sTitle);
//	MINT i1 = pCheckBuzai->GetCheck();
//	pCheckBuzai->ShowWindow( 0);
}


void CMCadApp::OnUpdateCheckBuzai(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsListBuzai);
}


void CMCadApp::OnBnClickedCheckKanagu()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsListKanagu = !m_bPartsListKanagu;
}


void CMCadApp::OnUpdateCheckKanagu(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsListKanagu);	
}


void CMCadApp::OnBnClickedCheckGohan()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsListGohan = !m_bPartsListGohan;
}


void CMCadApp::OnUpdateCheckGohan(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsListGohan);	
}


void CMCadApp::OnBnClickedCheckAttr1()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsAttr1 = !m_bPartsAttr1;
}


void CMCadApp::OnUpdateCheckAttr1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsAttr1);	
}


void CMCadApp::OnBnClickedCheckAttr2()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsAttr2 = !m_bPartsAttr2;
}


void CMCadApp::OnUpdateCheckAttr2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsAttr2);	
}


void CMCadApp::OnBnClickedCheckAttr3()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsAttr3 = !m_bPartsAttr3;
}


void CMCadApp::OnUpdateCheckAttr3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsAttr3);	
}


void CMCadApp::OnBnClickedCheckAttr4()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsAttr4 = !m_bPartsAttr4;
}


void CMCadApp::OnUpdateCheckAttr4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( m_bPartsAttr4);	
}


void CMCadApp::OnBnClickedPanelBefore()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdatePanelBefore(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}


void CMCadApp::OnBnClickedPanelNext()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdatePanelNext(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}


void CMCadApp::OnBnClickedPanelAll()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdatePanelAll(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
}


void CMCadApp::OnBnClickedRadioJyuuko()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_JYUKO);
}


void CMCadApp::OnUpdateRadioJyuuko(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_JYUKO);
}


void CMCadApp::OnBnClickedRadioJyuuto()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_JYUTO);
}


void CMCadApp::OnUpdateRadioJyuuto(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_JYUTO);
}


void CMCadApp::OnBnClickedRadioBukken()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_BUKKEN);
}


void CMCadApp::OnUpdateRadioBukken(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_BUKKEN);
}


void CMCadApp::OnBnClickedRadioSYane()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_S_YANE);
}


void CMCadApp::OnUpdateRadioSYane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_S_YANE);
}


void CMCadApp::OnBnClickedRadioSikiti()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_SIKITI);
}


void CMCadApp::OnUpdateRadioSikiti(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_SIKITI);
}


void CMCadApp::OnBnClickedRadioHekiryou()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_ISYOU);

	MC::z_mnIA.SetSCdGp( MP_GP_HEKIRYOU);
}


void CMCadApp::OnUpdateRadioHekiryou(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( MC::z_mnIA.GetSCdGp() == MP_GP_HEKIRYOU);
}
