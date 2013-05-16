//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsFile.cpp
//
//		
//
//
//  K.Matsu           11/17/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "afxdlgs.h"


// CChildView1 �E�B���h�E

namespace MC
{

// OnInitDialog�̃^�C�~���O�ŏڍו\���̃��b�Z�[�W�𔭂��邽�߂�
// �N���X�̌p�����g�p���ĐV�����N���X���쐬����
class MsFileDialog : public CFileDialog
{
public:
	explicit MsFileDialog(
					BOOL	bOpenFileDialog,
					LPCTSTR lpszDefExt = NULL,
					LPCTSTR lpszFileName = NULL,
					DWORD	dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					LPCTSTR lpszFilter = NULL,
					CWnd*	pParentWnd = NULL,
					DWORD	dwSize = 0
				);
	static void DispFileDlg(
					BOOL		i_bDialogType,		// �_�C�A���O�^�C�v�@TRUE:�ǂݍ��݁AFAULT:�ۑ�
					CWnd*		i_pWnd,				// �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
					MCHAR*		i_sInitFilePath,	// �����ݒ�t�@�C���p�X
					MCHAR*		o_sSelFilePath,		// �I���t�@�C���p�X
					int			i_iszSelFilePath,	// �I���t�@�C���p�X�o�b�t�@�T�C�Y(������)
					MCHAR*		i_sFilters			// �t�@�C������肷�邽�߂̃t�B���^ or NULL
				);
public:
	virtual BOOL OnInitDialog();
};

MsFileDialog::MsFileDialog(
					BOOL	i_bOpenFileDialog,		// TRUE: �t�@�C�����J��, FALSE: �t�@�C������t���ĕۑ�
					LPCTSTR i_lpszDefExt,			// ����̃t�@�C���g���q or NULL (�g���q���ȗ��������͎��ɕt������g���q)
					LPCTSTR i_lpszFileName,			// �����\�������t�@�C���� or NULL
					DWORD	i_dwFlags,				// �_�C�A���O �{�b�N�X���J�X�^�}�C�Y���邽�߂̃t���O
					LPCTSTR i_lpszFilter,			// �t�@�C������肷�邽�߂̃t�B���^
					CWnd*	i_pParentWnd,			// �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
					DWORD	i_dwSize				// OPENFILENAME �\���̂̃T�C�Y �܂��� 0
				)
				  : CFileDialog( i_bOpenFileDialog, i_lpszDefExt, i_lpszFileName, 
								 i_dwFlags, i_lpszFilter, i_pParentWnd, i_dwSize)
{
};

//	�ڍו\���̃{�^��������������v���O�����ōs��
//
BOOL MsFileDialog::OnInitDialog()
{
    CFileDialog::OnInitDialog();

	MINT wmCommand = 40964;										// �ڍו\��Id
    CWnd *parent = GetParent();
    if ( parent != NULL ) {
       parent->PostMessage(WM_COMMAND, wmCommand, NULL);
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//	�ǂݍ��ݗp�t�@�C���I���_�C�A���O��\������
void mslib::LoadFileDlg(
					CWnd*		i_pWnd,				// �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
					MCHAR*		i_sInitFilePath,	// �����ݒ�t�@�C���p�X
					MCHAR*		o_sSelFilePath,		// �I���t�@�C���p�X
					int			i_iszSelFilePath,	// �I���t�@�C���p�X�o�b�t�@�T�C�Y(������)
					MCHAR*		i_sFilters			// �t�@�C������肷�邽�߂̃t�B���^ or NULL
				)
{
	MsFileDialog::DispFileDlg( TRUE, i_pWnd, i_sInitFilePath, o_sSelFilePath, i_iszSelFilePath, i_sFilters);
}

///////////////////////////////////////////////////////////////////////////////
//	�ۑ��p�t�@�C���I���_�C�A���O��\������
void mslib::SaveFileDlg(
					CWnd*		i_pWnd,				// �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
					MCHAR*		i_sInitFilePath,	// �����ݒ�t�@�C���p�X
					MCHAR*		o_sSelFilePath,		// �I���t�@�C���p�X
					int			i_iszSelFilePath,	// �I���t�@�C���p�X�o�b�t�@�T�C�Y(������)
					MCHAR*		i_sFilters			// �t�@�C������肷�邽�߂̃t�B���^ or NULL
				)
{
	MsFileDialog::DispFileDlg( FALSE, i_pWnd, i_sInitFilePath, o_sSelFilePath, i_iszSelFilePath, i_sFilters);
}
#define	NCHEXP	10
///////////////////////////////////////////////////////////////////////////////
//	�t�@�C���I���_�C�A���O��\������
void MsFileDialog::DispFileDlg(
					BOOL		bDialogType,		// �_�C�A���O�^�C�v�@TRUE:�ǂݍ��݁AFAULT:�ۑ�
					CWnd*		i_pWnd,				// �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
					MCHAR*		i_sInitFilePath,	// �����ݒ�t�@�C���p�X
					MCHAR*		o_sSelFilePath,		// �I���t�@�C���p�X�o�b�t�@
					int			i_iszSelFilePath,	// �I���t�@�C���p�X�o�b�t�@�T�C�Y(������)
					MCHAR*		i_sFilters			// �t�@�C������肷�邽�߂̃t�B���^ or NULL
				)
{
	MCHAR*	psFilters; 
	MCHAR*	psDefExt; 
	MCHAR*	psInitFilePath; 

	MCHAR	sFilters[] = Mstr( "MyType Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	MCHAR	sDefExt[] = Mstr( "txt");
	MCHAR	sDefExtI[NCHEXP];
	MCHAR	sInitFilePath[] = Mstr( "D:\\Temp\\*.txt");

	MINT	iLen;
	MINT	iC;

	psFilters = ( ( i_sFilters) ? i_sFilters : sFilters);

	if ( i_sInitFilePath) {
		psInitFilePath = i_sInitFilePath;

		iLen = (MINT)Mstrlen( i_sInitFilePath);
		for ( iC = iLen - 1; iC >= 0 && i_sInitFilePath[iC] != '.'; iC--);
		if ( iC >= 0 ) {
			if ( iLen - iC < NCHEXP) 
				Mstrcpy_s( sDefExtI, &i_sInitFilePath[iC + 1]);
			psDefExt = sDefExt;
		} else {
			psDefExt = NULL;
		}
	} else {
		psInitFilePath = sInitFilePath;
		psDefExt = sDefExt;
	}

	MsFileDialog fileDlg( bDialogType, psDefExt, psInitFilePath,
				OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, psFilters, i_pWnd);

	if( fileDlg.DoModal() == IDOK )	{
		CString pathName = fileDlg.GetPathName();
		Mstrcpy_s( o_sSelFilePath, i_iszSelFilePath, pathName);

	} else {
		o_sSelFilePath[0] = 0;

	}
}

///////////////////////////////////////////////////////////////////////////////
// �t�H���_�I���_�C�A���O�v���V�[�W��
int CALLBACK MsForFolderDlg_Callback(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

/////////////////////////////////////////////////////////////////////////////
//	�t�H���_�I���_�C�A���O��\������
void mslib::ForFolderDlg( 
					HWND		i_hWnd,				// (I  ) �e�E�B���h�E�̃n���h��
					MCHAR*		i_sCaptionStr,		// (I  ) �����̕�����
					MCHAR*		i_sInitFldrPath,	// (I  ) �����ݒ�t�H���_�p�X
					MCHAR*		o_sSelFldrPath,		// (I  ) �I���t�H���_�p�X
					int			i_iszSelFldrPath	// �I���t�H���_�p�X�z��T�C�Y(������)
					)
{
	BROWSEINFO		stBInfo;
    LPITEMIDLIST    pidlRoot;      // �u���E�Y�̃��[�gPIDL
    LPITEMIDLIST    pidlBrowse;    // ���[�U�[���I������PIDL

    // < �u���E�Y���󂯎��o�b�t�@�̈�̊m�� >
	MCHAR			sPutFolder[MAX_PATH];
    //LPSTR           psPutFolder;
    //if ( (psPutFolder = (LPSTR) lpMalloc->Alloc(_MAX_PATH)) == NULL)
    //    return;

    // < IMalloc�C���^�t�F�[�X�̎擾 >
	LPMALLOC	pMalloc;
	HRESULT hr = SHGetMalloc( &pMalloc);
	if( FAILED( hr)) return;

	BOOL		bRes;

    // �_�C�A���O�\�����̃��[�g�t�H���_��PIDL���擾
    // ���ȉ��̓f�X�N�g�b�v�����[�g�Ƃ��Ă���B�f�X�N�g�b�v�����[�g�Ƃ���
    //   �ꍇ�́A�P�� bi.pidlRoot �ɂO��ݒ肷�邾���ł��悢�B���̑��̓�
    //   ��t�H���_�����[�g�Ƃ��鎖���ł���B�ڍׂ�SHGetSpecialFolderLoca
    //   tion�̃w���v���Q�Ƃ̎��B
	//		CSIDL_DESKTOP	�f�X�N�g�b�v 
	//		CSIDL_PROGRAMS	�v���O���� 
	//		CSIDL_CONTROLS	�R���g���[���p�l�� 
	//		CSIDL_PRINTERS	�v�����^ 
	//		CSIDL_PERSONAL	My Documents 
	//		CSIDL_FAVORITES ���C�ɓ��� 
	//		CSIDL_STARTUP	�X�^�[�g�A�b�v 
	//		CSIDL_RECENT	Recent 
	//		CSIDL_SENDTO	SendTo 
	//		CSIDL_BITBUCKET �S�~�� 
	//		CSIDL_STARTMENU �X�^�[�g���j���[ 
	//		CSIDL_DRIVES	�}�C�R���s���[�^ 
	//		CSIDL_NETWORK	�l�b�g���[�N�R���s���[�^ 
	//		CSIDL_NETHOOD	NetHood 
	//		CSIDL_FONTS		Fonts 
	//		CSIDL_TEMPLATES ShellNew 

    if ( !SUCCEEDED(SHGetSpecialFolderLocation( i_hWnd, CSIDL_DESKTOP, &pidlRoot))) { 
//        pMalloc->Free(psPutFolder);
        return;
    }
 
	//�@�\���̂����������܂��B
	stBInfo.hwndOwner		= i_hWnd;							// �\������_�C�A���O�̐e�E�B���h�E�̃n���h��
	stBInfo.pidlRoot		= pidlRoot;							// ���[�g�t�H���_         //�����J�n�_(null�Ȃ�MyComputer)
	stBInfo.pszDisplayName	= sPutFolder;						// �I������Ă���t�H���_��
	stBInfo.lpszTitle		= i_sCaptionStr;					// �����̕�����
	stBInfo.ulFlags			= BIF_RETURNONLYFSDIRS;				// �\���t���O
																//		BIF_RETURNONLYFSDIRS	����t�H���_��\�����Ȃ� 
																//		BIF_DONTGOBELOWDOMAIN	����t�H���_��\������ 
																//		BIF_STATUSTEXT			�I�����ꂽ�t�H���_���e�L�X�g�ɕ\�� 
																//		BIF_BROWSEINCLUDEFILES	�S�Ẵt�@�C����\���� 
	stBInfo.lpfn			= MsForFolderDlg_Callback;			// �_�C�A���O�v���V�[�W���ւ̃|�C���^
	stBInfo.lParam			= (LPARAM)i_sInitFldrPath;			// �v���V�[�W���ɑ���p�����[�^�[

	stBInfo.iImage			= 0;

	// < �_�C�A���O�{�b�N�X��\������ >
	pidlBrowse = SHBrowseForFolder( &stBInfo );

	//�@pidlBrowse�ɂ͂��̃t�H���_��\���A�C�e���h�c���X�g�ւ̃|�C���^��
	//�@�����Ă���BsPutFolder�ɂ͑I�����ꂽ�t�H���_���i��t���p�X�j����
	//�@���������Ă��Ȃ��̂ŁA���̃|�C���^�𗘗p����B

	if( pidlBrowse != NULL )	{
		//�@�t���p�X���擾���܂��B
		bRes = SHGetPathFromIDList( pidlBrowse, sPutFolder );
		if( bRes) {
			Mstrcpy_s( o_sSelFldrPath, i_iszSelFldrPath, sPutFolder);
		}
        //PIDL���������
		//::CoTaskMemFree( pidlBrowse );
        pMalloc->Free( pidlBrowse);
	} else {
		o_sSelFldrPath[0] = 0;
	}
    // �N���[���A�b�v����
    pMalloc->Free(pidlRoot); 
//    lpMalloc->Free(psPutFolder);
    pMalloc->Release();
}

///////////////////////////////////////////////////////////////////////////////
// �t�H���_�I���_�C�A���O�v���V�[�W��
static int CALLBACK MsForFolderDlg_Callback(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if( uMsg == BFFM_INITIALIZED) {
        SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}

} // namespace MC
