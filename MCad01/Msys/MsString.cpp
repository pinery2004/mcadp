//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsString.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MsLib.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
//	CString�̕�����������ɕϊ�����
MREAL MsGetMREAL(									// ����
						CString&	in_str			// CString������
				)
{
//	MCHAR	sNum[20];
//	Mstrncpy( sNum, in_str, 20);
//	MREAL	r = Matof( sNum);
	MREAL	r = Matof( in_str);
	return r;
}

///////////////////////////////////////////////////////////////////////////////
//	CString�̕�����𐮐��ɕϊ�����
MINT MsGetMINT(										// ����
						CString&	in_str			// CString������
				)
{
//	MINT	i = atoi( in_str);
//	MCHAR	sNum[20];
//	Mstrncpy( sNum, str, 20);
//	MINT	i = Matoi( sNum);
	MINT	i = Matoi( in_str);
	return i;
}

///////////////////////////////////////////////////////////////////////////////
//	MINT�̐�����CString�ɕϊ�����
CString MsCnvSMINT(									// ����������
						MINT	i_iMode,			// ���[�h�@0: "n"�`���ɕϊ�
						MINT	i_iNum				// ����
				)
{
	CString sKoumoku;
	sKoumoku.Format( Mstr( "%d"), i_iNum);
	return sKoumoku;
}

///////////////////////////////////////////////////////////////////////////////
//	MINT�̎�����CString�ɕϊ�����
CString MsCnvSMREAL(								// ����������
						MINT	i_iMode,			// ���[�h�@1: "0.0"�`���ɕϊ�
						MREAL	i_iReal				// ����
				)
{
	CString sKoumoku;
	sKoumoku.Format( Mstr( "%7.1f"), i_iReal);
	return sKoumoku;
}

///////////////////////////////////////////////////////////////////////////////
// �t�@�C�����̊g���q���`���𓾂�
// �Ԓl: �t�@�C���`�� �g���q�o�b�t�@�̔z��ԍ�    -1: �װ

MINT MsGetFileExtNo(							// �g���q�o�b�t�@�̔z��ԍ� -1:�װ
						MCHAR*	in_cFileName,	// ̧�ٖ�
						MCHAR**	in_ppExt,		// �g���q�o�b�t�@(�� "bmp", "jpg" : 0, 1)
						MINT	in_NExt)		// �g���q��
{
	MINT	iC;
//	MINT	iTp;								// ̧�ق̎��
	MCHAR	cPrd = '.';							// ��ص�ދL��
	MCHAR	cExt[11];							// �t�@�C�����̊g���q
	MCHAR*	pcExt;								// �g���q�̈ʒu�������߲��

	pcExt = Mstrrchr( in_cFileName, cPrd);						// ̧�ٖ��̖�������'.'��T��
	if ( pcExt != NULL) {
		pcExt++;												// �g���q
		Code::msstrtolower( pcExt, cExt, 11);							// �������ɕϊ�
		for ( iC=in_NExt; iC<in_NExt; iC--) {
			if ( Mstrcmp( pcExt, in_ppExt[iC]) == 0)			// �ޯ�ϯ��
				break;
		}
	} else {
		iC = -1;
	}
	return iC;
}

//U
///******************************************************************************************************************
//[ �@�\ ] �������";" ���f���~�^�Ƃ���������
//[ �Ԓl ] �s��      0 : �Ȃ�
//******************************************************************************************************************/
//MINT HsSplitString             (														// (  O) �s��         0:�Ȃ�
//								MCHAR				String[],							// (I  ) ������
//								MCHAR				SLine[][128])						// (  O) �����㕶���� [�s][��]
//{
//	MINT			NumLne;
//	
//	MINT			Num;
//	MINT			QFlg;
//	MINT			ic;
//
//
//	NumLne = 0;																			// �s��
//	Num    = 0;																			// ������
//	QFlg   = 0;																			// " �Ȃ�
//	ic     = 0;
//	while  (String[ic] != NULL && String[ic] != Mchar('\n')) {						// �I���E���s�ȊO
//		if (String[ic] == Mchar('"')) {
//			QFlg = 1 - QFlg;															// ���]
//		} else if (QFlg == 1) {															// �׸�ON
//			SLine[NumLne][Num] = String[ic];
//			if (SLine[NumLne][Num] == Mchar('\t'))  SLine[NumLne][Num] = Mchar(' ');
//			Num++;
//		} else {																		// �׸�OFF
//			if (String[ic] == Mchar(';')) {											// �����
//				SLine[NumLne][Num] = NULL;
//				NumLne++ ; Num = 0;
//			} else {
//				SLine[NumLne][Num] = String[ic];
//				if (SLine[NumLne][Num] == Mchar('\t'))  SLine[NumLne][Num] = Mchar(' ');
//				Num++;
//			}
//		}
//		ic++;
//	}
//	SLine[NumLne][Num] = NULL;
//	NumLne++;
//
//	return(NumLne);
//}
//
// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�zMBCS�������UNICODE������ɕϊ�����
//�y�Ԓl�z 0 : ����     -1 : �ُ�
//�y���Ӂz�Ȃ�
// ********************************************************************************

MINT Mmbstowcs( 
				char*	StrC,					// ( I  ) MBCS������
				MCHAR*	StrU,					// (  O) UNICODE������
				MINT	iSize					// ( I  ) �ő啶����
				)
{

#ifdef _UNICODE
	MINT iLen = ( MINT)strlen( StrC);

	if ( iLen == 0) {
		StrU[0] = NULL;
		return( 0);
	} else {
		MINT iLen1 = MultiByteToWideChar( CP_ACP, 0, ( LPCSTR)StrC,  iLen,  ( LPWSTR)StrU, iSize);
		if ( iLen1 == 0) {
			StrU[0] = NULL;
			return( -1);
		} else {
			StrU[min( iLen1, iSize)] = NULL;
			return( 0);
		}
	}
#else
	Mstrncpy( StrU, StrC, iSize+1);
	return( 0);
#endif
}

// *******************************************************************************
//										Created on 10/01/00 by K.Matsubayashi
//										Updated on xx/xx/xx/ by x.xxxxxx
//										Copyright
//�y�@�\�zUNICODE�������MBCS������ɕϊ�����
//�y�Ԓl�z 0 : ����     -1 : �ُ�
//�y���Ӂz�Ȃ�
// ********************************************************************************

MINT Mwcstombs( 
				MCHAR*	StrU,					// ( I  ) UNICODE������
				char*	StrC,					// (  O) MBCS������
				MINT	iSize					// ( I  ) �ő啶����
				)
{
#ifdef _UNICODE
	MINT iLen = ( MINT)Mstrlen( StrU);
	if ( iLen == 0) {
		StrC[0] = NULL;
		return( 0);
	} else {
		MINT iLen1 = WideCharToMultiByte( CP_ACP, 0, ( LPCWSTR)StrU, iLen, ( LPSTR)StrC, iSize, NULL, NULL);
		if ( iLen1 == 0) {
			StrC[0] = NULL;
			return( -1);
		} else {
			StrC[min( iLen1, iSize)] = NULL;
			return( 0);
		}
	}

#else
	strcpy( StrC, StrU);
	return( 0);
#endif
}

} // namespace MC