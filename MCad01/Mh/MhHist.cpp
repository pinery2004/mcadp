//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhHist.cpp
//
//		�����Ǘ�����T�|�[�g
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
#define	DLL_EXPORT_OPTION_DO
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"

#include "MhPlcInfo.h"

#include "MdLib.h"


#define	MH_ALL_BITS	0xFFFFFFFF

#define		MHSZ_Hist		sizeof(MUINT)*3


namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����Ǘ��R�[�h�̗̈���J������
	void MhOpt::MhHistFre(
//						MhHistV		*pHstv		// (I O) �J�������Ǘ� NULL: �J���s�v
						MsBitSet*	*pHstv		// (I O) �J�������Ǘ� NULL: �J���s�v
				)
{
	if ( pHstv != NULL)
		delete (char*)pHstv;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�V�K���R�[�h�ǉ����ɐݒ肷�闚���Ǘ��R�[�h���擾����
//		�@�i�����Ǘ��R�[�h������G���A�̊m�ۂ͖{�֐��ōs���j
void MhOpt::MhHistAdd(
						MsBitSet*		*ppHstv		// (  O) �ǉ����R�[�h�ɐݒ肷�闚���Ǘ��R�[�h�̃|�C���^ NULL: �S�����Ǘ�
				 )
{
	MsBitSet	bHstvC;
	MsBitSet	*pHstvW;

	if ( MhHist::MmVerGetC( &bHstvC)) {								// �J�����g�I�𗚗��Ǘ��擾
		*ppHstv = NULL;											// ����
	} else {													// �����ȊO�̃o�[�W������ݒ�
		pHstvW = (MhHistV*)new char[MHSZ_Hist];

#ifdef _DEBUG
						Msprintf_s( mlLog::m_Str, Mstr( "MALLOC Hist MhHistAdd TRC %x\n"), pHstvW);
						MBTRCPRBF;
#endif

		*pHstvW = bHstvC;
		*ppHstv = pHstvW;
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�C�����ɐݒ肷�闚���Ǘ��R�[�h���擾����
//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
//			1 : �C���������Ǘ��̓J�����g�o�[�W�����̂ݐݒ肳��Ă���ꍇ�ŁA
//				�C�������R�[�h�͗����Ǘ��ύX�Ȃ��ŏC�����e���㏑������B
//				�ǉ����R�[�h�͂Ȃ��B
//			3 : �C���������Ǘ��ɃJ�����g�o�[�W�����ȊO�̃o�[�W�������܂ޏꍇ�ŁA
//				�J�����g�o�[�W�����ȊO�̗��𕔕��́A�C�������R�[�h�����̂܂܎c�������Ǘ��R�[�h�̂ݏC������B
//				����ɁA�J�����g�o�[�W�����݂̗̂����Ǘ������C����̃��R�[�h��V���ɒǉ�����B
//				�i�����Ǘ��R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
MINT MhOpt::MhHistMod(
						mhPlcInfo	*pPlcEnR,		// (I O) �C��������
						mhPlcInfo*	*ppPlcEnM		// (  O) �C���敔��
				)
{
	MsBitSet	*pHstvR;
	MsBitSet	HstvMod;
	MsBitSet	*pHstvMod;
	MsBitSet	*pHstvAdd;
	MINT		iMod;

	pHstvR = pPlcEnR->GetPIVer();

	// �C�������ނ̗������̎擾
	if ( pHstvR == NULL) {										// �C���Ώە��i�z�u�̗����Ǘ����R�s�[
		pHstvMod = NULL;
	} else {
		HstvMod = *pHstvR;
		pHstvMod = &HstvMod;
	}
	
	iMod = MhHist::MmHistModChk( &pHstvMod, &pHstvAdd);

	switch ( iMod) {
		case 1:													// �C���������Ǘ��̓J�����g�o�[�W�����̂ݐݒ肵�Ă���ꍇ
			*ppPlcEnM = pPlcEnR;							// 		�C�����̃��R�[�h���C���ΏۂƂ���
			break;
		case 3:													// �C���������Ǘ��ɃJ�����g�o�[�W�����ȊO�̃o�[�W�������܂ޏꍇ
																// 		�C�����̗����Ǘ���ύX����i�J�����g�o�[�W�������n�e�e����j
			if ( pHstvR == NULL) {
				pPlcEnR->SetPIVer( pHstvMod);				//			�V�K�ǉ��J�����g�o�[�W�����ȊO�n�m�̗����Ǘ��̃|�C���^���Z�b�g
			} else {
				*pHstvR = *pHstvMod;							//			�����Ǘ����J�����g�o�[�W�����n�e�e�ɏC��
			}

			mhPlcInfo	PlcEnM;								// 		�V�K�ɗ����Ǘ����J�����g�̃R�s�[���R�[�h���쐬���C���ΏۂƂ���
			PlcEnM.Copy( *pPlcEnR);

			PlcEnM.FreePIVer();
			PlcEnM.SetPIVer( pHstvAdd);
			*ppPlcEnM = HaitiDb::MdInjectPts( &PlcEnM);
	}
	return iMod;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�폜���ɐݒ肷�闚���Ǘ��R�[�h���擾����
//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
//			1 : �폜�������Ǘ��̓J�����g�o�[�W�����Ɠ���̏ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			3 : �폜�������Ǘ��ɃJ�����g�o�[�W�����ȊO�̗����Ǘ����܂ޏꍇ�ŁA
//				�J�����g�o�[�W�����ȊO�̗����Ǘ������́A�폜�����R�[�h�����̂܂܎c�������Ǘ��R�[�h�̂ݏC������B
//				�i�����Ǘ��R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j


MINT MhOpt::MhHistDel(
						MsBitSet*		*ppHstvMod		// (I O) �폜��̃��R�[�h�̕\���n�m�����Ǘ��Q
				)
{
	return MhHist::MmHistDelChk( ppHstvMod);
}

} // namespace MC