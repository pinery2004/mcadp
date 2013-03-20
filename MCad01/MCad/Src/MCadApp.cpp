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

#include "ChildFrm1.h"
#include "ChildFrm2.h"
#include "ChildFrm3.h"
#include "MCadDoc.h"
#include "MCadView1.h"
#include "MCadView2.h"
#include "MCadForm3.h"

#include "MainFrm.h"
#include "MmSystem.h"
#include "MmDefine.h"
#include "MmCmdMsg.h"

#include "MmWnd.h"
#include "Mmlib.h"
#include "MhPlcInfo.h"
#include "MtInp.h"
#include "MhLib.h"
#include "MsDefFunc.h"
#include "MtInpAttr.h"

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

CMCadApp g_theApp;


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
	g_theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
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

	MC::mtInpMode::SetKai( MP_KAI1);
	MC::mtPlcInp::SetKai( MC::mtInpMode::GetKai());
	MC::mtInpMode::SetMode( MP_MD_CREATE);

	MC::mtInpMode::SetSGp( MP_GP_JYUKO);

	MC::mtInpMode::SetKGp( MP_GP_KABE);
	MC::mtInpMode::SetKBr( MP_BR_BUZAI);
	MC::mtInpMode::SetKSel( MP_SEL1);
	m_bPtsListBuzai	= false;
	m_bPtsListKanagu = false;
	m_bPtsListGohan	= false;

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

	MC::WindowCtrl::MmWndSetSyubetsuC( 1, MTHEIMENZU, 1, 1);

	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if ( !ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

//	((CMainFrame*)pFrame)->OnView1On();
//E	CreateWnd( 1, MTHEIMENZU, 1, 1);

	// ウィンドウのオープン
	pMainFrame->OpenView( m_pDocTemplate2);
	pMainFrame->OpenView( m_pDocTemplate3);
	return TRUE;
}

int CMCadApp::ExitInstance()
{
	//TODO: 追加したリソースがある場合にはそれらも処理してください
	MC::System::MmTerminate();

//S	if (m_hMDIMenu != NULL)
//		FreeResource(m_hMDIMenu);
//	if (m_hMDIAccel != NULL)
//		FreeResource(m_hMDIAccel);

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
//A ------------------------------------------------------------------------
//A	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// 新しい MDI 子ウィンドウを作成します
//A	pFrame->CreateNewChild(
//A		RUNTIME_CLASS(CChildFrame5), IDR_MCADTYPE, m_hMDIMenu, m_hMDIAccel);
//A ------------------------------------------------------------------------

	MINT				ist1;

	if ( MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( NULL, Mstr( "初期化しますか"), Mstr( "初期化確認"), MB_OKCANCEL);
//		ist1 = MessageBox( NULL, Mstr( "終了しますか"), Mstr( "終了確認"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}

	//　３次元表示は一旦消す
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if (pWndInfo) 
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	//	モデルを初期化し表示する
	ist1 = MC::IeModel::MhMdlLoad( NULL);
	MC::WindowCtrl::MmWndKReDrawAll();
}

void CMCadApp::OnFileOpen()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
//	MINT		Ist1;
	MCHAR		PathI[256];
	MCHAR		PathO[256];
//	CWnd*		ViewId;															// ﾋﾞｭｰのｲﾝｽﾀﾝｽ
	MINT		ist1;

//		Mstrcpy( TablePath, MC::MmSystemProperty::GetStr( MM_STR_MODEL_DIR));
//		Mstrcat( TablePath, _T("構成.csv"));
//
//	Ist1 = MsGetRegistryPath( PathI);													// ﾚｼﾞｽﾄﾘよりﾊﾟｽを取得
	Mstrcpy_s( PathI, Mstr("C:\\MCAD_32\\マスタ\\データ\\"));
	ist1 = MC::IeModel::MhFileDialog( true, PathI, PathO);								// ﾌｧｲﾙﾀﾞｲｱﾛｸﾞの表示

	if ( ist1 == 1) {																	// OKの場合読み込み
		//　３次元表示は一旦消す
		MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
		if (pWndInfo) 
			pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

		//	モデルを読み込み表示する
		ist1 = MC::IeModel::MhMdlLoad( PathO);
		MC::WindowCtrl::MmWndKReDrawAll();

		//　３次元表示がされていた場合は新しいデータで再度表示する
//E		if (pWndInfo) 
//E			OnView2On();
	}
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
//		OnFileNew();
		break;
	}
}
