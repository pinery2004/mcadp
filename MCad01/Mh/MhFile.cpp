//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhFile.cpp
//
//		構造家モデル読み書きＩＯ処理
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
//【機能】構造家モデル

////////////////////////////////////////////////////////////////////////////
//【機能】コンストラクタ

MhMdlIO::MhMdlIO()
{
	memset( &m_Header, 0, sizeof(MhMdlHeader));
	Mstrcpy_s( m_Header.cTitle, z_cTitle);
	Mstrcpy_s( m_Header.cVer, z_cVer);
	m_Header.cTime = ms::GetCurrentTime();						// 作成日時 
}

////////////////////////////////////////////////////////////////////////////
//【機能】デストラクタ
MhMdlIO::~MhMdlIO          ()
{
}

////////////////////////////////////////////////////////////////////////////
//【機能】ファイル読み書き処理開始宣言
//【返値】==  0 : 正常終了
//		  == -2 : 既にオープンされている
//		  ≦ -3 : その他エラー

MINT MhMdlIO::Open(
				const	DWORD		iMode,		// (I ) 使用モード
												//		== MBREAD:	読み込み専用
												//		== MBWRITE:	書き込み専用
				const	MCHAR*		cFilePath
				)
{
	MINT		ist = -1;
	MINT		OutSiz;
	MUINT		nOpenFlag;										// アクセスモード

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
//【機能】ファイル読み書き処理終了宣言
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

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
//【機能】ファイル読み込み
//【返値】 > 0 : 読み込みバイト数
//		  == 0 : 終了
//		   < 0 : その他エラー

MINT MhMdlIO::ReadItem(
						MINT*		o_piTp,		// (  O) ﾀｲﾌﾟ
						void**		o_Buf		// (  O) 読込み領域
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
		MQUIT;													// 終了

	//int* pTest = new int[2];
//===
#if( TRACE_IO)
	TRACE( "%d-%d: new char[%d]\n", iCht2_IO, iCnw_IO++, iSizeR);
#endif
//---
	*o_Buf = (byte *)new char[iSizeR];
	ASSERT( *o_Buf);											// メモリ　りアロックエラー　<ERROR>
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
//【機能】任意型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItems(
				const	MINT		i_iTp,		// ﾀｲﾌﾟ
				const	void*		i_Bf,		// 書込み領域
				const	MINT		i_iSz		// 書込みﾊﾞｲﾄ数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_Bf, i_iSz);									// 任意型データ
	ist = 0;
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//【機能】SHORT型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemIS(
				const	MINT		i_iTp,		// タイプ
				const	MSHORT*		i_iBf,		// 書込みSHORT配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_iBf, i_iSz);								// 整数配列
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
//【機能】整数型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemI(
				const	MINT		i_iTp,		// タイプ
				const	MINT*		i_iBf,		// 書込み整数配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_iBf, i_iSz);								// 整数配列
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
//【機能】整数型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemUI(
				const	MINT		i_iTp,		// タイプ
				const	MUINT*		i_iBf,		// 書込み整数配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_iBf, i_iSz);								// 整数配列
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
//【機能】FLOAT型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemR(
				const	MINT		i_iTp,		// タイプ
				const	float*		i_rBf,		// 書込み実数配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_rBf, i_iSz);								// 実数(float)配列
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
//【機能】DOUBLE型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemR(
				const	MINT		i_iTp,		// タイプ
				const	double*		i_rBf,		// 書込み実数配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_rBf, i_iSz);								// 実数(double)配列
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
//【機能】BYTE型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemIB(
				const	MINT		i_iTp,		// タイプ
				const	MUBYTE*		i_ibBf,		// 書込みBYTE配列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_ibBf, i_iSz);								// BYTE配列
	ist = 0;
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//【機能】文字(char)型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemCH(
				const	MINT		i_iTp,		// タイプ
				const	char*		i_cDat,		// 書込み文字列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_cDat, i_iSz);								// 文字列
	ist = 0;

#if( TRACE_IO)
	int		iCh = i_iSz / sizeof( char);
	TRACE( " Write Char [%d]:\tTp = %d,\t文字数 = %d", iCwr_IO++, i_iTp, iCh);
	TRACE( ",\t%s\n", i_cDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//【機能】文字(_TCHAR)型データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemCH(
				const	MINT		i_iTp,		// タイプ
				const	_TCHAR*		i_cDat,		// 書込み文字列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_cDat, i_iSz);								// 文字列
	ist = 0;

#if( TRACE_IO)
	int		iNcDat = i_iSz / sizeof( _TCHAR);
	TRACE( " Write TChar [%d]:\tTp = %d,\t文字数 = %d", iCwr_IO++, i_iTp, iNcDat);
	TRACE( ",\t%s\n", i_cDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//【機能】文字(CString)データのファイル書き込み
//【返値】==  0 : 正常終了
//		  ≠  0 : その他エラー

MINT MhMdlIO::WriteItemCS(
				const	MINT		i_iTp,		// タイプ
				const	CString*	i_sDat,		// 書込み文字列
				const	MINT		i_iSz		// 書込みバイト数
				)
{
	MINT		ist;
	ist = -1;
	m_File.Write( &i_iTp, SZMINT());							// タイプ
	m_File.Write( &i_iSz, SZMINT());							// サイズ
	m_File.Write( i_sDat, i_iSz);								// 文字列
	ist = 0;

#if( TRACE_IO)
	int		iNsDat = i_iSz / sizeof( char);
	TRACE( " Write CString [%d]:\tTp = %d,\t文字数 = %d", iCwr_IO++, i_iTp, iNsDat);
	TRACE( ",\t%s\n", i_sDat);
#endif

	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//	ファイルダイアログを表示しフルパスを取得する
//	[返値] ステイタス     0 : キャンセル  1 : ＯＫ

MINT IeModel::MhFileDialog(						//
				const	MINT		i_fRead,	// 読み取りフラグ		true:開く	false:保存
				const	MCHAR*		i_sPath,	// 指定ファイル名（フルパス）
						MCHAR*		o_sPath,	// 選択ファイル名（フルパス）
						int			i_nPath		// 選択ファイル名（フルパス）最大文字数
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

	if ( i_sPath) {																		// 指定ファイル名あり
		IeModel::MhSeparateFname( i_sPath, cFldPath, MAX_PATH, cFileName, MAX_PATH);
		pcFileName = cFileName;
	}

	CFileDialog FDlg( i_fRead,  Mstr( "mdk"), pcFileName, dwFlags,
						 	    Mstr( "構造家モデルファイル(*.mdk)|*.mdk|全ファイル(*.*)|*.*||"), NULL);
	if ( i_sPath)
		FDlg.m_ofn.lpstrInitialDir = cFldPath;

	if ( FDlg.DoModal() == IDOK) {														// ダイアログを表示する
		Mstrcpy_s( o_sPath, i_nPath, FDlg.GetPathName());
		ist = 1;
	}
	return( ist);
}

////////////////////////////////////////////////////////////////////////////
//	フルパス名から、フォルダーパス名、ファイル名、ファイルタイトル、
//					ファイル拡張子を取得する
void IeModel::MhSeparateFname(
				const	MCHAR*	i_sFullPath,	// ファイルフルパス名
						MCHAR*	o_sFolderPath,	// フォルダーパス名	または　NULL
						int		i_nFolderPath,	// フォルダーパス名最大文字数
						MCHAR*	o_sFileName,	// ファイル名			または　NULL
						int		i_nFileName,	// ファイル名			または　NULL
						MCHAR*	o_sFileTitle,	// ファイルタイトル	または　NULL
						int		i_nFileTitle,	// ファイルタイトル	または　NULL
						MCHAR*	o_sFileExt,		// ファイル拡張子		または　NULL
						int		i_nFileExt		// ファイル拡張子		または　NULL
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
