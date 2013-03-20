//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbFile.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#pragma warning( disable : 4996 )
#include "stdafx.h"
#define	DLL_EXPORT_CODE_DO
#include "MsBasic.h"

#define	DLL_EXPORT_FILE_DO
#include "MfFile.h"

namespace MC
{

// *******************************************************************************
//	CSV�t�@�C���̓ǂݍ��� �g�p���@
//
//	MBFILE	csv
//	ist = csv.Open( )
//	ist = csv.NextLine( )
//  ist = csv.Head( Str, 10);
//  ist = csv.GetStr( Str, 10);
//  ist = csv.GetReal( Flt, 3);
//  ist = csv.GetInt( Int, 10);
//	ist = csv.Close( )
//
// *******************************************************************************

// *******************************************************************************
//�y�@�\�z�t�@�C���ǂݏ��������J�n�錾
//�y�Ԓl�z==  0 : ����I��
//	�@�@�@== -2 : ���ɃI�[�v������Ă���
//		�@�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBFILE::Open( 
				MCHAR*	i_pcFileName,			// �t�@�C����
				DWORD	i_Mode					// �������[�h
												//		== MBREAD:		�ǂݍ��ݐ�p
												//		== MBWRITE:		�������ݐ�p
												//		== MBREADWRITE: �ǂݏ����\
				)
{
	int		ist0;								// �X�e�C�^�X
	ist0 = 0;
		if ( m_stat != 0) {						// ���ɃI�[�v������Ă���
			ist0 = STS_OPENED;	goto END;
		};
	if ( i_Mode == MBREAD) {
		m_fileHandle = CreateFileW( i_pcFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		m_stat = MBREAD;
	} else if ( i_Mode == MBWRITE) {
		m_fileHandle = CreateFileW( i_pcFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		m_stat = MBWRITE;
	} else {
		ist0 = STS_ACSMDERR;	goto END;
	}
	if ( m_fileHandle == INVALID_HANDLE_VALUE) {
		ist0 = STS_FLOPNERR;	goto END;
	}
END:
	return	ist0;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C���ǂݏ��������I���錾
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int	MBFILE::Close( void)
{
	CloseHandle( m_fileHandle);
	m_stat = 0;
	return 0;									//	�v�C��
}

//===========================================================================
//�y�@�\�z		:�t�@�C���̍X�V�����擾����
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[
//===========================================================================
MINT MBFILE::GetFileDate(
						MCHAR*	i_cFilePath,	// �t�@�C����
						MCHAR	o_cDate[9]		// �t�@�C���̍쐬��
						)
{
	MINT		ist;
	HANDLE		hFile;
	FILETIME	FileTime;
	FILETIME	LocalFileTime;
	SYSTEMTIME	SystemTime;

	hFile = CreateFile( i_cFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hFile == INVALID_HANDLE_VALUE) {
		o_cDate[0] = 0;
		ist = -1;

	} else {
		GetFileTime( hFile, NULL, NULL, &FileTime);
		FileTimeToLocalFileTime( &FileTime, &LocalFileTime);
		FileTimeToSystemTime( &LocalFileTime, &SystemTime);
		Msprintf_s( o_cDate, sizeof( o_cDate), Mstr( "%04d%02d%02d"), SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);
		ist = 0;
	}
	CloseHandle(hFile);

	return ist;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C�����ړǂݍ��ݏ����J�n�錾
//�y�Ԓl�z==  0 : ����I��
//		�@== -2 : ���ɃI�[�v������Ă���
//		�@�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::Open( 
				MCHAR*	i_pcFileName			// ( I ) �t�@�C����
				)
{
	m_icsLine = 0;
	m_icsDbuf = 0;
	m_fhead = 1;
	return 	MBFILE::Open( i_pcFileName, MBREAD);
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C�����ړǂݍ��ݏ����I���錾
//�y�Ԓl�z==  0 : ����I��
//		�@��  0 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int	MBHZDT::Close( void)
{
	m_fopen=0;
	m_fback=0;
	m_icsDbuf = -1;								// �����ǂݍ��ݏ����o�b�t�@����( -1)
	m_icsLine = 0;								// �����ǂݍ��ݏ����o�b�t�@�̐擪

	return	MBFILE::Close( );
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z���s�ǂݍ���
//�y�Ԓl�z == 0 : ����I��
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::NextLine( void)
{
	if ( m_fopen == MBEOL) {
		m_fopen = 0;
	}
	if ( m_fopen != MBEOF) {
		Skip( 0 );
	}
	m_fhead = 1;
	return m_fopen;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z���s�̐擪�����񍀖ڂ�ǂݍ���
//�y�Ԓl�z >  0 : �ǂݍ��ݕ�����
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::Head( 
				MCHAR*	str,					// ( O) �ǂݍ��ݕ�����
				int		cbstr					// ( I ) �ǂݍ��ݍő啶����
			)

{
	if ( m_fhead == 0) 
		if ( NextLine( ) == MBEOF)
			return MBEOF;
	m_fhead = 0;
	return GetStr( str, cbstr );
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z���̍��ڌQ���щz��
//�y�Ԓl�z >  0 : ����
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int 	MBHZDT::Skip( 
				int		ns						// ( I ) ns �� 0	�X�L�b�v���鍀�ڐ�
												//         �� 0 �P�s�X�L�b�v
				)
{
	char	Str[1];
	int		isf;
	int		ik;
//
	if ( m_fopen < 0) {
		isf = m_fopen;							// MBEOL �܂��� MBEOF
		goto END;
	}
	if ( ns == 0) {
		do {
			isf = GetCh( );
		} while ( ( isf != MBEOL) && ( isf != MBEOF));
		if ( isf == MBEOL) isf = 0;
		m_fhead = 1;
	} else {
		for ( ik=0; ik<ns; ik++) {
			isf = GetStrC( Str, 1 );
			if( ( isf == MBEOL) || ( isf == MBEOF)) break;
		}
		m_fhead = 0;
	}
	m_fopen = isf;
END:
	return isf;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C�����w�萔�̎������ڂ�ǂݍ���
//�y�Ԓl�z >  0 : �ǂݍ��ݍ��ڐ�
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::GetReal( 
				MREAL	*rb,					// ( O) �ǂݍ��ݐ�����o�b�t�@
				int		icrb					// ( I ) �ǂݍ��ݍ��ڐ�
			)
{
	char Str[MBCBSLINE];						//	���ڃf�[�^
	int ik;										//	�ǂݍ��ݍ��ڐ�
	int	ic;

	if ( ( m_fopen == MBEOL) || ( m_fopen == MBEOF)) {
		ik = m_fopen;
		goto END;
	}

	for( ik=0; ik<icrb; ) {
		UINT ichs = GetStrC( Str, MBCBSLINE );
		if( ( ichs == 0) || ( ichs == MBEOL)) {
			rb[ik] = 0;
		} else {
			#ifdef MG_DOUBLE_PRECISION_REAL
				sscanf_s( Str, "%lf", &rb[ik]);
			#else
				sscanf_s( Str, "%f", &rb[ik]);
			#endif
		}
		ik++;
	}
	for( ic=ik; ic<icrb; ic++) rb[ic] = 0.;
END:
	m_fhead = 0;
	return ik;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C�����w�萔�̐������ڂ�ǂݍ���
//�y�Ԓl�z >  0 : �ǂݍ��ݍ��ڐ�
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::GetInt( 
				int		*ib,					//	�ǂݍ��ݐ搮���o�b�t�@
				int		icib					//	�ǂݍ��ݍ��ڐ�
			)
{
	char	Str[MBCBSLINE];						//	���ڕ�����o�b�t�@
	int		ik;									//	���ڃJ�E���^
	int		ic;									//	�c���ڃJ�E���^

	if( ( m_fopen == MBEOL) || ( m_fopen == MBEOF)) {
		ik = m_fopen;
		goto END;
	}

	for( ik=0; ik<icib; ) {
		UINT ichs = GetStrC( Str, MBCBSLINE );
		if( ( ichs == 0) || ( ichs == MBEOL)) ib[ik] = 0;
		else sscanf_s( Str, "%d", &ib[ik] );
		ik++;
	}
	for( ic=ik; ic<icib; ic++) ib[ic] = 0;
END:
	m_fhead = 0;
	return ik;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C����蕶���񍀖ڂ��P���ړǂݍ���
//�y�Ԓl�z >  0 : �ǂݍ��ݕ�����
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::GetStr( 
				MCHAR*	Str,					// ( O) �ǂݍ��ݕ�����
				int		cbStr					// ( I ) �ǂݍ��ݍő啶����( ASCII���������G���A�Ŋ��Z���ŏINULL���܂܂Ȃ�������)
												//		EOL �܂��� EOF�@�Ȍ�� 0
				)
{
	MINT	ist;
	char	StrC[1000];
	ist = GetStrC( StrC, cbStr * 2);
	Code::msbstowcs( StrC, Str, cbStr);   
	return ist;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C����蕶���񍀖ڂ��P���ړǂݍ���
//�y�Ԓl�z >  0 : �ǂݍ��ݕ�����
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
//		�� -3 : ���̑��G���[
//�y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::GetStrC( 
				char	*Str,					// ( O) �ǂݍ��ݕ�����
				int		cbStr					// ( I ) �ǂݍ��ݍő啶����( NULL���܂܂�)
												//		EOL �܂��� EOF�@�Ȍ�� 0
				)
{
	int		ist0;								//	�X�e�C�^�X
	int		iclp;								//	�ǂݍ��ݕ�����
	int		fdbq;								//  '"'�ŋ��܂ꂽ������
												//	0:�擪����!='"'�A1,2:�擪����=='"'�̏ꍇ��'"'�̐�
	char	chs;

	ist0 = 0;

	Str[0] = 0;
	if( ( m_fopen == MBEOL) || ( m_fopen == MBEOF)) {
		iclp = m_fopen;
		goto END;
	}
//
//	��؂蕶���������܂ōs�o�b�t�@���ǂݍ���
	fdbq = 0;
	iclp = 0;
	for( ;;) {
		chs = GetCh( );
		if( ( chs == MBEOL) || ( chs == MBEOF)) break;		// MBEOL �܂��� MBEOF
		if( ( chs == ';')) {
			Skip( 0 );									// next line
			chs = GetCh( );
			if( ( chs == MBEOL) || ( chs == MBEOF)) break;	// MBEOL �܂��� MBEOF
		}
//		if( ( chs == ' ') || ( chs == '\x09')) break;
		if( ( chs == ',') && ( fdbq != 1)) break;
		if ( ( chs != 0x0A) && ( chs != 0x0D) && ( iclp < cbStr)) {
//
			if ( iclp == 0 && chs == '"') {				// 0:�擪���� == '"'
				fdbq = 1;
			} else if ( fdbq == 1 && chs == '"') {		// �擪���� == '"'�̏ꍇ��'"'�̃J�E���g( MAX 2)
				fdbq++;
			} else {
				Str[iclp++] = chs;
			}
		}
	}
//	if( iclp < cbStr) Str[iclp] = 0;
	if( chs == ';') {
		Skip( 0 );										// next line
	}
//
//	�X�y�[�X����у^�u�����ȊO�̕����������܂ōs�o�b�t�@�̕����ʒu��i�߂�
	while( ( chs != MBEOL) && ( chs != MBEOF)) {
		chs = GetCh( );
		if( chs == ';') {
			Skip( 0 );									// next line
		} else if ( chs == ' ') {
		} else if ( chs == '\x09') {
		} else {
			break;
		}
	}
	BackCh( );
//
//	�o�b�t�@�̌��̃X�y�[�X�����
	iclp--;
	for ( ; iclp>=0; iclp--) {
		if ( ( Str[iclp] != ' ') && ( Str[iclp] != '\x09'))  break;
	}
	iclp++;
	Str[iclp] = 0;
END:
	m_fhead = 0;
	return iclp;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z�t�@�C�����P�����ǂݍ���
//�y�Ԓl�z>=  0 : �����R�[�h
//		== -1 : �t�@�C���̏I���	( MBEOF)
//		== -2 : �s�̏I���			( MBEOL)
// �y���Ӂz�Ȃ�
// ********************************************************************************

int		MBHZDT::GetCh( 
				void
				)
{
	static int	chs;							//	�ǂݍ��ݕ���
	BOOL		successR;						//	�t�@�C���ǂݍ��݃X�e�C�^�X
//
	if( m_fopen < 0) {
		//	�e�L�X�g�t�@�C���̓ǂݍ��ݏ����󋵃t���O( m_fopen )�𒲂ׁA
		//	�s�̏I���܂��̓t�@�C���̏I���Ȃ� MBEOL �܂��� MBEOF ��Ԃ��B
		chs = m_fopen;							// MBEOL �܂��� MBEOF
		goto END;
	}
	if( m_fback == 1) {
		//	�ꕶ���߂��t���O( m_fback )�������Ă���( 1)�Ȃ�΍Ō�ɓǂݍ��񂾕�����Ԃ�
		//  ���t���O������
		m_fback = 0;
	}
	else {
		//	�ꕶ���߂��t���O( m_fback )�������Ă��Ȃ�( 0)�Ȃ�
		if ( m_icsLine >= m_icsDbuf) {
			//	( �����ǂݍ���)�����o�b�t�@���̕����񂪂��ׂď����ς݂ł���ꍇ�́A
			//	�t�@�C�����瓯�����o�b�t�@�ɁA�����������ǂݍ��ށB
			successR = ReadFile( m_fileHandle, m_sDbuf, MBCBSDBUF, ( DWORD*)&m_icsDbuf, 0);
			m_icsLine = 0;						// �����ςݕ����� = 0
			if( ( !successR) || ( m_icsDbuf <= 0)) {
				// �t�@�C�����ɑ��������������ꍇ�́A�t�@�C���̏I���( MBEOF )��Ԃ��ďI��
				m_fopen = MBEOF;
				chs = MBEOF;
				goto END;
			}
		}
		//	( �����ǂݍ���)�����o�b�t�@�����ꕶ�����o���B
		chs = m_sDbuf[m_icsLine++];
		if( chs == 0x0A) {
		    //	���o�������������s�����Ȃ�΁A�s�̏I���( MBEOL )��Ԃ��ďI��
			m_fopen = MBEOL;
			chs = MBEOL;
		}
	}
END:
	return chs;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�z���������|�C���^���ꕶ���߂�
//        ( �ꕶ���߂����Ƃ�\�킷�t���O�𗧂Ă�)
//�y�Ԓl�z�Ȃ�
//�y���Ӂz�Ȃ�
// ********************************************************************************

void	MBHZDT::BackCh( 
		void
		)
{
	m_fback = 1;
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�zMBCS�������UNICODE������ɕϊ�����
//�y�Ԓl�z 0 : ����     -1 : �ُ�
//�y���Ӂz�Ȃ�
// ********************************************************************************

MINT Code::msbstowcs( 
				char*	i_StrC,					// MBCS������
				MCHAR*	o_StrU,					// UNICODE������
				MINT	i_iSize					// �ő啶����
				)
{

#ifdef _UNICODE
	MINT iLen = ( MINT)strlen( i_StrC);

	if ( iLen == 0) {
		o_StrU[0] = NULL;
		return( 0);
	} else {
		MINT iLen1 = MultiByteToWideChar( CP_ACP, 0, ( LPCSTR)i_StrC,  iLen,  ( LPWSTR)o_StrU, i_iSize);
		if ( iLen1 == 0) {
			o_StrU[0] = NULL;
			return( -1);
		} else {
			o_StrU[min( iLen1, i_iSize)] = NULL;
			return( 0);
		}
	}
#else
	Mstrncpy_s( StrU, StrC, iSize+1);
	return( 0);
#endif
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�zUNICODE�������MBCS������ɕϊ�����
//�y�Ԓl�z 0 : ����     -1 : �ُ�
//�y���Ӂz�Ȃ�
// ********************************************************************************

MINT Code::mswcstombs( 
				MCHAR*	StrU,					// ( I  ) UNICODE������
				char*	StrC,					// (  O) MBCS������
				MINT	iSize					// ( I  ) �ő啶����
				)
{
#ifdef _UNICODE
	MINT iLen = ( MINT)Mstrlen( StrU);
	if ( iLen == 0) {
		StrC[0] = NULL;
		return( 0);
	} else {
		MINT iLen1 = WideCharToMultiByte( CP_ACP, 0, ( LPCWSTR)StrU, iLen, ( LPSTR)StrC, iSize, NULL, NULL);
		if ( iLen1 == 0) {
			StrC[0] = NULL;
			return( -1);
		} else {
			StrC[min( iLen1, iSize)] = NULL;
			return( 0);
		}
	}

#else
	strcpy( StrC, StrU);
	return( 0);
#endif
}

} // namespace MC
