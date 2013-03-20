//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdLight.cpp
//
//		ウィンドウ
//
//
//  K.Matsu           01/19/08    Created.
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
//		光源の図形情報を得る
//
//		指定された光源の図形情報を得る
//		
//		※注意
//		　円柱、面光源は、画面（OpenGL）に対して無効で、POV−RAYに対してのみ有効。
//		　画面（OpenGL）に対して有効な光源は８個まで。
//		８個以上ある場合は、生成順に有効な光源８個がOpenGLに設定される。
//
MINT	MdlGet (
						MDID		i_idLgt,	// 光源Ker
						MDFIG*		o_figLgt	// 光源の図形情報
				)
{
	return 0;
}

//===========================================================================
//		光源の生成
//
//		指定された図形情報の光源を生成する。
//
//		光源を生成するだけで、画面の表示は行わない。
//		生成した光源を画面に反映したい場合には、Refreshを呼ぶ必要がある。
//
//		※注意
//		　円柱、面光源は、画面（OpenGL）に対して無効で、POV−RAYに対してのみ有効。
//		　画面（OpenGL）に対して有効な光源は８個まで。
//		８個以上ある場合は、生成順に有効な光源８個がOpenGLに設定される。
//
MINT	MdlCreate(
						MDID*		o_idLgt,	// 光源Ker
						MDFIG&		i_stFigLgt	// 光源の図形情報
				)
{
	return 0;
}

//===========================================================================
//		光源の変更
//
//		指定された光源を変更する。
//
//		光源の図形情報を変更するだけで、画面の表示は行わない。
//		生成した光源を画面に反映したい場合には、Refreshを呼ぶ必要がある。
//
//		※注意
//		　円柱、面光源は、画面（OpenGL）に対して無効で、POV−RAYに対してのみ有効。
//		　画面（OpenGL）に対して有効な光源は８個まで。
//		８個以上ある場合は、生成順に有効な光源８個がOpenGLに設定される。
//
MINT	MdlChange(
						MDID		i_idLgt,	// 光源Ker
						MDFIG&		i_stFigLgt	// 光源の図形情報
				)
{
	return 0;
}

//===========================================================================
//		光源の削除
//
//		指定された光源を削除する。
//
//		光源を削除するだけで、画面の表示は行わない。
//		光源を削除した結果を画面に反映したい場合には、Refreshを呼ぶ必要がある。
//
MINT	MdlDelete(
						MDID		i_idLgt		// 光源Ker
				)
{
	return 0;
}

//===========================================================================
//		光源の一覧を得る
//
MINT	MdlGetList(
						MDGID*		i_GidLgt	// 光源Kerリスト
												//	＜入力＞
												//	0:最初から   
												//	0以外:途中から         
												//	＜出力＞
												//	0:残データなし
												//	0以外:残データあり
				)
{
	return 0;
}

//===========================================================================
//		光源使用ウィンドウの再表示
//
//		変更された光源の結果を反映するためウィンドウの再表示を行う。
//
MINT	MdlRefresh( )
{
	return 0;
}

//===========================================================================
//		環境光の図形情報を得る
//
//		環境光の図形情報を得る。
//
//		環境光はデータベース毎に１つだけ設定することができる。
//		データベースオープン時に、初期値の値（白で強さ０．３）で設定される。
//
MINT	GetAmbient(
						MDFIG*		o_pfigKLgt	// 環境光の図形情報
				)
{
	return 0;
}

//===========================================================================
//		環境光の設定
//
//		環境光を設定する。
//
//		環境光を設定するだけで、画面の表示は行わない。
//		設定した環境光を画面に反映したい場合には、Refreshを呼ぶ必要がある。
//
MINT	MdlSetAmbient(
						MDFIG&		i_stFigKLgt	// 環境光の図形情報
				)
{
	return 0;
}

//===========================================================================
//		光源のデフォルト図形情報を得る
//
//		指定されたタイプの光源の図形情報を得る
//
//		※注意
//		　円柱、面光源は、画面（OpenGL）に対して無効で、POV−RAYに対してのみ有効。
//		　画面（OpenGL）に対して有効な光源は８個まで。
//		８個以上ある場合は、生成順に有効な光源８個がOpenGLに設定される。
//
MINT	MdlGetDefaultData(
						MgPoint3&	i_ptOrg		// 光源タイプ
												//	0:平行光源
												//	1:点光源
												//	2:スポット光源
												//	3:円柱光源
												//	4:面光源
												//	光源の図形情報
												//	figバッファーサイズ
												//	得られた光源の図形情報サイズ
				)
{
	return 0;
}

} // namespace MC