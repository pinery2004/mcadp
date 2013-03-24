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

// MCad.h : MCad �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once
#include "MainFrm.h"

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CMCadApp:
// ���̃N���X�̎����ɂ��ẮAMCad.cpp ���Q�Ƃ��Ă��������B
//

class CMCadApp : public CWinAppEx
{
public:
	CMCadApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
// �\�����͗p
	MINT m_iKInpSel;											// �\�����͑I��
	bool m_bPtsListBuzai;										// ���i�\�p	���ވꗗ�@�`�F�b�N�{�b�N�X
	bool m_bPtsListKanagu;										// ���i�\�p	�����ꗗ�@�`�F�b�N�{�b�N�X
	bool m_bPtsListGohan;										// ���i�\�p	���ꗗ�@�`�F�b�N�{�b�N�X

public:
	void CreateWnd(
				MINT		iWndSyu,							// (I  ) �E�B���h�E���
				MINT		iZuSyu,								// (I  ) �}���
				MINT		iKai,								// (I  ) �K
				MINT		iZuNum								// (I  ) �}�ԍ�
				);

// ����
	UINT  m_nAppLook;

	CMainFrame* m_pMainFrame;
	CMultiDocTemplate* m_pDocTemplate1;
	CMultiDocTemplate* m_pDocTemplate2;
	CMultiDocTemplate* m_pDocTemplate3;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnView1On();
	afx_msg void OnView2On();
	afx_msg void OnView3On();
	afx_msg void OnView4On();
	afx_msg void OnView5On();
	afx_msg void OnView1Off();
	afx_msg void OnView2Off();
	afx_msg void OnView3Off();
	afx_msg void OnView4Off();
	afx_msg void OnView5Off();

	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();

	afx_msg void OnMainMenuP( UINT nID);
	afx_msg void OnUpdateMainMenuP(CCmdUI *pCmdUI);
	afx_msg void OnSubMenuP( UINT nID);
	afx_msg void OnUpdateSubMenuP(CCmdUI *pCmdUI);
};

extern CMCadApp g_theApp;
