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

// ���i�I��p�R���{�{�b�N�X
static MINT z_nComboIdPartsSpec;								// �\�����ڐ�
static MINT	z_iComboIdPartsSpec[MX_CMB_PARTSNM];				// �\�����ڑΉ����iID
static MINT z_iComboKmIdPartsTp;								// �J�����g�I�����ڔԍ�

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

void mnInpAttr::InitComboPartsTp()
{
	int		ist;
	int		ic1;
	int		ip = 0;
	int		iKCdGp = z_mn.GetKCdGp();			// �J�����g	�\���@�\��(�g)�R�[�h
	int		iKCdBr = z_mn.GetKCdBr();			// �J�����g	���ށ@���ރR�[�h
	mhPartsTp	*pPartsTp;						// ���ރe�[�u�� ����
	int		iPTCdGp;							// ���ރe�[�u��	���ށ@�\��(�g)�R�[�h
	int		iPTCdBr;							// ���ރe�[�u�� ���ށ@���ރR�[�h
	MCHAR*	pPTNmParts1;						// ���ރe�[�u�� ���ށ@���ޖ�

	CMFCRibbonComboBox* pCmbBox = MnpComboBuzai();
	pCmbBox->RemoveAllItems();

	MINT mxPartsNm = BuzaiCode::MhGetNoOfPartsTp();
	for ( ic1=0; ic1<mxPartsNm; ic1++) {
		pPartsTp = BuzaiCode::MhGetpPartsTp( ic1);
		iPTCdGp = pPartsTp->GetPTCdGp();
		if ( iKCdGp != iPTCdGp)									// �\��(�g)�R�[�h���J�����g�ƕs��v�͖���
			continue;
		iPTCdBr = pPartsTp->GetPTCdBr();
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
		z_iComboIdPartsSpec[ip] = ic1;								// ���ނh�c���e�[�u���ɐݒ�
		pPTNmParts1 = pPartsTp->GetPTNmParts1();						// ���ޖ������ڂɒǉ�
		ist = pCmbBox->AddItem( pPTNmParts1);
		ip++;
	}
	z_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}
	z_iComboKmIdPartsTp = -1;
	z_mn.SetKCdBrB( false, false, false);					//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���𖢑I���ɐݒ�

//	MmSetComboMbr();
}

///////////////////////////////////////////////////////////////////////////////
//	���ޖ���蕔�i�I�����ڔԍ����擾����
//	�R���{�{�b�N�X�̍��ڂ��w�肳�ꂽ���ނ̕��iID���������A
//	�Y���̕��i�I�����ڔԍ���Ԃ�
//	�Ԓl
//							�� 0: ���iID
//							��-1: �Y���Ȃ�
static MINT MmGetKmIdPartsTp( MCHAR* i_sNmParts1)
{
	MINT		iKmIdPartsTp;
	MINT		ic1;
	MINT		iIdPartsTp;
	mhPartsTp	*pPartsTp;
	
	for ( ic1=0; ic1<z_nComboIdPartsSpec; ic1++) {
		iIdPartsTp = z_iComboIdPartsSpec[ic1];
		pPartsTp = BuzaiCode::MhGetpPartsTp( iIdPartsTp);
		if ( Mstrcmp( pPartsTp->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < z_nComboIdPartsSpec)
		iKmIdPartsTp = ic1;
	else
		iKmIdPartsTp = -1;
	return iKmIdPartsTp;
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�Ɏw�肵�����i�I�����ڔԍ��̕��ޖ���\����
//	�J�����g�̕��i�I�����ڔԍ���ݒ肷��

void mnInpAttr::SetComboKmIdPartsTp(
						MINT	iKmIdPartsTp		// (I  ) ���i�I�����ڔԍ�
				)
{
	System::GetpMainFrame()->SetCombo1( iKmIdPartsTp);
	z_iComboKmIdPartsTp = iKmIdPartsTp;

	// ���ޓ��͑����̐ݒ�
	MINT iIdPartsTp = z_iComboIdPartsSpec[z_iComboKmIdPartsTp];
	mtPlcInp::SetIdPartsTp( iIdPartsTp);
	mhPartsTp *pPartsTp = BuzaiCode::MhGetpPartsTp( iIdPartsTp);
	mtPlcInp::SetpPartsTp( pPartsTp);

	MINT iCdPlc = pPartsTp->GetPTCdPlc();
	z_mn.SetComboCdPlc( iCdPlc);
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�Ɏw�肵�����ޖ���\�������̕��iID���擾����
//	�J�����g�̕��i�I�����ڔԍ���ݒ肷��
//	�Ԓl
//							�� 0: ���iID
//							��-1: �Y���Ȃ�
MINT mnInpAttr::SetComboCdPartsTp( MCHAR* i_sNmParts1)
{
	MINT 	iIdPartsTp = -1;
	MINT	iKmIdPartsTp;

	iKmIdPartsTp = MmGetKmIdPartsTp( i_sNmParts1);
	if ( iKmIdPartsTp < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "�����ރe�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mn.SetComboKmIdPartsTp( iKmIdPartsTp);

	iIdPartsTp = z_iComboIdPartsSpec[iKmIdPartsTp];
exit:
	return iIdPartsTp;
}

///////////////////////////////////////////////////////////////////////////////
//	���ޖ���蕔�iID���擾����
//							��-1: ���I��
//							�� 0: ���iID
MINT mnInpAttr::GetIdPartsTp( MCHAR* i_sNmParts1)
{
	MINT		ist;
	MINT		ic1;
	mhPartsTp	*pPartsTp;

	MINT	mxPartsNm = BuzaiCode::MhGetNoOfPartsTp();
	for ( ic1=0; ic1<mxPartsNm; ic1++) {
		pPartsTp = BuzaiCode::MhGetpPartsTp( ic1);
		if ( Mstrcmp( pPartsTp->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < mxPartsNm)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̕��iID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���iID
MINT mnInpAttr::GetCurIdPartsTp()
{
	MINT iIdPartsTp;

	if ( z_iComboKmIdPartsTp >= 0 && z_iComboKmIdPartsTp < z_nComboIdPartsSpec) {
		iIdPartsTp = z_iComboIdPartsSpec[z_iComboKmIdPartsTp];
	} else {
		iIdPartsTp = -1;
	}
	return iIdPartsTp;
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

	CMFCRibbonComboBox* pCmbBox = MmpComboMbr();
	pCmbBox->RemoveAllItems();

	MINT		iIdPartsTp = z_mn.GetCurIdPartsTp();
	if ( iIdPartsTp == -1) {
//		pCmbBox->>EnableToolTips(0);			NG
		goto exit;
	}

	MCHAR		cMTp1 = BuzaiCode::MhGetpPartsTp( iIdPartsTp)->GetPTTpMbr()[0];
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
//	�R���{�{�b�N�X�ɐ��@�^���I�����ڔԍ��̐��@�^����\����
//	�J�����g�̐��@�^���I�����ڔԍ���ݒ肷��

void mnInpAttr::SetComboKmIdMbr(
						MINT	iKmIdMbr			// (I  ) ���@�^���I�����ڔԍ�
				)
{
	System::GetpMainFrame()->SetCombo2( iKmIdMbr);
	z_iComboKmIdMbr = iKmIdMbr;

	// ���ޓ��͑����̐ݒ�
	MINT iMbrId = z_iComboMbrId[iKmIdMbr];
	mtPlcInp::SetIdMbr( iMbrId); 
	MhMbr *pMbr = BuzaiCode::MhGetpMbr( iMbrId);
	mtPlcInp::SetpMbr( pMbr);
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���I�����ڔԍ����擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���iID
MINT mnInpAttr::GetComboKmIdMbr( MCHAR* sCdMbr)
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
//	���@�^����ݒ肷��
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID
MINT mnInpAttr::SetComboCdMbr( MCHAR* sCdMbr)
{
	MINT		iMbrId = -1;
	MINT		iKmIdMbr;

	iKmIdMbr = z_mn.GetComboKmIdMbr( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);	// "�����@�^���e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mn.SetComboKmIdMbr( iKmIdMbr);

	iMbrId = z_iComboMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^��ID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID
static MINT GetComboIdMbr( MCHAR* sCdMbr)
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
MINT mnInpAttr::GetComboIdMbr()
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