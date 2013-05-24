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

// MCadView2.cpp : CMCadView2 �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "MCad.h"
#endif
#include "M3View.h"
#include "MCadDoc.h"
#include "MCadView2.h"
#include "MmWnd.h"

namespace MC
{
void ShowError( int e);
} // namespace MC

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCadView2

IMPLEMENT_DYNCREATE(CMCadView2, CView)

BEGIN_MESSAGE_MAP(CMCadView2, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCadView2::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMCadView2 �R���X�g���N�V����/�f�X�g���N�V����

CMCadView2::CMCadView2()
{
}

CMCadView2::~CMCadView2()
{
}

BOOL CMCadView2::PreCreateWindow(CREATESTRUCT& cs)
{
	MINT	ist;
//E	if ( !CWnd::PreCreateWindow( cs))
//E		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor( NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);


	MC::WindowCtrl::MmWndSetWndC( 2, this);										// �E�B���h�E�Ǘ�
	ist = MC::WindowCtrl::MmWndKAddC();											// �E�B���h�E�Ǘ�
	_ASSERTE( ist == 0);														// �E�B���h�E�Ǘ�

//E	return TRUE;
	return CView::PreCreateWindow(cs);
}

void CMCadView2::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	SetWindowPos(&wndTopMost , 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE | SWP_NOZORDER);

//	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFind( this);					// �E�B���h�E�Ǘ�
	MC::MmWndInfo* pWndInfo = MC::WindowCtrl::MmWndKFindSyu( 2, MTHEIMENZU, 1, 1);	// �E�B���h�E�Ǘ�
	(pWndInfo->GetFrame())->SetWindowText(Mstr( "WINDOW_02"));	// �E�B���h�E�Ǘ�

	// �`�惁�b�Z�[�W�� CWnd::OnPaint() ���Ăяo���Ȃ��ł��������B

#if( DEBUG1)
	MoGlLib::DrawGLobject();
	SwapBuffers( m_pDC->m_hDC);    // Double buffer
#else

	m_M3View.OnPaint();
	if( FALSE == SwapBuffers( m_pDC->GetSafeHdc())) MC::ShowError(7);	// Orig
//	SwapBuffers( m_pDC->m_hDC);    // Double buffer
#endif
}


BOOL CMCadView2::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CMCadView2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MC::MgPoint3D	PtCtr;						// ���S���W

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//	DC�̐���
	m_pDC = new CClientDC( this);
	if( NULL == m_pDC ){
		MC::ShowError( 1);
		return FALSE;
	}
	m_M3View.OnCreate( m_pDC->m_hDC);

#if( DEBUG1)
	MoGlLib::SetDCPixelFormat( m_pDC->m_hDC);					// OpenGL�p��Pixel Format���w��
	m_GLRC = wglCreateContext( m_pDC->m_hDC);					// Rendering context�̐���
	wglMakeCurrent( m_pDC->m_hDC, m_GLRC);						// ���݂�context�ݒ�

	MoGlLib::InitializeOpenGL();								//3D�V�[��������������֐���p�ӂ���
	MoGlLib::MakeGLObject();									//3D�I�u�W�F�N�g�𐶐�����
#endif

	return 0;
}

void CMCadView2::OnDestroy()
{
	CView::OnDestroy();

	m_M3View.OnDestroy();

	if( m_pDC ) delete m_pDC;
}


BOOL CMCadView2::OnEraseBkgnd(CDC* pDC)
{
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CMCadView2::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

#if( DEBUG1)
	MoGlLib::ViewSetting(cx, cy);
#endif

	m_M3View.OnSize( nType, cx, cy);
}


void CMCadView2::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_iPtLast = point;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMCadView2::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CMCadView2::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint	iPtD;												// �}�E�X�ړ���	
	CRect	iRcWin;												// �E�B���h�E�̈� (�`��̈�)
	CPoint	iSzWin;												// �E�B���h�E�̕��ƍ���
	MC::MgVect3D	PtD( 0., 0., 0.);
	MC::MgVect3D	RtD( 0., 0., 0.);
	MREAL	SclD = 0.;

	if (!(nFlags & MK_LBUTTON) && !( nFlags & MK_RBUTTON))
		MQUIT;													// �}�E�X�̍��܂��͉E�{�^����������Ă��Ȃ��ꍇ�͖���

	GetClientRect( iRcWin);
	
	iPtD.x = ( point.x - m_iPtLast.x) * 2;						// �}�E�X�ړ���	
	iPtD.y = (LONG)MMDIRY * ( m_iPtLast.y - point.y) * 2;		// Y�͏オ�������ł���(��: 1024:�� �`�@0:��)

	if ( ( MGABS( iPtD.x) < 5) && ( MGABS( iPtD.y) < 5)) 
		MQUIT;													// ����ړ��ʖ����̏ꍇ�͖���

	iSzWin = CPoint( iRcWin.right - iRcWin.left,
					 iRcWin.bottom - iRcWin.top);  

	//	Ctrl + Left Button:   ���E�ړ��A�㉺�ړ�
	if ( nFlags & MK_CONTROL && nFlags & MK_LBUTTON) {
		PtD.x = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		PtD.y = (MREAL)iPtD.y / (MREAL)iSzWin.y;

	//	Ctrl + Right Button:   ____�A�O��ړ�
	} else if ( nFlags & MK_CONTROL && nFlags & MK_RBUTTON) {
		PtD.z = (MREAL)iPtD.y / (MREAL)iSzWin.y;

	//	Left Button:   �x����]�A�w����]
	} else 	if ( nFlags & MK_LBUTTON) {
		RtD.x = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		RtD.y = (MREAL)iPtD.y / (MREAL)iSzWin.y;

		RtD.z = ((MREAL)iPtD.y * ((MREAL)point.x / (MREAL)iSzWin.x * 2 - 1) +		// �O���̕��̂w����]�Ƃx����]�͂y����]
				(MREAL)iPtD.x * ((MREAL)point.y / (MREAL)iSzWin.y * 2 -1)) /		// �ɂ��e�����y�ڂ��l�ɂ���
				(MREAL)iSzWin.x;;													// ���� (������:�y���ɑ΂��ĉE��])

	//	Right Button:   �y��]�A�g��k��
	} else if ( nFlags & MK_RBUTTON) {
		RtD.z = (MREAL)iPtD.x / (MREAL)iSzWin.x;
		SclD  = (MREAL)iPtD.y / (MREAL)iSzWin.y;

		if ( point.y < (iRcWin.top + iRcWin.bottom)/2)								// �y����]�p�@��ʒ������
			RtD.z = - RtD.z;														// ��� (������:�y���ɑ΂��č���]) �ŁA
																					//			   (�y�����猩�ĉE��])
																					// ���� (������:�y���ɑ΂��ĉE��])
																					//			   (�y�����猩�č���])
	}

	static bool bFirst = true;										// �P�x�ڂ̓}�E�X�̈ړ��ʂ�����̂��߃X�L�b�v
	if ( !bFirst) {
		m_M3View.OnMouseMove( nFlags, PtD, RtD, SclD);				
	}
	bFirst = false;

	m_iPtLast = point;

	PostMessage(WM_PAINT);										// �ĕ\���̃��b�Z�[�W�𑗂菈���̏I����҂����Ɏ��ֈڂ�
exit:
	CView::OnMouseMove(nFlags, point);
}


void CMCadView2::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_iPtLast = point;
	SetCapture();

	CView::OnRButtonDown(nFlags, point);
}

void CMCadView2::OnRButtonUp(UINT nFlags, CPoint point)
{
//E	ClientToScreen(&point);
//E	OnContextMenu(this, point);

	ReleaseCapture();

	CWnd::OnRButtonUp(nFlags, point);

}

void CMCadView2::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_M3View.m_iFWire++;
	if (m_M3View.m_iFWire >= 5 || (nFlags != 24 && m_M3View.m_iFWire >= 3))
		m_M3View.m_iFWire = 0;
	PostMessage(WM_PAINT);										// �ĕ\���̃��b�Z�[�W�𑗂菈���̏I����҂����Ɏ��ֈڂ�

	CView::OnMButtonDown(nFlags, point);
}


void CMCadView2::OnMButtonUp(UINT nFlags, CPoint point)
{
	CView::OnMButtonUp(nFlags, point);
}

// CMCadView2 �f�f

#ifdef _DEBUG
void CMCadView2::AssertValid() const
{
	CView::AssertValid();
}

void CMCadView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCadDoc* CMCadView2::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCadDoc)));
	return (CMCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCadView2 ���b�Z�[�W �n���h���[

void CMCadView2::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	CView::OnClose();
}

// CMCadView2 �`��

void CMCadView2::OnDraw(CDC* /*pDC*/)
{
	CMCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

// CMCadView2 ���

void CMCadView2::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCadView2::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CMCadView2::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMCadView2::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

void CMCadView2::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	z_MCadApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

