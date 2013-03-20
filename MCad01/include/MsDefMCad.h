#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsMCadDefine.h
//
//		基本　システム構成　定数・関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================
// windowの表示形態
//
#define	TAB_WINDOW		false					// タブ型式のウィンドウ表示

//===========================================================================
//		マップ モード
//
#define		MMAPMODE			MM_TWIPS		// 1/20ポイント
//
//#define	MMAPMODE			MM_HIMETRIC		// 0.01mm
//#define	MMAPMODE			MM_TWIPS		// 1/20ポイント
//#define	MMAPMODE			MM_TEXT

// Y座標の向き		1:上向き	-1:下向き
#if( MMAPMODE == MM_TEXT)
	#define		MMDIRY			-1.
#else
	#define		MMDIRY			1.
#endif

