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

// ChildFrm2.cpp : CChildFrame2 �N���X�̎���
//

#include "stdafx.h"
#include "MCad.h"
#include "MmWnd.h"
#include "M3View.h"
#include "MCadDoc.h"
#include "MCadView2.h"
#include "ChildFrm2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame2

IMPLEMENT_DYNCREATE(CChildFrame2, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame2, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame2::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame2::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame2::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame2::OnUpdateFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_CLOSE, &CChildFrame2::OnFileClose)
END_MESSAGE_MAP()

// CChildFrame2 �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame2::CChildFrame2()
{
}

CChildFrame2::~CChildFrame2()
{
}


BOOL CChildFrame2::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	// �f�B�X�v���C��ʃT�C�Y�̎擾
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	HDC hdc = ::GetDC( NULL);
	int Width = GetDeviceCaps(hdc, HORZRES);
	int Height = GetDeviceCaps(hdc, VERTRES);

	::ReleaseDC(NULL, hdc);

	// �\���E�B���h�E�T�C�Y�̐ݒ�
	if ( Width >= 0x500) {
		cs.x = 500; cs.cx = 700;					// ���s����̃E�B���h�E�̃T�C�Y 1280x??? 
	} else {
		cs.x = 200; cs.cx = 580; 					// ���s����̃E�B���h�E�̃T�C�Y 1024x???
	}
	if ( Height >= 0x400) {
		cs.y = 0;	cs.cy = 700;					// ���s����̃E�B���h�E�̃T�C�Y ????x1024
	} else {
		cs.y = 0;	cs.cy = 580;					// ���s����̃E�B���h�E�̃T�C�Y ????x768
	}

	return TRUE;
}

// CChildFrame2 �f�f

#ifdef _DEBUG
void CChildFrame2::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame2::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame2 ���b�Z�[�W �n���h���[

void CChildFrame2::OnFileClose()
{
	// ���̃t���[�������ɂ́AWM_CLOSE �𑗂�܂��B���̃��b�Z�[�W�́A
	// �V�X�e�� ���j���[�� [����] ��I�������ꍇ�Ɠ����ł��B
	SendMessage(WM_CLOSE);
}

int CChildFrame2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)							// view2 Create
		return -1;

//E	// �t���[���̃N���C�A���g�̈�S�̂��߂�r���[���쐬���܂��B
//	if (!m_wndView2.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,						// 
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
//	{
//		TRACE0("�r���[ �E�B���h�E���쐬�ł��܂���ł����B\n");
//		return -1;
//	}

	return 0;
}

void CChildFrame2::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWndEx::OnSetFocus(pOldWnd);

//E	m_wndView2.SetFocus();
}

void CChildFrame2::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame2::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ����v���r���[ ���[�h�������I�ɏI������
	}
}

void CChildFrame2::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

BOOL CChildFrame2::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect ,
						  CMDIFrameWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	MC::WindowCtrl::MmWndSetFrameC( 2, this);

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

void CChildFrame2::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindFrm( this);
	MC::WindowCtrl::MmWndKDelete( pWndInfo);

	CMDIChildWndEx::OnClose();
}
