#pragma once
#include "resource.h"

// CMmDialogPtsEdit �_�C�A���O

class CMmDialogPtsEdit : public CDialog
{
	DECLARE_DYNAMIC(CMmDialogPtsEdit)

public:
	CMmDialogPtsEdit(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMmDialogPtsEdit();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOGPARTSEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	BOOL Create(CWnd* pWnd);
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk();
public:
	CWnd* m_pParent;
public:
public:
	int m_nFixCols;
public:
	int m_nFixRows;
public:
	int m_nCols;
public:
	int m_nRows;
public:
	BOOL m_bHeaderSort;
public:
	CGridCtrl m_GridPtLst1;
};
