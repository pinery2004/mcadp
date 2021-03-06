//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsFile.cpp
//
//		
//
//
//  K.Matsu           11/17/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "afxdlgs.h"


// CChildView1 ウィンドウ

namespace MC
{

// OnInitDialogのタイミングで詳細表示のメッセージを発するために
// クラスの継承を使用して新しいクラスを作成する
class MsFileDialog : public CFileDialog
{
public:
	explicit MsFileDialog(
					BOOL	bOpenFileDialog,
					LPCTSTR lpszDefExt = NULL,
					LPCTSTR lpszFileName = NULL,
					DWORD	dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					LPCTSTR lpszFilter = NULL,
					CWnd*	pParentWnd = NULL,
					DWORD	dwSize = 0
				);
	static void DispFileDlg(
					BOOL		i_bDialogType,		// ダイアログタイプ　TRUE:読み込み、FAULT:保存
					CWnd*		i_pWnd,				// 親ウィンドウまたはオーナー ウィンドウへのポインタ
					MCHAR*		i_sInitFilePath,	// 初期設定ファイルパス
					MCHAR*		o_sSelFilePath,		// 選択ファイルパス
					int			i_iszSelFilePath,	// 選択ファイルパスバッファサイズ(文字数)
					MCHAR*		i_sFilters			// ファイルを特定するためのフィルタ or NULL
				);
public:
	virtual BOOL OnInitDialog();
};

MsFileDialog::MsFileDialog(
					BOOL	i_bOpenFileDialog,		// TRUE: ファイルを開く, FALSE: ファイル名を付けて保存
					LPCTSTR i_lpszDefExt,			// 既定のファイル拡張子 or NULL (拡張子を省略した入力時に付加する拡張子)
					LPCTSTR i_lpszFileName,			// 初期表示されるファイル名 or NULL
					DWORD	i_dwFlags,				// ダイアログ ボックスをカスタマイズするためのフラグ
					LPCTSTR i_lpszFilter,			// ファイルを特定するためのフィルタ
					CWnd*	i_pParentWnd,			// 親ウィンドウまたはオーナー ウィンドウへのポインタ
					DWORD	i_dwSize				// OPENFILENAME 構造体のサイズ または 0
				)
				  : CFileDialog( i_bOpenFileDialog, i_lpszDefExt, i_lpszFileName, 
								 i_dwFlags, i_lpszFilter, i_pParentWnd, i_dwSize)
{
};

//	詳細表示のボタンを押す操作をプログラムで行う
//
BOOL MsFileDialog::OnInitDialog()
{
    CFileDialog::OnInitDialog();

	MINT wmCommand = 40964;										// 詳細表示Id
    CWnd *parent = GetParent();
    if ( parent != NULL ) {
       parent->PostMessage(WM_COMMAND, wmCommand, NULL);
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//	読み込み用ファイル選択ダイアログを表示する
void mslib::LoadFileDlg(
					CWnd*		i_pWnd,				// 親ウィンドウまたはオーナー ウィンドウへのポインタ
					MCHAR*		i_sInitFilePath,	// 初期設定ファイルパス
					MCHAR*		o_sSelFilePath,		// 選択ファイルパス
					int			i_iszSelFilePath,	// 選択ファイルパスバッファサイズ(文字数)
					MCHAR*		i_sFilters			// ファイルを特定するためのフィルタ or NULL
				)
{
	MsFileDialog::DispFileDlg( TRUE, i_pWnd, i_sInitFilePath, o_sSelFilePath, i_iszSelFilePath, i_sFilters);
}

///////////////////////////////////////////////////////////////////////////////
//	保存用ファイル選択ダイアログを表示する
void mslib::SaveFileDlg(
					CWnd*		i_pWnd,				// 親ウィンドウまたはオーナー ウィンドウへのポインタ
					MCHAR*		i_sInitFilePath,	// 初期設定ファイルパス
					MCHAR*		o_sSelFilePath,		// 選択ファイルパス
					int			i_iszSelFilePath,	// 選択ファイルパスバッファサイズ(文字数)
					MCHAR*		i_sFilters			// ファイルを特定するためのフィルタ or NULL
				)
{
	MsFileDialog::DispFileDlg( FALSE, i_pWnd, i_sInitFilePath, o_sSelFilePath, i_iszSelFilePath, i_sFilters);
}
#define	NCHEXP	10
///////////////////////////////////////////////////////////////////////////////
//	ファイル選択ダイアログを表示する
void MsFileDialog::DispFileDlg(
					BOOL		bDialogType,		// ダイアログタイプ　TRUE:読み込み、FAULT:保存
					CWnd*		i_pWnd,				// 親ウィンドウまたはオーナー ウィンドウへのポインタ
					MCHAR*		i_sInitFilePath,	// 初期設定ファイルパス
					MCHAR*		o_sSelFilePath,		// 選択ファイルパスバッファ
					int			i_iszSelFilePath,	// 選択ファイルパスバッファサイズ(文字数)
					MCHAR*		i_sFilters			// ファイルを特定するためのフィルタ or NULL
				)
{
	MCHAR*	psFilters; 
	MCHAR*	psDefExt; 
	MCHAR*	psInitFilePath; 

	MCHAR	sFilters[] = Mstr( "MyType Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	MCHAR	sDefExt[] = Mstr( "txt");
	MCHAR	sDefExtI[NCHEXP];
	MCHAR	sInitFilePath[] = Mstr( "D:\\Temp\\*.txt");

	MINT	iLen;
	MINT	iC;

	psFilters = ( ( i_sFilters) ? i_sFilters : sFilters);

	if ( i_sInitFilePath) {
		psInitFilePath = i_sInitFilePath;

		iLen = (MINT)Mstrlen( i_sInitFilePath);
		for ( iC = iLen - 1; iC >= 0 && i_sInitFilePath[iC] != '.'; iC--);
		if ( iC >= 0 ) {
			if ( iLen - iC < NCHEXP) 
				Mstrcpy_s( sDefExtI, &i_sInitFilePath[iC + 1]);
			psDefExt = sDefExt;
		} else {
			psDefExt = NULL;
		}
	} else {
		psInitFilePath = sInitFilePath;
		psDefExt = sDefExt;
	}

	MsFileDialog fileDlg( bDialogType, psDefExt, psInitFilePath,
				OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, psFilters, i_pWnd);

	if( fileDlg.DoModal() == IDOK )	{
		CString pathName = fileDlg.GetPathName();
		Mstrcpy_s( o_sSelFilePath, i_iszSelFilePath, pathName);

	} else {
		o_sSelFilePath[0] = 0;

	}
}

///////////////////////////////////////////////////////////////////////////////
// フォルダ選択ダイアログプロシージャ
int CALLBACK MsForFolderDlg_Callback(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

/////////////////////////////////////////////////////////////////////////////
//	フォルダ選択ダイアログを表示する
void mslib::ForFolderDlg( 
					HWND		i_hWnd,				// (I  ) 親ウィンドウのハンドル
					MCHAR*		i_sCaptionStr,		// (I  ) 説明の文字列
					MCHAR*		i_sInitFldrPath,	// (I  ) 初期設定フォルダパス
					MCHAR*		o_sSelFldrPath,		// (I  ) 選択フォルダパス
					int			i_iszSelFldrPath	// 選択フォルダパス配列サイズ(文字数)
					)
{
	BROWSEINFO		stBInfo;
    LPITEMIDLIST    pidlRoot;      // ブラウズのルートPIDL
    LPITEMIDLIST    pidlBrowse;    // ユーザーが選択したPIDL

    // < ブラウズ情報受け取りバッファ領域の確保 >
	MCHAR			sPutFolder[MAX_PATH];
    //LPSTR           psPutFolder;
    //if ( (psPutFolder = (LPSTR) lpMalloc->Alloc(_MAX_PATH)) == NULL)
    //    return;

    // < IMallocインタフェースの取得 >
	LPMALLOC	pMalloc;
	HRESULT hr = SHGetMalloc( &pMalloc);
	if( FAILED( hr)) return;

	BOOL		bRes;

    // ダイアログ表示時のルートフォルダのPIDLを取得
    // ※以下はデスクトップをルートとしている。デスクトップをルートとする
    //   場合は、単に bi.pidlRoot に０を設定するだけでもよい。その他の特
    //   殊フォルダをルートとする事もできる。詳細はSHGetSpecialFolderLoca
    //   tionのヘルプを参照の事。
	//		CSIDL_DESKTOP	デスクトップ 
	//		CSIDL_PROGRAMS	プログラム 
	//		CSIDL_CONTROLS	コントロールパネル 
	//		CSIDL_PRINTERS	プリンタ 
	//		CSIDL_PERSONAL	My Documents 
	//		CSIDL_FAVORITES お気に入り 
	//		CSIDL_STARTUP	スタートアップ 
	//		CSIDL_RECENT	Recent 
	//		CSIDL_SENDTO	SendTo 
	//		CSIDL_BITBUCKET ゴミ箱 
	//		CSIDL_STARTMENU スタートメニュー 
	//		CSIDL_DRIVES	マイコンピュータ 
	//		CSIDL_NETWORK	ネットワークコンピュータ 
	//		CSIDL_NETHOOD	NetHood 
	//		CSIDL_FONTS		Fonts 
	//		CSIDL_TEMPLATES ShellNew 

    if ( !SUCCEEDED(SHGetSpecialFolderLocation( i_hWnd, CSIDL_DESKTOP, &pidlRoot))) { 
//        pMalloc->Free(psPutFolder);
        return;
    }
 
	//　構造体を初期化します。
	stBInfo.hwndOwner		= i_hWnd;							// 表示するダイアログの親ウィンドウのハンドル
	stBInfo.pidlRoot		= pidlRoot;							// ルートフォルダ         //検索開始点(nullならMyComputer)
	stBInfo.pszDisplayName	= sPutFolder;						// 選択されているフォルダ名
	stBInfo.lpszTitle		= i_sCaptionStr;					// 説明の文字列
	stBInfo.ulFlags			= BIF_RETURNONLYFSDIRS;				// 表示フラグ
																//		BIF_RETURNONLYFSDIRS	特殊フォルダを表示しない 
																//		BIF_DONTGOBELOWDOMAIN	特殊フォルダを表示する 
																//		BIF_STATUSTEXT			選択されたフォルダをテキストに表示 
																//		BIF_BROWSEINCLUDEFILES	全てのファイルを表示す 
	stBInfo.lpfn			= MsForFolderDlg_Callback;			// ダイアログプロシージャへのポインタ
	stBInfo.lParam			= (LPARAM)i_sInitFldrPath;			// プロシージャに送るパラメーター

	stBInfo.iImage			= 0;

	// < ダイアログボックスを表示する >
	pidlBrowse = SHBrowseForFolder( &stBInfo );

	//　pidlBrowseにはそのフォルダを表すアイテムＩＤリストへのポインタが
	//　入っている。sPutFolderには選択されたフォルダ名（非フルパス）だけ
	//　しか入っていないので、このポインタを利用する。

	if( pidlBrowse != NULL )	{
		//　フルパスを取得します。
		bRes = SHGetPathFromIDList( pidlBrowse, sPutFolder );
		if( bRes) {
			Mstrcpy_s( o_sSelFldrPath, i_iszSelFldrPath, sPutFolder);
		}
        //PIDLを解放する
		//::CoTaskMemFree( pidlBrowse );
        pMalloc->Free( pidlBrowse);
	} else {
		o_sSelFldrPath[0] = 0;
	}
    // クリーンアップ処理
    pMalloc->Free(pidlRoot); 
//    lpMalloc->Free(psPutFolder);
    pMalloc->Release();
}

///////////////////////////////////////////////////////////////////////////////
// フォルダ選択ダイアログプロシージャ
static int CALLBACK MsForFolderDlg_Callback(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if( uMsg == BFFM_INITIALIZED) {
        SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}

} // namespace MC
