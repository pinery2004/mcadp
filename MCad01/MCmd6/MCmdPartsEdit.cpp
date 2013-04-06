//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmPartsEdit.cpp
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

#include "MmDialogPartsEdit.h"

namespace MC
{

static	CMmDialogPartsEdit* z_pDlgPartsEdit = NULL;	// ���[�h���X�o�[�W�����_�C�A���O�̕\���p

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J

void MCmdPartsEdit()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEPARTSEDIT);
}

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J�ݒ����
void MCmdPartsEditInp(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDlgPartsEdit == NULL) {
		z_pDlgPartsEdit = new CMmDialogPartsEdit( pWnd);
		z_pDlgPartsEdit->Create( pWnd);
	} else {
		z_pDlgPartsEdit->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���i�W�J�ݒ�I��
void MCmdPartsEditEnd()
{
	z_pDlgPartsEdit = NULL;
}

} // namespace MC
