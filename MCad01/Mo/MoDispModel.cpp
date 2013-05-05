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
#include "MsMCAD.h"

#include "MmWnd.h"

#include "MgLib.h"
#include "MhDefParts.h"
#include "McSystemProperty.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MgGrp.h"
#include "MhRoof.h"
#include "MdLib.h"

#include "MhInpPlcParts.h"

#include "MdOpt.h"
#include "MdHist.h"

#include "MdmFig.h"

#include "MoDispList.h"
#include "MmValid.h"

#define	DLL_EXPORT_MDLDISPLIST_DO
#include "MoMdlDispList.h"

#include <GL/gl.h>						//ADD
#include <GL/glu.h>						//ADD
#include <GL/glut.h>					//ADD
#include "MoGlLib.h"					//ADD

#define		MP_PANEL_LINE			1
#define		MP_PANEL_RECTANGULAR	2

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�ƃ��f����MINMAX���擾����
//
	void MdlDispList::MhGetMinMaxMdl( MgMinMaxR3D	*prMmMdl)
{
	mhPlcParts*		pPlcEn;
	MPOSITION		posH;
	MgMinMaxR3D		rMmMdl;
	MINT			maxKai;
	MhRoofInfo*		pRoofEn;
	MPOSITION		posR;
	MgLine3D			LnPlc;

	MREAL			rRoofZ;
	MINT			ic1, ic2;
	MgPoint3D		Py1;


	// �ƃ��f����MINMAX���擾����
	rMmMdl.SetInit();

	maxKai = 0;
	for ( pPlcEn = HaitiDb::MdGetHeadParts( &posH); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &posH)) {
		if ( !MmChkValidParts( pPlcEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

//		LnPlc.Set( pPlcEn->m_lnPlc);
		LnPlc = pPlcEn->GetPIPlcIti();
		rMmMdl.Ins3( LnPlc);
		rMmMdl.min.z = 0;
		if (maxKai < pPlcEn->GetPIKai())
			maxKai = pPlcEn->GetPIKai();
	}

	rMmMdl.max.z = mcs::GetStnd( maxKai, MM_STNDH_ROOF) + 200.f;
	for ( pRoofEn = HaitiDb::MdGetHeadRoof( &posR); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof( &posR)) {
		if ( !MmChkValidRoof( pRoofEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;
		rRoofZ = mcs::GetStnd( pRoofEn->GetInpKai(),MM_STNDH_ROOF);
		for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
			for ( ic2=0; ic2<pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_n; ic2++) {
				Py1 = pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_P[ic2];
				rMmMdl.Ins3( Py1);
			}
		}
	}
	*prMmMdl = rMmMdl;
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�ǂ̃f�B�X�v���C���X�g���쐬���� ���ԁA������
//			
void MdlDispList::DrawKabe(
						mhPlcParts	*i_pPlcEn,		// ��
				const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MINT		ist1;	
	MREAL		rZU, rZL;
	MINT		ic1;

	MgLine3D		LnKabe0;
	MgVect3D		vuLnKabe0;
	MgLine3D		LnKabe1, LnKabe2;
	MgLine3D		LnKabe3;
	MgVect3D		vl;
	MREAL		dl;

	MGPOLYG3( PgW, 4);
	MGPOLYG3( PgR, 4);
	MGPOLYG3( PgL, 4);
	MgGPolyg3D	GPgR;
	MgGPolyg3D	GPgL;

	rZU = mcs::GetStnd( i_pPlcEn->GetPIKai(), MM_STNDH_CEILING);// �V��
	rZL = mcs::GetStnd( i_pPlcEn->GetPIKai(), MM_STNDH_LOWER);	// ���
	LnKabe0 = i_pPlcEn->GetPIPlcIti();
	vuLnKabe0 = LnKabe0.Vu();
	LnKabe1 = i_pPlcEn->GetPIZukei()->m_lnZukei[0];				// �E���ǖʐ���
	LnKabe2 = i_pPlcEn->GetPIZukei()->m_lnZukei[1];				// �����ǖʐ���

	// �E���ǖ�
	PgW.m_n = 4;
	PgW[0] = MgPoint3DC( MgPoint2DC( LnKabe1.p[0]), rZL);
	PgW[1] = MgPoint3DC( MgPoint2DC( LnKabe1.p[1]), rZL);
	PgW[2] = MgPoint3DC( MgPoint2DC( LnKabe1.p[1]), rZU);
	PgW[3] = MgPoint3DC( MgPoint2DC( LnKabe1.p[0]), rZU);
	GPgR += PgW;

	// �����ǖ�
	PgW.m_n = 4;
	PgW[0] = MgPoint3DC( MgPoint2DC( LnKabe2.p[0]), rZL);
	PgW[1] = MgPoint3DC( MgPoint2DC( LnKabe2.p[1]), rZL);
	PgW[2] = MgPoint3DC( MgPoint2DC( LnKabe2.p[1]), rZU);
	PgW[3] = MgPoint3DC( MgPoint2DC( LnKabe2.p[0]), rZU);
	GPgL += PgW;

	// ����̊J���Əd�Ȃ�L��Ȃ�J����ǉ�����
	mhPlcParts *pPlcTEn;
	MPOSITION	PartsPos;
	MhTateguInfo	*pAuxTategu;
	for ( pPlcTEn = HaitiDb::MdGetHeadParts( &PartsPos); pPlcTEn!=0;
		  pPlcTEn = HaitiDb::MdGetNextParts( &PartsPos)) {
		if ( !MmChkValidParts( i_pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		if ( pPlcTEn->GetPIKai() == i_pPlcEn->GetPIKai() &&
			Mstrcmp( (&pPlcTEn->GetPIPartsSpec()->GetPTNmGeneral()[2]), Mstr( "����")) == 0) {
			if ( MGeo::ChkLineOnLine3DWS( pPlcTEn->GetPIPlcIti(), i_pPlcEn->GetPIPlcIti(), &ist1)) {
				MdlDispList::TateguHole( i_pPlcEn, pPlcTEn, &PgR, &PgL);
				pAuxTategu = (MhTateguInfo*)pPlcTEn->GetPIAuxTategu();
				if ( MGeo::GE( pAuxTategu->GetHeight(), rZU) ||
					 MGeo::LE( pAuxTategu->GetHeight() - pAuxTategu->GetROH(),  0.) ||
					 MGeo::Abs( ist1) == 2) {					// �ǂƌ�������I�ɏd�Ȃ�
					 PgR.Rev();
					 PgL.Rev();
					 MGeo::MergeGPgPgtoGPolygon3D( MC_DIFF, GPgR, PgR, &GPgR);		// (  O) ���t�����p�`3
					 MGeo::MergeGPgPgtoGPolygon3D( MC_DIFF, GPgL, PgL, &GPgL);		// (  O) ���t�����p�`3
				} else {										// ����ǂ̒��Ɋ܂܂�
					GPgR += PgR;
					GPgL += PgL;
				}
			}
		}
	}

	MBLOGPRINTS( L"�R�c�ǃf�o�b�O");

	DispList::DrawPolygon( GPgR, PtCtr, rB);

	GPgR.Print( Mstr( "KabeR"));

	DispList::DrawPolygon( GPgL, PtCtr, rB);

	GPgL.Print( Mstr( "KabeL"));

	//�@�Ǐ㉺��
	dl = (LnKabe1.p[0] - LnKabe0.p[0]) * vuLnKabe0;				// �������̌��Ԃ𖄂߂�
	if (dl > MGPTOL->D)
		LnKabe1.p[0] -= (dl * vuLnKabe0);
	dl = (LnKabe1.p[1] - LnKabe0.p[1]) * vuLnKabe0;
	if (dl < - MGPTOL->D)
		LnKabe1.p[1] -= (dl * vuLnKabe0);
	dl = (LnKabe2.p[1] - LnKabe0.p[0]) * vuLnKabe0;
	if (dl > MGPTOL->D)
		LnKabe2.p[1] -= (dl * vuLnKabe0);
	dl = (LnKabe2.p[0] - LnKabe0.p[1]) * vuLnKabe0;
	if (dl < - MGPTOL->D)
		LnKabe2.p[0] -= (dl * vuLnKabe0);
	LnKabe2.SetRev();
	DispList::DspQuads( DPtoDSP( LnKabe2, rZL, PtCtr, rB), DPtoDSP( LnKabe1, rZL, PtCtr, rB));			// �ǉ���
	DispList::DspQuads( DPtoDSP( LnKabe1, rZU, PtCtr, rB), DPtoDSP( LnKabe2, rZU, PtCtr, rB));			// �Ǐ��

	for ( ic1=2; ic1<i_pPlcEn->GetPIZukei()->m_isNZukei; ic1++) {
		LnKabe3 = i_pPlcEn->GetPIZukei()->m_lnZukei[ic1];		// �ǒ[���ʐ���
		DispList::DspQuads( DPtoDSP( LnKabe3, rZL, PtCtr, rB), DPtoDSP( LnKabe3, rZU, PtCtr, rB));		// �ǒ[����
	}
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@���̗p
//			
void MdlDispList::DrawYane1(
						MhRoofInfo	*pRoofEn,		// ���u����
				const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MINT			ist1;
	MINT			ic0, ic1, ic2;
	MINT			ic0b;
	MgVect3D		VtU, VtL;
	MgLine3D		LnU, LnL;
	MgLine3D		LncU, LncL;
	MREAL			rZ;
	MgGPolyg3D		GPg2(10);
	MGPOLYG3( Pg3U, 3);
	MGPOLYG3( Pg3L, 3);
	MhRfm			*pRfm2;

	for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
		pRfm2 = &pRoofEn->GetpGRfm()->m_st[ic1];
		if ( MGeo::Zero( pRfm2->m_Pln.v.z, MGPTOL->A)) {
			// ���
			continue;
		} else {
			// ������
			MREAL	rYaneHHosei = 130.f / pRfm2->m_Pln.v.z;

			VtU = MgVect3D( 0., 0., rYaneHHosei);
			VtL = MgVect3D( 0., 0., 0.);
			
//			DispList::SetMaterial( 0, 0);
		}
		ist1 = MGeo::DivideTriPolygon3D( pRfm2->m_Pg, pRfm2->m_Pln.v, &GPg2);
		rZ = mcs::GetStnd( pRoofEn->GetInpKai(), MM_STNDH_ROOF);
		for ( ic2=0; ic2<GPg2.m_n; ic2++) {
			DPtoDSP3R( GPg2.m_Pg[ic2], rZ, VtL, PtCtr, rB, &Pg3L);
			DPtoDSP3( GPg2.m_Pg[ic2], rZ, VtU, PtCtr, rB, &Pg3U);
			DispList::DspTriangles( Pg3L, -pRfm2->m_Pln.v);
			DispList::DspTriangles( Pg3U, pRfm2->m_Pln.v);
		}
		for ( ic0b=pRfm2->m_Pg.m_n-1,ic0=0; ic0<pRfm2->m_Pg.m_n; ic0b=ic0,ic0++) {
			if ( pRfm2->m_cdPg.m_i[ic0] == MHRL_NOKI || pRfm2->m_cdPg.m_i[ic0] == MHRL_KERABA) {
				LnU = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtU;
				LnL = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtL;
				LncU = DPtoDSP( LnU, rZ, PtCtr, rB);
				LncL = DPtoDSP( LnL, rZ, PtCtr, rB);
				DispList::DspQuads( LncL, LncU);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z��؂̃f�B�X�v���C���X�g���쐬����@���̗p
//			
void MdlDispList::DrawYagiri(
						MhRoofInfo	*pRoofEn,		// ���u����
				const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MINT			ist1;
	MINT			ic0, ic1, ic2;
	MINT			ic0b;
	MgVect3D			VtU, VtL;
	MgLine3D			LnU, LnL;
	MgLine3D			LncU, LncL;
	MREAL			rZ;
	MgGPolyg3D		GPg2(10);
	MGPOLYG3( Pg3U, 3);
	MGPOLYG3( Pg3L, 3);
	MhRfm			*pRfm2;

	for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
		pRfm2 = &pRoofEn->GetpGRfm()->m_st[ic1];
		if ( MGeo::Zero( pRfm2->m_Pln.v.z, MGPTOL->A)) {
			// ���
			VtU = pRfm2->m_Pln.v * (89. * 0.5);
			VtL = -VtU;

//			DispList::SetMaterial( 0, 1);
		} else {
			// ������
			continue;
		}
		ist1 = MGeo::DivideTriPolygon3D( pRfm2->m_Pg, pRfm2->m_Pln.v, &GPg2);
		rZ = mcs::GetStnd( pRoofEn->GetInpKai(), MM_STNDH_ROOF);
		for ( ic2=0; ic2<GPg2.m_n; ic2++) {
			DPtoDSP3R( GPg2.m_Pg[ic2], rZ, VtL, PtCtr, rB, &Pg3L);
			DPtoDSP3( GPg2.m_Pg[ic2], rZ, VtU, PtCtr, rB, &Pg3U);
			DispList::DspTriangles( Pg3L, -pRfm2->m_Pln.v);
			DispList::DspTriangles( Pg3U, pRfm2->m_Pln.v);
		}
		for ( ic0b=pRfm2->m_Pg.m_n-1,ic0=0; ic0<pRfm2->m_Pg.m_n; ic0b=ic0,ic0++) {
			if ( pRfm2->m_cdPg.m_i[ic0] == MHRL_NOKI || pRfm2->m_cdPg.m_i[ic0] == MHRL_KERABA) {
				LnU = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtU;
				LnL = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtL;
				LncU = DPtoDSP( LnU, rZ, PtCtr, rB);
				LncL = DPtoDSP( LnL, rZ, PtCtr, rB);
				DispList::DspQuads( LncL, LncU);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@������
//			
void MdlDispList::DrawYane2(
						MhRoofInfo	*pRoofEn,		// ���u����
				const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MINT			ist1;
	MINT			ic0, ic1, ic2;
	MINT			ic0b;
	MgVect3D			VtU, VtL;
	MgLine3D			LnU, LnL;
	MgLine3D			LncU, LncL;
	MREAL			rZ;
	MgGPolyg3D		GPg2(10);
	MGPOLYG3( Pg3U, 3);
	MGPOLYG3( Pg3L, 3);
	MhRfm			*pRfm2;

	for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
		pRfm2 = &pRoofEn->GetpGRfm()->m_st[ic1];
		if ( MGeo::Zero( pRfm2->m_Pln.v.z, MGPTOL->A)) {
			// ���
			VtU = pRfm2->m_Pln.v * (89. * 0.5);
			VtL = -VtU;
		} else {
			// ������
			VtU = MgVect3D( 0., 0., 120.);
			VtL = MgVect3D( 0., 0., 0.);
		}
		ist1 = MGeo::DivideTriPolygon3D( pRfm2->m_Pg, pRfm2->m_Pln.v, &GPg2);
		rZ = mcs::GetStnd( pRoofEn->GetInpKai(), MM_STNDH_ROOF);
		for ( ic2=0; ic2<GPg2.m_n; ic2++) {
			DPtoDSP3R( GPg2.m_Pg[ic2], rZ, VtL, PtCtr, rB, &Pg3L);
			DPtoDSP3( GPg2.m_Pg[ic2], rZ, VtU, PtCtr, rB, &Pg3U);
			DispList::DspTriangles( Pg3L, -pRfm2->m_Pln.v);
			DispList::DspTriangles( Pg3U, pRfm2->m_Pln.v);
		}
		for ( ic0b=pRfm2->m_Pg.m_n-1,ic0=0; ic0<pRfm2->m_Pg.m_n; ic0b=ic0,ic0++) {
			if ( pRfm2->m_cdPg.m_i[ic0] == MHRL_NOKI || pRfm2->m_cdPg.m_i[ic0] == MHRL_KERABA) {
				LnU = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtU;
				LnL = MgLine3D( pRfm2->m_Pg.m_P[ic0b], pRfm2->m_Pg.m_P[ic0]) + VtL;
				LncU = DPtoDSP( LnU, rZ, PtCtr, rB);
				LncL = DPtoDSP( LnL, rZ, PtCtr, rB);
				DispList::DspQuads( LncL, LncU);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̃f�[�^��S�ēǂݍ��݂R�����f�B�X�v���C���X�g�쐬�p��
//  �\���{���ƒ��S���W�����߂�
//
void MdlDispList::MhGetBCtr(
						MREAL		*rB,			// �\���{��
						MgPoint3D	*PtCtr			// ���S���W
				)
{
	MgMinMaxR3D		rMmMdl;
	MgMinMaxR2D		rmmmdl;
	MREAL			rW;
	MREAL			rWh;

//	MmWndInfo*		pWndInfo;						// �J�����g�E�B���h�E���擾����
	MgPoint3D		pW;

	// �ƃ��f����MINMAX���擾����
	MhGetMinMaxMdl( &rMmMdl);
	rW = MGMAX( (rMmMdl.max.x - rMmMdl.min.x), (rMmMdl.max.y - rMmMdl.min.y));
	if ( MGeo::LE( rW, 0.)) {
		rMmMdl.SetUnit();
	}

	// �Ƃ̒��S���W�A�\���{�� 1/rWh
//	PtCtr->Set( rMmMdl.GetCenter());
	*PtCtr = rMmMdl.GetCenter();
	rWh = MGMAX( rW, (rMmMdl.max.z - rMmMdl.min.z)) * 0.5f;

	*rB = 1.8f / rWh;											// 1.8�{�ŕ\��
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	���ށA��b	����
//	
int MdlDispList::DrawIeMdl(
						MREAL		rB,				// �\���{��
				const	MgPoint3D	&PtCtr			// ���S���W
				)
{
	MdlDispList::DrawIeMdl1( rB, PtCtr);
	MdlDispList::DrawIeMdl2( rB, PtCtr);
	MdlDispList::DrawIeMdl3( rB, PtCtr);
	MdlDispList::MakeDispListMat0( rB, PtCtr);
	MdlDispList::MakeDispListMat1( rB, PtCtr);
	MdlDispList::MakeDispListMat2( rB, PtCtr);
	return 0;
}

GLint MsDrawPlane( GLdouble w, GLdouble d ,GLdouble h)
{
	GLdouble norm[3];
	glPushMatrix();
	glBegin( GL_POLYGON );
		norm[0]=1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( w/2.0 , h ,   d/2.0 );
		glVertex3d( w/2.0 , h ,  -d/2.0  );
		glVertex3d(-w/2.0 , h ,  -d/2.0  );
		glVertex3d(-w/2.0 , h ,   d/2.0  );
	glEnd();
	glPopMatrix();

	return(0) ;
}

GLint MsDrawBox(GLdouble d, GLdouble w, GLdouble h)
{
	GLdouble norm[3];
	
	glPushMatrix();
	glTranslated(-d/2.0,-w/2.0,-h/2.0);
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=-1;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , 0 , h );
		glVertex3d( 0 , 0 , h );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=-1;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , w , 0 );
		glVertex3d( d , w , 0 );
		glVertex3d( d , w , h );
		glVertex3d( 0 , w , h );
	glEnd();

	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=0;norm[2]=1;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , h );
		glVertex3d( d , 0 , h );
		glVertex3d( d , w , h );
		glVertex3d( 0 , w , h );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=0;norm[2]=1;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , w , 0 );
		glVertex3d( 0 , w , 0 );
	glEnd();

	glBegin( GL_POLYGON );
		norm[0]=-1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( 0 , 0 , h );
		glVertex3d( 0 , w , h );
		glVertex3d( 0 , w , 0 );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=-1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , 0 , h );
		glVertex3d( d , w , h );
		glVertex3d( d , w , 0 );
	glEnd();
	glPopMatrix();


	return(0) ;

}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	���ށA��b	����
//	
MINT MdlDispList::DrawIeMdl1(
						MREAL		rB,				// �\���{��
				const	MgPoint3D	&PtCtr			// ���S���W
				)
{
	if (  MdlDispList::OpenDL( 1))
		return 1;
#if	(Disp3DBox)
	MsDrawBox( 2.0, 3.0, 1.0);			//ADD
	MsDrawPlane( 5.0, 5.0 , 0.0);		//ADD
#else
	mhPlcParts*	pPlcEn;
	MPOSITION	posH;

	for ( pPlcEn = HaitiDb::MdGetHeadParts( &posH); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &posH)) {

		if ( !MmChkValidParts( pPlcEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		//	���ނ̃f�B�X�v���C���X�g���쐬����
		if (Mstrcmp( pPlcEn->GetPTNmGeneral(), Mstr( "��")) == 0 ||
			Mstrcmp( (&pPlcEn->GetPTNmGeneral()[2]), Mstr( "����")) == 0)			// �ǂƌ���͓ǂݔ�΂�
			continue;

		//	���Ęg�̃f�B�X�v���C���X�g���쐬����
		if ( pPlcEn->IsFrame()) {
			DispList::SetMaterial( 0, 3);
			MdlDispList::DrawTatewaku( pPlcEn, PtCtr, rB);

		//	�p�l���̃f�B�X�v���C���X�g���쐬����
		} else if ( pPlcEn->IsPanel()) {
			DispList::SetMaterial( 0, 3);
			MdlDispList::DrawPanel( pPlcEn, PtCtr, rB, 3);

		//	���A�V��A�����̊J���̃f�B�X�v���C���X�g���쐬����
		} else if ( pPlcEn->IsKaiko()) {
			DispList::SetMaterial( 0, 3);
			MdlDispList::DrawKaiko( pPlcEn, PtCtr, rB);

		//	��b�̃f�B�X�v���C���X�g���쐬����
		} else if ( pPlcEn->IsKiso()) {
			DispList::SetMaterial( 0, 4);
			MdlDispList::DrawKiso( pPlcEn, PtCtr, rB);

		//	���u���ނ̃f�B�X�v���C���X�g���쐬����
		} else if ( pPlcEn->IsOukaZai()) {
			DispList::SetMaterial( 0, 3);
			MdlDispList::DrawOukaZai( pPlcEn, PtCtr, rB);
		}
	}

	// �}�`���̃f�B�X�v���C���X�g���쐬����
	DispList::DrawAllEnt( PtCtr, rB);
#endif
	MdlDispList::CloseDL();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁@�}�e���A���Ȃ�
//
int MdlDispList::DrawIeMdl2(
						MREAL		rB,				// �\���{��
				const	MgPoint3D	&PtCtr			// ���S���W
				)
{
	mhPlcParts*	pPlcEn;
	MPOSITION	posH;
	MhRoofInfo*	pRoofEn;
	MPOSITION	posR;

	if ( MdlDispList::OpenDL( 2))
		return 1;

	//	�ǂ̃f�B�X�v���C���X�g���쐬����
	for ( pPlcEn = HaitiDb::MdGetHeadParts( &posH); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &posH)) {

		if ( !MmChkValidParts( pPlcEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		//	�ǂ̃f�B�X�v���C���X�g���쐬����
		if (Mstrcmp( pPlcEn->GetPTNmGeneral(), Mstr( "��")) == 0) {
			MdlDispList::DrawKabe( pPlcEn, PtCtr, rB);

		//	����̊J���̃f�B�X�v���C���X�g���쐬����
		} else if (Mstrcmp( (&pPlcEn->GetPTNmGeneral()[2]), Mstr( "����")) == 0) {
			MdlDispList::DrawTategu( NULL, pPlcEn, PtCtr, rB);
		}
	}

	//	��؂̃f�B�X�v���C���X�g���쐬����
	for ( pRoofEn = HaitiDb::MdGetHeadRoof( &posR); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof( &posR)) {

		if ( !MmChkValidRoof( pRoofEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

		MdlDispList::DrawYagiri( pRoofEn, PtCtr, rB);
	}

	MdlDispList::CloseDL();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�����@�}�e���A���Ȃ�
//
int MdlDispList::DrawIeMdl3(
						MREAL		rB,				// �\���{��
				const	MgPoint3D	&PtCtr			// ���S���W
				)
{

	MhRoofInfo*		pRoofEn;
	MPOSITION		posR;

	if ( MdlDispList::OpenDL( 3))
		return 1;

	//	�����̃f�B�X�v���C���X�g���쐬����
	for ( pRoofEn = HaitiDb::MdGetHeadRoof( &posR); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof( &posR)) {
		if ( !MmChkValidRoof( pRoofEn))							// �I�v�V�����Ɨ����̃`�F�b�N
			continue;
		MdlDispList::DrawYane1( pRoofEn, PtCtr, rB);
	}

	MdlDispList::CloseDL();
	return 0;
}

} // namespace MC