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
END_MESSAGE_MAP()

// CChildFrame2 �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame2::CChildFrame2()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
}

CChildFrame2::~CChildFrame2()
{
}


BOOL CChildFrame2::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

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

	return CMDIChildWndEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

int CChildFrame2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B

	return 0;
}
