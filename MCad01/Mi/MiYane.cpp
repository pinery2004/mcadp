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
#include "MdHist.h"

#include "MdLib.h"
#include "MhLib.h"


#include "MdList.h"
#include "MhRoof.h"
#include "MhLib.h"

#include "MhPlcParts.h"

#include "MdOpt.h"
#include "MmValid.h"

#include "MmPrompt.h"
#include "MhPlcPartsLib.h"


namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	屋根構成線丸め線を取得する
//
void mhInput::MmGetMarumeYaneLine(
						MINT		iKai,			// 検索階
				const	MgPoint2D	&Pi,			// 入力座標
						MgGLine2D	*pGLn			// 対象屋根構成線
				)
{
	MINT		ist1;
	MINT		iCdMarume;
	MREAL		rTol;
	MREAL		rDsv;
	MINT		ic1, ic2, ic2b;
	MhRoofInfo*	pRoofEn;
	MgPoint3D	Py1;
	MgLine2D		Ln1;

	iCdMarume = z_mnIA.GetComboMarumeCd();
	if ( iCdMarume == 0)
		rTol = MC_MARUME_TOL;
	else
		rTol = mcs::GetReal( MM_REAL_PITCH) / ( iCdMarume * 2);

	pGLn->m_n = 0;
	for ( pRoofEn = HaitiDb::MdGetHeadRoof(); pRoofEn!=0;
		  pRoofEn = HaitiDb::MdGetNextRoof()) {
		if ( pRoofEn->GetInpKai() != iKai)
			continue;
		if ( !MmCheckValidRoof( pRoofEn))							// オプションと履歴のチェック
			continue;
		for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
			if ( MGeo::CheckZero( pRoofEn->GetpGRfm()->m_st[ic1].m_Pln.v.z))				// 矢切は無視
				continue;
			ic2b = pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_n - 1;
			for ( ic2=0; ic2<pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_n; ic2b=ic2,ic2++) {
				Ln1 = MgLine2D( MgPoint2DC( pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_P[ic2b]),
							    MgPoint2DC( pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_P[ic2]));
				rDsv = MgTol::SetD( rTol);
				if ( MGeo::CheckPointOnLine2D( Pi, Ln1, &ist1))
					(*pGLn) += Ln1;
				MgTol::SetD( rDsv);
			}
		}
	}
}

} // namespace MC
