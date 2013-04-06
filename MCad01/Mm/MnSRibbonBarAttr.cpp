//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarAttr.cpp
//
//		
//	属性入力リボンバー
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
//#define	 WINVER	0x0400
#include <afxwin.h>         // MFC のコアおよび標準コンポーネント

#include "MsMCAD.h"
#include "MainFrm.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MmWnd.h"
#include "MhInp.h"
#include "resource.h"
#include "..\\MCAD\\resource.h"
#include "MhPlcInfo.h"
#include "MhLib.h"
#include "MgGeo.h"

#define MC_SZ_CMBATTR	6
#define MC_SZ_CHKATTR	4

namespace MC
{

static MINT z_IdcComboAttr[6] =		{ IDC_CMB_ATTR1, IDC_CMB_ATTR2, IDC_CMB_ATTR3,
									  IDC_CMB_ATTR4, IDC_CMB_ATTR5, IDC_CMB_ATTR6};
static MINT z_IdcStaticAttr[6] =	{ IDC_CMB_ATTR1, IDC_CMB_ATTR2, IDC_CMB_ATTR3,
									  IDC_CMB_ATTR4, IDC_CMB_ATTR5, IDC_CMB_ATTR6};
static MINT z_IdcCheckAttr[4] =		{ IDC_CHECKATTR1, IDC_CHECKATTR2,
									  IDC_CHECKATTR3, IDC_CHECKATTR4};

static MINT z_Combo_Attr[MC_SZ_CMBATTR];
static MINT z_Check_Attr[MC_SZ_CHKATTR];

//===========================================================================
//				初期化用スタティックデータ
//
//===========================================================================

static void MnsInitComboAttr( MCCMBATTR, MCCMBATTR, MCCMBATTR, MCCMBATTR, MCCMBATTR,
							  MCCMBATTR, MCCHKATTR, MCCHKATTR, MCCHKATTR, MCCHKATTR);

// ======== 部材用 ========

// 長さ補正値
static MREAL z_rLngH[] = {  95.5,  82.5,  70.0,  57.5,   44.5,  38.0, 
							32.0,   6.5,   0.0, -18.5,  -19.0, -31.5,
						   -38.0, -44.0, -44.5, -57.0,  -69.5, -70.0,
						   -82.5, -95.0, -95.5, -114.0};
#define	ISZLNGH		sizeof(z_rLngH)/sizeof(MREAL)
#define	INITLNGTH	0.0f

// 材軸芯ずれ量
static MREAL z_rSinZ[] = {  76.5,   76.0,  63.5,  57.0,  53.5,  51.0,
							38.5,  38.0,  25.5,  19.0,  13.0,  12.5,
							 0.5,   0.0, -12.5,  -19.0, -25.0, -25.5,
						   -38.0, -50.5, -53.5, -57.0, -63.5, -95.0};
#define	ISZSINZ		sizeof(z_rSinZ)/sizeof(MREAL)
#define	INITSINZ	0.0f

// 配置点ずれ量
static MREAL z_rHaiZ[] = { 152.5, 127.0,  114.5,  101.5,  95.5,  89.0,
							76.5,  70.0,   63.5,   57.0,  51.0,  44.5,
							38.5,  25.5,   19.0,   13.0,   0.5,   0.0,
						   -12.5, -19.0,  -25.0,  -50.5, -57.0, -95.0};
#define	ISZHAIZ	sizeof(z_rHaiZ)/sizeof(MREAL)
#define	INITHAIZ	0.0f

// 取り付け高さ
static MREAL z_rZ1[] = { 2250.0, 2150.0, 2095.0, 2067.0, 2057.0, 2055.0,
						 2050.0, 2010.0, 1950.0, 1850.0, 1810.0, 1750.0,
						 1650.0, 1550.0, 1450.0, 1350.0, 1250.0, 1150.0,
						 1050.0, 950.0, 850.0, 600.0, 0.0};
#define	ISZZ1		sizeof(z_rZ1)/sizeof(MREAL)
#define	INITZ1		0.0f

// ＲＯＨ
static MREAL z_rZ2[] = { 2250.0, 2150.0, 2095.0, 2067.0, 2055.0, 2050.0,
						 2010.0, 1950.0, 1850.0, 1550.0, 1545.0, 1450.0,
						 1400.0, 1350.0, 1245.0, 1000.0,  900.0,  750.0,
						  600.0, 0.0};
#define	ISZZ2		sizeof(z_rZ2)/sizeof(MREAL)
#define	INITZ2		0.0f

// 間隔
static MREAL z_rIntv[] = { 1820.0, 1368.0, 910.0, 455.0, 303.0, 227.5};
#define	ISZINTV		sizeof(z_rIntv)/sizeof(MREAL)
#define	INITINTV	455.0f

// 本数
static MINT	  z_iNum[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 
						   10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 9998};
#define	ISZNUM		sizeof(z_iNum)/SZMINT()
#define	INITNUM		1

// ======== パネル用 ========

// パネル幅補正値
static MREAL z_rLngH2[] = { 9999.0,  95.5,  70.0,  53.0,  44.5,  0.0,
							 -44.5, -53.0, -70.0, -95.5};
#define	ISZLNGH2	sizeof(z_rLngH2)/sizeof(MREAL)
#define	INITLNGTH2	0.0f

// 手前側補正値、奥行き補正値
static MREAL z_rOkuH[] = { 9999.0,	 95.5,	70.0,  53.0,  44.5,  0.0,
							-44.5,  -53.0, -70.0, -95.5};
#define	ISZOKUYUKIH	sizeof(z_rOkuH)/sizeof(MREAL)
#define	INITOKUYUKIH	0.0f

// 奥行き
static MREAL z_rOku[] = {	7280.0, 6825.0, 6370.0, 5915.0, 5460.0, 5005.0, 
							4550.0, 4095.0, 3640.0, 3185.0, 2730.0, 2275.0,
							1820.0, 1365.0,  910.0,  455.0, 9999.0};
#define	ISZOKUYUKI	sizeof(z_rOku)/sizeof(MREAL)
#define	INITOKUYUKI		3640.0f

// 屋根勾配
static MINT z_iKoubai[] = {	12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
#define	ISZKOUBAI	sizeof(z_iKoubai)/SZMINT()
#define	INITKOUBAI		4

// 軒の出
static MREAL z_rNokinoDe[] = {	650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZNOKINODE	sizeof(z_rNokinoDe)/sizeof(MREAL)
#define	INITNOKINODE		650.0f

// ケラバの出
static MREAL z_rKerabanoDe[] = { 650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZKERABANODE	sizeof(z_rKerabanoDe)/sizeof(MREAL)
#define	INITKERABANODE	650.0f

////////////////////////////////////////////////////////////////////////////
//	部材属性入力用コンボボックスの設定

void mnInpAttr::SetComboParts()
{
	//	部品選択用コンポボックスの項目を設定する
	InitComboPartsTp();

	//	寸法型式選択用コンポボックスの項目を設定する
	InitComboPartsMbr();

	//	パネル番号選択用コンポボックスの項目を設定する
	InitComboPanelNo();

	//	部材属性入力用コンポボックスの項目を設定する
	InitComboAttr();

	Window::CurWndFocus();
	WindowCtrl::MmWndKReDraw();
}

//////////////////////////////////////////////////////////////////////////////
// 属性入力用コンボボックスを取得する
CMFCRibbonComboBox* mnInpAttr::MnpComboAttr(
						MINT	iAttr				// (I  ) コンボボックス番号
				)
{
	return DYNAMIC_DOWNCAST(CMFCRibbonComboBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcStaticAttr[iAttr - 1]));
}

//////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックス番号を取得する

MINT mnInpAttr::GetComboAttrNo(
						MCCMBATTR	iAttr			// (I  ) 属性ID
				)
{
	MINT	ic;
	MINT	iCmbNo = 0;

	for ( ic=0; ic<MC_SZ_CMBATTR; ic++)
		if ( iAttr == z_Combo_Attr[ic])
			break;
	if ( ic < MC_SZ_CMBATTR)
		iCmbNo = ic + 1;
	return iCmbNo;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスのタイトルを設定する
void mnInpAttr::SetComboAttrText(
						MINT	iAttr,				// (I  ) コンボボックス番号
						MCHAR*	sTitle				// (I  ) タイトル
				)
{
	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);
	pCmbBox->SetText( sTitle);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに実数値を表示する

void mnInpAttr::SetComboAttrRCbn(
						MINT	iAttr,				// (I  ) コンボボックス番号
						MREAL	rValue				// (I  ) 表示する実数値
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7.1f"), rValue);

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);
	pCmbBox->SetToolTipText( strValue);
}

//////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに実数値を表示する

void mnInpAttr::SetComboAttrR(
						MCCMBATTR	iAttr,			// (I  ) 属性ID
						MREAL		rValue			// (I  ) 表示する実数値
				)
{
	MINT iCmbNo = GetComboAttrNo( iAttr);
	if ( iCmbNo != 0)
		SetComboAttrRCbn( iCmbNo, rValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンポボックスに実数値の項目(一覧)を設定する

void mnInpAttr::InitComboAttrR(
						MINT	iAttr,				// (I  ) コンボボックス番号
						MINT	nComboAttr,			// (I  ) 選択属性値の数
						MREAL	*rComboAttr,		// (I  ) 選択属性値
						MREAL	rInitValue			// (I  ) 初期表示する属性値
				)
{
	int		ist;
	int		ic1;
	int		ip = 0;
	CString	sKomoku;

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);

	pCmbBox->RemoveAllItems();

	// 選択属性値設定
	for ( ic1=0; ic1<nComboAttr; ic1++) {
		ASSERT( ip < MX_CMB_ATTR - 1);						// 属性値選択コンボボックス項目　オーバフロー　<ERROR>
//		if ( MgEqual( rComboAttr[ic1], 9999.0))
//			sKomoku = "自動";
		if ( MGeo::Equal( rComboAttr[ic1], MREAL( MC_INT_JIDO)))
			sKomoku = MC_STR_JIDO;
		else
			sKomoku.Format(Mstr( "  %6.1f"), rComboAttr[ic1]);
		ist = pCmbBox->AddItem( sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	} else {
		SetComboAttrRCbn( iAttr, rInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの実数値を取得する
//
MREAL mnInpAttr::GetComboAttrRCbn(						// (  O) 実数値　または　0(未設定)
						MINT	iAttr				// (I  ) コンボボックス番号
				)
{
	CString strValue;

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);
	strValue = pCmbBox->GetText();

	return MsGetMREAL( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの実数値を取得する

MINT mnInpAttr::GetComboAttrR(						// (  O) ステイタス0(未設定) 1(設定)
						MCCMBATTR	iAttr,			// (I  ) 属性ID
						MREAL		*rValue			// (  O) 実数値
				)
{
	MINT	ist;
	MINT	iCmbNo;

	iCmbNo = GetComboAttrNo( iAttr);

	if ( iCmbNo != 0) {
		*rValue = GetComboAttrRCbn( iCmbNo);
		ist = 1;
	} else {
		*rValue = 0.;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに整数値を表示する

void mnInpAttr::SetComboAttrICbn(
						MINT	iAttr,				// (I  ) コンボボックス番号
						MINT	iValue 				// (I  ) 表示する整数値
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7d"), iValue);

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);
	pCmbBox->SetToolTipText( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに整数値を表示する

void mnInpAttr::SetComboAttrI(
						MCCMBATTR	iAttr,			// (I  ) 属性ID
						MINT		iValue 			// (I  ) 表示する整数値
				)
{
	MINT iCmbNo = GetComboAttrNo( iAttr);
	if ( iCmbNo != 0)
		SetComboAttrICbn( iCmbNo, iValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用指定コンポボックスに整数値の項目(一覧)を設定する

void mnInpAttr::InitComboAttrI(
						MINT	iAttr,				// (I  ) コンボボックス番号
						MINT	nComboAttr,			// (I  ) 選択属性値の数
						MINT	*iCmbAttr,			// (I  ) 選択属性値
						MINT	iInitValue			// (I  ) 初期表示する属性値
				)
{
	int		ist;
	int		ic1;
	int		ip = 0;
	CString	sKomoku;

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);

	pCmbBox->RemoveAllItems();

	for ( ic1=0; ic1<nComboAttr; ic1++) {
		ASSERT( ip < MX_CMB_ATTR - 1);							// 開口部高さ選択コンボボックス項目　オーバフロー　<ERROR>
		if ( iCmbAttr[ic1] == MC_INT_JIDO)
			sKomoku = MC_STR_JIDO;								// 自動
		if ( iCmbAttr[ic1] == MC_INT_AREA)
			sKomoku = MC_STR_AREA;								// 領域
		else
			sKomoku.Format(Mstr( "  %6d"), iCmbAttr[ic1]);
		ist = pCmbBox->AddItem( sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->AddItem( Mstr( "none"));
	} else {
		SetComboAttrICbn( iAttr, iInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの整数値を取得する
//
MINT mnInpAttr::GetComboAttrICbn(						// (  O) 整数値　または　0(未設定)
						MINT	iAttr				// (I  ) コンボボックス番号
					)
{
	CString strValue;
	MINT	iNum;

	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);
	strValue = pCmbBox->GetText();

	if ( Mstrcmp( strValue, MC_STR_JIDO) == 0)					// 自動
		iNum = MC_INT_JIDO;										// 9999
	else if ( Mstrcmp( strValue, MC_STR_AREA) == 0)				// 領域
		iNum = MC_INT_AREA;										// 9998
	else
		iNum =  MsGetMINT( strValue);
		
	return iNum;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの整数値を取得する

MINT mnInpAttr::GetComboAttrI(						// (  O) ステイタス0(未設定) 1(設定)
						MCCMBATTR	iAttr,			// (I  ) 属性ID
						MINT		*iValue 		// (  O) 表示する整数値
					)
{
	MINT	ist;
	MINT	iCmbNo;

	ist = 0;
	iCmbNo = GetComboAttrNo( iAttr);

	if ( iCmbNo != 0) {
		*iValue = GetComboAttrICbn( iCmbNo);
		ist = 1;
	} else {
		*iValue = 0;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの値を取り込む

void mnInpAttr::GetComboAttrA( void)
{
	MINT	ist;

	MREAL	rComboAttr1;
	MREAL	rComboAttr2;
	MREAL	rComboAttr3;
	MREAL	rComboAttr4;
	MREAL	rComboAttr5;
	MREAL	rComboAttr6;

	MINT	iMode = z_mn.GetAtMd();						// 属性値入力モード

	switch ( iMode)
	{
	case MP_AT_YTPANEL:
	case MP_AT_YANEPANEL:

		if ( iMode == MP_AT_YTPANEL) {							// ***** 床・天井パネル *****
			z_mn.GetComboAttrR( MC_CMB_LFH1, &rComboAttr1);		// 　左巾補正値　→　長さ補正値1
			z_mn.GetComboAttrR( MC_CMB_RTH1, &rComboAttr2);		// 　右巾補正値　→　長さ補正値2
			z_mn.GetComboAttrR( MC_CMB_FHS1, &rComboAttr3);		// 　手前側補正値　→　手前側補正値

		} else if ( iMode == MP_AT_YANEPANEL) {					// ***** 屋根パネル *****
			z_mn.GetComboAttrR( MC_CMB_LFH2, &rComboAttr1);		// 　左巾補正値　→　長さ補正値1
			z_mn.GetComboAttrR( MC_CMB_RTH2, &rComboAttr2);		// 　右巾補正値　→　長さ補正値2
			z_mn.GetComboAttrR( MC_CMB_FHS2, &rComboAttr3);		// 　軒の出　→　手前側補正値
		}

		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// →　長さ補正値1
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// →　長さ補正値2
		mtPlcInp::SetMaeHosei( rComboAttr3);					// →　手前側補正値

		z_mn.GetComboAttrR( MC_CMB_OKYK, &rComboAttr4);
		mtPlcInp::SetOku( rComboAttr4);							// 奥行き　→　奥行き

		z_mn.GetComboAttrR( MC_CMB_OHS2, &rComboAttr5);
		mtPlcInp::SetOkuHosei( rComboAttr5);					// 奥行き補正値　→　奥行き補正値　

		z_mn.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);
		mtPlcInp::SetHgt( 0, rComboAttr5);						// 取り付け高さ　→　取り付け高さ 
		break;

	case MP_AT_HRZ_PARTS:
	case MP_AT_VRT_PARTS:
	case MP_AT_TATEGU:
																// ***** 横置き部材・縦置き部材・建具 *****
		z_mn.GetComboAttrR( MC_CMB_LHS1, &rComboAttr1);
		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// 長さ補正値1 　→　長さ補正値1

		z_mn.GetComboAttrR( MC_CMB_LHS2, &rComboAttr2);
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// 長さ補正値2 　→　長さ補正値2

		z_mn.GetComboAttrR( MC_CMB_ZJSZ, &rComboAttr3);
		mtPlcInp::SetSinZure( rComboAttr3);						// 材軸芯ずれ量　→　材軸芯ずれ量

		z_mn.GetComboAttrR( MC_CMB_HAIZ, &rComboAttr4);
		mtPlcInp::SetPlcZure( rComboAttr4);						// 配置点ずれ量　→　配置点ずれ量

		ist = z_mn.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);		// 取り付け高さ　→　高さ1
		if ( ist == 0)
			ist = z_mn.GetComboAttrR( MC_CMB_LWRH, &rComboAttr5);	// 下端高さ　→　高さ1

		mtPlcInp::SetHgt( 0, rComboAttr5);						// →　高さ1
		mtTateguInp::SetHeight( rComboAttr5);					// →　建具高さ

		ist = z_mn.GetComboAttrR( MC_CMB_KROH, &rComboAttr6);		// 建具ROH　→　高さ2
		if ( ist ==0)
			ist = z_mn.GetComboAttrR( MC_CMB_UPRH, &rComboAttr6);	// 上端高さ　→　高さ2

		mtPlcInp::SetHgt( 1, rComboAttr6);						// →　高さ2
		mtTateguInp::SetROH( rComboAttr6);						// →　建具ROH

//		iIdPartsTp = z_mn.GetCurIdPartsTp();						// カレントの部品ID
//		pPartsTp = BuzaiCode::MhGetpPartsTp( iIdPartsTp);				// 部品種類レコード
//		if ( pPartsTp->IsTategu()) {								// 建具 (部材コード = 建具)
//		}
		break;

	case MP_AT_ADJLNG:											// ***** 部材長さ調整入力 *****
	case MP_AT_YANE:											// ***** 屋根入力 *****

		ASSERT(false);											// エラー
		break;
	}

}

//////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックス番号を取得する

MINT mnInpAttr::GetCheckAttrNo(
						MCCHKATTR	iAttr			// (I  ) 属性ID
				)
{
	MINT ic;
	MINT iChkNo = 0;

	for ( ic=0; ic<MC_SZ_CHKATTR; ic++) {
		if ( iAttr == z_Check_Attr[ic])
			break;
	}
	if ( ic < MC_SZ_CHKATTR)
		iChkNo = ic + 1;
	return iChkNo;
}


///////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックスのタイトルを設定する
void mnInpAttr::SetCheckAttrText(
						MINT	iAttr,				// (I  ) チェックボックス番号
						MCHAR*	sTitle				// (I  ) タイトル　または　NULL:チェックボックスを表示しない
				)
{
	CMFCRibbonComboBox *pCmbBox = MnpComboAttr( iAttr);

	if ( sTitle) {
		pCmbBox->SetToolTipText( sTitle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックスのチェックマークを設定する

void mnInpAttr::SetCheckAttrCkb(
						MINT	iChkNo,				// (I  ) チェックボックス番号
						MINT	iCheckAttr			// (I  ) チェックマーク　0:OFF, 1:ON
				)
{
//U	CButton* pCheckAttr;
//U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[iChkNo - 1]));
//U	pCheckAttr->SetCheck( iCheckAttr);
}

///////////////////////////////////////////////////////////////////////////////
//	チェックボックスのチェックマークを設定する

void mnInpAttr::SetCheckAttr(
						MCCHKATTR	iAttr,			// (I  ) 属性ID
						MINT		iCheckAttr		// (I  ) チェックマーク　0:OFF, 1:ON
				)
{
	MINT iChkNo = GetCheckAttrNo( iAttr);
	if ( iChkNo != 0)
		SetCheckAttrCkb( iChkNo, iCheckAttr);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用チェックボックスのチェック有無を取得する
//
MINT mnInpAttr::GetCheckAttrCkb(						// (  O) チェックマーク　0:OFF, 1:ON
						MINT	iChkNo				// (I  ) チェックボックス番号
				)
{
//U	CButton* pCheckAttr;
//U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[iChkNo - 1]));
//U	return pCheckAttr->GetCheck();
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//	チェックボックスのチェック有無を取得する
//

MINT mnInpAttr::GetCheckAttr(						// (  O) ステイタス0(未設定) 1(設定)
						MCCHKATTR	iAttr,			// (I  ) 属性ID
						MINT		*iCheckAttr		// (  O) チェックマーク　0:OFF, 1:ON
				)
{
	MINT	ist;
	MINT	iChkNo;

	iChkNo = GetCheckAttrNo( iAttr);

	if ( iChkNo != 0) {
		*iCheckAttr = GetCheckAttrCkb( iChkNo);
		ist = 1;
	} else {
		*iCheckAttr = 0;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	構成コード、分類、部品種類IDより、属性値入力モードを求める

MINT mnInpAttr::MnCalcInpAtMode()
{
	MINT		iMode;							// 属性値入力モード
	MINT		iGp;
	MINT		iBr;

	MINT		iIdPartsTp;
	mhPartsTp*	pPartsTp;

	// 部材属性値入力モード( iMode)(表示項目)の決定
	iGp = z_mn.GetKCdGp();
	iBr = z_mn.GetKCdBr();

	iIdPartsTp = z_mn.GetCurIdPartsTp();
	pPartsTp = BuzaiCode::MhGetpPartsTp( iIdPartsTp);

	if ( pPartsTp->IsTategu()) {									// (部品種類ID == 建具)
		iMode = MP_AT_TATEGU;									//			建具入力

	} else if ( pPartsTp->IsFrame())	{							// (部品種類ID == たて枠 | 束) (依存コード == 垂直)
		iMode = MP_AT_VRT_PARTS;								//			垂直部材入力

	} else if ( pPartsTp->IsPanel() || pPartsTp->IsKaiko()) {		// (部品種類ID == パネル | 開口)
		if ( iGp == MP_GP_YUKA || iGp == MP_GP_TENJO)			//		(構成コード == 床 | 天井)
			iMode = MP_AT_YTPANEL;								//			床・天井パネル入力

		else if ( iGp == MP_GP_YANE)							//		(構成 == 屋根)
			iMode = MP_AT_YANEPANEL;							//			屋根パネル入力

		else													//		(その他)
			iMode = MP_AT_HRZ_PARTS;							//			横置き部材入力

	} else if ( iBr == MP_BR_YANE) {							// (分類 == 屋根)
		if ( iGp == MP_GP_YANE) 								//		(構成 == 屋根)
			iMode = MP_AT_YANE;									//			屋根入力
		else													//		(その他)
			iMode = MP_AT_HRZ_PARTS;							//			横置き部材入力

	} else {													// (その他)
		iMode = MP_AT_HRZ_PARTS;								//			横置き部材
	}
	return iMode;
}

/////////////////////////////////////////////////////////////////////////////
//	属性値入力モードで部材属性入力用リボンバーの項目を設定する
//	 (コンボボックスとチェックボックスの項目を設定する)
//	
void mnInpAttr::InitComboAttr(
						MINT	i_iInpAttrMd		// 属性値入力モード
													//  MP_AT_AUTO(-1)		:自動設定
													//	MP_AT_NONE(0)		:属性値入力なし
													//	MP_AT_HRZ_PARTS(1)	:水平部材入力
													//	MP_AT_VRT_PARTS(2)	:垂直部材入力
													//	MP_AT_YTPANEL(3)	:床天井パネル入力
													//	MP_AT_YANEPANEL(4)	:屋根パネル入力
													//	MP_AT_ADJLNG(5)		:部材長さ調整入力
													//	MP_AT_YANE(6)		:屋根入力
													//	MP_AT_TATEGU(7)		:建具入力
				)
{
	if ( i_iInpAttrMd >= 0)
		m_iInpAttrMd = i_iInpAttrMd;
	else
		m_iInpAttrMd = MnCalcInpAtMode();

	//	部材属性入力用コンボボックスとチェックボックスの項目を設定する
	switch ( m_iInpAttrMd)
	{
	case	MP_AT_NONE:
		MnsInitComboAttr( MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_HRZ_PARTS:									// 横置部材
		MnsInitComboAttr( MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_ZJSZ,	// 長さ補正1, 長さ補正2, 芯ずれ
						MC_CMB_TRTH, MC_CMB_INTR, MC_CMB_HONS,	// 取付高さ, 間隔, 本数
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_VRT_PARTS:									// たて枠
		MnsInitComboAttr( MC_CMB_UPRH, MC_CMB_LWRH, MC_CMB_HAIZ,	// 上端高さ, 下端高さ, 配置ずれ
						MC_CMB_NULL, MC_CMB_INTR, MC_CMB_HONS,	// null, 間隔, 本数
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_TATEGU:										// 建具
		MnsInitComboAttr( MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_TRTH,	// 長さ補正1, 長さ補正2, 取付高さ
						MC_CMB_KROH, MC_CMB_HAIZ, MC_CMB_NULL,	// ＲＯＨ, 配置ずれ ,null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null 
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_YTPANEL:										// 床・天井パネル
		MnsInitComboAttr( MC_CMB_LFH1, MC_CMB_RTH1, MC_CMB_TRTH,	// 左巾補正, 右巾補正, 取付高さ
						MC_CMB_FHS1, MC_CMB_OKYK, MC_CMB_OHS2,	// 手前補正, 奥行, 奥行補正
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_YANEPANEL:									// 屋根パネル
		MnsInitComboAttr( MC_CMB_LFH2, MC_CMB_RTH2, MC_CMB_TRTH,	// 左巾補正, 右巾補正, 取付高さ
						MC_CMB_FHS2, MC_CMB_OKYK, MC_CMB_OHS2,	// 軒の出, 奥行, 奥行補正
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL);				// null, null
		break;
	case	MP_AT_ADJLNG:										// 部材長さ調整
		MnsInitComboAttr( MC_CMB_LHS1, MC_CMB_NULL, MC_CMB_NULL,	// 長さ補正, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_KATI,				// null, 勝ち
						MC_CHK_MULT, MC_CHK_INTC);				// 複数, 交差部材調整
		break;
	case	MP_AT_YANE:											// 屋根
		MnsInitComboAttr( MC_CMB_KOBY, MC_CMB_NKDE, MC_CMB_KRDE,	// 屋根勾配, 軒の出, ケラバの出
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NKTP);				// null, 軒タイプ
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	部材属性入力用コンボボックスとチェックボックスの項目を設定する

void mnInpAttr::MnsInitComboAttr(
					MCCMBATTR	icombo1,			// 属性入力用コンボボックス1の属性ID
					MCCMBATTR	icombo2,			// 属性入力用コンボボックス2の属性ID
					MCCMBATTR	icombo3,			// 属性入力用コンボボックス3の属性ID
					MCCMBATTR	icombo4,			// 属性入力用コンボボックス4の属性ID
					MCCMBATTR	icombo5,			// 属性入力用コンボボックス5の属性ID
					MCCMBATTR	icombo6,			// 属性入力用コンボボックス6の属性ID
					MCCHKATTR	icheck1,			// 属性入力用チェックボックス1の属性ID
					MCCHKATTR	icheck2,			// 属性入力用チェックボックス2の属性ID
					MCCHKATTR	icheck3,			// 属性入力用チェックボックス3の属性ID
					MCCHKATTR	icheck4				// 属性入力用チェックボックス4の属性ID
				)
{
	z_Combo_Attr[0] = icombo1; z_Combo_Attr[1] = icombo2; z_Combo_Attr[2] = icombo3;
	z_Combo_Attr[3] = icombo4; z_Combo_Attr[4] = icombo5; z_Combo_Attr[5] = icombo6;
	z_Check_Attr[0] = icheck1; z_Check_Attr[1] = icheck2;
	z_Check_Attr[2] = icheck3; z_Check_Attr[3] = icheck4;

	MINT	ic1;
	
	for ( ic1=1; ic1<=MC_SZ_CMBATTR; ic1++) {
		switch (z_Combo_Attr[ic1-1]) {
			case MC_CMB_NULL:
				// コンボボックスを消し無効にする
				SetComboAttrText( ic1, Mstr( ""));
				InitComboAttrR( ic1, 0, NULL, 0);
				break;
			case MC_CMB_LHS1:
				// 長さ補正値1選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "長さ補正1"));
				InitComboAttrR( ic1, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LHS2:
				// 長さ補正値2選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "長さ補正2"));
				InitComboAttrR( ic1, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_ZJSZ:
				// 材軸芯ずれ量選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "芯ずれ"));
				InitComboAttrR( ic1, ISZSINZ, z_rSinZ, INITSINZ);
				break;
			case MC_CMB_HAIZ:
				// 配置点ずれ量選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "配置ずれ"));
				InitComboAttrR( ic1, ISZHAIZ, z_rHaiZ, INITHAIZ);
				break;
			case MC_CMB_TRTH:
				// 取り付け高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "取付高さ"));
				InitComboAttrR( ic1, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_KROH:
				// 開口部高さ(ROH)選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "ＲＯＨ"));
				InitComboAttrR( ic1, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_INTR:
				// 間隔選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "間隔"));
				InitComboAttrR( ic1, ISZINTV, z_rIntv, INITINTV);
				break;
			case MC_CMB_HONS:
				// 本数選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "本数"));
				InitComboAttrI( ic1, ISZNUM, z_iNum, INITNUM);
				break;

//			case MC_CMB_HHS1:
//				// 幅補正値1選択用コンポボックスの項目を設定する
//				SetComboAttrText( ic1, Mstr( "幅補正1"));
//				InitComboAttrR( ic1, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;
//			case MC_CMB_HHS2:
//				// 幅補正値2選択用コンポボックスの項目を設定する
//				SetComboAttrText( ic1, Mstr( "幅補正2"));
//				InitComboAttrR( ic1, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;

			case MC_CMB_FHS1:
				// 床･天井パネル用　手前補正選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "手前補正"));
				InitComboAttrR( ic1, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_FHS2:
				// 屋根パネル用　手前補正選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "軒の出"));
				InitComboAttrR( ic1, ISZKOUBAI, z_rNokinoDe, INITNOKINODE);
				break;
			case MC_CMB_OKYK:
				// 奥行き選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "奥行"));
				InitComboAttrR( ic1, ISZOKUYUKI, z_rOku, INITOKUYUKI);
				break;
			case MC_CMB_OHS2:
				// 奥行き補正選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "奥行補正"));
				InitComboAttrR( ic1, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_KOBY:
				// 屋根勾配選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "屋根勾配"));
				InitComboAttrI( ic1, ISZKOUBAI, z_iKoubai, INITKOUBAI);
				break;
			case MC_CMB_NKDE:
				// 軒の出選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "軒の出"));
				InitComboAttrR( ic1, ISZNOKINODE, z_rNokinoDe, INITNOKINODE);
				break;
			case MC_CMB_KRDE:
				// ケラバの出選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "ケラバの出"));
				InitComboAttrR( ic1, ISZKERABANODE, z_rKerabanoDe, INITKERABANODE);
				break;
			case MC_CMB_UPRH:
				// 上端高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "上端高さ"));
				InitComboAttrR( ic1, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_LWRH:
				// 下端高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "下端高さ"));
				InitComboAttrR( ic1, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_LFH1:
				// 床･天井パネル用　左巾補正(長さ補正値1)選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "左巾補正"));
				InitComboAttrR( ic1, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_RTH1:
				// 床･天井パネル用　右巾補正(長さ補正値2)選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "右巾補正"));
				InitComboAttrR( ic1, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LFH2:
				// 屋根パネル用　左巾補正(長さ補正値1)選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "左巾補正"));
				InitComboAttrR( ic1, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
			case MC_CMB_RTH2:
				// 屋根パネル用　右巾補正(長さ補正値2)選択用コンポボックスの項目を設定する
				SetComboAttrText( ic1, Mstr( "右巾補正"));
				InitComboAttrR( ic1, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
		}
	}
	for ( ic1=1; ic1<=MC_SZ_CHKATTR; ic1++) {
		switch (z_Check_Attr[ic1-1]) {
			case MC_CHK_NULL:
				// チェックボックスを消し無効にする
				SetCheckAttrText( ic1, NULL);		
				SetCheckAttrCkb( ic1, 0);		
				break;
			case MC_CHK_KATI:
				// 勝ち負け入力用チェックボックスを設定する
				SetCheckAttrText( ic1, Mstr( "勝ち"));
				SetCheckAttrCkb( ic1, 0);
				break;
			case MC_CHK_MULT:
				// 複数入力用チェックボックスを設定する
				SetCheckAttrText( ic1, Mstr( "複数"));
				SetCheckAttrCkb( ic1, 1);
				break;
			case MC_CHK_INTC:
				// 交差部材調整用チェックボックスを設定する
				SetCheckAttrText( ic1, Mstr( "交差部材調整"));
				SetCheckAttrCkb( ic1, 1);
				break;
			case MC_CHK_NKTP:
				// 軒先タイプ(0:勾配収まり、1:垂直)
				SetCheckAttrText( ic1, Mstr( "軒先タイプ垂直"));
				SetCheckAttrCkb( ic1, 1);
				break;
		}
	}
}

} // namespace MC