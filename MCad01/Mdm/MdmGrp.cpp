//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdGrp.cpp
//
//		モデルデータベース
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"

#include "MdModel.h"
#define DLL_EXPORT_DGRP_DO
#include "MdmDB.h"
#include "Mdm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

//===========================================================================
//		グループの生成
//
	MINT DGrp::CreateGrp(								//
					MCHAR		i_sName[],		// グループ名
					MREAL		i_rKt,			// 階高さ
					MREAL		i_rFl,			// 床高さ
					MDID*		o_pidGrp,		// グループId
					MINT		i_sz/*=10*/		// 初期グループIdバッファサイズ
				)
{
	MdmSetGRP*	pGrp;
	MdModel*	pCurMdl = Mdm::GetCurModel();

	// GrpBfより空きのIDを取得し、グループの子のID設定用領域を設ける
	//
	if ( pCurMdl->m_GrpBf.m_idSpaceLast == 0) {
		// 削除して空きになっているIDがない場合は最終ID+1を使用する
		pCurMdl->m_GrpBf ++;
		*o_pidGrp = pCurMdl->m_GrpBf.m_n;
		pGrp = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( *o_pidGrp)];

	} else {
		// 削除して空きになっているIDがある場合はそのIDを使用する
		ASSERT( pCurMdl->m_GrpBf.m_nidSpace >= 1);

		*o_pidGrp = pCurMdl->m_GrpBf.m_idSpaceLast;
		pGrp = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( *o_pidGrp)];

		// 空きエリアへのIDを一つ戻す
		pCurMdl->m_GrpBf.m_idSpaceLast = MDSPACEBEFORE( pGrp);
		if ( pCurMdl->m_GrpBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_GrpBf.m_pst[MIDtoHN( pCurMdl->m_GrpBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_GrpBf.m_nidSpace--;
	}

	//	生成グループに子IDの設定用領域を確保する
	pGrp->m_GidC.Alloc( (int)i_sz);

	// グループ名、階高さ、床高さを設定する
	pGrp->SetInit( 0, i_sName, i_rKt, i_rFl);
	return 0;
}

//===========================================================================
//		グループの削除
//
MINT DGrp::DeleteGrp(								//
						MDID		i_idGrp		// グループId
				)
{
	MdmSetGRP*	pGrpB;							// 直前に削除したグループ
	MdmSetGRP*	pGrpC;							// 削除グループ
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	// 削除し割り当て待ちのグループ数
	pCurMdl->m_GrpBf.m_nidSpace++;

	// グループ削除
	pGrpC = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)];
	MDSPACEID( pGrpC) = MDID_DELETE;
	pGrpC->Free();

	// 空きエリアリンクに追加
	// 直前に削除したグループの次のグループとする
	if ( pCurMdl->m_GrpBf.m_idSpaceLast) {
		pGrpB = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( pCurMdl->m_GrpBf.m_idSpaceLast)];
		MDSPACENEXT( pGrpB) = i_idGrp;
	}

	// 空きエリアリンクの先頭にリンク付ける
	MDSPACEBEFORE( pGrpC) = pCurMdl->m_GrpBf.m_idSpaceLast;
	MDSPACENEXT( pGrpC) = 0;
	pCurMdl->m_GrpBf.m_idSpaceLast = i_idGrp;
	return 0;
}

//===========================================================================
//		グループの階高とFLの問い合わせ
//
MINT DGrp::GetGrpParam(
						MDID		i_idGrp,	// グループId
						MREAL*		o_prKt,		// 階高さ
						MREAL*		o_prFl		// 床高さ
				)
{
	MdmSetGRP*	pGrp;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	pGrp = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)];
	*o_prKt = pGrp->m_rKt;
	*o_prFl = pGrp->m_rFl;
	return 0;
}

//===========================================================================
//		グループの階高とFLを設定
//
MINT DGrp::SetGrpParam(
						MDID		i_idGrp,	// グループId
						MREAL		i_rKt,		// 階高さ
						MREAL		i_rFl		// 床高さ
				)
{
	MdmSetGRP*	pGrp;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	pGrp = &pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)];
	pGrp->m_rKt = i_rKt;
	pGrp->m_rFl = i_rFl;
	return 0;
}

//===========================================================================
//		カレントグループIdを得る
//
MDID DGrp::GetCurGrpId()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return	pCurMdl->m_idCurGrp;
}

//===========================================================================
//		カレントグループIdを設定する
//
MDID DGrp::SetCurGrpId(							// 直前のグループId
						MDID		i_idGrp		// グループId
				)
{
	MDID idCurGrp;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	idCurGrp = pCurMdl->m_idCurGrp;
	pCurMdl->m_idCurGrp = i_idGrp;

	// カレント座標変換マトリックスを設定する
	DLyr::SetCurCoord( pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_MTrans);
	return	idCurGrp;
}

//===========================================================================
//		グループIdのグループ名を得る
//
MINT DGrp::GetGrpNameFromId(
						MDID		i_idGrp,	// グループId
						MCHAR*		o_sGName,	// グループ名
						int			i_nGName	// グループ名最大文字数
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	Mstrcpy_s( o_sGName, i_nGName, pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_psName);
	return 0;
}

//===========================================================================
//	xx	グループIdのグループ名を設定する
//
MINT DGrp::SetGrpNameFromId(
						MDID		i_idGrp,	// グループId
						int			i_nGName,	// グループ名最大文字数
						MCHAR*		i_sGName	// グループ名
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	Mstrcpy_s( pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_psName, i_nGName, i_sGName);
	return 0;
}

//===========================================================================
//		グループ名よりグループIdを得る
//
MINT DGrp::GetGrpIdFromName (
						MCHAR*		i_sName,	// グループ名
						MDID*		o_pidGrp	// グループId
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	for ( iC=0; iC<pCurMdl->m_GrpBf.m_n; iC++) {
		if ( Mstrcmp(  pCurMdl->m_GrpBf.m_pst[iC].m_psName, i_sName))
			break;
	}
	if ( iC < pCurMdl->m_GrpBf.m_n)
		*o_pidGrp = MHNtoID( iC);
	else
		*o_pidGrp = 0;
	return 0;
}

//===========================================================================
//		グループ数を得る
//
MINT DGrp::GetGrpCount ()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return ( pCurMdl->m_GrpBf.m_n - pCurMdl->m_GrpBf.m_nidSpace);
}

//===========================================================================
//		全グループIdのセットを得る
//

MINT DGrp::GetGrpIdAll (
						MDIDSET*		o_pGidGrp	// グループIdセット
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	o_pGidGrp->m_n = 0;
	for ( iC=0; iC<pCurMdl->m_GrpBf.m_n; iC++) {
		if ( MDSPACEID( &pCurMdl->m_GrpBf.m_pst[iC]) != MDID_DELETE)
			(*o_pGidGrp) += MHNtoID( iC);
	}
	return 0;
}

//===========================================================================
//		グループの座標変換マトリックスを得る
//
MINT	MdlGetGrpCoord (
						MDID		i_idGrp,
						MgMat3DE*		o_mTrans	// 座標変換マトリックス
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISGRP( i_idGrp));

	*o_mTrans = pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_MTrans;
	return 0;
}

//===========================================================================
//		基準座標変換マトリックスを得る
//
//		データベースをオープンすると、基準座標変換マトリックスは必ず１つ存在する。
//
MgMat3DE	MdlGetBaseCoord ( )						// 基準座標変換マトリックス
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return pCurMdl->m_MBaseTrans;
}


//===========================================================================
//		カレント座標変換マトリックスを得る
//
//		１つのグループには１つの座標系が存在する。
//		SetCurGrpIdでグループがカレントに設定されると、
//		そのグループの座標系がカレント座標系になる。
//		Inp:Point等で得られる座標値はカレント座標系上の座標値となる。
//
MgMat3DE	MdlGetCurCoord ( )						// カレント座標変換マトリックス
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return pCurMdl->m_MCurTrans;
}

//===========================================================================
//		カレント座標変換マトリックスを設定
//
//		１つのグループには１つの座標系が存在する。
//		SetCurGrpIdでグループがカレントに設定されると、
//		そのグループの座標系がカレント座標系になる。
//		Inp:Point等で得られる座標値はカレント座標系上の座標値となる。
//
//		カレント座標系を一時的に変更する場合は、事前にGetCurCoordで
//		元のカレント座標系を問い合わせておき、処理終了時に元に戻すこと。
//
MgMat3DE DLyr::SetCurCoord (
						MgMat3DE&		i_MTransr	// 座標変換マトリックス
				)
{
	MgMat3DE	MTrans;
	MdModel* pCurMdl = Mdm::GetCurModel();

	MTrans = pCurMdl->m_MCurTrans;
	pCurMdl->m_MCurTrans = i_MTransr;
	return MTrans;
}

} // namespace MC
