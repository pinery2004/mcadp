#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"
#include "MainFrm.h"
#include "MCad.h"

#include "MmIoPartsAttr.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100
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

// ���͑����@�ӏ��ƍ\���̋��ʍ���
class InpAttrIK
{
public:
	int			m_iComboInpKbn;						// ���͓_�敪
	int			m_iComboMarume;						// �ۂ߃R�[�h
	int			m_iComboPlcIzon;					// �z�u�ˑ��R�[�h

	MPKOSEI		m_iInpGp;							// ���͍\��		(�����A�����A�V��A�ϗ͕ǁA�ǁA���A�y��A��b)
	MPBUNRUI	m_iInpBr;							// ���͎��		(���ށA�����A�p�l���A���̑�)
	MPSELECT	m_iInpSel;							// ���͑I��		�I��1�A�I��2�A�I��3						���g�p

	int			m_iComboPartsNm;					// ���i��
	int			m_iComboMbr;						// ���@�^��
};

// ���͑����@�ӏ�+�\��
class InpAttrA
{
public:
	int			m_iCurCategory;						// �J�����g�J�e�S���@1:�ӏ�, 2:�\��, 3:����
	int			m_iInpKai;							// ���͊K			(1�K,2�K,3�K)

	MPPROC		m_iSInpProc;						// �ӏ�: ���͏���	(�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�)

	InpAttrIK	m_IK[2];							// �ӏ��ƍ\���̋��ʍ���

	int			m_iComboPanelNo;					// �\��: �p�l���ԍ�
	bool		m_bKDspBuzai;						// �\��: ���ޕ\���t���O
	bool		m_bKDspKanagu;						// �\��: �����\���t���O
	bool		m_bKDspGohan;						// �\��: ���\���t���O

	MPATTR		m_iAttr;							// �\��: �����l���̓��[�h

// ======== ���ޗp ========
	MREAL		m_rLngH;							// �����␳�l
	MREAL		m_rSinZ;							// �ގ��c�����
	MREAL		m_rHaiZ;							// �z�u�_�����
	MREAL		m_rZ1;								// ���t������
	MREAL		m_rZ2;								// �q�n�g
	MREAL		m_rIntv;							// �Ԋu
	int			m_iNum;								// �{��

// ======== �p�l���p ========
	MREAL		m_rLngH2;							// �p�l�����␳�l
	MREAL		m_rOkuH;							// ��O���␳�l�A���s���␳�l
	MREAL		m_rOku;								// ���s��
	int			m_iKoubai;							// �������z
	MREAL		m_rNokiDe;							// ���̏o
	MREAL		m_rKerabanoDe;						// �P���o�̏o
};

class DLL_EXPORT mnIoPartsAttr
{
	friend CMainFrame;
	friend CMCadApp;
	friend CMmDialogKAttr;
	friend mmIoPartsAttr;

protected:
	MPMODE		m_iInpMd;							// �n�����[�h		(�폜�A�C���A�ړ��A���ʁA�����\��)

	InpAttrA	m_IA;								// ���͑���

	////////////////////////////////////////////////////////////////////////////
	//	�R���X�g���N�^
public:
	mnIoPartsAttr();

	////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p
protected:
	ComboTp		m_iComboTp;							// �R���{���
	int			m_iCdArg1;							// �ݒ�R�[�h1 ����
	MREAL		m_rCdArg2;							// �ݒ�R�[�h2 ����
	int			m_iSts;								// �X�e�C�^�X

	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
protected:
	MPKOSEI		m_iRBKosei;							// �\��	�\��
	MPBUNRUI	m_iRBBunrui;						// �\��	����
	MCHAR*		m_sRBBuhin;							// ���i
	MCHAR*		m_sRBMbr;							// ���i�����o�[

	// ���i���R���{�{�b�N�X
	int		m_nComboIdPartsSpec;					// �\�����ڐ�
	int		m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// �\�����ڑΉ����iID
	int		m_iComboKmIdPartsNm;					// ���i���J�����g�I�����ڔԍ�

	// ���@�^���I��p�R���{�{�b�N�X
	int		m_nComboMbrId;							// �\�����ڐ�
	int		m_iComboMbrId[MX_CMB_CDMEMBER];			// �\�����ڑΉ����@�^��ID
	int		m_iComboKmIdMbr;						// ���@�`���J�����g�I�����ڔԍ�


	///////////////////////////////////////////////////////////////////////////////
	//	���{���o�[�̐ݒ�Ǝ�荞��
protected:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo���	1:���͓_�敪�R�[�h
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);

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

	///////////////////////////////////////////////////////////////////////////////
	//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�
protected:
	int MnCalcInpAtMode();

	///////////////////////////////////////////////////////////////////////////////
	//	���i�d�l�Ɛ��@�`���𕔕i�z�u���̓f�[�^�Ɏ�荞��
protected:
	void GetPartsSpec( void);

	//==================================//
	//		 1. �J�����g�J�e�S��		//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�J�e�S��	
public:
	void	SetCurCategory(
						int i_iCurCategory			// �J�����g�J�e�S���@1:�ӏ�, 2:�\��, 3:����
				)
	{
		m_IA.m_iCurCategory = i_iCurCategory;

	}

	int	GetCurCategory()
	{
		return m_IA.m_iCurCategory;
	}

	// ���͑����@�ӏ��ƍ\���̋��ʍ��ڂ̃|�C���^���擾
	InpAttrIK* GetpInpAttr()
	{
		int iIK = m_IA.m_iCurCategory - 1;
		ASSERT( iIK >=0 && iIK <=1); 
		return &m_IA.m_IK[iIK];
	}

	//==================================//
	//			  2. ���͊K				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	�K				�P�K�A�Q�K�A�R�K
public:
	void SetInpKai(
						int	 		i_iInpKai		// �K	
				)
	{
		m_IA.m_iInpKai = i_iInpKai;
	}

public:
	int GetInpKai()
	{
		return m_IA.m_iInpKai;
	}

	//==================================//
	//			3. ���͓_�敪			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	�R���{�{�b�N�X�ɓ��͓_�敪��\����
	//	�J�����g�̓��͓_�敪��ݒ肷�鏈�����N��
	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
public:
	void SelectComboInpKbnByInpKbnCdEntry(
						int			i_iCdCdInpKbn	// ���͓_�敪
				)
	{
		RibbonIO( MSET_INPUT_KUBUN_CD, i_iCdCdInpKbn);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�R���{�{�b�N�X�ɓ��͓_�敪��\����
	//	�J�����g�̓��͓_�敪��ݒ肷��	(�{��)
protected:
	void SelectComboInpKbnByInpKbnCdXqt(
						int			i_iCdCdInpKbn	// ���͓_�敪
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
	int GetComboInpKbnCd();

	//==================================//
	//			4. �ۂ߃R�[�h			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X�ɊۖڃR�[�h��\����
	//	�J�����g�̊ۖڃR�[�h��ݒ肷�鏈�����N��
	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
public:
	void SelectComboMarumeByMarumeCdEntry(
						int			i_iCdMarume		// �ۖڃR�[�h
				)
	{
		RibbonIO( MSET_INPUT_MARUME_CD, i_iCdMarume);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X�ɊۖڃR�[�h��\����
	//	�J�����g�̊ۖڃR�[�h��ݒ肷��	(�{��)
protected:
	void SelectComboMarumeByMarumeCdXqt(
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

	//==================================//
	//			 5. �z�u�ˑ��R�[�h			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�ˑ��R�[�h�I��p�R���{�{�b�N�X�ɔz�u�ˑ��R�[�h��\����
	//	�J�����g�̔z�u�ˑ��R�[�h��ݒ肷�鏈�����N��
	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
public:
	void SelectComboPlcIzonCdByPlaceCdEntry(
						int			i_iCdPlc		// �z�u�ˑ��R�[�h
				)
	{
		RibbonIO( MSET_INPUT_PLACE_CD, i_iCdPlc);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�ˑ��R�[�h�I��p�R���{�{�b�N�X�ɔz�u�ˑ��R�[�h��\����
	//	�J�����g�̔z�u�ˑ��R�[�h��ݒ肷��	(�{��)
protected:
	void SelectComboPlcIzonCdByPlaceCdXqt(
						int			i_iCdPlc		// �z�u�ˑ��R�[�h
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�ˑ��R�[�h�I��p�R���{�{�b�N�X���z�u�ˑ��R�[�h���擾����
	//	�i�J�����g�̔z�u�ˑ��R�[�h���擾����j
	//							��0 : �C��
	//							��1 : �ǐc�t��
	//							��2 : �����\�����t��
public:
	int GetComboPlcIzonCd();

	//==================================//
	//	 6�`9. �g,����,���i��,�����o�[	//
	//==================================//
	////////////////////////////////////////////////////////////////////////////
	//�@ ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷�鏈�����N��
	//		�g�A���ށA���i���A���@�^��
	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
public:
	int	SetRibbonBarEntry( 							// �X�e�C�^�X 0:���� -1:�G���[
					MPKOSEI		i_irbKumi,			// �\���g
					MPBUNRUI	i_irbBunrui,		// �\������
					MCHAR*		i_crbPartsSpec,		// ���i���		(���i��)
					MCHAR*		i_crbMbr = NULL		// ���i�����o�[	(���@�^��)
				)
	{
		int	ist;
		m_iRBKosei	= i_irbKumi;
		m_iRBBunrui = i_irbBunrui;
		m_sRBBuhin	= i_crbPartsSpec;
		m_sRBMbr	= i_crbMbr;

		ist = RibbonIO( MSET_RIBBON_BAR);

		return ist;
	}

	////////////////////////////////////////////////////////////////////////////
	// ���i���͗p�A���{���o�[�̕��i�I��p���ڂ�ݒ肷��(�{��)
	//		�g�A���ށA���i���A���@�^��	(�{��)
protected:
	int	SetRibbonBarXqt( 								// �X�e�C�^�X 0:���� -1:�G���[
					MPKOSEI		i_irbKumi,			// �\���g
					MPBUNRUI	i_irbBunrui,		// �\������
					MCHAR*		i_crbPartsSpec,		// ���i���		(���i��)
					MCHAR*		i_crbMbr = NULL		// ���i�����o�[	(���@�^��)
				);

	//==================================//
	//			  6. �\��(�g)			//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// �\���g		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b
public:
	void SetKCdGp(
						MPKOSEI		i_iKInpGp		// �\���@�\��(�g)
				)
	{
		m_IA.m_IK[1].m_iInpGp = i_iKInpGp;
	}

public:
	MPKOSEI GetKCdGp()
	{
		return m_IA.m_IK[1].m_iInpGp;
	}

	//==================================//
	//			  7. ����				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// �\�����͕���		���ށA�����A�p�l���A���̑�
public:
	void SetKCdBr(
						MPBUNRUI		i_iKInpBr		// �\���@���
				)
	{
		m_IA.m_IK[1].m_iInpBr = i_iKInpBr;
	}

public:
	MPBUNRUI GetKCdBr()
	{
		return m_IA.m_IK[1].m_iInpBr;
	}

	//==================================//
	//			   8. ���i��			//
	//==================================//
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

	//==================================//
	//			  9. �����o�[			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI������
protected:
	void SelectComboMbrByKmId(
						int			i_iKmIdMbr		// ���@�^�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
protected:
	int SelectComboMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�`�����琡�@�^���R���{�{�b�N�X�̐��@�^�����ڔԍ����擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
public:
	int GetComboMbrKmId(
						MCHAR*		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X��萡�@�^��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
public:
	int GetComboMbrCdId(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X��萡�@�^��ID���擾����
	//	�i�J�����g�̐��@�^��ID���擾����j
	//							��-1: ���I��
	//							�� 0: ���iID
public:
	int GetCurMbrCdId();

	//==================================//
	//			  10. ����				//
	//==================================//
//U	���g�p
//	////////////////////////////////////////////////////////////////////////////
//	//	���i�������͗p�R���{�{�b�N�X�̐ݒ菈�����N��
//	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
//public:
//	void InitComboPartsEntry()
//	{
//		RibbonIO( MSET_COMBO_PARTS);
//	}

	////////////////////////////////////////////////////////////////////////////
	//	���i�������͗p�R���{�{�b�N�X�̐ݒ�	(�{��)
protected:
	void InitComboPartsXqt();

	//////////////////////////////////////////////////////////////////////////////
	// ���i�������͗p�R���{�{�b�N�X���擾����
protected:
	CMFCRibbonComboBox* MnpComboAttr(
						int			i_iAttr			// �R���{�{�b�N�X�ԍ�
				);

	//==================================//
	//			  11. �I��				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p
public:
	void SetKSel(
						MPSELECT	i_iSel			// �I��ԍ�
				)
	{
		m_IA.m_IK[1].m_iInpSel = i_iSel;
	}

public:
	MPSELECT GetKSel()
	{
		return m_IA.m_IK[1].m_iInpSel;
	}

	//==================================//
	//			  12. ���L				//
	//==================================//
	//==================================//
	//			  13. ����				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	���ށA�����A���̃`�F�b�N�{�b�N�X�̕\���t���O��ݒ�
public:
	void SetKCdBrB(
						bool		i_bDspBuzai,	// ���ޕ\���t���O
						bool		i_bDspKanagu,	// ����\���t���O
						bool		i_bDspGohan		// ���\���t���O
				)
	{
		m_IA.m_bKDspBuzai  = i_bDspBuzai;
		m_IA.m_bKDspKanagu = i_bDspKanagu;
		m_IA.m_bKDspGohan  = i_bDspGohan;
	}

	//==================================//
	//			 14. �p�l��				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��
protected:
	void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������
	//	(�ʃv���Z�X����̃G���g���[��SendMessage���g�p���Ė{�̂����s)
public:
	void SetComboPanelNoEntry(
						int			i_iPanelNo		// �p�l���ԍ�
				)
	{
		RibbonIO( MSET_COMBO_PANELNO, i_iPanelNo);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������	(�{��)
protected:
	void SetComboPanelNoXqt(
						int			i_iPanelNo		// �p�l���ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
	//							��-1: ���I��
	//							�� 0: �S
	//							�� 1: �p�l���ԍ�
public:
	int GetComboPanelNo();

	//==================================//
	//			 15. �����I��			//
	//==================================//
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
						int		i_iChkNo,			// �`�F�b�N�{�b�N�X�ԍ�
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

	//==================================//
	//			 16. �n�����[�h			//
	//==================================//
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

	//==================================//
	//			 17. �ӏ�����			//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// �ӏ����͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�
public:
	void SetSCdProc(
						MPPROC		i_iSInpProc		// �݌v�@�\��
				)
	{
		m_IA.m_iSInpProc = i_iSInpProc;
	}
public:
	MPPROC GetSCdPrc()
	{
		return m_IA.m_iSInpProc;
	}

	//==================================//
	//			 18. �ӏ��g				//
	//==================================//
	/////////////////////////////////////////////////////////////////////////////
	// �\���g		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b
public:
	void SetSCdGp(
						MPKOSEI		i_iSInpGp		// �݌v�@�\��
				)
	{
		m_IA.m_IK[0].m_iInpGp = i_iSInpGp;
	}
public:
	MPKOSEI GetSCdGp()
	{
		return m_IA.m_IK[0].m_iInpGp;
	}

};

extern	MC::mnIoPartsAttr z_mnIA;

}// namespace MC