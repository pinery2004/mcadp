//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdHyo.cpp
//
//		�E�B���h�E
//
//
//  K.Matsu           01/19/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgPolygon.h"
#include "MgMat.h"

#include "MdModel.h"

namespace MC
{

//===========================================================================
//		�E�B���h�E�̒�`
//
//		�E�B���h�E�̒�`���s���B
//		���W�l�͊ǖʂ̍�������_�Ƃ����l���w�肷��B�iX,Y���ɉE���֌������ā{�����j
//		�����i�I�[�v�����́j�E�B���h�E�ɑ΂��ẮA�����ɐݒ�l�͔��f����Ȃ��B
//		����I�[�v��������L���ɂȂ�B
//
MINT	MdhPoint (
						MDID		i_idHyo,	// �\NO
						CPoint		i_ptSt,		// �n�_
						CPoint		i_ptSz		// �傫��
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E��`�̃N���A
//
//		�E�B���h�E�̒�`���폜����
//		�\NO��ɑ��݂���S�Ă̒�`���N���A����܂��B
//
MINT	MdhClearDefWindow(
						MDID		i_idHyo		// �\NO
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E�ʒu�E�傫���̖₢���킹
//
//		�\NO�ɑ΂���ʒu�E�傫���̖₢���킹�B
//		�iDefWindow�Œ�`���ꂽ�ʒu�E�傫�����Ԃ�B�j
//
//		������
//		�ʏ�A�E�B���h�E�ʒu�E�傫���́AGetWindowPos�œ��邱�Ƃ��ł���B
//		�A���A���[�U�ɂ��A�\�����T�C�Y���ꂽ�ꍇ
//		���ۂ̑傫���ƁAGetWindowPos�œ�����傫�����قȂ邱�Ƃ�����B
//		���̂悤�ȏꍇ�ɁAGetPhysicalWindowPos���g�p���Ď��ۂ̃T�C�Y�𓾂�B
//		�\�����T�C�Y���ꂽ�ꍇ�́AGetPhysicalWindowPos�ŃT�C�Y�𓾂���A
//		���̃T�C�Y��DefWindow�ōĒ�`���Ă����K�v������B
//
MINT	MdhGetWindowPos(
						MDID		i_idHyo,	// �\NO
						CPoint*		o_ptSt,		// �n�_
						CPoint*		o_ptSz		// �傫��
				)
{
	return 0;
}

//===========================================================================
//		�����E�B���h�E�ʒu�E�傫���̖₢���킹
//
//		�\NO�ɑ΂���A���ۂ̈ʒu�E�傫���̖₢���킹�B
//
//		������
//		�ʏ�A�E�B���h�E�ʒu�E�傫���́AGetWindowPos�œ��邱�Ƃ��ł���B
//		�A���A���[�U�ɂ��A�\�����T�C�Y���ꂽ�ꍇ
//		���ۂ̑傫���ƁAGetWindowPos�œ�����傫�����قȂ邱�Ƃ�����B
//		���̂悤�ȏꍇ�ɁAGetPhysicalWindowPos���g�p���Ď��ۂ̃T�C�Y�𓾂�B
//		�\�����T�C�Y���ꂽ�ꍇ�́AGetPhysicalWindowPos�ŃT�C�Y�𓾂���A
//		���̃T�C�Y��DefWindow�ōĒ�`���Ă����K�v������B
//
MINT	MdhPointPickSnap (
						MDID		i_idHyo,	// �\NO
						CPoint*		o_ptSt,		// �n�_
						CPoint*		o_ptSz		// �傫��
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E�^�C�v�̐ݒ�
//
//		�\�^�C�v�ꗗ
//		1:�A�v���P�[�V�����E�B���h�E      �i�V�X�e���p�B���[�U�[�g�p�s�j
//		2:�E�B���h�E                      �i�V�X�e���p�B���[�U�[�g�p�s�j
//		3:�\�P        �ړ��Ȃ�,����UP�Ȃ�
//		4:�\�Q        �ړ��Ȃ�,����UP����
//		5:�\�R        �ړ�����,����UP�Ȃ�
//		6:�\�S        �ړ�����,����UP����
//		7:���j���[                        �i�V�X�e���p�B���[�U�[�g�p�s�j
//
MINT	MdhDefWindowType(
						MDID		i_idHyo,	// �\NO
						MINT		i_iTp,		// �\�^�C�v�i�P�`�V�j���L�Q��
						MINT		i_iRs,		// �T�C�Y�ύX�t���O�i�O:�Ȃ��^�P�F����j
						MINT		i_iTt,		// �^�C�g���t���O�i�O:�Ȃ��^�P�F����j
						MINT		i_iIc,		// �A�C�R�����t���O�i�O:�Ȃ��^�P�F����j
						MINT		i_iMx		// �ő剻�t���O�i�O:�Ȃ��^�P�F����j
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E�^�C�v�̖₢���킹
//
//		�\�^�C�v�ꗗ
//		1:�A�v���P�[�V�����E�B���h�E      �i�V�X�e���p�B���[�U�[�g�p�s�j
//		2:�E�B���h�E                      �i�V�X�e���p�B���[�U�[�g�p�s�j
//		3:�\�P        �ړ��Ȃ�,����UP�Ȃ�
//		4:�\�Q        �ړ��Ȃ�,����UP����
//		5:�\�R        �ړ�����,����UP�Ȃ�
//		6:�\�S        �ړ�����,����UP����
//		7:���j���[                        �i�V�X�e���p�B���[�U�[�g�p�s�j
//
MINT	MdhGetWindowType(
						MDID		i_idHyo,	// �\NO
						MINT*		o_piTp,		// �\�^�C�v�i�P�`�V�j���L�Q��
						MINT*		o_piRs,		// �T�C�Y�ύX�t���O�i�O:�Ȃ��^�P�F����j
						MINT*		o_piTt,		// �^�C�g���t���O�i�O:�Ȃ��^�P�F����j
						MINT*		o_piIc,		// �A�C�R�����t���O�i�O:�Ȃ��^�P�F����j
						MINT*		o_piMx		// �ő剻�t���O�i�O:�Ȃ��^�P�F����j
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E�^�C�g��������̒�`
//
MINT	MdhDefWindowTitle(
						MDID		i_idHyo,	// �\NO
						MCHAR		i_sTtl[]	// �^�C�g��������o�b�t�@
				)
{
	return 0;
}

//===========================================================================
//		�E�B���h�E�^�C�g��������̖₢���킹
//
MINT	MdhGetWindowTitle(
						MDID		i_idHyo,	// �\NO
						MCHAR		o_sTtl[],	// �^�C�g��������o�b�t�@
						MINT		i_nTtl		// �^�C�g��������o�b�t�@�T�C�Y
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�̒�`
//
//		�T�u�E�B���h�E�̒�`���s���B
//		���W�l�̓E�B���h�E�̍�������_�Ƃ����l���w�肷��B�iX,Y���ɉE���֌������ā{�����j
//		�����i�I�[�v�����́j�E�B���h�E�ɑ΂��ẮA�����ɐݒ�l�͔��f����Ȃ��B
//		����I�[�v��������L���ɂȂ�B
//
//		�T�u�E�B���h�E�^�C�v�ɂ���
//			�P�F�L�����o�X�^�C�v
//		Field��\��t���邱�Ƃ��ł���B
//		�E�B���h�E�Y�̃A�C�e���͓\��t���邱�Ƃ��ł��Ȃ��B
//			�Q�F�p�l���^�C�v
//		Field��\��t���邱�Ƃ��ł��Ȃ��B
//		�E�B���h�E�Y�̃A�C�e���͓\��t���邱�Ƃ��ł���
//
MINT	MdhDefSubWindow(
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_iTpSWin,	// �T�u�E�B���h�E�^�C�v�i1:�L�����o�X 2:�p�l���j
						CPoint		i_ptSt,		// �T�u�E�B���h�E�n�_
						CPoint		i_ptSz		// �T�u�E�B���h�E�̑傫��
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E��`�̃N���A
//
//		�T�u�E�B���h�ENO�ȉ��̒�`�f�[�^���S�ăN���A����
//
MINT	MdhClearDefSubWindow(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin	// �T�u�E�B���h�ENO
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�ʒu�E�傫���̖₢���킹��
//
MINT	MdhGetSubWindowPos(
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_iTpSWin,	// �T�u�E�B���h�E�^�C�v�i1:�L�����o�X 2:�p�l���j
						CPoint*		o_pptSt,	// �T�u�E�B���h�E�n�_
						CPoint*		o_pptSz		// �T�u�E�B���h�E�̑傫��
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�ɃJ���[�}�b�v�����`
//
//		�T�u�E�B���h�E�ɃJ���[�}�b�v���`����B
//		�J���[�}�b�v���w�肷�邱�Ƃɂ��A�p���b�g�ԍ��ɂ��F�w�肪�\�ɂȂ�B
//
MINT	MdhGetKey(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MCHAR		i_sColMap	// �J���[�}�b�v��
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�̃J���[�}�b�v���𓾂�
//
MINT	MdhSetMouseMoveEventFlg (
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MCHAR		o_sColMap[],// �J���[�}�b�v��
						MINT		i_szColMap	// �J���[�}�b�v���o�b�t�@�T�C�Y
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�ɔw�i�F�R�[�h���`
//
//		�F�R�[�h�̓J���[�}�b�v���̃p���b�g�̃C���f�b�N�X��ݒ肷��B
//
MINT	MdhGetMouseUpEventFlg(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_icdCol	// �F�R�[�h
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�̔w�i�F�R�[�h�𓾂�
//
//		�F�R�[�h�̓J���[�}�b�v���̃p���b�g�̃C���f�b�N�X��������B
//
MINT	MdhGetSubWindowBackColor(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT*		o_picdCol	// �F�R�[�h
				)
{
	return 0;
}

//===========================================================================
//		�T�u�E�B���h�E�Ɍr�����`
//
//		�T�u�E�B���h�E�ɑ΂��Đ���������`���s���B
//		�T�u�E�B���h�E�̍�������_�Ƃ������W�l�Ŏw�肷��B
//
//		����ɂ��ẮA�ʎ��u����ꗗ�v���Q�ƁB
//
MINT	MdhDefSubWindowLine(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						CPoint		i_iptSt,	// �r���n�_
						CPoint		i_iptEn,	// �r���I�_
						MINT		i_iLW,		// �����i�s�N�Z���l�j
						MINT		i_iLTp,		// ����
						MINT		i_iLN,		// �{��
						MINT		i_iLSpn,	// �Ԋu
						MINT		i_iLCol		// �F�R�[�h
				)
{
	return 0;
}


//
//===========================================================================
//		�r���f�[�^�̖₢���킹
//
//		�T�u�E�B���h�E�ɒ�`����Ă���r���f�[�^�̑S�Ă𓾂�B
//		�o�b�t�@��1�̌r����long[10]�K�v
//
//		[0]  /* �r���J�n���n�_�i�w�j */
//		[1]  /* �r���J�n���n�_�i�x�j */
//		[2]  /* �r���J�n���I�_�i�w�j */
//		[3]  /* �r���J�n���I�_�i�x�j */
//		[4]  /* ����R�[�h */
//		[5]  /* �����i�s�N�Z���l�j */
//		[6]  /* �{�� */
//		[7]  /* �Ԋu�i�x�j */
//		[8]  /* �Ԋu�i�w�j */
//		[9]  /* �J���[�R�[�h */
//
//		����ɂ��ẮA�ʎ��u����ꗗ�v���Q�ƁB
//
MINT	MdhGetSubWindowLine(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MgGInt		o_iDt		// �r���f�[�^�o�b�t�@
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�ɏ����\����������`
//
//		�T�u�E�B���h�E�ɑ΂��ĕ�����`����`���s���B
//		�T�u�E�B���h�E�̍�������_�Ƃ������W�l�Ŏw�肷��B
//
MINT	MdhDefSubWindowText(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						CPoint		i_iptSt,	// �\���n�_
						MINT		i_nFont,	// �����t�H���g�m�n
						MCHAR		i_sStr		// �����\��������
				)
{
	return 0;
}

//
//===========================================================================
//		�r����`�E�����\���������`�̃N���A
//
//		�T�u�E�B���h�E�ɒ�`���ꂽ�r����`�E������`���폜����B
//
MINT	MdhClearDefSubWindowData(				
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin	// �T�u�E�B���h�ENO
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�̒�`
//
//		�t�B�[���h�̒�`���s���B
//		���W�l�̓T�u�E�B���h�E�̍�������_�Ƃ����l���w�肷��B�iX,Y���ɉE���֌������ā{�����j
//		�����i�I�[�v�����́j�E�B���h�E�ɑ΂��ẮA�����ɐݒ�l�͔��f����Ȃ��B
//		����I�[�v��������L���ɂȂ�B
//
MINT	MdhDefField(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint		i_iptFldSt,	// �t�B�[���h�n�_
						CPoint		i_iptFldSz,	// �t�B�[���h�̑傫��
						MINT		i_nLine,	// �s��
						MINT		i_nColm,	// ��
						CPoint		i_iptEcSt,	// �G�R�[�o�b�N�̈�n�_
						CPoint		i_iptEcSz,	// �G�R�[�o�b�N�̈�̑傫��
						MINT		i_nFont		// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�A�C�e���̒�`
//
//		�A�C�e���̒�`���s���B
//		���W�l�̓T�u�E�B���h�E�̍�������_�Ƃ����l���w�肷��B�iX,Y���ɉE���֌������ā{�����j
//		�����i�I�[�v�����́j�E�B���h�E�ɑ΂��ẮA�����ɐݒ�l�͔��f����Ȃ��B
//		����I�[�v��������L���ɂȂ�B
//
//		�A�C�e�����[�h�ɂ��ẮA�ʎ��u�A�C�e�����[�h�ꗗ�v���Q�ƁB
//
MINT	MdhDefItem(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nItem,	// ����NO
						CPoint		i_iptItemSt,// �A�C�e���n�_
						CPoint		i_iptItemSz,// �A�C�e���̑傫��
						MINT		i_mdItem,	// �A�C�e�����[�h
						MINT		i_nFont		// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�i�A�C�e���j��`�̃N���A
//
//		�t�B�[���h�ȉ��܂��̓A�C�e���ȉ��̒�`���N���A����B
//
//
MINT	MdhClearDefField(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nF		// �T�u�E�B���h�E�^�C�v��
												//	�L�����o�X�̏ꍇ�F�t�B�[���hNO
												//	�p�l���̏ꍇ�@�@�F�A�C�e��NO
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�f�[�^�̖₢���킹
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetField(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint*		o_piptFldSt,// �t�B�[���h�n�_
						CPoint*		o_piptFldSz,// �t�B�[���h�̑傫��
						MINT*		o_pnLine,	// �s��
						MINT*		o_pnColm,	// ��
						CPoint*		o_piptEcSt,	// �G�R�[�o�b�N�̈�n�_
						CPoint*		o_piptEcSz,	// �G�R�[�o�b�N�̈�̑傫��
						MINT*		o_pnFont	// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�ʒu�E�傫���̖₢���킹
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetFieldPos(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint*		o_piptFldSt,// �t�B�[���h�n�_
						CPoint*		o_piptFldSz	// �t�B�[���h�̑傫��
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�s�񐔂̖₢���킹
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetFieldLineColumn(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT*		o_pnLine,	// �s��
						MINT*		o_pnColm	// ��
				)
{
	return 0;
}

//
//===========================================================================
//		�G�R�[�o�b�N�̈�̖₢���킹
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetFieldEchoPos(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint*		o_piptEcSt,	// �G�R�[�o�b�N�̈�n�_
						CPoint*		o_piptEcSz	// �G�R�[�o�b�N�̈�̑傫��
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�̕����t�H���g�𓾂�
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetFieldFont(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT*		o_pnFont	// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�i�S�Z���j�ɕ����\���ʒu���`
//
//		�S�ẴZ���ɑ΂��ĕ����\���ʒu���`����B
//		������`���ꍇ�w�肵���ʒu����\������邱�ƂɂȂ�B
//
MINT	MdhDefFieldTextOffset(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint		i_iptFld	// �\���ʒu
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�i�S�Z���j�̕����\���ʒu�𓾂�
//
//		��`����Ă���t�B�[���h�f�[�^��₢���킹��B
//
MINT	MdhGetFieldTextOffset(
						MINT		i_mdRvrb,	// ���[�h
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						CPoint*		o_piptFld	// �\���ʒu
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�ɔw�i�F�R�[�h���`
//
//		�F�R�[�h�̓T�u�E�B���h�E�Ŏw�肵���J���[�}�b�v�̃C���f�b�N�X
//
MINT	MdhDefFieldBackColor (
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT		i_icdCol	// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�̔w�i�F�R�[�h�𓾂�
//
//		�F�R�[�h�̓T�u�E�B���h�E�Ŏw�肵���J���[�}�b�v�̃C���f�b�N�X
//
MINT	MdhGetFieldBackColor(						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT*		o_picdCol	// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�A�C�e���f�[�^�̖₢���킹
//
//		��`����Ă���A�C�e���f�[�^��₢���킹��B
//		���W�l�̓T�u�E�B���h�E�̍�������_�Ƃ����l�ł���B�iX,Y���ɉE���֌������ā{�����j

//		�A�C�e�����[�h�ɂ��ẮA�ʎ��u�A�C�e�����[�h�ꗗ�v���Q�ƁB

//
MINT	MdhGetItem(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nItem,	// ����NO
						CPoint		i_iptItemSt,// �A�C�e���n�_
						CPoint		i_iptItemSz,// �A�C�e���̑傫��
						MINT		i_mdItem,	// �A�C�e�����[�h
						MINT		i_nFont		// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���ɏ����\����������`
//
//		�Z���ɏ�����������`����B
//
MINT	MdhDefCellText(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT		i_nLine,	// �s��
						MINT		i_nColm,	// ��
						CPoint		i_iptEcSt,	// �\��������
						MINT		i_nFont		// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̏����\��������𓾂�
//
//		�Z���̏����������₢���킹��B
//
MINT	MdhGetCellText(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT*		o_pnLine,	// �s��
						MINT*		o_pnColm,	// ��
						CPoint*		o_piptEcSt,	// �\��������
						MINT*		o_pnFont	// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̗̈�𓾂�i�T�u�E�B���h�E��̈ʒu�j
//
//		�Z���ɒ�`���ꂽ�f�[�^��₢���킹��B
//
MINT	MdhGetCellPosInSubWindow(
						MDID		i_idHyo,	// �\NO
						MDID		i_idSWin,	// �T�u�E�B���h�ENO
						MINT		i_nField,	// �t�B�[���hNO
						MINT		i_nLine,	// �s��
						MINT		i_nColm,	// ��
						MDID*		o_pidSWin,	// �T�u�E�B���h�EID
						CPoint*		o_piptCelSt,// �Z���n�_
						CPoint*		o_piptCelEn,// �Z���I�_�iY�j
						MDID*		i_pidFont	// �����t�H���gID
				)
{
	return 0;
}

//
//===========================================================================
//		�����t�H���g�̒�`
//
//		�����t�H���g���`����B
//
MINT	MdhDefFont(
						MDID		i_idFont,	// �����t�H���gNO
						MCHAR		i_sflFont[]	// �t�H���g�t�@�C����������
				)
{
	return 0;
}

//
//===========================================================================
//		�����t�H���g�𓾂�
//
//		��`����Ă��镶���t�H���g�𓾂�B
//
MINT	MdhGetFont(
						MDID		i_idFont,	// �����t�H���gNO
						MCHAR*		i_sflFont[],// �t�H���g�t�@�C����������
						MINT		i_szflFont	// �t�H���g�t�@�C����������o�b�t�@�T�C�Y
				)
{
	return 0;
}

//
//===========================================================================
//		�����t�H���g��`�̃N���A
//
MINT	MdhClearDefFont(
						MDID		i_idFont	// �����t�H���gNO
				)
{
	return 0;
}

//
//===========================================================================
//		�C���[�W�̒�`
//
//		�C���[�W���̂ƃC���[�W�t�@�C���̃p�X���w�肵�ăC���[�W���`����B
//		��`�����C���[�W��DispSubWindowImage�����DispCellImage�Ŏg�p�ł���B
//
//		�C���[�W�t�@�C���Ƃ��Ďg�p�ł���t�@�C���`���͉��L�̒ʂ�B
//		*.bmp
//		*.jpg
//		*.tif
//		*.png
//
MINT	MdhDefImage(
						MCHAR*		i_snmImg,	// �C���[�W����
						MCHAR*		i_sflImg	// �C���[�W�t�@�C����������
				)
{
	return 0;
}

//
//===========================================================================
//		���g�p�̕\NO�𓾂�
//
//		�V�K�ɒ�`�\�ȕ\NO�𓾂�B
//		�擾�ł��Ȃ��ꍇ�́A�߂�l=0���Ԃ�B
//
MINT	MdhGetUnUseedWindowNo()					// �\No
{
	return 0;
}

//
//===========================================================================
//		��`�ς݃T�u�E�B���h�E�̖₢���킹
//
//		�\�m�n���ɑ��݂���T�u�E�B���h�E�m�n����������B
//
MINT	MdhGetSubWindowList(
						MDID		i_idHyo,	// �\�m�n
						MgGInt*		o_pgidSWin	// �T�u�E�B���h�ENO���X�g 
				)
{
	return 0;
}

//
//===========================================================================
//		��`�ς݃t�B�[���h�̖₢���킹
//
//		�T�u�E�B���h�E�m�n���ɑ��݂���t�B�[���h�m�n����������B
//
MINT	MdhGetFieldList(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_idSWin,	// �T�u�E�B���h�ENO 
						MDGID*		o_pGidFld	// �t�B�[���hNO
				)
{
	return 0;
}

//
//===========================================================================
//		��`�ς݃A�C�e���̖₢���킹
//
//		�T�u�E�B���h�E�m�n���ɑ��݂���t�B�[���h�m�n����������B
//
MINT	MdhGetItemList(
						MDID		i_idFont,	// �����t�H���gNO
						MCHAR*		i_sFontFl[],// �t�H���g�t�@�C����������
						MINT		i_szFontFl	// �t�H���g�t�@�C����������o�b�t�@�T�C�Y
				)
{
	return 0;
}

//
//===========================================================================
//		�\�̃I�[�v��
//
//		�w�肳�ꂽ�\���I�[�v������B
//		�w�肳�ꂽ�\�̃T�u�E�B���h�E���S�ăI�[�v������B
//		�\��\�������邽�߂ɂ́AOpen���Ă񂾌��Disp���ĂԕK�v������B
//
//		���\�̃I�[�v���ɂ���
//		�\�̃I�[�v���ɂ́A�Q�̊֐�������B
//			Open:�@ �\�̃E�B���h�E�t���[���ƁA���̕\�ɑ�����T�u�E�B���h�E�S�Ă��I�[�v������B
//			OpenWindowFrame:�@ �\�̃E�B���h�E�t���[���̂݃I�[�v������B
//
MINT	MdhOpen(
						MDID		i_idHyo		// �\�m�n
				)
{
	return 0;
}

//
//===========================================================================
//		�\�̃N���[�Y
//
//		�w�肳�ꂽ�\���N���[�Y����B
//		�w�肳�ꂽ�\�̃T�u�E�B���h�E���S�ăN���[�Y����B
//
MINT	MdhClose(
						MDID		i_idHyo		// �\�m�n
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�t���[���̃I�[�v��
//
//		�w�肳�ꂽ�\�̃E�B���h�E�t���[���݂̂��I�[�v������B
//
//		���\�̃I�[�v���ɂ���
//		�\�̃I�[�v���ɂ́A�Q�̊֐�������B
//			Open:�@ �\�̃E�B���h�E�t���[���ƁA���̕\�ɑ�����T�u�E�B���h�E�S�Ă��I�[�v������B
//			OpenWindowFrame:�@ �\�̃E�B���h�E�t���[���̂݃I�[�v������B
//
//		���̊֐��ł́A�w�肳�ꂽ�\�̃T�u�E�B���h�E�̓I�[�v�����Ȃ��̂ŁA
//		�@�@�@�@�@�@OpenSubWindow
//		���Ă�ŁA�K�v�ȃT�u�E�B���h�E�������ŃI�[�v������K�v������B
//		�܂��A�\��\�������邽�߂ɂ́A�e��I�[�v�����Ă񂾌��Disp���ĂԕK�v������B
//
MINT	MdhOpenWindowFrame(
						MDID		i_idHyo		// �\�m�n
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�̃I�[�v��
//
//		�w�肳�ꂽ�T�u�E�B���h�E���I�[�v������B
//
//		���\�̃I�[�v���ɂ���
//		�\�̃I�[�v���ɂ́A�Q�̊֐�������B
//			Open:�@ �\�̃E�B���h�E�t���[���ƁA���̕\�ɑ�����T�u�E�B���h�E�S�Ă��I�[�v������B
//			OpenWindowFrame:�@ �\�̃E�B���h�E�t���[���̂݃I�[�v������B
//
//		�T�u�E�B���h�E�̃I�[�v�����R���g���[���������ꍇ�́A
//		�@�@�@�@�@�@OpenWindowFrame
//		���Ă�ł���A���֐��ŕK�v�ȃT�u�E�B���h�E��������Open����B
//		�\��\�������邽�߂ɂ́AOpen���Ă񂾌��Disp���ĂԕK�v������B
//
MINT	MdhOpenSubWindow(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_idSWin	// �T�u�E�B���h�ENO
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�̃N���[�Y
//
//		�w�肳�ꂽ�T�u�E�B���h�E���N���[�Y����B
//
MINT	MdhCloseSubWindow(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_idSWin	// �T�u�E�B���h�ENO
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�̕\��
//
//		�w�肳�ꂽ�\��\������B
//
MINT	MdhDisp(
						MDID		i_idHyo		// �\�m�n
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�̏���
//
//		�w�肳�ꂽ�\���\���ɂ���B
//
//		��\���̕\���ēx�\������ꍇ�́ADisp���ĂԁB
//
MINT	MdhHide(
						MDID		i_idHyo		// �\�m�n
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�̎n�_�ʒu�̐ݒ�
//
//		�w�肳�ꂽ�\�̎n�_�ʒu��ݒ肷��B
//
//		�w�肳�ꂽ�\���I�[�v������Ă���΁A�\���ړ�����B
//		�w�肳�ꂽ�\���I�[�v������Ă��Ȃ��ꍇ�́A���̈ʒu���L�^����A���ɃI�[�v��������A
//		���̈ʒu�ɕ\�������B
//
MINT	MdhSetWindowPosition(
						MDID		i_idHyo,	// �\�m�n
						CPoint		i_iptFontSt	// �n�_
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�E�̃I�[�v����Ԃ̖₢���킹
//
//		�w�肳�ꂽ�\�̃I�[�v����Ԃ�₢���킹��B
//
MINT	MdhGetWindowOpenState(
						MDID		i_idHyo,	// �\�m�n
						MINT*		i_piCond	// �I�[�v�����
												//	 0:�I�[�v������Ă��Ȃ�
												//	 1:�I�[�v������Ă���
												//	-1:�I�[�v������Ă��邪��\��
				)
{
	return 0;
}

//
//===========================================================================
//		�E�B���h�EID�̖₢���킹
//
//		�w�肳�ꂽ�\�̃E�B���h�EID�𓾂�B
//
//		�E�B���h�EID�́AWindows�̃E�B���h�E�n���h���B
//
MINT	MdhGetWindowID(
						MDID		i_idHyo,	// �\�m�n
						MDID*		i_pidWin	// �E�B���h�EID
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�EID�̖₢���킹
//
//		�w�肳�ꂽ�T�u�E�B���h�E�̃T�u�E�B���h�EID�𓾂�B
//
//		�T�u�E�B���h�EID�́AWindows�̃E�B���h�E�n���h���B
//
MINT	MdhGetSubWindowID(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_nSWin,	// �T�u�E�B���h�ENO
						MDID*		i_pidWin	// �T�u�E�B���h�EID
				)
{
	return 0;
}

//
//===========================================================================
//		�A�C�e��ID�̖₢���킹
//
//		�w�肳�ꂽ�A�C�e���̃A�C�e��ID�𓾂�B
//
//		�A�C�e��ID�́AWindows�̃R���g���[���n���h���B
//
MINT	MdhGetItemID(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_nSWin,	// �T�u�E�B���h�ENO
						MINT		i_nItem,	// �A�C�e��NO
						MDID*		i_pidItem	// �A�C�e��ID
				)
{
	return 0;
}

//
//===========================================================================
//		�����t�H���gID�̖₢���킹
//
//		�w�肳�ꂽ�����t�H���g�̕����t�H���gID�𓾂�B
//
//		�����t�H���gID�́AWindows�̃t�H���g�n���h���B
//
MINT	MdhGetFontID(
						MINT		i_nFont,	// �����t�H���gNO
						MDID*		o_pidFont	// �����t�H���gId
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�̓h��Ԃ�
//
//		�w�肳�ꂽ�T�u�E�B���h�E�̗̈��w�i�F�œh��Ԃ��B
//
//		�T�u�E�B���h�E�ɔw�i�F���ݒ肳��Ă��Ȃ��ꍇ�́A�O�Ԃ̃J���[�œh��Ԃ����B
//
MINT	MdhFillSubWindow(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_nSWin		// �T�u�E�B���h�ENO
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�Ɍr����\��
//
//		�w�肳�ꂽ�T�u�E�B���h�E�ɐ���`���B
//
//		�w�肳�ꂽ�����T�u�E�B���h�E�̗̈���傫�����̓`�F�b�N�����Ȃ��B
//		�T�u�E�B���h�E���傫�Ȑ����w�肵����A�T�u�E�B���h�E�̗̈�Ő؂��ĕ\�������B
//
//		����ɂ��ẮA�ʎ��u����ꗗ�v���Q�ƁB
//
MINT	MdhDispSubWindowLine(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_nSWin,	// �T�u�E�B���h�ENO
						CPoint		i_ilnSt,	// �r���n�_
						CPoint		i_ilnEd,	// �r���I�_
						MINT		i_idWdt,	// �����i�s�N�Z���l�j
						MINT		i_idTyp,	// ����
						MINT		i_nLn,		// �{��
						CPoint		i_nSpn,		// ���Ԋu
						MINT		i_icdCl		// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�ɕ������\��
//
//		�w�肳�ꂽ�T�u�E�B���h�E�ɕ������\������B
//
//		�w�肳�ꂽ�����񂪃T�u�E�B���h�E�̗̈���傫�����̓`�F�b�N�����Ȃ��B
//		�T�u�E�B���h�E���傫�ȕ������w�肵����A�T�u�E�B���h�E�̗̈�Ő؂��ĕ\�������B
//
MINT	MdhDispSubWindowText(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						CPoint		i_iSt,		// �\���n�_
						MDID		i_idFont,	// �����t�H���gNO
						MCHAR*		i_sStr,		// �\��������
						MINT		i_icdCl		// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�T�u�E�B���h�E�ɃC���[�W��\��
//
//		�w�肳�ꂽ�T�u�E�B���h�E�Ɏw�肳�ꂽ�C���[�W��\������B
//
//		�C���[�W���T�u�E�B���h�E�̈���傫�����̓`�F�b�N�����Ȃ��B
//		�T�u�E�B���h�E���傫�ȃC���[�W���w�肵����A�T�u�E�B���h�E�̈�Ő؂��ĕ\�������
//
//		�C���[�W���̂Ƃ́ADefImage�œo�^�����C���[�W���̂��w�肷��B
//
MINT	MdhDispSubWindowImage(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						CPoint		i_iSt,		// �n�_
						MCHAR*		i_sNmImg	// �C���[�W����
				)
{
	return 0;
}

//
//===========================================================================
//		�t�B�[���h�̓h��Ԃ�
//
//		�w�肳�ꂽ�t�B�[���h�̗̈��w�i�F�œh��Ԃ��B
//
//		�t�B�[���h�ɔw�i�F���ݒ肳��Ă��Ȃ��ꍇ�́A���̃T�u�E�B���h�E�̔w�i�F�œh��Ԃ����B
//		�T�u�E�B���h�E�ɂ��w�i�F���ݒ肳��Ă��Ȃ��ꍇ�́A�O�Ԃ̃J���[�œh��Ԃ����B
//
MINT	MdhFillField(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld		// �t�B�[���hNO
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���ɕ������\��
//
//		�w�肳�ꂽ�Z���ɕ������\������B
//
//		�����́A�����\���ʒu���w�肳��Ă���΁A���̈ʒu�\�������B
//		�����\���ʒu���ݒ肳��Ă��Ȃ���΁A�G�R�[�o�b�N�̈�̍������_�ɕ\�������B
//		�w�肳�ꂽ�����񂪃Z���̗̈���傫�����̓`�F�b�N�����Ȃ��B
//		�Z�����傫�ȕ������w�肵����A�Z���̈���͂ݏo���ĕ\�������B
//
MINT	MdhDispCellText(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MCHAR*		i_sStr,		// �\��������
						MINT		i_icdCl		// �F�R�[�h
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���ɃC���[�W��\��
//
//		�w�肳�ꂽ�Z���ɃC���[�W��\������B
//		�Z���̃G�R�[�o�b�N�̈�̍���̓_���w�肵�ĕ\������B
//		�C���[�W���Z���̃G�R�[�o�b�N�̈���傫�����̓`�F�b�N�����Ȃ��B
//		�Z�����傫�ȃC���[�W���w�肵����A�Z���̈���͂ݏo���ĕ\�������B
//
//		�C���[�W���̂Ƃ́ADefImage�œo�^�����C���[�W���̂��w�肷��B
//
MINT	MdhDispCellImage(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MCHAR*		i_sStr,		// �\��������
						MINT		i_icdCl,	// �F�R�[�h
						MCHAR*		i_sNmImg	// �C���[�W����
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̔��]�\��
//
//		�w�肳�ꂽ�Z���̕\���𔽓]����B
//		���]�\�����ꂽ�Z���ɑ΂��āA�ēx���]������ƁA���Ƃ̕\���ɖ߂�B
//
MINT	MdhDispCellRevt(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm		// ��
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̃{�^��ON�\���i�\�������w��j
//
//		�w�肳�ꂽ�Z���Ɏw�肳�ꂽ������\�����A�{�^��ON�̐���`���B
//
//		�����́A�����\���ʒu���w�肳��Ă���΁A���̈ʒu�\�������B
//		�����\���ʒu���ݒ肳��Ă��Ȃ���΁A�G�R�[�o�b�N�̈�̍������_�ɕ\�������B
//		�w�肳�ꂽ�����񂪃Z���̗̈���傫�����̓`�F�b�N�����Ȃ��B
//		�Z�����傫�ȕ������w�肵����A�Z���̈���͂ݏo���ĕ\�������B
//		�{�^���̐��́A�Z���̃G�R�[�o�b�N�̈�̓����ɕ`���B
//
MINT	MdhDispCellTextButtonOn(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MINT		i_iclFil,	// �Z���h��Ԃ��F
						MCHAR*		i_sStr,		// �\��������
						MINT		i_iclStr,	// �����F
						MINT		i_iclBtL,	// �{�^���̖��e�F
						MINT		i_iclBtD,	// �{�^���̈Ée�F
						MINT		i_iclOLn	// �O�g���̐F
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̃{�^��OFF�\���i�\�������w��j
//
//		�w�肳�ꂽ�Z���Ɏw�肳�ꂽ������\�����A�{�^��OFF�̐���`���B
//
//		�����́A�����\���ʒu���w�肳��Ă���΁A���̈ʒu�\�������B
//		�����\���ʒu���ݒ肳��Ă��Ȃ���΁A�G�R�[�o�b�N�̈�̍������_�ɕ\�������B
//		�w�肳�ꂽ�����񂪃Z���̗̈���傫�����̓`�F�b�N�����Ȃ��B
//		�Z�����傫�ȕ������w�肵����A�Z���̈���͂ݏo���ĕ\�������B
//		�{�^���̐��́A�Z���̃G�R�[�o�b�N�̈�̓����ɕ`���B
//
MINT	MdhDispCellTextButtonOff(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MINT		i_iclFil,	// �Z���h��Ԃ��F
						MCHAR*		i_sStr,		// �\��������
						MINT		i_iclStr,	// �����F
						MINT		i_iclBtL,	// �{�^���̖��e�F
						MINT		i_iclBtD,	// �{�^���̈Ée�F
						MINT		i_iclOLn	// �O�g���̐F
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̃{�^��ON�\��
//
//		�w�肳�ꂽ�Z���Ƀ{�^��ON�̐���`���B
//		�{�^���̐��́A�Z���̃G�R�[�o�b�N�̈�̓����ɕ`���B
//
MINT	MdhDispCellButtonOn(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MINT		i_iclBtL,	// �{�^���̖��e�F
						MINT		i_iclBtD,	// �{�^���̈Ée�F
						MINT		i_iclOLn	// �O�g���̐F
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̃{�^��OFF�\��
//
//		�w�肳�ꂽ�Z���Ƀ{�^��OFF�̐���`���B
//		�{�^���̐��́A�Z���̃G�R�[�o�b�N�̈�̓����ɕ`���B
//
MINT	MdhDispCellButtonOff(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MINT		i_iclBtL,	// �{�^���̖��e�F
						MINT		i_iclBtD,	// �{�^���̈Ée�F
						MINT		i_iclOLn	// �O�g���̐F
				)
{
	return 0;
}

//
//===========================================================================
//		�A�C�e���ɕ������\��
//
//		�w�肳�ꂽ�A�C�e���ɕ������\������B
//
MINT	MdhDispItemText(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iItm,		// �A�C�e��NO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MCHAR*		i_sStr		// �\��������
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̕��������
//
//		�w�肳�ꂽ�Z���̕\���𔽓]����B
//		���]�\�����ꂽ�Z���ɑ΂��āA�ēx���]������ƁA���Ƃ̕\���ɖ߂�B
//
MINT	MdhInpCellText(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MCHAR*		i_sOStr,	// �����\��������
						MCHAR*		o_sInStr,	// ���͕�����
						MINT		i_szInStr,	// �o�b�t�@�[�T�C�Y
						MDID*		o_pidWin,	// �E�B���h�EID
						MINT*		o_piEvent	// �C�x���g
				)
{
	return 0;
}

//
//===========================================================================
//		�Z���̐��l����
//
//		�w�肳�ꂽ�Z���̐��l���͂��s���B
//		�d�샂�[�h���n�m�ɂȂ��Ă���ꍇ�́A�ȈՓd��\���\������A�������琔�l����͂���B
//		�n�e�e�̏ꍇ�̓L�[�{�[�h���琔�l����͂���B
//
//		�E�B���h�EID�ƃC�x���g�ɂ��ẮAInp::Point�ŕԂ������̂Ɠ����B
//
MINT	MdhInpCellNumber(
						MDID		i_idHyo,	// �\�m�n
						MDID		i_iSWin,	// �T�u�E�B���h�ENO
						MDID		i_iFld,		// �t�B�[���hNO
						MINT		i_iLn,		// �s
						MINT		i_iClm,		// ��
						MCHAR*		i_sStr,		// �����\��������
						MCHAR*		o_sStr,		// ���͕�����
						MINT		i_szStr,	// �o�b�t�@�[�T�C�Y
						MDID*		o_pidWin,	// �E�B���h�EID
						MINT*		o_piEvent	// �C�x���g
				)
{
	return 0;
}

//
//===========================================================================
//		�d��E�B���h�E�L���t���O�̐ݒ�
//
//		InpCellNumber���s���ɓd��E�B���h�E�̗L���^������ݒ肷��B
//		�t���O�������̏ꍇ�́A�w��Z���ɒ��ڃL�[�C�����͂ƂȂ�B
//		�t���O���L���̏ꍇ�́A�d��E�B���h�E���I�[�v������A�d��E�B���h�E�ւ̓��͂ƂȂ�B
//
MINT	MdhSetCalcWindowFlg(
						MINT		i_iFlg		// �t���O
												//�@0:����
												//�@1:�L��
				)
{
	return 0;
}

//
//===========================================================================
//		�d��E�B���h�E�L���t���O�̖₢���킹
//
//		InpCellNumber���s���ɓd��E�B���h�E�̗L���^�����t���O��₢���킹��B
//		�t���O�������̏ꍇ�́A�w��Z���ɒ��ڃL�[�C�����͂ƂȂ�B
//		�t���O���L���̏ꍇ�́A�d��E�B���h�E���I�[�v������A�d��E�B���h�E�ւ̓��͂ƂȂ�B
//
MINT	MdhGetCalcWindowFlg(
						MINT*		o_piFlg		// �t���O
												//�@0:����
												//�@1:�L��
				)
{
	return 0;
}

//
//===========================================================================
//		���̓Z���i�A�C�e���j�̖₢���킹
//
//		���O��Inp::Point���œ��͂��ꂽ�Z���̈ʒu�l�𓾂�B
//
//		�T�u�E�B���h�E�m�n���L�����o�X�^�C�v�̏ꍇ�́Afno=�t�B�[���hNO�A
//		�p�l���^�C�v�̏ꍇ�́Afno���A�C�e���m�n���Ԃ�B
//		fno���A�C�e���m�n�̎��ɂ́Alin�����col�ɂ�0���Ԃ�B
//
//		���O�ɓ��͊֐�Inp::Point�������s���邱�ƁB
//		wid�����event�ɂ�Inp::Point������̕ԋp�l��n���B
//
//		���֐��͉��L�̓��͒���Ɏ��s����邱�Ƃ��O��B����ȊO�̏�Ԃœ��֐������s�����ꍇ�A�l�͕ۏႵ�Ȃ��B
//		�O���t�B�b�N�E�B���h�E�ȊO�iwid>0�j�̃E�B���h�E�ւ̓��͎��B
//		�}�E�X�{�^����UP/DOWN�A�ړ��A����уA�C�e���ւ̓��͎��B
//
MINT	MdhGetInpCell(
						MDID		i_idWin,	// ���̓E�B���h�EID�iInp::Point���̕ԋp�l�j
						MINT		i_iEvent,	// ���̓C�x���g �@�@�iInp::Point���̕ԋp�l�j
						MDID*		o_pidHyo,	// �\�m�n
						MDID*		o_piSWin,	// �T�u�E�B���h�ENO
						MDID*		o_piFld,	// �t�B�[���hNO
						MINT*		o_piLn,		// �s
						MINT*		o_piClm		// ��
				)
{
	return 0;
}

//
//===========================================================================
//		���͈ʒu�̖₢���킹�i�}�E�X�C�x���g���j
//
//		���O��Inp::Point���œ��͂��ꂽ���W�l���A���̕\�̃T�u�E�B���h�E�̍��W�l�Ƃ��ē���B
//
//		���O�ɓ��͊֐�Inp::Point�������s���邱�ƁB
//		wid�����event�ɂ�Inp::Point������̕ԋp�l��n���B
//
//		���֐��͉��L�̓��͒���Ɏ��s����邱�Ƃ��O��B����ȊO�̏�Ԃœ��֐������s�����ꍇ�A�l�͕ۏႵ�Ȃ��B
//		�O���t�B�b�N�E�B���h�E�ȊO�iwid>0�j�̃E�B���h�E�ւ̓��͎��B
//		�}�E�X�{�^����UP/DOWN�A�ړ��̓��͎��B
//
MINT	MdhGetInpPosition(
						MDID		i_idWin,	// ���̓E�B���h�EID�iInp::Point���̕ԋp�l�j
						MINT		i_iEvent,	// ���̓C�x���g �@�@�iInp::Point���̕ԋp�l�j
						MDID*		o_pidHyo,	// �\�m�n
						MDID*		o_piSWin,	// �T�u�E�B���h�ENO
						CPoint*		o_pptInp	// �T�u�E�B���h�E���̍��W�l
				)
{
	return 0;
}

} // namespace MC
