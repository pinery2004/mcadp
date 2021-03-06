//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgRect.cpp
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
//#include "MlLog.h"

#define	DLL_EXPORT_RECT_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgRect.h"

namespace MC
{

//
//static MgMinMaxI2D	McMinMaxIN	= MgMinMaxI2D( 0, 0, 1, 1);
//static MgMinMaxR2D	McMinMaxRN	= MgMinMaxR2D( 0.0f, 0.0f, 1.0f, 1.0f);
//static MgMinMaxR3D McMinMaxR3N = MgMinMaxR3D( 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
//static MgRect2D	McRectN		= MgRect2D( 0.0f, 0.0f, 1.0f, 1.0f);
//static MgRect3D	McRect3N	= MgRect3D( 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
//
//======================( ２次元 )==============================
//		ＭＩＮ／ＭＡＸに単位長方形を設定する
//
void MgMinMaxI2D::SetUnit()	{ *this = MgMinMaxI2D( 0, 0, 1, 1);}
void MgMinMaxI2D::SetInit()	{ *this = MgMinMaxI2D( INT_MAX, INT_MAX, INT_MIN, INT_MIN);}
//
void MgMinMaxR2D::SetUnit()	{ *this = MgMinMaxR2D( 0.0f, 0.0f, 1.0f, 1.0f);}
void MgMinMaxR2D::SetInit()	{ *this = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);}
//
//======================( ３次元 )==============================
//		ＭＩＮ／ＭＡＸに単位直方体を設定する
//
void MgMinMaxR3D::SetUnit()	{ *this = MgMinMaxR3D( 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);}
void MgMinMaxR3D::SetInit()	{ *this = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);}
//
//======================( ２次元 )==============================
//		単位長方形を設定する
//
void MgRect2D::SetUnit()		{ *this = MgRect2D( 0.0f, 0.0f, 1.0f, 1.0f);}
//
//======================( ２次元 )==============================
//		長方形をトレースする
//
void MgRect2D::Print(MCHAR* s)														// print
{
//#ifdef LOGOUT
//	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgRect2D	= %f, %f, %f, %f\n"),
//							s, p[0].x, p[0].y, p[1].x, p[1].y);
//	MBLOGPRBF;
//	mlLog::Trace( mlLog::m_Str);
//#endif
}
//
//======================( ３次元 )==============================
//		単位直方体を設定する
//
void MgRect3D::SetUnit()		{ *this = MgRect3D( 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);}
//
//======================( ３次元 )==============================
//		直方体をトレースする
//
void MgRect3D::Print(MCHAR* s)														// print
{
//#ifdef LOGOUT
//	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgRect2D	= %f, %f, %f, %f, %f, %f\n"),
//							s, p[0].x, p[0].y, p[0].z, 
//							   p[1].x, p[1].y, p[1].z);
//	MBLOGPRBF;
//	mlLog::Trace( mlLog::m_Str);
//#endif
}
//

} // namespace MC
