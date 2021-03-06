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
#include "MsDefine.h"
#include "MmLib.h"

#include "MhPlcParts.h"

#include "MmPrompt.h"
#include "MhPlcPartsLib.h"

#define		MAXHAIKABE		500									// 配列制限値
#define		MC_KABE_TOL		44.5								// 壁判定トレランス

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	壁芯丸め線を取得する
//
void mhInput::GetMarumeKabeLine(
						MINT		iKai,			// 検索階
				const	MgPoint2D	&Pi,			// 入力座標
						MgGLine2D	*pGLn			// 対象壁芯
				)
{
	MINT		ist1;
	MINT		iCdMarume;
	MREAL		rTol;
	MREAL		rTolDsv;
	mhPlcParts*	pHaiKabe[MAXHAIKABE];				// 壁データ
	MINT		nHaiKabe;							// 壁数
	MINT		ic2;
	MgLine2D		ln1;

	iCdMarume = z_mnIA.GetComboMarumeCd();
	if ( iCdMarume == 0)
		rTol = MC_KABE_TOL;
	else
		rTol = mcs::GetReal( MM_REAL_PITCH) / iCdMarume;

	nHaiKabe = mhHaitiIn::GetParts( iKai, MP_GP_TAIRYOKU, Mstr( "壁"), NULL, MAXHAIKABE, pHaiKabe);
																				// 家モデルよりカレント階の全ての壁を取得
	pGLn->m_n = 0;
	for ( ic2=0; ic2<nHaiKabe; ic2++) {											// 壁
		ln1 = MgLine2DC( pHaiKabe[ic2]->GetPIPlcIti());
		rTolDsv = MgTol::SetD( rTol);
		if ( MGeo::CheckPointOnLine2D( Pi, ln1, &ist1))
			(*pGLn) += MgLine2DC( pHaiKabe[ic2]->GetPIPlcIti());
		MgTol::SetD( rTolDsv);
	}
	if ( pGLn->m_n == 0) {
		Msg::ErrorMsg( Mstr( "壁上に入力して下さい"), MC_ERR_BASE);				// ""
	}
}

} // namespace MC
