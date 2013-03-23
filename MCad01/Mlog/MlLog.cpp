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

//MCHAR	mlLog::m_Str[1000] = { MCHAR( "INIT")};
//FILE*	mlLog::m_File;
//MINT	mlLog::m_iCtl;

#define	PRINT_CNT_P_L		10					// １行あたりの印刷数

namespace MC
{

FILE*	Trace::m_pfp = 0;						// トレースファイルポインタ
MCHAR	Trace::m_cLogFilePath[MAX_PATH];		// トレースファイル名
MINT	Trace::m_iDepth = 0;					// トレースインデント深さ
MCHAR	Trace::m_cDepth[Msizeof( MBTRCINDENT) * ( MBTRCMAXDEPTH + 1)] = Mstr( "");
												// トレースインデント

//===========================================================================
//		デバッグ
MCHAR	mlLog::m_Str[1000];
FILE*	mlLog::m_File;
MINT	mlLog::m_iCtl;

//mlLog* MbDbg( )
//{
//	return &g_MbDbg;
//}

void mlLog::OpenTrace( MCHAR* i_cLogFilePath)
{
	errno_t	err;

//#ifdef _DEBUG
	if ( Mstrcmp( i_cLogFilePath, Mstr( "stdout")) == 0) {
		m_File = stdout;
	} else {
//		m_File = Mfopen( i_sFileName, Mstr( "w"));
		err = Mfopen_s( &m_File, i_cLogFilePath, Mstr( "w"));
		if ( err != 0) {
			ms::SysError( i_cLogFilePath, MC_ERR_FILEOPEN);
		}
	}
	m_iCtl = 1;
//#endif
}

void mlLog::CloseTrace( )
{
//#ifdef _DEBUG
	if ( m_File != stdout)
		fclose( m_File);
//#endif
}

void mlLog::Ctrl( int ictrl)
{
#ifdef _DEBUG
	m_iCtl = ictrl;
#endif
}

int mlLog::Wait( MCHAR* str)
{
#ifdef _DEBUG
	int ii;
	if( m_iCtl != 0) {
		Mprintf( Mstr( "%s --- Keyin dumy number >"), str);
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
#ifdef _DEBUG
	if( m_iCtl != 0) {
		fflush( m_File);
	}
#endif
}
void mlLog::PrintCR( )
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "\n"));
	}
#endif
}

void mlLog::Print( MCHAR* str)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s\n"), str);
	}
#endif
}

void mlLog::Print( MCHAR* str, const MCHAR* s1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %s\n"), str, s1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MINT i1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MINT *i1, int ni1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		if ( ni1 != 0) {
			Mfprintf( m_File, Mstr( "%s	="), str);
			int	iCr = PRINT_CNT_P_L;
			for ( int i=0; i<ni1; i++) {
				Mfprintf( m_File, Mstr( " %d"), i1[i]);
				if ( --iCr == 0) {
					Mfprintf( m_File, Mstr( "\n\t\t\t"));
					iCr = PRINT_CNT_P_L;
				}
			}
			if ( iCr != 0)
				Mfprintf( m_File, Mstr( "\n"));
		}
	}
#endif
}

void mlLog::Print( MCHAR* str, MUBYTE i1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %d\n"), str, i1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MUBYTE *i1, int ni1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	="), str);
		int	iCr = PRINT_CNT_P_L;
		for ( int i=0; i<ni1; i++) {
			if ( --iCr == 0) {
				Mfprintf( m_File, Mstr( "\n\t\t\t"));
				iCr = PRINT_CNT_P_L;
			}
		}
		if ( iCr != 0)
			Mfprintf( m_File, Mstr( "\n"));
	}
#endif
}

void mlLog::Print( MCHAR* str, MREAL f1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	= %f\n"), str, f1);
	}
#endif
}

void mlLog::Print( MCHAR* str, MREAL *f1, int nf1)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s	="), str);
		int	iCr = PRINT_CNT_P_L;
		for ( int i=0; i<nf1; i++) {
			Mfprintf( m_File, Mstr( " %f"), f1[i]);
			if ( --iCr == 0) {
				Mfprintf( m_File, Mstr( "\n\t\t\t"));
				iCr = PRINT_CNT_P_L;
			}
		}
		if ( iCr != 0)
			Mfprintf( m_File, Mstr( "\n"));
	}
#endif
}

void mlLog::Trace( MCHAR* str)
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s"), str);
	}
#endif
}

void mlLog::Trace( )
{
#ifdef _DEBUG
	if( m_iCtl != 0) {
		Mfprintf( m_File, Mstr( "%s"), m_Str);
	}
#endif
}

//------------------------------------------------------------------------
//【機能】		ログファイルのオープン
//【返値】		なし
//------------------------------------------------------------------------
void Trace::OpenLogFile(
						MCHAR i_cLogFilePath[]	// ログファイルパス
						)
{
	errno_t	err;

	if ( m_pfp == NULL) {
//S		m_pfp = Mfopen( i_cLogFilePath, Mstr( "at"));
		err = Mfopen_s( &m_pfp, i_cLogFilePath, Mstr( "at"));
		if ( err != 0) {
			ms::SysError( i_cLogFilePath, MC_ERR_FILEOPEN);
		}
	}
}

//------------------------------------------------------------------------
//【機能】		ログファイルのクローズ
//【返値】		なし
//------------------------------------------------------------------------
void Trace::CloseLogFile( void)
{
	if ( m_pfp!=NULL) {
		Mfclose( m_pfp);
		m_pfp = NULL;
	}
}


//===========================================================================
//【機能】		ログファイル出力コンストラクタ
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
	if ( m_iDepth < MBTRCMAXDEPTH) {
		Mstrcpy_s( &m_cDepth[m_iDepth * 2], MBTRCMAXDEPTH * 2 + 1, MBTRCINDENT);
	}
	Mstrcpy_s( m_cFuncName, Msizeof( m_cFuncName), i_cFuncName);
	fprintf( m_pfp, "%s===> Start( %s)", m_cDepth, m_cFuncName);
}

//===========================================================================
//【機能】		ログファイル出力デストラクタ
//【返値】		なし
//===========================================================================
Trace::~Trace( void)
{
	ASSERT( m_pfp > 0);
	fprintf( m_pfp, "%s<=== End( %s)", m_cDepth, m_cFuncName);

	m_iDepth--;
	if ( m_iDepth < MBTRCMAXDEPTH) {
		m_cDepth[m_iDepth * 2] = 0;
	}
}

//------------------------------------------------------------------------
//【機能】		ログファイルへインデントされたフォーマット付きで出力する
//【引数】		なし
//【返値】		なし
//------------------------------------------------------------------------
void Trace::Write(
						MCHAR* i_cFormat, ...	// ログ書き込みデータ
						)
{
	MCHAR cOut[256];
	va_list	cList;
	va_start( cList, i_cFormat);
	vswprintf_s( cOut, 256, i_cFormat, cList);
	va_end( cList);

	fprintf( m_pfp, "%s", cOut);
}

//------------------------------------------------------------------------
//【機能】		ログファイルへ一行出力する
//【引数】		なし
//【返値】		なし
//------------------------------------------------------------------------
void Trace::WriteLine( 
						MCHAR i_cOut[]			// ログ書き込み行データ
						)
{
	fprintf( m_pfp, "%s\n", i_cOut);
}

} // namespace MC
