//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmsRibbonBarParts.cpp
//
//		
//	1.4	部品選択
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhDefParts.h"
#include "MhInp.h"
#include "MhLib.h"
#include "MmPrompt.h"

namespace MC
{

// 部品名コンボボックス
static MINT z_nComboIdPartsSpec;								// 表示項目数
static MINT	z_iComboIdPartsSpec[MX_CMB_PARTSNM];				// 表示項目対応部品ID
static MINT z_iComboKmIdPartsNm;								// カレント選択項目番号

// 寸法型式選択用コンボボックス
static MINT z_nComboMbrId;										// 表示項目数
static MINT	z_iComboMbrId[MX_CMB_CDMEMBER];						// 表示項目対応寸法型式ID
static MINT z_iComboKmIdMbr;									// カレント選択項目番号

///////////////////////////////////////////////////////////////////////////////
//	部品選択用コンポボックスにカレントの組と分類の部材名一覧を設定し
//	対応する部材ＩＤテーブルを作成する
//
//	カレントの構成(組)コード( 屋根、小屋、天井、耐力壁、壁、床、基礎) と
//	分類コード("部材", "金物", "パネル", "屋根", "壁", "線分", "区画", "開口", "注記", "その他") とが
//	一致する部材のみ設定する

void mmInpAttr::InitComboPartsNm()
{
	int		ist;
	int		ic1;
	int		ip = 0;
	int		iKCdGp;								// カレント	構造構成(組)コード
	int		iKCdBr;								// カレント	部材分類コード
	mhPartsSpec	*pPartsSpec;					// 部材テーブル 部材
	int		iPTCdGp;							// 部材テーブル	部材　構成(組)コード
	int		iPTCdBr;							// 部材テーブル 部材　分類コード
	MCHAR*	pPTNmParts1;						// 部材テーブル 部材　部材名

	if ( !z_DlgKAttr.GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = z_DlgKAttr.GetCmbBzaiNm();
	pCmbBox->ResetContent();

	iKCdGp = z_mnIA.GetKCdGp();									// カレント	構造構成(組)コード
	iKCdBr = z_mnIA.GetKCdBr();									// カレント	部材分類コード

	int nPartsNm;
	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		iPTCdGp = pPartsSpec->GetPTCdGp();
		if ( iPTCdGp != iKCdGp)									// 構成(組)コードがカレントと不一致は無視
			continue;
		iPTCdBr = pPartsSpec->GetPTCdBr();
		if ( iKCdBr == MP_BR_OTHER) {							// 選択した分類がその他の場合
			if ( iPTCdBr == MP_BR_BUZAI ||						// "部材"、
				iPTCdBr == MP_BR_KANAGU ||						// "金物"、
				iPTCdBr == MP_BR_PANEL)							// "パネル"は無視
				continue;
		} else {												// 選択した分類が"部材", "金物", "パネル"の場合は
			if ( iPTCdBr != iKCdBr)								//		分類コードコードがカレントと不一致は無視
				 continue;
		}
		ASSERT( ip < MX_CMB_PARTSNM - 1);						// 部材コンボボックス項目　オーバフロー　<ERROR>
		z_iComboIdPartsSpec[ip] = ic1;							// 部材ＩＤをテーブルに設定
		pPTNmParts1 = pPartsSpec->GetPTNmParts1();				// 部材名を項目に追加
		ist = pCmbBox->InsertString( -1, pPTNmParts1);
		ip++;
	}
	z_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	z_iComboKmIdPartsNm = -1;
																				//S	z_mmIA.SetKCdBrB( false, false, false);						//	部材、金物、パネル、その他のラジオボタンを未選択に設定
}

///////////////////////////////////////////////////////////////////////////////
//	部品名項目番号で部品名コンポボックスを選択する
//	カレント部品名項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する
//	部品仕様の配置コードで配置コードコンポボックスをを選択する

void mmInpAttr::SelectComboPartsNmByKmId(
						MINT	i_iKmIdPartsNm	// 部品名項目番号
				)
{
	int iIdPartsSpec;
	if ( !z_DlgKAttr.GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = z_DlgKAttr.GetCmbBzaiNm();
//S	pCmbBox->ResetContent();
//	System::GetpMainFrame()->SelectCombo1( i_iKmIdPartsNm);
	pCmbBox->SetCurSel( i_iKmIdPartsNm);
	z_iComboKmIdPartsNm = i_iKmIdPartsNm;						// カレント部品名項目番号

	// 部品配置入力データへ設定
	iIdPartsSpec = z_iComboIdPartsSpec[z_iComboKmIdPartsNm];	// 部品仕様Id
	mhPartsSpec* pPartsSpec;
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);		// 部品仕様
	mtPlcInp::SetpPartsSpec( pPartsSpec);

//S	MINT iCdPlc = pPartsSpec->GetPTCdPlc();						// 部品仕様の配置コードで配置コードコンボを選択する
//	z_mmIA.SelectComboPlcCdByPlcCd( iCdPlc);
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	部品名で部品名コンポボックスを選択する
//	カレントの部品名項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する
//	部品仕様の配置コードで配置コードコンポボックスをを選択する
//
//	返値
//							≧ 0: 部品ID
//							＝-1: 該当なし

MINT mmInpAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// 部品名
				)
{
	MINT 	iIdPartsSpec = -1;
	MINT	iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "が部材テーブルに未設定です．"
		MQUIT;
	}
	z_mmIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

	iIdPartsSpec = z_iComboIdPartsSpec[iKmIdPartsNm];
exit:
	return iIdPartsSpec;
}

///////////////////////////////////////////////////////////////////////////////
//	部品名から部品名コンポボックスの部品名項目番号を取得する
//	コンボボックスの項目より指定された部材の部品IDを検索し、
//	該当の部品名項目番号を返す
//	返値
//							≧ 0: 部品ID
//							＝-1: 該当なし

MINT mmInpAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
{
	MINT		iKmIdPartsNm;
	MINT		ic1;
	MINT		iIdPartsSpec;
	mhPartsSpec	*pPartsSpec;
	
	for ( ic1=0; ic1<z_nComboIdPartsSpec; ic1++) {
		iIdPartsSpec = z_iComboIdPartsSpec[ic1];
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < z_nComboIdPartsSpec)
		iKmIdPartsNm = ic1;
	else
		iKmIdPartsNm = -1;
	return iKmIdPartsNm;
}

///////////////////////////////////////////////////////////////////////////////
//	部品名から部品IDを取得する
//							＝-1: 未選択
//							≧ 0: 部品ID

MINT mmInpAttr::GetComboPartsNmId(
						MCHAR* i_sNmParts1		// 部品名
				)
{
	MINT		ist;
	MINT		ic1;
	mhPartsSpec	*pPartsSpec;

	MINT	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < nPartsNm)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの部品IDを取得する
//							＝-1: 該当なし
//							≧ 0: 部品ID

MINT mmInpAttr::GetCurPartsNmId()
{
	MINT iIdPartsSpec;

	if ( z_iComboKmIdPartsNm >= 0 && z_iComboKmIdPartsNm < z_nComboIdPartsSpec) {
		iIdPartsSpec = z_iComboIdPartsSpec[z_iComboKmIdPartsNm];
	} else {
		iIdPartsSpec = -1;
	}
	return iIdPartsSpec;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式選択用コンポボックスに寸法型式の項目(一覧)を設定し
//	対応する寸法型式ＩＤテーブルを作成する
//
//	カレントの部材の寸法型式使用部位コードを持つ寸法型式のみ設定

void mmInpAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip;
	MCHAR	cMTp1;
	MCHAR	cMTp2;
	int		iIdPartsSpec;
	int		mxMbr;

	ip = 0;
	if ( !z_DlgKAttr.GetDispFlg())	goto EXIT;

	CComboBox* pCmbBox = z_DlgKAttr.GetCmbBzaiMbr();
	pCmbBox->ResetContent();

	iIdPartsSpec = z_mmIA.GetCurPartsNmId();
	if ( iIdPartsSpec >= 0) {
//		pCmbBox->>EnableToolTips(0);			NG

		cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];

		mxMbr = BuzaiCode::MhGetNoOfMbr();
		for ( ic1=0; ic1<mxMbr; ic1++) {
			pMbr = BuzaiCode::MhGetpMbr( ic1);

			for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {	// 一致する寸法型式使用部位コードがあるかnullまで調べる
				if ( cMTp1 == cMTp2) break;
			}
			if ( cMTp2 == 0) continue;							// 一致しない場合次の寸法型式に移る

			ASSERT( ip < MX_CMB_CDMEMBER - 1);					// 寸法型式選択コンボボックス項目　オーバフロー　<ERROR>
			z_iComboMbrId[ip] = ic1;
			pCmbBox->InsertString( -1, pMbr->GetMbrCode());
			ip++;
		}
	}
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	z_nComboMbrId = ip;
	z_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法形式項目番号で選択し
//	カレントの寸法型式項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する

void mmInpAttr::SelectComboPartsMbrByKmId(
						MINT	i_iKmIdMbr			// 寸法型式項目番号
				)
{
	if ( !z_DlgKAttr.GetDispFlg())	goto EXIT;

//S	System::GetpMainFrame()->SelectCombo2( i_iKmIdMbr);
	CComboBox* pCmbBox = z_DlgKAttr.GetCmbBzaiMbr();
	pCmbBox->SetCurSel(	i_iKmIdMbr);
	z_iComboKmIdMbr = i_iKmIdMbr;

	// 部品配置入力データへ設定
	int iMbrId;
	MhMbr* pMbr;
	iMbrId = z_iComboMbrId[i_iKmIdMbr];					// 寸法形式ID
	mtPlcInp::SetIdMbr( iMbrId); 
	pMbr = BuzaiCode::MhGetpMbr( iMbrId);				// 寸法形式仕様
	mtPlcInp::SetpMbr( pMbr);
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法型式で選択し
//	カレントの寸法型式項目番号を設定する
//							＝-1: 該当なし
//							≧ 0: 寸法型式ID

MINT mmInpAttr::SelectComboMbrCdByMbrCd( MCHAR* sCdMbr)
{
	MINT		iMbrId = -1;
	MINT		iKmIdMbr;

	iKmIdMbr = z_mmIA.GetComboMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);		// "が寸法型式テーブルに未設定です．"
		MQUIT;
	}
	z_mmIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = z_iComboMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法形式から寸法型式コンボボックスの寸法型式項目番号を取得する
//							＝-1: 該当なし
//							≧ 0: 部品ID

MINT mmInpAttr::GetComboMbrKmId( MCHAR* sCdMbr)
{
	MINT		ist;
	MINT		ic1;
	MINT		iMbrId;
	MhMbr	*pMbr;
	
	for ( ic1=0; ic1<z_nComboMbrId; ic1++) {
		iMbrId = z_iComboMbrId[ic1];
		pMbr = BuzaiCode::MhGetpMbr( iMbrId);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < z_nComboMbrId)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法形式から寸法型式IDを取得する
//							＝-1: 該当なし
//							≧ 0: 寸法型式ID

static MINT GetComboMbrCdId( MCHAR* sCdMbr)
{
	MINT		ist;
	MINT		ic1;
	MhMbr	*pMbr;

	MINT mxMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<mxMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < mxMbr)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの寸法型式IDを取得する
//							＝-1: 未選択
//							≧ 0: 寸法型式ID

MINT mmInpAttr::GetComboMbrCdId()
{
	MINT		iMbrId;

	if ( z_iComboKmIdMbr >= 0 && z_iComboKmIdMbr < z_nComboMbrId) {
		iMbrId = z_iComboMbrId[z_iComboKmIdMbr];
	} else {
		iMbrId = -1;
	}
	return iMbrId;
}

} // namespace MC