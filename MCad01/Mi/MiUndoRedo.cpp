//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MhDefParts.h"

#define DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"

#include "MmLib.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MhInp.h"
#include "MhInpAttr.h"

#include "MdLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n
	void HaitiCmd::MmUndo()
{
	mhPlcInfo	UndoPlcEn;

	if ( HaitiDb::MdIsNotEmptyParts()) {
		HaitiDb::MdEjectParts( &UndoPlcEn);
		HaitiDb::MdPushRedoParts( &UndoPlcEn);
		if ( mhHaitiIn::ChkParts( NULL, MP_GP_TAIRYOKU, Mstr( "��"), NULL, &UndoPlcEn)) {
			IeModel::MhKabeSetUpFlg();
			IeModel::MhNormKabe( 0);
		}
	}
}

bool HaitiCmd::MmUndoIsNotEmpty()
{
	return HaitiDb::MdIsNotEmptyParts();
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n
void HaitiCmd::MmRedo()
{
	mhPlcInfo	RedoPlcEn;

	if ( HaitiDb::MdIsNotEmptyRedoParts()) {
		HaitiDb::MdPopRedoParts( &RedoPlcEn);
		HaitiDb::MdInjectParts( &RedoPlcEn);
		if ( mhHaitiIn::ChkParts( NULL, MP_GP_TAIRYOKU, Mstr( "��"), NULL, &RedoPlcEn)) {
			IeModel::MhKabeSetUpFlg();
			IeModel::MhNormKabe( 1);
		}
	}
}

bool HaitiCmd::MmRedoIsNotEmpty()
{
	return HaitiDb::MdIsNotEmptyRedoParts();
}

} // namespace MC
