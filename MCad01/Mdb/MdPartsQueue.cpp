//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#define DLL_EXPORT_HAITIDB_DO
#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

#define DLL_EXPORT_HAITIIN_DO
#include "MtInpAttr.h"
#include "MdLib.h"

#include "MmDefine.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"
#include "MdList.h"

#include "MdPartsQueue.h"
#define DLL_EXPORT_IEMODEL_DO
#include "MhPlcInfo.h"

namespace MC
{
#if( TRACE_IO)
extern	int iCht2_IO;
extern	int iCnw_IO;
#endif

static	MdPtsQueue	z_PtsQueue( 100, sizeof( mhPlcInfo));		// �ƃ��f���ۑ��̈�
static	bool		z_modIeModel = false;

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���C���t���O�̐ݒ�
void IeModel::MhSetModFIeMdl(
						bool	i_bMod			// �C���t���O
				)
{
	z_modIeModel = i_bMod;
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���C���t���O�̌���
bool IeModel::MhGetModFIeMdl()
{
	return z_modIeModel;
}

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u�L���[�@�R���X�g���N�^�@�f�X�g���N�^
MdPtsQueue::MdPtsQueue(
						MINT	i_nBk,			// 
						MINT	i_sz			// 
				)			
	: MbListE( i_nBk, i_sz)
{
}

MdPtsQueue::~MdPtsQueue( void)
{
	RemoveAll();
}

//////////////////////////////////////////////////////////////
//	���i�z�u�L���[�̐擪��[���i�z�u]��ǉ�����B
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION MdPtsQueue::Push(						// �ǉ����R�[�h�ʒu
						mhPlcInfo*	i_pPlcEn	// ���i�z�u�Ǘ����
				)
{
	MPOSITION	pos;
	pos = MbListE::Push( i_pPlcEn);
	i_pPlcEn->InitPtrTypeAtr();
	IeModel::MhSetModFIeMdl( true);
	return pos;
}


//////////////////////////////////////////////////////////////
//	���i�z�u�L���[�̌����[���i�z�u]��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION MdPtsQueue::Inject(					// �ǉ����R�[�h�ʒu
						mhPlcInfo*	i_pPlcEn	// ���i�z�u�Ǘ����
				)
{
	MPOSITION	pos;
	pos = MbListE::Inject( i_pPlcEn);
	i_pPlcEn->InitPtrTypeAtr();
	IeModel::MhSetModFIeMdl( true);
	return pos;
}

//////////////////////////////////////////////////////////////
//	���i�z�u�L���[��[���i�z�u]��S�č폜����
void MdPtsQueue::RemoveAll( void)
{
	MPOSITION	pos1;
	mhPlcInfo	*PlcEn;

	for (PlcEn=(mhPlcInfo*)this->GetHead( &pos1); PlcEn!=0; PlcEn= (mhPlcInfo*)this->GetNext( &pos1)) {
		PlcEn->FreeAllAtr();
	}
		
	MbListE::RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	�c�a���C�j�V�����C�Y����
void HaitiDb::MdPtsDbInit( void)
{
	z_PtsQueue.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	�G���e�B�e�B��POSITION�̃|�C���^�̍������߂�
//   pEnt = pPos + MdGetSizeOfHd();
MINT HaitiDb::MdGetSizeOfHd()
{
	return z_PtsQueue.GetSizeOfHd();
}

/////////////////////////////////////////////////////////////////////////////
//	[���i�z�u]���폜����
void HaitiDb::MdPtsDelete(
						MPOSITION	i_pPosition		// [���i�z�u]�ʒu
				)
{
	MINT		ist1;
	mhPlcInfo	*pPlcEn;
	MsBitSet	*pOptvRN, *pOptvDN;
	MsBitSet	HstvMod;
	MsBitSet	*pHstvR, *pHstvMod;
	mhPlcInfo	*pPlcEnM;										// �J�����g�o�[�W�����̂ݍ폜�Ώۂ̂n�o�s�Q���폜

	pPlcEn = ( mhPlcInfo*)( i_pPosition + z_PtsQueue.GetSizeOfHd());
	pOptvRN = pPlcEn->GetPIOpt1();
	pOptvDN = pPlcEn->GetPIOpt2();
	if ( Option::MhDelOpt( &pOptvRN, &pOptvDN) == 3) {					// Delete Opt �� Plc Opt	�i���i�z�u�̂n�o�s�Q���폜�n�o�s�Q���L�͈́j
																// (���i�z�u�̃I�v�V�����̏C��)
		ist1 = MhOpt::MhHistMod( pPlcEn, &pPlcEnM);
			pPlcEnM->SetPIOpt1( pOptvRN);						// 		���i�z�u�̃I�v�V�������C��
			pPlcEnM->SetPIOpt2( pOptvDN);						// 		�폜�Ώۂ̂n�o�s�Q��\���n�e�e�n�o�s�Q�ɐݒ�
	} else {													// Delete Opt �� Plc Opt	�i���i�z�u�̂n�o�s�Q���폜�n�o�s�Q���L�͈͂܂��͓���j
																// (���i�z�u���폜)
		pHstvR = pPlcEn->GetPIVer();

		if ( pHstvR == NULL) {									// �폜�Ώە��i�z�u�̗����Ǘ����R�s�[
			pHstvMod = NULL;
		} else {
			HstvMod = *pHstvR;
			pHstvMod = &HstvMod;
		}

		if ( MhOpt::MhHistDel( &pOptvRN) == 1) {						// 		�J�����g Ver == �z�u Ver('s)
			pPlcEn->FreeAllAtr();								// 			���i�z�u�̗����Ǘ��ƃJ�����g�o�[�W����������ł���
			z_PtsQueue.RemoveAt( &i_pPosition);					//			���i�z�u���폜
		} else {												//		�J�����g Ver �� �z�u Ver('s)
																// 			���i�z�u�̗����Ǘ�����J�����g�o�[�W�����̂ݍ폜
			if ( pHstvR == NULL) {								//			(�o�[�W�����̏C��)
				pPlcEn->SetPIVer( pOptvRN);						//			�V�K�ǉ��J�����g�o�[�W�����ȊO�n�m�̗����Ǘ��̃|�C���^���Z�b�g
			} else {
				*pHstvR = *pOptvRN;								//			�����Ǘ����J�����g�o�[�W�����n�e�e�ɏC��
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u���C������
void HaitiDb::MdPtsModify(
						mhPlcInfo* io_pPlcEnR,	// �C��������
						mhPlcInfo* *o_ppPlcEnM	// �C���敔��
				)
{
	MINT	ist1, ist2;
	mhPlcInfo	*pPlcEnM1;										// 
	mhPlcInfo	*pPlcEnM2;										// 

	ist1 = Option::MhModOpt( io_pPlcEnR, &pPlcEnM1);
	ist2 = MhOpt::MhHistMod( pPlcEnM1, &pPlcEnM2);
	*o_ppPlcEnM = pPlcEnM2;

}

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION HaitiDb::MdPtsAdd(
						mhPlcInfo*	i_pPlcEn,	// ���i�z�u�Ǘ����
						MINT		i_fdispCtrl	// �\������t���O
												//		 0: �n�o�s�Q��āE�W�J���ށE�����Ǘ����ނ�ǉ����Ȃ�
												//			�O���t�@�C������c�a�֎�荞�ݎ��ɂ��̂܂܏������ނ��ߎg�p����
												//		 1: �n�o�s�Q��āE�W�J���ށE�����Ǘ����ނ�ǉ�����
				)
{
	MPOSITION	iPos;

	MsBitSet	*pOptv;
	MsBitSet	*pHstv;

	if ( i_fdispCtrl == 1) {
		Option::MhAddOpt( &pOptv);										// Opt�Ή�	�V�K�ǉ����R�[�h
		i_pPlcEn->SetPIOpt1( pOptv);							// Opt�Ή�
//DD		MhAddTenkai( &bTenkai);									// �Z���W�J�Ή�	�V�K�ǉ����R�[�h
//DD		i_pPlcEn->SetPITenkai1( bTenkai);						// �Z���W�J�Ή�
		MhOpt::MhHistAdd( &pHstv);										// �����Ǘ��Ή�	�V�K�ǉ����R�[�h
		i_pPlcEn->SetPIVer( pHstv);								// �����Ǘ��Ή�
	}

	iPos = z_PtsQueue.Inject( i_pPlcEn);
	
//	MhCreateGrp
	
#if( TRACE_IO)
	TRACE( " ��	================================================================\n ��	%d: MdPtsAdd\n ��	", iCht2_IO++);
	for( int i=0; i<sizeof( mhPlcInfo)/4; i++) {
		if( i == 7 || i == 8) {
			TRACE( " ********");
		} else {
			TRACE( " %8x", ((int*)i_pPlcEn)[i]);
		}
		if( i % 10 == 9)
			TRACE( "\n");
	}
	TRACE( "\n");
	iCnw_IO = 1;
#endif

	return iPos;
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̕��i�z�u���擾����
mhPlcInfo* HaitiDb::MdPtsGet(
						MPOSITION	i_pPosition		// [���i�z�u]�ʒu
				)
{
	return ( mhPlcInfo*)z_PtsQueue.GetAt( &i_pPosition);
}

static MPOSITION	z_PtsPos;

/////////////////////////////////////////////////////////////////////////////
//	�擪�̕��i�z�u���擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
mhPlcInfo* HaitiDb::MdGetHeadPts(
						MPOSITION*	o_pPtsPos		// [���i�z�u]�ʒu
				)
{
	if ( o_pPtsPos)
		return (mhPlcInfo*)z_PtsQueue.GetHead( o_pPtsPos);
	else
		return (mhPlcInfo*)z_PtsQueue.GetHead( &z_PtsPos);
}

/////////////////////////////////////////////////////////////////////////////
//	���̕��i�z�u���擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
mhPlcInfo* HaitiDb::MdGetNextPts(
						MPOSITION*	io_pPtsPos		// [���i�z�u]�ʒu
				)
{
	if ( io_pPtsPos)
		return (mhPlcInfo*)z_PtsQueue.GetNext( io_pPtsPos);
	else
		return (mhPlcInfo*)z_PtsQueue.GetNext( &z_PtsPos);
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̕��i�z�u�̗L���𒲂ׂ�

bool HaitiDb::MdIsNotEmptyPts()							// ���i�z�u�̗L�� true: ���i�z�u�L��/ false: ���i�z�u����
{
	return z_PtsQueue.IsNotEmpty();
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�ɕ��i�z�u��ǉ�����

mhPlcInfo* HaitiDb::MdInjectPts(
						mhPlcInfo*	i_pPlcEn	// ���i�z�u�Ǘ����
				)
{
	MPOSITION	pPosition;

	pPosition = z_PtsQueue.Inject( i_pPlcEn);
	return (mhPlcInfo*)z_PtsQueue.GetAt( &pPosition);
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�̕��i�z�u���擾����

void HaitiDb::MdEjectPts(
						mhPlcInfo*	o_pPlcEn	// ���i�z�u�Ǘ����
				)
{
	z_PtsQueue.Eject( o_pPlcEn);
}

} // namespace MC