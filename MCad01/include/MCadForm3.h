#pragma once


// CMCadForm3 �t�H�[�� �r���[

class CMCadForm3 : public CFormView
{
	DECLARE_DYNCREATE(CMCadForm3)

protected:
	CMCadForm3();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~CMCadForm3();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


