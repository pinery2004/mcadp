//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MtInpEventFilter.cpp
//
//	�@�\	�C�x���g�t�B���^
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MtInpEvent.h"
#include "MtInpEventFilter.h"

namespace MC
{

bool
MtInpEventFilter::Match( MtInpEvent *pEvent)
{
	bool bRetval = false;
	if ( ( pEvent->GetType() & m_iFilterFlags) != 0)
		{
		bRetval = true;
		}

	return bRetval;
}

} // namespace MC