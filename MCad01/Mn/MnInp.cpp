//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhFile.cpp
//
//		���͑����l�������ݒ肷��
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgPoint.h"

#include "MdList.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"

#include "MmLib.h"
#define	DLL_EXPORT_MHTATEGUINP_DO
#define	DLL_EXPORT_MHPLCINP_DO
#include "MhInpPlcParts.h"

#include "MmCmdMsg.h"

namespace MC
{

mhPlcParts		mtPlcInp::m_PIInp;
MhTateguInfo	mtTateguInp::m_TateguInp;

////////////////////////////////////////////////////////////////////////////
//	���̓��[�h	
mnIoPartsAttr	z_mnIA;

mnIoPartsAttr::mnIoPartsAttr()
{
//S1	m_iInpKai = 1;
	m_IA.m_iInpKai = 1;
	m_iInpMd = MP_MD_CREATE;
}

////////////////////////////////////////////////////////////////////////////
//    �ƃ��f�����͑����l������������
void IeModel::MnInitInpAt()
{
	// ���ޓ��͑���

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
	// ������͑���

	MhSetG_InpTateguCode( Mstr( ""));
	MhSetG_InpTateguROW( 910.f);
	MhSetG_InpTateguROH( 1000.f);
	MhSetG_InpTateguHeight( 2100.f);
	MhSetG_InpTateguMU( 38.f, 0);
	MhSetG_InpTateguMU( 38.f, 1);
*/
}

///////////////////////////////////////////////////////////////////////////////
//	���{���o�[�̐ݒ�Ǝ�荞��
int mnIoPartsAttr::RibbonIO(
					ComboTp	i_iComboTp,		// Combo���	1:���͓_�敪�R�[�h
					int		i_iCdArg1,		//				
					MREAL	i_rCdArg2		//				
				)
{
	m_iSts = 0;
	m_iComboTp = i_iComboTp;
	m_iCdArg1 = i_iCdArg1;
	m_rCdArg2 = i_rCdArg2;
	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_MYMESSAGE_RIBBONIO);
	return m_iSts;
}

int mmIoPartsAttr::RibbonIO(
					ComboTp	i_iComboTp,		// Combo���	1:���͓_�敪�R�[�h
					int		i_iCdArg1,		//				
					MREAL	i_rCdArg2		//				
				)
{
	return z_mnIA.RibbonIO( i_iComboTp, i_iCdArg1, i_rCdArg2);
}

} // namespace MC