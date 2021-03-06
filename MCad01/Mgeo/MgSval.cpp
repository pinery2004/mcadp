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
//		共通　形状演算
//
////	------------- Ｓ値の算出　------------------
//MREAL MGeo::SVal2SLine3D(						// (  O) Ｓ値(２直線の方向ベクトルからなる平行６面体の体積）
//			    const	MgSLine3D&	SLn1,		// (I  ) 直線1
//				const	MgSLine3D&	SLn2		// (I  ) 直線2
//		)
//{
////		( (SLn1.p.x*SLn1.v.y-SLn1.p.y*SLn1.v.x) * (SLn2.p.z*SLn2.v.w-SLn2.p.w*SLn2.v.z)
////		- (SLn1.p.x*SLn1.v.z-SLn1.p.z*SLn1.v.x) * (SLn2.p.y*SLn2.v.w-SLn2.p.w*SLn2.v.y)
////		+ (SLn1.p.x*SLn1.v.w-SLn1.p.w*SLn1.v.x) * (SLn2.p.y*SLn2.v.z-SLn2.p.z*SLn2.v.y)
////		+ (SLn1.p.y*SLn1.v.z-SLn1.p.z*SLn1.v.y) * (SLn2.p.x*SLn2.v.w-SLn2.p.w*SLn2.v.x)
////		- (SLn1.p.y*SLn1.v.w-SLn1.p.w*SLn1.v.y) * (SLn2.p.x*SLn2.v.z-SLn2.p.z*SLn2.v.x)
////		+ (SLn1.p.z*SLn1.v.w-SLn1.p.w*SLn1.v.z) * (SLn2.p.x*SLn2.v.y-SLn2.p.y*SLn2.v.x))
////
//	return
//	(	  (SLn1.p.x*SLn1.v.y-SLn1.p.y*SLn1.v.x) * (-SLn2.v.z)
//		- (SLn1.p.x*SLn1.v.z-SLn1.p.z*SLn1.v.x) * (-SLn2.v.y)
//		+ (-SLn1.v.x) * (SLn2.p.y*SLn2.v.z-SLn2.p.z*SLn2.v.y)
//		+ (SLn1.p.y*SLn1.v.z-SLn1.p.z*SLn1.v.y) * (-SLn2.v.x)
//		- (-SLn1.v.y) * (SLn2.p.x*SLn2.v.z-SLn2.p.z*SLn2.v.x)
//		+ (-SLn1.v.z) * (SLn2.p.x*SLn2.v.y-SLn2.p.y*SLn2.v.x));
//}

////
//MREAL MGeo::SValSLineLine3D(						// (  O) Ｓ値(直線の方向ベクトルと線分からなる平行６面体の体積）
//			    const	MgSLine3D&	SLn1,		// (I  ) 直線1
//				const	MgLine3D&	Ln2			// (I  ) 線分2
//		)
//{
////		( (SLn1.p.x*SLn1.v.y-SLn1.p.y*SLn1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
////		- (SLn1.p.x*SLn1.v.z-SLn1.p.z*SLn1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
////		+ (SLn1.p.x*SLn1.v.w-SLn1.p.w*SLn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
////		+ (SLn1.p.y*SLn1.v.z-SLn1.p.z*SLn1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
////		- (SLn1.p.y*SLn1.v.w-SLn1.p.w*SLn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
////		+ (SLn1.p.z*SLn1.v.w-SLn1.p.w*SLn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
////
//	return
//	(	  (SLn1.p.x*SLn1.v.y-SLn1.p.y*SLn1.v.x) * (Ln2.p[0].z-Ln2.p[1].z)
//		- (SLn1.p.x*SLn1.v.z-SLn1.p.z*SLn1.v.x) * (Ln2.p[0].y-Ln2.p[1].y)
//		+ (-SLn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
//		+ (SLn1.p.y*SLn1.v.z-SLn1.p.z*SLn1.v.y) * (Ln2.p[0].x-Ln2.p[1].x)
//		- (-SLn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
//		+ (-SLn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x));
//}

////
//MREAL MGeo::SVal2Line3D(							// (  O) Ｓ値(2線分からなる平行６面体の体積）
//			    const	MgLine3D&	Ln1,		// (I  ) 線分1
//				const	MgLine3D&	Ln2			// (I  ) 線分2
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
//void MGeo::SValLnSLnS3(						//
//				const	MgLine3D&	Ln1,		// (I  ) 線分1
//			    const	MgSLine3D&	SLn2,		// (I  ) 直線2
//				const	MgVect3D&	vso,		// (I  ) 線分1と直線2がある平面の法線ベクトル
//						MREAL* ss,				// (  O) 線分１の始点側Ｓ値
//												//		(直線2の方向ベクトルと平面の法線ベクトルと
//												//		 線分1の始点で出来る平行６面体の体積)
//						MREAL* se				// (  O) 線分１の終点側Ｓ値
//												//		(直線2の方向ベクトルと平面の法線ベクトルと
//												//		 線分1の終点で出来る平行６面体の体積)
//		)
//{
//	MgVect3D		N;							//	直線２と垂直ベクトルからなる平面の係数
//	MREAL		d;								//	基準点から直線1の始点までの同平面に垂直距離
////
//	N = SLn2.v ^ vso;
//	d =  SLn2.p * N;
//	*ss = (Ln1.p[0] * N) - d;
//	*se = (Ln1.p[1] * N) - d;
//}

////
//void MGeo::SVal2Line3D(							//
//			    const MgLine3D& Ln1,			// (I  ) 線分1
//				const MgLine3D& Ln2,			// (I  ) 線分2
//				const MgVect3D& vso,			// (I  ) 線分1と線分2がある平面の法線ベクトル
//				MREAL* ss,						// (I  ) 線分１の始点側Ｓ値
//												//		(線分2と平面の法線ベクトルと線分1の始点で
//												//		 出来る平行６面体の体積)
//				MREAL* se						// (I  ) 線分１の終点側Ｓ値
//												//		(直線2と平面の法線ベクトルと線分1の終点で
//												//		 出来る平行６面体の体積)
//		)
//{
//	MgVect3D	N;								//	直線２と垂直ベクトルからなる平面の係数
//	MREAL		d;								//	基準点から直線1の始点までの同平面に垂直距離
//	MgVect3D	vd;								//	線分２のベクトル
////
//	vd = Ln2.p[1] - Ln2.p[0];
//	N = vd ^ vso;
//	d =  Ln2.p[0] * N;
//	*ss = (Ln1.p[0] * N) - d;
//	*se = (Ln1.p[1] * N) - d;
//}

} // namespace MC
