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
#include "MhDefParts.h"

#define DLL_EXPORT_MC_HAITIIN_DO
#include "MmLib.h"

#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MgGrp.h"
#include "MhRoof.h"
#include "MdLib.h"

#include "MhInpPlcParts.h"
//#include "MhPlcPartsLib.h"

#include "MdOpt.h"

#include "MdHist.h"
#include "MmValid.h"


#include	"McSystemProperty.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	������z�u����
MINT mhHaitiIn::RoofPlc(							// (  O) �X�e�C�^�X	0: ����A-1: �����z�u�G���[
				const	MgPolyg2D	&pgJim,			// (I  ) �n�����
				const	MgGInt		&GifInp,		// (I  ) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				const	MgPoint2D	&pth			// (I  ) �����_
				)
{
	MINT	ist = -1;
	MINT	ist1;
	MhRoofInfo	RoofEn;

	RoofEn.InitAllAtr();

	RoofEn.SetInpKai( z_mnIA.GetInpKai());
	RoofEn.SetAttr();
	RoofEn.SetJimCd( pgJim, GifInp, pth);
	RoofEn.CreateRfmForJim();
	ist1 = RoofEn.AdjustRfm1();
	if ( ist1 < 0)
		MQUIT;
//								RoofEn.Print( Mstr( "1112 mhHaitiIn::RoofPlc"));
	RoofEn.ConnectRfm();
//								RoofEn.Print( Mstr( "1113 mhHaitiIn::RoofPlc"));
	RoofEn.OffsetRfm();
	ist1 = RoofEn.AdjustRfm2();
	if ( ist1 < 0)
		MQUIT;
//								RoofEn.Print( Mstr( "1114 mhHaitiIn::RoofPlc"));
	RoofEn.CreateRfmZukei();

	HaitiDb::MdRoofAdd( &RoofEn, 1);
	ist = 0;
exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	������\������
void WindowCtrl::MmWndKDrawRoof(
						msCod*		pCod,			// ���W�n
						MINT		iKaiC,			// �K  	(1,2,3)
						MINT		iGpC			// �\��
				)
{
	MPOSITION	pos1;
	MhRoofInfo	*pRoofEn;
//	MUINT		*pOpt;

	MgLine2D		LnRoof;
	MgPoint2D	PtRoofN;
	MgPoint2D	PtW[2];
	MgPoint2D	PtK[4];
	MgVect2D		vPtH;
	MgVect2D		vOffset = MgVect2D( 0., 20.);

	DWORD		RoofLineColor;
	DWORD		RoofTextColor;

	MINT		ign;
	MINT		ic;

	if ( iGpC < MP_GP_TAIRYOKU)
		return;													// �ϗ͕ǁA�V��A�����A�����@�̂ݕ\������

	RoofTextColor = mcs::GetColor( MM_COLOR_GRID_TEXT);
	pCod->SetTextAttr( Mstr( "�l�r �S�V�b�N"), 100.f, MT_LOWER, MT_CENTER, RoofTextColor,
					   MgVect2D( 1., 0.), vOffset, MT_FREESIZE);

	ign = 0;
	for ( pRoofEn = HaitiDb::MdGetHeadRoof( &pos1); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof( &pos1)) {

		if ( pRoofEn->GetInpKai() != iKaiC)
			continue;											// �قȂ�K�̕��ނ͕\�����Ȃ�
		if ( !MmChkValidRoof( pRoofEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		RoofLineColor = RGB( 10, 30, 30);
		pCod->SetLineAttr( MPS_SOLID, 1, RoofLineColor);
		if ( pRoofEn->GetpZukei()) {
			for ( ic=0; ic<pRoofEn->GetpZukei()->m_isNZukei; ic++) {
				pCod->Line( MgLine2DC( pRoofEn->GetpZukei()->m_lnZukei[ic]));
			}
		}

	}
}

static MPOSITION	z_RoofPos;

/////////////////////////////////////////////////////////////////////////////
//	�����ʂ���������
//	�Ԓl =NULL: �Y�������ʂȂ� !=NULL: �Y�������ʐ�
MhRfm*	mhHaitiIn::SrchRfm(							// (  O) �����ʁ@�܂��́@NULL
						MINT		imode,			// �������[�h�@�w���_�ɊY�����鉮���ʂ���������ꍇ�̗D��I������
													//				MC_PRI_MIN_AREA(0):	 �ʐς�����D��
													//				MC_PRI_MIN_HIGHT(1): ����������D��
													//				MC_PRI_MAX_HIGHT(2) | ���̑�: ���������D��	
				const	MgPoint2D	&pt1			// �w���_
				)
{
	MINT		ist1;

	MPOSITION	pos1;
	MhRoofInfo	*pRoofEn;

	MINT		ic1;

	MREAL		rArea;

	MgPolyg2D	pgRfm;
	MhRfm		*pRfm = 0;
	MREAL		rHight;

	MINT	iKaiC = z_mnIA.GetInpKai();								// ���݂̊K

	MREAL	rMinArea = MREALMAX;
	MREAL	rMinHight = MREALMAX;
	MREAL	rMaxHight = MREALMIN;

	for ( pRoofEn = HaitiDb::MdGetHeadRoof( &pos1); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof( &pos1)) {

		if ( pRoofEn->GetInpKai() != iKaiC)
			continue;											// �قȂ�K�̕��ނ͑ΏۊO
		if ( !MmChkValidRoof( pRoofEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
			if ( MGeo::Zero( pRoofEn->GetpGRfm()->m_st[ic1].m_Pln.v.z))// ��؂͖���
				continue;
			pgRfm = pRoofEn->GetpGRfm()->m_st[ic1].m_Pg;		// �|���S���@�R�c���Q�c
			
			if ( MGeo::ChkPointOnPolygon2DWS( pt1, pgRfm, &ist1)) {
				if ( imode == MC_PRI_MIN_AREA) {
					rArea = pgRfm.Area();
					if ( rArea < rMinArea) {
						rMinArea = rArea;
						pRfm = &(pRoofEn->GetpGRfm()->m_st[ic1]);
					}
				} else {
					rHight = pRoofEn->GetpGRfm()->m_st[ic1].m_Pln.GetZ( pt1);
					if ( imode == MC_PRI_MIN_HIGHT) {
						if ( rHight < rMinHight) {
							rMinHight = rHight;
							pRfm = &(pRoofEn->GetpGRfm()->m_st[ic1]);
						}
					} else {
						if ( rHight > rMinHight) {
							rMinHight = rHight;
							pRfm = &(pRoofEn->GetpGRfm()->m_st[ic1]);
						}
					}
				}
			}
		}
	}
	return pRfm;
}

} // namespace MC
