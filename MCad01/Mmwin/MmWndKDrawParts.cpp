//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		ドラッギング操作
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MhInpPlcParts.h"

#include "MdOpt.h"
#include "MdLib.h"

#include "MdHist.h"
#include "MmValid.h"

namespace MC
{

static	MINT			z_ign;

/////////////////////////////////////////////////////////////////////////////
//	１配置部品を表示する
void DrawPart( 
						msCod*		pCod,			// 座標系
						MINT		iGpC,			// 構成
						mhPlcParts	*pPlcEn
				);

/////////////////////////////////////////////////////////////////////////////
//	配置部品を表示する
void WindowCtrl::MmWndKDrawParts(
						msCod*		pCod,			// 座標系
						MINT		iKaiC,			// 階  	(1,2,3)
						MINT		iGpC			// 構成
				)
{
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
//	MsBitSet	*pOptv1, *pOptv2;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgLine2D		LnParts;
	MgPoint2D	ptPartsN;
	MgPoint2D	ptW[2];
	MgPoint2D	ptH;
	MgPoint2D	ptK[4];
	MgVect2D		vptH;
	MgVect2D		vOffset = MgVect2D( 0., 20.);
	
	DWORD		PartsTextColor;

	PartsTextColor = mcs::GetColor( MM_COLOR_GRID_TEXT);
	pCod->SetTextAttr( Mstr( "ＭＳ ゴシック"), 100.f, MT_CENTER, MT_CENTER,
					   PartsTextColor, MgVect2D( 1., 0.), vOffset, MT_FREESIZE);

	// パネルを表示する
	z_ign = 0;
	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// 異なる階の部材は表示しない
//		if ( pPlcEn->GetPIPartsSpec()->m_pGp->m_iCode != iGpC)
//			continue;											// 異なる構成の部材は表示しない
		if ( pPlcEn->GetPTCdGp() != iGpC)
			continue;											// 異なる構成の部材は表示しない

		if ( pPlcEn->IsPanel() || pPlcEn->IsKaiko()) {			// パネルまたは開口

			if ( !MmChkValidParts( pPlcEn))						// オプションと履歴のチェック
				continue;
			DrawPart( pCod, iGpC, pPlcEn);
		}
	}

	PartsTextColor = mcs::GetColor( MM_COLOR_GRID_TEXT);
	pCod->SetTextAttr( Mstr( "ＭＳ ゴシック"), 100.f, MT_LOWER, MT_CENTER,
					   PartsTextColor, MgVect2D( 1., 0.), vOffset, MT_FREESIZE);

	// 部材形状を表示する
	MINT iDB = 0;												// Debug Trace用
	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		iDB++;

		DWORD PartsLineColor;
		MINT iMdBziFig = 0;

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// 異なる階の部材は表示しない

//D		MUINT	*iOptv = pPlcEn->GetPIOpt1()->GetSOB();
//D		TRACE1( "MmWndKDrawParts(%d)		", iDB);
//D		if ( iOptv == 0)
//D			TRACE0( "pOptv_ON NULL		");
//D		else
//D			TRACE3( "pOptv_ON %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//D		iOptv = pPlcEn->GetPIOpt2()->GetSOB();
//D		if ( iOptv == 0)
//D			TRACE0( "pOptv_OFF NULL\n");
//D		else
//D			TRACE3( "pOptv_OFF %x, %x, %x\n", iOptv[0], iOptv[1], iOptv[2]);

		if ( pPlcEn->GetPTCdGp() != iGpC) {						// 基礎は
			if ( pPlcEn->GetPTCdBr() == MP_BR_KISO) {
				if ( iKaiC == 1 && iGpC == MP_GP_YUKA) {		// １階床組表示の場合は、壁芯線分で表示する
					iMdBziFig = 1;
					PartsLineColor = mcs::GetColor( MM_COLOR_KISOSIN);
				} else {
					continue;									// 基礎組と床組以外は表示しない
				}
			} else if ( pPlcEn->GetPTCdBr() == MP_BR_KABE) {	// 壁は
				if ( iGpC == MP_GP_KABE) {						// 壁枠組表示の場合は表示する
				} else {
					continue;
				}
			} else {											// 他は
				continue;										// 異なる構成の部材は表示しない
			}
		}

		if ( !MmChkValidParts( pPlcEn))							// オプションと履歴のチェック
			continue;

		if ( pPlcEn->GetPTCdBr() != MP_BR_PANEL) {				// パネル以外の部材を表示
			if ( iMdBziFig == 0) {
				DrawPart( pCod, iGpC, pPlcEn);					// 部材形状を表示
			} else {
				pCod->SetLineAttr( MPS_DASHDOT, 1, PartsLineColor);		// 一点鎖線の線分を表示
				ptW[0] = MgPoint2DC( pPlcEn->GetPIPlcIti( 0));
				ptW[1] = MgPoint2DC( pPlcEn->GetPIPlcIti( 1));
				pCod->Line( MgLine2D( ptW[0], ptW[1]));
//				pCod->Line( MgLine2D( ptW[0], ptW[1]));
			}
		}
	}
}

#define		MC_PNLNO_HANKEI		170.f

/////////////////////////////////////////////////////////////////////////////
//	１配置部品を表示する
void DrawPart( 
						msCod*		pCod,		// 座標系
						MINT		iGpC,		// 構成
						mhPlcParts	*pPlcEn
				)
{
	MgLine2D		LnParts;
	MgPoint2D	ptPartsN;
	MINT		iKeijoF;
	MREAL		rWidthR, rWidth;
	MgVect2D		VtWidthR, VtWidth;
	MgPoint2D	ptW[2];
	MgVect2D		VtW, VtUtW;
	MgPoint2D	ptH;
	MgPoint2D	ptK[4];
	MgVect2D		vptH;
	MgVect2D		vOffset = MgVect2D( 0., 20.);
	
	MhZukei		*pZukei;

	DWORD		PartsLineColor;

	MCHAR		SGN[100];

	MINT		ic;

	ptW[0] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0));
	ptW[1] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1));

	// 部材の形を表示
	VtW = ptW[1] - ptW[0];										// 芯線
	VtUtW = MGeo::UnitizeVect2D( VtW);								// 部材の形を求める

	// たて枠用の形状作成
	if ( pPlcEn->IsFrame()) {									// たて枠用の形状作成
		VtWidthR = (pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure()) * VtUtW.RotR90(); 
		VtWidth = pPlcEn->GetMbTWidth() * VtUtW.RotL90(); 
		ptH = ptW[0] + pPlcEn->GetPIPlcZure() * VtUtW;
		ptK[0] = ptH + pPlcEn->GetMbTHeightF() * VtUtW + VtWidthR;
		ptK[1] = ptH - pPlcEn->GetMbTHeightB() * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
		iKeijoF = 0;											// 形状算出済
		
	// パネルまたは床|天井|屋根・開口
	} else if ( pPlcEn->IsPanel() || pPlcEn->IsKaiko()) {
		// 床・天井
		if ( pPlcEn->IsYuka() || pPlcEn->IsTenjo()) {
			rWidthR = pPlcEn->GetPIMaeHosei();					// 手前側補正
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();			// 手前側補正 + 奥行き + 奥行き補正
			iKeijoF = 2;

		// 屋根
		} else if ( pPlcEn->IsYane()) {
			rWidthR = pPlcEn->GetPIMaeHosei();					// 手前側補正
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();			// 手前側補正 + 奥行き + 奥行き補正
			iKeijoF = 2;

		// その他?
		} else {
			rWidthR = pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure(); 
			rWidth = pPlcEn->GetMbTWidth(); 
			iKeijoF = 3;
		}
	
	// 横袈材
	} else {													// 横置部材の形状作成
		if ( pPlcEn->GetPIMbr() ) {
			rWidthR = pPlcEn->GetMbWidthR() + pPlcEn->GetPISinZure(); 
			rWidth = pPlcEn->GetMbWidth(); 
			iKeijoF = 1;
		} else {
			iKeijoF = 0;										// 形状算出済(図形データにあり)
		}
	}

	// 矩形形状作成
	if ( iKeijoF != 0) {										// 形状算出
		VtWidthR = rWidthR * VtUtW.RotR90(); 
		VtWidth = rWidth * VtUtW.RotL90(); 
		ptK[0] = ptW[0] - pPlcEn->GetPILenHosei( 0) * VtUtW + VtWidthR;
		ptK[1] = ptW[1] + pPlcEn->GetPILenHosei( 1) * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
	}

	// 線色の設定
	if ( iGpC == MP_GP_KABE && pPlcEn->IsKabe()) {
		PartsLineColor = mcs::GetColor( MM_COLOR_KABESEN);

	} else {
		PartsLineColor = pPlcEn->GetPTColor();
	}
	pCod->SetLineAttr( MPS_SOLID, 1, PartsLineColor);
	
	pZukei = pPlcEn->GetPIZukei();
	if ( pZukei) {												// 図形データ有りの場合は、それを表示
		for ( ic=0; ic<pZukei->m_isNZukei; ic++) {
			pCod->Line( MgLine2DC( pZukei->m_lnZukei[ic]));
		}
	
	} else {													// 図形データなしの場合は求めた形状を表示
		pCod->Polygon( ptK, 4);
	}

	// 部材の注記を表示

	// パネルの場合はパネル番号を表示
	if ( iKeijoF == 2) {										// パネル
		MgPoint2D ptCenter = (ptK[0] + ptK[2]) / 2.f;
		MgVect2D  vtL1 = ptK[2] - ptK[0];
		MgVect2D  vtutL1 = MGeo::UnitizeVect2D( vtL1);
		MgVect2D  vtL2 = ptK[3] - ptK[1];
		MgVect2D  vtutL2 = MGeo::UnitizeVect2D( vtL2);

		pCod->Arc1( ptCenter, MC_PNLNO_HANKEI, 0., 0.);

		pCod->Line( ptCenter - MC_PNLNO_HANKEI * vtutL1, ptK[0]);
		pCod->Line( ptCenter - MC_PNLNO_HANKEI * vtutL2, ptK[1]);
		pCod->Line( ptCenter + MC_PNLNO_HANKEI * vtutL1, ptK[2]);
		pCod->Line( ptCenter + MC_PNLNO_HANKEI * vtutL2, ptK[3]);

		Msprintf_s( SGN, Mstr( "%d"), pPlcEn->GetPIPanelNo());
//		Msprintf_s( SGN, Mstr( "%d"), 172);
		pCod->SetTextHeight( 130);
//		pCod->SetTextDirect( MgVect2D( 1., 0));
		pCod->SetTextDirect( MgVect2D( 1., 0.));
		pCod->Text( ptCenter + MgVect2D( 0., -20.), SGN);
	}

	// 壁枠組以外は部材注記を表示
	if ( iGpC != MP_GP_KABE) {
		ptPartsN = (ptK[3] + ptK[2]) * 0.5;
		pCod->SetTextDirect( VtW);
		Msprintf_s( SGN, Mstr( "%s %s %d"), pPlcEn->GetPTNmParts1(),
										 pPlcEn->GetMbCdMbr(), z_ign++);
		pCod->Text( ptPartsN, SGN);
	}
}

} // namespace MC
