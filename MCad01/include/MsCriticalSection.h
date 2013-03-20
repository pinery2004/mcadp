//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsCriticalSection.h
//
//		
//
//
//  K.Matsu           04/25/07    Created.
//

#pragma once

class MbCriticalSection
	{
	public:
		// �N���e�B�J���Z�N�V�����I�u�W�F�N�g������������
		MbCriticalSection::MbCriticalSection( void)
		{
			memset( &CritSect,0,sizeof( CRITICAL_SECTION));
			::InitializeCriticalSection( &CritSect);
		};
		// �N���e�B�J���Z�N�V�����I�u�W�F�N�g���������
		MbCriticalSection::~MbCriticalSection( void)
		{
			::DeleteCriticalSection( &CritSect);
		};

	public:
		bool MbCSIsValid( );			// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�ւ̃|�C���^��
										// ����ł��邩�`�F�b�N����
		void MbCSEnter( void);			// �N���e�B�J���Z�N�V�����I�u�W�F�N�g�̏��L����v������
										// ( ���L�����l������܂őҋ@����)
		void MbCSLeave( void);			// ���L�����������
	private:
		CRITICAL_SECTION CritSect;		// CRITICAL_SECTION�^�ϐ���錾����
	};


// �P��X���b�h�̂ݎ��s�������A�����̃X���b�h�̋N�����������ꍇ�͑��̃X���b�h�͑ҋ@����
//
// �g�p���@
//	static MbCriticalSection theSection;
//	MbSynchroGuard theGuard( &theSection );

class MbSynchroGuard
	{
	public:
		MbSynchroGuard( MbCriticalSection *pSection)
		{
			m_pSection = pSection;
			m_pSection->MbCSEnter( );
		}

		~MbSynchroGuard( void)
		{
			m_pSection->MbCSLeave( );
			m_pSection = NULL;
		}

	private:
		MbCriticalSection *m_pSection;
	};

