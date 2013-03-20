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
//void MGeo::PerpULnPt2(
//				const	MgULine2&	ULn1,		// (I  ) ����1
//				const	MgPoint2&	p2,			// (I  ) �_2
//						MgPoint2*	po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL		pa1;							//	����1�̎n�_���琂���̑��܂ł̋���
//
//	pa1 = (p2 - ULn1.p) * ULn1.v;				//	cos��v12v2
//	*po = ULn1.p + ULn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPt2(						// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
//												//					=0			:�����͈͊O)
//				const	MgLine2&	Ln1,		// (I  ) ����1
//				const	MgPoint2&	p2,			// (I  ) �_2
//						MgPoint2*	po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MINT		ist;
//	MgPoint2		vd1, vd2;
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
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_LINE;
//	else ist =  0;												//	�����̊O
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPtULn2(
				const	MgPoint2&	p1,			// (I  ) �_1
				const	MgULine2&	ULn2,		// (I  ) ����2
						MgPoint2*	po			// (  O) �Q������_(�_�̕W���`��)
		)
{
	MgPerpULnPt2(ULn2, p1, po);
}
//	------------------------
MINT MGeo::PerpPtLn2(							// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
												//					=0			:�����͈͊O)
				const	MgPoint2&	p1,			// (I  ) �_1
				const	MgLine2		&Ln2,		// (I  ) ����2
						MgPoint2*	po			// (  O) �Q������_(�_�̕W���`��)
		)
{
	return MgPerpLnPt2(Ln2, p1, po);
}
*/

////
////	-------------------------�R�c�k�h�m�d�E�o�n�h�m�s----------------------
////
////	�_���璼���ւ̐����̑��ʒu�����߂�
////
//void MGeo::PerpULnPt3(
//				const	MgULine3&	ULn1,		// (I  ) ����1
//				const	MgPoint3&	p2,			// (I  ) �_2
//						MgPoint3	*po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL	pa1;								//	����1�̎n�_���琂���̑��܂ł̋���
//
//	pa1 = (p2 - ULn1.p) * ULn1.v;		//	cos��v12v2
//	*po = ULn1.p + ULn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPt3(						// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
//												//					=0			:�����͈͊O)
//				const	MgLine3		&Ln1,		// (I  ) ����1
//				const	MgPoint3&	p2,			// (I  ) �_2
//				MgPoint3		*po				// (  O) �R������_(�_�̕W���`��)
//		)
//{
//	MINT		ist;
//	MgPoint3	vd1, vd2;
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
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_LINE;
//	else ist = 0;												//	�����̊O
//
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPtLn3(
				const	MgPoint3&	p1,			// (I  ) �_1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
		)
{
	MgPerpLnPt3(Ln2,	p1, po);
}

//	------------------------
MINT MGeo::PerpPtULn3(						// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
												//					=0			:�����͈͊O)
				const MgPoint3& p1,				// (I  ) �_1
				const MgULine3& ULn2,			// (I  ) ����2
				MgPoint3	*po					// (  O) �R������_(�_�̕W���`��)
		)
{
	return MgPerpULnPt3(ULn2, p1, po);
}
*/

////
////	-------------------------�R�c�ʁE�o�n�h�m�s----------------------
////
////	�_����ʂւ̐����̑��ʒu�����߂�
////
//void MGeo::PerpPlnPt3(
//				const	MgPlane3	&Pln1,		// (I  ) ��1
//				const	MgPoint3&	p2,			// (I  ) �_2
//						MgPoint3	*po			// (  O) �_���璼���ւ̐����̑�
//		)
//{
//	MREAL	pa1;								//	�_2���琂���̑��܂ł̋���
//
//	pa1 = (p2 * Pln1.v) + Pln1.d;
//	*po = p2 - Pln1.v * pa1;
//}

//	------------------------
/*
void MGeo::PerpPtPln3(
				const	MgPoint3&	p1,			// (I  ) �_1
				const	MgPlane3	&Pln2,		// (I  ) ��2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
		)
{
	MgPerpPlnPt3(Pln2, p1, po);
}
*/

} // namespace MC