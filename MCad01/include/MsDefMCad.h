#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsMCadDefine.h
//
//		��{�@�V�X�e���\���@�萔�E�֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================
// window�̕\���`��
//
#define	TAB_WINDOW		false					// �^�u�^���̃E�B���h�E�\��

//===========================================================================
//		�}�b�v ���[�h
//
#define		MMAPMODE			MM_TWIPS		// 1/20�|�C���g
//
//#define	MMAPMODE			MM_HIMETRIC		// 0.01mm
//#define	MMAPMODE			MM_TWIPS		// 1/20�|�C���g
//#define	MMAPMODE			MM_TEXT

// Y���W�̌���		1:�����	-1:������
#if( MMAPMODE == MM_TEXT)
	#define		MMDIRY			-1.
#else
	#define		MMDIRY			1.
#endif

