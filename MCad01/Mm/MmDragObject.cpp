//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����i���o�[�o���h�}�`�\���j
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MhDefParts.h"
#include "MsDefine.h"
#include "MmWnd.h"

#define DLL_EXPORT_MC_WINDOW_DO
#include "MmLib.h"
#include "McSystemProperty.h"
#include "MtAskForPoint.h"

#define		MAXDRAGGING		40
#define		MCREVOVRP		22

namespace MC
{

static	bool			z_fDragMode = false;					// �g���b�M���O���[�h
																// true : ON�Afalse : OFF

static	bool			z_fDrawDragging = FALSE;				// ���o�[�o���h�}�`�\�����t���O

static	MmWndInfo* 		z_pLDragWndInfo = NULL;
static	MINT			z_modeL = NULL;							// ���ݕ\�����̐}�`���
static	MINT			z_nLDragging;							// ���ݕ\�����̃|�����C�����_��(������+1)
static	CPoint			z_ptLDragging[MAXDRAGGING];				// ���ݕ\�����̃|�����C�����_�̘_�����W(������+1)

static	MmWndInfo* 		z_pRDragWndInfo = NULL;
static	MINT			z_modeR = NULL;							// ���͐}�`���
static	MINT			z_nRDragging;							// ���͍σ|�����C�����_��
static	MgPoint2		z_ptRDragging[MAXDRAGGING];				// ���͍σ|�����C�����_�̍��W

static	CPoint			z_ptLDragMouth;

/////////////////////////////////////////////////////////////////////////////
//	�V�K�E�B���h�E�쐬���̏����� (�r���[�̏����\�����Ɏg�p)
//	�r���[�̏����\�����Ƀ��o�[�o���h�}�`���\������Ă��Ȃ�����ݒ肷��

void Window::InitDragging()
{
	z_fDrawDragging = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	�h���b�M���O���[�h�I��

void Window::DragModeEnd()
{
	Window::EraseDragging();
	z_fDragMode = false;										// �g���b�M���O���[�h�I��
}

/////////////////////////////////////////////////////////////////////////////
//	�h���b�M���O���[�h�m�F

bool Window::GetDragMode()
{
	return z_fDragMode;
}

/////////////////////////////////////////////////////////////////////////////
//	���o�[�o���h�}�`����������

void Window::EraseDragging()
{
	if ( Window::GetDragMode() && z_fDrawDragging) {
		Window::DispDragging( -1, NULL, NULL);
		z_fDrawDragging = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���o�[�o���h�}�`��\������

void Window::DrawDragging(
						MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
						MgPoint2	ptMouthR		// (I  ) �}�E�X�ʒu�����W
				)
{
	if ( Window::GetDragMode() && !z_fDrawDragging) {
		Window::DispDragging( 1, pWndInfo, &ptMouthR);
		z_fDrawDragging = TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////
//	���o�[�o���h�}�`���ĕ\������
//	�r���|�C���g�̍��W�̓J�����g�̍��W�ϊ��}�g���b�N�X�ō��W�ϊ������_�����W��
//	�ŏI�|�C���g�̓J�����g�̃}�E�X�_�����W�ŕ`��

void Window::ReDrawDragging()
{
	if ( Window::GetDragMode()) {
		Window::DispDragging( 0, NULL, NULL);
		z_fDrawDragging = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���o�[�o���h�}�`��\�����ăh���b�M���O���[�h���J�n���A
//	�}�E�X�ɂč��W���͂���
//	���ɕ\������Ă����ꍇ�͂��̕\������������A�V���ɕ\������

MINT Window::DragObject(
						MINT		mode,			// (I  ) �h���b�M���O���̓��[�h
				const	void*		pFg,			// (I  ) �h���b�M���O���͍ςݍ��W
						MgPoint2*	ptGet			// (  O) �}�E�X�ʒu�����W
				)
{
	MINT		irt;
	MgPoint2*	pPtSt;
	MgPolyg2*	pPg;
	MINT		ic;

	// ���͍ύ��W�Ɠ_����ݒ肷��
	z_modeR = mode;

	switch( z_modeR) {
		case MC_RBND_LINE:										// Line
			pPtSt = (MgPoint2*)pFg;
			z_ptRDragging[0] = pPtSt[0];
			z_nRDragging = 1;
			break;
		case MC_RBND_RECT:										// Rectangle
			pPtSt = (MgPoint2*)pFg;
			z_ptRDragging[0] = pPtSt[0];
			z_nRDragging = 1;
			break;
		case MC_RBND_POLYGON:									// Polygon
			pPg = (MgPolyg2*)pFg;
			for ( ic=0; ic<pPg->m_n; ic++) {
				z_ptRDragging[ic] = pPg->m_p[ic];
			}
			z_nRDragging = pPg->m_n;
			break;
		case MC_RBND_PARALOG:									// Parallelogram
			pPtSt = (MgPoint2*)pFg;
			z_ptRDragging[0] = pPtSt[0];
			z_ptRDragging[1] = pPtSt[1];
			z_nRDragging = 1;
			break;
	}
	z_pRDragWndInfo = WindowCtrl::MmWndKGetCurWnd();						// ���o�[�o���h�}�`�\����J�����g�E�B���h�E��ݒ肷��
	z_fDragMode = true;											// ���o�[�o���h�}�`�\�����[�h�J�n

	Window::EraseDragging();
	Window::DrawDragging( z_pRDragWndInfo, z_pRDragWndInfo->GetCurMousePtR());
//S	irt = MtAskForPoint( NULL, NULL, ptGet);
	irt = MtAskForPoint( ptGet);

	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	���o�[�o���h�}�`��\��/�ĕ\��/��������
//		�\��: 

MINT Window::DispDragging(
						MINT		ictl,			// (I  ) �\������ 1 : �\���A0 : �ĕ\���A-1 : ����
						MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ���� �܂��� NULL
						MgPoint2*	pptRMouth		// (I  ) �}�E�X�ʒu�����W �܂��� NULL
				)
{
	MINT		ic;
	MINT		iUpL;											// �w�x�\���o�����X
	CPoint		rev( MCREVOVRP, MCREVOVRP);						// �h���b�O�\�������ƃO���b�h���Ƃ̏d�Ȃ�␳
	MgVect2 	v1, v2;

	if ( ictl == 1) {
		z_pLDragWndInfo = pWndInfo;
		z_modeL = z_modeR;
		z_nLDragging = z_nRDragging + 1;						// �\���_�� = ���͍ςݓ_�� + 1(�h���b�O�\���ŏI�_)
		z_ptLDragMouth = z_pLDragWndInfo->RPtoLP( *pptRMouth);
	}

	iUpL = z_pLDragWndInfo->GetUpL();							// �c���\���␳�l

	CClientDC	dc( z_pLDragWndInfo->GetWnd());
	DWORD		rgbCursor = mcs::GetColor( MM_COLOR_DRAGGING);
	CPen		CrossHairPen( PS_SOLID, 1, rgbCursor);
	CPen*		OldPen = dc.SelectObject( &CrossHairPen);

	MINT		iMapMode = z_pLDragWndInfo->GetMapMode();
	MINT		iOldMM = dc.SetMapMode( iMapMode);

	dc.SetROP2( R2_XORPEN);

	if ( ictl >= 0) {
		switch( z_modeL)  {
			case 1:																	// ����
				z_ptLDragging[0] = z_pLDragWndInfo->RPtoLP( z_ptRDragging[0]) + rev;
				z_ptLDragging[1] = CPoint( z_ptLDragMouth.x, z_ptLDragMouth.y * iUpL) + rev;
				break;
			case 2:																	// �����`
				z_ptLDragging[0] = z_pLDragWndInfo->RPtoLP( z_ptRDragging[0]) + rev;
				z_ptLDragging[2] = CPoint( z_ptLDragMouth.x, z_ptLDragMouth.y * iUpL) + rev;
				z_ptLDragging[1] = CPoint( z_ptLDragging[0].x, z_ptLDragging[2].y);
				z_ptLDragging[3] = CPoint( z_ptLDragging[2].x, z_ptLDragging[0].y);
				z_ptLDragging[4] = z_ptLDragging[0];
				z_nLDragging = 5;
				break;
			case 3:																	// ���
				for ( ic=0; ic<z_nRDragging; ic++)
					z_ptLDragging[ic] = z_pLDragWndInfo->RPtoLP( z_ptRDragging[ic]) + rev;
				if ( z_nLDragging == z_nRDragging + 1)
					z_ptLDragging[z_nRDragging] = CPoint( z_ptLDragMouth.x, z_ptLDragMouth.y * iUpL) + rev;

				if ( z_nLDragging > 2) {											// �\���\���_���R�_�ȏ�̏ꍇ�͋��\���ɂ���
					z_ptLDragging[z_nLDragging] = z_ptLDragging[0];
					z_nLDragging++;
				}
				break;
			case 4:																	// ���s�l�ӌ`
				z_ptLDragging[0] = z_pLDragWndInfo->RPtoLP( z_ptRDragging[0]) + rev;
				z_ptLDragging[1] = z_pLDragWndInfo->RPtoLP( z_ptRDragging[1]) + rev;
				z_ptLDragging[3] = CPoint( z_ptLDragMouth.x, z_ptLDragMouth.y * iUpL) + rev;
				z_ptLDragging[2] = z_ptLDragging[1] + z_ptLDragging[3] - z_ptLDragging[0];
				z_ptLDragging[4] = z_ptLDragging[0];
				z_nLDragging = 5;

				// �`�󂪈꒼���ɋ߂��ꍇ�͐����Q�{�ɊԈ���
				v1 = MgVect2C( z_ptLDragging[1] - z_ptLDragging[0]); 
				v1.SetUnitize();
				v2 = MgVect2C( z_ptLDragging[2] - z_ptLDragging[1]);
				v2.SetUnitize();
				if ( MGeo::Abs(v1 ^ v2) < 0.05) {
					if ( (v1 * v2) < 0) {
						z_ptLDragging[0] = z_ptLDragging[1];
						z_ptLDragging[1] = z_ptLDragging[2];
						z_ptLDragging[2] = z_ptLDragging[3];
					}
					z_nLDragging = 3;
				}
				break;
			default:
				;
		}
	}
	if ( z_nLDragging != 0)
		dc.Polyline( z_ptLDragging, z_nLDragging);					// �}�`����̏ꍇ�̓��o�[�o���h�}�`��\������
	if ( ictl == -1)
		z_nLDragging = 0;											// �폜��͌��ݕ\�����̐}�`�Ȃ��Ƃ���

	dc.SetMapMode( iOldMM);
	dc.SelectObject( OldPen);
	return 1;
}

} // namespace MC
