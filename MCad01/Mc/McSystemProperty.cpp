//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: McSystemProperty.cpp
//
//		システムプロパティ
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_SYSTEMPROPERTY_DO
#include "McSystemProperty.h"

namespace MC
{

//S McSystemProperty	g_SysProp;
//	システム定数
DWORD	mcs::m_Color[MM_N_COLOR];					// 色
MREAL	mcs::m_Real[MM_N_REAL];					// 実数
MINT	mcs::m_Int[MM_N_INT];						// 整数
MCHAR*	mcs::m_Str[MM_N_STR];						// 文字列
MCHAR*	mcs::m_Path[MM_N_PATH];					// PATH
MREAL	mcs::m_Stnd[MMAX_KAI][MM_N_STNDH];			// 基準高さ、厚さ　

/////////////////////////////////////////////////////////////////////////////
//	システム定数の初期化　(固有部分)
void	mcs::Init()
{
	m_Color[MM_COLOR_GRID_LINE]			= RGB( 110, 180, 150);	// グリッド線表示色
	m_Color[MM_COLOR_GRID_TEXT]			= RGB(  50, 100,  60);	// グリッド番号表示色
	m_Color[MM_COLOR_MARUME]			= RGB( 255,   0,   0);	// 丸め線表示色
	m_Color[MM_COLOR_CURSOR]			= RGB( 245, 150, 100);	// クロスヘアーカーソル色
	m_Color[MM_COLOR_DRAGGING]			= RGB(  20, 220, 245);	// ドラッギング色
	m_Color[MM_COLOR_HITBZI]			= RGB( 255, 255, 255);	// ヒット部材色
	m_Color[MM_COLOR_TEMP]				= RGB( 120,  20, 125);	// テンポラリ選択表示色
	m_Color[MM_COLOR_BACKGROUND]		= RGB( 252, 252, 252);	// 背景色
//
	m_Color[MM_COLOR_DOUKAIKABESIN]  	= RGB( 25, 25, 205);	// 同階壁芯青色
	m_Color[MM_COLOR_KAKAIKABESIN]	 	= RGB( 185, 75, 15);	// 下階壁芯橙色
	m_Color[MM_COLOR_JYOUKAIKABESIN] 	= RGB( 205, 15, 15);	// 上階壁芯線色
	m_Color[MM_COLOR_DOUKAITAIKABESIN]  = RGB( 25, 25, 205);	// 同階耐力壁芯青色
	m_Color[MM_COLOR_KAKAITAIKABESIN]	= RGB( 185, 75, 15);	// 下階耐力壁芯橙色
	m_Color[MM_COLOR_JYOUKAITAIKABESIN] = RGB( 205, 15, 15);	// 上階壁耐力芯線色
	m_Color[MM_COLOR_DOUKAISIJIKABESIN] = RGB( 25, 25, 205);	// 同階支持壁芯青色
	m_Color[MM_COLOR_KAKAISIJIKABESIN]	= RGB( 185, 75, 15);	// 下階支持壁芯橙色
	m_Color[MM_COLOR_JYOUKAISIJIKABESIN]= RGB( 205, 15, 15);	// 上階支持壁芯線色
	m_Color[MM_COLOR_KISOSIN]			= RGB( 195, 25, 25);	// 基礎芯線色
	m_Color[MM_COLOR_KABESEN]			= RGB( 185, 205, 145);	// 壁表示時の壁線色
	
	m_Real[MM_REAL_PITCH]			= 910.f;					// グリッド・ピッチ
	m_Real[MM_REAL_GRID_SPC]		= 7.f;						// グリッド番号表示空き(ポイント)
	m_Real[MM_REAL_GRID_HEI]		= 9.f;						// グリッド文字高さ(ポイント)
	m_Real[MM_REAL_GRID_AKI]		= 300.f;					// グリッド枠表示空き

	m_Int[MM_INT_GRID_N]			= 16;						// 初期北側グリッド数
	m_Int[MM_INT_GRID_W]			= -3;						// 初期西側グリッド数
	m_Int[MM_INT_GRID_S]			= -3;						// 初期南側グリッド数
	m_Int[MM_INT_GRID_E]			= 17;						// 初期東側グリッド数

	m_Str[MM_STR_TABLE]				= Mstr( "テーブル");		// テーブルフォルダ名
	m_Str[MM_STR_PARTSTABLE]		= Mstr( "テーブル\\部材");	// 部品フォルダ名
	m_Str[MM_STR_ATTR]				= Mstr( "属性");			// 属性フォルダ名
	m_Str[MM_STR_TEX]				= Mstr( "テクスチャ");		// テクスチャフォルダ名
	m_Str[MM_STR_FIG]				= Mstr( "図形");			// 図形フォルダ名 
	m_Str[MM_STR_INIFILE]			= Mstr( "MCAD.ini");		// MCAD.iniファイル名 
	m_Str[MM_STR_LOGFILE]			= Mstr( "MCADLOG.txt");		// LOGファイル名 
	m_Str[MM_STR_TRACEFILE]			= Mstr( "MCADTRACE.txt");	// TRACEファイル名 

	m_Str[MM_STR_CSV_MEMBER]		= Mstr( "寸法型式.csv");	// 寸法型式.csv 
	m_Str[MM_STR_CSV_PARTS]			= Mstr( "部品.csv");		// 部品.csv 
	m_Str[MM_STR_CSV_ATTR]			= Mstr( "属性.csv");		// 属性.csv 
	m_Str[MM_STR_CSV_DRAFTSZ]		= Mstr( "図面サイズ.csv");	// 図面サイズ.csv 
	m_Str[MM_STR_CSV_KOUSEI]		= Mstr( "構成.csv");		// 構成.csv 
	m_Str[MM_STR_CSV_BUNRUI]		= Mstr( "分類.csv");		// 分類.csv			 

	m_Str[MM_ERR_POINTER]			= Mstr( "メモリ取得エラー");
	m_Str[MM_ERR_OVERFLOW]			= Mstr( "領域オーバフローエラー");
	m_Str[MM_ERR_COMMAND]			= Mstr( "コマンドエラー");
	m_Str[MM_ERR_ID]				= Mstr( "ＩＤ誤りエラー");
	m_Str[MM_ERR_INPUT]				= Mstr( "入力エラー");
	m_Str[MM_ERR_NUM_OVER]			= Mstr( "処理可能個数超えエラー");
	m_Str[MM_ERR_VECT_ZERO]			= Mstr( "長さゼロのベクトルで処理不可エラー");
	m_Str[MM_ERR_VALUE_ZERO]		= Mstr( "数値ゼロで処理不可エラー");
	m_Str[MM_ERR_OFFSET]			= Mstr( "オフセット誤りエラー");
	m_Str[MM_ERR_FILEOPEN]			= Mstr( "ファイルオープンエラー");
	m_Str[MM_ERR_OTHER]				= Mstr( "その他エラー");
	m_Str[MM_ERR_SYSTEMEXIT]		= Mstr( "システム終了します　");

	// 実行モジュールのディレクトリ取得
	static MCHAR s_cRootDir[MAX_PATH];
	GetModuleFileName( NULL, s_cRootDir, sizeof( s_cRootDir));
	for ( int i1=(int)Mstrlen( s_cRootDir)-1; i1>=0; i1--) {
		if ( s_cRootDir[i1] == '\\') {
			s_cRootDir[i1] = '\0';
			break;
		}
	}
//N	m_Path[MM_PATH_ROOT_FLDR]		= s_cRootDir;								// 実行モジュールの(ルート)ディレクトリ
//N	m_Path[MM_PATH_PARTS_FLDR]		= Mstr( "D:\\MCAD_32\\テーブル\\部材\\");	// 構造部品テーブル
	m_Path[MM_PATH_SYS_ENV_FLDR]	= Mstr( "D:\\MCAD_32\\マスタ");				// システム環境ディレクトリ

	m_Stnd[0][MM_STNDH_KISO]		= 400.f;			// Kiso
	m_Stnd[0][MM_STNDH_LOWER]		= 645.f;			// Kiso + 245.f (90 + 140 + 15)
	m_Stnd[0][MM_STNDH_UPPER]		= 2740.f;			// rLower + 2095.f
	m_Stnd[0][MM_STNDH_CEILING]		= 3095.f;			// rLower + 2450.f
//	m_Stnd[0][MM_STNDH_ROOF]		= 3184.f;			// rUpper + 89.f
	m_Stnd[0][MM_STNDH_ROOF]		= 3125.f;			// rUpper + 89.f
	m_Stnd[0][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
//	m_Stnd[1][MM_STNDH_KISO]		= 0.f;
	m_Stnd[1][MM_STNDH_LOWER]		= 3354.f;			// rCeiling + 259.f (235 + 24)
	m_Stnd[1][MM_STNDH_UPPER]		= 5449.f;			// rLower + 2095.f
	m_Stnd[1][MM_STNDH_CEILING]		= 5804.f;			// rLower + 2450.f
//	m_Stnd[1][MM_STNDH_ROOF]		= 5893.f;			// rUpper + 89.f
	m_Stnd[1][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
//	m_Stnd[2][MM_STNDH_KISO]		= 0.f;
	m_Stnd[1][MM_STNDH_ROOF]		= 5834.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDH_LOWER]		= 6063.f;			// rCeiling + 259.f (235 + 24)
	m_Stnd[2][MM_STNDH_UPPER]		= 8158.f;			// rLower + 2095.f
	m_Stnd[2][MM_STNDH_CEILING]		= 8513.f;			// rLower + 2450.f
//	m_Stnd[2][MM_STNDH_ROOF]		= 8602.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDH_ROOF]		= 8543.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
}

/////////////////////////////////////////////////////////////////////////////
//	プロパティ値を取得する　(共有部分)

/////////////////////////////////////////////////////////////////////////////
//	システム色を取得する
DWORD	mcs::GetColor( MSYSTEMCOLOR iCol)
{
	return m_Color[iCol];
}

/////////////////////////////////////////////////////////////////////////////
//	システム実数定数を取得する
MREAL	mcs::GetReal( MSYSTEMREAL iReal)
{
	return m_Real[iReal];
}

/////////////////////////////////////////////////////////////////////////////
//	システム整数定数を取得する
MINT	mcs::GetInt( MSYSTEMINT iInt)
{
	return m_Int[iInt];
}

/////////////////////////////////////////////////////////////////////////////
//	システム文字列定数を取得する
MCHAR*	mcs::GetStr( MSYSTEMSTR iStr)
{
	return m_Str[iStr];
}

/////////////////////////////////////////////////////////////////////////////
//	PATH定数を取得する
MCHAR*	mcs::GetPath( MSYSTEMPATH iPath)
{
	return m_Path[iPath];
}

/////////////////////////////////////////////////////////////////////////////
//	システム環境　環境パスにファイル名を付加したファイルパスを得る
MINT mcs::GetEnvPath(				// ステイタス	0:正常	!=0:エラー
						MPPATHENV	i_iType,	// 環境パス種類
												//		 MP_PATH_ROOT:	ルート
												//		 MP_PATH_TABLE:	テーブル
												//		 MP_PATH_ATTR:	属性
												//		 MP_PATH_TEX:	テクスチャ(TEXTURE)
												//		 MP_PATH_FIG:	図形
						MCHAR*		i_cFile,	// ファイル名
						MCHAR*		o_cPath,	// パス名		最大259+1文字(MAX_PATH)
						int			i_ncPath	// パス名最大文字数+1
				)
{
	MINT	ist = 0;
	MSYSTEMSTR	icdPath;
	MINT	cPathN;
	MINT	ncFile;
	MCHAR*	pFile;

//	Mstrcpy( o_cPath, mcs::GetPath( MM_PATH_ROOT_FLDR));
//	Mstrcpy( o_cPath, mcs::GetPath( MM_PATH_PARTS_FLDR));

	Mstrcpy_s( o_cPath, i_ncPath, mcs::GetPath( MM_PATH_SYS_ENV_FLDR));		// 環境ルート\

	cPathN = (MINT)Mstrlen( o_cPath);
	ncFile = i_ncPath - cPathN;
	pFile = &o_cPath[cPathN-1];
	if ( *pFile != Mchar( '\\')) {
		pFile++;
		*pFile = Mchar( '\\');
		pFile++;
		*pFile = 0;
		ncFile--;
	}

	switch( i_iType)
	{
	case MP_PATH_ROOT:											break;			// 環境ルート
	case MP_PATH_TABLE:			icdPath = MM_STR_TABLE;			break;			// 環境ルート\テーブル
	case MP_PATH_PARTSTABLE:	icdPath = MM_STR_PARTSTABLE;	break;			// 環境ルート\テーブル\部品
	case MP_PATH_ATTR:			icdPath = MM_STR_ATTR;			break;			// 環境ルート\属性
	case MP_PATH_TEX:			icdPath = MM_STR_TEX;			break;			// 環境ルート\テクスチャ
	case MP_PATH_FIG:			icdPath = MM_STR_FIG;			break;			// 環境ルート\図形
	default:					ist = -1;
	}
	if ( ist == 0) {
		if ( i_iType != MP_PATH_ROOT) {
			Mstrcat_s( pFile, ncFile, mcs::GetStr( icdPath));
			Mstrcat_s( pFile, ncFile, Mstr( "\\"));
		}
		Mstrcat_s( pFile, ncFile, i_cFile);
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	基準高さを設定する
void	mcs::SetStnd(
						MINT		iKai,				// (I  ) 階　(1,2,3)
						MSTNDH		iKTCode,			// (I  ) 基準高さコード
						MREAL		rHA					// (I  ) 基準高さ(厚さ)

				)
{
	m_Stnd[iKai - 1][iKTCode] = rHA;
}

/////////////////////////////////////////////////////////////////////////////
//	基準高さを取得する
MREAL	mcs::GetStnd(						// (  O) 基準高さ(厚さ)
						MINT		iKai,				// (I  ) 階　(1,2,3)
						MSTNDH		iKTCode				// (I  ) 基準高さコード
				)
{
	return m_Stnd[iKai - 1][iKTCode];
}

} // namespace MC
