//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhOpt.cpp
//
//		�n�o�s�Q����T�|�[�g
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

#include "MhDefParts.h"
#include "MsBitSet.h"
#define	DLL_EXPORT_OPTION_DO
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"

#include "MmLib.h"
#include "MhInpPlcParts.h"

#include "MgGrp.h"

#include "MhRoof.h"
#include "MdLib.h"

#define	MH_ALL_BITS	0xFFFFFFFF

#define		MHSZ_OPTION		sizeof(MUINT)*3

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�n�o�s�Q�R�[�h�̗̈���J������
void Option::MhFreOpt(
						MsBitSet		*pOptv		// (I O) �J���n�o�s�Q NULL: �J���s�v
				)
{
	if ( pOptv != NULL)
		delete (char*)pOptv;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�V�K���R�[�h�ǉ����ɐݒ肷��n�o�s�Q�R�[�h���擾����
//		�@�i�n�o�s�Q�R�[�h������G���A�̊m�ۂ͖{�֐��ōs���j
void Option::MhAddOpt(
						MsBitSet*		*ppOptv		// (  O) �ǉ����R�[�h�ɐݒ肷��n�o�s�Q�R�[�h�̃|�C���^ NULL: �S�n�o�s�Q
				 )
{
	MhOpt	bOptC;
	MsBitSet	*pOptvW;

	if ( MhOptV::MmOptGetC( &bOptC)) {							// �J�����g�I���n�o�s�Q���擾����
		*ppOptv = NULL;											// �W��
	} else {													// �W���ȊO�̃I�v�V�����ݒ肠��
		pOptvW = (MsBitSet*)new char[MHSZ_OPTION];

#ifdef _DEBUG
						Msprintf_s( mlLog::m_Str, Mstr( "MALLOC OPTION MhAddOpt TRC %x\n"), pOptvW);
						MBTRCPRBF;
#endif
		if ( MhOptV::MmOptSrch( bOptC) == 0) {				// �V�����I�v�V�����Q�Ȃ�ǉ���
			MhOptV::MmOptAddDB();									// �Q�ƑΏۑSDB���R�[�h�ɂn�o�s�Q�ǉ�
			MhOptV::MmOptIncSrch( bOptC);							// �Ǎ��ݏ����݃I�v�V�����Q�Z�b�g�����߂�
		}
		*pOptvW = MhOptV::MhOptBScWGet();
		*ppOptv = pOptvW;
	}
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�C�����ɐݒ肷��n�o�s�Q�R�[�h���擾����
//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
//			1 : �C�����n�o�s�Q�͏����݂n�o�s�Q�Ɠ���̏ꍇ�ŁA
//				�C�������R�[�h�́A�n�o�s�Q�ύX�Ȃ���
//				�C�����e���㏑������B	�ǉ����R�[�h�͂Ȃ��B
//
//			2 :	�C�����n�o�s�Q�͏����݂n�o�s�Q�ɑS�Ċ܂܂ꂩ�ǉ��n�o�s�Q������ꍇ�ŁA
//				�C�������R�[�h�́A�����݂n�o�s�Q�ɕύX���A�� �n�o�s�Q�ύX�Ȃ��Ł@�i1�Ɠ����j
//				�C�����e���㏑������B�ǉ����R�[�h�͂Ȃ��B
//
//			3 : �C�����n�o�s�Q�ɏ����݂n�o�s�Q�ȊO�̂n�o�s�Q���܂ޏꍇ�ŁA
//				�����݂n�o�s�Q�ȊO�̂n�o�s�Q�����́A�C�������R�[�h�����̂܂܎c���n�o�s�Q�R�[�h�̂ݏC������B
//				����ɁA�����݂n�o�s�Q�����C����̃��R�[�h��V���ɒǉ�����B
//				�i�n�o�s�Q�R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
MINT Option::MhModOpt(
						mhPlcParts	 *pPlcEnR,		// (I O) �C��������
						mhPlcParts* *ppPlcEnM		// (  O) �C���敔��
				)
{
	MhOpt	OptC;
	MsBitSet	OptvM;

	MsBitSet	*pOptvRN;
	MsBitSet	*pOptvDN;
	MsBitSet	*pOptvWN;
	MINT		iMod;
	MhOptV	*pOptv;

	if ( !MhOptV::MmOptGetC( &OptC)) {								// �J�����g�I���n�o�s�Q���擾����
																// �W���ȊO�̃I�v�V�����ݒ肠��
		if ( MhOptV::MmOptSrch( OptC) == 0) {
			MhOptV::MmOptAddDB();									// �Q�ƑΏۑSDB���R�[�h�ɂn�o�s�Q�ǉ�
			MhOptV::MmOptIncSrch( OptC);
		}
	}

	pOptvRN = pPlcEnR->GetPIOpt1();
	iMod = MhOptV::MmOptModChk( &pOptvRN, &pOptvWN, &pOptv);

	if ( iMod < 3) {
																// �C�����n�o�s�Q�͏����݂n�o�s�Q�Ɠ���̏ꍇ
																// �C�����n�o�s�Q�͏����݂n�o�s�Q�ɑS�Ċ܂܂ꂩ�ǉ��n�o�s�Q������ꍇ
			*ppPlcEnM = pPlcEnR;							// �C�������R�[�h�́A�n�o�s�Q�ύX�Ȃ�
	} else {
																// �C�����n�o�s�Q�ɏ����݂n�o�s�Q�ȊO�̂n�o�s�Q���܂ޏꍇ
			mhPlcParts	PlcEnM;
			PlcEnM.Copy( *pPlcEnR);							// 

			pOptvDN = pPlcEnR->GetPIOpt2();
			if ( pOptvDN == NULL) {
				pOptvDN = (MsBitSet*)new char[sizeof( pOptv->bmCurWGOptSet)];	// �C���p�ɍ폜��̃��R�[�h�ɕ\���n�e�eOPT�Q�Z�b�g��ǉ�
				*pOptvDN = pOptv->bmCurWGOptSet;								// �A�ݒ�
			} else {
				*pOptvDN |= pOptv->bmCurWGOptSet;								// �C���p�ɍ폜��̃��R�[�h�ɕ\���n�e�eOPT�Q�Z�b�g��ݒ�
			} 
			pPlcEnR->SetPIOpt2( pOptvDN);

			PlcEnM.FreePIOpt1();
			PlcEnM.SetPIOpt1( pOptvWN);

			*ppPlcEnM = HaitiDb::MdInjectParts( &PlcEnM);
	}
	return iMod;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�폜���ɐݒ肷��n�o�s�Q�R�[�h���擾����
//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
//			1 : �폜���n�o�s�Q�͏����݂n�o�s�Q�Ɠ���̏ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			2 :	�폜���n�o�s�Q�͏����݂n�o�s�Q�ɑS�Ċ܂܂ꂩ�ǉ��n�o�s�Q������ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			3 : �폜���n�o�s�Q�ɏ����݂n�o�s�Q�ȊO�̂n�o�s�Q���܂ޏꍇ�ŁA
//				�����݂n�o�s�Q�ȊO�̂n�o�s�Q�����́A�폜�����R�[�h�����̂܂܎c���n�o�s�Q�R�[�h�̂ݏC������B
//				�i�n�o�s�Q�R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j

MINT Option::MhDelOpt(
						MsBitSet*		*ppOptvRN,		// (I O) �폜�O��̃��R�[�h�̕\���n�m  OPT�Q�Z�b�g
						MsBitSet*		*ppOptvDN		// (I O) �폜�O��̃��R�[�h�̕\���n�e�eOPT�Q�Z�b�g
				)
{
	MINT		ist;

	MhOpt	OptC;
	MsBitSet	OptvM;

	if ( !MhOptV::MmOptGetC( &OptC)) {						// �J�����g�I���n�o�s�Q���擾����
														// �W���ȊO�̃I�v�V�����ݒ肠��
		if ( MhOptV::MmOptSrch( OptC) == 0) {
			MhOptV::MmOptAddDB();							// �Q�ƑΏۑSDB���R�[�h�ɂn�o�s�Q�ǉ�
			MhOptV::MmOptIncSrch( OptC);
		}
	}
	ist = MhOptV::MmOptDelChk( ppOptvRN, ppOptvDN);
	return ist;
}

} // namespace MC