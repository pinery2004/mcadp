// この MFC サンプル ソース コードでは、MFC Microsoft Office Fluent ユーザー インターフェイス 
// ("Fluent UI") の使用方法を示します。このコードは、MFC C++ ライブラリ ソフトウェアに 
// 同梱されている Microsoft Foundation Class リファレンスおよび関連電子ドキュメントを
// 補完するための参考資料として提供されます。
// Fluent UI を複製、使用、または配布するためのライセンス条項は個別に用意されています。
// Fluent UI ライセンス プログラムの詳細については、Web サイト
// http://msdn.microsoft.com/ja-jp/office/aa973809.aspx を参照してください。
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : CMainFrame クラスのインターフェイス
//

#pragma once
#include "MsDefType.h"

//S #define WM_USER100 WM_USER + 100

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMDIChildWnd* OpenView(CDocTemplate *pTemplate);

public:
	MINT		m_iCombo1;										// 部品ID
	MINT		m_iCombo2;										// 寸法型式
	MINT		m_iComboInp1;									// 入力点区分
	MINT		m_iComboInp2;									// 丸めコード
	MINT		m_iComboInp3;									// 配置コード
	MINT		m_iComboPanelNo;								// パネル番号

	MINT		m_iSentaku;


protected:  // コントロール バー用メンバー
public:
	CMFCRibbonBar				m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages			m_PanelImages;
	CMFCRibbonStatusBar			m_wndStatusBar;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	class CWnd*				m_pCurView;
	class CMDIChildWnd*		m_pCurFrame;
	afx_msg void OnCbnSelchangeCombo1();						// 部材名
	afx_msg void OnCbnSelchangeCombo2();						// 寸法型式
	afx_msg void OnCbnSelchangeCombo11();						// 入力点区分
	afx_msg void OnCbnSelchangeCombo12();						// 丸めコード
	afx_msg void OnCbnSelchangeCombo13();						// 配置コード
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

extern CMainFrame *z_pMainFrame;								// メインフレーム ポインタ (グローバル変数)
