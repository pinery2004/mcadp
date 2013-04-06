//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmPartsEdit.cpp
//
//		部品展開
//
//
//  K.Matsu           07/14/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "resource.h"

#include "../gridctrl/gridctrl.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

#include "MmDialogPartsEdit.h"

namespace MC
{

static	CMmDialogPartsEdit* z_pDlgPartsEdit = NULL;	// モードレスバージョンダイアログの表示用

/////////////////////////////////////////////////////////////////////////////
//	部品展開

void MCmdPartsEdit()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEPARTSEDIT);
}

/////////////////////////////////////////////////////////////////////////////
//	部品展開設定入力
void MCmdPartsEditInp(
						CWnd*		pWnd			// (I  ) ウィンドウのインスタンス
				)
{
	if (z_pDlgPartsEdit == NULL) {
		z_pDlgPartsEdit = new CMmDialogPartsEdit( pWnd);
		z_pDlgPartsEdit->Create( pWnd);
	} else {
		z_pDlgPartsEdit->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	部品展開設定終了
void MCmdPartsEditEnd()
{
	z_pDlgPartsEdit = NULL;
}

} // namespace MC
