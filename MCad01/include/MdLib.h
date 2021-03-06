#pragma once

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_HAITIDB_DO
	#pragma message( "<<< HaitiDb・dll_EXport >>>")
	#define DLL_EXPORT			__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== HaitiDb・dll_IMport ===")
			#define DLL_EXPORT	__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class MhRoofInfo;
class mhPlcParts;

class DLL_EXPORT HaitiDb
{
public:
/////////////////////////////////////////////////////////////////////////////
//	ＤＢをイニシャライズする
static void MdPartsDbInit( void);

/////////////////////////////////////////////////////////////////////////////
//	エンティティとPOSITIONのポインタの差を求める
//   pEnt = pPos + MdGetSizeOfHd();
static MINT MdGetSizeOfHd();

/////////////////////////////////////////////////////////////////////////////
//	部品を削除する
static void MdPartsDelete(
						MPOSITION	i_pPosition		// (I  ) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	部品を追加する
//	レコードの属性領域は追加したレコードに引渡し、引数のレコードはイニシャライズする。
static MPOSITION MdPartsAdd(
						mhPlcParts*	i_pPlcEn,		// (I  ) 部品レコード
						MINT		i_fdispCtrl		// (I  ) 表示制御フラグ
													//		 0: ＯＰＴ群ｾｯﾄ・展開ｺｰﾄﾞ・履歴管理ｺｰﾄﾞを追加しない
													//		 1: ＯＰＴ群ｾｯﾄ・展開ｺｰﾄﾞ・履歴管理ｺｰﾄﾞを追加する
				);

/////////////////////////////////////////////////////////////////////////////
//	部品配置を修正する
static void MdPartsModify(
						mhPlcParts* io_pPlcEnR,		// 修正元部材
						mhPlcParts* *o_ppPlcEnM		// 修正先部材
				);

/////////////////////////////////////////////////////////////////////////////
//	屋根を削除する
static void HaitiDb::MdRoofDelete(
						MPOSITION	i_pPosition		// (I  ) 屋根レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	屋根を追加する
//	レコードの属性領域は追加したレコードに引渡し、引数のレコードはイニシャライズする。
static MPOSITION MdRoofAdd(
						MhRoofInfo*	i_pRoofEn,		// (I  ) 屋根レコード
						MINT		i_fOptv = 1		// (I  ) ＯＰＴ群追加フラグ
													//		 0: ＯＰＴ群追加しない
													//		 1: ＯＰＴ群追加する
				);

//////////////////////////////////////////////////////////////
//	指定ノードの部品を得る
static mhPlcParts* MdPartsGet(							// (  O) 部品レコード
						MPOSITION	i_pPosition		// (I  ) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	先頭の部品を得る
//	返値 =NULL: レコードなし !=NULL: 読み込み部品位置

static mhPlcParts* MdGetHeadParts(
						MPOSITION*	o_pPartsPos = NULL	// (  O) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	次の部品を得る
//	返値 =NULL: レコードなし !=NULL: 読み込み部品位置

static mhPlcParts* MdGetNextParts(
						MPOSITION*	io_pPartsPos = NULL	// (I O) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの部品の有無を調べる

static bool MdIsNotEmptyParts();							// true: 部品有り/ false: 部品無し

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの最後に部品を追加する

static mhPlcParts* MdInjectParts(
						mhPlcParts*	i_pPlcEn	// (I  ) 部品レコード
				);

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの最後の部品を得る

static void MdEjectParts(
						mhPlcParts*	i_pPlcEn	// (  O) 部品レコード
				);
/*
/////////////////////////////////////////////////////////////////////////////
//	部品を削除する
static void MmPanelDelete(
						MPOSITION	i_pPosition	// (I  ) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	部品を追加する
//	レコードの属性領域は追加したレコードに引渡し、引数のレコードはイニシャライズする。
static MPOSITION MmPanelAdd(
						mhPlcParts*	i_pPlcEn	// (I  ) 部品レコード
				);
*/


/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの屋根をイニシャライズする

static void MdRoofDbInit( void);

/////////////////////////////////////////////////////////////////////////////
//	屋根を削除する

//static void MdRoofDelete(
//						MPOSITION*	i_pPosition	// (I  ) 部品レコード位置（ノード位置）
//				);

/////////////////////////////////////////////////////////////////////////////
//	屋根を追加する
//	レコードの属性領域は追加したレコードに引渡し、引数のレコードはイニシャライズする。

//static MPOSITION MdRoofAdd(
//						MhRoofInfo*	i_pRoofEn	// (I  ) 屋根レコード
//				);

//////////////////////////////////////////////////////////////
//	指定ノードの屋根を得る

static MhRoofInfo* MdRoofGet(
						MPOSITION	i_pPosition	// (I  ) 部品レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	先頭の屋根を得る
//	返値 =NULL: レコードなし !=NULL: 読み込み部品位置

static MhRoofInfo* MdGetHeadRoof(
						MPOSITION*	o_pRoofPos = NULL	// (  O) 屋根レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	次の屋根を得る
//	返値 =NULL: レコードなし !=NULL: 読み込み部品位置

static MhRoofInfo* MdGetNextRoof(
						MPOSITION*	io_pRoofPos = NULL	// (I O) 屋根レコード位置（ノード位置）
				);

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの屋根の有無を調べる

static bool MdIsNotEmptyRoof();						// true: 屋根有り/ false: 屋根無し

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの最後に屋根を追加する

static void MdInjectRoof(
						MhRoofInfo*	i_pRoofEn	// (I  ) 屋根レコード
				);

/////////////////////////////////////////////////////////////////////////////
//	家モデルＤ／Ｂの最後の屋根を得る

static void MdEjectRoof(
						MhRoofInfo* o_pRoofEn	// (  O) 屋根レコード
				);


/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の部品の有無を調べる

static bool MdIsNotEmptyRedoParts();						// true: 部品有り/ false: 部品無し

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の先頭に部品を追加する

static void MdPushRedoParts(
						mhPlcParts*	i_pRedoEn	// (I  ) 部品レコード
				);

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の先頭の部品を得る

static void MdPopRedoParts(
						mhPlcParts*	o_pRedoEn	// (  O) 部品レコード
				);

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ保存領域のクリア
static void MdClearRedo();

};

} // namespace MC
