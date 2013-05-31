//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPartsAttr2.cpp
//
//		
//	属性入力リボンバー
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
//#define	 WINVER	0x0400
#include <afxwin.h>         // MFC のコアおよび標準コンポーネント

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
//	属性値入力用チェックボックス番号を取得する

int mnIoPartsAttr::GetCheckAttrNo(
						MCCHKATTR	i_iAttr		// 属性ID
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
//	属性値入力用チェックボックスのタイトルを設定する
void mnIoPartsAttr::SetCheckAttrText(
						int		i_iChkNo,		// チェックボックス番号
						MCHAR*	i_sTitle		// タイトル　または　NULL:チェックボックスを表示しない
				)
{
	CMFCRibbonCheckBox* pCheckBox;
	pCheckBox = DYNAMIC_DOWNCAST( CMFCRibbonCheckBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcCheckAttr[i_iChkNo - 1]));

	if ( i_sTitle) {
		pCheckBox->SetToolTipText( i_sTitle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックスのチェックマークを設定する

void mnIoPartsAttr::SetCheckAttrCkb(
						int		i_iChkNo,		// チェックボックス番号
						int		i_iCheckAttr	// チェックマーク　0:OFF, 1:ON
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
//	チェックボックスのチェックマークを設定する

void mnIoPartsAttr::SetCheckAttr(
						MCCHKATTR	i_iAttr,	// 属性ID
						int			i_iCheckAttr// チェックマーク　0:OFF, 1:ON
				)
{
	int	 iChkNo;
	iChkNo = GetCheckAttrNo( i_iAttr);
	if ( iChkNo != 0)
		SetCheckAttrCkb( iChkNo, i_iCheckAttr);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックスのチェック有無を取得する
//
int mnIoPartsAttr::GetCheckAttrCkb(				// チェックマーク　0:OFF, 1:ON
						int		i_iChkNo		// チェックボックス番号
				)
{
//U	CButton* pCheckAttr;
//U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
//U	return pCheckAttr->GetCheck();
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//	チェックボックスのチェック有無を取得する
//

int mnIoPartsAttr::GetCheckAttr(					// ステイタス0(未設定) 1(設定)
						MCCHKATTR	i_iAttr,	// 属性ID
						int*		o_iCheckAttr// チェックマーク　0:OFF, 1:ON
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
//	構成コード、分類、部品種類IDより、属性値入力モードを求める

int mnIoPartsAttr::MnCalcInpAtMode()
{
	int			iMode;							// 属性値入力モード
	int			iGp;
	int			iBr;

	int			iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;

	// 部材属性値入力モード( iMode)(表示項目)の決定
	iGp = z_mnIA.GetKCdGp();
	iBr = z_mnIA.GetKCdBr();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	if ( pPartsSpec->IsTategu()) {								// (部品種類ID == 建具)
		iMode = MP_AT_TATEGU;									//			建具入力

	} else if ( pPartsSpec->IsFrame())	{						// (部品種類ID == たて枠 | 束) (属性入力モード == 垂直)
		iMode = MP_AT_VRT_PARTS;								//			垂直部材入力

	} else if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {	// (部品種類ID == パネル | 開口)
		if ( iGp == MP_GP_YUKA || iGp == MP_GP_TENJO)			//		(構成コード == 床 | 天井)
			iMode = MP_AT_YTPANEL;								//			床・天井パネル入力

		else if ( iGp == MP_GP_YANE)							//		(構成 == 屋根)
			iMode = MP_AT_YANEPANEL;							//			屋根パネル入力

		else													//		(その他)
			iMode = MP_AT_HRZ_PARTS;							//			横置き部材入力

	} else if ( iBr == MP_BR_YANE) {							// (分類 == 屋根)
		if ( iGp == MP_GP_YANE) 								//		(構成 == 屋根)
			iMode = MP_AT_YANE;									//			屋根入力
		else													//		(その他)
			iMode = MP_AT_HRZ_PARTS;							//			横置き部材入力

	} else {													// (その他)
		iMode = MP_AT_HRZ_PARTS;								//			横置き部材
	}
	return iMode;
}

} // namespace MC