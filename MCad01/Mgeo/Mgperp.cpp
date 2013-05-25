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
//		形状演算
//
////	-------------------------２ＤＬＩＮＥ・ＰＯＩＮＴ----------------------
////
////	点から直線への垂線の足位置を求める
////
//void MGeo::PerpSLnPoint2D(
//				const	MgSLine2D&	SLn1,		// (I  ) 直線1
//				const	MgPoint2D&	p2,			// (I  ) 点2
//						MgPoint2D*	po			// (  O) 点から直線への垂線の足
//		)
//{
//	MREAL		pa1;							//	直線1の始点から垂線の足までの距離
//
//	pa1 = (p2 - SLn1.p) * SLn1.v;				//	cosΘv12v2
//	*po = SLn1.p + SLn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPoint2D(							// (  O) ステイタス(=MC_ON_SLINE	:線分上,
//												//					=0			:線分範囲外)
//				const	MgLine2D&	Ln1,		// (I  ) 線分1
//				const	MgPoint2D&	p2,			// (I  ) 点2
//						MgPoint2D*	po			// (  O) 点から直線への垂線の足
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
//	*po = Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	交点
//
//	if (ss * se < 0 ||											//	線分上
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_SLINE;
//	else ist =  0;												//	線分の外
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPointSLine2D(
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgSLine2D&	SLn2,		// (I  ) 直線2
						MgPoint2D*	po			// (  O) ２次元交点(点の標準形式)
		)
{
	MgPerpSLnPoint2D(SLn2, p1, po);
}
//	------------------------
MINT MGeo::PerpPointLine2D(							// (  O) ステイタス(=MC_ON_SLINE	:線分上,
												//					=0			:線分範囲外)
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgLine2D	&Ln2,		// (I  ) 線分2
						MgPoint2D*	po			// (  O) ２次元交点(点の標準形式)
		)
{
	return MgPerpLnPoint2D(Ln2, p1, po);
}
*/

////
////	-------------------------３ＤＬＩＮＥ・ＰＯＩＮＴ----------------------
////
////	点から直線への垂線の足位置を求める
////
//void MGeo::PerpSLnPoint3D(
//				const	MgSLine3D&	SLn1,		// (I  ) 直線1
//				const	MgPoint3D&	p2,			// (I  ) 点2
//						MgPoint3D	*po			// (  O) 点から直線への垂線の足
//		)
//{
//	MREAL	pa1;								//	直線1の始点から垂線の足までの距離
//
//	pa1 = (p2 - SLn1.p) * SLn1.v;				//	cosΘv12v2
//	*po = SLn1.p + SLn1.v * pa1;
//}

////	------------------------
//MINT MGeo::PerpLnPoint3D(							// (  O) ステイタス(=MC_ON_SLINE	:線分上,
//												//					=0			:線分範囲外)
//				const	MgLine3D	&Ln1,		// (I  ) 線分1
//				const	MgPoint3D&	p2,			// (I  ) 点2
//				MgPoint3D		*po				// (  O) ３次元交点(点の標準形式)
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
//	*po = Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	交点
//
//	if (ss * se < 0 ||											//	線分上
//		*po == Ln1.p[0] || *po == Ln1.p[1]) ist = MC_ON_SLINE;
//	else ist = 0;												//	線分の外
//
//	return ist;
//}

//	------------------------
/*
void MGeo::PerpPointLine3D(
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgLine3D	&Ln2,		// (I  ) 直線2
						MgPoint3D	*po			// (  O) ３次元交点(点の標準形式)
		)
{
	MgPerpLnPoint3D(Ln2,	p1, po);
}

//	------------------------
MINT MGeo::PerpPointSLine3D(							// (  O) ステイタス(=MC_ON_SLINE	:線分上,
												//					=0			:線分範囲外)
				const MgPoint3D& p1,			// (I  ) 点1
				const MgSLine3D& SLn2,			// (I  ) 線分2
				MgPoint3D	*po					// (  O) ３次元交点(点の標準形式)
		)
{
	return MgPerpSLnPoint3D(SLn2, p1, po);
}
*/

////
////	-------------------------３Ｄ面・ＰＯＩＮＴ----------------------
////
////	点から面への垂線の足位置を求める
////
//void MGeo::PerpPlnPoint3D(
//				const	MgPlane3D	&Pln1,		// (I  ) 面1
//				const	MgPoint3D&	p2,			// (I  ) 点2
//						MgPoint3D	*po			// (  O) 点から直線への垂線の足
//		)
//{
//	MREAL	pa1;								//	点2から垂線の足までの距離
//
//	pa1 = (p2 * Pln1.v) + Pln1.d;
//	*po = p2 - Pln1.v * pa1;
//}

//	------------------------
/*
void MGeo::PerpPointPln3D(
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgPlane3D	&Pln2,		// (I  ) 面2
						MgPoint3D	*po			// (  O) ３次元交点(点の標準形式)
		)
{
	MgPerpPlnPoint3D(Pln2, p1, po);
}
*/

} // namespace MC
