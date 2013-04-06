#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmEnt.h
//
//		ＭＣＡＤモデル
//						エンティティ
//
//==========================================================================================
//	エンティティ
#include	"MhPlcInfo.h"
#include	"MhRoof.h"
#include	"MlLog.h"

namespace MC
{

void	mdmDEntFree();

class mdmEnt
{
public:
	MDID		m_idP;							// 親ID( >=0) 	( -1: 削除し無効エンティティ)
	MDIDSET		m_GidC;							// 子IDセット
	MDRFCSET	m_Grfc;							// 関係のセット
	MSHORT		m_iTpAtr;						// 属性タイプ
	void*		m_pAtr;							// 属性
	MDFIG		m_Fig;							// 図形
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

	// デバッグ用トレース出力
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

//	トレース
inline void mdmEnt::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "\t%d: %s < mdmDEnt > 親ID = %d\n"), i_i, s, m_idP);
	MBTRCPRBF;
	m_GidC.Print( Mstr( "付属子"), MDC_NONE_ID);
	m_Grfc.Print( Mstr( "関係"), MDC_NONE_ID);
	//m_pAtr->Print( Mstr( "属性"));
	m_Fig.Print( Mstr( "図形"));
#endif
}

} // namespace MC
