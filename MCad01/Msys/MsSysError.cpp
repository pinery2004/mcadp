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
						char*	i_cFunction,	// エラー関数名
						int		i_iLineN,		// 行番号
						int		i_iErrorCode,	// エラーコード
						MCHAR*	i_cComment		// コメント
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// エラー関数名

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	ms::SysError( cFunction, i_iLineN, i_iErrorCode, i_cComment);
}

//===========================================================================
//	エラー表示後に処理を終了する
//
void 	ms::SysError( 
						MCHAR*	i_cFunction,	// エラー関数名
						int		i_iLineN,		// 行番号
						int		i_iErrorCode,	// エラーコード
						MCHAR*	i_cComment		// コメント
				  )
{
	MINT	ist;
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:	iErrorMsgCd = MM_ERR_COMMAND;		break;			// コマンドエラー
	case MC_ERR_ID:			iErrorMsgCd = MM_ERR_ID;			break;			// ＩＤ誤りエラー
	case MC_ERR_POINTER:	iErrorMsgCd = MM_ERR_POINTER;		break;			// メモリ取得エラー
	case MC_ERR_OVERFLOW:	iErrorMsgCd = MM_ERR_OVERFLOW;		break;			// 領域オーバフローエラー
	case MC_ERR_FILEOPEN:	iErrorMsgCd = MM_ERR_FILEOPEN;		break;			// ファイルオープンエラー
	case MC_ERR_INPUT:		iErrorMsgCd = MM_ERR_INPUT;			break;			// 入力エラー
	case MC_ERR_NUM_OVER:	iErrorMsgCd = MM_ERR_NUM_OVER;		break;			// 処理可能個数超えエラー
	case MC_ERR_VECT_ZERO:	iErrorMsgCd = MM_ERR_VECT_ZERO;		break;			// ゼロベクトルで処理不可エラー
	case MC_ERR_VALUE_ZERO:	iErrorMsgCd = MM_ERR_VALUE_ZERO;	break;			// 数値ゼロで処理不可エラー
	case MC_ERR_OFFSET:		iErrorMsgCd = MM_ERR_OFFSET;		break;			// オフセット誤りエラー
	default:				iErrorMsgCd = MM_ERR_OTHER;			break;			// その他エラー
	}
	if ( i_cComment) {
		Msprintf_s( cErrorMsg, Mstr( "Function Name = %s Line No = %d\n\n%s  \n\n%s　\n\n%s　"), i_cFunction, i_iLineN, i_cComment,
													mcs::GetStr( iErrorMsgCd),
													mcs::GetStr( MM_ERR_SYSTEMEXIT));
	} else {
		Msprintf_s( cErrorMsg, Mstr( "Function Name = %s Line No = %d\n\n%s　\n\n%s　"), i_cFunction,
													mcs::GetStr( iErrorMsgCd),
													mcs::GetStr( MM_ERR_SYSTEMEXIT));
	}

	ist = AfxMessageBox( cErrorMsg, 256, MB_ICONSTOP);
	__debugbreak();
	AfxGetMainWnd( )->PostMessage( WM_CLOSE, 0, 0);								// メインウィンドウ取得・終了
}

//===========================================================================
//	コマンドエラー表示
//
void 	ms::CmdError( 
						char*	i_cFunction,	// エラー関数名	最大256文字
						int		i_iLineN,		// 行番号
						int		i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// エラー関数名

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
//S	Mstrcat_s( cFunction, Mstr( "　\n\n"));

	ms::CmdError( cFunction, i_iLineN, i_iErrorCode);
}

//===========================================================================
//	コマンドエラー表示
//
void 	ms::CmdError( 
						MCHAR*	i_cFunction,	// エラー関数名	最大256文字
						int		i_iLineN,		// 行番号
						int		i_iErrorCode	// エラーコード
				  )
{
	MINT	ist;
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:	iErrorMsgCd = MM_ERR_COMMAND;		break;
	default:				iErrorMsgCd = MM_ERR_COMMAND;		break;
	}		


	Msprintf_s( cErrorMsg, Mstr( "Function Name = %s Line No = %d\n\n%s　"), i_cFunction, i_iLineN,
													mcs::GetStr( iErrorMsgCd));



	ist = AfxMessageBox( cErrorMsg, MB_ICONSTOP);
}

//===========================================================================
//	エラーリターンブレークポイント用
//
void	ms::ErrorReturn( void)
{
	__debugbreak();
}

} // namespace MC
