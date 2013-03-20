//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbSysErrorMsg.cpp
//
//		システムエラー表示
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#pragma warning( disable : 4996 )
#include "stdafx.h"
#define DLL_EXPORT_BASE_DO
#include "MsBasic.h"
#include "MgDefine.h"
#include "MfFile.h"
#include "McSystemProperty.h"

namespace MC
{

//===========================================================================
//	MCAD.iniファイルを読み込む
//
//LoadMCADIniFile

//===========================================================================
//	エラー表示後に処理を終了する
//
void 	ms::SysError( 
						char*	i_cFunction,	// エラー関数名	最大256文字
						MINT	i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// エラー関数名

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	ms::SysError( cFunction, i_iErrorCode);
}

//===========================================================================
//	エラー表示後に処理を終了する
//
void 	ms::SysError( 
						MCHAR*	i_cFunction,	// エラー関数名	最大256文字
						MINT	i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_POINTER:	iErrorMsgCd = MM_ERR_POINTER;		break;			// メモリ取得エラー
	case MC_ERR_OVERFLOW:	iErrorMsgCd = MM_ERR_OVERFLOW;		break;			// 領域オーバフローエラー
	case MC_ERR_ID:			iErrorMsgCd = MM_ERR_ID;			break;			// ＩＤ誤りエラー
	case MC_ERR_INPUT:		iErrorMsgCd = MM_ERR_INPUT;			break;			// 入力エラー
	case MC_ERR_NUM_OVER:	iErrorMsgCd = MM_ERR_NUM_OVER;		break;			// 処理可能個数超えエラー
	case MC_ERR_VECT_ZERO:	iErrorMsgCd = MM_ERR_VECT_ZERO;		break;			// ゼロベクトルで処理不可エラー
	case MC_ERR_INPUT_ZERO:	iErrorMsgCd = MM_ERR_INPUT_ZERO;	break;			// 数値ゼロで処理不可エラー
	case MC_ERR_OFFSET:		iErrorMsgCd = MM_ERR_OFFSET;		break;			// オフセット誤りエラー
	case MC_ERR_FILEOPEN:	iErrorMsgCd = MM_ERR_FILEOPEN;		break;			// ファイルオープンエラー
	default:				iErrorMsgCd = MM_ERR_OTHER;			break;			// その他エラー
	}
	Msprintf_s( cErrorMsg, Mstr( "%s\n\n%s　\n\n%s　"), i_cFunction,
													McSystemProperty::GetStr( iErrorMsgCd),
													McSystemProperty::GetStr( MM_ERR_SYSTEMEXIT));

	ist = AfxMessageBox( cErrorMsg, 256, MB_ICONSTOP);
	__debugbreak();
	AfxGetMainWnd( )->PostMessage( WM_CLOSE, 0, 0);								// メインウィンドウ取得・終了
}

//===========================================================================
//	コマンドエラー表示
//
void 	ms::CmdError( 
						char*	i_cFunction,	// エラー関数名	最大256文字
						MINT	i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// エラー関数名

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	Mstrcat_s( cFunction, Mstr( "　\n\n"));

	ms::CmdError( cFunction, i_iErrorCode);
}

//===========================================================================
//	コマンドエラー表示
//
void 	ms::CmdError( 
						MCHAR*	i_cFunction,	// エラー関数名	最大256文字
						MINT	i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:
		Mstrcat_s( i_cFunction, 256, Mstr( "コマンド処理エラー"));
		break;
	default:
		Mstrcat_s( i_cFunction, 256, Mstr( "コマンド処理エラー"));
	}		
	ist = AfxMessageBox( i_cFunction, MB_ICONSTOP);
}

//===========================================================================
//	エラーリターンブレークポイント用
//
void	ms::ErrorReturn( void)
{
	__debugbreak();
}

} // namespace MC
