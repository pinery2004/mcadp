//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MiPartsPlace.cpp
//
//		部品配置操作
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

#define DLL_EXPORT_MC_HAITIIN_DO
#include "MmLib.h"

#include "McSystemProperty.h"

#include "resource.h"
#include "..\\MCAD\\resource.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MhInpPlcParts.h"

#define	DLL_EXPORT_MC_INPATTR_DO 
#include "MhPlcPartsLib.h"

#include "MdOpt.h"
#include "MdLib.h"

#include "MdHist.h"
#include "MmValid.h"

#define	 DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"

#include "MhParts.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	部品を１本配置する
void HaitiCmd::MmPartsPlc(
				const	MgPoint3D	*Pt,		// (I  ) 配置点、配置方向点
				const	MgVect3D	vUpPlc,		// (I  ) 配置上方向
				const	MgPolyg2D	*ppg		// (I  ) 図形用の区画　または NULL
				)
{
	mhPlcParts	PlcEn;
	MhZukei*	pZukei;
	MINT		szZukei;
	MgVect3D		vBz = Pt[1] - Pt[0];
	MREAL		rBzLng_2 = vBz * vBz;
	if ( rBzLng_2 < MinmaxIN_BZILEN_2) {
		//	部材長さ不足エラー表示 **************************************
		MQUIT;
	}
/*D
	MsBitSet	*pOptv;
	MsBitSet	*pHstv;

	MhAddOpt( &pOptv);							// Opt対応　新規追加レコード
	PlcEn.SetPIOpt1( pOptv);					// Opt対応
	MhHistAdd( &pHstv);							// 履歴管理対応　新規追加レコード
	PlcEn.SetPIVer( pHstv);						// 履歴管理対応
*/
//D	MdPartsAdd( &PlcEn, 1);
	
	PlcEn.SetPIKai( mtPlcInp::GetInpKai());
	PlcEn.SetPIIdPartsSpec( mtPlcInp::GetComboPartsNmId());
	PlcEn.SetPIPartsSpec( mtPlcInp::GetPartsSpec());
	PlcEn.SetPIIdMbr( mtPlcInp::GetIdMbr());
	PlcEn.SetPIMbr( mtPlcInp::GetMbr());
	PlcEn.SetPILenHosei( 0, mtPlcInp::GetLenHosei( 0));
	PlcEn.SetPILenHosei( 1, mtPlcInp::GetLenHosei( 1));
	if ( PlcEn.IsPanel() || PlcEn.IsKaiko()) {
		PlcEn.SetPIMaeHosei( mtPlcInp::GetMaeHosei());
		PlcEn.SetPIOku( mtPlcInp::GetOku());
		PlcEn.SetPIOkuHosei(mtPlcInp::GetOkuHosei());
		PlcEn.SetPIHgt( 0, mtPlcInp::GetHgt( 0));
	} else {
		PlcEn.SetPISinZure( mtPlcInp::GetSinZure());
		PlcEn.SetPIPlcZure( mtPlcInp::GetPlcZure());
		PlcEn.SetPIHgt( 0, mtPlcInp::GetHgt( 0));
		PlcEn.SetPIHgt( 1, mtPlcInp::GetHgt( 1));
	}

	if ( PlcEn.IsFrame()) {										// たて枠 | 束　の上端高さを設定
		if ( MGeo::GT( PlcEn.m_rHgt[1], 0.f)) {
			PlcEn.SetPIHgt( 1, PlcEn.m_rHgt[1]);
		} else {
			PlcEn.SetPIHgt( 1, mcs::GetStnd( PlcEn.m_ibKai, MM_STNDH_CEILING) -	// 天井基準
							   mcs::GetStnd( PlcEn.m_ibKai, MM_STNDH_LOWER) +		// 下基準
							   PlcEn.m_rHgt[1]);
		}
	}
	PlcEn.SetPIPanelNo( mtPlcInp::GetPanelNo());
	PlcEn.SetPIKaikoNo( mtPlcInp::GetInpKaikoNo());

	PlcEn.SetPIPlcIti( 0, Pt[0]);
	PlcEn.SetPIPlcIti( 1, Pt[1]);
	PlcEn.SetPIUpPlc( vUpPlc);

	PlcEn.SetPIZukei( NULL);
	PlcEn.SetPIAuxAttr( mtPlcInp::GetpAuxAttr());
	mtPlcInp::SetpAuxAttr( NULL);

	if ( ppg != NULL && ppg->m_n>=2) {								// 図形用の区画データあり
		MINT nLine = ppg->m_n;
		if ( ppg->m_n == 2) nLine--;								// 2点の場合は直線1本

		szZukei = sizeof(MhZukei) + sizeof(MgLine3D) * (nLine - 1);	// 線分[nLine]本分の図形データサイズ
		pZukei = (MhZukei*)new char[szZukei];

		pZukei->m_ibObj = MHZK_DISP;								// 図形表示用
		pZukei->m_ibTp = MHZK_GLINE;								// 線分群

		pZukei->m_pNext = NULL;
		pZukei->m_isNZukei = nLine;
		for (MINT ic1=0; ic1<nLine; ic1++) {
			MINT ic2 = ic1 + 1;
			if ( ic2 == nLine) ic2 = 0;
			pZukei->m_lnZukei[ic1] = MgLine3D( MgPoint3DC( ppg->m_p[ic1]), MgPoint3DC( ppg->m_p[ic2]));
		}
		PlcEn.m_pZukei = pZukei;
		//
		szZukei = sizeof(MhZukei) - sizeof(MgLine3D) + sizeof(MgPoint3D) * (ppg->m_n);	// 点[ppg->n]個分の図形データサイズ
		pZukei = (MhZukei*)new char[szZukei];

		pZukei->m_ibObj = MHZK_AREA;								// 図形領域判定用
		pZukei->m_ibTp = MHZK_GPOINT;								// ポリゴン(点群)

		pZukei->m_pNext = NULL;
		pZukei->m_isNZukei = ppg->m_n;
		MgPoint2D* ppt = (MgPoint2D*)&pZukei->m_lnZukei[0];
		for (MINT ic1=0; ic1<ppg->m_n; ic1++) {
			ppt[ic1] = ppg->m_p[ic1];
		}
		PlcEn.m_pZukei->m_pNext = pZukei;
	}
//D	MdInjectParts( &PlcEn);
	HaitiDb::MdPartsAdd( &PlcEn, 1);
exit:;
}

/////////////////////////////////////////////////////////////////////////////
//	部品配置を取得する
//	返値 =-1: オーバーフロー, ≧0: 選択部品配置数
MINT mhHaitiIn::GetParts(
						MINT		iKai,			// (I  ) 階
						MINT		iIdPartsSpec,	// (I  ) 部品ID
				const	MCHAR*		cGeneralName,	// (I  ) 総称 または NULL
				const	MCHAR*		cNmParts1,		// (I  ) 操作用部材名 または NULL
						MINT		szPlcEn,		// (I  ) 部品配置最大数
						mhPlcParts*	*pPlcEno,		// (  O) 選択部品配置
						MPOSITION	*pPlcpos		// (  O) 選択[部品配置]位置 または NULL
				)
{
	MPOSITION	pos1;
	mhPlcParts* pPlcEn;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;

//	MINT szHE = szPlcEn - 1;
	MINT szHE = szPlcEn;

	MINT iHE = 0;
	for (pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		 pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {
		if ( !mhHaitiIn::CheckParts( iKai, iIdPartsSpec, cGeneralName, cNmParts1, pPlcEn))
			continue;											// 対象外部品配置
		if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

		if ( iHE >= szHE) {										// 選択部品配置　オーバフロー　<ERROR>
			iHE = -1;
			break;
		}
		pPlcEno[iHE] = pPlcEn;
		if ( pPlcpos)
			pPlcpos[iHE] = pos1;
		iHE++;
	}
	return iHE;
}

/////////////////////////////////////////////////////////////////////////////
//	部品配置を調べる
//	返値 true : 対象部品配置, false : 対象外部品配置
bool mhHaitiIn::CheckParts(
						MINT		iKai,			// (I  ) 階 または NULL
						MINT		iIdPartsSpec,	// (I  ) 部品ID または NULL
				const	MCHAR*		cGeneralName,	// (I  ) 総称 または NULL
				const	MCHAR*		cNmParts1,		// (I  ) 操作用部材名 または NULL
						mhPlcParts	*pPlcEn1		// (I  ) 調査部品配置
				)
{
	bool	bSt = false;
	if ( iKai != NULL && pPlcEn1->GetPIKai() != iKai)
		MQUIT;													// 異なる階の部材は対象外
	if ( iIdPartsSpec != NULL && pPlcEn1->GetPTCdGp() != iIdPartsSpec)
		MQUIT;													// 異なる構成の部材は対象外
	if ( cGeneralName != NULL &&
		Mstrcmp( pPlcEn1->GetPTNmGeneral(), cGeneralName) != 0)
		MQUIT;													// 異なる総称の部材は対象外
	if ( cNmParts1 != NULL &&
		Mstrcmp( pPlcEn1->GetPTNmParts1(), cNmParts1) != 0)
		MQUIT;													// 異なる操作用部材名の部材は対象外
	bSt = true;
exit:
	return bSt;
}

#define		MC_HITBZI_SZ	20
/////////////////////////////////////////////////////////////////////////////
//  部材配置を検索する
//	返値 検索結果　または　null:ヒットなし
mhPlcParts* mhHaitiIn::SrchBuzai(
						MmWndInfo*	pWndInfo,		// (I  ) ウィンドウ管理情報
						MgPoint2D&	ptMouthR,		// (I  ) 検索指示座標
						MINT		iCdBuzai,		// (I  ) 部材コード　または　NULL(全)
													//       MP_BZICD_PANEL(全パネル)
						MgPolyg2D*	ppgPartsShape	// (  O) 検出多角形　または　NULL
				)
{
	MINT		ist1;
	MINT		ic1;
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;							// 履歴管理対応
	mhPlcParts	*pHitBziEn[MC_HITBZI_SZ];
	MREAL		rAHitBziEn[MC_HITBZI_SZ];
	MgPolyg2D	pgHitBzi;
	MREAL		rArea;

	MINT		nHitBziEn = 0;
	MINT		iHitEnMin = 0;
   
	MINT		iKaiC   = z_mnIA.GetInpKai();	// 階  	(1,2,3)
	MINT		iGpC = z_mnIA.GetKCdGp();		// 構成

	MREAL		rAMinHitBziEn = MREALMAX;

	MINT		iBuzaiType = iCdBuzai / MP_BZICD_TYPE;
	if ( iCdBuzai - iBuzaiType * MP_BZICD_TYPE) iBuzaiType = -1;

	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// 異なる階の部材は検索しない
		if ( pPlcEn->GetPTCdGp() != iGpC)
			continue;											// 異なる構成の部材は検索しない
			
		if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

		if ( iCdBuzai) {										// 部材コードが指定されている場合はチェックする
			if ( (pPlcEn->GetPTCdBuzai() / MP_BZICD_TYPE == iBuzaiType) ||
				(pPlcEn->GetPTCdBuzai() == iCdBuzai))
				;
			else
				continue;										// 異なる部材コードの部材は検索しない
		} 

		mhHaitiIn::PartsShape( pPlcEn,	&pgHitBzi);				// 部材形状を求める
		// 部材形状のMIN/MAXを求める
		MgMinMaxR2D rMinMax;
		rMinMax.SetInit();
		for ( ic1=0; ic1<pgHitBzi.m_n; ic1++) 
			rMinMax.Ins2( pgHitBzi.m_p[ic1]);
		// 指示部材を検索
		if ( MGeo::CheckPointInMinmaxR2D( ptMouthR, rMinMax)) {				// 部材形状のMIN/MAXで検査し
			if ( MGeo::CheckPointOnPolygon2DWS( ptMouthR, pgHitBzi, &ist1)) {	// さらに部材形状で検査する
				pHitBziEn[nHitBziEn] = pPlcEn;
				// 複数該当の場合は面積最小を選ぶ
				rArea = pgHitBzi.Area();
				rAHitBziEn[nHitBziEn] = rArea;
				if ( rArea < rAMinHitBziEn) {
					rAMinHitBziEn = rArea;
					if ( ppgPartsShape)
						*ppgPartsShape = pgHitBzi;
					iHitEnMin = nHitBziEn;
				}
				nHitBziEn++;
//				return pPlcEn;									// 指示部材
			}
		}
	}
	if ( nHitBziEn)
		return pHitBziEn[iHitEnMin];
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//	長さ調整部材に接触する部材と交差する部材を求める
void mhHaitiIn::MmSrchCrossBuzai(
						MmWndInfo	*pWndInfo,		// (I  ) ウィンドウ管理情報
						mhPlcParts	*pBziInfo1,		// (I  ) 長さ調整部材
						MINT		iCdBuzai,		// (I  ) 検索対象の部材コード
						mhPlcParts	**pbTchBzi,		// (  O) 長さ調整後の部材に接触する部材
						mhPlcParts	**pbCrsBzi		// (  O) 長さ調整後の部材と交差する部材
				)
{
	MINT		ist1;
	MINT		ic1;
	MINT		iTch = 0;
	MINT		iCrs = 0;
	MgLine2D	lnBziSin1;
	MgPolyg2D	pgBzi1;
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
	MgLine2D	lnBziSin2;
	MgPolyg2D	pgBzi2;
	MINT		nT;
	MINT		iIntr;
	MgPoint2D	po;

	MINT		nBzi2En = 0;
	MINT		iHitEnMin = 0;
   
	MINT		iKaiC   = z_mnIA.GetInpKai();					// 階  	(1,2,3)
	MINT		iGpC = z_mnIA.GetKCdGp();						// 構成

	MREAL		rAMinBzi2En = MREALMAX;

	MINT		iBuzaiType = iCdBuzai / MP_BZICD_TYPE;
	if ( iCdBuzai - iBuzaiType * MP_BZICD_TYPE) iBuzaiType = -1;

	mhHaitiIn::PartsShape( pBziInfo1, &pgBzi1);					// 長さ調整部材の部材形状を求める
	// 長さ調整部材の部材形状のMIN/MAXを求める
	MgMinMaxR2D rMinMax1;
	rMinMax1.SetInit();											// 部材形状のMIN/MAXを求める
	for ( ic1=0; ic1<pgBzi1.m_n; ic1++) 
		rMinMax1.Ins2( pgBzi1.m_p[ic1]);
	BuzaiCode::MhBziSin( pBziInfo1, &lnBziSin1);				// 芯線を求める

	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		if ( pPlcEn == pBziInfo1)
			continue;											// 長さ調整部材は無視

		if ( pPlcEn->GetPIKai() != iKaiC)
			continue;											// 異なる階の部材は検索しない
		if ( pPlcEn->GetPTCdGp() != iGpC)
			continue;											// 異なる構成の部材は検索しない

		if ( !MmCheckValidParts( pPlcEn))						// オプションと履歴のチェック
			continue;

		if ( iCdBuzai) {										// 検索対象の部材コードが指定されている場合はチェックする
			if ( (pPlcEn->GetPTCdBuzai() / MP_BZICD_TYPE == iBuzaiType) ||
				(pPlcEn->GetPTCdBuzai() == iCdBuzai))
				;
			else
				continue;										// 異なる部材コードの部材は検索しない
		} 

		mhHaitiIn::PartsShape( pPlcEn,	&pgBzi2);				// 検索部材の部材形状を求める
		// 検索部材の部材形状のMIN/MAXを求める
		MgMinMaxR2D rMinMax2;
		rMinMax2.SetInit();										// 部材形状のMIN/MAXを求める
		for ( ic1=0; ic1<pgBzi2.m_n; ic1++)
			rMinMax2.Ins2( pgBzi2.m_p[ic1]);
		BuzaiCode::MhBziSin( pPlcEn, &lnBziSin2);				// 芯線を求める

		// 交差または端部接続部材を検索
		if ( MGeo::CheckMinmaxROnMinmaxR2D( rMinMax1, rMinMax2)) {		// 部材形状のMIN/MAXで重なりありかを検査する
			iIntr = MGeo::Intr2Line2D( lnBziSin2, lnBziSin1, &po);
			if ( iIntr != MC_PARALLEL) {						// 交差または接触
				nT = 0;
				for ( ic1=0; ic1<pgBzi2.m_n; ic1++) {			// 検索部部位の構成点が長さ調整部材内にある場合は接触とみなす
					if ( MGeo::CheckPointOnPolygon2DWS( pgBzi2.m_p[ic1], pgBzi1, &ist1))
						nT++;
				}
				if ( nT >= 1) {
//					MgVect2D vt0 = lnBziSin2.p[1] - lnBziSin2.p[0];
//					MgVect2D vt1 = lnBziSin1.p[0] - lnBziSin2.p[0];
//					MgVect2D vt2 = lnBziSin1.p[1] - lnBziSin2.p[0];
//					if ( MgLE( (vt1 ^ vt0) * (vt2 ^ vt0), 0)) 
						pbTchBzi[iTch++] = pPlcEn;
				} else if ( MF_CHECK_OR( iIntr, (MC_INT | MC_CONNECTION))) {
					pbCrsBzi[iCrs++] = pPlcEn;
				}
			}
		}
	}
	pbTchBzi[iTch] = NULL;
	pbCrsBzi[iCrs] = NULL;
}

/////////////////////////////////////////////////////////////////////////////
//  部材の形状を求める
void mhHaitiIn::PartsShape(
						mhPlcParts	*pPlcEn,		// 部材配置レコード
						MgPolyg2D*	pgPartsShape	// 部材形状
				)
{
	MINT		iKaiC   = z_mnIA.GetInpKai();					// 階  	(1,2,3)
	MINT		iGpC = z_mnIA.GetKCdGp();						// 構成

	MgLine2D		LnParts;
	MgPoint2D	ptPartsN;
	MINT		iKeijoF;
	MREAL		rWidthR, rWidth;
	MgVect2D		VtWidthR, VtWidth;
	MgPoint2D	ptW[2];
	MgVect2D		VtW, VtUtW;
	MgPoint2D	ptH;
	MgPoint2D	ptK[4];
	MgVect2D		vptH;
	MgVect2D		vOffset = MgVect2D( 0., 20.);
	
	MINT		ic1;

	ptW[0] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0));
	ptW[1] = *(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1));

	// 部材の形を求め検索する
	VtW = ptW[1] - ptW[0];										// 芯線
	VtUtW = MGeo::UnitizeVect2D( VtW);							// 部材の形を求める
	if ( pPlcEn->IsFrame()) {									// たて枠用の形状作成
		VtWidthR = (pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure()) * VtUtW.RotR90(); 
		VtWidth = pPlcEn->GetMbTWidth() * VtUtW.RotL90(); 
		ptH = ptW[0] + pPlcEn->GetPIPlcZure() * VtUtW;
		ptK[0] = ptH + pPlcEn->GetMbTHeightF() * VtUtW + VtWidthR;
		ptK[1] = ptH - pPlcEn->GetMbTHeightB() * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
		iKeijoF = 0;											// 形状算出済
	} else if ( pPlcEn->IsPanel() || pPlcEn->IsKaiko()) {		// パネル形状 | 開口形状
//		if ( pPlcEn->IsYukaPanel() || pPlcEn->IsTenjoPanel()) {
		if ( pPlcEn->IsYuka() || pPlcEn->IsTenjo()) {
			rWidthR = pPlcEn->GetPIMaeHosei();					// 手前側補正
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();			// 手前側補正 + 奥行き + 奥行き補正
			iKeijoF = 2;
//		} else if ( pPlcEn->IsYanePanel()) {
		} else if ( pPlcEn->IsYane()) {
			rWidthR = pPlcEn->GetPIMaeHosei();					// 手前側補正
			rWidth = pPlcEn->GetPIOkuHosei() + pPlcEn->GetPIOku() +
							   pPlcEn->GetPIMaeHosei();			// 手前側補正 + 奥行き + 奥行き補正
			iKeijoF = 2;
		} else {
			rWidthR = pPlcEn->GetMbTWidthR() + pPlcEn->GetPISinZure(); 
			rWidth = pPlcEn->GetMbTWidth(); 
			iKeijoF = 3;
		}
	} else {													// 横置部材の形状作成
		rWidthR = pPlcEn->GetMbWidthR() + pPlcEn->GetPISinZure(); 
		rWidth = pPlcEn->GetMbWidth(); 
		iKeijoF = 1;
	}

	if ( iKeijoF != 0) {										// 形状算出
		VtWidthR = rWidthR * VtUtW.RotR90(); 
		VtWidth = rWidth * VtUtW.RotL90(); 
		ptK[0] = ptW[0] - pPlcEn->GetPILenHosei( 0) * VtUtW + VtWidthR;
		ptK[1] = ptW[1] + pPlcEn->GetPILenHosei( 1) * VtUtW + VtWidthR;
		ptK[2] = ptK[1] + VtWidth;
		ptK[3] = ptK[0] + VtWidth;
	}

//L		pCod->SetLineAttr( MPS_SOLID, 1, PartsLineColor);
//		pZukei = pPlcEn->m_pZukei;
//		if ( pZukei) {											// 図形データ有りの場合は、それより検索
//			for ( ic=0; ic<pZukei->m_nZukei; ic++) {
//				pCod->Line( MgLine2DC( pZukei->m_lnZukei[ic]));
//			}
//		} else {												// 図形データなしの場合は求めた形状より検索
	pgPartsShape->m_n = 0;

	for ( ic1=0; ic1<4; ic1++) 
		(*pgPartsShape) += ptK[ic1];
//			pCod->Polygon( ptK, 4);
//		}

//		if ( pPlcEn->GetPIPartsSpec()->m_iBr == 2)
//			DrawPart( pCod, iGpC, pPlcEn);
}

/////////////////////////////////////////////////////////////////////////////
//	部材の配置点と長さ補正値を修正
void mhHaitiIn::MhModBzPH(
						MINT		iCdInpKbnCd,	// (I  ) 入力点区分コード
						MINT		iMov,			// (I  ) 修正側　(0:始点、1:終点)
				const	MgPoint3D	&PtInt,			// (I  ) 配置点
						MREAL		rLH,			// (I  ) 長さ補整値
						mhPlcParts	*pPlcEnR		// (I O) 長さ調整部材
				)
{
	mhPlcParts	*pPlcEnM;							// 長さ調整部材2

	if ( ( pPlcEnR->GetPIPlcIti( iMov) != PtInt) ||
		( !MGeo::CheckEqual(pPlcEnR->GetPILenHosei( iMov), rLH)) ||
		 pPlcEnR->GetPICdInpKbnCd() == iCdInpKbnCd) {

		HaitiDb::MdPartsModify( pPlcEnR, &pPlcEnM);
		iCdInpKbnCd = pPlcEnM->GetPICdInpKbnCd();
		if ( iCdInpKbnCd == MP_INPKB_1PT) {
			if ( iMov == 0) {
				pPlcEnM->SetPIPlcIti( 0, pPlcEnM->GetPIPlcIti(1));
			} else {
				pPlcEnM->SetPIPlcIti( iMov, PtInt);
				pPlcEnM->SetPILenHosei( iMov, rLH);
			}

		} else {
			pPlcEnM->SetPIPlcIti( iMov, PtInt);
			pPlcEnM->SetPILenHosei( iMov, rLH);
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
//	調整先が部材で示された部材の長さ調整
MINT mhHaitiIn::MhAdjBzL(							// (  O) ステイタス　
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_TWIST    (-2) 交差なし（ねじれ）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり長さ調整
						MINT		iKati,			// (I  ) 勝ち負けフラグ(1:勝ち、0:負け)
						mhPlcParts *pPlcEn1,			// (I O) 長さ調整部材1
				const	MgPoint3D	&Pt1,			// (I  ) 長さ調整指示点（部材1の残す側を示す最寄の点）
						mhPlcParts *pPlcEn2			// (I  ) 長さ調整先を示す部材2
				)
{
	MINT		ist;
	MINT		ist1, ist2;
	
	MhSenBuzai	Bz1, Bz2;
	MgPoint3D	PtInt;
	MREAL		s0, s1, s2;							// 長さ調整指示点と部材1の部材2に対する左右位置
	MINT		iMov;								// 部材1のカット端 0:配置点側 1:配置方向店側
	MgPoint3D	PtC;
	MgSLine3D	SLnBz1;								// 
	MgSLine3D	SLnBz2;
	MgPoint3D	PtI[2];
	MREAL		rLH;
	MREAL		rLnWH;

//	if ( pPlcEn1 == pPlcEn2)									// 長さ調整部材と調整先の部材が同じ場合は
//		return;													// 長さ調整対象外

	MgVect3D	VtUtZ( 0., 0., 1.);

	Bz1 = *pPlcEn1;
	Bz2 = *pPlcEn2;
	
	ist = MhSenBuzai::MhOn(  Bz1, Bz2, &PtInt, &ist1, &ist2);
	if ( ist != MC_INT && ist != MC_NINT) goto exit;			// 交差なしのため無処理
	
	iMov = ist2 - 1;
	
	s0 = (Bz2.vtUt ^ (Pt1 - Bz2.LnWH.p[0])) * VtUtZ;			// s0>0: 長さ調整指示点は長さ調整先の部材の左側
	s1 = (Bz2.vtUt ^ (Bz1.LnWH.p[0] - Bz2.LnWH.p[0])) * VtUtZ;	// s1>0: 長さ調整部材の配置点は長さ調整先の部材の左側
	s2 = (Bz2.vtUt ^ (Bz1.LnWH.p[1] - Bz2.LnWH.p[0])) * VtUtZ;	// s2>0: 長さ調整部材の配置方向点は長さ調整先の部材の左側

	if ( ist1 == MC_CLOSS) {
		if (s0 * s1 > 0) {
			iMov = 1;											// 配置方向点側の長さを補正
		} else {
			iMov = 0;											// 配置点側の長さを補正
		}
	}

	// 部材1の残す方の位置が部材２の左右どちらにあるか判定し、カット直線（調整先の勝ちまたは負け側の直線）を求める
	bool bLeft = (iMov == 1 && MGLEFT( s1) ||
				  iMov == 0 && MGLEFT( s2));					// true: 部材2の左側にあり
	if ( iKati == 1)
		bLeft = ! bLeft;										// 勝ちの場合は、左右逆にする
	if ( bLeft) {
		SLnBz2 = Bz2.SLnW[1];
	} else {
		SLnBz2 = Bz2.SLnW[0];
	}

	SLnBz1 = Bz1.SLnW[0];										// 部材1左側直線
	ist = MGeo::Intr2SLine3D( SLnBz1, SLnBz2, &PtI[0]);			// カット直線との交点
	if ( ist != MC_INT)
		goto exit;

	SLnBz1 = Bz1.SLnW[1];										// 部材1右側直線
	ist = MGeo::Intr2SLine3D( SLnBz1, SLnBz2, &PtI[1]);			// カット直線との交点
	if ( ist != MC_INT)
		goto exit;

	if ( iMov == 0) {											// 最大の長さ補正値を求める
		rLH = MGMAX( (PtI[0] - PtInt) * (- Bz1.vtUt), (PtI[1] - PtInt) * (- Bz1.vtUt));
	} else {
		rLH = MGMAX( (PtI[0] - PtInt) * (Bz1.vtUt), (PtI[1] - PtInt) * (Bz1.vtUt));
	}

	if ( MGABS( rLH) > MMAX_HOSEI_DBG)
		rLH = MMAX_HOSEI_DBG;									// デバッグ用　エラーチェックを可能にするため999をセット

	if ( Bz1.Ln.p[1 - iMov] == PtInt) {
		rLnWH = Bz1.rLH[1 - iMov] + rLH;
		if ( !MGeo::CheckZero( rLnWH))
			MhModBzPH( MP_INPKB_1PT, iMov, (MgPoint3D&)Bz1.vtUt, rLH, pPlcEn1);	// 長さ調整
	} else {
		MhModBzPH( MP_INPKB_LEN2PT, iMov, PtInt, rLH, pPlcEn1);	// 長さ調整
	}
exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	調整先が平行部材で示された部材の長さ調整
void mhHaitiIn::MhAdjBzL(							// (  O) ステイタス　
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_TWIST    (-2) 交差なし（ねじれ）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
						mhPlcParts *pPlcEn1,		// (I O) 長さ調整部材1
				const	MgPoint3D	&Pt1,			// (I  ) 部材1の長さ調整する側を示す最寄の点
						mhPlcParts *pPlcEn2,		// (I  ) 長さ調整先を示す部材2
				const	MgPoint3D	&Pt2			// (I  ) 部材2の長さ調整先を示す最寄の点
				)
{
	MhSenBuzai	Bz1, Bz2;
	MINT		iRef;

	Bz1 = *pPlcEn1;
	Bz2 = *pPlcEn2;

	if ( MGeo::Dist2Point3D( Bz2.LnWH.p[0], Pt2) < MGeo::Dist2Point3D( Bz2.LnWH.p[1], Pt2)) {
		iRef = 0;												// 調整先を部材2の配置点側とする
	} else {
		iRef = 1;												// 調整先を部材2の配置方向点側とする
	}


	MREAL		rLH;
	MREAL		rLnWH;
	MINT		iMov;

	MgPoint3D	PtIntWH;
	MgPoint3D	PtInt;
	MREAL		s1, s2;

	// 部材1の残す方の位置が部材２指定端部の前後ろどちらにあるか判定し、カット直線を求める
	MGeo::PerpLinePoint3D( Bz1.Ln, Bz2.LnWH.p[iRef], &PtIntWH);
	
	s1 = (Bz1.LnWH.p[0] - PtIntWH) * Bz1.vtUt;
	s2 = (Bz1.LnWH.p[1] - PtIntWH) * Bz1.vtUt;

	if ( s1 > 0 && s2 > 0) {									// 長さ調整部材は長さ調整先の部材の前側にあり
		if ( s1 < s2) {
			iMov = 0;											// 配置点側の長さを補正
		} else {
			iMov = 1;											// 配置方向点側の長さを補正
		}
	} else if(s1 < 0 && s2 < 0) {								// 長さ調整部材は長さ調整先の部材の後側にあり
		if ( s1 > s2) {
			iMov = 0;											// 配置点側の長さを補正
		} else {
			iMov = 1;											// 配置方向点側の長さを補正
		}
	} else {													// 長さ調整部材は長さ調整先の部材の前後にまたがってあり
		if ( MGeo::Dist2Point3D( Bz1.LnWH.p[0], Pt1) < MGeo::Dist2Point3D( Bz1.LnWH.p[1], Pt1)) {
			iMov = 0;											// 配置点側の長さを補正
		} else {
			iMov = 1;											// 配置方向点側の長さを補正
		}
	}

	MGeo::PerpLinePoint3D( Bz1.Ln, Bz2.Ln.p[iRef], &PtInt);
	rLH = Bz2.rLH[iRef];
	if (Bz1.vtUt * Bz2.vtUt > 0) {
		if ( iMov != iRef)
			rLH = -rLH;
	} else {
		if ( iMov == iRef)
			rLH = -rLH;
	}

	if (Bz1.Ln.p[1 - iMov] == PtInt) {
		rLnWH = Bz1.rLH[1 - iMov] + rLH;
		if ( !MGeo::CheckZero( rLnWH))
			MhModBzPH( MP_INPKB_1PT, iMov, (MgPoint3D&)Bz1.vtUt, rLH, pPlcEn1);	// 長さ調整
	} else {
		MhModBzPH( MP_INPKB_LEN2PT, iMov, PtInt, rLH, pPlcEn1);		// 長さ調整
	}
}

/////////////////////////////////////////////////////////////////////////////
//	調整先が点座標で示された部材の長さ調整を行う
void mhHaitiIn::MhAdjBzL(
						mhPlcParts *pPlcEn1,		// 長さ調整部材1
				const	MgPoint3D	&Pt1,			// 部材1の長さ調整する側を示す最寄の点1
				const	MgPoint3D	&Pt2			// 長さ調整先を示す点2
				)
{
	MINT		ist;
	MhSenBuzai	Bz1;
	MREAL		rLH;
	MREAL		rLnWH;
	MINT		iMov;
	MgPoint3D	PtInt;
	MREAL		s1, s2;


	Bz1 = *pPlcEn1;

	MGeo::PerpLinePoint3D( Bz1.Ln, Pt2, &PtInt);
	
	s1 = (Bz1.Ln.p[0] - PtInt) * Bz1.vtUt;
	s2 = (Bz1.Ln.p[1] - PtInt) * Bz1.vtUt;

	if ( s1 > 0 && s2 > 0) {									// 始点終点共に配置方向側なので
		iMov = 0;												// 配置点の方が近く配置点側の長さ補正を修正
	} else if(s1 < 0 && s2 < 0) {								// 始点終点共に配置点側なので
		iMov = 1;												// 配置方向点の方が近く配置方向点側の長さ補正を修正
	} else {
		if ( MGeo::Dist2Point3D( Bz1.Ln.p[0], Pt1) < MGeo::Dist2Point3D( Bz1.Ln.p[1], Pt1)) {
			iMov = 0;											// 配置点側の長さ補正
		} else {
			iMov = 1;											// 配置方向点側の長さ補正
		}
	}

	ist = z_mmIA.GetComboAttrR( MC_CMB_LHS1, &rLH);				// 長さ補正値を取得する
	if ( Bz1.Ln.p[1 - iMov] == PtInt) {
		rLnWH = Bz1.rLH[1 - iMov] + rLH;
		if ( !MGeo::CheckZero( rLnWH))
			MhModBzPH( MP_INPKB_1PT, iMov, (MgPoint3D&)Bz1.vtUt, rLH, pPlcEn1);	// 長さ調整
	} else {
		MhModBzPH( MP_INPKB_LEN2PT, iMov, PtInt, rLH, pPlcEn1);		// 長さ調整
	}
}

/////////////////////////////////////////////////////////////////////////////
//	長さ調整前後で接触状態と交差状態が変化する部材を求める
void mhHaitiIn::MhChngCrossBuzai(
						mhPlcParts	**pbTchBziI,	// (I  ) 長さ調整前に長さ調整部材に接触する部材
						mhPlcParts	**pbCrsBziI,	// (I  ) 長さ調整前に長さ調整部材と交差する部材
						mhPlcParts	**pbTchBziO,	// (I  ) 長さ調整後に長さ調整部材に接触する部材
						mhPlcParts	**pbCrsBziO,	// (I  ) 長さ調整後に長さ調整部材と交差する部材
						mhPlcParts	**pbFRtoTCBzi,	// (  O) 長さ調整前に長さ調整部材と離れていたが
													//		 長さ調整後に接触または交差した部材
						mhPlcParts	**pbTCtoFRBzi,	// (  O) 長さ調整前に長さ調整部材と接触または交差していたが
													//		 長さ調整後に離れた部材
						mhPlcParts	**pbTCtoTCBzi	// (  O) 長さ調整前に長さ調整部材に接触または交差していたが
													//		 、長さ調整後にも接触または交差している部材
				)
{
	MINT	ic0, ic1, ic2;
	mhPlcParts* TCBziI[MSZ_CROSS_BZI];
	mhPlcParts* TCBziO[MSZ_CROSS_BZI];
	MINT	if0;
//
	ic0 = 0;
	for ( ic1=0; pbTchBziI[ic1]!=NULL; ic1++)
		TCBziI[ic0++] = pbTchBziI[ic1];
	for ( ic1=0; pbCrsBziI[ic1]!=NULL; ic1++)
		TCBziI[ic0++] = pbCrsBziI[ic1];
	TCBziI[ic0] = NULL;
//
	ic0 = 0;
	for ( ic1=0; pbTchBziO[ic1]!=NULL; ic1++)
		TCBziO[ic0++] = pbTchBziO[ic1];
	for ( ic1=0; pbCrsBziO[ic1]!=NULL; ic1++)
		TCBziO[ic0++] = pbCrsBziO[ic1];
	TCBziO[ic0] = NULL;
//
	ic0 = 0;
	for ( ic1=0; TCBziO[ic1]!=NULL; ic1++) {
		if0 = 0;
		for ( ic2=0; TCBziI[ic2]!=NULL; ic2++) {
			if (TCBziI[ic2] == TCBziO[ic1]) {
				if0 = 1;
				break;
			}
		}
		if ( if0 == 1)
			continue;
		pbFRtoTCBzi[ic0++] = TCBziO[ic1];
	}
	pbFRtoTCBzi[ic0] = NULL;
//
	ic0 = 0;
	for ( ic1=0; TCBziI[ic1]!=NULL; ic1++) {
		if0 = 0;
		for ( ic2=0; TCBziO[ic2]!=NULL; ic2++) {
			if (TCBziO[ic2] == TCBziI[ic1]) {
				if0 = 1;
				break;
			}
		}
		if ( if0 == 1)
			continue;
		pbTCtoFRBzi[ic0++] = TCBziI[ic1];
	}
	pbTCtoFRBzi[ic0] = NULL;
//
	ic0 = 0;
	for ( ic1=0; TCBziO[ic1]!=NULL; ic1++) {
		for ( ic2=0; TCBziI[ic2]!=NULL; ic2++) {
			if (TCBziI[ic2] == TCBziO[ic1]) {
				pbTCtoTCBzi[ic0++] = TCBziO[ic1];
				break;
			}
		}
		if (TCBziO[ic1] == TCBziI[ic2])
			continue;
	}
	pbTCtoTCBzi[ic0] = NULL;
}

} // namespace MC
