#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhPlcPartsLib.h
//
//		部品配置用関数
//
//
//  K.Matsu           13/04/27    Created.
//==========================================================================================

#include "MhDefParts.h"
#include "MgPoint.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_HAITIIN_DO
	#pragma message( "<<< MC::HaitiIn・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::HaitiIn・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mhHaitiIn
{
public:
	/////////////////////////////////////////////////////////////////////////////////
	////	配置コード選択用コンボボックスに配置コードを表示し
	////	カレントの配置コードを設定する

	//static void SelectComboPlcCdByPlcCd(
	//						MINT		i_iCdPlc	// 配置コード
	//				);

	/////////////////////////////////////////////////////////////////////////////////
	////	配置コード選択用コンボボックスより配置コードを取得する
	////	（カレントの配置コードを取得する）
	////							＝0 : 任意
	////							＝1 : 壁芯付き
	////							＝2 : 屋根構成線付き

	//static MINT GetComboPlcCd();


	/////////////////////////////////////////////////////////////////////////////
	//	部品配置を取得する
	//	返値 =-1: オーバーフロー, ≧0: 選択部品配置数

	static MINT GetParts(
							MINT		i_iKai,			// 階
							MINT		i_iIdPartsSpec,		// 部品ID
					const	MCHAR*		i_sGeneralName,	// 総称 または NULL
					const	MCHAR*		i_sNmParts1,		// 操作用部材名 または NULL
							MINT		i_szPlcEn,		// 部品配置最大数
					class	mhPlcParts*	*o_pPlcEn,		// 選択部品配置
					class	MPOSITION*	o_pPlcpos = NULL// 選択[部品配置]位置 または NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	部品配置を調べる
	//	返値 true : 対象部品配置, false : 対象外部品配置

	static bool CheckParts(
							MINT		i_iKai,			// 階 または NULL
							MINT		i_iIdPartsSpec,		// 部品ID または NULL
					const	MCHAR*		i_sGeneralName,	// 総称 または NULL
					const	MCHAR*		i_sNmParts1,		// 操作用部材名 または NULL
					class	mhPlcParts*	i_pPlcEn		// 調査部品配置
					);

	/////////////////////////////////////////////////////////////////////////////
	//  部材配置を検索する
	//	返値 検索結果　または　null:ヒットなし
	static mhPlcParts* SrchBuzai(
					class	MmWndInfo*	i_pWndInfo,		// ウィンドウ管理情報
					class	MgPoint2D&	i_ptMouthR,		// 検索指示座標
							MINT		i_iCdBuzai,		// 部材コード　または　NULL(全)
														// MP_BZICD_PANEL(全パネル)
					class	MgPolyg2D*	o_ppgPartsShape	// 検出多角形　または　NULL
					);


	/////////////////////////////////////////////////////////////////////////////
	//  配置部品の形状を求める
	static void PartsShape(
					class	mhPlcParts*	i_pWndInfo,		// ウィンドウ管理情報
					class	MgPolyg2D*	o_pgPartsShape	// 部材の形状
					);

	/////////////////////////////////////////////////////////////////////////////
	//	１配置部品を表示する
	static void DrawPart( 
					class	msCod*		i_pCod,			// 座標系
							MINT		i_iGpC,			// 構成
					class	mhPlcParts*	i_pPlcEn		// 部品配置管理情報
					);

	/////////////////////////////////////////////////////////////////////////////
	//	部材の配置点と長さ補正値を修正
	static void mhHaitiIn::MhModBzPH(
							MINT		iCdInpKbCd,		// (I  ) 入力点区分コード
							MINT		iMov,			// (I  ) 修正側　(0:始点、1:終点)
					const	MgPoint3D	&PtInt,			// (I  ) 配置点
							MREAL		rLH,			// (I  ) 長さ補整値
							mhPlcParts	*pPlcEnR		// (I O) 長さ調整部材
					);

	/////////////////////////////////////////////////////////////////////////////
	//	調整先が部材で示された部材の長さ調整
	static MINT MhAdjBzL(								// (  O) ステイタス　
														//	MC_PARALLEL (-1) 交差なし（平行）
														//	MC_TWIST    (-2) 交差なし（ねじれ）
														//	MC_NINT	    (0)	交差なし
														//	MC_INT      (1)	交差あり
							MINT		iKati,			// (I  ) 勝ち負けフラグ(1:勝ち、0:負け)
							mhPlcParts*	pPlcEn1,		// (I O) 長さ調整部材1
					const	MgPoint3D	&Pt1,			// (I  ) 部材1の長さ調整する側を示す最寄の点
							mhPlcParts*	pPlcEn2		// (I  ) 長さ調整先を示す部材2
					);

	/////////////////////////////////////////////////////////////////////////////
	//	調整先が平行部材で示された部材の長さ調整
	static void MhAdjBzL(								// (  O) ステイタス　
														//	MC_PARALLEL (-1) 交差なし（平行）
														//	MC_TWIST    (-2) 交差なし（ねじれ）
														//	MC_NINT	    (0)	交差なし
														//	MC_INT      (1)	交差あり
							mhPlcParts*	pPlcEn1,		// (I O) 長さ調整部材1
					const	MgPoint3D	&Pt1,			// (I  ) 部材1の長さ調整する側を示す最寄の点
							mhPlcParts*	pPlcEn2,		// (I  ) 長さ調整先を示す部材2
					const	MgPoint3D	&Pt2			// (I  ) 部材2の長さ調整先を示す最寄の点
					);

	/////////////////////////////////////////////////////////////////////////////
	//	調整先が点座標で示された部材の長さ調整
	static void MhAdjBzL(
							mhPlcParts*	pPlcEn1,	// 長さ調整部材1
					const	MgPoint3D	&Pt1,		// 部材1の長さ調整する側を示す最寄の点1
					const	MgPoint3D	&Pt2		// 長さ調整先を示す点2
					);

	/////////////////////////////////////////////////////////////////////////////
	//	長さ調整後の部材に接触する部材と交差する部材を求める
	static void MmSrchCrossBuzai(
							MmWndInfo*	pWndInfo,		// (I  ) ウィンドウ管理情報
							mhPlcParts*	pBziInfo1,		// (I  ) 長さ調整部材
							MINT		iBuzaiCd,		// (I  ) 部材コード
							mhPlcParts**	pbTchBzi,		// (  O) 長さ調整後の部材に接触する部材
							mhPlcParts**	pbCrsBzi		// (  O) 長さ調整後の部材と交差する部材
					);

	/////////////////////////////////////////////////////////////////////////////
	//	長さ調整前後で接触状態と交差状態が変化する部材を求める
	static void MhChngCrossBuzai(
							mhPlcParts	**pbTchBziI,	// (I  ) 長さ調整前に長さ調整部材に接触する部材
							mhPlcParts	**pbCrsBziI,	// (I  ) 長さ調整前に長さ調整部材と交差する部材
							mhPlcParts	**pbTchBziO,	// (I  ) 長さ調整後に長さ調整部材に接触する部材
							mhPlcParts	**pbCrsBziO,	// (I  ) 長さ調整後に長さ調整部材と交差する部材
							mhPlcParts	**pbFRtoTCBzi,	// (  O) 長さ調整前に長さ調整部材と離れていたが
														//		 長さ調整後に接触または交差した部材
							mhPlcParts	**pbTCtoFRBzi,	// (  O) 長さ調整前に長さ調整部材と接触または交差していたが
														//		 長さ調整後に離れた部材
							mhPlcParts	**pbTCtoTCBzi	// (  O) 長さ調整前に長さ調整部材に接触または交差していたが
														//		 、長さ調整後にも接触または交差している部材
					);

	/////////////////////////////////////////////////////////////////////////////
	//	屋根を配置する

	static MINT RoofPlc(								// ステイタス	0: 正常、-1: 屋根配置エラー
			const	class	MgPolyg2D&	i_pgJim,		// 地廻り区画
			const	class	MgGInt&		i_GifInp,		// 地廻り線種類(仮想キー(nflag)  MK_SHIFT(004): シフトキー)
			const	class	MgPoint2D&	i_pth			// 方向点
					);

	/////////////////////////////////////////////////////////////////////////////
	//	屋根面を検索する
	//	返値 =NULL: 該当屋根面なし !=NULL: 該当屋根面数
	static class MhRfm*	SrchRfm(					// 屋根面　または　NULL
							MINT		i_iMode,		// 検索モード	指示点に該当する屋根面が複数ある場合の優先選択条件
														//				MC_PRI_MIN_AREA(0):	 面積が小を優先
														//				MC_PRI_MIN_HIGHT(1): 高さが小を優先
														//				MC_PRI_MAX_HIGHT(2) | その他: 高さが大を優先	
					const	MgPoint2D&	i_pt1			// 指示点
					);

	////////////////////////////////////////////////////////////////////////////
	//	カレント選択の屋根面を設定する

	static void SetCurRfm(
					class	MhRfm* 		pRfm			// (I  ) カレント選択の屋根面
				);

	////////////////////////////////////////////////////////////////////////////
	//	カレント選択の屋根面を返す
	static MhRfm* GetCurRfm();

};

////////////////////////////////////////////////////////////////////////////
// Input

#define		MAXHAIKABE		500							// 配列制限値
#define		MC_KABE_TOL		44.5						// 壁判定トレランス
#define		MC_MARUME_TOL	44.5						// 丸め対象線分判定トレランス

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPUT_DO
	#pragma message( "<<< MC::Input・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::Input・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mhInput
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//	長さ２点入力

	static MINT GetLen2Pt(
							MINT		i_iMode,		// 入力モード
														//			　0: 長さ２点入力
														//			　1: 連続長さ２点の終点入力
														//					始点は前回入力(pLn)の終点とする
														//			　2: 方向１点入力
					class	MgPoint2D*	o_pptln,		// 入力丸め座標（長さ２点座標 ＋　複数部材の領域をあらわす３点目）
					class	MgPoint2D*	o_pptln_org		// 入力オリジナル座標（長さ２点座標 ＋　複数部材の領域をあらわす３点目） 
					);

	/////////////////////////////////////////////////////////////////////////////
	//	１点入力

	static MINT Get1Pt(
					class	MgPoint2D*	o_ppt1,			// 入力丸め座標（点）
					class	MgPoint2D*	o_ppt1_org		// 入力オリジナル座標（点）
					);

	/////////////////////////////////////////////////////////////////////////////
	//	連続した長さ２点入力用の２点目の入力(外壁入力用)

	static MINT GetLenEPt(
					class	MgLine2D*	o_pLn
					);

	/////////////////////////////////////////////////////////////////////////////
	//	長方形区画入力

	static MINT GetRect2Pt(
					class	MgLine2D*	o_pLn
					);

	/////////////////////////////////////////////////////////////////////////////
	//	区画入力

	static MINT GetArea(
					class	MgPolyg2D*	o_pPg1
					);

	/////////////////////////////////////////////////////////////////////////////
	//	区画入力 
	//	各辺に　シフトキー有無のフラグ付き

	static MINT GetAreaI(
					class	MgPolyg2D*	pPg1,			// (  O) 地廻り区画
					class	MgGInt*		pGifInp			// (  O) 地廻り線種類(仮想キー(nflag)  MK_SHIFT(004): シフトキー)
				);

	/////////////////////////////////////////////////////////////////////////////
	//	壁芯丸め線を取得する

	static void GetMarumeKabeLine(
							MINT		i_iKai,			// 検索階
			const	class	MgPoint2D&	i_pti,			// 入力座標
					class	MgGLine2D*	o_pGLn			// 対象壁芯
					);

	/////////////////////////////////////////////////////////////////////////////
	//	屋根構成線丸め線を取得する
	//
	static void MmGetMarumeYaneLine(
							MINT		iKai,			// 検索階
			const	class	MgPoint2D	&Pi,			// 入力座標
					class	MgGLine2D*	pGLn			// 対象屋根構成線
					);

	/////////////////////////////////////////////////////////////////////////////
	//	丸め
	static void	Marume(									// 座標値を丸める
			const	class	MgPoint2D&	Pi,				// 入力座標
					class	MgPoint2D*	pPo				// 丸め後の座標
				);

};

}// namespace MC