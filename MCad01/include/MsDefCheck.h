#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsBasic.h
//
//		基本　エラー判定関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

/////////////////////////////////////////////////////////////////////////////
//		システムエラーステイタス

#define	 	MC_ERR_COMMAND		1200			// コマンドエラー
#define	 	MC_ERR_ID			1201			// ＩＤ誤りエラー
#define		MC_ERR_POINTER		1202			// メモリ取得エラー
#define		MC_ERR_OVERFLOW		1203			// 領域オーバフローエラー
#define		MC_ERR_FILEOPEN		1204			// ファイルオープンエラー
#define		MC_ERR_OTHER	   -999				// その他エラー

//		メモリ取得エラー表示
#define		MB_DM_MEM			{ msSysError( X, MC_ERR_POINTER);}

/////////////////////////////////////////////////////////////////////////////
//		ステイタス
#define		MC_SUCCESS			  0
#define		MC_FAILURE			 ~0

#define		MC_E_CANCEL			 13
#define		MC_E_NOMSG			 14
	
#define 	RETURN_COMMAND_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_COMMAND)
#define 	RETURN_ID_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_ID)
#define 	RETURN_POINTER_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_POINTER)
#define 	RETURN_OVERFLOW_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_OVERFLOW)
#define 	RETURN_OVERFLOW_ERR_S( CPROG)\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_OVERFLOW, CPROG)
#define 	RETURN_FILEOPEN_ERR_S( CPATH)\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_FILEOPEN, CPATH)
#define 	RETURN_NUM_OVER_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_NUM_OVER)
#define 	RETURN_VECT_ZERO_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_VECT_ZERO)
#define 	RETURN_VALUE_ZERO_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_VALUE_ZERO)
#define 	RETURN_OTHER_ERR()\
								ms::SysError( __FUNCTION__, __LINE__, MC_ERR_OTHER)

#define 	GOTO_ERROR			{ ms::ErrorReturn(); goto ERR_EXIT;}
#define 	GOTO_ERROR_1		{ ms::ErrorReturn(); goto ERR_EXIT_1;}
#define 	GOTO_ERROR1			{ ms::ErrorReturn(); goto ERR_EXIT1;}
#define 	GOTO_ERROR2			{ ms::ErrorReturn(); goto ERR_EXIT2;}
#define 	GOTO_ERROR3			{ ms::ErrorReturn(); goto ERR_EXIT3;}
#define 	GOTO_ERROR4			{ ms::ErrorReturn(); goto ERR_EXIT4;}
#define 	GOTO_ERROR999		{ ms::ErrorReturn(); goto ERR_EXIT999;}



//===========================================================================
//		ポインタチェック
//
//		アクセス可能なポインタである事をチェックする
//
//		CHECKDATA( p, n)	:	( p != 0) && ( p から n バイトのアクセス可能)
//		CHECKPTR( p)		:	( p != 0) && ( p から 1 バイトのアクセス可能)
//		CHECKFUNCPTR( p) 	:	( p != 0) && ( p にアクセス可能)
//		CHECKSTR( s)		:	( p != 0) && ( p から 30000文字のアクセス可能)
//		CHECKSTRUCTPTR( p)	:	( p != 0) && ( p から 構造体のサイズ分のアクセス可能)
//  
#define 	CHECKDATA( p, n)		( ( p) && !IsBadReadPtr( ( LPVOID)( p), ( n)))
#define 	CHECKPTR( p)			CHECKDATA( p, 1)
#define 	CHECKFUNCPTR( p) 		( ( p) && !IsBadCodePtr( ( FARPROC) ( p)))
#define 	CHECKSTR( s)			( ( s) && !IsBadStringPtr( ( LPCSTR)( s), 30000))
#define 	CHECKSTRUCTPTR( p)		CHECKDATA( p, sizeof( *p)) 

//===========================================================================
//		アロケーション誤りチェック
//			( out of memory)
//
//	使用方法:
//		  rc = MALLOC_FAIL( p = new CMyClass( a, b, c));
//
//	結果: rc = DM_MEM: アロケーション誤り
//		  rc = SUCCESS: アロケーション成功
//
#define MALLOC_FAIL( object) ( object) ? SUCCESS: DM_MEM

//
//	MGCHECK_ZEROVECT( ゼロチェックのベクトル長, "プログラム名");
//
#define 	MBCHECK_ZEROVECT(X,Z,T)\
								{ if ( ( X) < T)  ms::SysError( Z, __LINE__, MC_ERR_VECT_ZERO);}

#define 	MBCHECK_POINTER(P)	{ if ( P == NULL) RETURN_POINTER_ERR();}


