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
#include "MlLog.h"

#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_MC_SYSTEM_DO
#include "MmLib.h"
#include "MdModel.h"
#include "Mdm.h"

#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"

#include "MsBitSet.h"
#include "MdHist.h"

#include "MdOpt.h"
#include "MmTenkai.h"
#include "McSystemProperty.h"
#include "MhLib.h"


#define MC_SZ_CMBATTR	6
#define MC_SZ_CHKATTR	4

namespace MC
{
//===========================================================================
//				�V�X�e���������@(�ŗL����)
//
//
//===========================================================================

MINT System::MmInitialize()
{
	MINT	ist;

	// ���{�ꃂ�[�h�̐ݒ�
	//							setlocale(LC_ALL, "jpn");
	ms::SetJapanese();

	// ���[�g�f�B���N�g���̐ݒ�
	// �V�X�e���̃v���p�e�B���C�j�V�����ݒ肷��
	mcs::Init();

	//
	Msg::ClearErrorMsg();

	// �S�J�[�\���̂h�c��o�^���� 
	//	MINT	nIDCURSOR = 5;
	//	MINT	IDCURSOR[] = {IDC_CROSS1, IDC_CROSS2, IDC_CROSS3, IDC_ZOOM, IDC_GRAB};

	// MCAD.ini �t�@�C���̓ǂݍ���
	MCHAR	cIniFilePath[MAX_PATH];
	mcsGetEnvPath( MP_PATH_ROOT, mcs::GetStr( MM_STR_INIFILE), cIniFilePath);
	LoadMCADIniFile( cIniFilePath);

	// Log�t�@�C���̍폜�ƃI�[�v��
	MCHAR	cLogFilePath[MAX_PATH];
	mcsGetEnvPath( MP_PATH_ROOT, mcs::GetStr( MM_STR_TRACEFILE), cLogFilePath);
	Trace::OpenLogFile( cLogFilePath);
	
	// DB������������
	Mdm::MdmInitialize();

	// ���ރ}�X�^��ǂݍ���
	MhHist::MmHistInit();
	MhOptV::MmOptInit();
	JTTenkai::InitJTT();
	IeModel::MhInitParts();

	// ���͑����l������������
	IeModel::MnInitInpAt();

	// �g���[�X�����̃t�@�C���I�[�v��
	MCHAR	cTraceFilePath[MAX_PATH];
	mcsGetEnvPath( MP_PATH_ROOT, mcs::GetStr( MM_STR_LOGFILE), cTraceFilePath);
	MBLOGOPEN( cTraceFilePath);
#if(0)
	// ���b�Z�[�W�̏o�͐�ݒ�
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
#endif

	ist = 0;
	return ist;
}

void System::MmTerminate()
{
	// DB�̉��
	Mdm::MdmTerminate();

	// �g���[�X�����̃t�@�C���N���[�Y
	MBLOGCLOSE;
}

/////////////////////////////////////////////////////////////////////////////
//	MCADINI�t�@�C���̓ǂݍ���
void System::LoadMCADIniFile( MCHAR i_cIniFilePath[])
{
}

} // namespace MC
