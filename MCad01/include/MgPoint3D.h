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

namespace MC
{

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

//======================( �R���� )==============================
//		�R�����̓_
//
class DLL_EXPORT_POINT MgPoint3D
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
	MgPoint3D()			{}

	// �R�s�[�R���X�g���N�^
	MgPoint3D( MREAL x1, MREAL y2, MREAL z3);
	MgPoint3D( MgPoint2D v1, MREAL z3);
	MgPoint3D( const MgPoint2D& v1, const class MgPlane3D& Pln3);				// �Q�������R����

//	MgPoint3D( const MgVect3D& v1);

	// ���Z
//	MgPoint3D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// �P�ʃx�N�g�������߂�
	MgPoint3D RotR90() const;													// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����_�̈ʒu�����߂�
	MgPoint3D RotL90() const;													// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����_�̈ʒu�����߂�
	MgPoint3D Rot180() const;													// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����_�̈ʒu�����߂�
	MgPoint3D Rot( const MgVect2D& v) const;									// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]�����_�̈ʒu�����߂�
	MgPoint3D Rot( MREAL ang) const;											// Z���𒆐S���Ƃ��Ďw��p�x�ō���]�����_�̈ʒu�����߂�

	// �ϊ�
	MgPoint3D Set( const MgPoint2D& v1, const MgPlane3D& Pln3);					// �Q�������R����
	MgPoint3D SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)�ɕύX����
//	MgPoint3D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// �P�ʃx�N�g���ɕϊ�����
	MgPoint3D& operator = ( const MREAL* pt);
	MgPoint3D SetRotR90();														// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]����
	MgPoint3D SetRotL90();														// Z���𒆐S���Ƃ��č��ɂX�O�x��]����
	MgPoint3D SetRot180();														// Z���𒆐S���Ƃ��ĂP�W�O�x��]����
	MgPoint3D SetRot( const MgVect2D& v);										// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]����
	MgPoint3D SetRot( MREAL ang);												// Z���𒆐S���Ƃ��Ďw��p�x�ō���]����

	// �����l�̎擾
	void Get( MREAL* rP) const;
//S						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgPoint2D To2D() const;//	{ return MgPoint2D( x, y);}						// 3D Point �� 2D Point

	// ���Z�I�y���[�^
	MgPoint3D operator + ( const MgPoint3D& P) const;							// P3 = P1 + p2
	MgPoint3D operator + ( const MgVect3D& V) const;							// P3 = P1 + p2
	MgVect3D operator - ( const MgPoint3D& P) const;							// P3 = P1 - P2
	MgPoint3D operator - ( const MgVect3D& P) const;							// P3 = P1 - P2
	friend	MgPoint3D operator - ( const MgPoint3D& P);							// P1 = - P2
//	MgPoint3D& operator += ( const MgPoint3D& P);								// P1 += P2
	MgPoint3D& operator += ( const MgVect3D& V);								// P1 += V2
	MgPoint3D& operator -= ( const MgPoint3D& P);								// P1 -= P2
	MgPoint3D& operator -= ( const MgVect3D& V);								// P1 -= V2
	friend	MgPoint3D operator * ( MREAL r, const MgPoint3D& P);				// P2 = r * P1
	MgPoint3D operator * (  MREAL r)	const;									// P2 = P1 * r
	MgPoint3D operator / (  MREAL r) const;										// P2 = P1 / r
	MgPoint3D& operator *= ( MREAL r);											// P1 *= r
	MgPoint3D& operator /= ( MREAL r);											// P1 /= r
	MREAL operator * ( const MgPoint3D& P) const;								// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgVect3D& V) const;								// r = P1 * P2 (���� cos)
	MgVect3D operator ^ ( const MgPoint3D& P) const;							// V3 = P1 ^ P2 (�O�� sin)
	bool operator == ( const MgPoint3D& P) const;								// b = (P1 == P2) ����
	bool operator != ( const MgPoint3D& P) const;								// b = (P1 != P2) ����

	// �g���[�X
	void	Print(MCHAR* s) const;
};

//======================( �R���� )==============================
//		�R�����̓_�i�x�N�g���j
//
class DLL_EXPORT_POINT MgVect3D
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
	MgVect3D()			{}

	// �R�s�[�R���X�g���N�^
	MgVect3D( MREAL x1, MREAL y2, MREAL z3);
	MgVect3D( MgVect2D v1, MREAL z3);
	MgVect3D( const class MgLine3D& ln);										// 2D�����̕�����\��2D�x�N�g�������߂�
	MgVect3D( const class MgULine3D& uln);										// 2D�����̕�����\��2D�x�N�g�������߂�
	MgVect3D( const	MgPoint3D& P1, const MgPoint3D& P2);						// �n�_����I�_�����̃x�N�g��

//	MgVect3D( const MgPoint3D& v1);

	// �����l�̐ݒ�

	// �����l�̎擾
	void	Get( MREAL* rP) const;

	// ���Z
	MgVect2D	To2D() const;													// 3D Point �� 2D Point

	MgVect3D Unitize() const;													// �P�ʃx�N�g�������߂�

	MgVect3D RotR90() const;													// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����x�N�g�������߂�
	MgVect3D RotL90() const;													// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����x�N�g�������߂�
	MgVect3D Rot180() const;													// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����x�N�g�������߂�
	MgVect3D Rot( const MgVect2D& v) const;										// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
	MgVect3D Rot( MREAL ang) const;												// Z���𒆐S���Ƃ��Ďw��p�x�ō���]�����_�̈ʒu�����߂�
	MREAL AngleX();																// ������(X����)�ƃx�N�g�������Ƃ̊p�x�����߂� 
	MREAL AngleY();																// ������(Y����)�ƃx�N�g�������Ƃ̊p�x�����߂�
	MREAL AngleZ();																// �����ʂƃx�N�g�������Ƃ̊p�x�����߂�(-��/2�`��/2)
	MREAL Abs();																// �x�N�g���̒���
	MREAL SqAbs();																// �x�N�g���̒����̂Q��

	// �ϊ�
	MgVect3D SetUnitize();														// �P�ʃx�N�g���ɕϊ�����
	MgVect3D& operator = ( const MREAL* pt);
	MgVect3D Set( const MgPoint2D& v1, const MgPlane3D& Pln3);					// �Q�������R����
	MgVect3D SetRotR90();														// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]����
	MgVect3D SetRotL90();														// Z���𒆐S���Ƃ��č��ɂX�O�x��]����
	MgVect3D SetRot180();														// Z���𒆐S���Ƃ��ĂP�W�O�x��]����
	MgVect3D SetRot( const MgVect2D& v);										// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]����
	MgVect3D SetRot( MREAL ang);												// Z���𒆐S���Ƃ��Ďw��p�x�ō���]����
	MgVect2D SetAngleX( MREAL ang);												// ������(X����)����w��p�x�����̒P�ʃx�N�g���ɕϊ����� 
	MgVect2D SetAngleY( MREAL ang);												// ������(Y����)����w��p�x�����̒P�ʃx�N�g���ɕϊ����� 
	MgVect2D SetAngleXZ( MREAL angx, MREAL angz);								// ������(X����)����w��p�xX�����Ő����ʂ���w��p�xZ�����̂̒P�ʃx�N�g���ɕϊ����� 

	// ���Z�I�y���[�^
	MgVect3D operator + ( const MgVect3D& V) const;								// P1 = P2 + p3
	MgVect3D operator - ( const MgVect3D& V) const;								// P1 = P2 - P3
	friend	MgVect3D operator - ( const MgVect3D& V);							// P1 = - P2
	MgVect3D& operator += ( const MgVect3D& V);									// P1 += P2
	MgVect3D& operator -= ( const MgVect3D& V);									// P1 -= P2
	friend	MgVect3D operator * ( MREAL r, const MgVect3D& V);					// P1 = r * P2
	MgVect3D operator * (  MREAL r)	const;										// P1 = P2 * r
	MgVect3D operator / (  MREAL r) const;										// P1 = P2 / r
	MgVect3D& operator *= ( MREAL r);											// P1 *= r
	MgVect3D& operator /= ( MREAL r);											// P1 /= r
	MREAL operator * ( const MgVect3D& V) const;								// r = P1 * P2 (���� cos)
	MREAL operator * ( const MgPoint3D& P) const;								// r = P1 * P2 (���� cos)
	MgVect3D operator ^ ( const MgVect3D& V) const;								// P1 = P2 ^ P3 (�O�� sin)
	bool operator == ( const MgVect3D& V) const;								// b = (P1 == P2) ����
	bool operator != ( const MgVect3D& V) const;								// b = (P1 != P2) ����

	// �g���[�X
	void	Print(MCHAR* s) const;
};

// �T�C�Y
inline int SZMgPoint3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint3D));}
inline int SZMgPoint3D()			{ return  (int)sizeof( MgPoint3D);}
inline int SZMgVect3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect3D));}
inline int SZMgVect3D()				{ return  (int)sizeof( MgVect3D);}
inline int WSZMgPoint3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint3D) / SZMINT());}
inline int WSZMgPoint3D()			{ return  (int)sizeof( MgPoint3D) / SZMINT();}
inline int WSZMgVect3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect3D) / SZMINT());}
inline int WSZMgVect3D()			{ return  (int)sizeof( MgVect3D) / SZMINT();}

} // namespace MC
