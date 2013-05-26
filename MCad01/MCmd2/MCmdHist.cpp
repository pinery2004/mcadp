//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmCmdHist.cpp
//
//		�C�������Ǘ��ݒ葀��
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "resource.h"
#include "MmDialogHist.h"
#include "MrCmd.h"
#include "MmWnd.h"
#include "MmCmdMsg.h"

namespace MC
{

static	CMmDialogHist* z_pDlgHist = NULL;	// ���[�h���X�o�[�W�����_�C�A���O�̕\���p

/////////////////////////////////////////////////////////////////////////////
//	�C�������Ǘ�

void MCmdHist()
{
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();			// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();
	
	pWnd->PostMessage(WM_MYMESSAGEHIST);						// OK: 1st
//	pWnd->SendMessage(WM_MYMESSAGEHIST);						// OK:
//	MCmdHistInp( NULL);											// NG: ���ɉB��Ă��܂�
}

/////////////////////////////////////////////////////////////////////////////
//	�C�������Ǘ��ݒ����
void MCmdHistInp(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if (z_pDlgHist == NULL)
	{
		// CDialog::Create( CMmDialogHist::IDD, NULL);�Ŏ��̃A�{�[�g�����̂�h������
		// AFX_MANAGE_STATE(AfxGetStaticModuleState());��ǉ�
		// �������A���̂������s���ł��邪�AView1��G��ƌ��ɉB��Ă��܂�
		// (dlgcore.cpp)
		//	if (!_AfxCheckDialogTemplate(lpszTemplateName, FALSE))
		//	{
		//		ASSERT(FALSE);          // invalid dialog template name

//		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		// ���̌�MCmd2.cpp���܂߂鎖�ɂ��Ok�ƂȂ���
		//

		z_pDlgHist = new CMmDialogHist;							// OK 
		z_pDlgHist->Create( pWnd);
//		z_pDlgHist = new CMmDialogHist( NULL);					// OK
//				MATRACE(CMmDialogHist);
	}
	else
	{
		z_pDlgHist->BringWindowToTop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�C�������Ǘ��ݒ�I��
void MCmdHistEnd()
{
	z_pDlgHist = NULL;
}

} // namespace MC
