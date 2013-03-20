//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdAtr.cpp
//
//		ウィンドウ
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#include "MdModel.h"

namespace MC
{

//===========================================================================
//		初期設定
//
//		属性の初期設定を行う。
//		データベースをオープン後、属性の処理を行う場合は必ず最初にこの関数を呼ぶ。
//
MINT	MdaInit (
				)
{
	return 0;
}

//
//===========================================================================
//		項目の生成
//
//		項目名とデータ種別を指定して、属性項目を生成する。
//		渡された項目名が既に使用されている場合（戻り値=10）は、生成済みの項目IDが返る。
//
//		PutData関数で属性データ（値）を記録するには、予め本関数で項目を生成しておく必要が有る。
//
//		「データ種別一覧」
//			 1	整数（long）
//			 2	実数（float）
//			 3	倍制度（double）
//			 4	テキスト（char）
//			 5	テキストファイル（パス文字列）
//			 6	イメージ
//			 7	イメージファイル（パス文字列）
//			 8	音声
//			 9	音声ファイル（パス文字列）
//			10	APP
//			11	WWW
//
MINT	MdaCreateItem (
						MCHAR		i_snmAtr[],	// 項目名
						MINT		i_itpAtr,	// データ種別
						MDID*		o_pidAtr	// 項目ID
				)
{
	return 0;
}

//
//===========================================================================
//		項目の削除
//
//		属性項目を削除する。
//		渡された項目IDが何れかの属性Dprで使用されている場合は削除できない。
//
MINT	MdaDeleteItem (
						MDID		i_idAtr		// 項目ID
				)
{
	return 0;
}

//
//===========================================================================
//		項目名の変更
//
//		項目名を変更する。
//		渡された項目名が既に使用されている場合はエラーとなる。
//
MINT	MdaChangeItemName (
						MDID		i_idAtr,	// 項目ID
						MCHAR		i_snmAtr	// 項目名
				)
{
	return 0;
}


//
//===========================================================================
//		項目ＩＤよりデータ種別を得る
//
//		項目のデータ種別を問い合わせる。
//
//		データ種別については、別紙「データ種別一覧」を参照。
//
MINT	MdaGetItemType (
						MDID		i_idAtr,	// 項目ID
						MINT*		o_pitpAtr	// データ種別
				)
{
	return 0;
}

//
//===========================================================================
//		項目ＩＤより項目名を得る
//
MINT	MdaGetItemName (
						MINT		i_itpAtr,	// データ種別
						MCHAR		o_snmAtr[],	// 項目名
						MINT		i_sznmAtr	// 項目名サイズ
				)
{
	return 0;
}

//
//===========================================================================
//		項目名より項目ＩＤを得る
//
MINT	MdaGetItem (
						MCHAR		i_snmAtr,	// 項目名
						MDID*		o_pidAtr	// 項目ID
				)
{
	return 0;
}

//
//===========================================================================
//		項目IDの一覧を得る
//
//		生成済み項目IDの一覧を得る。
//
MINT	MdaGetItemList (
						MDIDSET*	o_pGidAtr	// 項目IDセット
				)
{
	return 0;
}

////
////===========================================================================
////		エンティティに属性Dprを生成する
////
////		エンティティを渡して属性Dprを生成する。
////		エンティティに既に属性Dprが存在していた場合は、既存の属性DprのIDが返る。
////		（ステータス=3が返る。）
////
////		MdaPutData関数で属性データ（値）を記録するには、予め本関数で属性Dprを生成しておく必要が有る。
////
//MINT	MdaCreateDpr (
//						MDID		i_idEnt,	// エンティティ
//						MDID*		o_pidAtr	// 属性Dpr
//				)
//{
//	return 0;
//}

//
//===========================================================================
//		属性データの記録（上書き／追加）
//
//		指定項目の値（属性データ）を記録する。
//		本関数の実行前に、CreateItem関数で予め項目を生成しておく必要が有る。
//
//		１つの属性Dprに対し、同じ項目IDで異なる値を複数個記録する事が出来る。
//		項目ID内の追番（no）はこの順番を示し、=0の場合は追加となる。
//		no≠0の場合は、その位置の値を指定属性データ（dat）で上書きする。
//
//		属性データ（dat）のデータ型は、項目IDのデータ種別で特定されるが、
//		本関数へはCharポインタ型にキャストして呼び出す。
//		データサイズはバイト長を渡す。
//
MINT	MdaPutData (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDID		i_idAtr,	// 項目ID
						MDID		i_idnAtr,	// 項目ID内の追番 ( =0：追加 )
						CHAR		i_sAtr[]	// 属性データ
				)
{
	return 0;
}

//
//===========================================================================
//		属性データの削除
//
//		属性Dprに記録されている指定項目の属性データを削除する。
//		指定された項目の属性データが存在しない場合は、エラーにはならずステータス＝０で返る。
//
//		１つの属性Dprに対し、同じ項目IDで異なる値を複数個記録する事が出来る。
//		項目ID内の追番（no）はこの順番を示し、
//		=0の場合は最初に記録された属性データを示すものとして、=1が渡された時と同じ処理を行う。
//
MINT	MdaRemoveData (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDID		i_idAtr,	// 項目ID
						MDID		i_idnAtr = 1	// 項目ID内の追番
				)
{
	return 0;
}

//
//===========================================================================
//		属性データの取得
//
//		属性Dprに記録されている指定項目の値（属性データ）を参照する。
//
//		１つの属性Dprに対し、同じ項目IDで異なる値を複数個記録する事が出来る。
//		項目ID内の追番（no）はこの順番を示し、=0の場合は最後のデータを参照する。
//		no≠0の場合は、その位置の値を参照する。
//
//		属性データ（dat）のデータ型は、項目IDのデータ種別で特定されるが、
//		本関数へはCharポインタ型にキャストして呼び出す。
//		データサイズはバイト長を渡す。
//
MINT	MdaGetData (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDID		i_idAtr,	// 項目ID
						MDID		i_idnAtr,	// 項目ID内の追番
						MCHAR		o_sAtr[],	// 属性データ
						MINT		i_szAtr		// 属性データサイズ
				)
{
	return 0;
}

//
//===========================================================================
//		属性データサイズの問い合わせ
//
//		属性Dprに記録されている属性データのデータサイズを得る。
//
//		１つの属性Dprに対し、同じ項目IDで異なる値を複数個記録する事が出来る。
//		項目ID内の追番（no）はこの順番を示し、=0の場合は最後のデータのサイズを得る。
//		no>0の場合は、その位置のデータサイズを得る。
//		no=-1の場合は、指定項目ID全てのトータルデータサイズを得る。
//
//		項目ID=-1の場合は、属性Dprに記録されている全項目が対象となり、
//		項目個数およびデータサイズは得られるトータル数となる。
//
MINT	MdaGetDataSize (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDID		i_idAtr,	// 項目ID
						MDID		i_idnAtr,	// 項目ID内の追番
						MINT*		o_pnAtr,	// 項目個数
						MINT*		o_piszAtr	// 属性データサイズ（バイト長）
				)
{
	return 0;
}

//
//===========================================================================
//		属性データを記録順に参照する
//
//		属性Dprに記録されている属性データを記録順に1つずつ得る。
//
//		属性データ（dat）のデータ型は、項目IDのデータ種別で特定されるが、
//		本関数へはCharポインタ型にキャストして呼び出す。
//		データサイズはバイト長を返す。
//
MINT	MdaGetDataSeq (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDID*		i_pidAtr,	// 項目ID
						MCHAR		o_sAtr[],	// 属性データ
						MINT		i_szAtr		// 属性データサイズ
				)
{
	return 0;
}

//
//===========================================================================
//		属性Dprに記録されている項目ＩＤの一覧を得る
//
//		属性Dprに記録されている項目IDのリストを得る。
//
MINT	MdaGetItemListInDpr (
						MDID		i_idAtrDpr,	// 属性Dpr
						MDIDSET*	o_pGidAtr	// 項目IDセット
				)
{
	return 0;
}

//
//===========================================================================
//		項目ＩＤを使用している属性Dprの一覧を得る
//
//		渡された項目IDが記録されている属性Dprの一覧を得る。
//
MINT	MdaGetDprHasItem (
						MDID		i_idAtrDpr,		// 属性Dpr
						MDIDSET*	o_pGidAtrDpr	// 項目DprIDセット
				)
{
	return 0;
}

} // namespace MC