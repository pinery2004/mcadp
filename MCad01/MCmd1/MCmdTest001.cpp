//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdSekkei.cpp
//
//		
//
//
//  K.Matsu           09/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"

#include "MgPoint.h"

#include "MdModel.h"
#include "MdmDB.h"
#include "MdmEnt.h"
#include "Mdm.h"
#include "MdmSet.h"
#include "MdZukei.h"
#include "MdmFig.h"
#include "MsLib.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	Geoテスト
//
void BrkPoint()
{
	_asm int 3;
}
void Test000_Geo()
{
	MgVect2 v22 = MgVect2( 1., 2.);
	MgVect2 v23 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.Print( Mstr("v23"));
	v22 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.SetRotR90();
	v23.Print( Mstr("v23"));
	MgVect2 v24;
	v24 = v22.Rot( MgVect2( 1., 1.).Unitize());
	v24.Print( Mstr("v24(v22.Rot(1.,1.))"));
	v22.SetRot( (MREAL)MC_PIE/4);
	v22.Print( Mstr("v22.SetRot(MC_PIE/4)"));

	MgPoint2 pt22 = MgPoint2( 1., 2.);
	MgPoint2 pt23 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.Print( Mstr("pt23"));
	pt22 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.SetRotR90();
	pt23.Print( Mstr("pt23"));
	MgPoint2 pt24;
	pt24 = pt22.Rot( (MREAL)MC_PIE/4);
	pt24.Print( Mstr("pt24(pt22.Rot(MC_PIE/4))"));
	pt22.SetRot( (MREAL)MC_PIE/4);
	pt22.Print( Mstr("pt22.SetRot(MC_PIE/4)"));

	MgVect3 v32 = MgVect3( 1., 2., 3.);
	MgVect3 v33 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.Print( Mstr("v33"));
	v32 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.SetRotR90();
	v33.Print( Mstr("v33"));
	MgVect3 v34;
	v34 = v32.Rot( MgVect2( 1., 1.).Unitize());
	v34.Print( Mstr("v34(v32.Rot(1.,1.))"));
	v32.SetRot( (MREAL)MC_PIE/4);
	v32.Print( Mstr("v22.SetRot(MC_PIE/4)"));

	MgPoint3 pt32 = MgPoint3( 1., 2., 3.);
	MgPoint3 pt33 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.Print( Mstr("pt33"));
	pt32 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.SetRotR90();
	pt33.Print( Mstr("pt33"));
	MgPoint3 pt34;
	pt34 = pt32.Rot( (MREAL)MC_PIE/4);
	pt34.Print( Mstr("pt34(pt32.Rot(MC_PIE/4))"));
	pt32.SetRot( (MREAL)MC_PIE/4);
	pt32.Print( Mstr("pt32.SetRot(MC_PIE/4)"));
	AfxDebugBreak( );
	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	ファイル・フォルダ選択テスト
//
void Test001_SelectFile()
{
	MCHAR FilePathI[] = Mstr( "D:\\temp\\*.txt");
	MCHAR FilePathO[MAX_PATH];

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd* pWnd = pWndInfo->m_pWnd;

	HWND hWnd;
	if ( pWnd != NULL ) hWnd = pWnd->GetSafeHwnd();
	else hWnd = NULL;

	//	読み込み用ファイル選択ダイアログを表示する
	//
	MsLoadFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);

	pWnd->MessageBox( FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);
	MessageBox( hWnd, FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);

	//	保存用ファイル選択ダイアログを表示する
	//
	MsSaveFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);
	MessageBox( hWnd, FilePathO, Mstr( "Save File Name"), MB_OK | MB_TOPMOST);


	//	フォルダ選択ダイアログを表示する
	//
	MCHAR FolderPath[MAX_PATH] = Mstr( "D:\\Temp");
	MsForFolderDlg( hWnd, Mstr( "テスト用フォルダの選択"), Mstr( "D:\\Temp"), FolderPath, MAX_PATH);
	MessageBox( hWnd, FolderPath, Mstr( "Folder Name"), MB_OK | MB_TOPMOST);
	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールグループ生成テスト
//
void Test002_DBModule()
{
	MINT	iSt;

	MDID	idGrp[5];							// グループId
	MINT	isz = 20;							// 初期グループIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 201., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 202., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));
	iSt = DGrp::DeleteGrp( idGrp[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ３"), 3000., 203., &idGrp[2], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ３"));
	//iSt = DGrp::CreateGrp( Mstr( "グループ４"), 3000., 250., &idGrp[3], isz);
	//pIeModel->Print( Mstr( "●家モデル　グループ４"));
	//iSt = DGrp::DeleteGrp( idGrp[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ３"));
	//iSt = DGrp::DeleteGrp( idGrp[3]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ４"));
	//iSt = DGrp::CreateGrp( Mstr( "グループ５"), 3000., 250., &idGrp[4], isz);
	//pIeModel->Print( Mstr( "●家モデル　グループ５"));
	//iSt = DGrp::DeleteGrp( idGrp[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールスキーマ生成テスト
//
void Test003_DBModule()
{
	MINT	iSt;

	MDID	idScm[5];							// レイヤーId
	MINT	isz = 20;							// 初期レイヤーIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ２"), &idScm[1], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ２"));
	iSt = DGrp::DeleteScm( idScm[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ３"), &idScm[2], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ３"));
	//iSt = DGrp::CreateScm( Mstr( "スキーマ４"), &idScm[3], isz);
	//pIeModel->Print( Mstr( "●家モデル　スキーマ４"));
	//iSt = DGrp::DeleteScm( idScm[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ３"));
	//iSt = DGrp::DeleteScm( idScm[3]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ４"));
	//iSt = DGrp::CreateScm( Mstr( "スキーマ５"), &idScm[4], isz);
	//pIeModel->Print( Mstr( "●家モデル　スキーマ５"));
	//iSt = DGrp::DeleteScm( idScm[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールレイヤー生成テスト
//
void Test004_DBModule()
{
	MINT	iSt;

	MDID	idGrp[2];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[5];							// レイヤーId

	MINT	isz = 20;							// 初期グループIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 204., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 205., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ２"), &idScm[1], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ２"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));
	iSt = DLyr::DeleteLyr( idLyr[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー１"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[0], &idLyr[2], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー３"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[1], &idLyr[3], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー４"));
	iSt = DLyr::DeleteLyr( idLyr[2]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー３"));
	iSt = DLyr::DeleteLyr( idLyr[3]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー４"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[4], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー５"));
	iSt = DLyr::DeleteLyr( idLyr[4]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールエンティティ生成テスト
//
void Test005_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[4];							// レイヤーId

	MDID	idEnt[10];							// エンティティId
	MINT	isz = 20;							// 初期エンティティIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 206., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 207., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[0], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１"));
	iSt = mdmDEnt::CreateEnt( 02, &idEnt[1], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ２"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[0]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ１"));
	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ２"));



	iSt = mdmDEnt::CreateEnt( 02, &idEnt[2], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ３"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[3], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ４"));

	//iSt = mdmDEnt::DeleteEnt( idEnt[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ３"));
	iSt = mdmDEnt::DeleteEnt( idEnt[3]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ４"));
	iSt = mdmDEnt::CreateEnt( 01, &idEnt[4], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ５"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ５"));
}
////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールエンティティ図形生成テスト
//
void Test006_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[4];							// レイヤーId

	MDID	idEnt[20];							// エンティティId
	MINT	isz = 40;							// 初期エンティティIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 208., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 209., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));

	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[0], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[1], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ２"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[2], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ３"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[3], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ４"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[4], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ５"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[5], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ６"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[6], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ７"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[7], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ８"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[8], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ９"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[9], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１０"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[10], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１１"));

	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[11], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１２"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[12], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１３"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[13], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１４"));

	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ２"));


	// 表示モードを設定する
	DLyr::SetLyrDispMode( 1, idLyr[0], 3);
	DLyr::SetLyrDispMode( 1, idLyr[1], 3);

	// エンティティに図形を設定する
	MgPoint3 Pt0( 0., 0., 0.);
	MgPoint3 Pt1( 1000., 0., 0.);
	MgPoint3 Pt2( 1000., 1000., 0.);

	
	//// テクスチャ
	//MINT iP;
	//iP = 0;
	//MDFIG stFig13( 100);
	//stFig13.Push();							// push プリミティブを追加
	//stFig13.SetN( WSZMgPush() + 1);			
	//;
	
	
	// 線分１
	MDFIG stFig1( 10);
	stFig1.Line3( MgLine3( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[0], stFig1); 

	// 線分２
	MDFIG stFig2( 12);
	stFig2.Line3( MgLine3( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[2], stFig2); 

	// ポリゴン
	MgPolyg3 Pg1(10);

	Pg1 += MgPoint3( 0., 0., -1000.);
	Pg1 += MgPoint3( 0., 2000., -1000.);
	Pg1 += MgPoint3( 2000., 2000., -1000.);
	Pg1 += MgPoint3( 2000., 0., -1000.);

	MDFIG stFig3( 20);
	stFig3.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[3], stFig3); 
	
	// 点
	MDFIG stFig4( 10);
	stFig4.Point3( MgPoint3( 1000., 1000., -1000.));
	mdmDEnt::SetFig( idEnt[4], stFig4);

	// 直線
	MDFIG stFig5( 10);
	stFig5.ULine3( MgULine3( MgPoint3( 3000., 3000., -2000.), MgVect3( 1., 0., 0.)));
	mdmDEnt::SetFig( idEnt[5], stFig5);

	// 半直線
	MDFIG stFig6( 10);
	stFig6.HLine3( MgHLine3( MgPoint3( 2000., 2000., -1500.), MgVect3( 0., 1., 0.)));
	mdmDEnt::SetFig( idEnt[6], stFig6);

	// ポリライン
	MgPolyl3 Pl1(10);

	Pl1 += MgPoint3( 0., 0., -2000.);
	Pl1 += MgPoint3( 0., 2000., -2000.);
	Pl1 += MgPoint3( 2000., 2000., -2000.);
	Pl1 += MgPoint3( 2000., 0., -2000.);

	MDFIG stFig7( 20);
	stFig7.Polyl3( Pl1);
	mdmDEnt::SetFig( idEnt[7], stFig7); 

	// 平面
	MDFIG stFig8( 10);
	stFig8.Plane3( MgPlane3( MgVect3( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[8], stFig8);

	// ポリゴン
	MgPolyg3 Pg2(10);

	Pg2 += MgPoint3( 0., 0., -3000.);
	Pg2 += MgPoint3( 0., 2000., -3000.);
	Pg2 += MgPoint3( 2000., 2000., -3000.);
	Pg2 += MgPoint3( 2000., 0., -3000.);

	MDFIG stFig9( 20);
	stFig9.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[9], stFig9); 

	// 円
	MDFIG stFig10( 10);
	stFig10.Cir3( MgCir3( MgPoint3( 5000., 5000., -1000.), MgVect3( 0., 1., 0.), 2000.));
	mdmDEnt::SetFig( idEnt[10], stFig10);

	// 円弧
	MDFIG stFig11( 15);
	stFig11.Arc3( MgArc3( MgPoint3( 2000., 0., -1500.), MgPoint3( 0., 2000., -1500.),
						  MgPoint3( 0., 0., -1500.), MgVect3( 0., 1., 0.), 1500.));
	mdmDEnt::SetFig( idEnt[11], stFig11);

	// 無限平面
	MDFIG stFig12( 10);
	stFig12.IPlane3( MgPlane3( MgVect3( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[12], stFig12);

	//// テクスチャ
	MDFIG stFig13( 100);
	stFig13.zPush();							// push プリミティブを追加

	stFig13.zMarker( 1, 2.);
	stFig13.zPaint( 2, 3, 4);
	stFig13.zLineTp( 5);

	stFig13.zColorRGB( MUQUARTER( 100, 200, 255, 100));			// RGB	{byte} ( 0, r, g, b)
	stFig13.zColorRGB( FLOAT3( 0.3f, 0.4f, 0.5f));				// RGB	{float} ( 1., 1., 1.) (1.)
	stFig13.zColorPlt( 2);										// 色(パレット)
	stFig13.zTransmissivity( 0.7f);								// 透過率 ( 0. ～ 1.)
	stFig13.zLineWd( 0.1f);										// 線幅
	stFig13.zMaterialRGBA( MC_AMBIENT, MUQUARTER( 100, 255, 200, 150));		// RGB	( A{透過率}, R, G, B)
	stFig13.zMaterialRGBA( MC_DIFFUSE, FLOAT3( 1.f, 0.5f, 0.3f), 0.7f);	// A 透過率	( 0. ～ 1.)
	stFig13.zMaterialShininess( 100.0f);						// 鏡面光係数 ( 0. ～ 128.)
	stFig13.zTexture( 5);										// テクスチャＩＤ
//S	MgMat3E mat3( 1., 0., 0., 1.,
//				  0., 1., 0., 1.,
//				  0., 1., 1., 1.,
//				  100., 200., 300., 1.);
	MgMat3E mat3( 1., 0., 0.,
				  0., 1., 0.,
				  0., 0., 1.,
				  100., 200., 300.);
	stFig13.zTextureCoordinate( 0, 1, &MgVect2( 1., 0.), &mat3);// 配置マトリックス
	stFig13.zTextureParam( 1, 1, 2, 3, 4,						// 拡大／縮小フィルタ
		MREAL3( 1., 0.5, 0.3f), MREAL3( 0.2f, 0.3f, 0.4f));		// 境界線色2		
	stFig13.zShininess( 101.);									// 鏡面反射率 ( 0. ～ 1.)
	stFig13.zPovRay( Mstr( "TEST"));							// 文字列


	stFig13.zPull();

	mdmDEnt::SetFig( idEnt[13], stFig13);

	pIeModel->Print( Mstr( "●家モデル　３図形追加"));
}

////////////////////////////////////////////////////////////////////////////
//	テスト用００１
//
void MCmdTest001()
{
	////	ファイル・フォルダ選択テスト
	//Test001_SelectFile();

	//	ＤＢモジュールテスト
	Test000_Geo();
//	Test001_SelectFile();
	Test002_DBModule();
	Test003_DBModule();
	Test004_DBModule();
	Test005_DBModule();
	Test006_DBModule();
}

} // namespace MC
