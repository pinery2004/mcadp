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
#include "MhInpPlcParts.h"

#include "MainFrm.h"
#include "MmCmdMsg.h"

namespace MC
{

mhPlcParts		mtPlcInp::m_PIInp;
MhTateguInfo	mtTateguInp::m_TateguInp;

////////////////////////////////////////////////////////////////////////////
//	入力モード	
mnIoPartsAttr	z_mnIA;

mnIoPartsAttr::mnIoPartsAttr()
{
	m_iInpKai = 1;
	m_iInpMd = MP_MD_CREATE;
}

////////////////////////////////////////////////////////////////////////////
//    家モデル入力属性値を初期化する
void IeModel::MnInitInpAt()
{
	// 部材入力属性

	MINT	iKai;
	iKai = z_mnIA.GetInpKai();
	mtPlcInp::SetInpKai( iKai);
	mtPlcInp::SetCdHgt( 0);
	mtPlcInp::SetPanelNo( 0);
	mtPlcInp::SetInpKaikoNo( 0);
//	mtPlcInp::SetIdPartsSpec( 0);
	mtPlcInp::SetIdMbr( 0);
//	mtPlcInp::SetpPartsSpec( NULL);
//Z	mtPlcInp::SetpMbr( BuzaiCode::MhGetpMbr( 0));
	z_mnIA.SetKCdBrB( true, true, true);

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
int mnIoPartsAttr::RibbonIO(
					ComboTp	i_iComboTp,		// Combo種類	1:入力点区分コード
					int		i_iCdArg1,		//				
					MREAL	i_rCdArg2		//				
				)
{
	m_iSts = 0;
	m_iComboTp = i_iComboTp;
	m_iCdArg1 = i_iCdArg1;
	m_rCdArg2 = i_rCdArg2;
	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_MYMESSAGERIBBONIO);
	return m_iSts;
}

//	SetComboCd( MSET_INPUT_KUBUN_CD, aaa);
///////////////////////////////////////////////////////////////////////////////
//	リボンバーのコンボックスの設定　本体
void mnIoPartsAttr::SetComboCdBody( void)
{
	switch ( m_iComboTp)
	{
	case MSET_INPUT_KUBUN_CD:
		SelectComboInpKbnByInpKbnCd( m_iCdArg1);
		break;
	case MGET_PARTS_ATTRA:
		GetPartsSpec();
//S		GetComboAttrA();
		break;
	}
}


} // namespace MC