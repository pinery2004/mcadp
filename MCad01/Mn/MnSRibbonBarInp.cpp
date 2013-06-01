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

//S static MINT		z_iComboInpKbnCd;
//static MINT		z_iComboMarume;
//static MINT		z_iComboPlcIzonCd;

// CMnRibbonBarInp ダイアログ


// CMnRibbonBarInp メッセージ ハンドラ

///////////////////////////////////////////////////////////////////////////////
//	リボンバーの入力点区分コード選択用コンボボックスの入力点区分コードを選択する	(本体)
//
void mnIoPartsAttr::SelectComboInpKbnByInpKbnCdXqt(
						MINT		iCdInpKbn		// (I  ) 入力点区分
				)
{
	System::GetpMainFrame()->SelectComboInp1( iCdInpKbn);
//S1	z_iComboInpKbnCd = iCdInpKbn;									//	カレントの入力点区分コード
	m_IA.m_IK[1].m_iComboInpKbn = iCdInpKbn;							//	カレントの入力点区分コード
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの入力点区分を取得する
//							＝1 : １点入力
//							＝2 : 方向１点入力
//							＝3 : 長さ２点入力
//							＝4 : 区画入力
//							＝5 : 自由入力
//
MINT mnIoPartsAttr::GetComboInpKbnCd()
{
//S1	return z_iComboInpKbnCd;
	return m_IA.m_IK[1].m_iComboInpKbn;
}

///////////////////////////////////////////////////////////////////////////////
//	リボンバーの丸めコード選択用コンボボックスの丸めコードを選択する	(本体)
//

void mnIoPartsAttr::SelectComboMarumeByMarumeCdXqt(
						MINT		i_iMarumeCd	// (I  ) 丸めコード
					)
{
	int		iComboMarume;

	if ( i_iMarumeCd >= MP_MRMCDN && i_iMarumeCd <= MP_MRMCD4)
		iComboMarume = i_iMarumeCd;
	else if ( i_iMarumeCd == 6)
		iComboMarume = MP_MRMCD6;
	else if ( i_iMarumeCd == 6)
		iComboMarume = MP_MRMCD6;
	else
		ASSERT( 0);												// 丸めコードエラー　<ERROR>
	
	System::GetpMainFrame()->SelectComboInp2( iComboMarume);
//S1	z_iComboMarume = iCdMarume;									// カレントの丸めコード
	m_IA.m_IK[1].m_iComboMarume = iComboMarume;					// カレントの丸めコード
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

MINT mnIoPartsAttr::GetComboMarumeCd()
{
	int		iComboMarume;
	int		iMCD;

	iComboMarume = m_IA.m_IK[1].m_iComboMarume;


	if ( iComboMarume >= MP_MRMCDN && iComboMarume <= MP_MRMCD4) 
		iMCD = iComboMarume;
	else if ( iComboMarume == MP_MRMCD6)
		iMCD = 6;
	else if ( iComboMarume == MP_MRMCD8)
		iMCD = 8;
	else
		ASSERT( 0);												// 丸めコードエラー　<ERROR>
		
	return iMCD;
}

///////////////////////////////////////////////////////////////////////////////
//	リボンバーの配置依存コード選択用コンボボックスの配置依存コードを選択する
//

void mnIoPartsAttr::SelectComboPlcIzonCdByPlaceCdXqt(
						MINT		i_iComboInpKbn	// (I  ) 配置依存コード
					)
{
	System::GetpMainFrame()->SelectComboInp3( i_iComboInpKbn);
//S1	z_iComboPlcIzonCd = iCdPlc;									//	カレントの配置依存コード
	m_IA.m_IK[1].m_iComboPlcIzon = i_iComboInpKbn;					//	カレントの配置依存コード
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの配置依存コードを取得する
//							＝0 : 任意
//							＝1 : 壁芯付き
//							＝2 : 屋根構成線付き

MINT mnIoPartsAttr::GetComboPlcIzonCd()
{
//S1	return z_iComboPlcIzonCd;
	return m_IA.m_IK[1].m_iComboPlcIzon;
}

} // namespace MC