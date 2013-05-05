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

//S //===========================================================================
////		点　形状演算
////
//// ---------------------( ２次元 )------------------------------
////
////		２点間の距離を求める。
////
//MREAL MGeo::Dist2Point2D(						// (  O) 直線から点までの距離 >0:左側 <0:右側
//				const	MgPoint2D&	p1,			// (I  ) 点1
//				const	MgPoint2D&	p2			// (I  ) 点2
//		)
//{
//	MgVect2D	v1;
//	MREAL	pa1;								//	直線から点までの距離
////
//	v1 = p1 - p2;
//	pa1 = sqrt( v1 * v1);
//	return pa1;
//}

//S //===========================================================================
////		点　形状演算
////
//// ---------------------( ３次元 )------------------------------
////
////		２点間の距離を求める。
////
//MREAL MGeo::Dist2Point3D(						// (  O) ２点間の距離 >0:左側 <0:右側
//				const	MgPoint3D&	p1,			// (I  ) 点1
//				const	MgPoint3D&	p2			// (I  ) 点2
//		)
//{
//	MgVect3D	v1;
//	MREAL	pa1;								//	直線から点までの距離
////
//	v1 = p1 - p2;
//	pa1 = sqrt( v1 * v1);
//	return pa1;
//}

//===========================================================================
//		直線　形状演算
//
// ---------------------( ２次元 )------------------------------
//
//		直線から点までの正負方向付き距離を求める。
//
MREAL MGeo::DistPointULine2D(						// (  O) 直線から点までの距離 >0:左側 <0:右側
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgULine2D&	ULn2		// (I  ) 直線2
		)
{
	MgVect2D	v1s2;
	MREAL	pa1;								//	直線から点までの距離
//
	v1s2 = p1 - ULn2.p;
	pa1 = ULn2.v ^ v1s2;
	return pa1;
}
//	------------------------
//		線分から点までの正負方向付き距離を求める。(直線と同様）
//
MREAL MGeo::DistPointLine2D(						// (  O) 線分から点までの距離 >0:左側 <0:右側
												//	線分の長さが0の場合は点から線分の始点までの距離
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgLine2D&	Ln2			// (I  ) 線分2
		)
{
	MgVect2D	v2s1;
	MgVect2D	v2;
	MREAL	sz2;								//	線分2の長さ
	MREAL	pa1;								//	線分から点までの距離
//
	v2s1 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = AbsVect2D( v2);
	if (sz2 < MGPTOL->D) return AbsVect2D( v2s1);
	pa1 = (v2 ^ v2s1) / sz2;
	return pa1;
}
// ---------------------( ３次元 )------------------------------
//		直線から点までの距離を求める。
//
MREAL MGeo::DistPointULine3D(						// (  O) 直線から点までの距離
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgULine3D&	ULn2		// (I  ) 直線2
		)
{
	MgVect3D	v21, va1;
	MREAL pa1;									//	直線から点までの距離
//
	v21 = p1 - ULn2.p;
	va1 = v21 ^ ULn2.v;
	pa1 = AbsVect3D( va1);
	return pa1;
}
//
//		線分から点までの距離を求める。(直線と同様）
//
MREAL MGeo::DistPointLine3D(						// (  O) 線分から点までの距離
												//	線分の長さが0の場合は点から線分の始点までの距離
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgLine3D	&Ln2			// (I  ) 線分2
		)
{
	MgVect3D	v21;
	MgVect3D	v2;
	MREAL	sz2;
	MgVect3D va1;
	MREAL pa1;									//	線分から点までの距離
//
	v21 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = AbsVect3D(v2);
	if (sz2 < MGPTOL->D) return AbsVect3D(v21);
	va1 = v21 ^ v2;
	pa1 = AbsVect3D(va1) / sz2;
	return pa1;
}
// ---------------------( ３次元 )------------------------------
//		直線から点までの正負方向付き距離を求める。
//
MREAL MGeo::DistPointULineVect3D(						// (  O) 直線から点までの距離 >0:左側 <0:右側
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgULine3D&	ULn2,		// (I  ) 直線2
				const	MgVect3D&	vn			// (I  ) 点と直線に直交する単位ベクトル
		)
{
	MgVect3D	v2s1, va1;
	MREAL pa1;									//	直線から点までの距離
//
	v2s1 = p1 - ULn2.p;
	va1 = ULn2.v ^ v2s1;
	pa1 = va1 * vn;
	return pa1;
}
//
//		線分から点までの正負方向付き距離を求める。(直線と同様）
//
MREAL MGeo::DistPointLine3DWH(						// (  O) 線分から点までの距離 >0:左側 <0:右側
												//		 線分の長さが0の場合は点から線分の始点までの距離
												//		 線分の長さが0の場合は点から線分の始点までの距離
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgLine3D&	Ln2,		// (I  ) 線分2
				const	MgVect3D&	vn			// (I  ) 点と直線に直交する単位ベクトル
		)
{
	MgVect3D	v2s1;
	MgVect3D	v2;
	MREAL	sz2;								//  線分2の長さ
	MgVect3D va1;
	MREAL pa1;									//	点から線分までの距離≧0
//
	v2s1 = p1 - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	sz2 = AbsVect3D(v2);
	if (sz2 < MGPTOL->D) return AbsVect3D(v2s1);
	va1 = v2 ^ v2s1;
	pa1 = (va1 * vn) / sz2;
	return pa1;
}
// ---------------------( ３次元 )------------------------------
//		平面から点までの正負方向付き距離を求める。
//
MREAL MGeo::DistPointPln3D(						// (  O) 点から平面までの距離 >0:表側（平面の単位ベクトル方向側）<0:裏側
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgPlane3D&	Pln2		// (I  ) 平面2
		)
{
	MREAL	pa1;								//	点から平面までの距離
//
	pa1 = (p1 * Pln2.v) - Pln2.d;
	return pa1;
}

} // namespace MC
