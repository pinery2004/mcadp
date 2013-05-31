#pragma once


// mnMFCRibbonBar

class mnMFCRibbonBar : public CMFCRibbonBar
{
	int m_LastActiveCategory;


	DECLARE_DYNAMIC(mnMFCRibbonBar)

public:
	mnMFCRibbonBar();
	virtual ~mnMFCRibbonBar();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()

public:
	// リボンバーのカテゴリ変更メッセージの取得用に追加したがメッセージ受けられず
	afx_msg LRESULT OnAfxWmOnChangeRibbonCategory(WPARAM wParam, LPARAM lParam);
};


enum	ComboTp {
	MSET_RIBBON_BAR = 1,			// リボンバーの部品選択用項目( 組、分類、部品タイプ、寸法型式)を設定する
	MSET_INPUT_KUBUN_CD,			// カレントの入力点区分を設定し、入力点区分選択用のコンボボックスに表示する
	MSET_INPUT_MARUME_CD,			// カレントの丸めコードを設定し、丸めコード用のコンボボックスに表示する
	MSET_INPUT_PLACE_CD,			// カレントの配置依存コードを設定し、配置依存コード用のコンボボックスに表示する
	MSET_COMBO_ATTRR,				// 属性値入力用コンボボックスに実数値を表示する
	MGET_PARTS_ATTRA,				// 部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
//U	未使用	MSET_COMBO_PARTS,				// 部材属性入力用コンボボックスの設定
	MSET_COMBO_PANELNO,				// カレントのパネル番号選択項目番号を設定し　コンボボックスにパネル番号を表示する

	MINIT_COMBO_ATTR				// 属性値入力モードに沿った部材属性入力用リボンバーの項目を設定する
};




