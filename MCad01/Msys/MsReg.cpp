////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsReg.cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
#include "stdafx.h"
#include "MsBasic.h"
#include	"MsLib.h"
#include	<atlbase.h>

#define			HOLDNUM			4

namespace MC
{

static MCHAR* HOLDER[HOLDNUM] = { Mstr("�f�[�^/����"),								// 0
								  Mstr("�f�[�^/�}�`"),								// 1
								  Mstr("�f�[�^/�e�[�u��"),							// 2
								  Mstr("�f�[�^/�e�L�X�`��") };						// 3

static MCHAR*	RegSub = Mstr( "SOFTWARE\\KMCreate\\Home_Designer\\Model");
static MCHAR*	SubKey = Mstr( "Path");
//HHHH
////////////////////////////////////////////////////////////////////////////
//	�v���Z�X���N�����I������܂ő҂B
MINT MsProcXqt(									// �ð��	0 : �v���Z�X�����s���I��   -1 : �v���Z�X�̎��s�Ɏ��s
						MCHAR*	i_AplName,		// ���s����Ӽޭ�ٖ�
						MCHAR*	i_cCmdLine)		// ���ع���݂ɓn�������ײ�
{
	MINT		Status;							// �ð��
	STARTUPINFO	StatInf;						// ��۾���Ҳݳ���޳�̕\�����\����
	PROCESS_INFORMATION	ProcInf;				// ��۾��Ɋւ�����\����
	BOOL		BolSts;							// CreateProcesss�֐��̽ð��
	HANDLE		HProc = NULL;					// �V������۾��������
	DWORD		ItrSts;							// ����ٌ���
	DWORD		ExitFlg;						// ��۾��̏I�����

	Status = 0;
	memset(&StatInf, 0, sizeof(StatInf));
	memset(&ProcInf, 0, sizeof(ProcInf));

	// �v���Z�X�̍쐬
	if ( ( BolSts = CreateProcess( i_AplName, i_cCmdLine, 0, 0, false, NORMAL_PRIORITY_CLASS,
								   0, 0, &StatInf, &ProcInf)) == false) {
		Status = -1;
		goto  PRG_EXIT;
	}
	HProc = ProcInf.hProcess;															// ��۾�����ق̾��

	do {
		while ( ( ItrSts = WaitForSingleObject( HProc, 200)) == WAIT_TIMEOUT);				// �ҋ@
		GetExitCodeProcess( HProc, &ExitFlg);

	} while ( ExitFlg == STILL_ACTIVE);													// �I���܂ő҂�

	if ( HProc != 0)  CloseHandle(HProc);												// ����ق�۰�ނ���

PRG_EXIT:

	return( Status);
}

////////////////////////////////////////////////////////////////////////////
//		���ϐ��𓾂�
MINT MsGetenv(									// �ð��	0 : ����   -1 : �G���[
						MCHAR*	i_cEnvNam,		// ���ϐ���
						MCHAR*	o_cEnvVal)		// ���ϐ��̒l
{
	MINT		iSt;							// �ð��
	MCHAR*		cEnvPtr;						// ���ϐ��߲��


	iSt = -1;

	cEnvPtr = _tgetenv( i_cEnvNam);
	if ( cEnvPtr == NULL)  goto  PRG_EXIT;

	Mstrcpy( o_cEnvVal, cEnvPtr);
	iSt = 0;

PRG_EXIT:

	return iSt;
}

////////////////////////////////////////////////////////////////////////////
//		���ϐ����������p�X���𓾂�
MINT MsAddEnvNam(								// �ð��	0 : ����   -1 : �G���[
						MINT	i_iType,		// 0;���� 1:�}�` 2:ð��� 3:÷��� -1:HTEMP
						MCHAR*	i_cFilNam,		// ̧�ٖ�
						MCHAR*	o_cPasNam)		// ���ϐ����������߽��
{
	MINT		Status;							// �ð��
	MINT		Leng;
	MINT		ItrSts;


	Status = -1;

	if ( i_iType >= 0 && i_iType < HOLDNUM) {
		ItrSts = MsGetenv( Mstr("MCAD"), o_cPasNam);
		if ( ItrSts != 0)  Mstrcpy( o_cPasNam, Mstr("E:/MCAD"));

		Leng = (MINT)Mstrlen( o_cPasNam);													// ������
		if ( Mstrncmp( &o_cPasNam[Leng-1], Mstr("/"), 1) != 0)  Mstrcat( o_cPasNam, Mstr("/"));

		Mstrcat( o_cPasNam, HOLDER[i_iType]);

		if ( i_cFilNam) {
			Mstrcat( o_cPasNam, Mstr("/"));
			Mstrcat( o_cPasNam, i_cFilNam);
		}
	} else if ( i_iType == -1) {
		ItrSts = MsGetenv( Mstr("MTEMP"), o_cPasNam);
		if ( ItrSts != 0)  Mstrcpy( o_cPasNam, Mstr("C:/TEMP"));

		Leng = (MINT)Mstrlen( o_cPasNam);													// ������
		if ( Mstrncmp( &o_cPasNam[Leng-1], Mstr("/"), 1) != 0)  Mstrcat( o_cPasNam, Mstr("/"));

		if ( i_cFilNam)  Mstrcat( o_cPasNam, i_cFilNam);
	}

	Status = 0;

	return(Status);
}

////////////////////////////////////////////////////////////////////////////
//		���W�X�g���̓o�^
MINT MsSetRegistry( void)						// (  O) �ð��	     0 : ����   -1 : �G���[
{
	MINT		Status;							// �ð��
	CRegKey		RKey;
	MINT		ItrSts;


	Status = -1;

	ItrSts = RKey.Open( HKEY_LOCAL_MACHINE, RegSub);
	if (ItrSts == ERROR_SUCCESS) {														// ���ɂ���
		RKey.Close();
		Status = 0;
	} else {
		ItrSts = RKey.Create(HKEY_LOCAL_MACHINE, RegSub); 
		if (ItrSts == ERROR_SUCCESS) {
			RKey.SetValue(Mstr( ""), SubKey);
//			RKey.SetKeyValue( SubKey, Mstr(""));
			RKey.Close();
			Status = 0;
		}
	}

	return(Status);
}

////////////////////////////////////////////////////////////////////////////
//		���W�X�g�����p�X���擾
MINT MsGetRegistryPath(							// (  O) �ð��	0 : ����   -1 : �G���[
						MCHAR*	PName)			// (  O) �߽���ް
{
	MINT		Status;							// �ð��
	CRegKey		RKey;
	MCHAR		NameW[MAX_PATH];
	MINT		Size;
	MINT		ItrSts;

	Status = -1;
	Mstrcpy(NameW, Mstr(""));

	ItrSts = RKey.Open( HKEY_LOCAL_MACHINE, RegSub, KEY_READ);
	if ( ItrSts == ERROR_SUCCESS) {														// ����
		Size = sizeof( NameW);
		RKey.QueryValue( NameW, SubKey, (MULONG *)&Size);
		if ( ItrSts == ERROR_SUCCESS)  Status = 0;
		RKey.Close();
	}
	Mstrcpy( PName, NameW);

	return( Status);
}

////////////////////////////////////////////////////////////////////////////
//		���W�X�g���Ƀp�X��ݒ�
MINT MsSetRegistryPath(							// (  O) �ð��	0 : ����   -1 : �G���[
						MCHAR*	PName)			// (I  ) �߽���ް
{
	MINT		Status;							// �ð��
	CRegKey		RKey;
	MINT		ItrSts;


	Status = -1;

	ItrSts = RKey.Open( HKEY_LOCAL_MACHINE, RegSub);
	if ( ItrSts == ERROR_SUCCESS) {														// ����
		RKey.SetValue( PName, SubKey);
		RKey.Close();
		Status = 0;
	}

	return(Status);
} 

} // namespace MC