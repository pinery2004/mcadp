//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPanel.cpp
//
//		
//	パネル番号選択リボンバー
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

#define		MC_PANEL_ALL	Mstr( "　　全")

namespace MC
{

// パネル番号選択用コンボボックス

static MINT z_nComboPanelNo;									// 表示項目数
static MINT	z_iComboPanelNo[MX_CMB_PANELNO];					// 表示項目対応パネル番号

///////////////////////////////////////////////////////////////////////////////
//	パネル番号選択用コンポボックスにパネル番号の項目(一覧)を設定し
//	パネル番号テーブルを作成する

void mnIoPartsAttr::InitComboPanelNo()
{
	MINT		ic1;
	MINT		ic;
	MINT		ip = 0;
	CString		sKomoku;

	CMFCRibbonComboBox* pCmbBox = mmpComboPanelNo();
	pCmbBox->RemoveAllItems();
	pCmbBox->SetEditText(_T(" "));

//	全パネル番号設定
	for ( ic=0; ic<10; ic++) {
		ASSERT( ip < MX_CMB_PANELNO - 1);								// パネル番号選択コンボボックス項目　オーバフロー　<ERROR>
		z_iComboPanelNo[ip++] = ic;
	}
	z_nComboPanelNo = ip;												// パネル数 + 1("全")　
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
//	カレントのパネル番号選択項目番号を設定し　コンボボックスにパネル番号を表示する

void mnIoPartsAttr::SetComboPanelNo(
						MINT	iPanelNo			// (I  ) パネル番号
				)
{
	CMFCRibbonComboBox *pCmbBox = mmpComboPanelNo();
	CString strPanelNo;
	strPanelNo.Format( Mstr( "%5d"), iPanelNo);
//E	pCmbBox->SetWindowText(strPanelNo);
	pCmbBox->SelectItem( strPanelNo);
}

///////////////////////////////////////////////////////////////////////////////
//	カレントのパネル番号を取得する
//							＝-1: 未選択
//							＝ 0: 全
//							≧ 1: パネル番号
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