#pragma once
#include "afxwin.h"


// CMmDialogOpt �_�C�A���O

class CMmDialogOpt : public CDialog
{
	DECLARE_DYNAMIC(CMmDialogOpt)

public:
	CMmDialogOpt(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMmDialogOpt();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOGOPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
public:
	CWnd *m_pParent;

	DECLARE_MESSAGE_MAP()
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckoption0();						// �W����p���I�t
	afx_msg void OnBnClickedCheckoption1();						// �I�v�V�����@�P
	afx_msg void OnBnClickedCheckoption2();						// �I�v�V�����@�Q
	afx_msg void OnBnClickedCheckoption3();						// �I�v�V�����@�R
	afx_msg void OnBnClickedCheckoption4();						// �I�v�V�����@�S
	afx_msg void OnBnClickedCheckoption5();						// �I�v�V�����@�T
	afx_msg void OnBnClickedCheckoption6();						// �I�v�V�����@�U
	afx_msg void OnBnClickedCheckoption7();						// �I�v�V�����@�V
	afx_msg void OnBnClickedCheckoption8();						// �I�v�V�����@�W
	afx_msg void OnBnClickedCheckoption9();						// �I�v�V�����@�X
	afx_msg void OnBnClickedCheckoption10();					// �I�v�V�����P�O
	virtual BOOL OnInitDialog();
	CButton m_chkBox0;											// �W����p���I�t
	CButton m_chkBox1;											// �I�v�V�����@�P
	CButton m_chkBox2;											// �I�v�V�����@�Q
	CButton m_chkBox3;											// �I�v�V�����@�R
	CButton m_chkBox4;											// �I�v�V�����@�S
	CButton m_chkBox5;											// �I�v�V�����@�T
	CButton m_chkBox6;											// �I�v�V�����@�U
	CButton m_chkBox7;											// �I�v�V�����@�V
	CButton m_chkBox8;											// �I�v�V�����@�W
	CButton m_chkBox9;											// �I�v�V�����@�X
	CButton m_chkBox10;											// �I�v�V�����P�O
public:
	BOOL Create(CWnd* pWnd);
public:
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
