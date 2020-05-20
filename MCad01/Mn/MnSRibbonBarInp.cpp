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

//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: CMnRibbonBarInp.cpp ���{���o�[
//
//		
//
//
//  K.Matsu           13/06/01    Created.
//==========================================================================================

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̓��͓_�敪�R�[�h�I��p�R���{�{�b�N�X�̓��͓_�敪�R�[�h��I������	(�{��)
//
void mnIoPartsAttr::SelectComboInpKbnByInpKbnCdXqt(
						MINT		iCdInpKbn		// (I  ) ���͓_�敪
				)
{
	System::GetpMainFrame()->SelectComboInp1( iCdInpKbn);
	m_IA.m_IK[1].m_iComboInpKbn = iCdInpKbn;							//	�J�����g�̓��͓_�敪�R�[�h
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
	return m_IA.m_IK[1].m_iComboInpKbn;
}

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̊ۂ߃R�[�h�I��p�R���{�{�b�N�X�̊ۂ߃R�[�h��I������	(�{��)
//

void mnIoPartsAttr::SelectComboMarumeByMarumeCdXqt(
						MINT		i_iMarumeCd	// (I  ) �ۂ߃R�[�h
					)
{
	int		iComboMarume;

	if ( i_iMarumeCd >= MP_MRMCDN && i_iMarumeCd <= MP_MRMCD4)
		iComboMarume = i_iMarumeCd;
	else if ( i_iMarumeCd == 6)
		iComboMarume = MP_MRMCD6;
	else if ( i_iMarumeCd == 6)
		iComboMarume = MP_MRMCD6;
	else
		ASSERT( 0);												// �ۂ߃R�[�h�G���[�@<ERROR>
	
	System::GetpMainFrame()->SelectComboInp2( iComboMarume);
	m_IA.m_IK[1].m_iComboMarume = iComboMarume;					// �J�����g�̊ۂ߃R�[�h
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
	int		iComboMarume;
	int		iMCD;

	iComboMarume = m_IA.m_IK[1].m_iComboMarume;


	if ( iComboMarume >= MP_MRMCDN && iComboMarume <= MP_MRMCD4) 
		iMCD = iComboMarume;
	else if ( iComboMarume == MP_MRMCD6)
		iMCD = 6;
	else if ( iComboMarume == MP_MRMCD8)
		iMCD = 8;
	else
		ASSERT( 0);												// �ۂ߃R�[�h�G���[�@<ERROR>
		
	return iMCD;
}

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̔z�u�ˑ��R�[�h�I��p�R���{�{�b�N�X�̔z�u�ˑ��R�[�h��I������
//

void mnIoPartsAttr::SelectComboPlcIzonCdByPlaceCdXqt(
						MINT		i_iComboInpKbn	// (I  ) �z�u�ˑ��R�[�h
					)
{
	System::GetpMainFrame()->SelectComboInp3( i_iComboInpKbn);
	m_IA.m_IK[1].m_iComboPlcIzon = i_iComboInpKbn;					//	�J�����g�̔z�u�ˑ��R�[�h
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̔z�u�ˑ��R�[�h���擾����
//							��0 : �C��
//							��1 : �ǐc�t��
//							��2 : �����\�����t��

MINT mnIoPartsAttr::GetComboPlcIzonCd()
{
	return m_IA.m_IK[1].m_iComboPlcIzon;
}

} // namespace MC