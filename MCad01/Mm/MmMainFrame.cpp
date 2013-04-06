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


class CMCADApp*		_System::ms_pMCADApp;		// �A�v���P�[�V�����|�C���^ 
class CMainFrame*	_System::ms_pMainFrame;		// ���C���t���[���|�C���^ 

////namespace MC
////{
////// MainFrame Pointer �ݒ�
////void	MC::System::MmMainFrame( CMainFrame* pMainFrame)
////{
////	System::GetpMainFrame = pMainFrame;
////}
////
////// MainFrame Pointer �擾
////CMainFrame* MC::System::MmGetpMainFrame()
////{
////	return System::GetpMainFrame;
////}
////
////// MCADApp Pointer �ݒ�
////void	MC::System::MmMCADApp( CMCADApp* pMCADApp)
////{
////	ms_pMCADApp = pMCADApp;
////}
////
////// MCADApp Pointer �擾
////CMCADApp* MC::System::MmGetpMCADApp()
////{
////	return ms_pMCADApp;
////}
////
////}

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

CMFCRibbonComboBox* MnpComboBuzai()
{
	static CMFCRibbonComboBox* pIDC_CMB_BZI1 = 0;
//E	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_BZI1));
//S	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
//S	CMFCRibbonBaseElement* pFCRibbonBaseElement = pMainFrame->m_wndRibbonBar.FindByID(IDC_CMB_BZI1);
//E	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pMainFrame->m_wndRibbonBar.FindByID(IDC_CMB_BZI1));
	if ( pIDC_CMB_BZI1 == 0) {
		pIDC_CMB_BZI1 =  DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_BZI1));
	}
	return pIDC_CMB_BZI1;
}

CMFCRibbonComboBox* MmpComboMbr()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_BZI2));
}

CMFCRibbonComboBox* MmpComboInpTp()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp1));
}

CMFCRibbonComboBox* MmpComboCdMarume()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp2));
}

CMFCRibbonComboBox* MmpComboCdPlc()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_CMB_Inp3));
}

CMFCRibbonComboBox* MnpComboPanelNo()
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, MC::System::GetpMainFrame()->m_wndRibbonBar.FindByID(IDC_COMBOPANELNO));
}
