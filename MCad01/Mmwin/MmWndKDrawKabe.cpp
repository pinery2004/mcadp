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
#include "MgMatD.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#include "MmWnd.h"
#include "MhDefParts.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "MsBitSet.h"
#include "MdList.h"
#include "MhLib.h"

#include "MhInpPlcParts.h"

#include "MdOpt.h"
#include "MdLib.h"

#include "MdHist.h"
#include "MmValid.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	������\������
void MmWndKDrawLine(
						msCod*			pCod,		// ���W�n
						mhPlcParts		*pPlcEn,	// �z�u���R�[�h
						MPENSTYLE		LineType,	// ����
						MSYSTEMCOLOR	iLineColor,	// ���F�R�[�h
						MgVect2D			vSinZ		// �c����
				)
{
	MgPoint2D	ptW[2];
	DWORD		PartsLineColor;

	ptW[0] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0))) + vSinZ;
	ptW[1] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1))) + vSinZ;

	PartsLineColor = mcs::GetColor( iLineColor);
	pCod->SetLineAttr( LineType, 1, PartsLineColor);
	pCod->Line( MgLine2D( ptW[0], ptW[1]));

}

/////////////////////////////////////////////////////////////////////////////
//	������\������
void MmWndKDrawLine(
						MINT			iMode,		// ���[�h
													//		0:�z�u������\���A
													//		1:�z�u�����܂��͐}�`��\��
						msCod*			pCod,		// ���W�n
						mhPlcParts		*pPlcEn,	// �z�u���R�[�h
						MPENSTYLE		LineType,	// ����
						MSYSTEMCOLOR	iLineColor,	// ���F�R�[�h
						MgVect2D			vSinZ		// �c����
				)
{
	MgPoint2D	ptW[2];
	DWORD		PartsLineColor;
	MhZukei		*pZukei;
	MINT		ic;

	ptW[0] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 0))) + vSinZ;
	ptW[1] = (*(MgPoint2D*)&(pPlcEn->GetPIPlcIti( 1))) + vSinZ;

	PartsLineColor = mcs::GetColor( iLineColor);
	pCod->SetLineAttr( LineType, 1, PartsLineColor);

	pZukei = pPlcEn->GetPIZukei();
	if ( iMode == 0 || pZukei == NULL) {
		pCod->Line( MgLine2D( ptW[0], ptW[1]));
	} else {
		for ( ic=0; ic<pZukei->m_isNZukei; ic++) 
			pCod->Line( MgLine2DC( pZukei->m_lnZukei[ic]));
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�ǐc����\������
void WindowCtrl::MmWndKDrawKabe(
						msCod*		pCod,			// ���W�n
						MINT		iKaiC,			// �K  	(1,2,3)
						MINT		iGpC			// �\��
				)
{
	MPOSITION	pos1;
	mhPlcParts	*pPlcEn;
	MINT		iEnKai;
//	MsBitSet	*pOptv;
//	MsBitSet*	pHstv;
	MgPoint2D	ptW[2];

	MREAL		rKabeSinZ = pCod->LPtoRP( MINT( pCod->DPtoLP(1)));
	MgVect2D		vKabeSinZ = MgVect2D( rKabeSinZ, rKabeSinZ) / 2.;

	// �ǐ���\������

	for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
		  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

		iEnKai = pPlcEn->GetPIKai();

		// ��(�ϗ͕�)
		if ( pPlcEn->IsKabe()) {

			if ( !MmCheckValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

			// ���g�A�ǘg�g�A�ϗ͕ǂɂ́A���K�̕ǐc����\������
			if ( iEnKai == iKaiC - 1) {							// ���K�̕�
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAIKABESIN, vKabeSinZ);

			// �ϗ͕�|�ǘg�g�ȊO�ɂ́A���K�̕ǐc����\������
			} else if ( iEnKai == iKaiC) {						// ���K�̕�
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// �ϗ͕�|�ǘg�g�݈ȊO�͕ǐc����\��
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAIKABESIN, vKabeSinZ);

			// �V��A�����A�����ɂ́A��K�̕ǐc����\������
			} else if ( iEnKai == iKaiC + 1) {					// ��K�̕�
				if ( iGpC >= MP_GP_TENJO)						// ��(�ϗ͕�)���ނ̕\��
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAIKABESIN, - vKabeSinZ);
			}

		// �ϗ͕ǋ��
		} else if ( pPlcEn->IsTaiKabeArea()) {

			if ( !MmCheckValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

			// ���g�A�ǘg�g�A�ϗ͕ǂɂ́A���K�̑ϗ͕ǋ���\������
			if ( iEnKai == iKaiC - 1) {							// ���K�̕�
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( 1, pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAITAIKABESIN, vKabeSinZ);

			// �ϗ͕�|�ǘg�g�ȊO�ɂ́A���K�̑ϗ͕ǋ���\������
			} else if ( iEnKai == iKaiC) {						// ���K�̕�
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// �ϗ͕�|�ǘg�g�݈ȊO�͕ǐc����\��
					MmWndKDrawLine( 1, pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAITAIKABESIN, vKabeSinZ);

			// �V��A�����A�����ɂ́A��K�̑ϗ͕ǋ���\������
//			} else if ( iEnKai == iKaiC + 1) {					// ��K�̕�
//				if ( iGpC >= MP_GP_TENJO)						// ��(�ϗ͕�)���ނ̕\��
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAITAIKABESIN, - vKabeSinZ);
			}

		// �ϗ͕ǐ�
		} else if ( pPlcEn->IsTaiKabeLine()) {

			if ( !MmCheckValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

			// ���g�A�ǘg�g�A�ϗ͕ǂɂ́A���K�̑ϗ͕ǐ���\������
			if ( iEnKai == iKaiC - 1) {							// ���K�̕�
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAITAIKABESIN, vKabeSinZ);

			// �ϗ͕�|�ǘg�g�ȊO�ɂ́A���K�̑ϗ͕ǐ���\������
			} else if ( iEnKai == iKaiC) {						// ���K�̕�
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// �ϗ͕�|�ǘg�g�݈ȊO�͕ǐc����\��
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAITAIKABESIN, vKabeSinZ);

			// �V��A�����A�����ɂ́A��K�̑ϗ͕ǐ���\������
//			} else if ( iEnKai == iKaiC + 1) {					// ��K�̕�
//				if ( iGpC >= MP_GP_TENJO)						// ��(�ϗ͕�)���ނ̕\��
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAITAIKABESIN, - vKabeSinZ);
			}

		// �x���ǐ�
		} else if ( pPlcEn->IsSijiKabeLine()) {

			if ( !MmCheckValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
			continue;

			// ���g�A�ǘg�g�A�ϗ͕ǂɂ́A���K�̎x���ǐ���\������
			if ( iEnKai == iKaiC - 1) {							// ���K�̕�
				if ( iGpC <= MP_GP_TAIRYOKU && iGpC > MP_GP_DODAI) 
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_KAKAISIJIKABESIN, vKabeSinZ);

			// �ϗ͕�|�ǘg�g�ȊO�ɂ́A���K�̎x���ǐ���\������
			} else if ( iEnKai == iKaiC) {						// ���K�̕�
				if ( iGpC != MP_GP_TAIRYOKU && iGpC != MP_GP_KABE)			// �ϗ͕�|�ǘg�g�݈ȊO�͕ǐc����\��
					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_DOUKAISIJIKABESIN, vKabeSinZ);

			// �V��A�����A�����ɂ́A��K�̎x���ǐ���\������
//			} else if ( iEnKai == iKaiC + 1) {					// ��K�̕�
//				if ( iGpC >= MP_GP_TENJO)						// ��(�ϗ͕�)���ނ̕\��
//					MmWndKDrawLine( pCod, pPlcEn, MPS_DASHDOT, MM_COLOR_JYOUKAISIJIKABESIN, - vKabeSinZ);
			}
		}
	}
}

} // namespace MC
