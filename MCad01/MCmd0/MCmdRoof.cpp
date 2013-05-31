//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"

#define DLL_EXPORT_MC_INPUT_DO
#include "MrAPI.h"
//#include "MhPlcPartsLib.h"

namespace MC
{

void MCmdRoofAdd();
void MCmdRoofDelete();

static void	MmPackAreaI(
						MgPolyg2D*	pPg1,			// (I O) 地廻り区画
						MgGInt*		pGifInp			// (I O) 地廻り線種類(仮想キー(nflag)  MK_SHIFT(004): シフトキー)
				);

void MCmdRoof()
{
	MINT iMode;
	iMode = z_mnIA.GetMode();
	if ( iMode == MP_MD_CREATE)
		MCmdRoofAdd();
	else if ( iMode == MP_MD_DELETE)
		MCmdRoofDelete();
}

void MCmdRoofAdd()
{
	MINT		ist1;
	MgPoint2D	pt1, pt2, pth;
	MgLine2D		Ln1;
	MgPolyg2D	pgJim(20);
	MgGInt		GifInp(20);

	Msg::ClearErrorMsg();

	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_YANE, MP_BR_OTHER, Mstr( "屋根"), Mstr( "204"));

	WindowCtrl::ReDrawWnd();

	Msg::OperationMsg( MC_OPRT_ROOF);								// ステイタスバーの操作表示部へ"屋根入力"を表示

	mhPartsSpec* pPartsSpec	= BuzaiCode::MhGetpPartsSpec( z_mnIA.GetCurPartsNmId());
//E	z_mnIA.SelectComboInpKbnByInpKbnCdXqt( pPartsSpec->GetPTCdInpKb());
//SS	z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, pPartsSpec->GetPTCdInpKb());	// 入力点区分選択用のコンボボックスに表示する
	z_mnIA.SelectComboInpKbnByInpKbnCdEntry( pPartsSpec->GetPTCdInpKb());	// 入力点区分選択用のコンボボックスに表示する
//E	z_mnIA.SelectComboMarumeByMarumeCdXqt( pPartsSpec->GetPTCdMarume());
//SS	z_mnIA.RibbonIO( MSET_INPUT_MARUME_CD, pPartsSpec->GetPTCdMarume());	// 丸めコードを選択用のコンボボックスに表示する
	z_mnIA.SelectComboMarumeByMarumeCdEntry( pPartsSpec->GetPTCdMarume());	// 丸めコードを選択用のコンボボックスに表示する

	MFOREVER {
		pgJim.m_n = 0;
		GifInp.m_n = 0;
		ist1 = mhInput::GetAreaI( &pgJim, &GifInp);

		if ( ist1 == MTRT_SYSTEMSTOP || ist1 == MTRT_CAN)
			break;
		MmPackAreaI( &pgJim, &GifInp);
		if ( pgJim.m_n < 3)
			continue;

		HaitiCmd::MmPresetCmd();

		ist1 = mhHaitiIn::RoofPlc( pgJim, GifInp, pth);

		WindowCtrl::ReDrawWnd();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// ステイタスバーの操作表示部へ""を表示
}

/////////////////////////////////////////////////////////////////////////////
//	地廻り種類が同一の地廻り区画の線分が直進して並んでいるものを１つにまとめる

static void	MmPackAreaI(
						MgPolyg2D*	pPg1,			// (I O) 地廻り区画
						MgGInt*		pGifInp			// (I O) 地廻り線種類(仮想キー(nflag)  MK_SHIFT(004): シフトキー)
				)
{
	MINT	ist1;
	MINT	icb, icc;
	MINT	ic0, ic1, ic2;
	MgLine2D	ln1;
	bool	fmabiki = false;

	ic0 = 0;
	icb = pPg1->m_n - 1;
	ic1 = 0;
	for ( ic2=1; ic2<=pPg1->m_n; ic2++) {
		ln1 = MgLine2D( pPg1->m_p[icb], pPg1->m_p[ic1]);
		if ( ic2 == pPg1->m_n)
			icc = 0;
		else
			icc = ic2;

		if ( pGifInp->m_i[icc] == pGifInp->m_i[ic1])				// 同一地廻り線種類の場合は
			MGeo::CheckPointOnLine2D( pPg1->m_p[icc], ln1, &ist1);		//	直進か否かを調べる
		else													// 異なる地廻り線種類の場合は
			ist1 = 0;											//	非直進とする

		if (MF_CHECK_OR( ist1, MC_ON_SLINE)) {					// 直進　間引き
//			if ( icc != 0) {
				pPg1->m_p[ic0] = pPg1->m_p[icc];
				pGifInp->m_i[ic0] = pGifInp->m_i[icc];
//			}
			fmabiki = true;
		} else {												// 非直進
			if (fmabiki) {
				pPg1->m_p[ic0] = pPg1->m_p[ic1];
				pGifInp->m_i[ic0] = pGifInp->m_i[ic1];
			}
			icb = ic1;
			ic0++;
		}
		ic1 = ic2;
	}
	pPg1->m_n = ic0;
}		

} // namespace MC
