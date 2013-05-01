//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: McSystemProperty.cpp
//
//		�V�X�e���v���p�e�B
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_SYSTEMPROPERTY_DO
#include "McSystemProperty.h"

namespace MC
{

//S McSystemProperty	g_SysProp;
//	�V�X�e���萔
DWORD	mcs::m_Color[MM_N_COLOR];					// �F
MREAL	mcs::m_Real[MM_N_REAL];					// ����
MINT	mcs::m_Int[MM_N_INT];						// ����
MCHAR*	mcs::m_Str[MM_N_STR];						// ������
MCHAR*	mcs::m_Path[MM_N_PATH];					// PATH
MREAL	mcs::m_Stnd[MMAX_KAI][MM_N_STNDH];			// ������A�����@

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e���萔�̏������@(�ŗL����)
void	mcs::Init()
{
	m_Color[MM_COLOR_GRID_LINE]			= RGB( 110, 180, 150);	// �O���b�h���\���F
	m_Color[MM_COLOR_GRID_TEXT]			= RGB(  50, 100,  60);	// �O���b�h�ԍ��\���F
	m_Color[MM_COLOR_MARUME]			= RGB( 255,   0,   0);	// �ۂߐ��\���F
	m_Color[MM_COLOR_CURSOR]			= RGB( 245, 150, 100);	// �N���X�w�A�[�J�[�\���F
	m_Color[MM_COLOR_DRAGGING]			= RGB(  20, 220, 245);	// �h���b�M���O�F
	m_Color[MM_COLOR_HITBZI]			= RGB( 255, 255, 255);	// �q�b�g���ސF
	m_Color[MM_COLOR_TEMP]				= RGB( 120,  20, 125);	// �e���|�����I��\���F
	m_Color[MM_COLOR_BACKGROUND]		= RGB( 252, 252, 252);	// �w�i�F
//
	m_Color[MM_COLOR_DOUKAIKABESIN]  	= RGB( 25, 25, 205);	// ���K�ǐc�F
	m_Color[MM_COLOR_KAKAIKABESIN]	 	= RGB( 185, 75, 15);	// ���K�ǐc��F
	m_Color[MM_COLOR_JYOUKAIKABESIN] 	= RGB( 205, 15, 15);	// ��K�ǐc���F
	m_Color[MM_COLOR_DOUKAITAIKABESIN]  = RGB( 25, 25, 205);	// ���K�ϗ͕ǐc�F
	m_Color[MM_COLOR_KAKAITAIKABESIN]	= RGB( 185, 75, 15);	// ���K�ϗ͕ǐc��F
	m_Color[MM_COLOR_JYOUKAITAIKABESIN] = RGB( 205, 15, 15);	// ��K�Ǒϗ͐c���F
	m_Color[MM_COLOR_DOUKAISIJIKABESIN] = RGB( 25, 25, 205);	// ���K�x���ǐc�F
	m_Color[MM_COLOR_KAKAISIJIKABESIN]	= RGB( 185, 75, 15);	// ���K�x���ǐc��F
	m_Color[MM_COLOR_JYOUKAISIJIKABESIN]= RGB( 205, 15, 15);	// ��K�x���ǐc���F
	m_Color[MM_COLOR_KISOSIN]			= RGB( 195, 25, 25);	// ��b�c���F
	m_Color[MM_COLOR_KABESEN]			= RGB( 185, 205, 145);	// �Ǖ\�����̕ǐ��F
	
	m_Real[MM_REAL_PITCH]			= 910.f;					// �O���b�h�E�s�b�`
	m_Real[MM_REAL_GRID_SPC]		= 7.f;						// �O���b�h�ԍ��\����(�|�C���g)
	m_Real[MM_REAL_GRID_HEI]		= 9.f;						// �O���b�h��������(�|�C���g)
	m_Real[MM_REAL_GRID_AKI]		= 300.f;					// �O���b�h�g�\����

	m_Int[MM_INT_GRID_N]			= 16;						// �����k���O���b�h��
	m_Int[MM_INT_GRID_W]			= -3;						// ���������O���b�h��
	m_Int[MM_INT_GRID_S]			= -3;						// �����쑤�O���b�h��
	m_Int[MM_INT_GRID_E]			= 17;						// ���������O���b�h��

	m_Str[MM_STR_TABLE]				= Mstr( "�e�[�u��");		// �e�[�u���t�H���_��
	m_Str[MM_STR_PARTSTABLE]		= Mstr( "�e�[�u��\\����");	// ���i�t�H���_��
	m_Str[MM_STR_ATTR]				= Mstr( "����");			// �����t�H���_��
	m_Str[MM_STR_TEX]				= Mstr( "�e�N�X�`��");		// �e�N�X�`���t�H���_��
	m_Str[MM_STR_FIG]				= Mstr( "�}�`");			// �}�`�t�H���_�� 
	m_Str[MM_STR_INIFILE]			= Mstr( "MCAD.ini");		// MCAD.ini�t�@�C���� 
	m_Str[MM_STR_LOGFILE]			= Mstr( "MCADLOG.txt");		// LOG�t�@�C���� 
	m_Str[MM_STR_TRACEFILE]			= Mstr( "MCADTRACE.txt");	// TRACE�t�@�C���� 

	m_Str[MM_STR_CSV_MEMBER]		= Mstr( "���@�^��.csv");	// ���@�^��.csv 
	m_Str[MM_STR_CSV_PARTS]			= Mstr( "���i.csv");		// ���i.csv 
	m_Str[MM_STR_CSV_ATTR]			= Mstr( "����.csv");		// ����.csv 
	m_Str[MM_STR_CSV_DRAFTSZ]		= Mstr( "�}�ʃT�C�Y.csv");	// �}�ʃT�C�Y.csv 
	m_Str[MM_STR_CSV_KOUSEI]		= Mstr( "�\��.csv");		// �\��.csv 
	m_Str[MM_STR_CSV_BUNRUI]		= Mstr( "����.csv");		// ����.csv			 

	m_Str[MM_ERR_POINTER]			= Mstr( "�������擾�G���[");
	m_Str[MM_ERR_OVERFLOW]			= Mstr( "�̈�I�[�o�t���[�G���[");
	m_Str[MM_ERR_ID]				= Mstr( "�h�c���G���[");
	m_Str[MM_ERR_INPUT]				= Mstr( "���̓G���[");
	m_Str[MM_ERR_NUM_OVER]			= Mstr( "�����\�������G���[");
	m_Str[MM_ERR_VECT_ZERO]			= Mstr( "�[���x�N�g���ŏ����s�G���[");
	m_Str[MM_ERR_INPUT_ZERO]		= Mstr( "���l�[���ŏ����s�G���[");
	m_Str[MM_ERR_OFFSET]			= Mstr( "�I�t�Z�b�g���G���[");
	m_Str[MM_ERR_FILEOPEN]			= Mstr( "�t�@�C���I�[�v���G���[");
	m_Str[MM_ERR_OTHER]				= Mstr( "���̑��G���[");
	m_Str[MM_ERR_SYSTEMEXIT]		= Mstr( "�V�X�e���I�����܂��@");

	// ���s���W���[���̃f�B���N�g���擾
	static MCHAR s_cRootDir[MAX_PATH];
	GetModuleFileName( NULL, s_cRootDir, sizeof( s_cRootDir));
	for ( int i1=(int)Mstrlen( s_cRootDir)-1; i1>=0; i1--) {
		if ( s_cRootDir[i1] == '\\') {
			s_cRootDir[i1] = '\0';
			break;
		}
	}
//N	m_Path[MM_PATH_ROOT_FLDR]		= s_cRootDir;								// ���s���W���[����(���[�g)�f�B���N�g��
//N	m_Path[MM_PATH_PARTS_FLDR]		= Mstr( "D:\\MCAD_32\\�e�[�u��\\����\\");	// �\�����i�e�[�u��
	m_Path[MM_PATH_SYS_ENV_FLDR]	= Mstr( "D:\\MCAD_32\\�}�X�^");				// �V�X�e�����f�B���N�g��

	m_Stnd[0][MM_STNDH_KISO]		= 400.f;			// Kiso
	m_Stnd[0][MM_STNDH_LOWER]		= 645.f;			// Kiso + 245.f (90 + 140 + 15)
	m_Stnd[0][MM_STNDH_UPPER]		= 2740.f;			// rLower + 2095.f
	m_Stnd[0][MM_STNDH_CEILING]		= 3095.f;			// rLower + 2450.f
//	m_Stnd[0][MM_STNDH_ROOF]		= 3184.f;			// rUpper + 89.f
	m_Stnd[0][MM_STNDH_ROOF]		= 3125.f;			// rUpper + 89.f
	m_Stnd[0][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
//	m_Stnd[1][MM_STNDH_KISO]		= 0.f;
	m_Stnd[1][MM_STNDH_LOWER]		= 3354.f;			// rCeiling + 259.f (235 + 24)
	m_Stnd[1][MM_STNDH_UPPER]		= 5449.f;			// rLower + 2095.f
	m_Stnd[1][MM_STNDH_CEILING]		= 5804.f;			// rLower + 2450.f
//	m_Stnd[1][MM_STNDH_ROOF]		= 5893.f;			// rUpper + 89.f
	m_Stnd[1][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
//	m_Stnd[2][MM_STNDH_KISO]		= 0.f;
	m_Stnd[1][MM_STNDH_ROOF]		= 5834.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDH_LOWER]		= 6063.f;			// rCeiling + 259.f (235 + 24)
	m_Stnd[2][MM_STNDH_UPPER]		= 8158.f;			// rLower + 2095.f
	m_Stnd[2][MM_STNDH_CEILING]		= 8513.f;			// rLower + 2450.f
//	m_Stnd[2][MM_STNDH_ROOF]		= 8602.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDH_ROOF]		= 8543.f;			// rUpper + 89.f
	m_Stnd[2][MM_STNDA_NOKI]		= 89.f;				// 89.f | 140.f
}

/////////////////////////////////////////////////////////////////////////////
//	�v���p�e�B�l���擾����@(���L����)

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e���F���擾����
DWORD	mcs::GetColor( MSYSTEMCOLOR iCol)
{
	return m_Color[iCol];
}

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�������萔���擾����
MREAL	mcs::GetReal( MSYSTEMREAL iReal)
{
	return m_Real[iReal];
}

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�������萔���擾����
MINT	mcs::GetInt( MSYSTEMINT iInt)
{
	return m_Int[iInt];
}

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e��������萔���擾����
MCHAR*	mcs::GetStr( MSYSTEMSTR iStr)
{
	return m_Str[iStr];
}

/////////////////////////////////////////////////////////////////////////////
//	PATH�萔���擾����
MCHAR*	mcs::GetPath( MSYSTEMPATH iPath)
{
	return m_Path[iPath];
}

/////////////////////////////////////////////////////////////////////////////
//	�V�X�e�����@���p�X�Ƀt�@�C������t�������t�@�C���p�X�𓾂�
MINT mcs::GetEnvPath(				// �X�e�C�^�X	0:����	!=0:�G���[
						MPPATHENV	i_iType,	// ���p�X���
												//		 MP_PATH_ROOT:	���[�g
												//		 MP_PATH_TABLE:	�e�[�u��
												//		 MP_PATH_ATTR:	����
												//		 MP_PATH_TEX:	�e�N�X�`��(TEXTURE)
												//		 MP_PATH_FIG:	�}�`
						MCHAR*		i_cFile,	// �t�@�C����
						MCHAR*		o_cPath,	// �p�X��		�ő�259+1����(MAX_PATH)
						int			i_ncPath	// �p�X���ő啶����+1
				)
{
	MINT	ist = 0;
	MSYSTEMSTR	icdPath;
	MINT	cPathN;
	MINT	ncFile;
	MCHAR*	pFile;

//	Mstrcpy( o_cPath, mcs::GetPath( MM_PATH_ROOT_FLDR));
//	Mstrcpy( o_cPath, mcs::GetPath( MM_PATH_PARTS_FLDR));

	Mstrcpy_s( o_cPath, i_ncPath, mcs::GetPath( MM_PATH_SYS_ENV_FLDR));		// �����[�g\

	cPathN = (MINT)Mstrlen( o_cPath);
	ncFile = i_ncPath - cPathN;
	pFile = &o_cPath[cPathN-1];
	if ( *pFile != Mchar( '\\')) {
		pFile++;
		*pFile = Mchar( '\\');
		pFile++;
		*pFile = 0;
		ncFile--;
	}

	switch( i_iType)
	{
	case MP_PATH_ROOT:											break;			// �����[�g
	case MP_PATH_TABLE:			icdPath = MM_STR_TABLE;			break;			// �����[�g\�e�[�u��
	case MP_PATH_PARTSTABLE:	icdPath = MM_STR_PARTSTABLE;	break;			// �����[�g\�e�[�u��\���i
	case MP_PATH_ATTR:			icdPath = MM_STR_ATTR;			break;			// �����[�g\����
	case MP_PATH_TEX:			icdPath = MM_STR_TEX;			break;			// �����[�g\�e�N�X�`��
	case MP_PATH_FIG:			icdPath = MM_STR_FIG;			break;			// �����[�g\�}�`
	default:					ist = -1;
	}
	if ( ist == 0) {
		if ( i_iType != MP_PATH_ROOT) {
			Mstrcat_s( pFile, ncFile, mcs::GetStr( icdPath));
			Mstrcat_s( pFile, ncFile, Mstr( "\\"));
		}
		Mstrcat_s( pFile, ncFile, i_cFile);
	}
	return ist;
}

/////////////////////////////////////////////////////////////////////////////
//	�������ݒ肷��
void	mcs::SetStnd(
						MINT		iKai,				// (I  ) �K�@(1,2,3)
						MSTNDH		iKTCode,			// (I  ) ������R�[�h
						MREAL		rHA					// (I  ) �����(����)

				)
{
	m_Stnd[iKai - 1][iKTCode] = rHA;
}

/////////////////////////////////////////////////////////////////////////////
//	��������擾����
MREAL	mcs::GetStnd(						// (  O) �����(����)
						MINT		iKai,				// (I  ) �K�@(1,2,3)
						MSTNDH		iKTCode				// (I  ) ������R�[�h
				)
{
	return m_Stnd[iKai - 1][iKTCode];
}

} // namespace MC
