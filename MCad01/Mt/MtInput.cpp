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
#define DLL_EXPORT_MC_INPUT_DO
#include "MrAPI.h"
#include "MhPlcPartsLib.h"

#define		MC_YANE_TAKASA_HOSEI 97.

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//	�A�����������Q�_���͗p�̂Q�_�ڂ̓���(�O�Ǔ��͗p)

MINT mhInput::GetLenEPt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;

	Msg::GuidanceMsg( MC_GUID_SYUUTEN);
	irt = Window::DragObject(  MC_RBND_LINE, (void*)&pLn->p[0], &pt1);// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڂ����
																// �h���b�M���O���[�h�J�n
	if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
		MQUIT;
	if ( irt == MTRT_RBTNDWN) {
//		MmWndKReDraw();
		Window::DragModeEnd();									// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
		MQUIT;
	}
	mhInput::Marume( pt1, &pt2);
	pLn->p[1] = pt2;
exit:
	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	�����`������

MINT mhInput::GetRect2Pt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;
	MINT		iSeq = 0;						// ���̓V�[�N�G���X

	MFOREVER {
		if ( iSeq == 0) {
			Msg::GuidanceMsg( MC_GUID_AREA_SITEN);
			irt = MtAskForPoint( &pt1);							// �P�_�ڂ����
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)		// �V�X�e���X�g�b�v�܂��̓L�����Z��
				break;
			if ( irt != MTRT_LBTNDWN)							// �}�E�X���{�^���łȂ��ꍇ�́A
				continue;										//	�ē���
			mhInput::Marume( pt1, &pt2);
			pLn->p[0] = pt2;
			iSeq = 1;

		} else {												// ( iSeq == 1)
			Msg::GuidanceMsg( MC_GUID_AREA_TAIKAKUTEN);
			irt = Window::DragObject(  MC_RBND_RECT, (void*)&pLn->p[0], &pt1);	// ���o�[�o���h�}�`�\�����Ȃ���Ίp�_�����
																// �h���b�M���O���[�h�J�n
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {
//				MmWndKReDraw();									// �P�_�L�����Z��
				Window::DragModeEnd();							// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�I���j
				iSeq = 0;
				continue;
			}
			if ( irt != MTRT_LBTNDWN)							// �}�E�X���{�^���łȂ��ꍇ�́A
				continue;										//	�ē���
			mhInput::Marume( pt1, &pt2);
			pLn->p[1] = pt2;
			break;
		}
	}

	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	������

MINT mhInput::GetArea(
						MgPolyg2D*	o_ppg1		// �Q�c���p�`
				)
{
	MINT		irt;
	MgPolyg2D	PgS(20);
	MgPoint2D	pt1, pt2;
	MgMinMaxR2D	mMM;
	CPoint		ptMouthL;
	MINT 		iCdInpKb;
	MINT		iSeq = 0;						// ���̓V�[�N�G���X

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();		// �J�����g�E�B���h�E�擾
	
	iCdInpKb = z_mnIA.GetComboInpKbCd();

	MFOREVER {
		if ( iSeq == 0) {										// �P�_�ڂ̓���
			Msg::GuidanceMsg( MC_GUID_AREA_SITEN);
			irt = MtAskForPoint( &pt1);							// �_�����

		} else {												// �Q�_�ڈȍ~�̓���
			iCdInpKb = z_mnIA.GetComboInpKbCd();
			if ( iCdInpKb == MP_INPKB_AREA) {
				Msg::GuidanceMsg( MC_GUID_AREA_TAIKAKUTEN);		// �Ίp�Q�_�^�C�v���
				irt = Window::DragObject( MC_RBND_RECT, (void*)o_ppg1->m_p, &pt1);	// ���o�[�o���h�}�`�\�����Ȃ���Ίp�_�����
																// �h���b�M���O���[�h�J�n

			} else {											// ���R���̓^�C�v���
				if ( iSeq == 1)
					Msg::GuidanceMsg( MC_GUID_AREA_HOUKOUTEN);	// �Q�_�ځ@�����_
				else
					Msg::GuidanceMsg( MC_GUID_AREA_TUUKATEN);	// �R�_�ڈȍ~�@�ʉߓ_
				irt = Window::DragObject( MC_RBND_POLYGON, (void*)o_ppg1, &pt1);		// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڈȍ~�����
																// �h���b�M���O���[�h�J�n
			}
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;												// �V�X�e���X�g�b�v�܂��̓R�}���h�L�����Z��

		if ( irt == MTRT_RBTNDWN) {								// �}�E�X�E�{�^��
			if ( iSeq == 0) {									//	�P�_�ڂ̓��͂̏ꍇ�́A
				iCdInpKb = MP_INPKB_AREA + MP_INPKB_FREE - iCdInpKb;//	���͓_�敪�����R���́��Ίp���́A�܂��́A�Ίp���́����R���͂ɕύX
//E				z_mnIA.SelectComboInpKbnByInpKbnCd( iCdInpKb);
				z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, iCdInpKb);

			} else {											//	�Q�_�ڈȍ~�̓��͂̏ꍇ�́A
				iSeq --;										//	�P�_�L�����Z��
				( *o_ppg1) --;									//	�|���S���̍��W���P�_���
			}
			if ( o_ppg1->m_n == 0) {
				Window::DragModeEnd();							// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�I���j
				iSeq = 0;										// ���̓��͂� �P�_�ڂ̓��͂��� �ĊJ
			}
			continue;
		}
		if ( irt != MTRT_LBTNDWN)								// �}�E�X���{�^���łȂ��ꍇ�́A
			continue;											//	�ē���

		mhInput::Marume( pt1, &pt2);								// ���W���ۂ߂�

		if ( iSeq > 1 && pt2 == o_ppg1->m_p[0]) 
			break;												// �J�n�_�Ɠ���ʒu�̏ꍇ�͋����͏I���Ƃ���
		if ( iSeq > 0 && pt2 == o_ppg1->m_p[iSeq-1]) { 
			;													// �Ō�̓_�Ɠ���ʒu�̓_�͎̂Ă�
		} else {
			( *o_ppg1) += pt2;									// �قȂ�ʒu�̓_�̓|���S���ɒǉ�����
			iSeq ++;
		}

		if ( iSeq == 2 && iCdInpKb == MP_INPKB_AREA) {
			mMM.SetInit();
			mMM.Ins2( o_ppg1->m_p[0]);
			mMM.Ins2( o_ppg1->m_p[1]);
			o_ppg1->m_p[0] = mMM.min;
			o_ppg1->m_p[1] = MgPoint2D( mMM.max.x, mMM.min.y);
			o_ppg1->m_p[2] = mMM.max;
			o_ppg1->m_p[3] = MgPoint2D( mMM.min.x, mMM.max.y);
			o_ppg1->m_n = 4;
			break;												// �Ίp�Q�_�̂Q�_�ڂ̓��͏I���͋����͏I���Ƃ���
		}
	}
	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	�����Q�_�A�����P�_���� �{�@�������ނ̗̈������킷�R�_�ڂ̓���
//
// �z�u�R�[�h�������\�����t���ۂ߂̏ꍇ�́A
// �ŏ��̓_�̓��͂Ń}�E�X�E�{�^���܂��̓V�t�g�L�[�������Ȃ���̓��͂́A�����ʑI����
// �����ʂ������������ʂ�������΁A�ȍ~�͂��̉����ʏ�̕��ނƂ݂Ȃ��A
// �����ʂ�������Ȃ���΁A�����ʑI���̓t���[�̏�����ԂƂȂ�
// �Ԓl: 0: ����
//		 1: 
MINT mhInput::GetLen2Pt(
						MINT		i_iMode,	// ���̓��[�h
												//				�@0: �����Q�_���́i�������ނ̏ꍇ�́A���s�l�ӌ`��\���j
												//				�@1: �A�������Q�_�̏I�_����
												//						�n�_�͑O�����(pLn)�̏I�_�Ƃ���
												//				�@2: �����P�_����
						MgPoint2D*	io_ptln,	// �܂�ߍ��W�i�����Q�_���W �{�@�������ނ̗̈������킷�R�_�ځj
						MgPoint2D*	io_ptln_org	// �I���W�i�����W�i�����Q�_���W �{�@�������ނ̗̈������킷�R�_�ځj 
				 )
{
	MINT		ist1;

	MINT		irt;
	MINT		iGuid;
	MINT		nflag;
	MINT		iSeq = 0;						// ���̓V�[�N�G���X
	MINT		iNum;

	if ( i_iMode == 1) {										// �A�������Q�_�̏I�_���͂�
		io_ptln[0] = io_ptln[1];								//		�O����͂̏I�_���n�_�Ƃ���
		iSeq = 1;
	}
	MFOREVER {
		if ( iSeq == 0) {
			// �n�_����
			if ( i_iMode == 0)
				iGuid = MC_GUID_SITEN;							// �����Q�_�n�_����
			else
				iGuid = MC_GUID_HAITITEN;						// �����Q�_�z�u�_����
            Msg::GuidanceMsg( iGuid);

			irt = MtAskForPoint( &io_ptln_org[0]);				// �P�_�ڂ����

			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)		// �V�X�e���X�g�b�v�܂��̓L�����Z��
				break;
			if ( z_mnIA.GetComboPlcCd() == MP_HAICD_YANEKOUSEISENZUKE) {
																// �z�u�R�[�h�������\�����t���ۂ�
				nflag = MtGetNFlag();							// ���z�L�[(nflag)�擾�i1:�L�[���͖����A5:shift�L�[���͂���)
				if ( irt == MTRT_RBTNDWN || MF_CHECK_OR( nflag, MK_SHIFT)) {	
																// �}�E�X�E�{�^���܂��̓V�t�g�L�[��������Ă���ꍇ�͉����ʂ�������
																// �����ʂ�������΁A�ȍ~�͂��̉����ʏ�̕��ނƂ݂Ȃ��A
																// �����ʂ�������Ȃ���΁A�����̏�ԂƂȂ�
					mhHaitiIn::SetCurRfm( mhHaitiIn::SrchRfm( MC_PRI_MIN_AREA, io_ptln_org[0]));
					WindowCtrl::MmWndKReDraw();
					continue;
				}
			}
			if ( irt != MTRT_LBTNDWN)							// �}�E�X���{�^���łȂ��ꍇ�́A
				continue;										//	�ē���
			mhInput::Marume( io_ptln_org[0], &io_ptln[0]);
			iSeq = 1;

		} else if ( iSeq == 1) {
			// �I�_����
			if ( i_iMode <= 1)
				iGuid = MC_GUID_SYUUTEN;						// �����Q�_���͂ƘA�������Q�_�̏I�_����
			else
				iGuid = MC_GUID_HOUKOUTEN;						// �����Q�_���͂̕����_����
			Msg::GuidanceMsg( iGuid);

			irt = Window::DragObject( MC_RBND_LINE, (void*)io_ptln, &io_ptln_org[1]);
																// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڂ����
																// �h���b�M���O���[�h�J�n
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {							// �}�E�X�E�{�^��
//				MmWndKReDraw();
				Window::DragModeEnd();							//	�h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
					iSeq = 0;									//	�����Q�_���� �܂��� �����P�_���͂̏ꍇ�͂P�_�ڂ��ē���	
				continue;
			}
			if ( irt != MTRT_LBTNDWN)							// �}�E�X���{�^���łȂ��ꍇ�́A
				continue;										//	�Q�_�ڂ��ē���
			mhInput::Marume( io_ptln_org[1], &io_ptln[1]);
			ist1 = z_mmIA.GetComboAttrI( MC_CMB_HONS, &iNum);
//S			iNum = z_mnIA.GetHonsu();							// 
			iSeq = 2;
			if ( ( i_iMode != 1) && ( iNum == MC_INT_AREA)) {	// (�����Q�_���� �܂��� �����P�_����)�@���@iNum == 9998: ��������
//S				iSeq = 2;
			} else {
				irt = 0;
				break;
			}

		} else {												// ( iSeq == 2)
			// �������ޗ̈����
			Window::EraseDragging();
			iGuid = MC_GUID_MULTI_BUZAIAREA;
			Msg::GuidanceMsg( iGuid);

			irt = Window::DragObject( MC_RBND_PARALOG, (void*)io_ptln, &io_ptln_org[2]);	// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڂ����
																// �h���b�M���O���[�h�J�n
			if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
				break;
			if ( irt == MTRT_RBTNDWN) {							// �}�E�X�E�{�^��
				WindowCtrl::MmWndKReDraw();
				Window::DragModeEnd();								//	�h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
				iSeq = 1;										//	�Q�_�ڂ��ē��͂���
				continue;
			}
			if (  irt != MTRT_LBTNDWN) {						// �}�E�X���{�^���łȂ��ꍇ�́A
				continue;										//	�R�_�ڂ��ē���
			}
			mhInput::Marume( io_ptln_org[2], &io_ptln[2]);
			iSeq = 3;											// �R�_�ړ��͍ς�
			irt = 0;
			break;
		}
	}

	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	�P�_����

MINT mhInput::Get1Pt(
						MgPoint2D*	ppt1,			// (  O) ���͊ۂߓ_
						MgPoint2D*	ppt1_org		// (  O) ���̓I���W�i���_
				 )
{
	MINT	irt;
	MINT	iGuid;

	iGuid = MC_GUID_SITEN;
	Msg::GuidanceMsg( iGuid);

	irt = MtAskForPoint( ppt1_org);								// �P�_�ڂ����

	if ( irt != MTRT_SYSTEMSTOP && irt != MTRT_CAN) {
		mhInput::Marume( *ppt1_org, ppt1);
	}
	return irt;
}

/*
/////////////////////////////////////////////////////////////////////////////
//	�����`������

MINT mhInput::GetRect2Pt( MgLine2D*	pLn)
{
	MINT		irt;
	MgPoint2D	pt1, pt2;

	MmWndInfo* pWndInfo = MmWndKGetCurWnd();					// �J�����g�E�B���h�E���擾����

	do {
		Msg::GuidanceMsg( MC_GUIDMSG_KUKAKU_SITEN);
		irt = MtAskForPoint( &pt1);								// �P�_�ڂ����
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN)
			continue;
		pWndInfo->MarumeGrid( pt1, &pt2);
		pLn->p[0] = pt2;

		Msg::GuidanceMsg( MC_GUIDMSG_KUKAKU_TAIKAKUTEN);
		irt = Window::DragObject(  MC_RBND_RECT, (void*)&pLn->p[0], &pt1);	// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڂ����
																// �h���b�M���O���[�h�J�n
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN) {
			MmWndKReDraw();										// �P�_�L�����Z��
			continue;
		}
		pWndInfo->MarumeGrid( pt1, &pt2);
		pLn->p[1] = pt2;
	} while (irt == MTRT_RBTNDWN);

	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}
*/

/////////////////////////////////////////////////////////////////////////////
//	������ 
//	�e�ӂɁ@�V�t�g�L�[�L���̃t���O�t��

MINT mhInput::GetAreaI(
						MgPolyg2D*	pPg1,			// (  O) �n�����
						MgGInt*		pGifInp			// (  O) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				)
{
	MINT			irt;
	MINT			ic;
	MgPolyg2D		PgS(20);
	MgPoint2D		pt1, pt2;

	MINT iCdInpKb = z_mnIA.GetComboInpKbCd();

	for ( ic=0;;ic++) {
		if ( ic == 0) {
			Msg::GuidanceMsg( MC_GUID_JIM_SITEN);
			irt = MtAskForPoint( &pt1);							// �P�_�ڂ����
		} else {
			if ( ic == 1) {
//				Msg::GuidanceMsg( MC_GUIDMSG_JIMAWARI_HOUKOUTEN);
				Msg::GuidanceMsg( MC_GUID_JIM_TUUKATEN);
			} else {
				Msg::GuidanceMsg( MC_GUID_JIM_TUUKATEN);
			}
			irt = Window::DragObject( MC_RBND_POLYGON, (void*)pPg1, &pt1);	// ���o�[�o���h�}�`�\�����Ȃ���Q�_�ڈȍ~�����
																// �h���b�M���O���[�h�J�n
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;												// �V�X�e���X�g�b�v�܂��̓R�}���h�L�����Z��

		if ( irt == MTRT_RBTNDWN) {
			if ( ic > 0) {
				ic -= 2;										// �P�_�L�����Z��
				(*pGifInp) --;
				(*pPg1) --;										// �|���S���̍��W���P�_���
			} else {
				iCdInpKb = MP_INPKB_AREA + MP_INPKB_FREE - iCdInpKb;	// ������ | ���R���� | 
//E				z_mnIA.SelectComboInpKbnByInpKbnCd( iCdInpKb);
				z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, iCdInpKb);	// ���͓_�敪�I��p�̃R���{�{�b�N�X�ɕ\������
			}
			if ( pPg1->m_n == 0) {
				Window::DragModeEnd();							// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
				ic = -1;										// ���̓��͂� IC = 0 ��� �ĊJ
			}
			continue;
		}

		MINT nflag = MtGetNFlag();								// ���z�L�[(nflag)���擾����i1:�L�[���͖����A5:shift�L�[���͂���)

		mhInput::Marume( pt1, &pt2);								// ���W���ۂ߂�

		if ( ic > 1 && pt2 == pPg1->m_p[0]) {
			pGifInp->m_i[0] = nflag;
			break;												// �J�n�_�Ɠ���ʒu�̏ꍇ�͋����͏I���Ƃ���
		} else if ( ic > 0 && pt2 == pPg1->m_p[ic-1]) { 
			ic--;												// �Ō�̓_�Ɠ���ʒu�̓_�͎̂Ă�
		} else {
			(*pGifInp) += nflag;
			(*pPg1) += pt2;										// �قȂ�ʒu�̓_�̓|���S���ɒǉ�����
		}
	}
	Window::DragModeEnd();										// �h���b�M���O���[�h�I���i���o�[�o���h�}�`�\�����[�h�j
	return irt;
}

/////////////////////////////////////////////////////////////////////////////
//	�ۂ�
void mhInput::Marume(
				const	MgPoint2D	&Pi,
						MgPoint2D*	pPo
				)
{
	MINT		ist;
	MgVect2D		vtDis;
	MREAL		rDis_2;
	MINT		ic1, ic2;

	MREAL		rDisMin_2;
	MgPoint2D	Po, P0;

	MINT		iCdPlc;											// �z�u�R�[�h
	MINT		iCdMarume;										// �O���b�h�ۂߕ����l
	MgPoint2D	PtGrid;
	MgLine2D		Lnm[2];
	MGGLINE2( GLnk, 10);

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();		// �J�����g�E�B���h�E���擾����

	MINT iKai = z_mnIA.GetInpKai();

	iCdMarume = z_mnIA.GetComboMarumeCd();
	iCdPlc = z_mnIA.GetComboPlcCd();

	if ( iCdPlc == MP_HAICD_KABESINZUKE ||
		iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {									// �ǐc�t���ۂ߁@�܂��́@�����\�����t���ۂ�
		// �t�߂̊ۂߑΏې��������߂�
		if ( iCdPlc == MP_HAICD_KABESINZUKE) {									// �ǐc�t���ۂ߂̏ꍇ�́A�Ŋ�̕ǐc�����߂�
			mhInput::GetMarumeKabeLine( iKai, Pi, &GLnk);
		} else if ( iCdPlc == MP_HAICD_YANEKOUSEISENZUKE) {						// �����\�����t���ۂ߂̏ꍇ�́A�Ŋ�̉����\���������߂�
			mhInput::MmGetMarumeYaneLine( iKai, Pi, &GLnk);
		}
		// �����{�̊ۂߑΏې������������ꍇ�͌�_���߂��ɂ���Ȃ炻�̌�_��Ԃ�
		rDisMin_2 = MREALMAX;
		if ( GLnk.m_n >= 2) {
			for ( ic1=0; ic1<GLnk.m_n - 1; ic1++) {
				for ( ic2=ic1+1; ic2<GLnk.m_n; ic2++) {
					ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], GLnk.m_ln[ic2], &P0);
					if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
						vtDis = P0 - Pi;
						rDis_2 =MGeo::Abs_2( vtDis);
						if ( rDis_2 < rDisMin_2) {
							rDisMin_2 = rDis_2;
							Po = P0;
						}
					}
				}
			}
		}
		if ( rDisMin_2 < MC_MARUME_TOL * MC_MARUME_TOL)
			MQUIT;
	} else {
		GLnk.m_n = 0;
	}
				
//	iCdMarume = z_mnIA.GetComboMarumeCd();

	// �O���b�h�ۂ߂Ȃ��̏ꍇ
	if ( iCdMarume == 0) {
		if ( GLnk.m_n == 0) {
			// �ǐc�ł̊ۂ߂Ȃ�(�܂��͌��̕ǂ��Ȃ�)�̏ꍇ�́A���͈ʒu�����̂܂ܕԂ�
			*pPo = Pi;
			return;
		} else {
			// �ǐc�ۂ߂ŕǂƂ̏d�Ȃ肠��̏ꍇ�́A�ł��߂��ǐc��̈ʒu��Ԃ�
			rDisMin_2 = MREALMAX;
			for ( ic1=0; ic1<GLnk.m_n; ic1++) {
				MGeo::PerpPtLn2( Pi, GLnk.m_ln[ic1], &P0);
				vtDis = P0 - Pi;
				rDis_2 =MGeo::Abs_2( vtDis);
				if ( rDis_2 < rDisMin_2) {
					rDisMin_2 = rDis_2;
					Po = P0;
				}
			}
	        MQUIT;
		}
	}

	// �O���b�h�ۂ߂���̏���
	pWndInfo->GetMarumeGridLine( iCdMarume, Pi, Lnm);
	if ( GLnk.m_n == 0) {
		// �ǐc�ł̊ۂ߂Ȃ�(�܂��͌��̕ǂȂ�)�̏ꍇ�́A�O���b�h�ۂ߈ʒu�����̂܂ܕԂ�
		ist = MGeo::Intr2Ln2( Lnm[0], Lnm[1], pPo);
		if ( !MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
			*pPo = Pi;
		}
		return;
	} else {
		// �ǐc�ۂ߂ŕǂƂ̏d�Ȃ肠��̏ꍇ�́A�ǐc�ƃO���b�h���Ƃ̌�_�ōł��߂��ʒu��Ԃ�
		rDisMin_2 = MREALMAX;
		for ( ic1=0; ic1<GLnk.m_n; ic1++) {
			for ( ic2=0; ic2<2; ic2++) {
				ist = MGeo::Intr2Ln2( GLnk.m_ln[ic1], Lnm[ic2], &P0);
				if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
					vtDis = P0 - Pi;
					rDis_2 = MGeo::Abs_2( vtDis);
					if ( rDis_2 < rDisMin_2) {
						rDisMin_2 = rDis_2;
						Po = P0;
					}
				}
			}
		}
		MQUIT;
	}
exit:
	*pPo = Po;
}

} // namespace MC