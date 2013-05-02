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
#include "MdModel.h"
#include "MdmDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

MdModel::MdModel( void)
{
	m_GrpBf.Alloc( 20);
	m_ScmBf.Alloc( 50);
	m_BriBf.Alloc( 20);
	m_LyrBf.Alloc( 50);
	m_EntBf.Alloc( 500);
	m_PartsBf.Alloc( 50);
	m_WinBf.Alloc( 10);

	m_MBaseTrans.SetUnit();
	
	//m_idGrp = new MDID[1000];
	//m_idScm = new MDID[1000];
	//m_idLyr = new MDID[3000];

	m_idCurGrp = -1;							// �J�����g�O���[�vID
	m_idCurWin = -1;							// �J�����g�E�B���h�EID
	m_itpCurWin = -1;							// �J�����g�E�B���h�E�^�C�v ( 0:�R�c�A1�F�}��)
	m_idCurLyr = -1;							// �J�����g���C���[ID
	m_idCurScm = -1;							// �J�����g�X�L�[�}ID

	for ( int iC=0; iC<28; iC++)
		m_mdTenkai[iC] = 0;
	for ( int iC=0; iC<7; iC++)
		m_rmdTenkai[iC] = 0;

}

MdModel::~MdModel( void)
{
	m_GrpBf.Free();
	m_ScmBf.Free();
	m_BriBf.Free();
	m_LyrBf.Free();
	m_EntBf.Free();
	m_PartsBf.Free();
	m_WinBf.Free();
}

//	�g���[�X
void MdModel::Print( MCHAR* s)
{
	MBLOGPRINTS( s);
	mlLog::Print( Mstr( "���ƃ��f��	"));
	m_GrpBf.Print( Mstr( "���O���[�v�Z�b�g	"), MDC_NONE_ID);
	m_ScmBf.Print( Mstr( "���X�L�[�}�Z�b�g	"), MDC_NONE_ID);
	m_LyrBf.Print( Mstr( "�����C���[�Z�b�g	"), MDC_NONE_ID);
	m_BriBf.Print( Mstr( "�����ރZ�b�g		"), MDC_NONE_ID);
	m_EntBf.Print( Mstr( "���G���e�B�e�B�Z�b�g"), MDC_NONE_ID);
	m_PartsBf.Print( Mstr( "�����i�Z�b�g		"), MDC_NONE_ID);
	m_WinBf.Print( Mstr( "���E�B���h�E�Z�b�g	"), MDC_NONE_ID);

	MBLOGPRINTS( Mstr( "���J�����g"));
	MBLOGPRINTI( Mstr( "	�J�����g�O���[�vID		"), m_idCurGrp);
	MBLOGPRINTI( Mstr( "	�J�����g�E�B���h�EID	"), m_idCurWin);
	MBLOGPRINTI( Mstr( "	�J�����g�E�B���h�E�^�C�v ( 0:�R�c�A1�F�}��)"), m_itpCurWin);
	MBLOGPRINTI( Mstr( "	�J�����g���C���[ID		"), m_idCurLyr);
	MBLOGPRINTI( Mstr( "	�J�����g�X�L�[�}ID		"), m_idCurScm);
	MBLOGPRINTIN( Mstr( "	�|���S���W�J�������[�h	"), m_mdTenkai, 28);
	MBLOGPRINTFN( Mstr( "	�|���S���W�J�����p�����[�^"), m_rmdTenkai, 7);
}


} // namesace MC
