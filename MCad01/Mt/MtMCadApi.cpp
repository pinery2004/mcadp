//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCadApi.cpp
//
//	�@�\	�R�}���h�����p�o�b�N�O���E���h�̃^�X�N�̋N��			
//
//  K.Matsu           08/01/04    Created.
//
//==========================================================================================
#include "stdafx.h"
#include "MCAD.h"
#include "..\\MCad\\resource.h"
#include "MtAskForPoint.h"
#include "MmCmdMsg.h"
#include "MtPrcEventQueue.h"
#include "MtMCadApi.h"

//#include "MCADLib.h"

#include "MrCmd.h"

namespace MC
{

void MtCmdLine();
void MtSetCmdList( struct MT_InternalCmdList *pInternalCmdList, MINT nInternalCmdList);

MINT			z_userbreak;

struct MT_InternalCmdList z_pInternalCmdList[] = {
	{ Mstr( "_CancelCmd")		,MCmdWait			,0	 ,NULL  ,IDC_CANCELCMD },
	{ Mstr( "_CreateKabeO")		,MCmdWallOuter		,0	 ,NULL  ,IDP_OUTERWALL },		// �O�Ǔ���
	{ Mstr( "_CreateKabeI")		,MCmdWallInner		,0	 ,NULL  ,IDP_INNERWALL },		// ���Ǔ���
	{ Mstr( "_CreatePts")		,MCmdPts			,0	 ,NULL  ,IDC_PARTSCREATE },		// ���ޓ���
	{ Mstr( "_GTate1")			,MCmdGaiTateSash	,0	 ,NULL  ,IDP_GAITATESASH },		// �O������i�T�b�V�j����
	{ Mstr( "_GTate2")			,MCmdGaiTateDoor	,0	 ,NULL  ,IDP_GAITATEDOOR },		// �O������i�h�A�j����
	{ Mstr( "_NTate")			,MCmdNaiTate		,0	 ,NULL  ,IDP_NAITATE },			// �����������
	{ Mstr( "_Demado")			,MCmdDemado			,0	 ,NULL  ,IDP_BAYWINDOW },		// �o������
	{ Mstr( "_CreateRoof")		,MCmdRoof			,0	 ,NULL  ,IDP_ROOF },			// ��������
	{ Mstr( "_YaneFutai")		,MCmdRoofSupplement	,0	 ,NULL  ,IDP_ROOFSUPPLEMENT },	// �����t�ѓ���
	{ Mstr( "_Kaikou")			,MCmdOpening		,0	 ,NULL  ,IDP_OPENING },			// �J��������
	{ Mstr( "_KKaidan")			,MCmdStairs			,0	 ,NULL  ,IDP_STAIRS },			// �K�i����
	{ Mstr( "_KBalcony")		,MCmdBalcony		,0	 ,NULL  ,IDP_BALCONY },			// �o���R�j�[����
	{ Mstr( "_KDebug")			,MCmdDebug			,0	 ,NULL  ,IDP_P0130 },			// �f�o�b�O�p
	{ Mstr( "_KYane")			,MCmdStructRoof		,0	 ,NULL  ,IDP_STRUCTROOF },		// �\���������ޓ���
	{ Mstr( "_KTenjo")			,MCmdStructCeiling	,0	 ,NULL  ,IDP_STRUCTCEILING },	// �\���V�䕔�ޓ���
	{ Mstr( "_KKabe")			,MCmdStructWall		,0	 ,NULL  ,IDP_STRUCTWALL },		// �\���Ǖ��ޓ���
	{ Mstr( "_KYuka")			,MCmdStructFloor	,0	 ,NULL  ,IDP_STRUCTFLOOR },		// �\�������ޓ���
	{ Mstr( "_KDodai")			,MCmdStructDodai	,0	 ,NULL  ,IDP_STRUCTDODAI },		// �\���y�䕔�ޓ���
	{ Mstr( "_KKiso")			,MCmdKiso			,0	 ,NULL  ,IDP_KISO },			// ��b����
	{ Mstr( "_Wasitu")			,MCmdWasitu			,0	 ,NULL  ,IDP_WASITU },			// �a������
//
	{ Mstr( "_Kitchen")			,MCmdKitchen		,0	 ,NULL  ,IDP_KITCHEN },			// �L�b�`������
	{ Mstr( "_Senmen")			,MCmdSenmen			,0	 ,NULL  ,IDP_SENMEN },			// ���ʁE��������
	{ Mstr( "_Toile")			,MCmdToile			,0	 ,NULL  ,IDP_TOILE },			// �g�C������
	{ Mstr( "_Settubi")			,MCmdSettubi		,0	 ,NULL  ,IDP_SETUBI },			// �ݔ�����
	{ Mstr( "_Denki")			,MCmdDenki			,0	 ,NULL  ,IDP_DENKI },			// �d�C����
	{ Mstr( "_Pipe")			,MCmdPipe			,0	 ,NULL  ,IDP_PIPE },			// �z�Ǔ���
//
	{ Mstr( "_SunpouSen")		,MCmdSunpouSen		,0	 ,NULL  ,IDP_SUNPOUSEN },		// ���@������
	{ Mstr( "_HikidasiSen")		,MCmdHikidasiSen	,0	 ,NULL  ,IDP_HIKIDASISEN },		// ���o���^���L����
//
	{ Mstr( "_Zumen")			,MCmdZumen			,0	 ,NULL  ,IDP_ZUMEN },			// �}�ʓ���
//
	{ Mstr( "_MCreate")			,MCmdMdCreate		,0	 ,NULL  ,IDC_MODECREATE },		// �n�����[�h
	{ Mstr( "_MDelete")			,MCmdMdDelete		,0	 ,NULL  ,IDC_MODEDELETE },		// �폜���[�h
	{ Mstr( "_MModify")			,MCmdMdModify		,0	 ,NULL  ,IDC_MODEMODIFY },		// �C�����[�h
	{ Mstr( "_MMove")			,MCmdMdMove			,0	 ,NULL  ,IDC_MODEMOVE },		// �ړ����[�h
	{ Mstr( "_MCopy")			,MCmdMdCopy			,0	 ,NULL  ,IDC_MODECOPY },		// ���ʃ��[�h
	{ Mstr( "_MProperty")		,MCmdMdProperty		,0	 ,NULL  ,IDC_MODEPROPERTY },	// �����\�����[�h
	{ Mstr( "_Undo")			,MCmdUndo			,0	 ,NULL  ,IDC_UNDO },			// �A���h�D
	{ Mstr( "_Redo")			,MCmdRedo			,0	 ,NULL  ,IDC_REDO },			// ���h�D
//	{ Mstr( "_Cancel1pt")		,MCmdCancel1Pt		,0	 ,NULL  ,IDC_CANCEL1PT },		// �P�_�L�����Z��
//	{ Mstr( "_CancelAll")		,MCmdCancelAll		,0	 ,NULL  ,IDC_CANCELALL },		// �S�_�L�����Z��
//	{ Mstr( "_InpKai")			,MCmdInpKai			,0	 ,NULL  ,IDC_INPUTKAI },		// �K����
//	{ Mstr( "_InpAll")			,MCmdInpAll			,0	 ,NULL  ,IDC_INPUTALL },		// �S�K����
//	{ Mstr( "_InpEnd")			,MCmdInpEnd			,0	 ,NULL  ,IDC_INPUTEND },		// ���͏I��
//	{ Mstr( "_BHeight")			,MCmdBaseHeight		,0	 ,NULL  ,IDC_BASEHIGHT },		// ���������
	{ Mstr( "_GridNum")			,MCmdGridNum		,0	 ,NULL  ,IDC_GRIDNUM },			// �O���b�h���ݒ�
	{ Mstr( "_Opt")				,MCmdOpt			,0	 ,NULL  ,IDC_OPTION },			// �I�v�V�����ݒ�
	{ Mstr( "_Hist")			,MCmdHist			,0	 ,NULL  ,IDC_HIST },			// �����Ǘ�
	{ Mstr( "_Tenkai")			,MCmdTenkai			,0	 ,NULL  ,IDC_TENKAI },			// �Z���W�J
	{ Mstr( "_PtsEdit")			,MCmdPtsEdit		,0	 ,NULL  ,IDC_PARTSEDIT },		// �O���b�h�R���g���[���e�X�g
	{ Mstr( "_MLoadDxfFile")	,MCmdLoadDxfFile	,0	 ,NULL  ,IDC_LOAD_DXF_FILE },	// �c�w�e�t�@�C���̓Ǎ���
	{ Mstr( "_ModLineLength")	,MCmdMdLineLength	,0	 ,NULL  ,IDC_MOD_LINELENGTH },	// ���u���ނ̒�������
	{ Mstr( "_ModPanelNo")		,MCmdMdPanelNo		,0	 ,NULL  ,IDC_MOD_PANELNO },		// �p�l���ԍ��̏C��
	{ Mstr( "_ModTest001")		,MCmdTest001		,0	 ,NULL  ,IDC_TEST_001 }			// �e�X�g�p�O�O�P
};
MINT z_nInternalCmdList = sizeof(z_pInternalCmdList)/sizeof(z_pInternalCmdList[0]);

// ===================================================================


static CWinThread		*z_pThread;
static DWORD			z_dwThreadID;
static HANDLE			z_hResumeEvent;

void MtCmdOpen()
{
	MtSetCmdList( z_pInternalCmdList, z_nInternalCmdList);
	MtLaunch();
}

void MtCmdClose()
{
	MtCloseThread();
}

//
//	�ʃX���b�h��MtThreadProcedure���N������
bool MtLaunch( void)
{
	z_hResumeEvent = CreateEvent( NULL,						// security attributes
								  FALSE,					// this means an auto-reset object
								  FALSE,					// initially in non-signaled state
								  NULL);					// unnamed object (we'll just keep the handle)

	ASSERT( z_hResumeEvent != NULL);
	if ( z_hResumeEvent)
	{
		//�X���b�h���x�~���Ő���
		z_pThread = AfxBeginThread( (UINT(*)(LPVOID))MtCmdThread,
									NULL,
									THREAD_PRIORITY_NORMAL,
									0,
									CREATE_SUSPENDED);
		ASSERT( z_pThread != NULL);

		//�X���b�h�̎����폜���֎~
		z_pThread->m_bAutoDelete = FALSE;
		z_dwThreadID = z_pThread->m_nThreadID;
	
		//�X���b�h�����s��Ԃɂ���
		z_pThread->ResumeThread();
	}
	return ( z_pThread != NULL);
}

void MtCloseThread( void)
{
	z_pThread->ResumeThread();									// �x�~���̃X���b�h�����s��Ԃɂ���
	HANDLE hThread = z_pThread ->m_hThread;						// �X���b�h�̃n���h�����擾����
	MtStopThread();												// �X���b�h�ɏI�����w��
	MtSendMessage( WM_APP_SYSTEMSTOP, 0, NULL);					// 
	WaitForSingleObject( hThread, INFINITE);					// �X���b�h���I������܂ő҂�	
	delete z_pThread;											// �X���b�h�I�u�W�F�N�g���폜
}


static MINT				z_IgnoreMenuWQuote;

static volatile MINT	z_iCommand;

//	�ʃ^�X�N�̏����ł���A���̓C�x���g��҂��Ȃ�����s����B
MINT MtCmdThread( void)
{
	MINT	ist = 0;
	MINT	irt;
	MCHAR	fs1[MC_MCADBUF], fs2[MC_MCADBUF];
	MgPoint2	pt1;
	
	MFOREVER {
		irt = MtAskForPoint( &pt1);								// ���̓C�x���g�ɑΉ������R�}���h���擾
		if ( irt == MTRT_CAN) continue;							// �L�����Z��
		if ( irt == MTRT_SYSTEMSTOP) break;						// �V�X�e���I��

		*fs1 = 0;

		switch( irt) {											// ���̓C�x���g�̎�ނɂ��
			//case MT_RTNONE:
			//	Mstrcpy( fs2, Mstr( "?1"));
			//	break;

			case MTRT_ERROR:
				Mstrcpy_s( fs2, Mstr( "?2"));
				break;

			case MTRT_LBTNDWN:									// �}�E�X�ɂ����W����
				Mstrcpy_s( fs2, Mstr( "?3"));
				break;

			case MTRT_MBTNDWN:									// �}�E�X�ɂ����W����
				Mstrcpy_s( fs2, Mstr( "?4"));
				break;

			case MTRT_RBTNDWN:									// �}�E�X�ɂ����W����
				Mstrcpy_s( fs2, Mstr( "?5"));
				break;

			case MTRT_KWORD:									// ���j���[����
				MtGetInp( fs1);
				break;
		}

		try {
			MtDoOneCommand( fs1,0);								// �Ή�����R�}���h�����s����

		} catch ( ...) {
			ms::CmdError( MBCstr( "MCadApi"), MC_ERR_COMMAND);

		}

	}
	return ist;
}

/*----------------------------------------------------------------------------*/
//
//	�R�}���h���ɑΉ�����R�}���h�����s����
//	�R�}���h�����o�^����Ă��Ȃ��ꍇ�͖�������
MINT MtDoOneCommand
						(
							MCHAR*	argcmd, 
							MINT	pushlsp
						) 
{
	MINT ic;
	MINT (*fnptr)(void);
	MINT ret = MTRT_ERROR;

	for ( ic=0; ic<z_nInternalCmdList; ic++) {
		if (Mstrcmp( z_pInternalCmdList[ic].globalName, argcmd) == 0) {
			fnptr = (MINT(*)(void))(z_pInternalCmdList[ic].funcPtr);
			ret = MTRT_NORM;
			if (fnptr)
				(*fnptr)();
			break;
		}
	}

    return(ret);
}

} // namespace MC