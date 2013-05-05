//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolyline.cpp
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_POLYLINE_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgDefine.h"
#include "MgPlane.h"
#include "MgPolyline.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		折れ線（点群）
//
//	構成点の領域をmallocで確保する場合のコンストラクタ
MgPolyl2D::MgPolyl2D( MINT sz1)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgPolyl2D::MgPolyl2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	構成点を()で指定して読み書きする
const MgPoint2D& MgPolyl2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

MgPoint2D& MgPolyl2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

//	複写
void MgPolyl2D::operator = ( const MgPolyl2D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	memcpy( m_p, Pg.m_p, sizeof( MgPoint2D) * nn);
}

void MgPolyl2D::operator = ( const MgPolyl3D& Pg)
{
	MINT	ic1;
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint2DC( Pg.m_p[ic1]);  
}

//	構成点の追加
void MgPolyl2D::operator += ( const MgPoint2D& p1)				// Pg += Pt1
{
	MgPoint2D	p1sv;
	if ( m_n >= m_isz) {
//		p1sv = p1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( (MINT)m_isz, 4));				// ２倍に領域拡張(拡張後の最低領域サイズは４とする)
//		m_p[n++] = p1sv;
		m_p[m_n++] = p1;
	} else {
		m_p[m_n++] = p1;
	}
}

//	折れ線（点群）の追加
void MgPolyl2D::operator += ( const MgPolyl2D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	３次元の折れ線より２次元の折れ線を作成
void MgPolyl2D::Set( const MgPolyl3D &Pg)
{
	MINT	ic1;
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint2DC( Pg.m_p[ic1]);  
}

//	回転方向を得る(MC_LEFT_ROT:左回転, MC_RIGHT_ROT:右回転)
MINT MgPolyl2D::Rotation() const
{
	MINT	ist = 0;
	MINT	ic;
	MgPoint2D	Pb;
	MgPoint2D	Pc;
//
	MINT	irot = 0;
	MREAL	s = 0.;
	Pb = m_p[m_n-1];
	for ( ic=0; ic<m_n; ic++) {
		Pc = m_p[ic];											// 原点から各頂点へのベクトルの外積の合計を求め
		s += (Pb ^ Pc);											// 回転方向を考慮した折れ線の面積*2を求める
		Pb = Pc;
	}
	if (s > MGPTOL->D_2) {
		ist = MC_LEFT_ROT;
	} else if (s < -MGPTOL->D_2) {
		ist = MC_RIGHT_ROT;
	}							
	return ist;
}

//	折れ線の回転方向の反転
void MgPolyl2D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	折れ線領域の拡張
void MgPolyl2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	構成点の領域をmallocで確保している場合
	//		MGREALLOC( p, MgPoint2D, szn);						//		構成点の領域をremallocで拡張
	//	} else {												//	構成点の領域を未確保または配列の場合
	//		MgPoint2D		*pb = p;
	//		MBMALLOC( p, MgPoint2D, szn);  						//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint2D) * n);	//	構成点の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint2D*	pb = m_p;
//E		MBMALLOC( m_p, MgPoint2D, szn);		 					//	構成点の新領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, szn);
		if ( m_n)
			 memcpy( m_p, pb, m_n * sizeof( MgPoint2D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if ( m_fa && pb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	折れ線領域の面積
MREAL MgPolyl2D::Area()
{
	MINT	ic1;
	MgVect2D	v1, v2;
	MREAL	rArea = 0;

	for ( ic1=2; ic1<m_n; ic1++) {
		v1 = m_p[ic1-1] - m_p[0];
		v2 = m_p[ic1] - m_p[0];
		rArea += (v1 ^ v2);
	}
	return rArea / 2;
}

//	最大最小を求める
MgMinMaxR2D MgPolyl2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	トレース
void MgPolyl2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr("%s	MgPolyl2D	サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f)\n"),
						  ic, m_p[ic].x, m_p[ic].y);
		MBLOGPRBF;
	}
#endif
}

//
//======================( ３次元 )==============================
//		折れ線（点群）
//
//	構成点の領域をmallocで確保する場合のコンストラクタ
MgPolyl3D::MgPolyl3D( MINT sz1)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_p, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgPolyl3D::MgPolyl3D( MINT sz1, MgPoint3D *p2)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	構成点を()で指定して読み書きする
const MgPoint3D& MgPolyl3D::operator () (MINT idx) const
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

MgPoint3D& MgPolyl3D::operator () (MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

//	複写
void MgPolyl3D::operator = ( const MgPolyl3D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	memcpy( m_p, Pg.m_p, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgPolyl3D::operator = (const MgPolyl2D &pg)				// ２次元→３次元 (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_p);									//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint3DC( pg.m_p[ic1], 0.);  
}

//	構成点の追加
void MgPolyl3D::operator += ( const MgPoint3D& p1)				// Pg += Pt1
{
	MgPoint3D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));						// ２倍に領域拡張(拡張後の最低領域サイズは４)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	折れ線（点群）の追加
void MgPolyl3D::operator += ( const MgPolyl3D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);					//
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	２次元の折れ線より３次元の折れ線を作成
void MgPolyl3D::Set( const MgPolyl2D &pg, MREAL z)				// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
//		m_p[ic1].Set( pg.m_p[ic1], z);  
		m_p[ic1] = MgPoint3D( pg.m_p[ic1], z);  
}

void MgPolyl3D::Set( const MgPolyl2D &pg, const MgPlane3D& Ply)	// ２次元→３次元代入用
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1].Set( pg.m_p[ic1], Ply);  
}

//	折れ線の回転方向の反転
void MgPolyl3D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	折れ線領域の拡張
void MgPolyl3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	構成点の領域をmallocで確保している場合
	//		MGREALLOC( p, MgPoint3D, szn);						//		構成点の領域をremallocで拡張
	//	} else {												//	構成点の領域を未確保または配列の場合
	//		MgPoint3D	*pb = p;
	//		MBMALLOC( p, MgPoint3D, szn);		 				//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint3D) * n);	//	構成点の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint3D	*pb = m_p;
//E		MBMALLOC( m_p, MgPoint3D, szn);		 					//	構成点の新領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, szn);
		if ( m_n)
			memcpy( m_p, pb, sizeof( MgPoint3D) * m_n);			//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pb)											//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	最大最小を求める
MgMinMaxR3D MgPolyl3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_p[ic1]);
	}
	return mm;
}

//	トレース
void MgPolyl3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyl3D サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f,%7.1f)\n"),
									ic, m_p[ic].x, m_p[ic].y, m_p[ic].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( ２次元 )==============================
//		折れ線群
//
//	構成折れ線の領域をmallocで確保する場合のコンストラクタ
MgGPolyl2D::MgGPolyl2D( MINT sz1)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyl2D, sz1);
	MbAlloc<MgPolyl2D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyl2D) * sz1);
}

//	構成折れ線の領域を配列で与える場合のコンストラクタ
MgGPolyl2D::MgGPolyl2D( MINT sz1, MgPolyl2D *pg2)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyl2D) * sz1);
}

//	デストラクタ
MgGPolyl2D::~MgGPolyl2D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	領域開放
void MgGPolyl2D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;
}

//	構成折れ線を()で指定し読み書きする
const MgPolyl2D& MgGPolyl2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgGPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_pg[idx];
}

MgPolyl2D& MgGPolyl2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgGPolyl2D ()"), MC_ERR_OVERFLOW);
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									// 最終データより後のデータはクリアし、n = idx+1　にする
	return m_pg[idx];
}

//	複写
void MgGPolyl2D::operator = ( const MgGPolyl2D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyl2D::operator = (const MgGPolyl3D &GPg)				// ３次元→２次元
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

//	構成折れ線の追加
void MgGPolyl2D::operator += ( const MgPolyl2D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	折れ線群の追加
void MgGPolyl2D::operator += ( const MgGPolyl2D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}


//	３次元の折れ線より２次元の折れ線を作成
void MgGPolyl2D::Set( const MgGPolyl3D &GPg)					// ３次元→２次元代入用
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

//	空折れ線の追加
void MgGPolyl2D::AddPolyg()
{
	MINT	nn = m_n++;
	if ( nn > m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		Resize( m_isz + sza);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	m_n = nn;
}

//	全ての折れ線の回転方向の反転
void MgGPolyl2D::Rev()
{
	MINT	ic1, ic2, ic3;
	MgPolyl2D	*pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	折れ線群領域の拡張(拡張部分は未クリア)
void MgGPolyl2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	構成折れ線の領域をmallocで確保している場合
	//		MGREALLOC( pg, MgPolyl2D, szn);						//		構成折れ線の領域をreallocで拡張
	//	} else {												//	構成折れ線の領域を未確保または配列の場合
	//		MgPolyl2D		*pgb = pg;
	//		MBMALLOC( pg, MgPolyl2D, szn);						//		構成折れ線の領域をmallocで確保
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyl2D) * n);	//	構成折れ線の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyl2D	*pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyl2D, szn);			 			//	構成点の新領域をmallocで確保
		MbAlloc<MgPolyl2D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyl2D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pgb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGPolyl2D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyl2D	サイズ: %d, ポリゴン数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyl2D"));
#endif
}

//
//======================( ３次元 )==============================
//		折れ線群
//
//	構成折れ線の領域をmallocで確保する場合のコンストラクタ
MgGPolyl3D::MgGPolyl3D( MINT sz1)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyl3D, sz1);
	MbAlloc<MgPolyl3D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyl3D) * sz1);
}

//	構成折れ線の領域を配列で与える場合のコンストラクタ
MgGPolyl3D::MgGPolyl3D( MINT sz1, MgPolyl3D *pg2)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyl3D) * sz1);
}

//	デストラクタ
MgGPolyl3D::~MgGPolyl3D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	領域開放
void MgGPolyl3D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;

}

//	構成折れ線を()で指定し読み書きする
const MgPolyl3D& MgGPolyl3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgGPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_pg[idx];
};

MgPolyl3D& MgGPolyl3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgGPolyl3D ()"), MC_ERR_OVERFLOW);
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									//  最終データより後のデータはクリアし、n = idx+1　にする
	return m_pg[idx];
};

//	複写
void MgGPolyl3D::operator = ( const MgGPolyl3D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyl3D::operator = (const MgGPolyl2D &Gpg)				// ２次元→３次元 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = Gpg.m_pg[ic];
	m_n = nn;
}

//	構成折れ線の追加
void MgGPolyl3D::operator += ( const MgPolyl3D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	折れ線群の追加
void MgGPolyl3D::operator += ( const MgGPolyl3D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}

//	２次元の折れ線群より３次元の折れ線群を作成
void MgGPolyl3D::Set( const MgGPolyl2D &Gpg, MREAL z)			// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic].Set( Gpg.m_pg[ic], z);
	m_n = nn;
}

void MgGPolyl3D::Set( const MgGPolyl2D &Gpg, const MgPlane3D& Pln)	// ２次元→３次元代入用
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic].Set( Gpg.m_pg[ic], Pln);
	m_n = nn;
}

//	空折れ線の追加
void MgGPolyl3D::AddPolyg()
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	m_n++;
}

//	全ての折れ線の回転方向の反転
void MgGPolyl3D::Rev()
{
	MINT		ic1, ic2, ic3;
	MgPolyl3D	*pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	折れ線群領域の拡張
void MgGPolyl3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	構成折れ線の領域をmallocで確保している場合
	//		MGREALLOC( pg, MgPolyl3D, szn);						//		構成折れ線の領域をremallocで拡張
	//	} else {												//	構成折れ線の領域を未確保または配列の場合
	//		MgPolyl3D	*pgb = pg;
	//		MBMALLOC( pg, MgPolyl3D, szn);						//		構成折れ線の領域をmallocで確保
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyl3D) * n);	//	構成折れ線の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyl3D	*pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyl3D, szn);		 					//	構成点の新領域をmallocで確保
		MbAlloc<MgPolyl3D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyl3D));			//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pgb)											//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pgb;										//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGPolyl3D::Print( MCHAR* s) const								// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyl3D	サイズ: %d, ポリゴン数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyl3D"));
#endif
}

} // namespace MC
