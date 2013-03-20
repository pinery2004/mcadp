//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdZukei.cpp
//
//		ウィンドウ
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
#include "MdmDB.h"

namespace MC
{

////===========================================================================
////		図形の生成
////
////		エンティティに図形情報を設定する。
////
//MINT	MdzSet (
//						MDID		i_idEnt,	// エンティテイID
//						MDFIG&		i_GiFig		// 図形情報
//				)
//{
//	ASSERT( MDISENT( i_idEnt));
//
//	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_stFig.m_GiFig = i_GiFig;
//	return 0;
//}
//
////===========================================================================
////		エンティテイに部材配置の設定
////
////		エンティテイに指定部品を配置する部材配置プリミティブを設定する。
////		配置壱と方向、大きさは配置座標系マトリックスで指定する。
////
//MINT	MdzSetPartPlc (
//						MDID		i_idEnt,	// エンティテイID
//						MgMat3E*		i_pmat,		// 配置座標系マトリックス
//						MDID		i_idB		// 部品ID
//				)
//{
//	return 0;
//}
//
////===========================================================================
////		エンティテイより図形情報を取り出す
////
//MINT	MdzGet (
//						MDID		i_idEnt,	// エンティテイID
//						MDFIG*		o_pstFig	// 図形情報
//				)
//{
//	return 0;
//}
//
////===========================================================================
////		エンティテイの図形情報を変更
////
//MINT	MdzChange (
//						MDID		i_idEnt,	// エンティテイID
//						MDFIG&		i_pstFig	// 図形情報
//				)
//{
//	return 0;
//}

//===========================================================================
//		図形情報の座標変換
//
MINT DZukei::MdzTrans (
						MgMat3E&		i_Mat,		// 配置座標系マトリックス
						MDFIG&		i_stFig,	// 図形情報
						MDFIG*		o_pstFig	// 座標変換後図形情報
				)
{
	return 0;
}

//===========================================================================
//		図形情報の移動
//
MINT DZukei::MdzMove (
						MgVect3&	i_VMv,		// 移動ベクトル
						MDFIG&		i_stFig,	// 図形情報
						MDFIG*		o_pstFig	// 座標変換後図形情報
				)
{
	return 0;
}

//===========================================================================
//		図形情報の座標変換
//
MINT DZukei::MdzMirror (
						MREAL		i_pln[4],	// 面情報（ax+by+cz+d=0）
						MDFIG&		i_stFig,	// 図形情報
						MDFIG*		o_pstFig	// 座標変換後図形情報
				)
{
	return 0;
}

//===========================================================================
//		図形情報の拡大
//
//		指定された原点を基点に指定の拡大率で図形を拡大／縮小する。
//
MINT DZukei::MdzExpansion (
						MgPoint3&	i_ptOrg,	// 原点
						MREAL		i_rScl,		// 拡大率
						MDFIG&		i_stFig,	// 図形情報
						MDFIG*		o_pstFig	// 座標変換後図形情報
				)
{
	return 0;
}

//===========================================================================
//		図形情報の取り出し時の座標系の問い合わせ
//
//		図形情報の取り出し時の座標系Dpr-IDを得る。
//		Getで取り出した図形情報や、Create、Changeで指定する図形情報は、
//		この座標系で記述されたものとみなされる。
//		通常、この座標系はカレントグループの座標系が設定されている。
//
MINT DZukei::MdzGetCoord ()							// 座標系Dpr-ID
{
	return 0;
}

//===========================================================================
//		図形情報の取り出し時の座標系を設定
//
//		図形情報の取り出し時の座標系Dpr-IDを設定する。
//		Getで取り出した図形情報や、Create、Changeで指定する図形情報は、
//		この座標系で記述されたものとみなされる。
//		通常、この座標系はカレントグループの座標系が設定されている。
//
MINT DZukei::MdzSetCoord (
					 	MDID		i_idCodDpr	// 座標系Dpr-ID
				)
{
	return 0;
}

//===========================================================================
//		図形情報の取り出し時の表示属性出力モードの問い合わせ
//
//		Getで図形情報を取り出す時の表示属性取り出しモードの値を参照する。
//
//		Getで指定されたプリミティブDprに、表示属性が記録されていた場合、
//		表示属性取り出しモードが0の時は、表示属性の無い図形情報を取り出す。
//		表示属性取り出しモードが1の時は、表示属性の有る図形情報を取り出す。
//
MINT	MdzGetAtrMode ()					 	// 表示属性取り出しモード
												//	0 : 出力 無
												//　1 : 出力 有
{
	return 0;
}

//===========================================================================
//		図形情報の取り出し時の表示属性出力モードの設定
//
//		Getで図形情報を取り出す時の表示属性取り出しモードの値を設定する。
//
//		Getで指定されたプリミティブDprに、表示属性が記録されていた場合、
//		表示属性取り出しモードが0の時は、表示属性の無い図形情報を取り出す。
//		表示属性取り出しモードが1の時は、表示属性の有る図形情報を取り出す。
//
MINT	MdzSetAtrMode (
					 	MINT		i_mdAtr		// 表示属性取り出しモード
												//	0 : 出力 無
												//　1 : 出力 有
				)
{
	return 0;
}

//===========================================================================
//		表示図形のＢＯＸを得る
//
//		指定された図形情報を包含する３次元のBOX情報を得る。
//
MINT	MdzGetBox (
						MDFIG&		i_pFig,		//	図形情報バッファ
						MgRect3*	o_prect		//  BOX図形情報バッファ
												//	(最小点から最大点までの線分の図形情報)
				)
{
	return 0;
}

//===========================================================================
//		図形情報のポリゴン展開
//
//		与えられた図形情報をポリゴン展開する。
//		展開後の図形情報は、線分、有意点列、平面、多面、多面体などの基本プリミティブになる。
//		展開後の図形情報プリミティブは、本関数に与えられる図形情報およびMszSetConvValueLong、
//		MszSetConvValueDoubleで設定されるポリゴン展開処理モードにより決定する。
//
MINT	MdzConvPolygon (
						MDFIG&		i_pFig,		//	図形情報バッファ
						MDFIG*		o_pFig		//	図形情報バッファ
				)
{
	return 0;
}

//===========================================================================
//		ポリゴン展開処理モード値（ｌｏｎｇ）の問い合わせ
//
//		ConvPolygonで図形情報をポリゴン展開する際の各処理モードを問い合わせる。
//		指定されたタイプのポリゴン展開処理モード値を返す。
//
MINT	MdzGetConvValueInt (
						MINT		i_mdTenkai,	//	ポリゴン展開処理モードタイプ
						MINT*		o_piValue	//	値
				)
{
	return 0;
}

//===========================================================================
//		ポリゴン展開処理モード値（ｌｏｎｇ）の問い合わせ
//
//		ConvPolygonで図形情報をポリゴン展開する際の各処理モードを設定する。
//		指定したタイプのポリゴン展開処理モードに値を設定する。
//
MINT	MdzSetConvValueInt (
						MINT		i_mdTenkai,	//	ポリゴン展開処理モードタイプ
						MINT		i_iValue	//	値
				)
{
	return 0;
}

//===========================================================================
//		ポリゴン展開処理モード値（ｆ ｌ ｏ ａ ｔ）の問い合わせ
//
//		ConvPolygonで図形情報をポリゴン展開する際の各処理モードを問い合わせる。
//		指定されたタイプのポリゴン展開処理モード値を返す。
//
MINT	MdzGetConvValueDouble (
						MINT		i_mdTenkai,	//	ポリゴン展開処理モードタイプ
						MREAL*		o_prValue	//	値
				)
{
	return 0;
}

//===========================================================================
//		ポリゴン展開処理モード値（ｆ ｌ ｏ ａ ｔ）の設定
//
//		ConvPolygonで図形情報をポリゴン展開する際の各処理モードを設定する。
//		指定したタイプのポリゴン展開処理モードに値を設定する。
//
MINT	MdzSetConvValueDouble (
						MINT		i_mdTenkai,	//	ポリゴン展開処理モードタイプ
						MREAL		i_rValue	//	値
				)
{
	return 0;
}

//===========================================================================
//		図形情報から属性情報をとる
//
//		指定した図形情報から属性情報をとった図形情報を返す。
//
MINT	MdzRemoveAtr (
						MDFIG&		i_pFig,		//	図形情報バッファ
						MDFIG*		o_pFig		//	図形情報バッファ
				)
{
	return 0;
}

} // namespace MC