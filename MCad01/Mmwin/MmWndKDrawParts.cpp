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
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MmDefine.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MtInp.h"

#include "MdOpt.h"
#include "MdLib.h"

#include "MdHist.h"
#include "MmValid.h"

namespace MC
{

static	MINT			z_ign;

/////////////////////////////////////////////////////////////////////////////
//	�P�z�u���i��\������
void DrawPart( 
						msCod*		pCod,			// ���W�n
						MINT		iGpC,		// �\��
						mhPlcInfo	*pPlcEn
				);

/////////////////////////////////////////////////////////////////////////////
//	�z�u���i��\������
void WindowCtrl::MmWndKDrawPts(
						msCod*		pCod,			// ���W�n
						MINT		iKaiC,			// �K  	(1,2,3)
						MINT		iGpC			// �\��
				)
{
	MPOSITION	pos1;
	mhPlcInfo	*pPlcEn;
//	MsBitSet	*pOptv1, *pOptv2;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgLine2		LnPts;
	MgPoint2	ptPtsN;
	MgPoint2	ptW[2];
	MgPoint2	ptH;
	MgPoint2	ptK[4];
	MgVect2		vptH;
	MgVect2		vOffset = MgVect2( 0., 20.);
	
	DWORD		PtsTextColor;

	PtsTextColor = McSystemProperty::GetColor( MM_COLOR_GRID_TEXT);
	pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 100.f, MT_CENTER, MT_CENTER,
					   PtsTextColor, MgVect2( 1., 0.), vOffset, MT_FREESIZE);

	// �p�l����\������
	z_ign = 0;
	for ( pPlcEn = HaitiDb::MdGetHeadPts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextPts( &pos1)) {

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// �قȂ�K�̕��ނ͕\�����Ȃ�
//		if ( pPlcEn->GetPITpPts()->m_pGp->m_iCode != iGpC)
//			continue;											// �قȂ�\���̕��ނ͕\�����Ȃ�
		if ( pPlcEn->GetPTCdGp() != iGpC)
			continue;											// �قȂ�\���̕��ނ͕\�����Ȃ�

		if ( pPlcEn->IsPanel() || pPlcEn->IsKaiko()) {			// �p�l���܂��͊J��

			if ( !MmChkValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
				continue;
			DrawPart( pCod, iGpC, pPlcEn);
		}
	}

	PtsTextColor = McSystemProperty::GetColor( MM_COLOR_GRID_TEXT);
	pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 100.f, MT_LOWER, MT_CENTER,
					   PtsTextColor, MgVect2( 1., 0.), vOffset, MT_FREESIZE);

	// ���ތ`���\������
	MINT iDB = 0;												// Debug Trace�p
	for ( pPlcEn = HaitiDb::MdGetHeadPts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextPts( &pos1)) {

		iDB++;

		DWORD PtsLineColor;
		MINT iMdBziFig = 0;

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// �قȂ�K�̕��ނ͕\�����Ȃ�

//D		MUINT	*iOptv = pPlcEn->GetPIOpt1()->GetSOB();
//D		TRACE1( "MmWndKDrawPts(%d)		", iDB);
//D		if ( iOptv == 0)
//D			TRACE0( "pOptv_ON NULL		");
//D		else
//D			TRACE3( "pOptv_ON %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//D		iOptv = pPlcEn->GetPIOpt2()->GetSOB();
//D		if ( iOptv == 0)
//D			TRACE0( "pOptv_OFF NULL\n");
//D		else
//D			TRACE3( "pOptv_OFF %x, %x, %x\n", iOptv[0], iOptv[1], iOptv[2]);

		if ( pPlcEn->GetPTCdGp() != iGpC) {			// ��b��
			if ( pPlcEn->GetPTBr() == MP_BR_KISO) {
				if ( iKaiC == 1 && iGpC == MP_GP_YUKA) {	// �P�K���g�\���̏ꍇ�́A�ǐc�����ŕ\������
					iMdBziFig = 1;
					PtsLineColor = McSystemProperty::GetColor( MM_COLOR_KISOSIN);
				} else {
					continue;									// ��b�g�Ə��g�ȊO�͕\�����Ȃ�
				}
			} else if ( pPlcEn->GetPTBr() == MP_BR_KABE) {		// �ǂ�
				if ( iGpC == MP_GP_KABE) {					// �ǘg�g�\���̏ꍇ�͕\������
				} else {
					continue;
				}
			} else {											// ����
				continue;										// �قȂ�\���̕��ނ͕\�����Ȃ�
			}
		}

		if ( !MmChkValidParts( pPlcEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		if ( pPlcEn->GetPTBr() != MP_BR_PANEL) {		// �p�l���ȊO�̕��ނ�\��
			if ( iMdBziFig == 0) {
				DrawPart( pCod, iGpC, pPlcEn);				// ���ތ`���\��
			} else {
				pCod->SetLineAttr( MPS_DASHDOT, 1, PtsLineColor);		// ��_�����̐�����\��
				ptW[0] = MgPoint2C( pPlcEn->GetPIPlcIti( 0));
				ptW[1] = MgPoint2C( pPlcEn->GetPIPlcIti( 1));
				pCod->Line( MgLine2( ptW[0], ptW[1]));
//				pCod->Line( MgLine2( ptW[0], ptW[1]));
			}
		}
	}
}

#define		MC_PNLNO_HANKEI		170.f

/////////////////////////////////////////////////////////////////////////////
//	�P�z�u���i��\������
void DrawPart( 
						msCod*		pCod,		// ���W�n
						MINT		iGpC,		// �\��
						mhPlcInfo	*pPlcEn
				)
{
	MgLine2		LnPts;
	MgPoint2	ptPtsN;
	MINT		iKeijoF;
	MREAL		rWidthR, rWidth;
	MgVect2		VtWidthR, VtWidth;
	MgPoint2	ptW[2];
	MgVect2		VtW, VtUtW;
	MgPoint2	ptH;
	MgPoint2	ptK[4];
	MgVect2		vptH;
	MgVect2		vOffset = MgVect2( 0., 20.);
	
	MhZukei		*pZukei;

	DWORD		PtsLineColor;

	MCHAR		SGN[100];

	MINT		ic;

	ptW[0] = *(MgPoint2*)&(pPlcEn->GetPIPlcIti( 0));
	ptW[1] = *(MgPoint2*)&(pPlcEn->GetPIPlcIti( 1));

	// ���ނ̌`��\��
	VtW = ptW[1] - ptW[0];										// �c��
	VtUtW = MGeo::UnitizeV2( VtW);								// ���ނ̌`�����߂�

	// ���Ęg�p�̌`��쐬
	if ( pPlcEn->IsFrame()) {									// ���Ęg�p�̌`��쐬
		VtWidthR = (pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure()) * VtUtW.RotR90(); 
		VtWidth = pPlcEn->GetMbTWidth() * VtUtW.RotL90(); 
		ptH = ptW[0] + pPlcEn->GetPIPlcZure() * VtUtW;
		ptK[0] = ptH + pPlcEn->GetMbTHeightF() * VtUtW + VtWidthR;
		ptK[1] = ptH - pPlcEn->GetMbTHeightB() * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
		iKeijoF = 0;											// �`��Z�o��
		
	// �p�l���܂��͏�|�V��|�����E�J��
	} else if ( pPlcEn->IsPanel() || pPlcEn->IsKaiko()) {
		// ���E�V��
		if ( pPlcEn->IsYuka() || pPlcEn->IsTenjo()) {
			rWidthR = pPlcEn->GetPIMaeHosei();				// ��O���␳
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();		// ��O���␳ + ���s�� + ���s���␳
			iKeijoF = 2;

		// ����
		} else if ( pPlcEn->IsYane()) {
			rWidthR = pPlcEn->GetPIMaeHosei();				// ��O���␳
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();		// ��O���␳ + ���s�� + ���s���␳
			iKeijoF = 2;

		// ���̑�?
		} else {
			rWidthR = pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure(); 
			rWidth = pPlcEn->GetMbTWidth(); 
			iKeijoF = 3;
		}
	
	// ���U��
	} else {													// ���u���ނ̌`��쐬
		if ( pPlcEn->GetPIMbr() ) {
			rWidthR = pPlcEn->GetMbWidthR() + pPlcEn->GetPISinZure(); 
			rWidth = pPlcEn->GetMbWidth(); 
			iKeijoF = 1;
		} else {
			iKeijoF = 0;										// �`��Z�o��(�}�`�f�[�^�ɂ���)
		}
	}

	// ��`�`��쐬
	if ( iKeijoF != 0) {											// �`��Z�o
		VtWidthR = rWidthR * VtUtW.RotR90(); 
		VtWidth = rWidth * VtUtW.RotL90(); 
		ptK[0] = ptW[0] - pPlcEn->GetPILenHosei( 0) * VtUtW + VtWidthR;
		ptK[1] = ptW[1] + pPlcEn->GetPILenHosei( 1) * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
	}

	// ���F�̐ݒ�
	if ( iGpC == MP_GP_KABE && pPlcEn->IsKabe()) {
		PtsLineColor = McSystemProperty::GetColor( MM_COLOR_KABESEN);

	} else {
		PtsLineColor = pPlcEn->GetPTColor();
	}
	pCod->SetLineAttr( MPS_SOLID, 1, PtsLineColor);
	
	pZukei = pPlcEn->GetPIZukei();
	if ( pZukei) {												// �}�`�f�[�^�L��̏ꍇ�́A�����\��
		for ( ic=0; ic<pZukei->m_isNZukei; ic++) {
			pCod->Line( MgLine2C( pZukei->m_lnZukei[ic]));
		}
	
	} else {													// �}�`�f�[�^�Ȃ��̏ꍇ�͋��߂��`���\��
		pCod->Polygon( ptK, 4);
	}

	// ���ނ̒��L��\��

	// �p�l���̏ꍇ�̓p�l���ԍ���\��
	if ( iKeijoF == 2) {											// �p�l��
		MgPoint2 ptCenter = (ptK[0] + ptK[2]) / 2.f;
		MgVect2  vtL1 = ptK[2] - ptK[0];
		MgVect2  vtutL1 = MGeo::UnitizeV2( vtL1);
		MgVect2  vtL2 = ptK[3] - ptK[1];
		MgVect2  vtutL2 = MGeo::UnitizeV2( vtL2);

		pCod->Arc1( ptCenter, MC_PNLNO_HANKEI, 0., 0.);

		pCod->Line( ptCenter - MC_PNLNO_HANKEI * vtutL1, ptK[0]);
		pCod->Line( ptCenter - MC_PNLNO_HANKEI * vtutL2, ptK[1]);
		pCod->Line( ptCenter + MC_PNLNO_HANKEI * vtutL1, ptK[2]);
		pCod->Line( ptCenter + MC_PNLNO_HANKEI * vtutL2, ptK[3]);

		Msprintf_s( SGN, Mstr( "%d"), pPlcEn->GetPIPanelNo());
//		Msprintf_s( SGN, Mstr( "%d"), 172);
		pCod->SetTextHeight( 130);
//		pCod->SetTextDirect( MgVect2( 1., 0));
		pCod->SetTextDirect( MgVect2( 1., 0.));
		pCod->Text( ptCenter + MgVect2( 0., -20.), SGN);
	}

	// �ǘg�g�ȊO�͕��ޒ��L��\��
	if ( iGpC != MP_GP_KABE) {
		ptPtsN = (ptK[3] + ptK[2]) * 0.5;
		pCod->SetTextDirect( VtW);
		Msprintf_s( SGN, Mstr( "%s %s %d"), pPlcEn->GetPTNmPts1(),
										 pPlcEn->GetMbCdMbr(), z_ign++);
		pCod->Text( ptPtsN, SGN);
	}
}

} // namespace MC