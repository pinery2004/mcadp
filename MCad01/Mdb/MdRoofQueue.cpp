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

#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

#define DLL_EXPORT_HAITIDB_DO
#include "MdLib.h"

#include "MhDefParts.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"
#include "MdList.h"
#include "MhLib.h"

#include "MgGrp.h"
#include "MhRoof.h"
#include "MdRoofQueue.h"

namespace MC
{

#if( TRACE_IO)
extern	int iCht2_IO;
extern	int iCrf2_IO;
extern	int iCzk_IO;
extern	int iCnw_IO;
#endif

static	MdRoofQueue	z_RoofQueue( 100, sizeof( MhRoofInfo));			// �ƃ��f���ۑ��̈�

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u�L���[�@�R���X�g���N�^�@�f�X�g���N�^
MdRoofQueue::MdRoofQueue( MINT nBk, MINT iSz)
	: MbListE( nBk, iSz)
{
}

MdRoofQueue::~MdRoofQueue( void)
{
	RemoveAll();
}

//////////////////////////////////////////////////////////////
//	�������X�g�̐擪�ɉ������R�[�h��ǉ�����B
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION MdRoofQueue::Push( MhRoofInfo *pRoofEn)
{
	MPOSITION	pos;
	pos = MbListE::Push( pRoofEn);
	pRoofEn->InitAllAtr();
	IeModel::MhSetModFIeMdl( true);
	return pos;
}

//////////////////////////////////////////////////////////////
//	�������X�g�̌���ɉ������R�[�h��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION MdRoofQueue::Inject( MhRoofInfo *pRoofEn)
{
	MPOSITION	pos;
	pos = MbListE::Inject( pRoofEn);
	pRoofEn->InitAllAtr();
	IeModel::MhSetModFIeMdl( true);
	return pos;
}

//////////////////////////////////////////////////////////////
//	�������X�g�̉������R�[�h��S�č폜����
void MdRoofQueue::RemoveAll( void)
{
	MPOSITION	pos1;
	MhRoofInfo	*pRoofEn;

	for (pRoofEn=(MhRoofInfo*)this->GetHead( &pos1); pRoofEn!=0; pRoofEn=(MhRoofInfo*)this->GetNext( &pos1)) {
		pRoofEn->FreeAllAtr();
	}
		
	MbListE::RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̉������C�j�V�����C�Y����
void HaitiDb::MdRoofDbInit( void)
{
	z_RoofQueue.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	�������폜����
//void MdRoofDelete( MPOSITION pPosition)
//{
//	MhRoofInfo*	pRoofEn = (MhRoofInfo*)(pPosition + z_RoofQueue.GetSizeOfHd());
//	pRoofEn->FreeAllAtr();
//	z_RoofQueue.RemoveAt( &pPosition);
//}

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u���폜����
void HaitiDb::MdRoofDelete(
						MPOSITION	i_pPosition		// [���i�z�u]�ʒu
				)
{
	MsBitSet	*pOptvRN, *pOptvDN;
	MhRoofInfo	*pRoofEn;

	pRoofEn = ( MhRoofInfo*)( i_pPosition + z_RoofQueue.GetSizeOfHd());
	pOptvRN = pRoofEn->GetPIOpt1();
	pOptvDN = pRoofEn->GetPIOpt2();

	if ( Option::MhDelOpt( &pOptvRN, &pOptvDN) < 3) {
		pRoofEn->FreeAllAtr();
		z_RoofQueue.RemoveAt( &i_pPosition);					// ���i�z�u�̂n�o�s�Q���폜�n�o�s�Q���L�͈͂ł��蕔�i�z�u���폜
	} else {
		pRoofEn->SetPIOpt1( pOptvRN);
		pRoofEn->SetPIOpt2( pOptvDN);							// �폜�Ώۂ̂n�o�s�Q��\���n�e�e�n�o�s�Q�ɐݒ�
	}
}

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
MPOSITION HaitiDb::MdRoofAdd(
						MhRoofInfo* io_pRoofEn,		// ���i�z�u�Ǘ����
						MINT		i_fOptv			// �n�o�s�Q�ǉ��t���O
													//		 0: �n�o�s�Q�ǉ����Ȃ�
													//		 1: �n�o�s�Q�ǉ�����
				)
{
	MsBitSet	*pOptv;
	MsBitSet	*pHstv;

	if ( i_fOptv == 1) {
		Option::MhAddOpt( &pOptv);								// Opt�Ή��@�V�K�ǉ����R�[�h
		io_pRoofEn->SetPIOpt1( pOptv);						// Opt�Ή�
		MhOpt::MhHistAdd( &pHstv);									// �����Ǘ��Ή��@�V�K�ǉ����R�[�h
		io_pRoofEn->SetPIVer( pHstv);						// �����Ǘ��Ή�
	}

#if( TRACE_IO)
	TRACE( " ��	================================================================\n ��	%d: MdRoofAdd\n ��	", iCrf2_IO++);
	for( int i=0; i<sizeof( MhRoofInfo)/4; i++) {
		TRACE( " %8x", ((int*)io_pRoofEn)[i]);
		if( i % 10 == 9)
			TRACE( "\n");

	}
	TRACE( "\n");
	iCnw_IO = 1;
#endif

	return z_RoofQueue.Inject( io_pRoofEn);
}

/////////////////////////////////////////////////////////////////////////////
//	������ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
//MPOSITION HaitiDb::MdRoofAdd( MhRoofInfo &RoofEn)
//{
//	return z_RoofQueue.Inject( &RoofEn);
//}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̉������擾����
MhRoofInfo* HaitiDb::MdRoofGet( MPOSITION pPosition)
{
	return (MhRoofInfo*)z_RoofQueue.GetAt( &pPosition);
}

static MPOSITION	z_RoofPos;

/////////////////////////////////////////////////////////////////////////////
//	�擪�̉������擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
MhRoofInfo* HaitiDb::MdGetHeadRoof( MPOSITION *o_pRoofPos)
{
	if ( o_pRoofPos)
		return (MhRoofInfo*)z_RoofQueue.GetHead( o_pRoofPos);
	else
		return (MhRoofInfo*)z_RoofQueue.GetHead( &z_RoofPos);
}

/////////////////////////////////////////////////////////////////////////////
//	���̉������擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
MhRoofInfo* HaitiDb::MdGetNextRoof( MPOSITION *io_pRoofPos)
{
	if ( io_pRoofPos)
		return (MhRoofInfo*)z_RoofQueue.GetNext( io_pRoofPos);
	else
		return (MhRoofInfo*)z_RoofQueue.GetNext( &z_RoofPos);
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̉����̗L���𒲂ׂ�

bool HaitiDb::MdIsNotEmptyRoof()								// true: �����L��/ false: ��������
{
	return z_RoofQueue.IsNotEmpty();
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�ɉ�����ǉ�����

void HaitiDb::MdInjectRoof(
						MhRoofInfo	*pRoofEn		// (I  ) �����Ǘ����
				)
{
	z_RoofQueue.Inject( pRoofEn);
}

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�̉������擾����

void HaitiDb::MdEjectRoof(
						MhRoofInfo *pRoofEn			// (  O) �����Ǘ����
				)
{
	z_RoofQueue.Eject( pRoofEn);
}

} // namespace MC
