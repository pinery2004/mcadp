//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: mhPlcInfo.cpp
//
//		���ޔz�u�ǂݏ���
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MgLib.h"

#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MhLib.h"
#include "MhPlcInfo.h"

#include "MfFile.h"
#include "MmTenkai.h"

#include "MhDefine.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	�o�C�g�f�[�^�̓ǂݍ���
//	[�Ԓl] �o�C�g�f�[�^
inline	byte	GetByte(
					int		i_iTp,				// �^�C�v�@1:byte�f�[�^, 4:int�f�[�^(��)
					int*	i_pDt				// �ǂݍ��݃f�[�^
				)
{
	byte	ibDt;
	if( i_iTp == 1) {
		ibDt = *(byte*)i_pDt;
	} else if( i_iTp == 4) {
		ibDt = *(MINT*)i_pDt;
	} else {
		ASSERT( 0);
		ibDt = 0;
	}
	return ibDt;
}

////////////////////////////////////////////////////////////////////////////
//	�z�u���ނ̓ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�
inline	short	GetShort(
					int		i_iTp,				// �^�C�v�@2:short�f�[�^, 4:int�f�[�^(��)
					int*	i_pDt				// �ǂݍ��݃f�[�^
				)
{
	short	isDt;
	if( i_iTp == 2) {
		isDt = *(short*)i_pDt;
	} else if( i_iTp == 4) {
		isDt = *(MINT*)i_pDt;
	} else {
		ASSERT( 0);
		isDt = 0;
	}
	return isDt;
}

////////////////////////////////////////////////////////////////////////////
//	���ޔz�u���R�[�h��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT mhPlcInfo::Save(							//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
	MINT		iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ST, &iDumy);							// �z�u���R�[�h
		
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_IKAI, &m_ibKai);					// �K
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ICDHGT, &m_ibCdHgt);				// ���t�������R�[�h
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_DISPLAYFLAG, &m_ibDisplayFlg);		// �\���t���O(�}�`,���L1,���L2)
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_IPANELNO, &m_isPanelNo);			// �p�l���ԍ�
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_IKAIKONO, &m_isKaikoNo);			// �J���ԍ�
	MINT iCdBuzaiW = GetPTCdBuzaiW();											// ���ރR�[�h
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_IPARTSTPCD, &iCdBuzaiW);
																				// p[0]: �n�_ | �z�u�_
																				// p[1]: �I�_ | �z�u�����_
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_LNHAITI, (MREAL*)&m_lnPlc, sizeof(MgLine3));
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_PTUPHAITI, (MREAL*)&m_vUpPlc, sizeof(MgPoint3));
																				// �z�u������_
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RSINZURE, &m_rSinZure);				// �ގ��c����ʁ@	>0:�E���A<0:����
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RHAITIZURE, &m_rPlcZure);			// �z�u�_�����		>0:�O�A�@<0:��
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RNAGASAHOSEI, m_rLngHosei, 2*sizeof(MREAL));
																				// �����␳�l�i�n�_���A�I�_���j
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RTAKASA, m_rHgt, 2*sizeof(MREAL));	// �����i���t�������A�����j
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_PTCMNT1, (MREAL*)&m_ptCmnt1, sizeof(MgPoint2));
																				// ���L�\���ʒu
	MCHAR	cMemBerCode[16];
	Mstrcpy_s( cMemBerCode, GetMbCdMbrW());										// ���@�^�� (�������ݗp�@�ʏ�m_cCode�Ɠ��� VerUp���ɕύX�������e������)
	i_phMdl->WriteItemCH( MDW_ATRCD_HAITIEN_MEMBER, cMemBerCode, sizeof(cMemBerCode));
	if ( GetPIAuxAttr() != 0) {
		if ( IsTategu())														// ������
			GetPIAuxTategu()->Save( i_phMdl);
		else if ( IsTenkai())													// �Z���W�J
			GetPIAuxTenkai()->Save( i_phMdl);
	}
	if ( m_pVer != 0)															// �o�[�W����
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_VERSION, (MUINT*)m_pVer, sizeof(MhHistV));
	if ( m_pOpt1 != 0)															// �n�o�s�Q
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_OPTION1, (MUINT*)m_pOpt1, sizeof(MsBitSet));
	if ( m_pOpt2 != 0)															// �n�o�s�Q
		i_phMdl->WriteItemUI( MDW_ATRCD_HAITIEN_OPTION2, (MUINT*)m_pOpt2, sizeof(MsBitSet));

	MhZukei*	pZukei;							// �}�`
	for( pZukei=m_pZukei; pZukei!=0; pZukei=pZukei->m_pNext) {
		pZukei->Save( i_phMdl);
	}
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_EOR, &iDumy);						// �z�u���R�[�h�I��

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�z�u���ނ̓ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT mhPlcInfo::Load(							//
						MhMdlIO*	i_phMdl		// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	MINT		nVer;
	
	void*		pEnt;
//	mhPlcInfo*	pPlcEn = 0;
	MhTateguInfo*	pAuxTategu;
	JTTenkaiPr*	pAuxTenkai;
	MhHistV*	pVer;
	MsBitSet*	pOpt;

	MhZukei**	ppZukei;
	MINT		iNZukei;
	MINT		iSzZukei;
	MCHAR*		pcMbr;
	MINT		iMbr;
	MINT		iCdBuzai;

	bool		fPlcSzChk = true;
	bool		fRoofSzChk = true;

	MgVect3		vLnPlc;
	
	bool		bEor = false;

	// �z�u���R�[�h�J�n

	memset( this, 0, sizeof( mhPlcInfo));
	ppZukei = &m_pZukei;

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDR_ATRCD_HAITIEN_EOR:											// �z�u ���R�[�h�I��r
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);													// TYPE_HAITIEN_EOR���R�[�h�p�G���A�̍폜
				
				m_pTpPts	= BuzaiCode::MhGetpTpPts( m_isIdTpPts);
				m_pMbr		= BuzaiCode::MhGetpMbr( m_isMbrId);
				
				bEor = true;
				break;
			case MDR_ATRCD_HAITIEN_IKAI:										// �K
				m_ibKai = GetByte( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_ICDHGT:										// �z�u�_
				m_ibCdHgt = GetByte( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IPANELNO:									// �z�u�_
				m_isPanelNo = GetShort( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IKAIKONO:									// �J���ԍ�
				m_isKaikoNo = GetShort( iSize, (int*)pEnt);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_IPARTSTPCD:									// ���i�z�u�^�C�v�R�[�h 
				ASSERT( iSize == SZMINT());
				iCdBuzai = *(MINT*)pEnt;										// (���ރR�[�h)
				m_isIdTpPts = BuzaiCode::MhGetPIIdTpPts( iCdBuzai);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_MEMBER:										// �����o�[
				ASSERT( iSize == sizeof( MhTateguInfo));
				pcMbr = (MCHAR*)pEnt;
				iMbr = BuzaiCode::MhGetIdMbr( pcMbr);
				if ( iMbr < 0) {
					iMbr = 0;
				}
				m_isMbrId	= iMbr;
				m_pMbr		= BuzaiCode::MhGetpMbr( m_isMbrId);
				MBFREE( pcMbr);
				break;
			case MDR_ATRCD_HAITIEN_LNHAITI:										// �z�u�_�A�z�u�����_
				ASSERT( iSize == sizeof(MgLine3));
				m_lnPlc = *(MgLine3*)pEnt;
				vLnPlc = m_lnPlc.p[1] - m_lnPlc.p[0];
				vLnPlc.SetUnitize();
				m_vUpPlc = vLnPlc ^ MgVect3( 0., 0., 1.);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_PTUPHAITI:									// �����
				ASSERT( iSize == sizeof(MgPoint3));
				m_vUpPlc = *(MgVect3*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RSINZURE:									// �ގ��c�����
				ASSERT( iSize == sizeof(MREAL));
				m_rSinZure = *(MREAL*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RHAITIZURE:									// �z�u�_����� 
				ASSERT( iSize == sizeof(MREAL));
				m_rPlcZure = *(MREAL*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RNAGASAHOSEI:								// �����␳�l1�A�����␳�l2
				ASSERT( iSize == sizeof(MREAL) * 2);
				m_rLngHosei[0] = *(MREAL*)pEnt;
				m_rLngHosei[1] = *(((MREAL*)pEnt)+1);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_RTAKASA:										// ����
				ASSERT( iSize == sizeof(MREAL) * 2);
				m_rHgt[0] = *(MREAL*)pEnt;
				m_rHgt[1] = *(((MREAL*)pEnt)+1);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_TATEGU:										// �����
				ASSERT( iSize == sizeof( MhTateguInfo));
				pAuxTategu = (MhTateguInfo*)pEnt;
				m_pAuxTategu = pAuxTategu;
				break;
			case MDR_ATRCD_HAITIEN_TENKAI:										// �Z���W�J
				ASSERT( iSize == sizeof(JTTenkaiPr));
				pAuxTenkai = (JTTenkaiPr*)pEnt;
				m_pAuxTenkai = pAuxTenkai;
				JTTenkai::SetJTTPara( pAuxTenkai);
				break;
			case MDR_ATRCD_HAITIEN_VERSION:										// �o�[�W����
				ASSERT( iSize == sizeof(MhHistV));
				pVer = (MhHistV*)pEnt;
				m_pVer = pVer;
				break;
			case MDR_ATRCD_HAITIEN_OPTION1:										// �n�o�s�Q
				ASSERT( iSize == sizeof(MsBitSet));
				pOpt = (MsBitSet*)pEnt;
				m_pOpt1 = pOpt;
				break;
			case MDR_ATRCD_HAITIEN_OPTION2:										// �n�o�s�Q
				ASSERT( iSize == sizeof(MsBitSet));
				pOpt = (MsBitSet*)pEnt;
				m_pOpt2 = pOpt;
				break;
			case MDR_ATRCD_OPTION_KANRI:										// �n�o�s�Q�Ǘ�
				MhOptV::nbmGOpt = iSize / sizeof( MhOpt);
				memcpy( MhOptV::bmGOpt, pEnt, iSize);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI0:										// �����Ǘ�
				nVer = 0;
				memcpy( &MhHistV::nVer, pEnt, iSize);
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI1:										// �����Ǘ��@�o�[�W����
				MhHistV::sVerC[nVer] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI2:										// �����Ǘ��@���O�o�[�W����
				MhHistV::sVerB[nVer] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_VERSION_KANRI3:										// �����Ǘ��@���t
				MhHistV::sVerD[nVer++] = (MCHAR*)pEnt;
				MBFREE( pEnt);
				break;
			case MDR_ATRCD_HAITIEN_ZUKEI:
				*ppZukei = (MhZukei*)pEnt;
				iSzZukei = sizeof( MhZukei) + sizeof( MgLine3) * ( (*ppZukei)->m_isNZukei - 1);
				ASSERT( iSize == iSzZukei);
				SetPIZukei( *ppZukei);
				GetPIZukei()->m_pNext = 0;
				break;

#if (MDR_TYPE1) 
			case MDR_ATRCD_HAITIEN_ZUKEI_ST:
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);
				break;
#endif
			case MDW_ATRCD_HAITIEN_ZUKEI_N:									// �}�`(����)��
				ASSERT( iSize == sizeof( MSHORT));
				iNZukei = *( MSHORT*)pEnt;
				MBFREE( pEnt);
				iSzZukei = sizeof( MhZukei) + sizeof( MgLine3) * ( iNZukei - 1);
				*ppZukei = (MhZukei*)new char[iSzZukei];
				(*ppZukei)->m_isNZukei = iNZukei;
				MBFREE( pEnt);
				memset( *ppZukei, 0, iSzZukei);
				(*ppZukei)->Load( i_phMdl);
				ppZukei = &(*ppZukei)->m_pNext;
				break;

			default:
				MBFREE( pEnt);
		}
	} while ( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	���ޔz�u���R�[�h ������@��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhTateguInfo::Save(							//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
	MINT	iDumy = 0;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TATEGU_ST, &iDumy);					// ������
		
	MCHAR	cKCode[MHTTSZ_CODE+1];
	Mstrcpy_s( cKCode, GetKCode());												// �J���R�[�h
	i_phMdl->WriteItemCH( MDW_ATRCD_HAITIEN_CCODE, cKCode, sizeof(cKCode));
	MREAL rROW = GetROW();														// �J����
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RROW, &rROW);
	MREAL rROH = GetROH();														// �J������
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RROH, &rROH);
	MREAL rHeight= GetHeight();													// ���t������(�܂������[����)
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RHEIGHT, &rHeight);
	MREAL* prMUSz =	GetMUSz();													// ���E�܂����󒷂�
	i_phMdl->WriteItemR( MDW_ATRCD_HAITIEN_RMUSZ, prMUSz, 2*sizeof(MREAL));

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TATEGU_EOR, &iDumy);					// ������I��

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	���ޔz�u���R�[�h �}�`��� ��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhZukei::Save(
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
//	MhZukei*	pZukei;
	MINT	iDumy = 0;
	MINT	iSzZukei;

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ZUKEI_ST, &iDumy);					// �}�`���J�n
	MSHORT	isNZukei = m_isNZukei;
	i_phMdl->WriteItemIS( MDW_ATRCD_HAITIEN_ZUKEI_N, &isNZukei);				// �}�`(����)��	(�}�`���J�n�̒���ɏo�͂��邱��)
	MUBYTE	ibObj = m_ibObj;
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ZUKEI_OBJ, &ibObj);					// �g�p�ړI
	MUBYTE	ibTp = m_ibTp;
	i_phMdl->WriteItemIB( MDW_ATRCD_HAITIEN_ZUKEI_TP, &ibTp);					// �}�`�f�[�^�^�C�v
	iSzZukei = m_isNZukei * sizeof( MgLine3);
	i_phMdl->WriteItems( MDW_ATRCD_HAITIEN_ZUKEI_ST, m_lnZukei, iSzZukei);

	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_ZUKEI_EOR, &iDumy);					// �}�`���I��

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	���ޔz�u���R�[�h �}�`��� �ǂݍ���
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT MhZukei::Load(								//
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				)
{
	MINT		ist = 0;
	MINT		iType;
	MINT		iSize;
	void*		pEnt;
	MINT		iDumy = 0;

	bool		bEor = false;

//	�}�`���

	do {
		iSize = i_phMdl->ReadItem( &iType, (void**)&pEnt);
//===
#if( TRACE_IO)
		static	int iCzukei = 0;
		TRACE( "%d; iType=%d\n", iCzk_IO++, iType);
#endif
//---

		if ( iSize <= 0)
			break;

		switch( iType) {
			case MDW_ATRCD_HAITIEN_ZUKEI_EOR:									// �}�`���I��
				ASSERT( iSize == SZMINT());
				MBFREE( pEnt);
				bEor = true;
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_TP:									// �^�C�v
				ASSERT( iSize == sizeof( m_ibTp));
				m_ibTp = *( MUBYTE*)pEnt;
				MBFREE( pEnt);
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_OBJ:									// �g�p�ړI
				ASSERT( iSize == sizeof( m_ibObj));
				m_ibObj = *( MUBYTE*)pEnt;
				MBFREE( pEnt);
				break;
			case MDW_ATRCD_HAITIEN_ZUKEI_BUF:									// �}�`(����)
				ASSERT( iSize == m_isNZukei * sizeof( MgLine3));
				memcpy( m_lnZukei, pEnt, iSize);
				MBFREE( pEnt);
				break;
			default:
				MBFREE( pEnt);
		}
	} while( !bEor);
    return ist;
}

////////////////////////////////////////////////////////////////////////////
//	���ޔz�u���R�[�h �Z���W�J��� ��������
//	[�Ԓl] �X�e�C�^�X     0 : ����  -1 : �ُ�

MINT JTTenkaiPr::Save(							//
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				)
{
	MINT			iDumy = 0;

//	i_phMdl->WriteItem( MDW_ATRCD_HAITIEN_TATEGU, &iDumy);						// �}�`���R�[�h
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TENKAI_ST, &iDumy);					// �Z���W�J���R�[�h
		

//	i_phMdl->WriteItem( MDW_ATRCD_HAITIEN_TATEGU_EOR, &iDumy);					// �}�`���R�[�h�I��
	i_phMdl->WriteItemI( MDW_ATRCD_HAITIEN_TENKAI_EOR, &iDumy);					// �Z���W�J���R�[�h�I��

	return 0;
}

} // namespace MC