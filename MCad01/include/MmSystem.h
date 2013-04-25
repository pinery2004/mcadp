#pragma once

#include "MhDefParts.h"
#include "MCad.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_SYSTEM_DO
	#pragma message( "<<< MC::System・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::System・dll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

namespace MC
{

class DLL_EXPORT System
{
private:

public:
	/////////////////////////////////////////////////////////////////////////////
	//	システム管理                                                           //
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	システム初期化
	static MINT MmInitialize();

	/////////////////////////////////////////////////////////////////////////////
	//	システム終了処理
	static void MmTerminate();

	/////////////////////////////////////////////////////////////////////////////
	//	MCADINIファイルの読み込み
	static void LoadMCADIniFile( MCHAR i_cIniFilePath[]);

//	/////////////////////////////////////////////////////////////////////////////
//	// MainFrame Pointer 設定
//	// class CMainFrame;
//	static void	SetpMainFrame(
//					class	CMainFrame*	pMainFrame
//					)
//	{
//		z_MCadApp.m_pMainFrame = pMainFrame;
//	}

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer 取得
	static CMainFrame* GetpMainFrame()
	{
		return z_MCadApp.m_pMainFrame;
	}

//	/////////////////////////////////////////////////////////////////////////////
//	// MCADApp Pointer 設定
//	//class CMCADApp;
//	static void	SetpMCADApp(
//					class	CMCADApp*	pMCADApp
//					)
//	{
//		z_MCadApp = pMCADApp;
//	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer 取得
	static CMCadApp* GetpMCADApp()
	{
		return &z_MCadApp;
	}

};


}// namespace MC
