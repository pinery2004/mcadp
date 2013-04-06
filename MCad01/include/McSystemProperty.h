#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: McSystemProperty.
//
//		�V�X�e���v���p�e�B
//
//  K.Matsu			11/01/09    Created.
//==========================================================================================

#ifdef DLL_EXPORT_SYSTEMPROPERTY
	#undef DLL_EXPORT_YSTEMPROPERTY
#endif

#ifdef DLL_EXPORT_SYSTEMPROPERTY_DO
	#pragma message( "<<< McSystemProperty�Edll_EXport >>>")
	#define DLL_EXPORT_SYSTEMPROPERTY			__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_SUB_DO
			#define DLL_EXPORT_SYSTEMPROPERTY
		#else
//			#pragma message( "=== McSystemProperty�Edll_IMport ===")
			#define DLL_EXPORT_SYSTEMPROPERTY	__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_SYSTEMPROPERTY
	#endif
#endif

namespace MC
{

#define		MMAX_KAI	3

enum	MSYSTEMCOLOR {
	MM_COLOR_GRID_LINE = 0,							// �O���b�h���\���F
	MM_COLOR_GRID_TEXT,								// �O���b�h�ԍ��\���F
	MM_COLOR_MARUME,								// �ۂߐ��\���F
	MM_COLOR_CURSOR,	   							// �N���X�w�A�[�J�[�\���F
	MM_COLOR_DRAGGING,	   							// �h���b�M���O�F
	MM_COLOR_HITBZI,	   							// �q�b�g���ސF
	MM_COLOR_TEMP,		   							// �e���|�����I��\���F
	MM_COLOR_BACKGROUND,   							// �w�i�F
	MM_COLOR_DOUKAIKABESIN,							// ���K�ǐc�F
	MM_COLOR_KAKAIKABESIN,  						// ���K�ǐc��F
	MM_COLOR_JYOUKAIKABESIN,						// ��K�ǐc���F,
	MM_COLOR_DOUKAITAIKABESIN,						// ���K�ϗ͕ǐc�FIN,
	MM_COLOR_KAKAITAIKABESIN,						// ���K�ϗ͕ǐc��FN,
	MM_COLOR_JYOUKAITAIKABESIN,						// ��K�Ǒϗ͐c���FSIN,
	MM_COLOR_DOUKAISIJIKABESIN,						// ���K�x���ǐc�FSIN,
	MM_COLOR_KAKAISIJIKABESIN,						// ���K�x���ǐc��FIN,
	MM_COLOR_JYOUKAISIJIKABESIN,					// ��K�x���ǐc���FESIN,
	MM_COLOR_KISOSIN,	   							// ��b�c���F
	MM_COLOR_KABESEN,	   							// �Ǖ\�����̕ǐ��F			
	MM_N_COLOR										// MSYSTEMCOLOR�̐�
};
enum	MSYSTEMREAL {
	MM_REAL_PITCH = 0,								// �O���b�h�E�s�b�`
	MM_REAL_GRID_SPC,  								// �O���b�h�ԍ��\����(�|�C���g)
	MM_REAL_GRID_HEI,  								// �O���b�h��������(�|�C���g)
	MM_REAL_GRID_AKI,  								// �O���b�h�g�\����
	MM_N_REAL											// MSYSTEMSTR�̐�	 
};
enum	MSYSTEMINT {
	MM_INT_GRID_N = 0,								// �����k���O���b�h��
	MM_INT_GRID_W,	  								// ���������O���b�h��
	MM_INT_GRID_S,	  								// �����쑤�O���b�h��
	MM_INT_GRID_E,	  								// ���������O���b�h��
	MM_N_INT										// MSYSTEMREAL�̐�
};
enum	MSYSTEMSTR {
	MM_STR_TABLE = 0,								// �e�[�u���t�H���_��
	MM_STR_PARTSTABLE,								// [�e�[�u��\]���i�t�H���_��
	MM_STR_ATTR,									// �����t�H���_��
	MM_STR_TEX,										// �e�N�X�`���t�H���_��
	MM_STR_FIG,										// �}�`�t�H���_��
	MM_STR_INIFILE,									// MCAD.ini�t�H���_��
	MM_STR_LOGFILE,									// LOG�t�@�C���� 
	MM_STR_TRACEFILE,								// TRACE�t�@�C����
	MM_STR_CSV_MEMBER,								// ���@�^��.csv 
	MM_STR_CSV_PARTS,								// ���i.csv 
	MM_STR_CSV_ATTR,								// ����.csv 
	MM_STR_CSV_DRAFTSZ,								// �}�ʃT�C�Y.csv 
	MM_STR_CSV_KOUSEI,								// �\��.csv 
	MM_STR_CSV_BUNRUI,								// ����.csv 
	MM_ERR_POINTER,									// �������擾�G���[
	MM_ERR_OVERFLOW,								// �̈�I�[�o�t���[�G���[
	MM_ERR_ID,										// �h�c���G���[
	MM_ERR_INPUT,									// ���̓G���[
	MM_ERR_NUM_OVER,								// �����\�������G���[
	MM_ERR_VECT_ZERO,								// �[���x�N�g���ŏ����s�G���[
	MM_ERR_INPUT_ZERO,								// ���l�[���ŏ����s�G���[
	MM_ERR_OFFSET,									// �I�t�Z�b�g���G���[
	MM_ERR_FILEOPEN,								// �t�@�C���I�[�v���G���[
	MM_ERR_OTHER,									// ���̑��G���[
	MM_ERR_SYSTEMEXIT,								// �V�X�e���I�����܂�
	MM_N_STR										// MSYSTEMSTR�̐�
};

enum	MSYSTEMPATH {
//N	MM_PATH_ROOT_FLDR = 0,							// ���s�t�@�C��(���[�g)�f�B���N�g��
//N	MM_PATH_PARTS_FLDR,								// �\�����i�e�[�u��
	MM_PATH_SYS_ENV_FLDR,							// �V�X�e�����f�B���N�g��
	MM_N_PATH										// MSYSTEMPATH�̐�
};

//===========================================================================
//		���ϐ�
//
enum MPPATHENV {
	MP_PATH_ROOT = 1,								// ���[�g
	MP_PATH_TABLE,									// �e�[�u��
	MP_PATH_PARTSTABLE,								// �e�[�u��\���i
	MP_PATH_ATTR,									// ����
	MP_PATH_TEX,									// �e�N�X�`��(TEXTURE)
	MP_PATH_FIG										// �}�`
};

enum	MSTNDH {
	MM_STNDH_SGL = 0,								//ZZZZZ
	MM_STNDH_KISO,
	MM_STNDH_LOWER,
	MM_STNDH_UPPER,
	MM_STNDH_CEILING,
	MM_STNDH_ROOF,
	MM_STNDA_NOKI,
	MM_N_STNDH
};

/*
class	MmStndH
{
public:
	MREAL	rKiso;
	MREAL	rLower;
	MREAL	rUpper;
	MREAL	rCeiling;
	MREAL	rRoof;
};
*/
class DLL_EXPORT_SYSTEMPROPERTY mcs
{
private:
//	�V�X�e���萔
static DWORD	m_Color[MM_N_COLOR];			// �F
static MREAL	m_Real[MM_N_REAL];				// ����
static MINT		m_Int[MM_N_INT];				// ����
static MCHAR*	m_Str[MM_N_STR];				// ������
static MCHAR*	m_Path[MM_N_PATH];				// PATH
static MREAL	m_Stnd[MMAX_KAI][MM_N_STNDH];	// ������A�����@

public:
/////////////////////////////////////////////////////////////////////////////
//	�V�X�e���v���p�e�B�̏�����
static void		Init();

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e���F���擾����
static DWORD	GetColor( MSYSTEMCOLOR iCol);

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�������萔���擾����
static MREAL	GetReal( MSYSTEMREAL iReal);

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�������萔���擾����
static MINT		GetInt( MSYSTEMINT iInt);

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e��������萔���擾����
static _TCHAR*	GetStr( MSYSTEMSTR iStr);

/////////////////////////////////////////////////////////////////////////////
//	PATH�萔���擾����
static _TCHAR*	GetPath( MSYSTEMPATH iPath);

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�����@�t�@�C���p�X�𓾂�
static MINT		GetEnvPath(	// �X�e�C�^�X	0:����	!=0:�G���[
						MPPATHENV	i_iType,	// ���p�X���
												//	MM_STR_TABLE:	�e�[�u��
												//	MM_STR_ATTR:	����
												//	MM_STR_TEX:	�e�N�X�`��(TEXTURE)
												//	MM_STR_FIG:	�}�`
						MCHAR*		i_cFile,	// �t�@�C����
						MCHAR*		o_cPath,	// �p�X��
						int			i_ncPath	// �p�X���ő啶����+1
				);

/////////////////////////////////////////////////////////////////////////////
//	�������ݒ肷��
static void		SetStnd(
						MINT		i_iKai,		// �K�@(1,2,3)
						MSTNDH		i_iKTCode,	// ������R�[�h
						MREAL		i_rHA		// �����(����)

				);

/////////////////////////////////////////////////////////////////////////////
//	��������擾����
static MREAL	GetStnd(		// �����(����)
						MINT		i_iKai,		// �K�@(1,2,3)
						MSTNDH		i_iKTCode	// ������R�[�h
				);
};

//template<typename TYPE, size_t SIZE>
//inline MINT		mcsGetEnvPath(	// �X�e�C�^�X	0:����	!=0:�G���[
//						MPPATHENV	i_iType,	// ���p�X���
//												//	MM_STR_TABLE:	�e�[�u��
//												//	MM_STR_ATTR:	����
//												//	MM_STR_TEX:	�e�N�X�`��(TEXTURE)
//												//	MM_STR_FIG:	�}�`
//						MCHAR*		i_cFile,	// �t�@�C����
//						TYPE (&o_cPath)[SIZE]	// �p�X���z��
//				)
//				{
//					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, SIZE);
//				}

template<size_t SIZE>
inline MINT		mcsGetEnvPath(	// �X�e�C�^�X	0:����	!=0:�G���[
						MPPATHENV	i_iType,	// ���p�X���
												//	MM_STR_TABLE:	�e�[�u��
												//	MM_STR_ATTR:	����
												//	MM_STR_TEX:	�e�N�X�`��(TEXTURE)
												//	MM_STR_FIG:	�}�`
						MCHAR*		i_cFile,	// �t�@�C����
						MCHAR (&o_cPath)[SIZE]	// �p�X���z��
				)
				{
					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, SIZE);
				}

inline MINT		mcsGetEnvPath(	// �X�e�C�^�X	0:����	!=0:�G���[
						MPPATHENV	i_iType,	// ���p�X���
												//	MM_STR_TABLE:	�e�[�u��
												//	MM_STR_ATTR:	����
												//	MM_STR_TEX:	�e�N�X�`��(TEXTURE)
												//	MM_STR_FIG:	�}�`
						MCHAR*		i_cFile,	// �t�@�C����
						MCHAR*		o_cPath,	// �p�X��
						int			i_ncPath	// �p�X���ő啶����+1
				)
				{
					return mcs::GetEnvPath( i_iType, i_cFile, o_cPath, i_ncPath);
				}
} // namespace MC
