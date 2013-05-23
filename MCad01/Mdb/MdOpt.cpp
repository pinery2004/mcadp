//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMatD.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MhInpPlcParts.h"

#define DLL_EXPORT_MHOPTV_DO
#include "MdOpt.h"
#include "MdLib.h"

#define	MH_ALL_BITS		0xFFFFFFFF

namespace MC
{

static	MhOptV	z_Optv;
/////////////////////////////////////////////////////////////////////////////
//	�n�o�s�Q�Ǘ����
//  �X�^�e�B�b�N�����l
bool		MhOptV::fcDB;						// �J�����g�I���n�o�s�Q��DB�֔��f�t���O
												//		(TRUE:���f�ρAFALSE: �����f)
bool		MhOptV::fcStd;						// �J�����g�I���n�o�s�Q==�W���@�t���O
												//		(TRUE:�W���AFALSE:�W���ȊO�̂n�o�s�Q�L��)
bool		MhOptV::fDispStd;					// �J�����g�I��W���\���n�m�t���O
												//		(TRUE:�W���\���n�m�AFALSE:�W���\���n�e�e)
MhOpt		MhOptV::bmCurGOpt;					// �J�����g�I���n�o�s�Q
MsBitSet	MhOptV::bmCurRGOptSet;				// �J�����g�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g
MsBitSet	MhOptV::bmCurWGOptSet;				// �J�����g�I���n�o�s�Q�ŏ����ݑΏۂ�OPT�Q�Z�b�g
MsBitSet	MhOptV::bmCurGOptSet;				// �J�����g�I���n�o�s�Q������OPT�Q�Z�b�g
MINT		MhOptV::nbmGOpt;					// �o�^OPT�Q��
MhOpt		MhOptV::bmGOpt[MSZ_OPTVB];			// �o�^OPT�Q

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�n�o�s�Q�Ǘ���������������
void MhOptV::MmOptInit()
{
	z_Optv.fcDB = FALSE;										// 
	z_Optv.fcStd = TRUE;

	z_Optv.fDispStd = TRUE;
	z_Optv.bmCurGOpt = MhOpt( 0);
	z_Optv.bmCurGOptSet = MsBitSet( 0, 0, 0);
	z_Optv.bmCurRGOptSet = z_Optv.bmCurWGOptSet = MsBitSet( 0, 0, 0);
	z_Optv.nbmGOpt = 1;											// �W���̂ݓo�^��
	z_Optv.bmGOpt[0] = MhOpt( 1);								// �W���̂ݓo�^��
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g���擾����
MsBitSet	MhOptV::MhOptBScRGet()
{
	return z_Optv.bmCurRGOptSet;
}
						
/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�I���n�o�s�Q�ŏ����ݑΏۂ�OPT�Q�Z�b�g���擾����
MsBitSet	MhOptV::MhOptBScWGet()
{
	return z_Optv.bmCurWGOptSet;
}
						
/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�I���n�o�s�Q������OPT�Q�Z�b�g���擾����
MsBitSet	MhOptV::MhOptBScGet()
{
	return z_Optv.bmCurGOptSet;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�n�o�s�Q�I���`�F�b�N�{�b�N�X�̑I���󋵂��J�����g�I���n�o�s�Q�ɔ��f����
void MhOptV::MmOptSet(
						MINT		i_nOpt,		// �`�F�b�N�{�b�N�X�ԍ�
												//		0 : �W���\���I�t
												//	   >0 : �n�o�s�Q�ԍ�
						MINT		i_iChk		// �`�F�b�N�{�b�N�X�I����
				)
{
	MsBitSet	OptvWDumy;
	MINT		iOptN;
	MhOpt		bOpt;

	if ( i_nOpt == 0) {
		if ( i_iChk == BST_CHECKED) {
			z_Optv.fDispStd = FALSE;
		} else {
			z_Optv.fDispStd = TRUE;
		}
	} else {
		iOptN = i_nOpt;
		bOpt = 1 << iOptN;
		if ( i_iChk == BST_CHECKED) {
			z_Optv.bmCurGOpt |= MhOpt( bOpt);					// �J�����g�I���n�o�s�Q�ɊY���I�v�V������ݒ�
		} else {
			z_Optv.bmCurGOpt &= ~bOpt;							// �J�����g�I���n�o�s�Q�̊Y���I�v�V����������
		}
	}
	z_Optv.fcStd = MhOptV::MmOptIncSrch( z_Optv.bmCurGOpt);
	z_Optv.fcDB = FALSE;										// �ύX

//D	TRACE1( "MhOptV::MmOptSet ********	z_Optv.cb %x		", z_Optv.cb);
//D	MUINT	*iOptv = z_Optv.bmCurRGOptSet.GetSOB();
//D	TRACE3( "z_Optv.bmCurRGOptSet %x, %x, %x\n", iOptv[0], iOptv[1], iOptv[2]);

	WindowCtrl::MmWndKReDraw();
/*
//-------------------   �R�����\��  -----------------------------------

	//�@�R�����\���͈�U����
	MmWndInfo* pWndInfo = MmWndKFind( 2, MTHEIMENZU, 1, 1);
	if ( pWndInfo) 
		pWndInfo->m_pChildFrm->SendMessage(WM_CLOSE);

	//	���f����ǂݍ��ݕ\������
//	ist1 = MhMdlLoad( PathO);
//	MmWndKReDrawAll();

	//�@�R�����\��������Ă����ꍇ�͐V�����f�[�^�ōēx�\������
	if ( pWndInfo) 
		z_MCadApp.CreateWnd( 2, MTHEIMENZU, 1, 1);
//		pWndInfo->m_pChildFrm->SendMessage(WM_CREATE);
//		z_MCadApp.OnView2On();

//------------------------------------------------------
*/
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�I���n�o�s�Q���擾����
//�y�Ԓl�z�n�o�s�Q�L��
//			TRUE : �W��
//			FALSE: �W���ȊO�̃I�v�V�����ݒ肠��
bool MhOptV::MmOptGetC(
						MhOpt*		o_pOpt		// �J�����g�I���n�o�s�Q
				)
{
	if ( z_Optv.fcStd) 
		*o_pOpt = MhOpt( 1);									// �W��
	else
		*o_pOpt = z_Optv.bmCurGOpt;

//D	TRACE1( "MmOptGet	z_Optv.cb %x \n", z_Optv.cb.GetOpt());

	return z_Optv.fcStd;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h��OPT�Q�Z�b�g���J�����g�I���n�o�s�Q���܂ނ����ׂ�
//�y�Ԓl�z�I���n�o�s�Q�܂݃t���O
//			TRUE : �܂�
//			FALSE: �܂܂Ȃ�
bool MhOptV::MmOptCheckC(
						MsBitSet*	i_pOptv		// �c�a���R�[�h��OPT�Q�Z�b�g
				)
{
	bool bst;
	MsBitSet	Optv;

	if ( i_pOptv == 0){											// DB �n�o�s�Q�@�W��
		if ( z_Optv.fDispStd)									// �J�����g�I��W���\���n�m�t���O
			bst = TRUE;
		else
			bst = FALSE;

	} else {
		if ( ( *i_pOptv) && z_Optv.bmCurRGOptSet)
			bst = TRUE;
		else
			bst = FALSE;

//D		MUINT	*iOptv = pOptv->GetSOB();
//D		TRACE3( "MhOptV::MmOptCheckC	DB Opt %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//D		iOptv = z_Optv.bmCurRGOptSet.GetSOB();
//D		TRACE3( "z_Optv.bmCurRGOptSet %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//D		if ( bst) TRACE0 ( "bst TRUE\n"); else  TRACE0 ( "bst FALSE\n"); 
	}
	return bst;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�̕\���n�e�eOPT�Q�Z�b�g���J�����g�I���n�o�s�Q���܂ނ����ׂ�
//�y�Ԓl�z�I���n�o�s�Q�܂݃t���O
//			TRUE : �܂�		�\���n�e�e
//			FALSE: �܂܂Ȃ�	�\���n�m
bool MhOptV::MmOptOffCheckC(
						MsBitSet*	i_pOptv		// �c�a���R�[�h��OPT�Q�Z�b�g
				)
{
	bool	bst;

	if ( i_pOptv == 0){											// DB �n�o�s�Q�@�W��
			bst = FALSE;

	} else {
		if ( ( *i_pOptv) && z_Optv.bmCurRGOptSet)
			bst = TRUE;
		else
			bst = FALSE;

//D		MUINT	*iOptv = pOptv->GetSOB();
//D		TRACE3( "MhOptV::MmOptOffCheckC	DB Opt %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//D		iOptv = z_Optv.bmCurRGOptSet.GetSOB();
//D		TRACE3( "z_Optv.bmCurRGOptSet %x, %x, %x \n", iOptv[0], iOptv[1], iOptv[2]);
	}

	return bst;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�C����̃��R�[�h�\���R�[�h���擾����
//		�@�i�C�����̂n�o�s�Q��OPT�Q�Z�b�g�ƃJ�����g�I���n�o�s�Q�̏����ݑΏ�OPT�Q�Z�b�g��
//		�@	��r���Ăǂ̂悤�ȏC�������̃��R�[�h�ł��邩���ׂ�j
//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
//			1: �C�������R�[�h��OPT�Q�Z�b�g ���� �����ݑΏۂ�OPT�Q�Z�b�g
//				�n�o�s�Q�̕ύX�͕s�v�ŁA�����C���̂ݕύX����
//			2: �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g
//				�n�o�s�Q�̕ύX�Ƒ����ύX���遨�n�o�s�Q�̕ύX�͕s�v�ŁA�����C���̂ݕύX����i1�Ɠ����j
//			3: ���̑� ( �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g || �����I�ɏd�Ȃ��Ă��� )
//				�i�C�������R�[�h��OPT�Q�Z�b�g �� �i�����ݑΏۂ�OPT�Q�Z�b�g �� �C�������R�[�h��OPT�Q�Z�b�g)�j
//				�C�������R�[�h�͂n�o�s�Q��ύX���A�V���������ݑΏۂ�OPT�Q�Z�b�g�̂n�o�s�Q������
//				�R�s�[���R�[�h���쐻�����̑�����ύX����
//
MINT MhOptV::MmOptModCheck(									// �C����̃��R�[�h�\���R�[�h
						MsBitSet*	*io_ppOptvRN,	// �C���O�ヌ�R�[�h��OPT�Q�Z�b�g�@	(�C����̃��R�[�h�\���R�[�h >= 2 �̎��L��)
						MsBitSet*	*o_ppOptvWN,	// �C���p�ɒǉ����R�[�h��OPT�Q�Z�b�g�@(�C����̃��R�[�h�\���R�[�h == 3 �̎��L��)
						MhOptV*		*o_ppOptv		// �n�o�s�Q�Ǘ����
				)
{
	MINT		ist;
	MsBitSet	*pOptvR;
	MsBitSet	OptvRN;

	pOptvR = *io_ppOptvRN;
	if ( ( pOptvR == NULL && z_Optv.fcStd) ||					// �J�����g�I���n�o�s�Q == �W�� (���̏ꍇ�͕W���̂ݕ\������Ă���폜�����R�[�h���W��)
		(pOptvR != NULL &&										// �J�����g�I���n�o�s�Q == �C�������R�[�h�n�o�s�Q
		 *pOptvR == z_Optv.bmCurWGOptSet)) {
		ist = 1;
	} else {
		if ( pOptvR == NULL) {
			*io_ppOptvRN = ( MsBitSet*)new char[sizeof( z_Optv.bmCurWGOptSet)];	// �C�����̃��R�[�h��OPT�Q�Z�b�g��ǉ�
			**io_ppOptvRN = ~z_Optv.bmCurWGOptSet;
			ist = 3;
		} else {
			OptvRN = *pOptvR & ~z_Optv.bmCurWGOptSet;			// �C�����n�o�s�Q �| �����ݑΏۂ�OPT�Q�Z�b�g

			if ( OptvRN.IsNull()) {								// �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g
				ist = 2;
				goto exit;
			} else {											// ���̑� �C�������R�[�h��OPT�Q�Z�b�g �� �i�����ݑΏۂ�OPT�Q�Z�b�g �� �C�������R�[�h��OPT�Q�Z�b�g)
				**io_ppOptvRN = OptvRN;
				ist = 3;
			}
		}
		*o_ppOptvWN = ( MsBitSet*)new char[sizeof( z_Optv.bmCurWGOptSet)];
		**o_ppOptvWN = z_Optv.bmCurWGOptSet;					// �C���Ώۂ�OPT�Q�Z�b�g�ݒ�
		*o_ppOptv = &z_Optv;
	}
exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�폜���ɐݒ肷��n�o�s�Q�R�[�h���擾����
//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
//			1 : �폜���n�o�s�Q�͏����݂n�o�s�Q�Ɠ���̏ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			2 :	�폜���n�o�s�Q�͏����݂n�o�s�Q�ɑS�Ċ܂܂ꂩ�ǉ��n�o�s�Q������ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			3 : �폜���n�o�s�Q�ɏ����݂n�o�s�Q�ȊO�̂n�o�s�Q���܂ޏꍇ�ŁA
//				�����݂n�o�s�Q�ȊO�̂n�o�s�Q�����́A�폜�����R�[�h�����̂܂܎c���n�o�s�Q�R�[�h�̂ݏC������B
//				�i�{�֐���**ppOptvRN,**ppOptvDN���C��)
//				�i�n�o�s�Q�R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
//
MINT MhOptV::MmOptDelCheck(							// �폜��̃��R�[�h�\���R�[�h
						MsBitSet*	*io_ppOptvRN,	// �폜�O��̃��R�[�h�̕\���n�mOPT�Q�Z�b�g
						MsBitSet*	*o_ppOptvDN		// �폜�O��̃��R�[�h�̕\���n�e�eOPT�Q�Z�b�g
				)
				
				
{
	MINT		ist;
	MsBitSet	*pOptvR;
	MsBitSet	OptvRN;

	pOptvR = *io_ppOptvRN;
	if ( z_Optv.fcStd ||											// �J�����g�I���n�o�s�Q == �W�� (���̏ꍇ�͕W���̂ݕ\������Ă���폜�����R�[�h���W��)
		( pOptvR != NULL &&											// �J�����g�I���n�o�s�Q �� �폜�����R�[�h��OPT�Q�Z�b�g
		  *pOptvR == z_Optv.bmCurWGOptSet)) {
		ist = 1;
	} else {
		if ( pOptvR == NULL) {
			 *io_ppOptvRN = ( MsBitSet*)new char[sizeof( z_Optv.bmCurWGOptSet)];	// �폜��̃��R�[�h�ɕ\���n�mOPT�Q�Z�b�g��ǉ�
			 **io_ppOptvRN = ~z_Optv.bmCurWGOptSet;					// �A�ݒ�
			ist = 3;
		} else {
//D			if ( *pOptvR == z_Optv.bmCurWGOptSet) {					// �����ݑΏۂ�OPT�Q�Z�b�g == �폜�����R�[�h��OPT�Q�Z�b�g
//D				ist = 1;
//D				goto exit;
//D			} else { 
				OptvRN = *pOptvR & ~z_Optv.bmCurWGOptSet;			// ( �폜���̃��R�[�h��OPT�Q�Z�b�g �| �����ݑΏۂ�OPT�Q�Z�b�g)

				if ( OptvRN.IsNull()) {								// �����ݑΏۂ�OPT�Q�Z�b�g �� �폜�����R�[�h��OPT�Q�Z�b�g
					ist = 2;
					goto exit;
				} else {											// ���̑�
					**io_ppOptvRN = OptvRN;							// �폜���̃��R�[�h��OPT�Q�Z�b�g���C��
					ist = 3;
				}
//D			}
		}

		if ( *o_ppOptvDN == NULL) {
			 *o_ppOptvDN = (MsBitSet*)new char[sizeof( z_Optv.bmCurWGOptSet)];	// �폜��̃��R�[�h�ɕ\���n�e�eOPT�Q�Z�b�g��ǉ�
			 **o_ppOptvDN = z_Optv.bmCurWGOptSet;					// �A�ݒ�
		} else {
			**o_ppOptvDN |= z_Optv.bmCurWGOptSet;					// �폜��̃��R�[�h�ɕ\���n�e�eOPT�Q�Z�b�g��ݒ�
		} 
	}
exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�^OPT�Q���I���n�o�s�Q��������������Βǉ��o�^����
//		�@�I���n�o�s�Q��S�Ċ܂ޓo�^OPT�Q�̏W�܂�ɑ�������
//		  OPT�Q�Z�b�g��ǉ�����
//�y�Ԓl�z������
//			0:�����ł���ǉ�
//			1:�L��
//
MINT MhOptV::MmOptSrch(
						MhOpt		i_Opt		// �����n�o�s�Q
				)
{
	MINT	ist;
	MINT	id;

	ist = 1;
	if ( !z_Optv.fcDB) {										// �J�����g�I���n�o�s�Q�ɕύX����
		for ( id=0; id<z_Optv.nbmGOpt; id++) {					// �J�����g�I���n�o�s�Q��{�o�^OPT�Q}��茟��
			if ( i_Opt == z_Optv.bmGOpt[id])
				break;
		}

		if ( id >= z_Optv.nbmGOpt) {							// ���o�^�ł���o�^����
			ASSERT( id < 96);									// �o�^OPT�Q�I�[�o�[�t���[�G���[�@<ERROR>
			z_Optv.bmGOpt[id] = i_Opt;
			z_Optv.nbmGOpt++;
			ist = 0;
		}

		z_Optv.bmCurGOptSet.SetMask( id);
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g��
//		  �����ݑΏۂ�OPT�Q�Z�b�g�����߂�
//�y�Ԓl�z
//			TRUE  : �I���n�o�s�Q�͕W��
//			FALSE : �I���n�o�s�Q�ɕW���ȊO�̃I�v�V�����ݒ肠��
//
bool MhOptV::MmOptIncSrch(
						MhOpt		i_Opt		// �I���n�o�s�Q
				)
{
	bool		bst;
	MINT		ic;
	MINT		id;
	MsBitSet	OptvF;
	
	MINT		nOptIdB = 0;					// �Ǎ��ݑΏۂn�o�s�Q��
	MINT		iOptIdB[96];					// �Ǎ��ݑΏۂn�o�s�Q�̏W��

	if ( i_Opt.IsStd()) {										// �I���n�o�s�Q==�W��(0|1)
		bst = TRUE;
		if ( z_Optv.fDispStd) 									// �W���\���n�m
			z_Optv.bmCurRGOptSet = MsBitSet( 1, 0, 0);			//		�Ǎ��ݑΏۂ�OPT�Q�Z�b�g = ( 1, 0, 0)
		else													// �W���\���n�e�e
			z_Optv.bmCurRGOptSet = MsBitSet( 0, 0, 0);			//		�Ǎ��ݑΏۂ�OPT�Q�Z�b�g = ( 0, 0, 0)
		z_Optv.bmCurWGOptSet = MsBitSet( 0, 0, 0);				// �����ݑΏۂ�OPT�Q�Z�b�g = ( 0, 0, 0)
	} else {
	// �Ǎ��ݑΏۂ�OPT�Q�Z�b�g�����߂�
		for ( id=0; id<z_Optv.nbmGOpt; id++) {					// �o�^OPT�Q���J�����g�I���n�o�s�Q�Ɋ܂܂����̂�S�ċ��߂�
			if ( z_Optv.bmGOpt[id] == i_Opt) {					// ���������̂�����ꍇ�́A���̃I�v�V�����Q�݂̂�ǂݍ��ݑΏۂƂ���
				iOptIdB[0] = id;
				nOptIdB = 1;
				break;
			} else {
				if ( z_Optv.bmGOpt[id] == ( i_Opt & z_Optv.bmGOpt[id]))	// �o�^OPT�Q[id]���J�����g�I���n�o�s�Q�Ɋ܂܂��
					iOptIdB[nOptIdB++] = id;
			}
		}
		z_Optv.bmCurRGOptSet = MsBitSet( 1, 0, 0);
		for ( ic=0; ic<nOptIdB; ic++) {
			if ( iOptIdB[ic] >= 0) {							// �I���n�o�s�Q�Ɋ܂܂��S�o�^OPT�Q������OPT�Q�Z�b�g�擾
				OptvF.SetMask( iOptIdB[ic]);
				z_Optv.bmCurRGOptSet |= OptvF;
			}
		}
		// �����ݑΏۂ�OPT�Q�Z�b�g�����߂�
		z_Optv.bmCurWGOptSet = MsBitSet( 0, 0, 0);
		for ( id=0; id<z_Optv.nbmGOpt; id++) {
			if ( i_Opt == (z_Optv.bmGOpt[id] & i_Opt)) {		// �I���n�o�s�Q���܂ޑS�o�^OPT�Q������OPT�Q�Z�b�g�擾
				OptvF.SetMask( id);
				z_Optv.bmCurWGOptSet |= OptvF;
			}
		}
		bst = FALSE;
	}

	return bst;
}

/////////////////////////////////////////////////////////////////////////////
// �J�����g�I���n�o�s�Q�ɑ�����OPT�Q�Z�b�g��DB�̎Q�ƑΏۃ��R�[�h�֔��f
void MhOptV::MmOptAddDB()
{
	MPOSITION	pos1;
	mhPlcParts*	pPlcEn;
	MsBitSet	*pOptv;

	MINT	iDB = 0;
	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0; pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {
		pOptv = pPlcEn->GetPIOpt1();
		if ( pOptv == NULL) {		// �I�v�V�����ݒ薳���̎Q�ƑΏۃ��R�[�h
		} else if ( MhOptV::MmOptCheckC( pOptv)) {						// �n�o�s�Q�L��̎Q�ƑΏۃ��R�[�h
			*pOptv |= z_Optv.bmCurGOptSet;
		} else {
		}


		pOptv = pPlcEn->GetPIOpt2();
		if ( pOptv == NULL) {		// �I�v�V�����ݒ薳���̎Q�ƑΏۃ��R�[�h
		} else if ( MhOptV::MmOptOffCheckC( pOptv)) {						// �n�o�s�Q�L��̎Q�ƑΏۃ��R�[�h
			*pOptv |= z_Optv.bmCurGOptSet;
		} else {
		}

	}
	z_Optv.fcDB = TRUE;											// �c�a�I�v�V�������f�ς�
}

} // namespace MC
