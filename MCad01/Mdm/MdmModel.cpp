//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.cpp
//
//		モデルデータベース
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"

#define DLL_EXPORT_MDMODEL_DO
#include "MdModel.h"
#include "MdmDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

MdModel::MdModel( void)
{
	m_GrpBf.Alloc( 20);
	m_ScmBf.Alloc( 50);
	m_BriBf.Alloc( 20);
	m_LyrBf.Alloc( 50);
	m_EntBf.Alloc( 500);
	m_PartsBf.Alloc( 50);
	m_WinBf.Alloc( 10);

	m_MBaseTrans.SetUnit();
	
	//m_idGrp = new MDID[1000];
	//m_idScm = new MDID[1000];
	//m_idLyr = new MDID[3000];

	m_idCurGrp = -1;							// カレントグループID
	m_idCurWin = -1;							// カレントウィンドウID
	m_itpCurWin = -1;							// カレントウィンドウタイプ ( 0:３Ｄ、1：図面)
	m_idCurLyr = -1;							// カレントレイヤーID
	m_idCurScm = -1;							// カレントスキーマID

	for ( int iC=0; iC<28; iC++)
		m_mdTenkai[iC] = 0;
	for ( int iC=0; iC<7; iC++)
		m_rmdTenkai[iC] = 0;

}

MdModel::~MdModel( void)
{
	m_GrpBf.Free();
	m_ScmBf.Free();
	m_BriBf.Free();
	m_LyrBf.Free();
	m_EntBf.Free();
	m_PartsBf.Free();
	m_WinBf.Free();
}

//	トレース
void MdModel::Print( MCHAR* s)
{
	MBLOGPRINTS( s);
	mlLog::Print( Mstr( "◇家モデル	"));
	m_GrpBf.Print( Mstr( "◇グループセット	"), MDC_NONE_ID);
	m_ScmBf.Print( Mstr( "◇スキーマセット	"), MDC_NONE_ID);
	m_LyrBf.Print( Mstr( "◇レイヤーセット	"), MDC_NONE_ID);
	m_BriBf.Print( Mstr( "◇分類セット		"), MDC_NONE_ID);
	m_EntBf.Print( Mstr( "◇エンティティセット"), MDC_NONE_ID);
	m_PartsBf.Print( Mstr( "◇部品セット		"), MDC_NONE_ID);
	m_WinBf.Print( Mstr( "◇ウィンドウセット	"), MDC_NONE_ID);

	MBLOGPRINTS( Mstr( "◇カレント"));
	MBLOGPRINTI( Mstr( "	カレントグループID		"), m_idCurGrp);
	MBLOGPRINTI( Mstr( "	カレントウィンドウID	"), m_idCurWin);
	MBLOGPRINTI( Mstr( "	カレントウィンドウタイプ ( 0:３Ｄ、1：図面)"), m_itpCurWin);
	MBLOGPRINTI( Mstr( "	カレントレイヤーID		"), m_idCurLyr);
	MBLOGPRINTI( Mstr( "	カレントスキーマID		"), m_idCurScm);
	MBLOGPRINTIN( Mstr( "	ポリゴン展開処理モード	"), m_mdTenkai, 28);
	MBLOGPRINTFN( Mstr( "	ポリゴン展開処理パラメータ"), m_rmdTenkai, 7);
}


} // namesace MC
