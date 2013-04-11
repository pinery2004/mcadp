#pragma once

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	汎用関数
//
typedef MINT MAryCmpFunc(
				const	void*	Arg1,
				const	void*	Arg2
				);

////////////////////////////////////////////////////////////////////////////
//【機能】クイックソート

void MsQSort(									// ｽﾃｰﾀｽ
						void*	i_base,			// 並び替える配列の先頭
						MINT	i_num,			// 配列の要素数
						MINT	i_width,		// 配列の要素サイズ(バイト数)
						MAryCmpFunc* i_AryCmpFunc// 比較関数
				);

////////////////////////////////////////////////////////////////////////////
//【機能】デフォルトの比較関数
//【返値】 < 0 : array1  < array2
//		  == 0 : array1 == array2
//		   > 0 : array1  > array2 

static MINT AryCompare(							// ｽﾃｰﾀｽ
				const	void*	i_array1,		// ﾃﾞｰﾀ1
				const	void*	i_array2		// ﾃﾞｰﾀ2
				);

////////////////////////////////////////////////////////////////////////////
//【機能】CArray を使用したクイックソートと検索

// Sample
class CData{
public:
	long	lgKey;
	CString	sNm;
	long	lgN;
};


template <class T> 
class CARRAY : public CArray <T, T&> {
	static int Compare( const void *, const void *);
public:
	void Sort() { qsort( GetData(), GetSize(), sizeof( T), Compare);};
	T * Search( T PartsInfo)
	{ return ( T *)bsearch( &PartsInfo, GetData(), GetSize(), sizeof( T), Compare);};
};


////////////////////////////////////////////////////////////////////////////
//【機能】現在時刻を取得する
//【返値】MTIME型　現在時刻

MTIME MsGetCurrentTime();

////////////////////////////////////////////////////////////////////////////
//【機能】時刻を比較する
//【返値】比較結果 -1 : cTime1が早い
//					0 : 同一
//					1 : cTime2が早い

MINT MsCmpTime(
						MTIME	i_cTime1,		// 比較対象時間1
						MTIME	i_cTime2		// 比較対象時間2
				);

////////////////////////////////////////////////////////////////////////////
//【機能】MTIME型時刻に変換する
//【返値】> 0 : MTIME型　現在時刻
//		  < 0 : エラー

MTIME MsMTime(
						MINT	i_nYear,		// 年
						MINT	i_nMonth,		// 月
						MINT	i_nDay,			// 日
						MINT	i_nHour,		// 時
						MINT	i_nMin,			// 分
						MINT	i_nSec			// 秒
				);

///////////////////////////////////////////////////////////////////////////////
//	CStringの文字列を実数に変換する
MREAL MsGetMREAL(								// 実数
						CString&	i_str		// CString文字列
				);

///////////////////////////////////////////////////////////////////////////////
//	CStringの文字列を整数に変換する
MINT MsGetMINT(									// 整数
						CString&	i_str		// CString文字列
				);

///////////////////////////////////////////////////////////////////////////////
//	MINTの整数をCStringに変換する
CString MsCnvSMINT(								// 整数文字列
						MINT	i_iMode,		// モード　0: "n"形式に変換
						MINT	i_iNum			// 整数
				);

///////////////////////////////////////////////////////////////////////////////
//	MINTの実数をCStringに変換する
CString MsCnvSMREAL(							// 整数文字列
						MINT	i_iMode,		// モード　1: "0.0"形式に変換
						MREAL	i_iReal			// 実数
				);

///////////////////////////////////////////////////////////////////////////////
//	読み込み用ファイル選択ダイアログを表示する
void MsLoadFileDlg(
						CWnd*	i_pWnd,			// 親ウィンドウまたはオーナー ウィンドウへのポインタ
						MCHAR*	i_sInitFilePath,// 初期設定ファイルパス
						MCHAR*	o_sSelFilePath,	// 選択ファイルパス
						int		i_iszSelFilePath,// 選択ファイルパス配列サイズ(文字数)
						MCHAR*	i_sFilters		// ファイルを特定するためのフィルタ or NULL
				);
///////////////////////////////////////////////////////////////////////////////
//	保存用ファイル選択ダイアログを表示する
void MsSaveFileDlg(
						CWnd*	i_pWnd,			// 親ウィンドウまたはオーナー ウィンドウへのポインタ
						MCHAR*	i_sInitFilePath,// 初期設定ファイルパス
						MCHAR*	o_sSelFilePath,	// 選択ファイルパス
						int		i_iszSelFilePath,// 選択ファイルパス配列サイズ(文字数)
						MCHAR*	i_sFilters		// ファイルを特定するためのフィルタ or NULL
				);
/////////////////////////////////////////////////////////////////////////////
//	フォルダ選択ダイアログを表示する
void MsForFolderDlg( 
						HWND	i_hWnd,			// 親ウィンドウのハンドル
						MCHAR*	i_sCaptionStr,	// 説明の文字列
						MCHAR*	i_sInitFldrPath,// 初期設定フォルダパス
						MCHAR*	o_sSelFldrPath,	// 選択フォルダパス
						int		i_iszSelFldrPath// 選択フォルダパス配列サイズ(文字数)
				);
///////////////////////////////////////////////////////////////////////////////
// ファイル名の拡張子より形式を得る
MINT MsGetFileExtNo(							// 拡張子バッファの配列番号 -1:ｴﾗｰ
						MCHAR*	in_cFileName,	// ﾌｧｲﾙ名
						MCHAR**	in_ppExt,		// 拡張子バッファ(例 "bmp", "jpg" : 0, 1)
						MINT	in_NExt			// 拡張子数
				);
/////////////////////////////////////////////////////////////////////////////
//	画像ファイル名を得る
MINT HsGetImageFile(							// ｽﾃｰﾀｽ   0:正常  1:異常
						MCHAR*	i_cFile1,		// 入力画像ﾌｧｲﾙ名
						MCHAR*	o_cFile2,		// 出力画像ﾌｧｲﾙ名
						MINT	i_iMFlag,		// 1:左右ﾐﾗｰ
						MREAL	i_Scale			// ｽｹｰﾙ
				);

/////////////////////////////////////////////////////////////////////////////
//	プロセスを起動し終了するまで待つ。
MINT MsProcXqt(									// ｽﾃｰﾀｽ	0 : プロセスを実行し終了   -1 : プロセスの実行に失敗
						MCHAR*	i_AplName,		// 実行するﾓｼﾞｭｰﾙ名
						MCHAR*	i_cCmdLine);	// ｱﾌﾟﾘｹｰｼｮﾝに渡すｺﾏﾝﾄﾞﾗｲﾝ

/////////////////////////////////////////////////////////////////////////////
//		環境変数を得る
MINT MsGetenv(									// ｽﾃｰﾀｽ	0 : 正常   -1 : エラー
						MCHAR*	i_cEnvNam,		// 環境変数名
						MCHAR*	o_cEnvVal);		// 環境変数の値

/////////////////////////////////////////////////////////////////////////////
//		環境変数を加えたパス名を得る
MINT MsAddEnvNam(								// ｽﾃｰﾀｽ	0 : 正常   -1 : エラー
						MINT	i_iType,		// 0;属性 1:図形 2:ﾃｰﾌﾞﾙ 3:ﾃｷｽﾁｬ -1:HTEMP
						MCHAR*	i_cFilNam,		// ﾌｧｲﾙ名
						MCHAR*	o_cPasNam);		// 環境変数を加えたﾊﾟｽ名

/////////////////////////////////////////////////////////////////////////////
//		レジストリの登録
MINT MsSetRegistry( void);						// ｽﾃｰﾀｽ	     0 : 正常   -1 : エラー

/////////////////////////////////////////////////////////////////////////////
//		レジストリよりパスを取得
MINT MsGetRegistryPath         (				// ｽﾃｰﾀｽ	0 : 正常   -1 : エラー
						MCHAR*	o_cPName);		// ﾊﾟｽﾎﾙﾀﾞｰ

/////////////////////////////////////////////////////////////////////////////
//		レジストリにパスを設定
MINT MsSetRegistryPath(							// ｽﾃｰﾀｽ	0 : 正常   -1 : エラー
						MCHAR*	i_cPName);		// ﾊﾟｽﾎﾙﾀﾞｰ

/////////////////////////////////////////////////////////////////////////////
//		画像ファイル名を得る
MINT MsGetImageFile(							// ｽﾃｰﾀｽ   0 : 正常    1 : 異常
						MCHAR*	i_cFile1,		// 入力画像ﾌｧｲﾙ名
						MCHAR*	o_cFile2,		// 出力画像ﾌｧｲﾙ名
						MINT	i_iMFlag,		// 1:左右ﾐﾗｰ
						MREAL	i_Scale);		// ｽｹｰﾙ


} // namespace MC