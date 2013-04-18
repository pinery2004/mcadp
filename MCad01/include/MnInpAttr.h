#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#include "MmDialogKAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

enum	ComboTp {
	MSET_RIBBON_BAR = 1,
	MSET_INPUT_KUBUN_CD,
	MSET_INPUT_MARUME_CD,
	MSET_COMBO_ATTRR,
	MGET_COMBO_ATTRA,
	MSET_COMBO_PARTS,
	MSET_COMBO_PANELNO,
	MINIT_COMBO_ATTR
};

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mnInpAttr・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mnInpAttr・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mnInpAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	int		m_iCCategory;						// カレントカテゴリ　1:意匠, 2:構造, 3:共通

	int		m_iInpKai;							// 階				(1階,2階,3階)
	int		m_iCdInpKbn;						// 入力点区分コード	(無指定,1点,方向2点,長さ2点,区画,自由)
	int		m_iCdMarume;						// 丸めコード		(1,2,3,4,6,8)
	int		m_iCdIzon;							// 依存コード		(任意,壁芯付き,屋根構成線付き)
	int		m_iCdPartsNm;						// 部品名Id
	int		m_iCdMbr;							// メンバーId
	MREAL	m_rLengthH1;						// 長さ補正1		(mm)
	MREAL	m_rLengthH2;						// 長さ補正2		(mm)
	MREAL	m_rSinzure;							// 芯ずれ			(mm)
	MREAL	m_rToritukeH;						// 取付高さ			(mm)
	MREAL	m_rSpan;							// 間隔				(mm)
	int		m_nHonsu;							// 本数
	int		m_iPanelNo;							// パネルNo			(0:全、1～n)

	int		m_iKobai;							// 勾配
	MREAL	m_rNokiDe;							// 軒の出
	MREAL	m_rKerabaDe;						// けらばの出

	MPMODE	m_iInpMd;							// 創成モード		(削除、修正、移動、複写、属性表示)

	MPKOSEI	m_iSInpGp;							// 設計入力構成		(住戸、住棟、物件、屋根、敷地、壁量)

	MPKOSEI  m_iKInpGp;							// 構造入力構成		(屋根、小屋、天井、耐力壁、壁、床、土台、基礎)
	MPBUNRUI m_iKInpBr;							// 構造入力種類		(部材、金物、パネル、その他)
	MPSELECT m_iKInpSel;							// 構造入力選択		選択1、選択2、選択3						未使用

	bool	m_bKDspBuzai;						// 部材表示フラグ
	bool	m_bKDspKanagu;						// 金物表示フラグ
	bool	m_bKDspGohan;						// 合板表示フラグ
	bool	m_bKAttr1;							// 属性1フラグ
	bool	m_bKAttr2;							// 属性2フラグ
	bool	m_bKAttr3;							// 属性3フラグ
	bool	m_bKAttr4;							// 属性4フラグ

	int		m_iInpAttrMd;						// 属性値入力モード
												//		MP_AT_AUTO(-1)		:自動設定
												//		MP_AT_NONE(0)		:属性値入力なし
												//		MP_AT_HRZ_PARTS(1)	:水平部材入力
												//		MP_AT_VRT_PARTS(2)	:垂直部材入力
												//		MP_AT_YTPANEL(3)	:床天井パネル入力
												//		MP_AT_YANEPANEL(4)	:屋根パネル入力
												//		MP_AT_ADJLNG(5)		:部材長さ調整入力
												//		MP_AT_YANE(6)		:屋根入力
												//		MP_AT_TATEGU(7)		:建具入力


	////////////////////////////////////////////////////////////////////////////
	//	コンストラクタ
public:
	mnInpAttr();

public:
	////////////////////////////////////////////////////////////////////////////
	//	属性値入力用
	ComboTp	m_iComboTp;								// コンボ種類
	int		m_iCdArg1;								// 設定コード1 整数
	MREAL	m_rCdArg2;								// 設定コード2 実数
	int		m_iSts;									// ステイタス

public:
	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、リボンバーの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
	MPKOSEI		m_iRBKosei;							// 構造	構成
	MPBUNRUI	m_iRBBunrui;						// 構造	分類
//S	CString		m_sRBBuhin;							// 部品
//S	CString		m_sRBMbr;							// 部品メンバー
	MCHAR*		m_sRBBuhin;							// 部品
	MCHAR*		m_sRBMbr;							// 部品メンバー

	///////////////////////////////////////////////////////////////////////////////
	//	リボンバーの設定と取り込み
public:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo種類	1:入力点区分コード
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);

	/////////////////////////////////////////////////////////////////////////////
	//	カレントカテゴリ	
	void	SetCCategory(
						int i_iCCategory			// カレントカテゴリ　1:意匠, 2:構造, 3:共通
				)
	{
		m_iCCategory = i_iCCategory;

	}
	int	GetCCategory()
	{
		return m_iCCategory;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	階				１階、２階、３階
public:
	void SetInpKai(
						MINT 		i_iInpKai		// 階	
				)
	{
		m_iInpKai = i_iInpKai;
	}
public:
	MINT GetInpKai()
	{
		return m_iInpKai;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	コンボボックスに入力点区分を表示し
	//	カレントの入力点区分を設定する
protected:
	void SelectComboInpKbnByInpKbnCd(
						MINT		i_iCdCdInpKb	// 入力点区分
				);

	///////////////////////////////////////////////////////////////////////////////
	//	入力点区分選択用コンボボックスより入力点区分を取得する
	//	（カレントの入力点区分を取得する）
	//							＝1 : １点入力
	//							＝2 : 方向１点入力
	//							＝3 : 長さ２点入力
	//							＝4 : 区画入力
	//							＝5 : 自由入力
public:
	MINT GetComboInpKbCd();

	///////////////////////////////////////////////////////////////////////////////
	//	丸目コード選択用コンボボックスに丸目コードを表示し
	//	カレントの丸目コードを設定する
protected:
	void SelectComboMarumeByMarumeCd(
						MINT		i_iCdMarume		// 丸目コード
				);

	///////////////////////////////////////////////////////////////////////////////
	//	丸目コード選択用コンボボックスより丸目コードを取得する
	//	（カレントの丸目コードを取得する）
	//							＝0 : 丸めなし
	//							＝1 : １／１グリッド丸め
	//							＝2 : １／２グリッド丸め
	//							＝3 : １／３グリッド丸め
	//							＝4 : １／４グリッド丸め
	//							＝5 : １／６グリッド丸め
	//							＝5 : １／８グリッド丸め
public:
	MINT GetComboMarumeCd();

	/////////////////////////////////////////////////////////////////////////////
	// 依存コード		(任意,壁芯付き,屋根構成線付き)
public:
	void SetIzonCd(
						MINT 		i_iCdIzon		// 依存コード	
				)
	{
		m_iCdIzon = i_iCdIzon;
	}
public:
	MINT GetIzonCd()
	{
		return m_iCdIzon;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスの項目を設定する
protected:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名項目番号で選択する
protected:
	void SelectComboPartsNmByKmId(
						MINT		i_iKmIdPartsNm	// 部品名項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名で選択する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
protected:
	MINT SelectComboPartsNmByPartsNm(
						MCHAR* 		i_sNmParts1		// 部品名
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名から部品名コンポボックスの部品名項目番号を取得する
	//	コンボボックスの項目より指定された部材の部品IDを検索し、
	//	該当の部品名項目番号を返す
	//	返値
	//							≧ 0: 部品ID
	//							＝-1: 該当なし
public:
	MINT GetComboPartsNmKmIdFromPartsNm(
						MCHAR*		i_sNmParts1		// 部品名
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスより部品IDを取得する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
public:
	MINT GetComboPartsNmId(
						MCHAR* 		i_sNmParts1		// 部品名
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスのカレントの部品IDを取得する
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	MINT GetCurPartsNmId();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスの項目を設定する
protected:
	void InitComboPartsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式項目番号で選択する
protected:
	void SelectComboPartsMbrByKmId(
						MINT		i_iKmIdMbr		// 寸法型式項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式で選択する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
protected:
	MINT SelectComboMbrCdByMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法形式から寸法型式コンボボックスの寸法型式項目番号を取得する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
public:
	MINT GetComboMbrKmId(
						MCHAR*		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスより寸法型式IDを取得する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
public:
	MINT GetComboMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスより寸法型式IDを取得する
	//	（カレントの寸法型式IDを取得する）
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	MINT GetComboMbrCdId();

	//////////////////////////////////////////////////////////////////////////////
	// 属性入力用コンボボックスを取得する
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						MINT	i_iAttr				// コンボボックス番号
				);

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックス番号を取得する
protected:
	MINT GetComboAttrNo(
						MCCMBATTR	i_iAttr			// 属性ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスのタイトルを設定する
protected:
	void SetComboAttrText(
						MINT	i_iAttr,			// コンボボックス番号
						MCHAR*	i_sTitle			// タイトル
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンポボックスに実数値の項目(一覧)を設定する
protected:
	void InitComboAttrR(
						MINT	i_iAttr,			// コンボボックス番号
						MINT	i_nComboAttr,		// 選択属性値の数
						MREAL*	i_rComboAttr,		// 選択属性値
						MREAL	i_rInitValue		// 初期表示する属性値
				);

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
protected:
	void SetComboAttrR(
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL		i_rValue		// 表示する実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの実数値を取得する
protected:
	MINT GetComboAttrR(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL*		o_prValue		// 実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
protected:
	void SetComboAttrRCbn(
						MINT	i_iAttr,			// コンボボックス番号
						MREAL	i_rValue			// 表示する実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの実数値を取得する
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) 実数値　または　0(未設定)
						MINT	i_iAttr				// コンボボックス番号
				);

	/////////////////////////////////////////////////////////////////////////////
	//	長さ補正1				
public:
	void SetLengthH1(
						MREAL 		i_rLengthH1		// 長さ補正1	
				)
	{
		m_rLengthH1 = i_rLengthH1;
	}
public:
	MREAL GetLengthH1()
	{
		return m_rLengthH1;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	長さ補正2				
public:
	void SetLengthH2(
						MREAL 		i_rLengthH2		// 長さ補正2	
				)
	{
		m_rLengthH2 = i_rLengthH2;
	}
public:
	MREAL GetLengthH2()
	{
		return m_rLengthH2;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	芯ずれ				
public:
	void SetSinzure(
						MREAL 		i_rSinzure		// 芯ずれ	
				)
	{
		m_rLengthH1 = i_rSinzure;
	}
public:
	MREAL GetSinzure()
	{
		return m_rSinzure;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	取付高さ				
public:
	void SetToritukeH(
						MREAL 		i_rToritukeH	// 取付高さ	
				)
	{
		m_rToritukeH = i_rToritukeH;
	}
public:
	MREAL GetToritukeH()
	{
		return m_rToritukeH;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	間隔				
public:
	void SetSpan(
						MREAL 		i_rSpan			// 間隔	
				)
	{
		m_rSpan = i_rSpan;
	}
public:
	MREAL GetSpan()
	{
		return m_rSpan;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrI(
						MCCMBATTR	i_iAttr,		// 属性ID
						MINT		i_iValue 		// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数を取得する
protected:
	MINT GetComboAttrI(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						MINT*		o_piValue		// 整数値
				);


	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrICbn(
						MINT	i_iAttr,			// コンボボックス番号
						MINT	i_iValue 			// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用指定コンポボックスに整数値の項目(一覧)を設定する
protected:
	void InitComboAttrI(
						MINT	i_iAttr,			// コンボボックス番号
						MINT	i_nComboAttr,		// 選択属性値の数
						MINT*	i_iCmbAttr,			// 選択属性値
						MINT	i_iInitValue		// 初期表示する属性値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数値を取得する
	//
protected:
	MINT GetComboAttrICbn(							// 整数値　または　0(未設定)
						MINT	i_iAttr				// コンボボックス番号
				);

	/////////////////////////////////////////////////////////////////////////////
	//	本数
public:
	void SetHonsu(
						MINT 		i_nHonsu		// 本数	
				)
	{
		m_nHonsu = i_nHonsu;
	}
public:
	MINT GetHonsu()
	{
		return m_nHonsu;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスの項目を設定する
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスにパネル番号を表示する
protected:
	void SetComboPanelNo(
						MINT		i_iPanelNo		// パネル番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号選択用コンポボックスよりパネル番号を取得する
	//							＝-1: 未選択
	//							＝ 0: 全
	//							≧ 1: パネル番号
public:
	MINT GetComboPanelNo();

	/////////////////////////////////////////////////////////////////////////////
	//	パネルNo
public:
	void SetPanelNo(
						MINT 		i_iPanelNo	// 本数	
				)
	{
		m_iPanelNo = i_iPanelNo;
	}
public:
	MINT GetPanelNo()
	{
		return m_iPanelNo;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	勾配
public:
	void SetKobai(
						MINT 		i_iKobai	// 勾配	
				)
	{
		m_iKobai = i_iKobai;
	}
public:
	MINT GetKobai()
	{
		return m_iKobai;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	軒の出				
public:
	void SetNokiDe(
						MREAL 		i_rNokiDe	// 軒の出	
				)
	{
		m_rNokiDe = i_rNokiDe;
	}
public:
	MREAL GetNokiDe()
	{
		return m_rNokiDe;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	けらばの出				
public:
	void SetKerabaDe(
						MREAL 		i_rKerabaDe	// けらばの出	
				)
	{
		m_rKerabaDe = i_rKerabaDe;
	}
public:
	MREAL GetKerabaDe()
	{
		return m_rKerabaDe;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	創成モード		削除、修正、移動、複写、属性表示
public:
	void SetMode(
						MPMODE 		i_iInpMd		// 創成モード
				)
	{
		m_iInpMd = i_iInpMd;
	}
public:
	MPMODE GetMode()
	{
		return m_iInpMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	// 設計入力構成		住戸、住棟、物件、屋根、敷地、壁量
public:
	void SetSCdGp(
						MPKOSEI		i_iSInpGp		// 設計　構成
				)
	{
		m_iSInpGp = i_iSInpGp;
	}
public:
	MPKOSEI GetSCdGp()
	{
		return m_iSInpGp;
	}

	/////////////////////////////////////////////////////////////////////////////
	// 構造入力構成		屋根、小屋、天井、耐力壁、壁、床、基礎
public:
	void SetKCdGp(
						MPKOSEI		i_iKInpGp		// 構造　構成(組)
				)
	{
		m_iKInpGp = i_iKInpGp;
	}
public:
	MPKOSEI GetKCdGp()
	{
		return m_iKInpGp;
	}

	/////////////////////////////////////////////////////////////////////////////
	// 構造入力種類		部材、金物、パネル、その他
public:
	void SetKCdBr(
						MPBUNRUI		i_iKInpBr		// 構造　種類
				)
	{
		m_iKInpBr = i_iKInpBr;
	}
public:
	MPBUNRUI GetKCdBr()
	{
		return m_iKInpBr;
	}

	/////////////////////////////////////////////////////////////////////////////
	// 構造入力選択		選択1、選択2、選択3						未使用
public:
	void SetKSel(
						MPSELECT	i_iSel			// 選択番号
				)
	{
		m_iKInpSel = i_iSel;
	}
public:
	MPSELECT GetKSel()
	{
		return m_iKInpSel;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	部材、金物、合板のチェックボックスの表示フラグを設定
public:
	void SetKCdBrB(
						bool		i_bDspBuzai,	// 部材表示フラグ
						bool		i_bDspKanagu,	// 金具表示フラグ
						bool		i_bDspGohan		// 合板表示フラグ
				)
	{
		m_bKDspBuzai  = i_bDspBuzai;
		m_bKDspKanagu = i_bDspKanagu;
		m_bKDspGohan  = i_bDspGohan;
	}


/* ====
*/

	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、リボンバーの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
public:
	int	SetRibbonBarEnt( 									// ステイタス 0:正常 -1:エラー
					MPKOSEI		i_irbKumi,			// 構造	組
					MPBUNRUI	i_irbBunrui,		// 構造	分類
					MCHAR*		i_crbPartsSpec,		// 部品種類
					MCHAR*		i_crbMbr = NULL		// 部品メンバー()
				)
	{
		int	ist;
		m_iRBKosei	= i_irbKumi;
		m_iRBBunrui = i_irbBunrui;
		m_sRBBuhin	= i_crbPartsSpec;
		m_sRBMbr	= i_crbMbr;

		ist = RibbonIO( MSET_RIBBON_BAR);

//US		z_pDlgKAttr->SetRibbonBarEnt( i_irbKumi, i_irbBunrui, i_crbPartsSpec, i_crbMbr);
		z_DlgKAttr.SetRibbonBarEnt( i_irbKumi, i_irbBunrui, i_crbPartsSpec, i_crbMbr);

		return ist;
	}

	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、リボンバーの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
protected:
	int	SetRibbonBar( 									// ステイタス 0:正常 -1:エラー
					MPKOSEI		i_irbKumi,			// 構造	組
					MPBUNRUI	i_irbBunrui,		// 構造	分類
					MCHAR*		i_crbPartsSpec,		// 部品種類
					MCHAR*		i_crbMbr = NULL		// 部品メンバー()
				);

	///////////////////////////////////////////////////////////////////////////////
	//	配置コード選択用コンボボックスに配置コードを表示し
	//	カレントの配置コードを設定する
protected:
	void SelectComboPlcCdByPlcCd(
						MINT		i_iCdPlc		// 配置コード
				);

	///////////////////////////////////////////////////////////////////////////////
	//	配置コード選択用コンボボックスより配置コードを取得する
	//	（カレントの配置コードを取得する）
	//							＝0 : 任意
	//							＝1 : 壁芯付き
	//							＝2 : 屋根構成線付き
public:
	MINT GetComboPlcCd();

//S	/////////////////////////////////////////////////////////////////////////////
//	// 設計入力種類
//
//	void SetSCdBr(
//						MINT		i_iSCdBr		// 設計　種類
//				);
//	MINT GetSCdBr();
//
//	/////////////////////////////////////////////////////////////////////////////
//	// 設計入力選択
//
//	void SetSSel(
//						MINT		i_iSel
//				);
//	MINT GetSSel();

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックス番号を取得する
protected:
	MINT GetCheckAttrNo(
						MCCHKATTR	i_iAttr			// 属性ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのタイトルを設定する
protected:
	void SetCheckAttrText(
						MINT	i_iAttr,			// チェックボックス番号
						MCHAR*	i_sTitle			// タイトル　または　NULL:チェックボックスを表示しない
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのチェックマークを設定する
protected:
	void SetCheckAttrCkb(
						MINT	i_iChkNo,			// チェックボックス番号
						MINT	i_iCheckAttr		// チェックマーク　0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのチェック有無を取得する
	//
protected:
	MINT GetCheckAttrCkb(							// チェックマーク　0:OFF, 1:ON
						MINT	i_iChkNo			// チェックボックス番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	構成コード、分類、部品種類IDより、属性値入力モードを求める
protected:
	MINT MnCalcInpAtMode();

	/////////////////////////////////////////////////////////////////////////////
	//	部品属性入力用コンボボックスとチェックボックスの項目を設定する
protected:
	void MnsInitComboAttr(
						MCCMBATTR	i_icombo1,		// 属性入力用コンボボックス1の属性ID
						MCCMBATTR	i_icombo2,		// 属性入力用コンボボックス2の属性ID
						MCCMBATTR	i_icombo3,		// 属性入力用コンボボックス3の属性ID
						MCCMBATTR	i_icombo4,		// 属性入力用コンボボックス4の属性ID
						MCCMBATTR	i_icombo5,		// 属性入力用コンボボックス5の属性ID
						MCCMBATTR	i_icombo6,		// 属性入力用コンボボックス6の属性ID
						MCCHKATTR	i_icheck1,		// 属性入力用チェックボックス1の属性ID
						MCCHKATTR	i_icheck2,		// 属性入力用チェックボックス2の属性ID
						MCCHKATTR	i_icheck3,		// 属性入力用チェックボックス3の属性ID
						MCCHKATTR	i_icheck4		// 属性入力用チェックボックス4の属性ID
				);

	////////////////////////////////////////////////////////////////////////////
	//	部品属性入力用コンボボックスの設定
protected:
	void SetComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	カレントの属性値入力モードを取得する
	//	(部品属性入力用リボンバーの項目設定中の属性値入力モード)
	//
public:
	MINT GetAtMd()
	{
		return m_iInpAttrMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	属性値入力モードで部品属性入力用リボンバーの項目を設定する
	//	 (コンボボックスとチェックボックスの項目を設定する)
	//	
protected:
	void InitComboAttr(
						MINT	i_iInpAttrMd = MP_AT_NONE	// 属性値入力モード
													//  MP_AT_AUTO(-1)		:自動設定
													//	MP_AT_NONE(0)		:属性値入力なし
													//	MP_AT_HRZ_PARTS(1)	:水平部材入力
													//	MP_AT_VRT_PARTS(2)	:垂直部材入力
													//	MP_AT_YTPANEL(3)	:床天井パネル入力
													//	MP_AT_YANEPANEL(4)	:屋根パネル入力
													//	MP_AT_ADJLNG(5)		:部材長さ調整入力
													//	MP_AT_YANE(6)		:屋根入力
													//	MP_AT_TATEGU(7)		:建具入力
				);

	///////////////////////////////////////////////////////////////////////////////
	//	リボンバーのコンボックスの設定　本体
protected:
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの値を取り込む
protected:
	void GetComboAttrA( void);

	///////////////////////////////////////////////////////////////////////////////
	//	チェックボックスのチェックマークを設定する
protected:
	void SetCheckAttr(
						MCCHKATTR	i_iAttr,		// 属性ID
						MINT		i_iCheckAttr	// チェックマーク　0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	チェックボックスのチェック有無を取得する
	//
public:
	MINT GetCheckAttr(								// ステイタス0(未設定) 1(設定)
						MCCHKATTR	i_iAttr,		// 属性ID
						MINT*		o_piCheckAttr	// チェックマーク　0:OFF, 1:ON
				);

};

extern	mnInpAttr z_mn;

}// namespace MC