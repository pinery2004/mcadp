#pragma once

#include "MhDefParts.h"
#include "MCad.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_SYSTEM_DO
	#pragma message( "<<< MC::System�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::System�Edll_IMport ===")
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
	//	�V�X�e���Ǘ�                                                           //
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	�V�X�e��������
	static MINT MmInitialize();

	/////////////////////////////////////////////////////////////////////////////
	//	�V�X�e���I������
	static void MmTerminate();

	/////////////////////////////////////////////////////////////////////////////
	//	MCADINI�t�@�C���̓ǂݍ���
	static void LoadMCADIniFile( MCHAR i_cIniFilePath[]);

//	/////////////////////////////////////////////////////////////////////////////
//	// MainFrame Pointer �ݒ�
//	// class CMainFrame;
//	static void	SetpMainFrame(
//					class	CMainFrame*	pMainFrame
//					)
//	{
//		z_MCadApp.m_pMainFrame = pMainFrame;
//	}

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer �擾
	static CMainFrame* GetpMainFrame()
	{
		return z_MCadApp.m_pMainFrame;
	}

//	/////////////////////////////////////////////////////////////////////////////
//	// MCADApp Pointer �ݒ�
//	//class CMCADApp;
//	static void	SetpMCADApp(
//					class	CMCADApp*	pMCADApp
//					)
//	{
//		z_MCadApp = pMCADApp;
//	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer �擾
	static CMCadApp* GetpMCADApp()
	{
		return &z_MCadApp;
	}

};


}// namespace MC
