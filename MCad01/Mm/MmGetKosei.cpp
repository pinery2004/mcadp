//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmGetGp.cpp
//
//		�J�����g���̓��[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmWnd.h"

#define DLL_EXPORT_MC_INPATTR_DO
#define DLL_EXPORT_MC_INPMODE_DO
#include "MmLib.h"

#include "MsBitSet.h"
#include "MCAD.h"
#include "MhLib.h"

#include "MtInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

static MINT z_iInpMd;							// �n�����[�h		�폜�A�C���A�ړ��A���ʁA�����\��
static MINT z_InpKai;							// �K				�P�K�A�Q�K�A�R�K

static MINT z_iSInpGp;							// �݌v���͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�
static MINT z_iSInpBr;							// �݌v���͎��
static MINT z_iSInpSel;							// �݌v���͑I��

static MINT z_iKInpGp;							// �\�����͍\��		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b
static MINT z_iKInpBr;							// �\�����͎��		���ށA�����A�p�l���A���̑�
static MINT z_iKInpSel;							// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p

static MINT z_bKInpBuzai;						// ���ޑI����͋��t���O
static MINT z_bKInpKanagu;						// �����I����͋��t���O
static MINT z_bKInpPanel;						// �p�l���I����͋��t���O
static MINT z_bKInpOther;						// ���ޑI����͋��t���O

//	static MINT z_nPtsID;						// �z�u���i�^�C�v(���ށA�����A�p�l���A���̑��@�̕���ID)

////////////////////////////////////////////////////////////////////////////
//	���ޑ������͗p�R���{�{�b�N�X�̐ݒ�

void mtInpAttr::SetComboPts()
{
	//	���ޑI��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	mtInpAttr::InitComboTpPtsAttr();

	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	mtInpAttr::InitComboPtsMbr();

	//	�p�l���ԍ��I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	mtInpAttr::InitComboPanelNo();

	//	���i�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
	mtInpAttr::InitComboAttr();

	Window::CurWndFocus();
	WindowCtrl::MmWndKReDraw();
}

//	�n�����[�h		�폜�A�C���A�ړ��A���ʁA�����\��

void mtInpMode::SetMode( MINT iMode)
{
	z_iInpMd = iMode;
}

MINT mtInpMode::GetMode()
{
	return z_iInpMd;
}

//	�K				�P�K�A�Q�K�A�R�K

void mtInpMode::SetKai( MINT iKai)
{
	z_InpKai = iKai;
}

MINT mtInpMode::GetKai()
{
	return z_InpKai;
}

// �݌v���͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�

void mtInpMode::SetSGp( MINT iGp)
{
	z_iSInpGp = iGp;
}

MINT mtInpMode::GetSGp()
{
	return z_iSInpGp;
}

// �݌v���͎��

void mtInpMode::SetSBr( MINT iBr)
{
	z_iSInpBr = iBr;
}

MINT mtInpMode::GetSBr()
{
	return z_iSInpBr;
}

// �݌v���͑I��

void mtInpMode::SetSSel( MINT iSel)
{
	z_iSInpSel = iSel;
}

MINT mtInpMode::GetSSel()
{
	return z_iSInpSel;
}

// �\�����͍\��		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b

void mtInpMode::SetKGp( MINT iGp)
{
	z_iKInpGp = iGp;
}

MINT mtInpMode::GetKGp()
{
	return z_iKInpGp;
}

// �\�����͎��		���ށA�����A�p�l���A���̑�

void mtInpMode::SetKBr( MINT iBr)
{
	z_iKInpBr = iBr;
}

MINT mtInpMode::GetKBr()
{
	return z_iKInpBr;
}

// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p

void mtInpMode::SetKSel( MINT iSel)
{
	z_iKInpSel = iSel;
}

MINT mtInpMode::GetKSel()
{
	return z_iKInpSel;
}

//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���̑I����͋���ݒ�

void mtInpMode::SetKBrB( bool bBuzai, bool bKanagu, bool bPanel, bool bOther)
{
	z_bKInpBuzai  = bBuzai;
	z_bKInpKanagu = bKanagu;
	z_bKInpPanel  = bPanel;
	z_bKInpOther  = bOther;
}

} // namespace MC