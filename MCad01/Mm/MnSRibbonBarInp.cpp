//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmRibbonBarInp.cpp
//
//		
//	入力選択リボンバー
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

static MINT		z_iComboInpKbCd;
static MINT		z_iComboMarume;
static MINT		z_iComboPlcCd;

// CMnRibbonBarInp ダイアログ


// CMnRibbonBarInp メッセージ ハンドラ

///////////////////////////////////////////////////////////////////////////////
//	カレントの入力点区分を設定し、入力点区分選択用のコンボボックスに表示する
//
void mnInpAttr::SelectComboInpKbnByInpKbnCd(
						MINT		iCdInpKb		// (I  ) 入力点区分
				)
{
	System::GetpMainFrame()->SelectComboInp1( iCdInpKb);
	z_iComboInpKbCd = iCdInpKb;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの入力点区分を取得する
//							＝1 : １点入力
//							＝2 : 方向１点入力
//							＝3 : 長さ２点入力
//							＝4 : 区画入力
//							＝5 : 自由入力
//
MINT mnInpAttr::GetComboInpKbCd()
{
	return z_iComboInpKbCd;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの丸めコードを設定し、コンボボックスに丸めコードを表示する
//

void mnInpAttr::SelectComboMarumeByMarumeCd(
						MINT		iCdMarume		// (I  ) 丸めコード
					)
{
	System::GetpMainFrame()->SelectComboInp2( iCdMarume);
	z_iComboMarume = iCdMarume;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの丸目コードを取得する
//							＝0 : 丸めなし
//							＝1 : １／１グリッド丸め
//							＝2 : １／２グリッド丸め
//							＝3 : １／３グリッド丸め
//							＝4 : １／４グリッド丸め
//							＝5 : １／６グリッド丸め
//							＝6 : １／８グリッド丸め

MINT mnInpAttr::GetComboMarumeCd()
{
	MINT	iMCD;

	if ( z_iComboMarume >= MP_MRMCDN && z_iComboMarume <= MP_MRMCD4) 
		iMCD = z_iComboMarume;
	else if ( z_iComboMarume == MP_MRMCD6)
		iMCD = 6;
	else if ( z_iComboMarume == MP_MRMCD8)
		iMCD = 8;
	else
		ASSERT( 0);												// 丸めコードエラー　<ERROR>
		
	return iMCD;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの配置コードを設定し、コンボボックスに配置コードを表示する
//

void mnInpAttr::SelectComboPlcCdByPlcCd(
						MINT		iCdPlc		// (I  ) 配置コード
					)
{
	System::GetpMainFrame()->SelectComboInp3( iCdPlc);
//	((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( m_iComboInp3);
// 	System::GetpMainFrame()->((CComboBox*)(m_wndDlgBar1.GetDlgItem(IDC_CMB_Inp3)))->SetCurSel( iCdPlc);
	z_iComboPlcCd = iCdPlc;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの配置コードを取得する
//							＝0 : 任意
//							＝1 : 壁芯付き
//							＝2 : 屋根構成線付き

MINT mnInpAttr::GetComboPlcCd()
{
	return z_iComboPlcCd;
}

} // namespace MC