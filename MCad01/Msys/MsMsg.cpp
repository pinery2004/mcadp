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
#include "MainFrm.h"
#include "MmSystem.h"
#include "MsMsg.h"
#include "MmWindow.h"
#include "MmWnd.h"
#include "MlLog.h"

namespace MC
{
////////////////////////////////////////////////////////////////////////////
//	���b�Z�[�W�{�b�N�X���őO�ʂɕ\������
//
void msmsg::MsgBox(									// �ð��
							LPCSTR	i_pcText,	// ���b�Z�[�W
							LPCSTR	i_pcCaption	// ���o��
					)
{
	int		ist;
	MCHAR	cText[256];							// �G���[�֐���
	MCHAR	cCaption[256];						// �R�����g

	ist = Code::msbstowcs( i_pcText, cText, 256);
	ist = Code::msbstowcs( i_pcCaption, cCaption, 256);
	MsgBox( cText, cCaption);
}
void msmsg::MsgBox(								// �ð��
				const	MCHAR* i_pcText,		// ���b�Z�[�W
				const	MCHAR* i_pcCaption		// ���o��
				)
{
	MmWndInfo* pWndInfo;
	CWnd* pWnd;
	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	if ( pWndInfo) {
		pWnd = pWndInfo->m_pWnd;
		pWnd->MessageBox( i_pcText, i_pcCaption, MB_OK | MB_TOPMOST);
	
//S		HWND hWnd;
//		if ( pWnd != NULL ) hWnd = pWnd->GetSafeHwnd();
//		else hWnd = NULL;
//		MessageBox( hWnd, i_pcText, i_pcCaption, MB_OK | MB_TOPMOST);
////S		MessageBox( NULL, cErrorMsg, Mstr( "System Error"), MB_OK | MB_TOPMOST);
////S		ist = AfxMessageBox( cErrorMsg, 256, MB_ICONSTOP);
	} else {
		MessageBox( NULL, i_pcText, i_pcCaption, MB_OK | MB_TOPMOST);
	}
}


//===========================================================================
//	MCAD.ini�t�@�C����ǂݍ���
//
//LoadMCADIniFile

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	msmsg::SysError( 
						char*	i_cFunction,	// �G���[�֐���
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode,	// �G���[�R�[�h
						char*	i_cComment		// �R�����g
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// �G���[�֐���
	MCHAR	cComment[256];						// �R�����g

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	ist = Code::msbstowcs( i_cComment, cComment, 256);
	SysError( cFunction, i_iLineN, i_iErrorCode, cComment);
}

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	msmsg::SysError( 
						char*	i_cFunction,	// �G���[�֐���
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode,	// �G���[�R�[�h
						MCHAR*	i_cComment/*0*/	// �R�����g
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// �G���[�֐���

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	SysError( cFunction, i_iLineN, i_iErrorCode, i_cComment);
}

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	msmsg::SysError( 
						MCHAR*	i_cFunction,	// �G���[�֐���
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode,	// �G���[�R�[�h
						char*	i_cComment		// �R�����g
				  )
{
	MINT	ist;
	MCHAR	cComment[256];						// �R�����g

	ist = Code::msbstowcs( i_cComment, cComment, 256);
	SysError( i_cFunction, i_iLineN, i_iErrorCode, cComment);
}

//===========================================================================
//	�G���[�\����ɏ������I������
//
void 	msmsg::SysError( 
						MCHAR*	i_cFunction,	// �G���[�֐���
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode,	// �G���[�R�[�h
						MCHAR*	i_cComment/*0*/	// �R�����g
				  )
{
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:	iErrorMsgCd = MM_ERR_COMMAND;		break;			// �R�}���h�G���[
	case MC_ERR_ID:			iErrorMsgCd = MM_ERR_ID;			break;			// �h�c���G���[
	case MC_ERR_POINTER:	iErrorMsgCd = MM_ERR_POINTER;		break;			// �������擾�G���[
	case MC_ERR_OVERFLOW:	iErrorMsgCd = MM_ERR_OVERFLOW;		break;			// �̈�I�[�o�t���[�G���[
	case MC_ERR_FILEOPEN:	iErrorMsgCd = MM_ERR_FILEOPEN;		break;			// �t�@�C���I�[�v���G���[
	case MC_ERR_INPUT:		iErrorMsgCd = MM_ERR_INPUT;			break;			// ���̓G���[
	case MC_ERR_NUM_OVER:	iErrorMsgCd = MM_ERR_NUM_OVER;		break;			// �����\�������G���[
	case MC_ERR_VECT_ZERO:	iErrorMsgCd = MM_ERR_VECT_ZERO;		break;			// �[���x�N�g���ŏ����s�G���[
	case MC_ERR_VALUE_ZERO:	iErrorMsgCd = MM_ERR_VALUE_ZERO;	break;			// ���l�[���ŏ����s�G���[
	case MC_ERR_OFFSET:		iErrorMsgCd = MM_ERR_OFFSET;		break;			// �I�t�Z�b�g���G���[
	default:				iErrorMsgCd = MM_ERR_OTHER;			break;			// ���̑��G���[
	}
	if ( i_cComment) {
		Msprintf_s( cErrorMsg, Mstr( "Function Name = %s\n Line No = %d\n\n%s  \n\n%s�@\n\n%s�@"), i_cFunction, i_iLineN, i_cComment,
													mcs::GetStr( iErrorMsgCd),
													mcs::GetStr( MM_ERR_SYSTEMEXIT));
	} else {
		Msprintf_s( cErrorMsg, Mstr( "Function Name = %s\n Line No = %d\n\n%s�@\n\n%s�@"), i_cFunction, i_iLineN,
													mcs::GetStr( iErrorMsgCd),
													mcs::GetStr( MM_ERR_SYSTEMEXIT));
	}
	MBLOGOUTWL( MC_LOG_ERROR, cErrorMsg);
	MsgBox( cErrorMsg, Mstr( "System Error")); 
	__debugbreak();
//U	AfxGetMainWnd( )->PostMessage( WM_CLOSE, 0, 0);								// ���C���E�B���h�E�擾�E�I��
	CMainFrame*	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->PostMessage( WM_CLOSE);
	WindowCtrl::MmWndKDeleteAll();
}

//===========================================================================
//	�R�}���h�G���[�\��
//
void 	msmsg::CmdError( 
						char*	i_cFunction,	// �G���[�֐���	�ő�256����
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode	// �G���[�R�[�h
				  )
{
	MINT	ist;
	MCHAR	cFunction[256];						// �G���[�֐���

	ist = Code::msbstowcs( i_cFunction, cFunction, 256);
	CmdError( cFunction, i_iLineN, i_iErrorCode);
}

//===========================================================================
//	�R�}���h�G���[�\��
//
void 	msmsg::CmdError( 
						MCHAR*	i_cFunction,	// �G���[�֐���	�ő�256����
						int		i_iLineN,		// �s�ԍ�
						int		i_iErrorCode	// �G���[�R�[�h
				  )
{
	MCHAR	cErrorMsg[256];
	MSYSTEMSTR	iErrorMsgCd;

	switch( i_iErrorCode)
	{
	case MC_ERR_COMMAND:	iErrorMsgCd = MM_ERR_COMMAND;		break;
	default:				iErrorMsgCd = MM_ERR_COMMAND;		break;
	}		

	Msprintf_s( cErrorMsg, Mstr( "Function Name = %s Line No = %d\n\n%s�@"), i_cFunction, i_iLineN,
													mcs::GetStr( iErrorMsgCd));
	MsgBox( cErrorMsg, Mstr( "Command Error")); 
//S	ist = AfxMessageBox( cErrorMsg, MB_ICONSTOP);
}

//===========================================================================
//	�G���[���^�[���u���[�N�|�C���g�p
//
void	msmsg::ErrorReturn( void)
{
	__debugbreak();
}

} // namespace MC