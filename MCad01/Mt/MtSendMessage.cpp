//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: M_CadApi.cpp
//
//		
//	�R�}���h�����p�o�b�N�O���E���h�̃^�X�N�̋N��
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsDefine.h"

#include "MsMCAD.h"
#include "MtAskForPoint.h"
#include "MsCriticalSection.h" 

#include "MtInpEvent.h"
#include "MtInpEventQueue.h"
#include "MtPrcEventQueue.h"

#include "MgPoint.h"

#include "MmLib.h"

namespace MC
{

void MtCmdLine();

//bool	MtIsMCadExiting( void);
bool	MtPostMtInpEvent( const MtInpEvent &theEvent );

static UINT	z_CurEventMask = 0;

#ifdef	MS_CMDMENU_STR_TYPE
struct MT_InternalCmdList *z_pInternalCmdList;
static MINT	z_nInternalCmdList;

////////////////////////////////////////////////////////////////
//	�R�}���h���X�g�̃|�C���^�ݒ�
void MtSetCmdList( struct MT_InternalCmdList *pInternalCmdList, MINT nInternalCmdList)
{
	z_pInternalCmdList = pInternalCmdList;
	z_nInternalCmdList = nInternalCmdList;
}

////////////////////////////////////////////////////////////////
//	�R�}���hID(���j���[ID)���R�}���h�����擾����
MCHAR* GetGlobalName( MINT nCmdIndex)
{
	MINT	ic;
	for ( ic=0; ic<z_nInternalCmdList; ic++) {
		if ( z_pInternalCmdList[ic].cmdIndex == nCmdIndex) {
			return z_pInternalCmdList[ic].globalName;
		}
	}
	return NULL;
}
#endif

///////////////////////////////////////////////////////////////////////////////
//	(Command_1) ���͑��삩��̏����Ώۃ��b�Z�[�W���C�x���g�L���[�ɒǉ�����
MINT MtSendMessage(
				MINT		message,							// ���b�Z�[�W
				MINT		nFlags,								// ��ރt���O
				MgPoint2D	*pPtMR								// �}�E�X�����W �܂��� NULL
				)
{
	MgPoint2D*	pPtR;
	MgPoint2D	PtZ = MgPoint2D( 0., 0.);
//	MgVect2D	PtZ = MgVect2D( 0., 0.);

#ifdef	MS_CMDMENU_STR_TYPE
	MCHAR* pcMenuStr;
#endif

	if ( pPtMR == 0)
		pPtR = &PtZ;
	else 
		pPtR = pPtMR;

	int hadevent = 1;
	MtInpEvent event( 0, nFlags, *pPtR);

	switch ( message)
	{
	case WM_CHAR:
		event.m_type = MT_EVM_KEYCHAR;
		break;
	case WM_LBUTTONDOWN:										// �}�E�X���{�^���_�E��
		event.m_type = MT_EVM_LBUTTONDOWN;
		break;
	case WM_MBUTTONDOWN:										// �}�E�X���{�^���_�E��
		event.m_type = MT_EVM_MBUTTONDOWN;
		break;
	case WM_RBUTTONDOWN:										// �}�E�X�E�{�^���_�E��
		event.m_type = MT_EVM_RBUTTONDOWN;
		break;

	case WM_LBUTTONUP:											// �}�E�X���{�^���A�b�v
		event.m_type = MT_EVM_LBUTTONUP;
		break;
	case WM_MBUTTONUP:											// �}�E�X���{�^���A�b�v
		event.m_type = MT_EVM_MBUTTONUP;
		break;
	case WM_RBUTTONUP:											// �}�E�X�E�{�^���A�b�v
		event.m_type = MT_EVM_RBUTTONUP;
		break;

	case WM_LBUTTONDBLCLK:										// �}�E�X���{�^���_�u���N���b�N
		event.m_type = MT_EVM_LBUTTONDBLCLK;
		break;
	case WM_MBUTTONDBLCLK:										// �}�E�X���{�^���_�u���N���b�N
		event.m_type = MT_EVM_MBUTTONDBLCLK;
		break;
	case WM_RBUTTONDBLCLK:										// �}�E�X�E�{�^���_�u���N���b�N
		event.m_type = MT_EVM_RBUTTONDBLCLK;
		break;

	case WM_MOUSEMOVE:											// �}�E�X�ړ�
		event.m_type = MT_EVM_MOUSEMOVE;
		break;
	case WM_MOUSEWHEEL:											// �}�E�X�z�C�[����]
		event.m_type = MT_EVM_MOUSEWHEEL;
		break;

	//case WM_POPUPCOMMAND:										// �|�b�v�A�b�v���j���[�R�}���h�I��
	//	event.m_type = MT_EVM_POPUPCOMMAND;
	//	break;

	//case WM_AUXMENU:											// 
	//	event.m_type = MT_EVM_AUXMENU;
	//	break;

	case WM_SIZE:												// �E�B���h�E�T�C�Y�ύX
		event.m_type = MT_EVM_SIZE;
		break;
	case WM_MOVE:												// �E�B���h�E�ړ�
		event.m_type = MT_EVM_MOVE;
		break;
	case WM_ACTIVATE:											// �E�B���h�E�A�N�e�B�u
		event.m_type = MT_EVM_ACTIVATE;
		break;
	case WM_TIMER:												// �^�C�}�[
		event.m_type = MT_EVM_TIMER;
		break;
	case WM_DROPFILES:											// �h���b�v�t�@�C��
		event.m_type = MT_EVM_DROPFILES;
		break;

	case WM_APP_SYSTEMSTOP:
		// �V�X�e���I��
		event.m_type = MT_EVM_SYSTEMSTOP;					// �V�X�e���X�g�b�v(�_�~�[���b�Z�[�W)
		break;

	case WM_CMDMENUP:											// ���j���[�R�}���h�I��
		event.m_type = MT_EVM_MENUCOMMAND;
#ifdef	MS_CMDMENU_STR_TYPE
		pcMenuStr	= GetGlobalName( nFlags);					// ���j���[ID���R�}���h���擾
		if ( pcMenuStr) {
			event.m_sMenuStr = (MCHAR* )new char[(Mstrlen( pcMenuStr) + 1)*sizeof( MCHAR)];
			Mstrcpy( event.m_sMenuStr, pcMenuStr);
		} else {
			hadevent = 0;
		}
#endif
		break;

	default:
		hadevent = 0;
	}

	if ( hadevent) {												// ���̓C�x���g�L���[�ɃC�x���g��ǉ�	
		if ( z_CurEventMask == 0 || ( z_CurEventMask & event.m_type)) {
			MtPostMtInpEvent( event );								// **?? �����Ŏ~�߂�ƃL���[�����܂肷����̂����[�v�̂悤�ȏ󋵂ɂȂ�
		}
	}
	return(0);
}

MtInpEventQueueInterface *MtGetMtInpEventQueue();
//
// ���̓C�x���g�L���[�ɃC�x���g��ǉ�	
bool MtPostMtInpEvent( const MtInpEvent &theEvent)
{
	MtInpEvent *pevent = new MtInpEvent( theEvent);

	return  MtGetMtInpEventQueue()->PostEvent( pevent );
}

} // namespace MC