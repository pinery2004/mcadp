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
#define DLL_EXPORT_MC_WINDOWCTRL_DO
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"

#include "resource.h"

#include "MdList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//  カレントのウィンドウを再表示する（メモリーＤＣに書き込み画面に表示する）
//	06/03/11　再表示後に部材長さ調整コマンドで修正先の位置を入力時に同一部材上の点を
//			　指示した時、元選択していた部材の図形が黒く表示され無いように待つように修正したが変わらず元に戻す		//IIP

MINT WindowCtrl::ReDrawWnd() 
{
	MmWndInfo* pWndInfo = WindowCtrl::GetCurWndInfo();			// カレントのウィンドウ管理情報取得
	pWndInfo->ClearMDC();
	WindowCtrl::DrawWndMDC( pWndInfo);

//	pWndInfo->GetWnd()->PostMessage(WM_PAINT);					// 再表示のメッセージを送り処理の終了を待たずに次へ移る
	pWndInfo->GetWnd()->SendMessage(WM_PAINT);					// 再表示のメッセージを送り処理の終了を待って次へ移る 060506 屋根選択後システム終了操作でハングアップ

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  全ウィンドウを再表示する（メモリーＤＣに書き込み画面に表示する）

MINT WindowCtrl::ReDrawAllWnd() 
{
	MPOSITION			WndPos;
	MmWndInfo*			pWndInfo;

	for (pWndInfo=GetHeadWnd( &WndPos); pWndInfo!=0; pWndInfo=GetNextWnd( &WndPos)) {
		pWndInfo->ClearMDC();
		if ( pWndInfo->GetWndSyu() == 5) {
																// グリッド表示数取り込み
//S1			MmWndInfo* pWndInfo1 = WindowCtrl::GetWndInfoBySyu( 1, MTHEIMENZU, 1, 1);
			MmWndInfo* pWndInfo1 = WindowCtrl::GetWndInfoBySyu( 1, MTHEIMENZU, 1);
//			MmWndInfo* pWndInfo5 = WindowCtrl::WndFind( this);
			MINT nGrid[4];
			pWndInfo1->GetGridNum( nGrid);
			pWndInfo->SetGridNum( nGrid);
			pWndInfo->SetMinMaxRS( pWndInfo->GetMinMaxGA( pWndInfo));	//	実座標(Min/Max)
			pWndInfo->SetMat();									// 座標変換用マトリックスの設定
		}
		WindowCtrl::DrawWndMDC( pWndInfo);
		pWndInfo->GetWnd()->PostMessage(WM_PAINT);				// 再表示のメッセージを送り処理の終了を待たずに次へ移る
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  ウィンドウを表示する（メモリーＤＣの内容を画面に表示する）

MINT WindowCtrl::DrawWnd( 
						MmWndInfo*	i_pWndInfo	// ウィンドウ管理情報
				) 
{
	MINT			ist = 1;
	CDC*			pMemDC;						// メモリsgＤＣ
	MINT			iStX;						// ウィンドウの始点Ｘ座標
	MINT			iStY;						// ウィンドウの始点Ｙ座標
	MINT			iWidth;						// ウィンドウの幅
	MINT			iHeight;					// ウィンドウの高さ
//	MINT			ItrSts;
//HHHH
//	ItrSts = HmClrCursorRubber(ViewId);							// ﾏｰｶとﾗﾊﾞｰﾊﾞﾝﾄﾞをｸﾘｱ

	if ( i_pWndInfo != 0) {
		CClientDC		dc( i_pWndInfo->GetWnd());
		MINT iMapMode = i_pWndInfo->GetMapMode();
		MINT iOldMM = dc.SetMapMode( iMapMode);

		i_pWndInfo->GetWinL( &iStX, &iStY, &iWidth, &iHeight);
		pMemDC = i_pWndInfo->GetMemDC();

		dc.BitBlt( iStX, iStY, iWidth, iHeight, pMemDC, 0, 0,SRCCOPY);

		dc.SetMapMode( iOldMM);
		ist = 0;
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//  ウィンドウイメージメモリＤＣに組図を表示

void WindowCtrl::DrawWndMDC(					// ステイタス　0:正常  1:エラー
						MmWndInfo*	i_pWndInfo	// ウィンドウ管理情報
				)
{
	i_pWndInfo->AsignMDC();										// メモリＤＣが割り当ててなければ割り当てる
	i_pWndInfo->ClearMDC();										// 画面を背景色で塗りつぶしクリア

	msCod*	pCod = i_pWndInfo;

	//	マップモードを設定
	MINT iOldMM = i_pWndInfo->SetMapMode( NULL);

	//	メモリーＤＣに表示
	WindowCtrl::DrawGridLine( i_pWndInfo, pCod);
	MINT iKaiC = z_mnIA.GetInpKai();							// 現在の階
	MINT iGpC = z_mnIA.GetKCdGp();								// 現在の構成
	WindowCtrl::DrawKabeSin( pCod, iKaiC, iGpC);
	WindowCtrl::DrawKisoSin( pCod, iKaiC, iGpC);
	WindowCtrl::DrawHaitiParts( pCod, iKaiC, iGpC);
	WindowCtrl::DrawRoof( pCod, iKaiC, iGpC);
	WindowCtrl::DrawWndTemp( i_pWndInfo, pCod);

	//	マップモードを戻す
	i_pWndInfo->m_pMemDC->SetMapMode( iOldMM);
}

/////////////////////////////////////////////////////////////////////////////
//	グリッドを表示する
void WindowCtrl::DrawGridLine(
						MmWndInfo*	i_pWndInfo,	// ウィンドウ管理情報
						msCod*		pCod
				)
{
	i_pWndInfo->DrawGrid( i_pWndInfo, pCod);
}

} // namespace MC
