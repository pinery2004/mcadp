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

// MainFrm.cpp : CMainFrame �N���X�̎���
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

CMainFrame *ms_pMainFrame;										// ���C���t���[���|�C���^(Global) 

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

// CMainFrame �R���X�g���N�V����/�f�X�g���N�V����

CMainFrame::CMainFrame()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
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
	// �Œ�l�Ɋ�Â��ăr�W���A�� �}�l�[�W���[�� visual �X�^�C����ݒ肵�܂�
	OnApplicationLook(g_theApp.m_nAppLook);

	// �^�u�^���̃E�B���h�E�\��
	if (TAB_WINDOW) {
		CMDITabInfo mdiTabParams;
		mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // �g�p�\�Ȃ��̑��̎��o�X�^�C��...
		mdiTabParams.m_bActiveTabCloseButton = TRUE;      // �^�u�̈�̉E���� [����] �{�^����z�u����ɂ́AFALSE �ɐݒ肵�܂�
		mdiTabParams.m_bTabIcons = FALSE;    // MDI �^�u�Ńh�L�������g �A�C�R����L���ɂ���ɂ́ATRUE �ɐݒ肵�܂�
		mdiTabParams.m_bAutoColor = TRUE;    // MDI �^�u�̎����F�ݒ�𖳌��ɂ���ɂ́AFALSE �ɐݒ肵�܂�
		mdiTabParams.m_bDocumentMenu = TRUE; // �^�u�̈�̉E�[�ɂ���h�L�������g ���j���[��L���ɂ��܂�
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
		TRACE0("�X�e�[�^�X �o�[�̍쐬�Ɏ��s���܂����B\n");
		return -1;      // �쐬�ł��Ȃ��ꍇ
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 �X�^�C���̃h�b�L���O �E�B���h�E�����L���ɂ��܂�
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 �X�^�C���̃h�b�L���O �E�B���h�E�̎�����\�������L���ɂ��܂�
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �g���E�B���h�E�Ǘ��_�C�A���O �{�b�N�X��L���ɂ��܂�
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// �E�B���h�E �^�C�g�� �o�[�Ńh�L�������g���ƃA�v���P�[�V�������̏�����؂�ւ��܂��B����ɂ��A
	// �h�L�������g�����T���l�C���ŕ\���ł��邽�߁A�^�X�N �o�[�̎g�p�������サ�܂��B
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

void CMainFrame::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MINT	ist1;
	if (MC::IeModel::MhGetModFIeMdl()) {
		ist1 = MessageBox( Mstr( "�I�����܂���"), Mstr( "�I���m�F"), MB_OKCANCEL);
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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return TRUE;
}

// CMainFrame �f�f

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

// CMainFrame ���b�Z�[�W �n���h���[

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

// PARTS �_�C�A���O�o�[�@���ޖ�

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
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo2()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo11()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	m_iComboInp1 = ((CComboBox*)(m_wndRibbonBar.GetDlgItem(IDC_CMB_Inp1)))->GetCurSel();
	MC::mtInpMode::SetComboInpKb( m_iComboInp1);
	MC::Window::CurWndFocus();
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo12()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeCombo13()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboPanelNo()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int ic1 = 1;
}


void CMainFrame::OnCbnSelchangeComboAttr1()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboAttr2()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboAttr3()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboAttr4()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboAttr5()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}


void CMainFrame::OnCbnSelchangeComboAttr6()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}

void CMainFrame::OnView1open()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
//S	CChildFrame1 *pChildFrm1 = new CChildFrame1;
//	TRACE( "new CChildFrame1(%x)\n", pChildFrm1);
//	MC::WindowCtrl::MmWndSetFrameC( 1, pChildFrm1);
//	if (!pChildFrm1->Create( NULL, _T("Window1"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// �E�B���h�E�̃I�[�v��
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 1, pChildWnd1);
}


void CMainFrame::OnView2open()
{
//S	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
//	CChildFrame2 *pChildFrm2 = new CChildFrame2;
//	MC::WindowCtrl::MmWndSetFrameC( 2, pChildFrm2);
//	if (!pChildFrm2->Create( NULL, _T("Window2"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// �E�B���h�E�̃I�[�v��
	CMDIChildWnd* pChildWnd2;
	pChildWnd2 = OpenView( g_theApp.m_pDocTemplate2);
	MC::WindowCtrl::MmWndSetFrameC( 2, pChildWnd2);
}


void CMainFrame::OnView3open()
{
//S	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
//	CChildFrame3 *pChildFrm3 = new CChildFrame3;
//	MC::WindowCtrl::MmWndSetFrameC( 3, pChildFrm3);
//	if (!pChildFrm3->Create( NULL, _T("Window3"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// �E�B���h�E�̃I�[�v��
	CMDIChildWnd* pChildWnd3;
	pChildWnd3 = OpenView( g_theApp.m_pDocTemplate3);
	MC::WindowCtrl::MmWndSetFrameC( 3, pChildWnd3);
}


void CMainFrame::OnView4open()
{
//S	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
//	CChildFrame4 *pChildFrm4 = new CChildFrame4;
//	MC::WindowCtrl::MmWndSetFrameC( 4, pChildFrm4);
//	if (!pChildFrm4->Create( NULL, _T("Window4"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// �E�B���h�E�̃I�[�v��
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 4, pChildWnd1);
}


void CMainFrame::OnView5open()
{
//S	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
//	CChildFrame5 *pChildFrm5 = new CChildFrame5;
//	MC::WindowCtrl::MmWndSetFrameC( 5, pChildFrm5);
//	if (!pChildFrm5->Create( NULL, _T("Window5"),
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this))
//		return;

	// �E�B���h�E�̃I�[�v��
	CMDIChildWnd* pChildWnd1;
	pChildWnd1 = OpenView( g_theApp.m_pDocTemplate1);
	MC::WindowCtrl::MmWndSetFrameC( 5, pChildWnd1);
}
