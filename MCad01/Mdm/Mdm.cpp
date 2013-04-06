//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.cpp
//
//		���f���f�[�^�x�[�X
//
//
//  K.Matsu           01/06/08    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"

#define DLL_EXPORT_MDMODEL_DO
#define DLL_EXPORT_MDM_DO
#include "MdModel.h"
#include "MdmDB.h"
#define DLL_EXPORT_MDM_DO
#include "Mdm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

CArray<MdModel*>	Mdm::ms_pMdl;			// ���f�����X�g
MDID				Mdm::ms_idCurMdl;		// �J�����g���f��ID
MdModel*			Mdm::ms_pCurMdl;		// �J�����g���f��

//===========================================================================
//�y�@�\�z���f��DB������������
//�y�Ԓl�z�Ȃ�
MINT Mdm::MdmInitialize( void)
{
	MDID idMdl;
	idMdl = AddModel( Mstr( ""));
	SetCurModel( idMdl);
	return 0;
}

//===========================================================================
//�y�@�\�z���f��DB���������
//�y�Ԓl�z�Ȃ�
MINT Mdm::MdmTerminate( void)
{
	MINT iC;

	for ( iC=0; iC<Mdm::ms_pMdl.GetCount(); iC++) {
		delete( Mdm::ms_pMdl[iC]);
	}
	return 0;
}

//===========================================================================
//�y�@�\�z���f����ǉ����A���f��ID���擾
//�y�Ԓl�z���f��ID
MDID Mdm::AddModel(
					MCHAR*	i_cMdlNm		// ���f����
					)
{
	MDID idMdl;
	MdModel* pMdl = new MdModel;
	Mdm::ms_pMdl.Add( pMdl);
	idMdl = (MDID)Mdm::ms_pMdl.GetCount();
	return idMdl; 
}

//===========================================================================
//�y�@�\�z���f�������烂�f��ID���擾����
//�y�Ԓl�z���f��ID
MDID Mdm::GetModelId(
					MCHAR*	i_cMdlNm		// ���f����
					)
{
	MDID idMdl = 0;
	for ( int iC=0; iC<ms_pMdl.GetCount(); iC++) {
		if ( Mstrcmp( ms_pMdl[iC]->m_cMdlNm, i_cMdlNm)) {
			idMdl = MHNtoID( iC);
			break;
		}
	}
	return idMdl; 
}

//===========================================================================
//�y�@�\�z���f��ID���烂�f�������擾����
//�y�Ԓl�z���f��ID
static MDID GetModelName(
					MDID	i_idMdl,		// ���f��ID
					MCHAR*	o_cMdlNm		// ���f����
					)
{
}

} // namesace MC
