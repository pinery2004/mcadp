#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsDefConst.h
//
//		基本　定数・関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

//===========================================================================
//		数値演算定数
//
#define		MC_E				2.71828182845904523536		// e
#define		MC_LOG2E			1.44269504088896340736		// log2( e)
#define		MC_LOG10E			0.434294481903251827651		// log10( e)
#define		MC_LN2				0.693147180559945309417		// ln( 2)
#define		MC_LN10				2.30258509299404568402		// ln( 10)

#define		MC_2PIE				6.28318530717958647692		// 2*円周率
#define		MC_PIE				3.14159265358979323846		// 円周率
#define		MC_PIE_2			1.57079632679489661923		// 円周率/2
#define		MC_PIE_4			0.785398163397448309616		// 円周率/4
#define		MC_1_PIE			0.318309886183790671538		// 1/円周率
#define		MC_2_PIE			0.636619772367581343076		// 2/円周率

#define		MC_DTR				0.0174532925199433f			// 円周率/180
#define		MC_RTD				57.2957795130824f			// 180/円周率
#define		MC_INCHES_TO_MM		25.4f;

#define		MC_SQRTPIE			1.77245385090551602729f		// sqrt( 円周率)
#define		MC_2_SQRTPIE		1.12837916709551257390f		// 2/sqrt( 円周率)
#define		MC_SQRT2			1.41421356237309504880f		// sqrt( 2)
#define		MC_SQRT1_2			0.707106781186547524401f	// 1/sqrt( 2)

//===========================================================================
//		テキスト 作業領域サイズ
//
#define		MX_PATH				MAX_PATH		// パス文字列　最大文字数 260

#define		MC_MCADBUF			512				// max mcad buffer for getstring & tile
//#define	MC_MCADNMLEN		256				// number of MCHAR in MCAD name
//#define	MC_SLBHEADER		32L				// length of slide library header
//#define	MC_SLBDIRHEAD		36L				// length of slide library directory
#define		MC_XDLIMIT			16384			// max length of total eed


