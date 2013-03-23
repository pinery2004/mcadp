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
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MmDefine.h"
#define DLL_EXPORT_MC_MSG_DO
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmPrompt.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�X�e�[�^�X�o�[�ɃK�C�_���X���b�Z�[�W��\������

void Msg::GuidanceMsg(
						MINT	i_iMsgNo		// �K�C�_���X���b�Z�[�W ID
				)
{
	CString		GuidanceMsg;

	switch ( i_iMsgNo) {
		case MC_GUID_BASE:				GuidanceMsg = Mstr( "");																						break;
		case MC_GUID_SITEN:				GuidanceMsg = Mstr( "�n�_���w�����ĉ�����");																	break;
		case MC_GUID_HAITITEN:			GuidanceMsg = Mstr( "�z�u�_���w�����ĉ�����");																break;
		case MC_GUID_SYUUTEN:			GuidanceMsg = Mstr( "�I�_���w�����ĉ�����");																	break;
		case MC_GUID_HOUKOUTEN:			GuidanceMsg = Mstr( "�����_���w�����ĉ�����");																break;
		case MC_GUID_AREA_SITEN:		GuidanceMsg = Mstr( "���̎n�_���w�����ĉ�����");															break;
		case MC_GUID_AREA_TUUKATEN:		GuidanceMsg = Mstr( "���̒ʉߓ_���w�����ĉ�����. �i�I���͋��̎n�_�w���j");								break;
		case MC_GUID_AREA_TAIKAKUTEN:	GuidanceMsg = Mstr( "���̑Ίp�_���w�����ĉ�����");															break;
		case MC_GUID_AREA_HOUKOUTEN:	GuidanceMsg = Mstr( "���̕����_���w�����ĉ�����");															break;
		case MC_GUID_JIM_SITEN:			GuidanceMsg = Mstr( "�n�����̎n�_���w�����ĉ�����");														break;
		case MC_GUID_JIM_TUUKATEN:		GuidanceMsg = Mstr( "�n�����̒ʉߓ_���w�����ĉ�����. �i�؂�ȕ���SHIFT�L�[�A�I���͋��̎n�_�w���j");	break;
		case MC_GUID_JIM_HOUKOUTEN:		GuidanceMsg = Mstr( "�n�����̕����_���w�����ĉ�����");													break;
		case MC_GUID_DEL_PARTS:			GuidanceMsg = Mstr( "�폜���镔�ނ��w�����ĉ�����");															break;
		case MC_GUID_DEL_ROOF:			GuidanceMsg = Mstr( "�폜���鉮�����w�����ĉ�����");															break;
		case MC_GUID_MOD_PANELNO:		GuidanceMsg = Mstr( "�p�l���ԍ���ݒ肵�A�p�l���ԍ����C������p�l�����w�����ĉ�����");						break;
		case MC_GUID_MOD_BUZAILENGTH1:	GuidanceMsg = Mstr( "���ނ̒����������̒[�����w�����ĉ�����");												break;
		case MC_GUID_MOD_BUZAILENGTH2:	GuidanceMsg = Mstr( "���ނ̒�����������w�����ĉ�����");												break;
		case MC_GUID_MULTI_BUZAIAREA:	GuidanceMsg = Mstr( "�������ނ̔z�u�̈�������[�_���w�����ĉ�����");												break;
		default:						GuidanceMsg = Mstr( "����` Guidance Message");
	}
	Msg::SetSelStatusBar( MC_STSBAR_GUIDANCE, GuidanceMsg);						// �X�e�C�^�X�o�[�̃K�C�_���X���b�Z�[�W�\�����֕\������
}

/////////////////////////////////////////////////////////////////////////////
//	�X�e�[�^�X�o�[�ɑ���\�����b�Z�[�W��\������

void Msg::OperationMsg(
						MINT	iOprtMsgId			// (I  ) ����\��ID
				)
{
	CString		OperationMsg;

	switch ( iOprtMsgId) {
		case MC_OPRT_BASE:				OperationMsg = Mstr( "");									break;
		case MC_OPRT_WAIT:				OperationMsg = Mstr( " ����҂�");							break;
		case MC_OPRT_PARTS:				OperationMsg = Mstr( " ���ޓ���");							break;
		case MC_OPRT_ROOF:				OperationMsg = Mstr( " ��������");							break;
		case MC_OPRT_DEL_PARTS:			OperationMsg = Mstr( " ���ލ폜");							break;
		case MC_OPRT_MOD_PANEL:			OperationMsg = Mstr( " �p�l���C��");						break;
		case MC_OPRT_MOD_BUZAI:			OperationMsg = Mstr( " ���ޏC��");							break;
		default:						OperationMsg = Mstr( " ����`MSG");
	}
	Msg::SetSelStatusBar( MC_STSBAR_OPERATION, OperationMsg);							// �X�e�C�^�X�o�[�̑���\�����֕\������
}

/////////////////////////////////////////////////////////////////////////////
//	�X�e�[�^�X�o�[�ɃG���[���b�Z�[�W��\������
// �@�G���[���b�Z�[�W1 + �G���[���b�Z�[�W2

void Msg::ErrorMsg(
						MCHAR*	i_sErrMsg1,		// �G���[���b�Z�[�W�P�@�܂��́@NULL
						MINT	i_idErrMsg2,	// �G���[���b�Z�[�W�Q�\��ID
						MINT	i_imd_Disp		// �G���[�\�����[�h
												//		1: ���b�Z�[�W�{�b�N�X�֕\��
												//		0: �R�}���h���C���֕\�� (�R�}���h���C���ւ̕\����������΃��b�Z�[�W�{�b�N�X�֕\��)
												//	   -1: �R�}���h���C���֕\��
				)
{
	CString		ErrorMsg;

	switch (i_idErrMsg2){
		case MC_ERR_BASE:					ErrorMsg = Mstr( "");										break;
		case MC_ERR_IMPOS_MAKE_ROOF:		ErrorMsg = Mstr( "�������쐬�s�ł�");						break;
		case MC_ERR_NOTSET_TABLE:			ErrorMsg = Mstr( "�e�[�u���ɖ��ݒ�ł�");					break;
		case MC_ERR_NOTSET_PARTS_TABLE:		ErrorMsg = Mstr( "�����i�e�[�u���ɖ��ݒ�ł�");				break;
		case MC_ERR_NOTSET_MEMBER_TABLE:	ErrorMsg = Mstr( "�����@�^���e�[�u���ɖ��ݒ�ł�");			break;
		default:							ErrorMsg = Mstr( "����` ERROR MSG");
	}
	if ( i_sErrMsg1 != NULL && i_sErrMsg1[0] != 0)
		ErrorMsg = i_sErrMsg1 + ErrorMsg;
	Msg::SetSelStatusBar( MC_STSBAR_ERROR, ErrorMsg);								// �X�e�C�^�X�o�[�̃G���[�\�����֕\������
}

/////////////////////////////////////////////////////////////////////////////
//	�X�e�[�^�X�o�[�̃G���[���b�Z�[�W����������
void Msg::ClearErrorMsg()
{
	Msg::SetSelStatusBar( MC_STSBAR_ERROR, Mstr( " "));							// �X�e�C�^�X�o�[�̃G���[�\�����֕\������
}

} // namespace MC