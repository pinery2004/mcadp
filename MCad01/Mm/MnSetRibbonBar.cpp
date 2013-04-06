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
//	リボンバーの項目を設定する
//		組、分類、部品タイプ、寸法型式
//
MINT mnInpAttr::SetRibbonBar(					// ステイタス 0:正常 -1:エラー
//S				MINT	iKumi,					// 組
//				MINT	iBr,					// 分類
//				MCHAR*	cPartsTp,					// タイプ
//				MCHAR*	cMbr					// 寸法型式 または NULL
						MPKOSEI		i_irbKumi,			// 構造	組
						MPBUNRUI	i_irbBunrui,		// 構造	分類
						MCHAR*		i_crbPartsTp,		// 部品種類
						MCHAR*		i_crbMbr			// 部品メンバー()
				)
{
	MINT	ist;
	MPATTR	iAttr;

	z_mn.SetKCdGp( i_irbKumi);
	z_mn.SetKCdBr( i_irbBunrui);
	z_mn.InitComboPartsTp();									// 組、分類に対応する部品を選択可能項目として設定する
	ist = z_mn.SetComboCdPartsTp( i_crbPartsTp);
	if ( ist < 0)
		MQUIT;

	z_mn.InitComboPartsMbr();										// 部品に対応する寸法型式を選択可能項目として設定する
	if ( i_crbMbr) {
        ist = z_mn.SetComboCdMbr( i_crbMbr);
		if ( ist < 0)
			MQUIT;
		if ( i_irbKumi == MP_GP_YANE) {
			iAttr = MP_AT_YANE;
		} else {
			iAttr = MP_AT_AUTO;
		}
		z_mn.InitComboAttr( iAttr);								// 属性入力用コンボボックスを初期化する
	}
	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC