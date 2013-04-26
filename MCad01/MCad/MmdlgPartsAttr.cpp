// MmdlgPartsAttr.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MCad.h"
#include "MmdlgPartsAttr.h"
#include "afxdialogex.h"


// CMmdlgPartsAttr ダイアログ

IMPLEMENT_DYNAMIC(CMmdlgPartsAttr, CDialogEx)

CMmdlgPartsAttr::CMmdlgPartsAttr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMmdlgPartsAttr::IDD, pParent)
{

}

CMmdlgPartsAttr::~CMmdlgPartsAttr()
{
}

void CMmdlgPartsAttr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMmdlgPartsAttr, CDialogEx)
END_MESSAGE_MAP()


// CMmdlgPartsAttr メッセージ ハンドラー
