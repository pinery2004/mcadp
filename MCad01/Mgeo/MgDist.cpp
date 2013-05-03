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

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

//===========================================================================
//		�_�@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//		�Q�_�Ԃ̋��������߂�B
//
MREAL MGeo::Dist2Pt2(						// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgPoint2D&	p2			// (I  ) �_2
		)
{
	MgVect2D	v1;
	MREAL	pa1;								//	��������_�܂ł̋���
//
	v1 = p1 - p2;
	pa1 = sqrt( v1 * v1);
	return pa1;
}

//===========================================================================
//		�_�@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------
//
//		�Q�_�Ԃ̋��������߂�B
//
MREAL MGeo::Dist2Pt3(						// (  O) �Q�_�Ԃ̋��� >0:���� <0:�E��
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgPoint3D&	p2			// (I  ) �_2
		)
{
	MgVect3D	v1;
	MREAL	pa1;								//	��������_�܂ł̋���
//
	v1 = p1 - p2;
	pa1 = sqrt( v1 * v1);
	return pa1;
}

//===========================================================================
//		�����@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//		��������_�܂ł̐��������t�����������߂�B
//
MREAL MGeo::DistPtULn2(						// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgULine2D&	ULn2		// (I  ) ����2
		)
{
	MgVect2D	v1s2;
	MREAL	pa1;								//	��������_�܂ł̋���
//
	v1s2 = p1 - ULn2.p;
	pa1 = ULn2.v ^ v1s2;
	return pa1;
}
//	------------------------
//		��������_�܂ł̐��������t�����������߂�B(�����Ɠ��l�j
//
MREAL MGeo::DistPtLn2(						// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
												//	�����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgLine2D&	Ln2			// (I  ) ����2
		)
{
	MgVect2D	v2s1;
	MgVect2D	v2;
	MREAL	sz2;								//	����2�̒���
	MREAL	pa1;								//	��������_�܂ł̋���
//
	v2s1 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = Abs(v2);
	if (sz2 < g_gTol.D) return Abs(v2s1);
	pa1 = (v2 ^ v2s1) / sz2;
	return pa1;
}
// ---------------------( �R���� )------------------------------
//		��������_�܂ł̋��������߂�B
//
MREAL MGeo::DistPtULn3(						// (  O) ��������_�܂ł̋���
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgULine3D&	ULn2		// (I  ) ����2
		)
{
	MgVect3D	v21, va1;
	MREAL pa1;									//	��������_�܂ł̋���
//
	v21 = p1 - ULn2.p;
	va1 = v21 ^ ULn2.v;
	pa1 = Abs(va1);
	return pa1;
}
//
//		��������_�܂ł̋��������߂�B(�����Ɠ��l�j
//
MREAL MGeo::DistPtLn3(						// (  O) ��������_�܂ł̋���
												//	�����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgLine3D	&Ln2			// (I  ) ����2
		)
{
	MgVect3D	v21;
	MgVect3D	v2;
	MREAL	sz2;
	MgVect3D va1;
	MREAL pa1;									//	��������_�܂ł̋���
//
	v21 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = Abs(v2);
	if (sz2 < g_gTol.D) return Abs(v21);
	va1 = v21 ^ v2;
	pa1 = Abs(va1) / sz2;
	return pa1;
}
// ---------------------( �R���� )------------------------------
//		��������_�܂ł̐��������t�����������߂�B
//
MREAL MGeo::DistPtULnV3(						// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgULine3D&	ULn2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �_�ƒ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3D	v2s1, va1;
	MREAL pa1;									//	��������_�܂ł̋���
//
	v2s1 = p1 - ULn2.p;
	va1 = ULn2.v ^ v2s1;
	pa1 = va1 * vn;
	return pa1;
}
//
//		��������_�܂ł̐��������t�����������߂�B(�����Ɠ��l�j
//
MREAL MGeo::DistPtLnV3(						// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
												//		 �����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
												//		 �����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgLine3D&	Ln2,		// (I  ) ����2
				const	MgVect3D&	vn			// (I  ) �_�ƒ����ɒ�������P�ʃx�N�g��
		)
{
	MgVect3D	v2s1;
	MgVect3D	v2;
	MREAL	sz2;								//  ����2�̒���
	MgVect3D va1;
	MREAL pa1;									//	�_��������܂ł̋�����0
//
	v2s1 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = Abs(v2);
	if (sz2 < g_gTol.D) return Abs(v2s1);
	va1 = v2 ^ v2s1;
	pa1 = (va1 * vn) / sz2;
	return pa1;
}
// ---------------------( �R���� )------------------------------
//		���ʂ���_�܂ł̐��������t�����������߂�B
//
MREAL MGeo::DistPtPln3(						// (  O) �_���畽�ʂ܂ł̋��� >0:�\���i���ʂ̒P�ʃx�N�g���������j<0:����
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgPlane3D&	Pln2		// (I  ) ����2
		)
{
	MREAL	pa1;								//	�_���畽�ʂ܂ł̋���
//
	pa1 = (p1 * Pln2.v) - Pln2.d;
	return pa1;
}

} // namespace MC
