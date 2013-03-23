//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MtInpEventQueue.cpp
//
//	�@�\	�C�x���g�L���[			
//		PostEvent
//		PeekEvent		
//		WaitEvent
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MsBasic.h"
#include "MsCriticalSection.h"
#include "MtInpEvent.h"
#include "MtInpEventFilter.h"
#include "MtInpEventQueue.h"

namespace MC
{

void ProcessMsgWaitForObject( HANDLE hSynchroObject); 

static volatile MINT	z_continue = 1;							// �X���b�h���s�t���O

MINT MtStopThread( void)
{
	z_continue = 0;
	return 0;
}

bool MtChkStopThread( void)
{
	return ( z_continue == 0);
}

// �R���X�g���N�^
MtInpEventQueue::MtInpEventQueue( void)
{
	m_ourState = EQS_BAD;
	m_nWaitCount = 0;

	m_hSynchroEvent = ::CreateEvent( NULL,	// security attributes
									 FALSE,	// this means an auto-reset object
									 FALSE,	// initially in non-signaled state
									 NULL	// unnamed object (we'll just keep the handle)
									);

	if ( m_hSynchroEvent != NULL)
		m_ourState = EQS_NORMAL;
}

// �f�X�g���N�^
MtInpEventQueue::~MtInpEventQueue( void)
{
	Shutdown();
	m_ourState = EQS_BAD;

	::CloseHandle( m_hSynchroEvent);
	m_hSynchroEvent = NULL;
}

////////////////////////////////////////////
//	�C�x���g�L���[�ɓ��͑���̃C�x���g��ǉ����A�ǉ��������Ƃ�m�点��
//
//	���Ӂ@�{�֐��͑҂��̂��鏈�����ł̎g�p�͋֎~�A�u���ɏI�����邱��
//
bool MtInpEventQueue::PostEvent( MtInpEvent *pEvent)
{
	SYNCHRONIZEMETHOD();

	if ( m_ourState != EQS_NORMAL)
		return false;

	m_theQueue.Add( pEvent);
	VERIFY( ::SetEvent( m_hSynchroEvent));						// �C�x���g�L���[�ɒǉ��������Ƃ�m�点��

	return true;
}

////S ////////////////////////////////////////////
////	���Ӂ@�{�֐��͑҂��̂��鏈�����ł̎g�p�͋֎~�A�u���ɏI�����邱��
////
//MtInpEvent * MtInpEventQueue::PeekEvent( MtInpEventFilter *pFilter)
//{
//	MtInpEvent *pRetval = NULL;
//
//	pRetval = getEvent( pFilter);
//
//	return pRetval;
//}

////////////////////////////////////////////
// ���b�Z�[�W�L���[�ւ̓��̓C�x���g�҂�
//
// ���Ӂ@�{�֐��́@m_hSynchroEvent�@���g�p���Ă���A�f�b�h���b�N
//       �ɂȂ�Ȃ��悤�l�����Ďg�p�̎�
//	
MtInpEvent * MtInpEventQueue::WaitEvent( MtInpEventFilter *pFilter)
{
	ASSERT( MbSOIsValid());

	MtInpEvent *pRetval = getEvent( pFilter);					// 

	while ( ( m_ourState == EQS_NORMAL) && ( pRetval == NULL)) {
		// �҂��J�n
		::InterlockedIncrement( &m_nWaitCount);

		while ( ( m_ourState == EQS_NORMAL) && ( pRetval == NULL))	{
			ProcessMsgWaitForObject( m_hSynchroEvent);			// ���̓C�x���g�҂�

			pRetval = getEvent( pFilter);
		}

		// �҂��I��
   		::InterlockedDecrement( &m_nWaitCount);
	}
	return pRetval;
}

////////////////////////////////////////////
// �C�x���g�L���[�̃L�����Z������
//
void MtInpEventQueue::SignalCancel( void)
{
	SYNCHRONIZEMETHOD();

	// �����҂��̃C�x���g���L�����Z������
	m_ourState = EQS_CANCEL;
	flushQueue();

	ASSERT( m_nWaitCount < 1000);
	ASSERT( m_nWaitCount >= 0);

	// �C�x���g�҂��ɃL�����Z����Ԃ�
	int iCount = m_nWaitCount;
	for( int i = 0; i < iCount; i++)
		::SetEvent( m_hSynchroEvent);

	m_ourState = EQS_NORMAL;
}

////////////////////////////////////////////
// �C�x���g�L���[�̏����I��
//
void MtInpEventQueue::Shutdown( void)
{
	SYNCHRONIZEMETHOD();

	SignalCancel();

	m_ourState = EQS_SHUTDOWN;
}

////////////////////////////////////////////
//	���̓C�x���g�L���[���t�B���^�ɉ����C�x���g���擾���A�L���[�����菜���B
//	�t�B���^��NULL�̏ꍇ�͍ŏ��̃C�x���g�B
//	�Ԓl NULL	  : �҂��C�x���g����
//		 �|�C���^ : �҂��C�x���g
//
MtInpEvent* MtInpEventQueue::getEvent( MtInpEventFilter *pFilter)
{
	SYNCHRONIZEMETHOD();

	MtInpEvent *pRetval = NULL;
	if ( ( m_theQueue.Number() > 0) && ( m_ourState == EQS_NORMAL)) {

		// �t�B���^�ɉ������ŏ��̃C�x���g��T��
		int i;
		for( i = 0; i < ( int)m_theQueue.Number(); i++)	{
			MtInpEvent *pCur;
			if ( m_theQueue.Get( i, &pCur) == false) {
				ASSERT( false);
				return NULL;
			}

			if ( ( pFilter == NULL) ||
				 ( pFilter->Match( pCur)))	{
				pRetval = pCur;
				ASSERT( pRetval->IsValid());
				m_theQueue.Remove( i);
				break;
			} 
			else {												// �t�B���^�ΏۊO�̃C�x���g�͎�菜�� AAAAAAAAAAAAAAAAAAAAAAAAA
				m_theQueue.Remove( i);							// �t�B���^�ΏۊO�̃C�x���g�͎�菜��
				break;											// �t�B���^�ΏۊO�̃C�x���g�͎�菜��
			}													// �t�B���^�ΏۊO�̃C�x���g�͎�菜��
		}
	}

	return pRetval;
}

////////////////////////////////////////////
//	�C�x���g�L���[���N���A����
void MtInpEventQueue::flushQueue( void)
{
	SYNCHRONIZEMETHOD();

	int iNumber;
	while( ( iNumber = m_theQueue.Number()) > 0) {
		MtInpEvent *pItem;
		if ( m_theQueue.Get( iNumber - 1 , &pItem)==false) {
			ASSERT(false);
			return;
		}
		m_theQueue.Remove( iNumber - 1);
		delete pItem;
	}
}

////////////////////////////////////////////
// ���b�Z�[�W(�C�x���g)��҂�
//
void ProcessMsgWaitForObject( HANDLE hSynchroObject) 
{
	CWinApp* pWinApp = AfxGetApp();
	static const DWORD GOTWINDOWSMESSAGE = (WAIT_OBJECT_0 + 1);

	DWORD dwWaitResult;
	do {
		MSG msg;
		// process any and all windows messages
		//
		while( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE)) {
			if ( !pWinApp->PreTranslateMessage(&msg)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}

		// hSynchroObject = HANDLE(0x000007a8);
		//
		dwWaitResult = ::MsgWaitForMultipleObjects( 1, 			// Only one object to wait on
											&hSynchroObject,	// this is the one
											FALSE,				// wait for only one (redundant, since there is only one)
											INFINITE,			// wait until the sun dies
											QS_ALLINPUT			// TODO -- is this right????
										);
	}
	while( dwWaitResult == GOTWINDOWSMESSAGE);
}
 
////S void MtInpEventQueue::processMessagesWhileWaiting( void)
//{
//	::ProcessMsgWaitForObject( m_hSynchroEvent);
//}

MtInpEventQueueInterface * CreateMtInpEventQueue( void)
{
	return new MtInpEventQueue;
}

} // namespace MC
