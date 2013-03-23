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

#define	PRINT_CNT_P_L		10					// �P�s������̈����

namespace MC
{

FILE*	Trace::m_pfp = 0;						// �g���[�X�t�@�C���|�C���^
MCHAR	Trace::m_cLogFilePath[MAX_PATH];		// �g���[�X�t�@�C����
MINT	Trace::m_iDepth = 0;					// �g���[�X�C���f���g�[��
MCHAR	Trace::m_cDepth[Msizeof( MBTRCINDENT) * ( MBTRCMAXDEPTH + 1)] = Mstr( "");
												// �g���[�X�C���f���g

//===========================================================================
//		�f�o�b�O
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
//�y�@�\�z		���O�t�@�C���̃I�[�v��
//�y�Ԓl�z		�Ȃ�
//------------------------------------------------------------------------
void Trace::OpenLogFile(
						MCHAR i_cLogFilePath[]	// ���O�t�@�C���p�X
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
//�y�@�\�z		���O�t�@�C���̃N���[�Y
//�y�Ԓl�z		�Ȃ�
//------------------------------------------------------------------------
void Trace::CloseLogFile( void)
{
	if ( m_pfp!=NULL) {
		Mfclose( m_pfp);
		m_pfp = NULL;
	}
}


//===========================================================================
//�y�@�\�z		���O�t�@�C���o�̓R���X�g���N�^
//�y�Ԓl�z		�Ȃ�
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
//�y�@�\�z		���O�t�@�C���o�̓f�X�g���N�^
//�y�Ԓl�z		�Ȃ�
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
//�y�@�\�z		���O�t�@�C���փC���f���g���ꂽ�t�H�[�}�b�g�t���ŏo�͂���
//�y�����z		�Ȃ�
//�y�Ԓl�z		�Ȃ�
//------------------------------------------------------------------------
void Trace::Write(
						MCHAR* i_cFormat, ...	// ���O�������݃f�[�^
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
//�y�@�\�z		���O�t�@�C���ֈ�s�o�͂���
//�y�����z		�Ȃ�
//�y�Ԓl�z		�Ȃ�
//------------------------------------------------------------------------
void Trace::WriteLine( 
						MCHAR i_cOut[]			// ���O�������ݍs�f�[�^
						)
{
	fprintf( m_pfp, "%s\n", i_cOut);
}

} // namespace MC
