//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MlLog.h"
#include "MgDefine.h"
#include "MgTol.h"

#include "MgAngle.h"
#include "MgPoint.h"
#include "MgLine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

#include "MhDefParts.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#include "MhLib.h"
#include "MdLib.h"

#define  DLL_EXPORT_HAITICMD_DO
#include "MmCmd.h"

#include "MdPartsQueue.h"
#include "MhPlcParts.h"

namespace MC
{

static	MdPartsQueue	z_RedoStk( 10, sizeof( mhPlcParts));			// ＲＥＤＯ用保存領域

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域をイニシャライズする
void MdRedoPartsDbInit( void)
{
	z_RedoStk.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の部品配置の有無を調べる

bool HaitiDb::MdIsNotEmptyRedoParts()						// true: 部品配置有り/ false: 部品配置無し
{
	return z_RedoStk.IsNotEmpty();
}

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の先頭に部品配置を追加する

void HaitiDb::MdPushRedoParts(
						mhPlcParts	*pRedoEn		// (I  ) 部品配置管理情報
				)
{
	z_RedoStk.Push( pRedoEn);
}

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ用保存領域の先頭の部品配置を取得する

void HaitiDb::MdPopRedoParts(
						mhPlcParts	*pRedoEn		// (I  ) 部品配置管理情報
				)
{
	z_RedoStk.Pop( pRedoEn);
}

/////////////////////////////////////////////////////////////////////////////
//	ＲＥＤＯ保存領域のクリア
void HaitiCmd::MdClearRedo()
{
	mhPlcParts	PlcEn;

	while (z_RedoStk.IsNotEmpty()) {
		z_RedoStk.Eject( &PlcEn);
		PlcEn.FreeAllAtr();
		//	配置エンティティ内で使用している領域を削除するコーディングの追加を必要
	}
}

} // namespace MC
