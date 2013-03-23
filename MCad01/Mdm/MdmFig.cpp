#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdFig.h
//
//		�}�`���
//
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgMat.h"

#define	DLL_EXPORT_MDFIG_DO

#include "MdModel.h"

#include "MdmDefine.h"
#include "MdAry.h"
#include "MdAryH.h"

#undef	inline_nu
#define inline_nu

namespace MC
{

/*
// �v���~�e�B�u�w�b�_���[�h���쐬����
inline_nu MINT MdPhd(  MUBYTE i_icd, MUBYTE i_itp, MUSHORT i_n)
{
	MDPHD	clsPhd;
	clsPhd.Init( i_icd, i_itp, i_n);
	return *(MINT*)&clsPhd;
} 

// CLASS MDPMTL

inline_nu MINT	MDPMTL::GetSz()	const						// �}�`���o�b�t�@�T�C�Y
{ 
	return m_sz;
}
inline_nu MINT	MDPMTL::GetN() const						// �}�`���T�C�Y
{
	return m_n;
}
inline_nu MREAL*	MDPMTL::GetP( MINT i_ip)				// �}�`���|�C���^
{
	return &m_pmt[i_ip];
}

inline_nu void	MDPMTL::SetSz( MINT i_sz)					// �}�`���o�b�t�@�T�C�Y
{
	m_sz = i_sz;
}
inline_nu void	MDPMTL::SetN( MINT i_n)						// �}�`���T�C�Y
{
	m_n = i_n;
}

// CLASS MDFIG

//	�R���X�g���N�^
inline_nu MDFIG::MDFIG()									
{
	m_pPmtl = 0;
}

inline_nu MDFIG::MDFIG(
				 MINT		i_sz							// �}�`���T�C�Y
				)
{
	MBMALLOCF( MDPMTL, m_pPmtl, MINT, i_sz);
	m_pPmtl->SetSz( i_sz);
	m_pPmtl->SetN( 0);
}
*/

// �}�`���̃o�b�t�@�T�C�Y�𓾂�
inline_nu MINT	MDFIG::GetSz() const						// �}�`���o�b�t�@�T�C�Y
{ 
	return ( m_pPmtl ? m_pPmtl->GetSz(): 0);
}

inline_nu MINT	MDFIG::GetN() const							// �}�`���T�C�Y
{
	return ( m_pPmtl ? m_pPmtl->GetN(): 0);
}

inline_nu MDPMTL* MDFIG::GetpPmtl()								// �}�`���
{ 
	return m_pPmtl;
}  

inline_nu void	MDFIG::SetSz( MINT i_sz)					// �}�`���o�b�t�@�T�C�Y
{
	ASSERT( m_pPmtl);
	m_pPmtl->SetSz( i_sz);
}

inline_nu void	MDFIG::SetN( MINT i_n)						// �}�`���T�C�Y
{
	ASSERT( m_pPmtl);
	m_pPmtl->SetN( i_n);
}

inline_nu void	MDFIG::SetpPmtl( MDPMTL* i_pPmtl)				// �}�`���
{
	m_pPmtl = i_pPmtl;
}

// �}�`�v�f
inline_nu MDPMT* MDFIG::GetpPmt( MDID i_idl)				// �}�`�v�f
{ 
//	return ( (MDPMT*)m_pPmtl->GetpPmt( i_idl));
	return m_pPmtl->GetpPmt( i_idl);
}  

inline_nu MINT	MDFIG::GetPmtCd( MDID i_idl)				// �}�`�v�f�̃R�[�h
{
	return ( GetpPmt( i_idl)->GetCd());
}

inline_nu MINT	MDFIG::GetPmtDm( MDID i_idl)				// �}�`�v�f�̎���
{
	return ( GetpPmt( i_idl)->GetDm());
}

//inline_nu MINT	MDFIG::GetPmtTp( MDID i_idl)			// �}�`�v�f�̃^�C�v
//{
//	return ( GetpPmt( i_idl)->GetTp());
//}

inline_nu MINT	MDFIG::GetPmtN( MDID i_idl)					// �}�`�v�f�̃T�C�Y
{
	return ( GetpPmt( i_idl)->GetN());
}

inline_nu MDID	MDFIG::GetNextPmt( MDID i_idl)				// ���̐}�`�v�f��IDL(�z��ԍ�)
{
	return ( i_idl + GetpPmt( i_idl)->GetN() + MP_SZ_MDHDR);
}

inline_nu void	MDFIG::SetHd( MDID i_idl, MINT i_icd,
							  MINT i_idm, MINT i_n)			// �}�`�v�f�̃R�[�h�A�����A�T�C�Y
{
	GetpPmt( i_idl)->SetCd( i_icd);
	GetpPmt( i_idl)->SetDm( i_idm);
	GetpPmt( i_idl)->SetN( i_n);
}

inline_nu void	MDFIG::SetPmtCd( MDID i_idl, MINT i_icd)	// �}�`�v�f�̃R�[�h
{
	return ( GetpPmt( i_idl)->SetCd( i_icd));
}

inline_nu void	MDFIG::SetPmtDm( MDID i_idl, MINT i_idm)	// �}�`�v�f�̎���
{
	return ( GetpPmt( i_idl)->SetDm( i_idm));
}

//inline_nu void	MDFIG::SetPmtTp( MDID i_idl, MINT i_itp)	// �}�`�v�f�̃^�C�v
//{
//	return ( GetpPmt( i_idl)->SetTp( i_itp));
//}

inline_nu void	MDFIG::SetPmtN( MDID i_idl, MINT i_n)		// �}�`�v�f�̃T�C�Y
{
	return ( GetpPmt( i_idl)->SetN( i_n));
}

// �}�`���S�̍Ō�̐}�`���ɗv�f��ǉ�
//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
inline_nu void MDFIG::operator += ( const MREAL i_r)				// Fig -= i
{
	if ( m_pPmtl->GetN() >= m_pPmtl->GetSz()) {
		ReSize( m_pPmtl->GetSz() + MGMAX( m_pPmtl->GetSz(), 4));
	}															// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_pPmtl->m_dt[m_pPmtl->m_n++] = i_r;
}

//	����				�\���̌Q = �\���̌Q
inline_nu void MDFIG::operator = ( const MDFIG& i_Fig)
{
	MINT	wi_n;
	MINT	w_sz;

	if ( i_Fig.m_pPmtl == 0) {
		if ( m_pPmtl)
			SetN( 0);
	} else {
		wi_n = i_Fig.m_pPmtl->m_n;
		w_sz = m_pPmtl ? m_pPmtl->m_sz: 0;

		if ( wi_n > w_sz) {
			MBFREE( m_pPmtl);									//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E			MBMALLOCF( MDPMTL, m_pPmtl, MINT, (wi_n + 1));		//	�\���_�̗̈��malloc�Ŋm��
			MbAllocF<MDPMTL,MINT>( m_pPmtl, wi_n + 1);
			SetSz( wi_n);
		}
		memcpy( m_pPmtl, i_Fig.m_pPmtl, SZMINT( wi_n + 1));
		SetN( wi_n);
	}
}

//	����				�\���̌Q = �\���̌Q
inline_nu void MDFIG::operator = ( const MDPMT& i_Pmt)
{
	MINT	wi_n;
	MINT	w_sz;

	wi_n = i_Pmt.GetN() + 1;
	w_sz = m_pPmtl ? m_pPmtl->m_sz: 0;

	if ( wi_n > w_sz) {
		MBFREE( m_pPmtl);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOCF( MDPMTL, m_pPmtl, MINT, wi_n);				//	�\���_�̗̈��malloc�Ŋm��
		MbAllocF<MDPMTL,MINT>( m_pPmtl, wi_n);
		SetSz( i_Pmt.GetN());
	}
	memcpy( &((MREAL*)m_pPmtl)[1], &i_Pmt, SZMINT( wi_n));

	SetN( wi_n);
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
inline_nu void MDFIG::operator += ( const MDFIG& i_Fig)			// Fig += Fig
{
	MINT	w_n;
	MINT	w_sz;

	if ( i_Fig.m_pPmtl && i_Fig.m_pPmtl->m_n) { 
		w_n = m_pPmtl->m_n + i_Fig.m_pPmtl->m_n - MP_SZ_MDHDR;


		if ( w_n > m_pPmtl->m_sz) {
			w_sz = MGMAX( ( m_pPmtl->m_sz + m_pPmtl->m_sz), w_n);
			ReSize( w_sz);										//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		}
		memcpy( &((MINT*)m_pPmtl)[m_pPmtl->m_n], 
				&((MINT*)i_Fig.m_pPmtl)[1],
				SZMINT( i_Fig.m_pPmtl->m_n - MP_SZ_MDHDR));
		SetN( w_n);
	}
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
inline_nu void MDFIG::operator += ( const MDPMT& i_Pmt)			// Fig += Fig
{
	MINT	w_n;
	MINT	w_sz;

	if ( i_Pmt.GetN()) { 
		w_n = m_pPmtl->m_n + i_Pmt.GetN() - MP_SZ_MDHDR;

		if ( w_n > m_pPmtl->m_sz) {
			w_sz = MGMAX( ( m_pPmtl->m_sz + m_pPmtl->m_sz), w_n);
			ReSize( w_sz);										//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		}
		memcpy( &((MINT*)m_pPmtl)[m_pPmtl->m_n], 
				&((MINT*)&i_Pmt)[1],
				SZMINT( i_Pmt.GetN() - MP_SZ_MDHDR));
		SetN( w_n);
	}
}

////	�\���\���̂�()�Ŏw�肵�ēǂݏ�������
////	��@Gst1(n).p, Gst1(n).i1, Gst1(n).i2
//inline_nu T& MDFIG::operator () (MUSHORT i_idx)
//{
//	if ( i_idx == m_sz) {
//		ReSize( m_sz + MGMAX( m_sz, 4));						//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
//	} else if ( idx > m_sz) {
//		MbSysError( MBCstr( "MdAryH()"), MC_ERR_OVERFLOW);
//	}
//	for (; m_n<=i_idx; n++) m_st[m_n].SetInit();				//	�ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
//	return m_st[i_idx];
//}

////	�\���̌Q�̈�̊m��
//inline_nu void MdAryH<T>::Alloc( MUSHORT i_sz)
//{
//	MBMALLOC( m_st, T, i_sz);									//	�\���\���̗̂̈��malloc�Ŋm��
//	memset( m_st, 0, sizeof( T) * (i_sz));
//	m_sz = i_sz;
//}

//	�\���̌Q�̈�̊m��
inline_nu void MDFIG::Alloc( MINT i_sz)
{
	ASSERT( m_pPmtl == 0);

//E	MBMALLOCF( MDPMTL, m_pPmtl, MINT, i_sz);					//	�\���_�̗̈��malloc�Ŋm��
	MbAllocF<MDPMTL,MINT>( m_pPmtl, i_sz);
	SetSz( i_sz);
}

//	�\���̌Q�̈�̃T�C�Y�ύX
inline_nu void MDFIG::ReSize( MINT i_sz)
{
	MDPMTL*	pFigs;

	if ( i_sz > m_pPmtl->m_sz) {
//E		MBMALLOCF( MDPMTL, pFigs, MINT, i_sz);					//	�\���_�̗̈��malloc�Ŋm��
		MbAllocF<MDPMTL,MINT>( pFigs, i_sz);
		memcpy( pFigs, m_pPmtl, SZMINT( i_sz));
		SetSz( i_sz);

		MBFREE( m_pPmtl);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_pPmtl = pFigs;
	}
}

//	�\���̌Q�̈�̊m��
inline_nu void MDFIG::IncrN( MINT i_n)
{
	MINT	n = m_pPmtl->m_n + i_n;
	ReSize( n);
	m_pPmtl->m_n = n;
}

// �}�`���f�[�^���𑝂₷
//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
inline_nu MDPMT* MDFIG::PmtAlloc( MINT i_n)
{
	MINT	sv_n;
	MINT	w_n;
	MINT	w_sz;

	sv_n = m_pPmtl->m_n;
	w_n = sv_n + i_n;

	if ( w_n > m_pPmtl->m_sz) {
		w_sz = m_pPmtl->m_sz + MGMAX( w_n, 4);
		ReSize( w_sz);										//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	}
	m_pPmtl->m_n = w_n;
	return (MDPMT*)&m_pPmtl->m_dt[sv_n];
}

//	�g���[�X
inline_nu void MDFIG::Print(MCHAR* i_s)
{
#ifdef _DEBUG
	if ( m_pPmtl) {
		Msprintf_s( mlLog::m_Str, Mstr( "\t\t\t%s < MDFIG > �����^�f�[�^�Z�b�g�C�T�C�Y =%d�C�f�[�^�� = %d\n"),
										i_s, m_pPmtl->m_sz, m_pPmtl->m_n);
		MBTRCPRBF;
		if ( m_pPmtl->m_n > 103) 
			 int iDumy = 1;

	}
//	MBTRCPRINTIN( Mstr( "\t\t\t�f�[�^"), m_pPmtl->m_st, m_n);
#endif
}

} // namespace MC