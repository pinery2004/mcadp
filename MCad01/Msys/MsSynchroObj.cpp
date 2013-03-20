//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbSynchroObj.cpp
//
//	[�@�\] �������s�����߂̊�{�N���X
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include <windows.h>
#include <assert.h>
#include "MsCriticalSection.h"
#include "MsSynchroObj.h"

//	�P��X���b�h�Ǘ��p�I�u�W�F�N�g�̏��L����v�������̃X���b�h����̗v����҂�����
//
void MbSynchroObj::MbSOLock( void)
{

	m_TryLockLock.MbCSEnter( );
	m_iLockCount++;
	m_TryLockLock.MbCSLeave( );

	m_ObjectLock.MbCSEnter( );
}

//	�P��X���b�h�Ǘ��p�I�u�W�F�N�g�̏��L�����������
//
void MbSynchroObj::MbSOUnlock( void)
{
	m_ObjectLock.MbCSLeave( );
	m_iLockCount--;
	assert( m_iLockCount >= 0);
}

bool MbSynchroObj::MbSOisValid( void)
{

	if ( !m_ObjectLock.MbCSIsValid( ))	// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�ւ̃|�C���^
		return false;							// m_ObjectLock ������ł��邩�`�F�b�N����

	if ( !m_TryLockLock.MbCSIsValid( ))	// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�ւ̃|�C���^
		return false;                        	// m_TryLockLock ������ł��邩�`�F�b�N����
                                             
	if ( m_iLockCount < 0)				// <0 �f�X�g���N�^�𔲂��Ă���
		return false;

	return true;
}

