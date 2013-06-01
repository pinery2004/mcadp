//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmMainframe.cpp
//
//		メインフレーム管理
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MhDefParts.h"
#define DLL_EXPORT_MC_SYSTEM_DO
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "..\\MCAD\\resource.h"

#include "MCAD.h"
#include "MainFrm.h"

// CMainFrame メッセージ ハンドラ

CMFCRibbonComboBox* mmpComboBuzai()
{
																								//SS	CMFCRibbonBar* pRibbonBar;
	mnMFCRibbonBar* pRibbonBar;
	pRibbonBar = &MC::System::GetpMainFrame()->m_wndRibbonBar;
//---> Debug用
	CMFCRibbonCategory* pRibbonCategory;
	pRibbonCategory = pRibbonBar->GetActiveCategory();

	CString sName;
	sName = pRibbonCategory->GetName();

	MCHAR cName[20];
	Mstrcpy_s( cName, pRibbonCategory->GetName());

	CString sName2;
	sName2 = z_MCadApp.m_pMainFrame->m_wndRibbonBar.GetActiveCategory()->GetName();

	TRACE( _T(" カレントカテゴリ = %s %s %s\n"), cName, sName, sName2);

	MCHAR sTest[] = _T("意匠");
	TRACE( _T(" カレントカテゴリ = %s\n"), sTest);

	CArray<CMFCRibbonBaseElement* ,CMFCRibbonBaseElement*> arButtons;
	MC::System::GetpMainFrame()->m_wndRibbonBar.GetElementsByID( IDC_CMBK_BZI1, arButtons);
//<----
	int iIdcCmb;
	int iCurCategory;
	iCurCategory = MC::z_mnIA.GetCurCategory();
	if ( iCurCategory == MP_SENTAKU_ISYOU) {
		iIdcCmb = IDC_CMBS_BZI1;
	} else {
		iIdcCmb = IDC_CMBK_BZI1;
	}
	CMFCRibbonComboBox* pComboBuzai;
	pComboBuzai = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbonBar->FindByID(iIdcCmb));
	return pComboBuzai;
}

CMFCRibbonComboBox* mmpComboMbr()
{
																								//SS	CMFCRibbonBar* pRibbonBar;
	mnMFCRibbonBar* pRibbonBar;
	pRibbonBar = &MC::System::GetpMainFrame()->m_wndRibbonBar;
	int iIdcCmb;
	int iCurCategory;
	iCurCategory = MC::z_mnIA.GetCurCategory();
	if ( iCurCategory == MP_SENTAKU_ISYOU) {
		iIdcCmb = IDC_CMBS_BZI2;
	} else {
		iIdcCmb = IDC_CMBK_BZI2;
	}
	CMFCRibbonComboBox* pComboMbr;
	pComboMbr = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbonBar->FindByID(iIdcCmb));
	return pComboMbr;
	//	DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMBK_BZI2));
}

CMFCRibbonComboBox* mmpComboInpTp()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp1));
}

CMFCRibbonComboBox* mmpComboMarume()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp2));
}

CMFCRibbonComboBox* mmpComboPlcIzonCd()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp3));
}

CMFCRibbonComboBox* mmpComboPanelNo()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_COMBOPANELNO));
}
