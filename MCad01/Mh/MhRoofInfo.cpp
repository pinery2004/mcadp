//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhRoofInfo.cpp
//
//		�����ǂݏ���
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MdLib.h"

#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MhLib.h"
#include "MhRoof.h"

#include "MfFile.h"
#include "MmTenkai.h"

#include "MhDefine.h"

PZBUF*	____pzbuf;

																				//void MdPtsDbInit();
																				//void MdRedoPtsDbInit();
																				//void MdRoofDbInit();

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	�����z�u���R�[�h��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhRoofInfo::Save(							//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_ST, &iDumy);
	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_KAI, &m_iKai);

	// �n����
	for ( iC1=0; iC1 < GetpGJim1()->m_n; iC1++) {
		GetpGJim1()->m_st[iC1].Save( i_phMdl);
	}

	// �����\����
	for( iC1=0; iC1<GetpGKs1()->m_n; iC1++) {
		GetpGKs1()->m_st[iC1].Save( i_phMdl);
	}

	// ������
	for ( iC1=0; iC1 < GetpGRfm()->m_n; iC1++) {
		GetpGRfm()->m_st[iC1].Save( i_phMdl);
	}

	i_phMdl->WriteItemI( MDW_ATRCD_ROOFEN_EOR, &iDumy);

    return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�����z�u���R�[�h�ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhRoofInfo::Load(							//
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT		ist = 0;
	MhMdlIO		hMdl;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;
	mhPlcInfo*	pPlcEn = 0;
																				//	MhRoofInfo*		pRoofEn;
	MhJim*		pJim1;
	MhRfm*		pRfm;
	MgPoint3*	pPt;
	MINT*		piCd;

	bool		fPlcSzChk = true;
	bool		fRoofSzChk = true;

	bool		bEor = false;

	MgVect3		vLnPlc;

//	�������R�[�h
	this->InitAllAtr( 0);										// �q�̃T�C�Y�ƃ��R�[�h�����N���A

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
#if (MDR_TYPE2)
			case MDR_ATRCD_ROOFEN_KAI:							// �K
				ASSERT( iSize == SZMINT());
				m_iKai = *( MINT*)pEnt;
				break;
#endif
			case MDR_ATRCD_ROOFEN_EOR:							// ���� eor
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				CreateRfmZukei();
				bEor = true;
				break;
#if (MDR_TYPE2)
			case MDR_ATRCD_JIM_ST:								// �n���
				if( iSize == SZMINT()) {
					MBFREE( pEnt);
					pJim1 = new MhJim[1];
					pJim1->Load( i_phMdl);
					*(this->GetpGJim1()) += (*pJim1);			// 
				} else if( iSize == sizeof( MhJim)) {
					pJim1 = (MhJim*)pEnt;
					*(this->GetpGJim1()) += (*pJim1);			// ���Ή��@MDR_ATRCD_JIM_EOR�Ȃ��̈�	ZZZZZZZZZZZZZ 091018
					MBFREE( pJim1);								// ���Ή�
				} else {
					ASSERT( 0);
				}
				break;
#endif
			case MDR_ATRCD_JIM:									// ������
				ASSERT( iSize == sizeof(MhJim));
				pJim1 = (MhJim*)pEnt;

				*(this->GetpGJim1()) += (*pJim1);				// ���Ή��@MDR_ATRCD_JIM_EOR�Ȃ��̈�	ZZZZZZZZZZZZZ 091018
				MBFREE( pJim1);									// ���Ή�
				break;
			case MDR_ATRCD_JIM_EOR:								// �n���
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				*(this->GetpGJim1()) += (*pJim1);
				MBFREE( pJim1);	
				break;
			case MDR_OLD_ATRCD_RFM:									// ������
				ASSERT( iSize == sizeof(MhRfm));
				pRfm = (MhRfm*)pEnt;
				break;
			case MDR_ATRCD_RFM_EOR:								// ������ eor
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);

				*(this->GetpGRfm()) += (*pRfm);
				pRfm->Free();
				MBFREE( pRfm);
				break;
			case MDR_OLD_ATRCD_RFM_PG_PT:							// �����ʍ\���_ 
				ASSERT( iSize == sizeof(MgPoint3) * pRfm->m_Pg.m_n);
				pPt = (MgPoint3*)pEnt;
				pRfm->m_Pg.m_P = pPt;
				pRfm->m_Pg.m_P = (MgPoint3*)pEnt;
				break;
			case MDR_OLD_ATRCD_RFM_ICD_I:							// �����ʃR�[�h
				ASSERT( iSize == SZMINT() * pRfm->m_cdPg.m_n);
				piCd = (MINT*)pEnt;
				pRfm->m_cdPg.m_i = piCd;
				pRfm->m_cdPg.m_i = (MINT*)pEnt;
				break;
			default:
				MBFREE( pEnt);
		}
	} while( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	�n�������R�[�h��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhJim::Save(								//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
																				//	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ST, &iDumy);
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_P, (MFLOAT*)&m_p, SZMgPoint2());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ICD, &m_icd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_IFINP, &m_ifInp, SZMINT());
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_RKB, &m_rKb, SZMREAL());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_IRFM, &m_iRfm, SZMINT());
	i_phMdl->WriteItemR( MDW_ATRCD_JIM_LNR, (MFLOAT*)&m_LnR, SZMgLine3());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_ILNRCD, &m_icdLnR, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_JIM_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	�n�������R�[�h�ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhJim::Load(								//
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;

	bool		bEor = false;

//	�n�������R�[�h
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_JIM_EOR:								// �n���� eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_JIM_P:								// �n�����E�[�̒��_
				ASSERT( iSize == SZMgPoint2());
				memcpy( &m_p, pEnt, SZMgPoint2());
				break;
			case MDR_ATRCD_JIM_ICD:								// �n�����R�[�h
				ASSERT( iSize == SZMINT());
				m_icd = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_IFINP:							// ���̓t���O
				ASSERT( iSize == SZMINT());
				m_ifInp = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_RKB:								// ���z
				ASSERT( iSize == SZMREAL());
				m_rKb = *(MREAL*)pEnt;
				break;
			case MDR_ATRCD_JIM_IRFM:							// �����ʔz��ԍ�
				ASSERT( iSize == SZMINT());
				m_iRfm = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_JIM_LNR:								// �E�������\�����i�����j 
				ASSERT( iSize == SZMgLine3());
				memcpy( &m_LnR, pEnt, SZMgLine3());
				break;
			case MDR_ATRCD_JIM_ILNRCD:							// �E�������\�����R�[�h
				ASSERT( iSize == SZMINT());
				m_icdLnR = *(MINT*)pEnt;
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif
////////////////////////////////////////////////////////////////////////////
//	�\���������R�[�h��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MgKs1::Save(								//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
																				//	MINT		iC1;
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_KSI_ST, &iDumy);
	i_phMdl->WriteItemR( MDW_ATRCD_KSI_LN, (MREAL*)&m_Ln, SZMgLine3());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_TPLN, (MINT*)&m_itpLn, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_CD, (MINT*)&m_iCd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_FPROC, &m_ifProc, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_RFM, m_iRfm, SZMREAL( 2));
	i_phMdl->WriteItemI( MDW_ATRCD_KSI_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	�\���������R�[�h�ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MgKs1::Load(								//
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;

	bool		bEor = false;

//	�\���������R�[�h
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_JIM_EOR:								// �\������ eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_KSI_LN:								// �\������
				ASSERT( iSize == SZMgLine3());
				memcpy( &m_Ln, pEnt, SZMgLine3());
				break;
			case MDR_ATRCD_KSI_TPLN:							// �����^�C�v(0: �������@1:����)
				ASSERT( iSize == SZMINT());
				m_itpLn = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_CD:								// �\���R�[�h
				ASSERT( iSize == SZMINT());
				m_iCd = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_FPROC:							// �v�Z�����p�t���O
				ASSERT( iSize == SZMINT());
				m_ifProc = *(MINT*)pEnt;
				break;
			case MDR_ATRCD_KSI_RFM:								// �����ʔz��ԍ� (���A�E)
				ASSERT( iSize == 2 * SZMREAL());
				memcpy( m_iRfm, pEnt, 2 * SZMREAL());
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif

////////////////////////////////////////////////////////////////////////////
//	�����ʃ��R�[�h��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhRfm::Save(								//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
																				//	MINT		iC1;
	MINT	iDumy = 0;
	MINT	iN;

	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ST, &iDumy);
	iN = m_Pg.m_n;
	i_phMdl->WriteItemR( MDW_ATRCD_RFM_PG, (MREAL*)&m_Pg.m_P, iN * SZMgPoint3());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ICD, (MINT*)&m_cdPg.m_tp, iN * SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_ICD, (MINT*)&m_icd, SZMINT());
	i_phMdl->WriteItemI( MDW_ATRCD_RFM_EOR, &iDumy);

	return 0;
}

#if (MDR_TYPE2)
////////////////////////////////////////////////////////////////////////////
//	�����ʃ��R�[�h�ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhRfm::Load(								//
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT	ist = 0;
	MINT	iType;
	MINT	iSize;
	void*	pEnt;
	MINT	iN = 0;

	bool	bEor = false;

//	�����ʃ��R�[�h
	memset( this, 0, sizeof( this));

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
		static	int iCyane = 0;
		TRACE( "%d; iType=%d\n", ++iCyane, iType);
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_RFM_EOR:								// �n���� eor
				ASSERT( iSize == SZMINT());
				bEor = true;
				break;
			case MDR_ATRCD_RFM_PLN:								// �����ʌW��
				ASSERT( iSize == SZMgPlane3());
				memcpy( &m_Pln, pEnt, SZMgPlane3());
				break;
			case MDR_ATRCD_RFM_PG:								// �����ʌ`��i�����\�����j
				iN = iSize / SZMgPoint3();
				m_Pg.Resize( iN);
				memcpy( &m_Pg[0], pEnt, iSize);
				break;
			case MDR_ATRCD_RFM_ICDPG:							// �����\�����R�[�h
				ASSERT( iSize == iN * SZMINT());
				m_cdPg.Resize( iN);
				memcpy( &m_cdPg[0], pEnt, iSize);
				break;
			case MDR_ATRCD_RFM_ICD:								// �\���R�[�h
				ASSERT( iSize == SZMINT());
				m_icd = *(MINT*)pEnt;
				break;
		}
		MBFREE( pEnt);
	} while( !bEor);
    return ist;
}
#endif
} // namespace MC