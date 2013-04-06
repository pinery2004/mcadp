//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdLyr.cpp
//
//		���C���[
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgMat.h"

#include "MdModel.h"

#define DLL_EXPORT_DLYR_DO
#include "MdmDB.h"
#include "Mdm.h"

namespace MC
{

//===========================================================================
//		���C���[�̐���
//
MINT DLyr::CreateLyr(
						MDID	i_idScm,		// �X�L�[�}ID
						MDID	i_idGrp,		// �O���[�vID
						MDID*	o_pidLyr,		// ���C���[ID
						MINT	i_sz /*=10*/	// �����G���e�B�e�BId�o�b�t�@�T�C�Y
				)
{
	MdmSetLYR*	pLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();
	
	ASSERT( MDISSCM( i_idScm));
	ASSERT( MDISGRP( i_idGrp));

	// LyrBf���󂫂�ID���擾���A���C���[�̎q��ID�ݒ�p�̈��݂���
	//
	if ( pCurMdl->m_LyrBf.m_idSpaceLast == 0) {
		// �폜���ċ󂫂ɂȂ��Ă���ID���Ȃ��ꍇ�͍ŏIID+1���g�p����
		pCurMdl->m_LyrBf ++;
		*o_pidLyr = pCurMdl->m_LyrBf.m_n;
		pLyr = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( *o_pidLyr)];

	} else {
		// �폜���ċ󂫂ɂȂ��Ă���ID������ꍇ�͂���ID���g�p����
		ASSERT( pCurMdl->m_LyrBf.m_nidSpace >= 1);

		*o_pidLyr = pCurMdl->m_LyrBf.m_idSpaceLast;
		pLyr = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( *o_pidLyr)];

		// �󂫃G���A�ւ�ID����߂�
		pCurMdl->m_LyrBf.m_idSpaceLast = MDSPACEBEFORE( pLyr);
		if ( pCurMdl->m_LyrBf.m_idSpaceLast)
			MDSPACENEXT( &pCurMdl->m_LyrBf.m_pst[MIDtoHN( pCurMdl->m_LyrBf.m_idSpaceLast)]) = 0;
		pCurMdl->m_LyrBf.m_nidSpace--;
	}

	// �X�L�[�}ID�A�O���[�vID�̐ݒ�A�G���e�B�e�BId�o�b�t�@�̐���
	pLyr->SetInit( i_idGrp, i_idScm, i_sz, 4);					// �O���[�v�A�X�L�[�}�A
																// �qID�G���A�A
																// �E�B���h�E���̕\���E���m���[�h(������4�E�B���h�E)
	// �������C���[�ƃO���[�v�A�X�L�[�}�Ƃ̃����N��t����
	pCurMdl->m_GrpBf.m_pst[MIDtoHN( i_idGrp)].m_GidC += (*o_pidLyr);
	pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_GidC += (*o_pidLyr);

//EXIT:
	return 0;
}

//===========================================================================
//		���C���[�̍폜
//
MINT DLyr::DeleteLyr(							//
						MDID		i_idLyr		// ���C���[Id
				)
{
	MdmSetLYR*	pLyrB;							// ���O�ɍ폜�������C���[
	MdmSetLYR*	pLyrC;							// �폜���C���[
	MDID		idGrp;
	MDID		idScm;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	// �O���[�v�A�X�L�[�}����̃����N���폜����
	pLyrC = &pCurMdl->m_LyrBf.m_pst[ MIDtoHN( i_idLyr)];
	idGrp = pLyrC->m_idP1;
	idScm = pLyrC->m_idP2;
	pCurMdl->m_GrpBf.m_pst[MIDtoHN( idGrp)] -= i_idLyr;
	pCurMdl->m_ScmBf.m_pst[MIDtoHN( idScm)] -= i_idLyr;

	// �폜�����蓖�đ҂��̋󂫃��C���[���ɒǉ�
	pCurMdl->m_LyrBf.m_nidSpace++;
	// ���C���[�폜�t���O�ݒ�Ǝg�p�G���A�J��
	MDSPACEID( pLyrC) = MDID_DELETE;
	pLyrC->Free();

	// �󂫃G���A�����N�ɒǉ�
	// ���O�ɍ폜�������C���[�̎��̃��C���[�Ƃ���
	if ( pCurMdl->m_LyrBf.m_idSpaceLast) {
		pLyrB = &pCurMdl->m_LyrBf.m_pst[ MIDtoHN( pCurMdl->m_LyrBf.m_idSpaceLast)];
		MDSPACENEXT( pLyrB) = i_idLyr;
	}
	// �󂫃G���A�����N�̐擪�Ƀ����N�t����
	MDSPACEBEFORE( pLyrC) = pCurMdl->m_LyrBf.m_idSpaceLast;
	MDSPACENEXT( pLyrC) = 0;
	pCurMdl->m_LyrBf.m_idSpaceLast = i_idLyr;
	return 0;
}

//===========================================================================
//		�J�����g���C���[Id�𓾂�
//
MDID DLyr::GetCurLyrId()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return	pCurMdl->m_idCurGrp;
}

//===========================================================================
//		�J�����g���C���[Id��ݒ肷��
//
MDID DLyr::SetCurLyrId(					// ���O�̃J�����g���C���[Id
						MDID		i_idLyr		// ���C���[Id
				)
{
	MDID idCurGrp;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	idCurGrp = pCurMdl->m_idCurGrp;
	pCurMdl->m_idCurGrp = i_idLyr;
	return	idCurGrp;
}

//===========================================================================
//		���C���[���𓾂�
//
MINT DLyr::GetLyrCount ()
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	return ( pCurMdl->m_LyrBf.m_n - pCurMdl->m_LyrBf.m_nidSpace);
}

//===========================================================================
//		�S���C���[Id�̃Z�b�g�𓾂�
//

MINT DLyr::GetLyrIdAll (
						MDIDSET*	o_pGidLyr	// ���C���[Id�Z�b�g
				)
{
	MINT	iC;
	MdModel* pCurMdl = Mdm::GetCurModel();

	o_pGidLyr->m_n = 0;
	for ( iC=0; iC<pCurMdl->m_LyrBf.m_n; iC++) {
		if ( MDSPACEID( &pCurMdl->m_LyrBf.m_pst[iC]) != MDID_DELETE)
			(*o_pGidLyr) += MHNtoID( iC);
	}
	return 0;
}

//===========================================================================
//		�O���[�vId�ƃX�L�[�}Id���烌�C���[Id�𓾂�
//

MINT DLyr::GetLyrId( 
						MDID		i_idScm,	// �X�L�[�}Id
						MDID		i_idGrp,	// �O���[�vId
						MDID*		o_pidLyr	// ���C���[Id
				)
{
	MINT		iC;
	MDIDSET*	pGidL;
	MDID		idLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISSCM( i_idScm));
	ASSERT( MDISGRP( i_idGrp));

	// �w��Id�̃X�L�[�}�̎qId�Z�b�g(���C���[Id�Z�b�g)�𓾂�
	pGidL = &pCurMdl->m_ScmBf.m_pst[MIDtoHN( i_idScm)].m_GidC;

	// �e�̃O���[�vId���w��O���[�vId�̃��C���[��T��
	*o_pidLyr = 0;
	for ( iC=0; iC<pGidL->m_n; iC++) {
		idLyr = pGidL->m_pst[iC];
		if ( idLyr > 0) {
			if ( pCurMdl->m_LyrBf.m_pst[MIDtoHN( idLyr)].m_idP2 == i_idGrp) {
				*o_pidLyr = idLyr;
				break;
			}
		}
	}
	return 0;
}

//===========================================================================
//		���C���[Id����O���[�vId���擾
//
MINT DLyr::GetGrpId (
						MDID	i_idLyr,		// ���C���[Id
						MDID*	o_idGrp			// �O���[�vId
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		ms::SysError( MBCstr( "GetGrpId"), MC_ERR_ID);

	*o_idGrp = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_idP1;
	return 0;
}

//===========================================================================
//		���C���[Id����X�L�[�}Id���擾
//
MINT DLyr::GetScm (
						MDID	i_idLyr,		// ���C���[Id
						MDID*	o_idScm			// �X�L�[�}Id
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		ms::SysError( MBCstr( "GetScm"), MC_ERR_ID);

	*o_idScm = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_idP2;
	return 0;
}

//===========================================================================
//		���C���[Id����G���e�B�e�BId�̃Z�b�g���擾����
//
MINT DLyr::GetEnt(
						MDID		i_idLyr,	// ���C���[Id
						MDIDSET*	o_pGidEnt	// �G���e�B�e�BId�Z�b�g
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	if ( i_idLyr > pCurMdl->m_LyrBf.m_n)
		ms::SysError( MBCstr( "GetScm"), MC_ERR_ID);

	*o_pGidEnt = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GidC;
	return 0;
}

//===========================================================================
//		���C���[�̕\���^���m�������擾
//
MINT DLyr::GetLyrDispMode (
						MDID		i_idWin,	// �E�B���h�EId
						MDID		i_idLyr,	// ���C���[Id
						MINT*		o_iaWD		// �E�B���h�E�\�����n���[�h
												//		0: ���ݒ�
												//		1: �\�� OFF	���n OFF			�~
												//		2: �\�� ON	���n OFF			��
												//		3: �\�� ON	���n ON				��
												//		5: �\�� OFF	���n OFF	Lock	�~p
												//		6: �\�� ON	���n OFF	Lock	��p
												//		7: �\�� ON	���n ON		Lock	��p
				)
{
	MUBYTESET*	pAWDSet;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pAWDSet = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GaWD;
	if ( pAWDSet->m_n == 0)
		*o_iaWD = 0;
	else {
		if ( i_idWin > pAWDSet->m_n) {
			ms::SysError( MBCstr( "GetLyrDispMode"), MC_ERR_ID);
		}
		*o_iaWD = pAWDSet->m_pst[MIDtoHN( i_idWin)];
	}
	return 0;
}

//===========================================================================
//		���C���[�̕\���^���m������ݒ�
//
MINT DLyr::SetLyrDispMode (
						MINT		i_idWin,	// �E�B���h�EId
						MINT		i_idLyr,	// ���C���[Id
						MINT		i_iaWD		// �E�B���h�E�\�����n���[�h
												//		GetLyrDispMode�̐������Q��
				)
{
	MUBYTESET*	pAWDSet;
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pAWDSet = &pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_GaWD;

	if ( i_idWin > pAWDSet->m_sz) {
		pAWDSet->ReSize( i_idWin+3);
	}
	pAWDSet->m_pst[MIDtoHN( i_idWin)] = i_iaWD;
	if ( i_idWin > pAWDSet->m_n)
		pAWDSet->m_n = i_idWin;
	return 0;
}

//===========================================================================
//		���C���[�̕\���^���m������ݒ�
//
MINT DLyr::SetLyrsDispMode (
						MINT		i_idWin,	// �E�B���h�EId
				const	MDIDSET&	i_GidScm,	// ���C���[Id�Z�b�g
						MINT		i_iaWD		// �E�B���h�E�\�����n���[�h
												//		GetLyrDispMode�̐������Q��
				)
{
	MINT	iC;
	MDID	idLyr;
	MdModel* pCurMdl = Mdm::GetCurModel();

	for ( iC=0; iC<i_GidScm.m_n; iC++) {
		idLyr = i_GidScm.m_pst[iC];
		ASSERT( MDISLYR( idLyr));
		SetLyrDispMode ( i_idWin, idLyr, i_iaWD);
	}
	return 0;
}

//===========================================================================
//		�J�����g�E�B���h�E�ɑ΂���\���^���m�����ɂ�郌�C���[�̌���
//
MINT DLyr::SerachLyrDispMode (
						MINT		i_imdD,		// �E�B���h�E�\�����n���[�h�I���R�[�h
												//	�@1 : ڲ԰�\�Ł��̂��̂���
												//	�@2 :         ���Ɓ�
												//	�@3 :         ���Ɓ��Ɓ~
												//	�ȊO:       ���Ɓ��Ɓ~�Ɓ|

						MDIDSET*	o_GidScm,	// ���C���[�Z�b�g
						MINT*		o_itpCurWin	// �J�����g�E�B���h�E�^�C�v( 0:�R�c�A1�F�}�ʁj
				)
{
	MINT	iC;
	MINT	iaWD;
	bool	bD;
	MdModel* pCurMdl = Mdm::GetCurModel();

	//	���C���[�Z�b�g�̌���
	o_GidScm->m_n = 0;

	for ( iC=0; iC<pCurMdl->m_LyrBf.m_n; iC++) {
		iaWD = pCurMdl->m_LyrBf.m_pst[iC].m_GaWD[MIDtoHN( pCurMdl->m_idCurWin)];
		switch ( i_imdD )
		{
		case 1:
			bD = (iaWD & 1) != 0;
			break;
		case 2:
			bD = (iaWD & 3) != 0;
			break;
		case 3:
			bD = (iaWD & 7) != 0;
			break;
		default:
			bD = true;
		}
		if ( bD)
			o_GidScm += MHNtoID( iC);
	}

	//	�J�����g�E�B���h�E�^�C�v
	*o_itpCurWin = pCurMdl->m_WinBf.m_pst[MIDtoHN( pCurMdl->m_idCurWin)].m_itpWin;
	return 0;
}

//===========================================================================
//		���C���[�̃J�����g�\���������擾
//
MINT DLyr::GetLyrCurMaterial (
						MINT	i_idLyr,		// ���C���[Id
						MDFIG*	o_pFig			// �J�����g���C���[�\������
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	*o_pFig = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_CurFig;
	return 0;
}

//===========================================================================
//		���C���[�̃J�����g�\��������ݒ�
//
MINT DLyr::SetlyrCurMaterial (
						MINT	i_idLyr,		// ���C���[Id
						MDFIG&	i_Fig			// ���C���[�\������
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_CurFig = i_Fig;

	return 0;
}

//===========================================================================
//		���C���[�̃f�t�H���g�\���������擾
//
MINT DLyr::GetLyrDefaultMaterial (
						MINT	i_idLyr,		// ���C���[Id
						MDFIG*	o_pFig			// �f�t�H���g���C���[�\������
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	*o_pFig = pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_DfltFig;
	return 0;
}

//===========================================================================
//		���C���[�̃f�t�H���g�\��������ݒ�
//
MINT DLyr::SetlyrDefaultMaterial (
						MINT	i_idLyr,		// ���C���[Id
						MDFIG&	i_Fig			// ���C���[�\������
				)
{
	MdModel* pCurMdl = Mdm::GetCurModel();

	ASSERT( MDISLYR( i_idLyr));

	pCurMdl->m_LyrBf.m_pst[MIDtoHN( i_idLyr)].m_DfltFig = i_Fig;
	return 0;
}

} // namespace MC
