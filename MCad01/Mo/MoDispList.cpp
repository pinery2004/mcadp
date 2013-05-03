//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdDispList.cpp
//
//		�f�B�X�v���C���X�g�쐬
//
//
//  K.Matsu           03/30/08    Created.
//==========================================================================================
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MdLib.h"

#include "MdModel.h"
#include "MdmDB.h"

#include "MdAry.h"
#include "MdAryH.h"

#define DLL_EXPORT_DISPLIST_DO
#include "MoDispList.h"

#include "MgArc.h"
#include "MgCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	MDMAX_COORDINATE_VAL	500000.0

namespace MC
{

//
//===========================================================================
//	�y�@�\�z�S�\���G���e�B�e�B�̃f�B�X�v���C���X�g���쐬����
//
	MINT DispList::DrawAllEnt(						//
				const	MgPoint3D&	i_PtCtr,		// �\���ƃ��f���̒��S
						MREAL		i_rB			// �R�����\���{��
				)
{
	MDIDSET	GidLyr;
	MDIDSET GidEnt;
	
	MINT	iCl;
	MINT	iCe;
	MDFIG	Fig;
	MDID	idLyr;
	MINT	iaWD;			//  

	// �S���C���[Id�̃Z�b�g�𓾂�
	DLyr::GetLyrIdAll( &GidLyr);
	for ( iCl=0; iCl<GidLyr.m_n; iCl++) {
		idLyr = GidLyr.m_pst[iCl];

		// �\�����[�h��OFF�̂��͖̂�������
		DLyr::GetLyrDispMode( 1, idLyr, &iaWD);
		if ( !( iaWD & MDD_MD_INDICATION))
			continue;

		// ���C���[���̑S�G���e�B�e�B�𓾂�
		DLyr::GetEnt( GidLyr.m_pst[iCl], &GidEnt);
		for ( iCe=0; iCe<GidEnt.m_n; iCe++) {

			// �G���e�B�e�B�̐}�`�𓾂�
			mdmDEnt::GetFig( GidEnt.m_pst[iCe], &Fig);

			// �}�`���f�B�X�v���C���X�g�ɒǉ�����
			DispList::DrawFig( Fig, i_PtCtr, i_rB);
		}
	}
	return 0;
}

//
//===========================================================================
//	�y�@�\�z�}�`�̃f�B�X�v���C���X�g���쐬����
//
MINT DispList::DrawFig(
						MDFIG&		i_fig,			// �}�`���
				const	MgPoint3D&	i_PtCtr,		// �\���ƃ��f���̒��S
						MREAL		i_rB			// �R�����\���{��
					)
{
	MINT		iC;
	MINT		icdPrim;
	MINT		ipPmt;

	int iN;
	MgPoint3D*	pPt;
	MgLine3D*	pLn;
	MgCir3D*		pCir;
	MgArc3D*		pArc;
	MgVect3D		Vt;
	MgLine3D		Ln;

	MgGPolyg3D	GPg(5);
	MgPolyg3D	Pg(10);

	MINT iNC;
	MgVect2D		uvd;
	MgVect2D		vd;
	MgVect2D		vdn;

	for( ipPmt=0; ipPmt<i_fig.GetN(); ipPmt=i_fig.GetNextPmt( ipPmt)) {
		icdPrim = i_fig.GetPmtCd( ipPmt);
		switch( icdPrim)
		{
		case MZCD_PNT:
		case MZCD_PNTV:
			pPt = (MgPoint3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			DispList::DrawPoint( (*pPt), i_PtCtr, i_rB);
			break;

		case MZCD_ULINE:
			pLn = (MgLine3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			Vt = (MgVect3D&)(MDMAX_COORDINATE_VAL * pLn->p[1]);
			Ln.p[0] = pLn->p[0];
			Ln.p[1] = pLn->p[0] + Vt;
			DispList::DrawLine( Ln, i_PtCtr, i_rB);
			Ln.p[1] = pLn->p[0] - Vt;
			DispList::DrawLine( Ln, i_PtCtr, i_rB);
			break;

		case MZCD_HLINE:
			pLn = (MgLine3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			Ln.p[0] = pLn->p[0];
			Ln.p[1] = pLn->p[0] + MDMAX_COORDINATE_VAL * pLn->p[1];
			DispList::DrawLine( Ln, i_PtCtr, i_rB);
			break;

		case MZCD_LINE:
			pLn = (MgLine3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
			break;

		case MZCD_PLY:
			iN = i_fig.GetPmtN( 0);
			for ( iC=0; iC<(iN - 3); iC+=3) {
				pLn = (MgLine3D*)i_fig.GetpPmt( ipPmt)->GetpDt( iC);
				DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
			}
			break;
		//	iN = i_fig.GetPmtN( 0);
		//	for ( iC=0; iC<(iN - 3); iC+=3) {
		//		pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( iC);
		//		DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	}
		//	break;

		//case MZCD_PLYV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_PAC:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_RCT:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		case MZCD_PGN:
			iN = i_fig.GetPmtN( 0);
			for ( iC=0; iC<(iN - 3); iC+=3) {
				pLn = (MgLine3D*)i_fig.GetpPmt( ipPmt)->GetpDt( iC);
				DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
			}
			Ln = MgLine3D( *(MgPoint3D*)i_fig.GetpPmt( ipPmt)->GetpDt( iC), *(MgPoint3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0));
			DispList::DrawLine( Ln, i_PtCtr, i_rB);

			DispList::SetMaterial( 0, 3);

			for ( iC=0; iC<iN; iC+=3)
				Pg += (*(MgPoint3D*)i_fig.GetpPmt( ipPmt)->GetpDt( iC));
			GPg += Pg;

			DispList::DrawPolygon( GPg, i_PtCtr, i_rB);
			break;

		//case MZCD_PGNV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_ARA:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HRCT:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HPLN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HARA:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		case MZCD_CIR:
			pCir = (MgCir3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			iNC = 32;
			
			uvd = MgVect2D( (MREAL)cos( MC_2PIE / iNC), (MREAL)sin( MC_2PIE / iNC));
			vd = MgVect2D( pCir->r, 0.);
			Ln.p[0] = pCir->Pc + MgVect3D( vd, 0.);
			for ( iC=0; iC<iNC; iC++) {
				vdn = vd & uvd;
				Ln.p[1] = pCir->Pc + MgVect3D( vdn, 0.);  
				DispList::DrawLine( Ln, i_PtCtr, i_rB);
				vd = vdn;
				Ln.p[0] = Ln.p[1];
			}
			break;

		case MZCD_ARC:
			pArc = (MgArc3D*)i_fig.GetpPmt( ipPmt)->GetpDt( 0);
			iNC = 32;

//			uvd = MgVect2D( (MREAL)cos( MC_2PIE / iNC), (MREAL)sin( MC_2PIE / iNC));
//			vd = MgVect2D( pCir->r, 0.);
//			for ( iC=0; iC<32; iC++) {

//				DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
//			}
			break;

		//case MZCD_ELN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_ELA:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_SPLN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_MPLO:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_MPLC:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_BMP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_MOJZ:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_MOJN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HSHN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HSAN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HSDN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HSRN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZCD_2D:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZCD_3D:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_LNS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_RGS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TRGS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGS2:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::Line( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGS3:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HIM:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_WIM:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_IPLN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_PLN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_LNV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_RGV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TRGV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGV2:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TGV3:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HIR:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_GSPR:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HBR:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_BOV2:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;


		//case MZCD_UNN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_GFS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_GFO:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_KKP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_KKB:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_RKP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_RKB:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HIRB:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_HIRP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_POL:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_PHIL:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_PYRA:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_TRPY:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_SPHE:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_UNNS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_LIG:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_KAN:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_PSH:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_PUL:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_ST:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_MRK:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_SLD:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_LTP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_COL:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_KCL:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_LTB:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_CA:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_CD:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_CS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_CE:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_SS:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;
	
		//case MZAT_TX:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_TXZ:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_TXP:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_REF:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_POV:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZAT_END:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_PNZ:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		//case MZCD_SAGY:
		//	pLn = (MgLine3D*)i_fig.GetP( ipPmt)->GetpDt( 0);
		//	DispList::DrawLine( (*pLn), i_PtCtr, i_rB);
		//	break;

		}
	}
	return 0;
}

} // namespace MC