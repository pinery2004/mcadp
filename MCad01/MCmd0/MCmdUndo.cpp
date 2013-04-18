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

////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n
void MCmdUndo()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	HaitiCmd::MmUndo();

	WindowCtrl::MmWndKReDraw();

//	ist1 = z_mn.SetRibbonBar( MP_GP_YUKA, MP_BR_BUZAI, Mstr( "������"), Mstr( "210"));
//	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n
void MCmdRedo()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	HaitiCmd::MmRedo();

	WindowCtrl::MmWndKReDraw();

	MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n�ۑ��̈�̃N���A
void MCmdClearRedo()
{
	HaitiCmd::MdClearRedo();

	WindowCtrl::MmWndKReDraw();
}

} // namespace MC
