#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

//#include "MmDialogKAttr.h"
#include "MmIoPartsAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

enum	ComboTp {
	MSET_RIBBON_BAR = 1,			// ���{���o�[�̕��i�I��p����( �g�A���ށA���i�^�C�v�A���@�^��)��ݒ肷��
	MSET_INPUT_KUBUN_CD,			// �J�����g�̓��͓_�敪��ݒ肵�A���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
	MSET_INPUT_MARUME_CD,			// �J�����g�̊ۂ߃R�[�h��ݒ肵�A�R���{�{�b�N�X�Ɋۂ߃R�[�h��\������
	MSET_COMBO_ATTRR,				// �����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
	MGET_PARTS_ATTRA,				// ���i�d�l,���@�`���Ƒ����l���͗p�R���{�{�b�N�X�̒l�𕔕i�z�u���̓f�[�^�Ɏ�荞��
	MSET_COMBO_PARTS,				// ���ޑ������͗p�R���{�{�b�N�X�̐ݒ�
	MSET_COMBO_PANELNO,				// �J�����g�̃p�l���ԍ��I�����ڔԍ���ݒ肵�@�R���{�{�b�N�X�Ƀp�l���ԍ���\������

	MINIT_COMBO_ATTR				// �����l���̓��[�h�ɉ��������ޑ������͗p���{���o�[�̍��ڂ�ݒ肷��
};

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::mnIoPartsAttr�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mnIoPartsAttr�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mnIoPartsAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	int		m_iCCategory;						// �J�����g�J�e�S���@1:�ӏ�, 2:�\��, 3:����

	int		m_iInpKai;							// �K				(1�K,2�K,3�K)
//
	MPMODE	m_iInpMd;							// �n�����[�h		(�폜�A�C���A�ړ��A���ʁA�����\��)
	MPKOSEI	m_iSInpGp;							// �݌v���͍\��		(�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�)
	MPKOSEI  m_iKInpGp;							// �\�����͍\��		(�����A�����A�V��A�ϗ͕ǁA�ǁA���A�y��A��b)
	MPBUNRUI m_iKInpBr;							// �\�����͎��		(���ށA�����A�p�l���A���̑�)
	MPSELECT m_iKInpSel;						// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p
//
	bool	m_bKDspBuzai;						// ���ޕ\���t���O
	bool	m_bKDspKanagu;						// �����\���t���O
	bool	m_bKDspGohan;						// ���\���t���O

	////////////////////////////////////////////////////////////////////////////
	//	�R���X�g���N�^
public:
	mnIoPartsAttr();

public:
	////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p
	ComboTp	m_iComboTp;								// �R���{���
	int		m_iCdArg1;								// �ݒ�R�[�h1 ����
	MREAL	m_rCdArg2;								// �ݒ�R�[�h2 ����
	int		m_iSts;									// �X�e�C�^�X

public:
	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
	MPKOSEI		m_iRBKosei;							// �\��	�\��
	MPBUNRUI	m_iRBBunrui;						// �\��	����
	MCHAR*		m_sRBBuhin;							// ���i
	MCHAR*		m_sRBMbr;							// ���i�����o�[

	// ���i���R���{�{�b�N�X
	int		m_nComboIdPartsSpec;					// �\�����ڐ�
	int		m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// �\�����ڑΉ����iID
	int		m_iComboKmIdPartsNm;					// ���i���J�����g�I�����ڔԍ�

	// ���@�^���I��p�R���{�{�b�N�X
	int		m_nComboPartsMbrId;						// �\�����ڐ�
	int		m_iComboPartsMbrId[MX_CMB_CDMEMBER];	// �\�����ڑΉ����@�^��ID
	int		m_iComboKmIdMbr;						// ���@�`���J�����g�I�����ڔԍ�

	///////////////////////////////////////////////////////////////////////////////
	//	���{���o�[�̐ݒ�Ǝ�荞��
public:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo���	1:���͓_�敪�R�[�h
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�J�e�S��	
	void	SetCCategory(
						int i_iCCategory			// �J�����g�J�e�S���@1:�ӏ�, 2:�\��, 3:����
				)
	{
		m_iCCategory = i_iCCategory;

	}
	int	GetCCategory()
	{
		return m_iCCategory;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�K				�P�K�A�Q�K�A�R�K
public:
	void SetInpKai(
						int	 		i_iInpKai		// �K	
				)
	{
		m_iInpKai = i_iInpKai;
	}
public:
	int GetInpKai()
	{
		return m_iInpKai;
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�R���{�{�b�N�X�ɓ��͓_�敪��\����
	//	�J�����g�̓��͓_�敪��ݒ肷��
protected:
	void SelectComboInpKbnByInpKbnCd(
						int			i_iCdCdInpKb	// ���͓_�敪
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
	int GetComboInpKbCd();

	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X�ɊۖڃR�[�h��\����
	//	�J�����g�̊ۖڃR�[�h��ݒ肷��
protected:
	void SelectComboMarumeByMarumeCd(
						int			i_iCdMarume		// �ۖڃR�[�h
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
	int GetComboMarumeCd();

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i�����ڔԍ��őI������
protected:
	void SelectComboPartsNmByKmId(
						int			i_iKmIdPartsNm	// ���i�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
protected:
	int SelectComboPartsNmByPartsNm(
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
	int GetComboPartsNmKmIdFromPartsNm(
						MCHAR*		i_sNmParts1		// ���i��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X��蕔�iID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	int GetComboPartsNmId(
						MCHAR* 		i_sNmParts1		// ���i��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�̃J�����g�̕��iID���擾����
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	int GetCurPartsNmId();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPartsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI������
protected:
	void SelectComboPartsMbrByKmId(
						int			i_iKmIdMbr		// ���@�^�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
protected:
	int SelectComboPartsMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�`�����琡�@�^���R���{�{�b�N�X�̐��@�^�����ڔԍ����擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	int GetComboPartsMbrKmId(
						MCHAR*		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X��萡�@�^��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
public:
	int GetComboPartsMbrCdId(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X��萡�@�^��ID���擾����
	//	�i�J�����g�̐��@�^��ID���擾����j
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	int GetCurPartsMbrCdId();

	//////////////////////////////////////////////////////////////////////////////
	// �������͗p�R���{�{�b�N�X���擾����
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						int		i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ԍ����擾����
protected:
	int GetComboAttrNo(
						MCCMBATTR	i_iAttr			// ����ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̃^�C�g����ݒ肷��
protected:
	void SetComboAttrText(
						int		i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MCHAR*	i_sTitle			// �^�C�g��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���|�{�b�N�X�Ɏ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrR(
						int		i_iAttr,			// �R���{�{�b�N�X�ԍ�
						int		i_nComboAttr,		// �I�𑮐��l�̐�
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
	int GetComboAttrR(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL*		o_prValue		// �����l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrRCbn(
						int		i_iAttr,			// �R���{�{�b�N�X�ԍ�
						MREAL	i_rValue			// �\����������l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) �����l�@�܂��́@0(���ݒ�)
						int		i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrI(
						MCCMBATTR	i_iAttr,		// ����ID
						int			i_iValue 		// �\�����鐮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐������擾����
protected:
	int GetComboAttrI(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						int*		o_piValue		// �����l
				);


	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrICbn(
						int		i_iAttr,			// �R���{�{�b�N�X�ԍ�
						int		i_iValue 			// �\�����鐮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�w��R���|�{�b�N�X�ɐ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrI(
						int		i_iAttr,			// �R���{�{�b�N�X�ԍ�
						int		i_nComboAttr,		// �I�𑮐��l�̐�
						int*	i_iCmbAttr,			// �I�𑮐��l
						int		i_iInitValue		// �����\�����鑮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����
	//
protected:
	int GetComboAttrICbn(							// �����l�@�܂��́@0(���ݒ�)
						int		i_iAttr				// �R���{�{�b�N�X�ԍ�
				);

	/////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������
protected:
	void SetComboPanelNo(
						int			i_iPanelNo		// �p�l���ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
	//							��-1: ���I��
	//							�� 0: �S
	//							�� 1: �p�l���ԍ�
public:
	int GetComboPanelNo();

	/////////////////////////////////////////////////////////////////////////////
	//	�n�����[�h		�폜�A�C���A�ړ��A���ʁA�����\��
public:
	void SetMode(
						MPMODE 		i_iInpMd		// �n�����[�h
				)
	{
		m_iInpMd = i_iInpMd;
	}
public:
	MPMODE GetMode()
	{
		return m_iInpMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	// �݌v���͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�
public:
	void SetSCdGp(
						MPKOSEI		i_iSInpGp		// �݌v�@�\��
				)
	{
		m_iSInpGp = i_iSInpGp;
	}
public:
	MPKOSEI GetSCdGp()
	{
		return m_iSInpGp;
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

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p
public:
	void SetKSel(
						MPSELECT	i_iSel			// �I��ԍ�
				)
	{
		m_iKInpSel = i_iSel;
	}
public:
	MPSELECT GetKSel()
	{
		return m_iKInpSel;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	���ށA�����A���̃`�F�b�N�{�b�N�X�̕\���t���O��ݒ�
public:
	void SetKCdBrB(
						bool		i_bDspBuzai,	// ���ޕ\���t���O
						bool		i_bDspKanagu,	// ����\���t���O
						bool		i_bDspGohan		// ���\���t���O
				)
	{
		m_bKDspBuzai  = i_bDspBuzai;
		m_bKDspKanagu = i_bDspKanagu;
		m_bKDspGohan  = i_bDspGohan;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
public:
	int	SetRibbonBarEnt( 									// �X�e�C�^�X 0:���� -1:�G���[
					MPKOSEI		i_irbKumi,			// �\��	�g
					MPBUNRUI	i_irbBunrui,		// �\��	����
					MCHAR*		i_crbPartsSpec,		// ���i���
					MCHAR*		i_crbMbr = NULL		// ���i�����o�[()
				)
	{
		int	ist;
		m_iRBKosei	= i_irbKumi;
		m_iRBBunrui = i_irbBunrui;
		m_sRBBuhin	= i_crbPartsSpec;
		m_sRBMbr	= i_crbMbr;

		ist = RibbonIO( MSET_RIBBON_BAR);
//U		z_mnIA.SetRibbonBarEnt( i_irbKumi, i_irbBunrui, i_crbPartsSpec, i_crbMbr);

		return ist;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
protected:
	int	SetRibbonBar( 									// �X�e�C�^�X 0:���� -1:�G���[
					MPKOSEI		i_irbKumi,			// �\��	�g
					MPBUNRUI	i_irbBunrui,		// �\��	����
					MCHAR*		i_crbPartsSpec,		// ���i���
					MCHAR*		i_crbMbr = NULL		// ���i�����o�[()
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X�ɔz�u�R�[�h��\����
	//	�J�����g�̔z�u�R�[�h��ݒ肷��
protected:
	void SelectComboPlcCdByPlcCd(
						int			i_iCdPlc		// �z�u�R�[�h
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X���z�u�R�[�h���擾����
	//	�i�J�����g�̔z�u�R�[�h���擾����j
	//							��0 : �C��
	//							��1 : �ǐc�t��
	//							��2 : �����\�����t��
public:
	int GetComboPlcCd();

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�ԍ����擾����
protected:
	int GetCheckAttrNo(
						MCCHKATTR	i_iAttr			// ����ID
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃^�C�g����ݒ肷��
protected:
	void SetCheckAttrText(
						int		i_iAttr,			// �`�F�b�N�{�b�N�X�ԍ�
						MCHAR*	i_sTitle			// �^�C�g���@�܂��́@NULL:�`�F�b�N�{�b�N�X��\�����Ȃ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
protected:
	void SetCheckAttrCkb(
						int		i_iChkNo,			// �`�F�b�N�{�b�N�X�ԍ�
						int		i_iCheckAttr		// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
	//
protected:
	int GetCheckAttrCkb(							// �`�F�b�N�}�[�N�@0:OFF, 1:ON
						int		i_iChkNo			// �`�F�b�N�{�b�N�X�ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�
protected:
	int MnCalcInpAtMode();

	////////////////////////////////////////////////////////////////////////////
	//	���i�������͗p�R���{�{�b�N�X�̐ݒ�
protected:
	void InitComboParts();

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̑����l���̓��[�h���擾����
	//	(���i�������͗p���{���o�[�̍��ڐݒ蒆�̑����l���̓��[�h)
	//
public:

	///////////////////////////////////////////////////////////////////////////////
	//	���{���o�[�̃R���{�b�N�X�̐ݒ�@�{��
protected:
	void SetComboCdBody( void);

	///////////////////////////////////////////////////////////////////////////////
	//	���i�d�l�Ɛ��@�`���𕔕i�z�u���̓f�[�^�Ɏ�荞��
protected:
	void GetPartsSpec( void);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l�𕔍ޔz�u���̓f�[�^�Ɏ�荞��
protected:
	void GetComboAttrA( void);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��
protected:
	void SetCheckAttr(
						MCCHKATTR	i_iAttr,		// ����ID
						int			i_iCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
	//
public:
	int GetCheckAttr(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCHKATTR	i_iAttr,		// ����ID
						int*		o_piCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
				);

};

extern	mnIoPartsAttr z_mnIA;

}// namespace MC