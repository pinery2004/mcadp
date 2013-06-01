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
#include "mnMFCRibbonBar.h"

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

protected:  // コントロール バー用メンバー
public:
	mnMFCRibbonBar				m_wndRibbonBar;
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
	afx_msg void OnCbnSelchangeComboPartsNm();					// 部品名
	afx_msg void OnCbnSelchangeComboMbr();						// 寸法型式
	afx_msg void OnCbnSelchangeComboInpKbn();					// 入力点区分
	afx_msg void OnCbnSelchangeComboMarume();					// 丸めコード
	afx_msg void OnCbnSelchangeComboPlcIzon();					// 配置依存コード
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

	// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
	afx_msg LRESULT OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam);
};
