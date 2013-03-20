#pragma once

//===========================================================================
//		�I��
//
enum MPSELCD {
	MP_SENTAKU_ISYOU = 1,						// �ӏ�����
	MP_SENTAKU_KOUZOU,							// �\������
};

//===========================================================================
//		���͓_�敪
//
enum MPInpKb {
	MP_INPKB_NONE,								// ���w�����
	MP_INPKB_1PT = 1,							// �P�_����
	MP_INPKB_DIR1PT,							// �����P�_����
	MP_INPKB_LEN2PT,							// �����Q�_����
	MP_INPKB_AREA,								// ������
	MP_INPKB_FREE								// ���R����
};

//===========================================================================
//		������R�[�h
//
enum MPHEIGHTCD {
	MP_HGTCD_SGL = 0,							// SGL					//ZZZZZ
	MP_HGTCD_KISOKJ,							// ��b�
	MP_HGTCD_SITAKJ,							// ���
	MP_HGTCD_UEKJ,								// ��
	MP_HGTCD_TENJOKJ,							// �V��
	MP_HGTCD_YANEKJ								// �����
};

//===========================================================================
//		�O���b�h�ۂ߃R�[�h
//
enum MPMARUMECD {
	MP_MRMCDN = 0,								// �ۂߖ���  
	MP_MRMCD1,									// �m�^�P�O���b�h�ۂ�
	MP_MRMCD2,									// �m�^�Q�O���b�h�ۂ�
	MP_MRMCD3,									// �m�^�R�O���b�h�ۂ�
	MP_MRMCD4,									// �m�^�S�O���b�h�ۂ�
	MP_MRMCD6,									// �m�^�U�O���b�h�ۂ�
	MP_MRMCD8									// �m�^�W�O���b�h�ۂ�
};

//===========================================================================
//		�ˑ��R�[�h
//
enum MPHAITICD {
	MP_HAICD_NINI = 0,							// �C��
	MP_HAICD_KABESINZUKE,						// �ǐc�t��
	MP_HAICD_YANEKOUSEISENZUKE					// �����\�����t��
};

//===========================================================================
//		�ˑ��R�[�h
//
enum MPIZONCD {
	MP_IZNCD_N = 0,								// ����
	MP_IZNCD_SUIHEI,							// ����
	MP_IZNCD_SUICYOKU,							// ����
	MP_IZNCD_TENJONETAUE,						// �V�䍪����
	MP_IZNCD_YANEMENNARI,						// �����ʂȂ�
	MP_IZNCD_YANEMENNARIENCYOKU,				// �����ʂȂ艔��
	MP_IZNCD_YANEMENNARISUICYOKU,				// �����ʂȂ萂��
	MP_IZNCD_YANEKOSEISENNARI,					// �����\�����Ȃ�
	MP_IZNCD_TARUKISITA,						// ���؉�
	MP_IZNCD_TARUKISITAYANEMENHEIKOU,			// ���؉������ʕ��s
	MP_IZNCD_TARUKISITASUICYOKU,				// ���؉�����
	MP_IZNCD_NOKISAKINARI						// ����Ȃ�
};

//===========================================================================
//		�K�A�g�A���ށA�I��
//
//	�K
#define		MMAX_KAI		3					// �ő�K��
enum MPKAI {
	MP_KAI1 = 1,								// �P�K
	MP_KAI2,									// �Q�K
	MP_KAI3										// �R�K
};

//	���̓��[�h
enum MPMODE {
	MP_MD_CREATE = 1,							// �n�����[�h
	MP_MD_DELETE,								// �폜���[�h
	MP_MD_MODIFY,								// �C�����[�h
	MP_MD_MOVE,									// �ړ����[�h
	MP_MD_COPY,									// ���ʃ��[�h
	MP_MD_PROPERTY								// �����\�����[�h
};

//	�g
#define		MMAX_KUMI		10					// �ő�g��
enum MPKOSEI {
	MP_GP_KISO = 1,								// "��b"
	MP_GP_DODAI,								// "�y��"
	MP_GP_YUKA,									// "���g"
	MP_GP_KABE,									// "�ǘg�g"
	MP_GP_TAIRYOKU,								// "�ϗ͕�"
	MP_GP_TENJO,								// "�V��g"
	MP_GP_KOYA,									// "�����g"
	MP_GP_YAGIRI,								// "���"
	MP_GP_YANE,									// "����"

	MP_GP_JYUKO = 101,							// "�Z��"
	MP_GP_JYUTO,								// "�Z��"
	MP_GP_BUKKEN,								// "����"
	MP_GP_S_YANE,								// "�݌v����"
	MP_GP_SIKITI,								// "�~�n"
	MP_GP_HEKIRYOU								// "�Ǘ�"
};

//	����
enum MPBUNRUI {
	MP_BR_BUZAI = 0,							// "����"
	MP_BR_KANAGU,								// "����"
	MP_BR_PANEL,								// "�p�l��"
	MP_BR_YANE,									// "����"
	MP_BR_KABE,									// "��"
	MP_BR_KISO,									// "��b"
	MP_BR_SENBUN,								// "����"
	MP_BR_KUKAKU,								// "���"
	MP_BR_KAIKO,								// "�J��"
	MP_BR_CYUKI,								// "���L"
	MP_BR_OTHER = 10							// "���̑�"
};

// �I��
enum MPSELECT {
	MP_SEL1 = 1,								// �I���P
	MP_SEL2,									// �I���Q
	MP_SEL3										// �I���R
};

//	�����l���̓��[�h
enum MPATTR {
	MP_AT_AUTO = -1,							// ����
	MP_AT_NONE = 0,								// �����l���͂Ȃ�
	MP_AT_HRZ_PARTS,							// �������ޓ��́A�X�Ε��ޓ���
	MP_AT_VRT_PARTS,							// �������ޓ���
	MP_AT_YTPANEL,								// ���V��p�l������
	MP_AT_YANEPANEL,							// �����p�l������
	MP_AT_ADJLNG,								// ���ޒ�����������
	MP_AT_YANE,									// ��������
	MP_AT_TATEGU								// �������ޓ���
};

//===========================================================================
//		�R���{�{�b�N�X�T�C�Y
#define		MX_CMB_PARTSNM	300					// ���ޖ��R���{�{�b�N�X�T�C�Y
#define		MX_CMB_CDMEMBER	200					// ���@�^���R���{�{�b�N�X�T�C�Y
#define		MX_CMB_PANELNO	300					// �p�l���ԍ��R���{�{�b�N�X�T�C�Y

#define		MX_CMB_ATTR		30					// �����l�R���{�{�b�N�X�T�C�Y

//	�������͗p�R���{�{�b�N�X�̑���ID
enum MCCMBATTR {
	MC_CMB_NULL = 100,							// ���ݒ�@�R���{�{�b�N�X��\��
	MC_CMB_LHS1,								// �����␳�l�P
	MC_CMB_LHS2,								// �����␳�l�Q
	MC_CMB_ZJSZ,								// �ގ��c�����
	MC_CMB_HAIZ,								// �z�u�_�����
	MC_CMB_TRTH,								// ���t������
	MC_CMB_KROH,								// �q�n�g
	MC_CMB_INTR,								// �Ԋu
	MC_CMB_HONS,								// �{��
//	MC_CMB_HHS1,								// ���␳�P
//	MC_CMB_HHS2,								// ���␳�Q
	MC_CMB_FHS1,								// ���E�V��p�l����O���␳
	MC_CMB_FHS2,								// �����p�l���p��O���␳
	MC_CMB_OKYK,								// ���s��
	MC_CMB_OHS2,								// ���s���␳
	MC_CMB_KOBY,								// �������z
	MC_CMB_NKDE,								// ���̏o
	MC_CMB_KRDE,								// �P���o�̏o
	MC_CMB_UPRH,								// ��[����
	MC_CMB_LWRH,								// ���[����
	MC_CMB_LFH1,								// ���E�V��p�l�����Е␳
	MC_CMB_RTH1,								// ���E�V��p�l���E�Е␳
	MC_CMB_LFH2,								// �����p�l���p���Е␳
	MC_CMB_RTH2,								// �����p�l���p�E�Е␳
};

//	�������͗p�`�F�b�N�{�b�N�X�̑���ID
enum MCCHKATTR {
	MC_CHK_NULL = 200,							// ���ݒ�@�`�F�b�N�{�b�N�X��\��
	MC_CHK_KATI,								// ����
	MC_CHK_MULT,								// ����
	MC_CHK_INTC,								// �������ޒ���
	MC_CHK_NKTP									// ����^�C�v(0:���z���܂�A1:����)
};

#define		MC_INT_JIDO 	9999				// ����
#define		MC_STR_JIDO 	Mstr( "����")		// ����
#define		MC_INT_AREA 	9998				// �̈�
#define		MC_STR_AREA 	Mstr( "�̈�w��")	// �̈�

#define		MMAX_BZI_HONSU	100					// �ő�z�u���i�{��(N�{�z�u)

//	�h���b�M���O���̓��[�h�i���o�[�o���h�\���`��j
#define		MC_RBND_LINE	1					// �����\�� Line
#define		MC_RBND_RECT	2					// �����`�\�� Rectangle
#define		MC_RBND_POLYGON	3					// ���p�`�\�� Polygon
#define		MC_RBND_PARALOG	4					// ���s�l�ӌ`�\�� Parallelogram

//	�������́@���ގ��
//enum MCINPATTRTYP {
//	MC_INP_HOR_PARTS,							// ���u������
//	MC_INP_VER_PARTS,							// �c�u������
//	MC_INP_HOR_PANEL,							// ���u���p�l��
//	MC_INP_VER_PANEL,							// �c�u���p�l��
//	MC_INP_TATEGU								// ����
//};

#define		MMAX_PARTSTP	300										// �ő啔�ގ�ސ�

#define		MMAX_BZILEN		30000.									// �ő啔�ޒ���30m
#define		MMIN_BZILEN		1.										// �ŏ����ޒ���
#define		MMIN_BZILEN_2	(MMIN_BZILEN * MMIN_BZILEN)				// �ŏ����ޒ��� * �ŏ����ޒ���

	