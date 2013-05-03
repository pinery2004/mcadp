//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdSekkei.cpp
//
//		
//
//
//  K.Matsu           09/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"

#include "MgPoint.h"

#include "MdModel.h"
#include "MdmDB.h"
#include "MdmEnt.h"
#include "Mdm.h"
#include "MdmSet.h"
#include "MdZukei.h"
#include "MdmFig.h"
#include "MsLib.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	Geo�e�X�g
//
void BrkPoint()
{
	_asm int 3;
}
void Test000_Geo()
{
	MgVect2 v22 = MgVect2( 1., 2.);
	MgVect2 v23 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.Print( Mstr("v23"));
	v22 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.SetRotR90();
	v23.Print( Mstr("v23"));
	MgVect2 v24;
	v24 = v22.Rot( MgVect2( 1., 1.).Unitize());
	v24.Print( Mstr("v24(v22.Rot(1.,1.))"));
	v22.SetRot( (MREAL)MC_PIE/4);
	v22.Print( Mstr("v22.SetRot(MC_PIE/4)"));

	MgPoint2 pt22 = MgPoint2( 1., 2.);
	MgPoint2 pt23 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.Print( Mstr("pt23"));
	pt22 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.SetRotR90();
	pt23.Print( Mstr("pt23"));
	MgPoint2 pt24;
	pt24 = pt22.Rot( (MREAL)MC_PIE/4);
	pt24.Print( Mstr("pt24(pt22.Rot(MC_PIE/4))"));
	pt22.SetRot( (MREAL)MC_PIE/4);
	pt22.Print( Mstr("pt22.SetRot(MC_PIE/4)"));

	MgVect3 v32 = MgVect3( 1., 2., 3.);
	MgVect3 v33 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.Print( Mstr("v33"));
	v32 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.SetRotR90();
	v33.Print( Mstr("v33"));
	MgVect3 v34;
	v34 = v32.Rot( MgVect2( 1., 1.).Unitize());
	v34.Print( Mstr("v34(v32.Rot(1.,1.))"));
	v32.SetRot( (MREAL)MC_PIE/4);
	v32.Print( Mstr("v22.SetRot(MC_PIE/4)"));

	MgPoint3 pt32 = MgPoint3( 1., 2., 3.);
	MgPoint3 pt33 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.Print( Mstr("pt33"));
	pt32 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.SetRotR90();
	pt33.Print( Mstr("pt33"));
	MgPoint3 pt34;
	pt34 = pt32.Rot( (MREAL)MC_PIE/4);
	pt34.Print( Mstr("pt34(pt32.Rot(MC_PIE/4))"));
	pt32.SetRot( (MREAL)MC_PIE/4);
	pt32.Print( Mstr("pt32.SetRot(MC_PIE/4)"));
	AfxDebugBreak( );
	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	�t�@�C���E�t�H���_�I���e�X�g
//
void Test001_SelectFile()
{
	MCHAR FilePathI[] = Mstr( "D:\\temp\\*.txt");
	MCHAR FilePathO[MAX_PATH];

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd* pWnd = pWndInfo->m_pWnd;

	HWND hWnd;
	if ( pWnd != NULL ) hWnd = pWnd->GetSafeHwnd();
	else hWnd = NULL;

	//	�ǂݍ��ݗp�t�@�C���I���_�C�A���O��\������
	//
	MsLoadFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);

	pWnd->MessageBox( FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);
	MessageBox( hWnd, FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);

	//	�ۑ��p�t�@�C���I���_�C�A���O��\������
	//
	MsSaveFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);
	MessageBox( hWnd, FilePathO, Mstr( "Save File Name"), MB_OK | MB_TOPMOST);


	//	�t�H���_�I���_�C�A���O��\������
	//
	MCHAR FolderPath[MAX_PATH] = Mstr( "D:\\Temp");
	MsForFolderDlg( hWnd, Mstr( "�e�X�g�p�t�H���_�̑I��"), Mstr( "D:\\Temp"), FolderPath, MAX_PATH);
	MessageBox( hWnd, FolderPath, Mstr( "Folder Name"), MB_OK | MB_TOPMOST);
	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	�c�a���W���[���O���[�v�����e�X�g
//
void Test002_DBModule()
{
	MINT	iSt;

	MDID	idGrp[5];							// �O���[�vId
	MINT	isz = 20;							// �����O���[�vId�o�b�t�@�T�C�Y

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�P"), 3000., 201., &idGrp[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�P"));
	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�Q"), 3000., 202., &idGrp[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�Q"));
	iSt = DGrp::DeleteGrp( idGrp[0]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�O���[�v�P"));
	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�R"), 3000., 203., &idGrp[2], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�R"));
	//iSt = DGrp::CreateGrp( Mstr( "�O���[�v�S"), 3000., 250., &idGrp[3], isz);
	//pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�S"));
	//iSt = DGrp::DeleteGrp( idGrp[2]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�O���[�v�R"));
	//iSt = DGrp::DeleteGrp( idGrp[3]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�O���[�v�S"));
	//iSt = DGrp::CreateGrp( Mstr( "�O���[�v�T"), 3000., 250., &idGrp[4], isz);
	//pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�T"));
	//iSt = DGrp::DeleteGrp( idGrp[4]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�O���[�v�T"));
}

////////////////////////////////////////////////////////////////////////////
//	�c�a���W���[���X�L�[�}�����e�X�g
//
void Test003_DBModule()
{
	MINT	iSt;

	MDID	idScm[5];							// ���C���[Id
	MINT	isz = 20;							// �������C���[Id�o�b�t�@�T�C�Y

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�P"), &idScm[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�P"));
	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�Q"), &idScm[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�Q"));
	iSt = DGrp::DeleteScm( idScm[0]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�X�L�[�}�P"));
	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�R"), &idScm[2], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�R"));
	//iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�S"), &idScm[3], isz);
	//pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�S"));
	//iSt = DGrp::DeleteScm( idScm[2]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�X�L�[�}�R"));
	//iSt = DGrp::DeleteScm( idScm[3]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�X�L�[�}�S"));
	//iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�T"), &idScm[4], isz);
	//pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�T"));
	//iSt = DGrp::DeleteScm( idScm[4]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�X�L�[�}�T"));
}

////////////////////////////////////////////////////////////////////////////
//	�c�a���W���[�����C���[�����e�X�g
//
void Test004_DBModule()
{
	MINT	iSt;

	MDID	idGrp[2];							// �O���[�vId
	MDID	idScm[2];							// ���C���[Id

	MDID	idLyr[5];							// ���C���[Id

	MINT	isz = 20;							// �����O���[�vId�o�b�t�@�T�C�Y

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�P"), 3000., 204., &idGrp[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�P"));
	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�Q"), 3000., 205., &idGrp[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�Q"));

	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�P"), &idScm[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�P"));
	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�Q"), &idScm[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�Q"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�P"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�Q"));
	iSt = DLyr::DeleteLyr( idLyr[0]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k���C���[�P"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[0], &idLyr[2], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�R"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[1], &idLyr[3], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�S"));
	iSt = DLyr::DeleteLyr( idLyr[2]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k���C���[�R"));
	iSt = DLyr::DeleteLyr( idLyr[3]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k���C���[�S"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[4], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�T"));
	iSt = DLyr::DeleteLyr( idLyr[4]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k���C���[�T"));
}

////////////////////////////////////////////////////////////////////////////
//	�c�a���W���[���G���e�B�e�B�����e�X�g
//
void Test005_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// �O���[�vId
	MDID	idScm[2];							// ���C���[Id

	MDID	idLyr[4];							// ���C���[Id

	MDID	idEnt[10];							// �G���e�B�e�BId
	MINT	isz = 20;							// �����G���e�B�e�BId�o�b�t�@�T�C�Y

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�P"), 3000., 206., &idGrp[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�P"));
	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�Q"), 3000., 207., &idGrp[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�Q"));

	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�P"), &idScm[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�P"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�P"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�Q"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P"));
	iSt = mdmDEnt::CreateEnt( 02, &idEnt[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�Q"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[0]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�P"));
	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�Q"));



	iSt = mdmDEnt::CreateEnt( 02, &idEnt[2], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�R"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[3], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�S"));

	//iSt = mdmDEnt::DeleteEnt( idEnt[2]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�R"));
	iSt = mdmDEnt::DeleteEnt( idEnt[3]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�S"));
	iSt = mdmDEnt::CreateEnt( 01, &idEnt[4], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�T"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[4]);
	//pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�T"));
}
////////////////////////////////////////////////////////////////////////////
//	�c�a���W���[���G���e�B�e�B�}�`�����e�X�g
//
void Test006_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// �O���[�vId
	MDID	idScm[2];							// ���C���[Id

	MDID	idLyr[4];							// ���C���[Id

	MDID	idEnt[20];							// �G���e�B�e�BId
	MINT	isz = 40;							// �����G���e�B�e�BId�o�b�t�@�T�C�Y

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�P"), 3000., 208., &idGrp[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�P"));
	iSt = DGrp::CreateGrp( Mstr( "�O���[�v�Q"), 3000., 209., &idGrp[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�O���[�v�Q"));

	iSt = DGrp::CreateScm( Mstr( "�X�L�[�}�P"), &idScm[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�X�L�[�}�P"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�P"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@���C���[�Q"));

	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[0], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[1], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�Q"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[2], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�R"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[3], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�S"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[4], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�T"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[5], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�U"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[6], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�V"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[7], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�W"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[8], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�X"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[9], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P�O"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[10], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P�P"));

	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[11], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P�Q"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[12], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P�R"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[13], isz);
	pIeModel->Print( Mstr( "���ƃ��f���@�G���e�B�e�B�P�S"));

	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "���ƃ��f���@�c�d�k�G���e�B�e�B�Q"));


	// �\�����[�h��ݒ肷��
	DLyr::SetLyrDispMode( 1, idLyr[0], 3);
	DLyr::SetLyrDispMode( 1, idLyr[1], 3);

	// �G���e�B�e�B�ɐ}�`��ݒ肷��
	MgPoint3 Pt0( 0., 0., 0.);
	MgPoint3 Pt1( 1000., 0., 0.);
	MgPoint3 Pt2( 1000., 1000., 0.);

	
	//// �e�N�X�`��
	//MINT iP;
	//iP = 0;
	//MDFIG stFig13( 100);
	//stFig13.Push();							// push �v���~�e�B�u��ǉ�
	//stFig13.SetN( WSZMgPush() + 1);			
	//;
	
	
	// �����P
	MDFIG stFig1( 10);
	stFig1.Line3( MgLine3( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[0], stFig1); 

	// �����Q
	MDFIG stFig2( 12);
	stFig2.Line3( MgLine3( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[2], stFig2); 

	// �|���S��
	MgPolyg3 Pg1(10);

	Pg1 += MgPoint3( 0., 0., -1000.);
	Pg1 += MgPoint3( 0., 2000., -1000.);
	Pg1 += MgPoint3( 2000., 2000., -1000.);
	Pg1 += MgPoint3( 2000., 0., -1000.);

	MDFIG stFig3( 20);
	stFig3.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[3], stFig3); 
	
	// �_
	MDFIG stFig4( 10);
	stFig4.Point3( MgPoint3( 1000., 1000., -1000.));
	mdmDEnt::SetFig( idEnt[4], stFig4);

	// ����
	MDFIG stFig5( 10);
	stFig5.ULine3( MgULine3( MgPoint3( 3000., 3000., -2000.), MgVect3( 1., 0., 0.)));
	mdmDEnt::SetFig( idEnt[5], stFig5);

	// ������
	MDFIG stFig6( 10);
	stFig6.HLine3( MgHLine3( MgPoint3( 2000., 2000., -1500.), MgVect3( 0., 1., 0.)));
	mdmDEnt::SetFig( idEnt[6], stFig6);

	// �|�����C��
	MgPolyl3 Pl1(10);

	Pl1 += MgPoint3( 0., 0., -2000.);
	Pl1 += MgPoint3( 0., 2000., -2000.);
	Pl1 += MgPoint3( 2000., 2000., -2000.);
	Pl1 += MgPoint3( 2000., 0., -2000.);

	MDFIG stFig7( 20);
	stFig7.Polyl3( Pl1);
	mdmDEnt::SetFig( idEnt[7], stFig7); 

	// ����
	MDFIG stFig8( 10);
	stFig8.Plane3( MgPlane3( MgVect3( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[8], stFig8);

	// �|���S��
	MgPolyg3 Pg2(10);

	Pg2 += MgPoint3( 0., 0., -3000.);
	Pg2 += MgPoint3( 0., 2000., -3000.);
	Pg2 += MgPoint3( 2000., 2000., -3000.);
	Pg2 += MgPoint3( 2000., 0., -3000.);

	MDFIG stFig9( 20);
	stFig9.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[9], stFig9); 

	// �~
	MDFIG stFig10( 10);
	stFig10.Cir3( MgCir3( MgPoint3( 5000., 5000., -1000.), MgVect3( 0., 1., 0.), 2000.));
	mdmDEnt::SetFig( idEnt[10], stFig10);

	// �~��
	MDFIG stFig11( 15);
	stFig11.Arc3( MgArc3( MgPoint3( 2000., 0., -1500.), MgPoint3( 0., 2000., -1500.),
						  MgPoint3( 0., 0., -1500.), MgVect3( 0., 1., 0.), 1500.));
	mdmDEnt::SetFig( idEnt[11], stFig11);

	// ��������
	MDFIG stFig12( 10);
	stFig12.IPlane3( MgPlane3( MgVect3( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[12], stFig12);

	//// �e�N�X�`��
	MDFIG stFig13( 100);
	stFig13.zPush();							// push �v���~�e�B�u��ǉ�

	stFig13.zMarker( 1, 2.);
	stFig13.zPaint( 2, 3, 4);
	stFig13.zLineTp( 5);

	stFig13.zColorRGB( MUQUARTER( 100, 200, 255, 100));			// RGB	{byte} ( 0, r, g, b)
	stFig13.zColorRGB( FLOAT3( 0.3f, 0.4f, 0.5f));				// RGB	{float} ( 1., 1., 1.) (1.)
	stFig13.zColorPlt( 2);										// �F(�p���b�g)
	stFig13.zTransmissivity( 0.7f);								// ���ߗ� ( 0. �` 1.)
	stFig13.zLineWd( 0.1f);										// ����
	stFig13.zMaterialRGBA( MC_AMBIENT, MUQUARTER( 100, 255, 200, 150));		// RGB	( A{���ߗ�}, R, G, B)
	stFig13.zMaterialRGBA( MC_DIFFUSE, FLOAT3( 1.f, 0.5f, 0.3f), 0.7f);	// A ���ߗ�	( 0. �` 1.)
	stFig13.zMaterialShininess( 100.0f);						// ���ʌ��W�� ( 0. �` 128.)
	stFig13.zTexture( 5);										// �e�N�X�`���h�c
//S	MgMat3E mat3( 1., 0., 0., 1.,
//				  0., 1., 0., 1.,
//				  0., 1., 1., 1.,
//				  100., 200., 300., 1.);
	MgMat3E mat3( 1., 0., 0.,
				  0., 1., 0.,
				  0., 0., 1.,
				  100., 200., 300.);
	stFig13.zTextureCoordinate( 0, 1, &MgVect2( 1., 0.), &mat3);// �z�u�}�g���b�N�X
	stFig13.zTextureParam( 1, 1, 2, 3, 4,						// �g��^�k���t�B���^
		MREAL3( 1., 0.5, 0.3f), MREAL3( 0.2f, 0.3f, 0.4f));		// ���E���F2		
	stFig13.zShininess( 101.);									// ���ʔ��˗� ( 0. �` 1.)
	stFig13.zPovRay( Mstr( "TEST"));							// ������


	stFig13.zPull();

	mdmDEnt::SetFig( idEnt[13], stFig13);

	pIeModel->Print( Mstr( "���ƃ��f���@�R�}�`�ǉ�"));
}

////////////////////////////////////////////////////////////////////////////
//	�e�X�g�p�O�O�P
//
void MCmdTest001()
{
	////	�t�@�C���E�t�H���_�I���e�X�g
	//Test001_SelectFile();

	//	�c�a���W���[���e�X�g
	Test000_Geo();
//	Test001_SelectFile();
	Test002_DBModule();
	Test003_DBModule();
	Test004_DBModule();
	Test005_DBModule();
	Test006_DBModule();
}

} // namespace MC
