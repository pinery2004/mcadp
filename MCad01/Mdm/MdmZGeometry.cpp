//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdZGeometry.cpp
//
//		図形情報の幾何計算
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgMat.h"

#include "MdModel.h"

namespace MC
{

//===========================================================================
//		プロット点より面を作る
//
//		指定された点を通る面を作成する。
//		作成した面は３角形の面の集まりでできた多面。
//
MINT	MdzCreateTriangleFromPoint(
						MgPolyg3	i_pgPlt,	// プロット点座標値リスト（３次元の点リスト）
						MDFIG*		o_pfigPln	// 生成された面の図形情報
				)
{
	return 0;
}

//
//===========================================================================
//		プロット点より立体を作る
//
//		上面は、指定された点を通る面、（作成した上面は３角形の面の集まりでできた多面）
//		下面は、上面の境界線からなるXY平面に平行な平面
//		から構成される線形構造立体の図形情報を作成する。
//
MINT	MdzCreateSolidFromPoint(
						MgPolyg3	i_pgPlt,	// プロット点座標値リスト（３次元の点リスト）
						MDFIG*		o_pfigPln	// 生成された面の図形情報
				)
{
	return 0;
}

//
//===========================================================================
//		線の長さを求める
//
//		線タイプ図形の長さを得る。
//		　図形は、線タイプの図形であれば、２次元、３次元どちらでも可。
//		　（ZUKEI:: ConvPolygonを呼ぶ必要はない。）
//		　線タイプ以外の図形を渡した場合はlen＝0が返る。
//
MINT	MdzGetLen(
						MDFIG&		i_stFigLn,	// 線タイプの図形情報
						MREAL*		o_prLng		// 線の長さ
				)
{
	return 0;
}

//
//===========================================================================
//		図形の長さ、表面積、体積を求める
//
//		図形の長さ、表面積、体積を得る。
//		　図形は、２次元、３次元どちらでも可。
//		　（ZUKEI:: ConvPolygonを呼ぶ必要はない。）
//		　対象外の図形に対しては、値が０で返る。
//		（例えば、線タイプの図形は、area＝volm＝0が返る。）
//
MINT	MdzGetLenAreaVol(
						MDFIG&		i_stFigZ,	// 図形情報
						MREAL*		o_prLng,	// 線の長さ
						MREAL*		o_prArea,	// 線の面積
						MREAL*		o_prVolm	// 線の体積
				)
{
	return 0;
}

//
//===========================================================================
//		点と立体の包含を調べる
//
//		指定された点と立体（多面体）との包含関係を調べる。
//
MINT	MdzCheckPointSolid(
						MgPoint3	i_ptChk,	// 点座標値
						MDFIG&		i_stFigVol,	// 多面体の図形情報
						MINT*		o_iCond		// チェック結果
												//	-1:立体の面上にある
												//	 0: 立体の外側にある
												//	 1: 立体の内側にある
				)
{
	return 0;
}

//
//===========================================================================
//	平面と有意点列の干渉を調べる
//
//		平面と有意点列の干渉を調べる。
//		図形は、２次元、３次元どちらでも可。
//
MINT	MdzCheckInterPolylinePlane(
						MDFIG&		i_stFigPln,	// 平面の図形情報
						MDFIG&		i_stFigPlg,	// 有意点列の図形情報
						MINT*		o_iCond		// チェック結果
												//	-1:立体の面上にある
												//	0:干渉していない
												//	1:干渉している
				)
{
	return 0;
}

//
//===========================================================================
//		平面と平面の干渉を調べる
//
//		平面と平面の干渉を調べる。
//		図形は、２次元、３次元どちらでも可。
//
MINT	MdzCheckInterPlanePlane(
						MDFIG&		i_stFigPln1,	// 平面の図形情報
						MDFIG&		i_stFigPln2,	// 平面の図形情報
						MINT*		o_iCond		// チェック結果
												//	0:干渉していない
												//	1:干渉している
				)
{
	return 0;
}

//
//===========================================================================
//		図形情報１と図形情報２の干渉を調べる
//
//		図形情報１と図形情報２の干渉を調べる。
//		図形は、２次元、３次元どちらでも可。
//
MINT	MdzCheckInter(
						MDFIG&		i_stFigZk1,	// 図形情報１
						MDFIG&		i_stFigZk2,	// 図形情報２
						MINT*		o_iCond		// チェック結果
												//	0:干渉していない
												//	1:干渉している
												//	2:図形情報１が図形情報２を包含している
												//	3:図形情報２が図形情報１を包含している
				)
{
	return 0;
}

//
//===========================================================================
//		図形の重心を求める
//
//		図形の重心を求める。
//		　図形情報、重心の点座標は、３次元のみとする。
//		　（ZUKEI:: ConvPolygonを呼ぶ必要はない。）
//		　線タイプ等対象外の図形を渡した場合は重心＝（0,0,0）が返る。

//
MINT	MdzGetGravityPoint(
						MDFIG&		i_stFigZk,	// 図形情報（３次元）
						MgPoint3*	o_pptG		// 重心の点座標値（３次元）
				)
{
	return 0;
}

//
//===========================================================================
//		有意点列と点の最短距離を求める
//
//		有意点列と点の最短距離を求める。
//		図形は、３次元のみが対象。
//
//
MINT	MdzBeelinePointPlane(
						MDFIG&		i_stFigPg,	// 有意点列の図形情報（３次元）
						MgPoint3	i_pt,		// 点座標値（３次元）
						MREAL*		o_pLng		// 最短距離
				)
{
	return 0;
}

//
//===========================================================================
//		面の集合の境界線を得る
//
//		渡された多面の外縁境界線を得る。
//		図形情報は、３次元のみとする。
//		境界線は有意点列（閉）の図形情報が返る。
//
MINT	MdzGetBorder(
						MDFIG&		i_stFigGPln,	// 多面の図形情報（３次元）
						MDFIG*		o_pfigPg	// 境界線の図形情報（３次元）
				)
{
	return 0;
}

//
//===========================================================================
//		有意点列の不要点を除去する(2D)（同一直線の点を除く）
//
//		有意点列中の直線上にある中間点を除去する。
//		（有意点列内で、隣り合う線分が１直線上にある場合の中間点を除去する。）
//
//		図形は、２次元の有意点列を対象とする。
//
MINT	MdzGetVertexFromPolyline (
						MDFIG&		i_stFigPg, 	// 有意点列の図形情報
						MDFIG*		o_pfigPg		// 除去後の図形情報
				)
{
	return 0;
}

//
//===========================================================================
//		線の反転
//
//		始終点を入れ替えて線の方向を反転する。
//		有意点列タイプは中間点列の並びも反転する。
//
//		fig1とfig2に同じメモリアドレスを渡しても良い。
//
//		図形は、３次元の線タイプ図形を対象とする。
//		（ZUKEI:: ConvPolygonを呼ぶ必要はない。）

//
MINT	MdzRevLine(
					 	MDFIG&		i_stFigLn, 	// 線の図形情報
					 	MDFIG*		o_pfigLn 	// 反転後の図形情報

				)
{
	return 0;
}

//
//===========================================================================
//		面の反転
//
//		面の表裏を反転する。
//		fig1とfig2に同じメモリアドレスを渡しても良い。
//
//		図形は３次元の面タイプ図形を対象とする。
//
MINT	MdzRevPlane(
						MDFIG&		i_stFigPln,	// 面の図形情報
						MDFIG*		o_pfigPln	// 反転後の図形情報

				)
{
	return 0;
}

//
//===========================================================================
//		論理演算
//
//		図形情報１と図形情報２の論理演算を行う。
//
//		処理モード=1の時は、２つの図形情報の結合を行う。
//		処理モード=2の時は、図形情報１から図形情報２の干渉部分を削除する。
//		処理モード=3の時は、図形情報１と図形情報２の干渉部分だけを残す。
//		処理モード=4の時は、図形情報１を図形情報２の干渉部分で切断する。
//		（切断後は２つ以上の図形情報になる。）
//
//		図形は、面および立体の図形を対象とする。
//		２次元、３次元どちらでも可。
//		（ZUKEI:: ConvPolygonを呼ぶ必要はない。）
//
//		演算後の図形情報は、平面、多面、多面体などの基本図形になる。
//
MINT	MdzBoolean(
						MINT		i_mdPrc,	// 処理モード（1:和 2:差 3:積 4:切断）
						MDFIG&		i_stFigZ1,	//	図形情報1
						MDFIG&		i_stFigZ2,	//	図形情報2
						MDFIG*		o_pfigZ3	//	演算後の図形情報
				)
{
	return 0;
}

} // namespace MC
