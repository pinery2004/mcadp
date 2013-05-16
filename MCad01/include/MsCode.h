#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: msCode.h
//
//		��{�@�����R�[�h�ϊ��֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

#include <Windows.h>

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_CODE_DO
	#pragma message( "<<< Code�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MBASIC_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Code�Edll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class DLL_EXPORT Code
{
public:
	//===========================================================================
	// MBCS�������UNICODE������ɕϊ�����
	//�y�Ԓl�z 0 : ����     -1 : �ُ�
	//===========================================================================

	static MINT msbstowcs( 
						LPCSTR	i_StrC,			// MBCS������
						LPWSTR	o_pStrU,		// UNICODE������
						MINT	i_iSize			// �ő啶����
						);

	//===========================================================================
	// UNICODE�������MBCS������ɕϊ�����
	//�y�Ԓl�z 0 : ����     -1 : �ُ�
	//===========================================================================

	static MINT mswcstombs( 
						LPCWSTR	i_StrU,			// UNICODE������
						LPSTR	o_pStrC,		// MBCS������
						MINT	i_iSize			// �ő啶����
						);

	//===========================================================================
	// ��������������ɕϊ�
	//===========================================================================
	static void msstrtolower(
						LPCWSTR	i_pstr,			// �ϊ��O�̕�����
						LPWSTR	o_pstrL,		// �ϊ���̕�����o�b�t�@
						size_t	i_iSzstrL)		// ������o�b�t�@�T�C�Y
	{
//S		MCHAR*	pstr;
//		MCHAR*	pstrL;
		size_t	available;

//S		pstr = i_pstr;
//		pstrL = o_pstrL;
		available = i_iSzstrL;
		while( *i_pstr != 0 && --available) {
			*o_pstrL++ = Mtolower( *i_pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR();
		}
		*o_pstrL = 0;
	}

	//===========================================================================
	// �������啶���ɕϊ�
	//===========================================================================
	static void msstrtoupper(
						LPCWSTR	i_pstr,		// �ϊ��O�̕�����
						LPWSTR	o_pstrU,	// �ϊ���̕�����o�b�t�@
						MINT	in_SzstrU)		// �ő啶����(�o�b�t�@�T�C�Y - 1)
	{
//S		MCHAR*	pstr;
//		MCHAR*	pstrU;
		size_t	available;

//S		pstr = in_pstr;
//		pstrU = out_pstrU;
		available = in_SzstrU;
		while( *i_pstr != 0 && --available) {
			*o_pstrU++ = Mtoupper( *i_pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR();
		}
		*o_pstrU = 0;
	}

};

} // namespace MC

