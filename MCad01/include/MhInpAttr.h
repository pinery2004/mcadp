#pragma once

#include "MhDefParts.h"
#include "MgPoint.h"

#define		MMAX_HOSEI_DBG	999
#define		MSZ_CROSS_BZI	100

namespace MC
{

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

class DLL_EXPORT mhHaitiIn
{
public:
	/////////////////////////////////////////////////////////////////////////////////
	////	�z�u�R�[�h�I��p�R���{�{�b�N�X�ɔz�u�R�[�h��\����
	////	�J�����g�̔z�u�R�[�h��ݒ肷��

	//static void SelectComboPlcCdByPlcCd(
	//						MINT		i_iCdPlc	// �z�u�R�[�h
	//				);

	/////////////////////////////////////////////////////////////////////////////////
	////	�z�u�R�[�h�I��p�R���{�{�b�N�X���z�u�R�[�h���擾����
	////	�i�J�����g�̔z�u�R�[�h���擾����j
	////							��0 : �C��
	////							��1 : �ǐc�t��
	////							��2 : �����\�����t��

	//static MINT GetComboPlcCd();


	/////////////////////////////////////////////////////////////////////////////
	//	���i�z�u���擾����
	//	�Ԓl =-1: �I�[�o�[�t���[, ��0: �I�𕔕i�z�u��

	static MINT GetParts(
							MINT		i_iKai,			// �K
							MINT		i_iIdPartsSpec,		// ���iID
					const	MCHAR*		i_sGeneralName,	// ���� �܂��� NULL
					const	MCHAR*		i_sNmParts1,		// ����p���ޖ� �܂��� NULL
							MINT		i_szPlcEn,		// ���i�z�u�ő吔
					class	mhPlcInfo*	*o_pPlcEn,		// �I�𕔕i�z�u
					class	MPOSITION*	o_pPlcpos = NULL// �I��[���i�z�u]�ʒu �܂��� NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���i�z�u�𒲂ׂ�
	//	�Ԓl true : �Ώە��i�z�u, false : �ΏۊO���i�z�u

	static bool ChkParts(
							MINT		i_iKai,			// �K �܂��� NULL
							MINT		i_iIdPartsSpec,		// ���iID �܂��� NULL
					const	MCHAR*		i_sGeneralName,	// ���� �܂��� NULL
					const	MCHAR*		i_sNmParts1,		// ����p���ޖ� �܂��� NULL
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
					class	MgPolyg2*	o_ppgPartsShape	// ���o���p�`�@�܂��́@NULL
					);


	/////////////////////////////////////////////////////////////////////////////
	//  �z�u���i�̌`������߂�
	static void PartsShape(
					class	mhPlcInfo*	i_pWndInfo,		// �E�B���h�E�Ǘ����
					class	MgPolyg2*	o_pgPartsShape	// ���ނ̌`��
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
	static void mhHaitiIn::MhModBzPH(
							MINT		iCdInpKbCd,		// (I  ) ���͓_�敪�R�[�h
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

class DLL_EXPORT mhInput
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

}// namespace MC