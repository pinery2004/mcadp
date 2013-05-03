//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_LINE_DO

#include "MgLib.h"
#include "MgLine.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		２次元直線の方向を単位ベクトルに正規化する
//
/*
MgULine2D MgULine2D::SetNorm()
{
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgULine2D SetNorm"));
	MREAL	dd = 1.f / dv;
	v.x *= dd;
	v.y *= dd;
	return *this;
}
*/
//
//======================( ２次元 )==============================
//		２次元直線の方向を単位ベクトルに正規化する
//
/*
MgULine2D MgULine2D::Norm()
{
	MgULine2D uln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgULine2D Norm"));
	MREAL	dd = 1.f / dv;
	uln.p = p;
	uln.v.x = v.x * dd;
	uln.v.x = v.y * dd;
	return uln;
}
*/

//======================( ２次元 )==============================
//		２次元直線同士が等しいか調べる
//
bool MgULine2D::operator == ( const MgULine2D& ULn1) const							// b = (uln == ULn1) 判定
{
	MINT	ist;
	return ( MGeo::ChkPt2OnULn2WS( p, ULn1, &ist) &&
			( MGeo::EqualV( v,  ULn1.v) || MGeo::EqualV( v, -ULn1.v)));
}

//======================( ２次元 )==============================
//		２次元直線をトレースする
//
void MgULine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgULine2D	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
								 s, p.x, p.y, v.x, v.y);
	MBLOGPRBF;
#endif
}

//======================( ２次元 )==============================
//		２次元半直線の方向を単位ベクトルに正規化する
//
/*
MgHLine2D MgHLine2D::SetNorm()
{
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgHLine2D SetNorm"));
	MREAL	dd = 1.f / dv;
	v.x *= dd;
	v.y *= dd;
	return *this;
}
*/
//
//======================( ２次元 )==============================
//		２次元半直線の方向を単位ベクトルに正規化する
//
/*
MgHLine2D MgHLine2D::Norm()
{
	MgHLine2D uln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgHLine2D Norm"));
	MREAL	dd = 1.f / dv;
	uln.p = p;
	uln.v.x = v.x * dd;
	uln.v.x = v.y * dd;
	return uln;
}
*/
//
//======================( ２次元 )==============================
//		２次元半直線同士が等しいか調べる
//
bool MgHLine2D::operator == ( const MgHLine2D &HLn1) const							// b = (uln == ULn1) 判定
{
	MINT	ist;
	return ( MGeo::ChkPt2OnHLn2WS( p, HLn1, &ist) &&
			( MGeo::EqualV( v,  HLn1.v)));
}
//
//======================( ２次元 )==============================
//		２次元半直線をトレースする
//
void MgHLine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgHLine2D	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
									s, p.x, p.y, v.x, v.y);
	MBLOGPRBF;
#endif
}
//
//======================( ２次元 )==============================
//		２次元線分同士が等しいか調べる (逆方向も含む)
//
bool MgLine2D::operator == ( const MgLine2D& Ln1) const								// b = (ln == Ln1) 判定
{ 
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( ２次元 )==============================
//		２次元線分をトレースする
//
void MgLine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgLine2D		: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
									 s, p[0].x, p[0].y, p[1].x, p[1].y);
	MBLOGPRBF;
#endif
}
//
//======================( ３次元 )==============================
//		直線の方向を単位ベクトルに正規化する
//
/*
MgULine3D MgULine3D::Norm()
{
	MREAL	d1 = MgAbs( v);
		MGCHECK_ZEROVECTOR( d1, Mstr( "MgULine3D Norm"));
	MREAL	d2 = 1.f / d1;
	v.x *= d2;
	v.y *= d2;
	v.z *= d2;
	return *this;
}
*/
//
//======================( ３次元 )==============================
//		３次元直線同士が等しいか調べる
//
bool MgULine3D::operator == ( const MgULine3D& ULn1) const							// b = (uln == ULn1) 判定
{
	return ( MGeo::ChkPt3OnULn3( p, ULn1) &&
			( MGeo::EqualV( v,  ULn1.v) || MGeo::EqualV( v, -ULn1.v)));
}
//
//======================( ３次元 )==============================
//		３次元直線をトレースする
//
void MgULine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgULine3D	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBLOGPRBF;
#endif
}
//
//======================( ３次元 )==============================
//		半直線の方向を単位ベクトルに正規化する
//
/*
MgHLine3D MgHLine3D::Norm()
{
	MREAL	d1 = MgAbs( v);
		MGCHECK_ZEROVECTOR( d1, Mstr( "MgHLine3D Norm"));
	MREAL	d2 = 1.f / d1;
	v.x *= d2;
	v.y *= d2;
	v.z *= d2;
	return *this;
}
*/
//
//======================( ３次元 )==============================
//		３次元半直線同士が等しいか調べる
//
bool MgHLine3D::operator == ( const MgHLine3D &HLn1) const							// b = (uln == ULn1) 判定
{
	return ( MGeo::ChkPt3OnHLn3( p, HLn1) &&
			( MGeo::EqualV( v,  HLn1.v)));
}
//
//======================( ３次元 )==============================
//		３次元半直線をトレースする
//
void MgHLine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgHLine3D	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBLOGPRBF;
#endif
}
//
//======================( ３次元 )==============================
//		３次元線分同士が等しいか調べる
//
bool MgLine3D::operator == ( const MgLine3D& Ln1) const							// b = (ln == Ln1) 判定
{
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( ３次元 )==============================
//		３次元線分をトレースする
//
void MgLine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgLine3D 	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									 s, p[0].x, p[0].y, p[0].z, p[1].x, p[1].y, p[1].z);
	MBLOGPRBF;
#endif
}

} // namespace MC
