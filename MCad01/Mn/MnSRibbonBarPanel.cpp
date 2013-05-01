//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPanel.cpp
//
//		
//	�p�l���ԍ��I�����{���o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhDefParts.h"
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

void mnIoPartsAttr::InitComboPanelNo()
{
	MINT		ic1;
	MINT		ic;
	MINT		ip = 0;
	CString		sKomoku;

	CMFCRibbonComboBox* pCmbBox = mmpComboPanelNo();
	pCmbBox->RemoveAllItems();
	pCmbBox->SetEditText(_T(" "));

//	�S�p�l���ԍ��ݒ�
	for ( ic=0; ic<10; ic++) {
		ASSERT( ip < MX_CMB_PANELNO - 1);								// �p�l���ԍ��I���R���{�{�b�N�X���ځ@�I�[�o�t���[�@<ERROR>
		z_iComboPanelNo[ip++] = ic;
	}
	z_nComboPanelNo = ip;												// �p�l���� + 1("�S")�@
//
	if ( z_nComboPanelNo == 0)
		goto exit;

	pCmbBox->AddItem( MC_PANEL_ALL);

	for ( ic1=1; ic1<z_nComboPanelNo; ic1++) {
		sKomoku.Format(Mstr( "  %4d"), z_iComboPanelNo[ic1]);

		pCmbBox->AddItem( sKomoku);
	}
exit:
	if ( z_nComboPanelNo == 0)
		pCmbBox->AddItem( Mstr( "none"));
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃p�l���ԍ��I�����ڔԍ���ݒ肵�@�R���{�{�b�N�X�Ƀp�l���ԍ���\������

void mnIoPartsAttr::SetComboPanelNo(
						MINT	iPanelNo			// (I  ) �p�l���ԍ�
				)
{
	CMFCRibbonComboBox *pCmbBox = mmpComboPanelNo();
	CString strPanelNo;
	strPanelNo.Format( Mstr( "%5d"), iPanelNo);
//E	pCmbBox->SetWindowText(strPanelNo);
	pCmbBox->SelectItem( strPanelNo);
}

///////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃p�l���ԍ����擾����
//							��-1: ���I��
//							�� 0: �S
//							�� 1: �p�l���ԍ�
MINT mnIoPartsAttr::GetComboPanelNo()
{
	int iPanelNo;
	int	iCurItemNo;
	CMFCRibbonComboBox *pCmbBox = mmpComboPanelNo();
	CString strPanelNo;
//E	pCmbBox->GetWindowText(strPanelNo);
	iCurItemNo = pCmbBox->GetCurSel();
	strPanelNo = pCmbBox->GetItem( iCurItemNo);
	if ( strPanelNo == MC_PANEL_ALL)
		iPanelNo = 0;
	else if ( strPanelNo == Mstr( ""))
		iPanelNo = -1;
	else
		iPanelNo = MsGetMINT( strPanelNo);
	return iPanelNo;
}

} // namespace MC