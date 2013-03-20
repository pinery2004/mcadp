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
#include "MmDefine.h"

#define DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"

#include "MmLib.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MtInp.h"

#include "MdLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n
	void HaitiCmd::MmUndo()
{
	mhPlcInfo	UndoPlcEn;

	if ( HaitiDb::MdIsNotEmptyPts()) {
		HaitiDb::MdEjectPts( &UndoPlcEn);
		HaitiDb::MdPushRedoPts( &UndoPlcEn);
		if ( mtHaitiIn::ChkPts( NULL, MP_GP_TAIRYOKU, Mstr( "��"), NULL, &UndoPlcEn)) {
			IeModel::MhKabeSetUpFlg();
			IeModel::MhNormKabe( 0);
		}
	}
}

bool HaitiCmd::MmUndoIsNotEmpty()
{
	return HaitiDb::MdIsNotEmptyPts();
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n
void HaitiCmd::MmRedo()
{
	mhPlcInfo	RedoPlcEn;

	if ( HaitiDb::MdIsNotEmptyRedoPts()) {
		HaitiDb::MdPopRedoPts( &RedoPlcEn);
		HaitiDb::MdInjectPts( &RedoPlcEn);
		if ( mtHaitiIn::ChkPts( NULL, MP_GP_TAIRYOKU, Mstr( "��"), NULL, &RedoPlcEn)) {
			IeModel::MhKabeSetUpFlg();
			IeModel::MhNormKabe( 1);
		}
	}
}

bool HaitiCmd::MmRedoIsNotEmpty()
{
	return HaitiDb::MdIsNotEmptyRedoPts();
}

} // namespace MC