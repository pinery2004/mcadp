//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgArc.cpp
//
//		
//
//
//  K.Matsu           09/20/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_ARC_DO

#include "MgLib.h"
#include "MgArc.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		２次元円弧をトレースする
//
void MgArc2D::Print(MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgArc2D	: (%7.1f,%7.1f), (%7.1f,%7.1f), (%7.1f,%7.1f), %7.1f\n"),
								 s, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pc.x, pc.y, r);
	MBLOGPRBF;
#endif
}

//
//======================( ３次元 )==============================
//		３次元円弧をトレースする
//
void MgArc3D::Print(MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgArc3D 	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), %7.1f\n"),
								 s,  Pt[0].x, Pt[0].y, Pt[1].x, Pt[1].y,Pc.x, Pc.y, Pc.z, V.x, V.y, V.z, r);
	MBLOGPRBF;
#endif
}

} // namespace MC
