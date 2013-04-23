#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#include "MmDialogKAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mmInpAttr�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mmInpAttr�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mmInpAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	int		m_iCdPartsNm;						// ���i��Id
	int		m_iCdMbr;							// �����o�[Id
	MREAL	m_rLengthH1;						// �����␳1		(mm)
	MREAL	m_rLengthH2;						// �����␳2		(mm)
	MREAL	m_rSinzure;							// �c����			(mm)
	MREAL	m_rToritukeH;						// ��t����			(mm)
	MREAL	m_rSpan;							// �Ԋu				(mm)
	int		m_nHonsu;							// �{��
//S	int		m_iPanelNo;							// �p�l��No			(0:�S�A1�`n)

	int		m_iKobai;							// ���z
	MREAL	m_rNokiDe;							// ���̏o
	MREAL	m_rKerabaDe;						// ����΂̏o

	MPKOSEI  m_iKInpGp;							// �\�����͍\��		(�����A�����A�V��A�ϗ͕ǁA�ǁA���A�y��A��b)
	MPBUNRUI m_iKInpBr;							// �\�����͎��		(���ށA�����A�p�l���A���̑�)
	MPSELECT m_iKInpSel;						// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p

	int		m_iInpAttrMd;						// �����l���̓��[�h
												//		MP_AT_AUTO(-1)		:�����ݒ�
												//		MP_AT_NONE(0)		:�����l���͂Ȃ�
												//		MP_AT_HRZ_PARTS(1)	:�������ޓ���
												//		MP_AT_VRT_PARTS(2)	:�������ޓ���
												//		MP_AT_YTPANEL(3)	:���V��p�l������
												//		MP_AT_YANEPANEL(4)	:�����p�l������
												//		MP_AT_ADJLNG(5)		:���ޒ�����������
												//		MP_AT_YANE(6)		:��������
												//		MP_AT_TATEGU(7)		:�������


	////////////////////////////////////////////////////////////////////////////
	//	�R���X�g���N�^
public:
	mmInpAttr(){};

//public:
//	////////////////////////////////////////////////////////////////////////////
//	//	�����l���͗p
//	ComboTp	m_iComboTp;								// �R���{���
//	int		m_iCdArg1;								// �ݒ�R�[�h1 ����
//	MREAL	m_rCdArg2;								// �ݒ�R�[�h2 ����
//	int		m_iSts;									// �X�e�C�^�X

public:
	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A�_�C�A���O�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
	MPKOSEI		m_iRBKosei;							// �\��	�\��
	MPBUNRUI	m_iRBBunrui;						// �\��	����
	MCHAR*		m_sRBBuhin;							// ���i
	MCHAR*		m_sRBMbr;							// ���i�����o�[

//	///////////////////////////////////////////////////////////////////////////////
//	//	�_�C�A���O�̐ݒ�Ǝ�荞��
//public:
//	int RibbonIO(
//						ComboTp	i_iComboTp,			// Combo���	1:���͓_�敪�R�[�h
//						int		i_iCdArg1 = NULL,	//				
//						MREAL	i_rCdArg2 = NULL	//				
//				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i�����ڔԍ��őI������
protected:
	void SelectComboPartsNmByKmId(
						MINT		i_iKmIdPartsNm	// ���i�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
protected:
	MINT SelectComboPartsNmByPartsNm(
						MCHAR* 		i_sNmParts1		// ���i��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i�����畔�i���R���|�{�b�N�X�̕��i�����ڔԍ����擾����
	//	�R���{�{�b�N�X�̍��ڂ��w�肳�ꂽ���ނ̕��iID���������A
	//	�Y���̕��i�����ڔԍ���Ԃ�
	//	�Ԓl
	//							�� 0: ���iID
	//							��-1: �Y���Ȃ�
public:
	MINT GetComboPartsNmKmIdFromPartsNm(
						MCHAR*		i_sNmParts1		// ���i��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X��蕔�iID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	MINT GetComboPartsNmId(
						MCHAR* 		i_sNmParts1		// ���i��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�̃J�����g�̕��iID���擾����
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	MINT GetCurPartsNmId();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI������
protected:
	void SelectComboPartsMbrByKmId(
						MINT		i_iKmIdMbr		// ���@�^�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
protected:
	MINT SelectComboMbrCdByMbrCd(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�`�����琡�@�^���R���{�{�b�N�X�̐��@�^�����ڔԍ����擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	MINT GetComboMbrKmId(
						MCHAR*		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X��萡�@�^��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
public:
	MINT GetComboMbrCd(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X��萡�@�^��ID���擾����
	//	�i�J�����g�̐��@�^��ID���擾����j
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	MINT GetComboMbrCdId();

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ԍ����擾����
protected:
	MINT GetComboAttrNo(
						MCCMBATTR	i_iAttr			// ����ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̃^�C�g����ݒ肷��
protected:
	void SetComboAttrText(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MCHAR*	i_sTitle			// �^�C�g��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���|�{�b�N�X�Ɏ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrR(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MINT	i_nComboAttr,		// �I�𑮐��l�̐�
						MREAL*	i_rComboAttr,		// �I�𑮐��l
						MREAL	i_rInitValue		// �����\�����鑮���l
				);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrR(
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL		i_rValue		// �\����������l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
protected:
	MINT GetComboAttrR(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL*		o_prValue		// �����l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrRCbn(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MREAL	i_rValue			// �\����������l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) �����l�@�܂��́@0(���ݒ�)
						MINT	i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	/////////////////////////////////////////////////////////////////////////////
	//	�����␳1				
public:
	void SetLengthH1(
						MREAL 		i_rLengthH1		// �����␳1	
				)
	{
		m_rLengthH1 = i_rLengthH1;
	}
public:
	MREAL GetLengthH1()
	{
		return m_rLengthH1;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�����␳2				
public:
	void SetLengthH2(
						MREAL 		i_rLengthH2		// �����␳2	
				)
	{
		m_rLengthH2 = i_rLengthH2;
	}
public:
	MREAL GetLengthH2()
	{
		return m_rLengthH2;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�c����				
public:
	void SetSinzure(
						MREAL 		i_rSinzure		// �c����	
				)
	{
		m_rLengthH1 = i_rSinzure;
	}
public:
	MREAL GetSinzure()
	{
		return m_rSinzure;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	��t����				
public:
	void SetToritukeH(
						MREAL 		i_rToritukeH	// ��t����	
				)
	{
		m_rToritukeH = i_rToritukeH;
	}
public:
	MREAL GetToritukeH()
	{
		return m_rToritukeH;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�Ԋu				
public:
	void SetSpan(
						MREAL 		i_rSpan			// �Ԋu	
				)
	{
		m_rSpan = i_rSpan;
	}
public:
	MREAL GetSpan()
	{
		return m_rSpan;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrI(
						MCCMBATTR	i_iAttr,		// ����ID
						MINT		i_iValue 		// �\�����鐮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐������擾����
protected:
	MINT GetComboAttrI(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						MINT*		o_piValue		// �����l
				);


	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrICbn(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MINT	i_iValue 			// �\�����鐮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�w��R���|�{�b�N�X�ɐ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrI(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MINT	i_nComboAttr,		// �I�𑮐��l�̐�
						MINT*	i_iCmbAttr,			// �I�𑮐��l
						MINT	i_iInitValue		// �����\�����鑮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����
	//
protected:
	MINT GetComboAttrICbn(							// �����l�@�܂��́@0(���ݒ�)
						MINT	i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	/////////////////////////////////////////////////////////////////////////////
	//	�{��
public:
	void SetHonsu(
						MINT 		i_nHonsu		// �{��	
				)
	{
		m_nHonsu = i_nHonsu;
	}
public:
	MINT GetHonsu()
	{
		return m_nHonsu;
	}

//U	/////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��
//protected:
//	void InitComboPanelNo();
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������
//protected:
//	void SetComboPanelNo(
//						MINT		i_iPanelNo		// �p�l���ԍ�
//				);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
//	//							��-1: ���I��
//	//							�� 0: �S
//	//							�� 1: �p�l���ԍ�
//public:
//	MINT GetComboPanelNo();
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	�p�l��No
//public:
//	void SetPanelNo(
//						MINT 		i_iPanelNo	// �{��	
//				)
//	{
//		m_iPanelNo = i_iPanelNo;
//	}
//public:
//	MINT GetPanelNo()
//	{
//		return m_iPanelNo;
//	}

	/////////////////////////////////////////////////////////////////////////////
	//	���z
public:
	void SetKobai(
						MINT 		i_iKobai	// ���z	
				)
	{
		m_iKobai = i_iKobai;
	}
public:
	MINT GetKobai()
	{
		return m_iKobai;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	���̏o				
public:
	void SetNokiDe(
						MREAL 		i_rNokiDe	// ���̏o	
				)
	{
		m_rNokiDe = i_rNokiDe;
	}
public:
	MREAL GetNokiDe()
	{
		return m_rNokiDe;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	����΂̏o				
public:
	void SetKerabaDe(
						MREAL 		i_rKerabaDe	// ����΂̏o	
				)
	{
		m_rKerabaDe = i_rKerabaDe;
	}
public:
	MREAL GetKerabaDe()
	{
		return m_rKerabaDe;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͍\��		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b
public:
	void SetKCdGp(
						MPKOSEI		i_iKInpGp		// �\���@�\��(�g)
				)
	{
		m_iKInpGp = i_iKInpGp;
	}
public:
	MPKOSEI GetKCdGp()
	{
		return m_iKInpGp;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͎��		���ށA�����A�p�l���A���̑�
public:
	void SetKCdBr(
						MPBUNRUI		i_iKInpBr		// �\���@���
				)
	{
		m_iKInpBr = i_iKInpBr;
	}
public:
	MPBUNRUI GetKCdBr()
	{
		return m_iKInpBr;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A�_�C�A���O�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
public:
	void SetRibbonBarEnt( 							// �X�e�C�^�X 0:���� -1:�G���[
					MPKOSEI		i_irbKumi,			// �\��	�g
					MPBUNRUI	i_irbBunrui,		// �\��	����
					MCHAR*		i_crbPartsSpec,		// ���i���
					MCHAR*		i_crbMbr = NULL		// ���i�����o�[()
				)
	{
		m_iRBKosei	= i_irbKumi;
		m_iRBBunrui = i_irbBunrui;
		m_sRBBuhin	= i_crbPartsSpec;
		m_sRBMbr	= i_crbMbr;

		z_DlgKAttr.MmDialogKAttr();
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�
protected:
	MINT MnCalcInpAtMode();

	/////////////////////////////////////////////////////////////////////////////
	//	���i�������͗p�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void MnsInitComboAttr(
						MCCMBATTR	i_icombo1,		// �������͗p�R���{�{�b�N�X1�̑���ID
						MCCMBATTR	i_icombo2,		// �������͗p�R���{�{�b�N�X2�̑���ID
						MCCMBATTR	i_icombo3,		// �������͗p�R���{�{�b�N�X3�̑���ID
						MCCMBATTR	i_icombo4,		// �������͗p�R���{�{�b�N�X4�̑���ID
						MCCMBATTR	i_icombo5,		// �������͗p�R���{�{�b�N�X5�̑���ID
						MCCMBATTR	i_icombo6,		// �������͗p�R���{�{�b�N�X6�̑���ID
						MCCHKATTR	i_icheck1,		// �������͗p�`�F�b�N�{�b�N�X1�̑���ID
						MCCHKATTR	i_icheck2,		// �������͗p�`�F�b�N�{�b�N�X2�̑���ID
						MCCHKATTR	i_icheck3,		// �������͗p�`�F�b�N�{�b�N�X3�̑���ID
						MCCHKATTR	i_icheck4		// �������͗p�`�F�b�N�{�b�N�X4�̑���ID
				);

	////////////////////////////////////////////////////////////////////////////
	//	���i�������͗p�R���{�{�b�N�X�̐ݒ�
protected:
public:									// ���ݒ�
	void SetComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̑����l���̓��[�h���擾����
	//	(���i�������͗p�_�C�A���O�̍��ڐݒ蒆�̑����l���̓��[�h)
	//
public:
	MINT GetAtMd()
	{
		return m_iInpAttrMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�����l���̓��[�h�ŕ��i�������͗p�_�C�A���O�̍��ڂ�ݒ肷��
	//	 (�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��)
	//	
protected:
	void InitComboAttr(
						MINT	i_iInpAttrMd = MP_AT_NONE	// �����l���̓��[�h
													//  MP_AT_AUTO(-1)		:�����ݒ�
													//	MP_AT_NONE(0)		:�����l���͂Ȃ�
													//	MP_AT_HRZ_PARTS(1)	:�������ޓ���
													//	MP_AT_VRT_PARTS(2)	:�������ޓ���
													//	MP_AT_YTPANEL(3)	:���V��p�l������
													//	MP_AT_YANEPANEL(4)	:�����p�l������
													//	MP_AT_ADJLNG(5)		:���ޒ�����������
													//	MP_AT_YANE(6)		:��������
													//	MP_AT_TATEGU(7)		:�������
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�_�C�A���O�̃R���{�b�N�X�̐ݒ�@�{��
protected:
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l����荞��
protected:
	void GetComboAttrA( void);

};

extern	mmInpAttr z_mmIA;

}// namespace MC