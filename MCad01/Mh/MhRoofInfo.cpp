//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhRoofInfo.cpp
//
//		屋根読み書き
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MdLib.h"

#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MhLib.h"
#include "MhRoof.h"

#include "MfFile.h"
#include "MmTenkai.h"

#include "MhDefine.h"

PZBUF*	____pzbuf;

																				//void MdPtsDbInit();
																				//void MdRedoPtsDbInit();
																				//void MdRoofDbInit();

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	屋根配置レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhRoofInfo::Save(							//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_ST, &iDumy);
	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_KAI, &m_iKai);

	// 地廻り線
	for ( iC1=0; iC1 < GetpGJim1()->m_n; iC1++) {
		GetpGJim1()->m_st[iC1].Save( i_phMdl);
	}

	// 屋根構成線
	for( iC1=0; iC1<GetpGKs1()->m_n; iC1++) {
		GetpGKs1()->m_st[iC1].Save( i_phMdl);
	}

	// 屋根面
	for ( iC1=0; iC1 < GetpGRfm()->m_n; iC1++) {
		GetpGRfm()->m_st[iC1].Save( i_phMdl);
	}

	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_EOR, &iDumy);

    return 0;
}

////////////////////////////////////////////////////////////////////////////
//	屋根配置レコード読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhRoofInfo::Load(							//
				MhMdlIO*		i_phMdl			// 読み込みファイル　ハンドル
				)
{
	MINT		ist = 0;
	MhMdlIO		hMdl;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;
	mhPlcInfo*	pPlcEn = 0;
																				//	MhRoofInfo*		pRoofEn;
	MhJim*		pJim1;
	MhRfm*		pRfm;
	MgPoint3*	pPt;
	MINT*		piCd;

	bool		fPlcSzChk = true;
	bool		fRoofSzChk = true;

	bool		bEor = false;

	MgVect3		vLnPlc;

//	屋根レコード
	this->InitAllAtr( 0);										// 子のサイズとレコード数をクリア

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
#if (MDR_TYPE2)
			case MDR_ATRCD_ROOFEN_KAI:							// 階
				ASSERT( iSize == SZMINT());
				m_iKai = *( MINT*)pEnt;
				break;
#endif
			case MDR_ATRCD_ROOFEN_EOR:							// 屋根 eor
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				CreateRfmZukei();
				bEor = true;
				break;
#if (MDR_TYPE2)
			case MDR_ATRCD_JIM_ST:								// 地廻り
				if( iSize == SZMINT()) {
					MBFREE( pEnt);
					pJim1 = new MhJim[1];
					pJim1->Load( i_phMdl);
					*(this->GetpGJim1()) += (*pJim1);			// 
				} else if( iSize == sizeof( MhJim)) {
					pJim1 = (MhJim*)pEnt;
					*(this->GetpGJim1()) += (*pJim1);			// 仮対応　MDR_ATRCD_JIM_EORなしの為	ZZZZZZZZZZZZZ 091018
					MBFREE( pJim1);								// 仮対応
				} else {
					ASSERT( 0);
				}
				break;
#endif
			case MDR_ATRCD_JIM:									// 屋根面
				ASSERT( iSize == sizeof(MhJim));
				pJim1 = (MhJim*)pEnt;

				*(this->GetpGJim1()) += (*pJim1);				// 仮対応　MDR_ATRCD_JIM_EORなしの為	ZZZZZZZZZZZZZ 091018
				MBFREE( pJim1);									// 仮対応
				break;
			case MDR_ATRCD_JIM_EOR:								// 地廻り
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				*(this->GetpGJim1()) += (*pJim1);
				MBFREE( pJim1);	
				break;
			case MDR_OLD_ATRCD_RFM:									// 屋根面
				ASSERT( iSize == sizeof(MhRfm));
				pRfm = (MhRfm*)pEnt;
				break;
			case MDR_ATRCD_RFM_EOR:								// 屋根面 eor
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				*(this->GetpGRfm()) += (*pRfm);
				pRfm->Free();
				MBFREE( pRfm);
				break;
			case MDR_OLD_ATRCD_RFM_PG_PT:							// 屋根面構成点 
				ASSERT( iSize == sizeof(MgPoint3) * pRfm->m_Pg.m_n);
				pPt = (MgPoint3*)pEnt;
				pRfm->m_Pg.m_P = pPt;
				pRfm->m_Pg.m_P = (MgPoint3*)pEnt;
				break;
			case MDR_OLD_ATRCD_RFM_ICD_I:							// 屋根面コード
				ASSERT( iSize == SZMINT() * pRfm->m_cdPg.m_n);
				piCd = (MINT*)pEnt;
				pRfm->m_cdPg.m_i = piCd;
				pRfm->m_cdPg.m_i = (MINT*)pEnt;
				break;
			default:
				MBFREE( pEnt);
		}
	} while( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	地廻り線レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhJim::Save(								//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
																				//	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ST, &iDumy);
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_P, (MFLOAT*)&m_p, SZMgPoint2());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ICD, &m_icd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_IFINP, &m_ifInp, SZMINT());
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_RKB, &m_rKb, SZMREAL());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_IRFM, &m_iRfm, SZMINT());
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_LNR, (MFLOAT*)&m_LnR, SZMgLine3());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ILNRCD, &m_icdLnR, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	地廻り線レコード読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhJim::Load(								//
				MhMdlIO*		i_phMdl			// 読み込みファイル　ハンドル
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;

	bool		bEor = false;

//	地廻り線レコード
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_JIM_EOR:								// 地廻り線 eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_JIM_P:								// 地廻り線右端の頂点
				ASSERT( iSize == SZMgPoint2());
				memcpy( &m_p, pEnt, SZMgPoint2());
				break;
			case MDR_ATRCD_JIM_ICD:								// 地廻り線コード
				ASSERT( iSize == SZMINT());
				m_icd = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_IFINP:							// 入力フラグ
				ASSERT( iSize == SZMINT());
				m_ifInp = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_RKB:								// 勾配
				ASSERT( iSize == SZMREAL());
				m_rKb = *(MREAL*)pEnt;
				break;
			case MDR_ATRCD_JIM_IRFM:							// 屋根面配列番号
				ASSERT( iSize == SZMINT());
				m_iRfm = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_LNR:								// 右側屋根構成線（延長） 
				ASSERT( iSize == SZMgLine3());
				memcpy( &m_LnR, pEnt, SZMgLine3());
				break;
			case MDR_ATRCD_JIM_ILNRCD:							// 右側屋根構成線コード
				ASSERT( iSize == SZMINT());
				m_icdLnR = *(MINT*)pEnt;
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif
////////////////////////////////////////////////////////////////////////////
//	構成線分レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MgKs1::Save(								//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
																				//	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_KSI_ST, &iDumy);
	i_phMdl->WriteItemR( MDW_ATRCD_KSI_LN, (MREAL*)&m_Ln, SZMgLine3());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_TPLN, (MINT*)&m_itpLn, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_CD, (MINT*)&m_iCd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_FPROC, &m_ifProc, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_RFM, m_iRfm, SZMREAL( 2));
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	構成線分レコード読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MgKs1::Load(								//
				MhMdlIO*		i_phMdl			// 読み込みファイル　ハンドル
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;

	bool		bEor = false;

//	構成線分レコード
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_JIM_EOR:								// 構成線分 eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_KSI_LN:								// 構成線分
				ASSERT( iSize == SZMgLine3());
				memcpy( &m_Ln, pEnt, SZMgLine3());
				break;
			case MDR_ATRCD_KSI_TPLN:							// 線分タイプ(0: 半直線　1:線分)
				ASSERT( iSize == SZMINT());
				m_itpLn = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_CD:								// 構成コード
				ASSERT( iSize == SZMINT());
				m_iCd = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_FPROC:							// 計算処理用フラグ
				ASSERT( iSize == SZMINT());
				m_ifProc = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_RFM:								// 屋根面配列番号 (左、右)
				ASSERT( iSize == 2 * SZMREAL());
				memcpy( m_iRfm, pEnt, 2 * SZMREAL());
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif

////////////////////////////////////////////////////////////////////////////
//	屋根面レコード書き込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhRfm::Save(								//
				MhMdlIO*		i_phMdl			// 書き込みファイル　ハンドル
				)
{
																				//	MINT		iC1;
	MINT	iDumy = 0;
	MINT	iN;

	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ST, &iDumy);
	iN = m_Pg.m_n;
	i_phMdl->WriteItemR( MDW_ATRCD_RFM_PG, (MREAL*)&m_Pg.m_P, iN * SZMgPoint3());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ICD, (MINT*)&m_cdPg.m_tp, iN * SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ICD, (MINT*)&m_icd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	屋根面レコード読み込み
//	[返値] ステイタス     0 : 正常  -1 : 異常

MINT MhRfm::Load(								//
				MhMdlIO*		i_phMdl			// 読み込みファイル　ハンドル
				)
{
	MINT	ist = 0;
	MINT	iType;
	MINT	iSize;
	void*	pEnt;
	MINT	iN = 0;

	bool	bEor = false;

//	屋根面レコード
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_RFM_EOR:								// 地廻り線 eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_RFM_PLN:								// 屋根面係数
				ASSERT( iSize == SZMgPlane3());
				memcpy( &m_Pln, pEnt, SZMgPlane3());
				break;
			case MDR_ATRCD_RFM_PG:								// 屋根面形状（屋根構成線）
				iN = iSize / SZMgPoint3();
				m_Pg.Resize( iN);
				memcpy( &m_Pg[0], pEnt, iSize);
				break;
			case MDR_ATRCD_RFM_ICDPG:							// 屋根構成線コード
				ASSERT( iSize == iN * SZMINT());
				m_cdPg.Resize( iN);
				memcpy( &m_cdPg[0], pEnt, iSize);
				break;
			case MDR_ATRCD_RFM_ICD:								// 構成コード
				ASSERT( iSize == SZMINT());
				m_icd = *(MINT*)pEnt;
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif
} // namespace MC