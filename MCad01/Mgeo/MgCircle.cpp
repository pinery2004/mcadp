//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgCircle.cpp
//
//		
//
//
//  K.Matsu           09/20/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_CIRCLE_DO

#include "MgLib.h"
#include "MgCircle.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		２次元円をトレースする
//
void MgCir2D::Print(MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgCir2D	: (%7.1f,%7.1f), %7.1f\n"),
								 s, pc.x, pc.y, r);
	MBLOGPRBF;
#endif
}
//
//======================( ３次元 )==============================
//		３次元円をトレースする
//
void MgCir3D::Print(MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgCir3D 	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), %7.1f\n"),
								 s, Pc.x, Pc.y, Pc.z, V.x, V.y, V.z, r);
	MBLOGPRBF;
#endif
}

} // namespace MC
