//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"

namespace MC
{

void MCmdLine( CWnd* pWnd);

/////////////////////////////////////////////////////////////////////////////
//	部材入力
void MCmdParts()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

//	MhInitInpAt();
//U1	MCmdLine( pWnd);
	MCmdLine( 0);
}

} // namespace MC
