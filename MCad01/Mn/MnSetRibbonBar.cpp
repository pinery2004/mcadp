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
MINT mnIoPartsAttr::SetRibbonBar(					// ステイタス 0:正常 -1:エラー
						MPKOSEI		i_irbKumi,			// 構造	組
						MPBUNRUI	i_irbBunrui,		// 構造	分類
						MCHAR*		i_crbPartsSpec,		// 部品種類
						MCHAR*		i_crbMbr			// 部品メンバー()
				)
{
	MINT	ist;
	MPATTR	iAttr;

	z_mnIA.SetKCdGp( i_irbKumi);
	z_mnIA.SetKCdBr( i_irbBunrui);
	z_mnIA.InitComboPartsNm();									// 組、分類に対応する部品を選択可能項目として設定する
	ist = z_mnIA.SelectComboPartsNmByPartsNm( i_crbPartsSpec);
	if ( ist < 0)
		MQUIT;

	z_mnIA.InitComboPartsMbr();									// 部品に対応する寸法型式を選択可能項目として設定する
	if ( i_crbMbr) {
        ist = z_mnIA.SelectComboPartsMbrByMbrCd( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( i_irbKumi == MP_GP_YANE) {
			iAttr = MP_AT_YANE;
		} else {
			iAttr = MP_AT_AUTO;
		}
//S		z_mnIA.InitComboAttr( iAttr);							// 属性入力用コンボボックスを初期化する
		z_mmIA.InitComboAttr( iAttr);							// 属性入力用コンボボックスを初期化する
	}
	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC