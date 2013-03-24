//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: M_CadApi.cpp
//		
//	�@�\	�R�}���h�����p�o�b�N�O���E���h�̃^�X�N�̋N��
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

#include "MmLib.h"
#include "MdCmds.h"

//E #include "..\\MCAD\\res\\MCADrc2.h"

namespace MC
{

void MtCmdLine();

bool	MtIsMCadExiting( void);
bool	MtPostMtInpEvent( const MtInpEvent &theEvent );

MtInpEventQueueInterface *MtGetMtInpEventQueue();

#ifndef	MS_CMDMENU_STR_TYPE

	struct	MT_InternalCmdList *z_pInternalCmdList_WL;
	MINT	z_nInternalCmdList_WL;

	//	�R�}���h���X�g�̃|�C���^�ݒ�
	void MtSetCmdList( struct MT_InternalCmdList *pInternalCmdList, MINT nInternalCmdList)
	{
		z_pInternalCmdList_WL = pInternalCmdList;
		z_nInternalCmdList_WL = nInternalCmdList;
	}

	//	�R�}���hID(���j���[ID)���R�}���h�����擾����
	MCHAR* GetGlobalName( MINT nCmdIndex)
	{
		MINT	ic;
		for ( ic=0; ic<z_nInternalCmdList_WL; ic++) {
			if ( z_pInternalCmdList_WL[ic].cmdIndex == nCmdIndex) {
				return z_pInternalCmdList_WL[ic].globalName;
			}
		}
		return NULL;
	}
#endif
////////////////////////////////////////////////////////////////////////////
//	(Command_2) ���j���[���́@�܂��́@���W���̓C�x���g��҂�
//�@�C�x���g�����j���[�L���[�ƃR�}���h�L���[�ɕ�����ResBuf��ǉ�����
//	���j���[�L���[�ɓ��͂�����ꍇ�̓R�}���h�L���[���N���A��A
//	�R�}���h�L���[�ɃL�����Z���R�}���h�ƃ��j���[�R�}���h��ǉ�����
// 
MINT MtWaitLoop( void)
{
	struct MtPrcEvent NextItem;

	if ( MtIsMCadExiting())										// �V�X�e���I���@0
		return 0;

	MtInpEvent *pEvent = NULL;

	// �����̋N����h��
	static MbCriticalSection theSection;
	MbSynchroGuard theGuard( &theSection );

	int retcode = 0;

	if( ! MtGetMenuQueue()->IsEmpty()) {						// ���j���[�L���[�ɓ��͂�����ꍇ
//		const MCHAR* szMenuToken = MtGetMenuQueue()->PeekString();

		MtGetCommandQueue()->Flush();						// �R�}���h�L���[���N���A��A�R�}���h�L���[�̖�����

		NextItem.m_restype = MTRT_CAN;
		MtGetCommandQueue()->AddItem( &NextItem );			// �R�}���h�L���[�ɃL�����Z���R�}���h(MTRT_CAN)��ǉ����A

		MtGetMenuQueue()->PopItem( &NextItem);				// ���j���[�L���[�̐擪�R�}���h���擾��A���j���[�L�[�����菜��
		MtGetCommandQueue()->AddItem( &NextItem );			// �R�}���h�L���[�Ƀ��j���[�L���[�̐擪�R�}���h��ǉ�����

		retcode=1;  
		MQUIT;
	}
	if( !MtGetCommandQueue()->IsEmpty()) {						// �R�}���h�L���[�ɓ��͂�����ꍇ
		retcode=1;  
		MQUIT;
	}

	pEvent = MtGetMtInpEventQueue()->WaitEvent();				// ���̓C�x���g��҂�
	if ( pEvent != NULL ) {
		MtProcessEvent( pEvent);
		delete pEvent;
		retcode = 1;
	}
	retcode = 1;
exit:
	return( retcode);
}

////////////////////////////////////////////////////////////////////////////////////////
//	(Command_2.1) ���̓C�x���g�ɑΉ����āA�R�}���h�L���[�܂��̓��j���[�L���[�ɒǉ�����
void MtProcessEvent( MtInpEvent *event ) 
{
	MtPrcEvent tRb;
	MtPrcEventQueue	RbQue( 10);
	MINT	iForm;								// �`���@( 1:���W�A)	
	MINT	iChar;
	MINT	nChar;
	MINT	nRepCnt;
#ifndef	MS_CMDMENU_STR_TYPE
	MCHAR*	pcMenuStr;
#endif

	iForm = 1;
	switch( event->GetType() ) 									// ���̓C�x���g�ɂ��Ή����鏈�������s
	{

	case MT_EVM_KEYCHAR:
 		tRb.m_restype = MTRT_KEYCHAR;							// �}�E�X���{�^���_�E��
		iChar = event->GetKey();

		nChar = *(MINT*)(&event->m_pt.x);
		nRepCnt = *(MINT*)(&event->m_pt.y);

//		iChar = 'a';

		//switch ( event->GetKey() ) 
		//	{
		//	case '\r':
		//		tRb.m_restype = MTRT_MENUCOMMAND;								// �R�}���h�^�C�v�����W(MTRT_LBTNDWN)�Ƃ���
		//		tRb.m_resval.rstring = (MCHAR* )new char[sizeof( MCHAR)];
		//		tRb.m_resval.rstring[0] = NULL;
		//		MtGetCommandQueue()->Push( &tRb );
		//		break;
		//	} // end of switch ( event->GetKey() );
		iForm = 0;
        break;

 	case MT_EVM_LBUTTONDOWN:
 		tRb.m_restype = MTRT_LBTNDWN;							// �}�E�X���{�^���_�E��
		break;

	case MT_EVM_MBUTTONDOWN:
		tRb.m_restype = MTRT_MBTNDWN;							// �}�E�X���{�^���_�E��
		break;

	case MT_EVM_RBUTTONDOWN:
		tRb.m_restype = MTRT_RBTNDWN;							// �}�E�X���{�^���_�E��
		break;

	case MT_EVM_LBUTTONUP:
		tRb.m_restype = MTRT_LBTNUP;							// �}�E�X���{�^���A�b�v
		break;

	case MT_EVM_MBUTTONUP:
		tRb.m_restype = MTRT_MBTNUP;							// �}�E�X���{�^���A�b�v
		break;

	case MT_EVM_RBUTTONUP:
		tRb.m_restype = MTRT_RBTNUP;							// �}�E�X���{�^���A�b�v
		break;

	case MT_EVM_LBUTTONDBLCLK:
		tRb.m_restype = MTRT_LBTNDBL;							// �}�E�X���{�^���_�u���N���b�N
		break;

	case MT_EVM_MBUTTONDBLCLK:
		tRb.m_restype = MTRT_MBTNDBL;							// �}�E�X���{�^���_�u���N���b�N
		break;

	case MT_EVM_RBUTTONDBLCLK:
		tRb.m_restype = MTRT_RBTNDBL;							// �}�E�X���{�^���_�u���N���b�N
		break;

	case MT_EVM_MOUSEMOVE:
		tRb.m_restype = MTRT_MOUSEMOVE;							// �}�E�X�ړ�
		break;
	case MT_EVM_MOUSEWHEEL:
		tRb.m_restype = MTRT_MOUSEWHEEL;						// �}�E�X�z�C�[��
		break;

    case MT_EVM_MENUCOMMAND:									// ���̓C�x���g�����j���[���͂̏ꍇ
    case MT_EVM_POPUPCOMMAND:
////E		if( z_IgnoreMenuWQuote && event->m_sMenuStr[0] == '\'' ) 
////E			break;
//
//		//tRb.m_restype = MTRT_RBTNDWN;							// �R�}���h�^�C�v�����W(MTRT_RBTNDWN)�Ƃ���
//		//tRb.m_nflag = event->GetNFlag();						// nflag
//		//event->GetPoint( tRb.m_resval.rpoint);				// �R�}���h���͍��W����̓C�x���g���W�Ƃ���
//		//MtGetCommandQueue()->Push( &tRb);						// �R�}���h�L���[�ɒǉ�����

#ifdef	MS_CMDMENU_STR_TYPE
		MtMnuStrToRB( &RbQue, event->m_sMenuStr);				// ���j���[�L���[�ɒǉ�����
		MBFREE( event->m_sMenuStr); 
#else
		pcMenuStr = GetGlobalName( event->GetNFlag());			// ���j���[ID���R�}���h���擾
		MtMnuStrToRB( &RbQue, pcMenuStr);						// ���j���[�L���[�ɒǉ�����
#endif

		if( RbQue.GetCount() != 0) {
			MtGetMenuQueue()->AddQueue( &RbQue);
			RbQue.RemoveAll();
		}
		iForm = 0;
		break;

	case MT_EVM_SIZE:
		tRb.m_restype = MTRT_SIZE;								// �E�B���h�E�T�C�Y�ύX
		iForm = 0;
		break;
	case MT_EVM_SIZEMAX:
		tRb.m_restype = MTRT_SIZEMAX;							// �E�B���h�E�ő剻(��)
		iForm = 0;
		break;
	case MT_EVM_SIZEICON:
		tRb.m_restype = MTRT_SIZEICON;							// �E�B���h�E�A�C�R����			(��)
		iForm = 0;
		break;
	case MT_EVM_MOVE:
		tRb.m_restype = MTRT_MOVE;								// �E�B���h�E�ړ�
		iForm = 0;
		break;
	case MT_EVM_ACTIVATE:
		tRb.m_restype = MTRT_ACTIVE;							// �E�B���h�E�A�N�e�B�u
		iForm = 0;
		break;
	case MT_EVM_TIMER:
		tRb.m_restype = MTRT_TIMER;								// �^�C�}�[�C�x���g
		iForm = 0;
		break;
	case MT_EVM_DROPFILES:
		tRb.m_restype = MTRT_DROPFILE;							// �h���b�v�t�@�C���C�x���g
		iForm = 0;
		break;
	default:
		iForm = 0;
		break;	
	}
//
	switch ( iForm)
	{
	case 1:
		tRb.m_nflag = event->GetNFlag();						// nflag
		event->GetPoint( tRb.m_resval.rpoint);					// �R�}���h���͍��W����̓C�x���g���W�Ƃ���
		MtGetCommandQueue()->Push( &tRb);						// �R�}���h�L���[�ɒǉ�����
		break;
	}
}

// �w�肵���R�}���h���̃��j���[�R�}���h�����j���[�L���[�ɓo�^�^�ŕԂ�
void MtMnuStrToRB(
						MtPrcEventQueue* i_pRbQue,	// ���j���[�R�}���h�L���[
						MCHAR*			 i_sMnuStr	// �R�}���h
				)
{
	MINT iSt;
	if ( i_sMnuStr != NULL && i_sMnuStr[0] != 0) {

#ifdef MS_CMDMENU_STR_TYPE
		MtInpEvent theMtInpEvent( MT_EVM_KEYCHAR, 0, i_sMnuStr);
		MtProcessEvent( &theMtInpEvent);
#endif
 
		iSt = MtBuildPrcEvent( i_pRbQue, MTRT_MENUCOMMAND, i_sMnuStr, 0);
		if ( iSt == NULL) {
			ASSERT( iSt);
			MdCmdErrorPrompt( CMD_ERR_UNABLE, 0);					// The user shouldn't need to care what went wrong internally.  OK?
		}
	}
}

} // namespace MC