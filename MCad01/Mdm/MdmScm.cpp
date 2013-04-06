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
	MdModel*	pCurMdl = Mdm::GetCurModel();
	
	// ScmBf���󂫂�ID���擾���A�X�L�[�}�̎q��ID�ݒ�p�̈��݂���
	//
	if ( pCurMdl->m_ScmBf.m_idSpaceLast == 0) {
		// �폜���ċ󂫂ɂȂ��Ă���ID���Ȃ��ꍇ�͍ŏIID+1���g�p����
		pCurMdl->m_ScmBf ++;
		*o_pidScm = pCurMdl->m_ScmBf.m_n;
		pScm = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( *o_pidScm)];

	} else {
		// �폜���ċ󂫂ɂȂ��Ă���ID������ꍇ�͂���ID���g�p����
		ASSERT( pCurMdl->m_ScmBf.m_nidSpace >= 1);

		*o_pidScm = pCurMdl->m_ScmBf.m_idSpaceLast;
		pScm = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( *o_pidScm)];

		// �󂫃G���A�ւ�ID����߂�
		pCurMdl->m_ScmBf.m_idSpaceLast = MDSPACEBEFORE( pScm);
		if ( pCurMdl->m_ScmBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_ScmBf.m_pst[MIDtoHN( pCurMdl->m_ScmBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_ScmBf.m_nidSpace--;
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
	MdModel*	pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	// �폜�����蓖�đ҂��̃X�L�[�}��
	pCurMdl->m_ScmBf.m_nidSpace++;
	// �X�L�[�}�폜
	idScmC = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)];
	MDSPACEID( idScmC) = MDID_DELETE;
	idScmC->Free();

	// �󂫃G���A�����N�ɒǉ�
	// ���O�ɍ폜�����X�L�[�}�̎��̃X�L�[�}�Ƃ���
	if ( pCurMdl->m_ScmBf.m_idSpaceLast) {
		idScmB = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( pCurMdl->m_ScmBf.m_idSpaceLast)];
		MDSPACENEXT( idScmB) = i_idScm;
	}
	// �󂫃G���A�����N�̐擪�Ƀ����N�t����
	MDSPACEBEFORE( idScmC) = pCurMdl->m_ScmBf.m_idSpaceLast;
	MDSPACENEXT( idScmC) = 0;
	pCurMdl->m_ScmBf.m_idSpaceLast = i_idScm;
	return 0;
}

//
//===========================================================================
//		�J�����g�X�L�[�}Id�𓾂�
//
MDID DGrp::GetCurScmId()
{
	MdModel* pCurMdl = Mdm::GetCurModel();
	return	pCurMdl->m_idCurScm;
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
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	idCurScm = pCurMdl->m_idCurScm;
	pCurMdl->m_idCurScm = i_idScm;
	return	idCurScm;
}

//
//===========================================================================
//		�X�L�[�}Id�̃��C���[���𓾂�
//
MINT DGrp::GetScmNameFromId(
						MDID		i_idScm,	// �X�L�[�}Id
						MCHAR*		o_sLName,	// ���C���[��
						int			i_nLName	// ���C���[���ő啶����
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( o_sLName, i_nLName, pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_psName);
	return 0;
}

//
//===========================================================================
//	xx	�X�L�[�}Id�̃��C���[����ݒ肷��
//
MINT DGrp::SetScmNameFromId(
						MDID		i_idScm,	// �X�L�[�}Id
						int			i_nLName,	// ���C���[���ő啶����				)
						MCHAR*		i_psName	// ���C���[��
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));

	Mstrcpy_s( pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_psName, i_nLName, i_psName);
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
	MdModel* pCurMdl = Mdm::GetCurModel();

	for ( iC=0; iC<pCurMdl->m_ScmBf.m_n; iC++) {
		if ( Mstrcmp(  pCurMdl->m_ScmBf.m_pst[iC].m_psName, i_psName))
			break;
	}
	if ( iC < pCurMdl->m_ScmBf.m_n)
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
	MdModel* pCurMdl = Mdm::GetCurModel();

	return ( pCurMdl->m_ScmBf.m_n - pCurMdl->m_ScmBf.m_nidSpace);
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
	MdModel* pCurMdl = Mdm::GetCurModel();

	o_pGidScm->m_n = 0;
	for ( iC=0; iC<pCurMdl->m_ScmBf.m_n; iC++) {
		if ( MDSPACEID( &pCurMdl->m_ScmBf.m_pst[iC]) != MDID_DELETE)
			(*o_pGidScm) += (iC+1);
	}
	return 0;
}

} // namespace MC
