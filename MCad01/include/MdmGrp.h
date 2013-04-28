#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmGrp.h
//
//		ＭＣＡＤモデル
//						グループの子IDセット
//
//==========================================================================================

#include "MgMat.h"

#undef new

namespace MC
{

//	グループの子IDセット
class MdmSetGRP
{
public:
	MDID		m_idP;							// 親ID(0)	( -1: 削除し無効グループ)
	MCHAR*		m_psName;						// グループ名
	MREAL		m_rKt;							// 階高さ
	MREAL		m_rFl;							// 床高さ
	MgMat3E		m_MTrans;						// 座標変換マトリックス
	MDIDSET		m_GidC;							// 子IDセット
	
public:
	MdmSetGRP()		{ Init();}
	~MdmSetGRP()		{ Free();}
	void Init()
	{
		m_psName = NULL;
		m_GidC.Init();
	}
	void Free()	
	{
		MBFREE( m_psName);
		m_GidC.Free();
	}

	// グループの子IDセット生成
	//	最大指定数の(子グループの)IDが入る空領域を確保する
	void* operator new( size_t i_sz);			// 初期の最大グループの子ID数
	// グループの子IDを追加する
	void operator += ( MDID i_idMdg);
	// グループの子IDを削除する
	void operator -= ( MDID i_idMdg);
	// グループに初期値を設定する
	void SetInit(
						MDID	i_idP,			// 親ID(0)
						MCHAR*	i_sName,		// グループ名
						MREAL	i_rKt,			// 階高さ
						MREAL	i_rFl			// 床高さ
				);
	// デバッグ用トレース出力
	void Print( MCHAR* s, MINT i_i);
};

// グループの子IDセット生成
//	最大指定数の(子グループの)IDが入る空領域を確保する
inline void* MdmSetGRP::operator new( size_t i_sz)
{
	MdmSetGRP* pSetGC = (MdmSetGRP*)DEBUG_NEW char[sizeof( MdmSetGRP)];
	pSetGC->m_idP = 0;
	pSetGC->m_psName = NULL;
	pSetGC->m_rKt = 0.;
	pSetGC->m_rFl = 0.;
	pSetGC->m_GidC.Alloc( (int)i_sz);
	return pSetGC;
}

// グループの子IDセットにグループの子IDを追加する
inline void MdmSetGRP::operator += (MDID i_idMdg)
{
	m_GidC += i_idMdg;
}

// グループの子IDセットのグループの子IDを削除する
inline void MdmSetGRP::operator -= (MDID i_idMd)
{
	//MINT iC;
	//bool bFnd = false;
	//for ( iC=0; iC<m_GidC.m_n; iC++) {
	//	if ( m_GidC.m_st[iC] == i_idMd) {
	//		for ( iC++; iC<m_GidC.m_n; iC++) {
	//			m_GidC.m_st[iC-1] = m_GidC.m_st[iC];
	//		}
	//		m_GidC.m_n --;
	//		bFnd = true;
	//		break;
	//	}
	//}
	//ASSERT( bFnd);

	m_GidC -= i_idMd;
}

	// グループに初期値を設定する
inline void MdmSetGRP::SetInit(
						MDID	i_idP,			// 親ID(0)
						MCHAR*	i_sName,		// グループの子IDセット名	最大256文字
						MREAL	i_rKt,			// 階高さ
						MREAL	i_rFl			// 床高さ
				)
{
	m_idP = i_idP;
	int	nsz = Mstrlen( i_sName) + 1;
	int	isz = nsz * sizeof( MCHAR);
	m_psName = (MCHAR*)DEBUG_NEW char[isz];
	Mstrcpy_s( m_psName, nsz, i_sName);
	m_rKt = i_rKt;
	m_rFl = i_rFl;
}

//	トレース
inline void MdmSetGRP::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "	%3d: %s < MdmSetGRP > 親ID = %d，"), i_i, m_psName, m_idP);
	MBLOGPRBF;
	Msprintf_s( mlLog::m_Str, Mstr( "階高さ = %.1f, 床高さ = %.1f\n"),
									m_rKt, m_rFl);
	MBLOGPRBF;
	m_GidC.Print( Mstr( "子レイヤーID群"), MDC_NONE_ID);
#endif
}

} // namespace MC
