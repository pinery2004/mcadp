#pragma once


// CMmdlgPartsAttr ダイアログ

class CMmdlgPartsAttr : public CDialogEx
{
	DECLARE_DYNAMIC(CMmdlgPartsAttr)

public:
	CMmdlgPartsAttr(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CMmdlgPartsAttr();

// ダイアログ データ
	enum { IDD = IDD_MMDLGPARTSATTR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
