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

// MCad.h : MCad アプリケーションのメイン ヘッダー ファイル
//
#pragma once
#include "MainFrm.h"

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CMCadApp:
// このクラスの実装については、MCad.cpp を参照してください。
//

class CMCadApp : public CWinAppEx
{
public:
	CMCadApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
// 構造入力用
	MINT m_iKInpSel;											// 構造入力選択
	bool m_bPartsListBuzai;										// 部品表用	部材一覧　チェックボックス
	bool m_bPartsListKanagu;									// 部品表用	金物一覧　チェックボックス
	bool m_bPartsListGohan;										// 部品表用	合板一覧　チェックボックス
	bool m_bPartsAttr1;
	bool m_bPartsAttr2;
	bool m_bPartsAttr3;
	bool m_bPartsAttr4;

public:
	void CreateWnd(
				MINT		iWndSyu,							// (I  ) ウィンドウ種類
				MINT		iZuSyu,								// (I  ) 図種類
				MINT		iKai,								// (I  ) 階
				MINT		iZuNum								// (I  ) 図番号
				);

// 実装
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

//	afx_msg void OnFileNew();
	void OnFileNew();
	afx_msg void OnFileOpen();

	afx_msg void OnMainMenuP( UINT nID);
	afx_msg void OnUpdateMainMenuP(CCmdUI *pCmdUI);
	afx_msg void OnSubMenuP( UINT nID);
	afx_msg void OnUpdateSubMenuP(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadio1f();
	afx_msg void OnUpdateRadio1f(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadio2f();
	afx_msg void OnUpdateRadio2f(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadio3f();
	afx_msg void OnUpdateRadio3f(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioYane();
	afx_msg void OnUpdateRadioYane(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioTenjo();
	afx_msg void OnUpdateRadioTenjo(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioTairyoku();
	afx_msg void OnUpdateRadioTairyoku(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioKabe();
	afx_msg void OnUpdateRadioKabe(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioYuka();
	afx_msg void OnUpdateRadioYuka(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioKoya();
	afx_msg void OnUpdateRadioKoya(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioDodai();
	afx_msg void OnUpdateRadioDodai(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioKiso();
	afx_msg void OnUpdateRadioKiso(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioBuzai();
	afx_msg void OnUpdateRadioBuzai(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioKanagu();
	afx_msg void OnUpdateRadioKanagu(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioPanel();
	afx_msg void OnUpdateRadioPanel(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioOther();
	afx_msg void OnUpdateRadioOther(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioSel1();
	afx_msg void OnUpdateRadioSel1(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioSel2();
	afx_msg void OnUpdateRadioSel2(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioSel3();
	afx_msg void OnUpdateRadioSel3(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedChukiDelete();
	afx_msg void OnUpdateChukiDelete(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedChukiMove();
	afx_msg void OnUpdateChukiMove(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedChukiChange();
	afx_msg void OnUpdateChukiChange(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckBuzai();
	afx_msg void OnUpdateCheckBuzai(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckKanagu();
	afx_msg void OnUpdateCheckKanagu(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckGohan();
	afx_msg void OnUpdateCheckGohan(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckAttr1();
	afx_msg void OnUpdateCheckAttr1(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckAttr2();
	afx_msg void OnUpdateCheckAttr2(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckAttr3();
	afx_msg void OnUpdateCheckAttr3(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedCheckAttr4();
	afx_msg void OnUpdateCheckAttr4(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedPanelBefore();
	afx_msg void OnUpdatePanelBefore(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedPanelNext();
	afx_msg void OnUpdatePanelNext(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedPanelAll();
	afx_msg void OnUpdatePanelAll(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioJyuuko();
	afx_msg void OnUpdateRadioJyuuko(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioJyuuto();
	afx_msg void OnUpdateRadioJyuuto(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioBukken();
	afx_msg void OnUpdateRadioBukken(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioSYane();
	afx_msg void OnUpdateRadioSYane(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioSikiti();
	afx_msg void OnUpdateRadioSikiti(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedRadioHekiryou();
	afx_msg void OnUpdateRadioHekiryou(CCmdUI *pCmdUI);
};

extern CMCadApp z_MCadApp;
