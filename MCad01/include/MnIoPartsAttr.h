#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#include "MmIoPartsAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100
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

// 入力属性　意匠と構造の共通項目
class InpAttrIK
{
public:
	int			m_iComboInpKbn;						// 入力点区分
	int			m_iComboMarume;						// 丸めコード
	int			m_iComboPlcIzon;					// 配置依存コード

	MPKOSEI		m_iInpGp;							// 入力構成		(屋根、小屋、天井、耐力壁、壁、床、土台、基礎)
	MPBUNRUI	m_iInpBr;							// 入力種類		(部材、金物、パネル、その他)
	MPSELECT	m_iInpSel;							// 入力選択		選択1、選択2、選択3						未使用

	int			m_iComboPartsNm;					// 部品名
	int			m_iComboMbr;						// 寸法型式
};

// 入力属性　意匠+構造
class InpAttrA
{
public:
	int			m_iCurCategory;						// カレントカテゴリ　1:意匠, 2:構造, 3:共通
	int			m_iInpKai;							// 入力階			(1階,2階,3階)

	MPPROC		m_iSInpProc;						// 意匠: 入力処理	(住戸、住棟、物件、屋根、敷地、壁量)

	InpAttrIK	m_IK[2];							// 意匠と構造の共通項目

	int			m_iComboPanelNo;					// 構造: パネル番号
	bool		m_bKDspBuzai;						// 構造: 部材表示フラグ
	bool		m_bKDspKanagu;						// 構造: 金物表示フラグ
	bool		m_bKDspGohan;						// 構造: 合板表示フラグ

	MPATTR		m_iAttr;							// 構造: 属性値入力モード

// ======== 部材用 ========
	MREAL		m_rLngH;							// 長さ補正値
	MREAL		m_rSinZ;							// 材軸芯ずれ量
	MREAL		m_rHaiZ;							// 配置点ずれ量
	MREAL		m_rZ1;								// 取り付け高さ
	MREAL		m_rZ2;								// ＲＯＨ
	MREAL		m_rIntv;							// 間隔
	int			m_iNum;								// 本数

// ======== パネル用 ========
	MREAL		m_rLngH2;							// パネル幅補正値
	MREAL		m_rOkuH;							// 手前側補正値、奥行き補正値
	MREAL		m_rOku;								// 奥行き
	int			m_iKoubai;							// 屋根勾配
	MREAL		m_rNokiDe;							// 軒の出
	MREAL		m_rKerabanoDe;						// ケラバの出
};

class DLL_EXPORT mnIoPartsAttr
{
	friend CMainFrame;
	friend CMCadApp;
	friend CMmDialogKAttr;
	friend mmIoPartsAttr;

protected:
	MPMODE		m_iInpMd;							// 創成モード		(削除、修正、移動、複写、属性表示)

	InpAttrA	m_IA;								// 入力属性

	////////////////////////////////////////////////////////////////////////////
	//	コンストラクタ
public:
	mnIoPartsAttr();

	////////////////////////////////////////////////////////////////////////////
	//	属性値入力用
protected:
	ComboTp		m_iComboTp;							// コンボ種類
	int			m_iCdArg1;							// 設定コード1 整数
	MREAL		m_rCdArg2;							// 設定コード2 実数
	int			m_iSts;								// ステイタス

	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、リボンバーの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
protected:
	MPKOSEI		m_iRBKosei;							// 構造	構成
	MPBUNRUI	m_iRBBunrui;						// 構造	分類
	MCHAR*		m_sRBBuhin;							// 部品
	MCHAR*		m_sRBMbr;							// 部品メンバー

	// 部品名コンボボックス
	int		m_nComboIdPartsSpec;					// 表示項目数
	int		m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// 表示項目対応部品ID
	int		m_iComboKmIdPartsNm;					// 部品名カレント選択項目番号

	// 寸法型式選択用コンボボックス
	int		m_nComboMbrId;							// 表示項目数
	int		m_iComboMbrId[MX_CMB_CDMEMBER];			// 表示項目対応寸法型式ID
	int		m_iComboKmIdMbr;						// 寸法形式カレント選択項目番号


	///////////////////////////////////////////////////////////////////////////////
	//	リボンバーの設定と取り込み
protected:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo種類	1:入力点区分コード
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);

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

	///////////////////////////////////////////////////////////////////////////////
	//	構成コード、分類、部品種類IDより、属性値入力モードを求める
protected:
	int MnCalcInpAtMode();

	///////////////////////////////////////////////////////////////////////////////
	//	部品仕様と寸法形式を部品配置入力データに取り込む
protected:
	void GetPartsSpec( void);

	//==================================//
	//		 1. カレントカテゴリ		//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	カレントカテゴリ	
public:
	void	SetCurCategory(
						int i_iCurCategory			// カレントカテゴリ　1:意匠, 2:構造, 3:共通
				)
	{
		m_IA.m_iCurCategory = i_iCurCategory;

	}

	int	GetCurCategory()
	{
		return m_IA.m_iCurCategory;
	}

	// 入力属性　意匠と構造の共通項目のポインタを取得
	InpAttrIK* GetpInpAttr()
	{
		int iIK = m_IA.m_iCurCategory - 1;
		ASSERT( iIK >=0 && iIK <=1); 
		return &m_IA.m_IK[iIK];
	}

	//==================================//
	//			  2. 入力階				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	階				１階、２階、３階
public:
	void SetInpKai(
						int	 		i_iInpKai		// 階	
				)
	{
		m_IA.m_iInpKai = i_iInpKai;
	}

public:
	int GetInpKai()
	{
		return m_IA.m_iInpKai;
	}

	//==================================//
	//			3. 入力点区分			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	コンボボックスに入力点区分を表示し
	//	カレントの入力点区分を設定する処理を起動
	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
public:
	void SelectComboInpKbnByInpKbnCdEntry(
						int			i_iCdCdInpKbn	// 入力点区分
				)
	{
		RibbonIO( MSET_INPUT_KUBUN_CD, i_iCdCdInpKbn);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	コンボボックスに入力点区分を表示し
	//	カレントの入力点区分を設定する	(本体)
protected:
	void SelectComboInpKbnByInpKbnCdXqt(
						int			i_iCdCdInpKbn	// 入力点区分
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
	int GetComboInpKbnCd();

	//==================================//
	//			4. 丸めコード			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	丸目コード選択用コンボボックスに丸目コードを表示し
	//	カレントの丸目コードを設定する処理を起動
	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
public:
	void SelectComboMarumeByMarumeCdEntry(
						int			i_iCdMarume		// 丸目コード
				)
	{
		RibbonIO( MSET_INPUT_MARUME_CD, i_iCdMarume);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	丸目コード選択用コンボボックスに丸目コードを表示し
	//	カレントの丸目コードを設定する	(本体)
protected:
	void SelectComboMarumeByMarumeCdXqt(
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

	//==================================//
	//			 5. 配置依存コード			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	配置依存コード選択用コンボボックスに配置依存コードを表示し
	//	カレントの配置依存コードを設定する処理を起動
	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
public:
	void SelectComboPlcIzonCdByPlaceCdEntry(
						int			i_iCdPlc		// 配置依存コード
				)
	{
		RibbonIO( MSET_INPUT_PLACE_CD, i_iCdPlc);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	配置依存コード選択用コンボボックスに配置依存コードを表示し
	//	カレントの配置依存コードを設定する	(本体)
protected:
	void SelectComboPlcIzonCdByPlaceCdXqt(
						int			i_iCdPlc		// 配置依存コード
				);

	///////////////////////////////////////////////////////////////////////////////
	//	配置依存コード選択用コンボボックスより配置依存コードを取得する
	//	（カレントの配置依存コードを取得する）
	//							＝0 : 任意
	//							＝1 : 壁芯付き
	//							＝2 : 屋根構成線付き
public:
	int GetComboPlcIzonCd();

	//==================================//
	//	 6～9. 組,分類,部品名,メンバー	//
	//==================================//
	////////////////////////////////////////////////////////////////////////////
	//　 部品入力用、リボンバーの部品選択用項目を設定する処理を起動
	//		組、分類、部品名、寸法型式
	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
public:
	int	SetRibbonBarEntry( 							// ステイタス 0:正常 -1:エラー
					MPKOSEI		i_irbKumi,			// 構造組
					MPBUNRUI	i_irbBunrui,		// 構造分類
					MCHAR*		i_crbPartsSpec,		// 部品種類		(部品名)
					MCHAR*		i_crbMbr = NULL		// 部品メンバー	(寸法型式)
				)
	{
		int	ist;
		m_iRBKosei	= i_irbKumi;
		m_iRBBunrui = i_irbBunrui;
		m_sRBBuhin	= i_crbPartsSpec;
		m_sRBMbr	= i_crbMbr;

		ist = RibbonIO( MSET_RIBBON_BAR);

		return ist;
	}

	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、リボンバーの部品選択用項目を設定する(本体)
	//		組、分類、部品名、寸法型式	(本体)
protected:
	int	SetRibbonBarXqt( 								// ステイタス 0:正常 -1:エラー
					MPKOSEI		i_irbKumi,			// 構造組
					MPBUNRUI	i_irbBunrui,		// 構造分類
					MCHAR*		i_crbPartsSpec,		// 部品種類		(部品名)
					MCHAR*		i_crbMbr = NULL		// 部品メンバー	(寸法型式)
				);

	//==================================//
	//			  6. 構成(組)			//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// 構造組		屋根、小屋、天井、耐力壁、壁、床、基礎
public:
	void SetKCdGp(
						MPKOSEI		i_iKInpGp		// 構造　構成(組)
				)
	{
		m_IA.m_IK[1].m_iInpGp = i_iKInpGp;
	}

public:
	MPKOSEI GetKCdGp()
	{
		return m_IA.m_IK[1].m_iInpGp;
	}

	//==================================//
	//			  7. 分類				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// 構造入力分類		部材、金物、パネル、その他
public:
	void SetKCdBr(
						MPBUNRUI		i_iKInpBr		// 構造　種類
				)
	{
		m_IA.m_IK[1].m_iInpBr = i_iKInpBr;
	}

public:
	MPBUNRUI GetKCdBr()
	{
		return m_IA.m_IK[1].m_iInpBr;
	}

	//==================================//
	//			   8. 部品名			//
	//==================================//
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

	//==================================//
	//			  9. メンバー			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスの項目を設定する
protected:
	void InitComboMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式項目番号で選択する
protected:
	void SelectComboMbrByKmId(
						int			i_iKmIdMbr		// 寸法型式項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式で選択する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
protected:
	int SelectComboMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法形式から寸法型式コンボボックスの寸法型式項目番号を取得する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
public:
	int GetComboMbrKmId(
						MCHAR*		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスより寸法型式IDを取得する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
public:
	int GetComboMbrCdId(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスより寸法型式IDを取得する
	//	（カレントの寸法型式IDを取得する）
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	int GetCurMbrCdId();

	//==================================//
	//			  10. 属性				//
	//==================================//
//U	未使用
//	////////////////////////////////////////////////////////////////////////////
//	//	部品属性入力用コンボボックスの設定処理を起動
//	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
//public:
//	void InitComboPartsEntry()
//	{
//		RibbonIO( MSET_COMBO_PARTS);
//	}

	////////////////////////////////////////////////////////////////////////////
	//	部品属性入力用コンボボックスの設定	(本体)
protected:
	void InitComboPartsXqt();

	//////////////////////////////////////////////////////////////////////////////
	// 部品属性入力用コンボボックスを取得する
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						int			i_iAttr			// コンボボックス番号
				);

	//==================================//
	//			  11. 選択				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// 構造入力選択		選択1、選択2、選択3						未使用
public:
	void SetKSel(
						MPSELECT	i_iSel			// 選択番号
				)
	{
		m_IA.m_IK[1].m_iInpSel = i_iSel;
	}

public:
	MPSELECT GetKSel()
	{
		return m_IA.m_IK[1].m_iInpSel;
	}

	//==================================//
	//			  12. 注記				//
	//==================================//
	//==================================//
	//			  13. 部種				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	部材、金物、合板のチェックボックスの表示フラグを設定
public:
	void SetKCdBrB(
						bool		i_bDspBuzai,	// 部材表示フラグ
						bool		i_bDspKanagu,	// 金具表示フラグ
						bool		i_bDspGohan		// 合板表示フラグ
				)
	{
		m_IA.m_bKDspBuzai  = i_bDspBuzai;
		m_IA.m_bKDspKanagu = i_bDspKanagu;
		m_IA.m_bKDspGohan  = i_bDspGohan;
	}

	//==================================//
	//			 14. パネル				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスの項目を設定する
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスにパネル番号を表示する
	//	(別プロセスからのエントリーでSendMessageを使用して本体を実行)
public:
	void SetComboPanelNoEntry(
						int			i_iPanelNo		// パネル番号
				)
	{
		RibbonIO( MSET_COMBO_PANELNO, i_iPanelNo);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号コンポボックスにパネル番号を表示する	(本体)
protected:
	void SetComboPanelNoXqt(
						int			i_iPanelNo		// パネル番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	パネル番号選択用コンポボックスよりパネル番号を取得する
	//							＝-1: 未選択
	//							＝ 0: 全
	//							≧ 1: パネル番号
public:
	int GetComboPanelNo();

	//==================================//
	//			 15. 属性選択			//
	//==================================//
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
						int		i_iChkNo,			// チェックボックス番号
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

	//==================================//
	//			 16. 創成モード			//
	//==================================//
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

	//==================================//
	//			 17. 意匠処理			//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// 意匠入力構成		住戸、住棟、物件、屋根、敷地、壁量
public:
	void SetSCdProc(
						MPPROC		i_iSInpProc		// 設計　構成
				)
	{
		m_IA.m_iSInpProc = i_iSInpProc;
	}
public:
	MPPROC GetSCdPrc()
	{
		return m_IA.m_iSInpProc;
	}

	//==================================//
	//			 18. 意匠組				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// 構造組		屋根、小屋、天井、耐力壁、壁、床、基礎
public:
	void SetSCdGp(
						MPKOSEI		i_iSInpGp		// 設計　構成
				)
	{
		m_IA.m_IK[0].m_iInpGp = i_iSInpGp;
	}
public:
	MPKOSEI GetSCdGp()
	{
		return m_IA.m_IK[0].m_iInpGp;
	}

};

extern	MC::mnIoPartsAttr z_mnIA;

}// namespace MC