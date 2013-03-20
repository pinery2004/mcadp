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
						char*	StrC,			// ( I  ) MBCS������
						MCHAR*	StrU,			// (  O) UNICODE������
						MINT	iSize			// ( I  ) �ő啶����
						);

	//===========================================================================
	// UNICODE�������MBCS������ɕϊ�����
	//�y�Ԓl�z 0 : ����     -1 : �ُ�
	//===========================================================================

	static MINT mswcstombs( 
						MCHAR*	StrU,			// ( I  ) UNICODE������
						char*	StrC,			// (  O) MBCS������
						MINT	iSize			// ( I  ) �ő啶����
						);

	//===========================================================================
	// ��������������ɕϊ�
	//===========================================================================
	static void msstrtolower(
							MCHAR	in_pstr[],		// �ϊ��O�̕�����
							MCHAR	out_pstrL[],	// �ϊ���̕�����o�b�t�@
							size_t	in_SzstrL)		// ������o�b�t�@�T�C�Y
	{
		MCHAR*	pstr;
		MCHAR*	pstrL;
		size_t	available;

		pstr = in_pstr;
		pstrL = out_pstrL;
		available = in_SzstrL;
		while( *pstr != 0 && --available) {
			*pstrL++ = Mtolower( *pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR( __FUNCTION__);
		}
		*pstrL = 0;
	}

	//===========================================================================
	// �������啶���ɕϊ�
	//===========================================================================
	static void msstrtoupper(
							MCHAR	in_pstr[],		// �ϊ��O�̕�����
							MCHAR	out_pstrU[],	// �ϊ���̕�����o�b�t�@
							MINT	in_SzstrU)		// �ő啶����(�o�b�t�@�T�C�Y - 1)
	{
		MCHAR*	pstr;
		MCHAR*	pstrU;
		size_t	available;

		pstr = in_pstr;
		pstrU = out_pstrU;
		available = in_SzstrU;
		while( *pstr != 0 && --available) {
			*pstrU++ = Mtoupper( *pstr++);
		}
		if ( available == 0) {
			RETURN_OVERFLOW_ERR( __FUNCTION__);
		}
		*pstrU = 0;
	}

};

} // namespace MC

