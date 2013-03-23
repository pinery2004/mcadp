#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhMbr.h
//
//		���@�^�����R�[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

//	���@�^��
#define	MHMBSZ_CODE		15						// ���@�^���ő啶����
#define	MHMBSZ_TYPE		15						// ���@�^���I��p��ރR�[�h�ő啶����
#define	MHMBSZ_CODEW	15						// ���@�^�� (�������ݗp)�ő啶����

namespace MC
{

class	MhMbr									// ���@�^�����R�[�h
{
	friend	class	mhPlcInfo;

	friend	void	MhLoadPtsMst();

//public:
	MINT				m_iMbrId;							// ���@�^��ID
	MCHAR				m_cMbrCode[MHMBSZ_CODE+1];			// ���@�^��
	MREAL				m_rBziWidth;						// ���ޕ�
	MREAL				m_rBziSZure;						// ���␳�p�c�����		�E�� = m_rWidth/2 + m_rSZure
															//						���� = m_rWidth/2 - m_rSZure
	MREAL				m_rBziHeight;						// ���ލ���
	MCHAR				m_cMbrType[MHMBSZ_TYPE+1];			// ���@�^���I��p��ރR�[�h
	MCHAR				m_cMbrCodeW[MHMBSZ_CODEW+1];		// ���@�^�� (�������ݗp�@�ʏ�m_cCode�Ɠ��� VerUp���ɕύX�������e������)

public:
	void	SetMbrId( MINT iMbrId)	
									{ m_iMbrId = iMbrId;}
	void	SetMbrCode( MCHAR* cMbrCode)
									{ Mstrncpy_s( m_cMbrCode, cMbrCode, MHMBSZ_CODE);}
	void	SetBziWidth( MREAL rBziWidth)
									{ m_rBziWidth = rBziWidth;}
	void	SetBziSZure( MREAL rBziSZure)
									{ m_rBziSZure = rBziSZure;}
	void	SetBziHeight( MREAL rBziHeight)
									{ m_rBziHeight = rBziHeight;}
	void	SetMbrType( MCHAR* cMbrType)
									{ Mstrncpy_s( m_cMbrType, cMbrType, MHMBSZ_TYPE);}
	void	SetMbrCodeW( MCHAR* cMbrCodeW)
									{ Mstrncpy_s( m_cMbrCodeW, cMbrCodeW, MHMBSZ_CODEW);}
	MINT 	GetMbrId()				{ return m_iMbrId;}
	MCHAR*	GetMbrCode()			{ return m_cMbrCode;}
	MREAL 	GetBziWidth()			{ return m_rBziWidth;}
	MREAL	GetBziSZure()			{ return m_rBziSZure;}
	MREAL	GetBziHeight()			{ return m_rBziHeight;}
	MCHAR*	GetMbrType()			{ return m_cMbrType;}
	MCHAR*	GetMbrCodeW()			{ return m_cMbrCodeW;}
};

} // namespace MC