//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgSval.cpp
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
//#include "MlLog.h"

#define	DLL_EXPORT_GEO_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"

namespace MC
{

//
//===========================================================================
//		���ʁ@�`�󉉎Z
//
////	------------- �r�l�̎Z�o�@------------------
//MREAL MGeo::SVal2ULine3D(						// (  O) �r�l(�Q�����̕����x�N�g������Ȃ镽�s�U�ʑ̂̑̐ρj
//			    const	MgULine3D&	ULn1,		// (I  ) ����1
//				const	MgULine3D&	ULn2		// (I  ) ����2
//		)
//{
////		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (ULn2.p.z*ULn2.v.w-ULn2.p.w*ULn2.v.z)
////		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (ULn2.p.y*ULn2.v.w-ULn2.p.w*ULn2.v.y)
////		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (ULn2.p.y*ULn2.v.z-ULn2.p.z*ULn2.v.y)
////		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (ULn2.p.x*ULn2.v.w-ULn2.p.w*ULn2.v.x)
////		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (ULn2.p.x*ULn2.v.z-ULn2.p.z*ULn2.v.x)
////		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (ULn2.p.x*ULn2.v.y-ULn2.p.y*ULn2.v.x))
////
//	return
//	(	  (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (-ULn2.v.z)
//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (-ULn2.v.y)
//		+ (-ULn1.v.x) * (ULn2.p.y*ULn2.v.z-ULn2.p.z*ULn2.v.y)
//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (-ULn2.v.x)
//		- (-ULn1.v.y) * (ULn2.p.x*ULn2.v.z-ULn2.p.z*ULn2.v.x)
//		+ (-ULn1.v.z) * (ULn2.p.x*ULn2.v.y-ULn2.p.y*ULn2.v.x));
//}

////
//MREAL MGeo::SValULineLine3D(						// (  O) �r�l(�����̕����x�N�g���Ɛ�������Ȃ镽�s�U�ʑ̂̑̐ρj
//			    const	MgULine3D&	ULn1,		// (I  ) ����1
//				const	MgLine3D&	Ln2			// (I  ) ����2
//		)
//{
////		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
////		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
////		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
////		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
////		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
////		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
////
//	return
//	(	  (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (Ln2.p[0].z-Ln2.p[1].z)
//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (Ln2.p[0].y-Ln2.p[1].y)
//		+ (-ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (Ln2.p[0].x-Ln2.p[1].x)
//		- (-ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
//		+ (-ULn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x));
//}

////
//MREAL MGeo::SVal2Line3D(							// (  O) �r�l(2��������Ȃ镽�s�U�ʑ̂̑̐ρj
//			    const	MgLine3D&	Ln1,		// (I  ) ����1
//				const	MgLine3D&	Ln2			// (I  ) ����2
//		)
//{
////		( (Ln1.p[0].x*Ln1.v.y-Ln1.p[0].y*Ln1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
////		- (Ln1.p[0].x*Ln1.v.z-Ln1.p[0].z*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
////		+ (Ln1.p[0].x*Ln1.v.w-Ln1.p[0].w*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
////		+ (Ln1.p[0].y*Ln1.v.z-Ln1.p[0].z*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
////		- (Ln1.p[0].y*Ln1.v.w-Ln1.p[0].w*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
////		+ (Ln1.p[0].z*Ln1.v.w-Ln1.p[0].w*Ln1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
////
//	return
//	(	  (Ln1.p[0].x*Ln1.p[1].y-Ln1.p[0].y*Ln1.p[1].x) * (Ln2.p[0].z-Ln2.p[1].z)
//		- (Ln1.p[0].x*Ln1.p[1].z-Ln1.p[0].z*Ln1.p[1].x) * (Ln2.p[0].y-Ln2.p[1].y)
//		+ (Ln1.p[0].x-Ln1.p[1].x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
//		+ (Ln1.p[0].y*Ln1.p[1].z-Ln1.p[0].z*Ln1.p[1].y) * (Ln2.p[0].x-Ln2.p[1].x)
//		- (Ln1.p[0].y-Ln1.p[1].y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
//		+ (Ln1.p[0].z-Ln1.p[1].z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x));
//}

////
//void MGeo::SValLnULnS3(						//
//				const	MgLine3D&	Ln1,		// (I  ) ����1
//			    const	MgULine3D&	ULn2,		// (I  ) ����2
//				const	MgVect3D&	vso,		// (I  ) ����1�ƒ���2�����镽�ʂ̖@���x�N�g��
//						MREAL* ss,				// (  O) �����P�̎n�_���r�l
//												//		(����2�̕����x�N�g���ƕ��ʂ̖@���x�N�g����
//												//		 ����1�̎n�_�ŏo���镽�s�U�ʑ̂̑̐�)
//						MREAL* se				// (  O) �����P�̏I�_���r�l
//												//		(����2�̕����x�N�g���ƕ��ʂ̖@���x�N�g����
//												//		 ����1�̏I�_�ŏo���镽�s�U�ʑ̂̑̐�)
//		)
//{
//	MgVect3D		N;							//	�����Q�Ɛ����x�N�g������Ȃ镽�ʂ̌W��
//	MREAL		d;								//	��_���璼��1�̎n�_�܂ł̓����ʂɐ�������
////
//	N = ULn2.v ^ vso;
//	d =  ULn2.p * N;
//	*ss = (Ln1.p[0] * N) - d;
//	*se = (Ln1.p[1] * N) - d;
//}

////
//void MGeo::SVal2Line3D(							//
//			    const MgLine3D& Ln1,			// (I  ) ����1
//				const MgLine3D& Ln2,			// (I  ) ����2
//				const MgVect3D& vso,			// (I  ) ����1�Ɛ���2�����镽�ʂ̖@���x�N�g��
//				MREAL* ss,						// (I  ) �����P�̎n�_���r�l
//												//		(����2�ƕ��ʂ̖@���x�N�g���Ɛ���1�̎n�_��
//												//		 �o���镽�s�U�ʑ̂̑̐�)
//				MREAL* se						// (I  ) �����P�̏I�_���r�l
//												//		(����2�ƕ��ʂ̖@���x�N�g���Ɛ���1�̏I�_��
//												//		 �o���镽�s�U�ʑ̂̑̐�)
//		)
//{
//	MgVect3D	N;								//	�����Q�Ɛ����x�N�g������Ȃ镽�ʂ̌W��
//	MREAL		d;								//	��_���璼��1�̎n�_�܂ł̓����ʂɐ�������
//	MgVect3D	vd;								//	�����Q�̃x�N�g��
////
//	vd = Ln2.p[1] - Ln2.p[0];
//	N = vd ^ vso;
//	d =  Ln2.p[0] * N;
//	*ss = (Ln1.p[0] * N) - d;
//	*se = (Ln1.p[1] * N) - d;
//}

} // namespace MC
