#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgGrp.h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
//
//	MgGrp は、構造体の群を定義するテンプレートである。
//
//	オーバレイ関数を定義する。
//
//
#include	"MlLog.h"

#define		MGTP_GROUP	100

namespace MC
{

//
//===================================================================
//		MgGrp 
//
//				・構造体(可変長クラスデータのentity)の集合を定義する
//
//				派生クラス
//
//					MgGrpS:	固定長の構造体で開放時には、各entityのFreeは行わない
//					MgGrpF:	可変長の構造体で開放時には、各entityのFreeも行う
//

template <typename T> class MgGrp
{
												// G == 1: 子もMEMALOCありで開放時に子もFREEする
public:
	MUBYTE		m_tp;							// データタイプ　MGTP_GROUP
	MUBYTE		m_fa;							// アロケーションフラグ(0:配列, 1:malloc)
												// 		=1の場合は使用終了時にfreeで領域の開放を必要とする
	MSHORT		m_isz;							// 最大構造体数
	MSHORT		m_n;							// 構造体数
	T*			m_st;							// 構造体
public:
	MgGrp()	
						{ m_tp = MGTP_GROUP;
						  m_isz = m_n = m_fa = 0;
						  m_st = NULL;}
	//MgGrp( MINT tp1)	
	//					{ tp = tp1;
	//					  sz = n = fa = 0;
	//					  st = NULL;}
	MgGrp( MINT sz1, MINT tp1 = MGTP_GROUP);

	MgGrp( MINT sz1, T *st2, MINT tp1 = MGTP_GROUP);

	void Init()													// この群がさらに群になった場合の最終データより後のデータのクリア用
						{ m_tp = MGTP_GROUP;
						  m_isz = m_n = m_fa = 0;
						  m_st = NULL;}
	T& operator [] (MINT idx)									// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_st[idx];}
	void operator -= (MINT dn)									// 最後のdn個の構造体を削除
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()											// 最後の１個の構造体を削除
						{ if ( m_n>0) -- n;}
	void operator -- (int)										// 最後の１個の構造体を削除
						{ if ( m_n>0) n --;}
	void ReSize( MINT szn);										// 最大構造体数の変更と領域確保、エラー表示用にProg名称を入力

	void Print( MCHAR* s);										// トレース
};

//	構造体(点･整数･整数)群領域を確保する場合のコンストラクタ
template <typename T> MgGrp<T>::MgGrp(
				MINT		sz1,								// 構造体群の初期に確保する構造体の数
				MINT		tp1 = MGTP_GROUP					// 構造体群のタイプコード
				)
{
	m_tp = MGTP_GROUP;
	m_fa = 1;
	
	m_isz = sz1;
	m_n = 0;
	MBMALLOC( m_st, T, sz1);
}

//	構造体(点･整数･整数)群の領域を配列で与える場合のコンストラクタ
template <typename T> MgGrp<T>::MgGrp(
				MINT		sz1,								// 構造体の配列のサイズ
				T			*st2,								// 構造体の配列(空)
				MINT		tp1 = MGTP_GROUP					// 構造体群のタイプコード
				)
{
	m_tp = MGTP_GROUP;
	m_fa = 0;
	
	m_isz = sz1;
	m_n = 0;
	m_st = st2;
}


//	構造体群領域の拡張
template <typename T> void MgGrp<T>::ReSize( MINT i_sz)
{
	//if (szn > sz) {
	//	if (fa && st) {											//	構成構造体の領域をmallocで確保している場合
	//		MGREALLOC( st, T, szn);								//		構成構造体の領域をremallocで拡張
	//	} else {												//	構成構造体の領域を未確保または配列の場合
	//		T	*stb = st;
	//		MBMALLOC( st, T, szn);								//		構成構造体の領域をmallocで確保
	//		if (!fa)
	//			memcpy( st, stb, sizeof( T) * n);				//	構成構造体の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if ( i_sz > m_isz) {
		T	*stb = m_st;
																								//E		MBMALLOC( m_st, T, i_sz);		 						//	構成点の新領域をmallocで確保
		MbAlloc<T>( m_st, i_sz);
		if ( m_isz)
			memcpy( m_st, stb, m_isz * sizeof( T));				//	構成点の領域にデータがあった場合は新領域へコピーする
		if ( m_fa && stb)												//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)stb;									//
		else
			m_fa = 1;
		m_isz = i_sz;
	}
}

//	トレース
template <typename T> void MgGrp<T>::Print(MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s < MgGrp > サイズ = %d、頂点数 = %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		m_st[ic].Print( s, ic);
	}
#endif
}

//
//===================================================================
//		MgGrpS
//
//		構造体群 
//				・構造体(固定長クラスデータのentity)の集合を定義する
//				・開放時に全体のfreeだけ行い、各entity毎のfreeは行わない
//
template <typename T>
class MgGrpS : public MgGrp<T>
{
public:
	~MgGrpS();
	void Free();
	void operator += (const T &st);								// 構成構造体の追加	構造体群 += 構造体
	void operator = (const MgGrpS<T> &Gst);					// 複写				構造体群 = 構造体群
	void operator += (const MgGrpS<T> &Gst);					// 構造体群の追加	構造体群 += 構造体群
	void operator ++ ( int);									// 最後の１個の構造体を追加(中身が空の構造体を追加)
	T& operator () ( MINT idx);									// 構成構造体を()で指定して読み書きする
																// 最大数の次を指定した場合は領域を拡張する
																// さらに大きな値の指定の場合はオーバフローエラーとする
};

//	デストラクタ
template <typename T> MgGrpS<T>::~MgGrpS()
{
	if ( m_st) {
		if ( m_fa)
			MBFREE( m_st);
	}
}

template <typename T> void MgGrpS<T>::Free()
{
	if ( m_st) {
		if ( m_fa) {
			MBFREE( m_st);
			m_fa = 0;
			m_isz = 0;
		}
		m_n = 0;
	}
}

//	構成構造体の追加	構造体群 += 構造体
template <typename T> void MgGrpS<T>::operator += (const T &st1)					// Gst += st1
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
	m_st[m_n] = st1;
	m_n++;
}

//	複写				構造体群 = 構造体群
template <typename T> void MgGrpS<T>::operator = (const MgGrpS<T>& Gst)
{
	MINT	nn = Gst.n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_st);										//	構成点の領域をmallocで確保していた場合は一旦free
		MBMALLOC( m_st, T, nn);									//	構成点の領域をmallocで確保
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_st, Gst.m_st, nn * sizeof( T));
	m_n = nn;
}

//	構造体群の追加		構造体群 += 構造体群
template <typename T> void MgGrpS<T>::operator += (const MgGrpS<T> &Gst)			// Gst += Gst1
{
	MINT	nn = m_n + Gst.m_n;
	if ( nn > m_isz)
		ReSize( nn);
	memcpy( &m_st[n], Gst.m_st, sizeof( T) * Gst.m_n);
	m_n = nn;
}

//	空の構成構造体を追加	構造体群 ++
template <typename T> void MgGrpS<T>::operator ++ ( int)							// Gst ++
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
	m_n++;
}

//	構成構造体を()で指定して読み書きする
//	例　Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> T& MgGrpS<T>::operator () (MINT idx)
{
	if ( idx == m_isz) {
		ReSize( sz + MGMAX( m_isz, 4));							// ２倍に領域拡張(拡張後の最低領域サイズは４とする)
	} else if ( idx > m_isz) {
		msSysError( MBCstr( "MgGrpS()"), MC_ERR_OVERFLOW);
	}
	//for (; m_n<=idx; m_n++)					
	memset( &m_st[n], 0, (idx-m_n) * sizeof(m_st));				// 最終データより後のデータはクリアし、n = idx+1　にする
	return m_st[idx];
};

//
//===================================================================
//		MgGrpF
//
//		構造体群 
//				・構造体(可変長クラスデータのentity)の集合を定義する
//				・開放時に全体のfreeだけでなく、各entity毎のfreeを行う
//
template <typename T>
class MgGrpF : public MgGrp<T>
{
public:
	~MgGrpF();
	void Free();
	void operator += (const T &st);								// 構成構造体の追加	構造体群 += 構造体
	void operator = (const MgGrpF<T> &Gst);					// 複写				構造体群 = 構造体群
	void operator += (const MgGrpF<T> &Gst);					// 構造体群の追加	構造体群 += 構造体群
	void operator ++ ( int);									// 最後の１個の構造体を追加(中身が空の構造体を追加)
	T& operator () ( MINT idx);									// 構成構造体を()で指定して読み書きする
																// 最大数の次を指定した場合は領域を拡張する
																// さらに大きな値の指定の場合はオーバフローエラーとする
};

//	デストラクタ
template <typename T> MgGrpF<T>::~MgGrpF()
{
	MINT	ic;
	if ( m_st) {
		for(ic=0; ic<m_n; ic++) 
			m_st[ic].Free();									// 領域開放
		if ( m_fa)
			MBFREE( m_st);
	}
}

template <typename T> void MgGrpF<T>::Free()
{
	MINT	ic;
	if ( m_st) {
		for(ic=0; ic<m_n; ic++) 
			m_st[ic].Free();									// 領域開放
		if ( m_fa) {
			MBFREE( m_st);
			m_fa = 0;
			m_isz = 0;
		}
		m_n = 0;
	}
}

//	構成構造体の追加	構造体群 += 構造体
template <typename T> void MgGrpF<T>::operator += (const T &st1)					// Gst += st1
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
	m_st[m_n].Init();
	m_st[m_n] = st1;
	m_n++;
}

//	複写				構造体群 = 構造体群
template <typename T> void MgGrpF<T>::operator = (const MgGrpF<T>& Gst)
{
	MINT	nn = Gst.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_st);										//	構成点の領域をmallocで確保していた場合は一旦free
		MBMALLOC( m_st, T, nn);									//	構成点の領域をmallocで確保
		m_fa = 1;
		m_isz = nn;
	}
//	memcpy( st, Gst.st, sizeof( T) * nn);
	for ( iC=0; iC<Gst.m_n; iC++) {
		m_st[iC].Init();
		m_st[iC] = Gst.m_st[iC];
	}
	m_n = nn;
}

//	構造体群の追加		構造体群 += 構造体群
template <typename T> void MgGrpF<T>::operator += (const MgGrpF<T> &Gst)		// Gst += Gst1
{
	MINT	nn = m_n + Gst.m_n;
	if ( nn > m_isz)
		ReSize( nn);
//	memcpy( &st[n], Gst.st, sizeof( T) * Gst.n);
	for ( iC=0; iC<Gst.m_n; iC++) {
		m_st[iC+n].Init();
		m_st[iC+n] = Gst.m_st[iC];
	}
	m_n = nn;
}

//	空の構成構造体を追加	構造体群 ++
template <typename T> void MgGrpF<T>::operator ++ ( int)							// Gst ++
{
	if ( n >= sz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
	m_st[n].Init();
	m_n++;
}

//	構成構造体を()で指定して読み書きする
//	例　Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> T& MgGrpF<T>::operator () (MINT idx)
{
	if ( idx == m_isz) {
		ReSize( m_isz + MGMAX( m_isz, 4));							//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
	} else if ( idx > sz) {
		msSysError( MBCstr( "MgGrpF()"), MC_ERR_OVERFLOW);
	}
	for (; m_n<=idx; m_n++)											// 最終データより後のデータはクリアし、n = idx+1　にする
		 m_st[n].SetInit();
	return m_st[idx];
};

} // namespace MC
