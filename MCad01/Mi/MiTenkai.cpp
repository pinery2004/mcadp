//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmTenkai.cpp
//
//		�Z���W�J
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
#include "MhDefParts.h"
#include "MmLib.h"
#include "McSystemProperty.h"

#include "MmCmd.h"
#include "resource.h"
#include "..\\MCAD\\resource.h"

#define DLL_EXPORT_TENKAI_DO
#include "MmTenkai.h"

#include "MsBitSet.h"
#include "MdList.h"
#include "MdLib.h"

#include "MhInp.h"
#include "MhInpAttr.h"

namespace MC
{

//static	CMmDialogTenkai* z_pDlgTenkai = NULL;		// ���[�h���X�o�[�W�����_�C�A���O�̕\���p
JTTenkaiPr 	JTTenkai::z_TenkaiPara;				// �Z���W�J�p�����[�^
MgMat2E		JTTenkai::z_matTenkai[MX_NJUKO];	// �Z���W�J�}�g���b�N�X
MgMat2E		JTTenkai::z_matRTenkai[MX_NJUKO];	// �Z���W�J�t�}�g���b�N�X
MgMinMaxR2	JTTenkai::z_mmTenkai[MX_NJUKO];		// �Z�˗̈�l�����l����
MINT		JTTenkai::z_iJuko;					// �I���Z��
MUINT		JTTenkai::z_iTenkai[MX_NJUKO];		// �Z���W�J����
/*
	JTTenkaiPr

	MUCHAR nJuko;								// �Z�ː�
	MUCHAR ifH[MX_NJUKO];						// 0: �R�s�[�A1: ���]�R�s�[
	MUCHAR nJuko[MX_NJUKO];						// �W�J���Z��
	MREAL rMDJuko[MX_NJUKO];					// �c�����I�t�Z�b�g
	MREAL rDJuko[MX_NJUKO];						// �Z�ˉ��s
	MREAL rWJuko[MX_NJUKO];						// �Z�ˋ�
*/
/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�Z���W�J��������������
void JTTenkai::InitJTT()
{
	MINT ifH = 0;
	for (MINT ic=0; ic<MX_NJUKO; ic++) {
//		z_TenkaiPara.iSelJuko = z_TenkaiPara.iRefJuko = 1;
		z_TenkaiPara.ifH[ic] = ifH;
		ifH = 1 - ifH;
		z_TenkaiPara.nOJuko[ic] = 2;
		z_TenkaiPara.rMDJuko[ic] = 0;
		z_TenkaiPara.rDJuko[ic] = 10920;
		z_TenkaiPara.rWJuko[ic] = 7280;
	}
	z_TenkaiPara.nOJuko[0] = 1;
	z_TenkaiPara.nJuko = 4;
	z_iJuko = 0;								// ���L���I���i�Z�ˑI���Ȃ��j�ɐݒ�
}
/*
/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�ݒ����
void JTTenkai::InpJTT(
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	if ( z_pDlgTenkai) {
		z_pDlgTenkai->BringWindowToTop();
	} else {
		z_pDlgTenkai = new CMmDialogTenkai( pWnd);
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�ݒ�I��
void JTTenkai::EndJTT()
{
	z_pDlgTenkai = NULL;
}
*/
/////////////////////////////////////////////////////////////////////////////
//	�Z�ˋ��̑n��
void JTTenkai::CreJTTArea()
{
	MINT	ist1;
	MgLine3 Ln1;
	mhPlcInfo*	pHaiTenkai[MX_NJUKO];							// �Z���W�J�f�[�^
	MPOSITION	pPlcPos[MX_NJUKO];								// �Z�ˏZ���W�J�f�[�^���R�[�h�ʒu
	MgPolyg2	pg1(4);

	ist1 = mhHaitiIn::GetParts( 0, MP_GP_KABE, Mstr( "�Z���W�J"), NULL, 3, pHaiTenkai, pPlcPos);
	ASSERT( ist1 >= 0);											// �Z���W�J�f�[�^�@�I�[�o�t���[�@<ERROR>
	if ( ist1 == 1)
		HaitiDb::MdPartsDelete( pPlcPos[0]);					// �Z���W�J�f�[�^���폜

	ist1 = mhHaitiIn::GetParts( 0, MP_GP_KABE, Mstr( "�Z�ˋ��"), NULL, MX_NJUKO, pHaiTenkai, pPlcPos);
	ASSERT( ist1 >= 0);											// �Z�ˋ��f�[�^�@�I�[�o�t���[�@<ERROR>
	for (MINT ic=0; ic<ist1; ic++) {
		HaitiDb::MdPartsDelete( pPlcPos[ic]);					// �Z�ˋ��f�[�^���폜
	}

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_KABE, MP_BR_OTHER, Mstr( "�Z�ˋ��"));
//E	z_mnIA.GetComboAttrA();
	z_mnIA.RibbonIO( MGET_COMBO_ATTRA, NULL);

	MgPoint2	ptJuko[2] = { MgPoint2( 0., 0.), MgPoint2( 0., 0.)};
	MgMinMaxR2	mm = MgMinMaxR2( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for (MINT ic=0; ic<z_TenkaiPara.nJuko; ic++) {
		pg1.m_n = 0;
		ptJuko[0] = MgPoint2( ptJuko[1].x, z_TenkaiPara.rMDJuko[ic]);
		ptJuko[1] = MgPoint2( ptJuko[0].x + z_TenkaiPara.rWJuko[ic], 
							  z_TenkaiPara.rMDJuko[ic] + z_TenkaiPara.rDJuko[ic]);

		pg1 += ptJuko[0];
		pg1 += MgPoint2( ptJuko[1].x, ptJuko[0].y);
		pg1 += ptJuko[1];
		pg1 += MgPoint2( ptJuko[0].x, ptJuko[1].y);

		Ln1.p[0] = MgPoint3C( pg1.m_p[0]);
		Ln1.p[1] = MgPoint3C( pg1.m_p[1]);
		HaitiCmd::MmPartsPlc( Ln1.p, MgVect3( 0., 0., 1.), &pg1);		// �Z�ˋ��i�̈�^�j�̕��i�z�u

		mm.Ins2( ptJuko[0]);
		mm.Ins2( ptJuko[1]);
	}
	mm.Ins2( MgPoint2( 0., 0.));

	ist1 = z_mnIA.SetRibbonBarEnt( MP_GP_KABE, MP_BR_OTHER, Mstr( "�Z���W�J"));
//E	z_mnIA.GetComboAttrA();
	z_mnIA.RibbonIO( MGET_COMBO_ATTRA, NULL);

	pg1.m_n = 0;
	pg1 += mm.min;
	pg1 += MgPoint2( mm.max.x, mm.min.y);
	pg1 += mm.max;
	pg1 += MgPoint2( mm.min.x, mm.max.y);

	JTTenkaiPr* pAuxTenkai = (JTTenkaiPr*)new char[sizeof( JTTenkaiPr)];
	*pAuxTenkai = z_TenkaiPara;
//	mhPlcInfo* pInfo = &g_hInpPIAttr;
	mtPlcInp::SetpAuxTenkai( pAuxTenkai);

	Ln1.p[0] = MgPoint3C( pg1.m_p[0]);
	Ln1.p[1] = MgPoint3C( pg1.m_p[1]);
	HaitiCmd::MmPartsPlc( Ln1.p, MgVect3( 0., 0., 1.), &pg1);				// �Z���W�J�i�̈�^�j�̕��i�z�u

	z_mnIA.SetInpKai( 1);
	mtPlcInp::SetInpKai( 1);
	MINT nGrid[4];
	nGrid[1] = MINT(mm.min.x / mcs::GetReal( MM_REAL_PITCH) - 3.99);							// ��
	nGrid[2] = MINT(mm.min.y / mcs::GetReal( MM_REAL_PITCH) - 2.34 - z_TenkaiPara.nJuko /3.);	// ��
	nGrid[3] = MINT(mm.max.x / mcs::GetReal( MM_REAL_PITCH) + 3.99);							// ��
	nGrid[0] = MINT(mm.max.y / mcs::GetReal( MM_REAL_PITCH) + 1.99 + z_TenkaiPara.nJuko);		// �k

	WindowCtrl::MmGridNumSet( nGrid);										// �����ݒ�
	WindowCtrl::MmGridNumXqt();												// �O���b�h���ύX�\��

//DDD	MmWndKReDraw();											// MmGridNumXqt�Ŋ��ɕ\���ς�
}

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�}�g���b�N�X��ݒ肷��
void JTTenkai::SetJTTMAT()
{
	MINT	ic;
	MgMat2E matSt;

	matSt.SetUnit();

	for ( ic=0; ic<z_TenkaiPara.nJuko; ic++) {
		z_matTenkai[ic] = matSt;
		z_mmTenkai[ic].min = MgPoint2( matSt.m[2][0], z_TenkaiPara.rMDJuko[ic]);

		matSt.m[2][0] += z_TenkaiPara.rWJuko[ic];
		z_mmTenkai[ic].max = MgPoint2( matSt.m[2][0], z_mmTenkai[ic].min.y + z_TenkaiPara.rDJuko[ic]);

		if ( z_TenkaiPara.ifH[ic]) {
			z_matTenkai[ic].m[0][0] = -1.;
			z_matTenkai[ic].m[2][0] = matSt.m[2][0];
		}
		z_matTenkai[ic].m[1][2] = z_TenkaiPara.rMDJuko[ic];

		z_matRTenkai[ic] = z_matTenkai[ic];
		z_matRTenkai[ic].m[2][0] = - z_matTenkai[ic].m[2][0];
		z_matRTenkai[ic].m[2][1] = - z_matTenkai[ic].m[2][1];
	}
	for ( ic=0; ic<MX_NJUKO; ic++)
		z_iTenkai[ic] = 0;
	for ( ic=0; ic<z_TenkaiPara.nJuko; ic++)
		z_iTenkai[ic] = z_iTenkai[z_TenkaiPara.nOJuko[ic]-1] | (1 << ic);
}

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�p�����[�^���擾����
JTTenkaiPr* JTTenkai::GetJTTPara()
{
	return &z_TenkaiPara;
}

/////////////////////////////////////////////////////////////////////////////
//	�Z���W�J�p�����[�^��ݒ肷��
void JTTenkai::SetJTTPara(
						JTTenkaiPr* pAuxTenkai		// (I  ) �Z���W�J�p�����[�^
				)
{
	z_TenkaiPara = *pAuxTenkai;
	JTTenkai::SetJTTMAT();
}

/////////////////////////////////////////////////////////////////////////////
//	�Z�ˑI������
void JTTenkai::SetJTTJuuko(
						MINT iJuko					// (I  ) �I���Z�˔ԍ��@�܂��́@0
				)
{
	z_iJuko = iJuko;
}

} // namespace MC
