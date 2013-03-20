#pragma once
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsDefine.h
//
//		MCAD�Ŏg�p����p��̒�`
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

//===========================================================================
// �}�`���
enum MFIGURETYPE {
	MPT_DOT			= 1,										// �_
	MPT_LINE,													// ��
	MPT_RECT,													// �܂��
	MPT_POLYLINE,												// �����`
	MPT_POLYGON,												// ���p�`
	MPT_CIRCLE,													// �~
	MPT_ELLIPSE,												// �ȉ~
	MPT_ARC,													// �~��
	MPT_TEXT													// ������
};

// ����
enum MPENSTYLE {
	MPS_SOLID		= 0,										// ����
	MPS_DASH		= 1,										// �j��
	MPS_DOT 		= 2,										// �_��
	MPS_DASHDOT 	= 3,										// �P�_����
	MPS_DASHDOTDOT	= 4,										// �Q�_����
	MPS_NULL		= 5											// ���F
};

// �̈�h��Ԃ��`��
enum MAREAFILL {
	MAF_NONE 		= 0,										// �Ȃ�
	MAF_DIAGONAL,												// �Ίp��
	MAF_SLANTTORIGHT,											// �E������n�b�`���O
	MAF_SLANTTOLEFT,											// ��������n�b�`���O
	MAF_HORIZONTAL,												// �����n�b�`���O
	MAF_VERTICAL,												// �����n�b�`���O
	MAF_CROSS,													// ���������i�q�n�b�`���O
	MAF_SLANTCROSS												// �΂ߊi�q�n�b�`���O
};

// �r���[���
enum MVIEWTYPE {
	MVIEWT_HEI = 1,												// ����
	MVIEWT_SYO,													// ����
	MVIEWT_HAI,													// �w��
	MVIEWT_LSK,													// ������
	MVIEWT_RSK,													// �E����
	MVIEWT_URA,													// ����
	MVIEWT_3D													// �R����
};

#define	MB_ESCAPECHAR	27
#define	MB_ENTERCHAR	13
