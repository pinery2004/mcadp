//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhFile.cpp
//
//		�\���ƃ��f���ǂݏ����h�n����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "afxdlgs.h"

#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"

#include "MhDefParts.h"
#include "MsBitSet.h"
#include "MdOpt.h"

#define DLL_EXPORT_IEMODEL_DO
#include "MhLib.h"

#include "MfFile.h"
#include "MsLib.h"

namespace MC
{

static MCHAR*	 z_cTitle = Mstr( "MCAD");
static MCHAR*	 z_cVer = Mstr( "V0.01");

#if( TRACE_IO)
	int	iCwr_IO = 1;
	int	iCrd_IO = 1;
	int	iCnw_IO = 1;
	int iCrf_IO = 1;
	int iCht2_IO = 1;
	int iCrf2_IO = 1;
	int iCzk_IO = 1;
#endif
////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�\���ƃ��f��

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�R���X�g���N�^

MhMdlIO::MhMdlIO()
{
	memset( &m_Header, 0, sizeof(MhMdlHeader));
	Mstrcpy_s( m_Header.cTitle, z_cTitle);
	Mstrcpy_s( m_Header.cVer, z_cVer);
	m_Header.cTime = ms::GetCurrentTime();						// �쐬���� 
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�f�X�g���N�^
MhMdlIO::~MhMdlIO          ()
{
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�t�@�C���ǂݏ��������J�n�錾
//�y�Ԓl�z==  0 : ����I��
//		  == -2 : ���ɃI�[�v������Ă���
//		  �� -3 : ���̑��G���[

MINT MhMdlIO::Open(
				const	DWORD		iMode,		// (I ) �g�p���[�h
												//		== MBREAD:	�ǂݍ��ݐ�p
												//		== MBWRITE:	�������ݐ�p
				const	MCHAR*		cFilePath
				)
{
	MINT		ist = -1;
	MINT		OutSiz;
	MUINT		nOpenFlag;										// �A�N�Z�X���[�h

	Mstrcpy_s( m_MdlPath, cFilePath);

	if ( iMode == MBREAD) {
		nOpenFlag = CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary;
	} else if ( iMode == MBWRITE) {
		nOpenFlag = CFile::modeWrite | CFile::modeCreate | CFile::shareExclusive;
	}
	
	if ( !m_File.Open( cFilePath, nOpenFlag)) {
		ist = -3;
		MQUIT;
	}

	if ( iMode == MBREAD) {
		OutSiz = m_File.Read( &m_Header, sizeof( MhMdlHeader));
		if ( OutSiz != sizeof( MhMdlHeader))
			MQUIT;
		if ( Mstrcmp( m_Header.cTitle, z_cTitle) != 0)
			MQUIT;
		MINT	itr;
		OutSiz = m_File.Read( &itr, SZMINT());
		OutSiz = m_File.Read( &itr, SZMINT());
	} else if ( iMode == MBWRITE) {
		m_File.Write( &m_Header, sizeof(MhMdlHeader));
		MINT	it = 333;
		m_File.Write( &it, SZMINT());
		it = 777;
		m_File.Write( &it, SZMINT());
	}
	ist = 0;
#if( TRACE_IO)
	iCwr_IO = 1;
	iCrd_IO = 1;
	iCnw_IO = 1;
	iCrf_IO = 1;
	iCht2_IO = 1;
	iCrf2_IO = 1;
	iCzk_IO = 1;
#endif
exit:
	return( ist);
}


////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�t�@�C���ǂݏ��������I���錾
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::Close()
{
	MINT		ist;
//	MINT		ist1;
	MINT		iSize = 0;

	ist = -1;

	if ( m_iMode == MBWRITE) {
		m_File.Write( &iSize, SZMINT());
		m_File.Write( &iSize, SZMINT());
	}

	m_File.Close();

	return ( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�t�@�C���ǂݍ���
//�y�Ԓl�z > 0 : �ǂݍ��݃o�C�g��
//		  == 0 : �I��
//		   < 0 : ���̑��G���[

MINT MhMdlIO::ReadItem(
						MINT*		o_piTp,		// (  O) ����
						void**		o_Buf		// (  O) �Ǎ��ݗ̈�
				)
{
	MINT		iSizeR;
	MINT		iSizeW;

	iSizeW = m_File.Read( o_piTp, SZMINT());

	if ( iSizeW != SZMINT()) {
		iSizeR = -1;
		MQUIT;
	}

	iSizeW = m_File.Read( &iSizeR, SZMINT());

	if ( iSizeW != SZMINT()) {
		iSizeR = -1;
		MQUIT;
	}
	if ( iSizeR == 0)
		MQUIT;													// �I��

	//int* pTest = new int[2];
//===
#if( TRACE_IO)
	TRACE( "%d-%d: new char[%d]\n", iCht2_IO, iCnw_IO++, iSizeR);
#endif
//---
	*o_Buf = (byte *)new char[iSizeR];
	ASSERT( *o_Buf);											// �������@��A���b�N�G���[�@<ERROR>
	iSizeW = m_File.Read( *o_Buf, iSizeR);

	if ( iSizeW != iSizeR) {
		iSizeR = -1;
		MQUIT;
	}

#if( TRACE_IO)
	int		iWd = iSizeR/4;
	MREAL*	pBuf = (MREAL*)*o_Buf;	
	if( iSizeR > 0 && iSizeR <SZMINT()) {
		iWd = 1;
		if( iSizeR == sizeof( MUBYTE)) {
			TRACE( " Read [%d]:\tTp = %d,\tCh = %d", iCwr_IO++, *o_piTp, 1);
			TRACE( ",\t%d", ((MUBYTE*)pBuf)[0]);
		} else if( iSizeR == sizeof( MSHORT)) {
			TRACE( " Read [%d]:\tTp = %d,\tSw = %d", iCwr_IO++, *o_piTp, 1);
			TRACE( ",\t%d", ((MSHORT*)pBuf)[0]);
		} else {
			TRACE( " Read [%d]:\tTp = %d,\tCh = %d", iCwr_IO++, *o_piTp, iSizeR);
		}
	} else {
		TRACE( " Read [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, *o_piTp, iWd);
		for( int i=0; i<iWd; i++) {
			TRACE( ",\t%8x", ((MINT*)pBuf)[i]);
		}
	}
	TRACE( "\n");
#endif

exit:
	return ( iSizeR);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�C�ӌ^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItems(
				const	MINT		i_iTp,		// ����
				const	void*		i_Bf,		// �����ݗ̈�
				const	MINT		i_iSz		// �������޲Đ�
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_Bf, i_iSz);									// �C�ӌ^�f�[�^
	ist = 0;
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zSHORT�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemIS(
				const	MINT		i_iTp,		// �^�C�v
				const	MSHORT*		i_iBf,		// ������SHORT�z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_iBf, i_iSz);								// �����z��
	ist = 0;

#if( TRACE_IO)
	int		iWd = i_iSz / sizeof( MSHORT);
	TRACE( " Write Short [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, i_iTp, iWd);
	for( int i=0; i<iWd; i++)
		TRACE( ",\t%d", i_iBf[i]);
	TRACE( "\n");
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemI(
				const	MINT		i_iTp,		// �^�C�v
				const	MINT*		i_iBf,		// �����ݐ����z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_iBf, i_iSz);								// �����z��
	ist = 0;

#if( TRACE_IO)
	int		iWd = i_iSz / SZMINT();
	TRACE( " Write Int [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, i_iTp, iWd);
	for( int i=0; i<iWd; i++)
		TRACE( ",\t%d", i_iBf[i]);
	TRACE( "\n");
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemUI(
				const	MINT		i_iTp,		// �^�C�v
				const	MUINT*		i_iBf,		// �����ݐ����z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_iBf, i_iSz);								// �����z��
	ist = 0;

#if( TRACE_IO)
	int		iWd = i_iSz / sizeof( MUINT);
	TRACE( " Write UInt [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, i_iTp, iWd);
	for( int i=0; i<iWd; i++)
		TRACE( ",\t%d", i_iBf[i]);
	TRACE( "\n");
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zFLOAT�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemR(
				const	MINT		i_iTp,		// �^�C�v
				const	float*		i_rBf,		// �����ݎ����z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_rBf, i_iSz);								// ����(float)�z��
	ist = 0;

#if( TRACE_IO)
	int		iWd = i_iSz / sizeof( float);
	TRACE( " Write Flort [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, i_iTp, iWd);
	for( int i=0; i<iWd; i++)
		TRACE( ",\t%.1f", i_rBf[i]);
	TRACE( "\n");
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zDOUBLE�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemR(
				const	MINT		i_iTp,		// �^�C�v
				const	double*		i_rBf,		// �����ݎ����z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_rBf, i_iSz);								// ����(double)�z��
	ist = 0;

#if( TRACE_IO)
	int		iWd = i_iSz / sizeof( double);
	TRACE( " Write Double [%d]:\tTp = %d,\tWd = %d", iCwr_IO++, i_iTp, iWd);
	for( int i=0; i<iWd; i++)
		TRACE( ",\t%.1f", i_rBf[i]);
	TRACE( "\n");
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zBYTE�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemIB(
				const	MINT		i_iTp,		// �^�C�v
				const	MUBYTE*		i_ibBf,		// ������BYTE�z��
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_ibBf, i_iSz);								// BYTE�z��
	ist = 0;
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z����(char)�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemCH(
				const	MINT		i_iTp,		// �^�C�v
				const	char*		i_cDat,		// �����ݕ�����
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_cDat, i_iSz);								// ������
	ist = 0;

#if( TRACE_IO)
	int		iCh = i_iSz / sizeof( char);
	TRACE( " Write Char [%d]:\tTp = %d,\t������ = %d", iCwr_IO++, i_iTp, iCh);
	TRACE( ",\t%s\n", i_cDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z����(_TCHAR)�^�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemCH(
				const	MINT		i_iTp,		// �^�C�v
				const	_TCHAR*		i_cDat,		// �����ݕ�����
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_cDat, i_iSz);								// ������
	ist = 0;

#if( TRACE_IO)
	int		iNcDat = i_iSz / sizeof( _TCHAR);
	TRACE( " Write TChar [%d]:\tTp = %d,\t������ = %d", iCwr_IO++, i_iTp, iNcDat);
	TRACE( ",\t%s\n", i_cDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z����(CString)�f�[�^�̃t�@�C����������
//�y�Ԓl�z==  0 : ����I��
//		  ��  0 : ���̑��G���[

MINT MhMdlIO::WriteItemCS(
				const	MINT		i_iTp,		// �^�C�v
				const	CString*	i_sDat,		// �����ݕ�����
				const	MINT		i_iSz		// �����݃o�C�g��
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// �^�C�v
	m_File.Write( &i_iSz, SZMINT());							// �T�C�Y
	m_File.Write( i_sDat, i_iSz);								// ������
	ist = 0;

#if( TRACE_IO)
	int		iNsDat = i_iSz / sizeof( char);
	TRACE( " Write CString [%d]:\tTp = %d,\t������ = %d", iCwr_IO++, i_iTp, iNsDat);
	TRACE( ",\t%s\n", i_sDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//	�t�@�C���_�C�A���O��\�����t���p�X���擾����
//	[�Ԓl] �X�e�C�^�X     0 : �L�����Z��  1 : �n�j

MINT IeModel::MhFileDialog(						//
				const	MINT		i_fRead,	// �ǂݎ��t���O		true:�J��	false:�ۑ�
				const	MCHAR*		i_sPath,	// �w��t�@�C�����i�t���p�X�j
						MCHAR*		o_sPath,	// �I���t�@�C�����i�t���p�X�j
						int			i_nPath		// �I���t�@�C�����i�t���p�X�j�ő啶����
				)
{
	MINT			ist;
	CFileDialog*	DlgFile = NULL;
	MCHAR			cFldPath[MAX_PATH];
	MCHAR			cFileName[MAX_PATH];
	MCHAR*			pcFileName = NULL;

	ist = 0;

	Mstrcpy_s( o_sPath, i_nPath, Mstr( ""));

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING;

	if ( i_sPath) {																		// �w��t�@�C��������
		IeModel::MhSeparateFname( i_sPath, cFldPath, MAX_PATH, cFileName, MAX_PATH);
		pcFileName = cFileName;
	}

	CFileDialog FDlg( i_fRead,  Mstr( "mdk"), pcFileName, dwFlags,
						 	    Mstr( "�\���ƃ��f���t�@�C��(*.mdk)|*.mdk|�S�t�@�C��(*.*)|*.*||"), NULL);
	if ( i_sPath)
		FDlg.m_ofn.lpstrInitialDir = cFldPath;

	if ( FDlg.DoModal() == IDOK) {														// �_�C�A���O��\������
		Mstrcpy_s( o_sPath, i_nPath, FDlg.GetPathName());
		ist = 1;
	}
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//	�t���p�X������A�t�H���_�[�p�X���A�t�@�C�����A�t�@�C���^�C�g���A
//					�t�@�C���g���q���擾����
void IeModel::MhSeparateFname(
				const	MCHAR*	i_sFullPath,	// �t�@�C���t���p�X��
						MCHAR*	o_sFolderPath,	// �t�H���_�[�p�X��	�܂��́@NULL
						int		i_nFolderPath,	// �t�H���_�[�p�X���ő啶����
						MCHAR*	o_sFileName,	// �t�@�C����			�܂��́@NULL
						int		i_nFileName,	// �t�@�C����			�܂��́@NULL
						MCHAR*	o_sFileTitle,	// �t�@�C���^�C�g��	�܂��́@NULL
						int		i_nFileTitle,	// �t�@�C���^�C�g��	�܂��́@NULL
						MCHAR*	o_sFileExt,		// �t�@�C���g���q		�܂��́@NULL
						int		i_nFileExt		// �t�@�C���g���q		�܂��́@NULL
				)
{
	MINT		ist = 0;
	MINT		ic;
	MINT		szFullPath;
	MINT		szPath;
	MINT		szName;
	MINT		szTitle;

	szFullPath = (MINT)Mstrlen( i_sFullPath);
	for ( ic=szFullPath-1; ic>=0; ic--) {
		if ( i_sFullPath[ic] == Mchar('\\'))
			break;
	}
	szPath = ic;
	if ( o_sFolderPath) {
		if ( szPath > 1) {
			Mstrncpy_s( o_sFolderPath, i_nFolderPath, i_sFullPath, szPath);
			o_sFolderPath[szPath] = NULL;
		} else {
			Mstrcpy_s( o_sFolderPath, i_nFolderPath, Mstr( ".\\"));
		}
	}
	if ( o_sFileName)
		Mstrcpy_s( o_sFileName, i_nFileName, &i_sFullPath[szPath+1]);
	
	szName = szFullPath - szPath - 1;
	if ( o_sFileTitle || o_sFileExt) {
		for ( ic=szName-1; ic>=0; ic--) {
			if ( o_sFileName[ic] == Mchar('.'))
				break;
		}
		szTitle = ic;
		if ( o_sFileTitle) {
			if ( szTitle < 0) {
				Mstrcpy_s( o_sFileTitle, i_nFileTitle, o_sFileName);
			} else {
				if ( szTitle)
					Mstrncpy_s( o_sFileTitle, i_nFileTitle, o_sFileName, szTitle);
				o_sFileTitle[szTitle] = NULL;
			}
		}
		if ( o_sFileExt) {
			if ( szTitle < 0) {
				o_sFileExt[0] = NULL;
			} else {
                Mstrcpy_s( o_sFileExt, i_nFileExt, &o_sFileName[szTitle+1]);
			}
		}
	}
}

} // namespace MC
