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
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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

//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³’¼ü“¯m‚ª“™‚µ‚¢‚©’²‚×‚é
//
bool MgSLine2D::operator == ( const MgSLine2D& SLn1) const						// b = (sln == SLn1) ”»’è
{
	MINT	ist;
	return ( MGeo::CheckPointOnSLine2D( p, SLn1, &ist) &&
			 ( MGeo::CheckEqualVect2D( v,  SLn1.v) || MGeo::CheckEqualVect2D( v, -SLn1.v)));
}

//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³’¼ü‚ğƒgƒŒ[ƒX‚·‚é
//
void MgSLine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgSLine2D	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
								 s, p.x, p.y, v.x, v.y);
	MBLOGPRBF;
#endif
}

//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³”¼’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³”¼’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³”¼’¼ü“¯m‚ª“™‚µ‚¢‚©’²‚×‚é
//
bool MgHLine2D::operator == ( const MgHLine2D &HLn1) const						// b = (sln == SLn1) ”»’è
{
	MINT	ist;
	return ( MGeo::CheckPointOnHLine2D( p, HLn1, &ist) &&
			( MGeo::CheckEqualVect2D( v,  HLn1.v)));
}
//
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³”¼’¼ü‚ğƒgƒŒ[ƒX‚·‚é
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
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³ü•ª“¯m‚ª“™‚µ‚¢‚©’²‚×‚é (‹t•ûŒü‚àŠÜ‚Ş)
//
bool MgLine2D::operator == ( const MgLine2D& Ln1) const							// b = (ln == Ln1) ”»’è
{ 
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( ‚QŸŒ³ )==============================
//		‚QŸŒ³ü•ª‚ğƒgƒŒ[ƒX‚·‚é
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
//======================( ‚RŸŒ³ )==============================
//		’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³’¼ü“¯m‚ª“™‚µ‚¢‚©’²‚×‚é
//
bool MgSLine3D::operator == ( const MgSLine3D& SLn1) const						// b = (sln == SLn1) ”»’è
{
	return ( MGeo::CheckPointOnSLine3D( p, SLn1) &&
			 ( MGeo::CheckEqualVect3D( v,  SLn1.v) || MGeo::CheckEqualVect3D( v, -SLn1.v)));
}

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³’¼ü‚ğƒgƒŒ[ƒX‚·‚é
//
void MgSLine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgSLine3D	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBLOGPRBF;
#endif
}

//======================( ‚RŸŒ³ )==============================
//		”¼’¼ü‚Ì•ûŒü‚ğ’PˆÊƒxƒNƒgƒ‹‚É³‹K‰»‚·‚é
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

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³”¼’¼ü“¯m‚ª“™‚µ‚¢‚©’²‚×‚é
//
bool MgHLine3D::operator == ( const MgHLine3D &HLn1) const						// b = (sln == SLn1) ”»’è
{
	return ( MGeo::CheckPointOnHLine3D( p, HLn1) &&
			( MGeo::CheckEqualVect3D( v,  HLn1.v)));
}

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³”¼’¼ü‚ğƒgƒŒ[ƒX‚·‚é
//
void MgHLine3D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgHLine3D	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBLOGPRBF;
#endif
}

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³ü•ª“¯m‚ª“™‚µ‚¢‚©’²‚×‚é
//
bool MgLine3D::operator == ( const MgLine3D& Ln1) const							// b = (ln == Ln1) ”»’è
{
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}

//======================( ‚RŸŒ³ )==============================
//		‚RŸŒ³ü•ª‚ğƒgƒŒ[ƒX‚·‚é
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
