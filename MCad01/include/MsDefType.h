#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsDefineType.h
//
//		��{�@�萔�E�֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

//===========================================================================
// �����̐��x	�{���x�����Ŏ�舵���ꍇ�́AMG_DOUBLE_PRECISION_REAL���`
//
// #define		MG_DOUBLE_PRECISION_REAL

//===========================================================================
//		�^�̒�`
//
typedef		_TCHAR				MCHAR;			// �����^
typedef		char				MBYTE;			// 1/4�ꐮ���^
typedef		short				MSHORT;			// 1/2�ꐮ���^
typedef		int					MINT;			// 32�r�b�g�����^
typedef		long				MLONG;			// 32�r�b�g�����^
typedef		__int64				MLONGLONG;		// 64�r�b�g�����^
typedef		float				MFLOAT;			// �P���x�����^
typedef		double				MDOUBLE;		// �{���x�����^

#ifdef MG_DOUBLE_PRECISION_REAL
	typedef		double				MREAL;			// �P���x�����^
#else
	typedef		float				MREAL;			// �{���x�����^
#endif

typedef		_TUCHAR				MUCHAR;			// �����Ȃ������^
typedef		unsigned char		MUBYTE;			// �����Ȃ�1/4�ꐮ���^
typedef		unsigned short		MUSHORT;		// �����Ȃ�1/2�ꐮ���^
typedef		unsigned int		MUINT;			// �����Ȃ�32�r�b�g�����^
typedef		unsigned long		MULONG;			// �����Ȃ�32�r�b�g�����^
typedef		unsigned __int64	MULONGLONG;		// �����Ȃ�64�r�b�g�����^

typedef		void				MVOID;			// VOID�^
typedef		void*				MHANDLE;		// HANDLE�^

typedef	 enum _mbool {							// �_���^
			MFALSE = 0,							// �U
			MTRUE  = 1							// �^
		} 						MBOOL;

typedef		MINT				MDID;			// ID	

typedef 	long 				MRC;			// ���^�[���R�[�h

//typedef	time_t				MTIME;			// ���Ԋl���p�ϐ��^
#define		MTIME				CTime			// ���Ԋl���p�ϐ��^

#define		MCONST				const			// �萔�^

//===========================================================================
//		�f�[�^�^�萔�́A�����f�[�^�^�Ɏg�p�ł���l�͈̔�
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

// �T�C�Y
inline MINT SZMINT( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MINT));}
inline MINT SZMREAL( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MREAL));}
inline MINT SZMFLOAT( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MFLOAT));}
inline MINT SZMDOUBLE( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MDOUBLE));}

