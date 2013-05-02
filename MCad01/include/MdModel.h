#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		�l�b�`�c���f��
//
//
#include "MdAry.h"
#include "MdAryH.h"

#include "MdmDefine.h"
#include "MdmSet.h"

#include "MdmGrp.h"
#include "MdmScm.h"
#include "MdmLyr.h"
#include "MdmSetC.h"
#include "MdmEnt.h"
#include "MdmWin.h"

namespace MC
{

class MDGRPSET : public MdAryH_F_D<MdmSetGRP> 			// �O���[�v�Z�b�g
{
public:
	MDGRPSET() : MdAryH_F_D<MdmSetGRP>() {};
};

class MDSCMSET : public MdAryH_F_D<MdmSetSCM> 			// �X�L�[�}�Z�b�g
{
public:
	MDSCMSET() : MdAryH_F_D<MdmSetSCM>() {};
};

class MDLYRSET : public MdAryH_F_D<MdmSetLYR> 			// ���C���[�Z�b�g
{
public:
	MDLYRSET() : MdAryH_F_D<MdmSetLYR>() {};
};

class MDBRISET : public MdAryH_F_D<MdmSetSCM> 			// ���ރZ�b�g
{
public:
	MDBRISET() : MdAryH_F_D<MdmSetSCM>() {};
};

class MDENTSET : public MdAryH_F_D<mdmEnt>				// �G���e�B�e�B�Z�b�g
{
public:
	MDENTSET() : MdAryH_F_D<mdmEnt>() {};
};

class MDPTSSET : public MdAryH_F_D<mdmEnt> 				// ���i�Z�b�g
{
public:
	MDPTSSET() : MdAryH_F_D<mdmEnt>() {};
};

class MDWINSET : public MdAryH_F_D<MdmWin>				// �E�B���h�E�Z�b�g
{
public:
	MDWINSET() : MdAryH_F_D<MdmWin>() {};
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MDMODEL_DO
	#pragma message( "<<< MdModel�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MdModel�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

//==========================================================================================
//	���f��
class DLL_EXPORT MdModel
{
public:
	MCHAR		m_cMdlNm[MDMSZ_NMMODEL];		// ���f����
	MDGRPSET	m_GrpBf;						// �O���[�v�Z�b�g
	MDSCMSET	m_ScmBf;						// �X�L�[�}�Z�b�g
	MDLYRSET	m_LyrBf;						// ���C���[�Z�b�g
	MDBRISET	m_BriBf;						// ���ރZ�b�g
	MDENTSET	m_EntBf;						// �G���e�B�e�B�Z�b�g
	MDPTSSET	m_PartsBf;						// ���i�Z�b�g
	MDWINSET	m_WinBf;						// �E�B���h�E�Z�b�g

	MgMat3E		m_MBaseTrans;					// ����W�ϊ��}�g���b�N�X
	MgMat3E		m_MCurTrans;					// �J�����g���W�ϊ��}�g���b�N�X

	MDID		m_idCurGrp;						// �J�����g�O���[�vID
	MDID		m_idCurWin;						// �J�����g�E�B���h�EID
	MINT		m_itpCurWin;					// �J�����g�E�B���h�E�^�C�v ( 0:�R�c�A1�F�}��)
	MDID		m_idCurLyr;						// �J�����g���C���[ID
	MDID		m_idCurScm;						// �J�����g�X�L�[�}ID
	MINT		m_mdTenkai[28];					// �|���S���W�J�������[�h
												//	 0: openGL�Ή��A1:�����\��,�����}�`�������̂܂ܕԂ�											
												//	 1: �ʃx�N�g���t���@0:���� 1:�t��(default)
												//	 2: ���x�@0:�s��(����) 1:��(�~)  2:�ς��Ȃ�(���̓�)
												//	 3: box�L�^�̏�� 0:���L�^ 3:���rAJ�Œǉ� 6:��
												//	 4: ���x(�e���t�̗L��) 0:�� 1:�L
												//	 5: ���g�p
												//	 6:  ���_�x�N�g���̕t���w�� 1:�t�� !=1:��
												//	 7: �����̈����w��  0:�����̓R�s�[�Ȃ��@1:�����̓R�s�[����
												//	 8: �~��~�ʂ�L�ӓ_��ɕϊ�����@1:�ϊ�����(default)�@2:�ϊ����Ȃ�
												//	 9: �X�v���C���̕������� 1:�ȗ��ɂ�镪�� 2:������
												//	10: �ʂ̕\��  1:���b�V���ŏo�́@1�ȊO�F���b�V���o�͂Ȃ�
												//	11: �}�b�s���O�@�@���g�p
												//	12: box���o�� 0:���� 1:���o�� 2:BOX�̂݁@�Q:agml2
												//	13: �ʂ̕����Ɋւ������   1:�ʁ�32�_�ȓ��̓ʖ�  2:���ʁ��ʖ�  3:�ʁ�������
												//	14: ���g�p
												//	15: �~�Ȃǂ̕����t���O
												//	16: �����̏o�͕��@�@-1:���ŏo�� 0:�ʂŏo�� 1:���̂܂� 2:���@�������̂܂�
												//	17: �ʂ̏o�̓��[�h 0:�ʂŎ��o��   1:���Ŏ��o��   2:�_�Ŏ��o��
												//	18: "�}�`�̃`�F�b�N���@�@
												//       0:�`�F�b�N�Ȃ��@
												//       1:�ʂɘc�݂�����ꍇ�G���[(st=5)�ɂ��� 
												//       2:�ʂɘc�݂�����ꍇ,�ĕ�������"
												//	19: 0:���a�Ɉˑ����镪���@�������g�p�@0�ł����g�p���Ă��Ȃ�
												//	20: �ʂ̕�����
												//	21: ��Ɩʐ}�`�@1�F�����𓾂�@2�F�_��𓾂�
												//	22:  �o�n�u�|�q�`�x�}�`�o�͂̐���
												//	23: ��Ɩʂ̍ו��x��(1,2,3,4,,, )�@����
												//	24:  ���ꕶ���̕ϊ�
												//	25:  true font �̊Ԋu�̐���
												//	26:  �e�N�X�`���Ή��}�`�o�͂̐���@0:off�@1:�o�͂���
												//	27: ���I�����}�ʐV�݃��[�h  0:default 1:�ό`���쒆�@2005/07/13

	MREAL	m_rmdTenkai[7];						// �|���S���W�J�����p�����[�^		
												// 100: �e���x�������l����̒P�ʒ����@agupzm = agupix*ax[7];�@�����f�[�^
												// 101: �s�N�Z���̑傫��
												// 102: ���g�p
												// 103: ���g�p
												// 104: ���g�p
												// 105: ��{�e���x����
												// 106: �����f�[�^�@�������̍ŏ��l�����߂�Ƃ��Ɏg�p
public:
	MdModel();
	~MdModel();

	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s);
};


} // namespace MC
