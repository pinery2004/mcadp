#pragma once


// CMmdlgPartsAttr �_�C�A���O

class CMmdlgPartsAttr : public CDialogEx
{
	DECLARE_DYNAMIC(CMmdlgPartsAttr)

public:
	CMmdlgPartsAttr(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CMmdlgPartsAttr();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MMDLGPARTSATTR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
