#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

enum	ComboTp {
	MSET_INPUT_KUBUN_CD = 1,
	MSET_INPUT_MARUME_CD,
	MSET_COMBO_ATTRR,
	MGET_COMBO_ATTRA,
	MSET_COMBO_PARTS,
	MSET_COMBO_PANELNO,
	MINIT_COMBO_ATTR
};

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mnInpAttr�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mnInpAttr�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mnInpAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	int		m_iInpKai;							// �K				(1�K,2�K,3�K)
	int		m_iCdInpKbn;						// ���͓_�敪�R�[�h	(���w��,1�_,����2�_,����2�_,���,���R)
	int		m_iCdMarume;						// �ۂ߃R�[�h		(1,2,3,4,6,8)
	int		m_iCdIzon;							// �ˑ��R�[�h		(�C��,�ǐc�t��,�����\�����t��)
	int		m_iCdBziNm;							// ���ޖ�Id
	int		m_iCdMbr;							// �����o�[Id
	MREAL	m_rLengthH1;						// �����␳1		(mm)
	MREAL	m_rLengthH2;						// �����␳2		(mm)
	MREAL	m_rSinzure;							// �c����			(mm)
	MREAL	m_rToritukeH;						// ��t����			(mm)
	MREAL	m_rSpan;							// �Ԋu				(mm)
	int		m_nHondu;							// �{��
	int		m_iPanelNo;							// �p�l��No			(0:�S�A1�`n)
	int		m_iInpMd;							// �n�����[�h		(�폜�A�C���A�ړ��A���ʁA�����\��)

	int		m_iSInpGp;							// �݌v���͍\��		(�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�)

	int		m_iKInpGp;							// �\�����͍\��		(�����A�����A�V��A�ϗ͕ǁA�ǁA���A�y��A��b)
	int		m_iKInpBr;							// �\�����͎��		(���ށA�����A�p�l���A���̑�)
	int		m_iKInpSel;							// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p

	bool	m_bKDspBuzai;						// ���ޕ\���t���O
	bool	m_bKDspKanagu;						// �����\���t���O
	bool	m_bKDspGohan;						// ���\���t���O
	bool	m_bKAttr1;							// ����1�t���O
	bool	m_bKAttr2;							// ����2�t���O
	bool	m_bKAttr3;							// ����3�t���O
	bool	m_bKAttr4;							// ����4�t���O

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
	mnInpAttr();

	//////////////////////////////////////////////////////////////////////////////
	// �������͗p�R���{�{�b�N�X���擾����
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						MINT	i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ԍ����擾����
protected:
	MINT GetComboAttrNo(
						MCCMBATTR	i_iAttr			// ����ID
				);

public:
	////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p
	int		m_iComboTp;								// �R���{���
	int		m_iCdArg1;								// �ݒ�R�[�h1

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̃^�C�g����ݒ肷��
protected:
	void SetComboAttrText(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MCHAR*	i_sTitle			// �^�C�g��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrRCbn(
						MINT	i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MREAL	i_rValue			// �\����������l
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

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) �����l�@�܂��́@0(���ݒ�)
						MINT	i_iAttr				// �R���{�{�b�N�X�ԍ�
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
						MINT	*iCmbAttr,			// (I  ) �I�𑮐��l
						MINT	iInitValue			// (I  ) �����\�����鑮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����
	//
protected:
	MINT GetComboAttrICbn(							// �����l�@�܂��́@0(���ݒ�)
						MINT	i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�ԍ����擾����
protected:
	MINT GetCheckAttrNo(
						MCCHKATTR	i_iAttr			// ����ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃^�C�g����ݒ肷��
protected:
	void SetCheckAttrText(
						MINT	i_iAttr,			// �`�F�b�N�{�b�N�X�ԍ�
						MCHAR*	i_sTitle			// �^�C�g���@�܂��́@NULL:�`�F�b�N�{�b�N�X��\�����Ȃ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
protected:
	void SetCheckAttrCkb(
						MINT	i_iChkNo,			// �`�F�b�N�{�b�N�X�ԍ�
						MINT	i_iCheckAttr		// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
	//
protected:
	MINT GetCheckAttrCkb(							// �`�F�b�N�}�[�N�@0:OFF, 1:ON
						MINT	i_iChkNo			// �`�F�b�N�{�b�N�X�ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�
protected:
	MINT MnCalcInpAtMode();

	/////////////////////////////////////////////////////////////////////////////
	//	���ޑ������͗p�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��
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
	//	���ޑ������͗p�R���{�{�b�N�X�̐ݒ�
protected:
	void SetComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̑����l���̓��[�h���擾����
	//	(���ޑ������͗p���{���o�[�̍��ڐݒ蒆�̑����l���̓��[�h)
	//
public:
	MINT GetAtMd()
	{
		return m_iInpAttrMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�����l���̓��[�h�ŕ��ޑ������͗p���{���o�[�̍��ڂ�ݒ肷��
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

public:
	///////////////////////////////////////////////////////////////////////////////
	//	���{���o�[�̐ݒ�Ǝ�荞��
	void RibbonIO(
						int		i_iComboTp,			// Combo���	1:���͓_�敪�R�[�h
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
					);

protected:
	///////////////////////////////////////////////////////////////////////////////
	//	���{���o�[�̃R���{�b�N�X�̐ݒ�@�{��
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l����荞��

protected:
	void GetComboAttrA( void);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrR(
							MCCMBATTR	i_iAttr,		// ����ID
							MREAL		i_rValue		// �\����������l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
public:
	MINT GetComboAttrR(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCMBATTR	i_iAttr,		// ����ID
							MREAL*		o_prValue		// �����l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrI(
							MCCMBATTR	i_iAttr,		// ����ID
							MINT		i_iValue 		// �\�����鐮���l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐������擾����
public:
	MINT GetComboAttrI(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCMBATTR	i_iAttr,		// ����ID
							MINT*		o_piValue		// �����l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
protected:
	void SetCheckAttr(
							MCCHKATTR	i_iAttr,		// ����ID
							MINT		i_iCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
	//
public:
	MINT GetCheckAttr(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCHKATTR	i_iAttr,		// ����ID
							MINT*		o_piCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������
protected:
	void SetComboPanelNo(
							MINT		i_iPanelNo		// �p�l���ԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
	//							��-1: ���I��
	//							�� 0: �S
	//							�� 1: �p�l���ԍ�
public:
	MINT GetComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	���i�I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsTp();

	///////////////////////////////////////////////////////////////////////////////
	//	���i�I�����ڔԍ���ݒ肷��
protected:
	void SetComboKmIdPartsTp(
							MINT		i_iKmIdPartsTp	// ���i�I�����ڔԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���i�I��p�R���|�{�b�N�X�ɕ��ނ�ݒ肷��
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
protected:
	MINT SetComboCdPartsTp(
							MCHAR* 		i_sNmParts1		// �i����p�j���ޖ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���i�I��p�R���|�{�b�N�X��蕔�iID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	MINT GetIdPartsTp(
							MCHAR* 		i_sNmParts1		// �i����p�j���ޖ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���i�I��p�R���|�{�b�N�X�̃J�����g�̕��iID���擾����
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	MINT GetCurIdPartsTp();


	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I�����ڔԍ���ݒ肷��
protected:
	void SetComboKmIdMbr(
							MINT		i_iKmIdMbr		// ���@�^���I�����ڔԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I�����ڔԍ����擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	MINT GetComboKmIdMbr(
							MCHAR*		i_sCdMbr
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�ɐ��@�^����ݒ肷��
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
protected:
	MINT SetComboCdMbr(
							MCHAR* 		i_sCdMbr
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
public:
	MINT GetComboCdMbr(
							MCHAR* 		i_sCdMbr
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X��萡�@�^��ID���擾����
	//	�i�J�����g�̐��@�^��ID���擾����j
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	MINT GetComboIdMbr();

public:
	////////////////////////////////////////////////////////////////////////////
	// ���ޓ��͗p�A���{���o�[�̎��̍��ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
	MPKOSEI		m_iRBKosei;							// �\��	�\��
	MPBUNRUI	m_iRBBunrui;						// �\��	����
	CString		m_sRBBuhin;							// ���i
	CString		m_sRBMbr;							// ���i�����o�[

	////////////////////////////////////////////////////////////////////////////
	// ���ޓ��͗p�A���{���o�[�̎��̍��ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
public:
	int	SetRibbonBar( 									// �X�e�C�^�X 0:���� -1:�G���[
						MPKOSEI		i_irbKumi,			// �\��	�g
						MPBUNRUI	i_irbBunrui,		// �\��	����
						MCHAR*		i_crbPartsTp,		// ���i���
						MCHAR*		i_crbMbr			// ���i�����o�[()
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X�ɔz�u�R�[�h��\����
	//	�J�����g�̔z�u�R�[�h��ݒ肷��
protected:
	void SetComboCdPlc(
							MINT		i_iCdPlc		// �z�u�R�[�h
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X���z�u�R�[�h���擾����
	//	�i�J�����g�̔z�u�R�[�h���擾����j
	//							��0 : �C��
	//							��1 : �ǐc�t��
	//							��2 : �����\�����t��
public:
	MINT GetComboCdPlc();

	/////////////////////////////////////////////////////////////////////////////
	//	�n�����[�h		�폜�A�C���A�ړ��A���ʁA�����\��
public:
	void SetMode(
							MINT 		i_iInpMd		// �n�����[�h
					)
	{
		m_iInpMd = i_iInpMd;
	}
public:
	MINT GetMode()
	{
		return m_iInpMd;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�R���{�{�b�N�X�ɓ��͓_�敪��\����
	//	�J�����g�̓��͓_�敪��ݒ肷��
protected:
	void SetComboCdInpKb(
							MINT		i_iCdCdInpKb	// ���͓_�敪
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���͓_�敪�I��p�R���{�{�b�N�X�����͓_�敪���擾����
	//	�i�J�����g�̓��͓_�敪���擾����j
	//							��1 : �P�_����
	//							��2 : �����P�_����
	//							��3 : �����Q�_����
	//							��4 : ������
	//							��5 : ���R����
public:
	MINT GetComboCdCdInpKb();

	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X�ɊۖڃR�[�h��\����
	//	�J�����g�̊ۖڃR�[�h��ݒ肷��
protected:
	void SetComboCdMarume(
							MINT		i_iCdMarume		// �ۖڃR�[�h
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X���ۖڃR�[�h���擾����
	//	�i�J�����g�̊ۖڃR�[�h���擾����j
	//							��0 : �ۂ߂Ȃ�
	//							��1 : �P�^�P�O���b�h�ۂ�
	//							��2 : �P�^�Q�O���b�h�ۂ�
	//							��3 : �P�^�R�O���b�h�ۂ�
	//							��4 : �P�^�S�O���b�h�ۂ�
	//							��5 : �P�^�U�O���b�h�ۂ�
	//							��5 : �P�^�W�O���b�h�ۂ�
public:
	MINT GetComboCdMarume();

	/////////////////////////////////////////////////////////////////////////////
	//	�K				�P�K�A�Q�K�A�R�K
public:
	void SetKai(
							MINT 		i_iInpKai
					)
	{
		m_iInpKai = i_iInpKai;
	}
public:
	MINT GetKai()
	{
		return m_iInpKai;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �݌v���͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�
public:
	void SetSCdGp(
							MINT		i_iSInpGp
					)
	{
		m_iSInpGp = i_iSInpGp;
	}
public:
	MINT GetSCdGp()
	{
		return m_iSInpGp;
	}

//S	/////////////////////////////////////////////////////////////////////////////
//	// �݌v���͎��
//
//	void SetSCdBr(
//							MINT		i_iSCdBr
//					);
//	MINT GetSCdBr();
//
//	/////////////////////////////////////////////////////////////////////////////
//	// �݌v���͑I��
//
//	void SetSSel(
//							MINT		i_iSel
//					);
//	MINT GetSSel();

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͍\��		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b
public:
	void SetKCdGp(
							int			i_iKInpGp
					)
	{
		m_iKInpGp = i_iKInpGp;
	}
public:
	MINT GetKCdGp()
	{
		return m_iKInpGp;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͎��		���ށA�����A�p�l���A���̑�
public:
	void SetKCdBr(
							int			i_iKInpBr
					)
	{
		m_iKInpBr = i_iKInpBr;
	}
public:
	MINT GetKCdBr()
	{
		return m_iKInpBr;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p
public:
	void SetKSel(
							MINT		i_iSel
					)
	{
		m_iKInpSel = i_iSel;
	}
public:
	MINT GetKSel()
	{
		return m_iKInpSel;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	���ށA�����A���̃`�F�b�N�{�b�N�X�̕��ޕ\����ݒ�
public:
	void SetKCdBrB(
							bool		i_bDspBuzai,
							bool		i_bDspKanagu,
							bool		i_bDspGohan
					)
	{
		m_bKDspBuzai  = i_bDspBuzai;
		m_bKDspKanagu = i_bDspKanagu;
		m_bKDspGohan  = i_bDspGohan;
	}

};

extern	mnInpAttr z_mn;

}// namespace MC