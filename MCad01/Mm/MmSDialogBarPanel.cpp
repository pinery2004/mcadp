//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDialogBarPanel.cpp
//
//		
//	�p�l���ԍ��I���_�C�A���O�o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MmDefine.h"
#include "resource.h"

#define		MC_PANEL_ALL	Mstr( "�@�@�S")

namespace MC
{

// �p�l���ԍ��I��p�R���{�{�b�N�X

static MINT z_nComboPanelNo;									// �\�����ڐ�
static MINT	z_iComboPanelNo[MX_CMB_PANELNO];					// �\�����ڑΉ��p�l���ԍ�

///////////////////////////////////////////////////////////////////////////////
//	�p�l���ԍ��I��p�R���|�{�b�N�X�Ƀp�l���ԍ��̍���(�ꗗ)��ݒ肵
//	�p�l���ԍ��e�[�u�����쐬����

void mtInpAttr::InitComboPanelNo()
{
	MINT		ic1;
	MINT		ic;
	MINT		ip = 0;
	CString		sKomoku;

	CComboBox *pCmb = MmpComboPanelNo();
	pCmb->ResetContent();

//	�S�p�l���ԍ��ݒ�
	for ( ic=0; ic<10; ic++) {
		ASSERT( ip < MX_CMB_PANELNO - 1);								// �p�l���ԍ��I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboPanelNo[ip++] = ic;
	}
	z_nComboPanelNo = ip;												// �p�l���� + 1("�S")�@
//
	if ( z_nComboPanelNo == 0)
		goto exit;

	pCmb->InsertString( -1, MC_PANEL_ALL);

	for ( ic1=1; ic1<z_nComboPanelNo; ic1++) {
		sKomoku.Format(Mstr( "  %4d"), z_iComboPanelNo[ic1]);

		pCmb->InsertString( -1, sKomoku);
	}
exit:
	if ( z_nComboPanelNo == 0)
		pCmb->InsertString( -1, Mstr( "none"));
}

///////////////////////////////////////////////////////////////////////////////
//	�R���{�{�b�N�X�Ƀp�l���ԍ���\����
//	�J�����g�̃p�l���ԍ��I�����ڔԍ���ݒ肷��

void mtInpAttr::SetComboPanelNo(
						MINT	iPanelNo			// (I  ) �p�l���ԍ�
				)
{
	CComboBox *pCmb = MmpComboPanelNo();
	CString strPanelNo;
	strPanelNo.Format( Mstr( "%5d"), iPanelNo);
	pCmb->SetWindowText(strPanelNo);
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃p�l���ԍ����擾����
//							��-1: ���I��
//							�� 0: �S
//							�� 1: �p�l���ԍ�
MINT mtInpAttr::GetComboPanelNo()
{
	MINT iPanelNo;
	CComboBox *pCmb = MmpComboPanelNo();
	CString strPanelNo;
	pCmb->GetWindowText(strPanelNo);
	if ( strPanelNo == MC_PANEL_ALL)
		iPanelNo = 0;
	else if ( strPanelNo == Mstr( ""))
		iPanelNo = -1;
	else
		iPanelNo = MsGetMINT( strPanelNo);
	return iPanelNo;
}

} // namespace MC