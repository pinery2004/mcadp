#pragma once


// mnMFCRibbonBar

class mnMFCRibbonBar : public CMFCRibbonBar
{
	int m_LastActiveCategory;


	DECLARE_DYNAMIC(mnMFCRibbonBar)

public:
	mnMFCRibbonBar();
	virtual ~mnMFCRibbonBar();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()

public:
	// ���{���o�[�̃J�e�S���ύX���b�Z�[�W�̎擾�p�ɒǉ����������b�Z�[�W�󂯂�ꂸ
	afx_msg LRESULT OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam);
};


enum	ComboTp {
	MSET_RIBBON_BAR = 1,			// ���{���o�[�̕��i�I��p����( �g�A���ށA���i�^�C�v�A���@�^��)��ݒ肷��
	MSET_INPUT_KUBUN_CD,			// �J�����g�̓��͓_�敪��ݒ肵�A���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
	MSET_INPUT_MARUME_CD,			// �J�����g�̊ۂ߃R�[�h��ݒ肵�A�ۂ߃R�[�h�p�̃R���{�{�b�N�X�ɕ\������
	MSET_INPUT_PLACE_CD,			// �J�����g�̔z�u�ˑ��R�[�h��ݒ肵�A�z�u�ˑ��R�[�h�p�̃R���{�{�b�N�X�ɕ\������
	MSET_COMBO_ATTRR,				// �����l���͗p�R���{�{�b�N�X�Ɏ����l��\������
	MGET_PARTS_ATTRA,				// ���i�d�l,���@�`���Ƒ����l���͗p�R���{�{�b�N�X�̒l�𕔕i�z�u���̓f�[�^�Ɏ�荞��
//U	���g�p	MSET_COMBO_PARTS,				// ���ޑ������͗p�R���{�{�b�N�X�̐ݒ�
	MSET_COMBO_PANELNO,				// �J�����g�̃p�l���ԍ��I�����ڔԍ���ݒ肵�@�R���{�{�b�N�X�Ƀp�l���ԍ���\������

	MINIT_COMBO_ATTR				// �����l���̓��[�h�ɉ��������ޑ������͗p���{���o�[�̍��ڂ�ݒ肷��
};




