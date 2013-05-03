#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MtInpEvent.h
//
//	�@�\	���̓C�x���g�L���[
//
//  K.Matsu           08/01/04    Created.
//
//#define MS_CMDMENU_STR_TYPE						// ��`: �R�}���h���j���[�L���[�ɕ�����`���œo�^�A����`: �����`���œo�^

namespace MC
{

class MtInpEvent
{
	friend MINT MtSendMessage( MINT msg, MINT nFlags, MgPoint2D* pPtMR);
	friend void MtProcessEvent( MtInpEvent *event);

	private:

#ifdef	MS_CMDMENU_STR_TYPE

		MUINT		m_type;
		MUINT		m_nflag;
		MCHAR		m_key;
		MgPoint2D	m_pt;
		MCHAR*		m_sMenuStr;
#else
		MUINT		m_type;
		MUINT		m_nflag;
		MCHAR		m_key;
		MgPoint2D	m_pt;
#endif
	public:
		//MtInpEvent( void)
		//				{ memset( this, 0, sizeof( *this));}
		//MtInpEvent( int type, MCHAR key)
		//				{ memset( this, 0, sizeof( *this)); m_key = key;}
#ifdef	MS_CMDMENU_STR_TYPE
		MtInpEvent( int type, int nflag, MgPoint2D pt)
						{ memset( this, 0, sizeof( *this)); m_type = type; m_nflag = nflag; m_pt= pt;}
		MtInpEvent( int type, int nflag, MCHAR* pcMenuString)
						{ memset( this, 0, sizeof( *this)); m_type = type;  m_nflag = nflag;
						  m_pt = MgPoint2D( 0.f, 0.f); m_sMenuStr = pcMenuString;}
#else
		MtInpEvent( int type, int nflag, MgPoint2D pt)
						{ memset( this, 0, sizeof( *this)); m_type = type; m_nflag = nflag; m_pt= pt;}
#endif
		//MtInpEvent( const MtInpEvent &theOther)
		//				{ m_type = theOther.m_type; m_nflag = theOther.m_nflag; m_key = theOther.m_key;
		//				  m_sMenuStr = theOther.m_sMenuStr; m_pt = theOther.m_pt;}
		virtual ~MtInpEvent( void)
						{ m_type = 0;}

	public:
		int		GetType( void)
						{ return m_type;}
		MCHAR	GetKey( void)
						{ return m_key;}
		MgPoint2D GetPoint( void)
						{ return m_pt;}
		void	GetPoint( MgPoint2D* pPt)
						{ *pPt = m_pt;}
		void	GetPoint( MREAL* pPt)
						{ pPt[0] = m_pt.x; pPt[1] = m_pt.y;}
#ifdef	MS_CMDMENU_STR_TYPE
		const MCHAR* GetMenuString( void)
						{ return m_sMenuStr;}
#endif
		bool	IsValid( void)
						{ return CHECKSTRUCTPTR( this);}
		void	SetNFlag( MINT	nflag)
						{ m_nflag = nflag & 0377;}
		MINT	GetNFlag( void)
						{ return m_nflag;}
};

} // namespace MC