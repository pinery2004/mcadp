//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarPartsAttr2.cpp
//
//		
//	属性入力リボンバー 	部品選択
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"
#include "MainFrm.h"

#define DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhDefParts.h"
#include "MhInpPlcParts.h"
#include "MhLib.h"
#include "MmPrompt.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	部品選択用コンポボックスにカレントの組と分類の部材名一覧を設定し
//	対応する部材ＩＤテーブルを作成する
//
//	カレントの構成(組)コード( 屋根、小屋、天井、耐力壁、壁、床、基礎) と
//	分類コード("部材", "金物", "パネル", "屋根", "壁", "線分", "区画", "開口", "注記", "その他") とが
//	一致する部材のみ設定する

void mnIoPartsAttr::InitComboPartsNm()
{
	int		ist;
	int		ic1;
	int		ip = 0;
	int		iKCdGp = z_mnIA.GetKCdGp();			// カレント	構造　構成(組)コード
	int		iKCdBr = z_mnIA.GetKCdBr();			// カレント	部材　分類コード
	mhPartsSpec	*pPartsSpec;					// 部材テーブル 部材
	int		iPTCdGp;							// 部材テーブル	部材　構成(組)コード
	int		iPTCdBr;							// 部材テーブル 部材　分類コード
	MCHAR*	pPTNmParts1;						// 部材テーブル 部材　部材名

	CMFCRibbonComboBox* pCmbBox = mmpComboBuzai();
	pCmbBox->RemoveAllItems();

	int		nPartsNm;
	nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
	for ( ic1=0; ic1<nPartsNm; ic1++) {
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( ic1);
		iPTCdGp = pPartsSpec->GetPTCdGp();
		if ( iKCdGp != iPTCdGp)									// 構成(組)コードがカレントと不一致は無視
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
		m_iComboIdPartsSpec[ip] = ic1;							// 部材ＩＤをテーブルに設定
		pPTNmParts1 = pPartsSpec->GetPTNmParts1();				// 部材名を項目に追加
		ist = pCmbBox->AddItem( pPTNmParts1);
		ip++;
	}
	m_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}
	m_iComboKmIdPartsNm = -1;
	z_mnIA.SetKCdBrB( false, false, false);						//	部材、金物、パネル、その他のラジオボタンを未選択に設定
}

///////////////////////////////////////////////////////////////////////////////
//	部品名項目番号で部品名コンポボックスを選択する
//	カレント部品名項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する
//	部品仕様の配置コードで配置コードコンポボックスをを選択する

void mnIoPartsAttr::SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// 部品名項目番号
				)
{
	System::GetpMainFrame()->SelectCombo1( i_iKmIdPartsNm);
	m_iComboKmIdPartsNm = i_iKmIdPartsNm;						// カレント部品名項目番号

	// 部品配置入力データへ設定
	int iIdPartsSpec;
	iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];			// 部品仕様Id
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	mhPartsSpec *pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);	// 部品仕様
	mtPlcInp::SetpPartsSpec( pPartsSpec);
	int iCdPlc;
	iCdPlc = pPartsSpec->GetPTCdPlc();						// 部品仕様の配置コードで配置コードコンボを選択する
	z_mnIA.SelectComboPlcCdByPlcCd( iCdPlc);
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

int mnIoPartsAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// 部品名
				)
{
	int	 	iIdPartsSpec = -1;
	int		iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "が部材テーブルに未設定です．"
		MQUIT;
	}
	z_mnIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

	iIdPartsSpec = m_iComboIdPartsSpec[iKmIdPartsNm];
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

int mnIoPartsAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
{
	int			iKmIdPartsNm;
	int			ic1;
	int			iIdPartsSpec;
	mhPartsSpec	*pPartsSpec;
	
	for ( ic1=0; ic1<m_nComboIdPartsSpec; ic1++) {
		iIdPartsSpec = m_iComboIdPartsSpec[ic1];
		pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
		if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), i_sNmParts1) == 0)
			break;
	}
	if ( ic1 < m_nComboIdPartsSpec)
		iKmIdPartsNm = ic1;
	else
		iKmIdPartsNm = -1;
	return iKmIdPartsNm;
}

///////////////////////////////////////////////////////////////////////////////
//	部品名から部品IDを取得する
//							＝-1: 未選択
//							≧ 0: 部品ID

int mnIoPartsAttr::GetComboPartsNmId(
						MCHAR* i_sNmParts1		// 部品名
				)
{
	int			ist;
	int			ic1;
	mhPartsSpec	*pPartsSpec;

	int		nPartsNm = BuzaiCode::MhGetNoOfPartsSpec();
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

int mnIoPartsAttr::GetCurPartsNmId()
{
	int	 iIdPartsSpec;

	if ( m_iComboKmIdPartsNm >= 0 && m_iComboKmIdPartsNm < m_nComboIdPartsSpec) {
		iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];
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

void mnIoPartsAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip = 0;

	CMFCRibbonComboBox* pCmbBox = mmpComboMbr();
	pCmbBox->RemoveAllItems();

	int		iIdPartsSpec;
	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	if ( iIdPartsSpec == -1) {
//		pCmbBox->>EnableToolTips(0);			NG
		goto exit;
	}

	MCHAR	cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];
	MCHAR	cMTp2;
	int		nMbr;
	nMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<nMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);

		for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {		// 一致する寸法型式使用部位コードがあるかnullまで調べる
			if ( cMTp1 == cMTp2) break;
		}
		if ( cMTp2 == 0) continue;								// 一致しない場合次の寸法型式に移る

		ASSERT( ip < MX_CMB_CDMEMBER - 1);						// 寸法型式選択コンボボックス項目　オーバフロー　<ERROR>
		m_iComboMbrId[ip] = ic1;
		pCmbBox->AddItem( pMbr->GetMbrCode());
		ip++;
	}
exit:
	m_nComboMbrId = ip;
	if ( ip == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	}

	m_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法形式項目番号で選択し
//	カレントの寸法型式項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する

void mnIoPartsAttr::SelectComboPartsMbrByKmId(
						int		i_iKmIdMbr			// 寸法型式項目番号
				)
{
	System::GetpMainFrame()->SelectCombo2( i_iKmIdMbr);
	m_iComboKmIdMbr = i_iKmIdMbr;

	// 部品配置入力データへ設定
	int	 iMbrId;
	iMbrId = m_iComboMbrId[i_iKmIdMbr];					// 寸法形式ID
	mtPlcInp::SetIdMbr( iMbrId); 
	MhMbr *pMbr = BuzaiCode::MhGetpMbr( iMbrId);				// 寸法形式仕様
	mtPlcInp::SetpMbr( pMbr);
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法型式で選択し
//	カレントの寸法型式項目番号を設定する
//							＝-1: 該当なし
//							≧ 0: 寸法型式ID

int mnIoPartsAttr::SelectComboMbrCdByMbrCd( MCHAR* sCdMbr)
{
	int		iMbrId = -1;
	int		iKmIdMbr;

	iKmIdMbr = z_mnIA.GetComboMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);	// "が寸法型式テーブルに未設定です．"
		MQUIT;
	}
	z_mnIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = m_iComboMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法形式から寸法型式コンボボックスの寸法型式項目番号を取得する
//							＝-1: 該当なし
//							≧ 0: 部品ID

int mnIoPartsAttr::GetComboMbrKmId( MCHAR* sCdMbr)
{
	int		ist;
	int		ic1;
	int		iMbrId;
	MhMbr	*pMbr;
	
	for ( ic1=0; ic1<m_nComboMbrId; ic1++) {
		iMbrId = m_iComboMbrId[ic1];
		pMbr = BuzaiCode::MhGetpMbr( iMbrId);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < m_nComboMbrId)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法形式から寸法型式IDを取得する
//							＝-1: 該当なし
//							≧ 0: 寸法型式ID

static int GetComboMbrCdId( MCHAR* sCdMbr)
{
	int		ist;
	int		ic1;
	MhMbr	*pMbr;
	int		nMbr;

	nMbr = BuzaiCode::MhGetNoOfMbr();
	for ( ic1=0; ic1<nMbr; ic1++) {
		pMbr = BuzaiCode::MhGetpMbr( ic1);
		if ( Mstrcmp( pMbr->GetMbrCode(), sCdMbr) == 0)
			break;
	}
	if ( ic1 < nMbr)
		ist = ic1;
	else
		ist = -1;
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	カレントの寸法型式IDを取得する
//							＝-1: 未選択
//							≧ 0: 寸法型式ID

int mnIoPartsAttr::GetComboMbrCdId()
{
	int		iMbrId;

	if ( m_iComboKmIdMbr >= 0 && m_iComboKmIdMbr < m_nComboMbrId) {
		iMbrId = m_iComboMbrId[m_iComboKmIdMbr];
	} else {
		iMbrId = -1;
	}
	return iMbrId;
}

} // namespace MC