//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdMessage.cpp
//
//		���b�Z�[�W
//
//
//  K.Matsu           12/15/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgMat.h"

#include "MdModel.h"

namespace MC
{

//
//===========================================================================
//		���b�Z�[�W�ԍ����w�肵���K�C�_���X���b�Z�[�W�̕\��
//
MINT	MgmDispGuide (
						MINT		i_iGMsg		// �K�C�_���X���b�Z�[�W�ԍ�
				)
{
	return 0;
}

//
//===========================================================================
//		��������w�肵���K�C�_���X���b�Z�[�W�̕\��
//
MINT	MgmDispGuideText (
						MCHAR		i_sGMsg		// ���b�Z�[�W������
				)
{
	return 0;
}



//
//===========================================================================
//		�K�C�_���X���b�Z�[�W�̏���
//
MINT	MgmClearGuide ( )
{
	return 0;
}

//
//===========================================================================
//		�G���[���b�Z�[�W�̕\��
//
//		���b�Z�[�W�ԍ����w�肵�āA���b�Z�[�W�f�[�^�x�[�X�ɓo�^����Ă���G���[���b�Z�[�W��\������B
//		�֐����ƃG���[�R�[�h�́A�G���[���b�Z�[�W�ɕt�����ĕ\������B
//		�w�肳�ꂽ���b�Z�[�W�ԍ����A���b�Z�[�W�f�[�^�x�[�X�ɂȂ��ꍇ�́A�w�肳�ꂽ���b�Z�[�W�ԍ���\������B
//
MINT	MgmDispError (
						MCHAR		i_sMsg[],	// �֐���
						MINT		i_iEMsg,	// �G���[���b�Z�[�W�ԍ�
						MINT		i_icdEMsg	// �G���[�R�[�h
				)
{
	return 0;
}

} // namespace MC
