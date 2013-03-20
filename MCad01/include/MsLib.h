#pragma once

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�ėp�֐�
//
typedef MINT MAryCmpFunc(
				const	void*	Arg1,
				const	void*	Arg2
				);

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�N�C�b�N�\�[�g

void MsQSort(									// (  O) �ð��
						void*	base,			// (I  ) ���ёւ���z��̐擪
						MINT	num,			// (I  ) �z��̗v�f��
						MINT	width,			// (I  ) �z��̗v�f�T�C�Y(�o�C�g��)
						MAryCmpFunc* AryCmpFunc	// (I  ) ��r�֐�
				);

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�f�t�H���g�̔�r�֐�
//�y�Ԓl�z < 0 : array1  < array2
//		  == 0 : array1 == array2
//		   > 0 : array1  > array2 

static MINT AryCompare(							// (  O) �ð��
				const	void*	array1,			// (I  ) �ް�1
				const	void*	array2			// (I  ) �ް�2
				);

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zCArray ���g�p�����N�C�b�N�\�[�g�ƌ���

// Sample
class CData{
public:
	long	lgKey;
	CString	sNm;
	long	lgN;
};


template <class T> 
class CARRAY : public CArray <T, T&> {
	static int Compare( const void *, const void *);
public:
	void Sort() { qsort( GetData(), GetSize(), sizeof( T), Compare);};
	T * Search( T PtsInfo)
	{ return ( T *)bsearch( &PtsInfo, GetData(), GetSize(), sizeof( T), Compare);};
};


////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���ݎ������擾����
//�y�Ԓl�zMTIME�^�@���ݎ���

MTIME MsGetCurrentTime();

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�������r����
//�y�Ԓl�z��r���� -1 : cTime1������
//					0 : ����
//					1 : cTime2������

MINT MsCmpTime(
						MTIME	cTime1,			// (I  ) ��r�Ώێ���1
						MTIME	cTime2			// (I  ) ��r�Ώێ���2
				);

////////////////////////////////////////////////////////////////////////////
//�y�@�\�zMTIME�^�����ɕϊ�����
//�y�Ԓl�z> 0 : MTIME�^�@���ݎ���
//		  < 0 : �G���[

MTIME MsMTime(
						MINT	nYear,			// (I  ) �N
						MINT	nMonth,			// (I  ) ��
						MINT	nDay,			// (I  ) ��
						MINT	nHour,			// (I  ) ��
						MINT	nMin,			// (I  ) ��
						MINT	nSec			// (I  ) �b
				);

///////////////////////////////////////////////////////////////////////////////
//	CString�̕�����������ɕϊ�����
MREAL MsGetMREAL(								// (  O) ����
						CString&	str			// (I  ) CString������
				);

///////////////////////////////////////////////////////////////////////////////
//	CString�̕�����𐮐��ɕϊ�����
MINT MsGetMINT(									// (  O) ����
						CString&	str			// (I  ) CString������
				);

///////////////////////////////////////////////////////////////////////////////
//	MINT�̐�����CString�ɕϊ�����
CString MsCnvSMINT(								// (  O) ����������
						MINT	iMode,			// (I  ) ���[�h�@0: "n"�`���ɕϊ�
						MINT	iNum			// (I  ) ����
				);

///////////////////////////////////////////////////////////////////////////////
//	MINT�̎�����CString�ɕϊ�����
CString MsCnvSMREAL(							// (  O) ����������
						MINT	iMode,			// (I  ) ���[�h�@1: "0.0"�`���ɕϊ�
						MREAL	iReal			// (I  ) ����
				);

///////////////////////////////////////////////////////////////////////////////
//	�ǂݍ��ݗp�t�@�C���I���_�C�A���O��\������
void MsLoadFileDlg(
						CWnd*	i_pWnd,			// (I  ) �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
						MCHAR*	i_sInitFilePath,// (I  ) �����ݒ�t�@�C���p�X
						MCHAR*	o_sSelFilePath,	// (  O) �I���t�@�C���p�X
						MCHAR*	i_sFilters		// (I  ) �t�@�C������肷�邽�߂̃t�B���^ or NULL
				);
///////////////////////////////////////////////////////////////////////////////
//	�ۑ��p�t�@�C���I���_�C�A���O��\������
void MsSaveFileDlg(
						CWnd*	i_pWnd,			// (I  ) �e�E�B���h�E�܂��̓I�[�i�[ �E�B���h�E�ւ̃|�C���^
						MCHAR*	i_sInitFilePath,// (I  ) �����ݒ�t�@�C���p�X
						MCHAR*	o_sSelFilePath,	// (  O) �I���t�@�C���p�X
						MCHAR*	i_sFilters		// (I  ) �t�@�C������肷�邽�߂̃t�B���^ or NULL
				);
/////////////////////////////////////////////////////////////////////////////
//	�t�H���_�I���_�C�A���O��\������
void MsForFolderDlg( 
						HWND	i_hWnd,			// (I  ) �e�E�B���h�E�̃n���h��
						MCHAR*	i_sCaptionStr,	// (I  ) �����̕�����
						MCHAR*	i_sInitFldrPath,// (I  ) �����ݒ�t�H���_�p�X
						MCHAR*	o_sSelFldrPath	// (  O) �I���t�H���_�p�X
				);
///////////////////////////////////////////////////////////////////////////////
// �t�@�C�����̊g���q���`���𓾂�
MINT MsGetFileExtNo(							// �g���q�o�b�t�@�̔z��ԍ� -1:�װ
						MCHAR*	in_cFileName,	// ̧�ٖ�
						MCHAR**	in_ppExt,		// �g���q�o�b�t�@(�� "bmp", "jpg" : 0, 1)
						MINT	in_NExt			// �g���q��
				);
/////////////////////////////////////////////////////////////////////////////
//	�摜�t�@�C�����𓾂�
MINT HsGetImageFile(							// �ð��   0:����  1:�ُ�
						MCHAR*	i_cFile1,		// ���͉摜̧�ٖ�
						MCHAR*	o_cFile2,		// �o�͉摜̧�ٖ�
						MINT	i_iMFlag,		// 1:���E�װ
						MREAL	i_Scale			// ����
				);

/////////////////////////////////////////////////////////////////////////////
//	�v���Z�X���N�����I������܂ő҂B
MINT MsProcXqt(									// �ð��	0 : �v���Z�X�����s���I��   -1 : �v���Z�X�̎��s�Ɏ��s
						MCHAR*	i_AplName,		// ���s����Ӽޭ�ٖ�
						MCHAR*	i_cCmdLine);	// ���ع���݂ɓn�������ײ�

/////////////////////////////////////////////////////////////////////////////
//		���ϐ��𓾂�
MINT MsGetenv(									// �ð��	0 : ����   -1 : �G���[
						MCHAR*	i_cEnvNam,		// ���ϐ���
						MCHAR*	o_cEnvVal);		// ���ϐ��̒l

/////////////////////////////////////////////////////////////////////////////
//		���ϐ����������p�X���𓾂�
MINT MsAddEnvNam(								// �ð��	0 : ����   -1 : �G���[
						MINT	i_iType,		// 0;���� 1:�}�` 2:ð��� 3:÷��� -1:HTEMP
						MCHAR*	i_cFilNam,		// ̧�ٖ�
						MCHAR*	o_cPasNam);		// ���ϐ����������߽��

/////////////////////////////////////////////////////////////////////////////
//		���W�X�g���̓o�^
MINT MsSetRegistry( void);						// �ð��	     0 : ����   -1 : �G���[

/////////////////////////////////////////////////////////////////////////////
//		���W�X�g�����p�X���擾
MINT MsGetRegistryPath         (				// �ð��	0 : ����   -1 : �G���[
						MCHAR*	o_cPName);		// �߽���ް

/////////////////////////////////////////////////////////////////////////////
//		���W�X�g���Ƀp�X��ݒ�
MINT MsSetRegistryPath(							// �ð��	0 : ����   -1 : �G���[
						MCHAR*	i_cPName);		// �߽���ް

/////////////////////////////////////////////////////////////////////////////
//		�摜�t�@�C�����𓾂�
MINT MsGetImageFile(							// �ð��   0 : ����    1 : �ُ�
						MCHAR*	i_cFile1,		// ���͉摜̧�ٖ�
						MCHAR*	o_cFile2,		// �o�͉摜̧�ٖ�
						MINT	i_iMFlag,		// 1:���E�װ
						MREAL	i_Scale);		// ����


} // namespace MC