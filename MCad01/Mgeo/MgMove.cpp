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
				const	MgPoint2&	p1,			//  (I  ) �ړ��_1
				const	MgVect2&	v2,			//	(I  ) �ړ������������x�N�g��
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * MGeo::UnitizeV2(v2);
}
//	------------------------
void MGeo::MovePt2AlongULn2(					//
				const	MgPoint2&	p1,			//  (I  ) �ړ��_1
				const	MgULine2&	ULn2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * ULn2.v;
}
//	------------------------
void MGeo::MovePt2AlongLn2(					//
				const	MgPoint2&	p1,			//  (I  ) �ړ��_1
				const	MgLine2&	Ln2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint2	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	MgVect2	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MGeo::UnitizeV2(vd);
	*p3 = p1 + dl * vn;
}
//
// ---------------------( �R���� )------------------------------
//
void MGeo::MovePt3InDirOfVt3(					//
				const	MgPoint3&	p1,			//  (I  ) �ړ��_1
				const	MgVect3&	v2,			//	(I  ) �ړ������������x�N�g��
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * MgUnitizeV3(v2);
}
//	------------------------
void MGeo::MovePt3AlongULn3(					//	(  O) �X�e�C�^�X
				const	MgPoint3&	p1,			//  (I  ) �ړ��_1
				const	MgULine3&	ULn2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	*p3 = p1 + dl * ULn2.v;
}
//	------------------------
void MGeo::MovePt3AlongLn3(					//	(  O) �X�e�C�^�X
				const	MgPoint3&	p1,			//  (I  ) �ړ��_1
				const	MgLine3		&Ln2,		//	(I  ) �ړ���������������2
						MREAL		dl,			//	(I  ) �ړ�����
						MgPoint3	*p3			//	(  O) �ړ����ꂽ�_3
		)
{
	MgVect3	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MgUnitizeV3(vd);
	*p3 = p1 + dl * vn;
}
//===========================================================================
//		�����̃I�t�Z�b�g�@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//	�������I�t�Z�b�g����B
//
void MGeo::OffsetULn2(						//	(  O) �X�e�C�^�X (=1)
				const	MgULine2&	ULn1,		//	(I  ) ����1
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgULine2 	*ULn2		//	(  O) �I�t�Z�b�g���ꂽ����2
		)
{

	ULn2->p = ULn1.p + dl * MgRotL90(ULn1.v);
	ULn2->v = ULn1.v;
}
//	------------------------
void MGeo::OffsetLn2(							//	(  O) �X�e�C�^�X
				const	MgLine2&	Ln1,		//	(I  ) ����1
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgLine2		*Ln2		//	(  O) �I�t�Z�b�g���ꂽ����2
		)
{
	MgVect2	vd, vn;
//
	vd = Ln1.p[1] - Ln1.p[0];
	vn = MGeo::UnitizeV2(vd);
	Ln2->p[0] = Ln1.p[0] + dl * MgRotL90(vn);
	Ln2->p[1] = Ln2->p[0] + vd;
}
//
// ---------------------( �R���� )------------------------------
//
void MGeo::OffsetULn3(						//	(  O) �X�e�C�^�X
				const	MgULine3&	ULn1,		//	(I  ) ����1
				const	MgPlane3	&Pln2,		//	(I  ) ����1����镽��2
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgULine3	*ULn3		//	(  O) �I�t�Z�b�g���ꂽ����3
		)
{
	ULn3->p = ULn1.p + dl * (Pln2.v ^ ULn1.v);
	ULn3->v = ULn1.v;
}
//	------------------------
void MGeo::OffsetLn3(							//	(  O) �X�e�C�^�X
				const	MgLine3		&Ln1,		//	(I  ) ����1
				const	MgPlane3	&Pln2,		//	(I  ) ����1����镽��2
						MREAL		dl,			//	(I  ) �I�t�Z�b�g��
						MgLine3		*Ln3		//	(  O) �I�t�Z�b�g���ꂽ����3
		)
{
	MgVect3	vd, vn;
//
	vd = Ln1.p[1] - Ln1.p[0];
	vn = MgUnitizeV3(vd);
	MgVect3 vv = vn ^ Pln2.v;
	Ln3->p[0] = Ln1.p[0] + dl * (Pln2.v ^ vn);
	Ln3->p[1] = Ln3->p[0] + vd;
}
*/

} // namespace MC
