//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsBasic.cpp
//
//		��{�I�Ȋ֐��̏W�܂�
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"

#define	DLL_EXPORT_BASE_DO
#include "MsBasic.h"

#include <memory.h>
#include <locale.h>

namespace MC
{

//===========================================================================
//	���{�ꃂ�[�h�ɐݒ肷��
//
void 	ms::SetJapanese( )
{
//	setlocale( LC_ALL, "ja");			// �G���[�ɂȂ��Ă���悤�����G���[�\������

//	setlocale( LC_ALL, ".ACP" );		// �ݒ�ɂ��킹��@( ���{���fwprintf���\�ɂȂ�)

	setlocale( LC_ALL, "jpn" );			// ���{���fwprintf���\�ɂ���
}

} // namespace MC
