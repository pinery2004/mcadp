//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmCursor.cpp
//
//		�E�B���h�E�\���֘A
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MmDefine.h"

#define	DLL_EXPORT_MC_WINDOW_DO
#include "MmLib.h"

#include "McSystemProperty.h"

namespace MC
{

static	bool		z_fDrawCrossCursor = FALSE;

static	CPoint			z_ptCurCrossHairL[2][2];
static	CPoint			z_ptLCurMouth;

static	MmWndInfo* 		z_pCurWndInfo = NULL;					// �N���X�w�A�[�J�[�\���\����J�����g�E�B���h�E

/////////////////////////////////////////////////////////////////////////////
//	�V�K�E�B���h�E�쐬���̏����� (�r���[�̏����\�����Ɏg�p)
//	�N���X�w�A�[�J�[�\�����\������Ă��Ȃ���Ԃł��鎖��ݒ肷��

void Window::InitCrossHair()
{
	z_fDrawCrossCursor = FALSE;
}

////////////////////////////////////////////////////////////////////////////
//  �J�[�\����ݒ肷��

MINT Window::SetCursor(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				) 
{
	MINT	ist = 1;
	MINT	iCursor;											// �E�B���h�E�̃J�����g�J�[�\���ԍ�

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKFindWnd( pWnd);

	if ( pWndInfo != 0) {

		iCursor = pWndInfo->m_iCursor;
		::SetCursor( AfxGetApp()->LoadCursor( iCursor));
		ist = 0;
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	�N���X�w�A�[�J�[�\������������

void Window::EraseCrossHair()
{
	if ( z_fDrawCrossCursor) {
		Window::DispCrossHair( -1, NULL, NULL);
		z_fDrawCrossCursor = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�N���X�w�A�[�J�[�\����\������

void Window::DrawCrossHair(
						MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
						CPoint		ptMouthL		// (I  ) �_�����W
				)
{
	if ( !z_fDrawCrossCursor) {
		Window::DispCrossHair( 1, pWndInfo, &ptMouthL);
		z_fDrawCrossCursor = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�N���X�w�A�[�J�[�\�����ĕ\������

void Window::ReDrawCrossHair()
{
	if ( !z_fDrawCrossCursor) {
		Window::DispCrossHair( 0, NULL, NULL);
		z_fDrawCrossCursor = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�N���X�w�A�[�J�[�\����\��/�ĕ\��/��������
MINT Window::DispCrossHair(
						MINT		ictl,			// (I  ) �\������	 1 : �\���A0:�ĕ\���A-1 : ����
						MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����(�\������ == 1) �܂��� NULL(�\������ <= 0)�@
						CPoint*		pptLMouth		// (I  ) �}�E�X�ʒu�_�����W(�\������ == 1) �܂��� NULL(�\������ <= 0)
				)
{
	if ( ictl == 1) {
		z_pCurWndInfo = pWndInfo;
		z_ptLCurMouth = *pptLMouth;
	}
	if ( z_pCurWndInfo == NULL)
		return 0;

	CClientDC	dc( z_pCurWndInfo->GetWnd());
	DWORD		rgbCursor = McSystemProperty::GetColor( MM_COLOR_CURSOR);
	CPen		CrossHairPen( PS_SOLID, 1, rgbCursor);
	CPen*		OldPen = dc.SelectObject( &CrossHairPen);

	MINT		iMapMode = z_pCurWndInfo->GetMapMode();
	MINT		iOldMM = dc.SetMapMode( iMapMode);

	dc.SetROP2( R2_XORPEN);

	if ( ictl >= 0) {
		MgMinMaxI2	iMinMaxL = z_pCurWndInfo->GetMinMaxL();
		MINT		iUpL = z_pCurWndInfo->GetUpL();								// �w�x�\���o�����X
//S		z_ptCurCrossHairL[0][0] = CPoint( z_ptLCurMouth.x, iMinMaxL.min.y * iUpL);
//		z_ptCurCrossHairL[0][1] = CPoint( z_ptLCurMouth.x, ( iMinMaxL.max.y+100) * iUpL);
//		z_ptCurCrossHairL[0][1] = CPoint( z_ptLCurMouth.x, iMinMaxL.max.y * iUpL);
//		z_ptCurCrossHairL[1][0] = CPoint( iMinMaxL.min.x, z_ptLCurMouth.y * iUpL);
//		z_ptCurCrossHairL[1][1] = CPoint( iMinMaxL.max.x, z_ptLCurMouth.y * iUpL);
		z_ptCurCrossHairL[0][0] = CPoint( z_ptLCurMouth.x, iMinMaxL.min.y * iUpL);
		z_ptCurCrossHairL[0][1] = CPoint( z_ptLCurMouth.x, iMinMaxL.max.y * iUpL);
		z_ptCurCrossHairL[1][0] = CPoint( iMinMaxL.min.x, z_ptLCurMouth.y * iUpL);
		z_ptCurCrossHairL[1][1] = CPoint( iMinMaxL.max.x, z_ptLCurMouth.y * iUpL);
	}
	dc.Polyline( z_ptCurCrossHairL[0], 2);										// 		�c��
	dc.Polyline( z_ptCurCrossHairL[1], 2);										// 		����

	dc.SetMapMode( iOldMM);
	dc.SelectObject( OldPen);
	return 1;
}

} // namespace MC