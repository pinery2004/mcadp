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
MINT mnIoPartsAttr::SetRibbonBar(					// �X�e�C�^�X 0:���� -1:�G���[
						MPKOSEI		i_irbKumi,			// �\��	�g
						MPBUNRUI	i_irbBunrui,		// �\��	����
						MCHAR*		i_crbPartsSpec,		// ���i���
						MCHAR*		i_crbMbr			// ���i�����o�[()
				)
{
	MINT	ist;
	MPATTR	iAttr;

	z_mnIA.SetKCdGp( i_irbKumi);
	z_mnIA.SetKCdBr( i_irbBunrui);
	z_mnIA.InitComboPartsNm();									// �g�A���ނɑΉ����镔�i��I���\���ڂƂ��Đݒ肷��
	ist = z_mnIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
	if ( ist < 0)
		MQUIT;

	z_mnIA.InitComboPartsMbr();									// ���i�ɑΉ����鐡�@�^����I���\���ڂƂ��Đݒ肷��
	if ( i_crbMbr) {
        ist = z_mnIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( i_irbKumi == MP_GP_YANE) {
			iAttr = MP_AT_YANE;
		} else {
			iAttr = MP_AT_AUTO;
		}
//S		z_mnIA.InitComboAttr( iAttr);							// �������͗p�R���{�{�b�N�X������������
		z_mmIA.InitComboAttr( iAttr);							// �������͗p�R���{�{�b�N�X������������
	}
	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC