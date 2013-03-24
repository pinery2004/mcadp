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
	bool m_bPtsListBuzai;										// 部品表用	部材一覧　チェックボックス
	bool m_bPtsListKanagu;										// 部品表用	金物一覧　チェックボックス
	bool m_bPtsListGohan;										// 部品表用	合板一覧　チェックボックス

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

	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();

	afx_msg void OnMainMenuP( UINT nID);
	afx_msg void OnUpdateMainMenuP(CCmdUI *pCmdUI);
	afx_msg void OnSubMenuP( UINT nID);
	afx_msg void OnUpdateSubMenuP(CCmdUI *pCmdUI);
};

extern CMCadApp g_theApp;
