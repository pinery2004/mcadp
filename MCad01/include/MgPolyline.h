#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolyline.h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "mdPlex.h"
#include "MsDefArea.h"

//
//	MgPolyg.h 
//	Copyright;
// 
//	説明
//
//	MgPolyl2Dは２次元の折れ線を、MgPolyl3Dは３次元の折れ線を定義する。
//	MgGPolyl2Dは２次元の折れ線群を、MgGPolyl3Dは３次元の折れ線群を定義する。
//	MgGLine2Dは２次元の線分群を、MgGPolyl3Dは３次元の線分群を定義する。
//	MgGIntは整数群を、MgGRealは実数群を定義する。
//	MgGPoint2Dは２次元の点群を、MgGPoint3Dは３次元の点群を定義する。
//	オーバレイ関数を定義する。
//
#include "MgPlane.h"
#include "MgRect.h"

#ifdef DLL_EXPORT_POLILINE
	#undef DLL_EXPORT_POLILINE
#endif

#ifdef DLL_EXPORT_POLYLINE_DO
	#pragma message( "<<< MgPolyline・dll_EXport >>>")
	#define DLL_EXPORT_POLILINE							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_POLILINE
		#else
//			#pragma message( "=== MgPolyline・dll_IMport ===")
			#define DLL_EXPORT_POLILINE						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_POLILINE
	#endif
#endif

namespace MC
{

//class MgGPoint2D;
//class MgGPoint3D;
//class MgGPolyl2D;
//class MgGPolyl3D;
//class MgGLine2D;
//class MgGLine3D;
//class MgGReal;
class MgPolyl3D;
class MgGPolyl3D;
//
//======================( ２次元 )==============================
//		折れ線
class DLL_EXPORT_POLILINE MgPolyl2D						// ２Ｄポリゴン
{
public:
	MUBYTE		m_tp;							// データタイプ　MGTP_POLYG
	MUBYTE		m_fa;							// アロケーションフラグ(0:配列, 1:malloc)
												// 		=1の場合は使用終了時にfreeで領域の開放を必要とする
	MSHORT		m_isz;							// 最大頂点数
	MSHORT		m_n;							// 頂点数
	MgPoint2D* 	m_p;
public:
	MgPolyl2D()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl2D( MINT sz);
	MgPolyl2D( MINT sz1, MgPoint2D *p2);
	~MgPolyl2D()			{ if ( m_fa) MBFREE( m_p);}								// 領域開放
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}	// 領域初期化
	void Free()			{ if ( m_fa) MBFREE( m_p); m_isz = m_n = m_fa = 0;}			// 領域開放
//	
	const MgPoint2D& operator () ( MINT idx) const;
	MgPoint2D& operator () ( MINT idx);
	const MgPoint2D& operator [] ( MINT idx) const								// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_p[idx];}
	MgPoint2D& operator [] ( MINT idx)											// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_p[idx];}
	void operator = (const MgPolyl2D &pg);
	void operator = (const MgPolyl3D &Pg);										// ３次元→２次元
	void operator += (const MgPoint2D& pt);										// ポリゴンに点を追加		Pg1 += Pt2
	void operator += (const MgPolyl2D &pg);										// ポリゴンにポリゴンを追加	Pg1 += Pg2
	void operator -= (MINT dn)													// ポリゴンの最終ｎ点を削除
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()															// ポリゴンの最終点を削除
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)														// ポリゴンの最終点を削除
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// この群がさらに群になった場合の最終データより後のデータのクリア用
	void Set( const MgPolyl3D &Pg);												// ３次元→２次元代入用
	MINT Rotation() const;
	void Rev();
	void Resize( MINT szn);
	MREAL Area();
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};
//
//======================( ３次元 )==============================
//		折れ線
//
class DLL_EXPORT_POLILINE MgPolyl3D						// ３Ｄポリゴン
{
public:
	MUBYTE		m_tp;							// データタイプ　MGTP_POLYG3
	MUBYTE		m_fa;							// アロケーションフラグ(0:配列, 1:malloc)
												// 		=1の場合は使用終了時にfreeで領域の開放を必要とする
	MSHORT		m_isz;							// 最大頂点数
	MSHORT		m_n;							// 頂点数
	MgPoint3D*	m_p;
public:
	MgPolyl3D()			{ m_tp = MGTP_POLYG3; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl3D( MINT sz1);
	MgPolyl3D( MINT sz1, MgPoint3D *p2);
	~MgPolyl3D()			{ if ( m_fa) MBFREE( m_p);}							// 領域開放
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}// 領域初期化
	void Free()	
				{
					if ( m_fa)
						MBFREE( m_p);
					m_isz = m_n = m_fa = 0;
				}					// 領域開放
//
	const MgPoint3D& operator () ( MINT idx) const;
	MgPoint3D& operator () ( MINT idx);
	const MgPoint3D& operator [] ( MINT idx) const								// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_p[idx];}
	MgPoint3D& operator [] ( MINT idx)											// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_p[idx];}
	void operator = (const MgPolyl3D &Pg);
	void operator = (const MgPolyl2D &pg);										// ２次元→３次元 (z = 0.)
//						{ *this = MgPolyl3D( pg);}
	void operator += (const MgPoint3D& Pt);										// Pg1 += Pt2
	void operator += (const MgPolyl3D &Pg);										// Pg1 += Pg2
	void operator -= (MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					//この群がさらに群になった場合の最終データより後のデータのクリア用
	void Set( const MgPolyl2D &pg, MREAL z = 0.);								// ２次元→３次元代入用 (z = 0.)
	void Set( const MgPolyl2D &pg, const MgPlane3D& Ply);						// ２次元→３次元代入用
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( ２次元 )==============================
//		折れ線群
//
class DLL_EXPORT_POLILINE MgGPolyl2D
{
public:
	MUBYTE		m_tp;							// データタイプ　MGTP_GPOLYG
	MUBYTE		m_fa;							// アロケーションフラグ(0:配列, 1:malloc)
												// 		=1の場合は使用終了時にfreeで領域の開放を必要とする
	MSHORT		m_isz;							// 最大ポリゴン+穴数数
	MSHORT		m_n;							// ポリゴン+穴数
	MgPolyl2D*	m_pg;							// ポリゴンおよび穴
public:
	MgGPolyl2D()			{ m_tp = MGTP_GPOLYG; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl2D( MINT sz);
	MgGPolyl2D( MINT sz1, MgPolyl2D *pg2);
	~MgGPolyl2D();
//
	void Free();																// 領域開放
//
	const MgPolyl2D& operator () ( MINT idx) const;
	MgPolyl2D& operator () ( MINT idx);
	const MgPolyl2D& operator [] ( MINT idx) const								// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_pg[idx];}
	MgPolyl2D& operator [] ( MINT idx)											// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl2D &Gpg);
	void operator = (const MgGPolyl3D &GPg);									// ３次元→２次元
	void operator += (const MgPolyl2D &pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl2D &Gpg);									// GPg1 += GPg2
	void operator -= (MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if (m_n>0) { --m_n; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if (m_n>0) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl3D &GPg);											// ３次元→２次元代入用
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( ３次元 )==============================
//		折れ線群
//
class DLL_EXPORT_POLILINE MgGPolyl3D
{
public:
	MUBYTE		m_tp;							// データタイプ　MGTP_GPOLYG3
	MUBYTE		m_fa;							// アロケーションフラグ(0:配列, 1:malloc)
												// 		=1の場合は使用終了時にfreeで領域の開放を必要とする
	MSHORT		m_isz;							// 最大ポリゴン+穴数数
	MSHORT		m_n;							// ポリゴン+穴数
	MgPolyl3D*	m_pg;							// ポリゴンおよび穴
public:
	MgGPolyl3D()	
						{ m_tp = MGTP_GPOLYG3; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl3D( MINT sz1);
	MgGPolyl3D( MINT sz1, MgPolyl3D *Pg2);
	~MgGPolyl3D();
//
	void Free();																// 領域開放
//
	const MgPolyl3D& operator () ( MINT idx) const; 
	MgPolyl3D& operator () ( MINT idx);
	const MgPolyl3D& operator [] ( MINT idx) const								// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_pg[idx];}
	MgPolyl3D& operator [] ( MINT idx)											// ()のチェック機能と領域拡張機能を取り外し高速版	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl3D &GPg);
	void operator = (const MgGPolyl2D &Gpg);									// ２次元→３次元 (z = 0.)
	void operator += (const MgPolyl3D &Pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl3D &GPg);									// GPg1 += GPg2
	void operator -= (MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if ( m_n>0) { --m_n; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if ( m_n>0) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl2D &Gpg, MREAL z = 0.);								// ２次元→３次元代入用 (z = 0.)
	void Set( const MgGPolyl2D &Gpg, const MgPlane3D& Pln);						// ２次元→３次元代入用
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

} // namespace MC
