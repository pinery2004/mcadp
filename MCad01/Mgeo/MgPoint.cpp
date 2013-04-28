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
//		�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect2 MgVect2::SetUnitize( MREAL i_Tol)		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::Abs( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2 Unitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	return *this;
}
//
//======================( �Q���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2 MgVect2::Unitize( MREAL i_Tol) const	//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::Abs( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2 MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2(x * d2, y * d2);
}
//
//======================( �Q���� )==============================
//		�x�N�g�����g���[�X����
//
void MgVect2::Print(MCHAR* s) const				// Print
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPoint2	: (%7.1f,%7.1f)\n"), s, x, y);
	MBLOGPRBF;
#endif
}
//
//======================( �Q���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2 MGeo::UnitizeV2( const MgVect2& i_v, MREAL i_Tol)		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::Abs( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2 MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2( i_v.x * d2, i_v.y * d2);
}
//
//======================( �R���� )==============================
//
MgVect3 MGeo::TaniV3( const MgVect3& i_v, MREAL i_Tol)
{
	MgVect3 vo;
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
	return MGeo::UnitizeV3( vo, i_Tol);
}
//
//======================( �Q���� )==============================
#ifdef _MgPoint2A
MgPoint2a Norma( const MgPoint2& i_p, MREAL i_Tol)
{
	MREAL	d1 = MgAbs(p);
//A		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint2A Norma"), i_Tol);
	MREAL	d2 = 1. / d1;
    return MgPoint2a( i_p.x * d2, i_p.y * d2, d1);
}
#endif
//
//======================( �R���� )==============================
//		�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect3 MgVect3::SetUnitize( MREAL i_Tol)		//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::Abs( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3 Unitize"), i_Tol);
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
MgVect3 MgVect3::Unitize( MREAL i_Tol) const				//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::Abs( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2 MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3( x * d2, y * d2, z * d2);
}
//
//======================( �R���� )==============================
//		�x�N�g�����g���[�X����
//
void MgVect3::Print(MCHAR* s) const				// Print
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgPoint3	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
	MBLOGPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect3 MGeo::UnitizeV3( const MgVect3& i_v, MREAL i_Tol)	//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::Abs( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3 MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3( i_v.x * d2, i_v.y * d2, i_v.z * d2);
}
#ifdef _MgPoint3A


MgPoint3a Norma( const MgPoint3& i_p, MREAL i_Tol)
{
	MREAL d1;
/*
	MgPoint3a p1;
	if(fabs(p.x < i_Tol)) p1.x = 0;	else p1.x = i_p.x;
	if(fabs(p.y < i_Tol)) p1.y = 0;	else p1.y = i_p.y;
	if(fabs(p.z < i_Tol)) p1.z = 0;	else p1.z = i_p.z;
*/
	MREAL	d1= MgAbs( p);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint3a Norma"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgPoint3a( i_p.x * d2, i_p.y * d2, i_p.z * d2, d1);
}
#endif

} // namespace MC
