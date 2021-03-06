//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmTenkai.cpp
//
//		住棟展開
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
#include "..\\MCAD\\resource.h"

#define DLL_EXPORT_TENKAI_DO
#include "MmTenkai.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MdLib.h"

#include "MhInpPlcParts.h"
#include "MhPlcPartsLib.h"

namespace MC
{

//static	CMmDialogTenkai* z_pDlgTenkai = NULL;	// モードレスバージョンダイアログの表示用
JTTenkaiPr 	JTTenkai::z_TenkaiPara;				// 住棟展開パラメータ
MgMat2E	JTTenkai::z_matTenkai[MX_NJUKO];	// 住棟展開マトリックス
MgMat2E	JTTenkai::z_matRTenkai[MX_NJUKO];	// 住棟展開逆マトリックス
MgMinMaxR2D	JTTenkai::z_mmTenkai[MX_NJUKO];		// 住戸領域ＭｉｎＭａｘ
MINT		JTTenkai::z_iJuko;					// 選択住戸
MUINT		JTTenkai::z_iTenkai[MX_NJUKO];		// 住棟展開制御
/*
	JTTenkaiPr

	MUCHAR nJuko;								// 住戸数
	MUCHAR ifH[MX_NJUKO];						// 0: コピー、1: 反転コピー
	MUCHAR nJuko[MX_NJUKO];						// 展開元住戸
	MREAL rMDJuko[MX_NJUKO];					// 縦方向オフセット
	MREAL rDJuko[MX_NJUKO];						// 住戸奥行
	MREAL rWJuko[MX_NJUKO];						// 住戸巾
*/
/////////////////////////////////////////////////////////////////////////////
//【機能】住棟展開情報を初期化する
void JTTenkai::InitJTT()
{
	MINT ifH = 0;
	for (MINT ic=0; ic<MX_NJUKO; ic++) {
//		z_TenkaiPara.iSelJuko = z_TenkaiPara.iRefJuko = 1;
		z_TenkaiPara.ifH[ic] = ifH;
		ifH = 1 - ifH;
		z_TenkaiPara.nOJuko[ic] = 2;
		z_TenkaiPara.rMDJuko[ic] = 0;
		z_TenkaiPara.rDJuko[ic] = 10920;
		z_TenkaiPara.rWJuko[ic] = 7280;
	}
	z_TenkaiPara.nOJuko[0] = 1;
	z_TenkaiPara.nJuko = 4;
	z_iJuko = 0;								// 共有部選択（住戸選択なし）に設定
}
/*
/////////////////////////////////////////////////////////////////////////////
//	住棟展開設定入力
void JTTenkai::InpJTT(
						CWnd*		pWnd		// (I  ) ウィンドウのインスタンス
				)
{
	if ( z_pDlgTenkai) {
		z_pDlgTenkai->BringWindowToTop();
	} else {
		z_pDlgTenkai = new CMmDialogTenkai( pWnd);
	}
}

/////////////////////////////////////////////////////////////////////////////
//	住棟展開設定終了
void JTTenkai::EndJTT()
{
	z_pDlgTenkai = NULL;
}
*/
/////////////////////////////////////////////////////////////////////////////
//	住戸区画の創成
void JTTenkai::CreJTTArea()
{
	MINT	ist1;
	MgLine3D Ln1;
	mhPlcParts*	pHaiTenkai[MX_NJUKO];							// 住棟展開データ
	MPOSITION	pPlcPos[MX_NJUKO];								// 住戸住棟展開データレコード位置
	MgPolyg2D	pg1(4);

	ist1 = mhHaitiIn::GetParts( 0, MP_GP_KABE, Mstr( "住棟展開"), NULL, 3, pHaiTenkai, pPlcPos);
	ASSERT( ist1 >= 0);											// 住棟展開データ　オーバフロー　<ERROR>
	if ( ist1 == 1)
		HaitiDb::MdPartsDelete( pPlcPos[0]);					// 住棟展開データを削除

	ist1 = mhHaitiIn::GetParts( 0, MP_GP_KABE, Mstr( "住戸区画"), NULL, MX_NJUKO, pHaiTenkai, pPlcPos);
	ASSERT( ist1 >= 0);											// 住戸区画データ　オーバフロー　<ERROR>
	for (MINT ic=0; ic<ist1; ic++) {
		HaitiDb::MdPartsDelete( pPlcPos[ic]);					// 住戸区画データを削除
	}

	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_KABE, MP_BR_OTHER, Mstr( "住戸区画"));
																								//E	z_mnIA.GetComboAttrAXqt();
																								//SS	z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);					// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
	z_mmIA.GetComboAttrAEntry();								// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む

	MgPoint2D	ptJuko[2] = { MgPoint2D( 0., 0.), MgPoint2D( 0., 0.)};
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for (MINT ic=0; ic<z_TenkaiPara.nJuko; ic++) {
		pg1.m_n = 0;
		ptJuko[0] = MgPoint2D( ptJuko[1].x, z_TenkaiPara.rMDJuko[ic]);
		ptJuko[1] = MgPoint2D( ptJuko[0].x + z_TenkaiPara.rWJuko[ic], 
							  z_TenkaiPara.rMDJuko[ic] + z_TenkaiPara.rDJuko[ic]);

		pg1 += ptJuko[0];
		pg1 += MgPoint2D( ptJuko[1].x, ptJuko[0].y);
		pg1 += ptJuko[1];
		pg1 += MgPoint2D( ptJuko[0].x, ptJuko[1].y);

		Ln1.p[0] = MgPoint3DC( pg1.m_p[0]);
		Ln1.p[1] = MgPoint3DC( pg1.m_p[1]);
		HaitiCmd::MmPartsPlc( Ln1.p, MgVect3D( 0., 0., 1.), &pg1);		// 住戸区画（領域型）の部品配置

		mm.Ins2( ptJuko[0]);
		mm.Ins2( ptJuko[1]);
	}
	mm.Ins2( MgPoint2D( 0., 0.));

	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_KABE, MP_BR_OTHER, Mstr( "住棟展開"));
																								//E	z_mnIA.GetComboAttrAXqt();
																								//SS	z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);							// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
	z_mmIA.GetComboAttrAEntry();										// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む

	pg1.m_n = 0;
	pg1 += mm.min;
	pg1 += MgPoint2D( mm.max.x, mm.min.y);
	pg1 += mm.max;
	pg1 += MgPoint2D( mm.min.x, mm.max.y);

	JTTenkaiPr* pAuxTenkai = (JTTenkaiPr*)new char[sizeof( JTTenkaiPr)];
	*pAuxTenkai = z_TenkaiPara;
//	mhPlcParts* pInfo = &g_hInpPIAttr;
	mtPlcInp::SetpAuxTenkai( pAuxTenkai);

	Ln1.p[0] = MgPoint3DC( pg1.m_p[0]);
	Ln1.p[1] = MgPoint3DC( pg1.m_p[1]);
	HaitiCmd::MmPartsPlc( Ln1.p, MgVect3D( 0., 0., 1.), &pg1);			// 住棟展開（領域型）の部品配置

	z_mnIA.SetInpKai( 1);
	mtPlcInp::SetInpKai( 1);
	MINT nGrid[4];
	nGrid[1] = MINT(mm.min.x / mcs::GetReal( MM_REAL_PITCH) - 3.99);							// 西
	nGrid[2] = MINT(mm.min.y / mcs::GetReal( MM_REAL_PITCH) - 2.34 - z_TenkaiPara.nJuko /3.);	// 南
	nGrid[3] = MINT(mm.max.x / mcs::GetReal( MM_REAL_PITCH) + 3.99);							// 東
	nGrid[0] = MINT(mm.max.y / mcs::GetReal( MM_REAL_PITCH) + 1.99 + z_TenkaiPara.nJuko);		// 北

	GridDispCtrl::SetGridNum( nGrid);									// 初期設定
	GridDispCtrl::XqtGridNum();											// グリッド数変更表示
}

/////////////////////////////////////////////////////////////////////////////
//	住棟展開マトリックスを設定する
void JTTenkai::SetJTTMAT()
{
	MINT	ic;
	MgMat2E matSt;

	matSt.SetUnit();

	for ( ic=0; ic<z_TenkaiPara.nJuko; ic++) {
		z_matTenkai[ic] = matSt;
		z_mmTenkai[ic].min = MgPoint2D( matSt.m[2][0], z_TenkaiPara.rMDJuko[ic]);

		matSt.m[2][0] += z_TenkaiPara.rWJuko[ic];
		z_mmTenkai[ic].max = MgPoint2D( matSt.m[2][0], z_mmTenkai[ic].min.y + z_TenkaiPara.rDJuko[ic]);

		if ( z_TenkaiPara.ifH[ic]) {
			z_matTenkai[ic].m[0][0] = -1.;
			z_matTenkai[ic].m[2][0] = matSt.m[2][0];
		}
		z_matTenkai[ic].m[1][2] = z_TenkaiPara.rMDJuko[ic];

		z_matRTenkai[ic] = z_matTenkai[ic];
		z_matRTenkai[ic].m[2][0] = - z_matTenkai[ic].m[2][0];
		z_matRTenkai[ic].m[2][1] = - z_matTenkai[ic].m[2][1];
	}
	for ( ic=0; ic<MX_NJUKO; ic++)
		z_iTenkai[ic] = 0;
	for ( ic=0; ic<z_TenkaiPara.nJuko; ic++)
		z_iTenkai[ic] = z_iTenkai[z_TenkaiPara.nOJuko[ic]-1] | (1 << ic);
}

/////////////////////////////////////////////////////////////////////////////
//	住棟展開パラメータを取得する
JTTenkaiPr* JTTenkai::GetJTTPara()
{
	return &z_TenkaiPara;
}

/////////////////////////////////////////////////////////////////////////////
//	住棟展開パラメータを設定する
void JTTenkai::SetJTTPara(
						JTTenkaiPr* pAuxTenkai		// (I  ) 住棟展開パラメータ
				)
{
	z_TenkaiPara = *pAuxTenkai;
	JTTenkai::SetJTTMAT();
}

/////////////////////////////////////////////////////////////////////////////
//	住戸選択する
void JTTenkai::SetJTTJuuko(
						MINT iJuko					// (I  ) 選択住戸番号　または　0
				)
{
	z_iJuko = iJuko;
}

} // namespace MC
