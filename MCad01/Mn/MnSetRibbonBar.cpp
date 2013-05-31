//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		ドラッギング操作
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MhDefParts.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MsDefine.h"
#include "MmWnd.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	リボンバーの部品選択用項目を設定する
//		組、分類、部品タイプ、寸法型式
//
MINT mnIoPartsAttr::SetRibbonBarXqt(						// ステイタス 0:正常 -1:エラー
						MPKOSEI		i_irbKumi,			// 構造組
						MPBUNRUI	i_irbBunrui,		// 構造分類
						MCHAR*		i_crbPartsSpec,		// 部品種類		(部品名)
						MCHAR*		i_crbMbr			// 部品メンバー	(寸法型式)
				)
{
	MINT	ist;
	MPATTR	iAttr;

	// 組を選択する
	z_mnIA.SetKCdGp( i_irbKumi);

	// 分類を選択する
	z_mnIA.SetKCdBr( i_irbBunrui);

	// 部品種類(部品名)のダイアログの項目を設定し部品名を選択する
	// 組、分類に対応する部品名を選択可能項目として設定する
	z_mnIA.InitComboPartsNm();
	ist = z_mnIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
	if ( ist < 0)
		MQUIT;
	if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {
		z_mmIA.MmDialogKAttrDisp( z_MCadApp.m_pMainFrame);
		z_mmIA.InitComboPartsNm();
		ist = z_mmIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
		if ( ist < 0)
			MQUIT;
	}

	// 部品名に対応するメンバー(寸法型式)を選択可能項目として設定する
	z_mnIA.InitComboPartsMbr();									// リボンバーの部品名選択用コンボボックス
	if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {
		z_mmIA.InitComboPartsMbr();								// ダイアログの部品名選択用コンボボックス
	}
	if ( i_crbMbr >= 0) {

		// リボンバーのメンバー選択用コンボボックスのメンバーを選択する
        ist = z_mnIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( z_mnIA.GetCCategory() == MP_SENTAKU_KOUZOU) {

			// ダイアログのメンバー選択用コンボボックスのメンバーを選択する
			ist = z_mmIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
			if ( ist < 0)
				MQUIT;

			// ダイアログの属性入力用コンボボックスを初期化する
			if ( i_irbKumi == MP_GP_YANE) {
				iAttr = MP_AT_YANE;
			} else {
				iAttr = MP_AT_AUTO;
			}
			z_mmIA.InitComboAttrXqt( iAttr);
		}
	}
	WindowCtrl::ReDrawWnd();

	ist = 0;
exit:
	return ist;
}

} // namespace MC