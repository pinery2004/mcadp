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

class MgVect2D;
class MgVect3D;
class MgPoint2D;
class MgPoint3D;
class MgPlane3D;

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
class DLL_EXPORT_POINT MgPoint2D
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// �R���X�g���N�^/�f�X�g���N�^
	MgPoint2D()			{}

	// �R�s�[�R���X�g���N�^
	MgPoint2D( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgPoint2D( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgPoint2D( const MgPoint3D& pt);

//	MgPoint2D( const MgVect2D& pt);

	// ���Z
//	MgPoint2D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// ���_����_�����̒P�ʃx�N�g�������߂�

	MgPoint2D RotR90() const													// ���_�𒆐S�ɉE�ɂX�O�x��]�����_�̈ʒu�����߂�
						{ return MgPoint2D( y, -x);}
	MgPoint2D RotL90() const													// ���_�𒆐S�ɍ��ɂX�O�x��]�����_�̈ʒu�����߂�
						{ return MgPoint2D( -y, x);}
	MgPoint2D Rot180() const													// ���_�𒆐S�ɂP�W�O�x��]�����_�̈ʒu�����߂�
						{ return MgPoint2D( -x, -y);}
	MgPoint2D Rot( const MgVect2D& v) const;									// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]�����_�̈ʒu�����߂�

	MgPoint2D Rot( MREAL ang);													// ���_�𒆐S�Ɏw��p�x�ō���]�����_�̈ʒu�����߂�

//S	MREAL Ang() const															// ���_����_������X������̔����v�����p�x


	// �ϊ�
//	MgPoint2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// ���_����_�����̒P�ʃx�N�g���ɕϊ�����
	
	MgPoint2D SetRotR90()														// ���_�𒆐S�ɉE�ɂX�O�x��]����
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgPoint2D SetRotL90()														// ���_�𒆐S�ɍ��ɂX�O�x��]����
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgPoint2D SetRot180()														// ���_�𒆐S�ɂP�W�O�x��]����
						{ x = -x; y = -y; return *this;}
	MgPoint2D SetRot( const MgVect2D& v);										// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]����

	MgPoint2D SetRot( MREAL ang);												// ���_�𒆐S�Ɏw��p�x�ō���]����

	// �����l�̎擾
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgPoint2D& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgPoint2D& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// ���Z�I�y���[�^
	MgPoint2D operator + ( const MgPoint2D& v) const;							// p3 = p1 + p2
	MgPoint2D operator + ( const MgVect2D& v) const;							// p3 = p1 + v2

	MgVect2D operator - ( const MgPoint2D& v) const;							// p3 = p1 - p2
	MgPoint2D operator - ( const MgVect2D& v) const;							// p3 = p1 - v2

	friend	MgPoint2D operator - ( const MgPoint2D& p)							// p2 = - p1
				 		{ MgPoint2D vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgPoint2D operator += ( const MgPoint2D& v);								// p1 += p2
	MgPoint2D operator += ( const MgVect2D& v);									// p1 += v2

	MgPoint2D operator -= ( const MgPoint2D& v);								// p1 -= p2
	MgPoint2D operator -= ( const MgVect2D& v);									// p1 -= v2

	friend	MgPoint2D operator * ( MREAL r, const MgPoint2D& v)					// p2 = r * p1
				 		{ MgPoint2D vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgPoint2D operator * ( MREAL r) const;										// p2 = p1 * r

	MgPoint2D operator / ( MREAL r) const;										// p2 = p1 / r

	MgPoint2D operator *= ( MREAL r);											// p1 *= r

	MgPoint2D operator /= ( MREAL r);											// p1 /= r

	MREAL operator * ( const MgPoint2D& v) const;								// r = p1 * p2 (���� cos)
	MREAL operator * ( const MgVect2D& v) const;								// r = p1 * v2 (���� cos)

	MREAL operator ^ ( const MgPoint2D& v) const;								// p3 = p1 ^ p2 (�O�� sin)

	MgPoint2D operator & ( const MgPoint2D& v) const;							// p3 = p1 & p2 (rotation)

	bool operator == (const MgPoint2D& v) const;								// b = (p1 == p2) ����

	bool operator != (const MgPoint2D& v) const;								// b = (p1 != p2) ����


	// �g���[�X
	void Print(MCHAR* s) const;
};
//
//======================( �Q���� )==============================
//		�Q�����̃x�N�g��
//
class DLL_EXPORT_POINT MgVect2D
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// �R���X�g���N�^/�f�X�g���N�^
	MgVect2D()			{}

	// �R�s�[�R���X�g���N�^
	MgVect2D( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgVect2D( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgVect2D( const MgVect3D& pt);

//	MgVect2D( const MgPoint2D& pt);

	// ���Z
	MgVect2D Unitize( MREAL i_tol = MgTol_Dt::D) const;							// �P�ʃx�N�g�������߂�

	MgVect2D RotR90() const														// �E�ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect2D( y, -x);}

	MgVect2D RotL90() const														// ���ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect2D( -y, x);}

	MgVect2D Rot180() const														// �P�W�O�x��]�����x�N�g�������߂�
						{ return MgVect2D( -x, -y);}

	MgVect2D Rot( const MgVect2D& v) const										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgVect2D( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}

	MgVect2D Rot( MREAL ang)													// �w��p�x�ō���]�����x�N�g�������߂�
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  return Rot( v);}

	// �ϊ�
	MgVect2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// �P�ʃx�N�g���ɕϊ�����
	
	MgVect2D SetRotR90()														// �E�ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgVect2D SetRotL90()														// ���ɂX�O�x��]�����x�N�g���ɕϊ�����
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgVect2D SetRot180()														// �P�W�O�x��]�����x�N�g���ɕϊ�����
						{ x = -x; y = -y; return *this;}
	MgVect2D SetRot( const MgVect2D& v)											// �P�ʃx�N�g�������ɉ�]�����x�N�g���ɕϊ�����
//S						{ MgVect2D vt = *this; 
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						{ *this = Rot( v);
						  return *this;}
	MgVect2D SetRot( MREAL ang)													// �w��p�x�ō���]�����x�N�g���ɕϊ�����
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
//S						  MgVect2D vt = *this;
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						  *this = Rot( v);
						  return *this;}

	// �����l�̎擾
	void Get( MREAL* rP) const													// MREAL[2] = v1
						{ rP[0] = x; rP[1] = y;}

	
	MgVect2D& operator = ( const CPoint &pt)									// v1 = CPoint 
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgVect2D& operator = ( const MREAL* pt)										// v1 = MREAL[2]
						{ x = pt[0]; y = pt[1]; return *this;}

	// ���Z�I�y���[�^
	MgVect2D operator + ( const MgVect2D& v) const;								// v3 = v1 + v2

	MgVect2D operator - ( const MgVect2D& v) const;								// v3 = v1 - v2

	friend	MgVect2D operator - ( const MgVect2D& p)							// v2 = - v1
				 		{ MgVect2D vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgVect2D operator += ( const MgVect2D& v);									// v1 += v2

	MgVect2D operator -= ( const MgVect2D& v);									// v1 -= v2

	friend	MgVect2D operator * ( MREAL r, const MgVect2D& v)					// v1 = r * v2
				 		{ MgVect2D vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgVect2D operator * ( MREAL r) const;										// v2 = v1 * r

	MgVect2D operator / ( MREAL r) const;										// v2 = v1 / r

	MgVect2D operator *= ( MREAL r);											// v1 *= r

	MgVect2D operator /= ( MREAL r);											// v1 /= r

	MREAL operator * ( const MgVect2D& v) const;								// r = v1 * v2 (���� cos)
	MREAL operator * ( const MgPoint2D& v) const;								// r = v1 * p2 (���� cos)

	MREAL operator ^ ( const MgVect2D& v) const;								// v3 = P1 ^ P2 (�O�� sin)

	MgVect2D operator & ( const MgVect2D& v) const;								// v3 = v1 & v2 (rotation)

	bool operator == (const MgVect2D& v) const;									// b = (v1 == v2) ����

	bool operator != (const MgVect2D& v) const;									// b = (v1 != v2) ����


	// �g���[�X
	void Print(MCHAR* s) const;
};

// �T�C�Y
inline MINT SZMgPoint2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2D));}
inline MINT SZMgVect2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2D));}
inline MINT WSZMgPoint2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2D) / SZMINT());}
inline MINT WSZMgVect2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2D) / SZMINT());}

} // namespace MC
