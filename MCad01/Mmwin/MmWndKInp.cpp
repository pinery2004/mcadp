//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmWndKInp.cpp
//
//		�E�B���h�E���͊֘A
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMatD.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#define DLL_EXPORT_MC_WINDOWCTRL_DO
#include "MmWnd.h"
#include "MhDefParts.h"

#define DLL_EXPORT_MC_VIEWINP_DO
#define DLL_EXPORT_MC_WINDOW_DO
#include "MmLib.h"
#include "MmPrompt.h"

#include "MtAskForPoint.h"
#include "MtDefine.h"
#include "MhPlcPartsLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�R�}���h���j���[����
void CmdCtrl::XqtMenuCmd(
						MINT		i_idCmd			// �R�}���hID
				) 
{
	MtSendMessage( WM_CMDMENUP, i_idCmd, NULL);
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���_�E������
MINT ViewInp::LButtonDown(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �h���b�M���O�Y�[������
	if ( CONTROL_FLAGS(nFlags)) {								// �R���g���[���L�[
		if ( pWndInfo->GetDrag()) {
			if ( pWndInfo->GetDrag()->GetMotion() == ZOOM_WAIT) {
				pWndInfo->GetDrag()->SetMotion( ZOOM);
//				pWndInfo->GetDrag()->SetStartPt( ptMouthR);		// �Y�[���̒��S�����{�^���_�E���ʒu�ɂ���
																// �R�����g�ɂ���ƃR���g���[���L�[����������
																// �ŏ��̍��{�^���_�E���ʒu�ɂ���
				pWndInfo->GetDrag()->SetLastPt( ptMouthR);		// ���{�^���A�b�v�ł̃}�E�X�̈ړ��ʂ𖳂��ɂ���
			} else {
				pWndInfo->DeleteDrag();
			}
		}
		if ( pWndInfo->GetDrag() == NULL) {
			pWndInfo->SetDrag( new MmDragZoom( pWndInfo, ptMouthR));
		}
// 070907		return ist;
	}

	// �R�}���h�L���[
	MtSendMessage( WM_LBUTTONDOWN, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���A�b�v����
MINT ViewInp::LButtonUp(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo* pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	// �h���b�M���O�Y�[������
	if ( pWndInfo->GetDrag()) {
		if ( pWndInfo->GetDrag()->GetMotion() == ZOOM)
			pWndInfo->GetDrag()->SetMotion( ZOOM_WAIT);
		else
			pWndInfo->DeleteDrag();
	}

	// �R�}���h�L���[		add 070907
	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�
	MtSendMessage( WM_LBUTTONUP, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�E�{�^���_�E������

MINT ViewInp::RButtonDown(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT				ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �h���b�M���O�ړ�����J�n
	pWndInfo->DeleteDrag();

	if ( CONTROL_FLAGS(nFlags)) {
		pWndInfo->SetDrag( new MmDragPan( pWndInfo, ptMouthR));
// 070907		return ist;
	}

	// �R�}���h�L���[
	MtSendMessage( WM_RBUTTONDOWN, nFlags, &ptMouthR);

	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�E�{�^���A�b�v����
MINT ViewInp::RButtonUp(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;
	MmWndInfo* pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	// �h���b�M���O�ړ�����I��
	pWndInfo->DeleteDrag();

	// �R�}���h�L���[		add 070907
	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�
	MtSendMessage( WM_RBUTTONUP, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���_�u���N���b�N����
MINT ViewInp::LButtonDblClk(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �R�}���h�L���[
	MtSendMessage( WM_LBUTTONDBLCLK, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�E�{�^���_�u���N���b�N����
MINT ViewInp::RButtonDblClk(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �R�}���h�L���[
	MtSendMessage( WM_RBUTTONDBLCLK, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���_�u���N���b�N����
MINT ViewInp::MButtonDblClk(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �R�}���h�L���[
	MtSendMessage( WM_MBUTTONDBLCLK, nFlags, &ptMouthR);
	return ist;
}

static	bool	z_fDispSelParts;					// �}�E�X�őI�𕔍ނ̕\���t���O
static	MINT	z_iCdBuzai;							// �}�E�X�őI��Ώۂ̕��ރR�[�h

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�I�𕔍ނ̕\������
void Window::SetDispSelParts(
						MINT 		iCdBuzai		// (I  ) �}�E�X�őI��Ώۂ̕��ރR�[�h�ANULL(�S)�A�܂��� -1(��\��)
				) 
{
	if ( iCdBuzai >= 0) {
		z_fDispSelParts = true;
		z_iCdBuzai = iCdBuzai;
	} else {
		z_fDispSelParts = false;
		z_iCdBuzai = NULL;
		Window::EraseHitBzi();
		Window::ResetDispHitBzi();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�}�E�X�I�𕔍ނ��ĕ\������
void Window::ReDrawHitBzi()
{
	if ( z_fDispSelParts) {
		Window::ReDispHitBzi();
	}
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�ړ�����
MINT ViewInp::MouseMove(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
// 070907	MINT		ist = 1;
	MINT		ist = 0;
//E	MCHAR		strPtMouthR[20];
	CPoint		ptMouthL;
	MgPoint2D	ptMouthR;
	MgPolyg2D	pgHitBzi;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MINT iOldMM = pWndInfo->SetMapMode( NULL);

	ptMouthL = pWndInfo->DPtoLP( ptMouthD);						// �_�����W�֕ϊ�
	ptMouthR = pWndInfo->LPtoRP( ptMouthL);						// �����W�֕ϊ�

	pWndInfo->SetCurMousePtL( ptMouthL);						// �E�B���h�E�Ǘ����̌��݂̃}�E�X�ʒu��ݒ�

	// �h���b�M���O����
// 070907	if ( pWndInfo->GetDrag() && !pWndInfo->GetDrag()->m_bContinuousOrbitStarted) {
	if ( pWndInfo->GetDrag()) {
		pWndInfo->GetDrag()->Continue( pWndInfo, ptMouthR);		// �h���b�M���O����
	}
	// �N���X�w�A�[�J�[�\���\��
	Window::EraseCrossHair();
//UTy	Window::DrawCrossHair( pWndInfo, ptMouthL);		//UT01���̍s��ǉ�����ƃJ�[�\���ړ��̃��X�|���X�������Ȃ�
//	Window::EraseCrossHair();
//	Window::DrawCrossHair( pWndInfo, ptMouthL);		//UT01���̍s��ǉ�����ƃJ�[�\���ړ��̃��X�|���X�������Ȃ�
	// ���o�[�o���h�}�`�\��
	Window::EraseDragging();
	Window::DrawDragging( pWndInfo, ptMouthR);
	// �q�b�g���ތ`��\��
	if ( z_fDispSelParts) {
		if ( mhHaitiIn::SrchBuzai( pWndInfo, ptMouthR, z_iCdBuzai, &pgHitBzi)) {
			Window::DrawHitBzi( pWndInfo, &pgHitBzi);
		} else {
			Window::EraseHitBzi();
		}
	}

//E	// �X�e�C�^�X�o�[�Ƀ}�E�X�ʒu���W�\��
//	Msprintf_s(strPtMouthR, Mstr( " %6.0f: %6.0f"),
//						  ptMouthR.x, ptMouthR.y);
//	Msg::DispSelStatusBar( MC_STSBAR_COORDINATE, strPtMouthR);						// �X�e�C�^�X�o�[�փ}�E�X���W��\��
//
	pWndInfo->GetMemDC()->SetMapMode( iOldMM);
//070907	ist = 0;

	// �R�}���h�L���[		add 070907
//G	MtSendMessage( WM_MOUSEMOVE, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���_�E������
MINT ViewInp::MButtonDown(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

// 070907	MINT iOldMM = pWndInfo->SetMapMode( NULL);
	
	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �h���b�M���O�ړ�����
	pWndInfo->DeleteDrag();
	pWndInfo->SetDrag( new MmDragPan( pWndInfo, ptMouthR));

// 070907	pWndInfo->GetMemDC()->SetMapMode( iOldMM);

	// �R�}���h�L���[		add 070907
	MtSendMessage( WM_MBUTTONDOWN, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X���{�^���A�b�v����
MINT ViewInp::MButtonUp(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				) 
{
	MINT				ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	// �h���b�M���O�ړ�����I��
	pWndInfo->DeleteDrag();

	// �R�}���h�L���[		add 070907
	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�
	MtSendMessage( WM_MBUTTONUP, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�E�X�z�C�[����]����
MINT ViewInp::MouseWheel(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT 		nFlags,			// (I  ) 
						short		zDelta,			// (I  ) 
						CPoint		ptMouthD		// (I  ) �\�����W
				)
{
	MINT		ist = 0;

	MmWndInfo*	pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	MgPoint2D	ptMouthR = pWndInfo->DPtoRP( ptMouthD);			// �����W�֕ϊ�

	// �h���b�M���O�Y�[������J�n
	pWndInfo->DeleteDrag();
	pWndInfo->SetDrag( new MmDragZoom( pWndInfo, ptMouthR));

	// �h���b�M���O�Y�[������
	MgMinMaxR2D rMinMaxR = pWndInfo->GetMinMaxRS();
	MREAL dHeight = rMinMaxR.GetHgt() / 10;
	if ( zDelta < 0)
		dHeight = - dHeight;

//	ptMouthR += MgVect2D( 0., dHeight);
//	pWndInfo->GetDrag()->Continue( pWndInfo, ptMouthR);
	// change 070907
	MgPoint2D	ptMouthRW = ptMouthR + MgVect2D( 0., dHeight);
	pWndInfo->GetDrag()->Continue( pWndInfo, ptMouthRW);

	// �h���b�M���O�ړ�����I��
	pWndInfo->DeleteDrag();

	// �R�}���h�L���[		add 070907
	MtSendMessage( WM_MOUSEWHEEL, nFlags, &ptMouthR);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�̃T�C�Y�ݒ�
void ViewInp::Size(									// (  O) �X�e�C�^�X�@0 : ����  1 : �G���[
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						CPoint		ptMouthD,		// (I  ) ��ʃT�C�Y(�\�����W)
						CPoint		ptMouthL		// (I  ) ��ʃT�C�Y(�_�����W)
				)
{
	MmWndInfo* pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);

	pWndInfo->SetWinD( 0, 0, ptMouthD.x, ptMouthD.y);				// �\����ʑ��g��ݒ�
	pWndInfo->SetWinL( 0, 0, ptMouthL.x, ptMouthL.y);				// �_���\����ʑ��g��ݒ�
	pWndInfo->SetMinMaxRS( pWndInfo->GetMinMaxGA( pWndInfo));		// �����W(Min/Max)
	pWndInfo->SetMat();												// ���W�ϊ��p�}�g���b�N�X�̐ݒ�

	pWndInfo->FreeMDC();

//	Window::ResetDispHitBzi();
//	Window::InitHitBuzai();

	WindowCtrl::DrawWndMDC( pWndInfo);
}

/////////////////////////////////////////////////////////////////////////////
//  �L�[�{�[�h�L�����N�^���͏���
MINT ViewInp::Char(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT		nChar,			// (I  )
						UINT		nRepCnt,		// (I  )
						UINT 		nFlags			// (I  ) 
				)
{
	MINT	ist = 0;
	MINT	iChar[2];

	// �R�}���h�L���[
	iChar[0] = nChar;											// Virtual-Key Cords 
	iChar[1] = nRepCnt;
	MtSendMessage( WM_CHAR, nFlags, (MgPoint2D *)iChar);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �L�[�{�[�h�L�[�A�b�v����
MINT ViewInp::KeyUp(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT		nChar,			// (I  )
						UINT		nRepCnt,		// (I  )
						UINT 		nFlags			// (I  ) 
				)
{
	MINT		ist = 0;
	MmWndInfo*	pWndInfo;
	MINT	iChar[2];

	// �R���g���[���L�[�̃A�b�v�Ȃ�h���b�M���O����I��
	if ( nChar == 17) {
		pWndInfo = WindowCtrl::GetWndInfoObWnd( pWnd);
		pWndInfo->DeleteDrag();
	}

	// �R�}���h�L���[		add 070907
	iChar[0] = nChar;											// Virtual-Key Cords 
	iChar[1] = nRepCnt;
	MtSendMessage( WM_KEYUP, nFlags, (MgPoint2D *)iChar);
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �L�[�{�[�h�L�[�_�E������
MINT ViewInp::KeyDown(
						CWnd*		pWnd,			// (I  ) �E�B���h�E�̃C���X�^���X
						UINT		nChar,			// (I  )
						UINT		nRepCnt,		// (I  )
						UINT 		nFlags			// (I  ) 
				)
{
	MINT		ist = 0;
	MINT		iChar[2];

	// �R�}���h�L���[		add 070907
	iChar[0] = nChar;											// Virtual-Key Cords 
	iChar[1] = nRepCnt;
	MtSendMessage( WM_KEYDOWN, nFlags, (MgPoint2D *)iChar);
	return ist;
}

} // namespace MC
