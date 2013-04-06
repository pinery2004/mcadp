//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhFile.cpp
//
//		入力属性値を初期設定する
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

#include "MhDefParts.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"

#include "MmLib.h"
#define	DLL_EXPORT_MHTATEGUINP_DO
#define	DLL_EXPORT_MHPLCINP_DO
#include "MhInp.h"

#include "MainFrm.h"

namespace MC
{

mhPlcInfo		mtPlcInp::m_PIInp;
MhTateguInfo	mtTateguInp::m_TateguInp;

////////////////////////////////////////////////////////////////////////////
//	入力モード	
mnInpAttr	z_mn;

mnInpAttr::mnInpAttr()
{
	m_iInpKai = 1;
	m_iInpMd = 0;
}

////////////////////////////////////////////////////////////////////////////
//    家モデル入力属性値を初期化する
void IeModel::MnInitInpAt()
{
	// 部材入力属性

	MINT	iKai;
	iKai = z_mn.GetKai();
	mtPlcInp::SetKai( iKai);
	mtPlcInp::SetCdHgt( 0);
	mtPlcInp::SetPanelNo( 0);
	mtPlcInp::SetKaikoNo( 0);
//	mtPlcInp::SetIdPartsTp( 0);
	mtPlcInp::SetIdMbr( 0);
//	mtPlcInp::SetpPartsTp( NULL);
//Z	mtPlcInp::SetpMbr( BuzaiCode::MhGetpMbr( 0));
	z_mn.SetKCdBrB( true, true, true);

	mtPlcInp::SetSinZure( 0.f);
	mtPlcInp::SetPlcZure( 0.f);
	mtPlcInp::SetLenHosei( 0, 0.f);
	mtPlcInp::SetLenHosei( 1, 0.f);
	mtPlcInp::SetHgt( 0, 0.f);
	mtPlcInp::SetHgt( 1, 0.f);
	mtPlcInp::SetpAuxAttr( NULL);
/*
	// 建具入力属性

	MhSetG_InpTateguCode( Mstr( ""));
	MhSetG_InpTateguROW( 910.f);
	MhSetG_InpTateguROH( 1000.f);
	MhSetG_InpTateguHeight( 2100.f);
	MhSetG_InpTateguMU( 38.f, 0);
	MhSetG_InpTateguMU( 38.f, 1);
*/
}

///////////////////////////////////////////////////////////////////////////////
//	リボンバーの設定と取り込み
void mnInpAttr::RibbonIO(
					int		i_iComboTp,		// Combo種類	1:入力点区分コード
					int		i_iCdArg1,		//				
					MREAL	i_rCdArg2		//				
				)
{
	m_iComboTp = i_iComboTp;
	m_iCdArg1 = i_iCdArg1;
	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_USER100);
}

//	SetComboCd( MSET_INPUT_KUBUN_CD, aaa);
///////////////////////////////////////////////////////////////////////////////
//	リボンバーのコンボックスの設定　本体
void mnInpAttr::SetComboCdBody( void)
{
	switch ( m_iComboTp)
	{
	case MSET_INPUT_KUBUN_CD:
		SetComboCdInpKb( m_iCdArg1);
		break;
	case MGET_COMBO_ATTRA:
		GetComboAttrA();
		break;
	}
}


} // namespace MC