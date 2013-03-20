//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbSysErrorMsg.cpp
//
//		�V�X�e���G���[�\��
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#pragma warning( disable : 4996 )
#include "stdafx.h"
#define DLL_EXPORT_BASE_DO
#include "MsBasic.h"
#include "MgDefine.h"
#include "MfFile.h"
#include "McSystemProperty.h"

namespace MC
{

//===========================================================================
//	MCAD.ini�t�@�C����ǂݍ���
//
//LoadMCADIniFile

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	ms::SysError( 
						char*	i_cFunction,	// �G���[�֐���	�ő�256����
						MINT	i_iErrorCode	// �G���[�R�[�h
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// �G���[�֐���

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	ms::SysError( cFunction, i_iErrorCode);
}

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	ms::SysError( 
						MCHAR*	i_cFunction,	// �G���[�֐���	�ő�256����
						MINT	i_iErrorCode	// �G���[�R�[�h
				  )
{
	MINT	ist;
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_POINTER:	iErrorMsgCd = MM_ERR_POINTER;		break;			// �������擾�G���[
	case MC_ERR_OVERFLOW:	iErrorMsgCd = MM_ERR_OVERFLOW;		break;			// �̈�I�[�o�t���[�G���[
	case MC_ERR_ID:			iErrorMsgCd = MM_ERR_ID;			break;			// �h�c���G���[
	case MC_ERR_INPUT:		iErrorMsgCd = MM_ERR_INPUT;			break;			// ���̓G���[
	case MC_ERR_NUM_OVER:	iErrorMsgCd = MM_ERR_NUM_OVER;		break;			// �����\�������G���[
	case MC_ERR_VECT_ZERO:	iErrorMsgCd = MM_ERR_VECT_ZERO;		break;			// �[���x�N�g���ŏ����s�G���[
	case MC_ERR_INPUT_ZERO:	iErrorMsgCd = MM_ERR_INPUT_ZERO;	break;			// ���l�[���ŏ����s�G���[
	case MC_ERR_OFFSET:		iErrorMsgCd = MM_ERR_OFFSET;		break;			// �I�t�Z�b�g���G���[
	case MC_ERR_FILEOPEN:	iErrorMsgCd = MM_ERR_FILEOPEN;		break;			// �t�@�C���I�[�v���G���[
	default:				iErrorMsgCd = MM_ERR_OTHER;			break;			// ���̑��G���[
	}
	Msprintf_s( cErrorMsg, Mstr( "%s\n\n%s�@\n\n%s�@"), i_cFunction,
													McSystemProperty::GetStr( iErrorMsgCd),
													McSystemProperty::GetStr( MM_ERR_SYSTEMEXIT));

	ist = AfxMessageBox( cErrorMsg, 256, MB_ICONSTOP);
	__debugbreak();
	AfxGetMainWnd( )->PostMessage( WM_CLOSE, 0, 0);								// ���C���E�B���h�E�擾�E�I��
}

//===========================================================================
//	�R�}���h�G���[�\��
//
void 	ms::CmdError( 
						char*	i_cFunction,	// �G���[�֐���	�ő�256����
						MINT	i_iErrorCode	// �G���[�R�[�h
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// �G���[�֐���

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	Mstrcat_s( cFunction, Mstr( "�@\n\n"));

	ms::CmdError( cFunction, i_iErrorCode);
}

//===========================================================================
//	�R�}���h�G���[�\��
//
void 	ms::CmdError( 
						MCHAR*	i_cFunction,	// �G���[�֐���	�ő�256����
						MINT	i_iErrorCode	// �G���[�R�[�h
				  )
{
	MINT	ist;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:
		Mstrcat_s( i_cFunction, 256, Mstr( "�R�}���h�����G���["));
		break;
	default:
		Mstrcat_s( i_cFunction, 256, Mstr( "�R�}���h�����G���["));
	}		
	ist = AfxMessageBox( i_cFunction, MB_ICONSTOP);
}

//===========================================================================
//	�G���[���^�[���u���[�N�|�C���g�p
//
void	ms::ErrorReturn( void)
{
	__debugbreak();
}

} // namespace MC
