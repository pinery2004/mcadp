//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdLyr.cpp
//
//		レイヤー
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgMatD.h"

#include "MdModel.h"

#define DLL_EXPORT_DLYR_DO
#include "MdmDB.h"
#include "Mdm.h"

namespace MC
{

//===========================================================================
//		レイヤーの生成
//
MINT DLyr::CreateLyr(
						MDID	i_idScm,		// スキーマID
						MDID	i_idGrp,		// グループID
						MDID*	o_pidLyr,		// レイヤーID
						MINT	i_sz /*=10*/	// 初期エンティティIdバッファサイズ
				)
{
	MdmSetLYR*	pLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();
	
	ASSERT( MDISSCM( i_idScm));
	ASSERT( MDISGRP( i_idGrp));

	// LyrBfより空きのIDを取得し、レイヤーの子のID設定用領域を設ける
	//
	if ( pCurMdl->m_LyrBf.m_idSpaceLast == 0) {
		// 削除して空きになっているIDがない場合は最終ID+1を使用する
		pCurMdl->m_LyrBf ++;
		*o_pidLyr = pCurMdl->m_LyrBf.m_n;
		pLyr = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( *o_pidLyr)];

	} else {
		// 削除して空きになっているIDがある場合はそのIDを使用する
		ASSERT( pCurMdl->m_LyrBf.m_nidSpace >= 1);

		*o_pidLyr = pCurMdl->m_LyrBf.m_idSpaceLast;
		pLyr = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( *o_pidLyr)];

		// 空きエリアへのIDを一つ戻す
		pCurMdl->m_LyrBf.m_idSpaceLast = MDSPACEBEFORE( pLyr);
		if ( pCurMdl->m_LyrBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_LyrBf.m_pst[MIDtoHN( pCurMdl->m_LyrBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_LyrBf.m_nidSpace--;
	}

	// スキーマID、グループIDの設定、エンティティIdバッファの生成
	pLyr->SetInit( i_idGrp, i_idScm, i_sz, 4);					// グループ、スキーマ、
																// 子IDエリア、
																// ウィンドウ毎の表示・検知モード(初期は4ウィンドウ)
	// 生成レイヤーとグループ、スキーマとのリンクを付ける
	pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_GidC += (*o_pidLyr);
	pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_GidC += (*o_pidLyr);

																								//EXIT:
	return 0;
}

//===========================================================================
//		レイヤーの削除
//
MINT DLyr::DeleteLyr(							//
						MDID		i_idLyr		// レイヤーId
				)
{
	MdmSetLYR*	pLyrB;							// 直前に削除したレイヤー
	MdmSetLYR*	pLyrC;							// 削除レイヤー
	MDID		idGrp;
	MDID		idScm;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	// グループ、スキーマからのリンクを削除する
	pLyrC = &pCurMdl->m_LyrBf.m_pst[ MIDtoHN( i_idLyr)];
	idGrp = pLyrC->m_idP1;
	idScm = pLyrC->m_idP2;
	pCurMdl->m_GrpBf.m_pst[MIDtoHN( idGrp)] -= i_idLyr;
	pCurMdl->m_ScmBf.m_pst[MIDtoHN( idScm)] -= i_idLyr;

	// 削除し割り当て待ちの空きレイヤー数に追加
	pCurMdl->m_LyrBf.m_nidSpace++;
	// レイヤー削除フラグ設定と使用エリア開放
	MDSPACEID( pLyrC) = MDID_DELETE;
	pLyrC->Free();

	// 空きエリアリンクに追加
	// 直前に削除したレイヤーの次のレイヤーとする
	if ( pCurMdl->m_LyrBf.m_idSpaceLast) {
		pLyrB = &pCurMdl->m_LyrBf.m_pst[ MIDtoHN( pCurMdl->m_LyrBf.m_idSpaceLast)];
		MDSPACENEXT( pLyrB) = i_idLyr;
	}
	// 空きエリアリンクの先頭にリンク付ける
	MDSPACEBEFORE( pLyrC) = pCurMdl->m_LyrBf.m_idSpaceLast;
	MDSPACENEXT( pLyrC) = 0;
	pCurMdl->m_LyrBf.m_idSpaceLast = i_idLyr;
	return 0;
}

//===========================================================================
//		カレントレイヤーIdを得る
//
MDID DLyr::GetCurLyrId()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return	pCurMdl->m_idCurGrp;
}

//===========================================================================
//		カレントレイヤーIdを設定する
//
MDID DLyr::SetCurLyrId(					// 直前のカレントレイヤーId
						MDID		i_idLyr		// レイヤーId
				)
{
	MDID idCurGrp;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	idCurGrp = pCurMdl->m_idCurGrp;
	pCurMdl->m_idCurGrp = i_idLyr;
	return	idCurGrp;
}

//===========================================================================
//		レイヤー数を得る
//
MINT DLyr::GetLyrCount ()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return ( pCurMdl->m_LyrBf.m_n - pCurMdl->m_LyrBf.m_nidSpace);
}

//===========================================================================
//		全レイヤーIdのセットを得る
//

MINT DLyr::GetLyrIdAll (
						MDIDSET*	o_pGidLyr	// レイヤーIdセット
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	o_pGidLyr->m_n = 0;
	for ( iC=0; iC<pCurMdl->m_LyrBf.m_n; iC++) {
		if ( MDSPACEID( &pCurMdl->m_LyrBf.m_pst[iC]) != MDID_DELETE)
			(*o_pGidLyr) += MHNtoID( iC);
	}
	return 0;
}

//===========================================================================
//		グループIdとスキーマIdからレイヤーIdを得る
//

MINT DLyr::GetLyrId( 
						MDID		i_idScm,	// スキーマId
						MDID		i_idGrp,	// グループId
						MDID*		o_pidLyr	// レイヤーId
				)
{
	MINT		iC;
	MDIDSET*	pGidL;
	MDID		idLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));
	ASSERT( MDISGRP( i_idGrp));

	// 指定Idのスキーマの子Idセット(レイヤーIdセット)を得る
	pGidL = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_GidC;

	// 親のグループIdが指定グループIdのレイヤーを探す
	*o_pidLyr = 0;
	for ( iC=0; iC<pGidL->m_n; iC++) {
		idLyr = pGidL->m_pst[iC];
		if ( idLyr > 0) {
			if ( pCurMdl->m_LyrBf.m_pst[MIDtoHN( idLyr)].m_idP2 == i_idGrp) {
				*o_pidLyr = idLyr;
				break;
			}
		}
	}
	return 0;
}

//===========================================================================
//		レイヤーIdからグループIdを取得
//
MINT DLyr::GetGrpId (
						MDID	i_idLyr,		// レイヤーId
						MDID*	o_idGrp			// グループId
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		RETURN_ID_ERR();

	*o_idGrp = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_idP1;
	return 0;
}

//===========================================================================
//		レイヤーIdからスキーマIdを取得
//
MINT DLyr::GetScm (
						MDID	i_idLyr,		// レイヤーId
						MDID*	o_idScm			// スキーマId
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		RETURN_ID_ERR();

	*o_idScm = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_idP2;
	return 0;
}

//===========================================================================
//		レイヤーIdからエンティティIdのセットを取得する
//
MINT DLyr::GetEnt(
						MDID		i_idLyr,	// レイヤーId
						MDIDSET*	o_pGidEnt	// エンティティIdセット
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		RETURN_ID_ERR();

	*o_pGidEnt = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GidC;
	return 0;
}

//===========================================================================
//		レイヤーの表示／検知属性を取得
//
MINT DLyr::GetLyrDispMode (
						MDID		i_idWin,	// ウィンドウId
						MDID		i_idLyr,	// レイヤーId
						MINT*		o_iaWD		// ウィンドウ表示検地モード
												//		0: 未設定
												//		1: 表示 OFF	検地 OFF			×
												//		2: 表示 ON	検地 OFF			△
												//		3: 表示 ON	検地 ON				○
												//		5: 表示 OFF	検地 OFF	Lock	×p
												//		6: 表示 ON	検地 OFF	Lock	△p
												//		7: 表示 ON	検地 ON		Lock	○p
				)
{
	MUBYTESET*	pAWDSet;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pAWDSet = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GaWD;
	if ( pAWDSet->m_n == 0)
		*o_iaWD = 0;
	else {
		if ( i_idWin > pAWDSet->m_n) {
			RETURN_ID_ERR();
		}
		*o_iaWD = pAWDSet->m_pst[MIDtoHN( i_idWin)];
	}
	return 0;
}

//===========================================================================
//		レイヤーの表示／検知属性を設定
//
MINT DLyr::SetLyrDispMode (
						MINT		i_idWin,	// ウィンドウId
						MINT		i_idLyr,	// レイヤーId
						MINT		i_iaWD		// ウィンドウ表示検地モード
												//		GetLyrDispModeの説明を参照
				)
{
	MUBYTESET*	pAWDSet;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pAWDSet = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GaWD;

	if ( i_idWin > pAWDSet->m_sz) {
		pAWDSet->ReSize( i_idWin+3);
	}
	pAWDSet->m_pst[MIDtoHN( i_idWin)] = i_iaWD;
	if ( i_idWin > pAWDSet->m_n)
		pAWDSet->m_n = i_idWin;
	return 0;
}

//===========================================================================
//		レイヤーの表示／検知属性を設定
//
MINT DLyr::SetLyrsDispMode (
						MINT		i_idWin,	// ウィンドウId
				const	MDIDSET&	i_GidScm,	// レイヤーIdセット
						MINT		i_iaWD		// ウィンドウ表示検地モード
												//		GetLyrDispModeの説明を参照
				)
{
	MINT	iC;
	MDID	idLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();

	for ( iC=0; iC<i_GidScm.m_n; iC++) {
		idLyr = i_GidScm.m_pst[iC];
		ASSERT( MDISLYR( idLyr));
		SetLyrDispMode ( i_idWin, idLyr, i_iaWD);
	}
	return 0;
}

//===========================================================================
//		カレントウィンドウに対する表示／検知属性によるレイヤーの検索
//
MINT DLyr::SerachLyrDispMode (
						MINT		i_imdD,		// ウィンドウ表示検地モード選択コード
												//	　1 : ﾚｲﾔｰ表で○のものだけ
												//	　2 :         ○と△
												//	　3 :         ○と△と×
												//	以外:       ○と△と×と−

						MDIDSET*	o_GidScm,	// レイヤーセット
						MINT*		o_itpCurWin	// カレントウィンドウタイプ( 0:３Ｄ、1：図面）
				)
{
	MINT	iC;
	MINT	iaWD;
	bool	bD;
	MdModel* pCurMdl = Mdm::GetCurModel();

	//	レイヤーセットの検索
	o_GidScm->m_n = 0;

	for ( iC=0; iC<pCurMdl->m_LyrBf.m_n; iC++) {
		iaWD = pCurMdl->m_LyrBf.m_pst[iC].m_GaWD[MIDtoHN( pCurMdl->m_idCurWin)];
		switch ( i_imdD )
		{
		case 1:
			bD = (iaWD & 1) != 0;
			break;
		case 2:
			bD = (iaWD & 3) != 0;
			break;
		case 3:
			bD = (iaWD & 7) != 0;
			break;
		default:
			bD = true;
		}
		if ( bD)
			o_GidScm += MHNtoID( iC);
	}

	//	カレントウィンドウタイプ
	*o_itpCurWin = pCurMdl->m_WinBf.m_pst[MIDtoHN( pCurMdl->m_idCurWin)].m_itpWin;
	return 0;
}

//===========================================================================
//		レイヤーのカレント表示属性を取得
//
MINT DLyr::GetLyrCurMaterial (
						MINT	i_idLyr,		// レイヤーId
						MDFIG*	o_pFig			// カレントレイヤー表示属性
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	*o_pFig = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_CurFig;
	return 0;
}

//===========================================================================
//		レイヤーのカレント表示属性を設定
//
MINT DLyr::SetlyrCurMaterial (
						MINT	i_idLyr,		// レイヤーId
						MDFIG&	i_Fig			// レイヤー表示属性
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_CurFig = i_Fig;

	return 0;
}

//===========================================================================
//		レイヤーのデフォルト表示属性を取得
//
MINT DLyr::GetLyrDefaultMaterial (
						MINT	i_idLyr,		// レイヤーId
						MDFIG*	o_pFig			// デフォルトレイヤー表示属性
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	*o_pFig = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_DfltFig;
	return 0;
}

//===========================================================================
//		レイヤーのデフォルト表示属性を設定
//
MINT DLyr::SetlyrDefaultMaterial (
						MINT	i_idLyr,		// レイヤーId
						MDFIG&	i_Fig			// レイヤー表示属性
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_DfltFig = i_Fig;
	return 0;
}

} // namespace MC
