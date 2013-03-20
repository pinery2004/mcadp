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
#include "MCAD.h"
#include "MmCmd.h"
#include "resource.h"

#include "MrCmd.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

#include "MmDialogGrid.h"

namespace MC
{

static CMmDialogGrid*	z_pDlgGrid = NULL;						// �O���b�h�_�C�A���O

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX����

void MCmdGridNum()
{
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();				// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEGRIDNUM);

//	MCmdOptInp( NULL);
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX����
void MCmdGridNumInp		(
						CWnd*		pWnd						// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDlgGrid == NULL) {
		z_pDlgGrid = new CMmDialogGrid( pWnd);
		z_pDlgGrid->Create( pWnd);
	} else {
		z_pDlgGrid->BringWindowToTop();
	}


}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX�I��
void MCmdGridNumEnd()
{
	z_pDlgGrid = NULL;
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h���ύX�L�����Z��
void MmGridNumCancel()
{
	if (z_pDlgGrid)
//		z_pDlgGrid->SendMessage(WM_CLOSE);
		z_pDlgGrid->PostMessage(WM_CLOSE);
}

} // namespace MC