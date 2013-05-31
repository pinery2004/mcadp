//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPartsAttr2.cpp
//
//		
//	�������̓��{���o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
//#define	 WINVER	0x0400
#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g

#include "MsMCAD.h"
#include "MainFrm.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MmWnd.h"
#include "MhInpPlcParts.h"
#include "resource.h"
#include "..\\MCAD\\resource.h"
#include "MhPlcParts.h"
#include "MhLib.h"
#include "MgGeo.h"

#define MC_SZ_CMBATTR	6
#define MC_SZ_CHKATTR	4

namespace MC
{

//SSstatic int z_IdcComboAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
//								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
//static int z_IdcStaticAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
//								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
static int z_IdcCheckAttr[4] =	{ IDC_CHECKATTR1, IDC_CHECKATTR2,
								  IDC_CHECKATTR3, IDC_CHECKATTR4};

//static int z_Combo_Attr[MC_SZ_CMBATTR];
static int z_Check_Attr[MC_SZ_CHKATTR];

//////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�`�F�b�N�{�b�N�X�ԍ����擾����

int mnIoPartsAttr::GetCheckAttrNo(
						MCCHKATTR	i_iAttr		// ����ID
				)
{
	int	 ic;
	int	 iChkNo = 0;

	for ( ic=0; ic<MC_SZ_CHKATTR; ic++) {
		if ( i_iAttr == z_Check_Attr[ic])
			break;
	}
	if ( ic < MC_SZ_CHKATTR)
		iChkNo = ic + 1;
	return iChkNo;
}


///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�`�F�b�N�{�b�N�X�̃^�C�g����ݒ肷��
void mnIoPartsAttr::SetCheckAttrText(
						int		i_iChkNo,		// �`�F�b�N�{�b�N�X�ԍ�
						MCHAR*	i_sTitle		// �^�C�g���@�܂��́@NULL:�`�F�b�N�{�b�N�X��\�����Ȃ�
				)
{
	CMFCRibbonCheckBox* pCheckBox;
	pCheckBox = DYNAMIC_DOWNCAST( CMFCRibbonCheckBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcCheckAttr[i_iChkNo - 1]));

	if ( i_sTitle) {
		pCheckBox->SetToolTipText( i_sTitle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��

void mnIoPartsAttr::SetCheckAttrCkb(
						int		i_iChkNo,		// �`�F�b�N�{�b�N�X�ԍ�
						int		i_iCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				)
{
//U	CButton* pCheckAttr;
//U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
//U	pCheckAttr->SetCheck( i_iCheckAttr);
	CMFCRibbonCheckBox* pCheckBox;
	pCheckBox = DYNAMIC_DOWNCAST( CMFCRibbonCheckBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcCheckAttr[i_iChkNo - 1]));
	pCheckBox->SetData( i_iCheckAttr);
}

///////////////////////////////////////////////////////////////////////////////
//	�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��

void mnIoPartsAttr::SetCheckAttr(
						MCCHKATTR	i_iAttr,	// ����ID
						int			i_iCheckAttr// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				)
{
	int	 iChkNo;
	iChkNo = GetCheckAttrNo( i_iAttr);
	if ( iChkNo != 0)
		SetCheckAttrCkb( iChkNo, i_iCheckAttr);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
//
int mnIoPartsAttr::GetCheckAttrCkb(				// �`�F�b�N�}�[�N�@0:OFF, 1:ON
						int		i_iChkNo		// �`�F�b�N�{�b�N�X�ԍ�
				)
{
//U	CButton* pCheckAttr;
//U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
//U	return pCheckAttr->GetCheck();
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//	�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
//

int mnIoPartsAttr::GetCheckAttr(					// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCHKATTR	i_iAttr,	// ����ID
						int*		o_iCheckAttr// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				)
{
	int		ist;
	int		iChkNo;

	iChkNo = GetCheckAttrNo( i_iAttr);

	if ( iChkNo != 0) {
		*o_iCheckAttr = GetCheckAttrCkb( iChkNo);
		ist = 1;
	} else {
		*o_iCheckAttr = 0;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�

int mnIoPartsAttr::MnCalcInpAtMode()
{
	int			iMode;							// �����l���̓��[�h
	int			iGp;
	int			iBr;

	int			iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;

	// ���ޑ����l���̓��[�h( iMode)(�\������)�̌���
	iGp = z_mnIA.GetKCdGp();
	iBr = z_mnIA.GetKCdBr();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	if ( pPartsSpec->IsTategu()) {								// (���i���ID == ����)
		iMode = MP_AT_TATEGU;									//			�������

	} else if ( pPartsSpec->IsFrame())	{						// (���i���ID == ���Ęg | ��) (�������̓��[�h == ����)
		iMode = MP_AT_VRT_PARTS;								//			�������ޓ���

	} else if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {	// (���i���ID == �p�l�� | �J��)
		if ( iGp == MP_GP_YUKA || iGp == MP_GP_TENJO)			//		(�\���R�[�h == �� | �V��)
			iMode = MP_AT_YTPANEL;								//			���E�V��p�l������

		else if ( iGp == MP_GP_YANE)							//		(�\�� == ����)
			iMode = MP_AT_YANEPANEL;							//			�����p�l������

		else													//		(���̑�)
			iMode = MP_AT_HRZ_PARTS;							//			���u�����ޓ���

	} else if ( iBr == MP_BR_YANE) {							// (���� == ����)
		if ( iGp == MP_GP_YANE) 								//		(�\�� == ����)
			iMode = MP_AT_YANE;									//			��������
		else													//		(���̑�)
			iMode = MP_AT_HRZ_PARTS;							//			���u�����ޓ���

	} else {													// (���̑�)
		iMode = MP_AT_HRZ_PARTS;								//			���u������
	}
	return iMode;
}

} // namespace MC