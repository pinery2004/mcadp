#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsDefFunc.h
//
//		基本　定数・関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

#include "MsLib.h"
#include "MsMsg.h"

//===========================================================================
//		文字列操作
//
#define		Mchar( cha)			_TEXT( cha)		// キャラクタUNICODE変換
#define		Mstring( str)		_TEXT( str)		// 文字列UNICODE変換
#define		Mstr( str)			_TEXT( str)		// 文字列UNICODE変換
#define		MBCstr( str)		( str)			// 文字列MBC	無変換
#define		Mgetchar( str, n)	string[number]	// 文字列中のキャラクタの取得
#define		Msizeof( str)		( sizeof( str)/sizeof( MCHAR)-1)
												// 文字列サイズ
#define		Mstrcpy				_tcscpy			// 文字列の複写
#define		Mstrcpy_s			_tcscpy_s		// 文字列の複写
#define		Mstrncpy			_tcsncpy		// 文字列の複写 (文字数はNULLを含まない)
#define		Mstrncpy_s			_tcsncpy_s		// 文字列の複写 (文字数はNULLを含まない)　( 後ろにNULLを付けてコピー)
#define		Mstrcat				_tcscat			// 文字列の連結
#define		Mstrcat_s			_tcscat_s		// 文字列の連結
#define		Mstrncat			_tcsncat		// 文字列の連結 (文字数はNULLを含まない)
#define		Mstrncat_s			_tcsncat_s		// 文字列の連結 (文字数はNULLを含まない)
#define		Mstrcmp				_tcscmp			// 文字列の比較
#define		Mstrcmp_s			_tcscmp_s		// 文字列の比較 (文字数はNULLを含まない)
#define		Mstricmp			_tcsicmp		// 文字列を小文字化して比較
#define		Mstricmp_s			_tcsicmp_s		// 文字列を小文字化して比較 (文字数はNULLを含まない)
#define		Mstrncmp			_tcsncmp		// 文字列の比較 (文字数はNULLを含まない)
#define		Mstrncmp_s			_tcsncmp_s		// 文字列の比較 (文字数はNULLを含まない)
#define		Mstrnicmp			_tcsnicmp		// 文字列を小文字化して比較 (文字数はNULLを含まない)
#define		Mstrnicmp_s			_tcsnicmp_s		// 文字列を小文字化して比較 (文字数はNULLを含まない)
#define		Mstrchr				_tcschr			// 文字列中の文字の検索 (str 内で c が最初に出現する位置を指すポインタを返す。c が見つからない場合は、NULL を返す。)
#define		Mstrchr_s			_tcschr_s		// 文字列中の文字の検索 (str 内で c が最初に出現する位置を指すポインタを返す。c が見つからない場合は、NULL を返す。)
#define		Mstrrchr			_tcsrchr		// 文字列中の文字の検索 (str 内で c が最後に出現する位置を指すポインタを返す。c が見つからない場合は、NULL を返す。)
#define		Mstrrchr_s			_tcsrchr_s		// 文字列中の文字の検索 (str 内で c が最後に出現する位置を指すポインタを返す。c が見つからない場合は、NULL を返す。)
#define		Mstrstr				_tcsstr			// 文字列中の文字列の検索
#define		Mstrstr_s			_tcsstr_s		// 文字列中の文字列の検索
//#define	Mstrrstr			_tcsrstr		// 文字列中の文字列の検索
#define		Mstrtok				_tcstok			// 文字列中の最初のトークンを取り出す
#define		Mstrtok_s			_tcstok_s		// 文字列中の最初のトークンを取り出す
#define		Mstrlen				_tcslen			// 文字列の文字数を取得
#define		Mstrlen_s			_tcslen_s		// 文字列の文字数を取得
//	入出力
#define		Msprintf			_stprintf		// メモリ領域への書式付き出力
#define		Msprintf_s			_stprintf_s		// メモリ領域への書式付き出力
#define		M_snprintf			_sntprintf		// メモリ領域への書式付き出力
#define		Mscanf				_tscanf			// 書式付き入力
#define		Mscanf_s			_tscanf_s		// 書式付き入力
#define		Msscanf				_stscanf		// メモリ領域からの書式付き入力
#define		Msscanf_s			_stscanf_s		// メモリ領域からの書式付き入力

#define		Mprintf				_tprintf		// 書式付き出力
#define		Mfprintf			_ftprintf		// ファイルへの書式付き出力
#define		Mfscanf				_ftscanf		// ファイルからの書式付き入力

//	評価
#define		Misalnum			_istalnum		// 英数字である
#define		Misalpha			_istalpha		// 英文字である
#define		Miscntrl			_istcntrl		// 削除文字または制御文字である
#define		Misdigit			_istdigit		// 0-9の数字である
#define		Misgraph			_istgraph		// 可視グラフィック文字である
#define		Mislower			_istlower		// 英小文字である
#define		Misprint			_istprint		// 印刷用文字である
#define		Mispunct			_istpunct		// 句読点である
#define		Misspace			_istspace		// SPACE,TAB,RETURN,NEWLINE,FORMFEED,垂直タブ
#define		Misupper			_istupper		// 英大文字である
#define		Misxdigit			_istxdigit		// 0-9,A-F,a-fの16進数字である

//	変換
#define		Mtolower			_totlower		// 文字を小文字に変換
#define		Mtoupper			_totupper		// 文字を大文字に変換
#define		Mstrlwr				_tcslwr			// 文字列の小文字化
#define		Mstrlwr_s			_tcslwr_s		// 文字列の小文字化
#define		Mstrupr				_tcsupr			// 文字列の大文字化
#define		Mstrupr_s			_tcsupr_s		// 文字列の大文字化
#define		Matoi				_tstoi			// 文字列を整数に変換
#define		Mwtoi				_tstoi			// 文字列を整数に変換
#define		Matol				_tstol			// 文字列を整数に変換
#define		Mwtol				_tstol			// 文字列を整数に変換
#define		Matof				( MREAL)_tstof	// 文字列を実数に変換
#define		Mwtof				( MREAL)_tstof	// 文字列を実数に変換
#define		Matodbl				_tstodbl		// 文字列を実数に変換
#define		Mwtodbl				_tstodbl		// 文字列を実数に変換

//===========================================================================
//		ファイル処理
//
#define		Mfopen				_tfopen			// ファイルオープン
#define		Mfopen_s			_tfopen_s		// ファイルオープン
#define		Mfclose				fclose			// ファイルクローズ
#define		Mfflush				fflush			// ストリームをフラッシュ


#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_BASE_DO
	#pragma message( "<<< Base・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Base・dll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{
//===========================================================================
//		リターン
class DLL_EXPORT ms : public mslib, public msmsg
{
public:
	//===========================================================================
	//		日本語モード
	//
	static void	SetJapanese( );

	//===========================================================================
	//		バッファ処理 fill memory, copy memory, copy memcopys
	//
	//===========================================================================
	//	文字を文字列全体にコピーする( fill)
	//
	static void Fill( void *sdest, char cdt, int nsz)
	{
		memset( sdest, cdt, nsz);
		//	for ( int n=0; n<nsz; sdest[n++]=cdt);
	}

	//===========================================================================
	//	整数を整数配列全体にコピーする( fill)
	//
	static void Fill( int* idest, int idt, int nsz)
	{
		for ( int n=0; n<nsz; idest[n++]=idt);
	}

	//===========================================================================
	//	実数を実数配列全体にコピーする( fill)
	//
	static void Fill( MREAL *rdest, MREAL rdt, int nsz)
	{
		for ( int n=0; n<nsz; rdest[n++]=rdt);
	}

	//===========================================================================
	//	文字配列から文字配列へコピーする( memcpy)
	//
	static void Copy( char *sdest, char *ssource, int nsz)
	{
		memcpy( sdest, ssource, nsz);
	//	for ( int n=0; n<nsz; n++) sdest[n] = ssource[n];
	}

	//===========================================================================
	//	整数配列から整数配列へコピーする( memcpy)
	//
	static void Copy( int* idest, int* isource, int nsz)
	{
		memcpy( idest, isource, nsz*4);
	//	for ( int n=0; n<nsz; n++)
	//		idest[n] = isource[n];
	}

	//===========================================================================
	//	実数配列から実数配列へコピーする( memcpy)
	//
	static void Copy( MREAL *rdest, MREAL *rsource, int nsz)
	{
		memcpy( rdest, rsource, nsz*4);
	//	for ( int n=0; n<nsz; n++)
	//		idest[n] = isource[n];
	}

	//===========================================================================
	//	文字配列から文字配列へコピーする( memcpy)
	//	領域の重なりも許可
	//
	static void CopyS( MCHAR* sdest, MCHAR* ssource, int nsz)
	{
		memmove( sdest, ssource, nsz);
	//	if( sdest < ssource) {
	//		for ( int n=0; n<nsz; n++)
	//			sdest[n] = ssource[n];
	//	} else {
	//		for ( int n=nsz-1; n>=0; n--)
	//			sdest[n] = ssource[n];
	//	}
	}

	//===========================================================================
	//	整数配列から整数配列へコピーする( memcpy)
	//	領域の重なりも許可
	//
	static void CopyS( int* idest, int* isource, int nsz)
	{
		memmove( idest, isource, nsz*4);
	//	if( idest < isource) {
	//		for ( int n=0; n<nsz; n++)
	//			idest[n] = isource[n];
	//	} else {
	//		for ( int n=nsz-1; n>=0; n--)
	//			idest[n] = isource[n];
	//	}
	}

	//===========================================================================
	//	実数配列から実数配列へコピーする( memcpy)
	//	領域の重なりも許可
	//
	static void CopyS( MREAL *rdest, MREAL *rsource, int nsz)
	{
		memcpy( rdest, rsource, nsz*4);
	//	if( rdest < rsource) {
	//		for ( int n=0; n<nsz; n++)
	//			rdest[n] = rsource[n];
	//	} else {
	//		for ( int n=nsz-1; n>=0; n--)
	//			rdest[n] = rsource[n];
	//	}
	}

//S	//===========================================================================
//	//	エラーリターンブレークポイント用
//	//
//	static void	ErrorReturn( void);
//	
//	static void	SysError( 
//							MCHAR*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode,						// エラーコード
//							MCHAR*				i_cComment = 0						// コメント
//							);
//	static void	SysError( 
//							MCHAR*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode,						// エラーコード
//							char*				i_cComment							// コメント
//							);
//	static void	SysError( 
//							char*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode,						// エラーコード
//							MCHAR*				i_cComment = 0						// コメント
//							);
//	static void	SysError( 
//							char*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode,						// エラーコード
//							char*				i_cComment							// コメント
//							);
//	static void	CmdError( 
//							char*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode						// エラーコード
//							);
//	static void	CmdError( 
//							MCHAR*				i_pcProgram,						// エラープログラム名
//							int					i_iLineN,							// 行番号
//							int					i_iErrorCode						// エラーコード
//							);
//
//	/////////////////////////////////////////////////////////////////////////////////
//	//////		リターンコード
//	////
//	////static short shortCast( int i)
//	////{
//	////	ASSERT( -MINSHORT <= i && i <= MAXSHORT);
//	////	return (short)i;
//	////}
//
//	////struct MbRT
//	////{
//	////	int	m_iRt;
//	////
//	////	MbRT()				: m_iRt( 0)		{}
//	////	MbRT( int i_iRt)	: m_iRt( i_iRt)	{}
//	////	
//	////	operator short()			{ return shortCast( m_iRt);}
//	////
//	////	bool operator &&( bool b)	{ return (*this != 0) && b;}
//	////	bool operator ||( bool b)	{ return (*this != 0) || b;}
//	////	bool operator ==( int i)	{ return m_iRt == i;}
//	////	bool operator !=( int i)	{ return m_iRt != i;}
//	////	bool operator < ( int i)	{ return m_iRt <  i;}
//	////	bool operator < ( long lg)	{ return m_iRt <  lg;}
//	////	bool operator <=( int i)	{ return m_iRt <= i;}
//	////	bool operator > ( int i)	{ return m_iRt >  i;}
//	////	bool operator >=( int i)	{ return m_iRt >= i;}

};

} // namespace MC



//===========================================================================
//		部分処理
//
#define		MBRED( Col)			( Col & 0xFF)
#define		MBGREEN( Col)		( ( Col >> 8) & 0xFF)
#define		MBBLUE( Col)		( ( Col >> 16)& 0xFF)

//===========================================================================
//		フラグチェック
//

inline bool MF_CHECK_ON( MINT a, MINT mask)						// maskの条件がＯＮであるかチェック
				{ return ( ( a & mask) != 0);}

inline bool MF_CHECK_OR( MINT a, MINT mask)						// maskのいずれかの条件がＯＮであるかチェック
				{ return ( ( a & mask) != 0);}

inline bool	MF_CHECK_AND( MINT a, MINT mask)					// maskの全ての条件がＯＮであるかチェック
				{ return ( ( a & mask) == mask);}

inline bool	MF_CHECK_EQ( MINT a, MINT mask)						// maskの全ての条件がセットされており
				{ return ( a == mask);}							// 他の条件のセットが無いことをチェック

inline bool	MF_CHECK_OFF( MINT a, MINT mask)					// maskの条件がＯＦＦであるかチェック
				{ return ( ( ~( a) & mask) != 0);}

inline bool	MF_CHECK_OFF_OR( MINT a, MINT mask)					// maskのいずれかの条件がＯＦＦであるかチェック
				{ return ( ( ~( a) & mask) != 0);}
				
inline bool	MF_CHECK_OFF_AND( MINT a, MINT mask)				// maskの全ての条件がＯＦＦであるかチェック
				{ return ( ( ~( a) & mask) == mask);}

inline void MF_SET_ON( MINT &a, MINT mask)						// maskの条件をセットする
				{ a |= mask;}

inline void MF_SET_OFF( MINT &a, MINT mask)						// maskの条件をクリアする
				{ a &= ~( mask);}

inline void MF_RESET_ON( MINT &a, MINT mask)					// maskの条件をクリアする
				{ a &= ~( mask);}

inline void MF_RESET( MINT &a)									// 前条件をクリアする
				{ a = 0;}

inline bool MI_CHECK_ODD( MINT n)								// 奇数チェック
				{ return ( n & 1);}

inline bool MI_CHECK_EVEN( MINT n)								// 偶数チェック
				{ return ( !MI_CHECK_ODD( n));}

#define 	MQUIT				{ goto exit;}
 				
#define 	MQUIT_IF_FAILED( p)	{ if ( !p) { rc = DM_MEM; goto exit;}}

#define		MQUIT_STS( s)		{ iSt = s; goto exit;}

//===========================================================================
//		永久ループ
//
#define		MFOREVER			for ( ;;)

//===========================================================================
//		0～1. 間の ランダム実数値を発生
//
#define FRAND	( ( double)rand( )/( double)RAND_MAX)

//===========================================================================
//		タイプを指定した２つのオブジェクトを交換
//
//#define msSwap( x,y,type)			{type z = x; x = y; y = z;}
template<class T>
inline void msSwap( T& t1, T& t2)
{
	T tw;
	tw = t1;
	t1 = t2;
	t2 = tw;
}


