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

// MCadView1.cpp : CMCadView1 �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "MCad.h"
#endif

#include "MCadDoc.h"
#include "MCadView1.h"

#include "MmWnd.h"

#include "MhDefParts.h"
#include "MmLib.h"

#include "MmCmd.h"
#include "resource.h"

#include "MsBitSet.h"

#include "MmCmdMsg.h"
#include "MrCmd.h"

#include "MmInp.h"
#include "MmDialogKAttr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CPoint			z_ptCurCursorD;							// ���݃J�[�\���ړ��ʒu(�\�����W)

// CMCadView1

IMPLEMENT_DYNCREATE(CMCadView1, CView)

BEGIN_MESSAGE_MAP(CMCadView1, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCadView1::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SHOWWINDOW()
    ON_MESSAGE(WM_MYMESSAGEPARTSEDIT, OnMyMessagePtsEdit)			// 1
    ON_MESSAGE(WM_MYMESSAGEGRIDNUM, OnMyMessageGridNum)				// 1
    ON_MESSAGE(WM_MYMESSAGESTATUSBAR, OnMyMessageStatusBar)			// 1
    ON_MESSAGE(WM_MYMESSAGEOPTION, OnMyMessageOpt)					// 1
    ON_MESSAGE(WM_MYMESSAGEHIST, OnMyMessageHist)					// 1
	ON_MESSAGE(WM_MYMESSAGETENKAI, OnMyMessageTenkai)				// 1
	ON_MESSAGE(WM_MYMESSAGEKATTR, OnMyMessageKAttr)					// 1
	
END_MESSAGE_MAP()

// CMCadView1 �R���X�g���N�V����/�f�X�g���N�V����

CMCadView1::CMCadView1()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CMCadView1::~CMCadView1()
{
}

BOOL CMCadView1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	if (!CView::PreCreateWindow(cs))
		return false;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER | WS_MAXIMIZE;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		NULL,reinterpret_cast<HBRUSH>(COLOR_WINDOW+1),NULL); 

	MC::WindowCtrl::SetCurWnd( 1, this);
	MINT ist = MC::WindowCtrl::AddCurWnd();
	_ASSERTE(ist == 0);
	return TRUE;
}

void CMCadView1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::GetWndInfoObWnd( this);

	pWndInfo->GetFrame()->SetWindowText( Mstr( "WINDOW_01"));			// �E�B���h�E�^�C�g���\��

	// �N���X�w�A�[�J�[�\���̏�����
	MC::Window::InitCrossHair();
	// �h���b�M���O�̏�����
	MC::Window::InitDragging();
	// ���ރq�b�g�\���̏�����
	MC::Window::InitHitBuzai();

	//	�}�b�v���[�h��ݒ�
	MINT iOldMM = pWndInfo->SetMapMode( NULL);

	// �������[�c�b�̓��e����ʂɕ\��
	MC::WindowCtrl::DrawWnd( pWndInfo);

	// �N���X�w�A�[�J�[�\���\��
	MC::Window::ReDrawCrossHair();

	//	���o�[�o���h�}�`���ĕ\������
	MC::Window::ReDrawDragging();
	
	//	�q�b�g���ނ��ĕ\������
	MC::Window::ReDrawHitBzi();
	
	//	�}�b�v���[�h��߂�
	pWndInfo->m_pMemDC->SetMapMode( iOldMM);
	// �`�惁�b�Z�[�W�� CView::OnPaint() ���Ăяo���Ȃ��ł��������B
}

// CMCadView1 �`��

void CMCadView1::OnDraw(CDC* /*pDC*/)
{
	CMCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}


void CMCadView1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::LButtonDown( this, nFlags, point);

	CView::OnLButtonDown(nFlags, point);
}

void CMCadView1::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::LButtonUp( this, nFlags, point);

	CView::OnLButtonUp(nFlags, point);
}

void CMCadView1::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::RButtonDown( this, nFlags, point);

	CView::OnRButtonDown(nFlags, point);
}

void CMCadView1::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::RButtonUp( this, nFlags, point);

	CView::OnRButtonUp(nFlags, point);
}

void CMCadView1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	z_ptCurCursorD = point;
	
	MC::ViewInp::MouseMove( this, nFlags,  point);

	CView::OnMouseMove(nFlags, point);
}


void CMCadView1::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::MButtonDown( this, nFlags, point);

	CView::OnMButtonDown(nFlags, point);
}


void CMCadView1::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::MButtonUp( this, nFlags, point);

	CView::OnMButtonUp(nFlags, point);
}


BOOL CMCadView1::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::MouseWheel( this, nFlags, zDelta, z_ptCurCursorD);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMCadView1::OnSize(UINT nType, int cx, int cy)
{
	MINT	iMM_sv;
	CView::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B

	if (cx > 0 && cy > 0) {
		CPoint	ptMouthD( cx, cy);							// ��ʃT�C�Y(�\�����W)
		CPoint	ptMouthL = ptMouthD;

		CClientDC dc( this);

		iMM_sv = dc.SetMapMode( MMAPMODE);
		dc.DPtoLP( &ptMouthL);								// ��ʃT�C�Y(�_�����W)
		dc.SetMapMode( iMM_sv);

		MC::ViewInp::Size( this, ptMouthD, ptMouthL);		// �E�B���h�E�T�C�Y�ݒ�
	}
}

LRESULT CMCadView1::OnMyMessageStatusBar(WPARAM wParam, LPARAM lParam)
{
	MC::Msg::DispStatusBar();
	return 0;
}	

LRESULT CMCadView1::OnMyMessagePtsEdit(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdPartsEditInp( this);
	return 0;
}	


LRESULT CMCadView1::OnMyMessageGridNum(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdGridNumInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageOpt(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdOptInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageHist(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdHistInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageTenkai(WPARAM wParam, LPARAM lParam)
{
	MC::MCmdTenkaiInp( this);
	return 0;
}	

LRESULT CMCadView1::OnMyMessageKAttr(WPARAM wParam, LPARAM lParam)
{
	MC::z_mmIA.MmDialogKAttrDisp( this);
	return 0;
}	

// CMCadView1 ���


void CMCadView1::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCadView1::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CMCadView1::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMCadView1::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

//void CMCadView1::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CMCadView1::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	z_MCadApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMCadView1 �f�f

#ifdef _DEBUG
void CMCadView1::AssertValid() const
{
	CView::AssertValid();
}

void CMCadView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCadDoc* CMCadView1::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCadDoc)));
	return (CMCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCadView1 ���b�Z�[�W �n���h���[


BOOL CMCadView1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::Window::SetCursor( this);

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CMCadView1::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadView1::OnCancelMode()
{
	CView::OnCancelMode();

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
}


void CMCadView1::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	z_MCadApp.m_pMainFrame->m_pCurView = this;
}


int CMCadView1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B

	return 0;
}


void CMCadView1::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	CView::OnClose();
}


void CMCadView1::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::Char( this, nChar, nRepCnt, nFlags);

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMCadView1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::KeyDown( this, nChar, nRepCnt, nFlags);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMCadView1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	MC::ViewInp::KeyUp( this, nChar, nRepCnt, nFlags);

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


int CMCadView1::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	SetFocus();

	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CMCadView1::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CView::OnShowWindow(bShow, nStatus);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
}
