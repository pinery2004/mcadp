//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MhDefParts.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MsDefine.h"
#include "MmWnd.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̕��i�I��p���ڂ�ݒ肷��
//		�g�A���ށA���i�^�C�v�A���@�^��
//
MINT mnIoPartsAttr::SetRibbonBarXqt(						// �X�e�C�^�X 0:���� -1:�G���[
						MPKOSEI		i_irbKumi,			// �\���g
						MPBUNRUI	i_irbBunrui,		// �\������
						MCHAR*		i_crbPartsSpec,		// ���i���		(���i��)
						MCHAR*		i_crbMbr			// ���i�����o�[	(���@�^��)
				)
{
	MINT	ist;
	MPATTR	iAttr;

	// �g��I������
	z_mnIA.SetKCdGp( i_irbKumi);

	// ���ނ�I������
	z_mnIA.SetKCdBr( i_irbBunrui);

	// ���i���(���i��)�̃_�C�A���O�̍��ڂ�ݒ肵���i����I������
	// �g�A���ނɑΉ����镔�i����I���\���ڂƂ��Đݒ肷��
	z_mnIA.InitComboPartsNm();
	ist = z_mnIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
	if ( ist < 0)
		MQUIT;
	if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {
		z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
		z_mmIA.InitComboPartsNm();
		ist = z_mmIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
		if ( ist < 0)
			MQUIT;
	}

	// ���i���ɑΉ����郁���o�[(���@�^��)��I���\���ڂƂ��Đݒ肷��
	z_mnIA.InitComboPartsMbr();									// ���{���o�[�̕��i���I��p�R���{�{�b�N�X
	if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {
		z_mmIA.InitComboPartsMbr();								// �_�C�A���O�̕��i���I��p�R���{�{�b�N�X
	}
	if ( i_crbMbr >= 0) {

		// ���{���o�[�̃����o�[�I��p�R���{�{�b�N�X�̃����o�[��I������
        ist = z_mnIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {

			// �_�C�A���O�̃����o�[�I��p�R���{�{�b�N�X�̃����o�[��I������
			ist = z_mmIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
			if ( ist < 0)
				MQUIT;

			// �_�C�A���O�̑������͗p�R���{�{�b�N�X������������
			if ( i_irbKumi == MP_GP_YANE) {
				iAttr = MP_AT_YANE;
			} else {
				iAttr = MP_AT_AUTO;
			}
			z_mmIA.InitComboAttrXqt( iAttr);
		}
	}
	WindowCtrl::ReDrawWnd();

	ist = 0;
exit:
	return ist;
}

} // namespace MC