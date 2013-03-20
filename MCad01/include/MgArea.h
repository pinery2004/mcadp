#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "MgLine.h"

namespace MC
{

struct	MgArea2H;

struct	MgArea2{
	MINT	nallocpnt;
	MINT	npnt;
	MgPoint2 *pnt;
	MINT	nAreaH;
	MgArea2H	*AreaH;
};
struct MgArea2H{
	MgArea2H	*next;
	MINT	npnt;
	MgPoint2*	pnt;
};
struct	MgGArea{
	MINT	nArea;
	MgArea2S	*Area;
};
//
/////////////////////////////////////////////////////
//
//	���t���p�`�g�P�Ƃg�Q�̈ʒu�֌W�𒲂ׂ�
MINT	MgCArea(MgGArea);

} // namespace MC