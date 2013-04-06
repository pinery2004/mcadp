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

// ChildFrm1.cpp : CChildFrame1 �N���X�̎���
//

#include "stdafx.h"
#include "MCad.h"
#include "MmWnd.h"

#include "MCadDoc.h"
#include "MCadView1.h"
#include "ChildFrm1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame1

IMPLEMENT_DYNCREATE(CChildFrame1, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame1, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame1::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame1::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame1::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame1::OnUpdateFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CChildFrame1 �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame1::CChildFrame1()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
}

CChildFrame1::~CChildFrame1()
{
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::~CChildFrame1(%x)\n", this);
#endif
}


BOOL CChildFrame1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::PreCreateWindow(%x)\n", this);
#endif

	cs.x  = 0;									//- GetSystemMetrics(SM_CXSIZEFRAME);
	cs.y  = 0;									//- GetSystemMetrics(SM_CXSIZEFRAME);

	int	iCXMAXIMIZED =	GetSystemMetrics(SM_CXMAXIMIZED);	//1936
	int	iCXSIZEFRAME =	GetSystemMetrics(SM_CXSIZEFRAME);	// 8
	int	iCXEDGE =		GetSystemMetrics(SM_CXEDGE);		// 2
	int	iCYMAXIMIZED =	GetSystemMetrics(SM_CYMAXIMIZED);	// 1096
	int	iCYMENU =		GetSystemMetrics(SM_CYMENU);		// 21
	int	iCYCAPTION =	GetSystemMetrics(SM_CYCAPTION);		// 22
	int	iCYSIZEFRAME =	GetSystemMetrics(SM_CYSIZEFRAME);	// 8

	cs.cx = min( iCXMAXIMIZED, 1280) - 
				 iCYMENU/* 20 */ -
				 iCXSIZEFRAME/* 4 */ * 4;
	cs.cy = min( iCYMAXIMIZED, 1060) -
				 ( iCYMENU/* 20 */ + iCXEDGE/* 2 */) * 5 -
				 iCYCAPTION/* 26 */ * 1 -
				 iCYSIZEFRAME/* 4 */ * 4 + iCXEDGE/* 2 */ * 3;


	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

// CChildFrame1 �f�f

#ifdef _DEBUG
void CChildFrame1::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame1::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame1 ���b�Z�[�W �n���h���[

void CChildFrame1::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame1::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ����v���r���[ ���[�h�������I�ɏI������
	}
}

void CChildFrame1::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

BOOL CChildFrame1::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect ,
						  CMDIFrameWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	MC::WindowCtrl::MmWndSetFrameC( 1, this);

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

int CChildFrame1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B
//E	// �t���[���̃N���C�A���g�̈�S�̂��߂�r���[���쐬���܂��B
//	if (!m_wndView1.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
//	{
//		TRACE0("�r���[ �E�B���h�E���쐬�ł��܂���ł����B\n");
//		return -1;
//	}

	return 0;
}

void CChildFrame1::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindFrm( this);
	MC::WindowCtrl::MmWndKDelete( pWndInfo);

	CMDIChildWndEx::OnClose();
}

void CChildFrame1::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWndEx::OnSetFocus(pOldWnd);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
#if( TRCAE_Frame)
	TRACE( "CChildFrame1::OnSetFocus(%x)\n", this);
#endif
	CMDIChildWnd::OnSetFocus(pOldWnd);

	ms_pMainFrame->m_pCurFrame = this;

//	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();

//E	m_wndView1.SetFocus();
}
