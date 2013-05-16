#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsDefFunc.h
//
//		��{�@�萔�E�֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

#include "MsLib.h"
#include "MsMsg.h"

//===========================================================================
//		�����񑀍�
//
#define		Mchar( cha)			_TEXT( cha)		// �L�����N�^UNICODE�ϊ�
#define		Mstring( str)		_TEXT( str)		// ������UNICODE�ϊ�
#define		Mstr( str)			_TEXT( str)		// ������UNICODE�ϊ�
#define		MBCstr( str)		( str)			// ������MBC	���ϊ�
#define		Mgetchar( str, n)	string[number]	// �����񒆂̃L�����N�^�̎擾
#define		Msizeof( str)		( sizeof( str)/sizeof( MCHAR)-1)
												// ������T�C�Y
#define		Mstrcpy				_tcscpy			// ������̕���
#define		Mstrcpy_s			_tcscpy_s		// ������̕���
#define		Mstrncpy			_tcsncpy		// ������̕��� (��������NULL���܂܂Ȃ�)
#define		Mstrncpy_s			_tcsncpy_s		// ������̕��� (��������NULL���܂܂Ȃ�)�@( ����NULL��t���ăR�s�[)
#define		Mstrcat				_tcscat			// ������̘A��
#define		Mstrcat_s			_tcscat_s		// ������̘A��
#define		Mstrncat			_tcsncat		// ������̘A�� (��������NULL���܂܂Ȃ�)
#define		Mstrncat_s			_tcsncat_s		// ������̘A�� (��������NULL���܂܂Ȃ�)
#define		Mstrcmp				_tcscmp			// ������̔�r
#define		Mstrcmp_s			_tcscmp_s		// ������̔�r (��������NULL���܂܂Ȃ�)
#define		Mstricmp			_tcsicmp		// ������������������Ĕ�r
#define		Mstricmp_s			_tcsicmp_s		// ������������������Ĕ�r (��������NULL���܂܂Ȃ�)
#define		Mstrncmp			_tcsncmp		// ������̔�r (��������NULL���܂܂Ȃ�)
#define		Mstrncmp_s			_tcsncmp_s		// ������̔�r (��������NULL���܂܂Ȃ�)
#define		Mstrnicmp			_tcsnicmp		// ������������������Ĕ�r (��������NULL���܂܂Ȃ�)
#define		Mstrnicmp_s			_tcsnicmp_s		// ������������������Ĕ�r (��������NULL���܂܂Ȃ�)
#define		Mstrchr				_tcschr			// �����񒆂̕����̌��� (str ���� c ���ŏ��ɏo������ʒu���w���|�C���^��Ԃ��Bc ��������Ȃ��ꍇ�́ANULL ��Ԃ��B)
#define		Mstrchr_s			_tcschr_s		// �����񒆂̕����̌��� (str ���� c ���ŏ��ɏo������ʒu���w���|�C���^��Ԃ��Bc ��������Ȃ��ꍇ�́ANULL ��Ԃ��B)
#define		Mstrrchr			_tcsrchr		// �����񒆂̕����̌��� (str ���� c ���Ō�ɏo������ʒu���w���|�C���^��Ԃ��Bc ��������Ȃ��ꍇ�́ANULL ��Ԃ��B)
#define		Mstrrchr_s			_tcsrchr_s		// �����񒆂̕����̌��� (str ���� c ���Ō�ɏo������ʒu���w���|�C���^��Ԃ��Bc ��������Ȃ��ꍇ�́ANULL ��Ԃ��B)
#define		Mstrstr				_tcsstr			// �����񒆂̕�����̌���
#define		Mstrstr_s			_tcsstr_s		// �����񒆂̕�����̌���
//#define	Mstrrstr			_tcsrstr		// �����񒆂̕�����̌���
#define		Mstrtok				_tcstok			// �����񒆂̍ŏ��̃g�[�N�������o��
#define		Mstrtok_s			_tcstok_s		// �����񒆂̍ŏ��̃g�[�N�������o��
#define		Mstrlen				_tcslen			// ������̕��������擾
#define		Mstrlen_s			_tcslen_s		// ������̕��������擾
//	���o��
#define		Msprintf			_stprintf		// �������̈�ւ̏����t���o��
#define		Msprintf_s			_stprintf_s		// �������̈�ւ̏����t���o��
#define		M_snprintf			_sntprintf		// �������̈�ւ̏����t���o��
#define		Mscanf				_tscanf			// �����t������
#define		Mscanf_s			_tscanf_s		// �����t������
#define		Msscanf				_stscanf		// �������̈悩��̏����t������
#define		Msscanf_s			_stscanf_s		// �������̈悩��̏����t������

#define		Mprintf				_tprintf		// �����t���o��
#define		Mfprintf			_ftprintf		// �t�@�C���ւ̏����t���o��
#define		Mfscanf				_ftscanf		// �t�@�C������̏����t������

//	�]��
#define		Misalnum			_istalnum		// �p�����ł���
#define		Misalpha			_istalpha		// �p�����ł���
#define		Miscntrl			_istcntrl		// �폜�����܂��͐��䕶���ł���
#define		Misdigit			_istdigit		// 0-9�̐����ł���
#define		Misgraph			_istgraph		// ���O���t�B�b�N�����ł���
#define		Mislower			_istlower		// �p�������ł���
#define		Misprint			_istprint		// ����p�����ł���
#define		Mispunct			_istpunct		// ��Ǔ_�ł���
#define		Misspace			_istspace		// SPACE,TAB,RETURN,NEWLINE,FORMFEED,�����^�u
#define		Misupper			_istupper		// �p�啶���ł���
#define		Misxdigit			_istxdigit		// 0-9,A-F,a-f��16�i�����ł���

//	�ϊ�
#define		Mtolower			_totlower		// �������������ɕϊ�
#define		Mtoupper			_totupper		// ������啶���ɕϊ�
#define		Mstrlwr				_tcslwr			// ������̏�������
#define		Mstrlwr_s			_tcslwr_s		// ������̏�������
#define		Mstrupr				_tcsupr			// ������̑啶����
#define		Mstrupr_s			_tcsupr_s		// ������̑啶����
#define		Matoi				_tstoi			// ������𐮐��ɕϊ�
#define		Mwtoi				_tstoi			// ������𐮐��ɕϊ�
#define		Matol				_tstol			// ������𐮐��ɕϊ�
#define		Mwtol				_tstol			// ������𐮐��ɕϊ�
#define		Matof				( MREAL)_tstof	// ������������ɕϊ�
#define		Mwtof				( MREAL)_tstof	// ������������ɕϊ�
#define		Matodbl				_tstodbl		// ������������ɕϊ�
#define		Mwtodbl				_tstodbl		// ������������ɕϊ�

//===========================================================================
//		�t�@�C������
//
#define		Mfopen				_tfopen			// �t�@�C���I�[�v��
#define		Mfopen_s			_tfopen_s		// �t�@�C���I�[�v��
#define		Mfclose				fclose			// �t�@�C���N���[�Y
#define		Mfflush				fflush			// �X�g���[�����t���b�V��


#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_BASE_DO
	#pragma message( "<<< Base�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Base�Edll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{
//===========================================================================
//		���^�[��
class DLL_EXPORT ms : public mslib, public msmsg
{
public:
	//===========================================================================
	//		���{�ꃂ�[�h
	//
	static void	SetJapanese( );

	//===========================================================================
	//		�o�b�t�@���� fill memory, copy memory, copy memcopys
	//
	//===========================================================================
	//	�����𕶎���S�̂ɃR�s�[����( fill)
	//
	static void Fill( void *sdest, char cdt, int nsz)
	{
		memset( sdest, cdt, nsz);
		//	for ( int n=0; n<nsz; sdest[n++]=cdt);
	}

	//===========================================================================
	//	�����𐮐��z��S�̂ɃR�s�[����( fill)
	//
	static void Fill( int* idest, int idt, int nsz)
	{
		for ( int n=0; n<nsz; idest[n++]=idt);
	}

	//===========================================================================
	//	�����������z��S�̂ɃR�s�[����( fill)
	//
	static void Fill( MREAL *rdest, MREAL rdt, int nsz)
	{
		for ( int n=0; n<nsz; rdest[n++]=rdt);
	}

	//===========================================================================
	//	�����z�񂩂當���z��փR�s�[����( memcpy)
	//
	static void Copy( char *sdest, char *ssource, int nsz)
	{
		memcpy( sdest, ssource, nsz);
	//	for ( int n=0; n<nsz; n++) sdest[n] = ssource[n];
	}

	//===========================================================================
	//	�����z�񂩂琮���z��փR�s�[����( memcpy)
	//
	static void Copy( int* idest, int* isource, int nsz)
	{
		memcpy( idest, isource, nsz*4);
	//	for ( int n=0; n<nsz; n++)
	//		idest[n] = isource[n];
	}

	//===========================================================================
	//	�����z�񂩂�����z��փR�s�[����( memcpy)
	//
	static void Copy( MREAL *rdest, MREAL *rsource, int nsz)
	{
		memcpy( rdest, rsource, nsz*4);
	//	for ( int n=0; n<nsz; n++)
	//		idest[n] = isource[n];
	}

	//===========================================================================
	//	�����z�񂩂當���z��փR�s�[����( memcpy)
	//	�̈�̏d�Ȃ������
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
	//	�����z�񂩂琮���z��փR�s�[����( memcpy)
	//	�̈�̏d�Ȃ������
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
	//	�����z�񂩂�����z��փR�s�[����( memcpy)
	//	�̈�̏d�Ȃ������
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
//	//	�G���[���^�[���u���[�N�|�C���g�p
//	//
//	static void	ErrorReturn( void);
//	
//	static void	SysError( 
//							MCHAR*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode,						// �G���[�R�[�h
//							MCHAR*				i_cComment = 0						// �R�����g
//							);
//	static void	SysError( 
//							MCHAR*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode,						// �G���[�R�[�h
//							char*				i_cComment							// �R�����g
//							);
//	static void	SysError( 
//							char*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode,						// �G���[�R�[�h
//							MCHAR*				i_cComment = 0						// �R�����g
//							);
//	static void	SysError( 
//							char*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode,						// �G���[�R�[�h
//							char*				i_cComment							// �R�����g
//							);
//	static void	CmdError( 
//							char*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode						// �G���[�R�[�h
//							);
//	static void	CmdError( 
//							MCHAR*				i_pcProgram,						// �G���[�v���O������
//							int					i_iLineN,							// �s�ԍ�
//							int					i_iErrorCode						// �G���[�R�[�h
//							);
//
//	/////////////////////////////////////////////////////////////////////////////////
//	//////		���^�[���R�[�h
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
//		��������
//
#define		MBRED( Col)			( Col & 0xFF)
#define		MBGREEN( Col)		( ( Col >> 8) & 0xFF)
#define		MBBLUE( Col)		( ( Col >> 16)& 0xFF)

//===========================================================================
//		�t���O�`�F�b�N
//

inline bool MF_CHECK_ON( MINT a, MINT mask)						// mask�̏������n�m�ł��邩�`�F�b�N
				{ return ( ( a & mask) != 0);}

inline bool MF_CHECK_OR( MINT a, MINT mask)						// mask�̂����ꂩ�̏������n�m�ł��邩�`�F�b�N
				{ return ( ( a & mask) != 0);}

inline bool	MF_CHECK_AND( MINT a, MINT mask)					// mask�̑S�Ă̏������n�m�ł��邩�`�F�b�N
				{ return ( ( a & mask) == mask);}

inline bool	MF_CHECK_EQ( MINT a, MINT mask)						// mask�̑S�Ă̏������Z�b�g����Ă���
				{ return ( a == mask);}							// ���̏����̃Z�b�g���������Ƃ��`�F�b�N

inline bool	MF_CHECK_OFF( MINT a, MINT mask)					// mask�̏������n�e�e�ł��邩�`�F�b�N
				{ return ( ( ~( a) & mask) != 0);}

inline bool	MF_CHECK_OFF_OR( MINT a, MINT mask)					// mask�̂����ꂩ�̏������n�e�e�ł��邩�`�F�b�N
				{ return ( ( ~( a) & mask) != 0);}
				
inline bool	MF_CHECK_OFF_AND( MINT a, MINT mask)				// mask�̑S�Ă̏������n�e�e�ł��邩�`�F�b�N
				{ return ( ( ~( a) & mask) == mask);}

inline void MF_SET_ON( MINT &a, MINT mask)						// mask�̏������Z�b�g����
				{ a |= mask;}

inline void MF_SET_OFF( MINT &a, MINT mask)						// mask�̏������N���A����
				{ a &= ~( mask);}

inline void MF_RESET_ON( MINT &a, MINT mask)					// mask�̏������N���A����
				{ a &= ~( mask);}

inline void MF_RESET( MINT &a)									// �O�������N���A����
				{ a = 0;}

inline bool MI_CHECK_ODD( MINT n)								// ��`�F�b�N
				{ return ( n & 1);}

inline bool MI_CHECK_EVEN( MINT n)								// �����`�F�b�N
				{ return ( !MI_CHECK_ODD( n));}

#define 	MQUIT				{ goto exit;}
 				
#define 	MQUIT_IF_FAILED( p)	{ if ( !p) { rc = DM_MEM; goto exit;}}

#define		MQUIT_STS( s)		{ iSt = s; goto exit;}

//===========================================================================
//		�i�v���[�v
//
#define		MFOREVER			for ( ;;)

//===========================================================================
//		0�`1. �Ԃ� �����_�������l�𔭐�
//
#define FRAND	( ( double)rand( )/( double)RAND_MAX)

//===========================================================================
//		�^�C�v���w�肵���Q�̃I�u�W�F�N�g������
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


