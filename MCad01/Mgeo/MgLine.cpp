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
MgULine2 MgULine2::SetNorm()
{
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgULine2 SetNorm"));
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
MgULine2 MgULine2::Norm()
{
	MgULine2 uln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgULine2 Norm"));
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
bool MgULine2::operator == ( const MgULine2& ULn1) const							// b = (uln == ULn1) ����
{
	MINT	ist;
	return ( MGeo::ChkPt2OnULn2WS( p, ULn1, &ist) &&
			( MGeo::EqualV( v,  ULn1.v) || MGeo::EqualV( v, -ULn1.v)));
}

//======================( �Q���� )==============================
//		�Q�����������g���[�X����
//
void MgULine2::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgULine2	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
								 s, p.x, p.y, v.x, v.y);
	MBTRCPRBF;
#endif
}

//======================( �Q���� )==============================
//		�Q�����������̕�����P�ʃx�N�g���ɐ��K������
//
/*
MgHLine2 MgHLine2::SetNorm()
{
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgHLine2 SetNorm"));
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
MgHLine2 MgHLine2::Norm()
{
	MgHLine2 uln;
	MREAL	dv = MgAbs( v);
		MGCHECK_ZEROVECTOR( dv, Mstr( "MgHLine2 Norm"));
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
bool MgHLine2::operator == ( const MgHLine2 &HLn1) const							// b = (uln == ULn1) ����
{
	MINT	ist;
	return ( MGeo::ChkPt2OnHLn2WS( p, HLn1, &ist) &&
			( MGeo::EqualV( v,  HLn1.v)));
}
//
//======================( �Q���� )==============================
//		�Q�������������g���[�X����
//
void MgHLine2::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgHLine2	: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
									s, p.x, p.y, v.x, v.y);
	MBTRCPRBF;
#endif
}
//
//======================( �Q���� )==============================
//		�Q�����������m�������������ׂ� (�t�������܂�)
//
bool MgLine2::operator == ( const MgLine2& Ln1) const								// b = (ln == Ln1) ����
{ 
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( �Q���� )==============================
//		�Q�����������g���[�X����
//
void MgLine2::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgLine2		: (%7.1f,%7.1f), (%7.1f,%7.1f)\n"),
									 s, p[0].x, p[0].y, p[1].x, p[1].y);
	MBTRCPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�����̕�����P�ʃx�N�g���ɐ��K������
//
/*
MgULine3 MgULine3::Norm()
{
	MREAL	d1 = MgAbs( v);
		MGCHECK_ZEROVECTOR( d1, Mstr( "MgULine3 Norm"));
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
bool MgULine3::operator == ( const MgULine3& ULn1) const							// b = (uln == ULn1) ����
{
	return ( MGeo::ChkPt3OnULn3( p, ULn1) &&
			( MGeo::EqualV( v,  ULn1.v) || MGeo::EqualV( v, -ULn1.v)));
}
//
//======================( �R���� )==============================
//		�R�����������g���[�X����
//
void MgULine3::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgULine3	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBTRCPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�������̕�����P�ʃx�N�g���ɐ��K������
//
/*
MgHLine3 MgHLine3::Norm()
{
	MREAL	d1 = MgAbs( v);
		MGCHECK_ZEROVECTOR( d1, Mstr( "MgHLine3 Norm"));
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
bool MgHLine3::operator == ( const MgHLine3 &HLn1) const							// b = (uln == ULn1) ����
{
	return ( MGeo::ChkPt3OnHLn3( p, HLn1) &&
			( MGeo::EqualV( v,  HLn1.v)));
}
//
//======================( �R���� )==============================
//		�R�������������g���[�X����
//
void MgHLine3::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgHLine3	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									s, p.x, p.y, p.z, v.x, v.y, v.z);
	MBTRCPRBF;
#endif
}
//
//======================( �R���� )==============================
//		�R�����������m�������������ׂ�
//
bool MgLine3::operator == ( const MgLine3& Ln1) const							// b = (ln == Ln1) ����
{
	return (((p[0] == Ln1.p[0]) && (p[1] == Ln1.p[1])) ||
			((p[0] == Ln1.p[1]) && (p[1] == Ln1.p[0])));
}
//
//======================( �R���� )==============================
//		�R�����������g���[�X����
//
void MgLine3::Print( MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgLine3 	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f)\n"),
									 s, p[0].x, p[0].y, p[0].z, p[1].x, p[1].y, p[1].z);
	MBTRCPRBF;
#endif
}

} // namespace MC