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
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// �W���̈���Z�b�g�A�b�v �R�}���h
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CMCadApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMCadApp::OnFileOpen)
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

CMCadApp g_theApp;


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
	g_theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
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

	MC::WindowCtrl::MmWndSetSyubetsuC( 1, MTHEIMENZU, 1, 1);

	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if ( !ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

//	((CMainFrame*)pFrame)->OnView1On();
//E	CreateWnd( 1, MTHEIMENZU, 1, 1);

	// �E�B���h�E�̃I�[�v��
	pMainFrame->OpenView( m_pDocTemplate2);
	pMainFrame->OpenView( m_pDocTemplate3);
	return TRUE;
}

int CMCadApp::ExitInstance()
{
	//TODO: �ǉ��������\�[�X������ꍇ�ɂ͂������������Ă�������
	MC::System::MmTerminate();

//S	if (m_hMDIMenu != NULL)
//		FreeResource(m_hMDIMenu);
//	if (m_hMDIAccel != NULL)
//		FreeResource(m_hMDIAccel);

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
//A ------------------------------------------------------------------------
//A	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// �V���� MDI �q�E�B���h�E���쐬���܂�
//A	pFrame->CreateNewChild(
//A		RUNTIME_CLASS(CChildFrame5), IDR_MCADTYPE, m_hMDIMenu, m_hMDIAccel);
//A ------------------------------------------------------------------------

	MINT				ist1;

	if ( MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( NULL, Mstr( "���������܂���"), Mstr( "�������m�F"), MB_OKCANCEL);
//		ist1 = MessageBox( NULL, Mstr( "�I�����܂���"), Mstr( "�I���m�F"), MB_OKCANCEL);
		if ( ist1 == IDCANCEL)
			return;
	}

	//�@�R�����\���͈�U����
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
	if (pWndInfo) 
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	//	���f�������������\������
	ist1 = MC::IeModel::MhMdlLoad( NULL);
	MC::WindowCtrl::MmWndKReDrawAll();
}

void CMCadApp::OnFileOpen()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
//	MINT		Ist1;
	MCHAR		PathI[256];
	MCHAR		PathO[256];
//	CWnd*		ViewId;															// �ޭ��̲ݽ�ݽ
	MINT		ist1;

//		Mstrcpy( TablePath, MC::MmSystemProperty::GetStr( MM_STR_MODEL_DIR));
//		Mstrcat( TablePath, _T("�\��.csv"));
//
//	Ist1 = MsGetRegistryPath( PathI);													// ڼ޽�؂���߽���擾
	Mstrcpy_s( PathI, Mstr("C:\\MCAD_32\\�}�X�^\\�f�[�^\\"));
	ist1 = MC::IeModel::MhFileDialog( true, PathI, PathO);								// ̧���޲�۸ނ̕\��

	if ( ist1 == 1) {																	// OK�̏ꍇ�ǂݍ���
		//�@�R�����\���͈�U����
		MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);
		if (pWndInfo) 
			pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

		//	���f����ǂݍ��ݕ\������
		ist1 = MC::IeModel::MhMdlLoad( PathO);
		MC::WindowCtrl::MmWndKReDrawAll();

		//�@�R�����\��������Ă����ꍇ�͐V�����f�[�^�ōēx�\������
//E		if (pWndInfo) 
//E			OnView2On();
	}
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
//		OnFileNew();
		break;
	}
}
