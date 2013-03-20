#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsDefineType.h
//
//		基本　定数・関数
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

//===========================================================================
// 実数の精度	倍精度実数で取り扱う場合は、MG_DOUBLE_PRECISION_REALを定義
//
// #define		MG_DOUBLE_PRECISION_REAL

//===========================================================================
//		型の定義
//
typedef		_TCHAR				MCHAR;			// 文字型
typedef		char				MBYTE;			// 1/4語整数型
typedef		short				MSHORT;			// 1/2語整数型
typedef		int					MINT;			// 32ビット整数型
typedef		long				MLONG;			// 32ビット整数型
typedef		__int64				MLONGLONG;		// 64ビット整数型
typedef		float				MFLOAT;			// 単精度実数型
typedef		double				MDOUBLE;		// 倍精度実数型

#ifdef MG_DOUBLE_PRECISION_REAL
	typedef		double				MREAL;			// 単精度実数型
#else
	typedef		float				MREAL;			// 倍精度実数型
#endif

typedef		_TUCHAR				MUCHAR;			// 符号なし文字型
typedef		unsigned char		MUBYTE;			// 符号なし1/4語整数型
typedef		unsigned short		MUSHORT;		// 符号なし1/2語整数型
typedef		unsigned int		MUINT;			// 符号なし32ビット整数型
typedef		unsigned long		MULONG;			// 符号なし32ビット整数型
typedef		unsigned __int64	MULONGLONG;		// 符号なし64ビット整数型

typedef		void				MVOID;			// VOID型
typedef		void*				MHANDLE;		// HANDLE型

typedef	 enum _mbool {							// 論理型
			MFALSE = 0,							// 偽
			MTRUE  = 1							// 真
		} 						MBOOL;

typedef		MINT				MDID;			// ID	

typedef 	long 				MRC;			// リターンコード

//typedef	time_t				MTIME;			// 時間獲得用変数型
#define		MTIME				CTime			// 時間獲得用変数型

#define		MCONST				const			// 定数型

//===========================================================================
//		データ型定数は、整数データ型に使用できる値の範囲
//
#define		MCHARMAX			CHAR_MAX		// 127
#define		MCHARMIN			CHAR_MIN		// -128
#define		MUCHARMAX			UCHAR_MAX		// 255		( 0xff)
#define		MUSHORTMAX			USHRT_MAX		// 65535	( 0xffff)
#define		MSHORTMAX			SHRT_MAX		// 32767
#define		MSHORTMIN			SHRT_MIN		// -32768
#define		MUINTMAX			UINT_MAX		// 4294967295	( 0xffffffff)
#define		MINTMAX				INT_MAX			// 2147483647
#define		MINTMIN				INT_MIN			// -2147483647-1
#define		MLONGLONGMAX		I64_MAX			// 9223372036854775807
#define		MLONGLONGMIN		I64_MIN			// -9223372036854775807-1
#define		MULONGLONGMAX		_UI64_MAX		// ( 0xffffffffffffffff)
//		 ( from FLOAT.H)
#define		MDOUBLEMAX			DBL_MAX			// 1.7976931348623158e+308
#define		MDOUBLEMIN			DBL_MIN			// 2.2250738585072014e-308
#define		MFLOATMAX			FLT_MAX			// 3.402823466e+38F
#define		MFLOATMIN			FLT_MIN			// 1.175494351e-38F

#ifdef MG_DOUBLE_PRECISION_REAL
	#define		MREALMAX			DBL_MAX			// 1.7976931348623158e+308
	#define		MREALMIN			DBL_MIN			// 2.2250738585072014e-308
#else
	#define		MREALMAX			FLT_MAX			// 3.402823466e+38F
	#define		MREALMIN			FLT_MIN			// 1.175494351e-38F
#endif

// サイズ
inline MINT SZMINT( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MINT));}
inline MINT SZMREAL( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MREAL));}
inline MINT SZMFLOAT( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MFLOAT));}
inline MINT SZMDOUBLE( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MDOUBLE));}

