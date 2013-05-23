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
#include "MgMatD.h"
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

/////////////////////////////////////////////////////////////////////////////
//	線分を表示する
void MmWndKDrawLine(
						msCod*			pCod,		// 座標系
						mhPlcParts		*pPlcEn,	// 配置レコード
						MPENSTYLE		LineType,	// 線種
						MSYSTEMCOLOR	iLineColor,	// 線色コード
						MgVect2D			vSinZ		// 芯ずれ
				)
{
	MgPoint2D	ptW[2];
	DWORD		PartsLineColor;

	ptW[0] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0))) + vSinZ;
	ptW[1] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1))) + vSinZ;

	PartsLineColor = mcs::GetColor( iLineColor);
	pCod->SetLineAttr( LineType, 1, PartsLineColor);
	pCod->Line( MgLine2D( ptW[0], ptW[1]));

}

/////////////////////////////////////////////////////////////////////////////
//	線分を表示する
void MmWndKDrawLine(
						MINT			iMode,		// モード
													//		0:配置線分を表示、
													//		1:配置線分または図形を表示
						msCod*			pCod,		// 座標系
						mhPlcParts		*pPlcEn,	// 配置レコード
						MPENSTYLE		LineType,	// 線種
						MSYSTEMCOLOR	iLineColor,	// 線色コード
						MgVect2D			vSinZ		// 芯ずれ
				)
{
	MgPoint2D	ptW[2];
	DWORD		PartsLineColor;
	MhZukei		*pZukei;
	MINT		ic;

	ptW[0] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0))) + vSinZ;
	ptW[1] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1))) + vSinZ;

	PartsLineColor = mcs::GetColor( iLineColor);
	pCod->SetLineAttr( LineType, 1, PartsLineColor);

	pZukei = pPlcEn->GetPIZukei();
	if ( iMode == 0 || pZukei == NULL) {
		pCod->Line( MgLine2D( ptW[0], ptW[1]));
	} else {
		for ( ic=0; ic<pZukei->m_isNZukei; ic++) 
			pCod->Line( MgLine2DC( pZukei->m_lnZukei[ic]));
	}
}

/////////////////////////////////////////////////////////////////////////////
//	壁芯線を表示する
void WindowCtrl::MmWndKDrawKabe(
						msCod*		pCod,			// 座標系
						MINT		iKaiC,			// 階  	(1,2,3)
						MINT		iGpC			// 構成
				)
{
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
	MINT		iEnKai;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgPoint2D	ptW[2];

	MREAL		rKabeSinZ = pCod->LPtoRP( MINT( pCod->DPtoLP(1)));
	MgVect2D		vKabeSinZ = MgVect2D( rKabeSinZ, rKabeSinZ) / 2.;

	// 壁線を表示する

	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		iEnKai = pPlcEn->GetPIKai();

		// 壁(耐力壁)
		if ( pPlcEn->IsKabe()) {

			if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

			// 床組、壁枠組、耐力壁には、下階の壁芯線を表示する
			if ( iEnKai == iKaiC - 1) {							// 下階の壁
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAIKABESIN, vKabeSinZ);

			// 耐力壁|壁枠組以外には、同階の壁芯線を表示する
			} else if ( iEnKai == iKaiC) {						// 同階の壁
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// 耐力壁|壁枠組み以外は壁芯線を表示
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAIKABESIN, vKabeSinZ);

			// 天井、小屋、屋根には、上階の壁芯線を表示する
			} else if ( iEnKai == iKaiC + 1) {					// 上階の壁
				if ( iGpC >= MP_GP_TENJO)						// 壁(耐力壁)部材の表示
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAIKABESIN, - vKabeSinZ);
			}

		// 耐力壁区画
		} else if ( pPlcEn->IsTaiKabeArea()) {

			if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

			// 床組、壁枠組、耐力壁には、下階の耐力壁区画を表示する
			if ( iEnKai == iKaiC - 1) {							// 下階の壁
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( 1, pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAITAIKABESIN, vKabeSinZ);

			// 耐力壁|壁枠組以外には、同階の耐力壁区画を表示する
			} else if ( iEnKai == iKaiC) {						// 同階の壁
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// 耐力壁|壁枠組み以外は壁芯線を表示
					MmWndKDrawLine( 1, pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAITAIKABESIN, vKabeSinZ);

			// 天井、小屋、屋根には、上階の耐力壁区画を表示する
//			} else if ( iEnKai == iKaiC + 1) {					// 上階の壁
//				if ( iGpC >= MP_GP_TENJO)						// 壁(耐力壁)部材の表示
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAITAIKABESIN, - vKabeSinZ);
			}

		// 耐力壁線
		} else if ( pPlcEn->IsTaiKabeLine()) {

			if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

			// 床組、壁枠組、耐力壁には、下階の耐力壁線を表示する
			if ( iEnKai == iKaiC - 1) {							// 下階の壁
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAITAIKABESIN, vKabeSinZ);

			// 耐力壁|壁枠組以外には、同階の耐力壁線を表示する
			} else if ( iEnKai == iKaiC) {						// 同階の壁
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// 耐力壁|壁枠組み以外は壁芯線を表示
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAITAIKABESIN, vKabeSinZ);

			// 天井、小屋、屋根には、上階の耐力壁線を表示する
//			} else if ( iEnKai == iKaiC + 1) {					// 上階の壁
//				if ( iGpC >= MP_GP_TENJO)						// 壁(耐力壁)部材の表示
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAITAIKABESIN, - vKabeSinZ);
			}

		// 支持壁線
		} else if ( pPlcEn->IsSijiKabeLine()) {

			if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

			// 床組、壁枠組、耐力壁には、下階の支持壁線を表示する
			if ( iEnKai == iKaiC - 1) {							// 下階の壁
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAISIJIKABESIN, vKabeSinZ);

			// 耐力壁|壁枠組以外には、同階の支持壁線を表示する
			} else if ( iEnKai == iKaiC) {						// 同階の壁
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// 耐力壁|壁枠組み以外は壁芯線を表示
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAISIJIKABESIN, vKabeSinZ);

			// 天井、小屋、屋根には、上階の支持壁線を表示する
//			} else if ( iEnKai == iKaiC + 1) {					// 上階の壁
//				if ( iGpC >= MP_GP_TENJO)						// 壁(耐力壁)部材の表示
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAISIJIKABESIN, - vKabeSinZ);
			}
		}
	}
}

} // namespace MC
