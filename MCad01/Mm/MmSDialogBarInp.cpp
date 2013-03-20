//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDialogBarInp.cpp
//
//		
//	���͑I���_�C�A���O�o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "resource.h"
#include "MainFrm.h"
#include "MmDefine.h"

#define DLL_EXPORT_MC_HAITIIN_DO
#define DLL_EXPORT_MC_INPMODE_DO
#include "MmLib.h"

namespace MC
{

static MINT		z_iComboInpKb;
static MINT		z_iComboCdMarume;
static MINT		z_iComboCdPlc;

// CMmDialogBarInp �_�C�A���O


// CMmDialogBarInp ���b�Z�[�W �n���h��

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̓��͓_�敪��ݒ肵�A���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
//
void mtInpMode::SetComboInpKb(
						MINT		iInpKb		// (I  ) ���͓_�敪
				)
{
	System::GetpMainFrame()->SetComboInp1( iInpKb);
	z_iComboInpKb = iInpKb;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̓��͓_�敪���擾����
//							��1 : �P�_����
//							��2 : �����P�_����
//							��3 : �����Q�_����
//							��4 : ������
//							��5 : ���R����
//
MINT mtInpMode::GetComboInpKb()
{
	return z_iComboInpKb;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̊ۂ߃R�[�h��ݒ肵�A�R���{�{�b�N�X�Ɋۂ߃R�[�h��\������
//

void mtInpMode::SetComboCdMarume(
						MINT		iCdMarume		// (I  ) �ۂ߃R�[�h
					)
{
	System::GetpMainFrame()->SetComboInp2( iCdMarume);
	z_iComboCdMarume = iCdMarume;
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

MINT mtInpMode::GetComboCdMarume()
{
	MINT	iMCD;

	if ( z_iComboCdMarume >= MP_MRMCDN && z_iComboCdMarume <= MP_MRMCD4) 
		iMCD = z_iComboCdMarume;
	else if ( z_iComboCdMarume == MP_MRMCD6)
		iMCD = 6;
	else if ( z_iComboCdMarume == MP_MRMCD8)
		iMCD = 8;
	else
		ASSERT( 0);												// �ۂ߃R�[�h�G���[�@<ERROR>
		
	return iMCD;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̔z�u�R�[�h��ݒ肵�A�R���{�{�b�N�X�ɔz�u�R�[�h��\������
//

void mtHaitiIn::SetComboCdPlc(
						MINT		iCdPlc		// (I  ) �z�u�R�[�h
					)
{
	System::GetpMainFrame()->SetComboInp3( iCdPlc);
//	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( m_iComboInp3);
// 	System::GetpMainFrame()->((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( iCdPlc);
	z_iComboCdPlc = iCdPlc;
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̔z�u�R�[�h���擾����
//							��0 : �C��
//							��1 : �ǐc�t��
//							��2 : �����\�����t��

MINT mtHaitiIn::GetComboCdPlc()
{
	return z_iComboCdPlc;
}

} // namespace MC