//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmDrag.cpp
//
//		�h���b�M���O����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MmDefine.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MtInp.h"

#include "MdOpt.h"
#include "MdLib.h"

#include "MdHist.h"
#include "MmValid.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	��b�c����\������
	void WindowCtrl::MmWndKDrawKiso(
						msCod*		pCod,			// ���W�n
						MINT		iKaiC,			// �K  	(1,2,3)
						MINT		iGpC			// �\��
				)
{
	MPOSITION	pos1;
	mhPlcInfo	*pPlcEn;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgPoint2	ptW[2];
	DWORD		PtsLineColor;

	MREAL		rKisoSinZ = pCod->LPtoRP( MINT( pCod->DPtoLP(1)));
	MgVect2		vKisoSinZ = MgVect2( rKisoSinZ, rKisoSinZ);

	// �P�K�̓y��ɂ́A��b�c����\������

	if ( iKaiC == 1 && iGpC == MP_GP_DODAI) {

		for ( pPlcEn = HaitiDb::MdGetHeadPts( &pos1); pPlcEn!=0;
			  pPlcEn = HaitiDb::MdGetNextPts( &pos1)) {

			if ( pPlcEn->IsKiso()) {								// ��b(�ϗ͊�b)����

			if ( !MmChkValidParts( pPlcEn))							// �I�v�V�����Ɨ����̃`�F�b�N
				continue;

				ptW[0] = (*(MgPoint2*)&(pPlcEn->GetPIPlcIti( 0))) + vKisoSinZ;
				ptW[1] = (*(MgPoint2*)&(pPlcEn->GetPIPlcIti( 1))) + vKisoSinZ;

				PtsLineColor = mcs::GetColor( MM_COLOR_KISOSIN);
				pCod->SetLineAttr( MPS_DASHDOT, 1, PtsLineColor);
				pCod->Line( MgLine2( ptW[0], ptW[1]));
			}
		}
	}
}

} // namespace MC