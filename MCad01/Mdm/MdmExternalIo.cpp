//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdExternal.cpp
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

namespace MC
{

//===========================================================================
//		DXF入力処理
//
//		指定されたファイル名のDXFファイルを入力する。
//
//		flenを０で渡すと本関数内でDXFファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdeDxfIn(
						MCHAR*		i_sFName		// DXFファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		DXF出力処理
//
//		指定されたファイル名でDXFファイルを出力する。
//
//		flenを０で渡すと本関数内でADFファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdeDxfOut(
						MCHAR*		i_sFName		// DXFファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		DXF入力パラメータを参照する
//
//		※　ival値について
//		mode＝1
//			ival: 0: ミリメートル、1: インチ、2: メートル
//		mode＝2
//			ival: 0: 閉じた線分を面にする、1: 閉じた線分は線にする
//		mode＝3
//			ival: 0: 複合図形を部品登録する、1: 複合図形を部品登録しない
//		mode＝4
//			ival: 1: TrueTypeフォントで表示、2: ベクターフォントで表示
//		mode＝5
//			ival: 0: 多面化しない、1: 多面化する
//		mode＝6
//			ival: 0: 256色、 1: 16色、 2: 8色
//
MINT	MdeGetDxfInParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:入力時単位の設定
													//	2:閉じた線分の設定
													//	3:複合図形の設定
													//	4:文字の種類
													//	5:隣り合う面の設定
													//	6:色数の設定
						MINT*		o_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		DXF入力パラメータを設定する
//
//		※　ival値について
//		mode＝1
//			ival: 0: ミリメートル、1: インチ、2: メートル
//		mode＝2
//			ival: 0: 閉じた線分を面にする、1: 閉じた線分は線にする
//		mode＝3
//			ival: 0: 複合図形を部品登録する、1: 複合図形を部品登録しない
//		mode＝4
//			ival: 1: TrueTypeフォントで表示、2: ベクターフォントで表示
//		mode＝5
//			ival: 0: 多面化しない、1: 多面化する
//		mode＝6
//			ival: 0: 256色、 1: 16色、 2: 8色
//
MINT	MdeSetDxfInParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:入力時単位の設定
													//	2:閉じた線分の設定
													//	3:複合図形の設定
													//	4:文字の種類
													//	5:隣り合う面の設定
													//	6:色数の設定
						MINT		i_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		DXF入力パラメータを設定する
//
//		※　ival値について
//		mode＝1
//			i_PtVal : MgPoint3	相対座標値を格納
//		DXF内の座標値にop[3]を足し算した結果で、取り込まれることになる。
//
MINT	MdeSetDxfInParamDoubleP(
						MINT		i_mdPar,		// パラメータの種類
													//	1:入力時単位の設定
						MgPoint3	i_PtVal			// パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		DXF出力パラメータを参照する
//
//		※　ival値について
//		mode＝1
//			ival: 0: ミリメートル、1: インチ、2: メートル
//		mode＝2の場合
//			ival: 0: 面を面として出力、 1: 面を線として出力
//		mode＝3の場合
//			ival: 0: 寸法線を寸法線として出力、1: 寸法線を要素分解して出力
//		mode＝4
//			ival: 0: 複合図形を出力しない、1: 部品を複合図形で出力、2: 全図形を複合図形として出力
//		mode＝5
//			ival: 0: テクスチャ名をレイヤ名としない、 1: テクスチャ名をレイヤ名とする
//
MINT	MdeGetDxfOutParamLong (
						MINT		i_mdPar,		// パラメータの種類
													//	1:出力時単位の設定
													//	2:面の設定
													//	3:寸法線の設定
													//	4:複合図形の設定
													//	5:テクスチャ図形の出力
						MINT*		o_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		DXF出力パラメータを設定する
//
//		※　ival値について
//		mode＝1
//			ival: 0: ミリメートル、1: インチ、2: メートル
//		mode＝2の場合
//			ival: 0: 面を面として出力、 1: 面を線として出力
//		mode＝3の場合
//			ival: 0: 寸法線を寸法線として出力、1: 寸法線を要素分解して出力
//		mode＝4
//			ival: 0: 複合図形を出力しない、1: 部品を複合図形で出力、2: 全図形を複合図形として出力
//		mode＝5
//			ival: 0: テクスチャ名をレイヤ名としない、 1: テクスチャ名をレイヤ名とする
//
MINT	MdeSetDxfOutParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:出力時単位の設定
													//	2:面の設定
													//	3:寸法線の設定
													//	4:複合図形の設定
													//	5:テクスチャ図形の出力
						MINT		i_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		JWW入力処理
//
//		指定されたファイル名のJWWファイルを入力する。
//
//		flenを０で渡すと本関数内で入力するファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdeJwwIn(
						MCHAR*		i_sFNameDxf	// DXFファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		JWW入力パラメータを参照する
//
//		※　ival値について
//		mode＝1
//			ival : 0 : 立面図を起こさない、1 : 立面図を起こす
//		mode＝2
//			ival : 0 : JWWに背景色を合わせる、1 : JWWに背景色を合わせない
//		mode＝3
//			ival : 0 : ワイヤーで表示する、1 : 面で表示する、2 : 面とエッジで表示
//
MINT	MdeGetJwwInParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:起こし絵の設定
													//	2:背景色の設定
													//	3:管の表示設定
						MINT*		o_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		JWW入力パラメータを設定する
//
//		※　ival値について
//		mode＝1
//			ival : 0 : 立面図を起こさない、1 : 立面図を起こす
//		mode＝2
//			ival : 0 : JWWに背景色を合わせる、1 : JWWに背景色を合わせない
//		mode＝3
//			ival : 0 : ワイヤーで表示する、1 : 面で表示する、2 : 面とエッジで表示
//
MINT	MdeSetJwwInParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:起こし絵の設定
													//	2:背景色の設定
													//	3:管の表示設定
						MINT		i_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		ADF入力処理
//
//		指定されたファイル名のADFファイルを入力する。
//
//		flenを０で渡すと本関数内で入力するファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdeADFIn(
						MCHAR*		i_sFNameAdf	// ADFファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		ADF出力処理
//
//		指定されたファイル名でADFファイルを出力する。
//
//		flenを０で渡すと本関数内でADFファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdeADFOut(
						MCHAR*		i_sFNameAdf	// ADFファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		Pov-Rayファイルを作成する
//
//		ウィンドウIDに表示されているすべての物をそのウィンドウの視点で、Pov-Rayファイルに出力する。
//
//		flenを０で渡すと本関数内で入力するファイル名を問い合わせる。（コモンダイアログ表示）
//
MINT	MdePovRayOut(
						MINT		i_idWin,		// ウィンドウID
						MCHAR*		i_sFnamePov	// Pov-Rayファイル名　または　０
				)
{
	return 0;
}

//
//===========================================================================
//		Pov-Rayを起動しイメージファイルを作成する
//
//		Pov-Rayを起動して、指定されたPov-Rayファイル名のイメージファイルを作成する。
//
MINT	MdePovRayExecute(
						MCHAR*		i_sFNamePov,	// Pov-Rayファイル名
						MCHAR*		i_sFNameImg	// イメージファイル名

				)
{
	return 0;
}

//
//===========================================================================
//		Pov-Ray出力パラメータを参照する
//
//		※　mode＝3のival値について
//		ival : 0 〜　１１　(大きくなるほどきれいになる。)
//
MINT	MdeGetPovRayOutParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:出力イメージの幅
													//	2:出力イメージの高さ
													//	3:クォリティ設定
						MINT*		o_iPar			// パラメータ値（modeによって異なる）
				)
{
	return 0;
}

//
//===========================================================================
//		Pov-Ray出力パラメータを設定する
//
//		※　mode＝3のival値について
//		ival : 0 〜　１１　(大きくなるほどきれいになる。)
//
MINT	MdeSetPovRayOutParamLong(
						MINT		i_mdPar,		// パラメータの種類
													//	1:出力イメージの幅
													//	2:出力イメージの高さ
													//	3:クォリティ設定
						MINT		i_iPar			//	パラメータ値（modeによって異なる）
				)
{
	return 0;
}

} // namespace MC
