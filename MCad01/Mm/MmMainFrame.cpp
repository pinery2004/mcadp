//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmMainframe.cpp
//
//		���C���t���[���Ǘ�
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

//namespace MC
//{
//// MainFrame Pointer �ݒ�
//void	MC::System::MmMainFrame( CMainFrame* pMainFrame)
//{
//	System::GetpMainFrame = pMainFrame;
//}
//
//// MainFrame Pointer �擾
//CMainFrame* MC::System::MmGetpMainFrame()
//{
//	return System::GetpMainFrame;
//}
//
//// MCADApp Pointer �ݒ�
//void	MC::System::MmMCADApp( CMCADApp* pMCADApp)
//{
//	ms_pMCADApp = pMCADApp;
//}
//
//// MCADApp Pointer �擾
//CMCADApp* MC::System::MmGetpMCADApp()
//{
//	return ms_pMCADApp;
//}
//
//}

// MainFrm.cpp : CMainFrame �N���X�̎���
//

// CMainFrame �f�f

#ifdef _DEBUG
//void CMainFrame::AssertValid() const
//{
//	CMDIFrameWnd::AssertValid();
//}

//void CMainFrame::Dump( CDumpContext& dc) const
//{
//	CMDIFrameWnd::Dump( dc);
//}

#endif //_DEBUG


// CMainFrame ���b�Z�[�W �n���h��

CMFCRibbonComboBox* mmpComboBuzai()
{
	CMFCRibbonBar* pRibbonBar;
	pRibbonBar = &MC::System::GetpMainFrame()->m_wndRibbonBar;

	CMFCRibbonCategory* pRibbonCategory;
	pRibbonCategory = pRibbonBar->GetActiveCategory();

	CString sName;
	sName = pRibbonCategory->GetName();

	MCHAR cName[20];
	Mstrcpy_s( cName, pRibbonCategory->GetName());

	CString sName2;
	sName2 = z_MCadApp.m_pMainFrame->m_wndRibbonBar.GetActiveCategory()->GetName();

	TRACE( _T(" �J�����g�J�e�S�� = %s %s %s\n"), cName, sName, sName2);

	MCHAR sTest[] = _T("�ӏ�");
	TRACE( _T(" �J�����g�J�e�S�� = %s\n"), sTest);

	CArray<CMFCRibbonBaseElement* ,CMFCRibbonBaseElement*> arButtons;
	MC::System::GetpMainFrame()->m_wndRibbonBar.GetElementsByID( IDC_CMBK_BZI1, arButtons);

	CMFCRibbonComboBox* pComboBuzai;
	int iIdcCmb;
	int iCCategory;
	iCCategory = MC::z_mnIA.GetCCategory();
	if ( iCCategory == MP_SENTAKU_ISYOU) {
		iIdcCmb = IDC_CMBS_BZI1;
	} else {
		iIdcCmb = IDC_CMBK_BZI1;
	}
	pComboBuzai = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(iIdcCmb));
	return pComboBuzai;
}

CMFCRibbonComboBox* mmpComboPartsMbr()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMBK_BZI2));
}

CMFCRibbonComboBox* mmpComboInpTp()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp1));
}

CMFCRibbonComboBox* mmpComboMarume()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp2));
}

CMFCRibbonComboBox* mmpComboPlcCd()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp3));
}

CMFCRibbonComboBox* mmpComboPanelNo()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_COMBOPANELNO));
}
