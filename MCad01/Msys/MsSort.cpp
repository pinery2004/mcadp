//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsLib.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MsLib.h"

namespace MC
{

static MINT			z_CmpWidth;									// �f�t�H���g�̔z��̗v�f�T�C�Y
static MAryCmpFunc	AryCompare;									// �f�t�H���g�̔�r�֐�

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�N�C�b�N�\�[�g

void MsQSort(													// (  O) �ð��
			void*			base,								// (I  ) ���ёւ���z��̐擪
			MINT			num,								// (I  ) �z��̗v�f��
			MINT			width,								// (I  ) �z��̗v�f�T�C�Y(�o�C�g��)
			MAryCmpFunc*	AryCmpFunc							// (I  ) ��r�֐�
			)
{
	z_CmpWidth = width;
	if ( AryCmpFunc == NULL)  AryCmpFunc = AryCompare;			// �f�t�H���g�̔�r�֐���ݒ�
	qsort( base, num, width, AryCmpFunc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�f�t�H���g�̔�r�֐�
//�y�Ԓl�z < 0 : array1  < array2
//		  == 0 : array1 == array2
//		   > 0 : array1  > array2 

static MINT AryCompare(											// (  O) �ð��
			const void*		array1,								// (I  ) �ް�1
			const void*		array2								// (I  ) �ް�2
			)
{
	return memcmp(array1, array2, z_CmpWidth);
}

} // namespace MC