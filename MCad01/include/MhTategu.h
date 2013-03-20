#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhTategu.h
//
//		��������R�[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

//	����(�ǊJ��)
#define	MHTTSZ_CODE		4										// �J���R�[�h�ő啶����

namespace MC
{

class MhMdlIO;

class	MhTateguInfo
{
	friend	class	mhPlcInfo;

	MCHAR	m_cKCode[MHTTSZ_CODE + 1];			// �J���R�[�h
	MREAL	m_rROW;								// �J����
	MREAL	m_rROH;								// �J������
	MREAL	m_rHeight;							// ���t������(�܂������[����)
	MREAL	m_rMUSz[2];							// ���E�܂����󒷂�

public:
	MINT	Load(												// �c�a���P���R�[�h�ǂݍ���
						MhMdlIO*	i_phMdl						// �ǂݍ��݃t�@�C���@�n���h��
				);
	MINT	Save(												// �c�a�ւP���R�[�h��������
						MhMdlIO*	i_phMdl						// �������݃t�@�C���@�n���h��
				);

	void	SetKCode( MCHAR* cKCode)	{ Mstrncpy_s( m_cKCode, cKCode, MHTTSZ_CODE);}
	void	SetROW( MREAL rROW)			{ m_rROW = rROW;}
	void	SetROH( MREAL rROH)			{ m_rROH = rROH;}
	void	SetHgt( MREAL rHeight)
										{ m_rHeight = rHeight;}
	void	SetMUSz( MREAL rMUSz, MINT iM)
										{ m_rMUSz[iM] = rMUSz;}

	MCHAR*	GetKCode()					{ return m_cKCode;}
	MREAL 	GetROW()					{ return m_rROW;}
	MREAL	GetROH()					{ return m_rROH;}
	MREAL	GetHeight()					{ return m_rHeight;}
	MREAL*	GetMUSz()					{ return m_rMUSz;}
	MREAL	GetMUSz( MINT iM)			{ return m_rMUSz[iM];}
};

} // namespace MC