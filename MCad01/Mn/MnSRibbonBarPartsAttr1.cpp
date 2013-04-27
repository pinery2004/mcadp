//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPartsAttr2.cpp
//
//		
//	�������̓��{���o�[ 	���i�I��
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhDefParts.h"
#include "MhInpPlcParts.h"
#include "MhLib.h"
#include "MmPrompt.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	���i�I��p�R���|�{�b�N�X�ɃJ�����g�̑g�ƕ��ނ̕��ޖ��ꗗ��ݒ肵
//	�Ή����镔�ނh�c�e�[�u�����쐬����
//
//	�J�����g�̍\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b) ��
//	���ރR�[�h("����", "����", "�p�l��", "����", "��", "����", "���", "�J��", "���L", "���̑�") �Ƃ�
//	��v���镔�ނ̂ݐݒ肷��

void mnIoPartsAttr::InitComboPartsNm()
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
		m_iComboIdPartsSpec[ip] = ic1;							// ���ނh�c���e�[�u���ɐݒ�
		pPTNmParts1 = pPartsSpec->GetPTNmParts1();				// ���ޖ������ڂɒǉ�
		ist = pCmbBox->AddItem( pPTNmParts1);
		ip++;
	}
	m_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}
	m_iComboKmIdPartsNm = -1;
	z_mnIA.SetKCdBrB( false, false, false);						//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���𖢑I���ɐݒ�
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����ڔԍ��ŕ��i���R���|�{�b�N�X��I������
//	�J�����g���i�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��
//	���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���|�{�b�N�X����I������

void mnIoPartsAttr::SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// ���i�����ڔԍ�
				)
{
	System::GetpMainFrame()->SelectCombo1( i_iKmIdPartsNm);
	m_iComboKmIdPartsNm = i_iKmIdPartsNm;						// �J�����g���i�����ڔԍ�

	// ���i�z�u���̓f�[�^�֐ݒ�
	int iIdPartsSpec;
	iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];			// ���i�d�lId
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	mhPartsSpec *pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);	// ���i�d�l
	mtPlcInp::SetpPartsSpec( pPartsSpec);
	int iCdPlc;
	iCdPlc = pPartsSpec->GetPTCdPlc();						// ���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���{��I������
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

int mnIoPartsAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// ���i��
				)
{
	int	 	iIdPartsSpec = -1;
	int		iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "�����ރe�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mnIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

	iIdPartsSpec = m_iComboIdPartsSpec[iKmIdPartsNm];
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

int mnIoPartsAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
{
	int			iKmIdPartsNm;
	int			ic1;
	int			iIdPartsSpec;
	mhPartsSpec	*pPartsSpec;
	
	for ( ic1=0; ic1<m_nComboIdPartsSpec; ic1++) {
		iIdPartsSpec = m_iComboIdPartsSpec[ic1];
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < m_nComboIdPartsSpec)
		iKmIdPartsNm = ic1;
	else
		iKmIdPartsNm = -1;
	return iKmIdPartsNm;
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����畔�iID���擾����
//							��-1: ���I��
//							�� 0: ���iID

int mnIoPartsAttr::GetComboPartsNmId(
						MCHAR* i_sNmParts1		// ���i��
				)
{
	int			ist;
	int			ic1;
	mhPartsSpec	*pPartsSpec;

	int		nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
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

int mnIoPartsAttr::GetCurPartsNmId()
{
	int	 iIdPartsSpec;

	if ( m_iComboKmIdPartsNm >= 0 && m_iComboKmIdPartsNm < m_nComboIdPartsSpec) {
		iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];
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

void mnIoPartsAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip = 0;

	CMFCRibbonComboBox* pCmbBox = mmpComboMbr();
	pCmbBox->RemoveAllItems();

	int		iIdPartsSpec;
	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	if ( iIdPartsSpec == -1) {
//		pCmbBox->>EnableToolTips(0);			NG
		goto exit;
	}

	MCHAR	cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];
	MCHAR	cMTp2;
	int		nMbr;
	nMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<nMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);

		for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {		// ��v���鐡�@�^���g�p���ʃR�[�h�����邩null�܂Œ��ׂ�
			if ( cMTp1 == cMTp2) break;
		}
		if ( cMTp2 == 0) continue;								// ��v���Ȃ��ꍇ���̐��@�^���Ɉڂ�

		ASSERT( ip < MX_CMB_CDMEMBER - 1);						// ���@�^���I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		m_iComboMbrId[ip] = ic1;
		pCmbBox->AddItem( pMbr->GetMbrCode());
		ip++;
	}
exit:
	m_nComboMbrId = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}

	m_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��

void mnIoPartsAttr::SelectComboPartsMbrByKmId(
						int		i_iKmIdMbr			// ���@�^�����ڔԍ�
				)
{
	System::GetpMainFrame()->SelectCombo2( i_iKmIdMbr);
	m_iComboKmIdMbr = i_iKmIdMbr;

	// ���i�z�u���̓f�[�^�֐ݒ�
	int	 iMbrId;
	iMbrId = m_iComboMbrId[i_iKmIdMbr];					// ���@�`��ID
	mtPlcInp::SetIdMbr( iMbrId); 
	MhMbr *pMbr = BuzaiCode::MhGetpMbr( iMbrId);				// ���@�`���d�l
	mtPlcInp::SetpMbr( pMbr);
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�^���őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID

int mnIoPartsAttr::SelectComboMbrCdByMbrCd( MCHAR* sCdMbr)
{
	int		iMbrId = -1;
	int		iKmIdMbr;

	iKmIdMbr = z_mnIA.GetComboMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);	// "�����@�^���e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mnIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = m_iComboMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�`�����琡�@�^���R���{�{�b�N�X�̐��@�^�����ڔԍ����擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���iID

int mnIoPartsAttr::GetComboMbrKmId( MCHAR* sCdMbr)
{
	int		ist;
	int		ic1;
	int		iMbrId;
	MhMbr	*pMbr;
	
	for ( ic1=0; ic1<m_nComboMbrId; ic1++) {
		iMbrId = m_iComboMbrId[ic1];
		pMbr = BuzaiCode::MhGetpMbr( iMbrId);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < m_nComboMbrId)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�`�����琡�@�^��ID���擾����
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID

static int GetComboMbrCdId( MCHAR* sCdMbr)
{
	int		ist;
	int		ic1;
	MhMbr	*pMbr;
	int		nMbr;

	nMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<nMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < nMbr)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̐��@�^��ID���擾����
//							��-1: ���I��
//							�� 0: ���@�^��ID

int mnIoPartsAttr::GetComboMbrCdId()
{
	int		iMbrId;

	if ( m_iComboKmIdMbr >= 0 && m_iComboKmIdMbr < m_nComboMbrId) {
		iMbrId = m_iComboMbrId[m_iComboKmIdMbr];
	} else {
		iMbrId = -1;
	}
	return iMbrId;
}

} // namespace MC