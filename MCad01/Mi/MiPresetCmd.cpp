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
#include "MgMatD.h"
#define  DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "resource.h"

#include "MsBitSet.h"
#include "MdHist.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	�R�}���h���s�̎��O����
void HaitiCmd::MmPresetCmd()
{
	HaitiCmd::MdClearRedo();
}

} // namespace MC
