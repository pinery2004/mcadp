#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhGp.h
//
//		�\�����R�[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

// �\��( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b)
#define	MHKSSZ_NMKOSEI	15									// �\��(�g)���ő啶����
#define	MHKSSZ_NMFUSEZU	15									// ���}���ő啶����

namespace MC
{

class	MhGp									// �\�����R�[�h
{
	friend	class	mhPlcInfo;
	friend	class	mhTpPts;

	MINT	m_iCdGp;							// �\��(�g)�R�[�h
	MCHAR	m_sNmGp[MHKSSZ_NMKOSEI + 1];		// �\��(�g)��
	MCHAR	m_sNmFusezu[MHKSSZ_NMFUSEZU + 1];	// ���}��
public:
	void	SetCdGp( MINT iCdGp)	{ m_iCdGp = iCdGp;}
	void	SetNmGp( MCHAR* cNmGp)	{ Mstrncpy_s( m_sNmGp, cNmGp, MHKSSZ_NMKOSEI + 1);}
	void	SetNmFusezu( MCHAR* cNmFusezu)
									{ Mstrncpy_s( m_sNmFusezu, cNmFusezu, MHKSSZ_NMKOSEI + 1);}

	MINT	GetCdGp()		{ return m_iCdGp;}
	MCHAR*	GetNmGp()		{ return m_sNmGp;}
	MCHAR*	GetNmFusezu()	{ return m_sNmFusezu;}

	bool	IsYane()		{ return m_iCdGp == MP_GP_YANE;}		// ����
	bool	IsTenjo()		{ return m_iCdGp == MP_GP_TENJO;}		// �V��
	bool	IsYuka()		{ return m_iCdGp == MP_GP_YUKA;}		// ��
	bool	IsKiso()		{ return m_iCdGp == MP_GP_KISO;}		// ��b
};

} // namespace MC