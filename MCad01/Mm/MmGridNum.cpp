//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����
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
#include "MmDrag.h"
#define DLL_EXPORT_GRIDNUM_DO
#include "MmGridNum.h"
#define DLL_EXPORT_MC_WINDOWCTRL_DO
#include "MmWnd.h"
#include "MmDefine.h"
#include "MmLib.h"
#include "McSystemProperty.h"

namespace MC
{

//static CMmDialogGrid*	z_pDlgGrid = NULL;						// �O���b�h�_�C�A���O
static MINT				z_nGridI[4] = { 16, -3, -3, 17};

/*
/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX����
void WindowCtrl::MmGridNumInp		(
						CWnd*		pWnd						// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if ( z_pDlgGrid) {
		z_pDlgGrid->BringWindowToTop();
	} else {
		z_pDlgGrid = new CMmDialogGrid( pWnd);
	}
}
*/
/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ݒ�	�i�V���O���O���b�h�p�j
void WindowCtrl::MmGridNumSet(
						MINT*		nGrid						// (I  ) �O���b�h���i�k�A���A��A���j�܂��� NULL(�����ݒ�)
				)
{
	MmWndInfo*	pWndInfo;
	MINT*		pnGrid;
//	MINT		nGridI[4] = { 16, -3, -3, 17};
	MINT		ic1;

	pWndInfo = WindowCtrl::MmWndKGetCurWnd();							// �J�����g�E�B���h�E�擾
	if ( pWndInfo == NULL)
		MQUIT;

	if ( nGrid == NULL)
		pnGrid = z_nGridI;										// �O���b�h��������
	else {
		pnGrid = nGrid;											// �w��̃O���b�h���ɐݒ�
		for ( ic1=0; ic1<4; ic1++)
			z_nGridI[ic1] = nGrid[ic1];
	}

//	if ( z_pDlgGrid != NULL) z_pDlgGrid->SetSpinGridNum( pnGrid);
	pWndInfo->SetGridNum( pnGrid);
exit:;
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ǂݍ���	�i�V���O���O���b�h�p�j
void WindowCtrl::MmGridNumGet(
						MINT*		nGrid						// (I  ) �O���b�h���i�k�A���A��A���j
				)
{
	MmWndInfo*	pWndInfo;

	pWndInfo = WindowCtrl::MmWndKGetCurWnd();							// �J�����g�E�B���h�E�擾
	if ( pWndInfo == NULL) MQUIT;

	pWndInfo->GetGridNum( nGrid);
exit:;
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX�\�����s
void WindowCtrl::MmGridNumXqt()
{
	MmWndInfo*	pWndInfo;

	pWndInfo = WindowCtrl::MmWndKGetCurWnd();							// �J�����g�E�B���h�E�擾
	if ( pWndInfo == NULL)
		MQUIT;

	pWndInfo->SetMinMaxRS( pWndInfo->GetMinMaxGA( pWndInfo));
	pWndInfo->SetMat();
	
	WindowCtrl::MmWndKDrawMDC( pWndInfo);

	pWndInfo->GetWnd()->PostMessage(WM_PAINT);

exit:;
//	Window::CurWndFocus();										// �Z���W�J�ŏZ�ˑI����2�x�̑I�𖈂�1�x�ύX�ƂȂ�R�����g��
}
/*
/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX�L�����Z��
void WindowCtrl::MmGridNumCancel()
{
	if ( z_pDlgGrid)
//		z_pDlgGrid->SendMessage(WM_CLOSE);
		z_pDlgGrid->PostMessage(WM_CLOSE);
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX�I��
void WindowCtrl::MmGridNumEnd()
{
	z_pDlgGrid = NULL;
}
*/
/////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
MmGridNum::MmGridNum()
{
	static MINT nGrid[4];
	MgMinMaxR2	rMinMaxG;

	nGrid[0] = mcs::GetInt( MM_INT_GRID_N);
	nGrid[1] = mcs::GetInt( MM_INT_GRID_W);
	nGrid[2] = mcs::GetInt( MM_INT_GRID_S);
	nGrid[3] = mcs::GetInt( MM_INT_GRID_E);

	m_bFlgDrawG = TRUE;
	m_PtOriginG = MgPoint2( 0., 0.);
	m_PichG[0][0] = m_PichG[1][0] = mcs::GetReal( MM_REAL_PITCH);
	
	SetGridNum( nGrid);
}
/*
// �}���`�O���b�h�p

/////////////////////////////////////////////////////////////////////////////
//	�c���̃O���b�h���̐ݒ�
void MmGridNum::SetNumG( MINT nGrid[2][MGRID_GRP_MAX])
{
	MINT	ic1, ic2;
	
	for ( ic1=0; ic1<2; ic1++)
		for ( ic2=0; ic2<m_nGrpG[0]; ic2++)
			m_nGrid[ic1][ic2] = nGrid[ic1][ic2];
}

/////////////////////////////////////////////////////////////////////////////
//	�c���̃O���b�h�����擾����
void MmGridNum::GetNumG( MINT nGrid[2][MGRID_GRP_MAX])
{
	MINT	ic1, ic2;
	
	for ( ic1=0; ic1<2; ic1++)
		for ( ic2=0; ic2<m_nGrpG[0]; ic2++)
			nGrid[ic1][ic2] = m_nGrid[ic1][ic2];
}

/////////////////////////////////////////////////////////////////////////////
//	�c���̃O���b�h�Ԋu�̐ݒ�
void MmGridNum::SetPichG( MREAL PichG[2][MGRID_GRP_MAX])
{
	MINT	ic1, ic2;
	
	for ( ic1=0; ic1<2; ic1++)
		for ( ic2=0; ic2<m_nGrpG[0]; ic2++)
			m_PichG[ic1][ic2] = PichG[ic1][ic2];
}

/////////////////////////////////////////////////////////////////////////////
//	�c���̃O���b�h�Ԋu���擾����
void MmGridNum::GetPichG( MREAL PichG[2][MGRID_GRP_MAX])
{
	MINT	ic1, ic2;
	
	for ( ic1=0; ic1<2; ic1++)
		for ( ic2=0; ic2<m_nGrpG[0]; ic2++)
			PichG[ic1][ic2] = m_PichG[ic1][ic2];
}
*/
/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ݒ�	�i�V���O���O���b�h�p�j
void MmGridNum::SetGridNum(
						MINT*		i_nGrid		// �O���b�h���i�k�A���A��A���j
				)
{
	m_nGrpG[0] = m_nGrpG[1] = 1;

	m_iMinG[0] = i_nGrid[1];
	m_nGrid[0][0] = i_nGrid[3] - i_nGrid[1];

	m_rMinMaxG.min.x = m_PichG[0][0] * m_iMinG[0] + m_PtOriginG.x; 
	m_rMinMaxG.max.x = m_rMinMaxG.min.x + m_PichG[0][0] * m_nGrid[0][0]; 

	m_iMinG[1] = i_nGrid[2];
	m_nGrid[1][0] = i_nGrid[0] - i_nGrid[2];

	m_rMinMaxG.min.y = m_PichG[1][0] * m_iMinG[1] + m_PtOriginG.y; 
	m_rMinMaxG.max.y = m_rMinMaxG.min.y + m_PichG[1][0] * m_nGrid[1][0];
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ǂݍ���	�i�V���O���O���b�h�p�j
void MmGridNum::GetGridNum(
						MINT*	o_nGrid		// �O���b�h���i�k�A���A��A���j
				)
{

	o_nGrid[1] = m_iMinG[0];
	o_nGrid[3] = m_iMinG[0] + m_nGrid[0][0];

	o_nGrid[2] = m_iMinG[1];
	o_nGrid[0] = m_iMinG[1] + m_nGrid[1][0];
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h�\�����MINMAX�Z�o	�i�V���O���O���b�h�p�j
//	�O���b�hMinMax�̗̈�Ɏ��͂̋󂫂��������̈���擾����
MgMinMaxR2 MmGridNum::GetMinMaxGA(
						msCod*		pCod
				)
{
	MgMinMaxR2	rMinMaxG = MgMinMaxR2(0., 0., 1., 1.);

	MREAL		GridHeight;
	MREAL		GridAki;
	MREAL		rHosei;

	MINT		iStX;												// �E�B���h�E�̎n�_�w���W
	MINT		iStY;												// �E�B���h�E�̎n�_�x���W
	MINT		iWidth;												// �E�B���h�E�̕�
	MINT		iHeight;											// �E�B���h�E�̍���

	pCod->GetWinL( &iStX, &iStY, &iWidth, &iHeight);

	MgVect2		Haba;
	MgMinMaxR2	Waku;

	GridHeight	= mcs::GetReal( MM_REAL_GRID_HEI) * 20.f;	// �O���b�h��������
	GridAki		= mcs::GetReal( MM_REAL_GRID_AKI);			// �O���b�h�g�\����
	rHosei		= MGMAX( m_nGrid[0][0] / (MGeo::Abs( iWidth) / 1300.f),
						 m_nGrid[1][0] / (MGeo::Abs( iHeight) / 1170.f));
	GridHeight	*= rHosei;											// �O���b�h��������
	GridAki		*= rHosei;											// �O���b�h�g�\����

	rMinMaxG = GetMinMaxG();

	Haba = rMinMaxG.max - rMinMaxG.min;
	Waku.min.x = - ((GridAki + GridHeight));		// �O���b�h�󂫂ƕ������������O���b�h���ŕ␳
	Waku.min.y = - ((GridAki + GridHeight));		// �O���b�h�󂫂ƕ������������O���b�h���ŕ␳
	Waku.max.x = GridAki;
	Waku.max.y = GridAki;

	rMinMaxG.min += Waku.min;
	rMinMaxG.max += Waku.max;

	return rMinMaxG;
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h��\������
void MmGridNum::DrawGrid(
						MmWndInfo*	pWndInfo,
						msCod*		pCod
				)
{
	MREAL		GridSpace;
	MREAL		GridHeight;
	MREAL		GridAki;

	MgVect2		Haba;
	MgVect2		vOffset;

	MgLine2		LnGrid;
	MgPoint2	PtGridN;
	MINT		ic1, ic2;
	MINT		ign;
	DWORD		GridLineColor;
	DWORD		GridTextColor;
	MCHAR		SGN[5];

	MREAL		rOnePt = pCod->LPtoRP( MINT( pCod->DPtoLP( 1))); 

	MgMinMaxR2	rMinMaxG = pWndInfo->GetMinMaxG();					// �O���b�h�\���̈�擾
	
	MgMinMaxI2	rMinMaxGA = pCod->GetMinMaxL();						// �_�����WMinMax�擾
	MgPoint2	ptGAMin = pCod->LPtoRP( rMinMaxGA.min);				// �\���̈�̍ŏ������W�����߂�

	GridSpace	= mcs::GetReal( MM_REAL_GRID_SPC);			// �O���b�h�ԍ��\����
	GridHeight	= mcs::GetReal( MM_REAL_GRID_HEI) * 20.f;	// �O���b�h��������
	GridAki		= mcs::GetReal( MM_REAL_GRID_AKI);			// �O���b�h�g�\����

	Haba = rMinMaxG.max - rMinMaxG.min;
	vOffset.x = pCod->LPtoRP( MINT( GridAki + GridHeight)) * 1.53f;	// �O���b�h�󂫂ƕ�����������␳
	vOffset.y = pCod->LPtoRP( MINT( GridAki + GridHeight)) * 1.28f;	// �O���b�h�󂫂ƕ�����������␳

	GridLineColor = mcs::GetColor( MM_COLOR_GRID_LINE);
	GridTextColor = mcs::GetColor( MM_COLOR_GRID_TEXT);

	// �c�̃O���b�h����\��	

	LnGrid.p[0].y = m_rMinMaxG.min.y;
	LnGrid.p[1].y = m_rMinMaxG.max.y;

	if ( MGeo::GE( LnGrid.p[0].y, ptGAMin.y + vOffset.y)) {
		// �O���b�h�ԍ��\���󂫂���̏ꍇ�́A�ŏ��O���b�h�l��艺�i-GridSpace�j�ɃO���b�h�ԍ���\��
		PtGridN.y = LnGrid.p[0].y;
		pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 10.f, MT_UPPER, MT_CENTER, GridTextColor,
							   MgVect2( 1., 0.), MgVect2( 0., - GridSpace), MT_FIXEDSIZE);
	} else {
		// �O���b�h�ԍ��\���󂫂Ȃ��̏ꍇ�́A�\���G���A�̉��[����iGridSpace�j�ɃO���b�h�ԍ���\��
		PtGridN.y = ptGAMin.y;
		pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 10.f, MT_LOWER, MT_CENTER, GridTextColor,
							   MgVect2( 1., 0.), MgVect2( 0., GridSpace), MT_FIXEDSIZE);
	}

	ign = m_iMinG[0];
	LnGrid.p[0].x = LnGrid.p[1].x = m_rMinMaxG.min.x;
	for ( ic1=0; ic1<m_nGrpG[0]; ic1++) {
		for ( ic2=0; ic2<m_nGrid[0][ic1]; ic2++) {
			if ( ic2==0 || (( ic2 + m_iMinG[0]) % 5) == 0) {
				pCod->SetLineAttr( MPS_SOLID, 1, GridLineColor, MT_FIXEDSIZE);
			} else {
				pCod->SetLineAttr( MPS_DOT, 1, GridLineColor, MT_FIXEDSIZE);
			}
			pCod->Line( LnGrid);
			PtGridN.x = LnGrid.p[0].x;
			Msprintf_s( SGN, Mstr( "%d"), ign++);
			pCod->Text( PtGridN, SGN);

			LnGrid.p[0].x = LnGrid.p[1].x = LnGrid.p[0].x + m_PichG[0][ic1];
		}
	}
	pCod->SetLineAttr( MPS_SOLID, 1, GridLineColor);
	pCod->Line( LnGrid);

	PtGridN.x = LnGrid.p[0].x;
	Msprintf_s( SGN, Mstr( "%d"), ign++);
	pCod->Text( PtGridN, SGN);

	// ���̃O���b�h����\��	

	LnGrid.p[0].x = m_rMinMaxG.min.x;
	LnGrid.p[1].x = m_rMinMaxG.max.x;

	if ( MGeo::GE( LnGrid.p[0].x, ptGAMin.x + vOffset.x)) {
		// �O���b�h�ԍ��\���󂫂���̏ꍇ�́A�ŏ��O���b�h�l��荶�i-GridSpace�j�ɃO���b�h�ԍ���\��
		PtGridN.x = LnGrid.p[0].x;
		pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 10.f, MT_CENTER, MT_RIGHT, GridTextColor,
							   MgVect2( 1., 0.), MgVect2( - GridSpace, 0.), MT_FIXEDSIZE);
	} else {
		// �O���b�h�ԍ��\���󂫂Ȃ��̏ꍇ�́A�\���G���A�̍��[���E�iGridSpace�j�ɃO���b�h�ԍ���\��
		PtGridN.x = ptGAMin.x;
		pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 10.f, MT_CENTER, MT_LEFT, GridTextColor,
							   MgVect2( 1., 0.), MgVect2( GridSpace, 0.), MT_FIXEDSIZE);
	}

	ign = m_iMinG[1];
	LnGrid.p[0].y = LnGrid.p[1].y = m_rMinMaxG.min.y;
	for ( ic1=0; ic1<m_nGrpG[1]; ic1++) {
		for ( ic2=0; ic2<m_nGrid[1][ic1]; ic2++) {
			if ( ic2==0 || (( ic2 + m_iMinG[1]) % 5) == 0) {
				pCod->SetLineAttr( MPS_SOLID, 1, GridLineColor, MT_FIXEDSIZE);
			} else {
				pCod->SetLineAttr( MPS_DOT, 1, GridLineColor, MT_FIXEDSIZE);
			}
			pCod->Line( LnGrid);

			PtGridN.y = LnGrid.p[0].y;
			Msprintf_s( SGN, Mstr( "%2d"), ign++);
			pCod->Text( PtGridN, SGN);

			LnGrid.p[0].y = LnGrid.p[1].y = LnGrid.p[0].y + m_PichG[1][ic1];
		}
	}
	pCod->SetLineAttr( MPS_SOLID, 1, GridLineColor);
	pCod->Line( LnGrid);

	PtGridN.y = LnGrid.p[0].y;
	Msprintf_s( SGN, Mstr( "%2d"), ign++);
	pCod->Text( PtGridN, SGN);
}

/////////////////////////////////////////////////////////////////////////////////
//////	�ۂ�
////void MmGridNum::Marume(
////				const	MgPoint2	&Pi,
////						MgPoint2*	pPo
////				)
////{
////	MINT		ist;
////	MgVect2		vtDis;
////	MREAL		rDis_2;
////	MINT		ic1, ic2;
////
////	MREAL		rDisMin_2;
////	MgPoint2	Po, P0;
////
////	MINT		iCdPlc;										// �z�u�R�[�h
////	MINT		iCdMarume;										// �O���b�h�ۂߕ����l
////	MgPoint2	PtGrid;
////	MgLine2		Lnm[2];
////	MGGLINE2( GLnk, 10);
////
////	MINT iKai = mtInpMode::GetKai();
////
////	iCdMarume = mtInpMode::GetComboCdMarume();
////	iCdPlc = mtHaitiIn::GetComboCdPlc();
////
////	if ( iCdPlc == MP_HAICD_KABESINZUKE ||
////		iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {									// �ǐc�t���ۂ߁@�܂��́@�����\�����t���ۂ�
////		// �t�߂̊ۂߑΏې��������߂�
////		if ( iCdPlc == MP_HAICD_KABESINZUKE) {									// �ǐc�t���ۂ߂̏ꍇ�́A�Ŋ�̕ǐc�����߂�
////			mtInput::GetMarumeKabeLine( iKai, Pi, &GLnk);
////		} else if ( iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {						// �����\�����t���ۂ߂̏ꍇ�́A�Ŋ�̉����\���������߂�
////			mtInput::MmGetMarumeYaneLine( iKai, Pi, &GLnk);
////		}
////		// �����{�̊ۂߑΏې������������ꍇ�͌�_���߂��ɂ���Ȃ炻�̌�_��Ԃ�
////		rDisMin_2 = MREALMAX;
////		if ( GLnk.m_n >= 2) {
////			for ( ic1=0; ic1<GLnk.m_n - 1; ic1++) {
////				for ( ic2=ic1+1; ic2<GLnk.m_n; ic2++) {
////					ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], GLnk.m_ln[ic2], &P0);
////					if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
////						vtDis = P0 - Pi;
////						rDis_2 =MGeo::Abs_2( vtDis);
////						if ( rDis_2 < rDisMin_2) {
////							rDisMin_2 = rDis_2;
////							Po = P0;
////						}
////					}
////				}
////			}
////		}
////		if ( rDisMin_2 < MC_MARUME_TOL * MC_MARUME_TOL)
////			MQUIT;
////	} else {
////		GLnk.m_n = 0;
////	}
////				
//////	iCdMarume = mtInpMode::GetComboCdMarume();
////
////	// �O���b�h�ۂ߂Ȃ��̏ꍇ
////	if ( iCdMarume == 0) {
////		if ( GLnk.m_n == 0) {
////			// �ǐc�ł̊ۂ߂Ȃ�(�܂��͌��̕ǂ��Ȃ�)�̏ꍇ�́A���͈ʒu�����̂܂ܕԂ�
////			*pPo = Pi;
////			return;
////		} else {
////			// �ǐc�ۂ߂ŕǂƂ̏d�Ȃ肠��̏ꍇ�́A�ł��߂��ǐc��̈ʒu��Ԃ�
////			rDisMin_2 = MREALMAX;
////			for ( ic1=0; ic1<GLnk.m_n; ic1++) {
////				MGeo::PerpPtLn2( Pi, GLnk.m_ln[ic1], &P0);
////				vtDis = P0 - Pi;
////				rDis_2 =MGeo::Abs_2( vtDis);
////				if ( rDis_2 < rDisMin_2) {
////					rDisMin_2 = rDis_2;
////					Po = P0;
////				}
////			}
////	        MQUIT;
////		}
////	}
////
////	// �O���b�h�ۂ߂���̏���
////	GetMarumeGridLine( iCdMarume, Pi, Lnm);
////	if ( GLnk.m_n == 0) {
////		// �ǐc�ł̊ۂ߂Ȃ�(�܂��͌��̕ǂȂ�)�̏ꍇ�́A�O���b�h�ۂ߈ʒu�����̂܂ܕԂ�
////		ist = MGeo::Intr2Ln2( Lnm[0], Lnm[1], pPo);
////		if ( !MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
////			*pPo = Pi;
////		}
////		return;
////	} else {
////		// �ǐc�ۂ߂ŕǂƂ̏d�Ȃ肠��̏ꍇ�́A�ǐc�ƃO���b�h���Ƃ̌�_�ōł��߂��ʒu��Ԃ�
////		rDisMin_2 = MREALMAX;
////		for ( ic1=0; ic1<GLnk.m_n; ic1++) {
////			for ( ic2=0; ic2<2; ic2++) {
////				ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], Lnm[ic2], &P0);
////				if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
////					vtDis = P0 - Pi;
////					rDis_2 = MGeo::Abs_2( vtDis);
////					if ( rDis_2 < rDisMin_2) {
////						rDisMin_2 = rDis_2;
////						Po = P0;
////					}
////				}
////			}
////		}
////		MQUIT;
////	}
////exit:
////	*pPo = Po;
////}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h�ۂߐ����擾����
void MmGridNum::GetMarumeGridLine(
						MINT		iCdMarume,
				const	MgPoint2	&Pi,
						MgLine2		*pLn
				)
{
	MgPoint2	PtGrid;
	MREAL		rMarumeGridP;
	MREAL		rDistMrmGrd, rDist;
	MINT		ic1, ic2, ic3;
	MgPoint2	Po;

	// �ۂߗL��̏ꍇ�́A���͈ʒu���ۂ߂ĕԂ�
	// �c�̃O���b�h�ۂ�	
	rDistMrmGrd = MREALMAX;
	PtGrid.x = m_rMinMaxG.min.x;
	for ( ic1=0; ic1<m_nGrpG[0]; ic1++) {
		rMarumeGridP = m_PichG[0][ic1] / iCdMarume;
		for ( ic2=0; ic2<m_nGrid[0][ic1]; ic2++) {
			for ( ic3=0; ic3<iCdMarume; ic3++) {
				rDist = MGABS( Pi.x - PtGrid.x);
				if ( rDist < rDistMrmGrd) {
					rDistMrmGrd = rDist;
					Po.x = PtGrid.x;
				}
				PtGrid.x += rMarumeGridP;
			}
		}
	}
	rDist = MGABS( Pi.x - PtGrid.x);
	if ( rDist < rDistMrmGrd) {
		rDistMrmGrd = rDist;
		Po.x = PtGrid.x;
	}
	pLn[0] = MgLine2( MgPoint2( Po.x, m_rMinMaxG.min.y), MgPoint2( Po.x, m_rMinMaxG.max.y));

	// ���̃O���b�h�ۂ�	
	rDistMrmGrd = MREALMAX;
	PtGrid.y = m_rMinMaxG.min.y;
	for ( ic1=0; ic1<m_nGrpG[1]; ic1++) {
		rMarumeGridP = m_PichG[1][ic1] / iCdMarume;
		for ( ic2=0; ic2<m_nGrid[1][ic1]; ic2++) {
			for ( ic3=0; ic3<iCdMarume; ic3++) {
				rDist = MGABS( Pi.y - PtGrid.y);
				if ( rDist < rDistMrmGrd) {
					rDistMrmGrd = rDist;
					Po.y = PtGrid.y;
				}
				PtGrid.y += rMarumeGridP;
			}
		}
	}
	rDist = MGABS( Pi.y - PtGrid.y);
	if ( rDist < rDistMrmGrd) {
		rDistMrmGrd = rDist;
		Po.y = PtGrid.y;
	}
	pLn[1] = MgLine2( MgPoint2( m_rMinMaxG.min.x, Po.y), MgPoint2( m_rMinMaxG.max.x, Po.y));
}

} // namespace MC