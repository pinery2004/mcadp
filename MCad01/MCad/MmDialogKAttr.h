#pragma once
#include "afxwin.h"
#include "MhDefParts.h"
#include "MmDialogKAttr.h"

// CMmDialogKAttr ダイアログ

class CMmDialogKAttr : public CDialogEx
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
	//	部材属性ダイアログ表示を起動 (別タスクからの起動用)
	void MmDialogKAttr();

	//	部材属性ダイアログ表示
	void MmDialogKAttrDisp(
					CWnd*		i_pWnd				// ウィンドウのインスタンス
				);

	//	部材属性ダイアログ表示フラグの取得
	bool GetDispFlg() {
		return m_bDispFlg;
	}

	// 部材名コンボボックスの取得
	CComboBox* GetCmbBzaiNm() {
		return &m_CmbKPartsNm;
	}

	// 部材メンバーコンボボックスの取得
	CComboBox* GetCmbBzaiMbr() {
		return &m_CmbKPartsMbr;
	}

	// 部材属性コンボボックスの取得
	CComboBox* GetCmbBzaiAttr(
					int			i_iAttrn);

protected:
	/////////////////////////////////////////////////////////////////////////////
	//	部材属性ダイアログ表示　終了
	void CMmDialogKAttr::MmDialogKAttrEnd() {
		m_bDispFlg = false;
	}

protected:
	CWnd *m_pParent;
	bool m_bDispFlg;								// 表示フラグ	TRUE:表示中、FALSE:無表示

	CStatic m_sPartsNm;
	CStatic m_sPartsMbr;
	CStatic m_sAttr1;
	CStatic m_sAttr2;
	CStatic m_sAttr3;
	CStatic m_sAttr4;
	CStatic m_sAttr5;
	CStatic m_sAttr6;
	CComboBox m_CmbKPartsNm;
	CComboBox m_CmbKPartsMbr;
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

	afx_msg void OnCbnSelchangeCmbkPartsNm();
	afx_msg void OnCbnSelchangeCmbkPartsMbr();
	afx_msg void OnCbnSelchangeCmbkAttr1();
	afx_msg void OnCbnSelchangeCmbkAttr2();
	afx_msg void OnCbnSelchangeCmbkAttr3();
	afx_msg void OnCbnSelchangeCmbkAttr4();
	afx_msg void OnCbnSelchangeCmbkAttr5();
	afx_msg void OnCbnSelchangeCmbkAttr6();
	afx_msg void OnCbnEditchangeCmbkAttr1();
};
