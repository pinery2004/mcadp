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
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#define DLL_EXPORT_MC_WINDOW_DO
#include "MmLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//  フォーカスをカレントウィンドウに設定する

	void Window::CurWndFocus( void)
{
	MmWndInfo* pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウ取得
	pWndInfo->GetWnd()->SetFocus();
}

} // namespace MC
