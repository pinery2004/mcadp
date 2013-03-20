#pragma once

#include "MsBitSet.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MHHISTV_DO
	#pragma message( "<<< MHHISTV�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MHHISTV�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif


namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�����S �N���X
#define	MSZ_HIST	3
#define	MSZ_HISTB	(3 * 32)

class MhHistV: public MsBitSet
{
//	MUINT	ver[MSZ_HIST];					// �o�[�W�����@�o�[�W�����S

public:
											// �o�[�W�����Ǘ����
//	static	bool		fcCng_NU;			// �J�����g�I���o�[�W�����̕ύX�L��
											//		(TRUE: �ύX�L��AFALSE: �ύX����)
//	static	bool		fcDB;				// �J�����g�I���o�[�W������DB�֔��f�t���O
											//		(TRUE:���f�ρAFALSE: �����f)
	static	bool		fcStd;				// �J�����g�I���o�[�W����==�W���@�t���O
											//		(TRUE:�W���AFALSE:�W���ȊO�̃o�[�W�����L��)
	static	MsBitSet	vVerC;				// �J�����g�o�[�W����
	static	MsBitSet	vVerB;				// �R�s�[���o�[�W����
	static	MINT		nVer;				// �o�^�o�[�W������
	static	CString		sVerC[MSZ_HISTB];	// �o�^�o�[�W�������S
	static	CString		sVerB[MSZ_HISTB];	// �R�s�[���o�[�W�������S
	static	CString		sVerD[MSZ_HISTB];	// �C�����S

public:
	MhHistV()	{}
};

class DLL_EXPORT MhHist
{
public:
/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�C�������Ǘ���������������
static void MmHistInit();

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�C�������Ǘ����𓾂�
static void MmHistGet(
						MINT*		m_pnVer,
						CString*	*m_ppsVerC,
						CString*	*m_ppsVerB,
						CString*	*m_ppsVerD
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�����t�o
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: ���̃o�[�W��������	-2: ��̃o�[�W���������ɗL��
static MINT MmVerUp(
						CString		sVerB,
						CString		sVerC,
						MINT*		m_pnVer,
						CString*	*m_ppsVerC,
						CString*	*m_ppsVerB,
						CString*	*m_ppsVerD
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�������ύX
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: ���̃o�[�W��������	-2: ��̃o�[�W���������ɗL��
static MINT MmVerCng(
						CString		sVerB,
						CString		sVerC,
						MINT*		m_pnVer,
						CString*	*m_ppsVerC,
						CString*	*m_ppsVerB,
						CString*	*m_ppsVerD
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�������폜
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: �o�[�W��������
static MINT MmVerDel(
						CString		sVer,
						MINT*		m_pnVer,
						CString*	*m_ppsVer
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�J�����g�I���o�[�W�����𓾂�
//�y�Ԓl�z�o�[�W�����L��
//			TRUE: �W��
//			FALSE: �W���ȊO�̃o�[�W�����ݒ肠��
static bool MmVerGetC(
						MsBitSet*	pVer			// (  O) �J�����g�I���o�[�W����
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�̗����Ǘ����J�����g�o�[�W�������܂ނ����ׂ�
//�y�Ԓl�z�J�����g�o�[�W�����܂݃t���O
//			TRUE : �܂�
//			FALSE: �܂܂Ȃ�
static bool MmHistChkC(
						MsBitSet	*pHstv			// (I  ) �c�a���R�[�h��OPT�Q�Z�b�g
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�̃o�[�W�����S���J�����g�I���o�[�W�������܂ނ����ׂ�
//�y�Ԓl�z�I���o�[�W�����܂݃t���O
//			TRUE:  �܂�
//			FALSE: �܂܂Ȃ�
static bool MmVerChkC(
						MsBitSet	*pVerv			// (I  ) �c�a���R�[�h�̃o�[�W�����S
				);


/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�c�a���R�[�h�C�����̃��R�[�h�����^�C�v���擾����
//		�@�i�C�����̃o�[�W�����̗����Ǘ��ƃJ�����g�o�[�W�����Y���̗����Ǘ���
//		�@	��r���Ăǂ̂悤�ȏC�������̃��R�[�h�ł��邩���ׂ�j
//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
//			1: �C�������R�[�h�̗����Ǘ� �� �����ݑΏۂ̗����Ǘ�
//				�o�[�W�����̕ύX�͕s�v�ŁA�����C���̂ݕύX����
//			3: ���̑� ( �C�������R�[�h�̗����Ǘ� �� �J�����g�o�[�W�����Y���̗����Ǘ� )
//				�C�������R�[�h�̓o�[�W�����ύX���A�V���������ݑΏۂ̗����Ǘ��̃o�[�W����������
//				�R�s�[���R�[�h���쐻�����̑�����ύX����
//
static MINT MmHistModChk(							// (  O) �C����̃��R�[�h�\���R�[�h
//						MsBitSet	*pHstvR,		// (I O) �C�������R�[�h�̗����Ǘ�
						MsBitSet*	*ppHstvMod,		// (I O) �C�������R�[�h�ɐݒ肷�闚���Ǘ��@(�C����̃��R�[�h�\���R�[�h >= 2 �̎��L��)
						MsBitSet*	*ppHstvAdd		// (  O) �C���p�ɒǉ����R�[�h�̗����Ǘ��@(�C����̃��R�[�h�\���R�[�h == 3 �̎��L��)
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���R�[�h�폜���ɐݒ肷��o�[�W�����R�[�h���擾����
//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
//			1 : �폜���o�[�W�����͏����݃o�[�W�����Ɠ���̏ꍇ�ŁA
//				�폜�����R�[�h�͍폜����B
//			3 : �폜���o�[�W�����ɏ����݃o�[�W�����ȊO�̃o�[�W�������܂ޏꍇ�ŁA
//				�J�����g�o�[�W�����̂ݍ폜����B
//				�J�����g�o�[�W�����ȊO�̃o�[�W���������́A�폜�����R�[�h�����̂܂܎c���B�i�o�[�W�����R�[�h�̂ݏC���j
//				�i�o�[�W�����R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
//
static MINT MmHistDelChk(							// (  O) �폜��̃��R�[�h�\���R�[�h
//						MsBitSet	*pHstvR,		// (I O) �폜�����R�[�h�̗����Ǘ�
//													// 		 �폜�ヌ�R�[�h�̗����Ǘ��ɕύX����
						MsBitSet*	*ppHstvMod		// (I O) �폜��̃��R�[�h�̕\���n�m�����Ǘ�
				);

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�o�[�W�����I��
//�y�Ԓl�z�X�e�C�^�X	0: ����	-1: �I���o�[�W��������
static MINT MmSetVer(
						CString		sVerB,
						CString		sVerC,
						MINT*		m_pnVer,
						CString*	*m_ppsVerC,
						CString*	*m_ppsVerB,
						CString*	*m_ppsVerD
				);
};

} // namespace MC