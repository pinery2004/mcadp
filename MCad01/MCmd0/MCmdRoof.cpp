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

#define DLL_EXPORT_MC_INPUT_DO
#include "MrAPI.h"

namespace MC
{

void MCmdRoofAdd();
void MCmdRoofDelete();

static void	MmPackAreaI(
						MgPolyg2*	pPg1,			// (I O) �n�����
						MgGInt*		pGifInp			// (I O) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				);

void MCmdRoof()
{
	MINT iMode;
	iMode = mtInpMode::GetMode();
	if ( iMode == MP_MD_CREATE)
		MCmdRoofAdd();
	else if ( iMode == MP_MD_DELETE)
		MCmdRoofDelete();
}

void MCmdRoofAdd()
{
	MINT		ist1;
	MgPoint2	pt1, pt2, pth;
	MgLine2		Ln1;
	MgPolyg2	pgJim(20);
	MgGInt		GifInp(20);

	Msg::ClearErrorMsg();
	mtInpMode::SetKGp( MP_GP_YANE);
	mtInpMode::SetKBr( MP_BR_OTHER);
	mtInpAttr::InitComboAttr( MP_AT_YANE);								// �������͗p�R���{�{�b�N�X�𑮐��l���͖����ɂ���
	mtInpAttr::InitComboTpPtsAttr();
	mtInpAttr::SetComboCdTpPts( Mstr( "����"));
	mtInpAttr::InitComboPtsMbr();
	mtInpAttr::SetComboCdMbr( Mstr( "204"));

	WindowCtrl::MmWndKReDraw();

	Msg::OperationMsg( MC_OPRT_ROOF);								// �X�e�C�^�X�o�[�̑���\������"��������"��\��

	mhTpPts* pTpPts	= BuzaiCode::MhGetpTpPts( mtInpAttr::GetCurIdTpPts());
	mtInpMode::SetComboInpKb( pTpPts->GetPTInpKb());
	mtInpMode::SetComboCdMarume( pTpPts->GetPTCdMarume());

	MFOREVER {
		pgJim.m_n = 0;
		GifInp.m_n = 0;
		ist1 = mtInput::GetAreaI( &pgJim, &GifInp);

		if ( ist1 == MTRT_SYSTEMSTOP || ist1 == MTRT_CAN)
			break;
		MmPackAreaI( &pgJim, &GifInp);
		if (pgJim.m_n < 3)
			continue;

		HaitiCmd::MmPresetCmd();

		ist1 = mtHaitiIn::RoofPlc( pgJim, GifInp, pth);

		WindowCtrl::MmWndKReDraw();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// �X�e�C�^�X�o�[�̑���\������""��\��
}

/////////////////////////////////////////////////////////////////////////////
//	�n����ނ�����̒n�����̐��������i���ĕ���ł�����̂��P�ɂ܂Ƃ߂�

static void	MmPackAreaI(
						MgPolyg2*	pPg1,			// (I O) �n�����
						MgGInt*		pGifInp			// (I O) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				)
{
	MINT	ist1;
	MINT	icb, icc;
	MINT	ic0, ic1, ic2;
	MgLine2	ln1;
	bool	fmabiki = false;

	ic0 = 0;
	icb = pPg1->m_n - 1;
	ic1 = 0;
	for ( ic2=1; ic2<=pPg1->m_n; ic2++) {
		ln1 = MgLine2( pPg1->m_p[icb], pPg1->m_p[ic1]);
		if ( ic2 == pPg1->m_n)
			icc = 0;
		else
			icc = ic2;

		if (pGifInp->m_i[icc] == pGifInp->m_i[ic1])				// ����n������ނ̏ꍇ��
			MGeo::ChkPt2OnLn2WS( pPg1->m_p[icc], ln1, &ist1);		//	���i���ۂ��𒲂ׂ�
		else													// �قȂ�n������ނ̏ꍇ��
			ist1 = 0;											//	�񒼐i�Ƃ���

		if (MF_CHECK_OR( ist1, MC_ON_LINE)) {					// ���i�@�Ԉ���
//			if ( icc != 0) {
				pPg1->m_p[ic0] = pPg1->m_p[icc];
				pGifInp->m_i[ic0] = pGifInp->m_i[icc];
//			}
			fmabiki = true;
		} else {												// �񒼐i
			if (fmabiki) {
				pPg1->m_p[ic0] = pPg1->m_p[ic1];
				pGifInp->m_i[ic0] = pGifInp->m_i[ic1];
			}
			icb = ic1;
			ic0++;
		}
		ic1 = ic2;
	}
	pPg1->m_n = ic0;
}		

} // namespace MC