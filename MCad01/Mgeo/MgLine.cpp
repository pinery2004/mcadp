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
//======================( �Q���� )==============================
//		�Q���������̕�����P�ʃx�N�g���ɐ��K������
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
//======================( �Q���� )==============================
//		�Q���������̕�����P�ʃx�N�g���ɐ��K������
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

//======================( �Q���� )==============================
//		�Q�����������m�������������ׂ�
//
bool MgULine2D::operator == ( const MgULine2D& ULn1) const						// b = (uln == ULn1) ����
{
	MINT	ist;
	return ( MGeo::CheckPointOnULine2DWS( p, ULn1, &ist) &&
			 ( MGeo::CheckEqualVect2D( v,  ULn1.v) || MGeo::CheckEqualVect2D( v, -ULn1.v)));
}

//======================( �Q���� )==============================
//		�Q�����������g���[�X����
//
void MgULine2D::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgULine2D	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
								 s, p.x, p.y, v.x, v.y);
	MBLOGPRBF;
#endif
}

//======================( �Q���� )==============================
//		�Q�����������̕�����P�ʃx�N�g���ɐ��K������
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
//======================( �Q���� )==============================
//		�Q�����������̕�����P�ʃx�N�g���ɐ��K������
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
//======================( �Q���� )==============================
//		�Q�������������m�������������ׂ�
//
bool MgHLine2D::operator == ( const MgHLine2D &HLn1) const						// b = (uln == ULn1) ����
{
	MINT	ist;
	return ( MGeo::CheckPointOnHLine2DWS( p, HLn1, &ist) &&
			( MGeo::CheckEqualVect2D( v,  HLn1.v)));
}
//
//======================( �Q���� )==============================
//		�Q�������������g���[�X����
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
//======================( �Q���� )==============================
//		�Q�����������m�������������ׂ� (�t�������܂�)
//
bool MgLine2D::operator == ( const MgLine2D& Ln1) const							// b = (ln == Ln1) ����
{ 
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( �Q���� )==============================
//		�Q�����������g���[�X����
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
//======================( �R���� )==============================
//		�����̕�����P�ʃx�N�g���ɐ��K������
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
//======================( �R���� )==============================
//		�R�����������m�������������ׂ�
//
bool MgULine3D::operator == ( const MgULine3D& ULn1) const						// b = (uln == ULn1) ����
{
	return ( MGeo::CheckPointOnULine3D( p, ULn1) &&
			 ( MGeo::CheckEqualVect3D( v,  ULn1.v) || MGeo::CheckEqualVect3D( v, -ULn1.v)));
}
//
//======================( �R���� )==============================
//		�R�����������g���[�X����
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
//======================( �R���� )==============================
//		�������̕�����P�ʃx�N�g���ɐ��K������
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
//======================( �R���� )==============================
//		�R�������������m�������������ׂ�
//
bool MgHLine3D::operator == ( const MgHLine3D &HLn1) const						// b = (uln == ULn1) ����
{
	return ( MGeo::CheckPointOnHLine3D( p, HLn1) &&
			( MGeo::CheckEqualVect3D( v,  HLn1.v)));
}
//
//======================( �R���� )==============================
//		�R�������������g���[�X����
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
//======================( �R���� )==============================
//		�R�����������m�������������ׂ�
//
bool MgLine3D::operator == ( const MgLine3D& Ln1) const							// b = (ln == Ln1) ����
{
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( �R���� )==============================
//		�R�����������g���[�X����
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
