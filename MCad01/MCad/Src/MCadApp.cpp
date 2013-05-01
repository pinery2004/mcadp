// ���� MFC �T���v�� �\�[�X �R�[�h�ł́AMFC Microsoft Office Fluent ���[�U�[ �C���^�[�t�F�C�X 
// ("Fluent UI") �̎g�p���@�������܂��B���̃R�[�h�́AMFC C++ ���C�u���� �\�t�g�E�F�A�� 
// ��������Ă��� Microsoft Foundation Class ���t�@�����X����ъ֘A�d�q�h�L�������g��
// �⊮���邽�߂̎Q�l�����Ƃ��Ē񋟂���܂��B
// Fluent UI �𕡐��A�g�p�A�܂��͔z�z���邽�߂̃��C�Z���X�����͌ʂɗp�ӂ���Ă��܂��B
// Fluent UI ���C�Z���X �v���O�����̏ڍׂɂ��ẮAWeb �T�C�g
// http://msdn.microsoft.com/ja-jp/office/aa973809.aspx ���Q�Ƃ��Ă��������B
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MCad.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
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
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// �W���̈���Z�b�g�A�b�v �R�}���h
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


// CMCadApp �R���X�g���N�V����

CMCadApp::CMCadApp()
{
	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �A�v���P�[�V���������ʌ��ꃉ���^�C�� �T�|�[�g (/clr) ���g�p���č쐬����Ă���ꍇ:
	//     1) ���̒ǉ��ݒ�́A�ċN���}�l�[�W���[ �T�|�[�g������ɋ@�\���邽�߂ɕK�v�ł��B
	//     2) �쐬����ɂ́A�v���W�F�N�g�� System.Windows.Forms �ւ̎Q�Ƃ�ǉ�����K�v������܂��B
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ���̃A�v���P�[�V���� ID ���������ӂ� ID ������Œu�����܂��B���������
	// ������̌`���� CompanyName.ProductName.SubProduct.VersionInformation �ł�
	SetAppID(_T("MCad.AppID.NoVersion"));

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

// �B��� CMCadApp �I�u�W�F�N�g�ł��B

CMCadApp z_MCadApp;


// CMCadApp ������

BOOL CMCadApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ���C�u���������������܂��B
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit �R���g���[�����g�p����ɂ� AfxInitRichEdit2() ���K�v�ł�	
	// AfxInitRichEdit2();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));
	LoadStdProfileSettings(4);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	z_MCadApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	m_pDocTemplate1 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
		RUNTIME_CLASS(CChildFrame1), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CMCadView1));
	if (!m_pDocTemplate1)
		return FALSE;
	AddDocTemplate(m_pDocTemplate1);

	m_pDocTemplate2 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
//E		RUNTIME_CLASS(CChildFrame1), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CChildFrame2), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CMCadView2));
	if (!m_pDocTemplate2)
		return FALSE;
	AddDocTemplate(m_pDocTemplate2);

	m_pDocTemplate3 = new CMultiDocTemplate(IDR_MCadTYPE,
		RUNTIME_CLASS(CMCadDoc),
//E		RUNTIME_CLASS(CChildFrame1), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CChildFrame3), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CMCadForm3));
	if (!m_pDocTemplate3)
		return FALSE;
	AddDocTemplate(m_pDocTemplate3);

	// ���C�� MDI �t���[�� �E�B���h�E���쐬���܂��B
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

	// �ڔ��������݂���ꍇ�ɂ̂� DragAcceptFiles ���Ăяo���܂��B
	//  MDI �A�v���P�[�V�����ł́A���̌Ăяo���́Am_pMainWnd ��ݒ肵������ɔ������Ȃ���΂Ȃ�܂���B
	// �h���b�O/�h���b�v �I�[�v���������܂��B
	m_pMainWnd->DragAcceptFiles();

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine( cmdInfo);

	// DDE Execute open ���g�p�\�ɂ��܂��B
	EnableShellOpen();
	RegisterShellFileTypes( TRUE);

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	MC::WindowCtrl::MmWndSetSyubetsuC( 1, MTHEIMENZU, 1, 1);

	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if ( !ProcessShellCommand(cmdInfo))
		return FALSE;

	MC::z_mnIA.InitComboPartsNm();												// �g�A���ނɑΉ����镔�i��I���\���ڂƂ��Đݒ肷��
//S	MC::z_mnIA.InitComboAttr( MP_AT_HRZ_PARTS);									// �������͗p�R���{�{�b�N�X������������

	//// �E�B���h�E�̃I�[�v��
	MC::WindowCtrl::MmWndSetSyubetsuC( 2, MTHEIMENZU, 1, 1);
	pMainFrame->OpenView( m_pDocTemplate2);
	MC::WindowCtrl::MmWndSetSyubetsuC( 3, MTHEIMENZU, 1, 1);
	pMainFrame->OpenView( m_pDocTemplate3);
	return TRUE;
}

int CMCadApp::ExitInstance()
{
	//TODO: �ǉ��������\�[�X������ꍇ�ɂ͂������������Ă�������
	MC::System::MmTerminate();

	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMCadApp ���b�Z�[�W �n���h���[


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CMCadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMCadApp �̃J�X�^�}�C�Y���ꂽ�ǂݍ��݃��\�b�h�ƕۑ����\�b�h

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

// CMCadApp ���b�Z�[�W �n���h���[
void CMCadApp::OnFileNew() 
{
	// �V���� MDI �q�E�B���h�E���쐬���܂�

	MINT				ist1;

	if ( MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( NULL, Mstr( "���������܂���"), Mstr( "�������m�F"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}

	//�@�R�����\���͈�U����
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if ( pWndInfo) 
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	//	���f�������������\������
	ist1 = MC::IeModel::MhMdlLoad( NULL);
	MC::WindowCtrl::MmWndKReDrawAll();
}

void CMCadApp::OnFileOpen()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
//	MINT		Ist1;
	MCHAR		PathI[MAX_PATH];
	MCHAR		PathO[MAX_PATH];
//	CWnd*		ViewId;															// �ޭ��̲ݽ�ݽ
	MINT		ist1;

//		Mstrcpy( TablePath, MC::MmSystemProperty::GetStr( MM_STR_MODEL_DIR));
//		Mstrcat( TablePath, _T("�\��.csv"));
//
//	Ist1 = MsGetRegistryPath( PathI);													// ڼ޽�؂���߽���擾
	Mstrcpy_s( PathI, Mstr("D:\\MCAD_32\\�}�X�^\\�f�[�^\\"));
	ist1 = MC::IeModel::MhFileDialog( true, PathI, PathO, MAX_PATH);					// ̧���޲�۸ނ̕\��

	if ( ist1 == 1) {																	// OK�̏ꍇ�ǂݍ���
		//�@�R�����\���͈�U����
		MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
		if ( pWndInfo) 
			pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

		//	���f����ǂݍ��ݕ\������
		ist1 = MC::IeModel::MhMdlLoad( PathO);
		MC::WindowCtrl::MmWndKReDrawAll();

		//�@�R�����\��������Ă����ꍇ�͐V�����f�[�^�ōēx�\������
		if ( pWndInfo) 
			OnView2On();
	}
}


void CMCadApp::OnView1On()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 1, MTHEIMENZU, 1, 1);		// �E�B���h�E�Ǘ�
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 1, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView2On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);		// �E�B���h�E�Ǘ�
	if ( pWndInfo) {
//		pWndInfo->GetWnd()->SetWindowPos(&CWnd::wndTopMost , 0, 0, 0, 0,		// �O�ʂɕ\�����������Ƃ��������s��
//		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE | SWP_NOZORDER);					// ���Ɉ�U�폜��ɍĕ\������
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	}
	CreateWnd( 2, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView3On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 3, MTHEIMENZU, 1, 1);		// �E�B���h�E�Ǘ�
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 3, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView4On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 4, MTHEIMENZU, 1, 1);		// �E�B���h�E�Ǘ�
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 4, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView5On()
{
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 5, MTHEIMENZU, 1, 1);		// �E�B���h�E�Ǘ�
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
	CreateWnd( 5, MTHEIMENZU, 1, 1);
}

void CMCadApp::OnView1Off()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 1, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView2Off()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView3Off()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 3, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
//		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView4Off()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 4, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnView5Off()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 5, MTHEIMENZU, 1, 1);
	if ( pWndInfo)
		pWndInfo->m_pChildFrm->PostMessage(WM_CLOSE);
}

void CMCadApp::OnMainMenuP( UINT nID)
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	// �R�}���h�L���[
	if ( nID == IDC_DISP_3D) {
		OnView2On();
	} else {
		if ( nID == IDC_ZOOMINIT) {
			MC::WindowCtrl::MmGridNumSet( NULL);								// �����ݒ�
			MC::WindowCtrl::MmGridNumXqt();
		}
		MC::WindowCtrl::MmWndKCmdXqt( nID);										//	���j���[�R�}���h
	}
}

void CMCadApp::OnUpdateMainMenuP( CCmdUI *pCmdUI)
{
	// TODO : �����ɃR�}���h�X�V UI �n���h�� �R�[�h��ǉ����܂��B
	if ( pCmdUI->m_nID == IDC_UNDO) {
		pCmdUI->Enable( MC::HaitiCmd::MmUndoIsNotEmpty());
	} else if ( pCmdUI->m_nID == IDC_REDO) {
		pCmdUI->Enable( MC::HaitiCmd::MmRedoIsNotEmpty());
	}
}

void CMCadApp::OnSubMenuP( UINT nID)
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	// �R�}���h�L���[
	MC::WindowCtrl::MmWndKCmdXqt( nID);											//	���j���[�R�}���h

}

void CMCadApp::OnUpdateSubMenuP( CCmdUI *pCmdUI)
{
	// TODO : �����ɃR�}���h�X�V UI �n���h�� �R�[�h��ǉ����܂��B
}

void CMCadApp::CreateWnd(
				const	MINT		iWndSyu,		// (I  ) �E�B���h�E���
				const	MINT		iZuSyu,			// (I  ) �}���
				const	MINT		iKai,			// (I  ) �K
				const	MINT		iZuNum			// (I  ) �}�ԍ�
				) 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	MC::WindowCtrl::MmWndSetSyubetsuC( iWndSyu, iZuSyu, iKai, iZuNum);

	// �V���� MDI �q�E�B���h�E���쐬���܂�
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
	MC::z_mnIA.SetInpKai( MP_KAI1);										// �P�K
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
	MC::z_mnIA.SetInpKai( MP_KAI2);										// �Q�K
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
	MC::z_mnIA.SetInpKai( MP_KAI3);										// �R�K
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// �_�C�A���O�̍��ڂ�ݒ肷��
	MC::z_mmIA.InitComboParts();
	MC::z_mnIA.InitComboParts();
//	�R�}���h�L�����Z��
	MC::WindowCtrl::MmWndKCmdXqt( IDC_CANCELCMD);							//	�R�}���h�L�����Z��
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
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadApp::OnBnClickedChukiMove()
{
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateChukiMove(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadApp::OnBnClickedChukiChange()
{
//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdateChukiChange(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
}

void CMCadApp::OnBnClickedCheckBuzai()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
	m_bPartsListBuzai = !m_bPartsListBuzai;

//E	MCHAR sTitle[] =Mstr( "�e�X�g");
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
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadApp::OnBnClickedPanelNext()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdatePanelNext(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadApp::OnBnClickedPanelAll()
{
	MC::z_mnIA.SetCCategory( MP_SENTAKU_KOUZOU);

//E	MC::Window::CurWndFocus();
}


void CMCadApp::OnUpdatePanelAll(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
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
