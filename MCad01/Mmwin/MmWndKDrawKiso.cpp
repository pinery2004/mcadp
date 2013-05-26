//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		ƒhƒ‰ƒbƒMƒ“ƒO‘€ì
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
//	Šî‘bcü‚ð•\Ž¦‚·‚é
	void WindowCtrl::DrawKisoSin(
						msCod*		pCod,			// À•WŒn
						MINT		iKaiC,			// ŠK  	(1,2,3)
						MINT		iGpC			// \¬
				)
{
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgPoint2D	ptW[2];
	DWORD		PartsLineColor;

	MREAL		rKisoSinZ = pCod->LPtoRP( MINT( pCod->DPtoLP(1)));
	MgVect2D		vKisoSinZ = MgVect2D( rKisoSinZ, rKisoSinZ);

	// ‚PŠK‚Ì“y‘ä‚É‚ÍAŠî‘bcü‚ð•\Ž¦‚·‚é

	if ( iKaiC == 1 && iGpC == MP_GP_DODAI) {

		for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
			  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

			if ( pPlcEn->IsKiso()) {								// Šî‘b(‘Ï—ÍŠî‘b)•”Þ

			if ( !MmCheckValidParts( pPlcEn))						// ƒIƒvƒVƒ‡ƒ“‚Æ—š—ð‚Ìƒ`ƒFƒbƒN
				continue;

				ptW[0] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0))) + vKisoSinZ;
				ptW[1] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1))) + vKisoSinZ;

				PartsLineColor = mcs::GetColor( MM_COLOR_KISOSIN);
				pCod->SetLineAttr( MPS_DASHDOT, 1, PartsLineColor);
				pCod->Line( MgLine2D( ptW[0], ptW[1]));
			}
		}
	}
}

} // namespace MC
