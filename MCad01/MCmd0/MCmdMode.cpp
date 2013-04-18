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
#include "MmCmdMsg.h"

namespace MC
{

void MCmdLine( CWnd* pWnd);

/////////////////////////////////////////////////////////////////////////////
//	創成モード

void MCmdMdCreate()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	z_mn.SetMode( MP_MD_CREATE);

	MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	削除モード

void MCmdMdDelete()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	z_mn.SetMode( MP_MD_DELETE);

	MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	修正モード

void MCmdMdModify()
{
	z_mn.SetMode( MP_MD_MODIFY);
}

/////////////////////////////////////////////////////////////////////////////
//	移動モード

void MCmdMdMove()
{
	z_mn.SetMode( MP_MD_MOVE);
}

/////////////////////////////////////////////////////////////////////////////
//	複写モード

void MCmdMdCopy()
{
	z_mn.SetMode( MP_MD_COPY);
}

/////////////////////////////////////////////////////////////////////////////
//	属性表示モード

void MCmdMdProperty()
{
	z_mn.SetMode( MP_MD_PROPERTY);
}
/*
/////////////////////////////////////////////////////////////////////////////
//	１点キャンセル

void MCmdCancel1Pt()
{
}

/////////////////////////////////////////////////////////////////////////////
//	全点キャンセル

void MCmdCancelAll()
{
}

/////////////////////////////////////////////////////////////////////////////
//	階入力

void MCmdInpKai()
{
}

/////////////////////////////////////////////////////////////////////////////
//	全階入力

void MCmdInpAll()
{
}

/////////////////////////////////////////////////////////////////////////////
//	入力終了

void MCmdInpEnd()
{
}

/////////////////////////////////////////////////////////////////////////////
//	基準高さ入力	

void MCmdBaseHeight()
{
}
*/
/*
/////////////////////////////////////////////////////////////////////////////
//	部品表入力

void MCmdPartsEdit()
{
	MmWndInfo*	pWndInfo = MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEPARTSEDIT);
}
*/

} // namespace MC
