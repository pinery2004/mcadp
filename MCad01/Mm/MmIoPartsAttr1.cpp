//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmIoPartsAttr1.cpp
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
#include "MhInpPlcParts.h"
#include "MhLib.h"
#include "MmPrompt.h"
#include "MmWnd.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	部材属性入力用コンボボックスの設定

void mmIoPartsAttr::InitComboParts()
{
	//	部品名コンポボックスの項目を設定する
	InitComboPartsNm();

	//	寸法型式選択用コンポボックスの項目を設定する
	InitComboPartsMbr();

//S	//	パネル番号選択用コンポボックスの項目を設定する
//	InitComboPanelNo();

	//	部材属性入力用コンポボックスの項目を設定する
	InitComboAttrXqt();
}

///////////////////////////////////////////////////////////////////////////////
//	部品選択用コンポボックスにカレントの組と分類の部材名一覧を設定し
//	対応する部材ＩＤテーブルを作成する
//
//	カレントの構成(組)コード( 屋根、小屋、天井、耐力壁、壁、床、基礎) と
//	分類コード("部材", "金物", "パネル", "屋根", "壁", "線分", "区画", "開口", "注記", "その他") とが
//	一致する部材のみ設定する

void mmIoPartsAttr::InitComboPartsNm()
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

	if ( !GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = GetCmbBzaiNm();
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
		m_iComboIdPartsSpec[ip] = ic1;							// 部材ＩＤをテーブルに設定
		pPTNmParts1 = pPartsSpec->GetPTNmParts1();				// 部材名を項目に追加
		ist = pCmbBox->InsertString( -1, pPTNmParts1);
		ip++;
	}
	m_nComboIdPartsSpec = ip;
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	m_iComboKmIdPartsNm = -1;
																				//S	z_mmIA.SetKCdBrB( false, false, false);						//	部材、金物、パネル、その他のラジオボタンを未選択に設定
}

///////////////////////////////////////////////////////////////////////////////
//	部品名項目番号で部品名コンポボックスを選択する
//	カレント部品名項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する
//	部品仕様の配置コードで配置コードコンポボックスをを選択する

void mmIoPartsAttr::SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// 部品名項目番号
				)
{
	int iIdPartsSpec;
	if ( !GetDispFlg())	goto EXIT;	

	CComboBox* pCmbBox = GetCmbBzaiNm();
	pCmbBox->SetCurSel( i_iKmIdPartsNm);
	m_iComboKmIdPartsNm = i_iKmIdPartsNm;						// カレント部品名項目番号

	// 部品配置入力データへ設定
	iIdPartsSpec = m_iComboIdPartsSpec[m_iComboKmIdPartsNm];	// 部品仕様Id
	mhPartsSpec* pPartsSpec;
	mtPlcInp::SetIdPartsSpec( iIdPartsSpec);
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);		// 部品仕様
	mtPlcInp::SetpPartsSpec( pPartsSpec);
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

int mmIoPartsAttr::SelectComboPartsNmByPartsNm(
						MCHAR* i_sNmParts1		// 部品名
				)
{
	int 	iIdPartsSpec = -1;
	int		iKmIdPartsNm;

	iKmIdPartsNm = GetComboPartsNmKmIdFromPartsNm( i_sNmParts1);
	if ( iKmIdPartsNm < 0) {
		Msg::ErrorMsg( i_sNmParts1, MC_ERR_NOTSET_PARTS_TABLE);	// "が部材テーブルに未設定です．"
		MQUIT;
	}
	z_mmIA.SelectComboPartsNmByKmId( iKmIdPartsNm);

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

int mmIoPartsAttr::GetComboPartsNmKmIdFromPartsNm( MCHAR* i_sNmParts1)
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
//	寸法型式選択用コンポボックスに寸法型式の項目(一覧)を設定し
//	対応する寸法型式ＩＤテーブルを作成する
//
//	カレントの部材の寸法型式使用部位コードを持つ寸法型式のみ設定

void mmIoPartsAttr::InitComboPartsMbr()
{
	MhMbr	*pMbr;
	int		ic1;
	int		ic;
	int		ip;
	MCHAR	cMTp1;
	MCHAR	cMTp2;
	int		iIdPartsSpec;
	int		nMbr;

	ip = 0;
	if ( !GetDispFlg())	goto EXIT;

	CComboBox* pCmbBox = GetCmbBzaiMbr();
	pCmbBox->ResetContent();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	if ( iIdPartsSpec >= 0) {
		cMTp1 = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec)->GetPTTpMbr()[0];

		nMbr = BuzaiCode::MhGetNoOfMbr();
		for ( ic1=0; ic1<nMbr; ic1++) {
			pMbr = BuzaiCode::MhGetpMbr( ic1);

			for ( ic=0; cMTp2=pMbr->GetMbrType()[ic]; ic++) {	// 一致する寸法型式使用部位コードがあるかnullまで調べる
				if ( cMTp1 == cMTp2) break;
			}
			if ( cMTp2 == 0) continue;							// 一致しない場合次の寸法型式に移る

			ASSERT( ip < MX_CMB_CDMEMBER - 1);					// 寸法型式選択コンボボックス項目　オーバフロー　<ERROR>
			m_iComboPartsMbrId[ip] = ic1;
			pCmbBox->InsertString( -1, pMbr->GetMbrCode());
			ip++;
		}
	}
	if ( ip == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	}
EXIT:
	m_nComboPartsMbrId = ip;
	m_iComboKmIdMbr = -1;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法形式項目番号で選択し
//	カレントの寸法型式項目番号を設定する
//	部品配置入力データへ部品仕様Idと部品仕様を設定する

void mmIoPartsAttr::SelectComboPartsMbrByKmId(
						int		i_iKmIdMbr			// 寸法型式項目番号
				)
{
	if ( !GetDispFlg())	goto EXIT;

	CComboBox* pCmbBox = GetCmbBzaiMbr();
	pCmbBox->SetCurSel(	i_iKmIdMbr);
	m_iComboKmIdMbr = i_iKmIdMbr;

	// 部品配置入力データへ設定
	int iMbrId;
	MhMbr* pMbr;
	iMbrId = m_iComboPartsMbrId[i_iKmIdMbr];					// 寸法形式ID
	mtPlcInp::SetIdMbr( iMbrId); 
	pMbr = BuzaiCode::MhGetpMbr( iMbrId);						// 寸法形式仕様
	mtPlcInp::SetpMbr( pMbr);
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	寸法型式コンボボックスを寸法型式で選択し
//	カレントの寸法型式項目番号を設定する
//							＝-1: 該当なし
//							≧ 0: 寸法型式ID

int mmIoPartsAttr::SelectComboPartsMbrByMbrCd( MCHAR* sCdMbr)
{
	int			iMbrId = -1;
	int			iKmIdMbr;

	iKmIdMbr = z_mnIA.GetComboPartsMbrKmId( sCdMbr);
	if ( iKmIdMbr < 0) {
		Msg::ErrorMsg( sCdMbr, MC_ERR_NOTSET_MEMBER_TABLE);		// "が寸法型式テーブルに未設定です．"
		MQUIT;
	}
	z_mmIA.SelectComboPartsMbrByKmId( iKmIdMbr);

	iMbrId = m_iComboPartsMbrId[iKmIdMbr];
exit:
	return iMbrId;
}

} // namespace MC