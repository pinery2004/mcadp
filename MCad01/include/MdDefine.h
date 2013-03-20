#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MddDefine.h
//
//		�l�b�`�c���f��
//						�\���pDefine
//
//
//==========================================================================================
//
//	�}�`�R�[�h
//

#ifdef	NOT_USED

#define		MZCD_PNT		0x01				// �_
#define		MZCD_PNTV		0x02				// �_
#define		MZCD_ULIN		0x03				// ����
#define		MZCD_HLIN		0x04				// ������
#define		MZCD_LIN		0x05				// ����
#define		MZCD_PLY		0x06				// �܂��
#define		MZCD_PLYV		0x07				// �܂�� VECTOR
#define		MZCD_PAC		0x08				// ����|�~�� �܂��

#define		MZCD_RCT		0x09				// �����`
#define		MZCD_PGN		0x0A				// ���p�`
#define		MZCD_PGNV		0x0B				// ���p�` VECTOR
#define		MZCD_ARA		0x0C				// �̈�

#define		MZCD_HRCT		0x0D				// ���t�����`
#define		MZCD_HPLN		0x0E				// ���t���p�`
#define		MZCD_HARA		0x0F				// ���t�̈�

#define		MZCD_CIR		0x10				// �~
#define		MZCD_ARC		0x11				// �~��
#define		MZCD_ELN		0x12				// �ȉ~
#define		MZCD_ELA		0x13				// �ȉ~��

#define		MZCD_SPLN		0x14				// �X�v���C���Ȑ�

#define		MZCD_MPLO		0x18				// �����Ȑ��i�J�j
#define		MZCD_MPLC		0x19				// �����Ȑ��i�j

#define		MZCD_BMP		0x1C				// �r�b�g�}�b�v

// ����
#define		MZCD_MOJZ		0x20				// ��������
#define		MZCD_MOJN		0x21				// ������

// ���@
#define		MZCD_HSHN		0x28				// ���@ ����/����/����/���s
#define		MZCD_HSAN		0x29				// ���@ �p�x
#define		MZCD_HSDN		0x2A				// ���@ ���a
#define		MZCD_HSRN		0x2B				// ���@ ���a

// ����
#define		MZCD_2D			0x40				// 2D�v���~�e�B�u �ϊ��p�p�����[�^
#define		MZCD_3D			0x00				// 3D�v���~�e�B�u �ϊ��p�p�����[�^

// ��
#define		MZCD_LNS		0x81				// ���`�\����
#define		MZCD_TGS		0x82				// �ړ������ʁi���s�j
#define		MZCD_RGS		0x83				// ��]������
#define		MZCD_TRGS		0x84				// �ړ���]������
#define		MZCD_TGS2		0x85				// �ړ������ʁi��]�j
#define		MZCD_TGS3		0x86				// �ړ������ʁi���Łj
#define		MZCD_HIM		0x87				// ������^�����
#define		MZCD_WIM		0x88				// ����^�����

// ����
#define		MZCD_IPLN		0x8C				// ��������
#define		MZCD_PLN		0x8D				// ����

// ����
#define		MZCD_LNV		0x91				// ���`�\������
#define		MZCD_TGV		0x92				// �ړ��������́i���s�j
#define		MZCD_RGV		0x93				// ��]��������
#define		MZCD_TRGV		0x94				// �ړ���]��������
#define		MZCD_TGV2		0x95				// �ړ��������́i��]�j
#define		MZCD_TGV3		0x96				// �ړ��������́i���Łj
#define		MZCD_HIR		0x97				// ������^���闧��
#define		MZCD_GSPR		0x98				// ����^���闧��
#define		MZCD_HBR		0x99				// ���ƍ�����^���闧��
#define		MZCD_BOV2		0x9A				// �󗧑�

#define		MZCD_UNN		0x9C				// �W��
#define		MZCD_GFS		0x9D				// ����
#define		MZCD_GFO		0x9E				// ���ʑ�

// ��
#define		MZCD_KKP		0xA1				// �p�i���j
#define		MZCD_KKB		0xA2				// �p�i���j
#define		MZCD_RKP		0xA3				// �ہi���j
#define		MZCD_RKB		0xA4				// �ہi���j
#define		MZCD_HIRB		0xA5				// �g�|�i���j
#define		MZCD_HIRP		0xA6				// �g�|�i���j
#define		MZCD_POL		0xA7				// ���p�`
#define		MZCD_PHIL		0xA8				// ����
#define		MZCD_PYRA		0xA9				// ����
#define		MZCD_TRPY		0xAA				// ����
#define		MZCD_SPHE		0xAB				// ��
#define		MZCD_UNNS		0xAC				// �k�ڑΉ��a�W��

// ����
#define		MZCD_LIG		0xB1				// ����
#define		MZCD_KAN		0xB2				// ����

// ����
#define		MZAT_PUSH		0xC0				// �����o�t�r�g
#define		MZAT_PULL		0xC1				// �����o�t�k�k
#define		MZAT_ST			0xC2				// �\������START
#define		MZAT_MRK		0xC3				// �}�[�J
#define		MZAT_SLD		0xC4				// �h��Ԃ�
#define		MZAT_LTP		0xC5				// ����
#define		MZAT_COL		0xC6				// �F
#define		MZAT_KCL		0xC7				// ���ߌW��
#define		MZAT_LTB		0xC8				// ����
#define		MZAT_CA			0xC9				// �ގ�����
#define		MZAT_CD			0xCA				// �ގ��g�U��
#define		MZAT_CS			0xCB				// �ގ����ʌ�
#define		MZAT_CE			0xCC				// �ގ����ˌ�
#define		MZAT_SS			0xCD				// �ގ����ʎw��
#define		MZAT_TX			0xCE				// �e�N�X�`��
#define		MZAT_TXZ		0xCF				// �e�N�X�`�����W
#define		MZAT_TXP		0xD0				// �e�N�X�`���p�����[�^
#define		MZAT_REF		0xD1				// ���ʔ��˗�
#define		MZAT_POV		0xD2				// POV-RAY�o�͗p����
#define		MZAT_END		0xD3				// �\������START

// ���ޔz�u
#define		MZCD_PNZ		0xE0				// �_����

// ��Ɩ�
#define		MZCD_SAGY		0xF0				// ��Ɩ�

//#define		MZCD_BUF		0xxx				// �}�`���\��

//	����
#define		MMD_2D			1					// �Q����
#define		MMD_3D			2					// �R����

//	�X�P�[��
#define		MSCL_50A		1					// 1/50A
#define		MSCL_50B		2					// 1/50B
#define		MSCL_100A		3					// 1/100A
#define		MSCL_100B		4					// 1/100B
#define		MSCL_200A		5					// 1/200A
#define		MSCL_200B		6					// 1/200B

//	�r���[���
#define		MVCD_HEIMEN		1					// ����
#define		MVCD_SYOUMEN	2					// ����
#define		MVCD_HAIMEN		3					// �w��
#define		MVCD_LFTSOK		4					// ������
#define		MVCD_RGTSOK		5					// �E����
#define		MVCD_URAMEN		6					// ����

//	�}�`���Z
#define		MZL_ADD			1					// �a
#define		MZL_SUB			2					// ��
#define		MZL_MLT			3					// ��

//	�Ώێw���L��
#define		MSYM_NO			0					// �Ȃ�
#define		MSYM_X			1					// �w���Ώ́A�x�y���ʑΏ�
#define		MSYM_Y			2					// �x���Ώ́A�y�w���ʑΏ�
#define		MSYM_Z			3					// �y���Ώ́A�w�x���ʑΏ�

//	���ʂ̖@���x�N�g������
#define		MVC_PLX			1					// �{�w����
#define		MVC_MNX			2					// �|�w����
#define		MVC_PLY			3					// �{�x����
#define		MVC_MNY			4					// �|�x����
#define		MVC_PLZ			5					// �{�y����
#define		MVC_MNZ			6					// �|�y����
#define		MVC_ETC			7					// ���̑�����

//	���ʃt���O
#define		MMEN_XY			1					// �w�x����
#define		MMEN_YZ			2					// �x�y����
#define		MMEN_ZX			3					// �y�w����
#define		MMEN_2D			4					// �Q�������W

//	�r���[�R�[�h
#define		MVW_PXY			1					// �{�w�x�i�t�o�j
#define		MVW_MXY			2					// �|�w�x�i�c�n�v�m�j
#define		MVW_PYZ			3					// �{�x�y�i�d�`�r�s�j
#define		MVW_MYZ			4					// �|�x�y�i�v�d�r�s�j
#define		MVW_PZX			5					// �{�y�w�i�r�n�t�s�g�j
#define		MVW_MZX			6					// �|�y�w�i�m�n�q�s�g�j

//	�w������
#define		MDIR_NO			0					// �Ȃ�
#define		MDIR_RIT		1					// �E��
#define		MDIR_LFT		2					// ����
#define		MDIR_PLS		3					// �{��
#define		MDIR_MNS		4					// �|��
#define		MDIR_OUT		5					// �O��
#define		MDIR_IN			6					// ����
#define		MDIR_UP			7					// �㑤
#define		MDIR_DWN		8					// ����

// �}�`�v���~�e�B�u
#define		MDZCODE(X)		m_st[X]
#define		MDZNEXT(X)		m_st[X]
#define		MDZPRIM(X)		m_st[X+1]

//#define		MDZCODE(X)		(*((short*)&m_st[X]))
//#define		MDZNEXT(X)		(X+((short*)&m_st[X])[1])
//#define		MDZPRIM(X)		m_st[X+1]

#endif