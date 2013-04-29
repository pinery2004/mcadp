#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

//#include "MmDialogKAttr.h"
#include "MmIoPartsAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

enum	ComboTp {
	MSET_RIBBON_BAR = 1,			// リボンバーの部品選択用項目( 組、分類、部品タイプ、寸法型式)を設定する
	MSET_INPUT_KUBUN_CD,			// カレントの入力点区分を設定し、入力点区分選択用のコンボボックスに表示する
	MSET_INPUT_MARUME_CD,			// カレントの丸めコードを設定し、コンボボックスに丸めコードを表示する
	MSET_COMBO_ATTRR,				// 属性値入力用コンボボックスに実数値を表示する
	MGET_PARTS_ATTRA,				// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
	MSET_COMBO_PARTS,				// 部材属性入力用コンボボックスの設定
	MSET_COMBO_PANELNO,				// カレントのパネル番号選択項目番号を設定し　コンボボックスにパネル番号を表示する

	MINIT_COMBO_ATTR				// 属性値入力モードに沿った部材属性入力用リボンバーの項目を設定する
};

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mnIoPartsAttr・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mnIoPartsAttr・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mnIoPartsAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	int		m_iCCategory;						// カレントカテゴリ　1:意匠, 2:構造, 3:共通

	int		m_iInpKai;							// 階				(1階,2階,3階)
//
	MPMODE	m_iInpMd;							// 創成モード		(削除、修正、移動、複写、属性表示)
	MPKOSEI	m_iSInpGp;							// 設計入力構成		(住戸、住棟、物件、屋根、敷地、壁量)
	MPKOSEI  m_iKInpGp;							// 構造入力構成		(屋根、小屋、天井、耐力壁、壁、床、土台、基礎)
	MPBUNRUI m_iKInpBr;							// 構造入力種類		(部材、金物、パネル、その他)
	MPSELECT m_iKInpSel;						// 構造入力選択		選択1、選択2、選択3						未使用
//
	bool	m_bKDspBuzai;						// 部材表示フラグ
	bool	m_bKDspKanagu;						// 金物表示フラグ
	bool	m_bKDspGohan;						// 合板表示フラグ

	////////////////////////////////////////////////////////////////////////////
	//	コンストラクタ
public:
	mnIoPartsAttr();

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
	MCHAR*		m_sRBBuhin;							// 部品
	MCHAR*		m_sRBMbr;							// 部品メンバー

	// 部品名コンボボックス
	int		m_nComboIdPartsSpec;					// 表示項目数
	int		m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// 表示項目対応部品ID
	int		m_iComboKmIdPartsNm;					// 部品名カレント選択項目番号

	// 寸法型式選択用コンボボックス
	int		m_nComboPartsMbrId;						// 表示項目数
	int		m_iComboPartsMbrId[MX_CMB_CDMEMBER];	// 表示項目対応寸法型式ID
	int		m_iComboKmIdMbr;						// 寸法形式カレント選択項目番号

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
						int	 		i_iInpKai		// 階	
				)
	{
		m_iInpKai = i_iInpKai;
	}
public:
	int GetInpKai()
	{
		return m_iInpKai;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	コンボボックスに入力点区分を表示し
	//	カレントの入力点区分を設定する
protected:
	void SelectComboInpKbnByInpKbnCd(
						int			i_iCdCdInpKb	// 入力点区分
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
	int GetComboInpKbCd();

	///////////////////////////////////////////////////////////////////////////////
	//	丸目コード選択用コンボボックスに丸目コードを表示し
	//	カレントの丸目コードを設定する
protected:
	void SelectComboMarumeByMarumeCd(
						int			i_iCdMarume		// 丸目コード
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
	int GetComboMarumeCd();

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスの項目を設定する
protected:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名項目番号で選択する
protected:
	void SelectComboPartsNmByKmId(
						int			i_iKmIdPartsNm	// 部品名項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名で選択する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
protected:
	int SelectComboPartsNmByPartsNm(
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
	int GetComboPartsNmKmIdFromPartsNm(
						MCHAR*		i_sNmParts1		// 部品名
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスより部品IDを取得する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
public:
	int GetComboPartsNmId(
						MCHAR* 		i_sNmParts1		// 部品名
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスのカレントの部品IDを取得する
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	int GetCurPartsNmId();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスの項目を設定する
protected:
	void InitComboPartsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式項目番号で選択する
protected:
	void SelectComboPartsMbrByKmId(
						int			i_iKmIdMbr		// 寸法型式項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式で選択する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
protected:
	int SelectComboPartsMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法形式から寸法型式コンボボックスの寸法型式項目番号を取得する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
public:
	int GetComboPartsMbrKmId(
						MCHAR*		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスより寸法型式IDを取得する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
public:
	int GetComboPartsMbrCdId(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスより寸法型式IDを取得する
	//	（カレントの寸法型式IDを取得する）
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	int GetCurPartsMbrCdId();

	//////////////////////////////////////////////////////////////////////////////
	// 属性入力用コンボボックスを取得する
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						int		i_iAttr				// コンボボックス番号
				);

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックス番号を取得する
protected:
	int GetComboAttrNo(
						MCCMBATTR	i_iAttr			// 属性ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスのタイトルを設定する
protected:
	void SetComboAttrText(
						int		i_iAttr,			// コンボボックス番号
						MCHAR*	i_sTitle			// タイトル
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンポボックスに実数値の項目(一覧)を設定する
protected:
	void InitComboAttrR(
						int		i_iAttr,			// コンボボックス番号
						int		i_nComboAttr,		// 選択属性値の数
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
	int GetComboAttrR(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL*		o_prValue		// 実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
protected:
	void SetComboAttrRCbn(
						int		i_iAttr,			// コンボボックス番号
						MREAL	i_rValue			// 表示する実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの実数値を取得する
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) 実数値　または　0(未設定)
						int		i_iAttr				// コンボボックス番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrI(
						MCCMBATTR	i_iAttr,		// 属性ID
						int			i_iValue 		// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数を取得する
protected:
	int GetComboAttrI(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						int*		o_piValue		// 整数値
				);


	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrICbn(
						int		i_iAttr,			// コンボボックス番号
						int		i_iValue 			// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用指定コンポボックスに整数値の項目(一覧)を設定する
protected:
	void InitComboAttrI(
						int		i_iAttr,			// コンボボックス番号
						int		i_nComboAttr,		// 選択属性値の数
						int*	i_iCmbAttr,			// 選択属性値
						int		i_iInitValue		// 初期表示する属性値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数値を取得する
	//
protected:
	int GetComboAttrICbn(							// 整数値　または　0(未設定)
						int		i_iAttr				// コンボボックス番号
				);

	/////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスの項目を設定する
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスにパネル番号を表示する
protected:
	void SetComboPanelNo(
						int			i_iPanelNo		// パネル番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号選択用コンポボックスよりパネル番号を取得する
	//							＝-1: 未選択
	//							＝ 0: 全
	//							≧ 1: パネル番号
public:
	int GetComboPanelNo();

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
//U		z_mnIA.SetRibbonBarEnt( i_irbKumi, i_irbBunrui, i_crbPartsSpec, i_crbMbr);

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
						int			i_iCdPlc		// 配置コード
				);

	///////////////////////////////////////////////////////////////////////////////
	//	配置コード選択用コンボボックスより配置コードを取得する
	//	（カレントの配置コードを取得する）
	//							＝0 : 任意
	//							＝1 : 壁芯付き
	//							＝2 : 屋根構成線付き
public:
	int GetComboPlcCd();

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックス番号を取得する
protected:
	int GetCheckAttrNo(
						MCCHKATTR	i_iAttr			// 属性ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのタイトルを設定する
protected:
	void SetCheckAttrText(
						int		i_iAttr,			// チェックボックス番号
						MCHAR*	i_sTitle			// タイトル　または　NULL:チェックボックスを表示しない
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのチェックマークを設定する
protected:
	void SetCheckAttrCkb(
						int		i_iChkNo,			// チェックボックス番号
						int		i_iCheckAttr		// チェックマーク　0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用チェックボックスのチェック有無を取得する
	//
protected:
	int GetCheckAttrCkb(							// チェックマーク　0:OFF, 1:ON
						int		i_iChkNo			// チェックボックス番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	構成コード、分類、部品種類IDより、属性値入力モードを求める
protected:
	int MnCalcInpAtMode();

	////////////////////////////////////////////////////////////////////////////
	//	部品属性入力用コンボボックスの設定
protected:
	void InitComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	カレントの属性値入力モードを取得する
	//	(部品属性入力用リボンバーの項目設定中の属性値入力モード)
	//
public:

	///////////////////////////////////////////////////////////////////////////////
	//	リボンバーのコンボックスの設定　本体
protected:
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	部品仕様と寸法形式を部品配置入力データに取り込む
protected:
	void GetPartsSpec( void);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの値を部材配置入力データに取り込む
protected:
	void GetComboAttrA( void);

	///////////////////////////////////////////////////////////////////////////////
	//	チェックボックスのチェックマークを設定する
protected:
	void SetCheckAttr(
						MCCHKATTR	i_iAttr,		// 属性ID
						int			i_iCheckAttr	// チェックマーク　0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	チェックボックスのチェック有無を取得する
	//
public:
	int GetCheckAttr(								// ステイタス0(未設定) 1(設定)
						MCCHKATTR	i_iAttr,		// 属性ID
						int*		o_piCheckAttr	// チェックマーク　0:OFF, 1:ON
				);

};

extern	mnIoPartsAttr z_mnIA;

}// namespace MC