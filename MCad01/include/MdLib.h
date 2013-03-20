#pragma once

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_HAITIDB_DO
	#pragma message( "<<< HaitiDb�Edll_EXport >>>")
	#define DLL_EXPORT			__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== HaitiDb�Edll_IMport ===")
			#define DLL_EXPORT	__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class MhRoofInfo;
class mhPlcInfo;

class DLL_EXPORT HaitiDb
{
public:
/////////////////////////////////////////////////////////////////////////////
//	�c�a���C�j�V�����C�Y����
static void MdPtsDbInit( void);

/////////////////////////////////////////////////////////////////////////////
//	�G���e�B�e�B��POSITION�̃|�C���^�̍������߂�
//   pEnt = pPos + MdGetSizeOfHd();
static MINT MdGetSizeOfHd();

/////////////////////////////////////////////////////////////////////////////
//	���i���폜����
static void MdPtsDelete(
						MPOSITION	i_pPosition		// (I  ) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	���i��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
static MPOSITION MdPtsAdd(
						mhPlcInfo*	i_pPlcEn,		// (I  ) ���i���R�[�h
						MINT		i_fdispCtrl		// (I  ) �\������t���O
													//		 0: �n�o�s�Q��āE�W�J���ށE�����Ǘ����ނ�ǉ����Ȃ�
													//		 1: �n�o�s�Q��āE�W�J���ށE�����Ǘ����ނ�ǉ�����
				);

/////////////////////////////////////////////////////////////////////////////
//	���i�z�u���C������
static void MdPtsModify(
						mhPlcInfo* io_pPlcEnR,		// �C��������
						mhPlcInfo* *o_ppPlcEnM		// �C���敔��
				);

/////////////////////////////////////////////////////////////////////////////
//	�������폜����
static void HaitiDb::MdRoofDelete(
						MPOSITION	i_pPosition		// (I  ) �������R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	������ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
static MPOSITION MdRoofAdd(
						MhRoofInfo*	i_pRoofEn,		// (I  ) �������R�[�h
						MINT		i_fOptv = 1		// (I  ) �n�o�s�Q�ǉ��t���O
													//		 0: �n�o�s�Q�ǉ����Ȃ�
													//		 1: �n�o�s�Q�ǉ�����
				);

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̕��i�𓾂�
static mhPlcInfo* MdPtsGet(							// (  O) ���i���R�[�h
						MPOSITION	i_pPosition		// (I  ) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	�擪�̕��i�𓾂�
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ��ݕ��i�ʒu

static mhPlcInfo* MdGetHeadPts(
						MPOSITION*	o_pPtsPos = NULL	// (  O) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	���̕��i�𓾂�
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ��ݕ��i�ʒu

static mhPlcInfo* MdGetNextPts(
						MPOSITION*	io_pPtsPos = NULL	// (I O) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̕��i�̗L���𒲂ׂ�

static bool MdIsNotEmptyPts();							// true: ���i�L��/ false: ���i����

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�ɕ��i��ǉ�����

static mhPlcInfo* MdInjectPts(
						mhPlcInfo*	i_pPlcEn	// (I  ) ���i���R�[�h
				);

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�̕��i�𓾂�

static void MdEjectPts(
						mhPlcInfo*	i_pPlcEn	// (  O) ���i���R�[�h
				);
/*
/////////////////////////////////////////////////////////////////////////////
//	���i���폜����
static void MmPanelDelete(
						MPOSITION	i_pPosition	// (I  ) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	���i��ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B
static MPOSITION MmPanelAdd(
						mhPlcInfo*	i_pPlcEn	// (I  ) ���i���R�[�h
				);
*/


/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̉������C�j�V�����C�Y����

static void MdRoofDbInit( void);

/////////////////////////////////////////////////////////////////////////////
//	�������폜����

//static void MdRoofDelete(
//						MPOSITION*	i_pPosition	// (I  ) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
//				);

/////////////////////////////////////////////////////////////////////////////
//	������ǉ�����
//	���R�[�h�̑����̈�͒ǉ��������R�[�h�Ɉ��n���A�����̃��R�[�h�̓C�j�V�����C�Y����B

//static MPOSITION MdRoofAdd(
//						MhRoofInfo*	i_pRoofEn	// (I  ) �������R�[�h
//				);

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̉����𓾂�

static MhRoofInfo* MdRoofGet(
						MPOSITION	i_pPosition	// (I  ) ���i���R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	�擪�̉����𓾂�
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ��ݕ��i�ʒu

static MhRoofInfo* MdGetHeadRoof(
						MPOSITION*	o_pRoofPos = NULL	// (  O) �������R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	���̉����𓾂�
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ��ݕ��i�ʒu

static MhRoofInfo* MdGetNextRoof(
						MPOSITION*	io_pRoofPos = NULL	// (I O) �������R�[�h�ʒu�i�m�[�h�ʒu�j
				);

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̉����̗L���𒲂ׂ�

static bool MdIsNotEmptyRoof();						// true: �����L��/ false: ��������

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�ɉ�����ǉ�����

static void MdInjectRoof(
						MhRoofInfo*	i_pRoofEn	// (I  ) �������R�[�h
				);

/////////////////////////////////////////////////////////////////////////////
//	�ƃ��f���c�^�a�̍Ō�̉����𓾂�

static void MdEjectRoof(
						MhRoofInfo* o_pRoofEn	// (  O) �������R�[�h
				);


/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̕��i�̗L���𒲂ׂ�

static bool MdIsNotEmptyRedoPts();						// true: ���i�L��/ false: ���i����

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̐擪�ɕ��i��ǉ�����

static void MdPushRedoPts(
						mhPlcInfo*	i_pRedoEn	// (I  ) ���i���R�[�h
				);

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�p�ۑ��̈�̐擪�̕��i�𓾂�

static void MdPopRedoPts(
						mhPlcInfo*	o_pRedoEn	// (  O) ���i���R�[�h
				);

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n�ۑ��̈�̃N���A
static void MdClearRedo();

};

} // namespace MC