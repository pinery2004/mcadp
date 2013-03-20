//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmHist.cpp
//
//		�����Ǘ�����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MmDefine.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"

#include "MsBitSet.h"
#define DLL_EXPORT_MHHISTV_DO
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"

#include "MhPlcInfo.h"
#include "MdLib.h"

namespace MC
{

static	MhHistV		z_Verv;						// �o�[�W�����@�����Ǘ�

/////////////////////////////////////////////////////////////////////////////
//	�o�[�W�����Ǘ����
//  �X�^�e�B�b�N�����l

//bool		MhHistV::fcCng_NU;					// �J�����g�o�[�W�����̕ύX�L��
												//		(TRUE: �ύX�L��AFALSE: �ύX����)
bool		MhHistV::fcStd;						// �J�����g�o�[�W����==�����@�t���O
												//		(TRUE:�����AFALSE:�����ȊO�̃o�[�W����)
MsBitSet	MhHistV::vVerC;						// �J�����g�o�[�W����
MsBitSet	MhHistV::vVerB;						// �R�s�[���o�[�W����
MINT		MhHistV::nVer;						// �o�^�o�[�W������
CString		MhHistV::sVerC[MSZ_HISTB];			// �o�^�o�[�W����
CString		MhHistV::sVerB[MSZ_HISTB];			// �R�s�[���o�[�W����
CString		MhHistV::sVerD[MSZ_HISTB];			// �C������

///////////////////////////////////////////////////////////////////////////////
//	CString�̕�����𐮐��ɕϊ�����
CString MsCnvSCTime(							// "YYYY/MM/DD HH:SS"
						MINT	i_iMode,		// ���[�h�@1: "YYYY/MM/DD HH:SS"�`���ɕϊ�
						CTime&	i_theTime		// CTime ����
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�C�������Ǘ���������������
void MhHist::MmHistInit()
{
//	z_Verv.fcCng_NU = false;
	z_Verv.fcStd = true;
	z_Verv.vVerC = z_Verv.vVerB = MsBitSet( 0, 0, 0);  
	z_Verv.nVer = 1;
	z_Verv.sVerC[0] = "0.00"; 
	z_Verv.sVerB[0] = ""; 
	z_Verv.sVerD[0] = "";
	CTime theTime = CTime::GetCurrentTime();
	z_Verv.sVerD[0] = MsCnvSCTime( 33, theTime); 
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�C�������Ǘ������擾����
void MhHist::MmHistGet(
						MINT*		o_pnVer,
						CString*	*o_ppsVerC,
						CString*	*o_ppsVerB,
						CString*	*o_ppsVerD
				)
{
	*o_pnVer = z_Verv.nVer;
	*o_ppsVerC = z_Verv.sVerC;
	*o_ppsVerB = z_Verv.sVerB;
	*o_ppsVerD = z_Verv.sVerD;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�����t�o
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: ���o�[�W��������	-2: �V�o�[�W���������ɗL��
//						-3: �V�o�[�W��������
MINT MhHist::MmVerUp(
						CString		i_sVerB,
						CString		i_sVerC,
						MINT*		o_pnVer,
						CString*	*o_ppsVerC,
						CString*	*o_ppsVerB,
						CString*	*o_ppsVerD
				)
{
	MINT		ist = 0;
	MINT		ic, icf, ict;
	MhHistV		VerB;
	MhHistV		VerC;
	CTime		theTime;

	if ( i_sVerB == "") {
		icf = 0;
	} else {
		for ( ic=0; ic<z_Verv.nVer; ic++)
			if ( i_sVerB == z_Verv.sVerC[ic])
				break;
		if ( ic == z_Verv.nVer) {
			ist = -1;								// ���o�[�W�����Ȃ�
			MQUIT;
		}
		icf = ic;
	}
	if ( i_sVerC == "") {
		ist = -3;									// �V�o�[�W��������
		MQUIT;
	}
	for ( ic=0; ic<z_Verv.nVer; ic++)
		if ( i_sVerC == z_Verv.sVerC[ic])
			break;
	if ( ic < z_Verv.nVer) {
		ist = -2;									// �V�o�[�W���������ɗL��
		MQUIT;
	}
	ict = z_Verv.nVer++;
	z_Verv.sVerC[ict] = i_sVerC;
	z_Verv.sVerB[ict] = i_sVerB;
	theTime = CTime::GetCurrentTime();
	z_Verv.sVerD[ict] = MsCnvSCTime( 33, theTime); 

	z_Verv.vVerC.SetMask( ict);
	z_Verv.vVerB.SetMask( icf);

	if ( ict == 0) 
		z_Verv.fcStd = true;
	else
		z_Verv.fcStd = false;

	MPOSITION	pos1;
	mhPlcInfo	*PlcEn;
	MsBitSet*	pVer;

	for ( PlcEn = HaitiDb::MdGetHeadPts( &pos1); PlcEn!=0; PlcEn = HaitiDb::MdGetNextPts( &pos1)) {
		pVer = PlcEn->GetPIVer();
		if ( pVer) {
			if ( *pVer && z_Verv.vVerB) {
				*pVer |= z_Verv.vVerC;
				PlcEn->SetPIVer( pVer);
			}
		}
	}
	WindowCtrl::MmWndKReDraw();
exit:
	*o_pnVer = z_Verv.nVer;
	*o_ppsVerC = z_Verv.sVerC;
	*o_ppsVerB = z_Verv.sVerB;
	*o_ppsVerD = z_Verv.sVerD;
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�������ύX
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: ���o�[�W��������	-2: �V�o�[�W���������ɗL��
MINT MhHist::MmVerCng(
						CString		i_sVerB,
						CString		i_sVerC,
						MINT*		o_pnVer,
						CString*	*o_ppsVerC,
						CString*	*o_ppsVerB,
						CString*	*o_ppsVerD
				)
{
	MINT		ist = 0;
	MINT		ic, icf;
	MhHistV		VerB;
	MhHistV		VerC;
	for ( ic=0; ic<z_Verv.nVer; ic++)
		if ( i_sVerB == z_Verv.sVerC[ic] || i_sVerC == z_Verv.sVerB[ic])
			break;
	if ( ic == z_Verv.nVer) {
		ist = -1;									// ���o�[�W�����Ȃ�
		MQUIT;
	}
	icf = ic;
	for ( ic=0; ic<z_Verv.nVer; ic++)
		if ( i_sVerC == z_Verv.sVerC[ic] || i_sVerC == z_Verv.sVerB[ic])
			break;
	if ( ic < z_Verv.nVer) {
		ist = -2;									// �V�o�[�W���������ɗL��
		MQUIT;
	}
	for ( ic=0; ic<z_Verv.nVer; ic++) {
		if ( i_sVerB == z_Verv.sVerC[ic])
			z_Verv.sVerC[ic] = i_sVerC;
		if ( i_sVerB == z_Verv.sVerB[ic])
			z_Verv.sVerB[ic] = i_sVerC;
	}
	*o_pnVer = z_Verv.nVer;
	*o_ppsVerC = z_Verv.sVerC;
	*o_ppsVerB = z_Verv.sVerB;
	*o_ppsVerD = z_Verv.sVerD;

	z_Verv.vVerC.SetMask( icf);
	WindowCtrl::MmWndKReDraw();

exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�����I��
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: �I���o�[�W��������
MINT MhHist::MmSetVer(
						CString		sVerB,		//
						CString		sVerC,		//
						MINT*		m_pnVer,	//
						CString*	*m_ppsVerC,	//
						CString*	*m_ppsVerB,	//
						CString*	*m_ppsVerD	//
				)
{
	MINT		ist = 0;
	MINT		ic, icf;
	MhHistV		VerB;
	MhHistV		VerC;
	for ( ic=0; ic<z_Verv.nVer; ic++)
		if ( sVerC == z_Verv.sVerC[ic])
			break;
	if ( ic == z_Verv.nVer) {
		ist = -1;									// �I���o�[�W�����Ȃ�
		MQUIT;
	}
	icf = ic;
	*m_pnVer = z_Verv.nVer;
	*m_ppsVerC = z_Verv.sVerC;
	*m_ppsVerB = z_Verv.sVerB;
	*m_ppsVerD = z_Verv.sVerD;

	z_Verv.vVerC.SetMask( icf);
	WindowCtrl::MmWndKReDraw();
exit:
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�o�[�W�������擾����
//�y�Ԓl�z�o�[�W�����L��
//			TRUE : ����
//			FALSE: �����ȊO�̃o�[�W�����ݒ肠��
bool MhHist::MmVerGetC(
						MsBitSet	*o_pHst		// �J�����g�o�[�W����
				)
{
//	MsBitSet	z_Verv;

	if ( z_Verv.fcStd) 
		*o_pHst = MsBitSet( 1, 0, 0);							// ����
	else
		*o_pHst = z_Verv.vVerC;

//	TRACE1( "MmHistGet	z_Verv.vVerC %x \n", z_Verv.vVerC.GetVer());

	return z_Verv.fcStd;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�̗����Ǘ����J�����g�o�[�W�������܂ނ����ׂ�
//�y�Ԓl�z�J�����g�o�[�W�����܂݃t���O
//			TRUE : �܂�
//			FALSE: �܂܂Ȃ�
bool MhHist::MmVerChkC(
						MsBitSet	*i_pHstv	// �c�a���R�[�h��OPT�Q�Z�b�g
				)
{
	bool bst;

	if ( i_pHstv == 0){											// DB �n�o�s�Q�@�W��
		bst = TRUE;

	} else {
		if ( (*i_pHstv) && z_Verv.vVerC)
			bst = TRUE;
		else
			bst = FALSE;

//		MUINT	*iOptv = pOptv->GetSOB();
//		TRACE3( "MhOptV::MmOptChkC	DB Opt %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//		iOptv = z_Optv.bmCurRGOptSet.GetSOB();
//		TRACE3( "z_Optv.bmCurRGOptSet %x, %x, %x		", iOptv[0], iOptv[1], iOptv[2]);
//		if ( bst) TRACE0 ( "bst TRUE\n"); else  TRACE0 ( "bst FALSE\n"); 
	}
	return bst;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�C�����̃��R�[�h�����^�C�v���擾����
//		�@�i�C�����̃o�[�W�����̗����Ǘ��ƃJ�����g�o�[�W�����Y���̗����Ǘ���
//		�@	��r���Ăǂ̂悤�ȏC�������̃��R�[�h�ł��邩���ׂ�j
//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
//			1: �C�������R�[�h�̗����Ǘ� �� �����ݑΏۂ̗����Ǘ�
//				�o�[�W�����̕ύX�͕s�v�ŁA�����C���̂ݕύX����
//			3: ���̑� ( �C�������R�[�h�̗����Ǘ� �� �J�����g�o�[�W�����Y���̗����Ǘ� )
//				�C�������R�[�h�̓o�[�W�����̂ݕύX���A�V���������ݑΏۂ̗����Ǘ��̃o�[�W����������
//				�R�s�[���R�[�h���쐻�����̑�����ύX����
//

MINT MhHist::MmHistModChk(							// �C����̃��R�[�h�\���R�[�h
						MsBitSet*	*io_ppHstvMod,	// �C�������R�[�h�ɐݒ肷�闚���Ǘ��@(�C����̃��R�[�h�\���R�[�h >= 2 �̎��L��)
						MsBitSet*	*o_ppHstvAdd	// �C���p�ɒǉ����R�[�h�̗����Ǘ��@(�C����̃��R�[�h�\���R�[�h == 3 �̎��L��)
				)
{
	MINT		ist;
	MsBitSet	*pHstvAdd;

	if ( (*io_ppHstvMod == NULL && z_Verv.fcStd) ||					// �J�����g�o�[�W���� == �����ŏC�������R�[�h�̗����Ǘ�������
		(*io_ppHstvMod != NULL && **io_ppHstvMod == z_Verv.vVerC)) {	// �܂��́A�C�������R�[�h�̗����Ǘ� == �����ݗ����Ǘ�
		ist = 1;
	} else {
		if ( *io_ppHstvMod == NULL) {
			*io_ppHstvMod = (MsBitSet*)new char[sizeof(MsBitSet)];	// �C�����̃��R�[�h�ɗ����Ǘ���ǉ�
			**io_ppHstvMod = ~z_Verv.vVerC;							// �S�o�[�W���� �| �����ݑΏۃo�[�W����
		} else {
//			*ppHstvMod = pHstvR;									// �C�����̃��R�[�h�̗����Ǘ����C��
			**io_ppHstvMod = **io_ppHstvMod & ~z_Verv.vVerC;		// �C�����o�[�W���� �| �����ݑΏۃo�[�W����
		}

		if ( (**io_ppHstvMod).IsNull()) {							// �C�������R�[�h�̗����Ǘ� �� �����ݑΏۃo�[�W����
			ist = 2;
//			**ppHstvMod = z_Verv.vVerC;								// �C���Ώۂ̗����Ǘ��ݒ�
			ASSERT( false);											// �����Ǘ��@�J�����g�o�[�W�����G���[�@<ERROR>
		} else {													// ���̑� �C�������R�[�h�̗����Ǘ� �� �i�����ݗ����Ǘ� �� �C�������R�[�h�̗����Ǘ�)
			pHstvAdd = (MsBitSet*)new char[sizeof(z_Verv.vVerC)];
			*pHstvAdd = z_Verv.vVerC;								// �C���Ώۂ̗����Ǘ��ݒ�
			*o_ppHstvAdd = pHstvAdd;
			ist = 3;
		}
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�폜���ɐݒ肷��o�[�W�����R�[�h���擾����
//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
//			1 : �폜���o�[�W�����͏����݃o�[�W�����Ɠ���̏ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			3 : �폜���o�[�W�����ɏ����݃o�[�W�����ȊO�̃o�[�W�������܂ޏꍇ�ŁA
//				�J�����g�o�[�W�����̂ݍ폜����B
//				�J�����g�o�[�W�����ȊO�̃o�[�W���������́A�폜�����R�[�h�����̂܂܎c���B�i�o�[�W�����R�[�h�̂ݏC���j
//				�i�o�[�W�����R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
//
MINT MhHist::MmHistDelChk(							// �폜��̃��R�[�h�\���R�[�h
//						MsBitSet	*i_pHstvR,		// �폜�����R�[�h�̗����Ǘ�
//													// �폜�ヌ�R�[�h�̗����Ǘ��ɕύX����
						MsBitSet*	*io_ppHstvMod	// �폜��̃��R�[�h�̗����Ǘ�
				)
{
	MINT		ist;
//	MsBitSet	HstvMod;

	if ( z_Verv.fcStd && *io_ppHstvMod == NULL ||				// �J�����g�o�[�W���� == �����ŁA(�폜�����R�[�h�̗����Ǘ�������
		(*io_ppHstvMod != NULL &&								// �܂��́A�폜�����R�[�h�̗����Ǘ� == �����ݗ����Ǘ�)
		 (**io_ppHstvMod) == z_Verv.vVerC)) {
		ist = 1;
	} else {
		if ( *io_ppHstvMod == NULL) {
			*io_ppHstvMod =  (MsBitSet*)new char[sizeof(z_Verv.vVerC)];	// �폜��̃��R�[�h�ɕ\���n�m�����Ǘ���ǉ�
			**io_ppHstvMod = ~z_Verv.vVerC;						// �A�ݒ�
		} else {
			**io_ppHstvMod = **io_ppHstvMod & ~z_Verv.vVerC;	// �폜���̃��R�[�h�̗����Ǘ� �| �����ݗ����Ǘ�
		}

		if ( (**io_ppHstvMod).IsNull()) {						// �폜�����R�[�h�̗����Ǘ� �� �����ݗ����Ǘ�
			ist = 2;
			ASSERT( false);										// �����Ǘ��@�J�����g�o�[�W�����G���[�@<ERROR>
		} else {
			ist = 3;
		}
	}
	return ist;
}

} // namespace MC