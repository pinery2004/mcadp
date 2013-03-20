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
#include "MmDefine.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"

#include "MsBitSet.h"
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"

#include "MhPlcInfo.h"

#include "MmPrompt.h"

#define		MAXHAIKABE		500									// 配列制限値
#define		MC_KABE_TOL		44.5								// 壁判定トレランス

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	壁芯丸め線を取得する
//
void mtInput::GetMarumeKabeLine(
						MINT		iKai,			// 検索階
				const	MgPoint2	&Pi,			// 入力座標
						MgGLine2	*pGLn			// 対象壁芯
				)
{
	MINT		ist1;
	MINT		iCdMarume;
	MREAL		rTol;
	mhPlcInfo*	pHaiKabe[MAXHAIKABE];				// 壁データ
	MINT		nHaiKabe;							// 壁数
	MINT		ic2;
	MgLine2		ln1;

	iCdMarume = mtInpMode::GetComboCdMarume();
	if ( iCdMarume == 0)
		rTol = MC_KABE_TOL;
	else
//		rTol = g_SysProp.Real[MM_REAL_PITCH] / iCdMarume;
		rTol = McSystemProperty::GetReal( MM_REAL_PITCH) / iCdMarume;

	nHaiKabe = mtHaitiIn::GetPts( iKai, MP_GP_TAIRYOKU, Mstr( "壁"), NULL, MAXHAIKABE, pHaiKabe);
																				// 家モデルよりカレント階の全ての壁を取得
	pGLn->m_n = 0;
	for ( ic2=0; ic2<nHaiKabe; ic2++) {											// 壁
		ln1 = MgLine2C( pHaiKabe[ic2]->GetPIPlcIti());
		if ( MGeo::ChkPt2OnLn2WS( Pi, ln1, &ist1, MC_KABE_TOL))
			(*pGLn) += MgLine2C( pHaiKabe[ic2]->GetPIPlcIti());
	}
	if ( pGLn->m_n == 0) {
		Msg::ErrorMsg( Mstr( "壁上に入力して下さい"), MC_ERR_BASE);				// ""
	}
}

} // namespace MC