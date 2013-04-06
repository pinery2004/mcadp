#pragma once

#define		MDR_TYPE1	0					// �f�[�^�ǂݍ��݃^�C�v�@0:OLD	1:NEW
#define		MDR_TYPE2	0					// �����f�[�^�ǂݍ��݃^�C�v�@0:OLD	1:NEW
#define		MDW_TYPE0	1					// �f�[�^�������݃^�C�v�@0:OLD	1:NEW

//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhDefine.cpp
//
//		�c�a�ǂݏ�����`
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
// �O���t�@�C���c�a	�����R�[�h(�Ǎ��p)
//
#define		MX_HAITI	5000
#define		MX_POINT	500
#define		MX_INT		500

#define		MDR_ATRCD_GRID					010

//-------------------------------------------------------------------------------------

#if (MDR_TYPE1)

// ���ޔz�u���R�[�h
#define		MDR_ATRCD_HAITIEN_ST			100						// �z�u���R�[�h�n�J
#define			MDR_ATRCD_HAITIEN_IKAI			100010
#define			MDR_ATRCD_HAITIEN_ICDHGT		100020
#define			MDR_ATRCD_HAITIEN_IPANELNO		100030
#define			MDR_ATRCD_HAITIEN_IKAIKONO		100040
#define			MDR_ATRCD_HAITIEN_IPARTSTPID	100050
#define			MDR_ATRCD_HAITIEN_IPARTSTPCD	100051
#define			MDR_ATRCD_HAITIEN_IMEMBERID		100060
#define			MDR_ATRCD_HAITIEN_IMEMBERCD		100061
#define			MDR_ATRCD_HAITIEN_LNHAITI		100070
#define			MDR_ATRCD_HAITIEN_PTUPHAITI		100071
#define			MDR_ATRCD_HAITIEN_RSINZURE		100080
#define			MDR_ATRCD_HAITIEN_RHAITIZURE	100090
#define			MDR_ATRCD_HAITIEN_RNAGASAHOSEI	100100
#define			MDR_ATRCD_HAITIEN_RTAKASA		100110
#define			MDR_ATRCD_HAITIEN_DISPLAYFLAG	100120
#define			MDR_ATRCD_HAITIEN_PTCMNT1		100130

#define			MDR_ATRCD_HAITIEN_MEMBER		101

// ������
#define			MDR_ATRCD_HAITIEN_TATEGU		110					// ����R�[�h
#define			MDR_ATRCD_HAITIEN_TATEGU_ST		11000				// ����R�[�h�J�n
#define				MDR_ATRCD_HAITIEN_CCODE			110010
#define				MDR_ATRCD_HAITIEN_RROW			110020
#define				MDR_ATRCD_HAITIEN_RROH			110030
#define				MDR_ATRCD_HAITIEN_RHEIGHT		110040
#define				MDR_ATRCD_HAITIEN_RMUSZ			110050
#define			MDR_ATRCD_HAITIEN_TATEGU_EOR	11099				// ����R�[�h�I��

#else

#define		MDR_ATRCD_HAITIEN_ST			100						// �z�u���R�[�h
#define		MDR_ATRCD_HAITIEN_EOR			199						// End of Record
#define			MDR_ATRCD_HAITIEN_IKAI			100010
#define			MDR_ATRCD_HAITIEN_ICDHGT		100020
#define			MDR_ATRCD_HAITIEN_IPANELNO		100030
#define			MDR_ATRCD_HAITIEN_IKAIKONO		100040
#define			MDR_ATRCD_HAITIEN_IPARTSTPID	100050
#define			MDR_ATRCD_HAITIEN_IPARTSTPCD	100051
#define			MDR_ATRCD_HAITIEN_IMEMBERID		100060
#define			MDR_ATRCD_HAITIEN_IMEMBERCD		100061
#define			MDR_ATRCD_HAITIEN_LNHAITI		100070
#define			MDR_ATRCD_HAITIEN_PTUPHAITI		100071
#define			MDR_ATRCD_HAITIEN_RSINZURE		100080
#define			MDR_ATRCD_HAITIEN_RHAITIZURE	100090
#define			MDR_ATRCD_HAITIEN_RNAGASAHOSEI	100100
#define			MDR_ATRCD_HAITIEN_RTAKASA		100110
#define			MDR_ATRCD_HAITIEN_DISPLAYFLAG	100120
#define			MDR_ATRCD_HAITIEN_PTCMNT1		100130
#define		MDR_ATRCD_HAITIEN_MEMBER		101

#define		MDR_ATRCD_HAITIEN_TATEGU		110						// ����R�[�h
//#define		MDR_ATRCD_HAITIEN_TATEGU		1100				// ����R�[�h
//#define		MDR_ATRCD_HAITIEN_TATEGU_EOR	1199
#define			MDR_ATRCD_HAITIEN_CCODE			110010
#define			MDR_ATRCD_HAITIEN_RROW			110020
#define			MDR_ATRCD_HAITIEN_RROH			110030
#define			MDR_ATRCD_HAITIEN_RHEIGHT		110040
#define			MDR_ATRCD_HAITIEN_RMUSZ			110050

#endif

//-------------------------------------------------------------------------------------

#if (MDR_TYPE1)

//#define		MDR_ATRCD_HAITIEN_TENKAI		111						// �z�u�W�J
// �Z���W�J
#define			MDR_ATRCD_HAITIEN_TENKAI_ST		11100					// �z�u�W�J
#define			MDR_ATRCD_HAITIEN_TENKAI_EOR	11199
//#define			MDR_ATRCD_HAITIEN_TENKAIPARA	111010

// �o�[�W���� 
#define		MDR_ATRCD_HAITIEN_VERSION		120						// �o�[�W����
// �n�o�s�Q
#define		MDR_ATRCD_HAITIEN_OPTION1		130						// �o�[�W����
#define		MDR_ATRCD_HAITIEN_OPTION2		131

#define		MDR_ATRCD_HAITIEN_EOR			199						// �z�u���R�[�h�I��

// �n�o�s�Q�Ǘ����
#define		MDR_ATRCD_OPTION_KANRI			132

#define		MDR_ATRCD_VERSION_KANRI0		121

#define		MDR_ATRCD_VERSION_KANRI1			122
#define		MDR_ATRCD_VERSION_KANRI2			123
#define		MDR_ATRCD_VERSION_KANRI3			124

#else

#define		MDR_ATRCD_HAITIEN_TENKAI		111						// �z�u�W�J
//#define			MDR_ATRCD_HAITIEN_TENKAIPARA	111010

#define		MDR_ATRCD_HAITIEN_VERSION		120						// �o�[�W����
#define		MDR_ATRCD_VERSION_KANRI0		121
#define		MDR_ATRCD_VERSION_KANRI1		122
#define		MDR_ATRCD_VERSION_KANRI2		123
#define		MDR_ATRCD_VERSION_KANRI3		124
#define		MDR_ATRCD_HAITIEN_OPTION1		130						// �o�[�W����
#define		MDR_ATRCD_HAITIEN_OPTION2		131
#define		MDR_ATRCD_OPTION_KANRI			132

#endif

//-------------------------------------------------------------------------------------

#if (MDR_TYPE1)

// �}�`���
#define		MDR_ATRCD_HAITIEN_ZUKEI			151						// �}�`���R�[�h
#define		MDR_ATRCD_HAITIEN_ZUKEI_ST		15100
#define		MDR_ATRCD_HAITIEN_ZUKEI_OBJ			15101
#define		MDR_ATRCD_HAITIEN_ZUKEI_TP			15102
#define		MDR_ATRCD_HAITIEN_ZUKEI_N			15103
#define		MDR_ATRCD_HAITIEN_ZUKEI_BUF			15104
#define		MDR_ATRCD_HAITIEN_ZUKEI_EOR		15199

#else

#define		MDR_ATRCD_HAITIEN_ZUKEI			151						// �}�`���R�[�h
#define		MDR_ATRCD_HAITIEN_ZUKEIN		152

#endif

//-------------------------------------------------------------------------------------

#if (MDR_TYPE2)

#define		MDR_ATRCD_ROOFEN_ST				200
#define		MDR_ATRCD_ROOFEN_EOR			299						// End of Record
#define			MDR_ATRCD_ROOFEN_KAI			200010

#define		MDR_ATRCD_JIM					210
#define		MDR_ATRCD_JIM_ST				21000
#define			MDR_ATRCD_JIM_P					210010
#define			MDR_ATRCD_JIM_ICD				210020
#define			MDR_ATRCD_JIM_IFINP				210030
#define			MDR_ATRCD_JIM_RKB				210040
#define			MDR_ATRCD_JIM_IRFM				210050
#define			MDR_ATRCD_JIM_LNR				210060
#define			MDR_ATRCD_JIM_ILNRCD			210070
#define		MDR_ATRCD_JIM_EOR				21099

#define		MDR_OLD_ATRCD_RFM				220
#define		MDR_OLD_ATRCD_RFM_PG_PT			222
#define		MDR_OLD_ATRCD_RFM_ICD_I			224

#define		MDR_ATRCD_RFM_ST				22000
#define			MDR_ATRCD_RFM_PLN				220010
#define			MDR_ATRCD_RFM_PG				220020
#define			MDR_ATRCD_RFM_ICDPG				220030
#define			MDR_ATRCD_RFM_ICD				220040
#define		MDR_ATRCD_RFM_EOR				22099

#else

#define		MDR_ATRCD_ROOFEN				200
#define		MDR_ATRCD_ROOFEN_EOR			299						// End of Record
#define		MDR_ATRCD_JIM					210
#define		MDR_ATRCD_JIM_EOR				219

//#define		MDR_ATRCD_RFM				220
#define		MDR_OLD_ATRCD_RFM				220
#define		MDR_ATRCD_RFM_PG				221

//#define		MDR_ATRCD_RFM_PG_PT				222
#define		MDR_OLD_ATRCD_RFM_PG_PT				222
#define		MDR_ATRCD_RFM_ICD				223
//#define		MDR_ATRCD_RFM_ICD_I				224
#define		MDR_OLD_ATRCD_RFM_ICD_I				224
#define		MDR_ATRCD_RFM_EOR				229

#endif

//-------------------------------------------------------------------------------------

#if (MDR_TYPE2)

#define		MDR_ATRCD_KSI					230
#define		MDR_ATRCD_KSI_ST				23000
#define			MDR_ATRCD_KSI_LN				230010
#define			MDR_ATRCD_KSI_TPLN				230020
#define			MDR_ATRCD_KSI_CD				230030
#define			MDR_ATRCD_KSI_FPROC				230040
#define			MDR_ATRCD_KSI_RFM				230050
#define		MDR_ATRCD_KSI_EOR				23099

#endif

//-------------------------------------------------------------------------------------

#if (MDW_TYPE0)

//==========================================================================================
//
// �O���t�@�C���c�a	�����R�[�h(�����p)
//
#define		MX_HAITI	5000
#define		MX_POINT	500
#define		MX_INT		500

//
#define		MDW_ATRCD_GRID					010

// ���ޔz�u���R�[�h
#define		MDW_ATRCD_HAITIEN_ST			100						// �z�u���R�[�h�n�J
#define			MDW_ATRCD_HAITIEN_IKAI			100010
#define			MDW_ATRCD_HAITIEN_ICDHGT		100020
#define			MDW_ATRCD_HAITIEN_IPANELNO		100030
#define			MDW_ATRCD_HAITIEN_IKAIKONO		100040
#define			MDW_ATRCD_HAITIEN_IPARTSTPID	100050
#define			MDW_ATRCD_HAITIEN_IPARTSTPCD	100051
#define			MDW_ATRCD_HAITIEN_IMEMBERID		100060
#define			MDW_ATRCD_HAITIEN_IMEMBERCD		100061
#define			MDW_ATRCD_HAITIEN_LNHAITI		100070
#define			MDW_ATRCD_HAITIEN_PTUPHAITI		100071
#define			MDW_ATRCD_HAITIEN_RSINZURE		100080
#define			MDW_ATRCD_HAITIEN_RHAITIZURE	100090
#define			MDW_ATRCD_HAITIEN_RNAGASAHOSEI	100100
#define			MDW_ATRCD_HAITIEN_RTAKASA		100110
#define			MDW_ATRCD_HAITIEN_DISPLAYFLAG	100120
#define			MDW_ATRCD_HAITIEN_PTCMNT1		100130

#define			MDW_ATRCD_HAITIEN_MEMBER		101

// ������
#define			MDW_ATRCD_HAITIEN_TATEGU_ST		11000				// ����R�[�h�J�n
#define				MDW_ATRCD_HAITIEN_CCODE			110010
#define				MDW_ATRCD_HAITIEN_RROW			110020
#define				MDW_ATRCD_HAITIEN_RROH			110030
#define				MDW_ATRCD_HAITIEN_RHEIGHT		110040
#define				MDW_ATRCD_HAITIEN_RMUSZ			110050
#define			MDW_ATRCD_HAITIEN_TATEGU_EOR	11099				// ����R�[�h�I��

// �Z���W�J
#define			MDW_ATRCD_HAITIEN_TENKAI_ST		11100
#define			MDW_ATRCD_HAITIEN_TENKAI_EOR	11199
#define				MDW_ATRCD_HAITIEN_TENKAIPARA	111010

// �o�[�W���� 
#define		MDW_ATRCD_HAITIEN_VERSION		120
// �n�o�s�Q
#define		MDW_ATRCD_HAITIEN_OPTION1		130
#define		MDW_ATRCD_HAITIEN_OPTION2		131

#define		MDW_ATRCD_HAITIEN_EOR			199						// �z�u���R�[�h�I��

// �n�o�s�Q�Ǘ����
#define		MDW_ATRCD_OPTION_KANRI			132

#define		MDW_ATRCD_VERSION_KANRI0		121

#define			MDW_ATRCD_VERSION_KANRI1		122
#define			MDW_ATRCD_VERSION_KANRI2		123
#define			MDW_ATRCD_VERSION_KANRI3		124

// �}�`���
#define		MDW_ATRCD_HAITIEN_ZUKEI_ST		15100
#define		MDW_ATRCD_HAITIEN_ZUKEI_OBJ			15101
#define		MDW_ATRCD_HAITIEN_ZUKEI_TP			15102
#define		MDW_ATRCD_HAITIEN_ZUKEI_N			15103
#define		MDW_ATRCD_HAITIEN_ZUKEI_BUF			15104
#define		MDW_ATRCD_HAITIEN_ZUKEI_EOR		15199

#define		MDW_ATRCD_ROOFEN_ST				200
#define		MDW_ATRCD_ROOFEN_EOR			299						// End of Record
#define			MDW_ATRCD_ROOFEN_KAI			200010
//#define			MDW_ATRCD_ROOFEN_PTH			200020
//#define			MDW_ATRCD_ROOFEN_GNUM			200030
//#define			MDW_ATRCD_ROOFEN_GHM			200040
//#define			MDW_ATRCD_ROOFEN_TPRF			200050
//#define			MDW_ATRCD_ROOFEN_KB				200060
//#define			MDW_ATRCD_ROOFEN_RKH			200070
//#define			MDW_ATRCD_ROOFEN_RFMA			200080
//#define			MDW_ATRCD_ROOFEN_NUMA			200090
//#define			MDW_ATRCD_ROOFEN_MNZ			200100
//#define			MDW_ATRCD_ROOFEN_NKD			200110
//#define			MDW_ATRCD_ROOFEN_KRD			200120
//#define			MDW_ATRCD_ROOFEN_TPNU			200130
//#define			MDW_ATRCD_ROOFEN_TPNS			200140
//#define			MDW_ATRCD_ROOFEN_HKMA			200150
//#define			MDW_ATRCD_ROOFEN_NKH			200160
//#define			MDW_ATRCD_ROOFEN_CDURS			200170

#define		MDW_ATRCD_JIM_ST				21000
#define			MDW_ATRCD_JIM_P					210010
#define			MDW_ATRCD_JIM_ICD				210020
#define			MDW_ATRCD_JIM_IFINP				210030
#define			MDW_ATRCD_JIM_RKB				210040
#define			MDW_ATRCD_JIM_IRFM				210050
#define			MDW_ATRCD_JIM_LNR				210060
#define			MDW_ATRCD_JIM_ILNRCD			210070
#define		MDW_ATRCD_JIM_EOR				21099

#define		MDW_ATRCD_RFM_ST				22000
#define		MDW_ATRCD_RFM_PG					22010
#define		MDW_ATRCD_RFM_ICDPG					22020
#define		MDW_ATRCD_RFM_ICD					22030
#define		MDW_ATRCD_RFM_EOR				22099

#define		MDW_ATRCD_KSI_ST				23000
#define			MDW_ATRCD_KSI_LN				230010
#define			MDW_ATRCD_KSI_TPLN				230020
#define			MDW_ATRCD_KSI_CD				230030
#define			MDW_ATRCD_KSI_FPROC				230040
#define			MDW_ATRCD_KSI_RFM				230050
#define		MDW_ATRCD_KSI_EOR				23099

#define		MDW_ATRCD_TENKAI				300
#define		MDW_ATRCD_TENKAI_EOR			309

//#define			MDW_ATRCD_TENKAI_NJUKO			300010
//#define			MDW_ATRCD_TENKAI_TPLN			300020

#else

//==========================================================================================
//
// �O���t�@�C���c�a	�����R�[�h(�����p)
//
#define		MX_HAITI	5000
#define		MX_POINT	500
#define		MX_INT		500

#define		MDW_ATRCD_GRID					010
#define		MDW_ATRCD_HAITIEN				100
#define		MDW_ATRCD_HAITIEN_EOR			199						// End of Record
#define			MDW_ATRCD_HAITIEN_IKAI			100010
#define			MDW_ATRCD_HAITIEN_ICDHGT		100020
#define			MDW_ATRCD_HAITIEN_IPANELNO		100030
#define			MDW_ATRCD_HAITIEN_IKAIKONO		100040
#define			MDW_ATRCD_HAITIEN_IPARTSTPID	100050
#define			MDW_ATRCD_HAITIEN_IPARTSTPCD	100051
#define			MDW_ATRCD_HAITIEN_IMEMBERID		100060
#define			MDW_ATRCD_HAITIEN_IMEMBERCD		100061
#define			MDW_ATRCD_HAITIEN_LNHAITI		100070
#define			MDW_ATRCD_HAITIEN_PTUPHAITI		100071
#define			MDW_ATRCD_HAITIEN_RSINZURE		100080
#define			MDW_ATRCD_HAITIEN_RHAITIZURE	100090
#define			MDW_ATRCD_HAITIEN_RNAGASAHOSEI	100100
#define			MDW_ATRCD_HAITIEN_RTAKASA		100110
#define			MDW_ATRCD_HAITIEN_DISPLAYFLAG	100120
#define			MDW_ATRCD_HAITIEN_PTCMNT1		100130
#define		MDW_ATRCD_HAITIEN_MEMBER		101
#define		MDW_ATRCD_HAITIEN_TATEGU		11000
#define		MDW_ATRCD_HAITIEN_TATEGU_EOR	11099
#define			MDW_ATRCD_HAITIEN_CCODE			110010
#define			MDW_ATRCD_HAITIEN_RROW			110020
#define			MDW_ATRCD_HAITIEN_RROH			110030
#define			MDW_ATRCD_HAITIEN_RHEIGHT		110040
#define			MDW_ATRCD_HAITIEN_RMUSZ			110050
#define		MDW_ATRCD_HAITIEN_TENKAI		11100
#define		MDW_ATRCD_HAITIEN_TENKAI_EOR	11199
#define			MDW_ATRCD_HAITIEN_TENKAIPARA	111010
#define		MDW_ATRCD_HAITIEN_VERSION		120
#define		MDW_ATRCD_VERSION_KANRI0		121
#define		MDW_ATRCD_VERSION_KANRI1		122
#define		MDW_ATRCD_VERSION_KANRI2		123
#define		MDW_ATRCD_VERSION_KANRI3		124
#define		MDW_ATRCD_HAITIEN_OPTION1		130
#define		MDW_ATRCD_HAITIEN_OPTION2		131
#define		MDW_ATRCD_OPTION_KANRI			132
#define		MDW_ATRCD_HAITIEN_ZUKEI			151
#define		MDW_ATRCD_HAITIEN_ZUKEIN		152

#define		MDW_ATRCD_ROOFEN				200
#define		MDW_ATRCD_ROOFEN_EOR			299						// End of Record
#define			MDW_ATRCD_ROOFEN_KAI			200010
#define			MDW_ATRCD_ROOFEN_PTH			200020
#define			MDW_ATRCD_ROOFEN_GNUM			200030
#define			MDW_ATRCD_ROOFEN_GHM			200040
#define			MDW_ATRCD_ROOFEN_TPRF			200050
#define			MDW_ATRCD_ROOFEN_KB				200060
#define			MDW_ATRCD_ROOFEN_RKH			200070
#define			MDW_ATRCD_ROOFEN_RFMA			200080
#define			MDW_ATRCD_ROOFEN_NUMA			200090
#define			MDW_ATRCD_ROOFEN_MNZ			200100
#define			MDW_ATRCD_ROOFEN_NKD			200110
#define			MDW_ATRCD_ROOFEN_KRD			200120
#define			MDW_ATRCD_ROOFEN_TPNU			200130
#define			MDW_ATRCD_ROOFEN_TPNS			200140
#define			MDW_ATRCD_ROOFEN_HKMA			200150
#define			MDW_ATRCD_ROOFEN_NKH			200160
#define			MDW_ATRCD_ROOFEN_CDURS			200170

#define		MDW_ATRCD_JIM					210
#define		MDW_ATRCD_JIM_EOR				219
#define			MDW_ATRCD_JIM_P					210010
#define			MDW_ATRCD_JIM_ICD				210020
#define			MDW_ATRCD_JIM_IFINP				210030
#define			MDW_ATRCD_JIM_RKB				210040
#define			MDW_ATRCD_JIM_IRFM				210050
#define			MDW_ATRCD_JIM_LNR				210060
#define			MDW_ATRCD_JIM_ILNRCD			210070

#define		MDW_ATRCD_KSI					220
#define		MDW_ATRCD_KSI_EOR				229
#define			MDW_ATRCD_KSI_LN				220010
#define			MDW_ATRCD_KSI_TPLN				220020
#define			MDW_ATRCD_KSI_CD				220030
#define			MDW_ATRCD_KSI_FPROC				220040
#define			MDW_ATRCD_KSI_RFM				220050


#define		MDW_ATRCD_RFM					230
#define		MDW_ATRCD_RFM_PG				231

#define		MDW_ATRCD_RFM_PG_PT				232
#define		MDW_ATRCD_RFM_ICD				233
#define		MDW_ATRCD_RFM_ICD_I				234
#define		MDW_ATRCD_RFM_EOR				239

#define		MDW_ATRCD_TENKAI				300
#define		MDW_ATRCD_TENKAI_EOR			309
#define			MDW_ATRCD_TENKAI_NJUKO			300010
#define			MDW_ATRCD_TENKAI_TPLN			300020

#endif

//
//	�����c�a
//
//	�萔
#define		MD_MAX_BKAI				2											// �ő�n���K��
#define		MD_MAX_FKAI				5											// �ő�n��K��
#define		MD_MAX_AKAI				( MD_MAX_BKAI + 1 + MD_MAX_FKAI)			// �ő�S�K���i�ő�n��{�n�K + �n���K���j
//#define		MD_MAX_SCM_KZTP			4											// �ő�\���X�L�[�}��ސ�

#define		MDIDGRPK(G,K)			( G + K + MD_MAX_BKAI) 
#define		MDIDSCMT(S,T)			( S + T)

// �O���[�v
#define		MD_NM_GRP_WIN			Mstr( "�E�B���h�E")
#define		MD_NH_GRP_WIN			0
#define		MD_NM_GRP_SHIKITI		Mstr( "�~�n")
#define		MD_NH_GRP_SHIKITI		1
#define		MD_NM_GRP_GAIKOU		Mstr( "�O�\")
#define		MD_NH_GRP_GAIKOU		1
#define		MD_NM_GRP_ISHOU			Mstr( "�ӏ�")
#define		MD_NH_GRP_ISHOU			2
#define		MD_NM_GRP_KOUZOU		Mstr( "�\��")
#define		MD_NH_GRP_KOUZOU		( MD_NH_GRP_ISHOU + MD_MAX_AKAI)

#define		MD_N_GRP				( MD_NH_GRP_KOUZOU + MD_MAX_AKAI)

//// �X�L�[�}
// �O�\�̎��
#define		MD_NM_SCMS_KUKAKU		Mstr( "�}�`")				// ���A����
#define		MD_NH_SCMS_KUKAKU		0
#define		MD_NM_SCMS_HAITI		Mstr( "�z�u")
#define		MD_NH_SCMS_HAITI		1
#define		MD_NM_SCMS_PANEL		Mstr( "��")
#define		MD_NH_SCMS_PANEL		2
#define		MD_NM_SCMS_BUZAI		Mstr( "��")
#define		MD_NH_SCMS_BUZAI		3
#define		MD_NM_SCMS_CHUKI		Mstr( "���L")
#define		MD_NH_SCMS_CHUKI		4

// �ӏ��̎��
#define		MD_NM_SCMI_KUKAKU		Mstr( "�}�`")				// ���A����
#define		MD_NH_SCMI_KUKAKU		0
#define		MD_NM_SCMI_HAITI		Mstr( "�z�u")
#define		MD_NH_SCMI_HAITI		1
#define		MD_NM_SCMI_WALL			Mstr( "��")
#define		MD_NH_SCMI_WALL			2
#define		MD_NM_SCMI_ROOM			Mstr( "����")
#define		MD_NH_SCMI_ROOM			3
#define		MD_NM_SCMI_TATEGU		Mstr( "����")
#define		MD_NH_SCMI_TATEGU		4
#define		MD_NM_SCMI_CHUKI		Mstr( "���L")
#define		MD_NH_SCMI_CHUKI		5

// �\�����ނ̎��(KIND)
#define		MD_NM_SCMK_KUKAKU		Mstr( "�}�`")				// ���A����
#define		MD_NH_SCMK_KUKAKU		0
#define		MD_NM_SCMK_BUZAI		Mstr( "����")
#define		MD_NH_SCMK_BUZAI		1
#define		MD_NM_SCMK_PANEL		Mstr( "�p�l��")
#define		MD_NH_SCMK_PANEL		2
#define		MD_NM_SCMK_KANAGU		Mstr( "����")
#define		MD_NH_SCMK_KANAGU		3
#define		MD_NM_SCMK_CHUKI		Mstr( "���L")
#define		MD_NH_SCMK_CHUKI		4

#define		MD_N_SCMK				( MD_NH_SCMK_CHUKI + 1)		// �X�L�[�}��ސ�

// �X�L�[�}
// ��ޕ������s���X�L�[�}
#define		MD_NM_SCM_GRID			Mstr( "�O���b�h")
#define		MD_NH_SCM_GRID			0
#define		MD_NM_SCM_HAITI			Mstr( "�z�u")
#define		MD_NH_SCM_HAITI			1
#define		MD_NM_SCM_GAIKOU		Mstr( "�O�\")
#define		MD_NH_SCM_GAIKOU		1
#define		MD_NM_SCM_ISYOU			Mstr( "�ӏ�")
#define		MD_NH_SCM_ISYOU			1

#define		MD_N_SCM1

// �\�����ނ̎�ޕ������s���X�L�[�}
#define		MD_NM_SCM_KISO			Mstr( "��b")
#define		MD_NH_SCM_KISO			2
#define		MD_NM_SCM_DODAI			Mstr( "�y��")
#define		MD_NH_SCM_DODAI			( MD_NH_SCM_KISO + MD_N_SCMK)
#define		MD_NM_SCM_YUKA			Mstr( "��")
#define		MD_NH_SCM_YUKA			( MD_NH_SCM_DODAI + MD_N_SCMK)
#define		MD_NM_SCM_KABE			Mstr( "��")
#define		MD_NH_SCM_KABE			( MD_NH_SCM_YUKA + MD_N_SCMK)
#define		MD_NM_SCM_TENJO			Mstr( "�V��")
#define		MD_NH_SCM_TENJO			( MD_NH_SCM_KABE + MD_N_SCMK)
#define		MD_NM_SCM_KOYA			Mstr( "����")
#define		MD_NH_SCM_KOYA			( MD_NH_SCM_TENJO + MD_N_SCMK)
#define		MD_NM_SCM_YANE			Mstr( "����")
#define		MD_NH_SCM_YANE			( MD_NH_SCM_KOYA + MD_N_SCMK)

#define		MD_N_SCMA				( MD_NH_SCM_YANE + MD_N_SCMK)
#define		MD_N_SCM2				( MD_N_SCMA - MD_N_SCM1)
#define		MD_N_SCM				7

// ���C���[
#define		MD_ID_LYR_GRID			0
#define		MD_ID_LYR_HAITI			1
#define		MD_ID_LYR_YANE			2
