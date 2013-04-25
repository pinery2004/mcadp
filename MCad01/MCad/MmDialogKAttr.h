#pragma once
#include "afxwin.h"
#include "MhDefParts.h"
#include "MmDialogKAttr.h"

namespace MC
{

// CMmDialogKAttr �_�C�A���O

class CMmDialogKAttr : public CDialog
{
	DECLARE_DYNAMIC(CMmDialogKAttr)

public:
	CMmDialogKAttr(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CMmDialogKAttr();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOGKATTR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

public:
	//	���ޑ����_�C�A���O�\�����N�� (�ʃ^�X�N����N��)
	void MmDialogKAttr();

	//	���ޑ����_�C�A���O�\��
	void MmDialogKAttrInp(
					CWnd*		i_pWnd				// �E�B���h�E�̃C���X�^���X
				);

	//	���ޑ����_�C�A���O�\���t���O�̎擾
	bool GetDispFlg() {
		return m_bDispFlg;
	}

	// ���ޖ��R���{�{�b�N�X�̎擾
	CComboBox* GetCmbBzaiNm() {
		return &m_CmbKbzi1;
	}

	// ���ރ����o�[�R���{�{�b�N�X�̎擾
	CComboBox* GetCmbBzaiMbr() {
		return &m_CmbKbzi2;
	}

	// ���ޑ����R���{�{�b�N�X�̎擾
	CComboBox* GetCmbBzaiAttr(
					int			i_iAttrn);

protected:
	/////////////////////////////////////////////////////////////////////////////
	//	���ޑ����_�C�A���O�\���@�I��
	void CMmDialogKAttr::MmDialogKAttrEnd();

public:
protected:
	CWnd *m_pParent;
protected:
	bool m_bDispFlg;								// �\���t���O	TRUE:�\�����AFALSE:���\��

	CStatic m_sBzi1;
	CStatic m_sBzi2;
	CStatic m_sAttr1;
	CStatic m_sAttr2;
	CStatic m_sAttr3;
	CStatic m_sAttr4;
	CStatic m_sAttr5;
	CStatic m_sAttr6;
	CComboBox m_CmbKbzi1;
	CComboBox m_CmbKbzi2;
	CComboBox m_CmbKAttr1;
	CComboBox m_CmbKAttr2;
	CComboBox m_CmbKAttr3;
	CComboBox m_CmbKAttr4;
	CComboBox m_CmbKAttr5;
	CComboBox m_CmbKAttr6;

public:
	BOOL Create(CWnd * pWnd);
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};

}

