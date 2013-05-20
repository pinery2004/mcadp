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

namespace MC
{

class MgVect2D;
class MgPoint2D;

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
	MgPoint2D( MREAL x1, MREAL y2);
	MgPoint2D( const CPoint& pt);
	MgPoint2D( const class MgPoint3D& pt);											// �R�������Q����

//S	MgPoint2D( const MgVect2D& pt);

	// ���Z
//	MgPoint2D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// ���_����_�����̒P�ʃx�N�g�������߂�
	MgPoint2D RotR90() const;													// ���_�𒆐S�ɉE�ɂX�O�x��]�����_�̈ʒu�����߂�
	MgPoint2D RotL90() const;													// ���_�𒆐S�ɍ��ɂX�O�x��]�����_�̈ʒu�����߂�
	MgPoint2D Rot180() const;													// ���_�𒆐S�ɂP�W�O�x��]�����_�̈ʒu�����߂�
	MgPoint2D Rot( const MgVect2D& v) const;									// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]�����_�̈ʒu�����߂�
	MgPoint2D Rot( MREAL ang);													// ���_�𒆐S�Ɏw��p�x�ō���]�����_�̈ʒu�����߂�

	// �ϊ�
//	MgPoint2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// ���_����_�����̒P�ʃx�N�g���ɕϊ�����
	MgPoint2D SetRotR90();														// ���_�𒆐S�ɉE�ɂX�O�x��]����
	MgPoint2D SetRotL90();														// ���_�𒆐S�ɍ��ɂX�O�x��]����
	MgPoint2D SetRot180();														// ���_�𒆐S�ɂP�W�O�x��]����
	MgPoint2D SetRot( const MgVect2D& v);										// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]����
	MgPoint2D SetRot( MREAL ang);												// ���_�𒆐S�Ɏw��p�x�ō���]����

	// �����l�̎擾
	void Get( MREAL* rP) const;

	// �����l�̐ݒ�
	MgPoint2D& operator = ( const CPoint &pt);
	MgPoint2D& operator = ( const MREAL* pt);

	// ���Z�I�y���[�^
	MgPoint2D operator + ( const MgPoint2D& v) const;							// p3 = p1 + p2
	MgPoint2D operator + ( const MgVect2D& v) const;							// p3 = p1 + v2
	MgVect2D operator - ( const MgPoint2D& v) const;							// v3 = p1 - p2
	MgPoint2D operator - ( const MgVect2D& v) const;							// p3 = p1 - v2
	friend	MgPoint2D operator - ( const MgPoint2D& p);							// p2 = - p1
	MgPoint2D& operator += ( const MgPoint2D& v);								// p1 += p2
	MgPoint2D& operator += ( const MgVect2D& v);								// p1 += v2
	MgPoint2D& operator -= ( const MgPoint2D& v);								// p1 -= p2
	MgPoint2D& operator -= ( const MgVect2D& v);								// p1 -= v2
	friend	MgPoint2D operator * ( MREAL r, const MgPoint2D& v);				// p2 = r * p1
	MgPoint2D operator * ( MREAL r) const;										// p2 = p1 * r
	MgPoint2D operator / ( MREAL r) const;										// p2 = p1 / r
	MgPoint2D& operator *= ( MREAL r);											// p1 *= r
	MgPoint2D& operator /= ( MREAL r);											// p1 /= r
	MREAL operator * ( const MgPoint2D& v) const;								// r = p1 * p2 (���� cos)
	MREAL operator * ( const MgVect2D& v) const;								// r = p1 * v2 (���� cos)
	MREAL operator ^ ( const MgPoint2D& v) const;								// p3 = p1 ^ p2 (�O�� sin)
	MgPoint2D operator & ( const MgPoint2D& v) const;							// p3 = p1 & p2 (rotation)
	bool operator == (const MgPoint2D& v) const;								// b = (p1 == p2) ����
	bool operator != (const MgPoint2D& v) const;								// b = (p1 != p2) ����

	// �g���[�X
	void Print(MCHAR* s) const;
};

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
	MgVect2D( MREAL x1, MREAL y2);												// ������(X,Y)�����̃x�N�g��
	MgVect2D( const CPoint& pt);												// CPoint�̌��_����_�܂ł̕����̃x�N�g��
	MgVect2D( const class MgVect3D& Vt);												// 3D�x�N�g����(X,Y)�����̃x�N�g��
	MgVect2D( const class MgLine2D& ln);										// �����̏I�_����I�_�����̃x�N�g��
	MgVect2D( const class MgULine2D& uln);										// �����̕����x�N�g��
	MgVect2D( const	MgPoint2D& p1, const MgPoint2D& p2);						// �n�_����I�_�����̃x�N�g��

//	MgVect2D( const MgPoint2D& pt);

	// ���Z
	MgVect2D Unitize() const;													// �P�ʃx�N�g�������߂�

	MgVect2D RotR90() const;													// �E�ɂX�O�x��]�����x�N�g�������߂�
	MgVect2D RotL90() const;													// ���ɂX�O�x��]�����x�N�g�������߂�
	MgVect2D Rot180() const;													// �P�W�O�x��]�����x�N�g�������߂�
	MgVect2D Rot( const MgVect2D& v) const;										// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
	MgVect2D Rot( MREAL ang);													// �w��p�x�ō���]�����x�N�g�������߂�
	MREAL AngleX();																// ������(X����)�ƃx�N�g�������Ƃ̊p�x�����߂� 
	MREAL AngleY();																// ������(Y����)�ƃx�N�g�������Ƃ̊p�x�����߂�
	MREAL Abs();																// �x�N�g���̒���
	MREAL SqAbs();																// �x�N�g���̒����̂Q��

	// �ϊ�
	MgVect2D SetUnitize();														// �P�ʃx�N�g���ɕϊ�����
	
	MgVect2D SetRotR90();														// �E�ɂX�O�x��]�����x�N�g���ɕϊ�����
	MgVect2D SetRotL90();														// ���ɂX�O�x��]�����x�N�g���ɕϊ�����
	MgVect2D SetRot180();														// �P�W�O�x��]�����x�N�g���ɕϊ�����
	MgVect2D SetRot( const MgVect2D& v);										// �P�ʃx�N�g�������ɉ�]�����x�N�g���ɕϊ�����
	MgVect2D SetRot( MREAL ang);												// �w��p�x(���W�A��)�ō���]�����x�N�g���ɕϊ�����
	MgVect2D SetAngleX( MREAL ang);												// ������(X����)����w��p�x�����̒P�ʃx�N�g���ɕϊ����� 
	MgVect2D SetAngleY( MREAL ang);												// ������(Y����)����w��p�x�����̒P�ʃx�N�g���ɕϊ����� 

	// �����l�̎擾
	void Get( MREAL* rP) const;													// MREAL[2] = v1

	// �����l�̐ݒ�
	MgVect2D& operator = ( const CPoint &pt);									// v1 = CPoint 
	MgVect2D& operator = ( const MREAL* pt);									// v1 = MREAL[2]


	// ���Z�I�y���[�^
	MgVect2D operator + ( const MgVect2D& v) const;								// v3 = v1 + v2
	MgVect2D operator - ( const MgVect2D& v) const;								// v3 = v1 - v2
	friend	MgVect2D operator - ( const MgVect2D& p);							// v2 = - v1
	MgVect2D& operator += ( const MgVect2D& v);									// v1 += v2
	MgVect2D& operator -= ( const MgVect2D& v);									// v1 -= v2
	friend	MgVect2D operator * ( MREAL r, const MgVect2D& v);					// v1 = r * v2
	MgVect2D operator * ( MREAL r) const;										// v2 = v1 * r
	MgVect2D operator / ( MREAL r) const;										// v2 = v1 / r
	MgVect2D& operator *= ( MREAL r);											// v1 *= r
	MgVect2D& operator /= ( MREAL r);											// v1 /= r
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
inline int SZMgPoint2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint2D));}
inline int SZMgPoint2D()			{ return  (int)sizeof( MgPoint2D);}
inline int SZMgVect2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect2D));}
inline int SZMgVect2D()				{ return  (int)sizeof( MgVect2D);}
inline int WSZMgPoint2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint2D) / SZMINT());}
inline int WSZMgPoint2D()			{ return  (int)sizeof( MgPoint2D) / SZMINT();}
inline int WSZMgVect2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect2D) / SZMINT());}
inline int WSZMgVect2D()			{ return  (int)sizeof( MgVect2D) / SZMINT();}

} // namespace MC
