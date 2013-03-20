#pragma once
#include "afxwin.h"

#define	MC_TENKAI_SET	1						// �Z�ˊ֌W�t��
#define	MC_TENKAI_SEL	2						// �Z�ˑI��

// CMmDialogTenkai �_�C�A���O

class CMmDialogTenkai : public CDialog
{
	DECLARE_DYNAMIC(CMmDialogTenkai)

public:
	CMmDialogTenkai(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMmDialogTenkai();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOGTENKAI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	BOOL Create(CWnd* pWnd);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeCombonum();
public:
	CWnd* m_pParent;

	MINT m_modeSel;								// �Z�ˑI�����[�h	MC_TENKAI_SET(1): �Z�ˊ֌W�t��
												//					MC_TENKAI_SEL(2): �Z�ˑI��
	CStatic m_staticMxJuko;
	MINT m_iSelJuko;							// �ݒ�Z��
	MINT m_iRefJuko;							// �Q�ƏZ��

	MC::JTTenkaiPr m_TenkaiPara;

public:
	CButton m_buttonKy1;
	CButton m_ButtonCancel1;

	CComboBox m_comboJuko;

	CEdit m_NmJuko1;
	CEdit m_NmJuko2;
	CEdit m_NmJuko3;
	CEdit m_NmJuko4;
	CEdit m_NmJuko5;
	CEdit m_NmJuko6;
	CEdit m_NmJuko7;
	CEdit m_NmJuko8;
	CEdit* m_pNmJuko( MINT iSel);

	CButton m_H1;
	CButton m_H2;
	CButton m_H3;
	CButton m_H4;
	CButton m_H5;
	CButton m_H6;
	CButton m_H7;
	CButton m_H8;
	CButton* m_pH( MINT iSel);

	CButton m_ButtonJuko1;
	CButton m_ButtonJuko2;
	CButton m_ButtonJuko3;
	CButton m_ButtonJuko4;
	CButton m_ButtonJuko5;
	CButton m_ButtonJuko6;
	CButton m_ButtonJuko7;
	CButton m_ButtonJuko8;
	CButton* m_pButtonJuko( MINT iSel);

	CEdit m_MDJuko1;
	CEdit m_MDJuko2;
	CEdit m_MDJuko3;
	CEdit m_MDJuko4;
	CEdit m_MDJuko5;
	CEdit m_MDJuko6;
	CEdit m_MDJuko7;
	CEdit m_MDJuko8;
	CEdit* m_pMDJuko( MINT iSel);

	CEdit m_DJuko1;
	CEdit m_DJuko2;
	CEdit m_DJuko3;
	CEdit m_DJuko4;
	CEdit m_DJuko5;
	CEdit m_DJuko6;
	CEdit m_DJuko7;
	CEdit m_DJuko8;
	CEdit* m_pDJuko( MINT iSel);

	CEdit m_WJuko1;
	CEdit m_WJuko2;
	CEdit m_WJuko3;
	CEdit m_WJuko4;
	CEdit m_WJuko5;
	CEdit m_WJuko6;
	CEdit m_WJuko7;
	CEdit m_WJuko8;
	CEdit* m_pWJuko( MINT iSel);

	CStatic m_grpJuko1;
	CStatic m_grpJuko2;
	CStatic m_grpJuko3;
	CStatic m_grpJuko4;
	CStatic m_grpJuko5;
	CStatic m_grpJuko6;
	CStatic m_grpJuko7;
	CStatic m_grpJuko8;
	CStatic* m_pgrpJuko( MINT iSel);

	void SetnJuko(								// �W�J���Z�˂�ݒ肵�\��
						MINT	iSel,			// �W�J��Z�˔ԍ��A�܂��́ANULL
						MINT	iRef			// �W�J���Z�˔ԍ��A�܂��́ANULL
				);
	void SetControl();								// �Z���W�J�_�C�A���O�ɏZ���W�J����\��
public:
	afx_msg void OnBnClickedButtonF1();
	afx_msg void OnBnClickedButtonF2();
	afx_msg void OnBnClickedButtonF3();
	afx_msg void OnBnClickedButtonF4();
	afx_msg void OnBnClickedButtonF5();
	afx_msg void OnBnClickedButtonF6();
	afx_msg void OnBnClickedButtonF7();
	afx_msg void OnBnClickedButtonF8();

	afx_msg void OnBnClickedCancel();

	void ChangeEditMd( MINT iJ);
	afx_msg void OnEnChangeEditMd1();
	afx_msg void OnEnChangeEditMd2();
	afx_msg void OnEnChangeEditMd3();
	afx_msg void OnEnChangeEditMd4();
	afx_msg void OnEnChangeEditMd5();
	afx_msg void OnEnChangeEditMd6();
	afx_msg void OnEnChangeEditMd7();
	afx_msg void OnEnChangeEditMd8();

	void SetfocusEditJK( MINT iJ);
	afx_msg void OnEnSetfocusEditJK1();
	afx_msg void OnEnSetfocusEditJK2();
	afx_msg void OnEnSetfocusEditJK3();
	afx_msg void OnEnSetfocusEditJK4();
	afx_msg void OnEnSetfocusEditJK5();
	afx_msg void OnEnSetfocusEditJK6();
	afx_msg void OnEnSetfocusEditJK7();
	afx_msg void OnEnSetfocusEditJK8();

	void ChangeEditD( MINT iJ);
	afx_msg void OnEnChangeEditD1();
	afx_msg void OnEnChangeEditD2();
	afx_msg void OnEnChangeEditD3();
	afx_msg void OnEnChangeEditD4();
	afx_msg void OnEnChangeEditD5();
	afx_msg void OnEnChangeEditD6();
	afx_msg void OnEnChangeEditD7();
	afx_msg void OnEnChangeEditD8();

	void ChangeEditW( MINT iJ);
	afx_msg void OnEnChangeEditW1();
	afx_msg void OnEnChangeEditW2();
	afx_msg void OnEnChangeEditW3();
	afx_msg void OnEnChangeEditW4();
	afx_msg void OnEnChangeEditW5();
	afx_msg void OnEnChangeEditW6();
	afx_msg void OnEnChangeEditW7();
	afx_msg void OnEnChangeEditW8();

	afx_msg void OnBnClickedButtonky1();
	afx_msg void OnBnClickedKankeijk();
	afx_msg void OnBnClickedSelectjk();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

