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
#include "MmDefine.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MsDefine.h"
#include "MmWnd.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	�_�C�A���O�o�[�̍��ڂ�ݒ肷��
//		�g�A���ށA���i�^�C�v�A���@�^��
//
MINT mtInpAttr::SetDialogBar(						// �X�e�C�^�X 0:���� -1:�G���[
				MINT	iKumi,				// �g
				MINT	iBr,				// ����
				MCHAR*	cTpPts,				// �^�C�v
				MCHAR*	cMbr				// ���@�^�� �܂��� NULL
				)
{
	MINT	ist;

	mtInpMode::SetKGp( iKumi);

	mtInpMode::SetKBr( iBr);

	mtInpAttr::InitComboTpPtsAttr();									// �g�A���ނɑΉ����镔�i��I���\���ڂƂ��Đݒ肷��

	ist = mtInpAttr::SetComboCdTpPts( cTpPts);
	if ( ist < 0)
		MQUIT;

	mtInpAttr::InitComboPtsMbr();									// ���i�ɑΉ����鐡�@�^����I���\���ڂƂ��Đݒ肷��

	if ( cMbr) {
        ist = mtInpAttr::SetComboCdMbr( cMbr);
		if ( ist < 0)
			MQUIT;
	mtInpAttr::InitComboAttr( MP_AT_AUTO);								// �������͗p�R���{�{�b�N�X������������

	}

	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC