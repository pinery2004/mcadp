#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: msCode.h
//
//		基本　文字コード変換関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

#include <Windows.h>

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_CODE_DO
	#pragma message( "<<< Code・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Code・dll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class DLL_EXPORT Code
{
public:
	//===========================================================================
	// MBCS文字列をUNICODE文字列に変換する
	//【返値】 0 : 正常     -1 : 異常
	//===========================================================================

	static MINT msbstowcs( 
						LPCSTR	i_StrC,			// MBCS文字列
						LPWSTR	o_pStrU,		// UNICODE文字列
						MINT	i_iSize			// 最大文字数
						);

	//===========================================================================
	// UNICODE文字列をMBCS文字列に変換する
	//【返値】 0 : 正常     -1 : 異常
	//===========================================================================

	static MINT mswcstombs( 
						LPCWSTR	i_StrU,			// UNICODE文字列
						LPSTR	o_pStrC,		// MBCS文字列
						MINT	i_iSize			// 最大文字数
						);

	//===========================================================================
	// 文字列を小文字に変換
	//===========================================================================
	static void msstrtolower(
						LPCWSTR	i_pstr,			// 変換前の文字列
						LPWSTR	o_pstrL,		// 変換後の文字列バッファ
						size_t	i_iSzstrL)		// 文字列バッファサイズ
	{
//S		MCHAR*	pstr;
//		MCHAR*	pstrL;
		size_t	available;

//S		pstr = i_pstr;
//		pstrL = o_pstrL;
		available = i_iSzstrL;
		while( *i_pstr != 0 && --available) {
			*o_pstrL++ = Mtolower( *i_pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR();
		}
		*o_pstrL = 0;
	}

	//===========================================================================
	// 文字列を大文字に変換
	//===========================================================================
	static void msstrtoupper(
						LPCWSTR	i_pstr,		// 変換前の文字列
						LPWSTR	o_pstrU,	// 変換後の文字列バッファ
						MINT	in_SzstrU)		// 最大文字数(バッファサイズ - 1)
	{
//S		MCHAR*	pstr;
//		MCHAR*	pstrU;
		size_t	available;

//S		pstr = in_pstr;
//		pstrU = out_pstrU;
		available = in_SzstrU;
		while( *i_pstr != 0 && --available) {
			*o_pstrU++ = Mtoupper( *i_pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR();
		}
		*o_pstrU = 0;
	}

};

} // namespace MC

