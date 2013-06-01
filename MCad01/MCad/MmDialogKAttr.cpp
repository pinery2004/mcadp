// MmDialogKAttr.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MCad.h"
#include "MmDialogKAttr.h"
#include "MnIoPartsAttr.h"
#include "afxdialogex.h"
#include "Winuser.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"
#include "MmSystem.h"
#include "MhGp.h"
#include "MhPartsSpec.h"
#include "MhLib.h"

/////////////////////////////////////////////////////////////////////////////
// 部材属性コンボボックスの取得
CComboBox* CMmDialogKAttr::GetCmbBzaiAttr(
						int			i_iAttrn		// 部材属性番号
				)
{
	static 	CComboBox* pCmbBziAttr[6] = { &m_CmbKAttr1, &m_CmbKAttr2, &m_CmbKAttr3,
										  &m_CmbKAttr4, &m_CmbKAttr5, &m_CmbKAttr6 };
	return pCmbBziAttr[i_iAttrn-1];
}

/////////////////////////////////////////////////////////////////////////////
//	部材属性ダイアログを表示する処理を起動
//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
void CMmDialogKAttr::MmDialogKAttr()
{
	MC::MmWndInfo*	pWndInfo = MC::WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*			pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage( WM_MYMESSAGE_KATTR);
}

/////////////////////////////////////////////////////////////////////////////
//	部材属性ダイアログを表示する	(本体)
void CMmDialogKAttr::MmDialogKAttrDisp(
						CWnd*		i_pWnd			// (I  ) ウィンドウのインスタンス
				)
{
	if ( m_bDispFlg)
	{
		BringWindowToTop();
	}
	else
	{
		m_bDispFlg = true;	
		Create( i_pWnd);
	}
}

// CMmDialogKAttr ダイアログ

IMPLEMENT_DYNAMIC( CMmDialogKAttr, CDialog)

CMmDialogKAttr::CMmDialogKAttr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMmDialogKAttr::IDD, pParent)
{
	m_pParent = NULL;
	m_bDispFlg = false;
}

CMmDialogKAttr::~CMmDialogKAttr()
{
}

BOOL CMmDialogKAttr::Create(CWnd * pWnd)
{
	BOOL bret;
	m_pParent = pWnd;
	bret = CDialog::Create( CMmDialogKAttr::IDD, m_pParent);
	if (bret == TRUE)
	{
		this->ShowWindow( SW_SHOW);
	}
	return bret;
}

void CMmDialogKAttr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXTK_BZI1, m_sBzi1);
	DDX_Control(pDX, IDC_TXTK_BZI2, m_sBzi2);
	DDX_Control(pDX, IDC_TXTK_ATTR1, m_sAttr1);
	DDX_Control(pDX, IDC_TXTK_ATTR2, m_sAttr2);
	DDX_Control(pDX, IDC_TXT3_ATTR3, m_sAttr3);
	DDX_Control(pDX, IDC_TXTK_ATTR4, m_sAttr4);
	DDX_Control(pDX, IDC_TXTK_ATTR5, m_sAttr5);
	DDX_Control(pDX, IDC_TXTK_ATTR6, m_sAttr6);
	DDX_Control(pDX, IDC_CMBK_BZI1, m_CmbKbzi1);
	DDX_Control(pDX, IDC_CMBK_BZI2, m_CmbKbzi2);
	DDX_Control(pDX, IDC_CMBK_ATTR1, m_CmbKAttr1);
	DDX_Control(pDX, IDC_CMBK_ATTR2, m_CmbKAttr2);
	DDX_Control(pDX, IDC_CMBK_ATTR3, m_CmbKAttr3);
	DDX_Control(pDX, IDC_CMBK_ATTR4, m_CmbKAttr4);
	DDX_Control(pDX, IDC_CMBK_ATTR5, m_CmbKAttr5);
	DDX_Control(pDX, IDC_CMBK_ATTR6, m_CmbKAttr6);
}

BEGIN_MESSAGE_MAP(CMmDialogKAttr, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CMmDialogKAttr::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMmDialogKAttr::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_CMBK_BZI1, &CMmDialogKAttr::OnCbnSelchangeCmbkBzi1)
	ON_CBN_SELCHANGE(IDC_CMBK_BZI2, &CMmDialogKAttr::OnCbnSelchangeCmbkBzi2)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR1, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr1)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR2, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr2)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR3, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr3)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR4, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr4)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR5, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr5)
	ON_CBN_SELCHANGE(IDC_CMBK_ATTR6, &CMmDialogKAttr::OnCbnSelchangeCmbkAttr6)
	ON_CBN_EDITCHANGE(IDC_CMBK_ATTR1, &CMmDialogKAttr::OnCbnEditchangeCmbkAttr1)
END_MESSAGE_MAP()


// CMmDialogKAttr メッセージ ハンドラー


void CMmDialogKAttr::OnClose()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		CDialog::OnClose();
	}
}

void CMmDialogKAttr::PostNcDestroy()
{
	if (m_pParent != NULL) {
		MmDialogKAttrEnd();
	}

	CDialog::PostNcDestroy();
}

BOOL CMmDialogKAttr::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
//		if (pMsg->wParam == VK_ESCAPE) {
//			SetControl();
//			return TRUE;
//		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMmDialogKAttr::OnBnClickedOk()
{
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		OnOK();
	}
}

void CMmDialogKAttr::OnBnClickedCancel()
{
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		OnCancel();
	}
}

BOOL CMmDialogKAttr::OnInitDialog()
{
	static int iPos[2] = { 1600, 60}; 
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	CRect rect;
	GetWindowRect(&rect);
	SetWindowPos(&wndTop, iPos[0], iPos[1], rect.right - rect.left, rect.bottom - rect.top,
		SWP_SHOWWINDOW);

	m_CmbKbzi1.InsertString( -1, _T("none"));
	m_CmbKbzi2.InsertString( -1, _T("none"));
	m_CmbKAttr1.InsertString( -1, _T("none"));
	m_CmbKAttr2.InsertString( -1, _T("none"));
	m_CmbKAttr3.InsertString( -1, _T("none"));
	m_CmbKAttr4.InsertString( -1, _T("none"));
	m_CmbKAttr5.InsertString( -1, _T("none"));
	m_CmbKAttr6.InsertString( -1, _T("none"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

// 部材名選択処理
void CMmDialogKAttr::OnCbnSelchangeCmbkBzi1()
{
	MC::z_mnIA.SetCurCategory( MP_SENTAKU_KOUZOU);

	CComboBox* pCmbBox;
	pCmbBox = (CComboBox*)GetDlgItem( IDC_CMBK_BZI1);
	MC::System::GetpMainFrame()->m_iComboPartsNm = pCmbBox->GetCurSel();			// 選択された部品名

	MC::z_mnIA.SelectComboPartsNmByKmId( MC::System::GetpMainFrame()->m_iComboPartsNm);

	MC::z_mnIA.InitComboMbr();

	MC::z_mmIA.MmDialogKAttrDisp( this);											// 部材属性ダイアログ表示
	MC::z_mmIA.InitComboParts();													// 全項目設定
//S	MC::z_mmIA.SelectComboPartsNmByKmId( MC::System::GetpMainFrame()->m_iComboPartsNm);

	MC::mhPartsSpec* pPartsSpec	= MC::BuzaiCode::MhGetpPartsSpec( MC::z_mnIA.GetCurPartsNmId());
	if ( pPartsSpec->GetPTCdBr() >= MP_BR_SENBUN || MC::z_mnIA.GetMode() == MP_MD_DELETE)
		MC::CmdCtrl::XqtMenuCmd( IDC_PARTSCREATE);									// 部材入力コマンド
	else 
		MC::CmdCtrl::XqtMenuCmd( IDC_CANCELCMD);									// コマンドキャンセル
}

// 部材メンバー選択処理
void CMmDialogKAttr::OnCbnSelchangeCmbkBzi2()
{
	MC::z_mnIA.SetCurCategory( MP_SENTAKU_KOUZOU);

	CComboBox* pCmbBox;
	pCmbBox = (CComboBox*)GetDlgItem( IDC_CMBK_BZI2);
	MC::System::GetpMainFrame()->m_iComboMbr = pCmbBox->GetCurSel();				// 選択された寸法型式ID

	MC::z_mmIA.MmDialogKAttrDisp( this);											// 部材属性ダイアログ表示
	MC::z_mmIA.InitComboParts();													// 全項目設定
	MC::z_mmIA.SelectComboPartsNmByKmId( MC::System::GetpMainFrame()->m_iComboPartsNm);		// 部品名を設定
	MC::z_mmIA.SelectComboMbrByKmId( MC::System::GetpMainFrame()->m_iComboMbr);		// 寸法形式を設定

	MC::z_mnIA.SelectComboMbrByKmId( MC::System::GetpMainFrame()->m_iComboMbr);
	MC::CmdCtrl::XqtMenuCmd( IDC_PARTSCREATE);										//	部品入力
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int i=1;
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr4()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr5()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CMmDialogKAttr::OnCbnSelchangeCmbkAttr6()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CMmDialogKAttr::OnCbnEditchangeCmbkAttr1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int i=1;
}
