#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: McSystemProperty.
//
//		システムプロパティ
//
//  K.Matsu			11/01/09    Created.
//==========================================================================================

#ifdef DLL_EXPORT_SYSTEMPROPERTY
	#undef DLL_EXPORT_YSTEMPROPERTY
#endif

#ifdef DLL_EXPORT_SYSTEMPROPERTY_DO
	#pragma message( "<<< McSystemProperty・dll_EXport >>>")
	#define DLL_EXPORT_SYSTEMPROPERTY			__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_SUB_DO
			#define DLL_EXPORT_SYSTEMPROPERTY
		#else
//			#pragma message( "=== McSystemProperty・dll_IMport ===")
			#define DLL_EXPORT_SYSTEMPROPERTY	__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_SYSTEMPROPERTY
	#endif
#endif

namespace MC
{

#define		MMAX_KAI	3

enum	MSYSTEMCOLOR {
	MM_COLOR_GRID_LINE = 0,							// グリッド線表示色
	MM_COLOR_GRID_TEXT,								// グリッド番号表示色
	MM_COLOR_MARUME,								// 丸め線表示色
	MM_COLOR_CURSOR,	   							// クロスヘアーカーソル色
	MM_COLOR_DRAGGING,	   							// ドラッギング色
	MM_COLOR_HITBZI,	   							// ヒット部材色
	MM_COLOR_TEMP,		   							// テンポラリ選択表示色
	MM_COLOR_BACKGROUND,   							// 背景色
	MM_COLOR_DOUKAIKABESIN,							// 同階壁芯青色
	MM_COLOR_KAKAIKABESIN,  						// 下階壁芯橙色
	MM_COLOR_JYOUKAIKABESIN,						// 上階壁芯線色,
	MM_COLOR_DOUKAITAIKABESIN,						// 同階耐力壁芯青色IN,
	MM_COLOR_KAKAITAIKABESIN,						// 下階耐力壁芯橙色N,
	MM_COLOR_JYOUKAITAIKABESIN,						// 上階壁耐力芯線色SIN,
	MM_COLOR_DOUKAISIJIKABESIN,						// 同階支持壁芯青色SIN,
	MM_COLOR_KAKAISIJIKABESIN,						// 下階支持壁芯橙色IN,
	MM_COLOR_JYOUKAISIJIKABESIN,					// 上階支持壁芯線色ESIN,
	MM_COLOR_KISOSIN,	   							// 基礎芯線色
	MM_COLOR_KABESEN,	   							// 壁表示時の壁線色			
	MM_N_COLOR										// MSYSTEMCOLORの数
};
enum	MSYSTEMREAL {
	MM_REAL_PITCH = 0,								// グリッド・ピッチ
	MM_REAL_GRID_SPC,  								// グリッド番号表示空き(ポイント)
	MM_REAL_GRID_HEI,  								// グリッド文字高さ(ポイント)
	MM_REAL_GRID_AKI,  								// グリッド枠表示空き
	MM_N_REAL											// MSYSTEMSTRの数	 
};
enum	MSYSTEMINT {
	MM_INT_GRID_N = 0,								// 初期北側グリッド数
	MM_INT_GRID_W,	  								// 初期西側グリッド数
	MM_INT_GRID_S,	  								// 初期南側グリッド数
	MM_INT_GRID_E,	  								// 初期東側グリッド数
	MM_N_INT										// MSYSTEMREALの数
};
enum	MSYSTEMSTR {
	MM_STR_TABLE = 0,								// テーブルフォルダ名
	MM_STR_PARTSTABLE,								// [テーブル\]部品フォルダ名
	MM_STR_ATTR,									// 属性フォルダ名
	MM_STR_TEX,										// テクスチャフォルダ名
	MM_STR_FIG,										// 図形フォルダ名
	MM_STR_INIFILE,									// MCAD.iniフォルダ名
	MM_STR_LOGFILE,									// LOGファイル名 
	MM_STR_TRACEFILE,								// TRACEファイル名
	MM_STR_CSV_MEMBER,								// 寸法型式.csv 
	MM_STR_CSV_PARTS,								// 部品.csv 
	MM_STR_CSV_ATTR,								// 属性.csv 
	MM_STR_CSV_DRAFTSZ,								// 図面サイズ.csv 
	MM_STR_CSV_KOUSEI,								// 構成.csv 
	MM_STR_CSV_BUNRUI,								// 分類.csv 
	MM_ERR_POINTER,									// メモリ取得エラー
	MM_ERR_OVERFLOW,								// 領域オーバフローエラー
	MM_ERR_ID,										// ＩＤ誤りエラー
	MM_ERR_INPUT,									// 入力エラー
	MM_ERR_NUM_OVER,								// 処理可能個数超えエラー
	MM_ERR_VECT_ZERO,								// ゼロベクトルで処理不可エラー
	MM_ERR_INPUT_ZERO,								// 数値ゼロで処理不可エラー
	MM_ERR_OFFSET,									// オフセット誤りエラー
	MM_ERR_FILEOPEN,								// ファイルオープンエラー
	MM_ERR_OTHER,									// その他エラー
	MM_ERR_SYSTEMEXIT,								// システム終了します
	MM_N_STR										// MSYSTEMSTRの数
};

enum	MSYSTEMPATH {
//N	MM_PATH_ROOT_FLDR = 0,							// 実行ファイル(ルート)ディレクトリ
//N	MM_PATH_PARTS_FLDR,								// 構造部品テーブル
	MM_PATH_SYS_ENV_FLDR,							// システム環境ディレクトリ
	MM_N_PATH										// MSYSTEMPATHの数
};

//===========================================================================
//		環境変数
//
enum MPPATHENV {
	MP_PATH_ROOT = 1,								// ルート
	MP_PATH_TABLE,									// テーブル
	MP_PATH_PARTSTABLE,								// テーブル\部品
	MP_PATH_ATTR,									// 属性
	MP_PATH_TEX,									// テクスチャ(TEXTURE)
	MP_PATH_FIG										// 図形
};

enum	MSTNDH {
	MM_STNDH_SGL = 0,								//ZZZZZ
	MM_STNDH_KISO,
	MM_STNDH_LOWER,
	MM_STNDH_UPPER,
	MM_STNDH_CEILING,
	MM_STNDH_ROOF,
	MM_STNDA_NOKI,
	MM_N_STNDH
};

/*
class	MmStndH
{
public:
	MREAL	rKiso;
	MREAL	rLower;
	MREAL	rUpper;
	MREAL	rCeiling;
	MREAL	rRoof;
};
*/
class DLL_EXPORT_SYSTEMPROPERTY mcs
{
private:
//	システム定数
static DWORD	m_Color[MM_N_COLOR];			// 色
static MREAL	m_Real[MM_N_REAL];				// 実数
static MINT		m_Int[MM_N_INT];				// 整数
static MCHAR*	m_Str[MM_N_STR];				// 文字列
static MCHAR*	m_Path[MM_N_PATH];				// PATH
static MREAL	m_Stnd[MMAX_KAI][MM_N_STNDH];	// 基準高さ、厚さ　

public:
/////////////////////////////////////////////////////////////////////////////
//	システムプロパティの初期化
static void		Init();

/////////////////////////////////////////////////////////////////////////////
//	システム色を取得する
static DWORD	GetColor( MSYSTEMCOLOR iCol);

/////////////////////////////////////////////////////////////////////////////
//	システム実数定数を取得する
static MREAL	GetReal( MSYSTEMREAL iReal);

/////////////////////////////////////////////////////////////////////////////
//	システム整数定数を取得する
static MINT		GetInt( MSYSTEMINT iInt);

/////////////////////////////////////////////////////////////////////////////
//	システム文字列定数を取得する
static _TCHAR*	GetStr( MSYSTEMSTR iStr);

/////////////////////////////////////////////////////////////////////////////
//	PATH定数を取得する
static _TCHAR*	GetPath( MSYSTEMPATH iPath);

/////////////////////////////////////////////////////////////////////////////
//	システム環境　ファイルパスを得る
static MINT		GetEnvPath(	// ステイタス	0:正常	!=0:エラー
						MPPATHENV	i_iType,	// 環境パス種類
												//	MM_STR_TABLE:	テーブル
												//	MM_STR_ATTR:	属性
												//	MM_STR_TEX:	テクスチャ(TEXTURE)
												//	MM_STR_FIG:	図形
						MCHAR*		i_cFile,	// ファイル名
						MCHAR*		o_cPath,	// パス名
						int			i_ncPath	// パス名最大文字数+1
				);

/////////////////////////////////////////////////////////////////////////////
//	基準高さを設定する
static void		SetStnd(
						MINT		i_iKai,		// 階　(1,2,3)
						MSTNDH		i_iKTCode,	// 基準高さコード
						MREAL		i_rHA		// 基準高さ(厚さ)

				);

/////////////////////////////////////////////////////////////////////////////
//	基準高さを取得する
static MREAL	GetStnd(		// 基準高さ(厚さ)
						MINT		i_iKai,		// 階　(1,2,3)
						MSTNDH		i_iKTCode	// 基準高さコード
				);
};

//template<typename TYPE, size_t SIZE>
//inline MINT		mcsGetEnvPath(	// ステイタス	0:正常	!=0:エラー
//						MPPATHENV	i_iType,	// 環境パス種類
//												//	MM_STR_TABLE:	テーブル
//												//	MM_STR_ATTR:	属性
//												//	MM_STR_TEX:	テクスチャ(TEXTURE)
//												//	MM_STR_FIG:	図形
//						MCHAR*		i_cFile,	// ファイル名
//						TYPE (&o_cPath)[SIZE]	// パス名配列
//				)
//				{
//					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, SIZE);
//				}

template<size_t SIZE>
inline MINT		mcsGetEnvPath(	// ステイタス	0:正常	!=0:エラー
						MPPATHENV	i_iType,	// 環境パス種類
												//	MM_STR_TABLE:	テーブル
												//	MM_STR_ATTR:	属性
												//	MM_STR_TEX:	テクスチャ(TEXTURE)
												//	MM_STR_FIG:	図形
						MCHAR*		i_cFile,	// ファイル名
						MCHAR (&o_cPath)[SIZE]	// パス名配列
				)
				{
					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, SIZE);
				}

inline MINT		mcsGetEnvPath(	// ステイタス	0:正常	!=0:エラー
						MPPATHENV	i_iType,	// 環境パス種類
												//	MM_STR_TABLE:	テーブル
												//	MM_STR_ATTR:	属性
												//	MM_STR_TEX:	テクスチャ(TEXTURE)
												//	MM_STR_FIG:	図形
						MCHAR*		i_cFile,	// ファイル名
						MCHAR*		o_cPath,	// パス名
						int			i_ncPath	// パス名最大文字数+1
				)
				{
					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, i_ncPath);
				}
} // namespace MC
