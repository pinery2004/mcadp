//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmsDialogBarPts.cpp
//
//		
//	1.4	���ޑI��
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MmDefine.h"
#include "MtInp.h"
#include "MhLib.h"
#include "MmPrompt.h"

namespace MC
{

// ���ޑI��p�R���{�{�b�N�X
static MINT z_nComboIdTpPts;									// �\�����ڐ�
static MINT	z_iComboIdTpPts[MX_CMB_PARTSNM];					// �\�����ڑΉ�����ID
static MINT z_iComboKmIdTpPts;								// �J�����g�I�����ڔԍ�

// ���@�^���I��p�R���{�{�b�N�X
static MINT z_nComboMbrId;									// �\�����ڐ�
static MINT	z_iComboMbrId[MX_CMB_CDMEMBER];					// �\�����ڑΉ����@�^��ID
static MINT z_iComboKmIdMbr;									// �J�����g�I�����ڔԍ�

///////////////////////////////////////////////////////////////////////////////
//	���ޑI��p�R���|�{�b�N�X�ɕ��ޖ��̍���(�ꗗ)��ݒ肵
//	�Ή����镔�ނh�c�e�[�u�����쐬����
//
//	�J�����g�̍\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b) ��
//	���ރR�[�h("����", "����", "�p�l��", "����", "��", "����", "���", "�J��", "���L", "���̑�") �Ƃ�
//	��v���镔�ނ̂ݐݒ肷��

void mtInpAttr::InitComboTpPtsAttr()
{
	mhTpPts	*pTpPts;
	MINT		ic1;
	MINT		ip = 0;

	CComboBox *pCmb = MmpComboCdBuzai();
	pCmb->ResetContent();

	MINT mxPtsNm = BuzaiCode::MhGetNoOfTpPts();
	for ( ic1=0; ic1<mxPtsNm; ic1++) {
		pTpPts = BuzaiCode::MhGetpTpPts( ic1);
		if ( mtInpMode::GetKGp() != pTpPts->GetPTCdGp())	// �\��(�g)�R�[�h���J�����g�ƕs��v�͖���
			continue;
		if ( mtInpMode::GetKBr() == MP_BR_OTHER) {			// �I���������ނ����̑��̏ꍇ
			if ( pTpPts->GetPTBr() == MP_BR_BUZAI ||	// "����"�A
				pTpPts->GetPTBr() == MP_BR_KANAGU ||	// "����"�A
				pTpPts->GetPTBr() == MP_BR_PANEL)		// "�p�l��"�͖���
				continue;
		} else {												// �I���������ނ�"����", "����", "�p�l��"�̏ꍇ��
			if ( mtInpMode::GetKBr() != pTpPts->GetPTBr())	//		���ރR�[�h�R�[�h���J�����g�ƕs��v�͖���
				 continue;
		}
		ASSERT( ip < MX_CMB_PARTSNM - 1);						// ���ރR���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboIdTpPts[ip++] = ic1;							// ���ނh�c���e�[�u���ɐݒ�
		pCmb->InsertString( -1, pTpPts->GetPTNmPts1());	// ���ޖ������ڂɒǉ�
	}
	z_nComboIdTpPts = ip;
	if ( ip == 0)
		pCmb->InsertString( -1, Mstr( "none"));
	z_iComboKmIdTpPts = -1;
	mtInpMode::SetKBrB( false, false, false, false);			//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���𖢑I���ɐݒ�

//	MmSetComboMbr();
}

///////////////////////////////////////////////////////////////////////////////
//	���ޖ���蕔�ޑI�����ڔԍ����擾����
//	�R���{�{�b�N�X�̍��ڂ��w�肳�ꂽ���ނ̕���ID���������A
//	�Y���̕��ޑI�����ڔԍ���Ԃ�
//	�Ԓl
//							�� 0: ����ID
//							��-1: �Y���Ȃ�
static MINT MmGetKmIdTpPts( MCHAR* i_pcNmPts1)
{
	MINT		iKmIdTpPts;
	MINT		ic1;
	MINT		iIdTpPts;
	mhTpPts	*pTpPts;
	
	for ( ic1=0; ic1<z_nComboIdTpPts; ic1++) {
		iIdTpPts = z_iComboIdTpPts[ic1];
		pTpPts = BuzaiCode::MhGetpTpPts( iIdTpPts);
		if ( Mstrcmp( pTpPts->GetPTNmPts1(), i_pcNmPts1) == 0)
			break;
	}
	if ( ic1 < z_nComboIdTpPts)
		iKmIdTpPts = ic1;
	else
		iKmIdTpPts = -1;
	return iKmIdTpPts;
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�Ɏw�肵�����ޑI�����ڔԍ��̕��ޖ���\����
//	�J�����g�̕��ޑI�����ڔԍ���ݒ肷��

void mtInpAttr::SetComboKmIdTpPts(
						MINT	iKmIdTpPts		// (I  ) ���ޑI�����ڔԍ�
				)
{
	System::GetpMainFrame()->SetCombo1( iKmIdTpPts);
	z_iComboKmIdTpPts = iKmIdTpPts;

	// ���ޓ��͑����̐ݒ�
	MINT iIdTpPts = z_iComboIdTpPts[z_iComboKmIdTpPts];
	mtPlcInp::SetIdTpPts( iIdTpPts);
	mhTpPts *pTpPts = BuzaiCode::MhGetpTpPts( iIdTpPts);
	mtPlcInp::SetpTpPts( pTpPts);

	MINT iCdPlc = pTpPts->GetPTCdPlc();
	mtHaitiIn::SetComboCdPlc( iCdPlc);
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�Ɏw�肵�����ޖ���\�������̕���ID���擾����
//	�J�����g�̕��ޑI�����ڔԍ���ݒ肷��
//	�Ԓl
//							�� 0: ����ID
//							��-1: �Y���Ȃ�
MINT mtInpAttr::SetComboCdTpPts( MCHAR* i_pcNmPts1)
{
	MINT 	iIdTpPts = -1;
	MINT	iKmIdTpPts;

	iKmIdTpPts = MmGetKmIdTpPts( i_pcNmPts1);
	if ( iKmIdTpPts < 0) {
		Msg::ErrorMsg( i_pcNmPts1, MC_ERR_NOTSET_PARTS_TABLE);	// "�����i�e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	mtInpAttr::SetComboKmIdTpPts( iKmIdTpPts);

	iIdTpPts = z_iComboIdTpPts[iKmIdTpPts];
exit:
	return iIdTpPts;
}

///////////////////////////////////////////////////////////////////////////////
//	���ޖ���蕔��ID���擾����
//							��-1: ���I��
//							�� 0: ����ID
MINT mtInpAttr::GetIdTpPts( MCHAR* i_pcNmPts1)
{
	MINT		ist;
	MINT		ic1;
	mhTpPts	*pTpPts;

	MINT	mxPtsNm = BuzaiCode::MhGetNoOfTpPts();
	for ( ic1=0; ic1<mxPtsNm; ic1++) {
		pTpPts = BuzaiCode::MhGetpTpPts( ic1);
		if ( Mstrcmp( pTpPts->GetPTNmPts1(), i_pcNmPts1) == 0)
			break;
	}
	if ( ic1 < mxPtsNm)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̕���ID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ����ID
MINT mtInpAttr::GetCurIdTpPts()
{
	MINT iIdTpPts;

	if ( z_iComboKmIdTpPts >= 0 && z_iComboKmIdTpPts < z_nComboIdTpPts) {
		iIdTpPts = z_iComboIdTpPts[z_iComboKmIdTpPts];
	} else {
		iIdTpPts = -1;
	}
	return iIdTpPts;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���I��p�R���|�{�b�N�X�ɐ��@�^���̍���(�ꗗ)��ݒ肵
//	�Ή����鐡�@�^���h�c�e�[�u�����쐬����
//
//	�J�����g�̕��ނ̐��@�^���g�p���ʃR�[�h�������@�^���̂ݐݒ�

void mtInpAttr::InitComboPtsMbr()
{
	MhMbr	*pMbr;
	MINT		ic1;
	MINT		ic;
	MINT		ip = 0;

	CComboBox *pCmb = MmpComboMbr();
	pCmb->ResetContent();

	MINT		iIdTpPts = mtInpAttr::GetCurIdTpPts();
	if ( iIdTpPts == -1) {
//		pCmb->>EnableToolTips(0);			NG
		goto exit;
	}

	MCHAR		cMTp1 = BuzaiCode::MhGetpTpPts( iIdTpPts)->GetPTTpMbr()[0];
	MCHAR		cMTp2;

	MINT mxMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<mxMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);

		for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {		// ��v���鐡�@�^���g�p���ʃR�[�h�����邩null�܂Œ��ׂ�
			if ( cMTp1 == cMTp2) break;
		}
		if ( cMTp2 == 0) continue;								// ��v���Ȃ��ꍇ���̐��@�^���Ɉڂ�

		ASSERT( ip < MX_CMB_CDMEMBER - 1);						// ���@�^���I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboMbrId[ip++] = ic1;
		pCmb->InsertString( -1, pMbr->GetMbrCode());
	}
exit:
	z_nComboMbrId = ip;
	if ( ip == 0)
		pCmb->InsertString( -1, Mstr( "none"));

	z_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�ɐ��@�^���I�����ڔԍ��̐��@�^����\����
//	�J�����g�̐��@�^���I�����ڔԍ���ݒ肷��

void mtInpAttr::SetComboKmIdMbr(
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
//							�� 0: ����ID
MINT mtInpAttr::GetComboKmIdMbr( MCHAR* sCdMbr)
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
MINT mtInpAttr::SetComboCdMbr( MCHAR* sCdMbr)
{
	MINT		iMbrId = -1;
	MINT		iKmIdMbr;

	iKmIdMbr = mtInpAttr::GetComboKmIdMbr( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);	// "�����@�^���e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	mtInpAttr::SetComboKmIdMbr( iKmIdMbr);

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
MINT mtInpAttr::GetComboIdMbr()
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