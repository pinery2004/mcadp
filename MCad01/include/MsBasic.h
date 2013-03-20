#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsBasic.h
//
//		基本　定数・関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================
//#ifndef WINVER				// Windows XP 以降のバージョンに固有の機能の使用を許可します。
//#define WINVER 0x0501		// これを Windows の他のバージョン向けに適切な値に変更してください。
//#endif
//
//#pragma warning( disable : 4996 )
//
//#include <afxwin.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//===========================================================================
//	システム設定

#include	"MsDefMCad.h"
#include	"MsDefConst.h"
#include	"MsDefType.h"
#include	"MsDefFunc.h"
#include	"MsDefArea.h"
#include	"MsDefCheck.h"
#include	"msCode.h"

//===========================================================================
//		全オブジェクトのベース
//
class 		MOBJECT				{};				// 全オブジェクトのベース

//===========================================================================
//		abstract iteration position
//
class 		__MPOSITION 		{};
//typedef 	__MPOSITION* 		MPOSITION;
#define		MPOSITION		 	__MPOSITION*

union PZBUF {
	long	lgDt[400];
	int		iDt[200];
	float	fDt[200];
	double	dbDt[200];
};
extern PZBUF* ____pzbuf;
