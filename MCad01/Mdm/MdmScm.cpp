//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdScm.cpp
//
//		スキーマ
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

//
//===========================================================================
//		スキーマの生成
//
MINT DGrp::CreateScm(								//
						MCHAR		i_sName[],		// レイヤー名
						MDID*		o_pidScm,		// スキーマId
						MINT		i_sz /*=10*/	// 初期スキーマIdバッファサイズ
				)
{
	MdmSetSCM*	pScm;
	MdModel*	pCurMdl = Mdm::GetCurModel();
	
	// ScmBfより空きのIDを取得し、スキーマの子のID設定用領域を設ける
	//
	if ( pCurMdl->m_ScmBf.m_idSpaceLast == 0) {
		// 削除して空きになっているIDがない場合は最終ID+1を使用する
		pCurMdl->m_ScmBf ++;
		*o_pidScm = pCurMdl->m_ScmBf.m_n;
		pScm = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( *o_pidScm)];

	} else {
		// 削除して空きになっているIDがある場合はそのIDを使用する
		ASSERT( pCurMdl->m_ScmBf.m_nidSpace >= 1);

		*o_pidScm = pCurMdl->m_ScmBf.m_idSpaceLast;
		pScm = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( *o_pidScm)];

		// 空きエリアへのIDを一つ戻す
		pCurMdl->m_ScmBf.m_idSpaceLast = MDSPACEBEFORE( pScm);
		if ( pCurMdl->m_ScmBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_ScmBf.m_pst[MIDtoHN( pCurMdl->m_ScmBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_ScmBf.m_nidSpace--;
	}

	//	スキーマIDにに子IDの設定用領域を確保する
	pScm->m_GidC.Alloc( i_sz);

	pScm->SetInit( 0, i_sName);

	return 0;
}

//
//===========================================================================
//		スキーマの削除
//
MINT DGrp::DeleteScm(							//
						MDID		i_idScm		// スキーマId
				)
{
	MdmSetSCM*	idScmB;							// 直前に削除したスキーマ
	MdmSetSCM*	idScmC;							// 削除レスキーマ
	MdModel*	pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	// 削除し割り当て待ちのスキーマ数
	pCurMdl->m_ScmBf.m_nidSpace++;
	// スキーマ削除
	idScmC = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)];
	MDSPACEID( idScmC) = MDID_DELETE;
	idScmC->Free();

	// 空きエリアリンクに追加
	// 直前に削除したスキーマの次のスキーマとする
	if ( pCurMdl->m_ScmBf.m_idSpaceLast) {
		idScmB = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( pCurMdl->m_ScmBf.m_idSpaceLast)];
		MDSPACENEXT( idScmB) = i_idScm;
	}
	// 空きエリアリンクの先頭にリンク付ける
	MDSPACEBEFORE( idScmC) = pCurMdl->m_ScmBf.m_idSpaceLast;
	MDSPACENEXT( idScmC) = 0;
	pCurMdl->m_ScmBf.m_idSpaceLast = i_idScm;
	return 0;
}

//
//===========================================================================
//		カレントスキーマIdを得る
//
MDID DGrp::GetCurScmId()
{
	MdModel* pCurMdl = Mdm::GetCurModel();
	return	pCurMdl->m_idCurScm;
}

//
//===========================================================================
//		カレントスキーマIdを設定する
//
MDID DGrp::SetCurScmId(
						MDID		i_idScm	// スキーマId
				)
{
	MDID idCurScm;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	idCurScm = pCurMdl->m_idCurScm;
	pCurMdl->m_idCurScm = i_idScm;
	return	idCurScm;
}

//
//===========================================================================
//		スキーマIdのレイヤー名を得る
//
MINT DGrp::GetScmNameFromId(
						MDID		i_idScm,	// スキーマId
						MCHAR*		o_sLName,	// レイヤー名
						int			i_nLName	// レイヤー名最大文字数
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( o_sLName, i_nLName, pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_psName);
	return 0;
}

//
//===========================================================================
//	xx	スキーマIdのレイヤー名を設定する
//
MINT DGrp::SetScmNameFromId(
						MDID		i_idScm,	// スキーマId
						int			i_nLName,	// レイヤー名最大文字数				)
						MCHAR*		i_psName	// レイヤー名
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_psName, i_nLName, i_psName);
	return 0;
}

//
//===========================================================================
//		レイヤー名よりスキーマIdを得る
//
MINT DGrp::GetScmIdFromName (
						MCHAR*		i_psName,	// レイヤー名
						MDID*		o_pidScm	// スキーマId
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	for ( iC=0; iC<pCurMdl->m_ScmBf.m_n; iC++) {
		if ( Mstrcmp(  pCurMdl->m_ScmBf.m_pst[iC].m_psName, i_psName))
			break;
	}
	if ( iC < pCurMdl->m_ScmBf.m_n)
		*o_pidScm = iC;
	else
		*o_pidScm = 0;
	return 0;
}

//
//===========================================================================
//		スキーマ数を得る
//
MINT DGrp::GetScmCount ()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return ( pCurMdl->m_ScmBf.m_n - pCurMdl->m_ScmBf.m_nidSpace);
}

//
//===========================================================================
//		全スキーマIdのセットを得る
//

MINT DGrp::GetScmIdAll (
//						MdGrpS<MINT>*	o_pGidScm	// スキーマIdセット
						MDIDSET*		o_pGidScm	// スキーマIdセット
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	o_pGidScm->m_n = 0;
	for ( iC=0; iC<pCurMdl->m_ScmBf.m_n; iC++) {
		if ( MDSPACEID( &pCurMdl->m_ScmBf.m_pst[iC]) != MDID_DELETE)
			(*o_pGidScm) += (iC+1);
	}
	return 0;
}

} // namespace MC
