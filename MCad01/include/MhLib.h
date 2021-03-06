#pragma once

#include "MsDefConst.h"
class MgLine2D;

#define	TRACE_IO		0			// Read / Write トレース　フラグ　( 0 | 1)		標準値(0)
#define DEBUG1			0			// 
#define Disp3DBox		0			// 1: 3Dの家モデルの代わりに3Dの箱を表示する, 0: 3Dの家モデルを表示する


namespace MC
{

#if( TRACE_IO)
extern	int iCzk_IO;
#endif

class	mhPlcParts;
class	MhRoofInfo;

class	MhMbr;
class	mhGp;
class	mhPartsSpec;

/////////////////////////////////////////////////////////////////////////////
//【機能】定数
//

#define MH_INS	1
#define MH_MOD	2
#define MH_DEL	3

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_IEMODEL_DO
	#pragma message( "<<< IeModel・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== IeModel・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT IeModel
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//【機能】汎用関数
	//

	/////////////////////////////////////////////////////////////////////////////
	//【機能】家モデル修正フラグの設定
	static void MhSetModFIeMdl( bool mod);

	/////////////////////////////////////////////////////////////////////////////
	//【機能】家モデル修正フラグの検索
	static bool MhGetModFIeMdl();

	////////////////////////////////////////////////////////////////////////////
	//【機能】部品データを読み込む

	static void MhInitParts();

	////////////////////////////////////////////////////////////////////////////
	//【機能】入力属性値を初期化する

	static void MnInitInpAt();

	////////////////////////////////////////////////////////////////////////////
	//【機能】壁データ　追加、修正フラグをセットする

	static void MhKabeSetUpFlg();

	////////////////////////////////////////////////////////////////////////////
	//【機能】壁を正規化する(交差部で分割し、直進部で連結する)

	static void MhNormKabe(
					const	MINT		nProc			// (I  ) 処理数	  0 : 全壁処理	
														//				 >0 : 最後のnProc壁を処理する
					);

	////////////////////////////////////////////////////////////////////////////
	//【機能】基礎データ　追加、修正フラグをセットする

	static void MhKisoSetUpFlg();

	////////////////////////////////////////////////////////////////////////////
	//【機能】基礎を正規化する(交差部で分割し、直進部で連結する)

	static void MhNormKiso(
					const	MINT		nProc			// (I  ) 処理数　0 : 全基礎処理	
														//				>0 : 最後のnProc基礎を処理する
					);

	////////////////////////////////////////////////////////////////////////////
	//【機能】読み込み家モデルファイル名を取得する
	//【返値】	0 : キャンセル、1 : ＯＫ

	static MINT MhFileDialog(
					const	MINT		DFlag,			// (I  ) 0:開く  1:保存
					const	MCHAR*		i_sPath,		// 指定ファイル名（フルパス）
							MCHAR*		o_sPath,		// 選択ファイル名（フルパス）
							int			i_nPath			// 選択ファイル名（フルパス）最大文字数
					);

	////////////////////////////////////////////////////////////////////////////
	//【機能】フルパス名から、フォルダーパス名、ファイル名、ファイルタイトル、
	//						　ファイル拡張子を取得する

	static void MhSeparateFname(
					const	MCHAR*		i_sFullPath,			// ファイルフルパス名
							MCHAR*		o_sFolderPath = NULL,	// フォルダーパス名	または　NULL
							int			i_nFolderPath = 0,		// フォルダーパス名最大文字数
							MCHAR*		o_sFileName = NULL,		// ファイル名			または　NULL
							int			i_nFileName = 0,		// ファイル名最大文字数
							MCHAR*		o_sFileTitle = NULL,	// ファイルタイトル	または　NULL
							int			i_nFileTitle = 0,		// ファイルタイトル最大文字数
							MCHAR*		o_sFileExt = NULL,		// ファイル拡張子		または　NULL
							int			i_nFileExt = 0			// ファイル拡張子最大文字数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】構造家モデル保存
	//【返値】	0 : 正常、1 : 異常

	static MINT MhMdlSave(
					const	MCHAR*		cFilePath		// (I  ) 構造家モデル保存先ファイル名（フルパス）
					);

	////////////////////////////////////////////////////////////////////////////
	//【機能】構造家モデル読み込み
	//【返値】  0 : 正常、1 : 異常

	static MINT MhMdlLoad(
							MCHAR*		cFilePath		// (I  ) 読み込み構造家モデルファイル名（フルパス）
					);


//	static class MhTategu* IeModel::MhpInpTategu();
//	{
//		return &g_hInpTateguAttr;
//	}
//	static class mhPlcParts* IeModel::MhpInpPI();
//	{
//		return &g_hInpPIAttr;
//	}

};

////////////////////////////////////////////////////////////////////////////
//【機能】構造家モデルヘッダ

class	MhMdlHeader
{
public:
	MCHAR		cTitle[12];						// タイトル
	MCHAR		cVer[8];						// バージョン
	MTIME		cAscTime[24];
	CTime		cTime;
};

////////////////////////////////////////////////////////////////////////////
//【機能】構造家モデル

class MhMdlIO
{
public:
	MINT		m_iMode;						// 読み書きモード	MBREAD  : 読み込み
												//					MBWRITE : 書き込み
	CFile		m_File;							// 構造家モデルCFileオブジェクト
	MCHAR		m_MdlPath[MAX_PATH];			// 構造家モデルファイル名（フルパス）
	MhMdlHeader	m_Header;						// 構造家モデルヘッダー

//	コンストラクタ
	MhMdlIO();

//	デストラクタ
	~MhMdlIO();

	////////////////////////////////////////////////////////////////////////////
	//【機能】ファイル読み書き処理開始宣言
	//【返値】==  0 : 正常終了
	//		  == -2 : 既にオープンされている
	//		  ≦ -3 : その他エラー

	MINT Open(
				const	DWORD		iMode,		// (I ) 使用モード
												//		== MBREAD:	読み込み専用
												//		== MBWRITE:	書き込み専用
				const	MCHAR*		cFilePath
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】ファイル読み書き処理終了宣言
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT Close();

	////////////////////////////////////////////////////////////////////////////
	//【機能】ファイル読み込み
	//【返値】>=  0 : 正常終了 読み込みバイト数
	//		   <  0 : その他エラー

	MINT ReadItem(
						MINT*		piType,		// (  O) ﾀｲﾌﾟ
						void**		Buff		// (  O) 読込み領域
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】任意型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー
	
	MINT WriteItems(
				const	MINT		i_iTp,		// タイプ
				const	void*		i_bf,		// 書込み領域
				const	MINT		i_iSz		// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】SHORT型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemIS(
				const	MINT		i_iTp,		// タイプ
				const	MSHORT*		i_ibf,		// 書込みSHORT配列
				const	MINT		i_iSz = sizeof(MSHORT)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】整数型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemI(
				const	MINT		i_iTp,		// タイプ
				const	MINT*		i_ibf,		// 書込み整数配列
				const	MINT		i_iSz = SZMINT()
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】整数型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemUI(
				const	MINT		i_iTp,		// タイプ
				const	MUINT*		i_ibf,		// 書込み整数配列
				const	MINT		i_iSz = sizeof(MUINT)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】FLOAT型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemR(
				const	MINT		i_iTp,		// タイプ
				const	float*		i_rbf,		// 書込み実数配列
				const	MINT		i_iSz = sizeof(float)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】DOUBLE型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemR(
				const	MINT		i_iTp,		// タイプ
				const	double*		i_rbf,		// 書込み実数配列
				const	MINT		i_iSz = sizeof(double)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】BYTE型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー
	
	MINT WriteItemIB(
				const	MINT		i_iTp,		// タイプ
				const	MUBYTE*		i_ibf,		// 書込みBYTE配列
				const	MINT		i_ibt = 1	// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】文字型(char)データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemCH(
				const	MINT		i_iTp,		// タイプ
				const	char*		i_cDat,		// 書込み文字列
				const	MINT		i_sz = 1	// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】文字型(_TCHAR)データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemCH(
				const	MINT		i_iTp,		// タイプ
				const	_TCHAR*		i_cDat,		// 書込み文字列
				const	MINT		i_sz = sizeof(_TCHAR)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】文字型(CString)データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemCS(
				const	MINT		i_iTp,		// タイプ
				const	CString*	i_sDat,		// 書込み文字列
				const	MINT		i_sz = 1	// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////
	//【機能】BOOL型データのファイル書き込み
	//【返値】==  0 : 正常終了
	//		  ≠  0 : その他エラー

	MINT WriteItemBL(
				const	MINT		i_iTp,		// タイプ
				const	bool*		i_bDat,		// 書込み文字列
				const	MINT		i_sz = sizeof(bool)
												// 書込みバイト数
				);

	////////////////////////////////////////////////////////////////////////////////
	//////【機能】ファイル読み込み
	//////【返値】>=  0 : 正常終了 読み込みバイト数
	//////		   <  0 : その他エラー
	////
	////	MINT Read(
	////						MINT*		piType,			// (  O) ﾀｲﾌﾟ
	////						void**		Buff			// (  O) 読込み領域
	////				);
	////
	////////////////////////////////////////////////////////////////////////////////
	//////【機能】ファイル書き込み
	//////【返値】==  0 : 正常終了
	//////		  ≠  0 : その他エラー
	////
	////	MINT WriteItem(
	////				const	MINT		i_iTp,			// (I  ) タイプ
	////				const	MINT		Size,			// (I  ) 書込みサイズ（バイト数）
	////				const	void*		Buff			// (I  ) 書込み領域
	////				);
	////
	////////////////////////////////////////////////////////////////////////////////
	//////【機能】ファイル読み込み
	//////【返値】>=  0 : 正常終了 読み込みバイト数
	//////		   <  0 : その他エラー
	////
	////	MINT Read(
	////						MINT*		piType,			// (  O) ﾀｲﾌﾟ
	////						void**		Buff			// (  O) 読込み領域
	////				);
	////
	////////////////////////////////////////////////////////////////////////////////
	//////【機能】ファイル書き込み
	//////【返値】==  0 : 正常終了
	//////		  ≠  0 : その他エラー
	////
	////	MINT WriteItem(
	////				const	MINT		iType,			// (I  ) ﾀｲﾌﾟ
	////				const	MINT		Size,			// (I  ) 書込みサイズ（バイト数）
	////				const	void*		Buff			// (I  ) 書込み領域
	////				);

};

class MsBitSet;

class Option
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//【機能】新規レコード追加時に設定するＯＰＴ群コードを取得する
	//		　（ＯＰＴ群コードが入るエリアの確保は本関数で行う）
	static void MhAddOpt(
							MsBitSet*		*ppOptv		// (  O) 追加レコードに設定するＯＰＴ群コードのポインタ NULL: 全ＯＰＴ群
					 );

	/////////////////////////////////////////////////////////////////////////////
	//【機能】レコード修正時に設定するＯＰＴ群コードを取得する
	//【返値】修正後のレコード構成コード
	//			1 : 修正元ＯＰＴ群は書込みＯＰＴ群と同一の場合で、
	//				修正元レコードはＯＰＴ群変更なしで修正内容を上書きする。
	//				追加レコードはなし。
	//			2 :	修正元ＯＰＴ群は書込みＯＰＴ群に全て含まれかつ追加ＯＰＴ群がある場合で、
	//				修正元レコードは書込みＯＰＴ群に変更し、修正内容を上書きする。
	//				追加レコードはなし。
	//			3 : 修正元ＯＰＴ群に書込みＯＰＴ群以外のＯＰＴ群を含む場合で、
	//				書込みＯＰＴ群以外のＯＰＴ群部分は、修正元レコードをそのまま残しＯＰＴ群コードのみ修正する。
	//				さらに、書込みＯＰＴ群を持つ修正後のレコードを新たに追加する。
	//				（ＯＰＴ群コードが入るエリアの開放と確保は本関数で行う）
	static MINT MhModOpt(
							mhPlcParts	 *pPlcEnR,		// (I O) 修正元部材
							mhPlcParts* *ppPlcEnM		// (  O) 修正先部材
					);

	/////////////////////////////////////////////////////////////////////////////
	//【機能】レコード削除時に設定するＯＰＴ群コードを取得する
	//【返値】削除後のレコード構成コード
	//			1 : 削除元ＯＰＴ群は書込みＯＰＴ群と同一の場合で、
	//				削除元レコードは削除する。
	//			2 :	削除元ＯＰＴ群は書込みＯＰＴ群に全て含まれかつ追加ＯＰＴ群がある場合で、
	//				削除元レコードは削除する。
	//			3 : 削除元ＯＰＴ群に書込みＯＰＴ群以外のＯＰＴ群を含む場合で、
	//				書込みＯＰＴ群以外のＯＰＴ群部分は、削除元レコードをそのまま残しＯＰＴ群コードのみ修正する。
	//				（ＯＰＴ群コードが入るエリアの開放と確保は本関数で行う）


	static MINT MhDelOpt(
	//D						MsBitSet		*pOptR,			// (I O) 削除元レコードのOPT群セット
							MsBitSet*		*ppOptRN1,		// (I O) 削除前後のレコードの表示ＯＮ　OPT群セット
							MsBitSet*		*ppOptRN2		// (I O) 削除前後のレコードの表示ＯＦＦOPT群セット
					);

	/////////////////////////////////////////////////////////////////////////////
	//【機能】ＯＰＴ群コードの領域を開放する
	static void MhFreOpt(
							MsBitSet	*pOptv		// (I O) 開放するＯＰＴ群コードのポインタ NULL: 開放不要
					);

};

class Version {

	/////////////////////////////////////////////////////////////////////////////
	//【機能】カレントバージョンの設定
	static bool MhSetCurVer(
					const	MUINT		*iVer		// (I  ) バージョン NULL: 全バージョン
					 );

	/////////////////////////////////////////////////////////////////////////////
	//【機能】カレントバージョンＵＰ
	static bool MhUpCurVer();

	/////////////////////////////////////////////////////////////////////////////
	//【機能】カレントバージョンの取込
	static bool MhGetCurVer(
							MUINT*		*piVer		// (  O) バージョン NULL: 全バージョン
					 );

	/////////////////////////////////////////////////////////////////////////////
	//【機能】新規レコード追加時に設定するバージョンコードを取得する
	//		　（バージョンコードを作成しそのポインタを返す）
	//【返値】バージョンコードのポインタ
	//		  NULL : 全バージョン有効
	static MUINT* MhAddVer();

	/////////////////////////////////////////////////////////////////////////////
	//【機能】レコード修正時に設定するバージョンコードを取得する
	//【返値】修正後のバージョンコードのポインタ
	//		  NULL : 読込バージョンコードと同一内容であり、修正レコードは読込レコードに上書きする事
	static MUINT* MhModVer(
							MUINT		*iVer		// (I O) 修正元レコードのバージョンコードのポインタ
					);

	/////////////////////////////////////////////////////////////////////////////
	//【機能】レコード削除時に設定するＯＰＴ群を取得する
	//【返値】削除後のバージョンコードのポインタ
	//		  　NULL : レコード消滅、削除レコードは削除する事
	//		  ≠NULL : バージョン変更、削除レコードはバージョンコードのみ修正する
	static MUINT* MhDelVer(
							MUINT*		*piVer		// (I O) 削除レコードのバージョンコードのポインタ
					);

	/////////////////////////////////////////////////////////////////////////////
	//【機能】バージョンコードの領域を開放する
	static void MhFreVer(
							MUINT*		*piVer		// (I O) 開放バージョン NULL: 開放不要
					);
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_BUZAICODE_DO
	#pragma message( "<<< BuzaiCode・dll_EXport >>>")
	#define DLL_EXPORT								__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== BuzaiCode・dll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

class DLL_EXPORT BuzaiCode
{
public:
	// 組レコード数を取得する
	static MINT MhGetNoOfGp();

	// 組レコードを取得する
	static mhGp* MhGetpGp(
							MINT		iGp							// 読み込み構成(組)レコード番号
					);

	// 部品種類レコード数を取得する
	static MINT	BuzaiCode::MhGetNoOfPartsSpec();

	// 部品種類レコードを取得する
	static mhPartsSpec* BuzaiCode::MhGetpPartsSpec(
							MINT		iPartsSpec					// 読み込み部品種類レコード番号
					);

	// 部品IDを取得する
	static MINT BuzaiCode::MhGetPIIdPartsSpec(
							MINT		iCdBuzai					// 部材コード
					);

	// 寸法型式レコード数を取得する
	static MINT	BuzaiCode::MhGetNoOfMbr();

	// 寸法型式レコードを取得する
	static MhMbr*	BuzaiCode::MhGetpMbr(
							MINT		iMbr						// 読み込み寸法型式レコード番号
					);

	// 寸法型式IDを取得する
	static MINT	BuzaiCode::MhGetIdMbr(
							MCHAR*		pMbr						// 寸法型式
					);

	// 部材の２次元芯線を取得する
	static void	BuzaiCode::MhBziSin(
							mhPlcParts	*pBziInfo1,					// (I  ) 部材
							MgLine2D		*lnBziSin1					// (  O) 部材の芯線
					);

	// 全配置内容をトレース
	static void	BuzaiCode::MhPrintallmhPlcParts(MCHAR* s);
};

} // namespace MC