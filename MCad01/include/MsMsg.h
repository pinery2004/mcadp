#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsMsg.h
//
//		���b�Z�[�W�̕\��
//		�G���[���b�Z�[�W�̕\��
//
//
//  K.Matsu           13/05/12    Created.
//==========================================================================================

namespace MC
{

class msmsg
{
public:
	////////////////////////////////////////////////////////////////////////////
	//	���b�Z�[�W�{�b�N�X���őO�ʂɕ\������
	//
	static void MsgBox(							// �ð��
						LPCSTR	i_pcText,		// ���b�Z�[�W
						LPCSTR	i_pcCaption		// ���o��
					);

	static void MsgBox(							// �ð��
				const	MCHAR*	i_pcText,		// ���b�Z�[�W
				const	MCHAR*	i_pcCaption		// ���o��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�G���[���^�[���u���[�N�|�C���g�p
	//
	static void	ErrorReturn( void);
	
	static void	SysError( 
							MCHAR*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode,						// �G���[�R�[�h
							MCHAR*				i_cComment = 0						// �R�����g
							);
	static void	SysError( 
							MCHAR*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode,						// �G���[�R�[�h
							char*				i_cComment							// �R�����g
							);
	static void	SysError( 
							char*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode,						// �G���[�R�[�h
							MCHAR*				i_cComment = 0						// �R�����g
							);
	static void	SysError( 
							char*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode,						// �G���[�R�[�h
							char*				i_cComment							// �R�����g
							);
	static void	CmdError( 
							char*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode						// �G���[�R�[�h
							);
	static void	CmdError( 
							MCHAR*				i_pcProgram,						// �G���[�v���O������
							int					i_iLineN,							// �s�ԍ�
							int					i_iErrorCode						// �G���[�R�[�h
							);

	/////////////////////////////////////////////////////////////////////////////////
	//////		���^�[���R�[�h
	////
	////static short shortCast( int i)
	////{
	////	ASSERT( -MINSHORT <= i && i <= MAXSHORT);
	////	return (short)i;
	////}

	////struct MbRT
	////{
	////	int	m_iRt;
	////
	////	MbRT()				: m_iRt( 0)		{}
	////	MbRT( int i_iRt)	: m_iRt( i_iRt)	{}
	////	
	////	operator short()			{ return shortCast( m_iRt);}
	////
	////	bool operator &&( bool b)	{ return (*this != 0) && b;}
	////	bool operator ||( bool b)	{ return (*this != 0) || b;}
	////	bool operator ==( int i)	{ return m_iRt == i;}
	////	bool operator !=( int i)	{ return m_iRt != i;}
	////	bool operator < ( int i)	{ return m_iRt <  i;}
	////	bool operator < ( long lg)	{ return m_iRt <  lg;}
	////	bool operator <=( int i)	{ return m_iRt <= i;}
	////	bool operator > ( int i)	{ return m_iRt >  i;}
	////	bool operator >=( int i)	{ return m_iRt >= i;}

};	// msmsg

} // namespace MC


