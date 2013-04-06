#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmEnt.h
//
//		�l�b�`�c���f��
//						�G���e�B�e�B
//
//==========================================================================================
//	�G���e�B�e�B
#include	"MhPlcInfo.h"
#include	"MhRoof.h"
#include	"MlLog.h"

namespace MC
{

void	mdmDEntFree();

class mdmEnt
{
public:
	MDID		m_idP;							// �eID( >=0) 	( -1: �폜�������G���e�B�e�B)
	MDIDSET		m_GidC;							// �qID�Z�b�g
	MDRFCSET	m_Grfc;							// �֌W�̃Z�b�g
	MSHORT		m_iTpAtr;						// �����^�C�v
	void*		m_pAtr;							// ����
	MDFIG		m_Fig;							// �}�`
public:
	mdmEnt()		{ Init();}
	~mdmEnt()		{ Free();}

	void	Init()
	{
		m_iTpAtr = 0;
		m_GidC.m_pst = 0;
		m_Grfc.m_pst = 0;
		m_pAtr = 0;
		m_Fig.SetpPmtl( 0);
	}		

	void	Free();

	// �f�o�b�O�p�g���[�X�o��
	void	Alloc( MINT i_szSC, MINT i_szAtr=0, MINT i_szFig=0);
	void	Print( MCHAR* s, MINT i_i);
};

inline void mdmEnt::Alloc( MINT i_szSC, MINT i_szAtr/*=0*/, MINT i_szFig/*=0*/)
{
	if ( i_szSC)
		m_GidC.Alloc( i_szSC);
		m_Grfc.Alloc( i_szSC);
	if ( i_szFig)
		m_Fig.Alloc( i_szFig);
}

//	�g���[�X
inline void mdmEnt::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "\t%d: %s < mdmDEnt > �eID = %d\n"), i_i, s, m_idP);
	MBTRCPRBF;
	m_GidC.Print( Mstr( "�t���q"), MDC_NONE_ID);
	m_Grfc.Print( Mstr( "�֌W"), MDC_NONE_ID);
	//m_pAtr->Print( Mstr( "����"));
	m_Fig.Print( Mstr( "�}�`"));
#endif
}

} // namespace MC
