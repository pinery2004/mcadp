//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmsRibbonBarParts.cpp
//
//		
//	1.4	���i�I��
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhDefParts.h"
#include "MhInp.h"
#include "MhLib.h"
#include "MmPrompt.h"

namespace MC
{

// ���i���R���{�{�b�N�X
static MINT z_nComboIdPartsSpec;								// �\�����ڐ�
static MINT	z_iComboIdPartsSpec[MX_CMB_PARTSNM];				// �\�����ڑΉ����iID
static MINT z_iComboKmIdPartsNm;								// �J�����g�I�����ڔԍ�

// ���@�^���I��p�R���{�{�b�N�X
static MINT z_nComboMbrId;										// �\�����ڐ�
static MINT	z_iComboMbrId[MX_CMB_CDMEMBER];						// �\�����ڑΉ����@�^��ID
static MINT z_iComboKmIdMbr;									// �J�����g�I�����ڔԍ�

///////////////////////////////////////////////////////////////////////////////
//	���i�I��p�R���|�{�b�N�X�ɃJ�����g�̑g�ƕ��ނ̕��ޖ��ꗗ��ݒ肵
//	�Ή����镔�ނh�c�e�[�u�����쐬����
//
//	�J�����g�̍\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b) ��
//	���ރR�[�h("����", "����", "�p�l��", "����", "��", "����", "���", "�J��", "���L", "���̑�") �Ƃ�
//	��v���镔�ނ̂ݐݒ肷��

void mnInpAttr::InitComboPartsNm()
{
	int		ist;
	int		ic1;
	int		ip = 0;
	int		iKCdGp = z_mnIA.GetKCdGp();			// �J�����g	�\���@�\��(�g)�R�[�h
	int		iKCdBr = z_mnIA.GetKCdBr();			// �J�����g	���ށ@���ރR�[�h
	mhPartsSpec	*pPartsSpec;					// ���ރe�[�u�� ����
	int		iPTCdGp;							// ���ރe�[�u��	���ށ@�\��(�g)�R�[�h
	int		iPTCdBr;							// ���ރe�[�u�� ���ށ@���ރR�[�h
	MCHAR*	pPTNmParts1;						// ���ރe�[�u�� ���ށ@���ޖ�

	CMFCRibbonComboBox* pCmbBox = mmpComboBuzai();
	pCmbBox->RemoveAllItems();

	int		nPartsNm;
	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		iPTCdGp = pPartsSpec->GetPTCdGp();
		if ( iKCdGp != iPTCdGp)									// �\��(�g)�R�[�h���J�����g�ƕs��v�͖���
			continue;
		iPTCdBr = pPartsSpec->GetPTCdBr();
		if ( iKCdBr == MP_BR_OTHER) {							// �I���������ނ����̑��̏ꍇ
			if ( iPTCdBr == MP_BR_BUZAI ||						// "����"�A
				iPTCdBr == MP_BR_KANAGU ||						// "����"�A
				iPTCdBr == MP_BR_PANEL)							// "�p�l��"�͖���
				continue;
		} else {												// �I���������ނ�"����", "����", "�p�l��"�̏ꍇ��
			if ( iPTCdBr != iKCdBr)								//		���ރR�[�h�R�[�h���J�����g�ƕs��v�͖���
				 continue;
		}
		ASSERT( ip < MX_CMB_PARTSNM - 1);						// ���ރR���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboIdPartsSpec[ip] = ic1;							// ���ނh�c���e�[�u���ɐݒ�
		pPTNmParts1 = pPartsSpec->GetPTNmParts1();				// ���ޖ������ڂɒǉ�
		ist = pCmbBox->AddItem( pPTNmParts1);
		ip++;
	}
	z_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}
	z_iComboKmIdPartsNm = -1;
	z_mnIA.SetKCdBrB( false, false, false);						//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���𖢑I���ɐݒ�
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����ڔԍ��ŕ��i���R���|�{�b�N�X��I������
//	�J�����g���i�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��
//	���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���|�{�b�N�X����I������

void mnInpAttr::SelectComboPartsNmByKmId(
						MINT	i_iKmIdPartsNm	// ���i�����ڔԍ�
				)
{
	System::GetpMainFrame()->SelectCombo1( i_iKmIdPartsNm);
	z_iComboKmIdPartsNm = i_iKmIdPartsNm;						// �J�����g���i�����ڔԍ�

	// ���i�z�u���̓f�[�^�֐ݒ�
	MINT iIdPartsSpec = z_iComboIdPartsSpec[z_iComboKmIdPartsNm];			// ���i�d�lId
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	mhPartsSpec *pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);	// ���i�d�l
	mtPlcInp::SetpPartsSpec( pPartsSpec);

	MINT iCdPlc = pPartsSpec->GetPTCdPlc();						// ���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���{��I������
	z_mnIA.SelectComboPlcCdByPlcCd( iCdPlc);
}

///////////////////////////////////////////////////////////////////////////////
//	���i���ŕ��i���R���|�{�b�N�X��I������
//	�J�����g�̕��i�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��
//	���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���|�{�b�N�X����I������
//
//	�Ԓl
//							�� 0: ���iID
//							��-1: �Y���Ȃ�

MINT mnInpAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// ���i��
				)
{
	MINT 	iIdPartsSpec = -1;
	MINT	iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "�����ރe�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mnIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

	iIdPartsSpec = z_iComboIdPartsSpec[iKmIdPartsNm];
exit:
	return iIdPartsSpec;
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����畔�i���R���|�{�b�N�X�̕��i�����ڔԍ����擾����
//	�R���{�{�b�N�X�̍��ڂ��w�肳�ꂽ���ނ̕��iID���������A
//	�Y���̕��i�����ڔԍ���Ԃ�
//	�Ԓl
//							�� 0: ���iID
//							��-1: �Y���Ȃ�

MINT mnInpAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
{
	MINT		iKmIdPartsNm;
	MINT		ic1;
	MINT		iIdPartsSpec;
	mhPartsSpec	*pPartsSpec;
	
	for ( ic1=0; ic1<z_nComboIdPartsSpec; ic1++) {
		iIdPartsSpec = z_iComboIdPartsSpec[ic1];
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < z_nComboIdPartsSpec)
		iKmIdPartsNm = ic1;
	else
		iKmIdPartsNm = -1;
	return iKmIdPartsNm;
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����畔�iID���擾����
//							��-1: ���I��
//							�� 0: ���iID

MINT mnInpAttr::GetComboPartsNmId(
						MCHAR* i_sNmParts1		// ���i��
				)
{
	MINT		ist;
	MINT		ic1;
	mhPartsSpec	*pPartsSpec;

	MINT	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < nPartsNm)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̕��iID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���iID

MINT mnInpAttr::GetCurPartsNmId()
{
	MINT iIdPartsSpec;

	if ( z_iComboKmIdPartsNm >= 0 && z_iComboKmIdPartsNm < z_nComboIdPartsSpec) {
		iIdPartsSpec = z_iComboIdPartsSpec[z_iComboKmIdPartsNm];
	} else {
		iIdPartsSpec = -1;
	}
	return iIdPartsSpec;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���I��p�R���|�{�b�N�X�ɐ��@�^���̍���(�ꗗ)��ݒ肵
//	�Ή����鐡�@�^���h�c�e�[�u�����쐬����
//
//	�J�����g�̕��ނ̐��@�^���g�p���ʃR�[�h�������@�^���̂ݐݒ�

void mnInpAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip = 0;

	CMFCRibbonComboBox* pCmbBox = mmpComboMbr();
	pCmbBox->RemoveAllItems();

	MINT		iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	if ( iIdPartsSpec == -1) {
//		pCmbBox->>EnableToolTips(0);			NG
		goto exit;
	}

	MCHAR		cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];
	MCHAR		cMTp2;

	MINT mxMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<mxMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);

		for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {		// ��v���鐡�@�^���g�p���ʃR�[�h�����邩null�܂Œ��ׂ�
			if ( cMTp1 == cMTp2) break;
		}
		if ( cMTp2 == 0) continue;								// ��v���Ȃ��ꍇ���̐��@�^���Ɉڂ�

		ASSERT( ip < MX_CMB_CDMEMBER - 1);						// ���@�^���I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboMbrId[ip] = ic1;
		pCmbBox->AddItem( pMbr->GetMbrCode());
		ip++;
	}
exit:
	z_nComboMbrId = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}

	z_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��

void mnInpAttr::SelectComboPartsMbrByKmId(
						MINT	i_iKmIdMbr			// ���@�^�����ڔԍ�
				)
{
	System::GetpMainFrame()->SelectCombo2( i_iKmIdMbr);
	z_iComboKmIdMbr = i_iKmIdMbr;

	// ���i�z�u���̓f�[�^�֐ݒ�
	MINT iMbrId = z_iComboMbrId[i_iKmIdMbr];					// ���@�`��ID
	mtPlcInp::SetIdMbr( iMbrId); 
	MhMbr *pMbr = BuzaiCode::MhGetpMbr( iMbrId);				// ���@�`���d�l
	mtPlcInp::SetpMbr( pMbr);
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�^���őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID

MINT mnInpAttr::SelectComboMbrCdByMbrCd( MCHAR* sCdMbr)
{
	MINT		iMbrId = -1;
	MINT		iKmIdMbr;

	iKmIdMbr = z_mnIA.GetComboMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);	// "�����@�^���e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mnIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = z_iComboMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�`�����琡�@�^���R���{�{�b�N�X�̐��@�^�����ڔԍ����擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���iID

MINT mnInpAttr::GetComboMbrKmId( MCHAR* sCdMbr)
{
	MINT		ist;
	MINT		ic1;
	MINT		iMbrId;
	MhMbr	*pMbr;
	
	for ( ic1=0; ic1<z_nComboMbrId; ic1++) {
		iMbrId = z_iComboMbrId[ic1];
		pMbr = BuzaiCode::MhGetpMbr( iMbrId);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < z_nComboMbrId)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�`�����琡�@�^��ID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID

static MINT GetComboMbrCdId( MCHAR* sCdMbr)
{
	MINT		ist;
	MINT		ic1;
	MhMbr	*pMbr;

	MINT mxMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<mxMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < mxMbr)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̐��@�^��ID���擾����
//							��-1: ���I��
//							�� 0: ���@�^��ID

MINT mnInpAttr::GetComboMbrCdId()
{
	MINT		iMbrId;

	if ( z_iComboKmIdMbr >= 0 && z_iComboKmIdMbr < z_nComboMbrId) {
		iMbrId = z_iComboMbrId[z_iComboKmIdMbr];
	} else {
		iMbrId = -1;
	}
	return iMbrId;
}

} // namespace MC