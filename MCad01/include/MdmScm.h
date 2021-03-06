#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		ＭＣＡＤモデル
//
//
//==========================================================================================
namespace MC
{

//	スキーマの子IDセット
class MdmSetSCM
{
public:
	MDID		m_idP;							// 親ID
	MCHAR*		m_psName;						// スキーマ名称
	MDIDSET		m_GidC;							// 子レイヤーID群

public:
	MdmSetSCM()		{ Init();}
	~MdmSetSCM()	{ Free();}
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
	// スキーマの子IDセット生成
	//	最大指定数の(子の)IDが入る空領域を確保する
	void* operator new( size_t i_sz);			// 初期の最大子ID数
	////	領域を開放する
	//void* operator delete();
	// スキーマの子IDを追加する
	void operator += ( MDID i_idMd);
	// スキーマの子IDを削除する
	void operator -= ( MDID i_idMd);
	// スキーマに初期値を設定する
	void SetInit(
						MDID	i_idP,			// 親ID
						MCHAR*	i_sName			// グループの子IDセット名
				);
	// デバッグ用トレース出力
	void Print( MCHAR* s, MINT i_i);
};

// スキーマの子IDセット生成
//	最大指定数の(子の)IDが入る空領域を確保
inline void* MdmSetSCM::operator new( size_t i_sz)
{
	MdmSetSCM* pSetSCM = (MdmSetSCM*)DEBUG_NEW char[sizeof( MdmSetSCM)];
	pSetSCM->m_idP = 0;
	pSetSCM->m_psName = NULL;
	pSetSCM->m_GidC.Alloc( (int)i_sz);
	return pSetSCM;
}

// スキーマの子IDセットに子IDを追加する
inline void MdmSetSCM::operator += (MDID i_idMd)
{
	m_GidC += i_idMd;
}

// スキーマの子IDセットの子IDを削除する
inline void MdmSetSCM::operator -= (MDID i_idMd)
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

// スキーマに初期値を設定する
inline void MdmSetSCM::SetInit(
						MDID	i_idP,			// 親ID
						MCHAR*	i_sName			// 子IDセット名
				)
{
	m_idP = i_idP;
	int nsz = Mstrlen( i_sName) + 1;
	int isz = nsz * sizeof( MCHAR);
	m_psName = (MCHAR*)DEBUG_NEW char[isz];
	Mstrcpy_s( m_psName, nsz, i_sName);
}

//	トレース
inline void MdmSetSCM::Print( MCHAR* s, MINT i_i)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "\t%3d: %s	< MdmSetSCM > 親ID = %d\n"),
									i_i, m_psName, m_idP);
	MBLOGPRBF;
	m_GidC.Print( Mstr( "子レイヤーID群"), MDC_NONE_ID);
#endif
}

} // namespace MC
