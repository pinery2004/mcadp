// MCadForm3.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MCad.h"
#include "MCadForm3.h"


// CMCadForm3

IMPLEMENT_DYNCREATE(CMCadForm3, CFormView)

CMCadForm3::CMCadForm3()
	: CFormView(CMCadForm3::IDD)
{

}

CMCadForm3::~CMCadForm3()
{
}

void CMCadForm3::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCadForm3, CFormView)
END_MESSAGE_MAP()


// CMCadForm3 診断

#ifdef _DEBUG
void CMCadForm3::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMCadForm3::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMCadForm3 メッセージ ハンドラー
