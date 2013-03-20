//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdDispControl.cpp
//
//		�E�B���h�E
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgMat.h"

#include "MdModel.h"

namespace MC
{

//===========================================================================
//		�e���|�����\��
//
//		�w�肳�ꂽ�}�`���̃e���|�����\�����s���B
//
MINT	MddDispTemp (
						MINT		i_ifPick,	// �s�b�N�\�t���O
												//	0:�s�b�N�Ȃ�
												//	1:�s�b�N����
						MDID		i_idWin,	// �\������E�B���h�E
												//	0:�S�ẴE�B���h�E
												//	0�ȊO:�E�B���h�EID
						MDFIG&		i_pFig,		// �}�`���
						MDID*		o_pidDisp	// �\���h�c
				)
{
	return 0;
}

//
//===========================================================================
//		�e���|�����\���폜
//
//		�w�肳�ꂽ�e���|�����\�����폜����B
//
MINT	MddEraseTemp (
						MDIDSET&	i_GidDisp	// �\���h�c�Z�b�g
				)
{
	return 0;
}

//
//===========================================================================
//		���o�[�o���h�̕\��
//
//		�w�肳�ꂽ�}�`���̃��o�[�o���h�\�����s���B
//
//		���o�[�o���h�\���́AXOR�ŕ\�����s���B
//		���̂��߁A�w�肷��}�`���̒��ŏd�Ȃ����������Ɓi�E�B���h�E�̎��_���猩���ꍇ�j
//		���̐����������Ă��܂��B
//		���̂悤�Ȑ}�`�������o�[�o���h�\������ꍇ�́A�d���`�F�b�N������w�肷��K�v��
//		����B
//		���o�[�o���h�\���́A���C���[�t���[���ɂ��\���݂̂œh��ׂ��͕s�B
//
MINT	MddDispRubberband (
						MDIDSET&	i_GidDisp,	// �t���O
												//	0:�d���`�F�b�N�Ȃ�
												//	1:�d���`�F�b�N����
						MDID		i_idWin,	// �\������E�B���h�E
												//	0:�S�ẴE�B���h�E
												//	0�ȊO:�E�B���h�EID
						MDFIG&		i_pFig,		// �}�`���
						MDID*		o_pidDisp	// �\���h�c
				)
{
	return 0;
}

//
//===========================================================================
//		���o�[�o���h�̕\���폜
//
//		�w�肳�ꂽ�}�`���̃��o�[�o���h�\�����s���B
//
//		�w�肳�ꂽ���o�[�o���h�\�����폜����B
//
MINT	MddEraseRubberband (
						MDID		i_idDisp	// �\���h�c
				)
{
	return 0;
}

//
//===========================================================================
//		���o�[�o���h�x�����[�h�̖₢���킹
//
//		���o�[�o���h�x�����[�h��₢���킹��B
//		���o�[�o���h�\������ꍇ�ɂ͉��L�̂悤�ɒx�����[�h��ݒ肷�邱�ƁB
//
//		ex)
//
//		mode = DispControl:: GetRubberbandDelayMode (  )  // �x�����[�h�̖₢���킹
//
//		�@while�i�E�E�j {
//		�@if ( mode == 0 ) DispControl:: SetRubberbandDelayMode ( 1 )  // �x�����[�h=ON
//		  Inp::PointSnap ( �E�E�E)
//		�@DispControl:: DispRubberband (�E�E�E)  // ���o�[�o���h�̕\��
//		�@if ( mode == 0 ) DispControl:: SetRubberbandDelayMode ( 0 )  // �x�����[�h=OFF
//
//		 }
//
MINT	MddGetRubberbandDelayMode ()			// �x�����[�h
												//	0:off
												//�@1:on
{
	return 0;
}

//
//===========================================================================
//		���o�[�o���h�x�����[�h�̐ݒ�
//
//		���o�[�o���h�x�����[�h��ݒ肷��B
//
MINT	MddSetRubberbandDelayMode (
						MDID		i_idDisp	// �\���h�c
				)
{
	return 0;
}

//
//===========================================================================
//		�\���}�`�̎��o��
//
//		�w�肳�ꂽ�E�B���h�E�ɕ\������Ă���c�����̐}�`��
//		���̃E�B���h�E�̎��_�n�ł̍��W�l�œ���B�i�Q�����j
//
MINT	MddGetViewZukei (
						MDIDSET&	i_pGidDisp,	// �E�B���h�E�h�c
						MDID		i_idDpr,	// �}�`DPR
						MDFIG*		o_pFig		// �}�`���
				)
{
	return 0;
}

//
//===========================================================================
//		���̕\����ON/OFF��ݒ肷��
//
//		�w�肳�ꂽ�E�B���h�E�ɕ\������Ă���}�`�c�����̕\���n�m�^�n�e�e��ݒ肷��B
//
//		�@���̊֐��ł͂n�m�^�n�e�e��ݒ肷�邾���Ȃ̂ŁA��ʂɔ��f�������ꍇ�́A
//		�@Window::Refresh�@���ĂԕK�v������B
//
//		������
//		����́u���I�����}�ʁv�̑��A���ȊO�̃��C���[�ł́A�A�N�\���A�����}�A���ʓ���
//		3�����E�B���h�E�̕\���������L�ɂ��Ă���B���̂��ߏ�L���C���[���R�����E�B���h�E��
//		�w�肷��ƁA�R�����E�B���h�E�S�ċ��ʂɍ�p����B
//
MINT	MddSetDprDispMode (
						MDID		i_idWin,	// �E�B���h�E�h�c
						MDID		i_idLyr,	// ���C���[Ker
						MDID		i_idDpr,	// �}�`Dpr
						MINT		i_ifDisp	// �\���t���O
												//�@0:�\��OFF
												//�@1:�\��ON
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�͈͂Ɋ܂܂�郌�C���[�ꗗ�𓾂�
//
//		�w�肳�ꂽ�E�B���h�E�͈͂Ɋ܂܂��\������Ă��镨�̃��C���[�ꗗ�𓾂�B
//
//		���E�B���h�E�͈͂��኱�傫�߂͈̔͂�ێ����Ă��邽�߁A���ۂ̕\������Ă��镨���
//		���߂̃��X�g���Ԃ邱�Ƃ�����B
//
//		���\������Ă��镨�iDpr�j�͂��̊֐��œ���ꂽ���C���[���w�肵�āA
//		GetDprList�@���瓾��B
//
MINT	MddGetLyrList (
						MDID		i_idWin,	// �E�B���h�E�h�c
						MDIDSET*	o_pGidLyr	// ���C���[Ker
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�͈͂Ɋ܂܂�镨�ꗗ�𓾂�
//
//		�w�肳�ꂽ�E�B���h�E�͈͂Ɋ܂܂�A�w�肳�ꂽ���C���[�ɑ�����A
//		�\������Ă��镨�̈ꗗ�𓾂�B
//
//		���E�B���h�E�͈͂��኱�傫�߂͈̔͂�ێ����Ă��邽�߁A
//		���ۂ̕\������Ă��镨��葽�߂̃��X�g���Ԃ邱�Ƃ�����B
//
//		���w�肷�郌�C���[�́AGetLyrList�@���瓾��B
//
MINT	MddGetDprList (
						MDID		i_idWin,	// �E�B���h�E�h�c
						MDID		i_idLyr,	// ���C���[Ker
						MDFIG*		o_pFig		// �}�`Dpr

				)
{
	return 0;
}

//
//===========================================================================
//		�w��}�`�̎��_�n�ł̂a�n�w���𓾂�
//
//		�w�肳�ꂽ�E�B���h�E�ł̐}�`Dpr��BOX�𓾂�B
//
MINT	MddGetBoxDpr (
						MDID		i_idWin,	// �E�B���h�E�h�c
						MDID		i_idLyr,	// ���C���[Ker
						MDFIG*		o_pFig,		// �}�`Dpr
						MgRect3*	o_pRect		// BOX�i�����_�A�E��_�j
												// �i�w�肳�ꂽ�E�B���h�E�̎��_���W�n�ł̍��W�l�j
				)
{
	return 0;
}

//
//===========================================================================
//		�w�肳�ꂽ�E�B���h�E�̕\�����S�̂̎��_�n�ł̂a�n�w�𓾂�
//
//		�w�肳�ꂽ�E�B���h�E�ł̐}�`Dpr��BOX�𓾂�B
//
MINT	MddGetBoxAllDpr (
						MDID		i_idWin,	// �E�B���h�E�h�c
						MgRect3*	o_pRect		// BOX�i�����_�A�E��_�j
												// �i�w�肳�ꂽ�E�B���h�E�̎��_���W�n�ł̍��W�l�j
				)
{
	return 0;
}

} // namespace MC