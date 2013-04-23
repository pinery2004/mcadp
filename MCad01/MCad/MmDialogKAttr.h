#pragma once
#include "afxwin.h"
#include "MhDefParts.h"
#include "MmDialogKAttr.h"

namespace MC
{

///////////////////////////////////////////////////////////////////////////////
////	部材属性ダイアログ表示を起動
//void MmDialogKAttr();
//
///////////////////////////////////////////////////////////////////////////////
////	部材属性ダイアログ表示　入力
//void MmDialogKAttrInp(
//						CWnd*		pWnd			// (I  ) ウィンドウのインスタンス
//				);
//
///////////////////////////////////////////////////////////////////////////////
////	部材属性ダイアログ表示　終了
//void MmDialogKAttrEnd();
//
//}

// CMmDialogKAttr ダイアログ

class CMmDialogKAttr : public CDialog
{
	DECLARE_DYNAMIC(CMmDialogKAttr)

public:
	CMmDialogKAttr(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMmDialogKAttr();

// ダイアログ データ
	enum { IDD = IDD_DIALOGKATTR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

public:
	//	部材属性ダイアログ表示を起動 (別タスクから起動)
	void MmDialogKAttr();

	//	部材属性ダイアログ表示
	void MmDialogKAttrInp(
					CWnd*		i_pWnd				// ウィンドウのインスタンス
				);

	//	部材属性ダイアログ表示フラグの取得
	bool GetDispFlg() {
		return m_bDispFlg;
	}

	// 部材名コンボボックスの取得
	CComboBox* GetCmbBzaiNm() {
		return &m_CmbKbzi1;
	}

	// 部材メンバーコンボボックスの取得
	CComboBox* GetCmbBzaiMbr() {
		return &m_CmbKbzi2;
	}

	// 部材属性コンボボックスの取得
	CComboBox* GetCmbBzaiAttr(
					int			i_iAttrn);

protected:
	/////////////////////////////////////////////////////////////////////////////
	//	部材属性ダイアログ表示　終了
	void CMmDialogKAttr::MmDialogKAttrEnd();

//	////////////////////////////////////////////////////////////////////////////
//	// 部品入力用、ダイアログの部品選択用項目を設定する
//	//		組、分類、部品タイプ、寸法型式
//public:
//	void SetRibbonBarEnt( 							// ステイタス 0:正常 -1:エラー
//					MPKOSEI		i_irbKumi,			// 構造	組
//					MPBUNRUI	i_irbBunrui,		// 構造	分類
//					MCHAR*		i_crbPartsSpec,		// 部品種類
//					MCHAR*		i_crbMbr = NULL		// 部品メンバー()
//				)
//	{
//		m_iRBKosei	= i_irbKumi;
//		m_iRBBunrui = i_irbBunrui;
//		m_sRBBuhin	= i_crbPartsSpec;
//		m_sRBMbr	= i_crbMbr;
//
//		MmDialogKAttr();
//	}


public:
protected:
	CWnd *m_pParent;
protected:
	bool m_bDispFlg;								// 表示フラグ	TRUE:表示中、FALSE:無表示

	////////////////////////////////////////////////////////////////////////////
	// 部品入力用、ダイアログの部品選択用項目を設定する
	//		組、分類、部品タイプ、寸法型式
	MPKOSEI		m_iRBKosei;							// 構造	構成
	MPBUNRUI	m_iRBBunrui;						// 構造	分類
	MCHAR*		m_sRBBuhin;							// 部品
	MCHAR*		m_sRBMbr;							// 部品メンバー

	CStatic m_sBzi1;
	CStatic m_sBzi2;
	CStatic m_sAttr1;
	CStatic m_sAttr2;
	CStatic m_sAttr3;
	CStatic m_sAttr4;
	CStatic m_sAttr5;
	CStatic m_sAttr6;
	CComboBox m_CmbKbzi1;
	CComboBox m_CmbKbzi2;
	CComboBox m_CmbKAttr1;
	CComboBox m_CmbKAttr2;
	CComboBox m_CmbKAttr3;
	CComboBox m_CmbKAttr4;
	CComboBox m_CmbKAttr5;
	CComboBox m_CmbKAttr6;

public:
	BOOL Create(CWnd * pWnd);
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};

//namespace MC
//{
//US	extern class CMmDialogKAttr* z_pDlgKAttr;
extern class CMmDialogKAttr z_DlgKAttr;
}

