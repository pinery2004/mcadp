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
#include "MgMatA.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#define DLL_EXPORT_MC_WINDOWCTRL_DO
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"

#include "resource.h"

#include "MdList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//  �J�����g�̃E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j
//	06/03/11�@�ĕ\����ɕ��ޒ��������R�}���h�ŏC����̈ʒu����͎��ɓ��ꕔ�ޏ�̓_��
//			�@�w���������A���I�����Ă������ނ̐}�`�������\�����ꖳ���悤�ɑ҂悤�ɏC���������ς�炸���ɖ߂�

MINT WindowCtrl::MmWndKReDraw() 
{
	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();		// �J�����g�̃E�B���h�E�Ǘ����擾
	pWndInfo->ClearMDC();
	WindowCtrl::MmWndKDrawMDC( pWndInfo);

//	pWndInfo->GetWnd()->PostMessage(WM_PAINT);					// �ĕ\���̃��b�Z�[�W�𑗂菈���̏I����҂����Ɏ��ֈڂ�
	pWndInfo->GetWnd()->SendMessage(WM_PAINT);					// �ĕ\���̃��b�Z�[�W�𑗂菈���̏I����҂��Ď��ֈڂ� 060506 �����I����V�X�e���I������Ńn���O�A�b�v

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  �S�E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j

MINT WindowCtrl::MmWndKReDrawAll() 
{
	MPOSITION			WndPos;
	MmWndInfo*			pWndInfo;

	for (pWndInfo=MmGetHeadWnd( &WndPos); pWndInfo!=0; pWndInfo=MmGetNextWnd( &WndPos)) {
		pWndInfo->ClearMDC();
		if ( pWndInfo->GetWndSyu() == 5) {
																// �O���b�h�\������荞��
			MmWndInfo* pWndInfo1 = WindowCtrl::MmWndKFindSyu( 1, MTHEIMENZU, 1, 1);
//			MmWndInfo* pWndInfo5 = WindowCtrl::MmWndKFind( this);
			MINT nGrid[4];
			pWndInfo1->GetGridNum( nGrid);
			pWndInfo->SetGridNum( nGrid);
			pWndInfo->SetMinMaxRS( pWndInfo->GetMinMaxGA( pWndInfo));	//	�����W(Min/Max)
			pWndInfo->SetMat();									// ���W�ϊ��p�}�g���b�N�X�̐ݒ�		//ZZ? �Ȃ������́@�ǉ� 070901
		}
		WindowCtrl::MmWndKDrawMDC( pWndInfo);
		pWndInfo->GetWnd()->PostMessage(WM_PAINT);				// �ĕ\���̃��b�Z�[�W�𑗂菈���̏I����҂����Ɏ��ֈڂ�
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E��\������i�������[�c�b�̓��e����ʂɕ\������j

MINT WindowCtrl::MmWndKDraw( 
						MmWndInfo*	i_pWndInfo	// �E�B���h�E�Ǘ����
				) 
{
	MINT			ist = 1;
	CDC*			pMemDC;						// ������sg�c�b
	MINT			iStX;						// �E�B���h�E�̎n�_�w���W
	MINT			iStY;						// �E�B���h�E�̎n�_�x���W
	MINT			iWidth;						// �E�B���h�E�̕�
	MINT			iHeight;					// �E�B���h�E�̍���
//	MINT			ItrSts;
//HHHH
//	ItrSts = HmClrCursorRubber(ViewId);							// ϰ�����ް����ނ�ر

	if ( i_pWndInfo != 0) {
		CClientDC		dc( i_pWndInfo->GetWnd());
		MINT iMapMode = i_pWndInfo->GetMapMode();
		MINT iOldMM = dc.SetMapMode( iMapMode);

		i_pWndInfo->GetWinL( &iStX, &iStY, &iWidth, &iHeight);
		pMemDC = i_pWndInfo->GetMemDC();

		dc.BitBlt( iStX, iStY, iWidth, iHeight, pMemDC, 0, 0,SRCCOPY);

		dc.SetMapMode( iOldMM);
		ist = 0;
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E�C���[�W�������c�b�ɑg�}��\��

void WindowCtrl::MmWndKDrawMDC(								// �X�e�C�^�X�@0:����  1:�G���[
						MmWndInfo*	i_pWndInfo	// �E�B���h�E�Ǘ����
				)
{
	i_pWndInfo->AsignMDC();										// �������c�b�����蓖�ĂĂȂ���Ί��蓖�Ă�
	i_pWndInfo->ClearMDC();										// ��ʂ�w�i�F�œh��Ԃ��N���A

	msCod*	pCod = i_pWndInfo;

	//	�}�b�v���[�h��ݒ�
	MINT iOldMM = i_pWndInfo->SetMapMode( NULL);

	//	�������[�c�b�ɕ\��
	WindowCtrl::MmWndKDrawGrid( i_pWndInfo, pCod);
	MINT iKaiC = z_mnIA.GetInpKai();							// ���݂̊K
	MINT iGpC = z_mnIA.GetKCdGp();								// ���݂̍\��
	WindowCtrl::MmWndKDrawKabe( pCod, iKaiC, iGpC);
	WindowCtrl::MmWndKDrawKiso( pCod, iKaiC, iGpC);
	WindowCtrl::MmWndKDrawParts( pCod, iKaiC, iGpC);
	WindowCtrl::MmWndKDrawRoof( pCod, iKaiC, iGpC);
	WindowCtrl::MmWndKDrawTemp( i_pWndInfo, pCod);

	//	�}�b�v���[�h��߂�
	i_pWndInfo->m_pMemDC->SetMapMode( iOldMM);
}

/////////////////////////////////////////////////////////////////////////////
//	�O���b�h��\������
void WindowCtrl::MmWndKDrawGrid(
						MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����
						msCod*		pCod
				)
{
	i_pWndInfo->DrawGrid( i_pWndInfo, pCod);
}

} // namespace MC
