//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmTenkai.cpp
//
//		�Z���W�J
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "MmCmd.h"
#include "resource.h"

#include "MrCmd.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

#include "MmTenkai.h"
#include "MmDialogTenkai.h"

namespace MC
{

static	CMmDialogTenkai* z_pDlgTenkai = NULL;	// ���[�h���X�o�[�W�����_�C�A���O�̕\���p

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J

void MCmdTenkai()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGE_TENKAI);
}
/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�ݒ����
void MCmdTenkaiInp(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDlgTenkai == NULL) {
		z_pDlgTenkai = new CMmDialogTenkai( pWnd);
		z_pDlgTenkai->Create( pWnd);
	} else {
		z_pDlgTenkai->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�ݒ�I��
void MCmdTenkaiEnd()
{
	z_pDlgTenkai = NULL;
}

} // namespace MC
