#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#include "MmDialogKAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mmIoPartsAttr・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mmIoPartsAttr・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mmIoPartsAttr: public CMmDialogKAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、ダイアログの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
//S	MPKOSEI		m_iRBKosei;						// 構造	構成
//	MPBUNRUI	m_iRBBunrui;					// 構造	分類
//	MCHAR*		m_sRBBuhin;						// 部品
//	MCHAR*		m_sRBMbr;						// 部品メンバー

protected:
//	int			m_iCdPartsNm;					// 部品名Id
//	int			m_iCdMbr;						// メンバーId
//	MREAL		m_rLengthH1;					// 長さ補正1		(mm)
//	MREAL		m_rLengthH2;					// 長さ補正2		(mm)
//	MREAL		m_rSinzure;						// 芯ずれ			(mm)
//	MREAL		m_rToritukeH;					// 取付高さ			(mm)
//	MREAL		m_rSpan;						// 間隔				(mm)
//	int			m_nHonsu;						// 本数
////S	int			m_iPanelNo;						// パネルNo			(0:全、1〜n)
//
//	int			m_iKobai;						// 勾配
//	MREAL		m_rNokiDe;						// 軒の出
//	MREAL		m_rKerabaDe;					// けらばの出
//
//	MPKOSEI		m_iKInpGp;						// 構造入力構成		(屋根、小屋、天井、耐力壁、壁、床、土台、基礎)
//	MPBUNRUI	m_iKInpBr;						// 構造入力種類		(部材、金物、パネル、その他)
//	MPSELECT	m_iKInpSel;						// 構造入力選択		選択1、選択2、選択3						未使用

	// 部品名コンボボックス
	int m_nComboIdPartsSpec;					// 表示項目数
	int m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// 表示項目対応部品ID
	int m_iComboKmIdPartsNm;					// カレント選択項目番号

	// 寸法型式選択用コンボボックス
	int m_nComboMbrId;							// 表示項目数
	int m_iComboMbrId[MX_CMB_CDMEMBER];			// 表示項目対応寸法型式ID
	int m_iComboKmIdMbr;						// カレント選択項目番号

	int	m_iIoPartsAttrMd;						// 属性値入力モード
												//		MP_AT_AUTO(-1)		:自動設定
												//		MP_AT_NONE(0)		:属性値入力なし
												//		MP_AT_HRZ_PARTS(1)	:水平部材入力
												//		MP_AT_VRT_PARTS(2)	:垂直部材入力
												//		MP_AT_YTPANEL(3)	:床天井パネル入力
												//		MP_AT_YANEPANEL(4)	:屋根パネル入力
												//		MP_AT_ADJLNG(5)		:部材長さ調整入力
												//		MP_AT_YANE(6)		:屋根入力
												//		MP_AT_TATEGU(7)		:建具入力


//S	// 部品属性コンボ番号
//	int m_iCmbAttrN[MC_CMB_N];
//	int m_Combo_Attr[MC_SZ_CMBATTR];
//U	int m_Check_Attr[MC_SZ_CHKATTR];

	////////////////////////////////////////////////////////////////////////////
	//	コンストラクタ
public:
	mmIoPartsAttr(){
		m_iIoPartsAttrMd = -1;
	};

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスの項目を設定する
protected:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名項目番号で選択する
protected:
	void SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// 部品名項目番号
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
	int SelectComboMbrCdByMbrCd(
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
	int GetComboMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスより寸法型式IDを取得する
	//	（カレントの寸法型式IDを取得する）
	//							＝-1: 未選択
	//							≧ 0: 部品ID
public:
	int GetComboMbrCdId();

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
public:
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

//S	/////////////////////////////////////////////////////////////////////////////
//	//	長さ補正1				
//public:
//	void SetLengthH1(
//						MREAL 		i_rLengthH1		// 長さ補正1	
//				)
//	{
//		m_rLengthH1 = i_rLengthH1;
//	}
//public:
//	MREAL GetLengthH1()
//	{
//		return m_rLengthH1;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	長さ補正2				
//public:
//	void SetLengthH2(
//						MREAL 		i_rLengthH2		// 長さ補正2	
//				)
//	{
//		m_rLengthH2 = i_rLengthH2;
//	}
//public:
//	MREAL GetLengthH2()
//	{
//		return m_rLengthH2;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	芯ずれ				
//public:
//	void SetSinzure(
//						MREAL 		i_rSinzure		// 芯ずれ	
//				)
//	{
//		m_rLengthH1 = i_rSinzure;
//	}
//public:
//	MREAL GetSinzure()
//	{
//		return m_rSinzure;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	取付高さ				
//public:
//	void SetToritukeH(
//						MREAL 		i_rToritukeH	// 取付高さ	
//				)
//	{
//		m_rToritukeH = i_rToritukeH;
//	}
//public:
//	MREAL GetToritukeH()
//	{
//		return m_rToritukeH;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	間隔				
//public:
//	void SetSpan(
//						MREAL 		i_rSpan			// 間隔	
//				)
//	{
//		m_rSpan = i_rSpan;
//	}
//public:
//	MREAL GetSpan()
//	{
//		return m_rSpan;
//	}

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
public:
	int GetComboAttrI(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						int*		o_piValue		// 整数値
				);


	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrICbn(
						int			i_iAttr,		// コンボボックス番号
						int			i_iValue 		// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用指定コンポボックスに整数値の項目(一覧)を設定する
protected:
	void InitComboAttrI(
						int			i_iAttr,		// コンボボックス番号
						int			i_nComboAttr,	// 選択属性値の数
						int*		i_iCmbAttr,		// 選択属性値
						int			i_iInitValue	// 初期表示する属性値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数値を取得する
	//
protected:
	int GetComboAttrICbn(							// 整数値　または　0(未設定)
						int			i_iAttr			// コンボボックス番号
				);

//S	/////////////////////////////////////////////////////////////////////////////
//	//	本数
//public:
//	void SetHonsu(
//						int			i_nHonsu		// 本数	
//				)
//	{
//		m_nHonsu = i_nHonsu;
//	}
//public:
//	int GetHonsu()
//	{
//		return m_nHonsu;
//	}

//U	/////////////////////////////////////////////////////////////////////////////
//	//	パネル番号コンポボックスの項目を設定する
//protected:
//	void InitComboPanelNo();
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	パネル番号コンポボックスにパネル番号を表示する
//protected:
//	void SetComboPanelNo(
//						int			i_iPanelNo		// パネル番号
//				);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	パネル番号選択用コンポボックスよりパネル番号を取得する
//	//							＝-1: 未選択
//	//							＝ 0: 全
//	//							≧ 1: パネル番号
//public:
//	int GetComboPanelNo();
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	パネルNo
//public:
//	void SetPanelNo(
//						int 		i_iPanelNo		// 本数	
//				)
//	{
//		m_iPanelNo = i_iPanelNo;
//	}
//public:
//	int GetPanelNo()
//	{
//		return m_iPanelNo;
//	}

//S	/////////////////////////////////////////////////////////////////////////////
//	//	勾配
//public:
//	void SetKobai(
//						int 		i_iKobai		// 勾配	
//				)
//	{
//		m_iKobai = i_iKobai;
//	}
//public:
//	int GetKobai()
//	{
//		return m_iKobai;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	軒の出				
//public:
//	void SetNokiDe(
//						MREAL 		i_rNokiDe		// 軒の出	
//				)
//	{
//		m_rNokiDe = i_rNokiDe;
//	}
//public:
//	MREAL GetNokiDe()
//	{
//		return m_rNokiDe;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	けらばの出				
//public:
//	void SetKerabaDe(
//						MREAL 		i_rKerabaDe		// けらばの出	
//				)
//	{
//		m_rKerabaDe = i_rKerabaDe;
//	}
//public:
//	MREAL GetKerabaDe()
//	{
//		return m_rKerabaDe;
//	}

//S	/////////////////////////////////////////////////////////////////////////////
//	// 構造入力構成		屋根、小屋、天井、耐力壁、壁、床、基礎
//public:
//	void SetKCdGp(
//						MPKOSEI		i_iKInpGp		// 構造　構成(組)
//				)
//	{
//		m_iKInpGp = i_iKInpGp;
//	}
//public:
//	MPKOSEI GetKCdGp()
//	{
//		return m_iKInpGp;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////
//	// 構造入力種類		部材、金物、パネル、その他
//public:
//	void SetKCdBr(
//						MPBUNRUI	i_iKInpBr		// 構造　種類
//				)
//	{
//		m_iKInpBr = i_iKInpBr;
//	}
//public:
//	MPBUNRUI GetKCdBr()
//	{
//		return m_iKInpBr;
//	}
//
//	////////////////////////////////////////////////////////////////////////////
//	// 部品入力用、ダイアログの部品選択用項目を設定する
//	//		組、分類、部品タイプ、寸法型式
//public:
//	void SetRibbonBarEnt( 							// ステイタス 0:正常 -1:エラー
//						MPKOSEI		i_irbKumi,		// 構造	組
//						MPBUNRUI	i_irbBunrui,	// 構造	分類
//						MCHAR*		i_crbPartsSpec,	// 部品種類
//						MCHAR*		i_crbMbr = NULL	// 部品メンバー()
//				)
//	{
//		m_iRBKosei	= i_irbKumi;
//		m_iRBBunrui = i_irbBunrui;
//		m_sRBBuhin	= i_crbPartsSpec;
//		m_sRBMbr	= i_crbMbr;
//
//		MmDialogKAttr();
//	}

	///////////////////////////////////////////////////////////////////////////////
	//	構成コード、分類、部品種類IDより、属性値入力モードを求める
protected:
	int MnCalcInpAtMode();

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
public:									// 仮設定
	void InitComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	カレントの属性値入力モードを取得する
	//	(部品属性入力用ダイアログの項目設定中の属性値入力モード)
	//
public:
	int GetAtMd()
	{
		return m_iIoPartsAttrMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	属性値入力モードで部品属性入力用ダイアログの項目を設定する
	//	 (コンボボックスとチェックボックスの項目を設定する)
	//	
public:
	void InitComboAttr(
						int	i_iIoPartsAttrMd = MP_AT_NONE	// 属性値入力モード
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
	//	ダイアログのコンボックスの設定　本体
protected:
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの値を取り込む
protected:
	void GetComboAttrA( void);

};

extern	mmIoPartsAttr z_mmIA;

}// namespace MC