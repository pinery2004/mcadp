//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhKiso.cpp
//
//		��b�f�[�^�𐳋K������
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"
#include "MhDefParts.h"
#include "MmLib.h"
#include "MdLib.h"
#include "MdList.h"
#include "MsBitSet.h"
#include "MhPlcParts.h"
#include "MhPlcPartsLib.h"

#define		MAXHAIKISO		500									// �z�񐧌��l
#define		EXPKISOLN		1000								// ��b���Z�o�p�̉�������

namespace MC
{

static bool	z_fUpdateKiso = false;								// ��b�f�[�^�@�ǉ��A�C���t���O

////////////////////////////////////////////////////////////////////////////
//    ��b�f�[�^�@�ǉ��A�C���t���O���Z�b�g����
void IeModel::MhKisoSetUpFlg()
{
	z_fUpdateKiso = true;
}

////////////////////////////////////////////////////////////////////////////
//    ��b�𐳋K������(�������ŕ������A���i���ŘA������)
//	  ���O�Ɂ@MhKisoSetUpFlg();�@�ŏC�������������Ƃ�v�ݒ�

void IeModel::MhNormKiso(
				MINT		nProc								// �������@0 : �S��b����	
																//		  >0 : �Ō��nProc��b����������
				)
{
	mhPlcParts* pHaiKiso[MAXHAIKISO+2];							// ��b�f�[�^
	MPOSITION	pPlcPos[MAXHAIKISO+2];							// ��b�f�[�^���R�[�h�ʒu
	MINT		fPlc[MAXHAIKISO+2];								// -1: �폜��b, 0: ��������̗L����b, 1: �ǉ������L����b, 
																//  2: �ǉ���b�ƒ[���Ō�������L����b
	MINT		iPlcCn[2];										// �n�_�A�I�_�ł̑���b�Ƃ̌�����
																// -2: ���ڑ�, -1: ����, >=0: ���i�ڑ�
	MINT		nHaiKiso, nHaiKisoI;							// ��b��
	mhPlcParts	HaiKisoI;										// �ǉ���b

	MINT		ic1, ic2, icst, ics;
	MgPoint3D	po, p0, p1;
	MgLine3D		lnKiso1;
	MINT		ist, istr, istl;
	MINT		ist1, ist2;
	MINT		ist1s2, ist1e2, ist2s1, ist2e1;

	MINT		nZukei;											// �}�`�����̖{��
	MgLine3D		lnZukei[6];									// �}�`����
	MINT		szZukei;										// �}�`�����f�[�^�T�C�Y
	MINT		idivdel;										// �����폜�t���O 0: �������A1: �����A2: �폜 

	bool		fModify;

//	if ( !z_fUpdateKiso && nProc != 0) MQUIT;
	if ( !z_fUpdateKiso) MQUIT;

	//�@�ƃ��f�����J�����g�K�̑S�Ă̊�b���擾����
	MINT iKai = z_mnIA.GetInpKai();
	nHaiKisoI = mhHaitiIn::GetParts( iKai, MP_GP_KISO, Mstr( "��b"), NULL, MAXHAIKISO, pHaiKiso, pPlcPos);
																					// �ƃ��f�����J�����g�K�̑S�Ă̊�b���擾����
		ASSERT( nHaiKisoI >= 0);													//		��b���I�[�o�[�t���[�@<ERROR>
	nHaiKiso = nHaiKisoI;
	for ( ic1=nHaiKiso-1; ic1>=0; ic1--) fPlc[ic1] = 0;								// �L����b

	//	�ǉ��C����b�̊�b�f�[�^�̐擪�ʒu�����߂�
	if ( nProc == 0)
		icst = 0;																	// �S��b����
	else
		icst = max( nHaiKiso - nProc, 0);											// �Ō��[nProc]�̊�b���ǉ��C����b�Ƃ��ď�������

	for ( ic1=icst; ic1<nHaiKiso; ic1++) fPlc[ic1] = 1;								// �ǉ���b

	//	������b�𕪊����A�d�Ȃ��b���폜����
	ics = icst;
	for ( ic1=0; ic1<nHaiKiso; ic1++) {												// ��b1
		if ( fPlc[ic1] < 0)
			continue;																// �폜��b�͔�r�ΏۊO
		idivdel = 0;
		if ( ic1 >= icst) ics = 0;
		for ( ic2=ics; ic2<nHaiKiso; ic2++) {										// ��b2
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// �����b�ƍ폜��b�͔�r�ΏۊO
			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKiso[ic1]->m_lnPlc)),
						    MgMinMaxR2D( MgLine2DC(pHaiKiso[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[0], pHaiKiso[ic1]->m_lnPlc, &ist2s1);	// ��b2�̎n�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[1], pHaiKiso[ic1]->m_lnPlc, &ist2e1);	// ��b2�̏I�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic1]->m_lnPlc.p[0], pHaiKiso[ic2]->m_lnPlc, &ist1s2);	// ��b1�̎n�_����b2�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic1]->m_lnPlc.p[1], pHaiKiso[ic2]->m_lnPlc, &ist1e2);	// ��b1�̏I�_����b2�̂ǂ��ɏ���Ă��邩���ׂ�
					// �d�Ȃ��Ċ܂܂���b���폜����
				if ( ( ist1s2 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				//		��b1����b2�ɏd�Ȃ�܂��͊܂܂��ꍇ				*** �O��b�A����b�̒����c ***
					( ist1e2 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					idivdel = 2;													//			��b1���폜
				} else if ( ist2s1 & MC_INSIDE) {									//		��b2�̎n�_����b1���ŏd�Ȃ��Ă���
					po = pHaiKiso[ic2]->m_lnPlc.p[0];								//			��b1����b2�̎n�_�ŕ���
					idivdel = 1;
				} else if ( ist2e1 & MC_INSIDE) {									//		��b2�̏I�_����b1���ŏd�Ȃ��Ă���
					po = pHaiKiso[ic2]->m_lnPlc.p[1];								//			��b1����b2�̏I�_�ŕ���
					idivdel = 1;
				} else {
					continue;														//		�d�Ȃ薳���̊�b�͕����ΏۊO
				}
			}

			if ( idivdel == 0) {
				ist = MGeo::Intr2Line3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc, &po);
				if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {					// ����
					ist = MGeo::CheckPointOnLine3D( po, pHaiKiso[ic1]->m_lnPlc, &ist1);
					if ( ist1 == (MC_ON_SLINE | MC_INSIDE)) {						//		��b1�̓����Ō��������蕪������
						idivdel = 1;
					} else {
						if ( fPlc[ic2] == 1)										//		�ǉ���b�ƒ[���Ō��������b
							fPlc[ic1] = 2;
					}
				}
			}

			if ( idivdel == 1) {													// ����
				ASSERT( nHaiKiso < MAXHAIKISO);										//		��b���I�[�o�[�t���[�@<ERROR>

				HaiKisoI = *pHaiKiso[ic1];											//		�����Ώۂ̊�b�Ɠ�����e�̒ǉ���b�f�[�^���쐬����
				HaiKisoI.m_pZukei = NULL;

				fPlc[ic1] = -1;

				pHaiKiso[ic1]->m_lnPlc.p[1] = po;									//		���̊�b�͎n�_��������_�܂Ŏc��
				pPlcPos[nHaiKiso] = pPlcPos[ic1];
				pHaiKiso[nHaiKiso] = pHaiKiso[ic1];
				fPlc[nHaiKiso] = 0;
				nHaiKiso++;

				HaiKisoI.m_lnPlc.p[0] = po;											//		�ǉ���b�͌����_����I�_�܂Ŏc��
				pPlcPos[nHaiKiso] = HaitiDb::MdPartsAdd( &HaiKisoI, 1);						//		�����ɂ���b��ǉ�
				pHaiKiso[nHaiKiso] = (mhPlcParts*)HaitiDb::MdPartsGet( pPlcPos[nHaiKiso]);
				fPlc[nHaiKiso] = 0;
				nHaiKiso++;
				break;

			} else if ( idivdel == 2) {												// �폜
				HaitiDb::MdPartsDelete( pPlcPos[ic1]);										//		��b1���폜
				fPlc[ic1] = -1;
				break;
			}
		}
	}

	//	��b�̘A��
	for ( ic1=icst; ic1<nHaiKiso; ic1++) {
		if ( fPlc[ic1] < 0)
			continue;																// �폜��b�͔�r�ΏۊO
		fModify = false;
		iPlcCn[0] = -2;																// �n�_���A����b�Ȃ�
		iPlcCn[1] = -2;																// �I�_���A����b�Ȃ�
		lnKiso1 = pHaiKiso[ic1]->m_lnPlc;											// ���������Z�o�p

		for ( ic2=0; ic2<nHaiKiso; ic2++) {
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// �����b�ƍ폜��b�͔�r�ΏۊO
			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKiso[ic1]->m_lnPlc)),
							MgMinMaxR2D( MgLine2DC( pHaiKiso[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[0], pHaiKiso[ic1]->m_lnPlc, &ist2s1);	// ��b2�̎n�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[1], pHaiKiso[ic1]->m_lnPlc, &ist2e1);	// ��b2�̏I�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�

				if ( ( ist2s1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				//		��b2����b1�ɏd�Ȃ�܂��͊܂܂��ꍇ��			*** �O��b�A����b�̒����c ***
					( ist2e1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					ASSERT( FALSE);													//			�d�Ȃ蕔�͍폜�ς݂Ȃ̂ŏ����G���[�@<ERROR>

				} else if ( (( ist2s1 & MC_ON_PS) || ( ist2e1 & MC_ON_PS)) && ( iPlcCn[0] == -2)) {
																					//		��b1�̎n�_�ŒP��A��
					if ( ist2s1 & MC_ON_PS) {										//			��b2�̎n�_�ŘA��
						lnKiso1.p[0] = pHaiKiso[ic2]->m_lnPlc.p[1];
//						fPlc[ic2] = 2;												// �ǉ��C����b�ƌ��������ݒ�
					} else if ( ist2e1 & MC_ON_PS) {								//			��b2�̏I�_�ŘA��
						lnKiso1.p[0] = pHaiKiso[ic2]->m_lnPlc.p[0];
//						fPlc[ic2] = 2;												// �ǉ��C����b�ƌ��������ݒ�
					}
					iPlcCn[0] = ic2;												//			�n�_���ɘA�������b��ݒ�

				} else if ( (( ist2s1 & MC_ON_PE) || ( ist2e1 & MC_ON_PE)) && ( iPlcCn[1] == -2)) {
																					//		��b1�̏I�_�ŒP��A��
					if ( ist2s1 & MC_ON_PE) {										//			��b2�̎n�_�ŘA��
						lnKiso1.p[1] = pHaiKiso[ic2]->m_lnPlc.p[1];
//						fPlc[ic2] = 2;												// �ǉ��C����b�ƌ��������ݒ�
					} else if ( ist2e1 & MC_ON_PE) {								//			��b2�̏I�_�ŘA��
						lnKiso1.p[1] = pHaiKiso[ic2]->m_lnPlc.p[0];
//						fPlc[ic2] = 2;												// �ǉ��C����b�ƌ��������ݒ�
					}
					iPlcCn[1] = ic2;												//			�I�_���ɘA�������b��ݒ�
				}
				continue;
			}

			ist = MGeo::Intr2Line3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc, &po);
			if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {						// ����( �܂��� �A��)(�A���͑O�̕��s�����ŃX�L�b�v���ꂱ���ɂ͓���Ȃ�)
				ist = MGeo::CheckPointOnLine3D( po, pHaiKiso[ic1]->m_lnPlc, &ist1);
					if ( ist1 == (MC_ON_SLINE | MC_INSIDE))							//		��b�����Ō�������
					ASSERT( FALSE);													//			�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>
				// ������b�̐}�`�쐬
				if ( ist1 == (MC_ON_SLINE | MC_ON_PS)) {
					iPlcCn[0] = -1;													//			�n�_���Ɍ��������b�����ݒ�
				} else if ( ist1 == (MC_ON_SLINE | MC_ON_PE)) {
					iPlcCn[1] = -1;													//			�I�_���Ɍ��������b�����ݒ�
				}
//				fPlc[ic2] = 2;														// �ǉ��C����b�ƌ��������ݒ�
			}
		}
		if ( iPlcCn[0] >= 0) {
			pHaiKiso[ic1]->m_lnPlc.p[0] = lnKiso1.p[0];								// ��b�P������
			HaitiDb::MdPartsDelete( pPlcPos[iPlcCn[0]]);							// �n�_���P��A����b���폜
			fPlc[iPlcCn[0]] = -1;
			fModify = true;
		}
		if ( iPlcCn[1] >= 0) {
			pHaiKiso[ic1]->m_lnPlc.p[1] = lnKiso1.p[1];								// ��b�P������
			HaitiDb::MdPartsDelete( pPlcPos[iPlcCn[1]]);							// �I�_���P��A����b���폜
			fPlc[iPlcCn[1]] = -1;
			fModify = true;
		}
		if ( fModify)
			ic1--;
//		if ( iPlcCn[0] != 0 || iPlcCn[1] != 0)
//			fPlc[ic2] = 2;															// �ǉ��C����b�ƌ��������ݒ�
	}

	//	��b�̉��̐}�`�쐬
	szZukei = sizeof(MhZukei) + sizeof(MgLine3D);									// �����Q�{���̐}�`�f�[�^�T�C�Y

	for ( ic1=0; ic1<nHaiKiso; ic1++) {
		if ( fPlc[ic1] < 0 || (fPlc[ic1] != 2 && ic1 < icst))
			continue;																// �폜��b�܂��͒ǉ��C���ȊO�̊�b�Œǉ��C����b�Ɩ������͑ΏۊO
		lnKiso1 = pHaiKiso[ic1]->m_lnPlc;											// ���������Z�o�p
		MgVect3D	vtutLn1 = MGeo::UnitizeVect3D( MgVect3DC( lnKiso1));
		lnKiso1.p[0] = lnKiso1.p[0] - vtutLn1 * EXPKISOLN;
		lnKiso1.p[1] = lnKiso1.p[1] + vtutLn1 * EXPKISOLN;

		if ( pHaiKiso[ic1]->m_pZukei == NULL) {
			pHaiKiso[ic1]->m_pZukei = (MhZukei*)new char[szZukei];					// �}�`����
			pHaiKiso[ic1]->m_pZukei->m_pNext = NULL;
		}

		pHaiKiso[ic1]->m_pZukei->m_isNZukei = 2;
		pHaiKiso[ic1]->m_pZukei->m_lnZukei[0] = lnKiso1 + vtutLn1.RotR90() * pHaiKiso[ic1]->GetMbWidthR();
		pHaiKiso[ic1]->m_pZukei->m_lnZukei[1] = lnKiso1 + vtutLn1.RotL90() * pHaiKiso[ic1]->GetMbWidthL();
	}

	//	��b�̉��̐}�`��������b�ŃJ�b�g�����K�̐}�`�쐬
	for ( ic1=0; ic1<nHaiKiso; ic1++) {
		if ( fPlc[ic1] < 0 || (fPlc[ic1] != 2 && ic1 < icst))
			continue;																// �폜��b�܂��͒ǉ��C���ȊO�̊�b�Œǉ��C����b�Ɩ������͑ΏۊO
		iPlcCn[0] = -2;																// �n�_���A����b�Ȃ�
		iPlcCn[1] = -2;																// �I�_���A����b�Ȃ�
		nZukei = 2;
		lnZukei[0] = pHaiKiso[ic1]->m_pZukei->m_lnZukei[0];							// �}�`���� �E��
		lnZukei[1] = pHaiKiso[ic1]->m_pZukei->m_lnZukei[1];							// �}�`����	����
		lnKiso1 = pHaiKiso[ic1]->m_lnPlc;											// ��b���`��Z�o�p��b�c��
		for ( ic2=0; ic2<nHaiKiso; ic2++) {
			if ( ic1 == ic2 || fPlc[ic2] < 0)
				continue;															// �����b�ƍ폜��b�͔�r�ΏۊO

			if ( !MGeo::CheckMinmaxROnMinmaxR2D( MgMinMaxR2D( MgLine2DC( pHaiKiso[ic1]->m_lnPlc)),
							MgMinMaxR2D( MgLine2DC( pHaiKiso[ic2]->m_lnPlc))))
				continue;															// MinMax�̏d�Ȃ�Ȃ��̏ꍇ�͔�r�ΏۊO
			if ( MGeo::ParallelLine3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc)) {	// ���s
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[0], pHaiKiso[ic1]->m_lnPlc, &ist2s1);	// ��b2�̎n�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�
//				if ( !( ist1 & MC_ON_SLINE))
//					continue;														//		����Ă����b�͌����ΏۊO
				ist = MGeo::CheckPointOnLine3D( pHaiKiso[ic2]->m_lnPlc.p[1], pHaiKiso[ic1]->m_lnPlc, &ist2e1);	// ��b2�̏I�_����b1�̂ǂ��ɏ���Ă��邩���ׂ�

				if ( ( ist2s1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE)) &&				//		��b2����b1�ɏd�Ȃ�܂��͊܂܂��ꍇ��			*** �O��b�A����b�̒����c ***
					( ist2e1 & (MC_ON_PS | MC_INSIDE | MC_ON_PE))) {
					ASSERT( FALSE);													//			�d�Ȃ蕔�͍폜�ς݂Ȃ̂ŏ����G���[�@<ERROR>

				} else if ( (( ist2s1 & MC_ON_PS) || ( ist2e1 & MC_ON_PS)) && ( iPlcCn[0] == -2)) {
																					//		��b1�̎n�_�ŒP��A��
					iPlcCn[0] = ic2;												//			�n�_���ɘA�������b��ݒ�

				} else if ( (( ist2s1 & MC_ON_PE) || ( ist2e1 & MC_ON_PE)) && ( iPlcCn[1] == -2)) {
																					//		��b1�̏I�_�ŒP��A��
					iPlcCn[1] = ic2;												//			�I�_���ɘA�������b��ݒ�
				}
				continue;
			}

			ist = MGeo::Intr2Line3D( pHaiKiso[ic1]->m_lnPlc, pHaiKiso[ic2]->m_lnPlc, &po);
			if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {						// ����( �܂��� �A��)(�A���͑O�̕��s�����ŃX�L�b�v���ꂱ���ɂ͓���Ȃ�)
				ist = MGeo::CheckPointOnLine3D( po, pHaiKiso[ic1]->m_lnPlc, &ist1);
				if ( ist1 == (MC_ON_SLINE | MC_INSIDE))								//		��b�����Ō�������
					ASSERT( FALSE);													//			�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>
				ist = MGeo::CheckPointOnLine3D( po, pHaiKiso[ic2]->m_lnPlc, &ist2);
				if ( ist2 == (MC_ON_SLINE | MC_INSIDE))								//		��b�����Ō�������
					ASSERT( FALSE);													//			�����_�ŕ����ς݂Ȃ̂ŏ����G���[�@<ERROR>

				// ������b�̐}�`�쐬
                MgVect3D vtutLn2 = MGeo::UnitizeVect3D( MgVect3DC( pHaiKiso[ic2]->m_lnPlc));
				MgSLine3D SLnR = MgSLine3D( pHaiKiso[ic2]->m_pZukei->m_lnZukei[0].p[0], vtutLn2);
				MgSLine3D SLnL = MgSLine3D( pHaiKiso[ic2]->m_pZukei->m_lnZukei[1].p[0], vtutLn2);

				if ( ( ist1 & (MC_ON_PS | MC_ON_PE)) == ( ist2 & (MC_ON_PS | MC_ON_PE))) {	// ��b�̌������Ό�
					istr = MGeo::IntrLineSLine3D( lnZukei[0], SLnL, &p0);
					istl = MGeo::IntrLineSLine3D( lnZukei[1], SLnR, &p1);
				} else {															// ��b�̌�����������
					istr = MGeo::IntrLineSLine3D( lnZukei[0], SLnR, &p0);
					istl = MGeo::IntrLineSLine3D( lnZukei[1], SLnL, &p1);
				}
				if ( ist1 & MC_ON_PS) {
					if ( MF_CHECK_OR( istr, (MC_INT | MC_CONNECTION)))
						lnZukei[0].p[0] = p0;
					if ( MF_CHECK_OR( istl, (MC_INT | MC_CONNECTION)))
						lnZukei[1].p[0] = p1;
					iPlcCn[0] = -1;													//			�n�_�_���Ɍ��������b�����ݒ�
				} else if ( ist1 == (MC_ON_SLINE | MC_ON_PE)) {
					if ( MF_CHECK_OR( istr, (MC_INT | MC_CONNECTION)))
						lnZukei[0].p[1] = p0;
					if ( MF_CHECK_OR( istl, (MC_INT | MC_CONNECTION)))
						lnZukei[1].p[1] = p1;
					iPlcCn[1] = -1;													//			�I�_���Ɍ��������b�����ݒ�
				}
			}
		}

		if ( iPlcCn[0] == -2 || iPlcCn[1] == -2) {
			MgVect3D	vtutLn1 = MGeo::UnitizeVect3D( MgVect3DC( lnKiso1));
			lnKiso1.p[0] = lnKiso1.p[0] - vtutLn1 * 60.0;
			lnKiso1.p[1] = lnKiso1.p[1] + vtutLn1 * 60.0;

			if ( iPlcCn[0] == -2) {													// �n�_���J���[
				lnZukei[0].p[0] = lnKiso1.p[0] + vtutLn1.RotR90() * pHaiKiso[ic1]->GetMbWidthR();
				lnZukei[1].p[0] = lnKiso1.p[0] + vtutLn1.RotL90() * pHaiKiso[ic1]->GetMbWidthL();
				lnZukei[nZukei].p[0] = lnZukei[1].p[0];
				lnZukei[nZukei].p[1] = lnZukei[0].p[0];
				nZukei++;

			}
			if ( iPlcCn[1] == -2) {													// �I�_���J���[
				lnZukei[0].p[1] = lnKiso1.p[1] + vtutLn1.RotR90() * pHaiKiso[ic1]->GetMbWidthR();
				lnZukei[1].p[1] = lnKiso1.p[1] + vtutLn1.RotL90() * pHaiKiso[ic1]->GetMbWidthL();
				lnZukei[nZukei].p[0] = lnZukei[0].p[1];
				lnZukei[nZukei].p[1] = lnZukei[1].p[1];
				nZukei++;
			}
		}

		if ( nZukei > pHaiKiso[ic1]->m_pZukei->m_isNZukei) {
			szZukei = sizeof(MhZukei) + sizeof(MgLine3D) * (nZukei - 1);			// ����nZukei�{���̐}�`�f�[�^�T�C�Y
			MBFREE(pHaiKiso[ic1]->m_pZukei);
			pHaiKiso[ic1]->m_pZukei = (MhZukei*)new char[szZukei];					// �}�`����
			pHaiKiso[ic1]->m_pZukei->m_pNext = NULL;
		}

		lnZukei[1].SetRev();
		for ( ic2=0; ic2<nZukei; ic2++)
			pHaiKiso[ic1]->m_pZukei->m_lnZukei[ic2] = lnZukei[ic2];
		pHaiKiso[ic1]->m_pZukei->m_isNZukei = nZukei;
	}

	z_fUpdateKiso = false;
exit:
	;
}

} // namespace MC
