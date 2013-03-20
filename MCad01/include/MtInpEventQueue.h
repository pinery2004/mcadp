#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MtInpEventQueue.h
//
//		�����^�̑o�������X�g
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "MsSynchroObj.h"
#include "MsArray.h"

// Interface of MtInpEventQueue uses these classes in name
//

namespace MC
{

class MtInpEvent;
class MtInpEventFilter;

class MtInpEventQueueInterface	: public MbSynchroObj
{
	public:

	// �L���[�ɃC�x���g��ǉ�
	//	���Ӂ@�{�֐��͑҂��̂��鏈�����ł̎g�p�͋֎~�A�u���ɏI�����邱��
	virtual bool PostEvent( MtInpEvent *pEvent) = 0;

	// �L���[����C�x���g���擾����B�C�x���g��������΁A�C�x���g�̔�����҂B
	// �L���[���L�����Z������Ă���܂��͔p������Ă���ꍇ�́ANULL��Ԃ��B
	virtual MtInpEvent *WaitEvent( MtInpEventFilter *pEventFilter = NULL) = 0;
};

MtInpEventQueueInterface* CreateMtInpEventQueue( void);

class MtInpEventQueue : public MtInpEventQueueInterface
{
private:
	// �L���[�̏�Ԃ𓾂�
	enum EventQueueState {
		EQS_BAD = 0,			// ����������Ă��Ȃ�
		EQS_NORMAL = 1,			// ����
		EQS_CANCEL = 2,			// �L�����Z�����Ă΂ꂽ
		EQS_SHUTDOWN = 3		// �V���b�g�_�E��
	};

public:
	MtInpEventQueue( void);
	virtual ~MtInpEventQueue( void);

public:
	virtual bool PostEvent( MtInpEvent *pEvent);

	virtual MtInpEvent *WaitEvent( MtInpEventFilter *pEventFilter);
	virtual void	SignalCancel( void);

	// �C�x���g�L���[�̎g�p���I������
	virtual void	Shutdown( void);
	virtual void	DestroySelf( void)
	{
		delete this;
   	}
private:
	// �C�x���g�L���[����ɂ���
	void	flushQueue( void);

	MtInpEvent *getEvent( MtInpEventFilter *pEventFilter);

private:
	// �C�x���g�L���[�̏��
	EventQueueState		m_ourState;

	// �҂��ɂȂ��Ă���X���b�h�̐�
	long				m_nWaitCount;

	// �C�x���g�L���[
	MbArray< MtInpEvent * >	m_theQueue;

	// �C�x���g���������p	( WIN32 Event Synchronization object)
	HANDLE				m_hSynchroEvent;
};

} // namespace MC