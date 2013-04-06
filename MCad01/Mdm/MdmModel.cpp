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

	//MBFREE( m_idGrp);
	//MBFREE( m_idScm);
	//MBFREE( m_idLyr);
}

//MDID*	MdModel::m_idGrp;			// �O���[�vID
//MDID*	MdModel::m_idScm;			// �X�L�[�}ID
//MDID*	MdModel::m_idLyr;			// ���C���[ID
//
} // namesace MC
