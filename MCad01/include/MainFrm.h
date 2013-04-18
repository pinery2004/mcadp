// ���� MFC �T���v�� �\�[�X �R�[�h�ł́AMFC Microsoft Office Fluent ���[�U�[ �C���^�[�t�F�C�X 
// ("Fluent UI") �̎g�p���@�������܂��B���̃R�[�h�́AMFC C++ ���C�u���� �\�t�g�E�F�A�� 
// ��������Ă��� Microsoft Foundation Class ���t�@�����X����ъ֘A�d�q�h�L�������g��
// �⊮���邽�߂̎Q�l�����Ƃ��Ē񋟂���܂��B
// Fluent UI �𕡐��A�g�p�A�܂��͔z�z���邽�߂̃��C�Z���X�����͌ʂɗp�ӂ���Ă��܂��B
// Fluent UI ���C�Z���X �v���O�����̏ڍׂɂ��ẮAWeb �T�C�g
// http://msdn.microsoft.com/ja-jp/office/aa973809.aspx ���Q�Ƃ��Ă��������B
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : CMainFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once
#include "MsDefType.h"

//S #define WM_USER100 WM_USER + 100

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMDIChildWnd* OpenView(CDocTemplate *pTemplate);

public:
	MINT		m_iCombo1;										// ���iID
	MINT		m_iCombo2;										// ���@�^��
	MINT		m_iComboInp1;									// ���͓_�敪
	MINT		m_iComboInp2;									// �ۂ߃R�[�h
	MINT		m_iComboInp3;									// �z�u�R�[�h
	MINT		m_iComboPanelNo;								// �p�l���ԍ�

	MINT		m_iSentaku;


protected:  // �R���g���[�� �o�[�p�����o�[
public:
	CMFCRibbonBar				m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages			m_PanelImages;
	CMFCRibbonStatusBar			m_wndStatusBar;

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	class CWnd*				m_pCurView;
	class CMDIChildWnd*		m_pCurFrame;
	afx_msg void OnCbnSelchangeCombo1();						// ���ޖ�
	afx_msg void OnCbnSelchangeCombo2();						// ���@�^��
	afx_msg void OnCbnSelchangeCombo11();						// ���͓_�敪
	afx_msg void OnCbnSelchangeCombo12();						// �ۂ߃R�[�h
	afx_msg void OnCbnSelchangeCombo13();						// �z�u�R�[�h
	afx_msg void OnCbnSelchangeComboPanelNo();
	afx_msg void OnCbnSelchangeComboAttr1();
	afx_msg void OnCbnSelchangeComboAttr2();
	afx_msg void OnCbnSelchangeComboAttr3();
	afx_msg void OnCbnSelchangeComboAttr4();
	afx_msg void OnCbnSelchangeComboAttr5();
	afx_msg void OnCbnSelchangeComboAttr6();
	afx_msg void OnDummy(UINT id);

	afx_msg LRESULT OnRibbonIO( UINT wParam, LONG lParam);

	void SelectCombo1( MINT iCombo1);
	void SelectCombo2( MINT iCombo2);
	void SelectComboInp1( MINT iCombo11);
	void SelectComboInp2( MINT iCombo12);
	void SelectComboInp3( MINT iCombo13);
//	void SeelectComboPanelNo( MINT iComboPanelNo);

	friend CMFCRibbonComboBox* mmpComboBuzai();
	friend CMFCRibbonComboBox* mmpComboMbr();
	friend CMFCRibbonComboBox* mmpComboInpTp();
	friend CMFCRibbonComboBox* mmpComboMarume();
	friend CMFCRibbonComboBox* mmpComboPlcCd();
	friend CMFCRibbonComboBox* mmpComboPanelNo();

	BOOL CreateRibbonBar ();
	afx_msg void OnView1open();
	afx_msg void OnView2open();
	afx_msg void OnView3open();
	afx_msg void OnView4open();
	afx_msg void OnView5open();
	afx_msg void OnClose();
};

extern CMainFrame *z_pMainFrame;								// ���C���t���[�� �|�C���^ (�O���[�o���ϐ�)
