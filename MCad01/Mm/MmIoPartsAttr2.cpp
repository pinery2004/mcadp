//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MnRibbonBarAttr.cpp
//
//		
//	�������̓��{���o�[
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g

#include "MlLog.h"
#include "MsMCAD.h"
#include "MainFrm.h"
#include "MhDefParts.h"

#define	DLL_EXPORT_MC_INPATTR_DO
#include "MmLib.h"
#include "MhInpPlcParts.h"
#include "MgGeo.h"

#define MC_SZ_CMBATTR	6
#define MC_SZ_CHKATTR	4

namespace MC
{
mmIoPartsAttr z_mmIA;

static int s_Combo_Attr[][10] = {								// MP_AT_NONE:			// 0
					{	MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_HRZ_PARTS:		// 1			// ���u����
					{ MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_ZJSZ,	// �����␳1, �����␳2, �c����
					MC_CMB_TRTH, MC_CMB_INTR, MC_CMB_HONS,		// ��t����, �Ԋu, �{��
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_VRT_PARTS:		// 2			// ���Ęg
					{ MC_CMB_UPRH, MC_CMB_LWRH, MC_CMB_HAIZ,	// ��[����, ���[����, �z�u����
					MC_CMB_NULL, MC_CMB_INTR, MC_CMB_HONS,		// null, �Ԋu, �{��
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_YTPANEL:		// 3			// ���E�V��p�l��
					{ MC_CMB_LFH1, MC_CMB_RTH1, MC_CMB_TRTH,	// ���Е␳, �E�Е␳, ��t����
					MC_CMB_FHS1, MC_CMB_OKYK, MC_CMB_OHS2,		// ��O�␳, ���s, ���s�␳
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_YANEPANEL:		// 4			// �����p�l��
					{ MC_CMB_LFH2, MC_CMB_RTH2, MC_CMB_TRTH,	// ���Е␳, �E�Е␳, ��t����
					MC_CMB_FHS2, MC_CMB_OKYK, MC_CMB_OHS2,		// ���̏o, ���s, ���s�␳
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NULL},					// null, null
																// MP_AT_ADJLNG:		// 5			// ���ޒ�������
					{ MC_CMB_LHS1, MC_CMB_NULL, MC_CMB_NULL,	// �����␳, null, null
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_KATI,					// null, ����
					MC_CHK_MULT, MC_CHK_INTC},					// ����, �������ޒ���
																// MP_AT_YANE:			// 6			// ����
					{ MC_CMB_KOBY, MC_CMB_NKDE, MC_CMB_KRDE,	// �������z, ���̏o, �P���o�̏o
					MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,		// null, null, null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null
					MC_CHK_NULL, MC_CHK_NKTP},					// null, ���^�C�v
																// MP_AT_TATEGU:		// 7			// ����
					{ MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_TRTH,	// �����␳1, �����␳2, ��t����
					MC_CMB_KROH, MC_CMB_HAIZ, MC_CMB_NULL,		// �q�n�g, �z�u���� ,null
					MC_CHK_NULL, MC_CHK_NULL,					// null, null 
					MC_CHK_NULL, MC_CHK_NULL}					// null, null
				};

static int s_IdcComboAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
static int s_IdcStaticAttr[6] =	{ IDC_CMBK_ATTR1, IDC_CMBK_ATTR2, IDC_CMBK_ATTR3,
								  IDC_CMBK_ATTR4, IDC_CMBK_ATTR5, IDC_CMBK_ATTR6};
static int s_IdcCheckAttr[4] =	{ IDC_CHECKATTR1, IDC_CHECKATTR2,
								  IDC_CHECKATTR3, IDC_CHECKATTR4};


//===========================================================================
//				�������p�X�^�e�B�b�N�f�[�^
//
//===========================================================================

static void MnsInitComboAttr( MCCMBATTR, MCCMBATTR, MCCMBATTR, MCCMBATTR, MCCMBATTR,
							  MCCMBATTR, MCCHKATTR, MCCHKATTR, MCCHKATTR, MCCHKATTR);

// ======== ���ޗp ========

// �����␳�l
static MREAL z_rLngH[] = {  95.5,  82.5,  70.0,  57.5,   44.5,  38.0, 
							32.0,   6.5,   0.0, -18.5,  -19.0, -31.5,
						   -38.0, -44.0, -44.5, -57.0,  -69.5, -70.0,
						   -82.5, -95.0, -95.5, -114.0};
#define	ISZLNGH		sizeof(z_rLngH)/sizeof(MREAL)
#define	INITLNGTH	0.0f

// �ގ��c�����
static MREAL z_rSinZ[] = {  76.5,   76.0,  63.5,  57.0,  53.5,  51.0,
							38.5,  38.0,  25.5,  19.0,  13.0,  12.5,
							 0.5,   0.0, -12.5,  -19.0, -25.0, -25.5,
						   -38.0, -50.5, -53.5, -57.0, -63.5, -95.0};
#define	ISZSINZ		sizeof(z_rSinZ)/sizeof(MREAL)
#define	INITSINZ	0.0f

// �z�u�_�����
static MREAL z_rHaiZ[] = { 152.5, 127.0,  114.5,  101.5,  95.5,  89.0,
							76.5,  70.0,   63.5,   57.0,  51.0,  44.5,
							38.5,  25.5,   19.0,   13.0,   0.5,   0.0,
						   -12.5, -19.0,  -25.0,  -50.5, -57.0, -95.0};
#define	ISZHAIZ	sizeof(z_rHaiZ)/sizeof(MREAL)
#define	INITHAIZ	0.0f

// ���t������
static MREAL z_rZ1[] = { 2250.0, 2150.0, 2095.0, 2067.0, 2057.0, 2055.0,
						 2050.0, 2010.0, 1950.0, 1850.0, 1810.0, 1750.0,
						 1650.0, 1550.0, 1450.0, 1350.0, 1250.0, 1150.0,
						 1050.0, 950.0, 850.0, 600.0, 0.0};
#define	ISZZ1		sizeof(z_rZ1)/sizeof(MREAL)
#define	INITZ1		0.0f

// �q�n�g
static MREAL z_rZ2[] = { 2250.0, 2150.0, 2095.0, 2067.0, 2055.0, 2050.0,
						 2010.0, 1950.0, 1850.0, 1550.0, 1545.0, 1450.0,
						 1400.0, 1350.0, 1245.0, 1000.0,  900.0,  750.0,
						  600.0, 0.0};
#define	ISZZ2		sizeof(z_rZ2)/sizeof(MREAL)
#define	INITZ2		0.0f

// �Ԋu
static MREAL z_rIntv[] = { 1820.0, 1368.0, 910.0, 455.0, 303.0, 227.5};
#define	ISZINTV		sizeof(z_rIntv)/sizeof(MREAL)
#define	INITINTV	455.0f

// �{��
static int	  z_iNum[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 
						   10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 9998};
#define	ISZNUM		sizeof(z_iNum)/sizeof(int)
#define	INITNUM		1

// ======== �p�l���p ========

// �p�l�����␳�l
static MREAL z_rLngH2[] = { 9999.0,  95.5,  70.0,  53.0,  44.5,  0.0,
							 -44.5, -53.0, -70.0, -95.5};
#define	ISZLNGH2	sizeof(z_rLngH2)/sizeof(MREAL)
#define	INITLNGTH2	0.0f

// ��O���␳�l�A���s���␳�l
static MREAL z_rOkuH[] = { 9999.0,	 95.5,	70.0,  53.0,  44.5,  0.0,
							-44.5,  -53.0, -70.0, -95.5};
#define	ISZOKUYUKIH	sizeof(z_rOkuH)/sizeof(MREAL)
#define	INITOKUYUKIH	0.0f

// ���s��
static MREAL z_rOku[] = {	7280.0, 6825.0, 6370.0, 5915.0, 5460.0, 5005.0, 
							4550.0, 4095.0, 3640.0, 3185.0, 2730.0, 2275.0,
							1820.0, 1365.0,  910.0,  455.0, 9999.0};
#define	ISZOKUYUKI	sizeof(z_rOku)/sizeof(MREAL)
#define	INITOKUYUKI		3640.0f

// �������z
static int z_iKoubai[] = {	12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
#define	ISZKOUBAI	sizeof(z_iKoubai)/sizeof(int)
#define	INITKOUBAI		4

// ���̏o
static MREAL z_rNokiDe[] = {	650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZNOKINODE	sizeof(z_rNokiDe)/sizeof(MREAL)
#define	INITNOKINODE		650.0f

// �P���o�̏o
static MREAL z_rKerabanoDe[] = { 650.0, 455.0, 330.0, 44.5, 0.};
#define	ISZKERABANODE	sizeof(z_rKerabanoDe)/sizeof(MREAL)
#define	INITKERABANODE	650.0f


/////////////////////////////////////////////////////////////////////////////
//	�����l���̓��[�h�ŕ��ޑ������͗p���{���o�[�̍��ڂ�ݒ肷��
//	 (�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��)
//	
void mmIoPartsAttr::InitComboAttr(
						int		i_iIoPartsAttrMd	// �����l���̓��[�h
												//  MP_AT_AUTO(-1)		:�����ݒ�
												//	MP_AT_NONE(0)		:�����l���͂Ȃ�
												//	MP_AT_HRZ_PARTS(1)	:�������ޓ���
												//	MP_AT_VRT_PARTS(2)	:�������ޓ���
												//	MP_AT_YTPANEL(3)	:���V��p�l������
												//	MP_AT_YANEPANEL(4)	:�����p�l������
												//	MP_AT_ADJLNG(5)		:���ޒ�����������
												//	MP_AT_YANE(6)		:��������
												//	MP_AT_TATEGU(7)		:�������
				)
{
	static int s_Combo_Attr[][10] = {							// MP_AT_NONE:			// 0
					  {	MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_HRZ_PARTS:		// 1			// ���u����
					  { MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_ZJSZ,	// �����␳1, �����␳2, �c����
						MC_CMB_TRTH, MC_CMB_INTR, MC_CMB_HONS,	// ��t����, �Ԋu, �{��
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_VRT_PARTS:		// 2			// ���Ęg
					  { MC_CMB_UPRH, MC_CMB_LWRH, MC_CMB_HAIZ,	// ��[����, ���[����, �z�u����
						MC_CMB_NULL, MC_CMB_INTR, MC_CMB_HONS,	// null, �Ԋu, �{��
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_YTPANEL:		// 3			// ���E�V��p�l��
					  { MC_CMB_LFH1, MC_CMB_RTH1, MC_CMB_TRTH,// ���Е␳, �E�Е␳, ��t����
						MC_CMB_FHS1, MC_CMB_OKYK, MC_CMB_OHS2,	// ��O�␳, ���s, ���s�␳
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_YANEPANEL:		// 4			// �����p�l��
					  { MC_CMB_LFH2, MC_CMB_RTH2, MC_CMB_TRTH,	// ���Е␳, �E�Е␳, ��t����
						MC_CMB_FHS2, MC_CMB_OKYK, MC_CMB_OHS2,	// ���̏o, ���s, ���s�␳
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NULL},				// null, null
																// MP_AT_ADJLNG:		// 5			// ���ޒ�������
					  { MC_CMB_LHS1, MC_CMB_NULL, MC_CMB_NULL,	// �����␳, null, null
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_KATI,				// null, ����
						MC_CHK_MULT, MC_CHK_INTC},				// ����, �������ޒ���
																// MP_AT_YANE:			// 6			// ����
					  { MC_CMB_KOBY, MC_CMB_NKDE, MC_CMB_KRDE,	// �������z, ���̏o, �P���o�̏o
						MC_CMB_NULL, MC_CMB_NULL, MC_CMB_NULL,	// null, null, null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null
						MC_CHK_NULL, MC_CHK_NKTP},				// null, ���^�C�v
																// MP_AT_TATEGU:		// 7			// ����
					  { MC_CMB_LHS1, MC_CMB_LHS2, MC_CMB_TRTH,	// �����␳1, �����␳2, ��t����
						MC_CMB_KROH, MC_CMB_HAIZ, MC_CMB_NULL,	// �q�n�g, �z�u���� ,null
						MC_CHK_NULL, MC_CHK_NULL,				// null, null 
						MC_CHK_NULL, MC_CHK_NULL}				// null, null
					};

	int iC1, iAn;

	if ( !GetDispFlg())	goto EXIT;	

	if ( i_iIoPartsAttrMd >= 0)
		m_iIoPartsAttrMd = i_iIoPartsAttrMd;
	else
		m_iIoPartsAttrMd = MnCalcInpAtMode();

	if ( m_iIoPartsAttrMd < 0 || m_iIoPartsAttrMd >= MP_AT_END) {
		mlLog::LogOutT( MC_LOG_ERROR, Mstr( "�����l���̓��[�h�G���[: %d\n"), m_iIoPartsAttrMd);
		goto EXIT;
	}

	//	���ޑ������͗p�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��
	for ( iAn=1; iAn<=MC_SZ_CMBATTR; iAn++) {

		switch ( s_Combo_Attr[m_iIoPartsAttrMd][iAn-1]) {
			case MC_CMB_NULL:
				// �R���{�{�b�N�X�����������ɂ���
				SetComboAttrText( iAn, Mstr( ""));
				InitComboAttrR( iAn, 0, NULL, 0);
				break;
			case MC_CMB_LHS1:
				// �����␳�l1�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�����␳1"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LHS2:
				// �����␳�l2�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�����␳2"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_ZJSZ:
				// �ގ��c����ʑI��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�c����"));
				InitComboAttrR( iAn, ISZSINZ, z_rSinZ, INITSINZ);
				break;
			case MC_CMB_HAIZ:
				// �z�u�_����ʑI��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�z�u����"));
				InitComboAttrR( iAn, ISZHAIZ, z_rHaiZ, INITHAIZ);
				break;
			case MC_CMB_TRTH:
				// ���t�������I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "��t����"));
				InitComboAttrR( iAn, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_KROH:
				// �J��������(ROH)�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�q�n�g"));
				InitComboAttrR( iAn, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_INTR:
				// �Ԋu�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�Ԋu"));
				InitComboAttrR( iAn, ISZINTV, z_rIntv, INITINTV);
				break;
			case MC_CMB_HONS:
				// �{���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�{��"));
				InitComboAttrI( iAn, ISZNUM, z_iNum, INITNUM);
				break;

//			case MC_CMB_HHS1:
//				// ���␳�l1�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
//				SetComboAttrText( iAn, Mstr( "���␳1"));
//				InitComboAttrR( iAn, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;
//			case MC_CMB_HHS2:
//				// ���␳�l2�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
//				SetComboAttrText( iAn, Mstr( "���␳2"));
//				InitComboAttrR( iAn, ISZLNGH2, z_rLngH2, INITLNGTH2);
//				break;

			case MC_CMB_FHS1:
				// ����V��p�l���p�@��O�␳�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "��O�␳"));
				InitComboAttrR( iAn, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_FHS2:
				// �����p�l���p�@��O�␳�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���̏o"));
				InitComboAttrR( iAn, ISZKOUBAI, z_rNokiDe, INITNOKINODE);
				break;
			case MC_CMB_OKYK:
				// ���s���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���s"));
				InitComboAttrR( iAn, ISZOKUYUKI, z_rOku, INITOKUYUKI);
				break;
			case MC_CMB_OHS2:
				// ���s���␳�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���s�␳"));
				InitComboAttrR( iAn, ISZOKUYUKIH, z_rOkuH, INITOKUYUKIH);
				break;
			case MC_CMB_KOBY:
				// �������z�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�������z"));
				InitComboAttrI( iAn, ISZKOUBAI, z_iKoubai, INITKOUBAI);
				break;
			case MC_CMB_NKDE:
				// ���̏o�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���̏o"));
				InitComboAttrR( iAn, ISZNOKINODE, z_rNokiDe, INITNOKINODE);
				break;
			case MC_CMB_KRDE:
				// �P���o�̏o�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�P���o�̏o"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITKERABANODE);
				break;
			case MC_CMB_UPRH:
				// ��[�����I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "��[����"));
				InitComboAttrR( iAn, ISZZ2, z_rZ2, INITZ2);
				break;
			case MC_CMB_LWRH:
				// ���[�����I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���[����"));
				InitComboAttrR( iAn, ISZZ1, z_rZ1, INITZ1);
				break;
			case MC_CMB_LFH1:
				// ����V��p�l���p�@���Е␳(�����␳�l1)�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���Е␳"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_RTH1:
				// ����V��p�l���p�@�E�Е␳(�����␳�l2)�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�E�Е␳"));
				InitComboAttrR( iAn, ISZLNGH, z_rLngH, INITLNGTH);
				break;
			case MC_CMB_LFH2:
				// �����p�l���p�@���Е␳(�����␳�l1)�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "���Е␳"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
			case MC_CMB_RTH2:
				// �����p�l���p�@�E�Е␳(�����␳�l2)�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
				SetComboAttrText( iAn, Mstr( "�E�Е␳"));
				InitComboAttrR( iAn, ISZKERABANODE, z_rKerabanoDe, INITLNGTH);
				break;
		}
	}
//	for ( int iCn=1; iCn<=MC_SZ_CHKATTR; iCn++) {
//		switch (z_Check_Attr[iCn-1]) {
//			case MC_CHK_NULL:
//				// �`�F�b�N�{�b�N�X�����������ɂ���
//				SetCheckAttrText( iCn, NULL);		
//				SetCheckAttrCkb( iCn, 0);		
//				break;
//			case MC_CHK_KATI:
//				// �����������͗p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( iCn, Mstr( "����"));
//				SetCheckAttrCkb( iCn, 0);
//				break;
//			case MC_CHK_MULT:
//				// �������͗p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( iCn, Mstr( "����"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//			case MC_CHK_INTC:
//				// �������ޒ����p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( iCn, Mstr( "�������ޒ���"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//			case MC_CHK_NKTP:
//				// ����^�C�v(0:���z���܂�A1:����)
//				SetCheckAttrText( iCn, Mstr( "����^�C�v����"));
//				SetCheckAttrCkb( iCn, 1);
//				break;
//		}
//	}
EXIT:;
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̒l����荞��

void mmIoPartsAttr::GetComboAttrA( void)
{
	int		ist;

	MREAL	rComboAttr1;
	MREAL	rComboAttr2;
	MREAL	rComboAttr3;
	MREAL	rComboAttr4;
	MREAL	rComboAttr5;
	MREAL	rComboAttr6;
//S	int		iMode;
//
//	iMode = z_mmIA.GetAtMd();						// �����l���̓��[�h

	switch ( m_iIoPartsAttrMd)
	{
	case MP_AT_YTPANEL:
	case MP_AT_YANEPANEL:

		if ( m_iIoPartsAttrMd == MP_AT_YTPANEL) {				// ***** ���E�V��p�l�� *****
			z_mmIA.GetComboAttrR( MC_CMB_LFH1, &rComboAttr1);	// �@���Е␳�l�@���@�����␳�l1
			z_mmIA.GetComboAttrR( MC_CMB_RTH1, &rComboAttr2);	// �@�E�Е␳�l�@���@�����␳�l2
			z_mmIA.GetComboAttrR( MC_CMB_FHS1, &rComboAttr3);	// �@��O���␳�l�@���@��O���␳�l

		} else if ( m_iIoPartsAttrMd == MP_AT_YANEPANEL) {		// ***** �����p�l�� *****
			z_mmIA.GetComboAttrR( MC_CMB_LFH2, &rComboAttr1);	// �@���Е␳�l�@���@�����␳�l1
			z_mmIA.GetComboAttrR( MC_CMB_RTH2, &rComboAttr2);	// �@�E�Е␳�l�@���@�����␳�l2
			z_mmIA.GetComboAttrR( MC_CMB_FHS2, &rComboAttr3);	// �@���̏o�@���@��O���␳�l
		}

		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// ���@�����␳�l1
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// ���@�����␳�l2
		mtPlcInp::SetMaeHosei( rComboAttr3);					// ���@��O���␳�l

		z_mmIA.GetComboAttrR( MC_CMB_OKYK, &rComboAttr4);
		mtPlcInp::SetOku( rComboAttr4);							// ���s���@���@���s��

		z_mmIA.GetComboAttrR( MC_CMB_OHS2, &rComboAttr5);
		mtPlcInp::SetOkuHosei( rComboAttr5);					// ���s���␳�l�@���@���s���␳�l�@

		z_mmIA.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);
		mtPlcInp::SetHgt( 0, rComboAttr5);						// ���t�������@���@���t������ 
		break;

	case MP_AT_HRZ_PARTS:
	case MP_AT_VRT_PARTS:
	case MP_AT_TATEGU:
																// ***** ���u�����ށE�c�u�����ށE���� *****
		z_mmIA.GetComboAttrR( MC_CMB_LHS1, &rComboAttr1);
		mtPlcInp::SetLenHosei( 0, rComboAttr1);					// �����␳�l1 �@���@�����␳�l1

		z_mmIA.GetComboAttrR( MC_CMB_LHS2, &rComboAttr2);
		mtPlcInp::SetLenHosei( 1, rComboAttr2);					// �����␳�l2 �@���@�����␳�l2

		z_mmIA.GetComboAttrR( MC_CMB_ZJSZ, &rComboAttr3);
		mtPlcInp::SetSinZure( rComboAttr3);						// �ގ��c����ʁ@���@�ގ��c�����

		z_mmIA.GetComboAttrR( MC_CMB_HAIZ, &rComboAttr4);
		mtPlcInp::SetPlcZure( rComboAttr4);						// �z�u�_����ʁ@���@�z�u�_�����

		ist = z_mmIA.GetComboAttrR( MC_CMB_TRTH, &rComboAttr5);	// ���t�������@���@����1
		if ( ist == 0)
			ist = z_mmIA.GetComboAttrR( MC_CMB_LWRH, &rComboAttr5);	// ���[�����@���@����1

		mtPlcInp::SetHgt( 0, rComboAttr5);						// ���@����1
		mtTateguInp::SetHeight( rComboAttr5);					// ���@�����

		ist = z_mmIA.GetComboAttrR( MC_CMB_KROH, &rComboAttr6);	// ����ROH�@���@����2
		if ( ist ==0)
			ist = z_mmIA.GetComboAttrR( MC_CMB_UPRH, &rComboAttr6);	// ��[�����@���@����2

		mtPlcInp::SetHgt( 1, rComboAttr6);						// ���@����2
		mtTateguInp::SetROH( rComboAttr6);						// ���@����ROH

		break;

	case MP_AT_ADJLNG:											// ***** ���ޒ����������� *****
	case MP_AT_YANE:											// ***** �������� *****

		ASSERT(false);											// �G���[
		break;
	}

}

///////////////////////////////////////////////////////////////////////////////
//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�

int mmIoPartsAttr::MnCalcInpAtMode()
{
	int		iMode;								// �����l���̓��[�h
	int		iGp;
	int		iBr;

	int		iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;

	// ���ޑ����l���̓��[�h( iMode)(�\������)�̌���
	iGp = z_mnIA.GetKCdGp();
	iBr = z_mnIA.GetKCdBr();

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	if ( pPartsSpec->IsTategu()) {								// (���i���ID == ����)
		iMode = MP_AT_TATEGU;									//			�������

	} else if ( pPartsSpec->IsFrame())	{						// (���i���ID == ���Ęg | ��) (�ˑ��R�[�h == ����)
		iMode = MP_AT_VRT_PARTS;								//			�������ޓ���

	} else if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {	// (���i���ID == �p�l�� | �J��)
		if ( iGp == MP_GP_YUKA || iGp == MP_GP_TENJO)			//		(�\���R�[�h == �� | �V��)
			iMode = MP_AT_YTPANEL;								//			���E�V��p�l������

		else if ( iGp == MP_GP_YANE)							//		(�\�� == ����)
			iMode = MP_AT_YANEPANEL;							//			�����p�l������

		else													//		(���̑�)
			iMode = MP_AT_HRZ_PARTS;							//			���u�����ޓ���

	} else if ( iBr == MP_BR_YANE) {							// (���� == ����)
		if ( iGp == MP_GP_YANE) 								//		(�\�� == ����)
			iMode = MP_AT_YANE;									//			��������
		else													//		(���̑�)
			iMode = MP_AT_HRZ_PARTS;							//			���u�����ޓ���

	} else {													// (���̑�)
		iMode = MP_AT_HRZ_PARTS;								//			���u������
	}
	return iMode;
}

//////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�ԍ����擾����

int mmIoPartsAttr::GetComboAttrNo(
						MCCMBATTR	i_iAttr		// ����ID
				)
{
	int		ic;
	int		iCmbNo = 0;

	if (  m_iIoPartsAttrMd == -1) {
		mlLog::LogOutT( MC_LOG_ERROR, Mstr( "�����l���̓��[�h�G���[: %d\n"), m_iIoPartsAttrMd);
	} else {
		for ( ic=0; ic<MC_SZ_CMBATTR; ic++)
			if ( i_iAttr == s_Combo_Attr[m_iIoPartsAttrMd][ic])
				break;
		if ( ic < MC_SZ_CMBATTR)
			iCmbNo = ic + 1;
	}
	return iCmbNo;
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̃^�C�g����ݒ肷��
void mmIoPartsAttr::SetComboAttrText(
						int		i_iAttr,		// �R���{�{�b�N�X�ԍ�
						MCHAR*	i_sTitle		// �^�C�g��
				)
{
	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( i_sTitle);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������

void mmIoPartsAttr::SetComboAttrRCbn(
						int		i_iAttr,		// �R���{�{�b�N�X�ԍ�
						MREAL	i_rValue		// �\����������l
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7.1f"), i_rValue);

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( strValue);
}

//////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������

void mmIoPartsAttr::SetComboAttrR(
						MCCMBATTR	i_iAttr,	// ����ID
						MREAL		i_rValue	// �\����������l
				)
{
	int iCmbNo;
	iCmbNo = GetComboAttrNo( i_iAttr);
	if ( iCmbNo != 0)
		SetComboAttrRCbn( iCmbNo, i_rValue);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���|�{�b�N�X�Ɏ����l�̍���(�ꗗ)��ݒ肷��

void mmIoPartsAttr::InitComboAttrR(
						int		i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int		nComboAttr,		// �I�𑮐��l�̐�
						MREAL	*rComboAttr,	// �I�𑮐��l
						MREAL	rInitValue		// �����\�����鑮���l
				)
{
	int		ist;
	int		ic1;
	CString	sKomoku;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);

	pCmbBox->ResetContent();

	// �I�𑮐��l�ݒ�
	for ( ic1=0; ic1<nComboAttr; ic1++) {
//		if ( MgEqual( rComboAttr[ic1], 9999.0))
//			sKomoku = "����";
		if ( MGeo::Equal( rComboAttr[ic1], MREAL( MC_INT_JIDO)))
			sKomoku = MC_STR_JIDO;
		else
			sKomoku.Format(Mstr( "  %6.1f"), rComboAttr[ic1]);
		ist = pCmbBox->InsertString( -1, sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	} else {
		SetComboAttrRCbn( i_iAttr, rInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
//
MREAL mmIoPartsAttr::GetComboAttrRCbn(				// �����l�@�܂��́@0(���ݒ�)
						int		i_iAttr			// �R���{�{�b�N�X�ԍ�
				)
{
	CString strValue;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->GetWindowText( strValue);

	return MsGetMREAL( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����

int mmIoPartsAttr::GetComboAttrR(					// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,	// ����ID
						MREAL*		o_rValue	// �����l
				)
{
	int		ist;
	int		iCmbNo;

	iCmbNo = GetComboAttrNo( i_iAttr);

	if ( iCmbNo != 0) {
		*o_rValue = GetComboAttrRCbn( iCmbNo);
		ist = 1;
	} else {
		*o_rValue = 0.;
		ist = 0;
	}
	return ist;
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������

void mmIoPartsAttr::SetComboAttrICbn(
						int		i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int		iValue 			// �\�����鐮���l
				)
{
	CString	strValue;
	strValue.Format( Mstr( "%7d"), iValue);

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->SetWindowText( strValue);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������

void mmIoPartsAttr::SetComboAttrI(
						MCCMBATTR	i_iAttr,	// ����ID
						int			iValue 		// �\�����鐮���l
				)
{
	int iCmbNo;
	iCmbNo = GetComboAttrNo( i_iAttr);
	if ( iCmbNo != 0)
		SetComboAttrICbn( iCmbNo, iValue);
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�w��R���|�{�b�N�X�ɐ����l�̍���(�ꗗ)��ݒ肷��

void mmIoPartsAttr::InitComboAttrI(
						int		i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int		nComboAttr,		// �I�𑮐��l�̐�
						int		*iCmbAttr,		// �I�𑮐��l
						int		iInitValue		// �����\�����鑮���l
				)
{
	int		ist;
	int		ic1;
	CString	sKomoku;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);

	pCmbBox->ResetContent();

	for ( ic1=0; ic1<nComboAttr; ic1++) {
		if ( iCmbAttr[ic1] == MC_INT_JIDO)
			sKomoku = MC_STR_JIDO;								// ����
		if ( iCmbAttr[ic1] == MC_INT_AREA)
			sKomoku = MC_STR_AREA;								// �̈�
		else
			sKomoku.Format(Mstr( "  %6d"), iCmbAttr[ic1]);
		ist = pCmbBox->InsertString( -1, sKomoku);
	}

	if ( nComboAttr == 0) {
		pCmbBox->InsertString( -1, Mstr( "none"));
	} else {
		SetComboAttrICbn( i_iAttr, iInitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����
//
int mmIoPartsAttr::GetComboAttrICbn(				// �����l�@�܂��́@0(���ݒ�)
						int		i_iAttr			// �R���{�{�b�N�X�ԍ�
					)
{
	CString strValue;
	int		iNum;

	CComboBox *pCmbBox = GetCmbBzaiAttr( i_iAttr);
	pCmbBox->GetWindowText( strValue);

	if ( Mstrcmp( strValue, MC_STR_JIDO) == 0)					// ����
		iNum = MC_INT_JIDO;										// 9999
	else if ( Mstrcmp( strValue, MC_STR_AREA) == 0)				// �̈�
		iNum = MC_INT_AREA;										// 9998
	else
		iNum =  MsGetMINT( strValue);
		
	return iNum;
}

///////////////////////////////////////////////////////////////////////////////
//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����

int	mmIoPartsAttr::GetComboAttrI(					// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,	// ����ID
						int*		o_iValue 	// �\�����鐮���l
					)
{
	int		ist;
	int		iCmbNo;

	ist = 0;
	iCmbNo = GetComboAttrNo( i_iAttr);

	if ( iCmbNo != 0) {
		*o_iValue = GetComboAttrICbn( iCmbNo);
		ist = 1;
	} else {
		*o_iValue = 0;
		ist = 0;
	}
	return ist;
}

//S//////////////////////////////////////////////////////////////////////////////
////	�����l���͗p�`�F�b�N�{�b�N�X�ԍ����擾����
//
//int mmIoPartsAttr::GetCheckAttrNo(
//						MCCHKATTR	i_iAttr		// ����ID
//				)
//{
//	int	 ic;
//	int	 iChkNo = 0;
//
//	for ( ic=0; ic<MC_SZ_CHKATTR; ic++) {
//		if ( i_iAttr == z_Check_Attr[ic])
//			break;
//	}
//	if ( ic < MC_SZ_CHKATTR)
//		iChkNo = ic + 1;
//	return iChkNo;
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	�����l���͗p�`�F�b�N�{�b�N�X�̃^�C�g����ݒ肷��
//void mmIoPartsAttr::SetCheckAttrText(
//						int		i_iAttr,		// �`�F�b�N�{�b�N�X�ԍ�
//						MCHAR*	i_sTitle		// �^�C�g���@�܂��́@NULL:�`�F�b�N�{�b�N�X��\�����Ȃ�
//				)
//{
//	CComboBox *pCmbBox = MnpComboAttr( i_iAttr);
//
//	if ( i_sTitle) {
//		pCmbBox->SetToolTipText( i_sTitle);
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
//
//void mmIoPartsAttr::SetCheckAttrCkb(
//						int		i_iChkNo,		// �`�F�b�N�{�b�N�X�ԍ�
//						int		i_iCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
//				)
//{
////U	CButton* pCheckAttr;
////U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
////U	pCheckAttr->SetCheck( i_iCheckAttr);
//	CMFCRibbonCheckBox* pCheckBox;
//	pCheckBox = DYNAMIC_DOWNCAST( CMFCRibbonCheckBox, System::GetpMainFrame()->m_wndRibbonBar.FindByID(z_IdcCheckAttr[i_iChkNo - 1]));
////	pCheckBox->set
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
//
//void mmIoPartsAttr::SetCheckAttr(
//						MCCHKATTR	i_iAttr,	// ����ID
//						int			i_iCheckAttr// �`�F�b�N�}�[�N�@0:OFF, 1:ON
//				)
//{
//	int	 iChkNo = GetCheckAttrNo( i_iAttr);
//	if ( iChkNo != 0)
//		SetCheckAttrCkb( iChkNo, i_iCheckAttr);
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
////
//int mmIoPartsAttr::GetCheckAttrCkb(				// �`�F�b�N�}�[�N�@0:OFF, 1:ON
//						int		i_iChkNo		// �`�F�b�N�{�b�N�X�ԍ�
//				)
//{
////U	CButton* pCheckAttr;
////U	pCheckAttr = (CButton*)(System::GetpMainFrame()->m_wndDlgBar5.GetDlgItem(z_IdcCheckAttr[i_iChkNo - 1]));
////U	return pCheckAttr->GetCheck();
//	return 0;
//}
//
/////////////////////////////////////////////////////////////////////////////////
////	�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
////
//
//int mmIoPartsAttr::GetCheckAttr(					// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
//						MCCHKATTR	i_iAttr,	// ����ID
//						int*		o_iCheckAttr// �`�F�b�N�}�[�N�@0:OFF, 1:ON
//				)
//{
//	int		ist;
//	int		iChkNo;
//
//	iChkNo = GetCheckAttrNo( i_iAttr);
//
//	if ( iChkNo != 0) {
//		*o_iCheckAttr = GetCheckAttrCkb( iChkNo);
//		ist = 1;
//	} else {
//		*o_iCheckAttr = 0;
//		ist = 0;
//	}
//	return ist;
//}

//S	for ( ic1=1; ic1<=MC_SZ_CHKATTR; ic1++) {
//		switch (z_Check_Attr[ic1-1]) {
//			case MC_CHK_NULL:
//				// �`�F�b�N�{�b�N�X�����������ɂ���
//				SetCheckAttrText( ic1, NULL);		
//				SetCheckAttrCkb( ic1, 0);		
//				break;
//			case MC_CHK_KATI:
//				// �����������͗p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( ic1, Mstr( "����"));
//				SetCheckAttrCkb( ic1, 0);
//				break;
//			case MC_CHK_MULT:
//				// �������͗p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( ic1, Mstr( "����"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//			case MC_CHK_INTC:
//				// �������ޒ����p�`�F�b�N�{�b�N�X��ݒ肷��
//				SetCheckAttrText( ic1, Mstr( "�������ޒ���"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//			case MC_CHK_NKTP:
//				// ����^�C�v(0:���z���܂�A1:����)
//				SetCheckAttrText( ic1, Mstr( "����^�C�v����"));
//				SetCheckAttrCkb( ic1, 1);
//				break;
//		}
//	}
//}

} // namespace MC