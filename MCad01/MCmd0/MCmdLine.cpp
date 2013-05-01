//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdLine.cpp
//
//		�����ނ̔z�u�R�}���h
//
//	[�@�\] 
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"
#include "MmCmd.h"
#include "MainFrm.h"
#include "MmDialogKAttr.h"
#include "MmCmdMsg.h"

#define		MC_YANE_TAKASA_HOSEI 97.

namespace MC
{

void MCmdLineAdd();
void MCmdLineDelete();

////////////////////////////////////////////////////////////////////////////
//	���̃R�}���h���͂܂ő҂�

void MCmdWait()
{
	MINT		irt;
	MgPoint2	pt1;

	Msg::OperationMsg( MC_OPRT_WAIT);							// �X�e�C�^�X�o�[�̑���\������"����҂�"��\��

	MFOREVER {
		irt = MtAskForPoint( &pt1);								// �V�X�e���X�g�b�v�܂��̓L�����Z���܂ő҂�
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// �}�E�X�E�{�^�� || ���j���[����
			continue;
	}
}

////////////////////////////////////////////////////////////////////////////
//	���̓��[�h�ɏ]�����ނ�ǉ��܂��͍폜����

void MCmdLine(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
	)
{
	MINT iMode;
	iMode = z_mnIA.GetMode();
	if ( iMode == MP_MD_CREATE) {
		z_mmIA.MmDialogKAttr();
		MCmdLineAdd();
	} else {
		if ( iMode == MP_MD_DELETE)
			MCmdLineDelete();
	}
}

////////////////////////////////////////////////////////////////////////////
//	���ނ�ǉ�����

void MCmdLineAdd()
{
	MINT		ist;
	MINT		irt;
	MgPoint2	pt1, pt2, pt1_org;
	MgPoint3	PtMltBziAr;
	MgPoint2	ptln1[3], ptln1_org[3], ptln1_chk[2];
	MgLine3		Ln1;
	MgVect2		vln;
	MgVect3		vUp;
	MgLine2		ln1;
	MgPolyg2	pg1(20);
	MINT		iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;
	bool		bFirst = TRUE;
	MINT		iMode;

	MhRfm	*pRfm1, *pRfm2;

	MgPlane3	plnYane;

	MREAL rIntrv;												// �Ԋu
	MgVect3 VtArea;
	MgVect3 VtBziIntrv;

	MINT iNum;
	MINT ic1;

	Window::CurWndFocus();
	CMainFrame*	pMainFrame;
	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_MYMESSAGERIBBONIO);

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_PARTS);							// �X�e�C�^�X�o�[�̑���\������"���ޒǉ�"��\��

	z_mnIA.RibbonIO( MINIT_COMBO_ATTR, MP_AT_AUTO);				// ���ޓ��͎�ނɍ������������̓R���{�{�b�N�X��\��

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
	z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, pPartsSpec->GetPTCdInpKb());	// ���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
	z_mnIA.RibbonIO( MSET_INPUT_MARUME_CD, pPartsSpec->GetPTCdMarume());// �ۂ߃R�[�h��I��p�̃R���{�{�b�N�X�ɕ\������
																		// �R���{�{�b�N�X�Ɋۂ߃R�[�h��\������
	mhHaitiIn::SetCurRfm( NULL);

	MFOREVER {
		// �z�u���W����
		//
		switch (pPartsSpec->GetPTCdInpKb())
		{
		case MP_INPKB_1PT:										// 1�_����
			irt = mhInput::Get1Pt( &pt1, &pt1_org);
			break;
		case MP_INPKB_DIR1PT:									// �����P�_����
			iMode = 2;
			irt = mhInput::GetLen2Pt( iMode, ptln1, ptln1_org);
			break;
		case  MP_INPKB_LEN2PT:									// �����Q�_����
			if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), Mstr( "�O��")) == 0 && !bFirst) {
				// �O�ǂ�2�Ԗڈȍ~�̕ǂ͘A�������Q�_���͂Ƃ��Ō�ɔz�u�����I�_���n�_�Ƃ��ďI�_�̂ݓ��͂���
				iMode = 1;
			} else {
				iMode = 0;										// ���́A�����Q�_����
			}
			irt = mhInput::GetLen2Pt( iMode, ptln1, ptln1_org);
			bFirst = FALSE;
			break;
		case MP_INPKB_AREA:										// �̈�(���)����
			pg1.m_n = 0;
			irt = mhInput::GetArea( &pg1);
//			irt = mtInput::GetRect2Pt( &ptln1);
			break;
		case MP_INPKB_FREE:
			pg1.m_n = 0;
			irt = mhInput::GetArea( &pg1);
			break;
        default:
			irt = 0;
//			ASSERT( 0);											// ���͓_�敪�G���[�@<ERROR>
			break;
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		// �z�u
		//
		if ( pPartsSpec->GetPTCdInpKb() == MP_INPKB_AREA) {
			// �̈�(���)�z�u�A�P�_�ڂƂQ�_�ڂ��n�_�I�_�Ƃ��Ĕz�u����
			Ln1.p[0] = MgPoint3C( pg1.m_p[0]);
			Ln1.p[1] = MgPoint3C( pg1.m_p[1]);
			z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);			//		���i�d�l,���@�`���Ƒ����l���͗p�R���{�{�b�N�X�̒l�𕔕i�z�u���̓f�[�^�Ɏ�荞��
			HaitiCmd::MmPartsPlc( Ln1.p, MgVect3( 0., 0., 1.), &pg1);	// �̈�^�̕��i�z�u
			
		} else {												// ���̑�
			// ���ޔz�u
			ist = z_mmIA.GetComboAttrI( MC_CMB_HONS, &iNum);	// �������ނ̔z�u�{��
			vUp = MgVect3( 0., 0., 1.);
			
			if ( pPartsSpec->GetPTCdIzon() >= MP_IZNCD_YANEMENNARI) {
				// �����ʂȂ�̏ꍇ�͑Ώۉ����ʂɉ�����������ݒ肵�A���ނ̏�����������ʂɐ��������ɐݒ肷��
				if ( mhHaitiIn::GetCurRfm()) {
					// �J�����g�����ʂ��I������Ă���ꍇ�͂��̉����ʂȂ��Z���W�����߂�
					plnYane = mhHaitiIn::GetCurRfm()->m_Pln;
					
				} else {
					// �I������Ă��Ȃ��ꍇ�́A���͓_�̈ʒu�ɂ�艮���ʂ�I������
					vln = ptln1[1] - ptln1[0];
					vln.SetUnitize();
					ptln1_chk[0] = ptln1[0] + 10.f * vln;
					ptln1_chk[1] = ptln1[1] - 10.f * vln;
					pRfm1 = mhHaitiIn::SrchRfm( MC_PRI_MIN_HIGHT, ptln1_chk[0]);
					pRfm2 = mhHaitiIn::SrchRfm( MC_PRI_MIN_HIGHT, ptln1_chk[1]);
					if ( pRfm1) {								//
						plnYane = pRfm1->m_Pln;					//	���͓_�̂P�_�ڂ������ʏ�̏ꍇ�́A���̉����ʂȂ��Z���W�����߂�
					} else if ( pRfm2) {						//
						plnYane = pRfm2->m_Pln;					//	���͓_�̂Q�_�ڂ̂݉����ʏ�̏ꍇ�́A���̉����ʂȂ��Z���W�����߂�
					} else {
						plnYane = MgPlane3( MgVect3( 0., 0., 1.), 0.);	//	���͓_�������ʏ�łȂ��ꍇ�̉��z������(Z=0.)
					}
				}
				Ln1 = MgLine3( MgPoint3C( ptln1[0], plnYane.GetZ( ptln1[0])),
							   MgPoint3C( ptln1[1], plnYane.GetZ( ptln1[1])));
				if ( iNum == MC_INT_AREA)						//		�{����̈�Ŏw�肷�镡�����ޔz�u�^�C�v��
					PtMltBziAr = MgPoint3C( ptln1[2], plnYane.GetZ( ptln1[2]));

				MREAL rYHHosei = MC_YANE_TAKASA_HOSEI;
				if ( !MGeo::Zero( plnYane.v.z) ) 
					rYHHosei /= plnYane.v.z;
				Ln1.p[0] += MgPoint3( 0., 0., rYHHosei);
				Ln1.p[1] += MgPoint3( 0., 0., rYHHosei);
				PtMltBziAr += MgPoint3( 0., 0., rYHHosei);
				if ( pPartsSpec->GetPTCdIzon() == MP_IZNCD_YANEMENNARIENCYOKU)
					vUp = plnYane.v;
			} else {
				// ���̑��̏ꍇ(�����ʂȂ�łȂ��ꍇ)
				Ln1 = MgLine3C( MgLine2(ptln1));				//			Z���W=0
				PtMltBziAr = MgPoint3C( ptln1[2]);
			}
			
			// �z�u�{���ƕ����t���Ԋu�����߂�
			//
			ist = z_mmIA.GetComboAttrR( MC_CMB_INTR, &rIntrv);	//		�Ԋu
			if ( iNum == MC_INT_AREA) {							//			�{����̈�Ŏw�肷�镡�����ނ̔z�u
				VtArea = PtMltBziAr - Ln1.p[0];
				iNum = MGMIN( MINT( MGeo::Abs( VtArea) / rIntrv + 1.0 + MGPTOL->D),
							  MMAX_BZI_HONSU);					//			���ޔz�u�{�����ő�100�{�Ɍ���
				if ( iNum > 1)
					VtBziIntrv = rIntrv * MGeo::UnitizeV3( VtArea);
				else
				VtBziIntrv = MgVect3( 1., 0., 0.);				//			dumy
					
			} else {											//			�{���w��ɂ�镡�����ނ̔z�u
				MgVect2 vtutBzi = MGeo::UnitizeV2( MgVect2C( Ln1.p[1] - Ln1.p[0]));
				if ( pPartsSpec->GetPTCdInpKb() != MP_INPKB_DIR1PT)	//			�����P�_�̏ꍇ�͕����Ɍ������ĕ����z�u����
					vtutBzi.SetRotR90();						//			�����Q�_�̏ꍇ�͉E�������ɕ����z�u����
				VtBziIntrv = rIntrv * MgVect3C( vtutBzi);
				
			}
			// Undo������
			HaitiCmd::MmPresetCmd();
			// ���͂���������ݒ肷��
			if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {
				z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);		//		���i�d�l,���@�`���Ƒ����l���͗p�R���{�{�b�N�X�̒l�𕔕i�z�u���̓f�[�^�Ɏ�荞��
			} else {
				z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);		//		���i�d�l,���@�`���Ƒ����l���͗p�R���{�{�b�N�X�̒l�𕔕i�z�u���̓f�[�^�Ɏ�荞��
			}
			// �{�����z�u����
			if ( iNum == 0) iNum = 1;							//		�{�������͂̏ꍇ�͂P�{�Ƃ���
			for ( ic1=0; ic1<iNum; ic1++) {
				HaitiCmd::MmPartsPlc( Ln1.p, vUp);				//		<<< ���ނ�z�u���� >>>
				Ln1 = Ln1 + VtBziIntrv;
			}
		}
		// �ǂ̐������𐮂���
		if ( pPartsSpec->GetPTCdBr() == MP_BR_KABE)
			IeModel::MhKabeSetUpFlg();							//		�ǃf�[�^�̏ꍇ�͐ڑ��ǂ�ǉ��A�C������
		IeModel::MhNormKabe( 1);
		// ��b�̐������𐮂���
		if ( pPartsSpec->GetPTCdBr() == MP_BR_KISO)
			IeModel::MhKisoSetUpFlg();							//		�ǃf�[�^�̏ꍇ�͐ڑ��ǂ�ǉ��A�C������
		IeModel::MhNormKiso( 1);
		// �ĕ\�����C���𔽉f����
		WindowCtrl::MmWndKReDraw();
		// ����I���ŁA�G���[�W�����N���A����
		Msg::ClearErrorMsg();
	}
	if ( mhHaitiIn::GetCurRfm()) {
		mhHaitiIn::SetCurRfm( NULL);							// �����ʂ̑I�����J������
		WindowCtrl::MmWndKReDraw();
	}
	Msg::OperationMsg( MC_OPRT_BASE);							// �X�e�C�^�X�o�[�̑���\������""��\��
}

/////////////////////////////////////////////////////////////////////////////
//	�\����������

/*
	MP_GP_KISO = 1,							// "��b"
	MP_GP_DODAI,							// "�y��"
	MP_GP_YUKA,								// "���g"
	MP_GP_KABE,								// "�ǘg�g"
	MP_GP_TAIRYOKU,							// "�ϗ͕�"
	MP_GP_TENJO,							// "�V��g"
	MP_GP_KOYA,								// "�����g"
	MP_GP_YAGIRI,							// "���"
	MP_GP_YANE								// "����"

	MP_BR_BUZAI,							// "����"
	MP_BR_KANAGU,							// "����"
	MP_BR_PANEL,							// "�p�l��"
	MP_BR_YANE,								// "����"
	MP_BR_KABE,								// "��"
	MP_BR_SENBUN,							// "����"
	MP_BR_KUKAKU,							// "���"
	MP_BR_CYUKI,							// "���L"
	MP_BR_OTHER = 9							// "���̑�"
*/

/////////////////////////////////////////////////////////////////////////////
//	��������

void MCmdStructRoof()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_YANE, MP_BR_BUZAI, Mstr( "����"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�\���V�����

void MCmdStructCeiling()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_TENJO, MP_BR_BUZAI, Mstr( "�V�䍪��"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�\���Ǔ���

void MCmdStructWall()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_KABE, MP_BR_BUZAI, Mstr( "���Ęg"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�\��������

void MCmdStructFloor()
{
	MINT	ist1;

	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

//S	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();
//
//	pMainFrame->SendMessage(1);




//S	z_mnIA.SetKCdGp( MP_GP_YUKA);
//E	z_mnIA.InitComboParts();
//U	z_mnIA.RibbonIO( MSET_COMBO_PARTS);		// ���i�I��p�̃R���{�{�b�N�X�ɕ\������
	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_YUKA, MP_BR_BUZAI, Mstr( "������"), Mstr( "210"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	�\���y�����

void MCmdStructDodai()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_DODAI, MP_BR_BUZAI, Mstr( "�y��"), Mstr( "404G"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	��b����

void MCmdKiso()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����
	CWnd*		pWnd = pWndInfo->GetWnd();

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_KISO, MP_BR_OTHER, Mstr( "�O���z��b"), Mstr( "120"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}


} // namespace MC