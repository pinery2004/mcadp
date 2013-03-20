//==========================================================================================
//  Copyright(C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdEnt.cpp
//
//		��
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgDefine.h"

#include "MdmFig.h"
#include "MdZukei.h"
#include "MgLib.h"

#include "MdModel.h"
#define DLL_EXPORT_DENT_DO
#include "MdmDB.h"
#include "Mdm.h"

namespace MC
{

//===========================================================================
//		���̐�����̕W������
//
//		�^����ꂽ�G���e�B�e�B�̃��C���[�̈Ӗ��ɏ]���A�������̕K�v�������s���B
//		�������e
//		�E�^����ꂽ�G���e�B�e�B���O���t�B�b�N�E�B���h�E�ɐ����\������B
//		�E�g�ǁh�̏ꍇ�́A�����́g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A������
//			�ꍇ�͕t���֌W��t����B
//		�E�g���h�A�g���h�A�g�J���h�̏ꍇ�́A�����́g�ǁh�Ƃ̐}�`���`�F�b�N���s���A������
//			�ꍇ�͕t���֌W��t���A���́g�ǁh�̍ĕ\�����s���B
//
MINT mdmDEnt::CmdAfterCreate(
						MDIDSET&		i_GidEnt	// �G���e�B�e�B�|�h�c�Z�b�g
				)
{
	return 0;
}

//===========================================================================
//		���̍폜�̕W������
//
//		�^����ꂽ�G���e�B�e�B�̃��C���[�̈Ӗ��ɏ]���A�폜���̕K�v�������s���B
//		�������e
//		�E�^����ꂽ�G���e�B�e�B���폜���A�O���t�B�b�N�E�B���h�E�̕\������������B
//		�E�g�ǁh�̏ꍇ�́A�t���֌W�ɂ���g���h�A�g���h�A�g�J���h�̍ĕ\�����s���B
//		�E�g���h�A�g���h�A�g�J���h�̏ꍇ�́A�t���֌W�ɂ���g�ǁh�̍ĕ\�����s���B
//
MINT mdmDEnt::CmdDelete(
						MDIDSET&	i_GidEnt	// �G���e�B�e�B�|�h�c�Z�b�g
				)
{
	return 0;
}

//===========================================================================
//		���̕��ʂ̕W������
//
//		�^����ꂽ�G���e�B�e�B�̃��C���[�̈Ӗ��ɏ]���A���ʎ��̕K�v�������s���B
//		�������e
//		�E�^����ꂽ�G���e�B�e�B�𕡎ʌ�A���ʐ�̐}�`���ړ����A�O���t�B�b�N�E�B���h�E�ɐ����\������B
//		�E�g�ǁh�̏ꍇ�́A���ʐ�̃G���e�B�e�B�Ɗ����́g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A
//			������ꍇ�͕t���֌W��t����B
//		�E�g���h�A�g���h�A�g�J���h�̏ꍇ�́A���ʐ�̃G���e�B�e�B�Ɗ����́g�ǁh�Ƃ̐}�`���`�F�b�N���s���A
//			������ꍇ�͕t���֌W��t���A���́g�ǁh�̍ĕ\�����s���B
//
//			mode=1�@�̎��@dat�͈ړ��x�N�g��[3]
//			mode=2�@�̎��@dat�͉�]�}�g���b�N�X[12]
//			mode=3�@�̎��@dat�͖ʏ��i�_�{�@���x�N�g���j[6]
//			mode=4�@�̎��@dat�͌��_�{�{��[4]�@���{����1.0������
//
MINT mdmDEnt::CmdCopy(
						MDIDSET&	i_pGidEnt,	// �G���e�B�e�B�|�h�c�Z�b�g
						MINT		i_imdMv,	// �ړ����[�h( 1:���s 2:��] 3:���� 4:�g�� )
						void*		i_pv,		// �ړ��f�[�^
						MDIDSET*	o_pGidEnt	// ���ʐ�@�G���e�B�e�B-ID���X�g
				)
{
	return 0;
}

//===========================================================================
//		���̈ړ��̕W������
//
//		�^����ꂽ�G���e�B�e�B�̃��C���[�̈Ӗ��ɏ]���A�ړ����̕K�v�������s���B
//		�������e
//		�E�^����ꂽ�G���e�B�e�B�̐}�`���ړ����A�O���t�B�b�N�E�B���h�E�ɍĕ\������B
//		�E�g�ǁh�̏ꍇ�́A�t���֌W�ɂ���g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A
//			�����Ȃ��ꍇ�͕t���֌W��؂�A���́g���h�A�g���h�A�g�J���h�̍ĕ\�����s���B
//			�����́g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A������ꍇ�͕t���֌W��
//			�t����B
//		�E�g���h�A�g���h�A�g�J���h�̏ꍇ�́A�t���֌W�ɂ���g�ǁh�Ƃ̐}�`���`�F�b�N���s���A
//			�����Ȃ��ꍇ�͕t���֌W��؂�A���́g�ǁh�̍ĕ\�����s���B
//			�����́g�ǁh�Ƃ̐}�`���`�F�b�N���s���A������ꍇ�͕t���֌W��t���A���́g�ǁh��
//			�ĕ\�����s���B
//			mode=1�@�̎��@dat�͈ړ��x�N�g��[3]
//			mode=2�@�̎��@dat�͉�]�}�g���b�N�X[12]
//			mode=3�@�̎��@dat�͖ʏ��i�_�{�@���x�N�g���j[6]
//			mode=4�@�̎��@dat�͌��_�{�{��[4]�@���{����1.0������
//
MINT mdmDEnt::CmdMove(
						MDIDSET&	i_pGidEnt,	// �G���e�B�e�B�|�h�c�Z�b�g
						MINT		i_imdMv,	// �ړ����[�h( 1:���s 2:��] 3:���� 4:�g�� )
						void*		i_pv		// �ړ��f�[�^
				)
{
	return 0;
}

//===========================================================================
//		���̕ό`��̕W������
//
//		�^����ꂽ�G���e�B�e�B�̃��C���[�̈Ӗ��ɏ]���A�}�`�ό`���̕K�v�������s���B
//		�������e
//		�E�^����ꂽ�G���e�B�e�B���O���t�B�b�N�E�B���h�E�ɍĕ\������B
//		�E�g�ǁh�̏ꍇ�́A�t���֌W�ɂ���g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A
//			�����Ȃ��ꍇ�͕t���֌W��؂�A���́g���h�A�g���h�A�g�J���h�̍ĕ\�����s���B
//			�����́g���h�A�g���h�A�g�J���h�Ƃ̐}�`���`�F�b�N���s���A������ꍇ�͕t���֌W��
//			�t����B
//		�E�g���h�A�g���h�A�g�J���h�̏ꍇ�́A�t���֌W�ɂ���g�ǁh�Ƃ̐}�`���`�F�b�N���s���A
//			�����Ȃ��ꍇ�͕t���֌W��؂�A���́g�ǁh�̍ĕ\�����s���B
//			�����́g�ǁh�Ƃ̐}�`���`�F�b�N���s���A������ꍇ�͕t���֌W��t���A���́g�ǁh��
//			�ĕ\�����s���B
//
MINT mdmDEnt::CmdAfterModify(
						MDIDSET&	i_GidEnt	// �G���e�B�e�B�|�h�c�Z�b�g
				)
{
	return 0;
}

//===========================================================================
//		���}�`�̋����\���i�G�R�[�o�b�N�j
//
//		�w�蕨�̋����\���i�G�R�[�o�b�N�j���s���B
//		�����\���́ANonHighlighting�ANonHighlightingAll�ŉ�������邩�ACmdMove���ōĕ\�������܂�
//		�p������B
//		�����\������CmdMove���ōĕ\������ꍇ�́AClearHighlightingList�ŋ����\�����s�����G���e�B�e�B��
//		���X�g���J������K�v������B
//
MINT mdmDEnt::EchoHighlighting(
						MDIDSET&	i_GidEnt	// �G���e�B�e�B�|�h�c�Z�b�g
				)
{
	return 0;
}

//===========================================================================
//		�����\���i�G�R�[�o�b�N�j�����ɖ߂��i�P�j
//
//		�w��G���e�B�e�B��EchoHighlighting�ŋ����\������Ă���ꍇ�ɕ\����߂��B
//		�w��G���e�B�e�B�������\������Ă��Ȃ��ꍇ�ɂ͉����s��Ȃ��B�i�߂�l���O�j
//
MINT mdmDEnt::NonHighlighting(
						MDID		i_idEnt		// �G���e�B�e�B�|�h�c
				)
{
	return 0;
}

//===========================================================================
//		�����\���i�G�R�[�o�b�N�j�����ɖ߂�
//
//		EchoHighlighting�ŋ����\������Ă��镨�̕\����S�Ė߂��B
//
MINT mdmDEnt::NonHighlightingAll()
{
	return 0;
}

//===========================================================================
//		�����\���i�G�R�[�o�b�N�j�Z�b�g�̋����N���A�i�ĕ\���Ȃ��j
//
//		EchoHighlighting�ŋ����\�������G���e�B�e�B�̃��X�g���J������B
//		�\���͍s��Ȃ��B
//
//		�����\������CmdMove���ōĕ\�������ꍇ�́A�{�֐��ŋ����\�����s�����G���e�B�e�B�̃��X�g��
//		�J������K�v������B
//
MINT mdmDEnt::ClearHighlightingSet()
{
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̐���
//
//		���C���[Id���w�肵�āA���̃��C���[Id�ɕt������G���e�B�e�B�𐶐�����B
//		�w�背�C���[Id�����݂��Ȃ��ꍇ��A�G���e�B�e�B�̐����Ɏ��s�����ꍇ��o_pidEnt=0�ŕԂ��B
//
MINT mdmDEnt::CreateEnt(
						MDID		i_idLyr,	// ���C���[ID
						MDID*		o_pidEnt,	// �G���e�B�e�BID
						MINT		i_sz		// �����O���[�vId�o�b�t�@�T�C�Y /*=10*/
				)
{
	mdmEnt*	pEnt;

	ASSERT( MDISLYR( i_idLyr));

	// EntBf���󂫂�ID���擾���A�G���e�B�e�B�̗̈��݂���
	//
	if ( Mdm::GetCurModel()->m_EntBf.m_idSpaceLast == 0) {
		// �폜���ċ󂫂ɂȂ��Ă���ID���Ȃ��ꍇ�͍ŏIID+1���g�p����
		Mdm::GetCurModel()->m_EntBf ++;
		*o_pidEnt = Mdm::GetCurModel()->m_EntBf.m_n;
		pEnt = &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( *o_pidEnt)];

	} else {
		// �폜���ċ󂫂ɂȂ��Ă���ID������ꍇ�͂���ID���g�p����
		ASSERT( Mdm::GetCurModel()->m_EntBf.m_nidSpace >= 1);

		*o_pidEnt = Mdm::GetCurModel()->m_EntBf.m_idSpaceLast;
		pEnt = &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( *o_pidEnt)];

		// �󂫃G���A�ւ�ID����߂�
		Mdm::GetCurModel()->m_EntBf.m_idSpaceLast = MDSPACEBEFORE( pEnt);
		if ( Mdm::GetCurModel()->m_EntBf.m_idSpaceLast)
			MDSPACENEXT( &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_EntBf.m_idSpaceLast)]) = 0;
		Mdm::GetCurModel()->m_EntBf.m_nidSpace--;
	}

	// �G���e�B�e�BID�ɎqID�̐ݒ�p�̈���m�ۂ���
	pEnt->Alloc( i_sz);

	// ���C���[�Ƃ̃����N��t����
//	pEnt->m_SC.m_idP = i_idLyr;
	pEnt->m_idP = i_idLyr;
	Mdm::GetCurModel()->m_LyrBf.m_st[MIDtoHN( i_idLyr)].m_GidC += (*o_pidEnt);

	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̍폜
//
MINT mdmDEnt::DeleteEnt(						//
						MDID		i_idEnt		// �G���e�B�e�BId
				)
{
	mdmEnt*	pEntB;								// ���O�ɍ폜�����G���e�B�e�B
	mdmEnt*	pEntC;								// �폜�G���e�B�e�B
	MDID		idLyr;

	ASSERT( i_idEnt >= 1 && i_idEnt <= Mdm::GetCurModel()->m_EntBf.m_n);

	// ���C���[����̃����N���폜����
	pEntC = &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)];
//	idLyr = pEntC->m_SC.m_idP;
	idLyr = pEntC->m_idP;
	Mdm::GetCurModel()->m_LyrBf.m_st[MIDtoHN( idLyr)] -= i_idEnt;
	// ���̑��̃����N���폜����

	// �폜�����蓖�đ҂��̋󂫃G���e�B�e�B���ɒǉ�
	Mdm::GetCurModel()->m_EntBf.m_nidSpace++;
	// �G���e�B�e�B�폜�t���O�ݒ�Ǝg�p�G���A�J��
	MDSPACEID( pEntC) = MDID_DELETE;
	pEntC->Free();

	// �󂫃G���A�����N�ɒǉ�
	// ���O�ɍ폜�����G���e�B�e�B�̎��̃G���e�B�e�B�Ƃ���
	if ( Mdm::GetCurModel()->m_EntBf.m_idSpaceLast) {
		pEntB = &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( Mdm::GetCurModel()->m_EntBf.m_idSpaceLast)];
		MDSPACENEXT( pEntB) = i_idEnt;
	}
	// �󂫃G���A�����N�̐擪�Ƀ����N�t����
	MDSPACEBEFORE( pEntC) = Mdm::GetCurModel()->m_EntBf.m_idSpaceLast;
	MDSPACENEXT( pEntC) = 0;
	Mdm::GetCurModel()->m_EntBf.m_idSpaceLast = i_idEnt;
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�ɐ}�`����ݒ肷��
//
//		�}�`��񂪕��i�z�u�̏ꍇ�́A�G���e�B�e�B�ɕ��i���֌W�t����B
//
MINT mdmDEnt::SetFigPmt(
						MDID		i_idEnt,	// �G���e�B�e�B-ID
						MDPMT&		i_Pmt		// �}�`���
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �}�`�����G���e�B�e�B�ɃR�s�[����
	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_Fig = i_Pmt;
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�ɐ}�`����ݒ肷��
//
//		�}�`��񂪕��i�z�u�̏ꍇ�́A�G���e�B�e�B�ɕ��i���֌W�t����B
//
MINT mdmDEnt::SetFig(
						MDID		i_idEnt,	// �G���e�B�e�B-ID
						MDFIG&		i_Fig		// �}�`���
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �}�`�����G���e�B�e�B�ɃR�s�[����
	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_Fig = i_Fig;
	return 0;
}

//===========================================================================
//		�G���e�B�e�C�ɕ��ޔz�u�̐ݒ�
//
//		�G���e�B�e�C�Ɏw�蕔�i��z�u���镔�ޔz�u�v���~�e�B�u��ݒ肷��B
//		�z�u��ƕ����A�傫���͔z�u���W�n�}�g���b�N�X�Ŏw�肷��B
//
MINT mdmDEnt::SetPartPlc (
						MDID		i_idEnt,	// �G���e�B�e�CID
						MgMat3E*		i_pmat,		// �z�u���W�n�}�g���b�N�X
						MDID		i_idB		// ���iID
				)
{
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̐}�`���𓾂�
//
//		�}�`��񂪖��ݒ�̏ꍇ�́Ao_pFig���O��Ԃ��B
//
MINT mdmDEnt::GetFig(
						MDID		i_idEnt,	// �G���e�B�e�B-ID
						MDFIG*		o_pFig		// �}�`���
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �}�`�����G���e�B�e�B����R�s�[����
	*o_pFig = Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_Fig;
	return 0;
}

//===========================================================================
//		�G���e�B�e�C�̐}�`����ύX
//
MINT mdmDEnt::CngZukei(
						MDID		i_idEnt,	// �G���e�B�e�CID
						MDFIG&		i_Fig		// �}�`���
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �}�`�����G���e�B�e�B�ɃR�s�[����
	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_Fig = i_Fig;
	return 0;
}

//===========================================================================
//		�����i�|�C���^�j���G���e�B�e�B�ɐݒ肷��
//
MINT mdmDEnt::SetAttr(
						MDID		i_idEnt,	// �G���e�B�e�B-ID
						MSHORT		i_iTpAtr,	// �����^�C�v
						void*		i_pAtr		// ����
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �������G���e�B�e�B�ɃR�s�[����
	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_iTpAtr = i_iTpAtr;
	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_pAtr = i_pAtr;
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̑����i�|�C���^�j�𓾂�
//
void* mdmDEnt::GetAttr(
						MDID		i_idEnt	// �G���e�B�e�B-ID
				)
{
	ASSERT( MDISENT( i_idEnt));

	// �������G���e�B�e�B���瓾��
	return Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_pAtr;
}

//===========================================================================
//		�G���e�B�e�B���烌�C���[Id�𓾂�
//
//		�G���e�B�e�B���w�肵�Ă��̂��̃G���e�B�e�B���t�����郌�C���[Id�𓾂�B
//		���C���[Id��������Ȃ��ꍇ�́Ao_pidLyr���O��Ԃ��B
//
MINT mdmDEnt::GetLyrId(
						MDID		i_idEnt,	// �G���e�B�e�BID
						MDID*		o_pidLyr	// ���C���[ID
				)
{
	*o_pidLyr = Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt)].m_idP;
	return 0;
}

//===========================================================================
//		�J�����g�̃��C���[�ɐ}�`�����G���e�B�e�B�����i�쐬�̂݁A�\�����͂��Ȃ��j
//
//		�J�����g���C���[�Ɏw�肳�ꂽ�}�`�����G���e�B�e�B�𐶐�����B
//		�J�����g���C���[���������̏ꍇ�́A���C���[�̐������s���B
//		�O���t�B�b�N�E�B���h�E�ւ̕\���͍s��Ȃ��B
//
//
MINT mdmDEnt::CreateFigEnt(
						MDFIG&		i_stFig,	// �}�`���
						MDID*		o_pidEnt	// �G���e�B�e�B-ID
				)
{
	// �J�����g���C���[���������̏ꍇ�̓��C���[�𐶐�
	if ( Mdm::GetCurModel()->m_idCurLyr == 0) {
		DLyr::CreateLyr( Mdm::GetCurModel()->m_idCurScm, Mdm::GetCurModel()->m_idCurGrp, &Mdm::GetCurModel()->m_idCurLyr, 10);
	}
	// �J�����g���C���[�Ƀ����N�����G���e�B�e�B�𐶐�
	mdmDEnt::CreateEnt( Mdm::GetCurModel()->m_idCurLyr, o_pidEnt, 0);
	// �}�`���R�s�[
	mdmDEnt::SetFig( *o_pidEnt, i_stFig);
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̃��C���[�ύX�i���C���[�Ԉړ��j
//
//		�w��̃G���e�B�e�B���w�肳�ꂽ���C���[�Ɉړ�����B
//		���̃��C���[�ƈړ���̃��C���[�ŃO���[�v���قȂ��Ă����ꍇ�́A
//		�ړ�����G���e�B�e�B�̐}�`�̐e���W�n��t���ւ��A�}�`�f�[�^�̍��W�ϊ����s���B
//		�i���ʁA����W�n���猩���}�`�̈ʒu�͕ς��Ȃ��B�j
//
MINT mdmDEnt::CngLyr(
						MDIDSET&	i_GidEntF,	// �G���e�B�e�BID�Z�b�g
						MDID		i_idLyrT	// ���C���[ID
				)
{
	MINT	iC;
	MDID	idEntF;								// �ύX��
	MDID	idLyrF;
	MDID	idGrpF;
	MDID	idGrpFB;
	MDID	idGrpT;								// �ύX��
	MgMat3E* pMTransT;							// �ύX��O���[�v�̍��W�ϊ��}�g���b�N�X
	MgMat3E	MTransTR;							// �ύX��O���[�v�̍��W�t�ϊ��}�g���b�N�X
	MgMat3E	MTrans;								// �ύX��O���[�v����ύX��O���[�v�ւ̍��W�ϊ��}�g���b�N�X

	// �ύX��̃��C���[��������O���[�v�̍��W�t�ϊ��}�g���b�N�X�����߂�
	idGrpT = Mdm::GetCurModel()->m_LyrBf.m_st[MIDtoHN( i_idLyrT)].m_idP1;
	pMTransT = &Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( idGrpT)].m_MTrans;
	MTransTR = MGeo::Mat3Inv( *pMTransT);

	// �w��S�G���e�B�e�B�̃��C���[��ύX����
	idGrpFB = MDC_ID_NULL;
	for ( iC=0; iC<i_GidEntF.m_n; iC++) {
		// �ύX���̃��C���[�ƃO���[�v�����߂�
		idEntF = i_GidEntF.m_st[iC];
		idLyrF = Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEntF)].m_idP;
		idGrpF = Mdm::GetCurModel()->m_LyrBf.m_st[MIDtoHN( idLyrF)].m_idP1;
		// ���C���[�ɕω���������̂̂ݕύX����
		if ( idLyrF != i_idLyrT) {
			// �O���[�v�ɕω���������̂̂ݍ��W�ϊ�����
			if ( idGrpT != idGrpF) {
				// �ϊ����O���[�v�����O�̕ϊ����O���[�v�ƈقȂ�ꍇ�ɂ͍��W�ϊ��}�g���b�N�X�����߂�
				if ( idGrpF != idGrpFB) {
					idGrpFB = idGrpF;
					MTrans = Mdm::GetCurModel()->m_GrpBf.m_st[MIDtoHN( idGrpF)].m_MTrans;
					MTrans *= MTransTR;
				}
				// �G���e�B�e�B�̍��W��ϊ�����
				DZukei::MdzTrans( MTrans, Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEntF)].m_Fig, 
								  &Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEntF)].m_Fig);
			}
			// ���C���[��ϊ�����
			Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEntF)].m_idP = i_idLyrT;
		}
	}
	return 0;
}

//===========================================================================
//		�G���e�B�e�B�̃��C���[�ԃR�s�[
//
//		�w��̃G���e�B�e�B���w�肳�ꂽ���C���[�ɕ��ʂ���B
//		lker=0�̏ꍇ�́A���̃��C���[�ɕ��ʂ���B
//		���̃��C���[�ƕ��ʐ�̃��C���[�ŃO���[�v���قȂ��Ă����ꍇ�́A
//		���ʌ�̃G���e�B�e�B�̐}�`�̐e���W�n�͕��ʐ�̃O���[�v�̍��W�n�ƂȂ�B
//		�}�`�f�[�^�̍��W�ϊ����s���B�i���ʁA����W�n���猩���}�`�̈ʒu�͕ς��Ȃ��B�j
//
MINT mdmDEnt::CpyEnt(
						MDIDSET&	i_GidEnt,	// �G���e�B�e�B-ID�Z�b�g
						MDID		i_idLyr,	// ���C���[ID
						MDIDSET*	o_pGidEnt	// �R�s�[�G���e�B�e�B-ID�Z�b�g
				)
{
	MINT		iC;
	MDID		idEnt;
	mdmEnt	entW;

	// �w��S�G���e�B�e�B���R�s�[����
	o_pGidEnt->m_n = 0;
	for ( iC=0; iC<i_GidEnt.m_n; iC++) {
		// �R�s�[���̃G���e�B�e�B�𓾂�
		entW = Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_GidEnt[iC])];
		// ���G���e�B�e�B�𐶐�����
		mdmDEnt::CreateEnt( 0, &idEnt, 0);
		Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEnt)] = entW;
	}

	// �R�s�[�G���e�B�e�B�̃��C���[��ύX����
	mdmDEnt::CngLyr(	*o_pGidEnt,	i_idLyr);
	return 0;
}

//===========================================================================
//		�a�n�w���̐}�`Dpr�𓾂�
//
//		�E�B���h�E�ɕ\������Ă���}�`�̓��Abox�͈͓��Ɋ��S��܂����}�`�����G���e�B�e�B�𓾂�B
//		box�̍ŏ��_�E�ő�_�̓J�����g���W�n�̍��W�l�ŕԂ��B
//
MINT mdmDEnt::GetEntInBox(
						MDID		i_idWin,	// �E�B���h�EID
						MgMinMaxR3&	i_rMnmx,	// box���W�l�i�ŏ��E�ő�_�j
						MDIDSET*	o_pGidEnt	// �G���e�B�e�B-ID�Z�b�g
				)
{
	MDIDSET	GidLyr;
	MDIDSET	GidEnt;

	MINT	iCl;
	MINT	iCe;
	MDID	idEnt;

	MgMinMaxR3	rMnMxEnt;

	o_pGidEnt->m_n = 0;
	DLyr::GetLyrIdAll( &GidLyr);
	for ( iCl=0; iCl<GidLyr.m_n; iCl++) {
		DLyr::GetEnt( GidLyr.m_st[iCl], &GidEnt);
		for ( iCe=0; iCe<GidEnt.m_n; iCe++) {
			idEnt = GidEnt.m_st[iCe];
//			rMnMxEnt = Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( idEnt)].m_Fig.m_pPmts->m_Mmx;
			if ( MGeo::ChkPt3InMMR3( rMnMxEnt.min, i_rMnmx) &&
				 MGeo::ChkPt3InMMR3( rMnMxEnt.max, i_rMnmx) ) {
				(*o_pGidEnt) += idEnt;
			}
		}
	}
	return 0;
}

//===========================================================================
//		�֌W�t��
//
//		ker1��ker2���w��̊֌W�Ŋ֌W�t����B
//		���̊֌W��Search�֐��Ō����ł���B
//
//		�֌WID�ɂ��ẮA�ʎ��֌W�ꗗ���Q�ƁB
//
MINT mdmDEnt::Link(
						MDID		i_idEnt1,	// �G���e�B�e�BID1
						MINT		i_icdRef1,	// �G���e�B�e�BID1����G���e�B�e�BID2�ւ̊֌W�R�[�h
						MDID		i_idEnt2,	// �G���e�B�e�BID2
						MINT		i_icdRef2	// �G���e�B�e�BID2����G���e�B�e�BID1�ւ̊֌W�R�[�h
				)
{
//	Mdm::GetCurModel()->m_EntBf.m_st[MIDtoHN( i_idEnt1)]
	return 0;
}

//===========================================================================
//		�֌W�؂�
//
//		ker1��ker2�̊Ԃɕt�����Ă���w��̊֌W��؂�B
//
//		�֌WID�ɂ��ẮA�ʎ��֌W�ꗗ���Q�ƁB
//
MINT mdmDEnt::DeLink(
						MDID		i_idEnt1,	// �G���e�B�e�BID1
						MINT		i_icdRef1,	// �G���e�B�e�BID1����G���e�B�e�BID2�ւ̊֌W�R�[�h
						MDID		i_idEnt2,	// �G���e�B�e�BID2
						MINT		i_icdRef2	// �G���e�B�e�BID2����G���e�B�e�BID1�ւ̊֌W�R�[�h
				)
{
	return 0;
}

//===========================================================================
//		�֌W����
//
//		ker1�Ɏw��̊֌W�Ŋ֌W�t���Ă���̃��X�g�𓾂�B
//
//		�֌WID�ɂ��ẮA�ʎ��֌W�ꗗ���Q�ƁB
//
MINT mdmDEnt::Srch(
						MDID		i_idEnt,	// �G���e�B�e�BID
						MINT		i_icdRef,	// �G���e�B�e�BID����̊֌W�R�[�h
						MDIDSET*	o_pGidEnt	// �G���e�B�e�BID�Z�b�g
				)
{
	return 0;
}

//===========================================================================
//		KCB�̐���
//
//		�L�[�����̂��߂�KCB�𐶐�����B
//
MINT mdmDEnt::KeyInit(
						MDID*		o_pidKCB	// KCB-ID
				)
{
	return 0;
}

//===========================================================================
//		KCB�̐���
//
//		�w�肳�ꂽ�L�[�Ŋ֌W�t����B
//		���̊֌W��KeySearch�֐��Ō����ł���B
//
MINT mdmDEnt::KeyLink(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// �L�[
						MDID		i_idInf		// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		�L�[�ł̊֌W�؂�
//
//		�w�肳�ꂽ�L�[�ł̊֌W��؂�B
//
MINT mdmDEnt::KeyDeLink(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// �L�[
						MDID		i_idInf		// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		�L�[�ł̌���
//
//		�w�肳�ꂽ�L�[�Ŋ֌W�t���Ă���G���e�B�e�C�𓾂�B
//
MINT mdmDEnt::KeySearch(
						MDID		i_idKCB,	// KCB-ID
						MCHAR		i_sKey[],	// �L�[
						MDID*		o_pidInf	// Information-ID
				)
{
	return 0;
}

//===========================================================================
//		KCB�̍폜
//
//		�L�[�����̂��߂�KCB���폜����B
//
MINT mdmDEnt::KeyDelete(
						MDID		i_idKCB		// KCB-ID
				)
{
	return 0;
}

//===========================================================================
//		�A�N�Z�X���[�g�̖₢���킹	
//
//		�L�[���[�h���w�肵�ăA�N�Z�X���[�g�ɓo�^����Ă���Information�𓾂�B
//
MINT mdmDEnt::GetAccessRoot(
						MCHAR		i_sKey[],	// �L�[
						MDID*		o_pidInf	// Information-ID
												//	�i�L�[���[�h�����݂��Ȃ��ꍇ�͂O�j
				)
{
	return 0;
}

//===========================================================================
//		�A�N�Z�X���[�g�̓o�^	
//
//		�L�[���[�h���w�肵�ăA�N�Z�X���[�g��Information-ID��o�^����B
//		�w�肳�ꂽ�L�[���[�h�����݂����ꍇ�́A�㏑������B
//
MINT mdmDEnt::PutAccessRoot(
						MCHAR		i_sKey[],	// �L�[
						MDID*		i_idInf		// Information-ID
												//	�i�L�[���[�h�����݂��Ȃ��ꍇ�͂O�j
				)
{
	return 0;
}

//===========================================================================
//		�A�N�Z�X���[�g�̍폜	
//
//		�w�肳�ꂽ�L�[���[�h�̃A�N�Z�X���[�g�̓o�^���폜����B
//		�w�肳�ꂽ�L�[���[�h���o�^����Ă��Ȃ��ꍇ�̓G���[�B
//
MINT mdmDEnt::DeleteAccessRoot(
						MCHAR		i_sKey[]	// �L�[
				)
{
	return 0;
}

} // namespace MC
