#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.h
//
//		�_�܂��̓x�N�g���̒�`�A�ҏW
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "MgAngle.h"

namespace MC
{

class MgVect2;
class MgVect3;
class MgPoint2;
class MgPoint3;
class MgPlane3;

//#include "mdPlex.h"

#ifdef DLL_EXPORT_POINT
	#undef DLL_EXPORT_POINT
#endif

#ifdef DLL_EXPORT_POINT_DO
	#pragma message( "<<< MgPoint�Edll_EXport >>>")
	#define DLL_EXPORT_POINT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
//			#pragma message( "=== MgPoint�Edll ===")
			#define DLL_EXPORT_POINT
		#else
//			#pragma message( "=== MgPoint�Edll_IMport ===")
			#define DLL_EXPORT_POINT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_POINT
	#endif
#endif

//
//======================( �R���� )==============================
//		�R�����̓_
//
class DLL_EXPORT_POINT MgPoint3
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;
	MREAL z;

public:
// �R���X�g���N�^
	MgPoint3()			{}

	// �R�s�[�R���X�g���N�^
	MgPoint3( MREAL x1, MREAL y2, MREAL z3)
						{ x = x1; y = y2; z = z3;}
	MgPoint3( MgPoint2 v1, MREAL z3)
						{ x = v1.x; y = v1.y; z = z3;}
	MgPoint3( const MgPoint2& v1, const MgPlane3& Pln3);						// �Q�������R����

//	MgPoint3( const MgVect3& v1);

	// �����l�̐ݒ�
	MgPoint3 Set( const MgPoint2& v1, const MgPlane3& Pln3);					// �Q�������R����

	MgPoint3 SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)�ɕύX����
	MgPoint3 SetUnitize( MREAL i_tol = MgTol_Dt::D);							// �P�ʃx�N�g���ɕϊ�����

	MgPoint3& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; z = pt[2]; return *this;}

	// �����l�̎擾
	void	Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgPoint2	To2D() const	{ return MgPoint2( x, y);}						// 3D Point �� 2D Point

	// ���Z�I�y���[�^
	MgPoint3 operator + ( const MgPoint3& v) const;								// P1 = P2 + p3
	MgPoint3 operator + ( const MgVect3& v) const;								// P1 = P2 + p3

	MgVect3 operator - ( const MgPoint3& p) const;								// P1 = P2 - P3
	MgPoint3 operator - ( const MgVect3& p) const;								// P1 = P2 - P3

	friend	MgPoint3 operator - ( const MgPoint3& v)							// P1 = - P2
				 		{ MgPoint3 Vto; Vto.x =-v.x; Vto.y = -v.y;
						  Vto.z = -v.z; return Vto;}
	MgPoint3 operator += ( const MgPoint3& v);									// P1 += P2
	MgPoint3 operator += ( const MgVect3& v);									// P1 += P2

	MgPoint3 operator -= ( const MgPoint3& v);									// P1 -= P2
	MgPoint3 operator -= ( const MgVect3& v);									// P1 -= P2

	friend	MgPoint3 operator * ( MREAL r, const MgPoint3& v)					// P1 = r * P2
				 		{ MgPoint3 Vto; Vto.x =r * v.x; Vto.y = r * v.y;
						  Vto.z = r * v.z; return Vto;}
	MgPoint3 operator * (  MREAL r)	const;										// P1 = P2 * r

	MgPoint3 operator / (  MREAL r) const;										// P1 = P2 / r

	MgPoint3 operator *= ( MREAL r);											// P1 *= r

	MgPoint3 operator /= ( MREAL r);											// P1 /= r

	MREAL operator * ( const MgPoint3& v) const;								// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgVect3& v) const;									// r = P1 * P2 (���� cos)

	MgVect3 operator ^ ( const MgPoint3& v) const;								// P1 = P2 ^ P3 (�O�� sin)

	bool operator == ( const MgPoint3& v) const;								// b = (P1 == P2) ����

	bool operator != ( const MgPoint3& v) const;								// b = (P1 != P2) ����

	MgPoint3 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// �P�ʃx�N�g�������߂�

	MgPoint3 RotR90() const;													// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����x�N�g�������߂�

	MgPoint3 RotL90() const;													// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����x�N�g�������߂�

	MgPoint3 Rot180() const;													// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����x�N�g�������߂�

	MgPoint3 Rot( const MgVect2& v) const;										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�

	// �g���[�X
	void	Print(MCHAR* s) const;
};

//
//======================( �R���� )==============================
//		�R�����̓_�i�x�N�g���j
//
class DLL_EXPORT_POINT MgVect3
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;
	MREAL z;

public:
// �R���X�g���N�^/�f�X�g���N�^
	MgVect3()			{}

	// �R�s�[�R���X�g���N�^
	MgVect3( MREAL x1, MREAL y2, MREAL z3)
						{ x = x1; y = y2; z = z3;}
	MgVect3( MgVect2 v1, MREAL z3)
						{ x = v1.x; y = v1.y; z = z3;}
//	MgVect3( const MgPoint3& v1);


	// �����l�̐ݒ�
//	MgVect3 Set( const MgPoint2& v1, const MgPlane3& Pln3);						// �Q�������R����

	MgVect3 SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)�ɕύX����
	MgVect3 SetUnitize( MREAL i_tol = MgTol_Dt::D);								// �P�ʃx�N�g���ɕϊ�����

	MgVect3& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; z = pt[2]; return *this;}

	// �����l�̎擾
	void	Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgVect2	To2D() const	{ return MgVect2( x, y);}							// 3D Point �� 2D Point

	// ���Z�I�y���[�^
	MgVect3 operator + ( const MgVect3& v) const;								// P1 = P2 + p3

	MgVect3 operator - ( const MgVect3& p) const;								// P1 = P2 - P3

	friend	MgVect3 operator - ( const MgVect3& v)								// P1 = - P2
				 		{ MgVect3 Vto; Vto.x =-v.x; Vto.y = -v.y;
						  Vto.z = -v.z; return Vto;}
	MgVect3 operator += ( const MgVect3& v);									// P1 += P2

	MgVect3 operator -= ( const MgVect3& v);									// P1 -= P2

	friend	MgVect3 operator * ( MREAL r, const MgVect3& v)						// P1 = r * P2
				 		{ MgVect3 Vto; Vto.x =r * v.x; Vto.y = r * v.y;
						  Vto.z = r * v.z; return Vto;}
	MgVect3 operator * (  MREAL r)	const;										// P1 = P2 * r

	MgVect3 operator / (  MREAL r) const;										// P1 = P2 / r

	MgVect3 operator *= ( MREAL r);												// P1 *= r

	MgVect3 operator /= ( MREAL r);												// P1 /= r

	MREAL operator * ( const MgVect3& v) const;									// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgPoint3& v) const;								// r = P1 * P2 (���� cos)

	MgVect3 operator ^ ( const MgVect3& v) const;								// P1 = P2 ^ P3 (�O�� sin)

	bool operator == ( const MgVect3& v) const;									// b = (P1 == P2) ����

	bool operator != ( const MgVect3& v) const;									// b = (P1 != P2) ����

	MgVect3 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// �P�ʃx�N�g�������߂�

	MgVect3 RotR90() const;														// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����x�N�g�������߂�

	MgVect3 RotL90() const;														// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����x�N�g�������߂�

	MgVect3 Rot180() const;														// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����x�N�g�������߂�

	MgVect3 Rot( const MgVect2& v) const;										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�

	// �g���[�X
	void	Print(MCHAR* s) const;
};

// �T�C�Y
inline MINT SZMgPoint3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint3));}
inline MINT SZMgVect3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect3));}
inline MINT WSZMgPoint3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint3) / SZMINT());}
inline MINT WSZMgVect3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect3) / SZMINT());}

} // namespace MC