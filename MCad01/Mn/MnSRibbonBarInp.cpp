//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmRibbonBarInp.cpp
//
//		
//	���͑I�����{���o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "resource.h"
#include "MainFrm.h"
#include "MhDefParts.h"

#define DLL_EXPORT_MC_HAITIIN_DO
#define DLL_EXPORT_MC_INPMODE_DO
#include "MmLib.h"

namespace MC
{

static MINT		z_iComboInpKbnCd;
static MINT		z_iComboMarume;
static MINT		z_iComboPlcIzonCd;

// CMnRibbonBarInp �_�C�A���O


// CMnRibbonBarInp ���b�Z�[�W �n���h��

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̓��͓_�敪�R�[�h�I��p�R���{�{�b�N�X�̓��͓_�敪�R�[�h��I������	(�{��)
//
void mnIoPartsAttr::SelectComboInpKbnByInpKbnCdXqt(
						MINT		iCdInpKbn		// (I  ) ���͓_�敪
				)
{
	System::GetpMainFrame()->SelectComboInp1( iCdInpKbn);
	z_iComboInpKbnCd = iCdInpKbn;									//	�J�����g�̓��͓_�敪�R�[�h
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̓��͓_�敪���擾����
//							��1 : �P�_����
//							��2 : �����P�_����
//							��3 : �����Q�_����
//							��4 : ������
//							��5 : ���R����
//
MINT mnIoPartsAttr::GetComboInpKbnCd()
{
	return z_iComboInpKbnCd;
}

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̊ۂ߃R�[�h�I��p�R���{�{�b�N�X�̊ۂ߃R�[�h��I������	(�{��)
//

void mnIoPartsAttr::SelectComboMarumeByMarumeCdXqt(
						MINT		iCdMarume		// (I  ) �ۂ߃R�[�h
					)
{
	System::GetpMainFrame()->SelectComboInp2( iCdMarume);
	z_iComboMarume = iCdMarume;									// �J�����g�̊ۂ߃R�[�h
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̊ۖڃR�[�h���擾����
//							��0 : �ۂ߂Ȃ�
//							��1 : �P�^�P�O���b�h�ۂ�
//							��2 : �P�^�Q�O���b�h�ۂ�
//							��3 : �P�^�R�O���b�h�ۂ�
//							��4 : �P�^�S�O���b�h�ۂ�
//							��5 : �P�^�U�O���b�h�ۂ�
//							��6 : �P�^�W�O���b�h�ۂ�

MINT mnIoPartsAttr::GetComboMarumeCd()
{
	MINT	iMCD;

	if ( z_iComboMarume >= MP_MRMCDN && z_iComboMarume <= MP_MRMCD4) 
		iMCD = z_iComboMarume;
	else if ( z_iComboMarume == MP_MRMCD6)
		iMCD = 6;
	else if ( z_iComboMarume == MP_MRMCD8)
		iMCD = 8;
	else
		ASSERT( 0);												// �ۂ߃R�[�h�G���[�@<ERROR>
		
	return iMCD;
}

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̔z�u�ˑ��R�[�h�I��p�R���{�{�b�N�X�̔z�u�ˑ��R�[�h��I������
//

void mnIoPartsAttr::SelectComboPlcIzonCdByPlaceCdXqt(
						MINT		iCdPlc		// (I  ) �z�u�ˑ��R�[�h
					)
{
	System::GetpMainFrame()->SelectComboInp3( iCdPlc);
	z_iComboPlcIzonCd = iCdPlc;									//	�J�����g�̔z�u�ˑ��R�[�h
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̔z�u�ˑ��R�[�h���擾����
//							��0 : �C��
//							��1 : �ǐc�t��
//							��2 : �����\�����t��

MINT mnIoPartsAttr::GetComboPlcIzonCd()
{
	return z_iComboPlcIzonCd;
}

} // namespace MC