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

// ���O�擾����
#ifdef _DEBUG
#define LOGOUT
#else
#undef LOGOUT
#endif

//#define LOGOUT									// releasemode�ł����O�쐬����悤�ɐݒ�

// ���O�擾��`
#define MBLOGMAXDEPTH			10								// �g���[�X�C���f���g�ő�[��
#define MBLOGINDENT				Mstr( "  ")						// �g���[�X�C���f���g
#define MBLOGFUNCNAME			40								// �֐����ő啶����

#define MBLOGOPEN( fn)			mlLog::OpenLogFile( fn)			// �g���[�X�J�n�錾�@�t�@�C����
#define MBLOGCLOSE				mlLog::CloseLogFile( )			// �g���[�X�I���錾
#define MBLOGON					mlLog::Ctrl( 1)					// �g���[�X�@�n�m
#define MBLOGOFF				mlLog::Ctrl( 0)					// �g���[�X�@�n�e�e
#define MBLOGPRBF				mlLog::Trace( )					// �g���[�X�o�b�t�@���̕�����
#define MBLOGPRS( S)			mlLog::Trace( S)				// ������
#define MBLOGFLUSH				mlLog::Flush( )					// �t���b�V���i�g���[�X���̍�ƃG���A���������|�������j

#define MBLOGPRINTCR			mlLog::PrintCR( )				// ���s
#define MBLOGPRINTS( S)			mlLog::Print( S)				// ������@���s
#define MBLOGPRINTSS( S, T)		mlLog::Print( S, T)				// ������ = ������@���s
#define MBLOGPRINTI( S, I)		mlLog::Print( S, I)				// ������ = �����@���s
#define MBLOGPRINTIN( S, I, N)	mlLog::Print( S, I, N)			// ������ = N�̐����@���s
#define MBLOGPRINTB( S, B)		mlLog::Print( S, B)				// ������ = �o�C�g( MUBYTE)�����@���s
#define MBLOGPRINTBN( S, B, N)	mlLog::Print( S, B, N)			// ������ = N�̃o�C�g( MUBYTE)�����@���s
#define MBLOGPRINTF( S, F)		mlLog::Print( S, F)				// ������ = �����@���s
#define MBLOGPRINTFN( S, F, N)	mlLog::Print( S, F, N)			// ������ = N�̎����@���s

#define MBLOGOUT				mlLog::LogOut					// �t�H�[�}�b�g�t���ŏo�͂���
#define MBLOGOUTWL				mlLog::LogOutWL					// ���O���x���ƃt�H�[�}�b�g�t���ŏo�͂���

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
	
enum LogType {
	MC_LOG_ERROR = 1,
	MC_LOG_WARNING,
	MC_LOG_NORMAL
};

//===========================================================================
//�y�@�\�z	���O
//
class DLL_EXPORT mlLog
{
public:
	static MCHAR	m_Str[1000];
	static FILE*	m_File;
	static MINT		m_iCtl;

public:
	static void	OpenLogFile( MCHAR* i_sFileName);
	static void	CloseLogFile( );
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
	static void LogOut( MCHAR* i_cFormat, ...);					// �t�H�[�}�b�g�t���ŏo�͂���
	static void LogOutWL( int i_iLevel, MCHAR* i_cFormat, ...);	// ���O���x���ƃt�H�[�}�b�g�t���ŏo�͂���
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
	static	MCHAR	m_cDepth[Msizeof( MBLOGINDENT) * (MBLOGMAXDEPTH + 1)];
																// �g���[�X�C���f���g
			MCHAR	m_cFuncName[MBLOGFUNCNAME];					// �֐���
	
public:
	Trace( void);
	Trace( MCHAR* i_cFuncName);
	~Trace( void);
	static void OpenTraceFile(									// ���O�t�@�C���̍폜�ƃI�[�v��
						MCHAR i_cLogFilePath[]	// ���O�t�@�C���p�X
						);
	static void CloseTraceFile( void);							// ���O�t�@�C���̃N���[�Y
	static void Write( MCHAR i_cFormat[], ...);					// ���O�f�[�^��������
	static void WriteLine( MCHAR i_cOut[]);						// ���O�f�[�^�s��������
};
//extern	CMbDebug g_MbDbg;

} // namespace MC
