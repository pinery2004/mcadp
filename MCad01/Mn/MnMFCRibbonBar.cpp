// mnMFCRibbonBar.cpp : 実装ファイル
//

#include "stdafx.h"
#include "mnMFCRibbonBar.h"
#include "MCad.h"
#include "MmCmdMsg.h"

// mnMFCRibbonBar

IMPLEMENT_DYNAMIC(mnMFCRibbonBar, CMFCRibbonBar)

mnMFCRibbonBar::mnMFCRibbonBar()
{
	m_LastActiveCategory = 0;
}

mnMFCRibbonBar::~mnMFCRibbonBar()
{
}

BEGIN_MESSAGE_MAP(mnMFCRibbonBar, CMFCRibbonBar)
	// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
	ON_MESSAGE(AFX_WM_ON_CHANGE_RIBBON_CATEGORY, &mnMFCRibbonBar::OnAfxWmOnChangeRibbonCategory)
END_MESSAGE_MAP()

// mnMFCRibbonBar メッセージ ハンドラー

// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
afx_msg LRESULT mnMFCRibbonBar::OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BOOL mnMFCRibbonBar::PreTranslateMessage( MSG* pMsg)
{
	// リボンバーのカテゴリ変更メッセージ( WM_MYMESSAGE_RIBBONCATEGORYCHANGED)を発生
	//If command was finishing a click
	if( pMsg->message == WM_LBUTTONUP && pMsg->wParam == 0)
	{
		//Allow ribbon to handle itself first
		BOOL result = CMFCRibbonBar::PreTranslateMessage( pMsg);

		//Get new active tab
		int activeTab = GetCategoryIndex( GetActiveCategory());

		//If tab has changed, forward message
		if( activeTab != m_LastActiveCategory)
		{
			//forward message to parent
			::SendMessage( GetParentFrame()->GetSafeHwnd(), WM_MYMESSAGE_RIBBONCATEGORYCHANGED, activeTab, 0);
			m_LastActiveCategory = activeTab;
		}
		return result;
	}

	//Otherwise handle like normal
	return CMFCRibbonBar::PreTranslateMessage( pMsg);
}
