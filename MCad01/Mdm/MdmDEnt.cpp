//==========================================================================================
//  Copyright(C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdEnt.cpp
//
//		物
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgDefine.h"

#include "MdmFig.h"
#include "MdZukei.h"
#include "MgLib.h"

#include "MdModel.h"
#define DLL_EXPORT_DENT_DO
#include "MdmDB.h"
#include "Mdm.h"

namespace MC
{

//===========================================================================
//		物の生成後の標準処理
//
//		与えられたエンティティのレイヤーの意味に従い、生成時の必要処理を行う。
//		処理内容
//		・与えられたエンティティをグラフィックウィンドウに生成表示する。
//		・“壁”の場合は、既存の“窓”、“扉”、“開口”との図形干渉チェックを行い、干渉する
//			場合は付属関係を付ける。
//		・“窓”、“扉”、“開口”の場合は、既存の“壁”との図形干渉チェックを行い、干渉する
//			場合は付属関係を付け、その“壁”の再表示を行う。
//
MINT mdmDEnt::CmdAfterCreate(
						MDIDSET&		i_GidEnt	// エンティティ−ＩＤセット
				)
{
	return 0;
}

//===========================================================================
//		物の削除の標準処理
//
//		与えられたエンティティのレイヤーの意味に従い、削除時の必要処理を行う。
//		処理内容
//		・与えられたエンティティを削除し、グラフィックウィンドウの表示を消去する。
//		・“壁”の場合は、付属関係にある“窓”、“扉”、“開口”の再表示を行う。
//		・“窓”、“扉”、“開口”の場合は、付属関係にある“壁”の再表示を行う。
//
MINT mdmDEnt::CmdDelete(
						MDIDSET&	i_GidEnt	// エンティティ−ＩＤセット
				)
{
	return 0;
}

//===========================================================================
//		物の複写の標準処理
//
//		与えられたエンティティのレイヤーの意味に従い、複写時の必要処理を行う。
//		処理内容
//		・与えられたエンティティを複写後、複写先の図形を移動し、グラフィックウィンドウに生成表示する。
//		・“壁”の場合は、複写先のエンティティと既存の“窓”、“扉”、“開口”との図形干渉チェックを行い、
//			干渉する場合は付属関係を付ける。
//		・“窓”、“扉”、“開口”の場合は、複写先のエンティティと既存の“壁”との図形干渉チェックを行い、
//			干渉する場合は付属関係を付け、その“壁”の再表示を行う。
//
//			mode=1　の時　datは移動ベクトル[3]
//			mode=2　の時　datは回転マトリックス[12]
//			mode=3　の時　datは面情報（点＋法線ベクトル）[6]
//			mode=4　の時　datは原点＋倍率[4]　※倍率は1.0が原寸
//
MINT mdmDEnt::CmdCopy(
						MDIDSET&	i_pGidEnt,	// エンティティ−ＩＤセット
						MINT		i_imdMv,	// 移動モード( 1:平行 2:回転 3:鏡面 4:拡大 )
						void*		i_pv,		// 移動データ
						MDIDSET*	o_pGidEnt	// 複写先　エンティティ-IDリスト
				)
{
	return 0;
}

//===========================================================================
//		物の移動の標準処理
//
//		与えられたエンティティのレイヤーの意味に従い、移動時の必要処理を行う。
//		処理内容
//		・与えられたエンティティの図形を移動し、グラフィックウィンドウに再表示する。
//		・“壁”の場合は、付属関係にある“窓”、“扉”、“開口”との図形干渉チェックを行い、
//			干渉しない場合は付属関係を切り、その“窓”、“扉”、“開口”の再表示を行う。
//			既存の“窓”、“扉”、“開口”との図形干渉チェックを行い、干渉する場合は付属関係を
//			付ける。
//		・“窓”、“扉”、“開口”の場合は、付属関係にある“壁”との図形干渉チェックを行い、
//			干渉しない場合は付属関係を切り、その“壁”の再表示を行う。
//			既存の“壁”との図形干渉チェックを行い、干渉する場合は付属関係を付け、その“壁”の
//			再表示を行う。
//			mode=1　の時　datは移動ベクトル[3]
//			mode=2　の時　datは回転マトリックス[12]
//			mode=3　の時　datは面情報（点＋法線ベクトル）[6]
//			mode=4　の時　datは原点＋倍率[4]　※倍率は1.0が原寸
//
MINT mdmDEnt::CmdMove(
						MDIDSET&	i_pGidEnt,	// エンティティ−ＩＤセット
						MINT		i_imdMv,	// 移動モード( 1:平行 2:回転 3:鏡面 4:拡大 )
						void*		i_pv		// 移動データ
				)
{
	return 0;
}

//===========================================================================
//		物の変形後の標準処理
//
//		与えられたエンティティのレイヤーの意味に従い、図形変形時の必要処理を行う。
//		処理内容
//		・与えられたエンティティをグラフィックウィンドウに再表示する。
//		・“壁”の場合は、付属関係にある“窓”、“扉”、“開口”との図形干渉チェックを行い、
//			干渉しない場合は付属関係を切り、その“窓”、“扉”、“開口”の再表示を行う。
//			既存の“窓”、“扉”、“開口”との図形干渉チェックを行い、干渉する場合は付属関係を
//			付ける。
//		・“窓”、“扉”、“開口”の場合は、付属関係にある“壁”との図形干渉チェックを行い、
//			干渉しない場合は付属関係を切り、その“壁”の再表示を行う。
//			既存の“壁”との図形干渉チェックを行い、干渉する場合は付属関係を付け、その“壁”の
//			再表示を行う。
//
MINT mdmDEnt::CmdAfterModify(
						MDIDSET&	i_GidEnt	// エンティティ−ＩＤセット
				)
{
	return 0;
}

//===========================================================================
//		物図形の強調表示（エコーバック）
//
//		指定物の強調表示（エコーバック）を行う。
//		強調表示は、NonHighlighting、NonHighlightingAllで解除されるか、CmdMove等で再表示されるまで
//		継続する。
//		強調表示中にCmdMove等で再表示する場合は、ClearHighlightingListで強調表示を行ったエンティティの
//		リストを開放する必要がある。
//
MINT mdmDEnt::EchoHighlighting(
						MDIDSET&	i_GidEnt	// エンティティ−ＩＤセット
				)
{
	return 0;
}

//===========================================================================
//		強調表示（エコーバック）を元に戻す（１つ）
//
//		指定エンティティがEchoHighlightingで強調表示されている場合に表示を戻す。
//		指定エンティティが強調表示されていない場合には何も行わない。（戻り値＝０）
//
MINT mdmDEnt::NonHighlighting(
						MDID		i_idEnt		// エンティティ−ＩＤ
				)
{
	return 0;
}

//===========================================================================
//		強調表示（エコーバック）を元に戻す
//
//		EchoHighlightingで強調表示されている物の表示を全て戻す。
//
MINT mdmDEnt::NonHighlightingAll()
{
	return 0;
}

//===========================================================================
//		強調表示（エコーバック）セットの強制クリア（再表示なし）
//
//		EchoHighlightingで強調表示したエンティティのリストを開放する。
//		表示は行わない。
//
//		強調表示中にCmdMove等で再表示した場合は、本関数で強調表示を行ったエンティティのリストを
//		開放する必要がある。
//
MINT mdmDEnt::ClearHighlightingSet()
{
	return 0;
}

//===========================================================================
//		エンティティの生成
//
//		レイヤーIdを指定して、そのレイヤーIdに付随するエンティティを生成する。
//		指定レイヤーIdが存在しない場合や、エンティティの生成に失敗した場合はo_pidEnt=0で返す。
//
MINT mdmDEnt::CreateEnt(
						MDID		i_idLyr,	// レイヤーID
						MDID*		o_pidEnt,	// エンティティID
						MINT		i_sz		// 初期グループIdバッファサイズ /*=10*/
				)
{
	mdmEnt*	pEnt;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	// EntBfより空きのIDを取得し、エンティティの領域を設ける
	//
	if ( pCurMdl->m_EntBf.m_idSpaceLast == 0) {
		// 削除して空きになっているIDがない場合は最終ID+1を使用する
		pCurMdl->m_EntBf ++;
		*o_pidEnt = pCurMdl->m_EntBf.m_n;
		pEnt = &pCurMdl->m_EntBf.m_pst[MIDtoHN( *o_pidEnt)];

	} else {
		// 削除して空きになっているIDがある場合はそのIDを使用する
		ASSERT( pCurMdl->m_EntBf.m_nidSpace >= 1);

		*o_pidEnt = pCurMdl->m_EntBf.m_idSpaceLast;
		pEnt = &pCurMdl->m_EntBf.m_pst[MIDtoHN( *o_pidEnt)];

		// 空きエリアへのIDを一つ戻す
		pCurMdl->m_EntBf.m_idSpaceLast = MDSPACEBEFORE( pEnt);
		if ( pCurMdl->m_EntBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_EntBf.m_pst[MIDtoHN( pCurMdl->m_EntBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_EntBf.m_nidSpace--;
	}

	// エンティティIDに子IDの設定用領域を確保する
	pEnt->Alloc( i_sz);

	// レイヤーとのリンクを付ける
//	pEnt->m_SC.m_idP = i_idLyr;
	pEnt->m_idP = i_idLyr;
	pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GidC += (*o_pidEnt);

	return 0;
}

//===========================================================================
//		エンティティの削除
//
MINT mdmDEnt::DeleteEnt(						//
						MDID		i_idEnt		// エンティティId
				)
{
	mdmEnt*	pEntB;								// 直前に削除したエンティティ
	mdmEnt*	pEntC;								// 削除エンティティ
	MDID	idLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( i_idEnt >= 1 && i_idEnt <= pCurMdl->m_EntBf.m_n);

	// レイヤーからのリンクを削除する
	pEntC = &pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)];
//	idLyr = pEntC->m_SC.m_idP;
	idLyr = pEntC->m_idP;
	pCurMdl->m_LyrBf.m_pst[MIDtoHN( idLyr)] -= i_idEnt;
	// その他のリンクを削除する

	// 削除し割り当て待ちの空きエンティティ数に追加
	pCurMdl->m_EntBf.m_nidSpace++;
	// エンティティ削除フラグ設定と使用エリア開放
	MDSPACEID( pEntC) = MDID_DELETE;
	pEntC->Free();

	// 空きエリアリンクに追加
	// 直前に削除したエンティティの次のエンティティとする
	if ( pCurMdl->m_EntBf.m_idSpaceLast) {
		pEntB = &pCurMdl->m_EntBf.m_pst[MIDtoHN( pCurMdl->m_EntBf.m_idSpaceLast)];
		MDSPACENEXT( pEntB) = i_idEnt;
	}
	// 空きエリアリンクの先頭にリンク付ける
	MDSPACEBEFORE( pEntC) = pCurMdl->m_EntBf.m_idSpaceLast;
	MDSPACENEXT( pEntC) = 0;
	pCurMdl->m_EntBf.m_idSpaceLast = i_idEnt;
	return 0;
}

//===========================================================================
//		エンティティに図形情報を設定する
//
//		図形情報が部品配置の場合は、エンティティに部品を関係付ける。
//
MINT mdmDEnt::SetFigPmt(
						MDID		i_idEnt,	// エンティティ-ID
						MDPMT&		i_Pmt		// 図形情報
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 図形情報をエンティティにコピーする
	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_Fig = i_Pmt;
	return 0;
}

//===========================================================================
//		エンティティに図形情報を設定する
//
//		図形情報が部品配置の場合は、エンティティに部品を関係付ける。
//
MINT mdmDEnt::SetFig(
						MDID		i_idEnt,	// エンティティ-ID
						MDFIG&		i_Fig		// 図形情報
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 図形情報をエンティティにコピーする
	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_Fig = i_Fig;
	return 0;
}

//===========================================================================
//		エンティテイに部材配置の設定
//
//		エンティテイに指定部品を配置する部材配置プリミティブを設定する。
//		配置壱と方向、大きさは配置座標系マトリックスで指定する。
//
MINT mdmDEnt::SetPartPlc (
						MDID		i_idEnt,	// エンティテイID
						MgMat3E*		i_pmat,		// 配置座標系マトリックス
						MDID		i_idB		// 部品ID
				)
{
	return 0;
}

//===========================================================================
//		エンティティの図形情報を得る
//
//		図形情報が無設定の場合は、o_pFig＝０を返す。
//
MINT mdmDEnt::GetFig(
						MDID		i_idEnt,	// エンティティ-ID
						MDFIG*		o_pFig		// 図形情報
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 図形情報をエンティティからコピーする
	*o_pFig = pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_Fig;
	return 0;
}

//===========================================================================
//		エンティテイの図形情報を変更
//
MINT mdmDEnt::CngZukei(
						MDID		i_idEnt,	// エンティテイID
						MDFIG&		i_Fig		// 図形情報
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 図形情報をエンティティにコピーする
	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_Fig = i_Fig;
	return 0;
}

//===========================================================================
//		属性（ポインタ）をエンティティに設定する
//
MINT mdmDEnt::SetAttr(
						MDID		i_idEnt,	// エンティティ-ID
						MSHORT		i_iTpAtr,	// 属性タイプ
						void*		i_pAtr		// 属性
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 属性をエンティティにコピーする
	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_iTpAtr = i_iTpAtr;
	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_pAtr = i_pAtr;
	return 0;
}

//===========================================================================
//		エンティティの属性（ポインタ）を得る
//
void* mdmDEnt::GetAttr(
						MDID		i_idEnt	// エンティティ-ID
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISENT( i_idEnt));

	// 属性をエンティティから得る
	return pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_pAtr;
}

//===========================================================================
//		エンティティからレイヤーIdを得る
//
//		エンティティを指定してそのものエンティティが付随するレイヤーIdを得る。
//		レイヤーIdが見つからない場合は、o_pidLyr＝０を返す。
//
MINT mdmDEnt::GetLyrId(
						MDID		i_idEnt,	// エンティティID
						MDID*		o_pidLyr	// レイヤーID
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	*o_pidLyr = pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt)].m_idP;
	return 0;
}

//===========================================================================
//		カレントのレイヤーに図形を持つエンティティを作る（作成のみ、表示等はしない）
//
//		カレントレイヤーに指定された図形を持つエンティティを生成する。
//		カレントレイヤーが未生成の場合は、レイヤーの生成も行う。
//		グラフィックウィンドウへの表示は行わない。
//
//
MINT mdmDEnt::CreateFigEnt(
						MDFIG&		i_stFig,	// 図形情報
						MDID*		o_pidEnt	// エンティティ-ID
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	// カレントレイヤーが未生成の場合はレイヤーを生成
	if ( pCurMdl->m_idCurLyr == 0) {
		DLyr::CreateLyr( pCurMdl->m_idCurScm, pCurMdl->m_idCurGrp, &pCurMdl->m_idCurLyr, 10);
	}
	// カレントレイヤーにリンクしたエンティティを生成
	mdmDEnt::CreateEnt( pCurMdl->m_idCurLyr, o_pidEnt, 0);
	// 図形をコピー
	mdmDEnt::SetFig( *o_pidEnt, i_stFig);
	return 0;
}

//===========================================================================
//		エンティティのレイヤー変更（レイヤー間移動）
//
//		指定のエンティティを指定されたレイヤーに移動する。
//		元のレイヤーと移動先のレイヤーでグループが異なっていた場合は、
//		移動するエンティティの図形の親座標系を付け替え、図形データの座標変換を行う。
//		（結果、基準座標系から見た図形の位置は変わらない。）
//
MINT mdmDEnt::CngLyr(
						MDIDSET&	i_GidEntF,	// エンティティIDセット
						MDID		i_idLyrT	// レイヤーID
				)
{
	MINT	iC;
	MDID	idEntF;								// 変更元
	MDID	idLyrF;
	MDID	idGrpF;
	MDID	idGrpFB;
	MDID	idGrpT;								// 変更先
	MgMat3E* pMTransT;							// 変更先グループの座標変換マトリックス
	MgMat3E	MTransTR;							// 変更先グループの座標逆変換マトリックス
	MgMat3E	MTrans;								// 変更先グループから変更先グループへの座標変換マトリックス
	MdModel* pCurMdl = Mdm::GetCurModel();

	// 変更先のレイヤーが属するグループの座標逆変換マトリックスを求める
	idGrpT = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyrT)].m_idP1;
	pMTransT = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( idGrpT)].m_MTrans;
	MTransTR = MGeo::Mat3EInv( *pMTransT);

	// 指定全エンティティのレイヤーを変更する
	idGrpFB = MDC_ID_NULL;
	for ( iC=0; iC<i_GidEntF.m_n; iC++) {
		// 変更元のレイヤーとグループを求める
		idEntF = i_GidEntF.m_pst[iC];
		idLyrF = pCurMdl->m_EntBf.m_pst[MIDtoHN( idEntF)].m_idP;
		idGrpF = pCurMdl->m_LyrBf.m_pst[MIDtoHN( idLyrF)].m_idP1;
		// レイヤーに変化があるもののみ変更する
		if ( idLyrF != i_idLyrT) {
			// グループに変化があるもののみ座標変換する
			if ( idGrpT != idGrpF) {
				// 変換元グループが直前の変換元グループと異なる場合には座標変換マトリックスを求める
				if ( idGrpF != idGrpFB) {
					idGrpFB = idGrpF;
					MTrans = pCurMdl->m_GrpBf.m_pst[MIDtoHN( idGrpF)].m_MTrans;
					MTrans *= MTransTR;
				}
				// エンティティの座標を変換する
				DZukei::MdzTrans( MTrans, pCurMdl->m_EntBf.m_pst[MIDtoHN( idEntF)].m_Fig, 
								  &pCurMdl->m_EntBf.m_pst[MIDtoHN( idEntF)].m_Fig);
			}
			// レイヤーを変換する
			pCurMdl->m_EntBf.m_pst[MIDtoHN( idEntF)].m_idP = i_idLyrT;
		}
	}
	return 0;
}

//===========================================================================
//		エンティティのレイヤー間コピー
//
//		指定のエンティティを指定されたレイヤーに複写する。
//		lker=0の場合は、元のレイヤーに複写する。
//		元のレイヤーと複写先のレイヤーでグループが異なっていた場合は、
//		複写後のエンティティの図形の親座標系は複写先のグループの座標系となる。
//		図形データの座標変換も行う。（結果、基準座標系から見た図形の位置は変わらない。）
//
MINT mdmDEnt::CpyEnt(
						MDIDSET&	i_GidEnt,	// エンティティ-IDセット
						MDID		i_idLyr,	// レイヤーID
						MDIDSET*	o_pGidEnt	// コピーエンティティ-IDセット
				)
{
	MINT	iC;
	MDID	idEnt;
	mdmEnt	entW;
	MdModel* pCurMdl = Mdm::GetCurModel();

	// 指定全エンティティをコピーする
	o_pGidEnt->m_n = 0;
	for ( iC=0; iC<i_GidEnt.m_n; iC++) {
		// コピー元のエンティティを得る
		entW = pCurMdl->m_EntBf.m_pst[MIDtoHN( i_GidEnt[iC])];
		// 同エンティティを生成する
		mdmDEnt::CreateEnt( 0, &idEnt, 0);
		pCurMdl->m_EntBf.m_pst[MIDtoHN( idEnt)] = entW;
	}

	// コピーエンティティのレイヤーを変更する
	mdmDEnt::CngLyr(	*o_pGidEnt,	i_idLyr);
	return 0;
}

//===========================================================================
//		ＢＯＸ内の図形Dprを得る
//
//		ウィンドウに表示されている図形の内、box範囲内に完全包含される図形を持つエンティティを得る。
//		boxの最小点・最大点はカレント座標系の座標値で返す。
//
MINT mdmDEnt::GetEntInBox(
						MDID		i_idWin,	// ウィンドウID
						MgMinMaxR3D&	i_rMnmx,	// box座標値（最小・最大点）
						MDIDSET*	o_pGidEnt	// エンティティ-IDセット
				)
{
	MDIDSET	GidLyr;
	MDIDSET	GidEnt;

	MINT	iCl;
	MINT	iCe;
	MDID	idEnt;

	MgMinMaxR3D	rMnMxEnt;

	o_pGidEnt->m_n = 0;
	DLyr::GetLyrIdAll( &GidLyr);
	for ( iCl=0; iCl<GidLyr.m_n; iCl++) {
		DLyr::GetEnt( GidLyr.m_pst[iCl], &GidEnt);
		for ( iCe=0; iCe<GidEnt.m_n; iCe++) {
			idEnt = GidEnt.m_pst[iCe];
//			rMnMxEnt = pCurMdl->m_EntBf.m_pst[MIDtoHN( idEnt)].m_Fig.m_pPmts->m_Mmx;
			if ( MGeo::CheckPt3InMinmaxR3D( rMnMxEnt.min, i_rMnmx) &&
				 MGeo::CheckPt3InMinmaxR3D( rMnMxEnt.max, i_rMnmx) ) {
				(*o_pGidEnt) += idEnt;
			}
		}
	}
	return 0;
}

//===========================================================================
//		関係付け
//
//		ker1とker2を指定の関係で関係付ける。
//		この関係はSearch関数で検索できる。
//
//		関係IDについては、別紙関係一覧を参照。
//
MINT mdmDEnt::Link(
						MDID		i_idEnt1,	// エンティティID1
						MINT		i_icdRef1,	// エンティティID1からエンティティID2への関係コード
						MDID		i_idEnt2,	// エンティティID2
						MINT		i_icdRef2	// エンティティID2からエンティティID1への関係コード
				)
{
//	pCurMdl->m_EntBf.m_pst[MIDtoHN( i_idEnt1)]
	return 0;
}

//===========================================================================
//		関係切り
//
//		ker1とker2の間に付けられている指定の関係を切る。
//
//		関係IDについては、別紙関係一覧を参照。
//
MINT mdmDEnt::DeLink(
						MDID		i_idEnt1,	// エンティティID1
						MINT		i_icdRef1,	// エンティティID1からエンティティID2への関係コード
						MDID		i_idEnt2,	// エンティティID2
						MINT		i_icdRef2	// エンティティID2からエンティティID1への関係コード
				)
{
	return 0;
}

//===========================================================================
//		関係検索
//
//		ker1に指定の関係で関係付いているのリストを得る。
//
//		関係IDについては、別紙関係一覧を参照。
//
MINT mdmDEnt::Srch(
						MDID		i_idEnt,	// エンティティID
						MINT		i_icdRef,	// エンティティIDからの関係コード
						MDIDSET*	o_pGidEnt	// エンティティIDセット
				)
{
	return 0;
}

//===========================================================================
//		KCBの生成
//
//		キー検索のためのKCBを生成する。
//
MINT mdmDEnt::KeyInit(
						MDID*		o_pidKCB	// KCB-ID
				)
{
	return 0;
}

//===========================================================================
//		KCBの生成
//
//		指定されたキーで関係付ける。
//		この関係はKeySearch関数で検索できる。
//
MINT mdmDEnt::KeyLink(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// キー
						MDID		i_idInf		// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		キーでの関係切り
//
//		指定されたキーでの関係を切る。
//
MINT mdmDEnt::KeyDeLink(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// キー
						MDID		i_idInf		// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		キーでの検索
//
//		指定されたキーで関係付いているエンティテイを得る。
//
MINT mdmDEnt::KeySearch(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// キー
						MDID*		o_pidInf	// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		KCBの削除
//
//		キー検索のためのKCBを削除する。
//
MINT mdmDEnt::KeyDelete(
						MDID		i_idKCB		// KCB-ID
				)
{
	return 0;
}

//===========================================================================
//		アクセスルートの問い合わせ	
//
//		キーワードを指定してアクセスルートに登録されているInformationを得る。
//
MINT mdmDEnt::GetAccessRoot(
						MCHAR		i_sKey[],	// キー
						MDID*		o_pidInf	// Information-ID
												//	（キーワードが存在しない場合は０）
				)
{
	return 0;
}

//===========================================================================
//		アクセスルートの登録	
//
//		キーワードを指定してアクセスルートにInformation-IDを登録する。
//		指定されたキーワードが存在した場合は、上書きする。
//
MINT mdmDEnt::PutAccessRoot(
						MCHAR		i_sKey[],	// キー
						MDID*		i_idInf		// Information-ID
												//	（キーワードが存在しない場合は０）
				)
{
	return 0;
}

//===========================================================================
//		アクセスルートの削除	
//
//		指定されたキーワードのアクセスルートの登録を削除する。
//		指定されたキーワードが登録されていない場合はエラー。
//
MINT mdmDEnt::DeleteAccessRoot(
						MCHAR		i_sKey[]	// キー
				)
{
	return 0;
}

} // namespace MC
