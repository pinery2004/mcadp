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
//		直線　形状演算
//
// ---------------------( ２次元 )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	水平線(X方向)からベクトルまでの角度(ラジアン)を求める
//
MREAL	MGeo::AngleXVect2D(						// (  O) 左回転角度　（度）
												//		ベクトルの長さがMGPTOL->D未満の場合は0度を返す
				const	MgVect2D&	v1			// (I  ) ベクトル
		)
{
	if ((v1 * v1) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	
	return MREAL( atan2( v1.y, v1.x));
}

/////////////////////////////////////////////////////////////////////////////
//	垂直線(Y方向)からベクトルまでの角度(ラジアン)を求める
//
MREAL	MGeo::AngleYVect2D(						// (  O) 左回転角度　（度）
												//		ベクトルの長さがMGPTOL->D未満の場合は0度を返す
				const	MgVect2D&	i_v1		// (I  ) ベクトル
		)
{
	if ((i_v1 * i_v1) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	
	return MREAL( atan2( - i_v1.x, i_v1.y));
}

/////////////////////////////////////////////////////////////////////////////
//	２ベクトルの角度(ラジアン)を求める
//
MREAL	MGeo::Angle2Vect2D(						// (  O) 左回転角度　（度）
												//		ベクトルの長さがMGPTOL->D未満の場合は0度を返す
				const	MgVect2D&	v1,			// (I  ) ベクトル1
				const	MgVect2D&	v2			// (I  ) ベクトル2
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
//	３点で作られる２線分の角度(ラジアン)を求める
//
MREAL	MGeo::Angle3Point2D(					// (  O) 左回転角度　（度）
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgPoint2D&	p2,			// (I  ) 点2
				const	MgPoint2D&	p3			// (I  ) 点3
		)
{
	MgVect2D	v21, v23;

	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect2D(v21, v23);
}

/////////////////////////////////////////////////////////////////////////////
//	２ベクトルの角度(ラジアン)を求める
//
MREAL	MGeo::Angle2Vect3D(						// (  O) 表から見た半時計方向の回転角度　（度）
												//		ベクトルの長さがMGPTOL->D未満の場合は0度を返す
				const	MgVect3D&	v1,			// (I  ) ベクトル1
				const	MgVect3D&	v2,			// (I  ) ベクトル2
				const	MgVect3D&	vn			// (I  ) ２ベクトルに直交する単位ベクトル (表方向判定)
		)
{
	MREAL s12, c12;

	s12 = (v1 ^ v2) * vn;
	c12 = v1 * v2;

	return MREAL( atan2( s12, c12));
}

/////////////////////////////////////////////////////////////////////////////
//	３点で作られる２線分の角度(ラジアン)を求める
//
MREAL	MGeo::Angle3Point3D(					// (  O) 表から見た半時計方向の回転角度　（度）
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgPoint3D&	p2,			// (I  ) 点2
				const	MgPoint3D&	p3,			// (I  ) 点3
				const	MgVect3D&	vn			// (I  ) 点1,点,2点3を通る平面に直交する単位ベクトル (表方向判定)
		)
{
	MgVect3D	v21, v23;

	v21 = p1 - p2;
	v23 = p3 - p2;
	return Angle2Vect3D( v21, v23, vn);
}

/////////////////////////////////////////////////////////////////////////////
//		直線　平面　形状演算
//
// ---------------------( ３次元 )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	ベクトルと平面の角度を求める
//
MREAL	MGeo::AngleVectPln3D(					// (  O) 回転角度　（ラジアン）
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgVect3D&	v1,			// (I  ) ベクトル1
				const	MgPlane3D&	Pln2		// (I  ) 平面2
		)
{
	MREAL s12, c12;

	if ((v1 * v1) < MGPTOL->D_2) return 0.0f;
	
	c12 = LenVect3D(v1 ^ Pln2.v);
	s12 = v1 * Pln2.v;
	
	return MREAL( atan2( s12, c12));
}

/////////////////////////////////////////////////////////////////////////////
//	ベクトルとXY平面の角度を求める
//
MREAL MGeo::AngleVectXYPln3D(					// (  O) 角度　（ラジアン） Z方向が正
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgVect3D&	i_v1		// (I  ) ベクトル1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.x * i_v1.x + i_v1.y  * i_v1.y;
	if ((rL_2 + i_v1.z * i_v1.z) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.z, rL));
}

/////////////////////////////////////////////////////////////////////////////
//	ベクトルとYZ平面の角度を求める
//
MREAL MGeo::AngleVectYZPln3D(					// (  O) 角度　（ラジアン） X方向が正
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgVect3D&	i_v1		// (I  ) ベクトル1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.y * i_v1.y + i_v1.z  * i_v1.z;
	if ((rL_2 + i_v1.x * i_v1.x) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.x, rL));
}

/////////////////////////////////////////////////////////////////////////////
//	ベクトルとZX平面の角度を求める
//
MREAL MGeo:: AngleVectZXPln3D(					// (  O) 角度　（ラジアン） Y方向が正
												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
				const	MgVect3D&	i_v1		// (I  ) ベクトル1
		)
{
	MREAL rL, rL_2;

	rL_2 = i_v1.z * i_v1.z + i_v1.x  * i_v1.x;
	if ((rL_2 + i_v1.y * i_v1.y) < MGPTOL->D_2) return 0.0f;

	rL = sqrt( rL_2);
	
	return MREAL( atan2( i_v1.y, rL));
}

//S /////////////////////////////////////////////////////////////////////////////
////	直線と平面の角度(ラジアン)を求める
////
//MREAL	MGeo::AngleULinePln3D(					// (  O) 左回転角度　（度）
//												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
//				const	MgULine3D&	ULn1,		// (I  ) 直線1
//				const	MgPlane3D&	Pln2		// (I  ) 平面2
//		)
//{
//	return AngleVectPln3D( ULn1.v, Pln2);
//}
//
///////////////////////////////////////////////////////////////////////////////
////	線分と平面の角度(ラジアン)を求める
////
//MREAL	MGeo::AngleLinePln3D(					// (  O) 左回転角度　（度）
//												//		2点間の距離がMGPTOL->D未満の場合は0度を返す
//				const	MgLine3D&	Ln1,		// (I  ) 線分1
//				const	MgPlane3D&	Pln2		// (I  ) 平面2
//		)
//{
//	MgVect3D	v1;
//	v1 = Ln1.p[1] - Ln1.p[0];
//	return AngleVectPln3D( v1, Pln2);
//}

/////////////////////////////////////////////////////////////////////////////
//		直線　形状演算
//
// ---------------------( ２次元 )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	２直線間の角の2等分線を求める
//
void	MGeo::Bisector2ULine2D(					// (  O) ステータス
				const	MgULine2D&	ULn1,		// (I  ) 直線1
				const	MgULine2D&	ULn2,		// (I  ) 直線2
						MgULine2D*	ULn3		// (  O) 直線3
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
//	直線と線分間の角の2等分線を求める
//
void MGeo::BisectorULineLine2D(					// (  O) ステータス
				const	MgULine2D&	ULn1,		// (I  ) 直線1
				const	MgLine2D&	Ln2,		// (I  ) 線分2
						MgULine2D*	ULn3		// (  O) 直線3
		)
{
	MgULine2D	ULn2;

	ULn2.p = Ln2.p[0];
	ULn2.v = MGeo::UnitizeVect2D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	線分と直線間の角の2等分線を求める
//
void MGeo::BisectorLineULine2D(					// (  O) ステータス
				const	MgLine2D&	Ln1,		// (I  ) 線分1
				const	MgULine2D&	ULn2,		// (I  ) 直線2
						MgULine2D*	ULn3		// (  O) 直線3
		)
{
	MgULine2D	ULn1;

	ULn1.p = Ln1.p[0];
	ULn1.v = MGeo::UnitizeVect2D(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULine2D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	線分と線分間の角の2等分線を求める
//
void MGeo::Bisector2Line2D(						// (  O) ステータス
				const	MgLine2D&	Ln1,		// (I  ) 線分1
				const	MgLine2D&	Ln2,		// (I  ) 線分2
						MgULine2D*	ULn3		// (  O) 直線3
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
// ---------------------( ３次元 )------------------------------

/////////////////////////////////////////////////////////////////////////////
//	２直線間の角の2等分線を求める
//
void MGeo::Bisector2ULine3D(					// (  O) ステータス
				const	MgULine3D&	ULn1,		// (I  ) 直線1
				const	MgULine3D&	ULn2,		// (I  ) 直線2
						MgULine3D*	ULn3		// (  O) 直線3
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
//	直線と線分間の角の2等分線を求める
//
void MGeo::BisectorULineLine3D(					// (  O) ステータス
				const	MgULine3D&	ULn1,		// (I  ) 直線1
				const	MgLine3D&	Ln2,		// (I  ) 線分2
						MgULine3D*	ULn3		// (  O) 直線3
		)
{
	MgULine3D ULn2;

	ULn2.p = Ln2.p[0];
	ULn2.v = UnitizeVect3D(Ln2.p[1] - Ln2.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	線分と直線間の角の2等分線を求める
//
void MGeo::BisectorLineULine3D(					//
				const	MgLine3D&	Ln1,		// (I  ) 線分1
				const	MgULine3D&	ULn2,		// (I  ) 直線2
						MgULine3D*	ULn3		// (  O) 直線3
		)
{
	MgULine3D ULn1;

	ULn1.p = Ln1.p[0];
	ULn1.v = UnitizeVect3D(Ln1.p[1] - Ln1.p[0]);
	Bisector2ULine3D( ULn1, ULn2, ULn3);
}

/////////////////////////////////////////////////////////////////////////////
//	線分と線分間の角の2等分線を求める
//
void MGeo::Bisector2Line3D(						//
				const	MgLine3D&	Ln1,		// (I  ) 線分1
				const	MgLine3D&	Ln2,		// (I  ) 線分2
						MgULine3D*	ULn3		// (  O) 直線3
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
