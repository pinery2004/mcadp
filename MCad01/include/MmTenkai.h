#pragma once

#include "MgMatD.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_TENKAI_DO
	#pragma message( "<<< Tenkai�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== Tenkai�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class	MmWndInfo;
class	MhMdlIO;

#define		MX_NJUKO	8

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J
class JTTenkaiPr
{
public:
	MUCHAR	nJuko;								// �Z�ː�
	MUCHAR	ifH[MX_NJUKO];						// ���]�t���O	0: ���W�J�A1: ���]�W�J
	MUCHAR	nOJuko[MX_NJUKO];					// �W�J���Z��
	MREAL	rMDJuko[MX_NJUKO];					// �c�����I�t�Z�b�g
	MREAL	rDJuko[MX_NJUKO];					// �Z�ˉ��s
	MREAL	rWJuko[MX_NJUKO];					// �Z�ˋ�

	MINT	Load(												// �c�a���P���R�[�h�ǂݍ���
						MhMdlIO*	i_phMdl						// �ǂݍ��݃t�@�C���@�n���h��
				);
	MINT	Save(												// �c�a�ւP���R�[�h��������
						MhMdlIO*	i_phMdl						// �������݃t�@�C���@�n���h��
				);
};

class DLL_EXPORT JTTenkai {
public:
	static	JTTenkaiPr 	z_TenkaiPara;			// �Z���W�J�p�����[�^
	static	MgMat2E		z_matTenkai[MX_NJUKO];	// �Z���W�J�}�g���b�N�X
	static	MgMat2E		z_matRTenkai[MX_NJUKO];	// �Z���W�J�t�}�g���b�N�X
	static	MgMinMaxR2D	z_mmTenkai[MX_NJUKO];	// �Z�˗̈�l�����l����
	static	MINT		z_iJuko;				// �I���Z��
	static	MUINT		z_iTenkai[MX_NJUKO];	// �Z���W�J����

public:
	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�C���Z���W�J��������������
	static void InitJTT();

	/////////////////////////////////////////////////////////////////////////////
	//	�Z���W�J����
	static void InpJTT(
					CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�Z���W�J�I��
	static void EndJTT();


	/////////////////////////////////////////////////////////////////////////////
	//	�Z���W�J�}�g���b�N�X��ݒ肷��
	static void SetJTTMAT();

	/////////////////////////////////////////////////////////////////////////////
	//	�Z���W�J�p�����[�^���擾����
	static JTTenkaiPr* GetJTTPara();					// (  O) �Z���W�J�p�����[�^

	/////////////////////////////////////////////////////////////////////////////
	//	�Z���W�J�p�����[�^��ݒ肷��
	static void SetJTTPara(
							JTTenkaiPr* pAuxTenkai		// (I  ) �Z���W�J�p�����[�^
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�Z�ˑI������
	static void SetJTTJuuko(
							MINT iJuko					// (I  ) �I���Z�˔ԍ��@�܂��́@0
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�Z�ˋ��̑n��
	static void CreJTTArea();
};

} // namespace MC
