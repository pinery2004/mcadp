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
//	���{���o�[�̍��ڂ�ݒ肷��
//		�g�A���ށA���i�^�C�v�A���@�^��
//
MINT mnInpAttr::SetRibbonBar(					// �X�e�C�^�X 0:���� -1:�G���[
//S				MINT	iKumi,					// �g
//				MINT	iBr,					// ����
//				MCHAR*	cPartsTp,					// �^�C�v
//				MCHAR*	cMbr					// ���@�^�� �܂��� NULL
						MPKOSEI		i_irbKumi,			// �\��	�g
						MPBUNRUI	i_irbBunrui,		// �\��	����
						MCHAR*		i_crbPartsTp,		// ���i���
						MCHAR*		i_crbMbr			// ���i�����o�[()
				)
{
	MINT	ist;
	MPATTR	iAttr;

	z_mn.SetKCdGp( i_irbKumi);
	z_mn.SetKCdBr( i_irbBunrui);
	z_mn.InitComboPartsTp();									// �g�A���ނɑΉ����镔�i��I���\���ڂƂ��Đݒ肷��
	ist = z_mn.SetComboCdPartsTp( i_crbPartsTp);
	if ( ist < 0)
		MQUIT;

	z_mn.InitComboPartsMbr();										// ���i�ɑΉ����鐡�@�^����I���\���ڂƂ��Đݒ肷��
	if ( i_crbMbr) {
        ist = z_mn.SetComboCdMbr( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( i_irbKumi == MP_GP_YANE) {
			iAttr = MP_AT_YANE;
		} else {
			iAttr = MP_AT_AUTO;
		}
		z_mn.InitComboAttr( iAttr);								// �������͗p�R���{�{�b�N�X������������
	}
	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC