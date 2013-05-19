//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: mlLog.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#pragma warning( disable : 4996 )
#include "stdafx.h"
#include "msBasic.h"

#define	DLL_EXPORT_MBLOG_DO
#define	DLL_EXPORT_TRACE_DO
#include "MlLog.h"

#define	PRINT_CNT_P_L		10					// １行あたりの印刷数

namespace MC
{

FILE*	Trace::m_pfp = 0;						// トレースファイルポインタ
MCHAR	Trace::m_cLogFilePath[MAX_PATH];		// トレースファイル名
MINT	Trace::m_iDepth = 0;					// トレースインデント深さ
MCHAR	Trace::m_cDepth[Msizeof( MBLOGINDENT) * ( MBLOGMAXDEPTH + 1)] = Mstr( "");
												// トレースインデント

//===========================================================================
//【機能】	ログ
//
MCHAR	mlLog::m_Str[1000];
FILE*	mlLog::m_File;
MINT	mlLog::m_iCtl;

void mlLog::OpenLogFile( MCHAR* i_cLogFilePath)
{
	errno_t	err;

#ifdef LOGOUT
	if ( Mstrcmp( i_cLogFilePath, Mstr( "stdout")) == 0) {
		m_File = stdout;
	} else {
		err = Mfopen_s( &m_File, i_cLogFilePath, Mstr( "w"));
		if ( err != 0) {
			RETURN_FILEOPEN_ERR_S( i_cLogFilePath);
		}
	}
	m_iCtl = 1;
#endif
}

void mlLog::CloseLogFile( )
{
#ifdef LOGOUT
	if ( m_File != stdout)
		fclose( m_File);
#endif
}

void mlLog::Ctrl( int ictrl)
{
#ifdef LOGOUT
	m_iCtl = ictrl;
#endif
}

int mlLog::Wait( MCHAR* str)
{
#ifdef LOGOUT
	int ii;
	if( m_iCtl != 0) {
		TRACE( Mstr( "%s --- Keyin dumy number >"), str);
		Mscanf_s( Mstr( "%d"), &ii);
	}
	else ii = 0;
	return ii;
#else
	return 0;
#endif
}
int mlLog::Wait( char* cstr)
{
#ifdef LOGOUT
	int ii;
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		TRACE( Mstr( "%s --- Keyin dumy number >"), str);
		Mscanf_s( Mstr( "%d"), &ii);
	}
	else ii = 0;
	return ii;
#else
	return 0;
#endif
}


void mlLog::Flush( )
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		fflush( m_File);
	}
#endif
}
void mlLog::PrintCR( )
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "\n"));
		TRACE( Mstr( "\n"));
	}
#endif
}

void mlLog::Print( MCHAR* str)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s\n"), str);
		TRACE( Mstr( "%s\n"), str);
	}
#endif
}
void mlLog::Print( char* cstr)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, Mstr( "%s\n"), str);
		TRACE( Mstr( "%s\n"), str);
	}
#endif
}

void mlLog::Print( MCHAR* str, const MCHAR* s1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %s\n"), str, s1);
		TRACE( Mstr( "%s	= %s\n"), str, s1);
	}
#endif
}
void mlLog::Print( char* cstr, const MCHAR* s1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, Mstr( "%s	= %s\n"), str, s1);
		TRACE( Mstr( "%s	= %s\n"), str, s1);
	}
#endif
}
void mlLog::Print( MCHAR* str, const char* cs1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	s1[256];
		Code::msbstowcs( cs1, s1, 256);
		Mfprintf( m_File, Mstr( "%s	= %s\n"), str, s1);
		TRACE( Mstr( "%s	= %s\n"), str, s1);
	}
#endif
}
void mlLog::Print( char* cstr, const char* cs1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256], s1[256];
		Code::msbstowcs( cstr, str, 256);
		Code::msbstowcs( cs1, s1, 256);
		Mfprintf( m_File, Mstr( "%s	= %s\n"), str, s1);
		TRACE( Mstr( "%s	= %s\n"), str, s1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MINT i1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
		TRACE( Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}
void mlLog::Print( char* cstr, MINT i1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
		TRACE( Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MINT i1[], int ni1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		if ( ni1 != 0) {
			Mfprintf( m_File, Mstr( "%s	="), str);
			TRACE( Mstr( "%s	="), str);
			int	iCr = PRINT_CNT_P_L;
			for ( int i=0; i<ni1; i++) {
				Mfprintf( m_File, Mstr( " %d"), i1[i]);
				TRACE( Mstr( " %d"), i1[i]);
				if ( --iCr == 0) {
					Mfprintf( m_File, Mstr( "\n\t\t\t"));
					TRACE( Mstr( "\n\t\t\t"));
					iCr = PRINT_CNT_P_L;
				}
			}
			if ( iCr != 0) {
				Mfprintf( m_File, Mstr( "\n"));
				TRACE( Mstr( "\n"));
			}
		}
	}
#endif
}
void mlLog::Print( char* cstr, MINT i1[], int ni1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Print( str, i1, ni1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MUBYTE i1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
		TRACE( Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}
void mlLog::Print( char* cstr, MUBYTE i1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
		TRACE( Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MUBYTE i1[], int ni1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	="), str);
		TRACE( Mstr( "%s	="), str);
		int	iCr = PRINT_CNT_P_L;
		for ( int i=0; i<ni1; i++) {
			if ( --iCr == 0) {
				Mfprintf( m_File, Mstr( "\n\t\t\t"));
				TRACE( Mstr( "\n\t\t\t"));
				iCr = PRINT_CNT_P_L;
			}
		}
		if ( iCr != 0) {
			Mfprintf( m_File, Mstr( "\n"));
			TRACE( Mstr( "\n"));
		}
	}
#endif
}
void mlLog::Print( char* cstr, MUBYTE i1[], int ni1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Print( str, i1, ni1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MREAL f1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %f\n"), str, f1);
		TRACE( Mstr( "%s	= %f\n"), str, f1);
	}
#endif
}
void mlLog::Print( char* cstr, MREAL f1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, Mstr( "%s	= %f\n"), str, f1);
		TRACE( Mstr( "%s	= %f\n"), str, f1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MREAL f1[], int nf1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	="), str);
		TRACE( Mstr( "%s	="), str);
		int	iCr = PRINT_CNT_P_L;
		for ( int i=0; i<nf1; i++) {
			Mfprintf( m_File, Mstr( " %f"), f1[i]);
			TRACE( Mstr( " %f"), f1[i]);
			if ( --iCr == 0) {
				Mfprintf( m_File, Mstr( "\n\t\t\t"));
				TRACE( Mstr( "\n\t\t\t"));
				iCr = PRINT_CNT_P_L;
			}
		}
		if ( iCr != 0) {
			Mfprintf( m_File, Mstr( "\n"));
			TRACE( Mstr( "\n"));
		}
	}
#endif
}
void mlLog::Print( char* cstr, MREAL f1[], int nf1)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Print( str, f1, nf1);
	}
#endif
}

//------------------------------------------------------------------------
// ログファイルへフォーマット付きで出力する
void mlLog::LogOut(
						MCHAR* i_cFormat, ...	// ログ書き込みデータ
						)
{
#ifdef LOGOUT
	MCHAR	CMsg[MAX_PATH];
	va_list	cList;
	if( m_iCtl != 0) {
		va_start( cList, i_cFormat);
		_vstprintf_s( CMsg, i_cFormat, cList);
		Mfprintf( m_File, CMsg);
		TRACE( CMsg);
		va_end( cList);
	}
#endif
}
void mlLog::LogOut(
						char* i_cFormat, ...	// ログ書き込みデータ
						)
{
#ifdef LOGOUT
	MCHAR	CMsg[MAX_PATH];
	va_list	cList;
	if( m_iCtl != 0) {
		MCHAR	sFormat[256];
		Code::msbstowcs( i_cFormat, sFormat, 256);
		va_start( cList, sFormat);
		_vstprintf_s( CMsg, sFormat, cList);
		Mfprintf( m_File, CMsg);
		TRACE( CMsg);
		va_end( cList);
	}
#endif
}

//------------------------------------------------------------------------
// ログファイルへログレベルとフォーマット付きで出力する
//
//		Ex.	mlLog::LogOut( MC_LOG_ERROR, Mstr("%s(%d) XXX処理\n"), __FILE__, __LINE__);
//
void mlLog::LogOutWL(
						int		i_iLevel,		// ログレベル
												//				MC_LOG_ERROR
												//				MC_LOG_WARNING
												//				MC_LOG_ERROR
						MCHAR*	i_cFormat, ...	// ログ書き込みデータ
						)
{
#ifdef LOGOUT
	MCHAR	cMsg[MAX_PATH];
	switch ( i_iLevel) {
	case MC_LOG_ERROR:
		fprintf( m_File, "\n *** ERROR *** ");
		TRACE( "\n *** ERROR *** ");
		break;
	case MC_LOG_WARNING:
		fprintf( m_File, "\n *** WARNING *** ");
		TRACE( "\n *** WARNING *** ");
		break;
	}
	va_list	cList;
	if( m_iCtl != 0) {
		va_start( cList, i_cFormat);
		_vstprintf_s( cMsg, i_cFormat, cList);
		Mfprintf( m_File, cMsg);
		TRACE( cMsg);
		va_end( cList);
	}
	if( i_iLevel == MC_LOG_ERROR) {
//S		__debugbreak();											// ブレークポイント
		AfxDebugBreak();										// ブレークポイント
	}
#endif
}
void mlLog::LogOutWL(
						int		i_iLevel,		// ログレベル
												//				MC_LOG_ERROR
												//				MC_LOG_WARNING
												//				MC_LOG_ERROR
						char*	i_cFormat, ...	// ログ書き込みデータ
						)
{
#ifdef LOGOUT
	MCHAR	cMsg[MAX_PATH];
	switch ( i_iLevel) {
	case MC_LOG_ERROR:
		fprintf( m_File, "\n *** ERROR *** ");
		TRACE( "\n *** ERROR *** ");
		break;
	case MC_LOG_WARNING:
		fprintf( m_File, "\n *** WARNING *** ");
		TRACE( "\n *** WARNING *** ");
		break;
	}
	va_list	cList;
	if( m_iCtl != 0) {
		MCHAR	sFormat[256];
		Code::msbstowcs( i_cFormat, sFormat, 256);
		va_start( cList, sFormat);
		_vstprintf_s( cMsg, sFormat, cList);
		Mfprintf( m_File, cMsg);
		TRACE( cMsg);
		va_end( cList);
	}
	if( i_iLevel == MC_LOG_ERROR) {
//S		__debugbreak();											// ブレークポイント
		AfxDebugBreak();										// ブレークポイント
	}
#endif
}


void mlLog::Trace( MCHAR* str)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, str);
		TRACE( str);
	}
#endif
}
void mlLog::Trace( char* cstr)
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		MCHAR	str[256];
		Code::msbstowcs( cstr, str, 256);
		Mfprintf( m_File, str);
		TRACE( str);
	}
#endif
}

void mlLog::Trace( )
{
#ifdef LOGOUT
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s"), m_Str);
		TRACE( Mstr( "%s"), m_Str);
	}
#endif
}

//------------------------------------------------------------------------
//【機能】		ログファイルのオープン
//【返値】		なし
//------------------------------------------------------------------------
void Trace::OpenTraceFile(
						MCHAR i_cLogFilePath[]	// ログファイルパス
						)
{
	errno_t	err;

	if ( m_pfp == NULL) {
		err = Mfopen_s( &m_pfp, i_cLogFilePath, Mstr( "at"));
		if ( err != 0) {
			RETURN_FILEOPEN_ERR_S( i_cLogFilePath);
		}
	}
}
void Trace::OpenTraceFile(
						char i_cLogFilePath[]	// ログファイルパス
						)
{
	errno_t	err;

	if ( m_pfp == NULL) {
		MCHAR	sLogFilePath[256];
		Code::msbstowcs( i_cLogFilePath, sLogFilePath, 256);
		err = Mfopen_s( &m_pfp, sLogFilePath, Mstr( "at"));
		if ( err != 0) {
			RETURN_FILEOPEN_ERR_S( sLogFilePath);
		}
	}
}

//------------------------------------------------------------------------
//【機能】		ログファイルのクローズ
//【返値】		なし
//------------------------------------------------------------------------
void Trace::CloseTraceFile( void)
{
	if ( m_pfp!=NULL) {
		Mfclose( m_pfp);
		m_pfp = NULL;
	}
}


//===========================================================================
//【機能】		トレースファイルへ出力コンストラクタ
//【返値】		なし
//===========================================================================
Trace::Trace( void)
{
	ASSERT( m_pfp);
}

Trace::Trace( MCHAR* i_cFuncName)
{
	ASSERT( m_pfp >= 0);
	m_iDepth++;
	if ( m_iDepth < MBLOGMAXDEPTH) {
		Mstrcpy_s( &m_cDepth[m_iDepth * 2], MBLOGMAXDEPTH * 2 + 1, MBLOGINDENT);
	}
	Mstrcpy_s( m_cFuncName, Msizeof( m_cFuncName), i_cFuncName);
	fprintf( m_pfp, "%s===> Start( %s)", m_cDepth, m_cFuncName);
}
Trace::Trace( char* i_cFuncName)
{
	MCHAR	sFuncName[256];
	Code::msbstowcs( i_cFuncName, sFuncName, 256);
	ASSERT( m_pfp >= 0);
	m_iDepth++;
	if ( m_iDepth < MBLOGMAXDEPTH) {
		Mstrcpy_s( &m_cDepth[m_iDepth * 2], MBLOGMAXDEPTH * 2 + 1, MBLOGINDENT);
	}
	Mstrcpy_s( m_cFuncName, Msizeof( m_cFuncName), sFuncName);
	fprintf( m_pfp, "%s===> Start( %s)", m_cDepth, m_cFuncName);
}

//===========================================================================
//【機能】		トレースファイルへ出力デストラクタ
//【返値】		なし
//===========================================================================
Trace::~Trace( void)
{
	ASSERT( m_pfp > 0);
	fprintf( m_pfp, "%s<=== End( %s)", m_cDepth, m_cFuncName);

	m_iDepth--;
	if ( m_iDepth < MBLOGMAXDEPTH) {
		m_cDepth[m_iDepth * 2] = 0;
	}
}

//------------------------------------------------------------------------
//【機能】		トレースファイルへフォーマット付きで出力する
//【引数】		なし
//【返値】		なし
//------------------------------------------------------------------------
void Trace::Write(
						MCHAR* i_cFormat, ...	// ログ書き込みデータ
						)
{
	va_list	cList;
	va_start( cList, i_cFormat);
	_vftprintf_s( m_pfp, i_cFormat, cList);
	va_end( cList);
}
void Trace::Write(
						char* i_cFormat, ...	// ログ書き込みデータ
						)
{
	va_list	cList;
	MCHAR	sFormat[256];
	Code::msbstowcs( i_cFormat, sFormat, 256);
	va_start( cList, sFormat);
	_vftprintf_s( m_pfp, sFormat, cList);
	va_end( cList);
}

//------------------------------------------------------------------------
//【機能】		トレースファイルへ一行出力する
//【引数】		なし
//【返値】		なし
//------------------------------------------------------------------------
void Trace::WriteLine( 
						MCHAR i_cOut[]			// ログ書き込み行データ
						)
{
	fprintf( m_pfp, "%s\n", i_cOut);
}
void Trace::WriteLine( 
						char i_cOut[]			// ログ書き込み行データ
						)
{
	MCHAR	sOut[256];
	Code::msbstowcs( i_cOut, sOut, 256);
	fprintf( m_pfp, "%s\n", sOut);
}

} // namespace MC
