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
//	���ޓ���
void MCmdParts()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

//	MhInitInpAt();
//U1	MCmdLine( pWnd);
	MCmdLine( 0);
}

} // namespace MC
