#pragma once

#include "MmDefine.h"
#include "MgPoint.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPATTR_DO
	#pragma message( "<<< MC::InpAttr�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::InpAttr�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mtInpAttr
{
public:
	////////////////////////////////////////////////////////////////////////////
	//	���ޑ������͗p�R���{�{�b�N�X�̐ݒ�

	static void SetComboPts();

	/////////////////////////////////////////////////////////////////////////////
	//	���ޑ������͗p�R���{�{�b�N�X�̃C�j�V�����C�Y

	static void InitComboAttr(
							MINT		i_iMode = MP_AT_NONE // 1:���ޓ��́@2:���V��p�l�� 3:�����p�l��
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l����荞��

	static void GetComboAttrA( void);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������

	static void SetComboAttrR(
							MCCMBATTR	i_iAttr,		// ����ID
							MREAL		i_rValue		// �\����������l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����

	static MINT GetComboAttrR(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCMBATTR	i_iAttr,		// ����ID
							MREAL*		o_prValue		// �����l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������

	static void SetComboAttrI(
							MCCMBATTR	i_iAttr,		// ����ID
							MINT		i_iValue 		// �\�����鐮���l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐������擾����

	static MINT GetComboAttrI(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCMBATTR	i_iAttr,		// ����ID
							MINT*		o_piValue		// �����l
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�}�[�N��ݒ肷��

	static void SetCheckAttr(
							MCCHKATTR	i_iAttr,		// ����ID
							MINT		i_iCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�`�F�b�N�{�b�N�X�̃`�F�b�N�L�����擾����
	//

	static MINT GetCheckAttr(							// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
							MCCHKATTR	i_iAttr,		// ����ID
							MINT*		o_piCheckAttr	// �`�F�b�N�}�[�N�@0:OFF, 1:ON
					);


	/////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��

	static void InitComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������

	static void SetComboPanelNo(
							MINT		i_iPanelNo		// �p�l���ԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
	//							��-1: ���I��
	//							�� 0: �S
	//							�� 1: �p�l���ԍ�

	static MINT GetComboPanelNo();

	///////////////////////////////////////////////////////////////////////////////
	//	���ޑI��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��

	static void InitComboTpPtsAttr();

	///////////////////////////////////////////////////////////////////////////////
	//	���ޑI�����ڔԍ���ݒ肷��

	static void SetComboKmIdTpPts(
							MINT		i_iKmIdTpPts	// ���ޑI�����ڔԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���ޑI��p�R���|�{�b�N�X�ɕ��ނ�ݒ肷��
	//							��-1: �Y���Ȃ�
	//							�� 0: ����ID

	static MINT SetComboCdTpPts(
							MCHAR* 		i_sNmPts1		// �i����p�j���ޖ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���ޑI��p�R���|�{�b�N�X��蕔��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ����ID

	static MINT GetIdTpPts(
							MCHAR* 		i_sNmPts1		// �i����p�j���ޖ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���ޑI��p�R���|�{�b�N�X�̃J�����g�̕���ID���擾����
	//							��-1: ���I��
	//							�� 0: ����ID

	static MINT GetCurIdTpPts();


	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��

	static void InitComboPtsMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I�����ڔԍ���ݒ肷��

	static void SetComboKmIdMbr(
							MINT		i_iKmIdMbr		// ���@�^���I�����ڔԍ�
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I�����ڔԍ����擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ����ID
	static MINT GetComboKmIdMbr( MCHAR* i_sCdMbr);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�ɐ��@�^����ݒ肷��
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID

	static MINT SetComboCdMbr(
							MCHAR* 		i_sCdMbr
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^��ID���擾����
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID

	static MINT GetComboCdMbr(
							MCHAR* 		i_sCdMbr
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X��萡�@�^��ID���擾����
	//	�i�J�����g�̐��@�^��ID���擾����j
	//							��-1: ���I��
	//							�� 0: ����ID

	static MINT GetComboIdMbr();

	/////////////////////////////////////////////////////////////////////////////
	//	�_�C�A���O�֘A

	///////////////////////////////////////////////////////////////////////////////
	//	�_�C�A���O�o�[�̎��̍��ڂ�ݒ肷��
	//		�g�A���ށA���i�^�C�v�A���@�^��
	//

	static MINT SetDialogBar(							// �X�e�C�^�X 0:���� -1:�G���[
							MINT		i_iKumi,		// �g
							MINT		i_iBr,			// ����
							MCHAR*		i_sTpPts,		// ���i�^�C�v
							MCHAR*		i_sMbr			// ���@�^�� �܂��� NULL
					);
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_HAITIIN_DO
	#pragma message( "<<< MC::HaitiIn�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::HaitiIn�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mtHaitiIn
{
public:
	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X�ɔz�u�R�[�h��\����
	//	�J�����g�̔z�u�R�[�h��ݒ肷��

	static void SetComboCdPlc(
							MINT		i_iCdPlc	// �z�u�R�[�h
					);

	///////////////////////////////////////////////////////////////////////////////
	//	�z�u�R�[�h�I��p�R���{�{�b�N�X���z�u�R�[�h���擾����
	//	�i�J�����g�̔z�u�R�[�h���擾����j
	//							��0 : �C��
	//							��1 : �ǐc�t��
	//							��2 : �����\�����t��

	static MINT GetComboCdPlc();


	/////////////////////////////////////////////////////////////////////////////
	//	���i�z�u���擾����
	//	�Ԓl =-1: �I�[�o�[�t���[, ��0: �I�𕔕i�z�u��

	static MINT GetPts(
							MINT		i_iKai,			// �K
							MINT		i_iIdTpPts,		// ���iID
					const	MCHAR*		i_sGeneralName,	// ���� �܂��� NULL
					const	MCHAR*		i_sNmPts1,		// ����p���ޖ� �܂��� NULL
							MINT		i_szPlcEn,		// ���i�z�u�ő吔
					class	mhPlcInfo*	*o_pPlcEn,		// �I�𕔕i�z�u
					class	MPOSITION*	o_pPlcpos = NULL// �I��[���i�z�u]�ʒu �܂��� NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���i�z�u�𒲂ׂ�
	//	�Ԓl true : �Ώە��i�z�u, false : �ΏۊO���i�z�u

	static bool ChkPts(
							MINT		i_iKai,			// �K �܂��� NULL
							MINT		i_iIdTpPts,		// ���iID �܂��� NULL
					const	MCHAR*		i_sGeneralName,	// ���� �܂��� NULL
					const	MCHAR*		i_sNmPts1,		// ����p���ޖ� �܂��� NULL
					class	mhPlcInfo*	i_pPlcEn		// �������i�z�u
					);

	/////////////////////////////////////////////////////////////////////////////
	//  ���ޔz�u����������
	//	�Ԓl �������ʁ@�܂��́@null:�q�b�g�Ȃ�
	static mhPlcInfo* SrchBuzai(
					class	MmWndInfo*	i_pWndInfo,		// �E�B���h�E�Ǘ����
					class	MgPoint2&	i_ptMouthR,		// �����w�����W
							MINT		i_iCdBuzai,		// ���ރR�[�h�@�܂��́@NULL(�S)
														// MP_BZICD_PANEL(�S�p�l��)
					class	MgPolyg2*	o_ppgPtsShape	// ���o���p�`�@�܂��́@NULL
					);


	/////////////////////////////////////////////////////////////////////////////
	//  �z�u���i�̌`������߂�
	static void PtsShape(
					class	mhPlcInfo*	i_pWndInfo,		// �E�B���h�E�Ǘ����
					class	MgPolyg2*	o_pgPtsShape	// ���ނ̌`��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�P�z�u���i��\������
	static void DrawPart( 
					class	msCod*		i_pCod,			// ���W�n
							MINT		i_iGpC,			// �\��
					class	mhPlcInfo*	i_pPlcEn		// ���i�z�u�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���ނ̔z�u�_�ƒ����␳�l���C��
	static void mtHaitiIn::MhModBzPH(
							MINT		iInpKbCd,		// (I  ) ���͓_�敪�R�[�h
							MINT		iMov,			// (I  ) �C�����@(0:�n�_�A1:�I�_)
					const	MgPoint3	&PtInt,			// (I  ) �z�u�_
							MREAL		rLH,			// (I  ) �����␮�l
							mhPlcInfo	*pPlcEnR		// (I O) ������������
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����悪���ނŎ����ꂽ���ނ̒�������
	static MINT MhAdjBzL(								// (  O) �X�e�C�^�X�@
														//	MC_PARALLEL (-1) �����Ȃ��i���s�j
														//	MC_TWIST    (-2) �����Ȃ��i�˂���j
														//	MC_NINT	    (0)	�����Ȃ�
														//	MC_INT      (1)	��������
							MINT		iKati,			// (I  ) ���������t���O(1:�����A0:����)
							mhPlcInfo*	pPlcEn1,		// (I O) ������������1
					const	MgPoint3	&Pt1,			// (I  ) ����1�̒����������鑤�������Ŋ�̓_
							mhPlcInfo*	pPlcEn2		// (I  ) �������������������2
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����悪���s���ނŎ����ꂽ���ނ̒�������
	static void MhAdjBzL(								// (  O) �X�e�C�^�X�@
														//	MC_PARALLEL (-1) �����Ȃ��i���s�j
														//	MC_TWIST    (-2) �����Ȃ��i�˂���j
														//	MC_NINT	    (0)	�����Ȃ�
														//	MC_INT      (1)	��������
							mhPlcInfo*	pPlcEn1,		// (I O) ������������1
					const	MgPoint3	&Pt1,			// (I  ) ����1�̒����������鑤�������Ŋ�̓_
							mhPlcInfo*	pPlcEn2,		// (I  ) �������������������2
					const	MgPoint3	&Pt2			// (I  ) ����2�̒���������������Ŋ�̓_
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����悪�_���W�Ŏ����ꂽ���ނ̒�������
	static void MhAdjBzL(
							mhPlcInfo*	pPlcEn1,	// ������������1
					const	MgPoint3	&Pt1,		// ����1�̒����������鑤�������Ŋ�̓_1
					const	MgPoint3	&Pt2		// ����������������_2
					);

	/////////////////////////////////////////////////////////////////////////////
	//	����������̕��ނɐڐG���镔�ނƌ������镔�ނ����߂�
	static void MmSrchCrossBuzai(
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							mhPlcInfo*	pBziInfo1,		// (I  ) ������������
							MINT		iBuzaiCd,		// (I  ) ���ރR�[�h
							mhPlcInfo**	pbTchBzi,		// (  O) ����������̕��ނɐڐG���镔��
							mhPlcInfo**	pbCrsBzi		// (  O) ����������̕��ނƌ������镔��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���������O��ŐڐG��Ԃƌ�����Ԃ��ω����镔�ނ����߂�
	static void MhChngCrossBuzai(
							mhPlcInfo	**pbTchBziI,	// (I  ) ���������O�ɒ����������ނɐڐG���镔��
							mhPlcInfo	**pbCrsBziI,	// (I  ) ���������O�ɒ����������ނƌ������镔��
							mhPlcInfo	**pbTchBziO,	// (I  ) ����������ɒ����������ނɐڐG���镔��
							mhPlcInfo	**pbCrsBziO,	// (I  ) ����������ɒ����������ނƌ������镔��
							mhPlcInfo	**pbFRtoTCBzi,	// (  O) ���������O�ɒ����������ނƗ���Ă�����
														//		 ����������ɐڐG�܂��͌�����������
							mhPlcInfo	**pbTCtoFRBzi,	// (  O) ���������O�ɒ����������ނƐڐG�܂��͌������Ă�����
														//		 ����������ɗ��ꂽ����
							mhPlcInfo	**pbTCtoTCBzi	// (  O) ���������O�ɒ����������ނɐڐG�܂��͌������Ă�����
														//		 �A����������ɂ��ڐG�܂��͌������Ă��镔��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	������z�u����

	static MINT RoofPlc(								// �X�e�C�^�X	0: ����A-1: �����z�u�G���[
			const	class	MgPolyg2&	i_pgJim,		// �n�����
			const	class	MgGInt&		i_GifInp,		// �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
			const	class	MgPoint2&	i_pth			// �����_
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����ʂ���������
	//	�Ԓl =NULL: �Y�������ʂȂ� !=NULL: �Y�������ʐ�
	static class MhRfm*	SrchRfm(					// �����ʁ@�܂��́@NULL
							MINT		i_iMode,		// �������[�h	�w���_�ɊY�����鉮���ʂ���������ꍇ�̗D��I������
														//				MC_PRI_MIN_AREA(0):	 �ʐς�����D��
														//				MC_PRI_MIN_HIGHT(1): ����������D��
														//				MC_PRI_MAX_HIGHT(2) | ���̑�: ���������D��	
					const	MgPoint2&	i_pt1			// �w���_
					);

	////////////////////////////////////////////////////////////////////////////
	//	�J�����g�I���̉����ʂ�ݒ肷��

	static void SetCurRfm(
					class	MhRfm* 		pRfm			// (I  ) �J�����g�I���̉�����
				);

	////////////////////////////////////////////////////////////////////////////
	//	�J�����g�I���̉����ʂ�Ԃ�
	static MhRfm* GetCurRfm();

};

////////////////////////////////////////////////////////////////////////////
// Input

#define		MAXHAIKABE		500							// �z�񐧌��l
#define		MC_KABE_TOL		44.5						// �ǔ���g�������X
#define		MC_MARUME_TOL	44.5						// �ۂߑΏې�������g�������X

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPUT_DO
	#pragma message( "<<< MC::Input�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::Input�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mtInput
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//	�����Q�_����

	static MINT GetLen2Pt(
							MINT		i_iMode,		// ���̓��[�h
														//			�@0: �����Q�_����
														//			�@1: �A�������Q�_�̏I�_����
														//					�n�_�͑O�����(pLn)�̏I�_�Ƃ���
														//			�@2: �����P�_����
					class	MgPoint2*	o_pptln,		// ���͊ۂߍ��W�i�����Q�_���W �{�@�������ނ̗̈������킷�R�_�ځj
					class	MgPoint2*	o_pptln_org		// ���̓I���W�i�����W�i�����Q�_���W �{�@�������ނ̗̈������킷�R�_�ځj 
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�P�_����

	static MINT Get1Pt(
					class	MgPoint2*	o_ppt1,			// ���͊ۂߍ��W�i�_�j
					class	MgPoint2*	o_ppt1_org		// ���̓I���W�i�����W�i�_�j
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�A�����������Q�_���͗p�̂Q�_�ڂ̓���(�O�Ǔ��͗p)

	static MINT GetLenEPt(
					class	MgLine2*	o_pLn
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����`������

	static MINT GetRect2Pt(
					class	MgLine2*	o_pLn
					);

	/////////////////////////////////////////////////////////////////////////////
	//	������

	static MINT GetArea(
					class	MgPolyg2*	o_pPg1
					);

	/////////////////////////////////////////////////////////////////////////////
	//	������ 
	//	�e�ӂɁ@�V�t�g�L�[�L���̃t���O�t��

	static MINT GetAreaI(
					class	MgPolyg2*	pPg1,			// (  O) �n�����
					class	MgGInt*		pGifInp			// (  O) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				);

	/////////////////////////////////////////////////////////////////////////////
	//	�ǐc�ۂߐ����擾����

	static void GetMarumeKabeLine(
							MINT		i_iKai,			// �����K
			const	class	MgPoint2&	i_pti,			// ���͍��W
					class	MgGLine2*	o_pGLn			// �Ώەǐc
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����\�����ۂߐ����擾����
	//
	static void MmGetMarumeYaneLine(
							MINT		iKai,			// �����K
			const	class	MgPoint2	&Pi,			// ���͍��W
					class	MgGLine2*	pGLn			// �Ώۉ����\����
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�ۂ�
	static void	Marume(									// ���W�l���ۂ߂�
			const	class	MgPoint2&	Pi,				// ���͍��W
					class	MgPoint2*	pPo				// �ۂߌ�̍��W
				);

};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_INPMODE_DO
	#pragma message( "<<< MC::mtInpMode�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mtInpMode�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT mtInpMode
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//	�n�����[�h		�폜�A�C���A�ړ��A���ʁA�����\��

	static void SetMode(
							MINT 		i_iMode
					);
	static MINT GetMode();

	///////////////////////////////////////////////////////////////////////////////
	//	�R���{�{�b�N�X�ɓ��͓_�敪��\����
	//	�J�����g�̓��͓_�敪��ݒ肷��

	static void SetComboInpKb(
							MINT		i_iInpKb		// ���͓_�敪
					);

	///////////////////////////////////////////////////////////////////////////////
	//	���͓_�敪�I��p�R���{�{�b�N�X�����͓_�敪���擾����
	//	�i�J�����g�̓��͓_�敪���擾����j
	//							��1 : �P�_����
	//							��2 : �����P�_����
	//							��3 : �����Q�_����
	//							��4 : ������
	//							��5 : ���R����

	static MINT GetComboInpKb();

	///////////////////////////////////////////////////////////////////////////////
	//	�ۖڃR�[�h�I��p�R���{�{�b�N�X�ɊۖڃR�[�h��\����
	//	�J�����g�̊ۖڃR�[�h��ݒ肷��

	static void SetComboCdMarume(
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

	static MINT GetComboCdMarume();

	/////////////////////////////////////////////////////////////////////////////
	//	�K				�P�K�A�Q�K�A�R�K

	static void SetKai(
							MINT 		i_iKai
					);
	static MINT GetKai();

	/////////////////////////////////////////////////////////////////////////////
	// �݌v���͍\��		�Z�ˁA�Z���A�����A�����A�~�n�A�Ǘ�

	static void SetSGp(
							MINT		i_iGp
					);
	static MINT GetSGp();

	/////////////////////////////////////////////////////////////////////////////
	// �݌v���͎��

	static void SetSBr(
							MINT		i_iBr
					);
	static MINT GetSBr();

	/////////////////////////////////////////////////////////////////////////////
	// �݌v���͑I��

	static void SetSSel(
							MINT		i_iSel
					);
	static MINT GetSSel();

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͍\��		�����A�����A�V��A�ϗ͕ǁA�ǁA���A��b

	static void SetKGp(
							MINT		i_iGp
					);
	static MINT GetKGp();

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͎��		���ށA�����A�p�l���A���̑�

	static void SetKBr(
							MINT		i_iBr
					);
	static MINT GetKBr();

	/////////////////////////////////////////////////////////////////////////////
	// �\�����͑I��		�I��1�A�I��2�A�I��3						���g�p

	static void SetKSel(
							MINT		i_iSel
					);
	static MINT GetKSel();

	/////////////////////////////////////////////////////////////////////////////
	//	���ށA�����A�p�l���A���̑��̃��W�I�{�^���̑I����͋���ݒ�

	static void SetKBrB(
							bool		i_bBuzai,
							bool		i_bKanagu,
							bool		i_bPanel,
							bool		i_bOther
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�����l���̓��[�h���擾����

	static MINT GetAtMd();

};

}// namespace MC