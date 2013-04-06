#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhIeModel.h
//
//		家モデル
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

#include	"MhDefParts.h"
#include	"MsBitSet.h"

#define		MMAX_KAI			3									// 最大階数
#define		MMAX_KUMI			10									// 最大組数
#define		MMAX_PARTSSPEC		300									// 最大部品仕様数
#define		MMAX_PARTSMEMBER	400									// 最大寸法型式数

#define		MMAX_BZILEN		30000.									// 最大部材長さ30m
#define		MMIN_BZILEN		1.										// 最小部材長さ
#define		MMIN_BZILEN_2	(MMIN_BZILEN * MMIN_BZILEN)				// 最小部材長さ * 最小部材長さ


