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
						char*	StrC,			// ( I  ) MBCS文字列
						MCHAR*	StrU,			// (  O) UNICODE文字列
						MINT	iSize			// ( I  ) 最大文字数
						);

	//===========================================================================
	// UNICODE文字列をMBCS文字列に変換する
	//【返値】 0 : 正常     -1 : 異常
	//===========================================================================

	static MINT mswcstombs( 
						MCHAR*	StrU,			// ( I  ) UNICODE文字列
						char*	StrC,			// (  O) MBCS文字列
						MINT	iSize			// ( I  ) 最大文字数
						);

	//===========================================================================
	// 文字列を小文字に変換
	//===========================================================================
	static void msstrtolower(
							MCHAR	in_pstr[],		// 変換前の文字列
							MCHAR	out_pstrL[],	// 変換後の文字列バッファ
							size_t	in_SzstrL)		// 文字列バッファサイズ
	{
		MCHAR*	pstr;
		MCHAR*	pstrL;
		size_t	available;

		pstr = in_pstr;
		pstrL = out_pstrL;
		available = in_SzstrL;
		while( *pstr != 0 && --available) {
			*pstrL++ = Mtolower( *pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR( __FUNCTION__);
		}
		*pstrL = 0;
	}

	//===========================================================================
	// 文字列を大文字に変換
	//===========================================================================
	static void msstrtoupper(
							MCHAR	in_pstr[],		// 変換前の文字列
							MCHAR	out_pstrU[],	// 変換後の文字列バッファ
							MINT	in_SzstrU)		// 最大文字数(バッファサイズ - 1)
	{
		MCHAR*	pstr;
		MCHAR*	pstrU;
		size_t	available;

		pstr = in_pstr;
		pstrU = out_pstrU;
		available = in_SzstrU;
		while( *pstr != 0 && --available) {
			*pstrU++ = Mtoupper( *pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR( __FUNCTION__);
		}
		*pstrU = 0;
	}

};

} // namespace MC

