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

//
//===========================================================================
//		�`�󉉎Z
//
////	-------------------------�Q�c�k�h�m�d�E�o�n�h�m�s----------------------
////
////	�_���璼���ւ̐����̑��ʒu�����߂�
////
//void MGeo::PerpSLnPoint2D(
//				const	MgSLine2D&	SLn1,		// (I  ) ����1
//				const	MgPoint2D&	p2,			// (I  ) �_2
//						MgPoint2D*	po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL		pa1;							//	����1�̎n�_���琂���̑��܂ł̋���
//
//	pa1 = (p2 - SLn1.p) * SLn1.v;				//	cos��v12v2
//	*po = SLn1.p + SLn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPoint2D(							// (  O) �X�e�C�^�X(=MC_ON_SLINE	:������,
//												//					=0			:�����͈͊O)
//				const	MgLine2D&	Ln1,		// (I  ) ����1
//				const	MgPoint2D&	p2,			// (I  ) �_2
//						MgPoint2D*	po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MINT		ist;
//	MgPoint2D		vd1, vd2;
//	MREAL		ss, se;
//
//	vd1 = Ln1.p[1] - Ln1.p[0];
//	vd2 = MgRotL90(vd1);
//
//	MgSVal(Ln1.p[0], Ln1.p[1], p2, vd2, &ss, &se);
//
//	*po = Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	��_
//
//	if (ss * se < 0 ||											//	������
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_SLINE;
//	else ist =  0;												//	�����̊O
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPointSLine2D(
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgSLine2D&	SLn2,		// (I  ) ����2
						MgPoint2D*	po			// (  O) �Q������_(�_�̕W���`��)
		)
{
	MgPerpSLnPoint2D(SLn2, p1, po);
}
//	------------------------
MINT MGeo::PerpPointLine2D(							// (  O) �X�e�C�^�X(=MC_ON_SLINE	:������,
												//					=0			:�����͈͊O)
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgLine2D	&Ln2,		// (I  ) ����2
						MgPoint2D*	po			// (  O) �Q������_(�_�̕W���`��)
		)
{
	return MgPerpLnPoint2D(Ln2, p1, po);
}
*/

////
////	-------------------------�R�c�k�h�m�d�E�o�n�h�m�s----------------------
////
////	�_���璼���ւ̐����̑��ʒu�����߂�
////
//void MGeo::PerpSLnPoint3D(
//				const	MgSLine3D&	SLn1,		// (I  ) ����1
//				const	MgPoint3D&	p2,			// (I  ) �_2
//						MgPoint3D	*po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL	pa1;								//	����1�̎n�_���琂���̑��܂ł̋���
//
//	pa1 = (p2 - SLn1.p) * SLn1.v;				//	cos��v12v2
//	*po = SLn1.p + SLn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPoint3D(							// (  O) �X�e�C�^�X(=MC_ON_SLINE	:������,
//												//					=0			:�����͈͊O)
//				const	MgLine3D	&Ln1,		// (I  ) ����1
//				const	MgPoint3D&	p2,			// (I  ) �_2
//				MgPoint3D		*po				// (  O) �R������_(�_�̕W���`��)
//		)
//{
//	MINT		ist;
//	MgPoint3D	vd1, vd2;
//	MREAL		ss, se;
//	MREAL		d;
//
//	vd1 = Ln1.p[1] - Ln1.p[0];
//
//	d  = p2 * vd1;
//	ss = (Ln1.p[0] * vd1) - d;
//	se = (Ln1.p[1] * vd1) - d;
//
//	*po = Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	��_
//
//	if (ss * se < 0 ||											//	������
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_SLINE;
//	else ist = 0;												//	�����̊O
//
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPointLine3D(
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgLine3D	&Ln2,		// (I  ) ����2
						MgPoint3D	*po			// (  O) �R������_(�_�̕W���`��)
		)
{
	MgPerpLnPoint3D(Ln2,	p1, po);
}

//	------------------------
MINT MGeo::PerpPointSLine3D(							// (  O) �X�e�C�^�X(=MC_ON_SLINE	:������,
												//					=0			:�����͈͊O)
				const MgPoint3D& p1,			// (I  ) �_1
				const MgSLine3D& SLn2,			// (I  ) ����2
				MgPoint3D	*po					// (  O) �R������_(�_�̕W���`��)
		)
{
	return MgPerpSLnPoint3D(SLn2, p1, po);
}
*/

////
////	-------------------------�R�c�ʁE�o�n�h�m�s----------------------
////
////	�_����ʂւ̐����̑��ʒu�����߂�
////
//void MGeo::PerpPlnPoint3D(
//				const	MgPlane3D	&Pln1,		// (I  ) ��1
//				const	MgPoint3D&	p2,			// (I  ) �_2
//						MgPoint3D	*po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL	pa1;								//	�_2���琂���̑��܂ł̋���
//
//	pa1 = (p2 * Pln1.v) + Pln1.d;
//	*po = p2 - Pln1.v * pa1;
//}

//	------------------------
/*
void MGeo::PerpPointPln3D(
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgPlane3D	&Pln2,		// (I  ) ��2
						MgPoint3D	*po			// (  O) �R������_(�_�̕W���`��)
		)
{
	MgPerpPlnPoint3D(Pln2, p1, po);
}
*/

} // namespace MC
