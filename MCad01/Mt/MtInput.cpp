//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdLine.cpp
//
//		線部材の配置コマンド
//
//	[機能] 
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#define DLL_EXPORT_MC_INPUT_DO
#include "MrAPI.h"
#include "MhPlcPartsLib.h"

#define		MC_YANE_TAKASA_HOSEI 97.

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	連続した長さ２点入力用の２点目の入力(外壁入力用)

MINT mhInput::GetLenEPt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;

	Msg::GuidanceMsg( MC_GUID_SYUUTEN);
	irt = Window::DragObject(  MC_RBND_LINE, (void*)&pLn->p[0], &pt1);// ラバーバンド図形表示しながら２点目を入力
																// ドラッギングモード開始
	if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
		MQUIT;
	if ( irt == MTRT_RBTNDWN) {
//		MmWndKReDraw();
		Window::DragModeEnd();									// ドラッギングモード終了（ラバーバンド図形表示モード）
		MQUIT;
	}
	mhInput::Marume( pt1, &pt2);
	pLn->p[1] = pt2;
exit:
	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	長方形区画入力

MINT mhInput::GetRect2Pt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;
	MINT		iSeq = 0;						// 入力シークエンス

	MFOREVER {
		if ( iSeq == 0) {
			Msg::GuidanceMsg( MC_GUID_AREA_SITEN);
			irt = MtAskForPoint( &pt1);							// １点目を入力
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)		// システムストップまたはキャンセル
				break;
			if ( irt != MTRT_LBTNDWN)							// マウス左ボタンでない場合は、
				continue;										//	再入力
			mhInput::Marume( pt1, &pt2);
			pLn->p[0] = pt2;
			iSeq = 1;

		} else {												// ( iSeq == 1)
			Msg::GuidanceMsg( MC_GUID_AREA_TAIKAKUTEN);
			irt = Window::DragObject(  MC_RBND_RECT, (void*)&pLn->p[0], &pt1);	// ラバーバンド図形表示しながら対角点を入力
																// ドラッギングモード開始
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {
//				MmWndKReDraw();									// １点キャンセル
				Window::DragModeEnd();							// ドラッギングモード終了（ラバーバンド図形表示モード終了）
				iSeq = 0;
				continue;
			}
			if ( irt != MTRT_LBTNDWN)							// マウス左ボタンでない場合は、
				continue;										//	再入力
			mhInput::Marume( pt1, &pt2);
			pLn->p[1] = pt2;
			break;
		}
	}

	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	区画入力

MINT mhInput::GetArea(
						MgPolyg2D*	o_ppg1		// ２Ｄ多角形
				)
{
	MINT		irt;
	MgPolyg2D	PgS(20);
	MgPoint2D	pt1, pt2;
	MgMinMaxR2D	mMM;
	CPoint		ptMouthL;
	MINT 		iCdInpKb;
	MINT		iSeq = 0;						// 入力シークエンス

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();		// カレントウィンドウ取得
	
	iCdInpKb = z_mnIA.GetComboInpKbCd();

	MFOREVER {
		if ( iSeq == 0) {										// １点目の入力
			Msg::GuidanceMsg( MC_GUID_AREA_SITEN);
			irt = MtAskForPoint( &pt1);							// 点を入力

		} else {												// ２点目以降の入力
			iCdInpKb = z_mnIA.GetComboInpKbCd();
			if ( iCdInpKb == MP_INPKB_AREA) {
				Msg::GuidanceMsg( MC_GUID_AREA_TAIKAKUTEN);		// 対角２点タイプ区画
				irt = Window::DragObject( MC_RBND_RECT, (void*)o_ppg1->m_p, &pt1);	// ラバーバンド図形表示しながら対角点を入力
																// ドラッギングモード開始

			} else {											// 自由入力タイプ区画
				if ( iSeq == 1)
					Msg::GuidanceMsg( MC_GUID_AREA_HOUKOUTEN);	// ２点目　方向点
				else
					Msg::GuidanceMsg( MC_GUID_AREA_TUUKATEN);	// ３点目以降　通過点
				irt = Window::DragObject( MC_RBND_POLYGON, (void*)o_ppg1, &pt1);		// ラバーバンド図形表示しながら２点目以降を入力
																// ドラッギングモード開始
			}
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;												// システムストップまたはコマンドキャンセル

		if ( irt == MTRT_RBTNDWN) {								// マウス右ボタン
			if ( iSeq == 0) {									//	１点目の入力の場合は、
				iCdInpKb = MP_INPKB_AREA + MP_INPKB_FREE - iCdInpKb;//	入力点区分を自由入力→対角入力、または、対角入力→自由入力に変更
//E				z_mnIA.SelectComboInpKbnByInpKbnCd( iCdInpKb);
				z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, iCdInpKb);

			} else {											//	２点目以降の入力の場合は、
				iSeq --;										//	１点キャンセル
				( *o_ppg1) --;									//	ポリゴンの座標を１点削る
			}
			if ( o_ppg1->m_n == 0) {
				Window::DragModeEnd();							// ドラッギングモード終了（ラバーバンド図形表示モード終了）
				iSeq = 0;										// 次の入力を １点目の入力から 再開
			}
			continue;
		}
		if ( irt != MTRT_LBTNDWN)								// マウス左ボタンでない場合は、
			continue;											//	再入力

		mhInput::Marume( pt1, &pt2);								// 座標を丸める

		if ( iSeq > 1 && pt2 == o_ppg1->m_p[0]) 
			break;												// 開始点と同一位置の場合は区画入力終了とする
		if ( iSeq > 0 && pt2 == o_ppg1->m_p[iSeq-1]) { 
			;													// 最後の点と同一位置の点は捨てる
		} else {
			( *o_ppg1) += pt2;									// 異なる位置の点はポリゴンに追加する
			iSeq ++;
		}

		if ( iSeq == 2 && iCdInpKb == MP_INPKB_AREA) {
			mMM.SetInit();
			mMM.Ins2( o_ppg1->m_p[0]);
			mMM.Ins2( o_ppg1->m_p[1]);
			o_ppg1->m_p[0] = mMM.min;
			o_ppg1->m_p[1] = MgPoint2D( mMM.max.x, mMM.min.y);
			o_ppg1->m_p[2] = mMM.max;
			o_ppg1->m_p[3] = MgPoint2D( mMM.min.x, mMM.max.y);
			o_ppg1->m_n = 4;
			break;												// 対角２点の２点目の入力終了は区画入力終了とする
		}
	}
	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	長さ２点、方向１点入力 ＋　複数部材の領域をあらわす３点目の入力
//
// 配置コードが屋根構成線付け丸めの場合は、
// 最初の点の入力でマウス右ボタンまたはシフトキーが押しながらの入力は、屋根面選択で
// 屋根面を検索し屋根面が見つかれば、以降はその屋根面上の部材とみなし、
// 屋根面が見つからなければ、屋根面選択はフリーの初期状態となる
// 返値: 0: 正常
//		 1: 
MINT mhInput::GetLen2Pt(
						MINT		i_iMode,	// 入力モード
												//				　0: 長さ２点入力（複数部材の場合は、平行四辺形を表示）
												//				　1: 連続長さ２点の終点入力
												//						始点は前回入力(pLn)の終点とする
												//				　2: 方向１点入力
						MgPoint2D*	io_ptln,	// まるめ座標（長さ２点座標 ＋　複数部材の領域をあらわす３点目）
						MgPoint2D*	io_ptln_org	// オリジナル座標（長さ２点座標 ＋　複数部材の領域をあらわす３点目） 
				 )
{
	MINT		ist1;

	MINT		irt;
	MINT		iGuid;
	MINT		nflag;
	MINT		iSeq = 0;						// 入力シークエンス
	MINT		iNum;

	if ( i_iMode == 1) {										// 連続長さ２点の終点入力は
		io_ptln[0] = io_ptln[1];								//		前回入力の終点を始点とする
		iSeq = 1;
	}
	MFOREVER {
		if ( iSeq == 0) {
			// 始点入力
			if ( i_iMode == 0)
				iGuid = MC_GUID_SITEN;							// 長さ２点始点入力
			else
				iGuid = MC_GUID_HAITITEN;						// 方向２点配置点入力
            Msg::GuidanceMsg( iGuid);

			irt = MtAskForPoint( &io_ptln_org[0]);				// １点目を入力

			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)		// システムストップまたはキャンセル
				break;
			if ( z_mnIA.GetComboPlcCd() == MP_HAICD_YANEKOUSEISENZUKE) {
																// 配置コードが屋根構成線付け丸め
				nflag = MtGetNFlag();							// 仮想キー(nflag)取得（1:キー入力無し、5:shiftキー入力あり)
				if ( irt == MTRT_RBTNDWN || MF_CHECK_OR( nflag, MK_SHIFT)) {	
																// マウス右ボタンまたはシフトキーが押されている場合は屋根面を検索し
																// 屋根面が見つかれば、以降はその屋根面上の部材とみなし、
																// 屋根面が見つからなければ、初期の状態となる
					mhHaitiIn::SetCurRfm( mhHaitiIn::SrchRfm( MC_PRI_MIN_AREA, io_ptln_org[0]));
					WindowCtrl::MmWndKReDraw();
					continue;
				}
			}
			if ( irt != MTRT_LBTNDWN)							// マウス左ボタンでない場合は、
				continue;										//	再入力
			mhInput::Marume( io_ptln_org[0], &io_ptln[0]);
			iSeq = 1;

		} else if ( iSeq == 1) {
			// 終点入力
			if ( i_iMode <= 1)
				iGuid = MC_GUID_SYUUTEN;						// 長さ２点入力と連続長さ２点の終点入力
			else
				iGuid = MC_GUID_HOUKOUTEN;						// 方向２点入力の方向点入力
			Msg::GuidanceMsg( iGuid);

			irt = Window::DragObject( MC_RBND_LINE, (void*)io_ptln, &io_ptln_org[1]);
																// ラバーバンド図形表示しながら２点目を入力
																// ドラッギングモード開始
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {							// マウス右ボタン
//				MmWndKReDraw();
				Window::DragModeEnd();							//	ドラッギングモード終了（ラバーバンド図形表示モード）
					iSeq = 0;									//	長さ２点入力 または 方向１点入力の場合は１点目より再入力	
				continue;
			}
			if ( irt != MTRT_LBTNDWN)							// マウス左ボタンでない場合は、
				continue;										//	２点目を再入力
			mhInput::Marume( io_ptln_org[1], &io_ptln[1]);
			ist1 = z_mmIA.GetComboAttrI( MC_CMB_HONS, &iNum);
//S			iNum = z_mnIA.GetHonsu();							// 
			iSeq = 2;
			if ( ( i_iMode != 1) && ( iNum == MC_INT_AREA)) {	// (長さ２点入力 または 方向１点入力)　かつ　iNum == 9998: 複数部材
//S				iSeq = 2;
			} else {
				irt = 0;
				break;
			}

		} else {												// ( iSeq == 2)
			// 複数部材領域入力
			Window::EraseDragging();
			iGuid = MC_GUID_MULTI_BUZAIAREA;
			Msg::GuidanceMsg( iGuid);

			irt = Window::DragObject( MC_RBND_PARALOG, (void*)io_ptln, &io_ptln_org[2]);	// ラバーバンド図形表示しながら２点目を入力
																// ドラッギングモード開始
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {							// マウス右ボタン
				WindowCtrl::MmWndKReDraw();
				Window::DragModeEnd();								//	ドラッギングモード終了（ラバーバンド図形表示モード）
				iSeq = 1;										//	２点目より再入力する
				continue;
			}
			if (  irt != MTRT_LBTNDWN) {						// マウス左ボタンでない場合は、
				continue;										//	３点目を再入力
			}
			mhInput::Marume( io_ptln_org[2], &io_ptln[2]);
			iSeq = 3;											// ３点目入力済み
			irt = 0;
			break;
		}
	}

	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	１点入力

MINT mhInput::Get1Pt(
						MgPoint2D*	ppt1,			// (  O) 入力丸め点
						MgPoint2D*	ppt1_org		// (  O) 入力オリジナル点
				 )
{
	MINT	irt;
	MINT	iGuid;

	iGuid = MC_GUID_SITEN;
	Msg::GuidanceMsg( iGuid);

	irt = MtAskForPoint( ppt1_org);								// １点目を入力

	if ( irt != MTRT_SYSTEMSTOP && irt != MTRT_CAN) {
		mhInput::Marume( *ppt1_org, ppt1);
	}
	return irt;
}

/*
/////////////////////////////////////////////////////////////////////////////
//	長方形区画入力

MINT mhInput::GetRect2Pt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;

	MmWndInfo* pWndInfo = MmWndKGetCurWnd();					// カレントウィンドウを取得する

	do {
		Msg::GuidanceMsg( MC_GUIDMSG_KUKAKU_SITEN);
		irt = MtAskForPoint( &pt1);								// １点目を入力
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN)
			continue;
		pWndInfo->MarumeGrid( pt1, &pt2);
		pLn->p[0] = pt2;

		Msg::GuidanceMsg( MC_GUIDMSG_KUKAKU_TAIKAKUTEN);
		irt = Window::DragObject(  MC_RBND_RECT, (void*)&pLn->p[0], &pt1);	// ラバーバンド図形表示しながら２点目を入力
																// ドラッギングモード開始
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN) {
			MmWndKReDraw();										// １点キャンセル
			continue;
		}
		pWndInfo->MarumeGrid( pt1, &pt2);
		pLn->p[1] = pt2;
	} while (irt == MTRT_RBTNDWN);

	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}
*/

/////////////////////////////////////////////////////////////////////////////
//	区画入力 
//	各辺に　シフトキー有無のフラグ付き

MINT mhInput::GetAreaI(
						MgPolyg2D*	pPg1,			// (  O) 地廻り区画
						MgGInt*		pGifInp			// (  O) 地廻り線種類(仮想キー(nflag)  MK_SHIFT(004): シフトキー)
				)
{
	MINT			irt;
	MINT			ic;
	MgPolyg2D		PgS(20);
	MgPoint2D		pt1, pt2;

	MINT iCdInpKb = z_mnIA.GetComboInpKbCd();

	for ( ic=0;;ic++) {
		if ( ic == 0) {
			Msg::GuidanceMsg( MC_GUID_JIM_SITEN);
			irt = MtAskForPoint( &pt1);							// １点目を入力
		} else {
			if ( ic == 1) {
//				Msg::GuidanceMsg( MC_GUIDMSG_JIMAWARI_HOUKOUTEN);
				Msg::GuidanceMsg( MC_GUID_JIM_TUUKATEN);
			} else {
				Msg::GuidanceMsg( MC_GUID_JIM_TUUKATEN);
			}
			irt = Window::DragObject( MC_RBND_POLYGON, (void*)pPg1, &pt1);	// ラバーバンド図形表示しながら２点目以降を入力
																// ドラッギングモード開始
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;												// システムストップまたはコマンドキャンセル

		if ( irt == MTRT_RBTNDWN) {
			if ( ic > 0) {
				ic -= 2;										// １点キャンセル
				(*pGifInp) --;
				(*pPg1) --;										// ポリゴンの座標を１点削る
			} else {
				iCdInpKb = MP_INPKB_AREA + MP_INPKB_FREE - iCdInpKb;	// 区画入力 | 自由入力 | 
//E				z_mnIA.SelectComboInpKbnByInpKbnCd( iCdInpKb);
				z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, iCdInpKb);	// 入力点区分選択用のコンボボックスに表示する
			}
			if ( pPg1->m_n == 0) {
				Window::DragModeEnd();							// ドラッギングモード終了（ラバーバンド図形表示モード）
				ic = -1;										// 次の入力を IC = 0 より 再開
			}
			continue;
		}

		MINT nflag = MtGetNFlag();								// 仮想キー(nflag)を取得する（1:キー入力無し、5:shiftキー入力あり)

		mhInput::Marume( pt1, &pt2);								// 座標を丸める

		if ( ic > 1 && pt2 == pPg1->m_p[0]) {
			pGifInp->m_i[0] = nflag;
			break;												// 開始点と同一位置の場合は区画入力終了とする
		} else if ( ic > 0 && pt2 == pPg1->m_p[ic-1]) { 
			ic--;												// 最後の点と同一位置の点は捨てる
		} else {
			(*pGifInp) += nflag;
			(*pPg1) += pt2;										// 異なる位置の点はポリゴンに追加する
		}
	}
	Window::DragModeEnd();										// ドラッギングモード終了（ラバーバンド図形表示モード）
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	丸め
void mhInput::Marume(
				const	MgPoint2D	&Pi,
						MgPoint2D*	pPo
				)
{
	MINT		ist;
	MgVect2D		vtDis;
	MREAL		rDis_2;
	MINT		ic1, ic2;

	MREAL		rDisMin_2;
	MgPoint2D	Po, P0;

	MINT		iCdPlc;											// 配置コード
	MINT		iCdMarume;										// グリッド丸め分割値
	MgPoint2D	PtGrid;
	MgLine2D		Lnm[2];
	MGGLINE2( GLnk, 10);

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();		// カレントウィンドウを取得する

	MINT iKai = z_mnIA.GetInpKai();

	iCdMarume = z_mnIA.GetComboMarumeCd();
	iCdPlc = z_mnIA.GetComboPlcCd();

	if ( iCdPlc == MP_HAICD_KABESINZUKE ||
		iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {									// 壁芯付け丸め　または　屋根構成線付け丸め
		// 付近の丸め対象線分を求める
		if ( iCdPlc == MP_HAICD_KABESINZUKE) {									// 壁芯付け丸めの場合は、最寄の壁芯を求める
			mhInput::GetMarumeKabeLine( iKai, Pi, &GLnk);
		} else if ( iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {						// 屋根構成線付け丸めの場合は、最寄の屋根構成線を求める
			mhInput::MmGetMarumeYaneLine( iKai, Pi, &GLnk);
		}
		// 複数本の丸め対象線分があった場合は交点が近くにあるならその交点を返す
		rDisMin_2 = MREALMAX;
		if ( GLnk.m_n >= 2) {
			for ( ic1=0; ic1<GLnk.m_n - 1; ic1++) {
				for ( ic2=ic1+1; ic2<GLnk.m_n; ic2++) {
					ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], GLnk.m_ln[ic2], &P0);
					if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
						vtDis = P0 - Pi;
						rDis_2 =MGeo::Abs_2( vtDis);
						if ( rDis_2 < rDisMin_2) {
							rDisMin_2 = rDis_2;
							Po = P0;
						}
					}
				}
			}
		}
		if ( rDisMin_2 < MC_MARUME_TOL * MC_MARUME_TOL)
			MQUIT;
	} else {
		GLnk.m_n = 0;
	}
				
//	iCdMarume = z_mnIA.GetComboMarumeCd();

	// グリッド丸めなしの場合
	if ( iCdMarume == 0) {
		if ( GLnk.m_n == 0) {
			// 壁芯での丸めなし(または候補の壁がなし)の場合は、入力位置をそのまま返す
			*pPo = Pi;
			return;
		} else {
			// 壁芯丸めで壁との重なりありの場合は、最も近い壁芯上の位置を返す
			rDisMin_2 = MREALMAX;
			for ( ic1=0; ic1<GLnk.m_n; ic1++) {
				MGeo::PerpPtLn2( Pi, GLnk.m_ln[ic1], &P0);
				vtDis = P0 - Pi;
				rDis_2 =MGeo::Abs_2( vtDis);
				if ( rDis_2 < rDisMin_2) {
					rDisMin_2 = rDis_2;
					Po = P0;
				}
			}
	        MQUIT;
		}
	}

	// グリッド丸めありの処理
	pWndInfo->GetMarumeGridLine( iCdMarume, Pi, Lnm);
	if ( GLnk.m_n == 0) {
		// 壁芯での丸めなし(または候補の壁なし)の場合は、グリッド丸め位置をそのまま返す
		ist = MGeo::Intr2Ln2( Lnm[0], Lnm[1], pPo);
		if ( !MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
			*pPo = Pi;
		}
		return;
	} else {
		// 壁芯丸めで壁との重なりありの場合は、壁芯とグリッド線との交点で最も近い位置を返す
		rDisMin_2 = MREALMAX;
		for ( ic1=0; ic1<GLnk.m_n; ic1++) {
			for ( ic2=0; ic2<2; ic2++) {
				ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], Lnm[ic2], &P0);
				if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
					vtDis = P0 - Pi;
					rDis_2 = MGeo::Abs_2( vtDis);
					if ( rDis_2 < rDisMin_2) {
						rDisMin_2 = rDis_2;
						Po = P0;
					}
				}
			}
		}
		MQUIT;
	}
exit:
	*pPo = Po;
}

} // namespace MC