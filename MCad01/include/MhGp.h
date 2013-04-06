#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhGp.h
//
//		構成レコード
//
//
//  K.Matsu           13/04/03    Created.
//==========================================================================================

// 構成( 屋根、小屋、天井、耐力壁、壁、床、基礎)
#define	MHKSSZ_NMKOSEI	15									// 構成(組)名最大文字数
#define	MHKSSZ_NMFUSEZU	15									// 伏図名最大文字数

namespace MC
{

class	mhGp									// 構成レコード
{
	friend	class	mhPlcInfo;
	friend	class	mhPartsTp;

	MINT	m_iCdGp;							// 構成(組)コード
	MCHAR	m_sNmGp[MHKSSZ_NMKOSEI + 1];		// 構成(組)名
	MCHAR	m_sNmFusezu[MHKSSZ_NMFUSEZU + 1];	// 伏図名
public:
	void	SetCdGp( MINT iCdGp)	{ m_iCdGp = iCdGp;}
	void	SetNmGp( MCHAR* cNmGp)	{ Mstrncpy_s( m_sNmGp, cNmGp, MHKSSZ_NMKOSEI);}
	void	SetNmFusezu( MCHAR* cNmFusezu)
									{ Mstrncpy_s( m_sNmFusezu, cNmFusezu, MHKSSZ_NMKOSEI);}

	MINT	GetCdGp()		{ return m_iCdGp;}
	MCHAR*	GetNmGp()		{ return m_sNmGp;}
	MCHAR*	GetNmFusezu()	{ return m_sNmFusezu;}

	bool	IsYane()		{ return m_iCdGp == MP_GP_YANE;}		// 屋根
	bool	IsTenjo()		{ return m_iCdGp == MP_GP_TENJO;}		// 天井
	bool	IsYuka()		{ return m_iCdGp == MP_GP_YUKA;}		// 床
	bool	IsKiso()		{ return m_iCdGp == MP_GP_KISO;}		// 基礎
};

} // namespace MC