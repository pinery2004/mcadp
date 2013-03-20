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
#include "MmDefine.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MsDefine.h"
#include "MmWnd.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	ダイアログバーの項目を設定する
//		組、分類、部品タイプ、寸法型式
//
MINT mtInpAttr::SetDialogBar(						// ステイタス 0:正常 -1:エラー
				MINT	iKumi,				// 組
				MINT	iBr,				// 分類
				MCHAR*	cTpPts,				// タイプ
				MCHAR*	cMbr				// 寸法型式 または NULL
				)
{
	MINT	ist;

	mtInpMode::SetKGp( iKumi);

	mtInpMode::SetKBr( iBr);

	mtInpAttr::InitComboTpPtsAttr();									// 組、分類に対応する部品を選択可能項目として設定する

	ist = mtInpAttr::SetComboCdTpPts( cTpPts);
	if ( ist < 0)
		MQUIT;

	mtInpAttr::InitComboPtsMbr();									// 部品に対応する寸法型式を選択可能項目として設定する

	if ( cMbr) {
        ist = mtInpAttr::SetComboCdMbr( cMbr);
		if ( ist < 0)
			MQUIT;
	mtInpAttr::InitComboAttr( MP_AT_AUTO);								// 属性入力用コンボボックスを初期化する

	}

	WindowCtrl::MmWndKReDraw();

	ist = 0;
exit:
	return ist;
}

} // namespace MC