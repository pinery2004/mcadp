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
MREAL	MGeo::GetAngleVH2(					// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2&	v1			// (I  ) �x�N�g��
		)
{
	if ((v1 * v1) < g_gTol.D_2) return 0.0f;
	
	return MGDEGREE( MREAL( atan2( v1.y, v1.x)));
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�_�Ɛ������̊p�x�����߂�
//
MREAL	MGeo::GetAngle2PtH2(					// (  O) ����]�p�x�@�i�x�j
												//		�n�_�A�I�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint2&	p1,			// (I  ) �n�_
				const	MgPoint2&	p2			// (I  ) �I�_
		)
{
	MgVect2 v1;
	
	v1 = p2 - p1;
	if ((v1 * v1) < g_gTol.D_2) return 0.0f;
	
	return MGDEGREE( MREAL( atan2( v1.y, v1.x)));
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x�����߂�
//
MREAL	MGeo::GetAngle2V2(					// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgVect2&	v1,			// (I  ) �x�N�g��1
				const	MgVect2&	v2			// (I  ) �x�N�g��2
		)
{
	MREAL l1, l2;
//	MREAL ss2, s12, c12, ang;
	MREAL s12, c12;
//
	if ((l1 = (v1 * v1)) < g_gTol.D_2 ||
	    (l2 = (v2 * v2)) < g_gTol.D_2) return 0.0f;

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
MREAL	MGeo::GetAngle3Pt2(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint2&	p1,			// (I  ) �_1
				const	MgPoint2&	p2,			// (I  ) �_2
				const	MgPoint2&	p3			// (I  ) �_3
		)
{
	MgVect2	v21, v23;
//
	v21 = p1 - p2;
	v23 = p3 - p2;
	return GetAngle2V2(v21, v23);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::GetAngle2ULn2(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgULine2&	ULn2		// (I  ) ����2
		)
{
	return GetAngle2V2(ULn1.v, ULn2.v);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����̊p�x�����߂�
//
MREAL	MGeo::GetAngleULnLn2(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgLine2&	Ln2			// (I  ) ����2
		)
{
	MgVect2	v2;
//
	v2 = Ln2.p[1] - Ln2.p[0];
	return GetAngle2V2( ULn1.v, v2);
}

//	-------------------------------------------------------
MREAL	MGeo::GetAngleLnULn2(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgULine2&	ULn2		// (I  ) ����2
		)
{
	MgVect2	v1;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	return GetAngle2V2(v1, ULn2.v);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::GetAngle2Ln2(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgLine2&	Ln2			// (I  ) ����2
		)
{
	MgVect2	v1, v2;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	return GetAngle2V2( v1, v2);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�x�N�g���̊p�x�����߂�
//
MREAL	MGeo::GetAngle2V3(					// (  O) ����]�p�x�@�i�x�j
												//		�x�N�g���̒�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3&	v1,			// (I  ) �x�N�g��1
				const	MgVect3&	v2,			// (I  ) �x�N�g��2
				const	MgVect3&	vn			// (I  ) �Q�x�N�g���ɒ�������P�ʃx�N�g��
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
	if ((l1 = (v1 * v1)) < g_gTol.D_2 ||
	    (l2 = (v2 * v2)) < g_gTol.D_2) return 0.0f;
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
MREAL	MGeo::GetAngle3Pt3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgPoint3&	p1,			// (I  ) �_1
				const	MgPoint3&	p2,			// (I  ) �_2
				const	MgPoint3&	p3,			// (I  ) �_3
				const	MgVect3&	vn			// (I  ) �_1,�_,2�_3��ʂ镽�ʂɒ�������P�ʃx�N�g��
		)
{
	MgVect3	v21, v23;
//
	v21 = p1 - p2;
	v23 = p3 - p2;
	return GetAngle2V3( v21, v23, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::GetAngle2ULn3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
				const	MgVect3&	vn			// (I  ) �Q�����ɒ�������P�ʃx�N�g��
		)
{
	return GetAngle2V3( ULn1.v, ULn2.v, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����̊p�x�����߂�
//
MREAL	MGeo::GetAngleULnLn3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgLine3&	Ln2,		// (I  ) ����2
				const	MgVect3&	vn			// (I  ) �����Ɛ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3	v2;
//
	v2 = Ln2.p[1] - Ln2.p[0];
	return GetAngle2V3( ULn1.v, v2, vn);
}

//	-------------------------------------------------------
MREAL	MGeo::GetAngleLnULn3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3&	Ln1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
				const	MgVect3&	vn			// (I  ) �����ƒ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3	v1;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	return GetAngle2V3( v1, ULn2.v, vn);
}

/////////////////////////////////////////////////////////////////////////////
//	�Q�����̊p�x�����߂�
//
MREAL	MGeo::GetAngle2Ln3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3&	Ln1,		// (I  ) ����1
				const	MgLine3&	Ln2,		// (I  ) ����2
				const	MgVect3&	vn			// (I  ) �Q�����ɒ��s����P�ʃx�N�g��
		)
{
	MgVect3	v1, v2;
//
	v1 = Ln1.p[1] - Ln1.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	return GetAngle2V3( v1, v2, vn);
}

/////////////////////////////////////////////////////////////////////////////
//		�����@���ʁ@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------
//
//	�x�N�g���ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::GetAngleVPln3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgVect3&	v1,			// (I  ) �x�N�g��1
				const	MgPlane3&	Pln2		// (I  ) ����2
		)
{
//	MREAL l1;
//	MREAL s12, c12, ang;
	MREAL s12, c12;
//
	if ((v1 * v1) < g_gTol.D_2) return 0.0f;
	
	c12 = Abs(v1 ^ Pln2.v);
	s12 = Abs(v1 * Pln2.v);
	
	return MGDEGREE( MREAL( atan2( s12, c12)));
/*
	l1 = MgAbs(v1);
	if (l1 < g_gTol.D) return 0.0f;
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
MREAL	MGeo::GetAngleULnPln3(				// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgPlane3&	Pln2		// (I  ) ����2
		)
{
	return GetAngleVPln3( ULn1.v, Pln2);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƕ��ʂ̊p�x�����߂�
//
MREAL	MGeo::GetAngleLnPln3(					// (  O) ����]�p�x�@�i�x�j
												//		2�_�Ԃ̋�����g_gTol.D�����̏ꍇ��0�x��Ԃ�
				const	MgLine3&	Ln1,		// (I  ) ����1
				const	MgPlane3&	Pln2		// (I  ) ����2
		)
{
	MgVect3	v1;
	v1 = Ln1.p[1] - Ln1.p[0];
	return GetAngleVPln3( v1, Pln2);
}

/////////////////////////////////////////////////////////////////////////////
//		�����@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//	�Q�����Ԃ̊p��2�����������߂�
//
void	MGeo::Bisector2ULn2(					// (  O) �X�e�[�^�X
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgULine2&	ULn2,		// (I  ) ����2
						MgULine2*	ULn3		// (  O) ����3
		)
{
	MREAL	c12;
	MgVect2 vd;
//
	if ( Intr2ULn2(ULn1, ULn2, &(*ULn3).p) == MC_PARALLEL) (*ULn3).p = ULn1.p;
	c12 = ULn1.v * ULn2.v;
	if ( c12 > -0.7) {
		vd = (ULn1.v + ULn2.v);
	} else {
		vd = RotL90( ULn1.v - ULn2.v);
	}
	(*ULn3).v = MGeo::UnitizeV2(vd);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorULnLn2(					// (  O) �X�e�[�^�X
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MgULine2*	ULn3		// (  O) ����3
		)
{
	MgULine2	ULn2;
//
	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeV2(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULn2( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLnULn2(					// (  O) �X�e�[�^�X
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgULine2&	ULn2,		// (I  ) ����2
						MgULine2*	ULn3		// (  O) ����3
		)
{
	MgULine2	ULn1;
//
	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeV2(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULn2( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2Ln2(						// (  O) �X�e�[�^�X
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MgULine2*	ULn3		// (  O) ����3
		)
{
	MgULine2	ULn1;
	MgULine2	ULn2;
//
	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeV2( Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeV2( Ln2.p[1] - Ln2.p[0]);
	Bisector2ULn2( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//
// ---------------------( �R���� )------------------------------
//
//	�Q�����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2ULn3(						// (  O) �X�e�[�^�X
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
						MgULine3*	ULn3		// (  O) ����3
		)
{
	MREAL	c12;
	MgVect3 vt;
	MgVect3 vp;
	MgVect3 vd;
//
	if ( Intr2ULn3( ULn1, ULn2, &(*ULn3).p) == MC_PARALLEL) (*ULn3).p = ULn1.p;
	c12 = ULn1.v * ULn2.v;
	if ( c12 > -0.7) {
		vd = (ULn1.v + ULn2.v);
	} else {
		vt = (ULn1.v - ULn2.v);
		vp = (ULn1.v ^ ULn2.v);
		vd = vt ^ vp;
	}
	ULn3->v = UnitizeV3( vd);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorULnLn3(					// (  O) �X�e�[�^�X
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgLine3&	Ln2,		// (I  ) ����2
						MgULine3*	ULn3		// (  O) ����3
		)
{
	MgULine3 ULn2;
//
	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeV3(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULn3( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����ƒ����Ԃ̊p��2�����������߂�
//
void MGeo::BisectorLnULn3(					//
				const	MgLine3&	Ln1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
						MgULine3*	ULn3		// (  O) ����3
		)
{
	MgULine3 ULn1;
//
	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeV3(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULn3( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	�����Ɛ����Ԃ̊p��2�����������߂�
//
void MGeo::Bisector2Ln3(						//
				const	MgLine3&	Ln1,		// (I  ) ����1
				const	MgLine3&	Ln2,		// (I  ) ����2
						MgULine3*	ULn3		// (  O) ����3
		)
{
	MgULine3 ULn1;
	MgULine3 ULn2;
//
	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeV3(Ln1.p[1] - Ln1.p[0]);
	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeV3(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULn3( ULn1, ULn2, ULn3);
}

} // namespace MC
