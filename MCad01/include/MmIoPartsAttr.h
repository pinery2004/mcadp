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
	#pragma message( "<<< MC::mmIoPartsAttr�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::mmIoPartsAttr�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class MmPartsComboKm {
	MINT		m_iComboPartsNm;				// ���iID
	MINT		m_iComboMbr;					// ���@�^��
	MINT		m_iComboInpKbn;					// ���͓_�敪
	MINT		m_iComboMarume;					// �ۂ߃R�[�h
	MINT		m_iComboPlcIzon;				// �z�u�ˑ��R�[�h
	MINT		m_iComboPanelNo;				// �p�l���ԍ�
};

class DLL_EXPORT mmIoPartsAttr: public CMmDialogKAttr
{
	friend CMainFrame;
	friend CMCadApp;

protected:
	// ���i���R���{�{�b�N�X
	int m_nComboIdPartsSpec;					// �\�����ڐ�
	int m_iComboIdPartsSpec[MX_CMB_PARTSNM];	// �\�����ڑΉ����iID
	int m_iComboKmIdPartsNm;					// �J�����g�I�����ڔԍ�

	// ���@�^���I��p�R���{�{�b�N�X
	int m_nComboMbrId;							// �\�����ڐ�
	int m_iComboMbrId[MX_CMB_CDMEMBER];			// �\�����ڑΉ����@�^��ID
	int m_iComboKmIdMbr;						// �J�����g�I�����ڔԍ�

	int	m_iIoPartsAttrMd;						// �����l���̓��[�h
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
	mmIoPartsAttr(){
		m_iIoPartsAttrMd = -1;
	};

	///////////////////////////////////////////////////////////////////////////////
	//	�_�C�A���O�̐ݒ�Ǝ�荞��
public:
	int RibbonIO(
						ComboTp	i_iComboTp,			// Combo���	1:���͓_�敪�R�[�h
						int		i_iCdArg1 = NULL,	//				
						MREAL	i_rCdArg2 = NULL	//				
				);


	//==================================//
	//			   8. ���i��			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�̍��ڂ�ݒ肷��
//protected:
public:
	void InitComboPartsNm();

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i�����ڔԍ��őI������
//protected:
public:
	void SelectComboPartsNmByKmId(
						int		i_iKmIdPartsNm	// ���i�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���i���R���|�{�b�N�X�𕔕i���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���iID
//protected:
public:
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

	//==================================//
	//			  9. �����o�[			//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���I��p�R���|�{�b�N�X�̍��ڂ�ݒ肷��
//protected:
public:
	void InitComboMbr();

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`�����ڔԍ��őI������
//protected:
public:
	void SelectComboMbrByKmId(
						int			i_iKmIdMbr		// ���@�^�����ڔԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	���@�^���R���{�{�b�N�X�𐡖@�`���őI������
	//							��-1: �Y���Ȃ�
	//							�� 0: ���@�^��ID
//protected:
public:
	int SelectComboMbrByMbrCd(
						MCHAR* 		i_sCdMbr		// ���@�^��
				);

	//==================================//
	//			  9. �����l				//
	//==================================//
	///////////////////////////////////////////////////////////////////////////////
	//	�\���R�[�h�A���ށA���i���ID���A�����l���̓��[�h�����߂�
protected:
	int MnCalcInpAtMode();

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̑����l���̓��[�h���擾����
	//	(���i�������͗p�_�C�A���O�̍��ڐݒ蒆�̑����l���̓��[�h)
	//
public:
	int GetAtMd()
	{
		return m_iIoPartsAttrMd;
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�����l���̓��[�h�ŕ��i�������͗p�_�C�A���O�̍��ڂ�ݒ肷��
	//	 (�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��)
	//	
public:
	void InitComboAttrEntry(
						int	i_iIoPartsAttrMd = MP_AT_NONE	// �����l���̓��[�h
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
			RibbonIO( MINIT_COMBO_ATTR, i_iIoPartsAttrMd);

	}

	/////////////////////////////////////////////////////////////////////////////
	//	�����l���̓��[�h�ŕ��i�������͗p�_�C�A���O�̍��ڂ�ݒ肷��
	//	 (�R���{�{�b�N�X�ƃ`�F�b�N�{�b�N�X�̍��ڂ�ݒ肷��)
	//	
public:
	void InitComboAttrXqt(
						int	i_iIoPartsAttrMd = MP_AT_NONE	// �����l���̓��[�h
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
//protected:
public:									// ���ݒ�
	void InitComboParts();

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l����荞��
public:
	void GetComboAttrAEntry( void)
	{
		RibbonIO( MGET_PARTS_ATTRA);
	}

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̒l����荞��
protected:
	void GetComboAttrAXqt( void);

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
						int			i_iAttr,		// �R���{�{�b�N�X�ԍ�
						MCHAR*		i_sTitle		// �^�C�g��
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���|�{�b�N�X�Ɏ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrR(
						int			i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int			i_nComboAttr,	// �I�𑮐��l�̐�
						MREAL*		i_rComboAttr,	// �I�𑮐��l
						MREAL		i_rInitValue	// �����\�����鑮���l
				);

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
public:
	void SetComboAttrREntry(
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL		i_rValue		// �\����������l
				)
	{
		RibbonIO( MSET_COMBO_ATTRR, i_iAttr, i_rValue);
	}

	//////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrRXqt(
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL		i_rValue		// �\����������l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
//protected:
public:
	int GetComboAttrR(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						MREAL*		o_prValue		// �����l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
protected:
	void SetComboAttrRCbn(
						int			i_iAttr,		// �R���{�{�b�N�X�ԍ�
						MREAL		i_rValue		// �\����������l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̎����l���擾����
	//
protected:
	MREAL GetComboAttrRCbn(		// (  O) �����l�@�܂��́@0(���ݒ�)
						int			i_iAttr			// �R���{�{�b�N�X�ԍ�
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�w��R���|�{�b�N�X�ɐ����l�̍���(�ꗗ)��ݒ肷��
protected:
	void InitComboAttrI(
						int			i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int			i_nComboAttr,	// �I�𑮐��l�̐�
						int*		i_iCmbAttr,		// �I�𑮐��l
						int			i_iInitValue	// �����\�����鑮���l
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
//protected:
public:
	int GetComboAttrI(								// �X�e�C�^�X0(���ݒ�) 1(�ݒ�)
						MCCMBATTR	i_iAttr,		// ����ID
						int*		o_piValue		// �����l
				);


	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�ɐ����l��\������
protected:
	void SetComboAttrICbn(
						int			i_iAttr,		// �R���{�{�b�N�X�ԍ�
						int			i_iValue 		// �\�����鐮���l
				);

	///////////////////////////////////////////////////////////////////////////////
	//	�����l���͗p�R���{�{�b�N�X�̐����l���擾����
	//
protected:
	int GetComboAttrICbn(							// �����l�@�܂��́@0(���ݒ�)
						int			i_iAttr			// �R���{�{�b�N�X�ԍ�
				);

//U	/////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��R���|�{�b�N�X�̍��ڂ�ݒ肷��
//protected:
//	void InitComboPanelNo();
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��R���|�{�b�N�X�Ƀp�l���ԍ���\������
//protected:
//	void SetComboPanelNoXqt(
//						int			i_iPanelNo		// �p�l���ԍ�
//				);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//	�p�l���ԍ��I��p�R���|�{�b�N�X���p�l���ԍ����擾����
//	//							��-1: ���I��
//	//							�� 0: �S
//	//							�� 1: �p�l���ԍ�
//public:
//	int GetComboPanelNo();
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	�p�l��No
//public:
//	void SetPanelNo(
//						int 		i_iPanelNo		// �{��	
//				)
//	{
//		m_iPanelNo = i_iPanelNo;
//	}
//public:
//	int GetPanelNo()
//	{
//		return m_iPanelNo;
//	}

};
extern	mmIoPartsAttr z_mmIA;

}// namespace MC