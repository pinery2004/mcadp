#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.h
//
//		�_�ƃx�N�g���̒�`�A�ҏW
//
//
//  K.Matsu           13/01/24    Created.
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
//======================( �Q���� )==============================
//		�Q�����̓_
//
class DLL_EXPORT_POINT MgPoint2
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// �R���X�g���N�^/�f�X�g���N�^
	MgPoint2()			{}

	// �R�s�[�R���X�g���N�^
	MgPoint2( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgPoint2( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgPoint2( const MgPoint3& pt);

//	MgPoint2( const MgVect2& pt);

	// �����l�̐ݒ�
	MgPoint2 SetUnitize( MREAL i_tol = MgTol_Dt::D);							// �P�ʃx�N�g���ɕϊ�����
	
	MgPoint2 SetRotR90()														// �E�ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgPoint2 SetRotL90()														// ���ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgPoint2 SetRot180()														// �P�W�O�x��]�����x�N�g���ɕϊ�����
						{ x = -x; y = -y; return *this;}
	MgPoint2 SetRot( const MgPoint2& v)											// �P�ʃx�N�g�������ɉ�]�����x�N�g���ɕϊ�����
						{ MgPoint2 vt = *this; 
						  x = vt.x * v.x -  vt.y * v.y;
						  y = vt.x * v.y +  vt.y * v.x;
						  return *this;}

	// �����l�̎擾
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgPoint2& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgPoint2& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// ���Z�I�y���[�^
	MgPoint2 operator + ( const MgPoint2& v) const;								// P1 = P2 + p3
	MgPoint2 operator + ( const MgVect2& v) const;								// P1 = P2 + p3

	MgVect2 operator - ( const MgPoint2& v) const;								// P1 = P2 - P3
	MgPoint2 operator - ( const MgVect2& v) const;								// P1 = P2 - P3

	friend	MgPoint2 operator - ( const MgPoint2& p)							// P1 = - P2
				 		{ MgPoint2 vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgPoint2 operator += ( const MgPoint2& v);									// P1 += P2
	MgPoint2 operator += ( const MgVect2& v);									// P1 += P2

	MgPoint2 operator -= ( const MgPoint2& v);									// P1 -= P2
	MgPoint2 operator -= ( const MgVect2& v);									// P1 -= P2

	friend	MgPoint2 operator * ( MREAL r, const MgPoint2& v)					// P1 = r * P2
				 		{ MgPoint2 vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgPoint2 operator * ( MREAL r) const;										// P1 = P2 * r

	MgPoint2 operator / ( MREAL r) const;										// P1 = P2 / r

	MgPoint2 operator *= ( MREAL r);											// P1 *= r

	MgPoint2 operator /= ( MREAL r);											// P1 /= r

	MREAL operator * ( const MgPoint2& v) const;								// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgVect2& v) const;									// r = P1 * P2 (���� cos)

	MREAL operator ^ ( const MgPoint2& v) const;								// P1 = P2 ^ P3 (�O�� sin)

	MgPoint2 operator & ( const MgPoint2& v) const;								// P1 = P2 & P3 (rotation)

	bool operator == (const MgPoint2& v) const;									// b = (P1 == P2) ����

	bool operator != (const MgPoint2& v) const;									// b = (P1 != P2) ����

	MgPoint2 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// �P�ʃx�N�g�������߂�

	MgPoint2 RotR90() const;													// �E�ɂX�O�x��]�����x�N�g�������߂�

	MgPoint2 RotL90() const;													// ���ɂX�O�x��]�����x�N�g�������߂�

	MgPoint2 Rot180() const;													// �P�W�O�x��]�����x�N�g�������߂�

	MgPoint2 Rot( const MgPoint2& v) const;										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�

	// �g���[�X
	void Print(MCHAR* s) const;
};
//
//======================( �Q���� )==============================
//		�Q�����̃x�N�g��
//
class DLL_EXPORT_POINT MgVect2
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// �R���X�g���N�^/�f�X�g���N�^
	MgVect2()			{}

	// �R�s�[�R���X�g���N�^
	MgVect2( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgVect2( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgVect2( const MgVect3& pt);

//	MgVect2( const MgPoint2& pt);

	// �����l�̐ݒ�
	MgVect2 SetUnitize( MREAL i_tol = MgTol_Dt::D);								// �P�ʃx�N�g���ɕϊ�����
	
	MgVect2 SetRotR90()															// �E�ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgVect2 SetRotL90()															// ���ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgVect2 SetRot180()															// �P�W�O�x��]�����x�N�g���ɕϊ�����
						{ x = -x; y = -y; return *this;}
	MgVect2 SetRot( const MgVect2& v)											// �P�ʃx�N�g�������ɉ�]�����x�N�g���ɕϊ�����
						{ MgVect2 vt = *this; 
						  x = vt.x * v.x -  vt.y * v.y;
						  y = vt.x * v.y +  vt.y * v.x;
						  return *this;}

	// �����l�̎擾
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgVect2& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgVect2& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// ���Z�I�y���[�^
	MgVect2 operator + ( const MgVect2& v) const;								// P1 = P2 + p3

	MgVect2 operator - ( const MgVect2& v) const;								// P1 = P2 - P3

	friend	MgVect2 operator - ( const MgVect2& p)								// P1 = - P2
				 		{ MgVect2 vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgVect2 operator += ( const MgVect2& v);									// P1 += P2

	MgVect2 operator -= ( const MgVect2& v);									// P1 -= P2

	friend	MgVect2 operator * ( MREAL r, const MgVect2& v)						// P1 = r * P2
				 		{ MgVect2 vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgVect2 operator * ( MREAL r) const;										// P1 = P2 * r

	MgVect2 operator / ( MREAL r) const;										// P1 = P2 / r

	MgVect2 operator *= ( MREAL r);												// P1 *= r

	MgVect2 operator /= ( MREAL r);												// P1 /= r

	MREAL operator * ( const MgVect2& v) const;									// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgPoint2& v) const;								// r = P1 * P2 (���� cos)

	MREAL operator ^ ( const MgVect2& v) const;									// P1 = P2 ^ P3 (�O�� sin)

	MgVect2 operator & ( const MgVect2& v) const;								// P1 = P2 & P3 (rotation)

	bool operator == (const MgVect2& v) const;									// b = (P1 == P2) ����

	bool operator != (const MgVect2& v) const;									// b = (P1 != P2) ����

	MgVect2 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// �P�ʃx�N�g�������߂�

	MgVect2 RotR90() const;														// �E�ɂX�O�x��]�����x�N�g�������߂�

	MgVect2 RotL90() const;														// ���ɂX�O�x��]�����x�N�g�������߂�

	MgVect2 Rot180() const;														// �P�W�O�x��]�����x�N�g�������߂�

	MgVect2 Rot( const MgVect2& v) const;										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�

	// �g���[�X
	void Print(MCHAR* s) const;
};

// �T�C�Y
inline MINT SZMgPoint2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2));}
inline MINT SZMgVect2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2));}
inline MINT WSZMgPoint2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2) / SZMINT());}
inline MINT WSZMgVect2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2) / SZMINT());}

} // namespace MC
