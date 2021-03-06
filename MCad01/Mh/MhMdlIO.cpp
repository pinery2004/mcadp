//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhMdlIO.cpp
//
//		家モデル読み書き
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MhDefParts.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"
#include "MmLib.h"
#include "MdLib.h"
#include "MdList.h"

#include "MhInpPlcParts.h"

#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MmCmd.h"
#include "MgGrp.h"
#include "MhPlcParts.h"
#include "MhRoof.h"

#include "MfFile.h"
#include "MmTenkai.h"

#include "MhDefDB.h"

#include "MdModel.h"

#include "MdmDB.h"

#include "MhModel.h"

#include "MmWnd.h"
namespace MC
{

#if( TRACE_IO)
extern	int iCrf_IO;
#endif

////////////////////////////////////////////////////////////////////////////
//	構造家モデルの読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT IeModel::MhMdlLoad(										//
						MCHAR*		i_sPathI		// 読み込みファイル　フルパス
				)
{
	MINT		ist = -1;
	MINT		ist1;
	MINT		ic;
	MhMdlIO		hMdl;
	MINT		iType;
	MINT		iSize;

	void*		pEnt;
	mhPlcParts*	pPlcEn = 0;
	MhRoofInfo*	pRoofEn = 0;
	MINT*		pnGrid;

	bool		fPlcSzChk = true;
	bool		fRoofSzChk = true;

	MgVect3D		vLnPlc;

	MDID		idEnt[3000];
	MINT		isz = 1;
	static MINT	iCe = 0;

	if ( i_sPathI == 0) {
		z_mnIA.SetInpKai( 1);
		mtPlcInp::SetInpKai( 1);
		GridDispCtrl::SetGridNum( NULL);										// 初期設定
		GridDispCtrl::XqtGridNum();
		IeModel::MhSetModFIeMdl( false);
		ist = 0;
		MQUIT;
	}

	// MDBオープン
	MhModel::Open();

	// DBファイルオープン
	ist1 = hMdl.Open( MBREAD, i_sPathI);
	if ( ist1 != 0)
		MQUIT;

	// DBファイル読み込み
	for (;;) {
		iSize = hMdl.ReadItem( &iType, (void**)&pEnt);
//===
#if( TRACE_IO)
		TRACE( "Roof iCrf_IO = %d\n", iCrf_IO++);
//			__debugbreak();														// ブレークポイント
#endif
//---
		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_GRID:												// グリッド
				// グリッドの読込
				pnGrid = (MINT*)pEnt;
				GridDispCtrl::SetGridNum( pnGrid);

				ist = mdmDEnt::CreateEnt( MhModel::m_db.pidLyr[MD_ID_LYR_GRID], &idEnt[iCe], isz);
				ist = mdmDEnt::SetAttr( idEnt[iCe++],	1, pnGrid);
				break;

			case MDR_ATRCD_HAITIEN_ST:											// 配置
				// 配置部品の読込
				MBFREE( pEnt);

				pPlcEn = (mhPlcParts*)malloc( sizeof( mhPlcParts));
				pPlcEn->Load( &hMdl);
				HaitiDb::MdPartsAdd( pPlcEn, NULL);								// ＯＰＴ群変更無しで追加

				ist = mdmDEnt::CreateEnt( MhModel::m_db.pidLyr[MD_ID_LYR_HAITI], &idEnt[iCe], isz);
				ist = mdmDEnt::SetAttr( idEnt[iCe++], 2, pPlcEn);
				break;

#if (MDR_TYPE2)
			case MDR_ATRCD_ROOFEN_ST:											// 屋根
				// 屋根の読込
				if( iSize == SZMINT()) {
					pRoofEn = new MhRoofInfo[1];
					pRoofEn->Load( &hMdl);
				} else if( iSize == sizeof(MhRoofInfo)) {
					pRoofEn = (MhRoofInfo*)pEnt;
					pRoofEn->Load( &hMdl);
				} else {
					ASSERT( iSize == sizeof(MhRoofInfo));
				}
				HaitiDb::MdRoofAdd( pRoofEn);

				ist = mdmDEnt::CreateEnt( MhModel::m_db.pidLyr[MD_ID_LYR_YANE], &idEnt[iCe], isz);
				ist = mdmDEnt::SetAttr( idEnt[iCe++],	3, pRoofEn);
				break;
#else
			case MDR_ATRCD_ROOFEN:												// 屋根
				// 屋根の読込
				ASSERT( iSize == sizeof(MhRoofInfo));

				pRoofEn = (MhRoofInfo*)pEnt;
				pRoofEn->Load( &hMdl);
				HaitiDb::MdRoofAdd( pRoofEn);

				ist = mdmDEnt::CreateEnt( MhModel::m_db.pidLyr[MD_ID_LYR_YANE], &idEnt[iCe], isz);
				ist = mdmDEnt::SetAttr( idEnt[iCe++],	3, pRoofEn);
				break;
#endif
			default:
				MBFREE( pEnt);
		}
	}
	hMdl.Close();

	for ( ic=1; ic<=MMAX_KAI; ic++) {
		z_mnIA.SetInpKai( ic);
		mtPlcInp::SetInpKai( ic);

		IeModel::MhKabeSetUpFlg();
		IeModel::MhNormKabe( 0);
		IeModel::MhKisoSetUpFlg();
		IeModel::MhNormKiso( 0);
	}

	z_mnIA.SetInpKai( 1);
	mtPlcInp::SetInpKai( 1);

	GridDispCtrl::SetGridNum( NULL);											// 初期設定
	GridDispCtrl::XqtGridNum();

	IeModel::MhSetModFIeMdl( false);
	ist = 0;
exit:
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	ＯＰＴ群管理情報レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhOptionSave(								//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
	// ＯＰＴ群管理情報の保存
																				//S	i_phMdl->Write( MDW_ATRCD_OPTION_KANRI, (MINT*)MhOptV::bmGOpt, MhOptV::nbmGOpt);
	i_phMdl->WriteItemI( MDW_ATRCD_OPTION_KANRI, (MINT*)MhOptV::bmGOpt, sizeof(MhOpt) * MhOptV::nbmGOpt);

	i_phMdl->WriteItemI( MDW_ATRCD_VERSION_KANRI0, &MhHistV::nVer);				// バージョン
	for (MINT ic=0; ic<MhHistV::nVer; ic++) {
		i_phMdl->WriteItemCH( MDW_ATRCD_VERSION_KANRI1, MhHistV::sVerC[ic], MSZ_HISTB);
		i_phMdl->WriteItemCH( MDW_ATRCD_VERSION_KANRI2, MhHistV::sVerB[ic], MSZ_HISTB);
		i_phMdl->WriteItemCH( MDW_ATRCD_VERSION_KANRI3, MhHistV::sVerD[ic], MSZ_HISTB);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	構造家モデルの書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT IeModel::MhMdlSave(									//
				const	MCHAR*		i_sPathO	// 書き込みファイル　フルパス
				)
{
	mhPlcParts*		pPlcEn1;
	MPOSITION		posH;
	MhRoofInfo*		pRoofEn1;
	MPOSITION		posR;
	MhMdlIO			hMdl;
	MINT			iDumy = 0;
	MINT			nGrid[4];

	hMdl.Open( MBWRITE, i_sPathO);

	// グリッドの保存
	GridDispCtrl::GetGridNum( nGrid);
																				//S	hMdl.Write( MDW_ATRCD_GRID, nGrid, SZMINT() * 4);			// グリッド
	hMdl.WriteItemI( MDW_ATRCD_GRID, nGrid, 4*SZMINT());						// グリッド
	
	// 配置部品の保存
	for ( pPlcEn1 = HaitiDb::MdGetHeadParts( &posH); pPlcEn1!=0;
		  pPlcEn1 = HaitiDb::MdGetNextParts( &posH)) {
		pPlcEn1->Save( &hMdl);
	}

	// 屋根の保存
	for ( pRoofEn1 = HaitiDb::MdGetHeadRoof( &posR); pRoofEn1!=0;
		  pRoofEn1 = HaitiDb::MdGetNextRoof( &posR)) {
		pRoofEn1->Save( &hMdl);
	}

	// ＯＰＴ群管理情報の保存
	MhOptionSave( &hMdl);

	hMdl.Close();

	return 0;
}

} // namespace MC
