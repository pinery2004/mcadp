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
#include "MgGeo.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

//===========================================================================
//		直線　形状演算

// ---------------------( ２次元 )------------------------------
//
//	点が直線上にあるかを調べる。
//
bool MGeo::CheckPointOnSLine2D(					// (  O) ステイタス
												//		 	true:	直線上にある
												//		 	false:	直線上にない
				const	MgPoint2D&	i_p1,		// (I  ) 点1
				const	MgSLine2D&	i_SLn2,		// (I  ) 直線2
						int*		o_pist		// (  O) 補助ステイタス
												//			MC_RIGHT			: 点が直線の右側
												//			MC_ON_SLINE			: 点が直線上
												//			MC_LEFT				: 点が直線の左側
				)
{
	bool		bst;							// ステイタス
	int			ist;							// 補助ステイタス
	MgVect2D	v2s1;							// 直線2の始点から点1までのベクトル
	MREAL		pa1;							// 直線2から点1までの鉛直距離

	// 直線2の方向（単位ベクトル）と直線2の始点から点1までのベクトルの外積より鉛直距離を求める
	v2s1 = i_p1 - i_SLn2.p;					
	pa1 = i_SLn2.v ^ v2s1;						// 直線2の方向（単位ベクトル）と直線2の始点から点1までのベクトルの外積

	// 鉛直距離が誤差内なら直線上
	if ( CheckZero(pa1)) {
		ist = MC_ON_SLINE;
		bst = true;

	// 鉛直距離が正なら直線の左側
	} else if ( pa1 > 0) {
		ist = MC_LEFT;
		bst = false;

	// 鉛直距離が負なら直線の右側
	} else {
		ist = MC_RIGHT;
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}
	
// ---------------------( ２次元 )------------------------------
//
//	点が半直線上にあるかを調べる。
//
bool  MGeo::CheckPointOnHLine2D(				// (  O) ステイタス
												//		 	true:	半直線上にある
												//		 	false:	半直線上にない
				const	MgPoint2D&	i_p1,		// (I  ) 点1
				const	MgHLine2D&	i_HLn2,		// (I  ) 半直線2
						MINT*		o_pist		// (  O) 補助ステイタス
												//		 ステイタス1
												//			MC_RIGHT			: 点が半直線の右側
												//			MC_ON_SLINE			: 点が半直線の延長直線上
												//			MC_LEFT				: 点が半直線の左側
												//		 ステイタス2
												//			MC_INSIDE			: 点が半直線の内側(始点を除く線上)
												//			MC_ON_PS			: 点が半直線の始点上
												//			MC_OUT_PS			: 点が半直線の始点側延長線上
				)
{
	bool		bst;							// ステイタス
	int			ist;							// 補助ステイタス
	MgVect2D	v2s1;							// 半直線2の始点から点1までのベクトル
	MREAL		rl21;							// 半直線2から点1までの鉛直距離

	// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積より鉛直距離を求める
	v2s1 = i_p1 - i_HLn2.p;					
	rl21 = i_HLn2.v ^ v2s1;						// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積

	// 鉛直距離が誤差内なら直線上
	if ( CheckZero( rl21)) {
		if ( v2s1 * v2s1 <= MGPTOL->D_2) {
			ist = MC_ON_PS;
			bst = true;
		} else if ( v2s1 * i_HLn2.v > 0) {
			ist = MC_INSIDE;
			bst = true;
		} else {
			ist = MC_OUT_PS;
			bst = false;
		}
		ist |= MC_ON_SLINE;

	// 鉛直距離が正なら直線の左側
	} else if ( rl21 > 0) {
		ist = MC_LEFT;
		bst = false;

	// 鉛直距離が負なら直線の右側
	} else {
		ist = MC_RIGHT;
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( ２次元 )------------------------------
//
//	点が線分上にあるかを調べる。
//
bool MGeo::CheckPointOnLine2D(					// (  O) ステイタス
												//			true:	線分上にある
												//			false:	線分上にない
				const	MgPoint2D&	p1,			// (I  ) 点1
				const	MgLine2D&	Ln2,		// (I  ) 線分2
						MINT*		o_pist		// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
												//		 ステイタス1
												//			MC_RIGHT			: 点が線分の右側
												//			MC_ON_SLINE			: 点が線分延長直線上
												//			MC_LEFT				: 点が線分の左側
												//		 ステイタス2
												//			MC_ON_PS			: 点が線分の始点上
												//			MC_INSIDE			: 点が線分の内側上
												//			MC_ON_PE			: 点が線分の終点上
												//			MC_OUT_PS			: 点が線分の始点側延長線上
												//			MC_OUT_PE			: 点が線分の終点側延長線上
		)
{
	bool		bst;
	int			ist;							// 補助ステイタス
	MgVect2D	v2s1;							// 線分2の始点から点1へのベクトル
	MgVect2D	v2e1;							// 線分2の始点から点1へのベクトル
	MgVect2D	v2;								// 線分2の始点から終点へのベクトル
	MREAL		pa1;							// 線分2と線分2の始点から点1へのベクトルの外積
	MREAL		cs, ce;							// 線分2と線分2の始点，終点から点1へのベクトルの内積
	MREAL		tol_2;							// 判定用誤差
	MREAL		v2tol_2;						// 判定用誤差

	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// 点から線分までの鉛直距離( abs( pa1)/abs( v2)) <= tol より直線上であるかを調べ
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	// 直線上なら、さらに線分上であるかを調べる
	tol_2 = MGPTOL->D_2;
	v2tol_2 = tol_2 * SqLenVect2D( v2);
	if ( pa1 * pa1 <= v2tol_2) { 								// 点から線分までの鉛直距離がrTol以内
		// 延長直線上
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		ist = 0;
		bst = true;
		if (v2s1 * v2s1 <= tol_2) {
			ist = MC_ON_PS;										// 点が線分の始点上
		} else if ( v2e1 * v2e1 <= tol_2) {
			ist = MC_ON_PE;										// 点が線分の終点上
		} else if ( cs > 0 &&  ce < 0) {
			ist = MC_INSIDE;									// 点が線分の内側上
		} else {
			if ( cs > 0) {
				ist = MC_OUT_PE;
			} else {
				ist = MC_OUT_PS;
			}
			bst = false;
		}
		ist |= MC_ON_SLINE;
	} else {
		// 延長直線上でないなら、線分の左右どちらにあるかを調べる
		if ( pa1 > 0) {
			ist = MC_LEFT;										// 左側
		} else {
			ist = MC_RIGHT;										// 右側
		}
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( ２次元 )------------------------------
//
//	線分と線分が重なっているかを調べる。
//
bool MGeo::CheckLineOnLine2D(					// (  O) ステイタス
												//			true:	重なっている
												//			false:	重なっていない
				const	MgLine2D&	Ln1,		// (I  ) 線分1
				const	MgLine2D&	Ln2			// (I  ) 線分2
		)
{
	bool		bst = false;
	MgVect2D	v2s1;							// 線分2の始点から点1へのベクトル
//	MgVect2D	v2e1;							// 線分2の始点から点1へのベクトル
	MgVect2D	v2;								// 線分2の始点から終点へのベクトル
	MREAL		pa1;							// 線分2と線分2の始点から点1へのベクトルの外積
	MREAL		v2tol_2;						// 判定用誤差
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;

	if (!MGeo::ParallelLine2D( Ln1, Ln2))						// 平行でない場合は
		MQUIT;													// 重なっていないとする
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// 線分1の始点から線分2までの鉛直距離( abs( pa1)/abs( v2)) <= tol より直線上であるかを調べる
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = MGPTOL->D_2 * cs22;
	if ( pa1 * pa1 > v2tol_2) 									// 点から線分までの鉛直距離がrTol超の場合は
		MQUIT;													// 重なっていないとする
	cs21 = 0;
	cs11 = (Ln1.p[0] - Ln2.p[0]) * v2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * v2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);
	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);
	}
	dd = d2 - d1;
	// 重なりの始点から終点までの距離( dd/abs( v2)) <= tol より重なっていないかを調べる
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= v2tol_2)						// 重なりがrTol以下の場合は
		MQUIT;													// 重なっていないとする

	bst = true;
exit:
	return bst;
}

// ---------------------( ３次元 )------------------------------
//
//	点が半直線上にあるかを調べる。
//
bool MGeo::CheckPointOnHLine3D(					// (  O) ステイタス
												//			true:	線分上にある
												//			false:	線分上にない
				const	MgPoint3D&	i_p1,		// (I  ) 点1
				const	MgHLine3D&	i_HLn2,		// (I  ) 半直線2
						int*		o_pist		// (  O) 補助ステイタス
												//		 ステイタス1
												//			MC_ON_SLINE			: 点が半直線の延長直線上
												//		 ステイタス2
												//			MC_INSIDE			: 点が半直線の内側(始点を除く線上)
												//			MC_ON_PS			: 点が半直線の始点上
												//			MC_OUT_PS			: 点が半直線の始点側延長線上
				)
{
	bool		bst;							// ステイタス
	int			ist;							// 補助ステイタス
	MgVect3D	v2s1;							// 半直線2の始点から点1までのベクトル
	MgVect3D	v21;							// 半直線2の始点から点1までの垂線ベクトル
	MREAL		rl21_2;							// 半直線2から点1までの鉛直距離の２乗

	// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積より鉛直距離を求める
	v2s1 = i_p1 - i_HLn2.p;					
	v21 = i_HLn2.v ^ v2s1;						// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積
	rl21_2 = v21 * v21;

	if ( rl21_2 <= MGPTOL->D_2) {
		if ( v2s1 * v2s1 <= MGPTOL->D_2) {
			ist = MC_ON_PS;
			bst = true;
		} else if ( v2s1 * i_HLn2.v > 0) {
			ist = MC_INSIDE;
			bst = true;
		} else {
			ist = MC_OUT_PS;
			bst = false;
		}
		ist |= MC_ON_SLINE;

	} else {
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( ３次元 )------------------------------
//
//	点が線分上にあるかを調べる。
//
bool MGeo::CheckPointOnLine3D(					// (  O) ステイタス
												//			true:	線分上にある
												//			false:	線分上にない
				const	MgPoint3D&	p1,			// (I  ) 点1
				const	MgLine3D	&Ln2,		// (I  ) 線分2
						int*		o_pist		// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
												//		 ステイタス1
												//			MC_ON_SLINE			: 点が線分延長直線上
												//		 ステイタス2
												//			MC_ON_PS			: 点が線分の始点上
												//			MC_INSIDE			: 点が線分の内側上
												//			MC_ON_PE			: 点が線分の終点上
												//			MC_OUT_PS			: 点が線分の始点側延長線上
												//			MC_OUT_PE			: 点が線分の終点側延長線上
		)
{
	bool		bst;
	int			ist;							// 補助ステイタス
	MgVect3D	v2s1;							// 線分2の始点から点1へのベクトル
	MgVect3D	v2e1;							// 線分2の終点から点1へのベクトル
	MgVect3D	v2;								// 線分2の始点から終点へのベクトル
	MgVect3D	va1;							// 線分2と線分2の始点から点1へのベクトルの外積 
	MREAL		cs, ce;
	MREAL		tol_2;							// 判定用誤差
	MREAL		v2tol_2;						// 判定用誤差
	MREAL		v2tol_2_1;						// 判定用誤差 v2tol_2/10000

	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	va1 = v2 ^ v2s1;
	//
	// 点から線分までの鉛直距離( abs( va1)/abs( v2)) <= tol より直線上であるかを調べ
	//						 ( (va1 * va1) <= tol * tol * (v2 * v2))
	// 直線上なら、さらに線分上であるかを調べる
	tol_2 = MGPTOL->D_2;
	v2tol_2 = tol_2 * SqLenVect3D( v2);
	v2tol_2_1 = tol_2 * SqLenVect3D( v2) * 0.0001f * 0.0001f;
	ist = 0;
	if ( SqLenVect3D( va1) <= v2tol_2) { 						// 点から線分までの鉛直距離がrTol以内
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		bst = true;
		if (v2s1 * v2s1 <= tol_2) {
			ist = MC_ON_PS;										// 点が線分の始点上
		} else if ( v2e1 * v2e1 <= v2tol_2) {
			ist = MC_ON_PE;										// 点が線分の終点上
		} else if ( cs > 0 &&  ce < 0) {
			ist = MC_INSIDE;									// 点が線分の内側上
		} else {
			if ( cs > 0) {
				ist = MC_OUT_PE;
			} else {
				ist = MC_OUT_PS;
			}
			bst = false;
		}
		ist |= MC_ON_SLINE;
	} else {
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( ３次元 )------------------------------
//
//	線分と線分が重なっているかを調べる。
//
bool MGeo::CheckLineOnLine3D(					// (  O) ステイタス
												//			true:	重なっている
												//			false:	重なっていない
				const	MgLine3D		&Ln1,	// (I  ) 線分1
				const	MgLine3D		&Ln2	// (I  ) 線分2
		)
{
	bool		bst = false;
	MgVect3D	v2s1;							// 線分2の始点から点1へのベクトル
//	MgVect3D	v2e1;							// 線分2の始点から点1へのベクトル
	MgVect3D	v2;								// 線分2の始点から終点へのベクトル
	MgVect3D	pa1;							// 線分2と線分2の始点から点1へのベクトルの外積
	MREAL		v2tol_2;						// 判定用誤差
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;

	if (!MGeo::ParallelLine3D( Ln1, Ln2))						// 平行でない場合は
		MQUIT;													// 重なっていないとする
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// 線分1の始点から線分2までの鉛直距離( abs( pa1)/abs( v2)) <= tol より直線上であるかを調べる
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = MGPTOL->D_2 * cs22;
	if ((pa1 * pa1) > v2tol_2) 									// 点から線分までの鉛直距離がrTol超の場合は
		MQUIT;													// 重なっていないとする
	cs21 = 0;
	cs11 = v2s1 * v2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * v2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);
	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);
	}
	dd = d2 - d1;
	// 重なりの始点から終点までの距離( dd/abs( v2)) <= tol より重なっていないかを調べる
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= v2tol_2)						// 重なりがrTol以下の場合は
		MQUIT;													// 重なっていないとする

	bst = true;
exit:
	return bst;
}
// ---------------------( ３次元 )------------------------------
//
//	線分と線分が重なっているかを調べる。
//
bool MGeo::CheckLineOnLine3DWS(					// (  O) ステイタス
												//			true:	重なっている
												//			false:	重なっていない
				const	MgLine3D	&Ln1,		// (I  ) 線分1
				const	MgLine3D	&Ln2,		// (I  ) 線分2
						MINT*		o_pist		// (  O) 補助ステイタス　重なりありの場合は次の通り
												//        -4    -3   -2   -1    0     1    2    3    4 		   	
												//		|--   |--  |--- | -- | --- |----| ---|  --|   --|           	  	
												//		|   --|  --| ---|----| --- | -- |--- |--  |--   |                　	
				)
{
	bool		bst = false;
	int			ist;							// 補助ステイタス
	MREAL		rTol;
	MgVect3D	v2s1;							// 線分2の始点から点1へのベクトル
	MgVect3D	v2, vu2;						// 線分2の始点から終点へのベクトル、同単位ベクトル
	MgVect3D	pa1;							// 線分2と線分2の始点から点1へのベクトルの外積
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;
	MREAL		d11, d12, d21, d22;

	ist = 0;
	rTol = MGPTOL->D;
	if (!MGeo::ParallelLine3D( Ln1, Ln2))						// 平行でない場合は
		MQUIT;													// 重なっていないとする
	v2s1 = Ln1.p[0] - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	vu2 = v2.Unitize();
	pa1 = vu2 ^ v2s1;
	//
	// 線分1の始点から線分2までの鉛直距離 abs( pa1) <= tol より直線上であるかを調べる
	//						 ( pa1 * pa1 <= tol * tol)
	if ( SqLenVect3D( pa1) > MGPTOL->D_2)						// 点から線分までの鉛直距離がrTol超の場合は
		MQUIT;													// 重なっていないとする
	cs21 = 0;
	cs22 = v2 * vu2;
	cs11 = v2s1 * vu2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * vu2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);

		d11 = cs11;
		d12 = cs12;
		d21 = cs21;
		d22 = cs22;

	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);

		d11 = cs12;
		d12 = cs11;
		d21 = cs22;
		d22 = cs21;
	}
	// 補助ステイタスを求める
	if (d12 > d22 + rTol) {
		if (d11 > d22 - rTol) {
			if (d11 > d22 + rTol)
				ist = 4;
			else
				ist = 3;
		} else {
			if (d11 > d21 + rTol)
				ist = 2;
			else
				ist = 1;
		}
	} else if (d11 < d21 - rTol) {
		if (d12 < d21 + rTol) {
			if (d12 < d21 - rTol)
				ist = -4;
			else
				ist = -3;
		} else {
			if (d12 < d22 - rTol)
				ist = -2;
			else
				ist = 1;
		}
	} else if (d12 > d22 - rTol && d11 < d21 + rTol)
		ist = 0;
	else
		ist = -1;

	dd = d2 - d1;
	// 重なりの始点から終点までの距離( dd/abs( v2)) <= tol より重なっていないかを調べる
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= MGPTOL->D_2)					// 重なりがrTol以下の場合は
		MQUIT;													// 重なっていないとする

	bst = true;
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

//
// ---------------------( ２次元 )------------------------------
//	点と穴付き多角形の位置関係を求める
//
bool MGeo::CheckPointOnGPolygon2DWS(			// (  O) ステイタス
												//			true:	穴付き多角形の内側または辺上
												//			false:	穴付き多角形の外側
				const	MgPoint2D&	i_pt,		// (I  ) 点
				const	MgGPolyg2D&	i_Gpg,		// (I  ) 穴付き多角形
						int*		o_pist		// (  O) ステイタス
												//			MC_IN_BORDER		: 点が穴付き多角形の内側
												//			MC_ON_BORDER		: 点が穴付き多角形の辺上(または頂点上)
												//			MC_OUT_BORDER		: 点が穴付き多角形の外側
		)
{
	bool		bst;
	int			ist;							// 補助ステイタス
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum;
	MgPolyg2D*	pPg;
	
	ictSum = 0;													// 内外判定用カウンタ
	for ( ic1=0; ic1<i_Gpg.m_n; ic1++) {
		pPg = &(i_Gpg.m_pg[ic1]);

		
		ist1 = CountPolygonAroundPoint2D( i_pt, NULL, *pPg, &ict);
		if ( ist1) {
			ist = MC_ON_BORDER;
			bst = true;											// 穴付き多角形の辺上(または頂点上)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		ist = MC_IN_BORDER;										// 穴付き多角形の内側
		bst = true;
	} else {
		ist = MC_OUT_BORDER;									// 穴付き多角形の外側
		bst = false;
	}
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

//
// ---------------------( ２次元 )------------------------------
//	線分の中心点と穴付き多角形の位置関係を求める
//
bool MGeo::CheckLineOnGPolygon2DWS(				// (  O) ステイタス
												//			true:	穴付き多角形の内側または辺上
												//			false:	穴付き多角形の外側
				const	MgLine2D&	Ln1,		// (I  ) 線分
				const	MgGPolyg2D&	GPg2,		// (I  ) 穴付き多角形
						int*		o_pist		// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
												// 		 テイタス1
												//			MC_IN_BORDER		: 点が穴付き多角形の内側
												//			MC_ON_BORDER		: 点が穴付き多角形の辺上(または頂点上)
												//			MC_OUT_BORDER		: 点が穴付き多角形の外側
												// 		 テイタス2
												//			MC_ON_SIDE_SAME		: 辺上(同一方向)	(MC_ON_BORDERと共に設定)
												//			MC_ON_SIDE_REV		: 辺上(逆方向)		(MC_ON_BORDERと共に設定)
												//			MC_ON_TOP			: 頂点上			(MC_ON_BORDERと共に設定)
				)
{
	bool		bst;
	int			ist;							// 補助ステイタス
	MgPoint2D	pt1;
	MgVect2D	vt1;
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum = 0;								// 内外判定用カウンタ
	MgPolyg2D*	pPg;
	
	pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	vt1 = Ln1.p[1] - Ln1.p[0];
	
	for ( ic1=0; ic1<GPg2.m_n; ic1++) {
		pPg = &(GPg2.m_pg[ic1]);
		
		ist1 = CountPolygonAroundPoint2D( pt1, &vt1, *pPg, &ict);
		if ( ist1) {
			ist = MC_ON_BORDER | ist1;
			bst = true;											// 穴付き多角形の辺上(または頂点上)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		ist = MC_IN_BORDER;										// 穴付き多角形の内側
		bst = true;
	} else {
		ist = MC_OUT_BORDER;									// 穴付き多角形の外側
		bst = false;
	}
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}
//
// ---------------------( ２次元 )------------------------------
// 点と多角形の位置関係を求める
// 多角形の辺が点の周りを回る周回数を求める（実体一周:1　穴一周:-1）
MINT MGeo::CountPolygonAroundPoint2D(			// (  O) ステイタス
												//			(000)				: 多角形の中または外	
												//			MC_ON_SIDE_SAME		: 辺上(同一方向)
												//			MC_ON_SIDE_REV		: 辺上(逆方向)
												//			MC_ON_SIDE			: 辺上(線分方向=NULL: 線分方向指定無し)
												//			MC_ON_TOP			: 頂点上
				const	MgPoint2D&	Pt,			// (I  ) 点
				const	MgVect2D	*vst,		// (I  ) 線分方向 または NULL
												//		 引数がNULLで無ければ点が辺上の場合、
												//		 辺の線分方向と比較する
				const	MgPolyg2D&	Pg,			// (I  ) 多角形
						MINT*		ict			// (  O) 周回カウント
												//			>0: 多角形が実体の場合の周回数	(1:1周)
												//			=0: 頂点、辺上、多角形の外
												//			<0: 多角形が穴の場合の周回数	(-1:1周)	
				)
{
	MINT		ist;
	MINT		ic;
	MgPoint2D	Ps, Pe;
	MgVect2D		Vs, Ve;
	MgVect2D		Vl;
	MINT		iQs, iQe;						// 始点、終点の象限
	MINT 		iQse;							// 始点から終点への象限移動数
	MINT 		iQSum = 0;						// 象限移動数の合計
	
	*ict = 0;
	Ps = Pg.m_p[Pg.m_n-1];
	if (Pt == Ps) {								// 点が始点上
		ist = MC_ON_TOP;
		MQUIT;
	}
	iQs = Quadrant( Pt, Ps);
	Vs = Pt - Ps;
	for ( ic=0; ic<Pg.m_n; ic++) {
		Pe = Pg.m_p[ic];
		Ve = Pt - Pe;
		if ( SqLenVect2D( Ve) <= MGPTOL->D_2) {					// 点が終点上(Pt == Pe)
			ist = MC_ON_TOP;
			MQUIT;
		}
		Vl = Pe - Ps;
		MREAL Ss = Vl ^ Vs;
		if ( ( Ss * Ss) <= ( MGPTOL->D_2 * SqLenVect2D( Vl))) {	// 点から辺までの距離がrTol以内
			MREAL Cs = Vs * Vl;
			MREAL Ce = Ve * Vl;
			if (Cs >= 0.0f && Ce <= 0.0f) {						// 辺上
				if (vst) {
					if (*vst * Vl > 0.f) 
						ist = MC_ON_SIDE_SAME;					// 点が辺上(同一方向)
					else
						ist = MC_ON_SIDE_REV;					// 点が辺上(逆方向)
				} else {
					ist = MC_ON_SIDE;							// 点が辺上(線分方向=NULL: 線分方向指定無し)
				}
				MQUIT;
			}
		}
		
		iQe = Quadrant( Pt, Pe);
		iQse = iQe - iQs;

		if (Ss > 0.0f) {										// 点が線分の左側
			if ( iQse < 0) iQse += 4;
		} else {												// 点が線分の右側
			if ( iQse > 0) iQse -= 4;
		}
		iQSum += iQse;
		
		Ps = Pe;
		iQs = iQe;
		Vs = Ve;
	}
	*ict = iQSum / 4;
	ist = 0;
exit:
	return ist;
}
//
// ---------------------( ３次元 )------------------------------
//	点と多角形の位置関係を求める ３Ｄ
//
/*
bool MGeo::CheckPt3OnPg3WS(						// (  O) ステイタス
												//			true:	多角形の内側または辺上
												//			false:	多角形の外側
				const	MgPoint3D&	Pt,			// (I  ) 点
				const	MgPolyg3D&	Pg,			// (I  ) 多角形
						MINT*		ist,		// (  O) ステイタス
							  					//		 多角形の平面と点の位置関係
												//			MC_UPPER			: 点が平面の上側	
												//			MC_ON_PLANE			: 点が平面上
												//			MC_LOWER			: 点が平面の下側
												//		 多角形と点の位置関係
												//			MC_IN_BORDER		: 点が多角形の内側
												//			MC_ON_BORDER		: 点が多角形の辺上
												//			MC_OUT_BORDER		: 点が多角形の外側
//SS					MREAL		rTol		// (I  ) トレランス
				)
{
	MgPoint2D wPt;												// 点の２Ｄ作業用
	MINT work[sizeof(MgPolyg2D)+MX_LIN2*(sizeof(MgPoint2D)-1)];	// 最大構成線数がMX_LIN2の
	MgPolyg2D *wPg = (MgPolyg2D*)work;							// 多角形用２Ｄ作業用エリアを確保

	*ist = 0;
	
	MgPlane3D Pln = MgPgtoPln( Pg);								// 多角形が乗る平面
	MREAL pa1 = (Pln.v * Pt) + Pln.d;							// 点から平面までの距離
	
	if (!(MgAbs_2( pa1) <= Geo::D_2)) {							// 多角形の平面上で無い場合に、多角形の上下を判定する
		if ( pa1 > 0) *ist = MC_UPPER;							// 多角形の構成点を右ねじ回転とみなし進む方向を上側とする
		else *ist = MC_LOWER;
		return	false;
	}
	MgMat3E mat = MgMat3EDto2D( Pln);
	Mg3Dto2D( Pt, mat, &wPt);
	Mg3Dto2D( Pg, mat, wPg);
	MgPolyg2D wPg1;
	bool bst = MgOnPtPolygon3D( wPt, wPg1, ist);
	bst = MgOnPtPolygon3D( wPt, *wPg, ist);
	*ist |= MC_ON_PLANE;
	return bst;
}
*/
//
// ---------------------( ３次元 )------------------------------
//	線分の中心点と多角形の位置関係を求める
//
/*
bool MGeo::CheckLn3OnPg3WS(						// (  O) ステイタス
												//			true:	多角形上
												//			false:	多角形外
				const	MgLine3D	&Ln1,		// (I  ) 線分
				const	MgPolyg3D&	Pg2,		// (I  ) 多角形
						MINT*		ist			// (  O) 補助ステイタス
							  					//		 多角形の平面と点の位置関係
												//			MC_UPPER			: 点が平面の上側	
												//			MC_ON_PLANE			: 点が平面上
												//			MC_LOWER			: 点が平面の下側
												//       多角形と点の位置関係
												//			MC_IN_BORDER		: 点が多角形の内側
												//			MC_ON_BORDER		: 点が多角形の辺上
												//			MC_OUT_BORDER		: 点が多角形の外側
		)
{
	MgPoint3D	Pt1;
	Pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	return MgOnPtPolygon3D( Pt1, Pg2, ist);
}
*/

////		平面　形状演算
////
//// ---------------------( ３次元 )------------------------------
////
////	点が平面上にあるかを調べる。
////
//bool MGeo::CheckPt3OnPln3WS(					// (  O) ステイタス
//												//			true:  平面上
//												//			false: 平面外
//				const	MgPoint3D&	p1,			// (I  ) 点1
//				const	MgPlane3D	&Pln2,		// (I  ) 平面2
//						MINT*		ist			// (  O) 補足ステイタス
//												//			MC_UPPER			: 点が平面の上側	
//												//			MC_ON_PLANE			: 点が平面上
//												//			MC_LOWER			: 点が平面の下側
//SS //					MREAL		rTol		// (I  ) トレランス
//		)
//{
//	bool	bst;
//	MREAL	pa1;								//	点から平面までの距離
////
//	pa1 = (Pln2.v * p1) + Pln2.d;
//	if ( pa1 > rTol) {
//		*ist = MC_UPPER;
//		bst = false;
//	} else if ( pa1 < -rTol) {
//		*ist = MC_LOWER;
//		bst = false;
//	} else {
//		*ist = MC_ON_PLANE;
//		bst = true;
//	}
//	return bst;
//}

////
//// ---------------------( ３次元 )------------------------------
////	直線が平面上にあるかを調べる。
////
//bool MGeo::CheckSLn3OnPln3D(					// (  O) ステイタス
//												//			true:  平面上
//												//			false: 平面外
//				const	MgSLine3D&	SLn1,		// (I  ) 直線1
//				const	MgPlane3D	&Pln2		// (I  ) 平面2
//SS //					MREAL		rTol		// (I  ) トレランス
//		)
//{
//	int		ist;
//	if (MgCheckPt3OnPln3WS(SLn1.p, Pln2, &ist)) {
////
////	平行のチェック
////
//		if (MgCheckPerp2V3(SLn1.v, Pln2.v)) return true;	//	平面上
//	}
//	return false;
//}

////
//// ---------------------( ３次元 )------------------------------
////	線分が平面上にあるかを調べる。
////
//bool MGeo::CheckLn3OnPln3WS(					// (  O) ステイタス
//												//			true:  平面上
//												//			false: 平面外
//				const	MgLine3D	&Ln1,		// (I  ) 線分1
//				const	MgPlane3D	&Pln2,		// (I  ) 平面2
//						MINT*		ist			// (  O) 補足ステイタス
//							  					//		 多角形の平面と点の位置関係
//												//			MC_PS_UPPER			: 始点が平面の上側	
//												//			MC_PS_ON_PLANE		: 始点が平面上
//												//			MC_PS_LOWER			: 始点が平面の下側
//												//       多角形と点の位置関係
//												//			MC_PE_UPPER			: 終点が平面の上側	
//												//			MC_PE_ON_PLANE		: 終点が平面上
//												//			MC_PE_LOWER			: 終点が平面の下側
//SS //					MREAL		rTol		// (I  ) トレランス
//		)
//{
//	bool	bs, be;
//	MINT	ists, iste;
//
//	bs = MgCheckPt3OnPln3WS(Ln1.p[0], Pln2, &ists);
//	be = MgCheckPt3OnPln3WS(Ln1.p[1], Pln2, &iste);
//	*ist = (ists * MC_PS_UPPER + iste * MC_PE_UPPER)/ MC_UPPER;
//	return (bs && be);
//}

////
//// ---------------------( ２次元 )------------------------------
//// P1を原点としたP2の位置の象限を求める
////
//static MINT MGeo::Quadrant	(				// (  O) 1〜4: 象限
//				const	MgPoint2D&	p1,			// (I  ) P1
//				const	MgPoint2D&	p2			// (I  ) P2
//		)
//{
//	return ((p2.x > p1.x) ? ((p2.y > p1.y) ? 1 : 4) : ((p2.y > p1.y) ? 2 : 3));
//}

} // namespace MC
