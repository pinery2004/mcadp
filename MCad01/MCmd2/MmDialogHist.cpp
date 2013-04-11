// MmDialogHist.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "resource.h"
#include "MdHist.h"

#include "MmDialogHist.h"

namespace MC
{

void MCmdHistEnd();

} // namespace MC

// CMmDialogHist �_�C�A���O

IMPLEMENT_DYNAMIC(CMmDialogHist, CDialog)

CMmDialogHist::CMmDialogHist(CWnd* pParent /*=NULL*/)
	: CDialog(CMmDialogHist::IDD, pParent)
{
	m_pParent = NULL;
}

CMmDialogHist::~CMmDialogHist()
{
}

BOOL CMmDialogHist::Create(CWnd * pWnd)
{

	m_pParent = pWnd;
	BOOL bret = CDialog::Create( CMmDialogHist::IDD, m_pParent);

	MC::MhHist::MmHistGet( &m_nVer, &m_psVerC, &m_psVerB, &m_psVerD);

	m_listHistC.ResetContent();
	m_listHistB.ResetContent();
	m_listHistD.ResetContent();
	for (MINT ic=0; ic<m_nVer; ic++) {
		m_listHistC.AddString( m_psVerC[ic]);
		m_listHistB.AddString( m_psVerB[ic]);
		m_listHistD.AddString( m_psVerD[ic]);
	}

	if (bret == TRUE)
	{
		this->ShowWindow( SW_SHOW);
	}
	return bret;
}

void CMmDialogHist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTHISTC, m_listHistC);
	DDX_Control(pDX, IDC_LISTHISTB, m_listHistB);
	DDX_Control(pDX, IDC_LISTHISTD, m_listHistD);
	DDX_Control(pDX, IDC_EDT_HISTC, m_edt_Ver_C);
	DDX_Control(pDX, IDC_EDT_HISTB, m_edt_Ver_B);
}

BEGIN_MESSAGE_MAP(CMmDialogHist, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CMmDialogHist::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMmDialogHist::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTONV3, &CMmDialogHist::OnBnClickedButtonv3)
	ON_BN_CLICKED(IDC_BUTTONV1, &CMmDialogHist::OnBnClickedButtonv1)
	ON_BN_CLICKED(IDC_BUTTONV2, &CMmDialogHist::OnBnClickedButtonv2)
END_MESSAGE_MAP()


// CMmDialogHist ���b�Z�[�W �n���h��

void CMmDialogHist::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		CDialog::OnClose();
	}
}

void CMmDialogHist::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		OnOK();
	}
}

void CMmDialogHist::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	if (m_pParent != NULL) {
		DestroyWindow();
	} else {
		OnCancel();
	}
}

// �o�[�W�����I��
void CMmDialogHist::OnBnClickedButtonv3()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CString sVerB;
	CString sVerC;

	m_edt_Ver_B.GetWindowTextW( sVerB);
	m_edt_Ver_C.GetWindowTextW( sVerC);

	MC::MhHist::MmSetVer( sVerB, sVerC, &m_nVer, &m_psVerC, &m_psVerB, &m_psVerD);

	m_listHistC.ResetContent();
	m_listHistB.ResetContent();
	m_listHistD.ResetContent();
	for (MINT ic=0; ic<m_nVer; ic++) {
		m_listHistC.AddString( m_psVerC[ic]);
		m_listHistB.AddString( m_psVerB[ic]);
		m_listHistD.AddString( m_psVerD[ic]);
	}
}


// �o�[�W����UP
void CMmDialogHist::OnBnClickedButtonv1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CString sVerB;
	CString sVerC;

	m_edt_Ver_B.GetWindowTextW( sVerB);
	m_edt_Ver_C.GetWindowTextW( sVerC);

	MC::MhHist::MmVerUp( sVerB, sVerC, &m_nVer, &m_psVerC, &m_psVerB, &m_psVerD);

	m_listHistC.ResetContent();
	m_listHistB.ResetContent();
	m_listHistD.ResetContent();
	for (MINT ic=0; ic<m_nVer; ic++) {
		m_listHistC.AddString( m_psVerC[ic]);
		m_listHistB.AddString( m_psVerB[ic]);
		m_listHistD.AddString( m_psVerD[ic]);
	}
}

// �o�[�W�������ύX
void CMmDialogHist::OnBnClickedButtonv2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CString sVerB;
	CString sVerC;

	m_edt_Ver_B.GetWindowTextW( sVerB);
	m_edt_Ver_C.GetWindowTextW( sVerC);

	MC::MhHist::MmVerCng( sVerB, sVerC, &m_nVer, &m_psVerC, &m_psVerB, &m_psVerD);

	m_listHistC.ResetContent();
	m_listHistB.ResetContent();
	m_listHistD.ResetContent();
	for (MINT ic=0; ic<m_nVer; ic++) {
		m_listHistC.AddString( m_psVerC[ic]);
		m_listHistB.AddString( m_psVerB[ic]);
		m_listHistD.AddString( m_psVerD[ic]);
	}
}

void CMmDialogHist::PostNcDestroy()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	if (m_pParent != NULL) {
		MC::MCmdHistEnd();
		delete	this;
	}

	CDialog::PostNcDestroy();
}


BOOL CMmDialogHist::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	if ( pMsg->message == WM_KEYDOWN) {
		if ( pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
//		if ( pMsg->wParam == VK_ESCAPE) {
//			SetControl();
//			return TRUE;
//		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
