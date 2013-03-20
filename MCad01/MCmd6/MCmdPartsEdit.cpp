//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmPtsEdit.cpp
//
//		���i�W�J
//
//
//  K.Matsu           07/14/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "resource.h"

#include "../gridctrl/gridctrl.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

#include "MmDialogPtsEdit.h"

namespace MC
{

static	CMmDialogPtsEdit* z_pDlgPtsEdit = NULL;	// ���[�h���X�o�[�W�����_�C�A���O�̕\���p

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J

void MCmdPtsEdit()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEPARTSEDIT);
}

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J�ݒ����
void MCmdPtsEditInp(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDlgPtsEdit == NULL) {
		z_pDlgPtsEdit = new CMmDialogPtsEdit( pWnd);
		z_pDlgPtsEdit->Create( pWnd);
	} else {
		z_pDlgPtsEdit->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J�ݒ�I��
void MCmdPtsEditEnd()
{
	z_pDlgPtsEdit = NULL;
}

} // namespace MC