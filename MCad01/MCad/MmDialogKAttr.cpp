// MmDialogKAttr.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MCad.h"
#include "MmDialogKAttr.h"
#include "afxdialogex.h"
#include "Winuser.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

namespace MC
{

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
//	部材属性ダイアログ表示・入力処理の起動(別タスクから起動)
void CMmDialogKAttr::MmDialogKAttr()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEKATTR);
}

/////////////////////////////////////////////////////////////////////////////
//	部材属性ダイアログ表示
void CMmDialogKAttr::MmDialogKAttrInp(
						CWnd*		i_pWnd			// (I  ) ウィンドウのインスタンス
				)
{
																				//US	if ( z_pDlgKAttr == NULL)
	if ( m_bDispFlg)
	{
																				//US		z_pDlgKAttr->BringWindowToTop();
		BringWindowToTop();
	}
	else
	{
																				//US		z_pDlgKAttr = new CMmDialogKAttr;	
																				//US		z_pDlgKAttr->Create( pWnd);																				
		m_bDispFlg = true;	
		Create( i_pWnd);
	}
}

/////////////////////////////////////////////////////////////////////////////
//	部材属性ダイアログ表示　終了
void CMmDialogKAttr::MmDialogKAttrEnd()
{
																				//US	z_pDlgKAttr = NULL;
	m_bDispFlg = false;
}

// CMmDialogKAttr ダイアログ

IMPLEMENT_DYNAMIC( CMmDialogKAttr, CDialog)

CMmDialogKAttr::CMmDialogKAttr(CWnd* pParent /*=NULL*/)
	: CDialog(CMmDialogKAttr::IDD, pParent)
{
	m_pParent = NULL;
}

CMmDialogKAttr::~CMmDialogKAttr()
{
}

BOOL CMmDialogKAttr::Create(CWnd * pWnd)
{
	m_pParent = pWnd;
	BOOL bret = CDialog::Create( CMmDialogKAttr::IDD, m_pParent);






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
																			//US		delete	this;
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
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
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

}