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
#include "MrAPI.h"
/*
#include	"MCad.h"
#include	"MtGet.h"
#include	"Mt.h"
#include	"MmWnd.h"
#include	"MmLib.h"
#include	"MmOpt.h"
#include	"MmHist.h"
#include	"MdLib.h"
#include	"MmPrompt.h"
*/
#define		MMAX_NPANEL				500
#include "MmValid.h"
//#include "MhPlcPartsLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	パネル番号修正
void MCmdMdPanelNo()
{
	MINT		irt;
	MINT		ic1, ic2;
	MgPoint2D	pt1;
	bool		bFirst = TRUE;

	MINT		iBuzaiCd;
	MgPolyg2D	pgHitBzi;
	
	mhPlcParts* pPtInfo[MMAX_NPANEL];							// パネル配置情報
	mhPlcParts* pPtInfo1;
	mhPlcParts* pPlcEn;
	MPOSITION	posH;
//	MsBitSet*	pOptv;
//	MsBitSet*	pHstv;
	MINT		ic1Pt, ic2Pt;

	MINT		iPtNo[MMAX_NPANEL];								// パネル番号
	MINT		iSetPtNo;
	MINT		iGetPtNo;
	MINT		iPt;
	MINT		iPtNoMin;

	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();				// カレントウィンドウを取得する
	MINT		iKaiC   = z_mnIA.GetInpKai();						// 階  	(1,2,3)
	MINT		iGpC = z_mnIA.GetKCdGp();							// 構成

	Window::CurWndFocus();

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_MOD_BUZAI);							// ステイタスバーの操作表示部へ"部材修正"を表示

	MFOREVER {
		Window::SetDispSelParts( NULL);

		Msg::GuidanceMsg( MC_GUID_MOD_PANELNO);						// パネル番号を設定し、パネル番号を修正するパネルを指示して下さい
		irt = MtAskForPoint( &pt1);

		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		iSetPtNo = z_mnIA.GetComboPanelNo();
		if ( iSetPtNo < 1)
			iSetPtNo = 1;

		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		iBuzaiCd = NULL;
		if ( ( pPtInfo1 = mhHaitiIn::SrchBuzai( pWndInfo, pt1, iBuzaiCd, &pgHitBzi)) &&
			pPtInfo1->IsPanel()) {

			iPt = 0;
			for ( pPlcEn = HaitiDb::MdGetHeadParts( &posH); pPlcEn!=0;
				  pPlcEn = HaitiDb::MdGetNextParts( &posH)) {
				if ( pPlcEn->GetPIKai() != iKaiC)
					continue;										// 異なる階の部材は対象外とする
				if ( pPlcEn->GetPIPartsSpec()->GetPTCdGp() != iGpC)
					continue;										// 異なる構成の部材は対象外とする
				if (!pPlcEn->IsPanel())
					continue;										// パネル以外は対象外とする

				if ( !MmCheckValidParts( pPlcEn))					// オプションと履歴のチェック
					continue;

				if ( pPlcEn == pPtInfo1)
					ic1Pt = iPt;
				pPtInfo[iPt] = pPlcEn;
				iPtNo[iPt++] = pPlcEn->GetPIPanelNo();
			}
			
			for ( ic1=1; ic1<=iPt; ic1++) {
				iPtNoMin = INT_MAX;
				for ( ic2=0; ic2<iPt; ic2++) {
					if ( iPtNo[ic2] < iPtNoMin) {
						iPtNoMin = iPtNo[ic2];
						ic2Pt = ic2;
					}
				}
				iPtNo[ic2Pt] = ic1 + 10000;
			}
			for ( ic1=0; ic1<iPt; ic1++)
				iPtNo[ic1] -= 10000;
			
			iGetPtNo = iPtNo[ic1Pt];

			if ( iSetPtNo > iPt)
				iSetPtNo = iPt;
			if ( iGetPtNo != iSetPtNo) {
				for ( ic1=0; ic1<iPt; ic1++) {
					if ( iPtNo[ic1] < iGetPtNo && iPtNo[ic1] < iSetPtNo)
						continue;
					if ( iPtNo[ic1] > iGetPtNo && iPtNo[ic1] > iSetPtNo)
						continue;
					if ( iGetPtNo < iSetPtNo) {
						if ( iPtNo[ic1] == iGetPtNo)
							iPtNo[ic1] = iSetPtNo;
						else
							iPtNo[ic1]--;
					} else {
						if ( iPtNo[ic1] == iGetPtNo)
							iPtNo[ic1] = iSetPtNo;
						else
							iPtNo[ic1]++;
					}
					pPtInfo[ic1]->SetPIPanelNo( iPtNo[ic1]);
				}
			}
			if ( iSetPtNo < iPt)
				iSetPtNo++;
																								//E			z_mnIA.SetComboPanelNoXqt( iSetPtNo);
																								//S			z_mnIA.RibbonIO( MSET_COMBO_PANELNO, iSetPtNo);			// パネル番号選択用のコンボボックスに表示する
			z_mnIA.SetComboPanelNoEntry( iSetPtNo);					// パネル番号選択用のコンボボックスに表示する


			WindowCtrl::ReDrawWnd();
			Msg::ClearErrorMsg();
		}
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// ステイタスバーの操作表示部へ""を表示
}

} // namespace MC
