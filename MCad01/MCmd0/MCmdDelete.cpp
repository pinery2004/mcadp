//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"
#include "MmValid.h"

namespace MC
{

void MCmdLineDelete()
{
	MINT			ist1;
	MINT			irt;
	MgPoint2D		pt1, pt2;
	MgPoint2D		ptK[2];
	MgPoint2D		ptW[2];
	MgLine2D			Ln1;
	MgPolyg2D		pg1(20);
	MINT			iIdPartsSpec, iIdPartsSpecB;
	MINT			iKaiC;
	MINT			iGpC, iGpB;
	mhPartsSpec*		pPartsSpec;
	mhPlcParts*		pPlcEn;
	MPOSITION		pos1;
	Window::CurWndFocus();

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_DEL_PARTS);							// ステイタスバーの操作表示部へ"部材追加"を表示

	iKaiC = z_mnIA.GetInpKai();
	iGpC = z_mnIA.GetKCdGp();
	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	MFOREVER {
		Msg::GuidanceMsg( MC_GUID_DEL_PARTS);
		irt = MtAskForPoint( &pt1);								// １点目を入力
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)			// システムストップまたはキャンセル
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// マウス右ボタン || メニュー入力
			continue;

		HaitiCmd::MmPresetCmd();
		// 指示部材を検索する
		for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
			  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

			if ( pPlcEn->GetPIKai() != iKaiC)
				continue;										// 異なる階の部材は表示しない
			iGpB = pPlcEn->GetPIPartsSpec()->GetPTCdGp();
			iIdPartsSpecB = pPlcEn->GetPIIdPartsSpec();
			if ( iGpB != iGpC || iIdPartsSpecB != iIdPartsSpec)
				continue;										// 異なる構成の部材は表示しない

			if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
				continue;

			ptW[0] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0));
			ptW[1] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1));

			MgVect2D	VtW = ptW[1] - ptW[0];
			MgVect2D	VtUtW = MGeo::UnitizeVect2D( VtW);
			MgVect2D	VtWidthR = (pPlcEn->GetMbWidthR() + pPlcEn->GetPISinZure()) * VtUtW.RotR90(); 
			MgVect2D	VtWidth = pPlcEn->GetMbWidth() * VtUtW.RotL90(); 
			pg1.m_n = 0;
			pg1 += (ptW[0] - pPlcEn->GetPILenHosei( 0) * VtUtW + VtWidthR);
			pg1 += (ptW[1] + pPlcEn->GetPILenHosei( 1) * VtUtW + VtWidthR);
			pg1 += (pg1.m_p[1] + VtWidth);
			pg1 += (pg1.m_p[0] + VtWidth);

			MGeo::CheckPointOnPolygon2DWS( pt1, pg1, &ist1);
			if ( ist1 == MC_IN_BORDER) {
				if (mhHaitiIn::CheckParts( NULL, MP_GP_TAIRYOKU, Mstr( "壁"), NULL, pPlcEn))
					IeModel::MhKabeSetUpFlg();
				break;
			}
		}
		// 削除する
		if ( pPlcEn != 0)
			HaitiDb::MdPartsDelete( pos1);

		IeModel::MhNormKabe( 0);

		WindowCtrl::ReDrawWnd();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// ステイタスバーの操作表示部へ""を表示
}

void MCmdRoofDelete()
{
	MINT			irt;
	MgPoint2D		pt1, pt2;
	MgPoint2D		ptK[2];
	MgPoint2D		ptW[2];
	MgPoint3D		Py1;
	MgLine2D			Ln1;
	MgPolyg2D		pg1(20);
	MINT			ic1, ic2;
	MhRoofInfo*		pRoofEn;
	MPOSITION		pos1;
	Window::CurWndFocus();
	MgMinMaxR3D		rMmMdl;
	MgMinMaxR2D		rmmMdl;
	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_DEL_ROOF);							// ステイタスバーの操作表示部へ"屋根削除"を表示

	MFOREVER {
		Msg::GuidanceMsg( MC_GUID_DEL_ROOF);
		irt = MtAskForPoint( &pt1);								// １点目を入力
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)			// システムストップまたはキャンセル
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// マウス右ボタン || メニュー入力
			continue;

		HaitiCmd::MmPresetCmd();
		// 屋根を検索する
		for ( pRoofEn = HaitiDb::MdGetHeadRoof( &pos1); pRoofEn!=0;
			  pRoofEn = HaitiDb::MdGetNextRoof( &pos1)) {
			if ( !MmCheckValidRoof( pRoofEn))						// オプションと履歴のチェック
				continue;
			// 屋根のMINMAXを求める
			rMmMdl.SetInit();
			for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
				for ( ic2=0; ic2<pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_n; ic2++) {
					Py1 = pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_P[ic2];
					rMmMdl.Ins3( Py1);
				}
			}
			rmmMdl = MgMinMaxR2D( MgPoint2DC( rMmMdl.min), MgPoint2DC( rMmMdl.max));
			if ( MGeo::CheckPointInMinmaxR2D( pt1, rmmMdl))
				break;
		}

		// 削除する
		if ( pRoofEn != 0)
			HaitiDb::MdRoofDelete( pos1);

		WindowCtrl::ReDrawWnd();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// ステイタスバーの操作表示部へ""を表示
}

} // namespace MC
