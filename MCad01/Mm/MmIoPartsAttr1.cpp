//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmIoPartsAttr1.cpp
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
#include "MhInpPlcParts.h"
#include "MhLib.h"
#include "MmPrompt.h"
#include "MmWnd.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	���ޑ������͗p�R���{�{�b�N�X�̐ݒ�

void mmIoPartsAttr::InitComboParts()
{
	//	���i���R���|�{�b�N�X�̍��ڂ�ݒ肷��
	InitComboPartsNm();

	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	InitComboPartsMbr();

//S	//	�p�l���ԍ��I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
//	InitComboPanelNo();

	//	���ޑ������͗p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	InitComboAttrXqt();
}

///////////////////////////////////////////////////////////////////////////////
//	���i�I��p�R���|�{�b�N�X�ɃJ�����g�̑g�ƕ��ނ̕��ޖ��ꗗ��ݒ肵
//	�Ή����镔�ނh�c�e�[�u�����쐬����
//
//	�J�����g�̍\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b) ��
//	���ރR�[�h("����", "����", "�p�l��", "����", "��", "����", "���", "�J��", "���L", "���̑�") �Ƃ�
//	��v���镔�ނ̂ݐݒ肷��

void mmIoPartsAttr::InitComboPartsNm()
{
	int		ist;
	int		ic1;
	int		ip = 0;
	int		iKCdGp;								// �J�����g	�\���\��(�g)�R�[�h
	int		iKCdBr;								// �J�����g	���ޕ��ރR�[�h
	mhPartsSpec	*pPartsSpec;					// ���ރe�[�u�� ����
	int		iPTCdGp;							// ���ރe�[�u��	���ށ@�\��(�g)�R�[�h
	int		iPTCdBr;							// ���ރe�[�u�� ���ށ@���ރR�[�h
	MCHAR*	pPTNmParts1;						// ���ރe�[�u�� ���ށ@���ޖ�

	if ( !GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = GetCmbBzaiNm();
	pCmbBox->ResetContent();

	iKCdGp = z_mnIA.GetKCdGp();									// �J�����g	�\���\��(�g)�R�[�h
	iKCdBr = z_mnIA.GetKCdBr();									// �J�����g	���ޕ��ރR�[�h

	int nPartsNm;
	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		iPTCdGp = pPartsSpec->GetPTCdGp();
		if ( iPTCdGp != iKCdGp)									// �\��(�g)�R�[�h���J�����g�ƕs��v�͖���
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
		ist = pCmbBox->InsertString( -1, pPTNmParts1);
		ip++;
	}
	m_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	m_iComboKmIdPartsNm = -1;
																				//S	z_mmIA.SetKCdBrB( false, false, false);						//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���𖢑I���ɐݒ�
}

///////////////////////////////////////////////////////////////////////////////
//	���i�����ڔԍ��ŕ��i���R���|�{�b�N�X��I������
//	�J�����g���i�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��
//	���i�d�l�̔z�u�R�[�h�Ŕz�u�R�[�h�R���|�{�b�N�X����I������

void mmIoPartsAttr::SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// ���i�����ڔԍ�
				)
{
	int iIdPartsSpec;
	if ( !GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = GetCmbBzaiNm();
	pCmbBox->SetCurSel( i_iKmIdPartsNm);
	m_iComboKmIdPartsNm = i_iKmIdPartsNm;						// �J�����g���i�����ڔԍ�

	// ���i�z�u���̓f�[�^�֐ݒ�
	iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];	// ���i�d�lId
	mhPartsSpec* pPartsSpec;
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);		// ���i�d�l
	mtPlcInp::SetpPartsSpec( pPartsSpec);
EXIT:;
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

int mmIoPartsAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// ���i��
				)
{
	int 	iIdPartsSpec = -1;
	int		iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "�����ރe�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mmIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

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

int mmIoPartsAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
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
//	���@�^���I��p�R���|�{�b�N�X�ɐ��@�^���̍���(�ꗗ)��ݒ肵
//	�Ή����鐡�@�^���h�c�e�[�u�����쐬����
//
//	�J�����g�̕��ނ̐��@�^���g�p���ʃR�[�h�������@�^���̂ݐݒ�

void mmIoPartsAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip;
	MCHAR	cMTp1;
	MCHAR	cMTp2;
	int		iIdPartsSpec;
	int		nMbr;

	ip = 0;
	if ( !GetDispFlg())	goto EXIT;

	CComboBox* pCmbBox = GetCmbBzaiMbr();
	pCmbBox->ResetContent();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	if ( iIdPartsSpec >= 0) {
		cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];

		nMbr = BuzaiCode::MhGetNoOfMbr();
		for ( ic1=0; ic1<nMbr; ic1++) {
			pMbr = BuzaiCode::MhGetpMbr( ic1);

			for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {	// ��v���鐡�@�^���g�p���ʃR�[�h�����邩null�܂Œ��ׂ�
				if ( cMTp1 == cMTp2) break;
			}
			if ( cMTp2 == 0) continue;							// ��v���Ȃ��ꍇ���̐��@�^���Ɉڂ�

			ASSERT( ip < MX_CMB_CDMEMBER - 1);					// ���@�^���I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
			m_iComboPartsMbrId[ip] = ic1;
			pCmbBox->InsertString( -1, pMbr->GetMbrCode());
			ip++;
		}
	}
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	m_nComboPartsMbrId = ip;
	m_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//	���i�z�u���̓f�[�^�֕��i�d�lId�ƕ��i�d�l��ݒ肷��

void mmIoPartsAttr::SelectComboPartsMbrByKmId(
						int		i_iKmIdMbr			// ���@�^�����ڔԍ�
				)
{
	if ( !GetDispFlg())	goto EXIT;

	CComboBox* pCmbBox = GetCmbBzaiMbr();
	pCmbBox->SetCurSel(	i_iKmIdMbr);
	m_iComboKmIdMbr = i_iKmIdMbr;

	// ���i�z�u���̓f�[�^�֐ݒ�
	int iMbrId;
	MhMbr* pMbr;
	iMbrId = m_iComboPartsMbrId[i_iKmIdMbr];					// ���@�`��ID
	mtPlcInp::SetIdMbr( iMbrId); 
	pMbr = BuzaiCode::MhGetpMbr( iMbrId);						// ���@�`���d�l
	mtPlcInp::SetpMbr( pMbr);
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	���@�^���R���{�{�b�N�X�𐡖@�^���őI����
//	�J�����g�̐��@�^�����ڔԍ���ݒ肷��
//							��-1: �Y���Ȃ�
//							�� 0: ���@�^��ID

int mmIoPartsAttr::SelectComboPartsMbrByMbrCd( MCHAR* sCdMbr)
{
	int			iMbrId = -1;
	int			iKmIdMbr;

	iKmIdMbr = z_mnIA.GetComboPartsMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);		// "�����@�^���e�[�u���ɖ��ݒ�ł��D"
		MQUIT;
	}
	z_mmIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = m_iComboPartsMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

} // namespace MC