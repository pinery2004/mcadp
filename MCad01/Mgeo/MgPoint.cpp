//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.cpp
//
//		
//
//
//  K.Matsu           13/01/23    Created.
//==========================================================================================
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#include "MgDefine.h"
#include "MgTol.h"
#include "MgAngle.h"

#define DLL_EXPORT_POINT_DO

#include "MgPoint.h"

#define DLL_EXPORT_GEO_DO

#include "MgGeo.h"

namespace MC
{

//
//======================( �Q���� )==============================
//		�x�N�g�����g���[�X����
//
void MgPoint2D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPoint2D	: (%7.1f,%7.1f)\n"), s, x, y);
	MBLOGPRBF;
#endif
}
//
//======================( �Q���� )==============================
//		�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect2D MgVect2D::SetUnitize( MREAL i_Tol)		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::AbsVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D Unitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	return *this;
}
//
//======================( �Q���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2D MgVect2D::Unitize( MREAL i_Tol) const	//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::AbsVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2D(x * d2, y * d2);
}
//
//======================( �Q���� )==============================
//		�x�N�g�����g���[�X����
//
void MgVect2D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgVect2D	: (%7.1f,%7.1f)\n"), s, x, y);
	MBLOGPRBF;
#endif
}
//
//======================( �Q���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2D MGeo::UnitizeVect2D( const MgVect2D& i_v, MREAL i_Tol)		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::AbsVect2D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2D( i_v.x * d2, i_v.y * d2);
}
//
//======================( �R���� )==============================
//
MgVect3D MGeo::TaniVect3D( const MgVect3D& i_v, MREAL i_Tol)
{
	MgVect3D vo;
	MREAL	ax, ay, az;
//
	ax = MGeo::Abs( i_v.x);
	ay = MGeo::Abs( i_v.y);
	az = MGeo::Abs( i_v.z);
	vo.x = vo.y = vo.z = 1.;
//
	if (ax > ay && ax > az)	
		vo.x = - ( i_v.y + i_v.z) / i_v.x;
	else if ( ay >= ax && ay >= az)
		vo.y = - ( i_v.x + i_v.z) / i_v.y;
	else					 
		vo.z = - ( i_v.x + i_v.y) / i_v.z;
//
	return MGeo::UnitizeVect3D( vo, i_Tol);
}
//
//======================( �Q���� )==============================
#ifdef _MgPoint2DA
MgPoint2Da Norma( const MgPoint2D& i_p, MREAL i_Tol)
{
	MREAL	d1 = MgAbs(p);
//A		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint2DA Norma"), i_Tol);
	MREAL	d2 = 1. / d1;
    return MgPoint2Da( i_p.x * d2, i_p.y * d2, d1);
}
#endif
//
//======================( �R���� )==============================
//		�x�N�g�����g���[�X����
//
void MgPoint3D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgPoint3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
	MBLOGPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect3D MgVect3D::SetUnitize( MREAL i_Tol)			//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::AbsVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D Unitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	z *= d2;
	return *this;
}
//
//======================( �R���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect3D MgVect3D::Unitize( MREAL i_Tol) const		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::AbsVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3D( x * d2, y * d2, z * d2);
}
//
//======================( �R���� )==============================
//		�x�N�g�����g���[�X����
//
void MgVect3D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgVect3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
	MBLOGPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect3D MGeo::UnitizeVect3D( const MgVect3D& i_v, MREAL i_Tol)	//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::AbsVect3D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3D( i_v.x * d2, i_v.y * d2, i_v.z * d2);
}
#ifdef _MgPoint3DA


MgPoint3Da Norma( const MgPoint3D& i_p, MREAL i_Tol)
{
	MREAL d1;
/*
	MgPoint3Da p1;
	if(fabs(p.x < i_Tol)) p1.x = 0;	else p1.x = i_p.x;
	if(fabs(p.y < i_Tol)) p1.y = 0;	else p1.y = i_p.y;
	if(fabs(p.z < i_Tol)) p1.z = 0;	else p1.z = i_p.z;
*/
	MREAL	d1= MgAbs( p);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint3Da Norma"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgPoint3Da( i_p.x * d2, i_p.y * d2, i_p.z * d2, d1);
}
#endif

} // namespace MC
