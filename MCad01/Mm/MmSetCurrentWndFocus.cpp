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
//  �t�H�[�J�X���J�����g�E�B���h�E�ɐݒ肷��

	void Window::CurWndFocus( void)
{
	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E�擾
	pWndInfo->GetWnd()->SetFocus();
}

} // namespace MC