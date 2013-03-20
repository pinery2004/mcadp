//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhFile.cpp
//
//		“ü—Í‘®«’l‚ğ‰Šúİ’è‚·‚é
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

#include "MmDefine.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"

#include "MmLib.h"
#define	DLL_EXPORT_MHTATEGUINP_DO
#define	DLL_EXPORT_MHPLCINP_DO
#include "MtInp.h"

namespace MC
{

mhPlcInfo		mtPlcInp::m_PIInp;
MhTateguInfo	mtTateguInp::m_TateguInp;

////////////////////////////////////////////////////////////////////////////
//    “ü—Í‘®«’l‚ğ‰Šú‰»‚·‚é
void IeModel::MhInitInpAt()
{
	// •”Ş“ü—Í‘®«

	MINT	iKai;
	iKai = MC::mtInpMode::GetKai();
	mtPlcInp::SetKai( iKai);
	mtPlcInp::SetCdHgt( 0);
	mtPlcInp::SetPanelNo( 0);
	mtPlcInp::SetKaikoNo( 0);
//	mtPlcInp::SetIdTpPts( 0);
	mtPlcInp::SetIdMbr( 0);
//	mtPlcInp::SetpTpPts( NULL);
//Z	mtPlcInp::SetpMbr( BuzaiCode::MhGetpMbr( 0));

	mtPlcInp::SetSinZure( 0.f);
	mtPlcInp::SetPlcZure( 0.f);
	mtPlcInp::SetLenHosei( 0, 0.f);
	mtPlcInp::SetLenHosei( 1, 0.f);
	mtPlcInp::SetHgt( 0, 0.f);
	mtPlcInp::SetHgt( 1, 0.f);
	mtPlcInp::SetpAuxAttr( NULL);
/*
	// Œš‹ï“ü—Í‘®«

	MhSetG_InpTateguCode( Mstr( ""));
	MhSetG_InpTateguROW( 910.f);
	MhSetG_InpTateguROH( 1000.f);
	MhSetG_InpTateguHeight( 2100.f);
	MhSetG_InpTateguMU( 38.f, 0);
	MhSetG_InpTateguMU( 38.f, 1);
*/
}

////S MhTategu* MhpInpTategu()
////{
////	return &g_hInpTateguAttr;
////}
////mhPlcInfo* MhpInpPI()
////{
////	return &g_hInpPIAttr;
////}

} // namespace MC