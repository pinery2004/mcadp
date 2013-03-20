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
//======================( �Q���� )==============================
//		�Q�����~�ʂ��g���[�X����
//
void MgArc2::Print(MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgArc2	: (%7.1f,%7.1f), (%7.1f,%7.1f), (%7.1f,%7.1f), %7.1f\n"),
								 s, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pc.x, pc.y, r);
	MBTRCPRBF;
#endif
}

//
//======================( �R���� )==============================
//		�R�����~�ʂ��g���[�X����
//
void MgArc3::Print(MCHAR* s)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s 	MgArc3 	: (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), (%7.1f,%7.1f,%7.1f), %7.1f\n"),
								 s,  Pt[0].x, Pt[0].y, Pt[1].x, Pt[1].y,Pc.x, Pc.y, Pc.z, V.x, V.y, V.z, r);
	MBTRCPRBF;
#endif
}

} // namespace MC
