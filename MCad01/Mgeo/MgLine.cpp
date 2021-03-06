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
MgSLine2D MgSLine2D::SetNorm()
{
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgSLine2D SetNorm"));
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
MgSLine2D MgSLine2D::Norm()
{
	MgSLine2D sln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgSLine2D Norm"));
	MREAL	dd = 1.f / dv;
	sln.p = p;
	sln.v.x = v.x * dd;
	sln.v.x = v.y * dd;
	return sln;
}
*/

//======================( ２次元 )==============================
//		２次元直線同士が等しいか調べる
//
bool MgSLine2D::operator == ( const MgSLine2D& SLn1) const						// b = (sln == SLn1) 判定
{
	MINT	ist;
	return ( MGeo::CheckPointOnSLine2D( p, SLn1, &ist) &&
			 ( MGeo::CheckEqualVect2D( v,  SLn1.v) || MGeo::CheckEqualVect2D( v, -SLn1.v)));
}

//======================( ２次元 )==============================
//		２次元直線をトレースする
//
void MgSLine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgSLine2D	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
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
	MgHLine2D sln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgHLine2D Norm"));
	MREAL	dd = 1.f / dv;
	sln.p = p;
	sln.v.x = v.x * dd;
	sln.v.x = v.y * dd;
	return sln;
}
*/
//
//======================( ２次元 )==============================
//		２次元半直線同士が等しいか調べる
//
bool MgHLine2D::operator == ( const MgHLine2D &HLn1) const						// b = (sln == SLn1) 判定
{
	MINT	ist;
	return ( MGeo::CheckPointOnHLine2D( p, HLn1, &ist) &&
			( MGeo::CheckEqualVect2D( v,  HLn1.v)));
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
bool MgLine2D::operator == ( const MgLine2D& Ln1) const							// b = (ln == Ln1) 判定
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
MgSLine3D MgSLine3D::Norm()
{
	MREAL	d1 = MgAbs( v);
		MGCHECK_ZEROVECTOR( d1, Mstr( "MgSLine3D Norm"));
	MREAL	d2 = 1.f / d1;
	v.x *= d2;
	v.y *= d2;
	v.z *= d2;
	return *this;
}
*/

//======================( ３次元 )==============================
//		３次元直線同士が等しいか調べる
//
bool MgSLine3D::operator == ( const MgSLine3D& SLn1) const						// b = (sln == SLn1) 判定
{
	return ( MGeo::CheckPointOnSLine3D( p, SLn1) &&
			 ( MGeo::CheckEqualVect3D( v,  SLn1.v) || MGeo::CheckEqualVect3D( v, -SLn1.v)));
}

//======================( ３次元 )==============================
//		３次元直線をトレースする
//
void MgSLine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgSLine3D	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBLOGPRBF;
#endif
}

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

//======================( ３次元 )==============================
//		３次元半直線同士が等しいか調べる
//
bool MgHLine3D::operator == ( const MgHLine3D &HLn1) const						// b = (sln == SLn1) 判定
{
	return ( MGeo::CheckPointOnHLine3D( p, HLn1) &&
			( MGeo::CheckEqualVect3D( v,  HLn1.v)));
}

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

//======================( ３次元 )==============================
//		３次元線分同士が等しいか調べる
//
bool MgLine3D::operator == ( const MgLine3D& Ln1) const							// b = (ln == Ln1) 判定
{
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}

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
