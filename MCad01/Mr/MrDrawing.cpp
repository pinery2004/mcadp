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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//  ＤＣに構造図を描く

void WindowCtrl::DrawStructure(
				MmWndInfo*	pWndInfo,							// (I  ) ウィンドウ管理情報
				msCod*		pCod
				)
{
	CDC* pDC = pCod->GetDC();

	// マップモードを設定する
	MINT iOldMM = pDC->SetMapMode(MM_HIMETRIC);

	// 図面サイズと倍率を取得する
	CSize cszB = pDC->GetWindowExt();

	// 図面枠を描く
	pDC->MoveTo( 0,			-cszB.cy);
	pDC->LineTo( cszB.cx,	-cszB.cy);
	pDC->LineTo( cszB.cx,	0);
	pDC->LineTo( 0,			0);
	pDC->LineTo( 0,			-cszB.cy);

	// 描画領域を設定する
	pCod->SetMinMaxRS( pWndInfo->GetMinMaxRS());

	MINT iLleft = 0;
	MINT iLtop = 0;
	MINT iLwidth = cszB.cx;
	MINT iLhight = -cszB.cy;
	pCod->SetWinL( iLleft, iLtop, iLwidth, iLhight);
	pCod->SetMat();

	// ＤＣに表示
	WindowCtrl::DrawGridLine( pWndInfo, pCod);
	MINT iKaiC = z_mnIA.GetInpKai();							// 現在の階
	MINT iGpC = z_mnIA.GetKCdGp();								// 現在の構成
	WindowCtrl::DrawKabeSin( pCod, iKaiC, iGpC);
	WindowCtrl::DrawKisoSin( pCod, iKaiC, iGpC);
	WindowCtrl::DrawHaitiParts( pCod, iKaiC, iGpC);
	WindowCtrl::DrawRoof( pCod, iKaiC, iGpC);
//	WindowCtrl::DrawWndTemp( pWndInfo, pCod);

	//	マップモードを戻す
	pWndInfo->m_pMemDC->SetMapMode( iOldMM);
}

} // namespace MC