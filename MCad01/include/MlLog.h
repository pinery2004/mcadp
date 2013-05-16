#pragma once
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MlLog.h
//
//	[機能] トレース
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

// ログ取得制御
#ifdef _DEBUG
#define LOGOUT
#else
#undef LOGOUT
#endif

//#define LOGOUT									// releasemodeでもログ作成するように設定

// ログ取得定義
#define MBLOGMAXDEPTH			10								// トレースインデント最大深さ
#define MBLOGINDENT				Mstr( "  ")						// トレースインデント
#define MBLOGFUNCNAME			40								// 関数名最大文字数

#define MBLOGOPEN( fn)			mlLog::OpenLogFile( fn)			// トレース開始宣言　ファイル名
#define MBLOGCLOSE				mlLog::CloseLogFile( )			// トレース終了宣言
#define MBLOGON					mlLog::Ctrl( 1)					// トレース　ＯＮ
#define MBLOGOFF				mlLog::Ctrl( 0)					// トレース　ＯＦＦ
#define MBLOGPRBF				mlLog::Trace( )					// トレースバッファ内の文字列
#define MBLOGPRS( S)			mlLog::Trace( S)				// 文字列
#define MBLOGFLUSH				mlLog::Flush( )					// フラッシュ（トレース中の作業エリア内文字列を掃きだす）

#define MBLOGPRINTCR			mlLog::PrintCR( )				// 改行
#define MBLOGPRINTS( S)			mlLog::Print( S)				// 文字列　改行
#define MBLOGPRINTSS( S, T)		mlLog::Print( S, T)				// 文字列 = 文字列　改行
#define MBLOGPRINTI( S, I)		mlLog::Print( S, I)				// 文字列 = 整数　改行
#define MBLOGPRINTIN( S, I, N)	mlLog::Print( S, I, N)			// 文字列 = N個の整数　改行
#define MBLOGPRINTB( S, B)		mlLog::Print( S, B)				// 文字列 = バイト( MUBYTE)整数　改行
#define MBLOGPRINTBN( S, B, N)	mlLog::Print( S, B, N)			// 文字列 = N個のバイト( MUBYTE)整数　改行
#define MBLOGPRINTF( S, F)		mlLog::Print( S, F)				// 文字列 = 実数　改行
#define MBLOGPRINTFN( S, F, N)	mlLog::Print( S, F, N)			// 文字列 = N個の実数　改行

#define MBLOGOUT				mlLog::LogOut					// フォーマット付きで出力する
#define MBLOGOUTWL				mlLog::LogOutWL					// ログレベルとフォーマット付きで出力する

#include "MsBasic.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MBLOG_DO
	#pragma message( "<<< mlLog・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== mlLog・dll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{
	
enum LogType {
	MC_LOG_ERROR = 1,
	MC_LOG_WARNING,
	MC_LOG_NORMAL
};

//===========================================================================
//【機能】	ログ
//
class DLL_EXPORT mlLog
{
public:
	static MCHAR	m_Str[1000];
	static FILE*	m_File;
	static MINT		m_iCtl;

public:
	static void	OpenLogFile( MCHAR* i_sFileName);
	static void	CloseLogFile( );
	static void	Ctrl( int ictrl);
	static int	Wait( MCHAR* str);
	static void	Flush( );
	static void	PrintCR( );
	static void	Print( MCHAR* str);
	static void	Print( MCHAR* str, const MCHAR* s1);
	static void	Print( MCHAR* str, MINT i1);
	static void	Print( MCHAR* str, MINT *i1, int ni1);
	static void	Print( MCHAR* str, MUBYTE i1);
	static void	Print( MCHAR* str, MUBYTE *i1, int ni1);
	static void	Print( MCHAR* str, MREAL f1);
	static void	Print( MCHAR* str, MREAL *f1, int nf1);
	static void LogOut( MCHAR* i_cFormat, ...);					// フォーマット付きで出力する
	static void LogOutWL( int i_iLevel, MCHAR* i_cFormat, ...);	// ログレベルとフォーマット付きで出力する
	static void	Trace( MCHAR* str);
	static void	Trace( );
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_TRACE_DO
	#pragma message( "<<< Trace・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Trace・dll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

//===========================================================================
//【機能】	トレース
//
class  DLL_EXPORT Trace
{
private:
	static	MCHAR	m_cLogFilePath[MAX_PATH];					// トレースファイル名
	static	FILE*	m_pfp;										// トレースファイルポインタ
	static	MINT	m_iDepth;									// トレースインデント深さ
	static	MCHAR	m_cDepth[Msizeof( MBLOGINDENT) * (MBLOGMAXDEPTH + 1)];
																// トレースインデント
			MCHAR	m_cFuncName[MBLOGFUNCNAME];					// 関数名
	
public:
	Trace( void);
	Trace( MCHAR* i_cFuncName);
	~Trace( void);
	static void OpenTraceFile(									// ログファイルの削除とオープン
						MCHAR i_cLogFilePath[]	// ログファイルパス
						);
	static void CloseTraceFile( void);							// ログファイルのクローズ
	static void Write( MCHAR i_cFormat[], ...);					// ログデータ書き込み
	static void WriteLine( MCHAR i_cOut[]);						// ログデータ行書き込み
};
//extern	CMbDebug g_MbDbg;

} // namespace MC
