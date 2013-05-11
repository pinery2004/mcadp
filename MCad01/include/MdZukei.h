#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdZukei.h
//
//		�l�b�`�c���f��
//		�f�B�X�v���C�Ǘ�
//	
//==========================================================================================
//
#include "MgMatD.h"
#include "MgPlane.h"
#include "MgCircle.h"
#include "MgArc.h"

// �T�C�Y
#define		MZWD_PNT_2D		2					// �_(�Q����)���[�h�T�C�Y
#define		MZWD_PNT_3D		3					// �_(�R����)���[�h�T�C�Y
#define		MZWD_LINE_2D	4					// ����(�Q����)���[�h�T�C�Y
#define		MZWD_LINE_3D	6					// ����(�R����)���[�h�T�C�Y
#define		MZWD_ULINE_2D	4					// ����(�Q����)���[�h�T�C�Y
#define		MZWD_ULINE_3D	6					// ����(�R����)���[�h�T�C�Y
#define		MZWD_HLINE_2D	4					// ������(�Q����)���[�h�T�C�Y
#define		MZWD_HLINE_3D	6					// ������(�R����)���[�h�T�C�Y
#define		MZWD_CIR_2D		3					// �~(�Q����)���[�h�T�C�Y
#define		MZWD_CIR_3D		7					// �~(�R����)���[�h�T�C�Y
#define		MZWD_ARC_2D		8					// �~��(�Q����)���[�h�T�C�Y
#define		MZWD_ARC_3D		13					// �~��(�R����)���[�h�T�C�Y
#define		MZWD_PLN_3D		4					// �ʕ�(�R����)���[�h�T�C�Y
#define		MZWD_IPLN_3D	4					// ��������(�R����)���[�h�T�C�Y
#define		MZWD_PUSH		0					// Push���[�h�T�C�Y
#define		MZWD_PULL		0					// Pull���[�h�T�C�Y
#define		MZWD_MRKR		1					// �}�[�J
#define		MZWD_PAINT		1					// �h��Ԃ�
#define		MZWD_LINETP		0					// ����
#define		MZWD_COLOR_I	1					// �F( RGB) 
#define		MZWD_COLOR_R	3					// �F( RGB) 
#define		MZWD_COLOR_P	1					// �p���b�g�m�� �F( RGB) 
#define		MZWD_TRANSM		1					// ���ߗ� ( 0. �` 1.)
#define		MZWD_LINEWD		1					// ����
#define		MZWD_MTRL_I		1					// �ގ�( RGB)
#define		MZWD_MTRL_R		4					// �ގ�( RGB)
#define		MZWD_MTRLSHINNS	1					// �ގ����ʌ�( ����)�W��
#define		MZWD_TXTR		1					// �e�N�X�`��
#define		MZWD_TXTRC_S	1					// �e�N�X�`�����W( TpCdn=0:�ʂ�����W�𐶐�)
#define		MZWD_TXTRC_L	19					// �e�N�X�`�����W( TpCdn=1:���W���w��)
#define		MZWD_TXTPRM		7					// �e�N�X�`���p�����[�^
#define		MZWD_SHINNS		1					// ���ʔ��˗�
#define		MZWD_POVRAY		0					// PovRay�o�͑���

// ����
#define		MZTP_3D			0x00				// �R����
#define		MZTP_2D			0x80				// �Q����

// �}�`PMT�R�[�h
#define		MZCD_PNT		0x01				// �_
#define		MZCD_PNTV		0x02				// �_
#define		MZCD_ULINE		0x03				// ����
#define		MZCD_HLINE		0x04				// ������
#define		MZCD_LINE		0x05				// ����
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

#define		MZCD_PLN		0x1A				// �ʕ�
#define		MZCD_IPLN		0x1B				// ��������

// ����PMT�R�[�h
#define		MZAT_PUSH		0x20				// Push
#define		MZAT_PULL		0x21				// Pull

#define		MZAT_MRKR		0x22				// �}�[�J
#define		MZAT_PAINT		0x23				// �h��Ԃ�
#define		MZAT_LINETP		0x24				// ����
#define		MZAT_COLOR		0x25				// �F( RGB) 
#define		MZAT_TRANSM		0x26				// ���ߗ� ( 0. �` 1.)
#define		MZAT_LINEWD		0x27				// ����
#define		MZAT_MTRL		0x28				// �ގ�( RGB)
#define		MZAT_MTRLSHINNS	0x29				// �ގ����ʌ�(����)�W��
#define		MZAT_TXTR		0x2A				// �e�N�X�`��
#define		MZAT_TXTRC		0x2B				// �e�N�X�`�����W
#define		MZAT_TXTPRM		0x2C				// �e�N�X�`���p�����[�^
#define		MZAT_SHINNS		0x2D				// ���ʔ��˗�
#define		MZAT_POVRAY		0x2E				// PovRay�o�͑���



#define		MAX_BUFFSIZE8		0				// 0xFF
#define		MAX_BUFFSIZE16		1				// 0xFFFF
#define		MAX_BUFFSIZE1M		2				// 1000000
#define		MAX_BUFFSIZE10M		3				// 10000000
#define		MAX_BUFFSIZE100M	4				// 100000000

#define		MC_SZ_FBF_MIN		20

namespace MC
{

inline void	MgByteCpy( void* out_ppt, size_t i_szpt, const void* in_ppt, size_t i_npt)
{
	memcpy_s( out_ppt, i_szpt, in_ppt, i_npt);
}

inline void	MgPt3Cpy( MgPoint3D* out_pPt, MINT i_szPt, const MgPoint3D* in_pPt, MINT i_nPt)
{
//	MINT	iC;
	ASSERT( i_nPt <= i_szPt);
//	for ( iC=0; iC<i_nPt; iC++)
//		out_pPt[iC] = in_pPt[iC];
	memcpy( out_pPt, in_pPt, i_nPt * sizeof( MgPoint3D));
}

inline void	MgPt2Cpy( MgPoint2D* out_ppt, MINT i_szpt, const MgPoint2D* in_ppt, MINT i_npt)
{
//	MINT	iC;
	ASSERT( i_npt <= i_szpt);
//	for ( iC=0; iC<i_npt; iC++)
//		out_ppt[iC] = in_ppt[iC];
	memcpy( out_ppt, in_ppt, i_npt * sizeof( MgPoint2D));
}

} // namespace MC
