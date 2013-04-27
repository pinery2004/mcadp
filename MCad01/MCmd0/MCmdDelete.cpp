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
#include "MrAPI.h"
#include "MmValid.h"

namespace MC
{

void MCmdLineDelete()
{
	MINT			ist1;
	MINT			irt;
	MgPoint2		pt1, pt2;
	MgPoint2		ptK[2];
	MgPoint2		ptW[2];
	MgLine2			Ln1;
	MgPolyg2		pg1(20);
	MINT			iIdPartsSpec, iIdPartsSpecB;
	MINT			iKaiC;
	MINT			iGpC, iGpB;
	mhPartsSpec*		pPartsSpec;
	mhPlcParts*		pPlcEn;
	MPOSITION		pos1;
	Window::CurWndFocus();

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_DEL_PARTS);							// �X�e�C�^�X�o�[�̑���\������"���ޒǉ�"��\��

	iKaiC = z_mnIA.GetInpKai();
	iGpC = z_mnIA.GetKCdGp();
	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);

	MFOREVER {
		Msg::GuidanceMsg( MC_GUID_DEL_PARTS);
		irt = MtAskForPoint( &pt1);								// �P�_�ڂ����
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)			// �V�X�e���X�g�b�v�܂��̓L�����Z��
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// �}�E�X�E�{�^�� || ���j���[����
			continue;

		HaitiCmd::MmPresetCmd();
		// �w�����ނ���������
		for ( pPlcEn = HaitiDb::MdGetHeadParts( &pos1); pPlcEn!=0;
			  pPlcEn = HaitiDb::MdGetNextParts( &pos1)) {

			if ( pPlcEn->GetPIKai() != iKaiC)
				continue;										// �قȂ�K�̕��ނ͕\�����Ȃ�
			iGpB = pPlcEn->GetPIPartsSpec()->GetPTCdGp();
			iIdPartsSpecB = pPlcEn->GetPIIdPartsSpec();
			if ( iGpB != iGpC || iIdPartsSpecB != iIdPartsSpec)
				continue;										// �قȂ�\���̕��ނ͕\�����Ȃ�

			if ( !MmChkValidParts( pPlcEn))						// �I�v�V�����Ɨ����̃`�F�b�N
				continue;

			ptW[0] = *(MgPoint2*)&(pPlcEn->GetPIPlcIti( 0));
			ptW[1] = *(MgPoint2*)&(pPlcEn->GetPIPlcIti( 1));

			MgVect2	VtW = ptW[1] - ptW[0];
			MgVect2	VtUtW = MGeo::UnitizeV2( VtW);
			MgVect2	VtWidthR = (pPlcEn->GetMbWidthR() + pPlcEn->GetPISinZure()) * VtUtW.RotR90(); 
			MgVect2	VtWidth = pPlcEn->GetMbWidth() * VtUtW.RotL90(); 
			pg1.m_n = 0;
			pg1 += (ptW[0] - pPlcEn->GetPILenHosei( 0) * VtUtW + VtWidthR);
			pg1 += (ptW[1] + pPlcEn->GetPILenHosei( 1) * VtUtW + VtWidthR);
			pg1 += (pg1.m_p[1] + VtWidth);
			pg1 += (pg1.m_p[0] + VtWidth);

			MGeo::ChkPt2OnPg2WS( pt1, pg1, &ist1);
			if ( ist1 == MC_IN_BORDER) {
				if (mhHaitiIn::ChkParts( NULL, MP_GP_TAIRYOKU, Mstr( "��"), NULL, pPlcEn))
					IeModel::MhKabeSetUpFlg();
				break;
			}
		}
		// �폜����
		if ( pPlcEn != 0)
			HaitiDb::MdPartsDelete( pos1);

		IeModel::MhNormKabe( 0);

		WindowCtrl::MmWndKReDraw();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// �X�e�C�^�X�o�[�̑���\������""��\��
}

void MCmdRoofDelete()
{
	MINT			irt;
	MgPoint2		pt1, pt2;
	MgPoint2		ptK[2];
	MgPoint2		ptW[2];
	MgPoint3		Py1;
	MgLine2			Ln1;
	MgPolyg2		pg1(20);
	MINT			ic1, ic2;
	MhRoofInfo*		pRoofEn;
	MPOSITION		pos1;
	Window::CurWndFocus();
	MgMinMaxR3		rMmMdl;
	MgMinMaxR2		rmmMdl;
	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_DEL_ROOF);							// �X�e�C�^�X�o�[�̑���\������"�����폜"��\��

	MFOREVER {
		Msg::GuidanceMsg( MC_GUID_DEL_ROOF);
		irt = MtAskForPoint( &pt1);								// �P�_�ڂ����
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)			// �V�X�e���X�g�b�v�܂��̓L�����Z��
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// �}�E�X�E�{�^�� || ���j���[����
			continue;

		HaitiCmd::MmPresetCmd();
		// ��������������
		for ( pRoofEn = HaitiDb::MdGetHeadRoof( &pos1); pRoofEn!=0;
			  pRoofEn = HaitiDb::MdGetNextRoof( &pos1)) {
			if ( !MmChkValidRoof( pRoofEn))						// �I�v�V�����Ɨ����̃`�F�b�N
				continue;
			// ������MINMAX�����߂�
			rMmMdl.SetInit();
			for ( ic1=0; ic1<pRoofEn->GetpGRfm()->m_n; ic1++) {
				for ( ic2=0; ic2<pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_n; ic2++) {
					Py1 = pRoofEn->GetpGRfm()->m_st[ic1].m_Pg.m_P[ic2];
					rMmMdl.Ins3( Py1);
				}
			}
			rmmMdl = MgMinMaxR2( MgPoint2C( rMmMdl.min), MgPoint2C( rMmMdl.max));
			if ( MGeo::ChkPt2InMMR2( pt1, rmmMdl))
				break;
		}

		// �폜����
		if ( pRoofEn != 0)
			HaitiDb::MdRoofDelete( pos1);

		WindowCtrl::MmWndKReDraw();
		Msg::ClearErrorMsg();
	}
	Msg::OperationMsg( MC_OPRT_BASE);								// �X�e�C�^�X�o�[�̑���\������""��\��
}

} // namespace MC
