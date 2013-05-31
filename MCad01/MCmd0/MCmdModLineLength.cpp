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
//#include "MhParts1.h"
//#include "MhPlcPartsLib.h"

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	���u���ނ̒�������
	void MCmdMdLineLength()
{
	MINT		irt;
	MINT		ist1;
	MINT		ic1;
	MgPoint2D	pt1, pt2, pt2m;
	MgPoint3D	Pt1, Pt2, Pt2m;
	MgLine2D		ln1;
	MgLine3D		Ln1;
	MgPolyg2D	Pg1(20);
//	MINT		iIdPartsSpec;
//	mhPartsSpec*	pPartsSpec;
	bool		bFirst = TRUE;
	MINT		iKati;
//	MINT		iMulti;
	MINT		iCrsC;

	MINT		iBuzaiCd;
	MgPolyg2D	pgHitBzi;
	mhPlcParts* pBziInfo1;
	mhPlcParts* pBziInfo2;
	mhPlcParts* pbTchBziI[MSZ_CROSS_BZI];
	mhPlcParts* pbCrsBziI[MSZ_CROSS_BZI];
	mhPlcParts* pbTchBziO[MSZ_CROSS_BZI];
	mhPlcParts* pbCrsBziO[MSZ_CROSS_BZI];

	mhPlcParts* pbFRtoTCBzi[MSZ_CROSS_BZI];
	mhPlcParts* pbTCtoFRBzi[MSZ_CROSS_BZI];
	mhPlcParts* pbTCtoTCBzi[MSZ_CROSS_BZI];

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_MOD_BUZAI);							// �X�e�C�^�X�o�[�̑���\������"���ޏC��"��\��

//E	z_mnIA.InitComboAttrXqt( MP_AT_ADJLNG);							// �������͗p�R���{�{�b�N�X�𕔍ޒ��������p�ɂ���
//SS	z_mnIA.RibbonIO( MINIT_COMBO_ATTR, MP_AT_ADJLNG);
	z_mmIA.InitComboAttrEntry( MP_AT_ADJLNG);						// ���ޒ��������p�̑������̓R���{�{�b�N�X��\��

	MmWndInfo* pWndInfo = WindowCtrl::GetCurWndInfo();			// �J�����g�E�B���h�E���擾����
	Window::CurWndFocus();											// �t�H�[�J�X���J�����g�E�B���h�E�ɐݒ肷��

	MFOREVER {
		Window::SetDispSelParts( NULL);

		Msg::GuidanceMsg( MC_GUID_MOD_BUZAILENGTH1);				// "���ނ̒����������̒[�����w�����ĉ�����"
		irt = MtAskForPoint( &pt1);

		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		iBuzaiCd = NULL;
		if ( pBziInfo1 = mhHaitiIn::SrchBuzai( pWndInfo, pt1, iBuzaiCd, &pgHitBzi)) {
			Window::SetCurBziFig( &pgHitBzi);						// �J�����g�I��(����������)�̕���(����������)�`���ݒ肷��
			WindowCtrl::ReDrawWnd();
		} else {
			Window::ClrCurBziFig();									// �J�����g�I���̕��ތ`����N���A����
			continue;
		}

		Window::SetDispSelParts( NULL);

		Msg::GuidanceMsg( MC_GUID_MOD_BUZAILENGTH2);				// "���ނ̒�����������w�����ĉ�����"
		irt = MtAskForPoint( &pt2);

		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		iBuzaiCd = NULL;
		pBziInfo2 = mhHaitiIn::SrchBuzai( pWndInfo, pt2, iBuzaiCd, &pgHitBzi);
		if ( pBziInfo1 == pBziInfo2)								// �������������ނƒ��������敔�ނƓ��ꕔ�ނ�I���̏ꍇ�͍��W�w���Ƃ݂Ȃ�
			pBziInfo2 = NULL;

		Pt1 = MgPoint3DC( pt1);

		Window::DrawHitBzi( pWndInfo, &pgHitBzi);					//	�q�b�g���ށi���������敔�ށj��\������
																	//	�i���\���q�b�g���ނ�������ɁA�q�b�g���ނ�\������j
		ist1 = z_mnIA.GetCheckAttr( MC_CHK_KATI, &iKati);			// ���������`�F�b�N�{�b�N�X�̏����}�[�N���擾����(1:����,0:����)
		ist1 = z_mnIA.GetCheckAttr( MC_CHK_INTC, &iCrsC);			// �������ޒ����`�F�b�N�{�b�N�X�̒����}�[�N���擾����(1:����,0:�Ȃ�)

		mhHaitiIn::MmSrchCrossBuzai( pWndInfo, pBziInfo1, iBuzaiCd, pbTchBziI, pbCrsBziI);
																	// �������������ނƒ����O�ɐG��Ă��镔�ތQ�ƌ������Ă��镔�ތQ�����߂�
		if ( pBziInfo2) {
			ist1 = mhHaitiIn::MhAdjBzL( iKati, pBziInfo1, Pt1, pBziInfo2);	// ��������
		} else {
			mhInput::Marume( pt2, &pt2m);
			Pt2m = MgPoint3DC( pt2m);
			mhHaitiIn::MhAdjBzL( pBziInfo1, Pt1, Pt2m);
		}

		if ( ist1 == MC_PARALLEL) {
			Pt2 = MgPoint3DC( pt2);
			mhHaitiIn::MhAdjBzL( pBziInfo1, Pt1, pBziInfo2, Pt2);		// ���������ނƒ����敔�ނ����s���̒���
		}
			
		mhHaitiIn::MmSrchCrossBuzai( pWndInfo, pBziInfo1, iBuzaiCd, pbTchBziO, pbCrsBziO);
																	// �������������ނƒ�����ɐG��Ă��镔�ތQ�ƌ������Ă��镔�ތQ�����߂�
			
		mhHaitiIn::MhChngCrossBuzai( pbTchBziI, pbCrsBziI, pbTchBziO, pbCrsBziO, 
								   pbFRtoTCBzi, pbTCtoFRBzi, pbTCtoTCBzi);
		if ( iCrsC == 1) {
			MgLine3D 	LnBzi;
			MgPoint3D	Pt0;
			// ����Ă��� �� �ڐG�@�܂��́@����
				// ���������@�܂��́@����
			for ( ic1=0; pbFRtoTCBzi[ic1]; ic1++) {
				LnBzi = pbFRtoTCBzi[ic1]->GetPIPlcIti();
				Pt0 = (LnBzi.p[0] + LnBzi.p[1]) / 2.;
				mhHaitiIn::MhAdjBzL( 0, pbFRtoTCBzi[ic1], Pt0, pBziInfo1);
			}
			// �ڐG�@�܂��́@���� �� ����Ă���
/*
			for ( ic1=0; pbTCtoFRBzi[ic1]; ic1++) {
				// �A���@�܂��́@����
				LnBzi = pbTCtoFRBzi[ic1]->GetPIPlcIti();
				Pt0 = (LnBzi.p[0] + LnBzi.p[1]) / 2.;
				MhAdjBzL( 0, pbTCtoFRBzi[ic1], Pt0, pBziInfo1);
			}
*/
			// �ڐG�@�܂��́@���� �� �ڐG�@�܂��́@����
				// ���������@�܂��́@����
			for ( ic1=0; pbTCtoTCBzi[ic1]; ic1++) {
				LnBzi = pbTCtoTCBzi[ic1]->GetPIPlcIti();
				Pt0 = (LnBzi.p[0] + LnBzi.p[1]) / 2.;
				mhHaitiIn::MhAdjBzL( 0, pbTCtoTCBzi[ic1], Pt0, pBziInfo1);
			}
		}
		Window::ClrCurBziFig();
		Window::EraseHitBzi();
		WindowCtrl::ReDrawWnd();
		Msg::ClearErrorMsg();
	}
	Window::SetDispSelParts( -1);
	Msg::OperationMsg( MC_OPRT_BASE);								// �X�e�C�^�X�o�[�̑���\������""��\��
}

} // namespace MC
