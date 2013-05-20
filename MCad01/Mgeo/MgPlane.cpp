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

#define DLL_EXPORT_GEO_DO
#define DLL_EXPORT_PLANE_DO

#include "MgLib.h"

namespace MC
{

//===========================================================================
//		���� �`�󉉎Z
//

//===========================================================================
//		�R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
//
//	ax+by+cz+d=0
//
MgPlane3D MGeo::Plane3pPoint3D(						// (  O) ���ʎ�
				const	MgPoint3D*	pt			// (I  ) �R�_���W
				)
{
	MgPlane3D	Plno;
	MgVect3D		v1, v2;

	v1 = pt[1] - pt[0];
	v2 = pt[2] - pt[0];

	Plno.v = MGeo::UnitizeVect3D( v1 ^ v2);
	Plno.d = -(Plno.v * pt[0]);
	return Plno;
}

//===========================================================================
//		�R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
//
MgPlane3D MGeo::Plane3Point3D(						// (  O) ���ʎ�
				const	MgPoint3D&	p0,			// (I  ) �_�P
				const	MgPoint3D&	p1,			// (I  ) �_�Q
				const	MgPoint3D&	p2			// (I  ) �_�R
				)
{
	MgPlane3D	Plno;
	MgVect3D		v1, v2;

	v1 = p1 - p0;
	v2 = p2 - p0;

	Plno.v = MGeo::UnitizeVect3D( v1 ^ v2);
	Plno.d = -(Plno.v * p0);
	return Plno;
}

//===========================================================================
//		���p�`��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
//													pkm	�ʐς̐�Βl�̍��v�ŋ��ߕ����͎��ʐςŋ��߂�����ǂ��� pkm
MgPlane3D MGeo::Plane3DPolygon3D(						// (  O) ���ʎ�
				const	MgPolyg3D&	i_Pg		// (I  ) ���p�`
				)
{
	MgPlane3D	Plno;
	MINT		ic0, ic1;
	MgPlane3D	pl;

	MgVect3D vNf = MgVect3D(0.f, 0.f, 0.f);
	ic1 = i_Pg.m_n - 1;
	for ( ic0=0; ic0<i_Pg.m_n; ic0++) {
		vNf += (i_Pg.m_P[ic1] ^ i_Pg.m_P[ic0]);
		ic1 = ic0;
	}
	Plno.v = MGeo::UnitizeVect3D( vNf);
	Plno.d = -(Plno.v * i_Pg.m_P[0]);
	return Plno;
}

//
//===========================================================================
//		�Q�����n�_�ƂQ�����I�_�̂Q�_�A���z�Ƃy���W��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
//
MgPlane3D MGeo::Plane2PointSlope3D(
				const	MgPoint2D&	p1,			// (I  ) �Q�����n�_
				const	MgPoint2D&	p2,			// (I  ) �Q�����I�_
						MREAL		rkb,		// (I  ) ���z	(�n�_����I�_�Ɍ�����������=0 tan)
						MREAL		z			// (I  ) �y���W
				)
{
	MgPlane3D	Plno;
	MgPoint3D	Pt[3];
	MgVect3D		v1, v2;
	MREAL		h1;

	Pt[0] = MgPoint3DC( p1, z);
	Pt[1] = MgPoint3DC( p2, z);
	v1 = Pt[1] - Pt[0];

	Pt[2] = Pt[0] + v1.RotL90();
	h1 = MGeo::LenVect3D( v1) * rkb;
	Pt[2].z += h1;
	v2 = Pt[2] - Pt[0];

	Plno.v = MGeo::UnitizeVect3D( v1 ^ v2);
	Plno.d = -(Plno.v * Pt[0]);
	return Plno;
}

//
//===========================================================================
//		�Q���������A���z�Ƃy���W��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
//
MgPlane3D MGeo::PlaneLineSlope3D(
				const	MgLine2D&	ln1,		// (I  ) �Q��������
						MREAL		rkb,		// (I  ) ���z	(�����̎n�_����I�_�Ɍ�����������=0 tan)
						MREAL		z			// (I  ) �y���W
				)
{
	MgPlane3D	Plno;
	MgPoint3D	Pt[3];
	MgVect3D		v1, v2;
	MREAL		h1;

	Pt[0] = MgPoint3DC( ln1.p[0], z);
	Pt[1] = MgPoint3DC( ln1.p[1], z);
	v1 = Pt[1] - Pt[0];

	Pt[2] = Pt[0] + v1.RotL90();
	h1 = MGeo::LenVect3D( v1) * rkb;
	Pt[2].z += h1;
	v2 = Pt[2] - Pt[0];

	Plno.v = MGeo::UnitizeVect3D( v1 ^ v2);
	Plno.d = -(Plno.v * Pt[0]);
	return Plno;
}

////===========================================================================
////		���ʂ̕������̌W���ƒ萔�𐳋K������(�W��a,b,c��P�ʃx�N�g���ɕϊ�����)
////
//MgPlane3D MgPlane3D::SetNorm( MREAL i_Tol)
//{
//	MgPlane3D	Plno;
//	MREAL	d1 = MgAbs( v);
//		MBCHECK_ZEROVECT( d1, MBCstr("MgPlane3D Norm"). i_Tol);
//	MREAL	d2 = 1.f / d1;
////	v.x *= d2;
////	v.y *= d2;
////	v.z *= d2;
//	v *= d2;
//	d *= d2;
//	return *this;
//}

//===========================================================================
//		���ʂ̕������̌W���ƒ萔�𐳋K������(�W��a,b,c��P�ʃx�N�g���ɕϊ�����)���ʂ����߂�
//
MgPlane3D MgPlane3D::Norm()
{
	MREAL	d1 = MGeo::LenVect3D( v);
		MBCHECK_ZEROVECT( d1, MBCstr("MgPlane3D Norm"));
	MREAL	d2 = 1.f / d1;
	return MgPlane3D(v.x * d2, v.y * d2, v.z * d2, d * d2);
}
//
//===========================================================================
//		���ʂ����������𔻒肷��i���ʂ̕������̌W���ƒ萔�𐳋K������r����j
//
bool MgPlane3D::operator == ( const MgPlane3D& pl) const							// b = (Pl1 == Pl2) ����
{
//	MgPlane3D pl1 = MgNorm( *this);
//	MgPlane3D pl2 = MgNorm( pl); 
//	return (pl1.v == pl2.v) && MFEQUAL( pl1.d, pl2.d, MGPTOL->D);
//	return ( v == pl.v) && MFEQUAL( d, pl.d, MGPTOL->D);
	return ( v == pl.v) && MGeo::Equal( d, pl.d, MGPTOL->D);
}
//
//======================( �R���� )==============================
//		���ʂ��g���[�X����
//
void MgPlane3D::Print(
						MCHAR*		s
				)								// print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPlane3D	: (%7.1f,%7.1f,%7.1f),%7.1f\n"),
								s, v.x, v.y, v.z, d);
	MBLOGPRBF;
#endif
};
//
//===========================================================================
//		���ʂ̕������̌W���ƒ萔�𐳋K������(�W��a,b,c��P�ʃx�N�g���ɕϊ�����)���ʂ����߂�
//
MgPlane3D MGeo::NormPln(
				const	MgPlane3D&	i_pl
//SS						MREAL		i_Tol
				)
{
	MREAL	d1 = MGeo::LenVect3D( i_pl.v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgPlane3D MgNorm"));
	MREAL	d2 = 1.f / d1;
	return MgPlane3D( i_pl.v.x * d2, i_pl.v.y * d2, i_pl.v.z * d2, i_pl.d * d2);
}

} // namespace MC
