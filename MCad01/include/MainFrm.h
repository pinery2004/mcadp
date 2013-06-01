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
#include "mnMFCRibbonBar.h"

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

protected:  // �R���g���[�� �o�[�p�����o�[
public:
	mnMFCRibbonBar				m_wndRibbonBar;
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
	afx_msg void OnCbnSelchangeComboPartsNm();					// ���i��
	afx_msg void OnCbnSelchangeComboMbr();						// ���@�^��
	afx_msg void OnCbnSelchangeComboInpKbn();					// ���͓_�敪
	afx_msg void OnCbnSelchangeComboMarume();					// �ۂ߃R�[�h
	afx_msg void OnCbnSelchangeComboPlcIzon();					// �z�u�ˑ��R�[�h
	afx_msg void OnCbnSelchangeComboPanelNo();
	afx_msg void OnDummy(UINT id);

	afx_msg LRESULT OnRibbonIO( UINT wParam, LONG lParam);
	afx_msg LRESULT OnRibbonCategoryChanged( UINT wParam, LONG lParam);
	afx_msg LRESULT OnWindow( UINT wParam, LONG lParam);

	void SelectComboPartsNm( MINT iComboPartsNm);
	void SelectComboMbr( MINT iComboMbr);
	void SelectComboInp1( MINT iComboInpKbn);
	void SelectComboInp2( MINT iComboMarume);
	void SelectComboInp3( MINT iComboPlcIzon);
//	void SeelectComboPanelNo( MINT iComboPanelNo);

	friend CMFCRibbonComboBox* mmpComboBuzai();
	friend CMFCRibbonComboBox* mmpComboMbr();
	friend CMFCRibbonComboBox* mmpComboInpTp();
	friend CMFCRibbonComboBox* mmpComboMarume();
	friend CMFCRibbonComboBox* mmpComboPlcIzonCd();
	friend CMFCRibbonComboBox* mmpComboPanelNo();

	BOOL CreateRibbonBar ();
	afx_msg void OnView1open();
	afx_msg void OnView2open();
	afx_msg void OnView3open();
	afx_msg void OnView4open();
	afx_msg void OnView5open();
	afx_msg void OnClose();

	// ���{���o�[�̃J�e�S���ύX���b�Z�[�W�̎擾�p�ɒǉ����������b�Z�[�W�󂯂�ꂸ
	afx_msg LRESULT OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam);
};
