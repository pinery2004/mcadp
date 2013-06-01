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

class MmPartsComboKm {
	MINT		m_iComboPartsNm;				// 部品ID
	MINT		m_iComboMbr;					// 寸法型式
	MINT		m_iComboInpKbn;					// 入力点区分
	MINT		m_iComboMarume;					// 丸めコード
	MINT		m_iComboPlcIzon;				// 配置依存コード
	MINT		m_iComboPanelNo;				// パネル番号
};

class DLL_EXPORT mmIoPartsAttr: public CMmDialogKAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
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

	////////////////////////////////////////////////////////////////////////////
	//	コンストラクタ
public:
	mmIoPartsAttr(){
		m_iIoPartsAttrMd = -1;
	};

	///////////////////////////////////////////////////////////////////////////////
	//	ダイアログの設定と取り込み
public:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo種類	1:入力点区分コード
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);


	//==================================//
	//			   8. 部品名			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスの項目を設定する
//protected:
public:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名項目番号で選択する
//protected:
public:
	void SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// 部品名項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	部品名コンポボックスを部品名で選択する
	//							＝-1: 該当なし
	//							≧ 0: 部品ID
//protected:
public:
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

	//==================================//
	//			  9. メンバー			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式選択用コンポボックスの項目を設定する
//protected:
public:
	void InitComboMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式項目番号で選択する
//protected:
public:
	void SelectComboMbrByKmId(
						int			i_iKmIdMbr		// 寸法型式項目番号
				);

	///////////////////////////////////////////////////////////////////////////////
	//	寸法型式コンボボックスを寸法形式で選択する
	//							＝-1: 該当なし
	//							≧ 0: 寸法型式ID
//protected:
public:
	int SelectComboMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// 寸法型式
				);

	//==================================//
	//			  9. 属性値				//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	構成コード、分類、部品種類IDより、属性値入力モードを求める
protected:
	int MnCalcInpAtMode();

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
	void InitComboAttrEntry(
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
				)
	{
			RibbonIO( MINIT_COMBO_ATTR, i_iIoPartsAttrMd);

	}

	/////////////////////////////////////////////////////////////////////////////
	//	属性値入力モードで部品属性入力用ダイアログの項目を設定する
	//	 (コンボボックスとチェックボックスの項目を設定する)
	//	
public:
	void InitComboAttrXqt(
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
//protected:
public:									// 仮設定
	void InitComboParts();

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの値を取り込む
public:
	void GetComboAttrAEntry( void)
	{
		RibbonIO( MGET_PARTS_ATTRA);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの値を取り込む
protected:
	void GetComboAttrAXqt( void);

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
						int			i_iAttr,		// コンボボックス番号
						MCHAR*		i_sTitle		// タイトル
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンポボックスに実数値の項目(一覧)を設定する
protected:
	void InitComboAttrR(
						int			i_iAttr,		// コンボボックス番号
						int			i_nComboAttr,	// 選択属性値の数
						MREAL*		i_rComboAttr,	// 選択属性値
						MREAL		i_rInitValue	// 初期表示する属性値
				);

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
public:
	void SetComboAttrREntry(
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL		i_rValue		// 表示する実数値
				)
	{
		RibbonIO( MSET_COMBO_ATTRR, i_iAttr, i_rValue);
	}

	//////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
protected:
	void SetComboAttrRXqt(
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL		i_rValue		// 表示する実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの実数値を取得する
//protected:
public:
	int GetComboAttrR(								// ステイタス0(未設定) 1(設定)
						MCCMBATTR	i_iAttr,		// 属性ID
						MREAL*		o_prValue		// 実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスに実数値を表示する
protected:
	void SetComboAttrRCbn(
						int			i_iAttr,		// コンボボックス番号
						MREAL		i_rValue		// 表示する実数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの実数値を取得する
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) 実数値　または　0(未設定)
						int			i_iAttr			// コンボボックス番号
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
	//	属性値入力用コンボボックスに整数値を表示する
protected:
	void SetComboAttrI(
						MCCMBATTR	i_iAttr,		// 属性ID
						int			i_iValue 		// 表示する整数値
				);

	///////////////////////////////////////////////////////////////////////////////
	//	属性値入力用コンボボックスの整数を取得する
//protected:
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
	//	属性値入力用コンボボックスの整数値を取得する
	//
protected:
	int GetComboAttrICbn(							// 整数値　または　0(未設定)
						int			i_iAttr			// コンボボックス番号
				);

//U	/////////////////////////////////////////////////////////////////////////////
//	//	パネル番号コンポボックスの項目を設定する
//protected:
//	void InitComboPanelNo();
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	パネル番号コンポボックスにパネル番号を表示する
//protected:
//	void SetComboPanelNoXqt(
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

};
extern	mmIoPartsAttr z_mmIA;

}// namespace MC