#pragma once
/********************************************************************************************************************************

              �i�o�����ϊ�  �w�b�_�t�@�C�� (HsJpegLib.h)

********************************************************************************************************************************/

#include		<setjmp.h>
#include		"MsJpegLib.h"

// �萔

// �f�B�U�����O�̎��
#define		HJPDTNONE		0															// �ި���ݸނ��s��Ȃ�
#define		HJPDTFS  		1															// �۲�ޥ������ٸޕ���
#define		HJPDTORD		2															// �����ݸޕ���

// JPEG�t�@�C���̃C���[�W�ϊ��̎��

#define		HJPGPROG		0															// ��۸�گ���JPEĢ�ق��쐬����
#define		HJPGGRAY		1															// ��ڰ���قɕϊ�����
#define		HJPGHORMIR		10															// �����������װ���]������i���E���]�j
#define		HJPGVERMIR		11															// �����������װ���]������i�㉺���]�j
#define		HJPGROT90		20															// ���v����90�x��]������
#define		HJPGROT180		21															// ���v����180�x��]������
#define		HJPGROT270		22															// ���v����270�x��]������i�����v����90�x�j
#define		HJPGTRNSP		31															// ����ƉE�������ԑΊp�������Ƃ��Ĕ��]������
#define		HJPGTRNSV		32															// �����ƉE������ԑΊp�������Ƃ��Ĕ��]������

//HHHH
// �摜���k�I�v�V����
typedef struct _picmprsvars {
	MUINT	Quality;																	// JPEG�F�i��(0�`100,��̫��85)
	MUINT	Smooth;																		// JPEG�F�Ѱ��ݸ�(0�`100,�f�t�H���g0)
} PiCmprsVars;

// �f�B�U�����O�E�I�v�V����
typedef struct _pirdcvars {
	MUINT	Colors;																		// �F��
	MUINT	DitherOpt;																	// �ި���ݸނ̎��
} PiRdcVars;

// �a�l�o�t�@�C���̃w�b�_���
typedef struct _pgbmpflhead {
	MSHORT		Type;																	// BM�Ƃ���������ASCII�l
	MINT		Size;																	// ̧�ق̻���
	MSHORT		Reserved1;																// ���0
	MSHORT		Reserved2;																// ���0
	MINT		OffBit;																	// ̧�ق̎n�܂肩���ޯ�ϯ�߂܂ł��޲Đ�
} PGBMPFLHEAD;
typedef struct _pgbmpinfhead {
	MINT		Size;																	// ���̍\���̂��޲Ļ���
	MINT		Width;																	// �ޯ�ϯ�߂̕����߸�ْl
	MINT		Height;																	// �ޯ�ϯ�߂̍������߸�ْl
	MSHORT		Planes;																	// ���1
	MSHORT		BitCount;																// 1�߸�ق�������ޯĐ�
	MINT		Compression;															// ���k�̎�� ���0
	MINT		SizeImage;																// �ޯ�ϯ�߂̻��ނ�\���޲Đ�	
	MINT		XPixPerMeter;															// 1Ұ�ق�����̐��������߸�ِ�
	MINT		YPixPerMeter;															// 1Ұ�ق�����̐��������߸�ِ�
	MINT		ColUsed;																// �g�p�����F�̐�
	MINT		ColImprtant;															// �d�v�ȐF�̐�
} PGBMPINFHEAD;

// �J���[�}�b�v��
typedef struct _pgrgbquad {
	MBYTE		Blue;																	// �װϯ�ߴ��؂̐̒l
	MBYTE		Green;																	// �װϯ�ߴ��؂̗΂̒l
	MBYTE		Red;																	// �װϯ�ߴ��؂̐Ԃ̒l
	MBYTE		Reserved;																// ���0
} PGRGBQUAD;

// �a�l�o�t�@�C��
typedef struct _pgbmpfile {
	PGBMPFLHEAD		FileHead;															// ̧��ͯ�ޕ�
	PGBMPINFHEAD	InfHead;															// �ޯ�ϯ��ͯ�ޕ�
	PGRGBQUAD		RgbQuad[256];														// �װϯ�ߕ�
} PGBMPFILE;


// IJG �̃G���[�n���h�����O�p��`
typedef struct _pi_ijg_error_mgr {
	struct jpeg_error_mgr	pub;														// "public"�t�B�[���h
	jmp_buf					setjmp_buffer;												// �Ăяo�����ւ����ݗp
} PiIjgErrorMgr;

typedef struct _pi_ijg_error_mgr*	PiIjgErrorPtr;

/******************************************************************************************************************
[ �@�\ ] ����J�֐��̃v���g�^�C�v�錾 (IJG �̊֐����̃G���[����ʊ֐��ɕԂ�)
[ �Ԓl ] �Ȃ�
******************************************************************************************************************/
void MsJpegErrExit            (
								j_common_ptr		cinfo);								// (I  ) JPEG���k��L�������Ұ��p�\���̂ւ��߲��


/////////////////////////////////////////////////////////////////////////////
//		JPEG�t�@�C����BMAP�t�H�[�}�b�g�ɕϊ�
MINT MsJpegJpgToBmp(															// (  O) �ð��
								MCHAR*				i_FLName1,					// (I  ) �ϊ����摜̧�ٖ�
								MCHAR*				i_FLName2,					// (I  ) �ϊ���摜̧�ٖ�
								MINT				i_MFlag     = 0,			// (I  ) 1:���E�װ
								MREAL				i_Scale     = 100,			// (I  ) �摜���ނ̏k����
								MUINT				i_Colors    = 0,			// (I  ) �F���i==0�F�팸���Ȃ��j
								MUINT				i_DitherOpt = 0);			// (I  ) �ި���ݸނ̎��

/////////////////////////////////////////////////////////////////////////////
//		BMAP�t�@�C����JPEG�t�H�[�}�b�g�Ɉ��k�E�ϊ�
MINT MsJpegBmpToJpg(															// (  O) �ð��
								MCHAR*				i_FLName1,					// (I  ) �ϊ����摜̧�ٖ�
								MCHAR*				i_FLName2,					// (I  ) �ϊ���摜̧�ٖ�
								MUINT				i_Quality = 100,			// (I  ) ���k��   (0�`100)
								MUINT				i_Smooth  = 100);			// (I  ) �Ѱ��ݸ� (0�`100)

/////////////////////////////////////////////////////////////////////////////
//		IJG �����ŃG���[�����������ꍇ�̏���
void MsJpegErrExit(
								j_common_ptr		i_cinfo);					// (I ) JPEG���k��L�������Ұ��p�\���̂ւ��߲��
