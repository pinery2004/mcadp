//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

#include "MmDefine.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"
#include "MdLib.h"

#define  DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"

#include "MdPartsQueue.h"
#include "MhPlcInfo.h"

namespace MC
{

static	MdPtsQueue	z_RedoStk( 10, sizeof( mhPlcInfo));			// �q�d�c�n�p�ۑ��̈�

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈���C�j�V�����C�Y����
void MdRedoPtsDbInit( void)
{
	z_RedoStk.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̕��i�z�u�̗L���𒲂ׂ�

bool HaitiDb::MdIsNotEmptyRedoPts()						// true: ���i�z�u�L��/ false: ���i�z�u����
{
	return z_RedoStk.IsNotEmpty();
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̐擪�ɕ��i�z�u��ǉ�����

void HaitiDb::MdPushRedoPts(
						mhPlcInfo	*pRedoEn		// (I  ) ���i�z�u�Ǘ����
				)
{
	z_RedoStk.Push( pRedoEn);
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̐擪�̕��i�z�u���擾����

void HaitiDb::MdPopRedoPts(
						mhPlcInfo	*pRedoEn		// (I  ) ���i�z�u�Ǘ����
				)
{
	z_RedoStk.Pop( pRedoEn);
}

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�ۑ��̈�̃N���A
void HaitiCmd::MdClearRedo()
{
	mhPlcInfo	PlcEn;

	while (z_RedoStk.IsNotEmpty()) {
		z_RedoStk.Eject( &PlcEn);
		PlcEn.FreeAllAtr();
		//	�z�u�G���e�B�e�B���Ŏg�p���Ă���̈���폜����R�[�f�B���O�̒ǉ���K�v
	}
}

} // namespace MC