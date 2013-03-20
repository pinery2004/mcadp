//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdScm.cpp
//
//		�X�L�[�}
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"

#include "MdModel.h"

#define DLL_EXPORT_DGRP_DO
#include "MdmDB.h"
#include "Mdm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

//
//===========================================================================
//		�X�L�[�}�̐���
//
MINT DGrp::CreateScm(								//
						MCHAR		i_sName[],		// ���C���[��
						MDID*		o_pidScm,		// �X�L�[�}Id
						MINT		i_sz /*=10*/	// �����X�L�[�}Id�o�b�t�@�T�C�Y
				)
{
	MdmSetSCM*	pScm;
	
	// ScmBf���󂫂�ID���擾���A�X�L�[�}�̎q��ID�ݒ�p�̈��݂���
	//
	if ( Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast == 0) {
		// �폜���ċ󂫂ɂȂ��Ă���ID���Ȃ��ꍇ�͍ŏIID+1���g�p����
		Mdm::GetCurModel()->m_ScmBf ++;
		*o_pidScm = Mdm::GetCurModel()->m_ScmBf.m_n;
		pScm = &Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( *o_pidScm)];

	} else {
		// �폜���ċ󂫂ɂȂ��Ă���ID������ꍇ�͂���ID���g�p����
		ASSERT( Mdm::GetCurModel()->m_ScmBf.m_nidSpace >= 1);

		*o_pidScm = Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast;
		pScm = &Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( *o_pidScm)];

		// �󂫃G���A�ւ�ID����߂�
		Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast = MDSPACEBEFORE( pScm);
		if ( Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast)
			MDSPACENEXT( &Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast)]) = 0;
		Mdm::GetCurModel()->m_ScmBf.m_nidSpace--;
	}

	//	�X�L�[�}ID�ɂɎqID�̐ݒ�p�̈���m�ۂ���
	pScm->m_GidC.Alloc( i_sz);

	pScm->SetInit( 0, i_sName);

	return 0;
}

//
//===========================================================================
//		�X�L�[�}�̍폜
//
MINT DGrp::DeleteScm(							//
						MDID		i_idScm		// �X�L�[�}Id
				)
{
	MdmSetSCM*	idScmB;							// ���O�ɍ폜�����X�L�[�}
	MdmSetSCM*	idScmC;							// �폜���X�L�[�}

	ASSERT( MDISSCM( i_idScm));

	// �폜�����蓖�đ҂��̃X�L�[�}��
	Mdm::GetCurModel()->m_ScmBf.m_nidSpace++;
	// �X�L�[�}�폜
	idScmC = &Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( i_idScm)];
	MDSPACEID( idScmC) = MDID_DELETE;
	idScmC->Free();

	// �󂫃G���A�����N�ɒǉ�
	// ���O�ɍ폜�����X�L�[�}�̎��̃X�L�[�}�Ƃ���
	if ( Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast) {
		idScmB = &Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast)];
		MDSPACENEXT( idScmB) = i_idScm;
	}
	// �󂫃G���A�����N�̐擪�Ƀ����N�t����
	MDSPACEBEFORE( idScmC) = Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast;
	MDSPACENEXT( idScmC) = 0;
	Mdm::GetCurModel()->m_ScmBf.m_idSpaceLast = i_idScm;
	return 0;
}

//
//===========================================================================
//		�J�����g�X�L�[�}Id�𓾂�
//
MDID DGrp::GetCurScmId()
{
	return	Mdm::GetCurModel()->m_idCurScm;
}

//
//===========================================================================
//		�J�����g�X�L�[�}Id��ݒ肷��
//
MDID DGrp::SetCurScmId(
						MDID		i_idScm	// �X�L�[�}Id
				)
{
	MDID idCurScm;

	ASSERT( MDISSCM( i_idScm));

	idCurScm = Mdm::GetCurModel()->m_idCurScm;
	Mdm::GetCurModel()->m_idCurScm = i_idScm;
	return	idCurScm;
}

//
//===========================================================================
//		�X�L�[�}Id�̃��C���[���𓾂�
//
MINT DGrp::GetScmNameFromId(
						MDID		i_idScm,	// �X�L�[�}Id
						MCHAR*		o_psName	// ���C���[��
				)
{
	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( o_psName, 256, Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( i_idScm)].m_sName);
	return 0;
}

//
//===========================================================================
//	xx	�X�L�[�}Id�̃��C���[����ݒ肷��
//
MINT DGrp::SetScmNameFromId(
						MDID		i_idScm,	// �X�L�[�}Id
						MCHAR*		i_psName	// ���C���[��
				)
{
	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( Mdm::GetCurModel()->m_ScmBf.m_st[MIDtoHN( i_idScm)].m_sName, 256, i_psName);
	return 0;
}

//
//===========================================================================
//		���C���[�����X�L�[�}Id�𓾂�
//
MINT DGrp::GetScmIdFromName (
						MCHAR*		i_psName,	// ���C���[��
						MDID*		o_pidScm	// �X�L�[�}Id
				)
{
	MINT	iC;

	for ( iC=0; iC<Mdm::GetCurModel()->m_ScmBf.m_n; iC++) {
		if ( Mstrcmp(  Mdm::GetCurModel()->m_ScmBf.m_st[iC].m_sName, i_psName))
			break;
	}
	if ( iC < Mdm::GetCurModel()->m_ScmBf.m_n)
		*o_pidScm = iC;
	else
		*o_pidScm = 0;
	return 0;
}

//
//===========================================================================
//		�X�L�[�}���𓾂�
//
MINT DGrp::GetScmCount ()
{
	return ( Mdm::GetCurModel()->m_ScmBf.m_n - Mdm::GetCurModel()->m_ScmBf.m_nidSpace);
}

//
//===========================================================================
//		�S�X�L�[�}Id�̃Z�b�g�𓾂�
//

MINT DGrp::GetScmIdAll (
//						MdGrpS<MINT>*	o_pGidScm	// �X�L�[�}Id�Z�b�g
						MDIDSET*		o_pGidScm	// �X�L�[�}Id�Z�b�g
				)
{
	MINT	iC;

	o_pGidScm->m_n = 0;
	for ( iC=0; iC<Mdm::GetCurModel()->m_ScmBf.m_n; iC++) {
		if ( MDSPACEID( &Mdm::GetCurModel()->m_ScmBf.m_st[iC]) != MDID_DELETE)
			(*o_pGidScm) += (iC+1);
	}
	return 0;
}

} // namespace MC