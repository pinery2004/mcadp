//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: mhPlcInfo.cpp
//
//		部材配置読み書き
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MhLib.h"
#include "MhPlcInfo.h"

#include "MfFile.h"
#include "MmTenkai.h"

#include "MhDefine.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	バイトデータの読み込み
//	[返値] バイトデータ
inline	byte	GetByte(
					int		i_iTp,				// タイプ　1:byteデータ, 4:intデータ(旧)
					int*	i_pDt				// 読み込みデータ
				)
{
	byte	ibDt;
	if( i_iTp == 1) {
		ibDt = *(byte*)i_pDt;
	} else if( i_iTp == 4) {
		ibDt = *(MINT*)i_pDt;
	} else {
		ASSERT( 0);
		ibDt = 0;
	}
	return ibDt;
}

////////////////////////////////////////////////////////////////////////////
//	配置部材の読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常
inline	short	GetShort(
					int		i_iTp,				// タイプ　2:shortデータ, 4:intデータ(旧)
					int*	i_pDt				// 読み込みデータ
				)
{
	short	isDt;
	if( i_iTp == 2) {
		isDt = *(short*)i_pDt;
	} else if( i_iTp == 4) {
		isDt = *(MINT*)i_pDt;
	} else {
		ASSERT( 0);
		isDt = 0;
	}
	return isDt;
}

////////////////////////////////////////////////////////////////////////////
//	部材配置レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT mhPlcInfo::Save(							//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ST, &iDumy);							// 配置レコード
		
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_IKAI, &m_ibKai);					// 階
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ICDHGT, &m_ibCdHgt);				// 取り付け高さコード
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_DISPLAYFLAG, &m_ibDisplayFlg);		// 表示フラグ(図形,注記1,注記2)
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_IPANELNO, &m_isPanelNo);			// パネル番号
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_IKAIKONO, &m_isKaikoNo);			// 開口番号
	MINT iCdBuzaiW = GetPTCdBuzaiW();											// 部材コード
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_IPARTSTPCD, &iCdBuzaiW);
																				// p[0]: 始点 | 配置点
																				// p[1]: 終点 | 配置方向点
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_LNHAITI, (MREAL*)&m_lnPlc, sizeof(MgLine3));
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_PTUPHAITI, (MREAL*)&m_vUpPlc, sizeof(MgPoint3));
																				// 配置上方向点
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RSINZURE, &m_rSinZure);				// 材軸芯ずれ量　	>0:右側、<0:左側
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RHAITIZURE, &m_rPlcZure);			// 配置点ずれ量		>0:前、　<0:後
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RNAGASAHOSEI, m_rLngHosei, 2*sizeof(MREAL));
																				// 長さ補正値（始点側、終点側）
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RTAKASA, m_rHgt, 2*sizeof(MREAL));	// 高さ（取り付け高さ、高さ）
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_PTCMNT1, (MREAL*)&m_ptCmnt1, sizeof(MgPoint2));
																				// 注記表示位置
	MCHAR	cMemBerCode[16];
	Mstrcpy_s( cMemBerCode, GetMbCdMbrW());										// 寸法型式 (書き込み用　通常m_cCodeと同じ VerUp時に変更した内容が入る)
	i_phMdl->WriteItemCH( MDW_ATRCD_HAITIEN_MEMBER, cMemBerCode, sizeof(cMemBerCode));
	if ( GetPIAuxAttr() != 0) {
		if ( IsTategu())														// 建具情報
			GetPIAuxTategu()->Save( i_phMdl);
		else if ( IsTenkai())													// 住棟展開
			GetPIAuxTenkai()->Save( i_phMdl);
	}
	if ( m_pVer != 0)															// バージョン
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_VERSION, (MUINT*)m_pVer, sizeof(MhHistV));
	if ( m_pOpt1 != 0)															// ＯＰＴ群
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_OPTION1, (MUINT*)m_pOpt1, sizeof(MsBitSet));
	if ( m_pOpt2 != 0)															// ＯＰＴ群
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_OPTION2, (MUINT*)m_pOpt2, sizeof(MsBitSet));

	MhZukei*	pZukei;							// 図形
	for( pZukei=m_pZukei; pZukei!=0; pZukei=pZukei->m_pNext) {
		pZukei->Save( i_phMdl);
	}
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_EOR, &iDumy);						// 配置レコード終了

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	配置部材の読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT mhPlcInfo::Load(							//
						MhMdlIO*	i_phMdl		// 読み込みファイル　ハンドル
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	MINT		nVer;
	
	void*		pEnt;
//	mhPlcInfo*	pPlcEn = 0;
	MhTateguInfo*	pAuxTategu;
	JTTenkaiPr*	pAuxTenkai;
	MhHistV*	pVer;
	MsBitSet*	pOpt;

	MhZukei**	ppZukei;
	MINT		iNZukei;
	MINT		iSzZukei;
	MCHAR*		pcMbr;
	MINT		iMbr;
	MINT		iCdBuzai;

	bool		fPlcSzChk = true;
	bool		fRoofSzChk = true;

	MgVect3		vLnPlc;
	
	bool		bEor = false;

	// 配置レコード開始

	memset( this, 0, sizeof( mhPlcInfo));
	ppZukei = &m_pZukei;

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_HAITIEN_EOR:											// 配置 レコード終了r
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);													// TYPE_HAITIEN_EORレコード用エリアの削除
				
				m_pTpPts	= BuzaiCode::MhGetpTpPts( m_isIdTpPts);
				m_pMbr		= BuzaiCode::MhGetpMbr( m_isMbrId);
				
				bEor = true;
				break;
			case MDR_ATRCD_HAITIEN_IKAI:										// 階
				m_ibKai = GetByte( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_ICDHGT:										// 配置点
				m_ibCdHgt = GetByte( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IPANELNO:									// 配置点
				m_isPanelNo = GetShort( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IKAIKONO:									// 開口番号
				m_isKaikoNo = GetShort( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IPARTSTPCD:									// 部品配置タイプコード 
				ASSERT( iSize == SZMINT());
				iCdBuzai = *(MINT*)pEnt;										// (部材コード)
				m_isIdTpPts = BuzaiCode::MhGetPIIdTpPts( iCdBuzai);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_MEMBER:										// メンバー
				ASSERT( iSize == sizeof( MhTateguInfo));
				pcMbr = (MCHAR*)pEnt;
				iMbr = BuzaiCode::MhGetIdMbr( pcMbr);
				if ( iMbr < 0) {
					iMbr = 0;
				}
				m_isMbrId	= iMbr;
				m_pMbr		= BuzaiCode::MhGetpMbr( m_isMbrId);
				MBFREE( pcMbr);
				break;
			case MDR_ATRCD_HAITIEN_LNHAITI:										// 配置点、配置方向点
				ASSERT( iSize == sizeof(MgLine3));
				m_lnPlc = *(MgLine3*)pEnt;
				vLnPlc = m_lnPlc.p[1] - m_lnPlc.p[0];
				vLnPlc.SetUnitize();
				m_vUpPlc = vLnPlc ^ MgVect3( 0., 0., 1.);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_PTUPHAITI:									// 上方向
				ASSERT( iSize == sizeof(MgPoint3));
				m_vUpPlc = *(MgVect3*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RSINZURE:									// 材軸芯ずれ量
				ASSERT( iSize == sizeof(MREAL));
				m_rSinZure = *(MREAL*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RHAITIZURE:									// 配置点ずれ量 
				ASSERT( iSize == sizeof(MREAL));
				m_rPlcZure = *(MREAL*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RNAGASAHOSEI:								// 長さ補正値1、長さ補正値2
				ASSERT( iSize == sizeof(MREAL) * 2);
				m_rLngHosei[0] = *(MREAL*)pEnt;
				m_rLngHosei[1] = *(((MREAL*)pEnt)+1);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RTAKASA:										// 高さ
				ASSERT( iSize == sizeof(MREAL) * 2);
				m_rHgt[0] = *(MREAL*)pEnt;
				m_rHgt[1] = *(((MREAL*)pEnt)+1);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_TATEGU:										// 建具属性
				ASSERT( iSize == sizeof( MhTateguInfo));
				pAuxTategu = (MhTateguInfo*)pEnt;
				m_pAuxTategu = pAuxTategu;
				break;
			case MDR_ATRCD_HAITIEN_TENKAI:										// 住棟展開
				ASSERT( iSize == sizeof(JTTenkaiPr));
				pAuxTenkai = (JTTenkaiPr*)pEnt;
				m_pAuxTenkai = pAuxTenkai;
				JTTenkai::SetJTTPara( pAuxTenkai);
				break;
			case MDR_ATRCD_HAITIEN_VERSION:										// バージョン
				ASSERT( iSize == sizeof(MhHistV));
				pVer = (MhHistV*)pEnt;
				m_pVer = pVer;
				break;
			case MDR_ATRCD_HAITIEN_OPTION1:										// ＯＰＴ群
				ASSERT( iSize == sizeof(MsBitSet));
				pOpt = (MsBitSet*)pEnt;
				m_pOpt1 = pOpt;
				break;
			case MDR_ATRCD_HAITIEN_OPTION2:										// ＯＰＴ群
				ASSERT( iSize == sizeof(MsBitSet));
				pOpt = (MsBitSet*)pEnt;
				m_pOpt2 = pOpt;
				break;
			case MDR_ATRCD_OPTION_KANRI:										// ＯＰＴ群管理
				MhOptV::nbmGOpt = iSize / sizeof( MhOpt);
				memcpy( MhOptV::bmGOpt, pEnt, iSize);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI0:										// 履歴管理
				nVer = 0;
				memcpy( &MhHistV::nVer, pEnt, iSize);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI1:										// 履歴管理　バージョン
				MhHistV::sVerC[nVer] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI2:										// 履歴管理　直前バージョン
				MhHistV::sVerB[nVer] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI3:										// 履歴管理　日付
				MhHistV::sVerD[nVer++] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_ZUKEI:
				*ppZukei = (MhZukei*)pEnt;
				iSzZukei = sizeof( MhZukei) + sizeof( MgLine3) * ( (*ppZukei)->m_isNZukei - 1);
				ASSERT( iSize == iSzZukei);
				SetPIZukei( *ppZukei);
				GetPIZukei()->m_pNext = 0;
				break;

#if (MDR_TYPE1) 
			case MDR_ATRCD_HAITIEN_ZUKEI_ST:
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);
				break;
#endif
			case MDW_ATRCD_HAITIEN_ZUKEI_N:									// 図形(線分)数
				ASSERT( iSize == sizeof( MSHORT));
				iNZukei = *( MSHORT*)pEnt;
				MBFREE( pEnt);
				iSzZukei = sizeof( MhZukei) + sizeof( MgLine3) * ( iNZukei - 1);
				*ppZukei = (MhZukei*)new char[iSzZukei];
				(*ppZukei)->m_isNZukei = iNZukei;
				MBFREE( pEnt);
				memset( *ppZukei, 0, iSzZukei);
				(*ppZukei)->Load( i_phMdl);
				ppZukei = &(*ppZukei)->m_pNext;
				break;

			default:
				MBFREE( pEnt);
		}
	} while ( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	部材配置レコード 建具情報　書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhTateguInfo::Save(							//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
	MINT	iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TATEGU_ST, &iDumy);					// 建具情報
		
	MCHAR	cKCode[MHTTSZ_CODE+1];
	Mstrcpy_s( cKCode, GetKCode());												// 開口コード
	i_phMdl->WriteItemCH( MDW_ATRCD_HAITIEN_CCODE, cKCode, sizeof(cKCode));
	MREAL rROW = GetROW();														// 開口幅
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RROW, &rROW);
	MREAL rROH = GetROH();														// 開口高さ
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RROH, &rROH);
	MREAL rHeight= GetHeight();													// 取り付け高さ(まぐさ下端高さ)
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RHEIGHT, &rHeight);
	MREAL* prMUSz =	GetMUSz();													// 左右まぐさ受長さ
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RMUSZ, prMUSz, 2*sizeof(MREAL));

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TATEGU_EOR, &iDumy);					// 建具情報終了

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	部材配置レコード 図形情報 書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhZukei::Save(
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
//	MhZukei*	pZukei;
	MINT	iDumy = 0;
	MINT	iSzZukei;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ZUKEI_ST, &iDumy);					// 図形情報開始
	MSHORT	isNZukei = m_isNZukei;
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_ZUKEI_N, &isNZukei);				// 図形(線分)数	(図形情報開始の直後に出力すること)
	MUBYTE	ibObj = m_ibObj;
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ZUKEI_OBJ, &ibObj);					// 使用目的
	MUBYTE	ibTp = m_ibTp;
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ZUKEI_TP, &ibTp);					// 図形データタイプ
	iSzZukei = m_isNZukei * sizeof( MgLine3);
	i_phMdl->WriteItems( MDW_ATRCD_HAITIEN_ZUKEI_ST, m_lnZukei, iSzZukei);

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ZUKEI_EOR, &iDumy);					// 図形情報終了

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	部材配置レコード 図形情報 読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhZukei::Load(								//
				MhMdlIO*		i_phMdl			// 読み込みファイル　ハンドル
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;
	MINT		iDumy = 0;

	bool		bEor = false;

//	図形情報

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
#if( TRACE_IO)
		static	int iCzukei = 0;
		TRACE( "%d; iType=%d\n", iCzk_IO++, iType);
#endif
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDW_ATRCD_HAITIEN_ZUKEI_EOR:									// 図形情報終了
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);
				bEor = true;
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_TP:									// タイプ
				ASSERT( iSize == sizeof( m_ibTp));
				m_ibTp = *( MUBYTE*)pEnt;
				MBFREE( pEnt);
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_OBJ:									// 使用目的
				ASSERT( iSize == sizeof( m_ibObj));
				m_ibObj = *( MUBYTE*)pEnt;
				MBFREE( pEnt);
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_BUF:									// 図形(線分)
				ASSERT( iSize == m_isNZukei * sizeof( MgLine3));
				memcpy( m_lnZukei, pEnt, iSize);
				MBFREE( pEnt);
				break;
			default:
				MBFREE( pEnt);
		}
	} while( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	部材配置レコード 住棟展開情報 書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT JTTenkaiPr::Save(							//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
	MINT			iDumy = 0;

//	i_phMdl->WriteItem( MDW_ATRCD_HAITIEN_TATEGU, &iDumy);						// 図形レコード
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TENKAI_ST, &iDumy);					// 住棟展開レコード
		

//	i_phMdl->WriteItem( MDW_ATRCD_HAITIEN_TATEGU_EOR, &iDumy);					// 図形レコード終了
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TENKAI_EOR, &iDumy);					// 住棟展開レコード終了

	return 0;
}

} // namespace MC