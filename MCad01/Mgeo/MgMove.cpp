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

/*        inline化
//
//===========================================================================
//		点の移動　形状演算
//
// ---------------------( ２次元 )------------------------------
//
void MGeo::MovePt2InDirOfVt2(					//
				const	MgPoint2D&	p1,			//  (I  ) 移動点1
				const	MgVect2D&	v2,			//	(I  ) 移動方向を示すベクトル
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint2D	*p3			//	(  O) 移動された点3
		)
{
	*p3 = p1 + dl * MGeo::UnitizeVect2D(v2);
}
//	------------------------
void MGeo::MovePt2AlongSLine2D(					//
				const	MgPoint2D&	p1,			//  (I  ) 移動点1
				const	MgSLine2D&	SLn2,		//	(I  ) 移動方向を示す直線2
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint2D	*p3			//	(  O) 移動された点3
		)
{
	*p3 = p1 + dl * SLn2.v;
}
//	------------------------
void MGeo::MovePt2AlongLine2D(						//
				const	MgPoint2D&	p1,			//  (I  ) 移動点1
				const	MgLine2D&	Ln2,		//	(I  ) 移動方向を示す線分2
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint2D	*p3			//	(  O) 移動された点3
		)
{
	MgVect2D	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MGeo::UnitizeVect2D(vd);
	*p3 = p1 + dl * vn;
}
//
// ---------------------( ３次元 )------------------------------
//
void MGeo::MovePt3InDirOfVt3(					//
				const	MgPoint3D&	p1,			//  (I  ) 移動点1
				const	MgVect3D&	v2,			//	(I  ) 移動方向を示すベクトル
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint3D	*p3			//	(  O) 移動された点3
		)
{
	*p3 = p1 + dl * MgUnitizeVect3D(v2);
}
//	------------------------
void MGeo::MovePt3AlongSLine3D(					//	(  O) ステイタス
				const	MgPoint3D&	p1,			//  (I  ) 移動点1
				const	MgSLine3D&	SLn2,		//	(I  ) 移動方向を示す直線2
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint3D	*p3			//	(  O) 移動された点3
		)
{
	*p3 = p1 + dl * SLn2.v;
}
//	------------------------
void MGeo::MovePt3AlongLine3D(						//	(  O) ステイタス
				const	MgPoint3D&	p1,			//  (I  ) 移動点1
				const	MgLine3D	&Ln2,		//	(I  ) 移動方向を示す線分2
						MREAL		dl,			//	(I  ) 移動距離
						MgPoint3D	*p3			//	(  O) 移動された点3
		)
{
	MgVect3D	vd, vn;
//
	vd = Ln2.p[1] - Ln2.p[0];
	vn = MgUnitizeVect3D(vd);
	*p3 = p1 + dl * vn;
}
//===========================================================================
//		直線のオフセット　形状演算
//
// ---------------------( ２次元 )------------------------------
//
//	直線をオフセットする。
//
void MGeo::OffsetSLine2D(							//	(  O) ステイタス (=1)
				const	MgSLine2D&	SLn1,		//	(I  ) 直線1
						MREAL		dl,			//	(I  ) オフセット量
						MgSLine2D 	*SLn2		//	(  O) オフセットされた直線2
		)
{

	SLn2->p = SLn1.p + dl * MgRotL90(SLn1.v);
	SLn2->v = SLn1.v;
}
//	------------------------
void MGeo::OffsetLine2D(							//	(  O) ステイタス
				const	MgLine2D&	Ln1,		//	(I  ) 線分1
						MREAL		dl,			//	(I  ) オフセット量
						MgLine2D	*Ln2		//	(  O) オフセットされた線分2
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
// ---------------------( ３次元 )------------------------------
//
void MGeo::OffsetSLine3D(							//	(  O) ステイタス
				const	MgSLine3D&	SLn1,		//	(I  ) 直線1
				const	MgPlane3D	&Pln2,		//	(I  ) 直線1が乗る平面2
						MREAL		dl,			//	(I  ) オフセット量
						MgSLine3D	*SLn3		//	(  O) オフセットされた直線3
		)
{
	SLn3->p = SLn1.p + dl * (Pln2.v ^ SLn1.v);
	SLn3->v = SLn1.v;
}
//	------------------------
void MGeo::OffsetLine3D(							//	(  O) ステイタス
				const	MgLine3D	&Ln1,		//	(I  ) 線分1
				const	MgPlane3D	&Pln2,		//	(I  ) 線分1が乗る平面2
						MREAL		dl,			//	(I  ) オフセット量
						MgLine3D	*Ln3		//	(  O) オフセットされた線分3
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
