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
//
//	�x�N�g���Ɛ������̊p�x�����߂�
//
MREAL	MGeo::AngleVectH2D(					// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2D&	v1			// (I  ) �x�N�g��
		)
{
	if ((v1 * v1) < MGPTOL->D_2) return 0.0f;
	
	return MGDEGREE( MREAL( atan2( v1.y, v1.x)));
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�_�Ɛ������̊p�x�����߂�
//
MREAL	MGeo::Angle2PointH2D(					// (  O) ����]�p�x�@�i�x�j
												//		�n�_�A�I�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint2D&	p1,			// (I  ) �n�_
				const	MgPoint2D&	p2			// (I  ) �I�_
		)
{
	MgVect2D v1;
	
	v1 = p2 - p1;
	if ((v1 * v1) < MGPTOL->D_2) return 0.0f;
	
	return MGDEGREE( MREAL( atan2( v1.y, v1.x)));
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x�����߂�
//
MREAL	MGeo::Angle2Vect2D(						// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2D&	v1,			// (I  ) �x�N�g��1
				const	MgVect2D&	v2			// (I  ) �x�N�g��2
		)
{
	MREAL l1, l2;
//	MREAL ss2, s12, c12, ang;
	MREAL s12, c12;
//
	if ((l1 = (v1 * v1)) < MGPTOL->D_2 ||
	    (l2 = (v2 * v2)) < MGPTOL->D_2) return 0.0f;

	s12 = (v1 ^ v2);
	c12 = (v1 * v2);
	
	return MGDEGREE( MREAL( atan2( s12, c12)));
/*
	ss2 = MREAL( sqrt( l1 * l2));
	s12 = (v1 ^ v2) / ss2;
	c12 = (v1 * v2) / ss2;
	if (s12*s12 < 0.5) {
		ang = MREAL( asin( s12)) * MC_RTD;
		if (c12 < 0.) ang = 180.f - ang;
	} else {
		ang = MREAL( acos( c12)) * MC_RTD;
		if (s12 <0.) ang = - ang;
	}
	return ang;
*/
}

/////////////////////////////////////////////////////////////////////////////
//	�R�_�ō����Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle3Point2D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgPoint2D&	p2,			// (I  ) �_2
				const	MgPoint2D&	p3			// (I  ) �_3
		)
{
	MgVect2D	v21, v23;
//
	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect2D(v21, v23);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle2ULine2D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgULine2D&	ULn1,		// (I  ) ����1
				const	MgULine2D&	ULn2		// (I  ) ����2
		)
{
	return Angle2Vect2D(ULn1.v, ULn2.v);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����̊p�x�����߂�
//
MREAL	MGeo::AngleULineLine2D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgULine2D&	ULn1,		// (I  ) ����1
				const	MgLine2D&	Ln2			// (I  ) ����2
		)
{
	MgVect2D	v2;
//
	v2 = Ln2.p[1] - Ln2.p[0];
	return Angle2Vect2D( ULn1.v, v2);
}

//	-------------------------------------------------------
MREAL	MGeo::AngleLineULine2D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgULine2D&	ULn2		// (I  ) ����2
		)
{
	MgVect2D	v1;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	return Angle2Vect2D(v1, ULn2.v);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle2Line2D(						// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgLine2D&	Ln2			// (I  ) ����2
		)
{
	MgVect2D	v1, v2;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	return Angle2Vect2D( v1, v2);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x�����߂�
//
MREAL	MGeo::Angle2Vect3D(						// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	v1,			// (I  ) �x�N�g��1
				const	MgVect3D&	v2,			// (I  ) �x�N�g��2
				const	MgVect3D&	vn			// (I  ) �Q�x�N�g���ɒ�������P�ʃx�N�g��
		)
{
//	MREAL l1, l2;
//	MREAL ss2, s12, c12, ang;
	MREAL s12, c12;
//
	s12 = (v1 ^ v2) * vn;
	c12 = v1 * v2;

	return MGDEGREE( MREAL( atan2( s12, c12)));
/*
	if ((l1 = (v1 * v1)) < MGPTOL->D_2 ||
	    (l2 = (v2 * v2)) < MGPTOL->D_2) return 0.0f;
	ss2 = MREAL(sqrt(l1 * l2));
	s12 = ((v1 ^ v2) * vn) / ss2;
	c12 = (v1 * v2) / ss2;
	if (s12*s12 < 0.5) {
		ang = MREAL(asin(s12)) * MC_RTD;
		if (c12 < 0.) ang = 180.f - ang;
	} else {
		ang = MREAL(acos(c12)) * MC_RTD;
		if (s12 <0.) ang = - ang;
	}
	return ang;
*/
}

/////////////////////////////////////////////////////////////////////////////
//	�R�_�ō����Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle3Point3D(						// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgPoint3D&	p2,			// (I  ) �_2
				const	MgPoint3D&	p3,			// (I  ) �_3
				const	MgVect3D&	vn			// (I  ) �_1,�_,2�_3��ʂ镽�ʂɒ�������P�ʃx�N�g��
		)
{
	MgVect3D	v21, v23;
//
	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect3D( v21, v23, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle2ULine3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �Q�����ɒ�������P�ʃx�N�g��
		)
{
	return Angle2Vect3D( ULn1.v, ULn2.v, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����̊p�x�����߂�
//
MREAL	MGeo::AngleULineLine3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgLine3D&	Ln2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �����Ɛ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3D	v2;
//
	v2 = Ln2.p[1] - Ln2.p[0];
	return Angle2Vect3D( ULn1.v, v2, vn);
}

//	-------------------------------------------------------
MREAL	MGeo::AngleLineULine3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �����ƒ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3D	v1;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	return Angle2Vect3D( v1, ULn2.v, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::Angle2Line3D(						// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgLine3D&	Ln2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �Q�����ɒ��s����P�ʃx�N�g��
		)
{
	MgVect3D	v1, v2;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	return Angle2Vect3D( v1, v2, vn);
}

/////////////////////////////////////////////////////////////////////////////
//		�����@���ʁ@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------
//
//	�x�N�g���ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::AngleVectPln3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3D&	v1,			// (I  ) �x�N�g��1
				const	MgPlane3D&	Pln2		// (I  ) ����2
		)
{
//	MREAL l1;
//	MREAL s12, c12, ang;
	MREAL s12, c12;
//
	if ((v1 * v1) < MGPTOL->D_2) return 0.0f;
	
	c12 = AbsVect3D(v1 ^ Pln2.v);
	s12 = Abs(v1 * Pln2.v);
	
	return MGDEGREE( MREAL( atan2( s12, c12)));
/*
	l1 = MgAbs(v1);
	if (l1 < MGPTOL->D) return 0.0f;
	c12 = MgAbs(v1 ^ Pln2.v) / l1;
	s12 = MgAbs(v1 * Pln2.v) / l1;
	if (s12 < 0.5) {
		ang = MREAL( asin( s12)) * MC_RTD;
	} else {
		ang = MREAL( acos( c12)) * MC_RTD;
	}
	return ang;
*/
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::AngleULinePln3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgPlane3D&	Pln2		// (I  ) ����2
		)
{
	return AngleVectPln3D( ULn1.v, Pln2);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::AngleLinePln3D(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgPlane3D&	Pln2		// (I  ) ����2
		)
{
	MgVect3D	v1;
	v1 = Ln1.p[1] - Ln1.p[0];
	return AngleVectPln3D( v1, Pln2);
}

/////////////////////////////////////////////////////////////////////////////
//		�����@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
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
//
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
void MGeo::BisectorULineLine2D(						// (  O) �X�e�[�^�X
				const	MgULine2D&	ULn1,		// (I  ) ����1
				const	MgLine2D&	Ln2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MgULine2D	ULn2;
//
	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeVect2D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLineULine2D(						// (  O) �X�e�[�^�X
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgULine2D&	ULn2,		// (I  ) ����2
						MgULine2D*	ULn3		// (  O) ����3
		)
{
	MgULine2D	ULn1;
//
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
//
	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeVect2D( Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeVect2D( Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//
// ---------------------( �R���� )------------------------------
//
//	�Q�����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2ULine3D(						// (  O) �X�e�[�^�X
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MREAL	c12;
	MgVect3D vt;
	MgVect3D vp;
	MgVect3D vd;
//
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
void MGeo::BisectorULineLine3D(						// (  O) �X�e�[�^�X
				const	MgULine3D&	ULn1,		// (I  ) ����1
				const	MgLine3D&	Ln2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MgULine3D ULn2;
//
	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeVect3D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLineULine3D(						//
				const	MgLine3D&	Ln1,		// (I  ) ����1
				const	MgULine3D&	ULn2,		// (I  ) ����2
						MgULine3D*	ULn3		// (  O) ����3
		)
{
	MgULine3D ULn1;
//
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
//
	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeVect3D(Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeVect3D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

} // namespace MC
