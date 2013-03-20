#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmInp.h
//
//		���͏���
//
//
//  K.Matsu           07/25/07    Created.
//==========================================================================================
#define MM_MOUSEFIRST		0x0200
#define MM_MOUSEMOVE		0x0200		// �}�E�X�ړ�
#define MM_LBUTTONDOWN		0x0201		// ���{�^���_�E��
#define MM_LBUTTONUP		0x0202		// ���{�^���A�b�v
#define MM_LBUTTONDBLCLK	0x0203		// ���{�^���_�u���N���b�N
#define MM_RBUTTONDOWN		0x0204		// �E�{�^���_�E��
#define MM_RBUTTONUP		0x0205		// �E�{�^���A�b�v
#define MM_RBUTTONDBLCLK	0x0206		// �E�{�^���_�u���N���b�N
#define MM_MBUTTONDOWN		0x0207		// ���{�^���_�E��
#define MM_MBUTTONUP		0x0208		// ���{�^���A�b�v
#define MM_MBUTTONDBLCLK	0x0209		// ���{�^���_�u���N���b�N
#define MM_MOUSEWHEEL		0x020A		// �z�C�[��
#define MM_XBUTTONDOWN		0x020B
#define MM_XBUTTONUP		0x020C
#define MM_XBUTTONDBLCLK	0x020D
#define MM_MOUSELAST		0x020D

#define MM_WINDOWSIZE		0x0100		// �E�B���h�E�T�C�Y�ύX
#define MM_WINDOWMAX		0x0101		// �E�B���h�E�ő剻
#define MM_WINDOWMIN		0x0102		// �E�B���h�E�A�C�R����
#define MM_WINDOWMOVE		0x0103		// �E�B���h�E�ړ�
#define MM_WINDOWDELETE		0x0104		// �E�B���h�E�폜
#define MM_MENU				0x0105		// ���j���[�C�x���g
#define MM_WINDOWACTIVE		0x0106		// �E�B���h�E�A�N�e�B�u
#define MM_TIMER			0x0107		// �^�C�}�[�C�x���g
#define MM_FLOATMENU		0x0108		// �t���[�e�B���O���j���[�C�x���g
#define MM_DROPFILE			0x0109		// �h���b�v�t�@�C���C�x���g
#define MM_KE				0x010A		// �L�[�{�[�h����
#define MM_KEY31			0x010B		// �L�[�{�[�h����
#define MM_P_RET			0x0300		// �p�l��������return����
#define MM_P_BTN			0x0301		// �p�l���{�^������
#define MM_P_MNU			0x0302		// �p�l�����j���[����
#define MM_P_CHI			0x0303		// �p�l���`���C�X����
#define MM_P_CYC			0x0304		// �p�l���T�C�N������
#define MM_P_TGL			0x0305		// �p�l���g�O������
#define MM_P_SLI			0x0306		// �p�l���X���C�_�[����
#define MM_P_KEY			0x0307		// �p�l����������́ireturn�ȊO�j
#define MM_P_LST			0x0308		// �p�l�����X�g�{�b�N�X����
#define MM_P_CBX			0x0309		// �p�l���R���{�{�b�N�X����
#define MM_P_MCX			0x030A		// �J�����_�[����
#define MM_P_DTX			0x030B		// DateTimePicker����
#define MM_J_COM			0x030C		// �����j���[�������ꂽ
#define MM_S_BPR			0x040D		// ���F  �P�y�[�W�E
#define MM_S_BLR			0x040E		//       �P�s�E
#define MM_S_BPL			0x040F		//       �P�y�[�W��
#define MM_S_BLL			0x0410		//       �P�s��
#define MM_S_BPD			0x0411		// �c�F  �P�y�[�W��
#define MM_S_BLD			0x0412		//       �P�s��
#define MM_S_BPU			0x0413		//       �P�y�[�W��
#define MM_S_BLU			0x0414		//       �P�s��
#define MM_S_BTO			0x0415		// ���ʁF�ŏ�s�A�ŉE�s
#define MM_S_BBO			0x0416		//       �ŉ��s�A�ō��s
#define MM_S_BTP			0x0417		//       �܂݂̃h���b�O��
#define MM_S_BTT			0x0418		//       �܂݂̃h���b�O��
#define MM_KYIN 			0x0419		// �L�[�C���\�̓��́iINPUT�Ŏg�p
#define MM_USER				0x041A		// ���[�U�[�C�x���g�ŏ��l
// 
//

namespace MC
{

//
////////////////////////////////////////////////////////////////////////////
//	�o�b�N�O���E���h�����J�n�錾
void MmWndKOpen();

////////////////////////////////////////////////////////////////////////////
//	�o�b�N�O���E���h�����I���錾
void MmWndKClose();

/////////////////////////////////////////////////////////////////////////////
//	�R�}���h���j���[����
void MmWndKCmdMenu(
						MINT		i_idCmd			// �R�}���hID
				);

} // namespace MC