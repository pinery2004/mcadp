//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbCriticalSection.cpp
//
//	��������	
//	[�@�\] ��̃X���b�h�̂ݎ��s�����̃X���b�h��҂�����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MsCriticalSection.h" /*DNT*/

// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�ւ̃|�C���^������ł��邩�`�F�b�N����
//
bool MbCriticalSection::MbCSIsValid( void)
{

//	if ( this == NULL) return false;       // CHECKSTRUCTPTR��NUL�`�F�b�N�@�\����

	if ( !CHECKSTRUCTPTR( this))
	{
		return false;
	}
	return true;
}

// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�̏��L����v������
// ( ���L�����l������܂őҋ@����)
//
void MbCriticalSection::MbCSEnter( void)
{
	::EnterCriticalSection( ( LPCRITICAL_SECTION)&CritSect);
}

// ���L�����������
//
void MbCriticalSection::MbCSLeave( void)
{
	::LeaveCriticalSection( ( LPCRITICAL_SECTION)&CritSect);
}

