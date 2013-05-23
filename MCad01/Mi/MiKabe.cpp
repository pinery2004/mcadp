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
#include "MsDefine.h"
#include "MmLib.h"

#include "MhPlcParts.h"

#include "MmPrompt.h"
#include "MhPlcPartsLib.h"

#define		MAXHAIKABE		500									// �z�񐧌��l
#define		MC_KABE_TOL		44.5								// �ǔ���g�������X

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�ǐc�ۂߐ����擾����
//
void mhInput::GetMarumeKabeLine(
						MINT		iKai,			// �����K
				const	MgPoint2D	&Pi,			// ���͍��W
						MgGLine2D	*pGLn			// �Ώەǐc
				)
{
	MINT		ist1;
	MINT		iCdMarume;
	MREAL		rTol;
	MREAL		rTolDsv;
	mhPlcParts*	pHaiKabe[MAXHAIKABE];				// �ǃf�[�^
	MINT		nHaiKabe;							// �ǐ�
	MINT		ic2;
	MgLine2D		ln1;

	iCdMarume = z_mnIA.GetComboMarumeCd();
	if ( iCdMarume == 0)
		rTol = MC_KABE_TOL;
	else
		rTol = mcs::GetReal( MM_REAL_PITCH) / iCdMarume;

	nHaiKabe = mhHaitiIn::GetParts( iKai, MP_GP_TAIRYOKU, Mstr( "��"), NULL, MAXHAIKABE, pHaiKabe);
																				// �ƃ��f�����J�����g�K�̑S�Ă̕ǂ��擾
	pGLn->m_n = 0;
	for ( ic2=0; ic2<nHaiKabe; ic2++) {											// ��
		ln1 = MgLine2DC( pHaiKabe[ic2]->GetPIPlcIti());
		rTolDsv = MgTol::SetD( rTol);
		if ( MGeo::CheckPointOnLine2DWS( Pi, ln1, &ist1))
			(*pGLn) += MgLine2DC( pHaiKabe[ic2]->GetPIPlcIti());
		MgTol::SetD( rTolDsv);
	}
	if ( pGLn->m_n == 0) {
		Msg::ErrorMsg( Mstr( "�Ǐ�ɓ��͂��ĉ�����"), MC_ERR_BASE);				// ""
	}
}

} // namespace MC
