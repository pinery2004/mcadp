//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhRoof.cpp
//
//		�����ʂ𐶐�����
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgLib.h"
#include "MgGrp.h"

#include "MdList.h"
#include "MlLog.h"

#include "MhPlcParts.h"

#include "McSystemProperty.h"

#include "MmLib.h"
#include "MhRoof.h"
//#include "MhPlcPartsLib.h"

#define	 	MCMAXIESIZE		50000.								// �����ʍő剜�s��50m
#define		MCMINKSSIZE		1.

#define		MAXHAIKABE		500									// �ǔz�񐧌��l
#define		MAXGKABE		100									// �O�Ǎő吔(��)
#define		MAXRFMKJ		10									// �����ʌ`��ő�p��(��)

namespace MC
{

/*
//
// ---------------------( �R���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�����o��
//
inline MINT	MgDivide(								// (  O) �X�e�C�^�X
													//		 MC_NINT		(0): �����Ȃ�
													//		 MC_INT			(1): ��������
						MINT		Sel,			// (I  ) �I������
													//		 MC_IN_BORDER	(001): ����
													//		 MC_ON_BORDER	(002): �ӏ�
				const	MgULine3D	&ULn1,			// (I  ) ����
				const	MgPolyg3D	&Pg2,			// (I  ) ���p�`
						MgGLine3D	*GLn3			// (  O) ������̐����Q
				)
{
	GLn3->n = 0;
	return MgDivideAdd( Sel, ULn1, Pg2, GLn3);
}
*/

static void MgAndGLineOnULineAdd(
				const	MgGLine2D	&Gln1,			// (I  ) �����Q1	(1�̒�����̐����Q)
				const	MgGLine2D	&Gln2,			// (I  ) �����Q2	(�����Q1�Ɠ��꒼����̐����Q)
						MgGLine2D	*Glno			// (  O) �����Q1�Ɛ����Q2�Ƃ̏d�Ȃ��������̐����Q
													//		 ��0: �d�Ȃ�����Ȃ�
													//		 ��0: �d�Ȃ��������
				);

static bool MgChkRfmCls(									// (  O) true:	�����`�F�b�N�Ώۉ�����
													//		 false:	�����`�F�b�N�ΏۊO������
				const	MgLine3D		&LnJim1,		// (I  ) ������1�̒n����
				const	MgPlane3D	&Pln1,			// (I  ) ������1�̕��ʌW��
				const	MgLine3D		&LnJim2,		// (I  ) ������2�̒n����
				const	MgPlane3D	&Pln2			// (I  ) ������2�̕��ʌW��
				);

////////////////////////////////////////////////////////////////////////////////////
//���z�@�@�@�@�@= �����@�@�@�@�@<�n������̉����ʂ̌��z,
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�������ȑ���9900, ��������99900
//					(10��������̉����ʂ̏オ���:�P��1/10��)
//�������{ = �\���_�Q�����
//
//�@�@�@�@�\���_�Q �@�@�@= (�����Q)�Q�@�@�@ <���[�_�̍��W:(X�Y)�Q (�A�����W�n)>
//�@�@�@�@����@�@�@�@�@= 1|2|3|4|5|6|7 <1:�����2:�ȑ��3:�R�4:�J�5:���6:������(����)�
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ 7:������(���z)>
//	�����\�����^�C�v�R�[�h
static	MREAL	McRfmOffset[] = {
				0.,			// MHRL_DUMMY,				// �_�~�[
				455.,		// MHRL_NOKI,				// ��
				300.,		// MHRL_KERABA,				// �����
				0.,			// MHRL_MUNE,				// ��
				0.,			// MHRL_RYOU,				// ��
				0.,			// MHRL_TANI,				// �J
				0.,			// NHRL_MIZUKIRI,			// ���؂�
				0.,			// MHRL_KATANAGARENOKI,		// �З��ꌬ
				0.,			// MHRL_YANEUEMIZUKIRI,		// �e�����̏�ɏ��q�����̍\����
				0.			// MHRL_YAGIRI				// ���
				};	

void MhRoofInfo::FreeAllAtr()
{ 
	MBFREE( m_pVer);
	MBFREE( m_pOpt1);
	MBFREE( m_pOpt2);

	m_GJim1.Free();
//	m_GJim2.Free();
//	m_GTn.Free();
	m_GKs1.Free();
//	m_GKs2.Free();
	m_GRfm.Free();
	m_GNUm.Free();
	m_GHm.Free();
	if ( m_pZukei) {
		MBFREE( m_pZukei->m_pNext);
		delete (char*)m_pZukei;
	}
}
void MhRoofInfo::InitAllAtr(
				MINT	ifPtr									// �C�j�V�����C�Y�͈� 1:�S�Ă̑��� 0:�����̈�|�C���^�̂�
				)
{
	m_pVer = NULL;
	m_pOpt1 = NULL;
	m_pOpt2 = NULL;
	m_GJim1.m_st = NULL;
	m_GJim1.m_n = m_GJim1.m_isz = 0;
	m_GKs1.m_st = NULL;
	m_GKs1.m_n = m_GKs1.m_isz = 0;
	m_GRfm.m_st = NULL;
	m_GRfm.m_n = m_GRfm.m_isz = 0;
	m_GNUm.m_Pg = NULL;
	m_GNUm.m_n = m_GNUm.m_isz = 0;
	m_GHm.m_Pg = NULL;
	m_GHm.m_n = m_GHm.m_isz = 0;
//
	m_pZukei = NULL;

	if ( ifPtr == 1) {
		m_iKai = 0;
//		m_Oya = NULL;											// �e����
		m_itpRf = 0;											// �����^�C�v
		m_rKb = 0;												// ���z
		m_rRkH = 0.;											// ����������ύX��
		m_rRfmA = 89.;											// �����ʌ���(89,140,182)
		m_rNUmA = 89.;											// �����ʌ���(89,140)
		m_rMnZ[0] = m_rMnZ[1] = 0.;								// ������ʂP�E�Q
		m_rNkD[0] = m_rNkD[1] = 0.;								// ���̏o
		m_rKrD[0] = m_rKrD[1] = 0.;								// ����΂̏o
		m_itpNU = 0;											// �����^�C�v�P�E�Q
		m_itpNS = 0;											// ����^�C�v�P�E�Q
		m_rHKmA = 0.;											// �@�B���ʌ���
		m_rNUk = 0.;											// �����Ԃ���
		m_rNkH = 0.;											// ���̍����i��`�h�[�}�p�j
		m_icdURS = 0;											// �������R�[�h
//		m_icdRR = 0;											// �剮���R�[�h

		m_imdDsp = 0;											// �\�����[�h (0: ������  1:�\����)
		m_colDispD = RGB( 0, 0, 0);								// �\���F�i�f�[�^�w��j
		m_colDispC = RGB( 0, 0, 0);								// �\���F�i���݁j
//		m_nDispM = NULL;										// �\�����i�ʁj
//		m_nDispL = NULL;										// �\�����i�����j

		m_nRtm = 0;												// ���ʐ�
		m_pifRitm = NULL;										// ���ʕ\��(�ʃt���O)  0:��  1:��
		m_pnPtRitm = NULL;										// ���ʕ\��(���_��)
		m_pPtRitm = NULL;										// ���ʕ\��(���_)
//		m_pLnRitm = NULL;										// ���ʕ\�����i�����j

//		MhTexture*			m_KsInfo[NKSINFO];					// �\�����
	}
}

////////////////////////////////////////////////////////////////////////////
//	�������͒l����荞�ݐݒ肷�� 
void MhRoofInfo::SetAttr()
{
	MINT	ist;
	MINT	iKobai;
	MREAL	rNokiDe;
	MREAL	rKerabaDe;

	ist = z_mmIA.GetComboAttrI( MC_CMB_KOBY, &iKobai);			// ���z
//S	iKobai = z_mnIA.GetKobai();
	m_rKb = MREAL( iKobai);

	ist = z_mmIA.GetComboAttrR( MC_CMB_NKDE, &rNokiDe);
//S	rNokiDe = z_mnIA.GetNokiDe();
	m_rNkD[0] = m_rNkD[1] = rNokiDe;							// ���̏o
	McRfmOffset[MHRL_NOKI] = rNokiDe;

	ist = z_mmIA.GetComboAttrR( MC_CMB_KRDE, &rKerabaDe);
//S	rKerabaDe = z_mnIA.GetKerabaDe();
	m_rKrD[0] = m_rKrD[1] = rKerabaDe;							// ����΂̏o
	McRfmOffset[MHRL_KERABA] = rKerabaDe;
}

////////////////////////////////////////////////////////////////////////////
//	�n�����ɃR�[�h��ݒ肷�� 
//  ���݂�m_itpRf==MHRF_YOSEMUNE�̂ݎg�p�ł���A������͂��ꂽ�V�t�g�L�[�ɂ��؂�Ȃ𔻒肵�Ă���
//	�܂��A�����_�͖��g�p
void MhRoofInfo::SetJimCd(
				const	MgPolyg2D	&pgJim,			// (I  ) �n�����
				const	MgGInt		&GifInp,		// (I  ) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				const	MgPoint2D	&pth			// (I  ) �����_
				)
{
	MINT	ic;
//	MINT	Id;
	MhJim	pgJimw;
	
	for ( ic=0; ic<pgJim.m_n; ic++) {
		pgJimw.m_p = pgJim.m_p[ic];
		int ii = sizeof( MhJim);
		m_GJim1 += pgJimw;
	}

	switch(m_itpRf) {
		case(MHRF_YOSEMUNE):									// ��
			for ( ic=0; ic<m_GJim1.m_n; ic++) {
				if ( MF_CHECK_OR( GifInp.m_i[ic], MK_SHIFT)) {
					m_GJim1[ic].m_icd = MHRL_KERABA;			// �n���R�[�h = ����
					m_GJim1[ic].m_rKb = 999;					// ���z(�P��:1/10)�@MgGetKobai
				} else {
					m_GJim1[ic].m_icd = MHRL_NOKI;				// �n���R�[�h = ����
					m_GJim1[ic].m_rKb = m_rKb;					// ���z(�P��:1/10)�@MgGetKobai
				}
			}
			break;
		case(MHRF_KIRITUMA):									// �؍�
/*
			MINT		ist;
			MINT		ic0, ic1;
			MgPoint2D	pt0;
			MgVect2D		v1;
			MREAL		rD2, rMinD2;

			Id = -1;
			rMinD2 = MREALMAX;
			ic0 = m_GJim1.n;
			for ( ic1=0; ic1<m_GJim1.n; ic1++) {
				ist = MgPerpPointLine2D( m_ptH, MgLine2D( m_GJim1[ic0].p, m_GJim1[ic1].p), &pt0);
				if ( ist == MC_ON_LINE) {
					rD2 = MgDist_2( pt0, m_ptH);				// �����̂Q��
					if ( rD2 < rMinD2) {
						Id = ic0;
						rMinD2 = rD2;
					}
				}
				ic0 = ic1;
			}

			Id &= 1;
			for ( ic=0; ic<m_GJim1.n; ic++) {
				if ( Id == 0) {
					m_GJim1[ic].iCd = MHRL_KERABA;				// �n���R�[�h = ����ΐ�
					m_GJim1[ic].rKb = 999;						// ���z(�P��:1/10) �܂��� 999:���� MgGetKobai
				} else {
					m_GJim1[ic].iCd = MHRL_NOKI;				// �n���R�[�h = ����
					m_GJim1[ic].rKb = m_rKb;					// ���z(�P��:1/10)�@MgGetKobai
				}
				Id = 1 - Id;
			}
			*/
			ms::SysError( MBCstr( "MhRoof"), MC_ERR_OTHER);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
//  �n�����ɑΉ����鉮���ʂ��쐬���� 
//		�����ʌ`��͏���ɉ������ꂽ�`��ō쐬����
void MhRoofInfo::CreateRfmForJim()
{
	MINT		ist;
	MINT		ic0, ic1;
	MhRfm		RfmI;
	MgPoint3D	Pth;
	MINT		iRfm0, iRfm1;
	MgPlane3D	Pln0, Pln1;
	MgULine3D	ULn1;
	MgLine3D		Ln0, Ln1, Ln2, Ln3;
	MgPoint3D	P0, P1;
//
//    �n�����ɑΉ����鉮���ʂ��쐬���� 
	ic0 = m_GJim1.m_n - 1;
	for ( ic1=0; ic1<m_GJim1.m_n; ic0=ic1,ic1++) {
		RfmI.m_icd = 0;
		if ( m_GJim1[ic1].m_icd == MHRL_NOKI) {
			RfmI.m_icd = MHRL_NOKI;
			RfmI.m_Pln = MgPlane2PointSlope3D( m_GJim1[ic0].m_p, m_GJim1[ic1].m_p, m_GJim1[ic1].m_rKb / 10.f);	// �n�_�E�I�_����z
		} else if ( m_GJim1[ic1].m_icd == MHRL_KERABA) {
			RfmI.m_icd = MHRL_YAGIRI;
			Pth = MgPoint3DC( m_GJim1[ic0].m_p);
			Pth.z += 1000.;
			RfmI.m_Pln = MgPlane3Point3D( MgPoint3DC( m_GJim1[ic0].m_p), MgPoint3DC( m_GJim1[ic1].m_p), Pth);			// �R�_
		}
		if ( RfmI.m_icd) {
			m_GRfm += RfmI;										// �����ʒǉ�
			int ii = sizeof( MhRfm);
			m_GJim1[ic1].m_iRfm = m_GRfm.m_n - 1;				// �n���ɔz��ԍ���ݒ�
		}
	}
//
//    �n�������O���猩�ĉE���ɐڑ����鉮���\�����i���������j���쐬���� 
	ic0 = m_GJim1.m_n - 1;
	for ( ic1=0; ic1<m_GJim1.m_n; ic0=ic1,ic1++) {
		iRfm0 = m_GJim1[ic0].m_iRfm;
		Pln0 = m_GRfm.m_st[iRfm0].m_Pln;						// �n�����ɐڑ����鉮����
		iRfm1 = m_GJim1[ic1].m_iRfm;
		Pln1 = m_GRfm.m_st[iRfm1].m_Pln;						// ���̒n�����ɐڑ����鉮����
		ist = MGeo::Intr2Pln3D( Pln0, Pln1, &ULn1);				// �����ʊԂ̌�������߂�
			ASSERT( ist == MC_INT);								// �񓏕��\�����쐬�G���[�@<ERROR>
		if ( ULn1.v.z < 0.0)									// ����̕�����������ɂ���
			ULn1.v = - ULn1.v;
		P0 = MgPoint3DC( m_GJim1[ic0].m_p);
		P1 = P0 + MCMAXIESIZE * ULn1.v;
		m_GJim1[ic0].m_LnR = MgLine3D( P0, P1);					// �O���猩�Ēn�����̉E���ɐڑ����鉮���\�����i�ő剄�������j
		if ( m_GJim1[ic0].m_icd == MHRL_KERABA ||
			m_GJim1[ic1].m_icd == MHRL_KERABA)
			m_GJim1[ic0].m_icdLnR = MHRL_KERABA;
		else {
			if ( ( MgVect2DC(Pln0.v) ^ MgVect2DC( Pln1.v)) > 0.)
				m_GJim1[ic0].m_icdLnR = MHRL_RYOU;
			else
				m_GJim1[ic0].m_icdLnR = MHRL_TANI;
		}
	}
//
//    �n�����ɑΉ����鉮���ʂɍ\�������쐬����i����ɉ��������̈�j 
	ic0 = m_GJim1.m_n - 1;
	for ( ic1=0; ic1<m_GJim1.m_n; ic0=ic1,ic1++) {
		iRfm1 = m_GJim1[ic1].m_iRfm;

		Ln1 = m_GJim1[ic0].m_LnR;
		Ln2 = m_GJim1[ic1].m_LnR;
		Ln0 = MgLine3D( Ln1.p[0], Ln2.p[0]); 
		ist = MGeo::Intr2Line3D( Ln1, Ln2, &P0);						// �n�����ɐڑ����鍶�E�̉����\�������������m�F

		m_GRfm.m_st[iRfm1].m_Pg   += Ln1.p[0];					// 0: �n����( ic1)�̍��̓_���A�n�����ɐڑ����鉮���ʌ`��̍ŏ��_�Ƃ��Ēǉ�
		m_GRfm.m_st[iRfm1].m_cdPg += m_GJim1[ic0].m_icdLnR;		// 0: ��O�̒n����( ic0)�̉E���̐����ݒ�
		m_GRfm.m_st[iRfm1].m_Pg   += Ln2.p[0];					// 1: �n����( ic1)�̉E�̓_���A�n�����ɐڑ����鉮���ʌ`��̂Q�Ԗڂ̓_�Ƃ��Ēǉ�
		m_GRfm.m_st[iRfm1].m_cdPg += m_GJim1[ic1].m_icd;		// 1: ���g�̒n����( ic1)�̐����ݒ�
		m_GRfm.m_st[iRfm1].m_cdPg += m_GJim1[ic1].m_icdLnR;		// 2: ���g�̒n����( ic1)�̉E���̐����ݒ�
		if ( MF_CHECK_OR( ist, (MC_INT | MC_CONNECTION))) {
			m_GRfm.m_st[iRfm1].m_Pg += P0;						// 2: ��������ꍇ�A�����_��ǉ�
		} else {
			m_GRfm.m_st[iRfm1].m_Pg += Ln2.p[1];				// 3,4: �������Ȃ��ꍇ�͗������������̒[�_��ǉ�
			m_GRfm.m_st[iRfm1].m_Pg += Ln1.p[1];
//			m_GRfm.m_st[iRfm1].m_cdPg += MHRL_DUMMY;			// 4: ��ӂ̐�����_�~�[�ɐݒ�
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//	���̉����ʂƂ̌����𒲂׌��������ŉ����ʌ`����J�b�g����
MINT MhRoofInfo::AdjustRfm1()						// (  O) �X�e�C�^�X�@0: ����@-1: �����ʌ`��쐬�G���[
{
	MINT		ist = -1;
	MINT		ist1;
	MINT		ic1, ic2;
	MINT		sel1;
	MgPlane3D	*pPln1, *pPln2;
	MgMat3E		MatXY;											// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3E		MatPln;											// XY���� to Pln �R�c�}�g���b�N�X
	MgLine2D		ln0;
	MgULine3D	ULn0;
	MgULine2D	uln1;
	MgGLine2D	Gln0, Gln1, Gln2, Gln3;
	MgGLine3D	GLn2;
	MgPolyg2D	pg0, pg1, pg3;
	MgPolyg3D	Pg0;
	MgGLine3D	GLnW;
//#ifdef LOGOUT
//MBLOGON;
//#endif
	for ( ic1=0; ic1<m_GRfm.m_n; ic1++) {
//#ifdef LOGOUT
//							MBLOGON;
//							Msprintf_s( mlLog::m_Str, Mstr( "******* ���� AdjustRfm ic1=%d\n"), ic1); MBLOGPRBF;
//#endif
		pPln1 = &m_GRfm.m_st[ic1].m_Pln;						// ������1�����o��

		MGeo::Mat3EPlntoXY( *pPln1, m_GRfm.m_st[ic1].m_Pg.m_P[0], &MatXY, &MatPln);	// �R�c���Q�c�p�ϊ��}�g���b�N�X�Ƌt�ϊ��}�g���b�N�X�����߂�

		MGeo::Polyg3Dto2D( m_GRfm.m_st[ic1].m_Pg, MatXY, &pg1);		// ������1�̌`����Q�����ɕϊ�����
//							m_GRfm.m_st[ic1].pg.Print( Mstr( "051114 m_GRfm.m_st[ic1].pg"));
//							pg1.Print( Mstr( "051114�� pg1"));
		ln0 = MgLine2D( pg1.m_p[0], pg1.m_p[1]);
		Gln0.m_n = 0;
		Gln0 += MgLine2D( pg1.m_p[1], pg1.m_p[2]);
		Gln0 += MgLine2D( pg1.m_p[pg1.m_n-1], pg1.m_p[0]);

		for ( ic2=0; ic2<m_GRfm.m_n; ic2++) {
//#ifdef LOGOUT
//							Msprintf_s( mlLog::m_Str, Mstr( "-------- ���� AdjustRfm ic2=%d\n"), ic2); MBLOGPRBF;
//#endif
			if ( ic1 == ic2)										// ���ꉮ���ʂ͖���
				continue;
			if ( m_GRfm.m_st[ic2].m_Pg.m_n == 0)
				MQUIT;
//			ASSERT(m_GRfm.m_st[ic2].pg.n != 0);
			pPln2 = &m_GRfm.m_st[ic2].m_Pln;					// ���̉�����2�����o��
			ist1 = MGeo::Intr2Pln3D( *pPln1, *pPln2, &ULn0);			// ��̉����ʂ̌������������߂�
																// �����ʂ͒n�����̏��ɕ���ł�����������̕�����
																// �Q�����ɂ�������x���傩�珬�̕����Ɍ������Ă���
			if ( ist1 != MC_INT) 
				continue;

			MGeo::ULine3Dto2D( ULn0,  MatXY, &uln1);					// �����������Q�����ɕϊ���
			ist1 = MGeo::DivideULinePolygon2D( MC_IN_BORDER | MC_ON_BORDER , uln1, pg1, &Gln1);
																// ������1�̌`����Ɋ܂܂������Q1�����߂�
//							Gln1.Print( Mstr( "051114 ������1�̌`����Ɋ܂܂������Q1 Gln1"));
			if ( ist1 != (MC_INT | MC_MATCH)) 
				continue;
																// �R�����ŉ�����2�̌`����Ɋ܂܂������Q2�����߂�
			if ( MgChkRfmCls( MgLine3D( m_GRfm.m_st[ic1].m_Pg.m_P), *pPln1,
							 MgLine3D( m_GRfm.m_st[ic2].m_Pg.m_P), *pPln2))
				sel1 = MC_IN_BORDER | MC_ON_BORDER;
			else
				sel1 = MC_IN_BORDER;
//				sel1 = MC_IN_BORDER | MC_ON_BORDER;

			ist1 = MGeo::DivideULinePolygon3D( sel1, ULn0, m_GRfm.m_st[ic2].m_Pg, &GLn2);
//							GLn2.Print( Mstr( "051114 ������2�̌`����Ɋ܂܂������Q2 GLn2"));
			if ( ist1 != (MC_INT | MC_MATCH)) 
				continue;
			MGeo::GLine3Dto2D( GLn2, MatXY, &Gln2);					// �����Q�Q���Q�����ɕϊ�����
//							Gln2.Print( Mstr( "051114 ������2�̌`����Ɋ܂܂������Q2 Gln2"));
			
			MgAndGLineOnULineAdd( Gln1, Gln2, &Gln3);			// (���꒼�����)�����Q1�Ɛ����Q2�̏d�Ȃ蕔�������o��
																// �i��: ���̓f�[�^�͎n�_X < �I�_X�ŁA �w�������т̃f�[�^�j
//			GLine2Dto3D( Gln3, MatPln, &GLnW);					// �f�o�b�O�p
			Gln0 += Gln3;
//							Gln0.Print( Mstr( "051114 �d�˂������Q�v Gln0"));
		}
		if ( Gln0.m_n > 1) {
			MGeo::MakeGPolygonFromLineInGLine2D( ln0, Gln0, &pg0);			// �n����������Ƃ������������������ŏ��̑��p�`�����
//							pg0.Print( Mstr( "051114 �������ŏ��̑��p�` pg0"));
			MGeo::Polyg2Dto3D( pg0, MatPln, &Pg0);						// �R�����ɖ߂�
//							Pg0.Print( Mstr( "051114 �������ŏ��̑��p�` Pg0"));
			m_GRfm.m_st[ic1].m_Pg = Pg0;						// �����ʌ`����C��
			for ( ic2=3; ic2<m_GRfm.m_st[ic1].m_Pg.m_n; ic2++)	// �����\�����̐�����_�~�[�ɐݒ肷��
				m_GRfm.m_st[ic1].m_cdPg += MHRL_DUMMY;
		}
	}
	ist = 0;
exit:
	return ist;
}

////////////////////////////////////////////////////////////////////////////
//	��K�O�ǂƂ̌����𒲂׌��������ŉ����ʌ`����J�b�g����
MINT MhRoofInfo::AdjustRfm2()						// (  O) �X�e�C�^�X�@0: ����@-1: �����ʌ`��쐬�G���[
{
	MINT		ist = 0;
	MINT		ist1;

	mhPlcParts* pHaiKabe[MAXHAIKABE+2];						// �ǃf�[�^
	MPOSITION	pPlcPos[MAXHAIKABE+2];						// �ǃf�[�^���R�[�h�ʒu
	MINT		nHaiKabe;										// �ǐ�
	mhPlcParts	HaiKabeI;										// �ǉ���

	MINT		ic1, ic2, ic3b, ic3, ic4b, ic4;

	this->Print( Mstr( "121205�O�ǂƂ̌����`�F�b�N�O�@����"));

	MGGLINE2(GlnGKb, MAXGKABE);
	MGGPOLYG2(GpgGKb, MAXGKABE, MAXGKABE, MAXGKABE);
	MGPOLYG2(pgRfm, MAXRFMKJ);
	MgGPolyg2D	GpgRfm(3);
	MgGPolyg3D	GPgRfm(3);
	MgGInt		GiCd(10);
	MgPolyg3D	*pPgRfm;
	MgGInt		*ppgCdRfm;
	MgPolyg3D	*pPgRfmN;
	MhRfm		Rfm;

	//�@�ƃ��f�����J�����g�K�̏�K�̑S�Ă̕ǂ��擾����
	MINT iKai = z_mnIA.GetInpKai() + 1;
	nHaiKabe = mhHaitiIn::GetParts( iKai, MP_GP_TAIRYOKU, NULL, Mstr( "�O��"), MAXHAIKABE, pHaiKabe, pPlcPos);
																// �ƃ��f�����J�����g�K�̏�K�̑S�Ă̕ǂ��擾����
	if ( nHaiKabe <= 0)
		return ist;												//		��K�O�ǂȂ�
	for ( ic1=0; ic1<nHaiKabe; ic1++)
		GlnGKb += MgLine2DC( pHaiKabe[ic1]->GetPIPlcIti());

	MGeo::MakeGPolygonInGLine2D( GlnGKb, &GpgGKb);
	if ( GpgGKb.m_n == 0)
		return ist;

	MgPlane3D	*pPln1;

//MBLOGON;
	for ( ic1=0; ic1<m_GRfm.m_n; ic1++) {
		pPln1 = &m_GRfm.m_st[ic1].m_Pln;						// ������1�����o��
		pPgRfm = &m_GRfm.m_st[ic1].m_Pg;
		ppgCdRfm = &m_GRfm.m_st[ic1].m_cdPg;

		//if ( MGeo::Zero( pPln1->v.z))								// XY���ʂɐ����̉����ʂ̓X�L�b�v
		//	continue;
		pgRfm = (*pPgRfm);										// XY���ʂɓ��e���Q������

		ist1 = MGeo::MergePgGPgtoGPolygon2D( MC_DIFF, pgRfm, GpgGKb, &GpgRfm);
		if ( ist1 == MC_MATCH)									// �����ʌ`�󂪊O�ǂƌ����Ȃ��ł��̂܂܎c��ꍇ��
			continue;											// �����ʌ`��̕ύX�Ȃ�
		GPgRfm.Set( GpgRfm, *pPln1);							// �������ʏ�̂R������

		if ( GPgRfm.m_n == 0) {									// �����ʌ`�󂪏�K�O�Ǔ��ɑS�ĉB���ꍇ�͍폜
			m_GRfm.m_st[ic1].m_Pg.m_n = 0;
			m_GRfm.m_st[ic1].m_cdPg.m_n = 0;
		} else {												// �����ʌ`��̈ꕔ���d�Ȃ�ꍇ�́A�����ʌ`��Ɖ����\�����R�[�h���C��
																// �����ɕ������ꍇ�͒ǉ�
			for ( ic2=0; ic2<GPgRfm.m_n; ic2++) {
				GiCd.m_n = 0;
				
				// �쐬���ꂽ�����ʖ��Ɍ��̉����ʂ��Q�Ƃ��ĉ����\�����R�[�h��ݒ肷��
				pPgRfmN = &GPgRfm.m_Pg[ic2];
				for ( ic3b=pPgRfmN->m_n-1,ic3=0; ic3<pPgRfmN->m_n; ic3b=ic3,ic3++) {
					
					for ( ic4b=pPgRfm->m_n-1,ic4=0; ic4<pPgRfm->m_n; ic4b=ic4,ic4++) {
						if ( MGeo::ChkLineOnLine3D( MgLine3D(pPgRfmN->m_P[ic3b], pPgRfmN->m_P[ic3]), MgLine3D(pPgRfm->m_P[ic4b], pPgRfm->m_P[ic4])))
							break;
					}
					if ( ic4 < pPgRfm->m_n)
						GiCd += ppgCdRfm->m_i[ic4];
					else
						GiCd += NHRL_MIZUKIRI;
				}
				if ( ic2 == 0) {
					(*pPgRfm) = (*pPgRfmN);							// �����ʌ`����C��
					(*ppgCdRfm) = GiCd;
				} else {
					Rfm.m_Pln = *pPln1;								// �����ʌ`���ǉ�
					Rfm.m_Pg = (*pPgRfmN);
					Rfm.m_cdPg = GiCd;
					m_GRfm += Rfm;
				}
//				for ( ic2=3; ic2<m_GRfm.m_st[ic1].m_Pg.m_n; ic2++)			// �����\�����̐�����_�~�[�ɐݒ肷��
//					m_GRfm.m_st[ic1].m_cdPg += MHRL_DUMMY;
			}
		}
	}
	ist = 0;
	return ist;
}

////////////////////////////////////////////////////////////////////////////
//	�����ʂP�ɑ΂�������2�̌������`�F�b�N���ɋ��E���܂߂邩�ۂ��𔻒肷��

static bool MgChkRfmCls(							// (  O) true:	�����`�F�b�N���ɉ�����2�̋��E���܂߂�
													//		 false:	�����`�F�b�N���ɉ�����2�̋��E���܂߂Ȃ�
				const	MgLine3D		&LnJim1,		// (I  ) ������1�̒n����
				const	MgPlane3D	&Pln1,			// (I  ) ������1�̕��ʌW��
				const	MgLine3D		&LnJim2,		// (I  ) ������2�̒n����
				const	MgPlane3D	&Pln2			// (I  ) ������2�̕��ʌW��
				)
{
	bool	bst;
	MINT	ist1, ist2;
	bool	bst1, bst2;

	MGeo::ChkLineOnPln3DWS( LnJim1, Pln2, &ist1);							// ������1�̒n�����ʒu���A������2�̏㉺�ǂ��炩�𔻒�
	MGeo::ChkLineOnPln3DWS( LnJim2, Pln1, &ist2);							// ������2�̒n�����ʒu���A������1�̏㉺�ǂ��炩�𔻒�

	bst1 = !( ist1 & MC_PS_LOWER || ist1 & MC_PE_LOWER);	// ������1�̒n����1��������2�̏�܂��͏㑤
	bst2 = !( ist2 & MC_PS_LOWER || ist2 & MC_PE_LOWER);	// ������2�̒n����2��������1�̏�܂��͏㑤

	if ( !bst1 && bst2)									// �n����1��������2�̉����@���@�n����2��������1�̏�܂��͏㑤
		bst = false;									// �����`�F�b�N�ŋ��E�͊܂߂Ȃ�
	else
		bst = true;
	return bst;
}

////////////////////////////////////////////////////////////////////////////
//	���꒼����̐����Q�Ɛ����Q�̏d�Ȃ蕔���̎��o��
//	�i��: ���̓f�[�^�͂w�������т̃f�[�^�j
static void MgAndGLineOnULineAdd(
				const	MgGLine2D	&Gln1,			// (I  ) �����Q1	(1�̒�����̐����Q)
				const	MgGLine2D	&Gln2,			// (I  ) �����Q2	(�����Q1�Ɠ��꒼����̐����Q)
						MgGLine2D	*Glno			// (  O) �����Q1�Ɛ����Q2�Ƃ̏d�Ȃ��������̐����Q
													//		 ��0: �d�Ȃ�����Ȃ�
													//		 ��0: �d�Ȃ��������
				)
{
	MINT		ic1, ic2;
	MgLine2D		lno;
	MREAL		y1;
	MgVect2D		V1, V2;
	MGGLINE2( Glnw1, MX_LIN0);
	MGGLINE2( Glnw2, MX_LIN0);
	MgLine2D		lnw1, lnw2;
	MREAL		d1, d2, dd;

	Glno->m_n = 0;
	if ( Gln1.m_n == 0 || Gln2.m_n == 0)
		return;

	V1 = Gln1.m_ln[0].p[1] - Gln1.m_ln[0].p[0];
	V1.SetUnitize();

	//	�E��]��( x = x cos(a) + y sin(a); y = -x sin(a) + y cos(a); )�A
	//  �w���ɕ��s�ɂ���
	y1 = - Gln1.m_ln[0].p[0].x * V1.y + Gln1.m_ln[0].p[0].y * V1.x;
	for ( ic1=0; ic1<Gln1.m_n; ic1++) {
//		pln1 = &Gln1.m_ln[ic1];
		lnw1 = MgLine2D( MgPoint2D( Gln1.m_ln[ic1].p[0].x * V1.x + Gln1.m_ln[ic1].p[0].y * V1.y, y1),
						MgPoint2D( Gln1.m_ln[ic1].p[1].x * V1.x + Gln1.m_ln[ic1].p[1].y * V1.y, y1));
		Glnw1 += lnw1;
	}
	for ( ic1=0; ic1<Gln2.m_n; ic1++) {
		lnw2 = MgLine2D( MgPoint2D( Gln2.m_ln[ic1].p[0].x * V1.x + Gln2.m_ln[ic1].p[0].y * V1.y, y1),
						MgPoint2D( Gln2.m_ln[ic1].p[1].x * V1.x + Gln2.m_ln[ic1].p[1].y * V1.y, y1));
		for ( ic2=0; ic2<Glnw1.m_n; ic2++) {
			if ( lnw2.p[0].x < lnw2.p[1].x) {
				d1 = MGMAX( lnw2.p[0].x, Glnw1.m_ln[ic2].p[0].x);
				d2 = MGMIN( lnw2.p[1].x, Glnw1.m_ln[ic2].p[1].x);
			} else {
				d1 = MGMAX( lnw2.p[1].x, Glnw1.m_ln[ic2].p[0].x);
				d2 = MGMIN( lnw2.p[0].x, Glnw1.m_ln[ic2].p[1].x);
			}
			dd = d2 - d1;
			if ( dd > MGPTOL->D) {											// �d�Ȃ肪MgTol()->D���̏ꍇ�͏d�Ȃ�L��

				// ����]��(x = x cos(a) - y sin(a); y = x sin(a) + y cos(a); )�A
				// �o�͂���
				lnw1 = MgLine2D( MgPoint2D( d1 * V1.x - y1 * V1.y, d1 * V1.y + y1 * V1.x),
								MgPoint2D( d2 * V1.x - y1 * V1.y, d2 * V1.y + y1 * V1.x));
				(*Glno) += lnw1;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//	�d�Ȃ鉮���ʂ�1�ɂ܂Ƃ߂�
void MhRoofInfo::ConnectRfm()
{
	MINT		ist1;
	MINT		ic1, ic2, ic3, ic3b, ic4, ic4b;
	MINT		nRfm;
	MgPlane3D	Pln1, Pln2;
	MgGPolyg3D	GPgw;
	MgPolyg3D	Pgw;
	MgGInt		GpgCd;
	bool		fSet;
	MgPolyg3D	*pPg1, *pPg2;
	MgLine3D		Ln3, Ln4;

	nRfm = m_GRfm.m_n;
	for ( ic1=0; ic1<nRfm; ic1++) {
		if ( m_GRfm.m_st[ic1].m_Pg.m_n == 0)							// �}�[�W�ɂč폜���������ʂ�ǂݔ�΂�
			continue;
		Pln1 = m_GRfm.m_st[ic1].m_Pln;								// ������1�����o��
		for ( ic2=ic1+1; ic2<nRfm; ic2++) {
			if ( m_GRfm.m_st[ic2].m_Pg.m_n == 0)						// �폜���������ʁi�`�󖳂��̉����ʁj�͖���
				continue;
			Pln2 = m_GRfm.m_st[ic2].m_Pln;							// ������2�����o��
			if ( Pln1 != Pln2)
				continue;										// ���ꕽ�ʏ�ɖ��������ʂ͖���

			ist1 = MGeo::Merge2PgtoGPolygon3D( MC_OR, m_GRfm.m_st[ic1].m_Pg, m_GRfm.m_st[ic2].m_Pg, &GPgw);
			if ( MF_CHECK_OR( ist1, MC_INT) && GPgw.m_n == 1) {			// �����L��̏ꍇ��
				// �����\������̌����p
				Pgw = m_GRfm.m_st[ic1].m_Pg;
				Pgw += m_GRfm.m_st[ic2].m_Pg;
				pPg1 = &m_GRfm.m_st[ic1].m_Pg;
				pPg2 = &m_GRfm.m_st[ic2].m_Pg;
				GpgCd.m_n = 0;
				for ( ic3b=GPgw.m_Pg[0].m_n-1,ic3=0; ic3<GPgw.m_Pg[0].m_n; ic3b=ic3,ic3++) {
					Ln3 = MgLine3D( GPgw.m_Pg[0].m_P[ic3b], GPgw.m_Pg[0].m_P[ic3]);
					fSet = false;
					for ( ic4b=pPg1->m_n-1,ic4=0; !fSet && ic4<pPg1->m_n; ic4b=ic4,ic4++) {
						Ln4 = MgLine3D( pPg1->m_P[ic4b], pPg1->m_P[ic4]);
						if ( MGeo::ChkLineOnLine3D( Ln3, Ln4)) {
							GpgCd += m_GRfm.m_st[ic1].m_cdPg.m_i[ic4];
							fSet = true;
						}
					}
					for ( ic4b=pPg2->m_n-1,ic4=0; !fSet && ic4<pPg2->m_n; ic4b=ic4,ic4++) {
						Ln4 = MgLine3D( pPg2->m_P[ic4b], pPg2->m_P[ic4]);
						if ( MGeo::ChkLineOnLine3D( Ln3, Ln4)) {
							GpgCd += m_GRfm.m_st[ic2].m_cdPg.m_i[ic4];
							fSet = true;
						}
					}
					ASSERT(GpgCd.m_n == ic3 + 1);
				}

				// �����ʌ`��̏C��
				m_GRfm.m_st[ic1].m_Pg = GPgw.m_Pg[0];				// ������1�̉����ʌ`����C��
				m_GRfm.m_st[ic1].m_cdPg = GpgCd;					// ��������R�[�h���C��
				m_GRfm.m_st[ic2].m_Pg.m_n = 0;						// ������2�͍폜
				m_GRfm.m_st[ic2].m_cdPg.m_n = 0;

				ic2 = ic1 + 1;									// ������2�̎��o����������1�̎������蒼��
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// �����ʂ̌����A����ΐ����I�t�Z�b�g����
void MhRoofInfo::OffsetRfm()
{
	MINT		ic1, ic2;
	MINT		nRfm;
	MhRfm		*Rfm;
	MgPlane3D	Pln1;
	MINT		ib2, ib1;
	MgPoint2D	pb2, pb1, pc2;
	MgPoint2D	pb0;
	MgVect2D		vb1, vc2;
	MgLine2D		lnb1, lnc2;
	MgPolyg3D	Pg1;

	nRfm = m_GRfm.m_n;
	for ( ic1=0; ic1<nRfm; ic1++) {
		Rfm = &m_GRfm.m_st[ic1];
		if ( Rfm->m_Pg.m_n == 0)										// �}�[�W�ɂč폜���������ʂ̓X�L�b�v
			continue;
		Pln1 = Rfm->m_Pln;										// ������1�����o��
//		if ( MgZero( Pln1.v.z))									// XY���ʂɐ����̉����ʂ̓X�L�b�v
		if ( Rfm->m_icd == MHRL_YAGIRI)							// ��؂̓X�L�b�v
			continue;
		Pg1 = Rfm->m_Pg;
		ib2 = Pg1.m_n-2;
		pb2 = MgPoint2DC( Pg1.m_P[ib2]);
		ib1 = ib2 + 1;
		pb1 = MgPoint2DC( Pg1.m_P[ib1]);
		ASSERT( Pg1.m_n == Rfm->m_cdPg.m_n);
		for ( ic2=0; ic2<Pg1.m_n; ic2++) {
			pc2 = MgPoint2DC( Pg1.m_P[ic2]);
			vb1 = pb1 - pb2;
			vb1.SetUnitize();
			lnb1 = MgLine2D( pb2, pb1) + vb1.RotR90() * McRfmOffset[Rfm->m_cdPg[ib1]];
			vc2 = pc2 - pb1;
			vc2.SetUnitize();
			lnc2 = MgLine2D( pb1, pc2) + vc2.RotR90() * McRfmOffset[Rfm->m_cdPg[ic2]];
			MGeo::Intr2Line2D( lnb1, lnc2, &pb0);
			Rfm->m_Pg.m_P[ib1] = MgPoint3DC( pb0, Pln1.GetZ( pb0));
			pb2 = pb1;
			ib1 = ic2;
			pb1 = pc2;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// �����ʂ̐}�`���쐬����
void MhRoofInfo::CreateRfmZukei()
{
	MINT		nLine, nLineS;
	MINT		szZukei;
	MINT		ic0, ic1, ic2, icz;

	nLineS = 0;
	for ( ic0=0; ic0<m_GRfm.m_n; ic0++)
		nLineS += m_GRfm.m_st[ic0].m_Pg.m_n;

	szZukei = sizeof(MhZukei) + sizeof(MgLine3D) * (nLineS - 1);			// ����[nLine]�{���̐}�`�f�[�^�T�C�Y
	m_pZukei = (MhZukei*)new char[szZukei];
	m_pZukei->m_ibObj = MHZK_DISP;											// �}�`�\���p
	m_pZukei->m_ibTp = MHZK_GLINE;											// �����Q
	m_pZukei->m_pNext = NULL;
	m_pZukei->m_isNZukei = nLineS;

	icz = 0;
	for ( ic0=0; ic0<m_GRfm.m_n; ic0++) {
		nLine = m_GRfm.m_st[ic0].m_Pg.m_n;
		ic1 = nLine - 1;
		for ( ic2=0; ic2<nLine; ic1=ic2,ic2++) {
			m_pZukei->m_lnZukei[icz++] = MgLine3D( m_GRfm.m_st[ic0].m_Pg.m_P[ic1], 
									 			  m_GRfm.m_st[ic0].m_Pg.m_P[ic2]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// �g���[�X
void MhJim::Print( MCHAR* s, MINT ic)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MhJim[%2d]	(%7.1f,%7.1f)	Cd: %d	fInp: %d	rKb:%7.1f	Rfm: %d")
						   Mstr( "	LnR:(%7.1f,%7.1f,%7.1f)	(%7.1f,%7.1f,%7.1f)\n"),
								s, ic, m_p.x, m_p.y, m_icd, m_ifInp, m_rKb, m_iRfm,
								m_LnR.p[0].x, m_LnR.p[0].y, m_LnR.p[0].z, m_LnR.p[1].x, m_LnR.p[1].y, m_LnR.p[1].z);
	MBLOGPRBF;
#endif
}
void MgKs1::Print( MCHAR* s, MINT ic)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgKs1[%2d]	LnR: (%7.1f,%7.1f,%7.1f) (%7.1f,%7.1f,%7.1f)")
						   Mstr( "	Typ: %d	Cd: %d	fProc: %d	Rfm = %d, %d\n"),
								s, ic, m_Ln.p[0].x, m_Ln.p[0].y, m_Ln.p[0].z, m_Ln.p[1].x, m_Ln.p[1].y, m_Ln.p[1].z,
								m_itpLn, m_iCd, m_ifProc, m_iRfm[0], m_iRfm[1]);
	MBLOGPRBF;
#endif
}
void MhRfm::Print( MCHAR* s, MINT ic)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MhRfm[%2d]	pln: (%7.3f,%7.3f,%7.3f),%7.1f	Cd: %d\n"),
								s, ic, m_Pln.v.x, m_Pln.v.y, m_Pln.v.z, m_Pln.d, m_icd);
	MBLOGPRBF;
	m_cdPg.Print( Mstr( "MhRfm pgCd"));
	m_Pg.Print( Mstr( "MhRfm pg"));
#endif
}

void MhRoofInfo::Print( MCHAR* s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MhRoofInfo	Kai: %d	Kb:%7.1f	RkH:%7.1f	RfmA:%7.1f	NUmA:%7.1f\n")
						   Mstr( "			MnZ:%7.1f,%7.1f	NkD:%7.1f,%7.1f	KrD:%7.1f,%7.1f")
						   Mstr( "	tpNU: %d	tpNS: %d	HKmA:%7.1f	NUk:%7.1f	cdURS:  %d\n"),
								 s, m_iKai, m_rKb, m_rRkH, m_rRfmA, m_rNUmA,
								 m_rMnZ[0], m_rMnZ[1], m_rNkD[0], m_rNkD[1], m_rKrD[0], m_rKrD[1],
								 m_itpNU, m_itpNS, m_rHKmA, m_rNUk, m_rNkH, m_icdURS);
	m_GJim1.Print( Mstr( "GJim1"));								// �n�����i���́j
	m_GKs1.Print( Mstr( "GKs1"));								// �\�����i���́j
	m_GRfm.Print( Mstr( "GRfm"));								// ������
#endif
}

} // namespace MC
