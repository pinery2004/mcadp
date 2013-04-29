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
#include <afxwin.h>         // MFC のコアおよび標準コンポーネント

#include "MlLog.h"
#include "MsMCAD.h"
#include "MainFrm.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhInpPlcParts.h"
#include "MgGeo.h"

#define MC_SZ_CMBATTR	6
#define MC_SZ_CHKATTR	4

namespace MC
{
mmIoPartsAttr z_mmIA;

static int s_Combo_Attr[][10] = {								// MP_AT_NONE:			// 0
					{	MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_HRZ_PARTS:		// 1			// 横置部材
					{ MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_ZJSZ,	// 長さ補正1, 長さ補正2, 芯ずれ
					MC_CMB_TRTH, MC_CMB_INTR, MC_CMB_HONS,		// 取付高さ, 間隔, 本数
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_VRT_PARTS:		// 2			// たて枠
					{ MC_CMB_UPRH, MC_CMB_LWRH, MC_CMB_HAIZ,	// 上端高さ, 下端高さ, 配置ずれ
					MC_CMB_NULL, MC_CMB_INTR, MC_CMB_HONS,		// null, 間隔, 本数
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_YTPANEL:		// 3			// 床・天井パネル
					{ MC_CMB_LFH1, MC_CMB_RTH1, MC_CMB_TRTH,	// 左巾補正, 右巾補正, 取付高さ
					MC_CMB_FHS1, MC_CMB_OKYK, MC_CMB_OHS2,		// 手前補正, 奥行, 奥行補正
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_YANEPANEL:		// 4			// 屋根パネル
					{ MC_CMB_LFH2, MC_CMB_RTH2, MC_CMB_TRTH,	// 左巾補正, 右巾補正, 取付高さ
					MC_CMB_FHS2, MC_CMB_OKYK, MC_CMB_OHS2,		// 軒の出, 奥行, 奥行補正
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_ADJLNG:		// 5			// 部材長さ調整
					{ MC_CMB_LHS1, MC_CMB_NULL, MC_CMB_NULL,	// 長さ補正, null, null
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_KATI,					// null, 勝ち
					MC_CHK_MULT, MC_CHK_INTC},					// 複数, 交差部材調整
																// MP_AT_YANE:			// 6			// 屋根
					{ MC_CMB_KOBY, MC_CMB_NKDE, MC_CMB_KRDE,	// 屋根勾配, 軒の出, ケラバの出
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NKTP},					// null, 軒タイプ
																// MP_AT_TATEGU:		// 7			// 建具
					{ MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_TRTH,	// 長さ補正1, 長さ補正2, 取付高さ
					MC_CMB_KROH, MC_CMB_HAIZ, MC_CMB_NULL,		// ＲＯＨ, 配置ずれ ,null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null 
					MC_CHK_NULL, MC_CHK_NULL}					// null, null
				};

static int s_IdcComboAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
static int s_IdcStaticAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
static int s_IdcCheckAttr[4] =	{ IDC_CHECKATTR1, IDC_CHECKATTR2,
								  IDC_CHECKATTR3, IDC_CHECKATTR4};


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
static int	  z_iNum[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 
						   10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 9998};
#define	ISZNUM		sizeof(z_iNum)/sizeof(int)
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
static int z_iKoubai[] = {	12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
#define	ISZKOUBAI	sizeof(z_iKoubai)/sizeof(int)
#define	INITKOUBAI		4

// 軒の出
static MREAL z_rNokiDe[] = {	650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZNOKINODE	sizeof(z_rNokiDe)/sizeof(MREAL)
#define	INITNOKINODE		650.0f

// ケラバの出
static MREAL z_rKerabanoDe[] = { 650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZKERABANODE	sizeof(z_rKerabanoDe)/sizeof(MREAL)
#define	INITKERABANODE	650.0f


/////////////////////////////////////////////////////////////////////////////
//	属性値入力モードで部材属性入力用リボンバーの項目を設定する
//	 (コンボボックスとチェックボックスの項目を設定する)
//	
void mmIoPartsAttr::InitComboAttr(
						int		i_iIoPartsAttrMd	// 属性値入力モード
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
	static int s_Combo_Attr[][10] = {							// MP_AT_NONE:			// 0
					  {	MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_HRZ_PARTS:		// 1			// 横置部材
					  { MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_ZJSZ,	// 長さ補正1, 長さ補正2, 芯ずれ
						MC_CMB_TRTH, MC_CMB_INTR, MC_CMB_HONS,	// 取付高さ, 間隔, 本数
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_VRT_PARTS:		// 2			// たて枠
					  { MC_CMB_UPRH, MC_CMB_LWRH, MC_CMB_HAIZ,	// 上端高さ, 下端高さ, 配置ずれ
						MC_CMB_NULL, MC_CMB_INTR, MC_CMB_HONS,	// null, 間隔, 本数
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_YTPANEL:		// 3			// 床・天井パネル
					  { MC_CMB_LFH1, MC_CMB_RTH1, MC_CMB_TRTH,// 左巾補正, 右巾補正, 取付高さ
						MC_CMB_FHS1, MC_CMB_OKYK, MC_CMB_OHS2,	// 手前補正, 奥行, 奥行補正
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_YANEPANEL:		// 4			// 屋根パネル
					  { MC_CMB_LFH2, MC_CMB_RTH2, MC_CMB_TRTH,	// 左巾補正, 右巾補正, 取付高さ
						MC_CMB_FHS2, MC_CMB_OKYK, MC_CMB_OHS2,	// 軒の出, 奥行, 奥行補正
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_ADJLNG:		// 5			// 部材長さ調整
					  { MC_CMB_LHS1, MC_CMB_NULL, MC_CMB_NULL,	// 長さ補正, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_KATI,				// null, 勝ち
						MC_CHK_MULT, MC_CHK_INTC},				// 複数, 交差部材調整
																// MP_AT_YANE:			// 6			// 屋根
					  { MC_CMB_KOBY, MC_CMB_NKDE, MC_CMB_KRDE,	// 屋根勾配, 軒の出, ケラバの出
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NKTP},				// null, 軒タイプ
																// MP_AT_TATEGU:		// 7			// 建具
					  { MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_TRTH,	// 長さ補正1, 長さ補正2, 取付高さ
						MC_CMB_KROH, MC_CMB_HAIZ, MC_CMB_NULL,	// ＲＯＨ, 配置ずれ ,null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null 
						MC_CHK_NULL, MC_CHK_NULL}				// null, null
					};

	int iC1, iAn;

	if ( !GetDispFlg())	goto EXIT;	

	if ( i_iIoPartsAttrMd >= 0)
		m_iIoPartsAttrMd = i_iIoPartsAttrMd;
	else
		m_iIoPartsAttrMd = MnCalcInpAtMode();

	if ( m_iIoPartsAttrMd < 0 || m_iIoPartsAttrMd >= MP_AT_END) {
		mlLog::LogOutT( MC_LOG_ERROR, Mstr( "属性値入力モードエラー: %d\n"), m_iIoPartsAttrMd);
		goto EXIT;
	}

	//	部材属性入力用コンボボックスとチェックボックスの項目を設定する
	for ( iAn=1; iAn<=MC_SZ_CMBATTR; iAn++) {

		switch ( s_Combo_Attr[m_iIoPartsAttrMd][iAn-1]) {
			case MC_CMB_NULL:
				// コンボボックスを消し無効にする
				SetComboAttrText( iAn, Mstr( ""));
				InitComboAttrR( iAn, 0, NULL, 0);
				break;
			case MC_CMB_LHS1:
				// 長さ補正値1選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "長さ補正1"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LHS2:
				// 長さ補正値2選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "長さ補正2"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_ZJSZ:
				// 材軸芯ずれ量選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "芯ずれ"));
				InitComboAttrR( iAn, ISZSINZ, z_rSinZ, INITSINZ);
				break;
			case MC_CMB_HAIZ:
				// 配置点ずれ量選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "配置ずれ"));
				InitComboAttrR( iAn, ISZHAIZ, z_rHaiZ, INITHAIZ);
				break;
			case MC_CMB_TRTH:
				// 取り付け高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "取付高さ"));
				InitComboAttrR( iAn, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_KROH:
				// 開口部高さ(ROH)選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "ＲＯＨ"));
				InitComboAttrR( iAn, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_INTR:
				// 間隔選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "間隔"));
				InitComboAttrR( iAn, ISZINTV, z_rIntv, INITINTV);
				break;
			case MC_CMB_HONS:
				// 本数選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "本数"));
				InitComboAttrI( iAn, ISZNUM, z_iNum, INITNUM);
				break;

//			case MC_CMB_HHS1:
//				// 幅補正値1選択用コンポボックスの項目を設定する
//				SetComboAttrText( iAn, Mstr( "幅補正1"));
//				InitComboAttrR( iAn, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;
//			case MC_CMB_HHS2:
//				// 幅補正値2選択用コンポボックスの項目を設定する
//				SetComboAttrText( iAn, Mstr( "幅補正2"));
//				InitComboAttrR( iAn, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;

			case MC_CMB_FHS1:
				// 床･天井パネル用　手前補正選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "手前補正"));
				InitComboAttrR( iAn, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_FHS2:
				// 屋根パネル用　手前補正選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "軒の出"));
				InitComboAttrR( iAn, ISZKOUBAI, z_rNokiDe, INITNOKINODE);
				break;
			case MC_CMB_OKYK:
				// 奥行き選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "奥行"));
				InitComboAttrR( iAn, ISZOKUYUKI, z_rOku, INITOKUYUKI);
				break;
			case MC_CMB_OHS2:
				// 奥行き補正選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "奥行補正"));
				InitComboAttrR( iAn, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_KOBY:
				// 屋根勾配選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "屋根勾配"));
				InitComboAttrI( iAn, ISZKOUBAI, z_iKoubai, INITKOUBAI);
				break;
			case MC_CMB_NKDE:
				// 軒の出選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "軒の出"));
				InitComboAttrR( iAn, ISZNOKINODE, z_rNokiDe, INITNOKINODE);
				break;
			case MC_CMB_KRDE:
				// ケラバの出選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "ケラバの出"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITKERABANODE);
				break;
			case MC_CMB_UPRH:
				// 上端高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "上端高さ"));
				InitComboAttrR( iAn, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_LWRH:
				// 下端高さ選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "下端高さ"));
				InitComboAttrR( iAn, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_LFH1:
				// 床･天井パネル用　左巾補正(長さ補正値1)選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "左巾補正"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_RTH1:
				// 床･天井パネル用　右巾補正(長さ補正値2)選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "右巾補正"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LFH2:
				// 屋根パネル用　左巾補正(長さ補正値1)選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "左巾補正"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
			case MC_CMB_RTH2:
				// 屋根パネル用　右巾補正(長さ補正値2)選択用コンポボックスの項目を設定する
				SetComboAttrText( iAn, Mstr( "右巾補正"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
		}
	}
//	for ( int iCn=1; iCn<=MC_SZ_CHKATTR; iCn++) {
//		switch (z_Check_Attr[iCn-1]) {
//			case MC_CHK_NULL:
//				// チェックボックスを消し無効にする
//				SetCheckAttrText( iCn, NULL);		
//				SetCheckAttrCkb( iCn, 0);		
//				break;
//			case MC_CHK_KATI:
//				// 勝ち負け入力用チェックボックスを設定する
//				SetCheckAttrText( iCn, Mstr( "勝ち"));
//				SetCheckAttrCkb( iCn, 0);
//				break;
//			case MC_CHK_MULT:
//				// 複数入力用チェックボックスを設定する
//				SetCheckAttrText( iCn, Mstr( "複数"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//			case MC_CHK_INTC:
//				// 交差部材調整用チェックボックスを設定する
//				SetCheckAttrText( iCn, Mstr( "交差部材調整"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//			case MC_CHK_NKTP:
//				// 軒先タイプ(0:勾配収まり、1:垂直)
//				SetCheckAttrText( iCn, Mstr( "軒先タイプ垂直"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//		}
//	}
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの値を取り込む

void mmIoPartsAttr::GetComboAttrA( void)
{
	int		ist;

	MREAL	rComboAttr1;
	MREAL	rComboAttr2;
	MREAL	rComboAttr3;
	MREAL	rComboAttr4;
	MREAL	rComboAttr5;
	MREAL	rComboAttr6;
//S	int		iMode;
//
//	iMode = z_mmIA.GetAtMd();						// 属性値入力モード

	switch ( m_iIoPartsAttrMd)
	{
	case MP_AT_YTPANEL:
	case MP_AT_YANEPANEL:

		if ( m_iIoPartsAttrMd == MP_AT_YTPANEL) {				// ***** 床・天井パネル *****
			z_mmIA.GetComboAttrR( MC_CMB_LFH1, &rComboAttr1);	// 　左巾補正値　→　長さ補正値1
			z_mmIA.GetComboAttrR( MC_CMB_RTH1, &rComboAttr2);	// 　右巾補正値　→　長さ補正値2
			z_mmIA.GetComboAttrR( MC_CMB_FHS1, &rComboAttr3);	// 　手前側補正値　→　手前側補正値

		} else if ( m_iIoPartsAttrMd == MP_AT_YANEPANEL) {		// ***** 屋根パネル *****
			z_mmIA.GetComboAttrR( MC_CMB_LFH2, &rComboAttr1);	// 　左巾補正値　→　長さ補正値1
			z_mmIA.GetComboAttrR( MC_CMB_RTH2, &rComboAttr2);	// 　右巾補正値　→　長さ補正値2
			z_mmIA.GetComboAttrR( MC_CMB_FHS2, &rComboAttr3);	// 　軒の出　→　手前側補正値
		}

		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// →　長さ補正値1
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// →　長さ補正値2
		mtPlcInp::SetMaeHosei( rComboAttr3);					// →　手前側補正値

		z_mmIA.GetComboAttrR( MC_CMB_OKYK, &rComboAttr4);
		mtPlcInp::SetOku( rComboAttr4);							// 奥行き　→　奥行き

		z_mmIA.GetComboAttrR( MC_CMB_OHS2, &rComboAttr5);
		mtPlcInp::SetOkuHosei( rComboAttr5);					// 奥行き補正値　→　奥行き補正値　

		z_mmIA.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);
		mtPlcInp::SetHgt( 0, rComboAttr5);						// 取り付け高さ　→　取り付け高さ 
		break;

	case MP_AT_HRZ_PARTS:
	case MP_AT_VRT_PARTS:
	case MP_AT_TATEGU:
																// ***** 横置き部材・縦置き部材・建具 *****
		z_mmIA.GetComboAttrR( MC_CMB_LHS1, &rComboAttr1);
		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// 長さ補正値1 　→　長さ補正値1

		z_mmIA.GetComboAttrR( MC_CMB_LHS2, &rComboAttr2);
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// 長さ補正値2 　→　長さ補正値2

		z_mmIA.GetComboAttrR( MC_CMB_ZJSZ, &rComboAttr3);
		mtPlcInp::SetSinZure( rComboAttr3);						// 材軸芯ずれ量　→　材軸芯ずれ量

		z_mmIA.GetComboAttrR( MC_CMB_HAIZ, &rComboAttr4);
		mtPlcInp::SetPlcZure( rComboAttr4);						// 配置点ずれ量　→　配置点ずれ量

		ist = z_mmIA.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);	// 取り付け高さ　→　高さ1
		if ( ist == 0)
			ist = z_mmIA.GetComboAttrR( MC_CMB_LWRH, &rComboAttr5);	// 下端高さ　→　高さ1

		mtPlcInp::SetHgt( 0, rComboAttr5);						// →　高さ1
		mtTateguInp::SetHeight( rComboAttr5);					// →　建具高さ

		ist = z_mmIA.GetComboAttrR( MC_CMB_KROH, &rComboAttr6);	// 建具ROH　→　高さ2
		if ( ist ==0)
			ist = z_mmIA.GetComboAttrR( MC_CMB_UPRH, &rComboAttr6);	// 上端高さ　→　高さ2

		mtPlcInp::SetHgt( 1, rComboAttr6);						// →　高さ2
		mtTateguInp::SetROH( rComboAttr6);						// →　建具ROH

		break;

	case MP_AT_ADJLNG:											// ***** 部材長さ調整入力 *****
	case MP_AT_YANE:											// ***** 屋根入力 *****

		ASSERT(false);											// エラー
		break;
	}

}

///////////////////////////////////////////////////////////////////////////////
//	構成コード、分類、部品種類IDより、属性値入力モードを求める

int mmIoPartsAttr::MnCalcInpAtMode()
{
	int		iMode;								// 属性値入力モード
	int		iGp;
	int		iBr;

	int		iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;

	// 部材属性値入力モード( iMode)(表示項目)の決定
	iGp = z_mnIA.GetKCdGp();
	iBr = z_mnIA.GetKCdBr();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	if ( pPartsSpec->IsTategu()) {								// (部品種類ID == 建具)
		iMode = MP_AT_TATEGU;									//			建具入力

	} else if ( pPartsSpec->IsFrame())	{						// (部品種類ID == たて枠 | 束) (依存コード == 垂直)
		iMode = MP_AT_VRT_PARTS;								//			垂直部材入力

	} else if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {	// (部品種類ID == パネル | 開口)
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

//////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックス番号を取得する

int mmIoPartsAttr::GetComboAttrNo(
						MCCMBATTR	i_iAttr		// 属性ID
				)
{
	int		ic;
	int		iCmbNo = 0;

	if (  m_iIoPartsAttrMd == -1) {
		mlLog::LogOutT( MC_LOG_ERROR, Mstr( "属性値入力モードエラー: %d\n"), m_iIoPartsAttrMd);
	} else {
		for ( ic=0; ic<MC_SZ_CMBATTR; ic++)
			if ( i_iAttr == s_Combo_Attr[m_iIoPartsAttrMd][ic])
				break;
		if ( ic < MC_SZ_CMBATTR)
			iCmbNo = ic + 1;
	}
	return iCmbNo;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスのタイトルを設定する
void mmIoPartsAttr::SetComboAttrText(
						int		i_iAttr,		// コンボボックス番号
						MCHAR*	i_sTitle		// タイトル
				)
{
	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( i_sTitle);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに実数値を表示する

void mmIoPartsAttr::SetComboAttrRCbn(
						int		i_iAttr,		// コンボボックス番号
						MREAL	i_rValue		// 表示する実数値
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7.1f"), i_rValue);

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( strValue);
}

//////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに実数値を表示する

void mmIoPartsAttr::SetComboAttrR(
						MCCMBATTR	i_iAttr,	// 属性ID
						MREAL		i_rValue	// 表示する実数値
				)
{
	int iCmbNo;
	iCmbNo = GetComboAttrNo( i_iAttr);
	if ( iCmbNo != 0)
		SetComboAttrRCbn( iCmbNo, i_rValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンポボックスに実数値の項目(一覧)を設定する

void mmIoPartsAttr::InitComboAttrR(
						int		i_iAttr,		// コンボボックス番号
						int		nComboAttr,		// 選択属性値の数
						MREAL	*rComboAttr,	// 選択属性値
						MREAL	rInitValue		// 初期表示する属性値
				)
{
	int		ist;
	int		ic1;
	CString	sKomoku;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);

	pCmbBox->ResetContent();

	// 選択属性値設定
	for ( ic1=0; ic1<nComboAttr; ic1++) {
//		if ( MgEqual( rComboAttr[ic1], 9999.0))
//			sKomoku = "自動";
		if ( MGeo::Equal( rComboAttr[ic1], MREAL( MC_INT_JIDO)))
			sKomoku = MC_STR_JIDO;
		else
			sKomoku.Format(Mstr( "  %6.1f"), rComboAttr[ic1]);
		ist = pCmbBox->InsertString( -1, sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	} else {
		SetComboAttrRCbn( i_iAttr, rInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの実数値を取得する
//
MREAL mmIoPartsAttr::GetComboAttrRCbn(				// 実数値　または　0(未設定)
						int		i_iAttr			// コンボボックス番号
				)
{
	CString strValue;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->GetWindowText( strValue);

	return MsGetMREAL( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの実数値を取得する

int mmIoPartsAttr::GetComboAttrR(					// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,	// 属性ID
						MREAL*		o_rValue	// 実数値
				)
{
	int		ist;
	int		iCmbNo;

	iCmbNo = GetComboAttrNo( i_iAttr);

	if ( iCmbNo != 0) {
		*o_rValue = GetComboAttrRCbn( iCmbNo);
		ist = 1;
	} else {
		*o_rValue = 0.;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに整数値を表示する

void mmIoPartsAttr::SetComboAttrICbn(
						int		i_iAttr,		// コンボボックス番号
						int		iValue 			// 表示する整数値
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7d"), iValue);

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスに整数値を表示する

void mmIoPartsAttr::SetComboAttrI(
						MCCMBATTR	i_iAttr,	// 属性ID
						int			iValue 		// 表示する整数値
				)
{
	int iCmbNo;
	iCmbNo = GetComboAttrNo( i_iAttr);
	if ( iCmbNo != 0)
		SetComboAttrICbn( iCmbNo, iValue);
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用指定コンポボックスに整数値の項目(一覧)を設定する

void mmIoPartsAttr::InitComboAttrI(
						int		i_iAttr,		// コンボボックス番号
						int		nComboAttr,		// 選択属性値の数
						int		*iCmbAttr,		// 選択属性値
						int		iInitValue		// 初期表示する属性値
				)
{
	int		ist;
	int		ic1;
	CString	sKomoku;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);

	pCmbBox->ResetContent();

	for ( ic1=0; ic1<nComboAttr; ic1++) {
		if ( iCmbAttr[ic1] == MC_INT_JIDO)
			sKomoku = MC_STR_JIDO;								// 自動
		if ( iCmbAttr[ic1] == MC_INT_AREA)
			sKomoku = MC_STR_AREA;								// 領域
		else
			sKomoku.Format(Mstr( "  %6d"), iCmbAttr[ic1]);
		ist = pCmbBox->InsertString( -1, sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	} else {
		SetComboAttrICbn( i_iAttr, iInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	属性値入力用コンボボックスの整数値を取得する
//
int mmIoPartsAttr::GetComboAttrICbn(				// 整数値　または　0(未設定)
						int		i_iAttr			// コンボボックス番号
					)
{
	CString strValue;
	int		iNum;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->GetWindowText( strValue);

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

int	mmIoPartsAttr::GetComboAttrI(					// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,	// 属性ID
						int*		o_iValue 	// 表示する整数値
					)
{
	int		ist;
	int		iCmbNo;

	ist = 0;
	iCmbNo = GetComboAttrNo( i_iAttr);

	if ( iCmbNo != 0) {
		*o_iValue = GetComboAttrICbn( iCmbNo);
		ist = 1;
	} else {
		*o_iValue = 0;
		ist = 0;
	}
	return ist;
}

//S//////////////////////////////////////////////////////////////////////////////
////	属性値入力用チェックボックス番号を取得する
//
//int mmIoPartsAttr::GetCheckAttrNo(
//						MCCHKATTR	i_iAttr		// 属性ID
//				)
//{
//	int	 ic;
//	int	 iChkNo = 0;
//
//	for ( ic=0; ic<MC_SZ_CHKATTR; ic++) {
//		if ( i_iAttr == z_Check_Attr[ic])
//			break;
//	}
//	if ( ic < MC_SZ_CHKATTR)
//		iChkNo = ic + 1;
//	return iChkNo;
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	属性値入力用チェックボックスのタイトルを設定する
//void mmIoPartsAttr::SetCheckAttrText(
//						int		i_iAttr,		// チェックボックス番号
//						MCHAR*	i_sTitle		// タイトル　または　NULL:チェックボックスを表示しない
//				)
//{
//	CComboBox *pCmbBox = MnpComboAttr( i_iAttr);
//
//	if ( i_sTitle) {
//		pCmbBox->SetToolTipText( i_sTitle);
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	属性値入力用チェックボックスのチェックマークを設定する
//
//void mmIoPartsAttr::SetCheckAttrCkb(
//						int		i_iChkNo,		// チェックボックス番号
//						int		i_iCheckAttr	// チェックマーク　0:OFF, 1:ON
//				)
//{
////U	CButton* pCheckAttr;
////U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
////U	pCheckAttr->SetCheck( i_iCheckAttr);
//	CMFCRibbonCheckBox* pCheckBox;
//	pCheckBox = DYNAMIC_DOWNCAST( CMFCRibbonCheckBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcCheckAttr[i_iChkNo - 1]));
////	pCheckBox->set
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	チェックボックスのチェックマークを設定する
//
//void mmIoPartsAttr::SetCheckAttr(
//						MCCHKATTR	i_iAttr,	// 属性ID
//						int			i_iCheckAttr// チェックマーク　0:OFF, 1:ON
//				)
//{
//	int	 iChkNo = GetCheckAttrNo( i_iAttr);
//	if ( iChkNo != 0)
//		SetCheckAttrCkb( iChkNo, i_iCheckAttr);
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	属性値入力用チェックボックスのチェック有無を取得する
////
//int mmIoPartsAttr::GetCheckAttrCkb(				// チェックマーク　0:OFF, 1:ON
//						int		i_iChkNo		// チェックボックス番号
//				)
//{
////U	CButton* pCheckAttr;
////U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
////U	return pCheckAttr->GetCheck();
//	return 0;
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	チェックボックスのチェック有無を取得する
////
//
//int mmIoPartsAttr::GetCheckAttr(					// ステイタス0(未設定) 1(設定)
//						MCCHKATTR	i_iAttr,	// 属性ID
//						int*		o_iCheckAttr// チェックマーク　0:OFF, 1:ON
//				)
//{
//	int		ist;
//	int		iChkNo;
//
//	iChkNo = GetCheckAttrNo( i_iAttr);
//
//	if ( iChkNo != 0) {
//		*o_iCheckAttr = GetCheckAttrCkb( iChkNo);
//		ist = 1;
//	} else {
//		*o_iCheckAttr = 0;
//		ist = 0;
//	}
//	return ist;
//}

//S	for ( ic1=1; ic1<=MC_SZ_CHKATTR; ic1++) {
//		switch (z_Check_Attr[ic1-1]) {
//			case MC_CHK_NULL:
//				// チェックボックスを消し無効にする
//				SetCheckAttrText( ic1, NULL);		
//				SetCheckAttrCkb( ic1, 0);		
//				break;
//			case MC_CHK_KATI:
//				// 勝ち負け入力用チェックボックスを設定する
//				SetCheckAttrText( ic1, Mstr( "勝ち"));
//				SetCheckAttrCkb( ic1, 0);
//				break;
//			case MC_CHK_MULT:
//				// 複数入力用チェックボックスを設定する
//				SetCheckAttrText( ic1, Mstr( "複数"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//			case MC_CHK_INTC:
//				// 交差部材調整用チェックボックスを設定する
//				SetCheckAttrText( ic1, Mstr( "交差部材調整"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//			case MC_CHK_NKTP:
//				// 軒先タイプ(0:勾配収まり、1:垂直)
//				SetCheckAttrText( ic1, Mstr( "軒先タイプ垂直"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//		}
//	}
//}

} // namespace MC