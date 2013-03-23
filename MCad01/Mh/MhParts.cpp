//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhPts.cpp
//
//		���ރ}�X�^��ǂݍ���
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgLib.h"

#include "MmDefine.h"
#include "MsBitSet.h"
#include "MdOpt.h"
#include "MdHist.h"

#include "MdList.h"
#define DLL_EXPORT_BUZAICODE_DO
#include "MhLib.h"

#include "MhPlcInfo.h"

#include "MmLib.h"

#include "MgGrp.h"

#include "MhRoof.h"
#include "MdLib.h"

#include "MhParts.h"
#include "MfFile.h"
#include "McSystemProperty.h"

namespace MC
{

void mhPlcInfo::Copy( const mhPlcInfo &Ent)
{
	MINT		szZukei;
	MINT		szVer;
	MINT		szOpt1;
	MINT		szOpt2;
	MhZukei*	pZukei;
	MsBitSet*	pVer;
	MsBitSet*	pOpt1;
	MsBitSet*	pOpt2;

	MBFREE( m_pZukei);
	MBFREE( m_pOpt1);
	MBFREE( m_pOpt2);

	*this = Ent;
	if ( Ent.m_pZukei) {
//		szZukei = sizeof( *Ent.m_pZukei) + sizeof( MgLine3) * (Ent.m_pZukei->m_isNZukei - 1);
		szZukei = sizeof( MhZukei) + sizeof( MgLine3) * (Ent.m_pZukei->m_isNZukei - 1);
		pZukei = (MhZukei*)new char[szZukei];
		memcpy( pZukei, Ent.m_pZukei, szZukei);
		m_pZukei = pZukei;
	} else {
		m_pZukei = NULL;
	}
	if ( Ent.m_pVer) {
		szVer = sizeof( MsBitSet);
		pVer = (MsBitSet*)new char[szVer];
	
#ifdef _DEBUG
		Msprintf_s( mlLog::m_Str, Mstr( "MALLOC VERSION TRC %x\n"), pVer);
		MBTRCPRBF;
#endif

		memcpy( pVer, Ent.m_pVer, szVer);
		m_pVer = pVer;
	} else {
		m_pOpt2 = NULL;
	}
	if ( Ent.m_pOpt1) {
		szOpt1 = sizeof( MsBitSet);
		pOpt1 = (MsBitSet*)new char[szOpt1];

#ifdef _DEBUG
		Msprintf_s( mlLog::m_Str, Mstr( "MALLOC OPTION Copy1 TRC %x\n"), pOpt1);
		MBTRCPRBF;
#endif

		memcpy( pOpt1, Ent.m_pOpt1, szOpt1);
		m_pOpt1 = pOpt1;
	} else {
		m_pOpt1 = NULL;
	}
	if ( Ent.m_pOpt2) {
		szOpt2 = sizeof( MsBitSet);
		pOpt2 = (MsBitSet*)new char[szOpt2];

#ifdef _DEBUG
		Msprintf_s( mlLog::m_Str, Mstr( "MALLOC OPTION Copy2 TRC %x\n"), pOpt2);
		MBTRCPRBF;
#endif

		memcpy( pOpt2, Ent.m_pOpt2, szOpt2);
		m_pOpt2 = pOpt2;
	} else {
		m_pOpt2 = NULL;
	}

	return;
}					// �R�s�[

////////////////////////////////////////////////////////////////////////////
//    ���ރ}�X�^

static	MINT		z_nGp;
static	MhGp		z_Gp[MMAX_KUMI];
static	MINT		z_nTpPts;
static	mhTpPts		z_TpPts[MMAX_PARTSTP];
static	MINT		z_nMbr;
static	MhMbr		z_Mbr[MMAX_MEMBER];
struct	BZMTBK
{
	MCHAR*	c;
	MINT	i;
};
static	const	BZMTBK	z_Br[] =	
{
	Mstr( "����"),				MP_BR_BUZAI,
	Mstr( "����"),				MP_BR_KANAGU,
	Mstr( "�p�l��"),			MP_BR_PANEL,
	Mstr( "����"),				MP_BR_YANE,
	Mstr( "��"),				MP_BR_KABE,
	Mstr( "��b"),				MP_BR_KISO,
	Mstr( "����"),				MP_BR_SENBUN,
	Mstr( "���"),				MP_BR_KUKAKU,
	Mstr( "�J��"),				MP_BR_KAIKO,
	Mstr( "���L"),				MP_BR_CYUKI,
	Mstr( "���̑�"),			MP_BR_OTHER
};

#define	NBUNRUI		(sizeof(z_Br)/sizeof(BZMTBK))
static	const	BZMTBK	z_InpKb[] =
{
//	Mstr( "���w��"),			MP_INPKB_NONE,
	Mstr( "�P�_"),				MP_INPKB_1PT,
	Mstr( "�����P�_"),			MP_INPKB_DIR1PT,
	Mstr( "�����Q�_"),			MP_INPKB_LEN2PT,
	Mstr( "���"),				MP_INPKB_AREA,
	Mstr( "���R"),				MP_INPKB_FREE
};
#define	NInpKb	(sizeof(z_InpKb)/sizeof(BZMTBK))
static	const	BZMTBK	z_CdHgt[] =
{
	Mstr( "SGL"),				MP_HGTCD_SGL,			//ZZZZZ
	Mstr( "��b"),				MP_HGTCD_KISOKJ,
	Mstr( "���"),			MP_HGTCD_SITAKJ,
	Mstr( "��"),			MP_HGTCD_UEKJ,
	Mstr( "�V��"),			MP_HGTCD_TENJOKJ,
	Mstr( "�����"),			MP_HGTCD_YANEKJ
};
#define	NHEIGHTCD	(sizeof(z_CdHgt)/sizeof(BZMTBK))
static	const	BZMTBK	z_CdPlc[] =
{
	Mstr( "�C��"),				MP_HAICD_NINI,
	Mstr( "�ǐc�t��"),			MP_HAICD_KABESINZUKE,
	Mstr( "�����\�����t��"),	MP_HAICD_YANEKOUSEISENZUKE
};
#define	NHAITICD	(sizeof(z_CdPlc)/sizeof(BZMTBK))
/*
static	const	MCHAR*	z_cCdIzon[] =
{
	Mstr( "����"),
	Mstr( "����"), Mstr( "����"), Mstr( "�V�䍪����"),
	Mstr( "�����ʂȂ�"), Mstr( "�����ʂȂ萂��"), Mstr( "���؉�"),
	Mstr( "���؉������ʕ��s"), Mstr( "���؉�����"), Mstr( "����Ȃ�")
};
static	const	MINT	z_iCdIzon[] =
{
	MP_IZNCD_N, MP_IZNCD_SUIHEI, MP_IZNCD_SUICYOKU, MP_IZNCD_TENJONETAUE,
	MP_IZNCD_YANEMENNARI, MP_IZNCD_YANEMENNARISUICYOKU, MP_IZNCD_TARUKISITA,
	MP_IZNCD_TARUKISITAYANEMENHEIKOU, MP_IZNCD_TARUKISITASUICYOKU, MP_IZNCD_NOKISAKINARI 
};
*/										  
static	const	BZMTBK	z_CdIzon[] =
{
	Mstr( "����"),				MP_IZNCD_N,
	Mstr( "����"),				MP_IZNCD_SUIHEI,
	Mstr( "����"),				MP_IZNCD_SUICYOKU,
	Mstr( "�V�䍪����"),		MP_IZNCD_TENJONETAUE,
	Mstr( "�����ʂȂ�"),		MP_IZNCD_YANEMENNARI,
	Mstr( "�����ʂȂ艔��"),	MP_IZNCD_YANEMENNARIENCYOKU,
	Mstr( "�����ʂȂ萂��"),	MP_IZNCD_YANEMENNARISUICYOKU,
	Mstr( "�����\�����Ȃ�"),	MP_IZNCD_YANEKOSEISENNARI,
	Mstr( "���؉�"),			MP_IZNCD_TARUKISITA,
	Mstr( "���؉������ʕ��s"),
								MP_IZNCD_TARUKISITAYANEMENHEIKOU,
	Mstr( "���؉�����"),		MP_IZNCD_TARUKISITASUICYOKU,
	Mstr( "����Ȃ�"),			MP_IZNCD_NOKISAKINARI
};
#define	NIZONCD	(sizeof(z_CdIzon)/sizeof(BZMTBK))
static	const	BZMTBK	z_CdMarume[] =
{
	Mstr( "����"),				MP_MRMCDN,
	Mstr( "�l�P"),				MP_MRMCD1,
	Mstr( "�l�Q"),				MP_MRMCD2,
	Mstr( "�l�R"),				MP_MRMCD3,
	Mstr( "�l�S"),				MP_MRMCD4,
	Mstr( "�l�U"),				MP_MRMCD6,
	Mstr( "�l�W"),				MP_MRMCD8
};
#define	NMARUMECD	(sizeof(z_CdMarume)/sizeof(BZMTBK))

////////////////////////////////////////////////////////////////////////////
//    �R�[�h�ϊ�
//		return :    -1: ���̓R�[�h�G���[�@��0: ID

static MINT GetCd( const MCHAR* cCd, MINT nCd, const BZMTBK* pCd)
{
	MINT	ic;
	MINT	iCd = -1;
	for ( ic=0; ic<nCd; ic++) {
		if ( Mstrcmp( cCd, pCd[ic].c) == 0) {
			iCd = (MSTNDH)ic;
			break;
		}
	}
//	ASSERT( iCd >= 0);													// �e�[�u���@�ϊ��G���[�@<ERROR>
	if ( iCd >= 0)
		iCd = pCd[iCd].i;
	return iCd;
}

////////////////////////////////////////////////////////////////////////////
//    �G���[�\��
//		return :    -1: ���̓R�[�h�G���[�@��0: ID
void GetCdErrorMsg(
						MCHAR*	sTable,			// (I  ) �e�[�u����
						MCHAR*	sLineNo,		// (I  ) �s�ԍ�
						MCHAR*	sKoumoku,		// (I  ) ���ږ�
						MCHAR*	sCont			// (I  ) ���ړ��e
				)
{
	CString ErrorMsg;
	ErrorMsg.Format(Mstr( "�e�[�u��(%s)�̍s�ԍ�%s ����(%s)��%s�����o�^�ł�"), 
							sTable, sLineNo, sKoumoku, sCont);
	MessageBox( NULL, ErrorMsg, Mstr( "�e�[�u���Ǎ��݃G���["), MB_OK);
}

////////////////////////////////////////////////////////////////////////////
//    ���ރ}�X�^��ǂݍ���

void MhLoadPtsMst()
{
	MINT		ist;
	MINT		ic1;
	MINT		ik;

	MCHAR		TablePath[MAX_PATH];
	MBHZDT		csvTbl;

	MhGp		*MKM;							// �\�����R�[�h
	mhTpPts		*MPT;							// ���ގ�ރ��R�[�h
	MhMbr		*MBR;							// ���@�^�����R�[�h

	MCHAR		CmntF[2];
	MCHAR		cLineNo[3];
	MCHAR		cGp[16];
	MCHAR		cBr[16];
	MCHAR		cInpKb[8];
	MCHAR		cCdHgt[8];
	MCHAR		cCdPlc[10];
	MCHAR		cCdIzon[10];
	MCHAR		cCdMarume[8];
	MCHAR		cCdToritk[2];

	//	�\���i�g�j�e�[�u���̓ǂݍ���

	mcsGetEnvPath( MP_PATH_PARTSTABLE, mcs::GetStr( MM_STR_CSV_KOUSEI), TablePath);

	ist = csvTbl.Open( TablePath);
	ASSERT( ist == 0);													// �\���e�[�u���@�ǂݍ��݊J�n�G���[�@<ERROR>

	for ( ic1=1 ; ic1<MMAX_KUMI && ist!=MBEOF; ) {
		ist = csvTbl.Head( CmntF, 1);
		if ( ist == MBEOF) break;
		if ( *CmntF == '#') continue;

		MKM = &z_Gp[ic1];
		MKM->SetCdGp( ic1);
		ist = csvTbl.GetStr( MKM->GetNmGp(), MHKSSZ_NMKOSEI);			// �E�\���i�g�j�ݒ�
		ist = csvTbl.GetStr( MKM->GetNmFusezu(), MHKSSZ_NMFUSEZU);		// �E���}���ݒ�
		if ( ist == MBEOF) break;
		ic1++;
	}
	ASSERT( ic1 <= MMAX_KUMI);											// �\���e�[�u���@�I�[�o�t���[�@<ERROR>
	z_nGp = ic1;

	ist = csvTbl.Close();

	//	���i��ރe�[�u���̓ǂݍ���
	mcsGetEnvPath( MP_PATH_PARTSTABLE, mcs::GetStr( MM_STR_CSV_PARTS), TablePath);

	ist = csvTbl.Open( TablePath);
	ASSERT( ist == 0);													// ���i��ރe�[�u���@�ǂݍ��݊J�n�G���[�@<ERROR>

	for ( ic1=0 ;ic1<MMAX_PARTSTP && ist!=MBEOF; ) {
		ist = csvTbl.Head( CmntF, 1);
		if ( ist == MBEOF) break;
		if ( *CmntF == '#') continue;									// '#'�@�R�����g

		MPT = &z_TpPts[ic1];											// ���i��ރ��R�[�h

		ist = csvTbl.GetStr( cLineNo, Msizeof( cLineNo));				// �E�s�ԍ��@�ǂݔ�΂�
		ist = csvTbl.GetStr( cGp, Msizeof( cGp));						// �E�\���R�[�h�ݒ�
		if ( ist == MBEOF) break;
		for ( ik=1; ik<z_nGp; ik++) {
			if ( Mstrcmp( cGp, z_Gp[ik].GetNmGp()) == 0) {
				MPT->SetPTGp( &z_Gp[ik]);
//				MPT->m_iGp = ik;
				break;
			}
		}
		ASSERT( ik < z_nGp);											// ���i��ރe�[�u���@�\��(�g)�G���[�@<ERROR>�@print

		ist = csvTbl.GetStr( cBr, Msizeof( cBr));						// �E���ރR�[�h�ݒ�
		if ( ist == MBEOF) break;
		MPT->SetPTBr( GetCd( cBr, NBUNRUI, z_Br));	
		ist = csvTbl.GetStr( MPT->GetPTNmGeneral(), MHPTSZ_NMGENERAL);	// �E���̐ݒ�
		ist = csvTbl.GetStr( MPT->GetPTNmPts1(), MHPTSZ_NMPARTS1);		// �E����p���ޖ��ݒ�
		ist = csvTbl.GetStr( MPT->GetPTNmPts2(), MHPTSZ_NMPARTS2);		// �E�ώZ�p���ޖ��ݒ�
		MINT iPTColor;		ist = csvTbl.GetInt( &iPTColor, 1);			// �E�F
		MPT->SetPTColor( iPTColor); 
		MINT iPTCdBuzaiR;	ist = csvTbl.GetInt( &iPTCdBuzaiR, 1);		// �E���ރR�[�h�ݒ�(�ǂݍ��ݗp)
		MPT->SetPTCdBuzaiR( iPTCdBuzaiR);
		MINT iPTCdBuzaiW;	ist = csvTbl.GetInt( &iPTCdBuzaiW, 1);		// �E���ރR�[�h�ݒ�(�������ݗp Ver Up �Ɏg�p)
		MPT->SetPTCdBuzaiW( iPTCdBuzaiW);
		ist = csvTbl.GetStr( MPT->GetPTTpMbr(), MHPTSZ_TPMEMBER);		// �E���@�^���I��p��ރR�[�h�ݒ�
		ist = csvTbl.GetStr( MPT->GetPTCdMbr(), MHPTSZ_CDMEMBER);		// �E���@�^���R�[�h�ݒ�
		ist = csvTbl.GetStr( cInpKb, Msizeof( cInpKb));					// �E���̓R�[�h
		MPT->SetPTInpKb( GetCd( cInpKb, NInpKb, z_InpKb));	
		ist = csvTbl.GetStr( cCdHgt, Msizeof( cCdHgt));					// �E���t�������R�[�h
		MPT->SetPTCdHgt( (MSTNDH)GetCd( cCdHgt, NHEIGHTCD, z_CdHgt));								
		ist = csvTbl.GetStr( cCdPlc, Msizeof( cCdPlc));					// �E�z�u�R�[�h
		MPT->SetPTCdPlc( GetCd( cCdPlc, NHAITICD, z_CdPlc));							
		ist = csvTbl.GetStr( cCdIzon, Msizeof( cCdPlc));				// �E�ˑ��R�[�h
		MPT->SetPTCdIzon( GetCd( cCdIzon, NIZONCD, z_CdIzon));								
		ist = csvTbl.GetStr( cCdMarume, Msizeof( cCdMarume));			// �E�ۂ߃R�[�h
		MPT->SetPTCdMarume( GetCd( cCdMarume, NMARUMECD, z_CdMarume));	
		ist = csvTbl.GetStr( cCdToritk, Msizeof( cCdToritk));			// �E���t���ʒu�R�[�h('��':��t��(1), '��':���t��(0))
//		if ( cCdToritk[0] == MCHAR( '��'))
		if ( cCdToritk[0] == Mchar( '��'))
			MPT->SetPTCdToritk( 1);
		else	
			MPT->SetPTCdToritk( 0);
		if ( ist == MBEOF) break;
		ic1++;
	}
	ASSERT( ic1 <= MMAX_PARTSTP);										// ���i��ރe�[�u���@�I�[�o�t���[�@<ERROR>
	z_nTpPts = ic1;
	
	ist = csvTbl.Close();
	
	//	���@�^���e�[�u���̓ǂݍ���
	mcsGetEnvPath( MP_PATH_PARTSTABLE, mcs::GetStr( MM_STR_CSV_MEMBER), TablePath);

	ist = csvTbl.Open( TablePath);
	ASSERT( ist == 0);													// ���@�^���e�[�u���@�ǂݍ��݊J�n�G���[�@<ERROR>
	
	for ( ic1=0; ic1<MMAX_MEMBER && ist!=MBEOF; ) {
		ist = csvTbl.Head( CmntF, 1);
		if ( ist == MBEOF) break;
		if ( *CmntF == '#') continue;

		MBR = &z_Mbr[ic1];
		ist = csvTbl.GetStr( cLineNo, Msizeof( cLineNo));				// �E�s�ԍ��@�ǂݔ�΂�
		ist = csvTbl.GetStr( MBR->m_cMbrCode, MHMBSZ_CODE);				// �E���@�^���ݒ�
		ist = csvTbl.GetReal( (MREAL*)&MBR->m_rBziWidth, 1);			// �E���ݒ�
		ist = csvTbl.GetReal( (MREAL*)&MBR->m_rBziSZure, 1);			// �E�c����ʐݒ�
		ist = csvTbl.GetReal( (MREAL*)&MBR->m_rBziHeight, 1);			// �E�����ݒ�
		ist = csvTbl.GetStr( MBR->m_cMbrType, MHMBSZ_TYPE);				// �E���@�^���I��p��ރR�[�h�ݒ�
		ist = csvTbl.GetStr( MBR->m_cMbrCodeW, MHMBSZ_CODEW);			// �E���@�^���ݒ�@(�������ݗp�@�ʏ�m_cCode�Ɠ��� VerUp���ɕύX�������e������)
		if ( ist == MBEOF) break;
		ic1++;
	}
	if ( Mstrcmp( z_Mbr[0].m_cMbrCode, Mstr( "����")) == 0)
		z_Mbr[0].m_cMbrCode[0] = NULL;									// �擪�̐��@�^��=="����"��NULL�ɒu��������
	ASSERT( ic1 <= MMAX_MEMBER);										// ���@�^���e�[�u���@�I�[�o�t���[�@<ERROR>
	z_nMbr = ic1;

	ist = csvTbl.Close();
}

// ���ރ}�X�^�[��ǂݍ���
void IeModel::MhInitPts()
{
	MhLoadPtsMst();
}

// �g���R�[�h�����擾����
MINT BuzaiCode::MhGetNoOfGp()
{
	return z_nGp;
}

// �g���R�[�h���擾����
//MhGp* BuzaiCode::MhGeTpGp(
//				MINT		iGp					// �ǂݍ��ݍ\�����R�[�h�ԍ�
//				)
//{
//	return &z_Gp[iGp];
//}

// ���i��ރ��R�[�h�����擾����
MINT BuzaiCode::MhGetNoOfTpPts()
{
	return z_nTpPts;
}

// ���i��ރ��R�[�h���擾����
mhTpPts* BuzaiCode::MhGetpTpPts(
				MINT		iTpPts				// �ǂݍ��ݕ��i��ރ��R�[�h�ԍ�
				)
{
	return &z_TpPts[iTpPts];
}

// ���iID���擾����
MINT BuzaiCode::MhGetPIIdTpPts(
						MINT	iCdBuzai		// ���ރR�[�h
				)
{
	MINT		ic1;
	MINT		iIdTpPts = -1;
	
	for ( ic1=0; ic1<z_nTpPts; ic1++) {
		if ( iCdBuzai == z_TpPts[ic1].GetPTCdBuzai()) {
			iIdTpPts = ic1;
		}
	}
	return iIdTpPts;
}

// ���@�^�����R�[�h�����擾����
MINT BuzaiCode::MhGetNoOfMbr()
{
	return z_nMbr;
}

// ���@�^�����R�[�h���擾����
MhMbr* BuzaiCode::MhGetpMbr(
				MINT		iMbr				// �ǂݍ��ݐ��@�^�����R�[�h�ԍ�
				)
{
	MhMbr*	pMbr;
	if ( iMbr >= 0)
		pMbr = &z_Mbr[iMbr];
	else 
		pMbr = &z_Mbr[0];
	return pMbr;
}

// ���@�^��ID���擾����
MINT	BuzaiCode::MhGetIdMbr(
						MCHAR*		pMbr		// ���@�^��
				)
{
	MINT		ic1;
	MINT		iMbr = -1;
	
	for ( ic1=0; ic1<z_nMbr; ic1++) {
		if ( Mstrcmp( pMbr, z_Mbr[ic1].GetMbrCode()) == 0) {
			iMbr = ic1;
		}
	}
	return iMbr;
}

// ���ނ̂Q�����c�����擾����
void	BuzaiCode::MhBziSin(
						mhPlcInfo	*pBziInfo,	// (I  ) ����
						MgLine2		*plnBziSin	// (  O) ���ނ̐c��
				)
{
	MgLine2		LnPts;
	MgPoint2	ptW[2];
	MgVect2		VtW, VtUtW;
	MgVect2		VtSZ;							// �c����
	MgPoint2	ptS[2];
	
	ptW[0] = *(MgPoint2*)&(pBziInfo->GetPIPlcIti( 0));
	ptW[1] = *(MgPoint2*)&(pBziInfo->GetPIPlcIti( 1));

	// ���ނ̌`�����ߌ�������
	VtW = ptW[1] - ptW[0];													// �c��
	VtUtW = MGeo::UnitizeV2( VtW);											// ���ނ̌`�����߂�
	if ( pBziInfo->IsFrame()) {												// ���Ęg�p�̌`��쐬
	}
	VtSZ = pBziInfo->GetPISinZure() * VtUtW.RotR90();
	ptS[0] = ptW[0] - pBziInfo->GetPILenHosei( 0) * VtUtW + VtSZ;
	ptS[1] = ptW[1] + pBziInfo->GetPILenHosei( 1) * VtUtW + VtSZ;
	*plnBziSin = MgLine2( ptS[0], ptS[1]);
}

// �z�u�f�[�^�@�g���[�X
void	mhPlcInfo::Print(MCHAR* s)
{
#ifdef _DEBUG
//	Msprintf_s( mlLog::m_Str, Mstr( "%s 	mhPlcInfo\n", s);
	MCHAR sTrc[256], sCat[256];
	MUINT*	pVmb;

	m_lnPlc.Print( Mstr( "mhPlcInfo Line") );
//	Msprintf_s( mlLog::m_Str, Mstr( "%s OnOpt %x %x %x, OffOpt %x %x %x\n"), s, m_pOpt1);
	if ( m_pOpt1) {
		pVmb = m_pOpt1->GetSOB();
		Msprintf_s( sTrc, Mstr( "OnOpt %x %x %x"), pVmb[0], pVmb[1], pVmb[2]);
	} else {
		Mstrcpy_s( sTrc, Mstr( "OnOpt NULL"));
	}
	if ( m_pOpt2) {
		pVmb = m_pOpt2->GetSOB();
		Msprintf_s( sCat, Mstr( " OffOpt %x %x %x"), pVmb[0], pVmb[1], pVmb[2]);
	} else {
		Mstrcpy_s( sCat, Mstr( " OffOpt NULL"));
	}
	Mstrcat_s( sTrc, sCat);

	Msprintf_s( mlLog::m_Str, Mstr( "%s %s\n"), s, sTrc);
	MBTRCPRBF;
#endif
}

// �S�z�u���e���g���[�X
void	BuzaiCode::MhPrintallmhPlcInfo(MCHAR* s)
{
#ifdef _DEBUG
	mhPlcInfo* pPlcEn;
	MPOSITION	PtsPos;

	Msprintf_s( mlLog::m_Str, Mstr( "%s 	All mhPlcInfo\n"), s);
	for (pPlcEn = HaitiDb::MdGetHeadPts( &PtsPos); pPlcEn!=0; pPlcEn = HaitiDb::MdGetNextPts( &PtsPos)) {
		pPlcEn->Print( s);
	}
	MBTRCPRBF;
#endif
}

//�@���u���ނƉ��u���ނ̈ʒu�֌W�𒲂ׂ�B
//�@�Q�����ނ��d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//  �Q�����ނ��d�Ȃ�Ȃ������I�Ɍ������Ă���ꍇ�͂��̌����_����_�Ƃ݂Ȃ��B
MINT	MhSenBuzai::MhOn(										// (  O) �X�e�C�^�X
												//	MC_PARALLEL	(-1) �����Ȃ��i���s�j
												//  MC_CONNECTION(4) �ڑ�	 �i���s�j
												//	MC_TWIST    (-2) �����Ȃ��i�˂���j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MhSenBuzai	&Bz1,		// (I  ) ������1
				const	MhSenBuzai	&Bz2,		// (I  ) ������2
						MgPoint3	*Po,		// (  O) ��_
						MINT		*ist1,		// (  O) �⏕�X�e�C�^�X1
												// 			MC_LEFT:	������1�͐�����2�̍����ɂ���	�i�����Ȃ��j
												// 			MC_RIGHT:	������1�͐�����2�̉E���ɂ���	�i�����Ȃ��j
												//			MC_CLOSS:	������1�͐�����2�ƌ���			�i��������j
												//			MC_ON_LINE:	������1�͐�����2�̒�����ɂ���	�i���s�j
						MINT		*ist2		// (  O) �⏕�X�e�C�^�X2
												// 			MC_PS_NEAR:	������1�͐�����2���n�_���������i�����Ȃ��܂��͌�������j
												// 			MC_PE_NEAR:	������1�͐�����2���I�_���������i�����Ȃ��܂��͌�������j
												// 			MC_PARALEL:	������1�͐�����2���n�_�ƏI�_�͓�����	�i���s�j
				)
{
	MINT		ist;
	
	MgPoint3	PtInt;
	MREAL		s1, s2;							// ���������w���_�ƕ���1�̕���2�ɑ΂��鍶�E�ʒu

	MgVect3	VtUtZ( 0., 0., 1.);

	ist = MGeo::Intr2Ln3( Bz1.Ln, Bz2.Ln, Po);					// ��_
	if ( !MF_CHECK_OR( ist, (MC_INT | MC_NINT))) {
		if ( MGeo::ChkLn3OnLn3( Bz1.LnWH, Bz2.LnWH)) {
			*ist1 = MC_ON_LINE;									// ������1�͐�����2�̒�����ɂ���	�i���s�j
		} else {
			*ist1 = 0;
		}
		*ist2 = MC_PARALLEL;
		goto exit;												// �����Ȃ��̂��ߖ�����
	}

																// �����������ނ̒�����̕��ނɑ΂��鍶�E�ʒu�ƃJ�b�g�[�����߂�
	s1 = (Bz2.vtUt ^ (Bz1.LnWH.p[0] - Bz2.LnWH.p[0])) * VtUtZ;	// s1>0: �����������ނ̔z�u�_�͒���������̕��ނ̍���
	s2 = (Bz2.vtUt ^ (Bz1.LnWH.p[1] - Bz2.LnWH.p[0])) * VtUtZ;	// s2>0: �����������ނ̔z�u�����_�͒���������̕��ނ̍���

	if ( s1 > 0 && s2 > 0) {									// �����������ނ͒���������̕��ނ̍����ɂ���
		*ist1 = MC_LEFT;
//		if ( s1 < s2) {
//			*ist2 = MC_PS_NEAR;									// �z�u�_���̒�����␳
//		} else {
//			*ist2 = MC_PE_NEAR;									// �z�u�����_���̒�����␳
//		}
	} else if ( s1 < 0 && s2 < 0) {								// �����������ނ͒���������̕��ނ̉E���ɂ���
		*ist1 = MC_RIGHT;
//		if ( s1 > s2) {
//			*ist2 = MC_PS_NEAR;									// �z�u�_���̒�����␳
//		} else {
//			*ist2 = MC_PE_NEAR;									// �z�u�����_���̒�����␳
//		}
	} else {													// �����������ނ͒���������̕��ނ̍��E���ɂ܂������Ă���
		*ist1 = MC_CLOSS;
	}
	if ( MGABS(s1) < MGABS(s2)) {
			*ist2 = MC_PS_NEAR;									// �z�u�_���̒�����␳
	} else {
			*ist2 = MC_PE_NEAR;									// �z�u�����_���̒�����␳
	}
exit:;
	return ist;
}

} // namespace MC