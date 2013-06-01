 //==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdCmdErorPrompt.cpp
//		
//	機能	エラー表示 インテリCadを参考に追加予定　未　//IIP
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCAD.h"

#define DLL_EXPORT_CMDS_DO

#include "MdCmds.h"/*DNT*/
#include "..\\MCAD\\res\\MCADrc2.h"

namespace MC
{

//inline
__ResourceString:: __ResourceString( int resourceID, LPCTSTR t) 
		: m_string( t), m_loaded( NULL), m_id( resourceID)
{
}


//inline this for performance if necessary
//makes rebuilds easier for now if it isn't inlined
__ResourceString:: operator LPCTSTR()
{
	if ( !m_loaded)
		{
		TCHAR	buffer[1000];

										// load string into static
		int	size = ::LoadString( MCadSharedGlobals::GetMCadResourceInstance(), m_id,
								 buffer, sizeof( buffer));
		ASSERT( size < sizeof( buffer)-1 );

										// allocate buffer if immediate too small
		LPTSTR	dest;
		if ( size < sizeof( m_buffer) )
			dest = m_buffer;
		else
			dest = new TCHAR[ size+1];

										// copy the string value
										// (dest is a non-const alias)
		if ( dest )
			_tcscpy_s( dest, size+1, buffer);

		m_loaded = dest;

#ifdef USBUILD
		ASSERT( strsame( m_string, m_loaded) );
#endif
		}

	return m_loaded;
}

__ResourceString:: ~__ResourceString()
{
	if ( m_loaded != m_buffer )
		delete[] const_cast<LPTSTR>(m_loaded);
}



bool        cmd_GaveACISMsg;
bool        cmd_GaveProxyMsg;
bool        cmd_GaveHatchMsg;
bool        cmd_GaveImageMsg;
bool        cmd_GaveA2KEntMsg;

/*********************************************************************
**	Function:	cmd_ErrorPrompt()				     4/15/96		**
**	Purpose:	Keeps all the error message strings in one place.	**
**                                                                  **
**  Notes:  When you make up new ones, please try to be consistent  **
**  in making up the ErrNo names, and kind to the users.			**
**  It's easy to confuse these in the ErrNo names...look out:		**
**			2DPT	2-Dimensional point, as in Pick a 2D point		**
**			2NDPT	Second point, as in Pick 2nd point				**
**			2PTS	2 Points, as in Pick two points					**
**	When you make up new ones, please follow the above convention.	**
**                                                                  **
**  - When the command line is not displayed, the error messages    **
**  appear in a message box so the user doesn't miss them.          **
**  - Be sure to add new ones to the #defines in cmds.h also.       **
**                                                                  **
**  Example:                                                        **
**          cmd_ErrorPrompt(CMD_ERR_YESNO,0);                       **
**                                                                  **
*********************************************************************/

void MdCmdErrorPrompt(int ErrNo, short DispMode, void *arg1, void *arg2, void *arg3)
{
	// mode =1 for message box by default
	// mode =0 for command line (or msg box if no command line)
	// mode=-1 for command line only

	CString	ErrPrompt;
	MCHAR	fs1[IC_MCADBUF];

	CString strTitle;

	switch (ErrNo){
		case CMD_ERR_UNABLE:
		    strTitle.LoadString(AFX_IDS_APP_TITLE);
			strTitle.LoadString(IDS_HATCHEDITERROR);
			ErrPrompt=ResourceString(IDC_ERRORPROMPT_INTELLICAD_270, "IntelliCAD is unable to complete this operation." );
			break;
									// Replace this where possible.  I've only used it when the old message just said "ERROR" (+/-)
//		// If all else fails...
		default:					ErrPrompt=ResourceString(IDC_ERRORPROMPT_INTELLICAD_270, "IntelliCAD is unable to complete this operation." );

	}

	_snwprintf_s( fs1, sizeof(fs1), ErrPrompt, arg1, arg2, arg3);

}

} // namespace MC
