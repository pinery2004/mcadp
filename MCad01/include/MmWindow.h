#pragma once

#include "MhDefParts.h"

namespace MC
{

	/////////////////////////////////////////////////////////////////////////////
	//	�R�}���h�⏕����                                                       //
	/////////////////////////////////////////////////////////////////////////////

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_WINDOW_DO
	#pragma message( "<<< MC::Window�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::Window�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT Window
{
public:
	////////////////////////////////////////////////////////////////////////////
	//  �J�[�\����ݒ肷��

	static MINT SetCursor(
					class	CWnd*		i_pWnd
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�V�K�E�B���h�E�쐬���̃N���X�w�A�[�J�[�\���̏�����

	static void InitCrossHair();

	/////////////////////////////////////////////////////////////////////////////
	//	�N���X�w�A�[�J�[�\������������

	static void EraseCrossHair();

	/////////////////////////////////////////////////////////////////////////////
	//	�N���X�w�A�[�J�[�\����\������

	static void DrawCrossHair(
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����
					class	CPoint		i_ptMouthL	// �_�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�N���X�w�A�[�J�[�\�����ĕ\������
	static void ReDrawCrossHair();

	/////////////////////////////////////////////////////////////////////////////
	//	�N���X�w�A�J�[�\����\��/��������

	static MINT DispCrossHair(
							MINT		i_ictl,		// �\������	 1 : �\���A0:�ĕ\���A-1 : ����
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����(�\������ == 1) �܂��� NULL(�\������ <= 0)�@
					class	CPoint*		i_pptLMouth	// �}�E�X�ʒu�_�����W(�\������ == 1) �܂��� NULL(�\������ <= 0)
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�V�K�E�B���h�E�쐬���̏����� (�r���[�̏����\�����Ɏg�p)
	//	�r���[�̏����\�����Ƀ��o�[�o���h�}�`���\������Ă��Ȃ�����ݒ肷��

	static void InitDragging();

	/////////////////////////////////////////////////////////////////////////////
	//	�h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�I���j

	static void DragModeEnd();

	/////////////////////////////////////////////////////////////////////////////
	//	�h���b�M���O���[�h�m�F�i���o�[�o���h�}�`�\�����[�h�m�F�j

	static bool GetDragMode();

	/////////////////////////////////////////////////////////////////////////////
	//	���o�[�o���h�}�`����������

	static void EraseDragging();

	/////////////////////////////////////////////////////////////////////////////
	//	���o�[�o���h�}�`��\������

	static void DrawDragging(
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����
					class	MgPoint2	i_ptMouthR	// �}�E�X�ʒu�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���o�[�o���h�}�`���ĕ\������
	//	�r���|�C���g�̍��W�̓J�����g�̍��W�ϊ��}�g���b�N�X�ō��W�ϊ������_�����W��
	//	�ŏI�|�C���g�̓J�����g�̃}�E�X�_�����W�ŕ`��

	static void ReDrawDragging();

	/////////////////////////////////////////////////////////////////////////////
	//	���o�[�o���h�}�`��\�����ăh���b�M���O���[�h���J�n���A
	//	�}�E�X�ɂč��W���͂���

	static MINT DragObject(
							MINT		i_iMode,	// �h���b�M���O���̓��[�h
					const	void*		i_pFg,		// �h���b�M���O���͍ςݍ��W
					class	MgPoint2*	o_ptGet		// �}�E�X�ʒu�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���o�[�o���h�}�`��\��/�ĕ\��/��������

	static MINT DispDragging(
							MINT		i_ictl,		// �\������ 1 : �\���A0 : �ĕ\���A-1 : ����
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����
					class	MgPoint2*	i_pptMouthR	// �}�E�X�ʒu�����W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�J�����g�I���̕��ތ`����N���A����

	static void ClrCurBziFig();

	////////////////////////////////////////////////////////////////////////////
	//	�J�����g�I���̕��ތ`���ݒ肷��

	static void SetCurBziFig(
					class	 MgPolyg2*	i_ppgBziFig	// �J�����g�I���̕��ތ`��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�J�����g�I���̕��ތ`���Ԃ�

	static MgPolyg2* GetCurBziFig();

	/////////////////////////////////////////////////////////////////////////////
	//	�V�K�E�B���h�E�쐬���̃q�b�g���ޕ\���̏�����

	static void InitHitBuzai();

	/////////////////////////////////////////////////////////////////////////////
	//	�q�b�g���ނ̕\������������

	static void EraseHitBzi();

	/////////////////////////////////////////////////////////////////////////////
	//	�q�b�g���ނ�\������

	static void DrawHitBzi(
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����
					class	MgPolyg2*	i_pgHitBzi	// �q�b�g���ނ̌`��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�q�b�g���ނ��ĕ\������

	static void ReDispHitBzi();

	/////////////////////////////////////////////////////////////////////////////
	//	�q�b�g���ނ̌`��\��������������i�s�\���ɂ���j

	static void ResetDispHitBzi();

	/////////////////////////////////////////////////////////////////////////////
	//	�q�b�g���ނ̌`���\��/�ĕ\��/��������

	static MINT DispHitBzi(
							MINT		i_ictl,		// �\������ 1 : �\���A0 : �ĕ\���A-1 : ����
					class	MmWndInfo*	i_pWndInfo,	// �E�B���h�E�Ǘ����(�\������ == 1) �܂��� NULL(�\������ <= 0)
					class	MgPolyg2*	i_pgHitBzi	// �q�b�g���ނ̌`��(�\������ == 1) �܂��� NULL(�\������ <= 0)
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�I�𕔍ނ̕\������

	static void SetDispSelParts(
							MINT 		i_iCdBuzai	// �}�E�X�őI��Ώۂ̕��ރR�[�h�ANULL(�S)�A�܂��� -1(��\��)
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�}�E�X�I�𕔍ނ��ĕ\������

	static void ReDrawHitBzi();

	/////////////////////////////////////////////////////////////////////////////
	//  �t�H�[�J�X���J�����g�E�B���h�E�ɐݒ肷��

	static void CurWndFocus();

};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_VIEWINP_DO
	#pragma message( "<<< MC::ViewInp�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::ViewInp�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT ViewInp
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���_�E������

	static MINT LButtonDown( 
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���A�b�v����

	static MINT LButtonUp(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�E�{�^���_�E������

	static MINT RButtonDown( 
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�E�{�^���A�b�v����

	static MINT RButtonUp(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���_�E������

	static MINT MButtonDown( 
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���A�b�v����

	static MINT MButtonUp(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���_�u���N���b�N����
	static MINT LButtonDblClk(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�E�{�^���_�u���N���b�N����
	static MINT RButtonDblClk(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X���{�^���_�u���N���b�N����
	static MINT MButtonDblClk(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�z�C�[����]����

	static MINT MouseWheel(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							short		i_zDelta,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �}�E�X�ړ�����

	static MINT MouseMove( 
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT 		i_nFlags,	// 
							CPoint		i_ptMouthD	// �\�����W
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �L�[�{�[�h�L�����N�^���͏���

	static MINT Char(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT		i_nChar,	// 
							UINT		i_nRepCnt,	// 
							UINT 		i_nFlags	// 
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �L�[�{�[�h�L�[�A�b�v����

	static MINT KeyUp(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT		i_nChar,	// 
							UINT		i_nRepCnt,	// 
							UINT 		i_nFlags	// 
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �L�[�{�[�h�L�[�_�E������

	static MINT KeyDown(
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							UINT		i_nChar,	// 
							UINT		i_nRepCnt,	// 
							UINT 		i_nFlags	// 
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�E�B���h�E�̃T�C�Y�ݒ�

	static void Size(								// �X�e�C�^�X 0 : ����  1 : �G���[
					class	CWnd*		i_pWnd,		// �E�B���h�E�̃C���X�^���X
							CPoint		i_ptMouthD,	// ��ʃT�C�Y(�\�����W)
							CPoint		i_ptMouthL	// ��ʃT�C�Y(�_�����W)
					);
};


#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_MSG_DO
	#pragma message( "<<< MC::Msg�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::Msg�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT Msg
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//	�X�e�[�^�X�o�[�ɕ������\������

	static void DispSelStatusBar(
							MINT		i_iStb,		// �X�e�C�^�X�o�[���ڔԍ�
					const	MCHAR*		i_sStb		// �X�e�C�^�X�o�[���ڕ\�����e
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �X�e�C�^�X�o�[�\������

	static void SetSelStatusBar(
							MINT		i_iStb,		// �X�e�C�^�X�o�[�\����ԍ�
					const	MCHAR*		i_sStb		// �X�e�C�^�X�o�[�\�����e
					);

	static void DispStatusBar();

	/////////////////////////////////////////////////////////////////////////////
	//	�X�e�[�^�X�o�[�ɃK�C�_���X���b�Z�[�W��\������

	static void GuidanceMsg(
							MINT		i_iMsgNo	// �K�C�_���X���b�Z�[�W ID
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�X�e�[�^�X�o�[�ɑ���\�����b�Z�[�W��\������

	static void OperationMsg(
							MINT		i_iOprtMsgId // ����\��ID
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�X�e�[�^�X�o�[�ɃG���[���b�Z�[�W��\������
	// �@�G���[���b�Z�[�W1 + �G���[���b�Z�[�W2 + �v�����v�g

	static void ErrorMsg(
							MCHAR*		i_sErrMsg1,		// �G���[���b�Z�[�W�P�@�܂��́@NULL
							MINT		i_idErrMsg2,	// �G���[���b�Z�[�W�Q�\��ID
							MINT		i_imdDisp = -1	// �G���[�\�����[�h
														//		1: ���b�Z�[�W�{�b�N�X�֕\��
														//		0: �R�}���h���C���֕\�� (�R�}���h���C���ւ̕\����������΃��b�Z�[�W�{�b�N�X�֕\��)
														//	   -1: �R�}���h���C���֕\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�X�e�[�^�X�o�[�̃G���[���b�Z�[�W����������

	static void ClearErrorMsg();

};

}// namespace MC
