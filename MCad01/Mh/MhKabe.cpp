//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhKabe.cpp
//
//		�ǃf�[�^�𐳋K������
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhDefParts.h"
#include "MmLib.h"
#include "MdLib.h"
#include "MdList.h"
#include "MsBitSet.h"
#include "MhPlcParts.h"
#include "MhPlcPartsLib.h"

#define		MAXHAIKABE		500									// �z�񐧌��l
#define		EXPKABELN		1000								// �ǐ��Z�o�p�̉�������

namespace MC
{

static bool	z_fUpdateKabe = false;								// �ǃf�[�^�@�ǉ��A�C���t���O

////////////////////////////////////////////////////////////////////////////
//    �ǃf�[�^�@�ǉ��A�C���t���O���Z�b�g����
void IeModel::MhKabeSetUpFlg()
{
	z_fUpdateKabe = true;
}

////////////////////////////////////////////////////////////////////////////
//    �ǂ𐳋K������(�������ŕ������A���i���ŘA������)
//	  ���O�Ɂ@MhKabeSetUpFlg();�@�ŏC�������������Ƃ�v�ݒ�

void IeModel::MhNormKabe(
				MINT		nProc								// �������@0 : �S�Ǐ���	
																//		  >0 : �Ō��nProc�ǂ���������
				)
{
	mhPlcParts*	pHaiKabe[MAXHAIKABE+2];							// �ǃf�[�^
	MPOSITION	pPlcPos[MAXHAIKABE+2];							// �ǃf�[�^���R�[�h�ʒu
	MINT		fPlc[MAXHAIKABE+2];								// -1: �폜��, 0: ��������̗L����, 1: �ǉ������L����, 
																//  2: �ǉ��ǂƒ[���Ō�������L����
	MINT		iPlcCn[2];										// �n�_�A�I�_�ł̑��ǂƂ̌�����
																// -2: ���ڑ�, -1: ����, >=0: ���i�ڑ�
	MINT		nHaiKabe, nHaiKabeI;							// �ǐ�

	mhPlcParts	HaiKabeI;										// �ǉ���

	MINT		ic1, ic2, icst, ics;
	MgPoint3D	po, p0, p1;
	MgLine3D		lnKabe1;
	MINT		ist, istr, istl;
	MINT		ist1, ist2;
	MINT		ist1s2, ist1e2, ist2s1, ist2e1;

	MINT		nZukei;											// �}�`�����̖{��
	MgLine3D		lnZukei[6];										// �}�`����
	MINT		szZukei;										// �}�`�����f�[�^�T�C�Y
	MINT		idivdel;										// �����폜�t���O 0: �������A1: �����A2: �폜 

	bool		fModify;

	if ( !z_fUpdateKabe) MQUIT;

	//�@�ƃ��f�����J�����g�K�̑S�Ă̕ǂ��擾����
	MINT iKai = z_mnIA.GetInpKai();
	nHaiKabeI = mhHaitiIn::GetParts( iKai, MP_GP_TAIRYOKU, Mstr( "��"), NULL, MAXHAIKABE, pHaiKabe, pPlcPos);
																					// �ƃ��f�����J�����g�K�̑S�Ă̕ǂ��擾����
		ASSERT( nHaiKabeI >= 0);													//		�ǐ��I�[�o�[�t���[�@<ERROR>
	nHaiKabe = nHaiKabeI;
	for ( ic1=nHaiKabe-1; ic1>=0; ic1--) fPlc[ic1] = 0;								// �L����

	//	�ǉ��C���ǂ̕ǃf�[�^�̐擪�ʒu�����߂�
	if ( nProc == 0)
		icst = 0;																	// �S�ǌ���
	else
		icst = max( nHaiKabe - nProc, 0);											// �Ō��[nProc]�̕ǂ�ǉ��ǂƂ��ď�������

	for ( ic1=icst; ic1<nHaiKabe; ic1++) fPlc[ic1] = 1;								// �ǉ���

	//	�����ǂ𕪊����A�d�Ȃ�ǂ��폜����
	ics = icst;
	for ( ic1=0; ic1<nHaiKabe; ic1++) {												// ��1
		if ( fPlc[ic1] < 0)
			continue;																// �폜�ǂ͔�r�ΏۊO
		idivdel = 0;
		if ( ic1 >= icst) ics = 0;
		for ( ic2=ics; ic2<nHaiKabe; ic2++) {										// ��2
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// ����ǂƍ폜�ǂ͔�r�ΏۊO
			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKabe[ic1]->m_lnPlc)),
								   MgMinMaxR2D( MgLine2DC(pHaiKabe[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[0], pHaiKabe[ic1]->m_lnPlc, &ist2s1);	// ��2�̎n�_����1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[1], pHaiKabe[ic1]->m_lnPlc, &ist2e1);	// ��2�̏I�_����1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic1]->m_lnPlc.p[0], pHaiKabe[ic2]->m_lnPlc, &ist1s2);	// ��1�̎n�_����2�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic1]->m_lnPlc.p[1], pHaiKabe[ic2]->m_lnPlc, &ist1e2);	// ��1�̏I�_����2�̂ǂ��ɏ���Ă��邩���ׂ�
					// �d�Ȃ��Ċ܂܂��ǂ��폜����
				if ( ( ist1s2 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				// ��1����2�ɏd�Ȃ�܂��͊܂܂��ꍇ				*** �O�ǁA���ǂ̒����c ***
					( ist1e2 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					idivdel = 2;													//		��1���폜
				} else if ( ist2s1 & MC_INSIDE) {									// ��2�̎n�_����1���ŏd�Ȃ��Ă���
					po = pHaiKabe[ic2]->m_lnPlc.p[0];								//		��1���2�̎n�_�ŕ���
					idivdel = 1;
				} else if ( ist2e1 & MC_INSIDE) {									// ��2�̏I�_����1���ŏd�Ȃ��Ă���
					po = pHaiKabe[ic2]->m_lnPlc.p[1];								//		��1���2�̏I�_�ŕ���
					idivdel = 1;
				} else {
					continue;														// �d�Ȃ薳���̕ǂ͕����ΏۊO
				}
			}

			if ( idivdel == 0) {
				ist = MGeo::Intr2Line3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc, &po);
				if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {					// ����
					ist = MGeo::CheckPointOnLine3DWS( po, pHaiKabe[ic1]->m_lnPlc, &ist1);
					if ( ist1 == (MC_ON_LINE | MC_INSIDE)) {						// ��1�̓����Ō��������蕪������
						idivdel = 1;
					} else {
						if ( fPlc[ic2] == 1)										// �ǉ��ǂƒ[���Ō��������
							fPlc[ic1] = 2;
					}
				}
			}

			if ( idivdel == 1) {													// ����
				ASSERT( nHaiKabe < MAXHAIKABE);										//		�ǐ��I�[�o�[�t���[�@<ERROR>

				HaiKabeI.Copy( *pHaiKabe[ic1]);										//		�����Ώۂ̕ǂƓ�����e�̒ǉ��ǃf�[�^���쐬����

				fPlc[ic1] = -1;

//D				MINT ist1;
				mhPlcParts *pPlcEnM;
//D				ist1 = MdPartsModify( pHaiKabe[ic1], &pPlcEnM);						//		�C���惌�R�[�h�����߂�
				HaitiDb::MdPartsModify( pHaiKabe[ic1], &pPlcEnM);								//		�C���惌�R�[�h�����߂�

//D				if ( ist1 == 3) {
					pPlcEnM->m_lnPlc.p[1] = po;										//		���̕ǂ͎n�_��������_�܂Ŏc��
					pPlcPos[nHaiKabe] = (MPOSITION)( pPlcEnM - HaitiDb::MdGetSizeOfHd());
					pHaiKabe[nHaiKabe] = pPlcEnM;
//D				} else {
//D					pHaiKabe[ic1]->m_lnPlc.p[1] = po;								//		���̕ǂ͎n�_��������_�܂Ŏc��
//D					pPlcPos[nHaiKabe] = pPlcPos[ic1];
//D					pHaiKabe[nHaiKabe] = pHaiKabe[ic1];
//D				}
				fPlc[nHaiKabe] = 0;
				nHaiKabe++;

				HaiKabeI.m_lnPlc.p[0] = po;											//		�ǉ��ǂ͌����_����I�_�܂Ŏc��
				pPlcPos[nHaiKabe] = HaitiDb::MdPartsAdd( &HaiKabeI, 1);				//		�����ɂ��ǂ�ǉ�
				pHaiKabe[nHaiKabe] = (mhPlcParts*)HaitiDb::MdPartsGet( pPlcPos[nHaiKabe]);

				fPlc[nHaiKabe] = 0;
				nHaiKabe++;
				break;

			} else if ( idivdel == 2) {												// �폜
				HaitiDb::MdPartsDelete( pPlcPos[ic1]);								//		��1���폜
				fPlc[ic1] = -1;
				break;
			}
		}
	}

	//	�ǂ̘A��
	for ( ic1=icst; ic1<nHaiKabe; ic1++) {
		if ( fPlc[ic1] < 0)
			continue;																// �폜�ǂ͔�r�ΏۊO
		fModify = false;
		iPlcCn[0] = -2;																// �n�_���A���ǂȂ�
		iPlcCn[1] = -2;																// �I�_���A���ǂȂ�
		lnKabe1 = pHaiKabe[ic1]->m_lnPlc;											// ���������Z�o�p

		for ( ic2=0; ic2<nHaiKabe; ic2++) {
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// ����ǂƍ폜�ǂ͔�r�ΏۊO
			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKabe[ic1]->m_lnPlc)),
					   MgMinMaxR2D( MgLine2DC( pHaiKabe[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[0], pHaiKabe[ic1]->m_lnPlc, &ist2s1);	// ��2�̎n�_����1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[1], pHaiKabe[ic1]->m_lnPlc, &ist2e1);	// ��2�̏I�_����1�̂ǂ��ɏ���Ă��邩���ׂ�

				if ( ( ist2s1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				// ��2����1�ɏd�Ȃ�܂��͊܂܂��ꍇ��			*** �O�ǁA���ǂ̒����c ***
					( ist2e1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					ASSERT( FALSE);													//		�d�Ȃ蕔�͍폜�ς݂Ȃ̂ŏ����G���[�@<ERROR>

				} else if ( (( ist2s1 & MC_ON_PS) || ( ist2e1 & MC_ON_PS)) && ( iPlcCn[0] == -2)) {
																					// ��1�̎n�_�ŒP��A��
					if ( ist2s1 & MC_ON_PS) {										//		��2�̎n�_�ŘA��
						lnKabe1.p[0] = pHaiKabe[ic2]->m_lnPlc.p[1];
					} else if ( ist2e1 & MC_ON_PS) {								//		��2�̏I�_�ŘA��
						lnKabe1.p[0] = pHaiKabe[ic2]->m_lnPlc.p[0];
					}
					iPlcCn[0] = ic2;												//		�n�_���ɘA������ǂ�ݒ�

				} else if ( (( ist2s1 & MC_ON_PE) || ( ist2e1 & MC_ON_PE)) && ( iPlcCn[1] == -2)) {
																					// ��1�̏I�_�ŒP��A��
					if ( ist2s1 & MC_ON_PE) {										//		��2�̎n�_�ŘA��
						lnKabe1.p[1] = pHaiKabe[ic2]->m_lnPlc.p[1];
					} else if ( ist2e1 & MC_ON_PE) {								//		��2�̏I�_�ŘA��
						lnKabe1.p[1] = pHaiKabe[ic2]->m_lnPlc.p[0];
					}
					iPlcCn[1] = ic2;												// �I�_���ɘA������ǂ�ݒ�
				}
				continue;
			}

			ist = MGeo::Intr2Line3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc, &po);
			if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {						// ����( �܂��� �A��)(�A���͑O�̕��s�����ŃX�L�b�v���ꂱ���ɂ͓���Ȃ�)
				ist = MGeo::CheckPointOnLine3DWS( po, pHaiKabe[ic1]->m_lnPlc, &ist1);
					if ( ist1 == (MC_ON_LINE | MC_INSIDE))							// �Ǔ����Ō�������
					ASSERT( FALSE);													//		�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>
				// �����ǂ̐}�`�쐬
				if ( ist1 == (MC_ON_LINE | MC_ON_PS)) {
					iPlcCn[0] = -1;													//		�n�_���Ɍ�������ǂ����ݒ�
				} else if ( ist1 == (MC_ON_LINE | MC_ON_PE)) {
					iPlcCn[1] = -1;													// 		�I�_���Ɍ�������ǂ����ݒ�
				}
			}
		}
		if ( iPlcCn[0] >= 0) {
			pHaiKabe[ic1]->m_lnPlc.p[0] = lnKabe1.p[0];								// �ǂP������
			HaitiDb::MdPartsDelete( pPlcPos[iPlcCn[0]]);										// �n�_���P��A���ǂ��폜
			fPlc[iPlcCn[0]] = -1;
			fModify = true;
		}
		if ( iPlcCn[1] >= 0) {
			pHaiKabe[ic1]->m_lnPlc.p[1] = lnKabe1.p[1];								// �ǂP������
			HaitiDb::MdPartsDelete( pPlcPos[iPlcCn[1]]);							// �I�_���P��A���ǂ��폜
			fPlc[iPlcCn[1]] = -1;
			fModify = true;
		}
		if ( fModify)
			ic1--;
	}

	//	�ǂ̉��̐}�`�쐬
	szZukei = sizeof(MhZukei) + sizeof(MgLine3D);									// �����Q�{���̐}�`�f�[�^�T�C�Y

	for ( ic1=0; ic1<nHaiKabe; ic1++) {
		if ( fPlc[ic1] < 0 || (fPlc[ic1] != 2 && ic1 < icst))
			continue;																// �폜�ǂ܂��͒ǉ��C���ȊO�̕ǂŒǉ��C���ǂƖ������͑ΏۊO
		lnKabe1 = pHaiKabe[ic1]->m_lnPlc;											// ���������Z�o�p
//		MgVect3D	vtutLn1 = MGeo::UnitizeVect3D( MgVect3DC( lnKabe1));
		MgVect3D	vw = MgVect3DC( lnKabe1);
		MgVect3D	vtutLn1 = MGeo::UnitizeVect3D( vw);
		lnKabe1.p[0] = lnKabe1.p[0] - vtutLn1 * EXPKABELN;
		lnKabe1.p[1] = lnKabe1.p[1] + vtutLn1 * EXPKABELN;

		if ( pHaiKabe[ic1]->m_pZukei == NULL) {
			pHaiKabe[ic1]->m_pZukei = (MhZukei*)new char[szZukei];					// �}�`����
			pHaiKabe[ic1]->m_pZukei->m_pNext = NULL;
		}

		pHaiKabe[ic1]->m_pZukei->m_isNZukei = 2;
		pHaiKabe[ic1]->m_pZukei->m_lnZukei[0] = lnKabe1 + vtutLn1.RotR90() * pHaiKabe[ic1]->GetMbWidthR();
		pHaiKabe[ic1]->m_pZukei->m_lnZukei[1] = lnKabe1 + vtutLn1.RotL90() * pHaiKabe[ic1]->GetMbWidthL();
	}

	//	�ǂ̉��̐}�`�������ǂŃJ�b�g�����K�̐}�`�쐬
	for ( ic1=0; ic1<nHaiKabe; ic1++) {
		if ( fPlc[ic1] < 0 || (fPlc[ic1] != 2 && ic1 < icst))
			continue;																// �폜�ǂ܂��͒ǉ��C���ȊO�̕ǂŒǉ��C���ǂƖ������͑ΏۊO
		iPlcCn[0] = -2;																// �n�_���A���ǂȂ�
		iPlcCn[1] = -2;																// �I�_���A���ǂȂ�
		nZukei = 2;
		lnZukei[0] = pHaiKabe[ic1]->m_pZukei->m_lnZukei[0];							// �}�`���� �E��
		lnZukei[1] = pHaiKabe[ic1]->m_pZukei->m_lnZukei[1];							// �}�`����	����
		lnKabe1 = pHaiKabe[ic1]->m_lnPlc;											// �ǐ��`��Z�o�p�ǐc��
		for ( ic2=0; ic2<nHaiKabe; ic2++) {
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// ����ǂƍ폜�ǂ͔�r�ΏۊO

			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKabe[ic1]->m_lnPlc)),
							MgMinMaxR2D( MgLine2DC( pHaiKabe[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[0], pHaiKabe[ic1]->m_lnPlc, &ist2s1);	// ��2�̎n�_����1�̂ǂ��ɏ���Ă��邩���ׂ�
//				if ( !( ist1 & MC_ON_LINE))
//					continue;														// ����Ă���ǂ͌����ΏۊO
				ist = MGeo::CheckPointOnLine3DWS( pHaiKabe[ic2]->m_lnPlc.p[1], pHaiKabe[ic1]->m_lnPlc, &ist2e1);	// ��2�̏I�_����1�̂ǂ��ɏ���Ă��邩���ׂ�

				if ( ( ist2s1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				// ��2����1�ɏd�Ȃ�܂��͊܂܂��ꍇ��			*** �O�ǁA���ǂ̒����c ***
					( ist2e1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					ASSERT( FALSE);													//		�d�Ȃ蕔�͍폜�ς݂Ȃ̂ŏ����G���[�@<ERROR>

				} else if ( (( ist2s1 & MC_ON_PS) || ( ist2e1 & MC_ON_PS)) && ( iPlcCn[0] == -2)) {
																					// ��1�̎n�_�ŒP��A��
					iPlcCn[0] = ic2;												//		�n�_���ɘA������ǂ�ݒ�

				} else if ( (( ist2s1 & MC_ON_PE) || ( ist2e1 & MC_ON_PE)) && ( iPlcCn[1] == -2)) {
																					// ��1�̏I�_�ŒP��A��
					iPlcCn[1] = ic2;												//		�I�_���ɘA������ǂ�ݒ�
				}
				continue;
			}

			ist = MGeo::Intr2Line3D( pHaiKabe[ic1]->m_lnPlc, pHaiKabe[ic2]->m_lnPlc, &po);
			if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {						// ����( �܂��� �A��)(�A���͑O�̕��s�����ŃX�L�b�v���ꂱ���ɂ͓���Ȃ�)
				ist = MGeo::CheckPointOnLine3DWS( po, pHaiKabe[ic1]->m_lnPlc, &ist1);
				if ( ist1 == (MC_ON_LINE | MC_INSIDE))								// �Ǔ����Ō�������
					ASSERT( FALSE);													//		�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>
				ist = MGeo::CheckPointOnLine3DWS( po, pHaiKabe[ic2]->m_lnPlc, &ist2);
				if ( ist2 == (MC_ON_LINE | MC_INSIDE))								// �Ǔ����Ō�������
					ASSERT( FALSE);													// 		�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>

				// �����ǂ̐}�`�쐬
                MgVect3D vtutLn2 = MGeo::UnitizeVect3D( MgVect3DC( pHaiKabe[ic2]->m_lnPlc));
				MgULine3D ULnR = MgULine3D( pHaiKabe[ic2]->m_pZukei->m_lnZukei[0].p[0], vtutLn2);
				MgULine3D ULnL = MgULine3D( pHaiKabe[ic2]->m_pZukei->m_lnZukei[1].p[0], vtutLn2);

				if ( ( ist1 & (MC_ON_PS | MC_ON_PE)) == ( ist2 & (MC_ON_PS | MC_ON_PE))) {	// �ǂ̌������Ό�
					istr = MGeo::IntrLineULine3D( lnZukei[0], ULnL, &p0);
					istl = MGeo::IntrLineULine3D( lnZukei[1], ULnR, &p1);
				} else {															// �ǂ̌�����������
					istr = MGeo::IntrLineULine3D( lnZukei[0], ULnR, &p0);
					istl = MGeo::IntrLineULine3D( lnZukei[1], ULnL, &p1);
				}
				if ( ist1 & MC_ON_PS) {
					if ( MF_CHECK_OR( istr, (MC_INT | MC_CONNECTION))) lnZukei[0].p[0] = p0;
					if ( MF_CHECK_OR( istl, (MC_INT | MC_CONNECTION))) lnZukei[1].p[0] = p1;
					iPlcCn[0] = -1;													// �n�_�_���Ɍ�������ǂ����ݒ�
				} else if ( ist1 == (MC_ON_LINE | MC_ON_PE)) {
					if ( MF_CHECK_OR( istr, (MC_INT | MC_CONNECTION))) lnZukei[0].p[1] = p0;
					if ( MF_CHECK_OR( istl, (MC_INT | MC_CONNECTION))) lnZukei[1].p[1] = p1;
					iPlcCn[1] = -1;													// �I�_���Ɍ�������ǂ����ݒ�
				}
			}
		}

		if ( iPlcCn[0] == -2 || iPlcCn[1] == -2) {
			MgVect3D	vtutLn1 = MGeo::UnitizeVect3D( MgVect3DC( lnKabe1));
			lnKabe1.p[0] = lnKabe1.p[0] - vtutLn1 * 44.5;
			lnKabe1.p[1] = lnKabe1.p[1] + vtutLn1 * 44.5;

			if ( iPlcCn[0] == -2) {													// �n�_���J���[
				lnZukei[0].p[0] = lnKabe1.p[0] + vtutLn1.RotR90() * pHaiKabe[ic1]->GetMbWidthR();
				lnZukei[1].p[0] = lnKabe1.p[0] + vtutLn1.RotL90() * pHaiKabe[ic1]->GetMbWidthL();
				lnZukei[nZukei].p[0] = lnZukei[1].p[0];
				lnZukei[nZukei].p[1] = lnZukei[0].p[0];
				nZukei++;
			}
			if ( iPlcCn[1] == -2) {													// �I�_���J���[
				lnZukei[0].p[1] = lnKabe1.p[1] + vtutLn1.RotR90() * pHaiKabe[ic1]->GetMbWidthR();
				lnZukei[1].p[1] = lnKabe1.p[1] + vtutLn1.RotL90() * pHaiKabe[ic1]->GetMbWidthL();
				lnZukei[nZukei].p[0] = lnZukei[0].p[1];
				lnZukei[nZukei].p[1] = lnZukei[1].p[1];
				nZukei++;
			}
		}

		if ( nZukei > pHaiKabe[ic1]->m_pZukei->m_isNZukei) {
			szZukei = sizeof(MhZukei) + sizeof(MgLine3D) * (nZukei - 1);			// ����nZukei�{���̐}�`�f�[�^�T�C�Y
			MBFREE(pHaiKabe[ic1]->m_pZukei);
			pHaiKabe[ic1]->m_pZukei = (MhZukei*)new char[szZukei];					// �}�`����
			pHaiKabe[ic1]->m_pZukei->m_pNext = NULL;
		}

		lnZukei[1].SetRev();
		for ( ic2=0; ic2<nZukei; ic2++)
			pHaiKabe[ic1]->m_pZukei->m_lnZukei[ic2] = lnZukei[ic2];
		pHaiKabe[ic1]->m_pZukei->m_isNZukei = nZukei;
	}

	z_fUpdateKabe = false;
exit:;
//DBG #ifdef _DEBUG
//DBG	Msprintf_s( mlLog::m_Str, Mstr( "MhNormKabe ===================================\n"));
//DBG	MBLOGPRBF;
//DBG	BuzaiCode::MhPrintallmhPlcParts( Mstr( "MhNormKabe"));
//DBG #endif
}

} // namespace MC
