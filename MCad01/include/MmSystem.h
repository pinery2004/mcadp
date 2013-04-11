#pragma once

#include "MhDefParts.h"

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

class _System
{
private:
	static class CMCADApp	*ms_pMCADApp;		// �A�v���P�[�V�����|�C���^(Global) 
	static class CMainFrame	*z_pMainFrame;		// ���C���t���[���|�C���^(Global) 

public:
	/////////////////////////////////////////////////////////////////////////////
	//	�V�X�e���Ǘ�                                                           //
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer �ݒ�
	// class CMainFrame;
	static void	SetpMainFrame(
					class	CMainFrame*	pMainFrame
					)
	{
		z_pMainFrame = pMainFrame;
	}

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer �擾
	static CMainFrame* GetpMainFrame()
	{
		return z_pMainFrame;
	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer �ݒ�
	// class CMCADApp;
	static void	SetpMCADApp(
					class	CMCADApp*	pMCADApp
					)
	{
	//	CMCADApp* pApp = (CMCADApp*)AfxGetApp();
		ms_pMCADApp = pMCADApp;
	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer �擾
	static CMCADApp* GetpMCADApp()
	{
		return ms_pMCADApp;
	}

};

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

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer �ݒ�
	// class CMainFrame;
	static void	SetpMainFrame(
					class	CMainFrame*	pMainFrame
					)
	{
		::_System::SetpMainFrame( pMainFrame);
	}

	/////////////////////////////////////////////////////////////////////////////
	// MainFrame Pointer �擾
	static CMainFrame* GetpMainFrame()
	{
		return ::_System::GetpMainFrame();
	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer �ݒ�
	//class CMCADApp;
	static void	SetpMCADApp(
					class	CMCADApp*	pMCADApp
					)
	{
		::_System::SetpMCADApp( pMCADApp);
	}

	/////////////////////////////////////////////////////////////////////////////
	// MCADApp Pointer �擾
	static CMCADApp* GetpMCADApp()
	{
		return ::_System::GetpMCADApp();
	}

};


}// namespace MC
