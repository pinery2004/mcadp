#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmValid.h
//
//		�l�b�`�c���f��
//						�I�v�V�����Ɨ����̗L���f�[�^�̃`�F�b�N
//
//==========================================================================================

#include "MhRoof.h"

namespace MC
{

// ���i�z�u�̃I�v�V�����Ɨ����̃`�F�b�N
// 
inline bool MmChkValidParts( mhPlcInfo*	pPlcEn) 
{
	MsBitSet* pOptv1;
	MsBitSet* pOptv2;
	MsBitSet* pHstv;

	// �I�v�V�����`�F�b�N
	pOptv1 = pPlcEn->GetPIOpt1();
	if ( MhOptV::MmOptChkC( pOptv1) &&
		 ( ( pOptv2 = pPlcEn->GetPIOpt2()) == NULL || !MhOptV::MmOptOffChkC( pOptv2)) &&

		// �����`�F�b�N
		MhHist::MmVerChkC( pHstv = pPlcEn->GetPIVer()))
		return true;
	else
		return false;
}

// �����z�u�̃I�v�V�����Ɨ����̃`�F�b�N
//
inline bool MmChkValidRoof( MhRoofInfo* i_pRoofEn) 
{
	MsBitSet* pOptv1;
	MsBitSet* pOptv2;
	MsBitSet* pHstv;

	// �I�v�V�����`�F�b�N
	pOptv1 = i_pRoofEn->GetPIOpt1();
	if ( MhOptV::MmOptChkC( pOptv1) &&
		 ( ( pOptv2 = i_pRoofEn->GetPIOpt2()) == NULL || !MhOptV::MmOptOffChkC( pOptv2)) &&

	// �����`�F�b�N
		MhHist::MmVerChkC( pHstv = i_pRoofEn->GetPIVer()))
		return true;
	else
		return false;
}

} // namespace MC