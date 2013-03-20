//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdGrp.cpp
//
//		���f���f�[�^�x�[�X
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

//===========================================================================
//		�O���[�v�̐���
//
	MINT DGrp::CreateGrp(								//
					MCHAR		i_sName[],		// �O���[�v��
					MREAL		i_rKt,			// �K����
					MREAL		i_rFl,			// ������
					MDID*		o_pidGrp,		// �O���[�vId
					MINT		i_sz/*=10*/		// �����O���[�vId�o�b�t�@�T�C�Y
				)
{
	MdmSetGRP*	pGrp;
	
	// GrpBf���󂫂�ID���擾���A�O���[�v�̎q��ID�ݒ�p�̈��݂���
	//
	if ( Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast == 0) {
		// �폜���ċ󂫂ɂȂ��Ă���ID���Ȃ��ꍇ�͍ŏIID+1���g�p����
		Mdm::GetCurModel()->m_GrpBf ++;
		*o_pidGrp = Mdm::GetCurModel()->m_GrpBf.m_n;
		pGrp = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( *o_pidGrp)];

	} else {
		// �폜���ċ󂫂ɂȂ��Ă���ID������ꍇ�͂���ID���g�p����
		ASSERT( Mdm::GetCurModel()->m_GrpBf.m_nidSpace >= 1);

		*o_pidGrp = Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast;
		pGrp = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( *o_pidGrp)];

		// �󂫃G���A�ւ�ID����߂�
		Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast = MDSPACEBEFORE( pGrp);
		if ( Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast)
			MDSPACENEXT( &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast)]) = 0;
		Mdm::GetCurModel()->m_GrpBf.m_nidSpace--;
	}

	//	�����O���[�v�ɎqID�̐ݒ�p�̈���m�ۂ���
	pGrp->m_GidC.Alloc( (int)i_sz);

	// �O���[�v���A�K�����A��������ݒ肷��
	pGrp->SetInit( 0, i_sName, i_rKt, i_rFl);
	return 0;
}

//===========================================================================
//		�O���[�v�̍폜
//
MINT DGrp::DeleteGrp(								//
						MDID		i_idGrp		// �O���[�vId
				)
{
	MdmSetGRP*	pGrpB;							// ���O�ɍ폜�����O���[�v
	MdmSetGRP*	pGrpC;							// �폜�O���[�v

	ASSERT( MDISGRP( i_idGrp));

	// �폜�����蓖�đ҂��̃O���[�v��
	Mdm::GetCurModel()->m_GrpBf.m_nidSpace++;

	// �O���[�v�폜
	pGrpC = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)];
	MDSPACEID( pGrpC) = MDID_DELETE;
	pGrpC->Free();

	// �󂫃G���A�����N�ɒǉ�
	// ���O�ɍ폜�����O���[�v�̎��̃O���[�v�Ƃ���
	if ( Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast) {
		pGrpB = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast)];
		MDSPACENEXT( pGrpB) = i_idGrp;
	}

	// �󂫃G���A�����N�̐擪�Ƀ����N�t����
	MDSPACEBEFORE( pGrpC) = Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast;
	MDSPACENEXT( pGrpC) = 0;
	Mdm::GetCurModel()->m_GrpBf.m_idSpaceLast = i_idGrp;
	return 0;
}

//===========================================================================
//		�O���[�v�̊K����FL�̖₢���킹
//
MINT DGrp::GetGrpParam(
						MDID		i_idGrp,	// �O���[�vId
						MREAL*		o_prKt,		// �K����
						MREAL*		o_prFl		// ������
				)
{
	MdmSetGRP*	pGrp;

	ASSERT( MDISGRP( i_idGrp));

	pGrp = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)];
	*o_prKt = pGrp->m_rKt;
	*o_prFl = pGrp->m_rFl;
	return 0;
}

//===========================================================================
//		�O���[�v�̊K����FL��ݒ�
//
MINT DGrp::SetGrpParam(
						MDID		i_idGrp,	// �O���[�vId
						MREAL		i_rKt,		// �K����
						MREAL		i_rFl		// ������
				)
{
	MdmSetGRP*	pGrp;

	ASSERT( MDISGRP( i_idGrp));

	pGrp = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)];
	pGrp->m_rKt = i_rKt;
	pGrp->m_rFl = i_rFl;
	return 0;
}

//===========================================================================
//		�J�����g�O���[�vId�𓾂�
//
MDID DGrp::GetCurGrpId()
{
	return	Mdm::GetCurModel()->m_idCurGrp;
}

//===========================================================================
//		�J�����g�O���[�vId��ݒ肷��
//
MDID DGrp::SetCurGrpId(							// ���O�̃O���[�vId
						MDID		i_idGrp		// �O���[�vId
				)
{
	MDID idCurGrp;

	ASSERT( MDISGRP( i_idGrp));

	idCurGrp = Mdm::GetCurModel()->m_idCurGrp;
	Mdm::GetCurModel()->m_idCurGrp = i_idGrp;

	// �J�����g���W�ϊ��}�g���b�N�X��ݒ肷��
	DLyr::SetCurCoord( Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)].m_MTrans);
	return	idCurGrp;
}

//===========================================================================
//		�O���[�vId�̃O���[�v���𓾂�
//
MINT DGrp::GetGrpNameFromId(
						MDID		i_idGrp,	// �O���[�vId
						MCHAR*		o_psName	// �O���[�v��
				)
{
	ASSERT( MDISGRP( i_idGrp));

	Mstrcpy_s( o_psName, 256, Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)].m_sName);
	return 0;
}

//===========================================================================
//	xx	�O���[�vId�̃O���[�v����ݒ肷��
//
MINT DGrp::SetGrpNameFromId(
						MDID		i_idGrp,	// �O���[�vId
						MCHAR*		i_psName	// �O���[�v��
				)
{
	ASSERT( MDISGRP( i_idGrp));

	Mstrcpy_s( Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)].m_sName, 256, i_psName);
	return 0;
}

//===========================================================================
//		�O���[�v�����O���[�vId�𓾂�
//
MINT DGrp::GetGrpIdFromName (
						MCHAR*		i_psName,	// �O���[�v��
						MDID*		o_pidGrp	// �O���[�vId
				)
{
	MINT	iC;

	for ( iC=0; iC<Mdm::GetCurModel()->m_GrpBf.m_n; iC++) {
		if ( Mstrcmp(  Mdm::GetCurModel()->m_GrpBf.m_st[iC].m_sName, i_psName))
			break;
	}
	if ( iC < Mdm::GetCurModel()->m_GrpBf.m_n)
		*o_pidGrp = MHNtoID( iC);
	else
		*o_pidGrp = 0;
	return 0;
}

//===========================================================================
//		�O���[�v���𓾂�
//
MINT DGrp::GetGrpCount ()
{
	return ( Mdm::GetCurModel()->m_GrpBf.m_n - Mdm::GetCurModel()->m_GrpBf.m_nidSpace);
}

//===========================================================================
//		�S�O���[�vId�̃Z�b�g�𓾂�
//

MINT DGrp::GetGrpIdAll (
						MDIDSET*		o_pGidGrp	// �O���[�vId�Z�b�g
				)
{
	MINT	iC;

	o_pGidGrp->m_n = 0;
	for ( iC=0; iC<Mdm::GetCurModel()->m_GrpBf.m_n; iC++) {
		if ( MDSPACEID( &Mdm::GetCurModel()->m_GrpBf.m_st[iC]) != MDID_DELETE)
			(*o_pGidGrp) += MHNtoID( iC);
	}
	return 0;
}

//===========================================================================
//		�O���[�v�̍��W�ϊ��}�g���b�N�X�𓾂�
//
MINT	MdlGetGrpCoord (
						MDID		i_idGrp,
						MgMat3E*		o_mTrans	// ���W�ϊ��}�g���b�N�X
				)
{
	ASSERT( MDISGRP( i_idGrp));

	*o_mTrans = Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( i_idGrp)].m_MTrans;
	return 0;
}

//===========================================================================
//		����W�ϊ��}�g���b�N�X�𓾂�
//
//		�f�[�^�x�[�X���I�[�v������ƁA����W�ϊ��}�g���b�N�X�͕K���P���݂���B
//
MgMat3E	MdlGetBaseCoord ( )						// ����W�ϊ��}�g���b�N�X
{
	return Mdm::GetCurModel()->m_MBaseTrans;
}


//===========================================================================
//		�J�����g���W�ϊ��}�g���b�N�X�𓾂�
//
//		�P�̃O���[�v�ɂ͂P�̍��W�n�����݂���B
//		SetCurGrpId�ŃO���[�v���J�����g�ɐݒ肳���ƁA
//		���̃O���[�v�̍��W�n���J�����g���W�n�ɂȂ�B
//		Inp:Point���œ�������W�l�̓J�����g���W�n��̍��W�l�ƂȂ�B
//
MgMat3E	MdlGetCurCoord ( )						// �J�����g���W�ϊ��}�g���b�N�X
{
	return Mdm::GetCurModel()->m_MCurTrans;
}

//===========================================================================
//		�J�����g���W�ϊ��}�g���b�N�X��ݒ�
//
//		�P�̃O���[�v�ɂ͂P�̍��W�n�����݂���B
//		SetCurGrpId�ŃO���[�v���J�����g�ɐݒ肳���ƁA
//		���̃O���[�v�̍��W�n���J�����g���W�n�ɂȂ�B
//		Inp:Point���œ�������W�l�̓J�����g���W�n��̍��W�l�ƂȂ�B
//
//		�J�����g���W�n���ꎞ�I�ɕύX����ꍇ�́A���O��GetCurCoord��
//		���̃J�����g���W�n��₢���킹�Ă����A�����I�����Ɍ��ɖ߂����ƁB
//
MgMat3E DLyr::SetCurCoord (
						MgMat3E&		i_MTransr	// ���W�ϊ��}�g���b�N�X
				)
{
	MgMat3E	MTrans;

	MTrans = Mdm::GetCurModel()->m_MCurTrans;
	Mdm::GetCurModel()->m_MCurTrans = i_MTransr;
	return MTrans;
}

} // namespace MC