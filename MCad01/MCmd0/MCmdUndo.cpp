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

void MCmdLine();

////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n
void MCmdUndo()
{

	HaitiCmd::MmUndo();

	WindowCtrl::MmWndKReDraw();

//	ist1 = mtInpAttr::SetDialogBar( MP_GP_YUKA, MP_BR_BUZAI, Mstr( "������"), Mstr( "210"));
//	if ( ist1 == 0)
		MCmdLine();
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n
void MCmdRedo()
{
	HaitiCmd::MmRedo();

	WindowCtrl::MmWndKReDraw();

	MCmdLine();
}

/////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n�ۑ��̈�̃N���A
void MCmdClearRedo()
{
	HaitiCmd::MdClearRedo();

	WindowCtrl::MmWndKReDraw();
}

} // namespace MC