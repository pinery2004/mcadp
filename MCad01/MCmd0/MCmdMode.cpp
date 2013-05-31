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
//	�n�����[�h

void MCmdMdCreate()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	z_mnIA.SetMode( MP_MD_CREATE);

	MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�폜���[�h

void MCmdMdDelete()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	z_mnIA.SetMode( MP_MD_DELETE);

	MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�C�����[�h

void MCmdMdModify()
{
	z_mnIA.SetMode( MP_MD_MODIFY);
}

/////////////////////////////////////////////////////////////////////////////
//	�ړ����[�h

void MCmdMdMove()
{
	z_mnIA.SetMode( MP_MD_MOVE);
}

/////////////////////////////////////////////////////////////////////////////
//	���ʃ��[�h

void MCmdMdCopy()
{
	z_mnIA.SetMode( MP_MD_COPY);
}

/////////////////////////////////////////////////////////////////////////////
//	�����\�����[�h

void MCmdMdProperty()
{
	z_mnIA.SetMode( MP_MD_PROPERTY);
}
/*
/////////////////////////////////////////////////////////////////////////////
//	�P�_�L�����Z��

void MCmdCancel1Pt()
{
}

/////////////////////////////////////////////////////////////////////////////
//	�S�_�L�����Z��

void MCmdCancelAll()
{
}

/////////////////////////////////////////////////////////////////////////////
//	�K����

void MCmdInpKai()
{
}

/////////////////////////////////////////////////////////////////////////////
//	�S�K����

void MCmdInpAll()
{
}

/////////////////////////////////////////////////////////////////////////////
//	���͏I��

void MCmdInpEnd()
{
}

/////////////////////////////////////////////////////////////////////////////
//	���������	

void MCmdBaseHeight()
{
}
*/
/*
/////////////////////////////////////////////////////////////////////////////
//	���i�\����

void MCmdPartsEdit()
{
	MmWndInfo*	pWndInfo = WndKGetCurWnd();								// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGE_PARTSEDIT);
}
*/

} // namespace MC
