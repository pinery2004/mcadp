#pragma once
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MlLog.h
//
//	[�@�\] �g���[�X
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#define MBTRCMAXDEPTH			10							// �g���[�X�C���f���g�ő�[��
#define MBTRCINDENT				Mstr( "  ")					// �g���[�X�C���f���g
//S #define	MBTRCLOGFILENAME		Mstr( "MCADLOG.txt")		// �g���[�X�t�@�C����
#define MBTRCFUNCNAME			40							// �֐����ő啶����

#define MBTRCOPEN( fn)			mlLog::OpenTrace( fn)		// �g���[�X�J�n�錾�@�t�@�C����
#define MBTRCCLOSE				mlLog::CloseTrace( )		// �g���[�X�I���錾
#define MBTRCON					mlLog::Ctrl( 1)				// �g���[�X�@�n�m
#define MBTRCOFF				mlLog::Ctrl( 0)				// �g���[�X�@�n�e�e
#define MBTRCPRBF				mlLog::Trace( )				// �g���[�X�o�b�t�@���̕�����
#define MBTRCPRS( S)			mlLog::Trace( S)			// ������
#define MBTRCFLUSH				mlLog::Flush( )				// �t���b�V���i�g���[�X���̍�ƃG���A���������|�������j

#define MBTRCPRINTCR			mlLog::PrintCR( )			// ���s
#define MBTRCPRINTS( S)			mlLog::Print( S)			// ������@���s
#define MBTRCPRINTSS( S, T)		mlLog::Print( S, T)			// ������ = ������@���s
#define MBTRCPRINTI( S, I)		mlLog::Print( S, I)			// ������ = �����@���s
#define MBTRCPRINTIN( S, I, N)	mlLog::Print( S, I, N)		// ������ = N�̐����@���s
#define MBTRCPRINTB( S, B)		mlLog::Print( S, B)			// ������ = �o�C�g( MUBYTE)�����@���s
#define MBTRCPRINTBN( S, B, N)	mlLog::Print( S, B, N)		// ������ = N�̃o�C�g( MUBYTE)�����@���s
#define MBTRCPRINTF( S, F)		mlLog::Print( S, F)			// ������ = �����@���s
#define MBTRCPRINTFN( S, F, N)	mlLog::Print( S, F, N)			// ������ = N�̎����@���s

#include "MsBasic.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MBLOG_DO
	#pragma message( "<<< mlLog�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== mlLog�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

//===========================================================================
//�y�@�\�z	�g���[�X
//
class DLL_EXPORT mlLog
{
public:
	static MCHAR	m_Str[1000];
	static FILE*	m_File;
	static MINT		m_iCtl;

public:
	static void	OpenTrace( MCHAR* i_sFileName);
	static void	CloseTrace( );
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
	static void	Trace( MCHAR* str);
	static void	Trace( );
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_TRACE_DO
	#pragma message( "<<< Trace�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Trace�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

//===========================================================================
//�y�@�\�z	�g���[�X
//
class  DLL_EXPORT Trace
{
private:
	static	MCHAR	m_cLogFilePath[MAX_PATH];					// �g���[�X�t�@�C����
	static	FILE*	m_pfp;										// �g���[�X�t�@�C���|�C���^
	static	MINT	m_iDepth;									// �g���[�X�C���f���g�[��
	static	MCHAR	m_cDepth[Msizeof( MBTRCINDENT) * (MBTRCMAXDEPTH + 1)];
																// �g���[�X�C���f���g
			MCHAR	m_cFuncName[MBTRCFUNCNAME];					// �֐���
	
public:
	Trace( void);
	Trace( MCHAR* i_cFuncName);
	~Trace( void);
	// ���O�t�@�C���̍폜�ƃI�[�v��
	static void OpenLogFile(
						MCHAR i_cLogFilePath[]	// ���O�t�@�C���p�X
						);
	// ���O�t�@�C���̃N���[�Y
	static void CloseLogFile( void);
	// ���O�f�[�^��������
	void Write( MCHAR i_cFormat[], ...);
	// ���O�f�[�^�s��������
	void WriteLine( MCHAR i_cOut[]);
};
//extern	CMbDebug g_MbDbg;

} // namespace MC
