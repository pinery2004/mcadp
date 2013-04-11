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
#include "MhInpAttr.h"

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
	iMode = z_mn.GetMode();
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
//S	z_mn.SetKCdGp( MP_GP_YANE);
//	z_mn.SetKCdBr( MP_BR_OTHER);
//	z_mn.InitComboAttr( MP_AT_YANE);								// �������͗p�R���{�{�b�N�X�𑮐��l���͖����ɂ���
//	z_mn.InitComboPartsNm();
//	z_mn.SelectComboPartsNmByPartsNm( Mstr( "����"));
//	z_mn.InitComboPartsMbr();
//	z_mn.SelectComboMbrCdByMbrCd( Mstr( "204"));

	ist1 = z_mn.SetRibbonBarEnt( MP_GP_YANE, MP_BR_OTHER, Mstr( "����"), Mstr( "204"));

	WindowCtrl::MmWndKReDraw();

	Msg::OperationMsg( MC_OPRT_ROOF);								// �X�e�C�^�X�o�[�̑���\������"��������"��\��

	mhPartsSpec* pPartsSpec	= BuzaiCode::MhGetpPartsSpec( z_mn.GetCurPartsNmId());
//E	z_mn.SelectComboInpKbnByInpKbnCd( pPartsSpec->GetPTCdInpKb());
	z_mn.RibbonIO( MSET_INPUT_KUBUN_CD, pPartsSpec->GetPTCdInpKb());	// ���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
//E	z_mn.SelectComboMarumeByMarumeCd( pPartsSpec->GetPTCdMarume());
	z_mn.RibbonIO( MSET_INPUT_MARUME_CD, pPartsSpec->GetPTCdMarume());	// �ۂ߃R�[�h��I��p�̃R���{�{�b�N�X�ɕ\������

	MFOREVER {
		pgJim.m_n = 0;
		GifInp.m_n = 0;
		ist1 = mhInput::GetAreaI( &pgJim, &GifInp);

		if ( ist1 == MTRT_SYSTEMSTOP || ist1 == MTRT_CAN)
			break;
		MmPackAreaI( &pgJim, &GifInp);
		if ( pgJim.m_n < 3)
			continue;

		HaitiCmd::MmPresetCmd();

		ist1 = mhHaitiIn::RoofPlc( pgJim, GifInp, pth);

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

		if ( pGifInp->m_i[icc] == pGifInp->m_i[ic1])				// ����n������ނ̏ꍇ��
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
