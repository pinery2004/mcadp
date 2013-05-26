//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdOpt.cpp
//
//		�I�v�V�����ݒ葀��
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "resource.h"
#include "MmDialogOpt.h"
#include "MrCmd.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

namespace MC
{

static	CMmDialogOpt* z_pDialogOpt = NULL;		// ���[�h���X�n�o�s�Q�_�C�A���O�̕\���p

/////////////////////////////////////////////////////////////////////////////
//	�n�o�s�Q����

void MCmdOpt()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEOPTION);

//	MCmdOptInp( NULL);
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�I�v�V�����ݒ�_�C�A���O�\���@����
void MCmdOptInp(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDialogOpt == NULL)
	{
		z_pDialogOpt = new CMmDialogOpt;
		z_pDialogOpt->Create( pWnd);
	}
	else
	{
		z_pDialogOpt->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�I�v�V�����ݒ�_�C�A���O�\���@�I��
void MCmdOptEnd()
{
	z_pDialogOpt = NULL;
}

} // namespace MC
