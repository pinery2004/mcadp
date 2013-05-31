//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdWin.cpp
//
//		ウィンドウ
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"

#include "MdModel.h"
#include "MdmDB.h"
#include "Mmlib.h"
#include "MmCmdMsg.h"
#include "MainFrm.h"

namespace MC
{

//===========================================================================
//		座標変換マトリックスを求める（視点座標 -> DB座標）
//
MINT	MdwTransMatrixViewToWorld (
						MDID		i_idWin,	// ウィンドウＩＤ
						MDID		i_idDB,		// DB座標系
						MgMat3E*		o_pmatVtD	// 座標変換マトリックス (視点座標 -> DB座標)
				)
{
	return 0;
}

//
//===========================================================================
//		座標変換マトリックスを求める（DB座標 -> 視点座標）
//
MINT	MdwTransMatrixWorldToView (
						MDID		i_idDB,		// DB座標系
						MDID		i_idWin,	// ウィンドウＩＤ
						MgMat3E*		o_pmatDtV	// 座標変換マトリックス (視点座標 -> DB座標)
				)
{
	return 0;
}

//
//===========================================================================
//		座標変換マトリックスを求める（pixel座標 -> 視点座標）
//
MINT	MdwTransMatrixPixelToView (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgMat3E*		o_pmatPtV	// 座標変換マトリックス (pixel座標 -> 視点座標)
				)
{
	return 0;
}

//
//===========================================================================
//		座標変換マトリックスを求める（視点座標 -> pixel座標）
//
MINT	MdwTransMatrixViewToPixel (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgMat3E*		o_pmatVtP	// 座標変換マトリックス (視点座標 -> pixel座標)
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの視点座標変換マトリックスを取得する
//
MINT	MdwGetEyeCoord (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgMat3E*		o_pmatV		// 視点座標変換マトリックス（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの視点座標変換マトリックスを設定する
//
MINT	MdwSetEyeCoord (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgMat3E*		i_pmatV		// 視点座標変換マトリックス（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの機能番号に対する視点座標変換マトリックスを取得する
//
MINT	MdwGetTypeEyeCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		o_pmatV		// 視点座標変換マトリックス（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの機能番号に対する視点座標変換マトリックスを設定する
//
MINT	MdwSetTypeEyeCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		i_pmatV		// 視点座標変換マトリックス（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		注視点を取得する
//
MINT	MdwGetLookPoint (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgPoint3D*	o_pptLook	// 注視点座標（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		注視点を設定する
//
MINT	MdwSetLookPoint (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgPoint3D*	i_pptLook	// 注視点座標（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対する注視点を取得する
//
MINT	MdwGetTypeLookPoint (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgPoint3D*	o_pptLook	// 注視点座標（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対する注視点を設定する
//
MINT	MdwSetTypeLookPoint (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgPoint3D*	i_pptLook	// 注視点座標（基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのクリッピング座標を取得する
//
MINT	MdwGetZClipping (
						MDID		i_idWin,	// ウィンドウＩＤ
						MREAL		o_rZClp[2]	// クリッピング前面、後面
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのクリッピング座標を設定する
//
MINT	MdwSetZClipping (
						MDID		i_idWin,	// ウィンドウＩＤ
						MREAL		i_rZClp[2]	// クリッピング前面、後面
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対するクリッピング座標を取得する
//
MINT	MdwGetTypeZClipping (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		o_rZClp[2]	// クリッピング前面、後面
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対するクリッピング座標を設定する
//
MINT	MdwSetTypeZClipping (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		i_rZClp[2]	// クリッピング前面、後面
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのウィンドウ表示属性を取得する
//
MINT	MdwGetDispAtr (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		o_iDspA[4]	// 表示属性テーブル
												//	[0]: 塗り潰し（0=ﾜｲﾔｰ、1=ｿﾘｯﾄﾞ、2=既定）
												//	[1]:スムーズ（0=OFF、1=ON）
												//	[2]:スポット対応（0=OFF、1=ON）
												//	[3]:図形の取出し（1=奥、2=断面、3=奥と断面）
												//	（断面のみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのウィンドウ表示属性を設定する
//
MINT	MdwSetDispAtr (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		i_iDspA[4]	// 表示属性テーブル
												//	[0]: 塗り潰し（0=ﾜｲﾔｰ、1=ｿﾘｯﾄﾞ、2=既定）
												//	[1]:スムーズ（0=OFF、1=ON）
												//	[2]:スポット対応（0=OFF、1=ON）
												//	[3]:図形の取出し（1=奥、2=断面、3=奥と断面）
												//	（断面のみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対するウィンドウ表示属性を取得する
//
MINT	MdwGetTypeDispAtr (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		o_iDspA[4]	// 表示属性テーブル
												//	[0]: 塗り潰し（0=ﾜｲﾔｰ、1=ｿﾘｯﾄﾞ、2=既定）
												//	[1]:スムーズ（0=OFF、1=ON）
												//	[2]:スポット対応（0=OFF、1=ON）
												//	[3]:図形の取出し（1=奥、2=断面、3=奥と断面）
												//	（断面のみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ機能番号に対するウィンドウ表示属性を設定する
//
MINT	MdwSetTypeDispAtr (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		i_iDspA[4]	// 表示属性テーブル
												//	[0]: 塗り潰し（0=ﾜｲﾔｰ、1=ｿﾘｯﾄﾞ、2=既定）
												//	[1]:スムーズ（0=OFF、1=ON）
												//	[2]:スポット対応（0=OFF、1=ON）
												//	[3]:図形の取出し（1=奥、2=断面、3=奥と断面）
												//	（断面のみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのカレント拡大率を取得する
//
MINT	MdwGetScale (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL*		o_prScale	// 拡大率
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウのカレント拡大率を設定する
//
MINT	MdwSetScale (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		i_rScale	// 拡大率
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの表示領域の問い合わせを取得する
//
MINT	MdwGetRange (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgPoint3D	o_ptArea[2]	// 表示領域（左下点、右上点）
												//	視点系での座標値
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの表示領域の問い合わせを設定する
//
MINT	MdwSetRange (
						MDID		i_idWin,	// ウィンドウＩＤ
						MgPoint3D	i_ptArea[2]	// 表示領域（左下点、右上点）
												//	視点系での座標値
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの画角を取得する（透視ウィンドウのみ）
//		指定されたウィンドウが透視ウィンドウ以外の場合は無効
//
MINT	MdwGetAngle (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL*		o_prAgl		// 画角
				)
{
	return 0;
}


//
//===========================================================================
//		ウィンドウの画角を設定する（透視ウィンドウのみ）
//		指定されたウィンドウが透視ウィンドウ以外の場合は無効
//
MINT	MdwSetAngle (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MREAL		i_rAgl		// 画角
				)
{
	return 0;
}

//
//===========================================================================
//		スクロール
//
MINT	MdwScroll (
						MDID		i_idWin,	// ウィンドウId
						MgPoint2D	i_vMv		// 移動ベクトル（視点座標系でのベクトル）
				)
{
	return 0;
}

//
//===========================================================================
//		パンニング
//
MINT	MdwPanning (
						MDID		i_idWin,	// ウィンドウId
						MgPoint2D	i_ptCnt		// 画面の中心としたい点（視点座標系での座標値）
				)
{
	return 0;
}

//
//===========================================================================
//		フィット表示（表示物が画面上に全て表示されるようにする）
//
MINT	MdwFit ( 
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		フィット表示（表示物が画面上に全て表示されるようにする）
//
//		指定されたウィンドウの現在の視点情報を、そのウィンドウの初期表示の視点情報として記録する。
//		視点情報とは、視点座標、注視点、クリッピング等視点に関する値全てを含む。
//
MINT	MdwSaveFirstView(
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		初期表示を行う
//
//		指定されたウィンドウの視点情報を、記録されている初期表示の視点情報に設定して再描画する。
//		視点情報とは、視点座標、注視点、クリッピング等視点に関する値全てを含む。
//
MINT	MdwSetFirstView (
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		直前表示を行う
//
//		渡されたウィンドウの直前表示を行う。
//
//		ウィンドウは、視点座標系の変更やスクロール、拡大／縮小など視点が変更される度に
//		視点情報の履歴を記録する。
//		本関数は、この履歴を遡って１つ前の視点に戻し表示を行う。（アンドゥ）
//		DispViewAfterは、本関数で戻された視点を１つ後に直し表示を行う。（リドゥ）
//
//		視点変更の履歴は、ウィンドウ毎に記録され、ウィンドウをクローズすると破棄される。
//
MINT	MdwDispViewBefore (
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		直後表示を行う
//
//		渡されたウィンドウの直後表示を行う。
//
//		ウィンドウは、視点座標系の変更やスクロール、拡大／縮小など視点が変更される度に
//		視点情報の履歴を記録する。
//		DispViewBeforeは、この履歴を遡って１つ前の視点に戻し表示を行う。（アンドゥ）
//		本関数は、DispViewBeforeで戻された視点を１つ後に直し表示を行う。（リドゥ）
//
//		視点変更の履歴は、ウィンドウ毎に記録され、ウィンドウをクローズすると破棄される。
//
MINT	MdwDispViewAfter (
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		視点を記録する
//
//		渡されたウィンドウの現在の視点を記録する。
//		記録した視点はDispViewListで戻すことができる。
//
//		視点情報は機能番号毎に記録される。（最大１０個）
//		同じ機能のウィンドウが複数オープンされている場合、記録した情報は共有される。
//		　ウィンドウが全てクローズされた場合でも、記録した情報は保持される。
//
MINT	MdwSaveViewList (
						MDID		i_idWin,	// ウィンドウId
						MDID		i_idView	// 視点記録インデックス
				)
{
	return 0;
}

//
//===========================================================================
//		記録された視点に変更し表示
//
//		渡されたウィンドウの視点をDispViewListで記録された視点に変更する。
//
//		視点情報は機能番号毎に記録される。（最大１０個）
//		同じ機能のウィンドウが複数オープンされている場合、記録した情報は共有される。
//		　ウィンドウが全てクローズされた場合でも、記録した情報は保持される。
//
MINT	MdwDispViewList (
						MDID		i_idWin,	// ウィンドウId
						MDID		i_idView	// 視点記録インデックス
				)
{
	return 0;
}

//
//===========================================================================
//		視点記録をクリアする（１つ）
//
//		渡された視点記録インデックスに記録されている視点情報を１つ消去する。
//
MINT	MdwClearViewList(
						MDID		i_idView	// 視点記録インデックス
				)
{
	return 0;
}

//
//===========================================================================
//		視点記録をクリアする
//
//		渡されたウィンドウの機能番号に記録されている視点情報を全て消去する。
//
MINT	MdwClearViewListAll(
						MDID		i_idWFn		// ウィンドウ機能番号
				)
{
	return 0;
}

//
//===========================================================================
//		背景イメージを取得
//
//		ウィンドウの背景に貼り付けるイメージの情報を取得する。
//
MINT	MdwGetBackImage(
						MDID		i_idWin,	// ウィンドウId
						MINT*		o_pmdPst,	// 貼り付けるモード
												//	0:ウィンドウにあわせる
												//　1:縦横比固定　小さいほうにあわせる
												//　2:縦横比固定　大きいほうにあわせる
						MINT*		o_pmdDsp,	// 表示モード　0:なし　1:外部ファイル　2: テクスチャ
						MCHAR		o_snmT[],	// テクスチャorファイル名
						MINT		i_sznmT		// o_snmTバッファーサイズ
				)
{
	return 0;
}

//
//===========================================================================
//		背景イメージを設定
//
//		ウィンドウの背景に貼り付けるイメージを設定する。
//		この関数では、イメージに関する情報を設定するだけで表示は行わない。
//		設定後は、描画関数
//		　　DispBackimage
//		を必ず呼ぶ必要がある。
//
MINT	MdwSetBackImage(
						MDID		i_idWin,	// ウィンドウId
						MINT		i_mdPst,	// 貼り付けるモード
												//	0:ウィンドウにあわせる
												//　1:縦横比固定　小さいほうにあわせる
												//　2:縦横比固定　大きいほうにあわせる
						MINT		i_mdDsp,	// 表示モード　0:なし　1:外部ファイル　2: テクスチャ
						MCHAR		i_snmT[],	// テクスチャorファイル名
						MINT		i_nnmT		// ファイル名サイズ
				)
{
	return 0;
}



//
//===========================================================================
//		背景イメージの表示
//
//		ウィンドウの背景に設定されたイメージを表示する。
//
MINT	MdwDispBackImage(
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ領域を取得
//
//		ウィンドウ描画領域を取得する。タイトル部分は含めない。
//
//		ウィンドウ描画領域は、MDIクライアントの描画領域の左上を基点（0,0）とした
//		左下点（X,Y）・右上点（X,Y）を返す。
//
MINT	MdwGetRect (
						MDID		i_idWin,	// ウィンドウId
						CPoint		i_iRect[2]	//	ウィンドウ領域（ピクセル）(左下、右上)
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ領域を設定
//
//		ウィンドウ描画領域を設定する。タイトル部分は含めない。
//
//		ウィンドウ描画領域は、MDIクライアントの描画領域の左上を基点（0,0）とした
//		左下点（X,Y）・右上点（X,Y）で設定する。
//
MINT	MdwSetRect (
						MDID		i_idWin,	// ウィンドウId
						CPoint		i_iRect[2]	//	ウィンドウ領域（ピクセル）(左下、右上)
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウ領域を設定
//
//		ウィンドウ描画領域を設定する。タイトル部分は含めない。
//
//		ウィンドウ描画領域は、MDIクライアントの描画領域の左上を基点（0,0）とした
//		左下点（X,Y）・右上点（X,Y）で設定する。
//
MINT	MdwSetState (
						MDID		i_idWin,	// ウィンドウId
						INT			i_mdDsp		// モード
												//　1:　最小化（アイコン化）
												//	2:　最大化
												//	0:　縮小（元に戻す）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの整列
//
//		オープンされているタイトル付きウィンドウの整列を行う。
//		オープンされているウィンドウがカスケードタイプの場合は無効。（戻り値＝０で返す）
//
//		本関数はGUIの「表示」メニュー下の並べ替えメニューと同様の動作を行う。
//
MINT	MdwAlignment (
						INT			i_mdDsp		// 表示モード
												//	1 : 重ねて表示
												//	2 : 上下に並べて表示
												//	3 : 左右に並べて表示
												//	4 : 予約（未使用）
												//	5 : アイコンの整列
				)
{
	return 0;
}

//
//===========================================================================
//		オープンモード（カスケードタイプ）を取得
//
//		現在オープンされているウィンドウのカスケードタイプを問い合わせる。
//		ウィンドウが１枚もオープンされていない場合や、カスケード以外
//		（タイトル付きウィンドウ）がオープンされている場合は、戻り値＝０を返す。
//
MINT	MdwGetCascadeMode (
						INT			i_mOpn		// オープンモード
												//	1:　１面
												//	2:　２面（横並び）（左・右）
												//	3:　２面（縦並び）（上・下）
												//	4:　３面（左・右上・右下）
												//	5:　４面（左上・右上・左下・右下）
												//	0:　ウィンドウ無し
												//	　　　またはタイトル付きウィンドウ
				)
{
	return 0;
}


//
//===========================================================================
//		自動スクロール有効フラグの問い合わせ
//
//		GUIの操作で、ウィンドウの端でマウスクリック・ドラッグ時に
//		画面をスクロールする機能を有効にする／しないのフラグを問い合わせる。
//
//		このフラグはシステム全体で共通であり、オープンされている全ウィンドウ、
//		および以後生成する全てのウィンドウに適用される。
//
MINT	MdwGetAutoScrollFlg ()						// 自動スクロール有効フラグ
												//　0:　無効
												//　1:　有効
{
	return 0;
}

//
//===========================================================================
//		自動スクロール有効フラグの設定
//
//		GUIの操作で、ウィンドウの端でマウスクリック・ドラッグ時に
//		画面をスクロールする機能を有効にする／しないのフラグを設定する。
//
//		このフラグはシステム全体で共通であり、オープンされている全ウィンドウ、
//		および以後生成する全てのウィンドウに適用される。
//
MINT	MdwSetAutoScrollFlg (
						MINT		i_ifAtScl	// 自動スクロール有効フラグ
												//　0:　無効
												//　1:　有効
				)
{
	return 0;
}

//
//===========================================================================
//		拡大ホイール方向の問い合わせ
//
//		マウスホイールの回転によるウィンドウ拡大／縮小の操作における、
//		ホイールの回転方向を問い合わせる。
//
//		フラグ値＝０の場合
//		　手前方向：縮小
//		　奥　方向：拡大
//		フラグ値＝１の場合
//		　手前方向：拡大
//		　奥　方向：縮小
//
MINT	MdwGetWheelFlg ()							// 拡大ホイール方向フラグ
												//　0:　奥方向で拡大
												//　1:　手前方向で拡大
{
	return 0;
}

//
//===========================================================================
//		拡大ホイール方向の問い合わせ
//
//		マウスホイールの回転によるウィンドウ拡大／縮小の操作における、
//		ホイールの回転方向を問い合わせる。
//
//		フラグ値＝０の場合
//		　手前方向：縮小
//		　奥　方向：拡大
//		フラグ値＝１の場合
//		　手前方向：拡大
//		　奥　方向：縮小
//
MINT	MdwSetWheelFlg (
						MINT		i_ifWheel	// 拡大ホイール方向フラグ
												//　0:　奥方向で拡大
												//　1:　手前方向で拡大
				)
{
	return 0;
}

//
//===========================================================================
//		アイコンメニュー表示フラグの設定
//
//		ウィンドウ下部のアイコンメニューを表示する／しないのフラグを設定する。
//		このフラグはシステム全体で共通であり、オープンされている全ウィンドウ、
//		および以後生成する全てのウィンドウに適用される。
//
MINT	MdwSetIconMenuFlg (
						MINT		i_ifACDsp	// アイコンメニュー表示フラグ
												//　0:　表示しない
												//　1:　表示する
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウオープン時の初期表示のモードを問い合わせる。
//
//		本関数は、GUIの「ウィンドウ」−「設定」メニューで表示されるウィンドウ設定表の
//		“初期表示”の値を問い合わせる。
//
MINT	MdwGetFirstDispMode ()				// 表示モード
												//	0:　カレントレイヤのみ表示
												//	1:　全て表示
												//　2:　何も表示しない
{
	return 0;
}

//===========================================================================
//		ウィンドウオープン時の初期表示のモードを設定する。
//
//		本関数は、GUIの「ウィンドウ」−「設定」メニューで表示されるウィンドウ設定表の
//		“初期表示”の値を設定する。
//
MINT	MdwSetFirstDispMode (
						MINT		i_mdDsp		// 表示モード
												//	0:　カレントレイヤのみ表示
												//	1:　全て表示
												//　2:　何も表示しない
				)
{
	return 0;
}


//
//===========================================================================
//		ウィンドウオープン時の縮尺のモードおよび初期値を問い合わせる。	
//
//		本関数は、GUIの「ウィンドウ」−「設定」メニューで表示されるウィンドウ設定表の
//		“縮尺”の各値を問い合わせる。
//
MINT	MdwGetDefaultScale (	
						MDID*		i_pidWFn,	// モード
												//　0:　設定された縮尺でオープンする
												//　1:　カレントウィンドウの縮尺でオープンする
												//　2:　フィット表示でオープンする
						MREAL*		o_pScl		// 縮尺の分母（mode=0のときのみ有効）
				)
{
	return 0;
}

//===========================================================================
//		ウィンドウオープン時の縮尺のモードおよび初期値を設定する。
//
//		本関数は、GUIの「ウィンドウ」−「設定」メニューで表示されるウィンドウ設定表の
//		“縮尺”の各値を設定する。
//
MINT	MdwSetDefaultScale (	
						MDID		i_idWFn,	// モード
												//　0:　設定された縮尺でオープンする
												//　1:　カレントウィンドウの縮尺でオープンする
												//　2:　フィット表示でオープンする
						MREAL		i_Scl		// 縮尺の分母（mode=0のときのみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウオープン時の大きさ問い合わせ	
//
//		ウィンドウオープン時の大きさのモードおよび幅、高さの初期値を問い合わせる。
//
//		本関数は、GUIの「ウィンドウ」−「設定」メニューで表示されるウィンドウ設定表の“大きさ”の
//		各値を問い合わせる。
//
MINT	MdwGetDefaultSize (	
						MDID		i_idWFn	// モード
												//	0:　フルスクリーン
												//	1:　１／２
												//	2:　１／４
												//	3:　幅×高　指定
												//	幅　（ピクセル値）（mode=3の時のみ有効）
												//	高さ（ピクセル値）（mode=3の時のみ有効）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウオープン	
//
//		指定された機能のウィンドウを新規にオープンする。
//		既にカスケードタイプのウィンドウがオープンされている場合は、全ウィンドウクローズ後に
//		新規オープンされる。
//
//		機能番号は別紙「機能番号一覧」を参照。
//		ウィンドウ枠は、メインフレームのウィンドウ描画領域内のピクセル値で、
//		左上を基点（0,0）とした左下点（X,Y）・右上点（X,Y）を指定する。
//
//		本関数はタイトル付きウィンドウをオープンする。
//		カスケードウィンドウをオープンする場合は、OpenExを使用する。
//
MINT	MdwSetDefaultSize (	
						MDID		i_idWFn,	// ウィンドウ機能番号
						CPoint		i_iRect[2],	// ウィンドウ領域（ピクセル）(左下、右上)
						MREAL		i_rScl,		// 拡大率（原寸=1.0）
						MINT		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウオープン	
//
//		指定された機能のウィンドウを新規にオープンする。
//		既にカスケードタイプのウィンドウがオープンされている場合は、全ウィンドウクローズ後に
//		新規オープンされる。
//
//		機能番号は別紙「機能番号一覧」を参照。
//		ウィンドウ枠は、メインフレームのウィンドウ描画領域内のピクセル値で、
//		左上を基点（0,0）とした左下点（X,Y）・右上点（X,Y）を指定する。
//
//		本関数はタイトル付きウィンドウをオープンする。
//		カスケードウィンドウをオープンする場合は、OpenExを使用する。
//
MINT	DWin::MdwOpen (	
						MDID		i_idWFn,	// ウィンドウ機能番号
						CPoint		i_iRect[2],	// ウィンドウ領域（ピクセル）(左下、右上)
						MREAL		i_rScl,		// 拡大率（原寸=1.0）
						MINT		i_idWin		// ウィンドウId
				)
{
	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_MYMESSAGE_WINDOW);
	return 0;
}

//
//===========================================================================
//		オープンするウィンドウの機能設定（OpenExに有効）	
//
//		OpenEXでカスケードタイプのウィンドウをオープンする際の各ウィンドウの機能番号を設定する。
//		オープンモードによりウィンドウの枚数と配置を指定する。
//		機能番号はオープンするウィンドウの枚数分を指定する。
//		（※modeに対応する配列数を保障する事。）
//
//		各モードに対して設定した機能番号は、システム終了時まで保持される。
//		規定値は下記の通り。
//		　1:　１面（透視）
//		　2:　２面（透視・平面）
//		　3:　２面（透視・平面）
//		　4:　３面（透視・平面・南立面）
//		　5:　４面（アクソメ・平面・南立面・東立面）
//
MINT	MdwSetOpenType (	
						MINT		i_tpScm,	// オープンモード
												//　1:　１面
												//　2:　２面（横並び）（左・右）
												//　3:　２面（縦並び）（上・下）
												//	4:　３面（左・右上・右下）
												//	5:　４面（左上・右上・左下・右下）
						MINT		i_idWFn[4]	// ウィンドウ機能番号セット
												//	（modeの値により配列数が決まる。上記順序で返る。）
				)
{
	return 0;
}

//
//===========================================================================
//		カスケードタイプのウィンドウオープン	
//
//		カスケードタイプのウィンドウを新規にオープンする。
//		既にタイトル付きウィンドウがオープンされている場合は、全ウィンドウクローズ後に新規オープンされる。
//
//		オープンモードによりウィンドウの枚数と配置を指定する。
//		ウィンドウIDはオープンするウィンドウの枚数分を返す。
//		（※modeに対応する配列数を保障する事。）
//		各ウィンドウの機能番号は、事前にSetOpenTypeで指定する。
//
//		本関数はカスケードウィンドウをオープンする。
//		タイトル付きウィンドウをオープンする場合は、Openを使用する。
//
MINT	MdwOpenEx (	
						MINT		i_tpScm,	// オープンモード
												//　1:　１面
												//　2:　２面（横並び）（左・右）
												//　3:　２面（縦並び）（上・下）
												//	4:　３面（左・右上・右下）
												//	5:　４面（左上・右上・左下・右下）
						MINT		o_idWin[4]	// ウィンドウＩＤセット
												//	（modeの値により配列数が決まる。上記順序で返る。）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの削除
//
//		渡されたウィンドウを削除（クローズ）する。
//		他のウィンドウが1つ以上存在し、カスケードタイプで表示されている場合は、
//		残ウィンドウの位置・大きさが自動調整される。
//
MINT	MdwClose (	
						MINT		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		オープンされているウィンドウを得る	
//
//		シノニムウィンドウとは、フレームを持たないウィンドウで、他のシノニム以外のウィンドウ上に
//		表示領域を持つウィンドウである。
//		親ウィンドウ（領域を貼り付けたウィンドウ）上に表示を行う以外は、通常のウィンドウと同じように
//		取り扱う。
//		親ウィンドウをクローズすると、シノニムウィンドウもクローズされる。
//
MINT	MdwGetWindowList (	
						MINT		i_tpScm,	// 検索タイプ
												//　1:シノニムウィンドウを含む
												//　2:シノニムウィンドウを除く
						MINT		o_GidWin	// ウィンドウId | シノニムウィンドウIdセット
				)
{
	return 0;
}

//
//===========================================================================
//		指定ウィンドウを参照しているシノニムウィンドウを得る	
//
//		シノニムウィンドウとは、フレームを持たないウィンドウで、他のシノニム以外のウィンドウ上に
//		表示領域を持つウィンドウである。
//		親ウィンドウ（領域を貼り付けたウィンドウ）上に表示を行う以外は、通常のウィンドウと同じように
//		取り扱う。
//		親ウィンドウをクローズすると、シノニムウィンドウもクローズされる。
//
MINT	MdwGetSynonymWindowList (	
						MINT		i_idWin,	// ウィンドウId |
						MINT		o_GidSWin	// シノニムウィンドウIdセット
				)
{
	return 0;
}

//
//===========================================================================
//		カレントウィンドウの取得
//
//		カレントウィンドウを問い合わせる。
//		ウィンドウが１つも存在しない場合は、戻り値=0を返す。
//
//		ウィンドウが１つ以上オープンされている場合、何れか１つのウィンドウがカレントウィンドウに
//		設定される。
//		カレントウィンドウは、常に最前面に表示される。
//		GUIで「印刷」や「ＤＸＦ出力」、工程表による視点変更等、１つのウィンドウに限定されるコマンドは
//		カレントウィンドウを対象とする。
//
MDID	MdwGetCur ()							// ウィンドウId
{
	return 0;
}

//
//===========================================================================
//		カレントウィンドウの設定
//
//		渡されたウィンドウをカレントウィンドウに設定する。
//
MINT	MdwSetCur (
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//===========================================================================
//		遅延モードの問い合わせ
//
//		渡されたウィンドウの遅延モードを問い合わせる。
//		遅延モードとは、ウィンドウの表示（描画）を抑制するモードで、主に各ビュー情報の設定や複数の
//		図形を表示する際に画面のちらつきを押さえ描画速度を向上するために使用する。
//
//		・遅延モードがONに設定されている場合、
//		SetEyeCoord等でビュー情報を変更したり、MdeCmdAfterCreate等で図形の表示を行ってもこれらの
//		関数呼び出し時には描画されない。その後、遅延モードOFFで本関数を実行すると描画される。
//		（※Refresh、RefreshAllは呼び出し時に描画される。）
//		・遅延モードがOFFに設定されている場合、
//		　描画は随時行われる。
//		ex)
//		　MdwSetDelayMode ( wid , 1 );			// 遅延モード=ON
//		　 MdeCmdAfterCreate( mker, siz );		// 図形生成表示（描画は遅延される）
//		　 MdeEchoHighlighting( mker, siz );	// 図形強調表示（描画は遅延される）
//		　MdwSetDelayMode ( wid , 0 );			// 遅延モード=OFF（生成図形を強調表示で描画）
//
MINT	MdwGetDelayMode (
						MDID		i_idWin,	// ウィンドウId
						MDID*		o_pmdDly	// 遅延モード 1=on , 0=off
				)
{
	return 0;
}

//
//===========================================================================
//		遅延モードの設定
//
//		渡されたウィンドウの遅延モードを設定する。
//
MINT	MdwSetDelayMode (
						MDID		i_idWin,	// ウィンドウId
						MDID		i_mdDly		// 遅延モード 1=on , 0=off
				)
{
	return 0;
}

//===========================================================================
//		全ウィンドウに対する遅延モードの設定
//
//		オープンされている全ウィンドウに遅延モードを設定する。
//
MINT	MdwSetDelayModeAll (
						MDID		i_mdDly		// 遅延モード 1=on , 0=off
				)
{
	return 0;
}

//
//
//===========================================================================
//		ウィンドウの再表示
//
//		指定されたウィンドウの再表示を行う。
//		SetDelayModeでウィンドウに遅延モードが設定されている場合でも再表示を行う。

//
MINT	MdwRefresh (
						MDID		i_idWin		// ウィンドウId
				)
{
	return 0;
}

//
//
//===========================================================================
//		全ウィンドウの再表示
//
//		オープンされている全てのウィンドウの再表示を行う。
//		SetDelayModeで遅延モードが設定されているウィンドウも再表示を行う。
//
MINT	MdwRefreshAll ()
{
	return 0;
}

//
//
//===========================================================================
//		機能番号の問い合わせ
//
//		指定ウィンドウの機能番号を問い合わせる。
//
MINT	MdwGetType (
						MDID		i_idWin,	// ウィンドウId
						MDID*		o_pidWFn	// ウィンドウ機能番号
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号の設定
//
//		指定ウィンドウの機能番号を設定する。
//
MINT	MdwChangeType (
						MDID		i_idWin,	// ウィンドウId
						MDID		i_idWFn		// ウィンドウ機能番号
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する機能名の問い合わせ
//
//		機能名は最大１６文字（バイト）
//
MINT	MdwGetTypeName (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MCHAR		o_snmFn,	// 機能名
						MINT*		o_sznmFn	// 機能名サイズ
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する原点位置の問い合わせ
//
//		渡されたウィンドウの作業面図形のグリッドの間隔を問い合わせる。
//
MINT	MdwGetTypeOriginPosition (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgPoint2D*	o_pptOrg	// ウィンドウ領域内（(0,0)-(1,1)）の原点位置
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する原点位置の設定
//
//		渡されたウィンドウの作業面図形のグリッドの間隔を設定する。
//
MINT	MdwSetTypeOriginPosition (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgPoint2D	i_ptOrg		// ウィンドウ領域内（(0,0)-(1,1)）の原点位置
				)
{
	return 0;
}

//
//===========================================================================
//		グリッド点間隔の問い合わせ
//
//		渡されたウィンドウの作業面図形のグリッドの間隔を問い合わせる。
//
MINT	MdwGetGridSpan (
						MDID		i_idWin,	// ウィンドウId
						MREAL*		o_prSpn		// 作業面表示スパン
				)
{
	return 0;
}

//
//===========================================================================
//		グリッド点間隔の設定
//
//		渡されたウィンドウの作業面図形のグリッドの間隔を設定する。
//
MINT	MdwSetGridSpan (
						MDID		i_idWin,	// ウィンドウId
						MREAL		i_rSpn		// 作業面表示スパン
				)
{
	return 0;
}

//
//===========================================================================
//		作業面表示フラグの問い合わせ
//
//		作業面の図形を　表示する／表示しない　のフラグ値を問い合わせる。
//
MINT	MdwGetBasePlaneDispFlg (				// 表示フラグ
												//　0:表示しない
												//　1:表示する
				)
{
	return 0;
}


//
//===========================================================================
//		作業面ＦＬ連動フラグの設定
//
//		カレントグループ変更時に、平面およびアクソメウィンドウの作業面をグループ座標系の
//		フロアレベルに変更する／しない　のフラグ値を設定する。
//
MINT	MdwSetBasePlaneDispFlg (
						MINT		i_ifDspF	// 表示フラグ
												//　0:表示しない
												//　1:表示する
				)
{
	return 0;
}

//
//===========================================================================
//		作業面ＦＬ連動フラグの問い合わせ
//
//		カレントグループ変更時に、平面およびアクソメウィンドウの作業面をグループ座標系の
//		フロアレベルに変更する／しない　のフラグ値を問い合わせる。
//
MINT	MdwGetBasePlaneFLFlg (						// ＦＬ連動フラグ
												//　0:連動しない
												//　1:連動する
				)
{
	return 0;
}


//
//===========================================================================
//		作業面ＦＬ連動フラグの設定
//
//		カレントグループ変更時に、平面およびアクソメウィンドウの作業面をグループ座標系の
//		フロアレベルに変更する／しない　のフラグ値を設定する。
//
MINT	MdwSetBasePlaneFLFlg (
						MINT		i_ifMvm		// ＦＬ連動フラグ
												//　0:連動しない
												//　1:連動する
				)
{
	return 0;
}

//
//===========================================================================
//		基準線表示フラグの問い合わせ
//
//		基準線の図形を　表示する／表示しない　のフラグ値を問い合わせる。
//
MINT	MdwGetBaseAxisDispFlg (					// 表示フラグ
												//　0:表示しない
												//　1:表示する
				)
{
	return 0;
}

//
//===========================================================================
//		基準線表示フラグの設定
//
//		基準線の図形を　表示する／表示しない　のフラグ値を設定する。
//
MINT	MdwSetBaseAxisDispFlg (
						MINT		i_ifDspF	// 表示フラグ
												//　0:表示しない
												//　1:表示する
				)
{
	return 0;
}

//
//===========================================================================
//		作業面表示図形フラグの問い合わせ
//
//		作業面の表示図形を　線で表示する／点で表示する　のフラグ値を問い合わせる。
//
MINT	MdwGetBasePlaneShapeFlg (					// 表示図形フラグ
												//　1:線
												//　2:点
				)
{
	return 0;
}

//
//===========================================================================
//		作業面表示図形フラグの設定
//
//		作業面の表示図形を　線で表示する／点で表示する　のフラグ値を設定する。
//
MINT	MdwSetBasePlaneShapeFlg (
						MINT	i_ifWkSDsp		// 表示図形フラグ
												//　1:線
												//　2:点
				)
{
	return 0;
}


//
//===========================================================================
//		作業面表示範囲の問い合わせ
//
//		渡されたウィンドウの作業面の表示範囲を問い合わせる。
//
//		表示範囲は、作業面座標系上での最小値（X、Y）と最大値（X、Y）。
//
MINT	MdwGetBasePlaneRange (
						MDID		i_idWin,	// ウィンドウId
						MgRect2D*	o_prcDsp	//	作業面表示範囲（最小XY、最大XY）
				)
{
	return 0;
}

//
//===========================================================================
//		作業面表示範囲の問い合わせ
//
//		渡されたウィンドウの作業面の表示範囲を問い合わせる。
//
//		表示範囲は、作業面座標系上での最小値（X、Y）と最大値（X、Y）。
//
MINT	MdwSetBasePlaneRange (
						MDID		i_idWin,	// ウィンドウId
						MgRect2D*	o_prcDsp	//	作業面表示範囲（最小XY、最大XY）
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する作業面表示範囲の問い合わせ
//
//		渡された機能番号に対する作業面の表示範囲を問い合わせる。
//		渡された機能番号でオープンするウィンドウの初期値を反す。
//
//		表示範囲は、作業面座標系上での最小値（X、Y）と最大値（X、Y）。
//
MINT	MdwGetDefaultBasePlaneRange (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgRect2D*	o_prcDsp	//	作業面表示範囲（最小XY、最大XY）
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する作業面表示範囲の設定
//
//		渡された機能番号に対する作業面の表示範囲を設定する。
//		以後、渡された機能番号でオープンするウィンドウの初期値はこの値になる。
//		既にオープンされているウィンドウには影響しない。
//
//		表示範囲は、作業面座標系上での最小値（X、Y）と最大値（X、Y）。
//
MINT	MdwSetDefaultBasePlaneRange (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgRect2D*	i_prcDsp	//	作業面表示範囲（最小XY、最大XY）
				)
{
	return 0;
}

//
//===========================================================================
//		作業面の状態問い合わせ
//
//		渡されたウィンドウの作業面の状態を問い合わせる。
//		o_piWkSはウィンドウの作業面を基準／任意のどちらで表示するかの値。
//		o_piCodは作業面座標系のXY／YZ／ZXのどの平面を使用するかの値。
//
MINT	MdwGetBasePlaneXYZ (
						MDID		i_idWin,	// ウィンドウId
						MINT		o_piWkS,	//	0:基準    1:任意
						MINT		o_piCod		//	1:xy   2:yz   3:zx
				)
{
	return 0;
}

//
//===========================================================================
//		作業面の状態設定（切り替え）
//
//		渡されたウィンドウの作業面の状態を設定する。
//		flg1はウィンドウの作業面を基準／任意のどちらで表示するかの値。
//		flg2は作業面座標系のXY／YZ／ZXのどの平面を使用するかの値。
//
MINT	MdwSetBasePlaneXYZ (
						MDID		i_idWin,	// ウィンドウId
						MINT		i_iWkS,		//	0:基準    1:任意
						MINT		i_iCod		//	1:xy   2:yz   3:zx
				)
{
	return 0;
}

//
//===========================================================================
//		任意作業面の座標系への座標変換マトリックスを取得する
//
MINT	MdwGetTempPlaneCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		o_pmatV		// 作業面の座標系の座標変換マトリックス
												// （基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		任意作業面の座標系への座標変換マトリックスを設定する
//
MINT	MdwSetTempPlaneCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		i_pmatV		// 作業面の座標系の座標変換マトリックス
												// （基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		ウィンドウの作業面の座標系への座標変換マトリックスを取得する
//
//		渡されたウィンドウIDの作業面の座標系を得る。
//		渡されたウィンドウの状態（表示）が任意作業面に設定されている場合でも基準作業面の座標系を返す。
//
MINT	MdwGetBasePlaneCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		o_pmatV		// 作業面の座標系の座標変換マトリックス
												// （基準座標系での値）
				)
{
	return 0;
}

//
//===========================================================================
//		機能番号に対する作業面の座標系への座標変換マトリックスを取得
//
//		渡された機能番号に対する作業面の座標系を得る。
//		渡された機能番号でオープンするウィンドウの初期値を返す。
//
MINT	MdwGetDefaultBasePlaneCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		o_pmatV		// 作業面の座標系の座標変換マトリックス
												// （基準座標系での値）
				)
{
	return 0;
}


//
//===========================================================================
//		機能番号に対する作業面の座標系への座標変換マトリックスを設定
//
//		渡された機能番号に対する作業面の座標系を設定する。
//		以後、渡された機能番号でオープンするウィンドウの初期値はこの値になる。
//		既にオープンされているウィンドウには影響しない。
//
MINT	MdwSetDefaultBasePlaneCoord (
						MDID		i_idWFn,	// ウィンドウ機能番号
						MgMat3E*		i_pmatV		// 作業面の座標系の座標変換マトリックス
												// （基準座標系での値）
				)
{
	return 0;
}

} // namespace MC
