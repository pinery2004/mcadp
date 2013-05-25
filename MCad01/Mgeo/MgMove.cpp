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

#include "MgLib.h"

namespace MC
{

/*        inline��
//
//===========================================================================
//		�_�̈ړ��@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
void MGeo::MovePt2InDirOfVt2(					//
				const	MgPoint2D&	p1,			//  (I  ) �ړ��_1
				const	MgVect2D&	v2,			//	(I  ) �ړ������������x�N�g��
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * MGeo::UnitizeVect2D(v2);
}
//	------------------------
void MGeo::MovePt2AlongSLine2D(					//
				const	MgPoint2D&	p1,			//  (I  ) �ړ��_1
				const	MgSLine2D&	SLn2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * SLn2.v;
}
//	------------------------
void MGeo::MovePt2AlongLine2D(						//
				const	MgPoint2D&	p1,			//  (I  ) �ړ��_1
				const	MgLine2D&	Ln2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	MgVect2D	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MGeo::UnitizeVect2D(vd);
	*p3 = p1 + dl * vn;
}
//
// ---------------------( �R���� )------------------------------
//
void MGeo::MovePt3InDirOfVt3(					//
				const	MgPoint3D&	p1,			//  (I  ) �ړ��_1
				const	MgVect3D&	v2,			//	(I  ) �ړ������������x�N�g��
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * MgUnitizeVect3D(v2);
}
//	------------------------
void MGeo::MovePt3AlongSLine3D(					//	(  O) �X�e�C�^�X
				const	MgPoint3D&	p1,			//  (I  ) �ړ��_1
				const	MgSLine3D&	SLn2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * SLn2.v;
}
//	------------------------
void MGeo::MovePt3AlongLine3D(						//	(  O) �X�e�C�^�X
				const	MgPoint3D&	p1,			//  (I  ) �ړ��_1
				const	MgLine3D	&Ln2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3D	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	MgVect3D	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MgUnitizeVect3D(vd);
	*p3 = p1 + dl * vn;
}
//===========================================================================
//		�����̃I�t�Z�b�g�@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//	�������I�t�Z�b�g����B
//
void MGeo::OffsetSLine2D(							//	(  O) �X�e�C�^�X (=1)
				const	MgSLine2D&	SLn1,		//	(I  ) ����1
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgSLine2D 	*SLn2		//	(  O) �I�t�Z�b�g���ꂽ����2
		)
{

	SLn2->p = SLn1.p + dl * MgRotL90(SLn1.v);
	SLn2->v = SLn1.v;
}
//	------------------------
void MGeo::OffsetLine2D(							//	(  O) �X�e�C�^�X
				const	MgLine2D&	Ln1,		//	(I  ) ����1
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgLine2D	*Ln2		//	(  O) �I�t�Z�b�g���ꂽ����2
		)
{
	MgVect2D	vd, vn;
//
	vd = Ln1.p[1] - Ln1.p[0];
	vn = MGeo::UnitizeVect2D(vd);
	Ln2->p[0] = Ln1.p[0] + dl * MgRotL90(vn);
	Ln2->p[1] = Ln2->p[0] + vd;
}
//
// ---------------------( �R���� )------------------------------
//
void MGeo::OffsetSLine3D(							//	(  O) �X�e�C�^�X
				const	MgSLine3D&	SLn1,		//	(I  ) ����1
				const	MgPlane3D	&Pln2,		//	(I  ) ����1����镽��2
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgSLine3D	*SLn3		//	(  O) �I�t�Z�b�g���ꂽ����3
		)
{
	SLn3->p = SLn1.p + dl * (Pln2.v ^ SLn1.v);
	SLn3->v = SLn1.v;
}
//	------------------------
void MGeo::OffsetLine3D(							//	(  O) �X�e�C�^�X
				const	MgLine3D	&Ln1,		//	(I  ) ����1
				const	MgPlane3D	&Pln2,		//	(I  ) ����1����镽��2
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgLine3D	*Ln3		//	(  O) �I�t�Z�b�g���ꂽ����3
		)
{
	MgVect3D	vd, vn;
//
	vd = Ln1.p[1] - Ln1.p[0];
	vn = MgUnitizeVect3D(vd);
	MgVect3D vv = vn ^ Pln2.v;
	Ln3->p[0] = Ln1.p[0] + dl * (Pln2.v ^ vn);
	Ln3->p[1] = Ln3->p[0] + vd;
}
*/

} // namespace MC
