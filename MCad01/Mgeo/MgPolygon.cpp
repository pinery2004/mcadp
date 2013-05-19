//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolygon.cpp
//		
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_POLYGON_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgDefine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		多角形（点群）
//
//	構成点の領域をmallocで確保する場合のコンストラクタ
MgPolyg2D::MgPolyg2D( MINT sz1)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgPolyg2D::MgPolyg2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	構成点を()で指定して読み書きする
const MgPoint2D& MgPolyg2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( "MgPolyg2D ()");
	return m_p[idx];
}

MgPoint2D& MgPolyg2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( "MgPolyg2D ()");
	return m_p[idx];
}

//	複写
void MgPolyg2D::operator = ( const MgPolyg2D& Pg)
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

void MgPolyg2D::operator = ( const MgPolyg3D& Pg)
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
		m_p[ic1] = MgPoint2DC( Pg.m_P[ic1]);  
}

//	構成点の追加
void MgPolyg2D::operator += ( const MgPoint2D& p1)				// Pg += Pt1
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

//	多角形（点群）の追加
void MgPolyg2D::operator += ( const MgPolyg2D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	３次元の多角形より２次元の多角形を作成
void MgPolyg2D::Set( const MgPolyg3D &Pg)
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
		m_p[ic1] = MgPoint2DC( Pg.m_P[ic1]);  
}

//	回転方向を得る(MC_LEFT_ROT:左回転, MC_RIGHT_ROT:右回転)
MINT MgPolyg2D::Rotation() const
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
		s += (Pb ^ Pc);											// 回転方向を考慮した多角形の面積*2を求める
		Pb = Pc;
	}
	if (s > MGPTOL->D_2) {
		ist = MC_LEFT_ROT;
	} else if (s < -MGPTOL->D_2) {
		ist = MC_RIGHT_ROT;
	}							
	return ist;
}

//	多角形の回転方向の反転
void MgPolyg2D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	多角形領域の拡張
void MgPolyg2D::Resize( MINT szn)
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

//	多角形領域の面積
MREAL MgPolyg2D::Area()
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
MgMinMaxR2D MgPolyg2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	トレース
void MgPolyg2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
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
//		多角形（点群）
//
//	構成点の領域をmallocで確保する場合のコンストラクタ
MgPolyg3D::MgPolyg3D( MINT sz1)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_P, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_P, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgPolyg3D::MgPolyg3D( MINT i_isz1, MgPoint3D *i_pP2)
{
	m_tp = MGTP_POLYG3;
	m_isz = i_isz1;
	m_n = 0;
	m_fa = 0;
	m_P = i_pP2;
}

//	構成点を()で指定して読み書きする
const MgPoint3D& MgPolyg3D::operator () (MINT idx) const
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgPolyg3D ()"));
	return m_P[idx];
}

MgPoint3D& MgPolyg3D::operator () (MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgPolyg3D ()"));
	return m_P[idx];
}

//	複写
void MgPolyg3D::operator = ( const MgPolyg3D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	memcpy( m_P, Pg.m_P, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgPolyg3D::operator = (const MgPolyg2D &pg)				// ２次元→３次元 (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_P);									//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_P[ic1] = MgPoint3DC( pg.m_p[ic1], 0.);  
}

//	構成点の追加
void MgPolyg3D::operator += ( const MgPoint3D& i_P1)			// Pg += Pt1
{
	MgPoint3D	P1sv;
	if (m_n >= m_isz) {
		P1sv = i_P1;											// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));						// ２倍に領域拡張(拡張後の最低領域サイズは４)
		m_P[m_n++] = P1sv;
	} else {
		m_P[m_n++] = i_P1;
	}
}

//	多角形（点群）の追加
void MgPolyg3D::operator += ( const MgPolyg3D &i_Pg)			// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + i_Pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);					//
	for ( ic=0; ic<i_Pg.m_n; ic++)
		m_P[m_n++] = i_Pg.m_P[ic];
}

//	２次元の多角形より３次元の多角形を作成
void MgPolyg3D::Set( const MgPolyg2D &i_pg, MREAL z)			// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic1;
	MINT	nn = i_pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
//		m_P[ic1].Set( i_pg.m_p[ic1], z);  
		m_P[ic1] = MgPoint3D( i_pg.m_p[ic1], z);  
}

void MgPolyg3D::Set( const MgPolyg2D &i_pg, const MgPlane3D& o_pPly)// ２次元→３次元代入用
{
	MINT	ic1;
	MINT	nn = i_pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	構成点の領域をmallocで確保していた場合は一旦free
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_P[ic1].Set( i_pg.m_p[ic1], o_pPly);  
}

//	多角形の回転方向の反転
void MgPolyg3D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_P[ic1], m_P[ic2]);
		ic2--;
	}
}

//	多角形領域の拡張
void MgPolyg3D::Resize( MINT szn)
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
		MgPoint3D	*pb = m_P;
//E		MBMALLOC( m_P, MgPoint3D, szn);		 					//	構成点の新領域をmallocで確保
		MbAlloc<MgPoint3D>( m_P, szn);
		if ( m_n)
			memcpy( m_P, pb, sizeof( MgPoint3D) * m_n);			//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pb)											//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	最大最小を求める
MgMinMaxR3D MgPolyg3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_P[ic1]);
	}
	return mm;
}

//	トレース
void MgPolyg3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg3D サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f,%7.1f)\n"),
									ic, m_P[ic].x, m_P[ic].y, m_P[ic].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( ２次元 )==============================
//		多角形群
//
//	構成多角形の領域をmallocで確保する場合のコンストラクタ
MgGPolyg2D::MgGPolyg2D( MINT sz1)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyg2D, sz1);
	MbAlloc<MgPolyg2D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyg2D) * sz1);
}

//	構成多角形の領域を配列で与える場合のコンストラクタ
MgGPolyg2D::MgGPolyg2D( MINT sz1, MgPolyg2D *pg2)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyg2D) * sz1);
}

//	デストラクタ
MgGPolyg2D::~MgGPolyg2D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	領域開放
void MgGPolyg2D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;
}

//	構成多角形を()で指定し読み書きする
const MgPolyg2D& MgGPolyg2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg2D ()"));
	return m_pg[idx];
}

MgPolyg2D& MgGPolyg2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg2D ()"));
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									// 最終データより後のデータはクリアし、n = idx+1　にする
	return m_pg[idx];
}

//	複写
void MgGPolyg2D::operator = ( const MgGPolyg2D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyg2D::operator = (const MgGPolyg3D &GPg)				// ３次元→２次元
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

//	構成多角形の追加
void MgGPolyg2D::operator += ( const MgPolyg2D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	多角形群の追加
void MgGPolyg2D::operator += ( const MgGPolyg2D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}


//	３次元の多角形より２次元の多角形を作成
void MgGPolyg2D::Set( const MgGPolyg3D &GPg)					// ３次元→２次元代入用
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

//	空多角形の追加
void MgGPolyg2D::AddPolyg()
{
	MINT	nn = m_n++;
	if ( nn > m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		Resize( m_isz + sza);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	m_n = nn;
}

//	全ての多角形の回転方向の反転
void MgGPolyg2D::Rev()
{
	MINT	ic1, ic2, ic3;
	MgPolyg2D*	pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	多角形群領域の拡張(拡張部分は未クリア)
void MgGPolyg2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	構成多角形の領域をmallocで確保している場合
	//		MGREALLOC( pg, MgPolyg2D, szn);						//		構成多角形の領域をreallocで拡張
	//	} else {												//	構成多角形の領域を未確保または配列の場合
	//		MgPolyg2D		*pgb = pg;
	//		MBMALLOC( pg, MgPolyg2D, szn);						//		構成多角形の領域をmallocで確保
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyg2D) * n);	//	構成多角形の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyg2D*	pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyg2D, szn);			 			//	構成点の新領域をmallocで確保
		MbAlloc<MgPolyg2D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyg2D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pgb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGPolyg2D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyg2D	サイズ: %d, ポリゴン数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyg2D"));
#endif
}

//
//======================( ３次元 )==============================
//		多角形群
//
//	構成多角形の領域をmallocで確保する場合のコンストラクタ
MgGPolyg3D::MgGPolyg3D( MINT sz1)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_Pg, MgPolyg3D, sz1);
	MbAlloc<MgPolyg3D>( m_Pg, sz1);
	memset( m_Pg, 0, sizeof( MgPolyg3D) * sz1);
}

//	構成多角形の領域を配列で与える場合のコンストラクタ
MgGPolyg3D::MgGPolyg3D( MINT sz1, MgPolyg3D *pg2)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_Pg = pg2;
	memset( m_Pg, 0, sizeof( MgPolyg3D) * sz1);
}

//	デストラクタ
MgGPolyg3D::~MgGPolyg3D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_Pg[ic].Free();
	if ( m_fa)
		MBFREE( m_Pg);
}

//	領域開放
void MgGPolyg3D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_Pg[ic].Free();
	if ( m_fa)
		MBFREE( m_Pg);
	m_isz = m_n = m_fa = 0;

}

//	構成多角形を()で指定し読み書きする
const MgPolyg3D& MgGPolyg3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr("MgGPolyg3D ()"));
	return m_Pg[idx];
};

MgPolyg3D& MgGPolyg3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg3D ()"));
	for (; m_n<=idx; m_n++)
		m_Pg[m_n].SetInit();									//  最終データより後のデータはクリアし、n = idx+1　にする
	return m_Pg[idx];
};

//	複写
void MgGPolyg3D::operator = ( const MgGPolyg3D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

void MgGPolyg3D::operator = (const MgGPolyg2D &Gpg)				// ２次元→３次元 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic] = Gpg.m_pg[ic];
	m_n = nn;
}

//	構成多角形の追加
void MgGPolyg3D::operator += ( const MgPolyg3D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	m_Pg[m_n++] = Pg1;
}

//	多角形群の追加
void MgGPolyg3D::operator += ( const MgGPolyg3D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_Pg[m_n++] = GPg.m_Pg[ic];
}

//	２次元の多角形群より３次元の多角形群を作成
void MgGPolyg3D::Set( const MgGPolyg2D &Gpg, MREAL z)			// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic].Set( Gpg.m_pg[ic], z);
	m_n = nn;
}

void MgGPolyg3D::Set( const MgGPolyg2D &Gpg, const MgPlane3D& Pln)	// ２次元→３次元代入用
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic].Set( Gpg.m_pg[ic], Pln);
	m_n = nn;
}

//	空多角形の追加
void MgGPolyg3D::AddPolyg()
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// ２倍に領域拡張(拡張後の最低領域サイズは４)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	m_n++;
}

//	全ての多角形の回転方向の反転
void MgGPolyg3D::Rev()
{
	MINT		ic1, ic2, ic3;
	MgPolyg3D*	Pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		Pg1 = &m_Pg[ic1];
		ic3 = Pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( Pg1->m_P[ic2], Pg1->m_P[ic3]);
			ic3--;
		}
	}
}

//	多角形群領域の拡張
void MgGPolyg3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	構成多角形の領域をmallocで確保している場合
	//		MGREALLOC( pg, MgPolyg3D, szn);						//		構成多角形の領域をremallocで拡張
	//	} else {												//	構成多角形の領域を未確保または配列の場合
	//		MgPolyg3D*	pgb = pg;
	//		MBMALLOC( pg, MgPolyg3D, szn);						//		構成多角形の領域をmallocで確保
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyg3D) * n);	//	構成多角形の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyg3D*	pgb = m_Pg;
//E		MBMALLOC( m_Pg, MgPolyg3D, szn);		 				//	構成点の新領域をmallocで確保
		MbAlloc<MgPolyg3D>( m_Pg, szn);
		if ( m_n)
			 memcpy( m_Pg, pgb, m_n * sizeof( MgPolyg3D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && pgb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGPolyg3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyg3D	サイズ: %d, ポリゴン数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_Pg[ic].Print( Mstr( "MgGPolyg3D"));
#endif
}

//
//======================( ２次元 )==============================
//		線分群
//
//	構成線分の領域をmallocで確保する場合のコンストラクタ
MgGLine2D::MgGLine2D( MINT sz1)
{
	m_tp = MGTP_GLINE; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_ln, MgLine2D, sz1);
	MbAlloc<MgLine2D>( m_ln, sz1);
}

//	構成線分の領域を配列で与える場合のコンストラクタ
MgGLine2D::MgGLine2D( MINT sz1, MgLine2D *ln2)
{
	m_tp = MGTP_GLINE; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_ln = ln2;
}

//	構成線分を()で指定して読み書きする
const MgLine2D& MgGLine2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine2D ()"));
	return m_ln[idx];
}

MgLine2D& MgGLine2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine2D ()"));
	return m_ln[idx];
}

//	複写
void MgGLine2D::operator = ( const MgGLine2D& GLn)
{
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_ln, GLn.m_ln, sizeof( MgLine2D) * nn);
	m_n = nn;
}

void MgGLine2D::operator = ( const MgGLine3D &GLn)				// ３次元→２次元
{
	MINT	ic;
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine2DC( GLn.m_ln[ic]);
	m_n = nn;
}

//	構成線分の追加
void MgGLine2D::operator += ( const MgLine2D& Ln1)				// GLn += Ln1
{
	MgLine2D	Ln1sv;
	if (m_n >= m_isz) {
		Ln1sv = Ln1;											// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_ln[m_n++] = Ln1sv;
	} else {
		m_ln[m_n++] = Ln1;
	}
}

//	構成線分群の追加
void MgGLine2D::operator += ( const MgGLine2D &GLn)				// GLn += GLn1
{
	MINT	nn = m_n + GLn.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_ln[m_n], GLn.m_ln, sizeof( MgLine2D) * GLn.m_n);
	m_n = nn;
}

//	３次元の線分群より２次元の線分群を作成
void MgGLine2D::Set( const MgGLine3D &GLn)						// ３次元→２次元代入用
{
	MINT	ic;
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine2DC( GLn.m_ln[ic]);
	m_n = nn;
}

//	全線分の反転
void MgGLine2D::Rev()
{
	MINT	ic1;
	for ( ic1=0; ic1<m_n; ic1++) {
		msSwap( m_ln[ic1].p[0], m_ln[ic1].p[1]);
	}
}

//	線分群領域の拡張
void MgGLine2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && ln) {											//	構成線分の領域をmallocで確保している場合
	//		MGREALLOC( ln, MgLine2D, szn);						//		構成線分の領域をremallocで拡張
	//	} else {												//	構成線分の領域を未確保または配列の場合
	//		MgLine2D		*lnb = ln;
	//		MBMALLOC( ln, MgLine2D, szn);						//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( ln, lnb, sizeof( MgLine2D) * n);	//	構成線分の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgLine2D	*lnb = m_ln;
//E		MBMALLOC( m_ln, MgLine2D, szn);			 				//	構成点の新領域をmallocで確保
		MbAlloc<MgLine2D>( m_ln, szn);
		if ( m_n)
			 memcpy( m_ln, lnb, m_n * sizeof( MgLine2D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && lnb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)lnb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGLine2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGLine2D	サイズ: %d, 線分数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			ln[%2d]: (%7.1f,%7.1f,%7.1f,%7.1f)\n"),
						  ic, m_ln[ic].p[0].x, m_ln[ic].p[0].y,
						      m_ln[ic].p[1].x, m_ln[ic].p[1].y);
		MBLOGPRBF;
	}
#endif
}

//
//======================( ３次元 )==============================
//		線分群
//

//	構成多角形の領域をmallocで確保する場合のコンストラクタ
MgGLine3D::MgGLine3D( MINT sz1)
{
	m_tp = MGTP_GLINE3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_ln, MgLine3D, sz1);
	MbAlloc<MgLine3D>( m_ln, sz1);
}

//	構成線分の領域を配列で与える場合のコンストラクタ
MgGLine3D::MgGLine3D( MINT sz1, MgLine3D *ln2)
{
	m_tp = MGTP_GLINE3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_ln = ln2;
}

//	構成線分を()で指定して読み書きする
const MgLine3D& MgGLine3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine3D ()"));
	return m_ln[idx];
};

MgLine3D& MgGLine3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine3D ()"));
	return m_ln[idx];
};

//	複写
void MgGLine3D::operator = ( const MgGLine3D& GLn)
{
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_ln, GLn.m_ln, sizeof( MgLine3D) * nn);
	m_n = nn;
}

//	２次元の直線群より３次元の直線群を作成
void MgGLine3D::operator = (const MgGLine2D &Gln)				// ２次元→３次元 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine3DC( Gln.m_ln[ic]);
	m_n = nn;
}

//	構成線分の追加
void MgGLine3D::operator += ( const MgLine3D& Ln1)				// GLn += Ln1
{
	MgLine3D	Ln1sv;
	if (m_n >= m_isz) {
		Ln1sv = Ln1;											// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_ln[m_n++] = Ln1sv;
	} else {
		m_ln[m_n++] = Ln1;
	}
}

//	構成線分群の追加
void MgGLine3D::operator += ( const MgGLine3D &GLn)				// GLn += GLn1
{
	MINT	nn = m_n + GLn.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_ln[m_n], GLn.m_ln, sizeof( MgLine3D) * GLn.m_n);
	m_n = nn;
}

//	２次元の線分群より３次元の線分群を作成
void MgGLine3D::Set( const MgGLine2D &Gln, const MgPlane3D& Pln)	// ２次元→３次元代入用
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic].Set( Gln.m_ln[ic], Pln);
	m_n = nn;
}

void MgGLine3D::Set( const MgGLine2D &Gln, MREAL z)				// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	構成線分の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	構成線分の領域をmallocで確保
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic].Set( Gln.m_ln[ic], z);
	m_n = nn;
}

//	全線分の反転
void MgGLine3D::Rev()
{
	MINT	ic1;
	for ( ic1=0; ic1<m_n; ic1++) {
		msSwap( m_ln[ic1].p[0], m_ln[ic1].p[1]);
	}
}

//	線分群領域の拡張
void MgGLine3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && ln) {											//	構成線分の領域をmallocで確保している場合
	//		MGREALLOC( ln, MgLine3D, szn);						//		構成線分の領域をremallocで拡張
	//	} else {												//	構成線分の領域を未確保または配列の場合
	//		MgLine3D	*lnb = ln;
	//		MBMALLOC( ln, MgLine3D, szn);						//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( ln, lnb, sizeof( MgLine3D) * n);	//	構成線分の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgLine3D	*lnb = m_ln;
//E		MBMALLOC( m_ln, MgLine3D, szn);		 					//	構成点の新領域をmallocで確保
		MbAlloc<MgLine3D>( m_ln, szn);
		if ( m_n)
			 memcpy( m_ln, lnb, m_n * sizeof( MgLine3D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && lnb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)lnb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGLine3D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGLine3D	サイズ: %d, 線分数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			ln[%2d]: (%7.1f,%7.1f,%7.1f),(%7.1f,%7.1f,%7.1f)\n"),
						  ic, m_ln[ic].p[0].x, m_ln[ic].p[0].y, m_ln[ic].p[0].z,
						      m_ln[ic].p[1].x, m_ln[ic].p[1].y, m_ln[ic].p[1].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( １次元 )==============================
//		整数群
//

//	構成整数の領域をmallocで確保する場合のコンストラクタ
MgGInt::MgGInt( MINT sz1)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_i, MINT, sz1);
	MbAlloc<MINT>( m_i, sz1);
}

//	構成整数の領域を配列で与える場合のコンストラクタ
MgGInt::MgGInt( MINT sz1, MINT *i2)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_i = i2;
}

//	構成整数を()で指定して読み書きする
const MINT& MgGInt::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGInt ()"));
	return m_i[idx];
};

MINT& MgGInt::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGInt ()"));
	return m_i[idx];
};

//	複写
void MgGInt::operator = ( const MgGInt& GI)
{
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	構成整数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_i, MINT, nn);								//	構成整数の領域をmallocで確保
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_i, GI.m_i, sizeof( MINT) * nn);
	m_n = nn;
}

void MgGInt::operator = (const MgGReal &GR)						// 実数群 → 整数群
{
	MINT	ic;
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	構成整数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_i, MINT, nn);								//	構成整数の領域をmallocで確保
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_i[ic] = (MINT)GR.m_r[ic];
	m_n = nn;
}

//	構成整数の追加
void MgGInt::operator += ( MINT i1)								// GPt += i1
{
	MINT	i1sv;
	if (m_n >= m_isz) {
		i1sv = i1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_i[m_n++] = i1sv;
	} else {
		m_i[m_n++] = i1;
	}
}

//	整数群の追加
void MgGInt::operator += ( const MgGInt &GI)					// GPt += GI
{
	MINT	nn = m_n + GI.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_i[m_n], GI.m_i, sizeof( MINT) * GI.m_n);
	m_n = nn;
}

//	実数群の代入
void MgGInt::Set( const MgGReal &GR)							// 実数群→整数群 代入用
{
	MINT	ic;
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	構成整数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_i, MINT, nn);								//	構成整数の領域をmallocで確保
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_i[ic] = (MINT)GR.m_r[ic];
	m_n = nn;
}

//	整数群領域の拡張
void MgGInt::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && i) {											//	構成整数の領域をmallocで確保している場合
	//		MGREALLOC( i, MINT, szn);							//		構成整数の領域をremallocで拡張
	//	} else {												//	構成整数の領域を未確保または配列の場合
	//		MINT*		pb = i;
	//		MBMALLOC( i, MINT, szn);							//		構成整数の領域をmallocで確保
	//		if (!fa) memcpy( i, pb, sizeof( MINT) * n);			//	構成整数の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MINT	*ib = m_i;
//E		MBMALLOC( m_i, MINT, szn);			 					//	構成点の新領域をmallocで確保
		MbAlloc<MINT>( m_i, szn);
		if ( m_n)
			 memcpy( m_i, ib, m_n * sizeof( MINT));				//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && ib)											//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)ib;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGInt::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGInt	サイズ: %d, 整数の数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: %d\n"),
						  ic, m_i[ic]);
		MBLOGPRBF;
	}
#endif
}

//
//======================( １次元 )==============================
//		実数群
//

//	構成実数の領域をmallocで確保する場合のコンストラクタ
MgGReal::MgGReal( MINT sz1)
{
	m_tp = MGTP_GREAL;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_r, MREAL, sz1);
	MbAlloc<MREAL>( m_r, sz1);
}

//	構成実数の領域を配列で与える場合のコンストラクタ
MgGReal::MgGReal( MINT sz1, MREAL* r2)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_r = r2;
}

//	構成実数を()で指定して読み書きする
const MREAL& MgGReal::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGReal ()"));
	return m_r[idx];
};

MREAL& MgGReal::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGReal ()"));
	return m_r[idx];
};

//	複写
void MgGReal::operator = ( const MgGReal& GR)
{
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	構成実数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_r, MREAL, nn);								//	構成実数の領域をmallocで確保
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_r, GR.m_r, sizeof( MREAL) * nn);
	m_n = nn;
}

void MgGReal::operator = (const MgGInt &GI)						// 整数群 → 実数群
{
	MINT	ic;
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	構成実数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_r, MREAL, nn);								//	構成実数の領域をmallocで確保
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_r[ic] = (MREAL)GI.m_i[ic];
	m_n = nn;
}

//	構成実数の追加
void MgGReal::operator += ( MREAL r1)							// GPt += i1
{
	MREAL	r1sv;
	if (m_n >= m_isz) {
		r1sv = r1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_r[m_n++] = r1sv;
	} else {
		m_r[m_n++] = r1;
	}
}

//	実数群の追加
void MgGReal::operator += ( const MgGReal &GR)					// GPt += GI
{
	MINT	nn = m_n + GR.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_r[m_n], GR.m_r, sizeof( MREAL) * GR.m_n);
	m_n = nn;
}

//	整数群の代入
void MgGReal::Set( const MgGInt &GI)							// 整数群→実数群 代入用
{
	MINT	ic;
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	構成実数の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_r, MREAL, nn);								//	構成実数の領域をmallocで確保
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_r[ic] = (MREAL)GI.m_i[ic];
	m_n = nn;
}

//	実数群領域の拡張
void MgGReal::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && r) {											//	構成実数の領域をmallocで確保している場合
	//		MGREALLOC( r, MREAL, szn);							//		構成実数の領域をremallocで拡張
	//	} else {												//	構成実数の領域を未確保または配列の場合
	//		MREAL		*pb = r;
	//		MBMALLOC( r, MREAL, szn);							//		構成実数の領域をmallocで確保
	//		if (!fa) memcpy( r, pb, sizeof( MREAL) * n);		//	構成実数の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MREAL	*rb = m_r;
//E		MBMALLOC( m_r, MREAL, szn);				 				//	構成点の新領域をmallocで確保
		MbAlloc<MREAL>( m_r, szn);
		if ( m_n)
			 memcpy( m_r, rb, m_n * sizeof( MREAL));			//	構成点の領域にデータがあった場合は新領域へコピーする
		if (m_fa && rb)											//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)rb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	トレース
void MgGReal::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGReal	サイズ: %d, 実数の数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d] = %f\n"),
						  ic, m_r[ic]);
		MBLOGPRBF;
	}
#endif
}

//
//======================( ２次元 )==============================
//		点群
//

//	構成点の領域をmallocで確保する場合のコンストラクタ
MgGPoint2D::MgGPoint2D( MINT sz1)
{
	m_tp = MGTP_GPOINT2;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgGPoint2D::MgGPoint2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_GPOINT2;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	構成点を()で指定して読み書きする
const MgPoint2D& MgGPoint2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint2D ()"));
	return m_p[idx];
};

MgPoint2D& MgGPoint2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint2D ()"));
	return m_p[idx];
};

//	複写
void MgGPoint2D::operator = ( const MgGPoint2D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_p, Pg.m_p, sizeof( MgPoint2D) * nn);
	m_n = nn;
}

void MgGPoint2D::operator = (const MgGPoint3D &GPt)				// ３次元→２次元
{
	MINT	ic;
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint2DC( GPt.m_p[ic]);
	m_n = nn;
}

//	構成点の追加
void MgGPoint2D::operator += ( const MgPoint2D& p1)				// GPt += Pt1
{
	MgPoint2D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	点群の追加
void MgGPoint2D::operator += ( const MgGPoint2D &GPt)			// GPt += GPt1
{
	MINT	nn = m_n + GPt.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_p[m_n], GPt.m_p, sizeof( MgPoint2D) * GPt.m_n);
	m_n = nn;
}

//	３次元の点群より２次元の点群を作成
void MgGPoint2D::Set( const MgGPoint3D &GPt)					// ３次元→２次元代入用
{
	MINT	ic;
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint2DC( GPt.m_p[ic]);
	m_n = nn;
}

//	点群領域の拡張
void MgGPoint2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	構成点の領域をmallocで確保している場合
	//		MGREALLOC( p, MgPoint2D, szn);						//		構成点の領域をremallocで拡張
	//	} else {												//	構成点の領域を未確保または配列の場合
	//		MgPoint2D		*pb = p;
	//		MBMALLOC( p, MgPoint2D, szn);						//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint2D) * n);	//	構成点の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint2D*	pb = m_p;
//E		MBMALLOC( m_p, MgPoint2D, szn);			 				//	構成点の新領域をmallocで確保
		MbAlloc<MgPoint2D>( m_p, szn);
		if ( m_n)
			 memcpy( m_p, pb, m_n * sizeof( MgPoint2D));		//	構成点の領域にデータがあった場合は新領域へコピーする
		if ( m_fa && pb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	最大最小を求める
MgMinMaxR2D MgGPoint2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	トレース
void MgGPoint2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
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
//		点群
//

//	構成点の領域をmallocで確保する場合のコンストラクタ
MgGPoint3D::MgGPoint3D( MINT sz1)
{
	m_tp = MGTP_GPOINT3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_p, sz1);
}

//	構成点の領域を配列で与える場合のコンストラクタ
MgGPoint3D::MgGPoint3D( MINT sz1, MgPoint3D *p2)
{
	m_tp = MGTP_GPOINT3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	構成点を()で指定して読み書きする
const MgPoint3D& MgGPoint3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint3D ()"));
	return m_p[idx];
};

MgPoint3D& MgGPoint3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint3D ()"));
	return m_p[idx];
};

//	複写
void MgGPoint3D::operator = ( const MgGPoint3D& GPt)
{
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_p, GPt.m_p, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgGPoint3D::operator = ( const MgGPoint2D& Gpt)
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint3DC( Gpt.m_p[ic]);
	m_n = nn;
}

//	構成点の追加
void MgGPoint3D::operator += ( const MgPoint3D& p1)				// GPt += Pt1
{
	MgPoint3D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// ソースがリサイズする元の領域にあるデータの場合を考慮
		Resize( m_isz + MGMAX( m_isz, 4));
																//	２倍に領域拡張(拡張後の最低領域サイズは４とする)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	点群の追加
void MgGPoint3D::operator += ( const MgGPoint3D &GPt)			// GPt += GPt1
{
	MINT	nn = m_n + GPt.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_p[m_n], GPt.m_p, sizeof( MgPoint3D) * GPt.m_n);
	m_n = nn;
}

//	２次元の点群より３次元の点群を作成
void MgGPoint3D::Set( const MgGPoint2D &Gpt, const MgPlane3D& Pln)	// ２次元→３次元代入用
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic].Set( Gpt.m_p[ic], Pln);
	m_n = nn;
}

void MgGPoint3D::Set( const MgGPoint2D &Gpt, MREAL z)			// ２次元→３次元代入用 (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	構成点の領域をmallocで確保していた場合は一旦free
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	構成点の領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint3D( Gpt.m_p[ic], z);
	m_n = nn;
}

//	点群領域の拡張
void MgGPoint3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	構成点の領域をmallocで確保している場合
	//		MGREALLOC( p, MgPoint3D, szn);						//		構成点の領域をremallocで拡張
	//	} else {												//	構成点の領域を未確保または配列の場合
	//		MgPoint3D	*pb = p;
	//		MBMALLOC( p, MgPoint3D, szn);						//		構成点の領域をmallocで確保
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint3D) * n);	//	構成点の領域が配列であった場合はmalloc領域へコピーする
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint3D	*pb = m_p;
//E		MBMALLOC( m_p, MgPoint3D, szn);							//	構成点の新領域をmallocで確保
		MbAlloc<MgPoint3D>( m_p, szn);
		if ( m_n)
			memcpy( m_p, pb, sizeof( MgPoint3D) * m_n);			//	構成点の領域にデータがあった場合は新領域へコピーする
		if ( m_fa && pb)										//	構成点の領域をmallocで確保していた場合はその領域を開放する
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	最大最小を求める
MgMinMaxR3D MgGPoint3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_p[ic1]);
	}
	return mm;
}

//	トレース
void MgGPoint3D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	サイズ: %d, 頂点数: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f)\n"),
						  ic, m_p[ic].x, m_p[ic].y);
		MBLOGPRBF;
	}
#endif
}

} // namespace MC
