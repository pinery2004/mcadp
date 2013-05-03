#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPlane.h
//
//	[�@�\] 
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

#include "MgLine.h"

class MgPolyg3D;

										// ���p�`�̕��ʂƓ_�̈ʒu�֌W
//#define	MC_UPPER	010				// �_�����ʂ̏㑤	
//#define	MC_ON_PLANE	020				// �_�����ʏ�
//#define	MC_LOWER	040				// �_�����ʂ̉���

//#define	MgcUndef	-999			// ���ݒ���

#include "mdPlex.h"

#ifdef DLL_EXPORT_PLANE
	#undef DLL_EXPORT_PLANE
#endif

#ifdef DLL_EXPORT_PLANE_DO
	#pragma message( "<<< MgPlane�Edll_EXport >>>")
	#define DLL_EXPORT_PLANE							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_PLANE
		#else
//			#pragma message( "=== MgPlane�Edll_IMport ===")
			#define DLL_EXPORT_PLANE						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_PLANE
	#endif
#endif

namespace MC
{

//===========================================================================
//		�R��������
//		( ax + by + cz + d = 0)
//
class DLL_EXPORT_PLANE MgPlane3D
{
public:
	MgVect3D	v;												// ���ʂ̕������̌W�� a, b, c
	MREAL		d;												// �萔 d

public:
	MgPlane3D() 			{}

	MgPlane3D( MREAL pla, MREAL plb, MREAL plc, MREAL pld)
						{ v.x = pla;	v.y = plb;
						  v.z = plc;	d = pld;}
	MgPlane3D( const MgVect3D& v1, MREAL d1)
						{ v.x = v1.x;	v.y = v1.y;
						  v.z = v1.z;	d = d1;}

	MgPlane3D SetNorm( MREAL i_Tol = g_gTol.D);					// �W���𐳋K������	(a,b,c��P�ʃx�N�g���ɕϊ�����)

	MgPlane3D Norm( MREAL i_Tol = g_gTol.D);					// �W���𐳋K���������ʂ𓾂�
																//		(a,b,c��P�ʃx�N�g���ɕϊ������l�����߂�)
	void SetHorizontal()
						{ v.x = 0.;		v.y = 0.;
						  v.z = 1.;		d = 0.;}
	MREAL GetZ( const MgPoint2D p1, MREAL i_Tol = g_gTol.D) const	// �Q�������W�̈ʒu�̂y���W�����߂�
						{ if ( MgTol::MgZero( v.z, i_Tol)) return 0.f;
						  else return - (v.x * p1.x + v.y * p1.y + d) / v.z;}
	bool operator == ( const MgPlane3D& pl) const;				// b = (Pl1 == Pl2) ����

	bool operator != ( const MgPlane3D& pl) const				// b = (Pl1 != Pl2) ����
						{ return !(*this == pl);}

	void Print(MCHAR* s);										// �g���[�X
};

} // namespace MC
