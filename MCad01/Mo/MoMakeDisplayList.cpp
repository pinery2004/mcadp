//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsDispModel.cpp
//
//		�ƃ��f���̃f�B�X�v���C���X�g�쐬
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgLib.h"
#include "MhLib.h"

#include "MtInp.h"

#include "MdOpt.h"
#include "MdHist.h"

#include "MoDispList.h"

#define DLL_EXPORT_MDLDISPLIST_DO
#include "MoMdlDispList.h"

//S #define		MP_PANEL_LINE			1
//S #define		MP_PANEL_RECTANGULAR	2

namespace MC
{

//////////////////////////////////////////////////////////////////////////////
////	�y�@�\�z�ƃ��f����MINMAX���擾����
////

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z����̌��̑��p�`�����߂�
//			
	void MdlDispList::TateguHole(
						mhPlcInfo	*i_pPlcEn,		// �ǂ܂���NULL
						mhPlcInfo	*pPlcTEn,		// ����
						MgPolyg3	*PgR,			// �ǉE�ʊJ��
						MgPolyg3	*PgL			// �Ǎ��ʊJ��
				)
{
	MGPOLYG3( PgW, 4);

	MhTateguInfo*	pAuxTategu;

	MREAL		rZU, rZL;

	MgPoint2	ptW[2];
	MgLine2		lnK[2];
	MgLine3		LnK[2];
	MgLine3		LnKL[2];
	MgLine3		LnKR[2];
	MgVect2		vtW;
	MgVect2		vuW;
	MgVect2		vtWidthR;
	MgVect2		vtWidth;
	MINT		iRev;
	MgVect3		V1, V2;
	MREAL		cc;

	// �J���̏�[�����Ɖ��[���������߂�
	pAuxTategu = (MhTateguInfo *)pPlcTEn->GetPIAuxTategu();
	rZU = mcs::GetStnd( pPlcTEn->GetPIKai(), MM_STNDH_LOWER) + pAuxTategu->GetHeight();
	rZL = rZU - pAuxTategu->GetROH();

	ptW[0] = (MgPoint2&)pPlcTEn->GetPIPlcIti( 0);
	ptW[1] = (MgPoint2&)pPlcTEn->GetPIPlcIti( 1);
	vtW = ptW[1] - ptW[0];
	vuW = MGeo::UnitizeV2( vtW);
	vtWidthR = pPlcTEn->GetMbWidthR() * vuW.RotR90(); 
	vtWidth = pPlcTEn->GetMbWidth() * vuW.RotL90(); 

	iRev = 0;
	if ( i_pPlcEn != NULL) {
		V1 = i_pPlcEn->GetPIPlcIti( 1) - i_pPlcEn->GetPIPlcIti( 0);
		V2 = pPlcTEn->GetPIPlcIti( 1) - pPlcTEn->GetPIPlcIti( 0);
		cc = V1 * V2;												// cc > 0: �ǂƌ���������
		if (cc < 0)
			iRev = 1;
	}
	if ( iRev == 0) {
		lnK[0].p[0] = ptW[0] - pPlcTEn->GetPILenHosei( 0) * vuW + vtWidthR;		// �E���Q���������n�_
		lnK[0].p[1] = ptW[1] + pPlcTEn->GetPILenHosei( 1) * vuW + vtWidthR;		// �E���Q���������I�_
		lnK[1] = lnK[0] + vtWidth;												// �����Q��������
	} else {
		vtWidthR = -vtWidthR;
		vtWidth = - vtWidth;

		lnK[0].p[0] = ptW[1] + pPlcTEn->GetPILenHosei( 1) * vuW + vtWidthR;		// �E���Q���������n�_
		lnK[0].p[1] = ptW[0] - pPlcTEn->GetPILenHosei( 0) * vuW + vtWidthR;		// �E���Q���������I�_
		lnK[1] = lnK[0] + vtWidth;												// �����Q��������
	}

	// �E���J�����p�`�����߂�
	PgR->m_n = 4;
	PgR->m_P[3] = MgPoint3C( lnK[0].p[1], rZL);
	PgR->m_P[2] = MgPoint3C( lnK[0].p[1], rZU);
	PgR->m_P[1] = MgPoint3C( lnK[0].p[0], rZU);
	PgR->m_P[0] = MgPoint3C( lnK[0].p[0], rZL);

	// �����J�����p�`�����߂�
	PgL->m_n = 4;
	PgL->m_P[0] = MgPoint3C( lnK[1].p[1], rZL);
	PgL->m_P[1] = MgPoint3C( lnK[1].p[1], rZU);
	PgL->m_P[2] = MgPoint3C( lnK[1].p[0], rZU);
	PgL->m_P[3] = MgPoint3C( lnK[1].p[0], rZL);
}

//////////////////////////////////////////////////////////////////////////////
////	�y�@�\�z�ǂ̃f�B�X�v���C���X�g���쐬���� ���ԁA������
////			
//void Kabe(

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z����̊J���g�̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawTategu(
						mhPlcInfo	*i_pPlcEn,		// �ǂ܂���NULL
						mhPlcInfo	*pPlcTEn,		// ����
				const	MgPoint3	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MGPOLYG3( PgR, 4);
	MGPOLYG3( PgL, 4);
	MINT	ic1b, ic1;
	MgLine3	LnKR, LnKL;

	TateguHole( i_pPlcEn, pPlcTEn, &PgR, &PgL);

	for ( ic1b=0,ic1=PgR.m_n - 1; ic1>=0; ic1b=ic1,ic1--) {
		LnKR = MgLine3( PgR[ic1b], PgR[ic1]);
		LnKL = MgLine3( PgL[3 - ic1b], PgL[3 - ic1]);
		DispList::DspQuads( DPtoDSP( LnKR, 0., PtCtr, rB), DPtoDSP( LnKL, 0., PtCtr, rB));
	}
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z��b�̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawKiso(
						mhPlcInfo	*i_pPlcEn,		// ��b
				const	MgPoint3	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MREAL		rZU, rZL;
	MINT		ic1;

	MgLine3		LnKiso0;
	MgVect3		vuLnKiso0;
	MgLine3		LnKiso1, LnKiso2;
	MgLine3		LnKiso3;
	MREAL		dl;

	MGPOLYG3( PgW, 4);
	MGPOLYG3( PgR, 4);
	MGPOLYG3( PgL, 4);
	MgGPolyg3	GPgR;
	MgGPolyg3	GPgL;

	rZU = mcs::GetStnd( i_pPlcEn->GetPIKai(), MM_STNDH_KISO);			// ��b�
	rZL = 0.;																	// �O�����h
	LnKiso0 = i_pPlcEn->GetPIPlcIti();
	vuLnKiso0 = LnKiso0.Vu();
	LnKiso1 = i_pPlcEn->GetPIZukei()->m_lnZukei[0];				// �E����b�ʐ���
	LnKiso2 = i_pPlcEn->GetPIZukei()->m_lnZukei[1];				// ������b�ʐ���

	// �E����b��
	PgW.m_n = 4;
	PgW[0] = MgPoint3C( MgPoint2C( LnKiso1.p[0]), rZL);
	PgW[1] = MgPoint3C( MgPoint2C( LnKiso1.p[1]), rZL);
	PgW[2] = MgPoint3C( MgPoint2C( LnKiso1.p[1]), rZU);
	PgW[3] = MgPoint3C( MgPoint2C( LnKiso1.p[0]), rZU);
	GPgR += PgW;

	// ������b��
	PgW.m_n = 4;
	PgW[0] = MgPoint3C( MgPoint2C( LnKiso2.p[0]), rZL);
	PgW[1] = MgPoint3C( MgPoint2C( LnKiso2.p[1]), rZL);
	PgW[2] = MgPoint3C( MgPoint2C( LnKiso2.p[1]), rZU);
	PgW[3] = MgPoint3C( MgPoint2C( LnKiso2.p[0]), rZU);
	GPgL += PgW;

	DispList::DrawPolygon( GPgR, PtCtr, rB);
	DispList::DrawPolygon( GPgL, PtCtr, rB);

	// ��b�㉺�ʁ@
	dl = (LnKiso1.p[0] - LnKiso0.p[0]) * vuLnKiso0;				// �������̌��Ԃ𖄂߂�
	if (dl > MGPTOL->D)
		LnKiso1.p[0] -= (dl * vuLnKiso0);
	dl = (LnKiso1.p[1] - LnKiso0.p[1]) * vuLnKiso0;
	if (dl < - MGPTOL->D)
		LnKiso1.p[1] -= (dl * vuLnKiso0);
	dl = (LnKiso2.p[1] - LnKiso0.p[0]) * vuLnKiso0;
	if (dl > MGPTOL->D)
		LnKiso2.p[1] -= (dl * vuLnKiso0);
	dl = (LnKiso2.p[0] - LnKiso0.p[1]) * vuLnKiso0;
	if (dl < - MGPTOL->D)
		LnKiso2.p[0] -= (dl * vuLnKiso0);

	LnKiso2.SetRev();
	DispList::DspQuads( DPtoDSP( LnKiso2, rZL, PtCtr, rB), DPtoDSP( LnKiso1, rZL, PtCtr, rB));		// ��b����
	DispList::DspQuads( DPtoDSP( LnKiso1, rZU, PtCtr, rB), DPtoDSP( LnKiso2, rZU, PtCtr, rB));		// ��b���

	// ��b�[����
	for ( ic1=2; ic1<i_pPlcEn->GetPIZukei()->m_isNZukei; ic1++) {
		LnKiso3 = i_pPlcEn->GetPIZukei()->m_lnZukei[ic1];									// ��b�[���ʐ���
		DispList::DspQuads( DPtoDSP( LnKiso3, rZL, PtCtr, rB), DPtoDSP( LnKiso3, rZU, PtCtr, rB));	// ��b�[����
	}
}

//////////////////////////////////////////////////////////////////////////////
////	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@���̗p
////			
//void MdlDispList::DrawYane1(

//////////////////////////////////////////////////////////////////////////////
////	�y�@�\�z��؂̃f�B�X�v���C���X�g���쐬����@���̗p
////			
//void MdlDispList::DrawYagiri(

//////////////////////////////////////////////////////////////////////////////
////	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@������
////			
//void MdlDispList::DrawYane2(

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z���Ęg�A���̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawTatewaku( 
						mhPlcInfo	*i_pPlcEn,
				const	MgPoint3	&PtCtr,
						MREAL		rB
				)
{
	MREAL		rZ1, rZ2;
	MgLine3		LnPlc;
	MgLine3		LnBz;
	MREAL		rW1, rH1;

	MgVect3		VtHoko, VtRt, VtUp;					// ���ނ̔z�u�����x�N�g���A�E�����x�N�g���A������x�N�g��
	MgVect3		VuHoko, VuRt, VuUp;					// ���ނ̔z�u�����P�ʃx�N�g���A�E�����P�ʃx�N�g���A������P�ʃx�N�g��
	MgVect3		VtHzSz;								// �z�u�_���� + �ގ��c����
	MREAL		rHgt1, rHgt2;

	MgPoint3	PT[2][2][2];						// ���_���W

	rZ1 = mcs::GetStnd( i_pPlcEn->GetPIKai(), MM_STNDH_LOWER);
	rZ2 = mcs::GetStnd( i_pPlcEn->GetPIKai(), MM_STNDH_CEILING);
//	LnPlc.Set( i_pPlcEn->m_lnPlc);
	LnPlc = i_pPlcEn->GetPIPlcIti();

	VuHoko = LnPlc.Vu();
	VuRt = VuHoko.RotR90();
	VuUp = VuRt ^ VuHoko;

	VtHzSz = (i_pPlcEn->GetPIPlcZure() - i_pPlcEn->GetMbWidth() * 0.5f) * VuHoko +
			 i_pPlcEn->GetPISinZure() * VuHoko.RotR90();
	
	rHgt1 = i_pPlcEn->GetPIHgt( 0);												// ���[����
	LnPlc.p[0] = MgPoint3C( MgPoint2C( LnPlc.p[0] + VtHzSz), rHgt1);
	rHgt2 = i_pPlcEn->GetPIHgt( 1);												// ��[����
	if ( MGeo::LE( rHgt2, 0.)) {
		rHgt2 = rZ2 - rZ1 + rHgt2;
	} else {
		rHgt2 = rHgt2;
	}
	LnPlc.p[1] = MgPoint3C( MgPoint2C( LnPlc.p[0]), rHgt2);

	LnBz = DPtoDSP( LnPlc, rZ1, PtCtr, rB);
	rW1 = (i_pPlcEn->GetMbTWidth() - 0.2f) * rB;
	rH1 = i_pPlcEn->GetMbTHeight() * rB;

	VtHoko = VuHoko * rH1;
	VtRt = VuRt * rW1;
	VtUp = LnBz.p[1] - LnBz.p[0];

	//PT[0][0][0].Set( LnBz.p[0] + VtRt * 0.5);					// ���t����
	//PT[0][0][1].Set( PT[0][0][0] + VtUp);						//
	//PT[0][1][0].Set( PT[0][0][0] - VtRt);						//
	//PT[0][1][1].Set( PT[0][0][1] - VtRt);						//
	//PT[1][0][0].Set( PT[0][0][0] + VtHoko);						//
	//PT[1][0][1].Set( PT[0][0][1] + VtHoko);						//
	//PT[1][1][0].Set( PT[0][1][0] + VtHoko);						//
	//PT[1][1][1].Set( PT[0][1][1] + VtHoko);						//
	PT[0][0][0] = LnBz.p[0] + VtRt * 0.5;						// ���t����
	PT[0][0][1] = PT[0][0][0] + VtUp;							//
	PT[0][1][0] = PT[0][0][0] - VtRt;							//
	PT[0][1][1] = PT[0][0][1] - VtRt;							//
	PT[1][0][0] = PT[0][0][0] + VtHoko;							//
	PT[1][0][1] = PT[0][0][1] + VtHoko;							//
	PT[1][1][0] = PT[0][1][0] + VtHoko;							//
	PT[1][1][1] = PT[0][1][1] + VtHoko;							//

	DispList::DspRectangular( PT, VuHoko, VuRt, VuUp);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z���u���ނ̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawOukaZai( 
						mhPlcInfo	*i_pPlcEn,
				const	MgPoint3	&PtCtr,
						MREAL		rB
				)
{
	MSTNDH		iCdHgt;
	MINT		iULCd;								// �㉺�t���R�[�h (0:���t��, 1:��t��)
	MREAL		rZ;
	MgLine3		LnPlc;
	MgLine3		LnBz;
	MREAL		rW1, rH1;

	MgVect3		VtLng, VtRt, VtUp;					// ���ނ̒��������x�N�g���A�E�����x�N�g���A������x�N�g��
	MgVect3		VuLng, VuRt, VuUp;					// ���ނ̒��������P�ʃx�N�g���A�E�����P�ʃx�N�g���A������P�ʃx�N�g��
	MgVect3		VtTkSz;								// ���t������ + �ގ��c����

	MgPoint3	PT[2][2][2];						// ���_���W

	iCdHgt = i_pPlcEn->GetPTCdHgt();
	iULCd = i_pPlcEn->GetPTCdToritk();

	rZ = mcs::GetStnd( i_pPlcEn->GetPIKai(), iCdHgt);
	LnPlc = i_pPlcEn->GetPIPlcIti();

	VuLng = LnPlc.Vu();
	VuUp = i_pPlcEn->GetPIUpPlc();
	VuRt = VuLng ^ VuUp;
	
	VtTkSz = i_pPlcEn->GetPIHgt( 0) * VuUp + i_pPlcEn->GetPISinZure() * VuRt;		// ���t������+�ގ��c����
	LnPlc.p[0] = LnPlc.p[0] - i_pPlcEn->GetPILenHosei( 0) * VuLng + VtTkSz;
	LnPlc.p[1] = LnPlc.p[1] + i_pPlcEn->GetPILenHosei( 1) * VuLng + VtTkSz;

	// �\�����W�n
	LnBz = DPtoDSP( LnPlc, rZ, PtCtr, rB);
	rW1 = i_pPlcEn->GetMbWidth() * rB;
	rH1 = i_pPlcEn->GetMbHeight() * rB;

	VtLng = LnBz.p[1] - LnBz.p[0];
	VtRt = VuRt * rW1;
	VtUp = VuUp * rH1;

	//if ( iULCd == 0) 
	//	PT[0][0][0].Set( LnBz.p[0] + VtRt * 0.5);				// ���t����
	//else
	//	PT[0][0][0].Set( LnBz.p[0] + VtRt * 0.5 - VtUp);		// ��t����

	//PT[0][0][1].Set( PT[0][0][0] + VtUp);						//
	//PT[0][1][0].Set( PT[0][0][0] - VtRt);						//
	//PT[0][1][1].Set( PT[0][0][1] - VtRt);						//
	//PT[1][0][0].Set( PT[0][0][0] + VtLng);						//
	//PT[1][0][1].Set( PT[0][0][1] + VtLng);						//
	//PT[1][1][0].Set( PT[0][1][0] + VtLng);						//
	//PT[1][1][1].Set( PT[0][1][1] + VtLng);						//
	if ( iULCd == 0) 
		PT[0][0][0] = LnBz.p[0] + VtRt * 0.5;					// ���t����
	else
		PT[0][0][0] = LnBz.p[0] + VtRt * 0.5 - VtUp;			// ��t����

	PT[0][0][1] = PT[0][0][0] + VtUp;							//
	PT[0][1][0] = PT[0][0][0] - VtRt;							//
	PT[0][1][1] = PT[0][0][1] - VtRt;							//
	PT[1][0][0] = PT[0][0][0] + VtLng;							//
	PT[1][0][1] = PT[0][0][1] + VtLng;							//
	PT[1][1][0] = PT[0][1][0] + VtLng;							//
	PT[1][1][1] = PT[0][1][1] + VtLng;							//

	DispList::DspRectangular( PT, VuLng, VuRt, VuUp);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z���A�V��A�����̊J���̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawKaiko( 
						mhPlcInfo *i_pPlcEn,
				const	MgPoint3	&PtCtr,
						MREAL		rB
				)
{
	MSTNDH		iCdHgt;
	MINT		iULCd;								// �㉺�t���R�[�h (0:���t��, 1:��t��)
	MREAL		rZ;
	MgLine3		LnPlc;
	MgLine3		LnBz;
	MREAL		rH1, rTH, rOY;

	MgVect3		VtLng, VtRt, VtUp;					// ���ނ̒��������x�N�g���A�E�����x�N�g���A������x�N�g��
	MgVect3		VuLng, VuRt, VuUp;					// ���ނ̒��������P�ʃx�N�g���A�E�����P�ʃx�N�g���A������P�ʃx�N�g��
	MgVect3		VtTkH;								// ���t������
	MgVect3		VtTH, VtOY;							// ��O���␳�l�A���s��
	MgPoint3	PT[2][2][2];						// ���_���W
	MgVect2		vuRt;								// �����p�l���p���s�������Q�����x�N�g��
	MREAL		rlXY;								// �����p�l���p���s�������Q�����x�N�g����XY���ʏ㒷��
	
	iCdHgt = (MSTNDH)i_pPlcEn->GetPICdHgt();
	iULCd = i_pPlcEn->GetPTCdToritk();

	rZ = mcs::GetStnd( i_pPlcEn->GetPIKai(), iCdHgt);
	LnPlc = i_pPlcEn->GetPIPlcIti();

	VuLng = LnPlc.Vu();
	if ( MGeo::Zero( VuLng.z))
		VuRt = VuLng.RotR90();
	else {
		MREAL r1_D = 1.f / sqrt( VuLng.x * VuLng.x + VuLng.y * VuLng.y);
//		VuRt.Set( VuLng.y * r1_D, - VuLng.x * r1_D, 0.f);
		VuRt = MgVect3( VuLng.y * r1_D, - VuLng.x * r1_D, 0.f);
	}
	VuUp = i_pPlcEn->GetPIUpPlc();
	VuRt = VuLng ^ VuUp;
	
	VtTkH = i_pPlcEn->GetPIHgt( 0)  * VuUp;						// ���t������
	LnPlc.p[0] = LnPlc.p[0] - i_pPlcEn->GetPILenHosei( 0) * VuLng + VtTkH;
	LnPlc.p[1] = LnPlc.p[1] + i_pPlcEn->GetPILenHosei( 1) * VuLng + VtTkH;

	// �\�����W�n
	LnBz = DPtoDSP( LnPlc, rZ, PtCtr, rB);
	rH1 = i_pPlcEn->GetMbHeight() * rB;
	rTH = i_pPlcEn->GetPIMaeHosei() * rB;						// �p�l����O���␳�l
	rOY = (i_pPlcEn->GetPIMaeHosei() + i_pPlcEn->GetPIOku() +
		   i_pPlcEn->GetPIOkuHosei()) * rB;						// �p�l����O���␳�l + ���s�� + �����␳�l
	if ( i_pPlcEn->IsYanePanel()) {
		vuRt = MgVect2C( VuRt);
		rlXY = MGeo::Abs( vuRt);
		if ( !MGeo::Zero( rlXY)) {
			rTH /= rlXY;
			rOY /= rlXY;
		}
	}

	VtLng = LnBz.p[1] - LnBz.p[0];
	VtTH = VuRt * rTH;
	VtOY = VuRt * rOY;
	VtUp = VuUp * rH1;

	//if ( iULCd == 0) 
	//	PT[0][0][0].Set( LnBz.p[0] + VtTH);						// ���t����
	//else
	//	PT[0][0][0].Set( LnBz.p[0] + VtTH - VtUp);				// ��t����

	//PT[0][0][1].Set( PT[0][0][0] + VtUp);						//
	//PT[0][1][0].Set( PT[0][0][0] - VtOY);						//
	//PT[0][1][1].Set( PT[0][0][1] - VtOY);						//
	//PT[1][0][0].Set( PT[0][0][0] + VtLng);						//
	//PT[1][0][1].Set( PT[0][0][1] + VtLng);						//
	//PT[1][1][0].Set( PT[0][1][0] + VtLng);						//
	//PT[1][1][1].Set( PT[0][1][1] + VtLng);						//
	if ( iULCd == 0) 
		PT[0][0][0] = LnBz.p[0] + VtTH;							// ���t����
	else
		PT[0][0][0] = LnBz.p[0] + VtTH - VtUp;					// ��t����

	PT[0][0][1] = PT[0][0][0] + VtUp;							//
	PT[0][1][0] = PT[0][0][0] - VtOY;							//
	PT[0][1][1] = PT[0][0][1] - VtOY;							//
	PT[1][0][0] = PT[0][0][0] + VtLng;							//
	PT[1][0][1] = PT[0][0][1] + VtLng;							//
	PT[1][1][0] = PT[0][1][0] + VtLng;							//
	PT[1][1][1] = PT[0][1][1] + VtLng;							//

	DispList::DspRectangular( PT, VuLng, VuRt, VuUp);
}

} // namespace MC