//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgAngle.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//		�����@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	������(X����)����x�N�g���܂ł̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::AngleXVect2D(						// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2D&	v1			// (I  ) �x�N�g��
		)
{
	if ((v1 * v1) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	
	return MREAL( atan2( v1.y, v1.x));
}

/////////////////////////////////////////////////////////////////////////////
//	������(Y����)����x�N�g���܂ł̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::AngleYVect2D(						// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2D&	i_v1		// (I  ) �x�N�g��
		)
{
	if ((i_v1 * i_v1) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	
	return MREAL( atan2( - i_v1.x, i_v1.y));
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::Angle2Vect2D(						// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2D&	v1,			// (I  ) �x�N�g��1
				const	MgVect2D&	v2			// (I  ) �x�N�g��2
		)
{
	MREAL l1, l2;
	MREAL s12, c12;

	if ((l1 = (v1 * v1)) < MGPTOL->D_2 ||
	    (l2 = (v2 * v2)) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();

	s12 = (v1 ^ v2);
	c12 = (v1 * v2);
	
	return MREAL( atan2( s12, c12));

}

/////////////////////////////////////////////////////////////////////////////
//	�R�_�ō����Q�����̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::Angle3Point2D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgPoint2D&	p2,			// (I  ) �_2
				const	MgPoint2D&	p3			// (I  ) �_3
		)
{
	MgVect2D	v21, v23;

	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect2D(v21, v23);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::Angle2Vect3D(						// (  O) �\���猩�������v�����̉�]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	v1,			// (I  ) �x�N�g��1
				const	MgVect3D&	v2,			// (I  ) �x�N�g��2
				const	MgVect3D&	vn			// (I  ) �Q�x�N�g���ɒ�������P�ʃx�N�g�� (�\��������)
		)
{
	MREAL s12, c12;

	s12 = (v1 ^ v2) * vn;
	c12 = v1 * v2;

	return MREAL( atan2( s12, c12));
}

/////////////////////////////////////////////////////////////////////////////
//	�R�_�ō����Q�����̊p�x(���W�A��)�����߂�
//
MREAL	MGeo::Angle3Point3D(					// (  O) �\���猩�������v�����̉�]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgPoint3D&	p2,			// (I  ) �_2
				const	MgPoint3D&	p3,			// (I  ) �_3
				const	MgVect3D&	vn			// (I  ) �_1,�_,2�_3��ʂ镽�ʂɒ�������P�ʃx�N�g�� (�\��������)
		)
{
	MgVect3D	v21, v23;

	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect3D( v21, v23, vn);
}

/////////////////////////////////////////////////////////////////////////////
//		�����@���ʁ@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	�x�N�g���ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::AngleVectPln3D(					// (  O) ��]�p�x�@�i���W�A���j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	v1,			// (I  ) �x�N�g��1
				const	MgPlane3D&	Pln2		// (I  ) ����2
		)
{
	MREAL s12, c12;

	if ((v1 * v1) < MGPTOL->D_2) return 0.0f;
	
	c12 = LenVect3D(v1 ^ Pln2.v);
	s12 = v1 * Pln2.v;
	
	return MREAL( atan2( s12, c12));
}

/////////////////////////////////////////////////////////////////////////////
//	�x�N�g����XY���ʂ̊p�x�����߂�
//
MREAL MGeo::AngleVectXYPln3D(					// (  O) �p�x�@�i���W�A���j Z��������
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.x * i_v1.x + i_v1.y  * i_v1.y;
	if ((rL_2 + i_v1.z * i_v1.z) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.z, rL));
}

/////////////////////////////////////////////////////////////////////////////
//	�x�N�g����YZ���ʂ̊p�x�����߂�
//
MREAL MGeo::AngleVectYZPln3D(					// (  O) �p�x�@�i���W�A���j X��������
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.y * i_v1.y + i_v1.z  * i_v1.z;
	if ((rL_2 + i_v1.x * i_v1.x) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.x, rL));
}

/////////////////////////////////////////////////////////////////////////////
//	�x�N�g����ZX���ʂ̊p�x�����߂�
//
MREAL MGeo:: AngleVectZXPln3D(					// (  O) �p�x�@�i���W�A���j Y��������
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.z * i_v1.z + i_v1.x  * i_v1.x;
	if ((rL_2 + i_v1.y * i_v1.y) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.y, rL));
}

//S /////////////////////////////////////////////////////////////////////////////
////	�����ƕ��ʂ̊p�x(���W�A��)�����߂�
////
//MREAL	MGeo::AngleULinePln3D(					// (  O) ����]�p�x�@�i�x�j
//												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
//				const	MgULine3D&	ULn1,		// (I  ) ����1
//				const	MgPlane3D&	Pln2		// (I  ) ����2
//		)
//{
//	return AngleVectPln3D( ULn1.v, Pln2);
//}
//
///////////////////////////////////////////////////////////////////////////////
////	�����ƕ��ʂ̊p�x(���W�A��)�����߂�
////
//MREAL	MGeo::AngleLinePln3D(					// (  O) ����]�p�x�@�i�x�j
//												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
//				const	MgLine3D&	Ln1,		// (I  ) ����1
//				const	MgPlane3D&	Pln2		// (I  ) ����2
//		)
//{
//	MgVect3D	v1;
//	v1 = Ln1.p[1] - Ln1.p[0];
//	return AngleVectPln3D( v1, Pln2);
//}

/////////////////////////////////////////////////////////////////////////////
//		�����@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	�Q�����Ԃ̊p��2�����������߂�
//
void	MGeo::Bisector2ULine2D(					// (  O) �X�e�[�^�X
				const	MgULine2D&	ULn1,		// (I  ) ����1
				const	MgULine2D&	ULn2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MREAL	c12;
	MgVect2D vd;

	if ( Intr2ULine2D(ULn1, ULn2, &(*ULn3).p) == MC_PARALLEL) (*ULn3).p = ULn1.p;
	c12 = ULn1.v * ULn2.v;
	if ( c12 > -0.7) {
		vd = (ULn1.v + ULn2.v);
	} else {
		vd = RotL90Vect2D( ULn1.v - ULn2.v);
	}
	(*ULn3).v = MGeo::UnitizeVect2D(vd);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorULineLine2D(					// (  O) �X�e�[�^�X
				const	MgULine2D&	ULn1,		// (I  ) ����1
				const	MgLine2D&	Ln2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MgULine2D	ULn2;

	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeVect2D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLineULine2D(					// (  O) �X�e�[�^�X
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgULine2D&	ULn2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MgULine2D	ULn1;

	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeVect2D(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2Line2D(						// (  O) �X�e�[�^�X
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgLine2D&	Ln2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MgULine2D	ULn1;
	MgULine2D	ULn2;

	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeVect2D( Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeVect2D( Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//
// ---------------------( �R���� )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	�Q�����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2ULine3D(					// (  O) �X�e�[�^�X
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MREAL	c12;
	MgVect3D vt;
	MgVect3D vp;
	MgVect3D vd;

	if ( Intr2ULine3D( ULn1, ULn2, &(*ULn3).p) == MC_PARALLEL) (*ULn3).p = ULn1.p;
	c12 = ULn1.v * ULn2.v;
	if ( c12 > -0.7) {
		vd = (ULn1.v + ULn2.v);
	} else {
		vt = (ULn1.v - ULn2.v);
		vp = (ULn1.v ^ ULn2.v);
		vd = vt ^ vp;
	}
	ULn3->v = UnitizeVect3D( vd);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorULineLine3D(					// (  O) �X�e�[�^�X
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgLine3D&	Ln2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MgULine3D ULn2;

	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeVect3D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLineULine3D(					//
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MgULine3D ULn1;

	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeVect3D(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2Line3D(						//
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgLine3D&	Ln2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MgULine3D ULn1;
	MgULine3D ULn2;

	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeVect3D(Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeVect3D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

} // namespace MC
