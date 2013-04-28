#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmSet.h
//
//		�֌W�ݒ�
//
//
#include	"MdmDefine.h"
#include	"MdAry.h"
#include	"MdAryH.h"
#define MDC_DELETE 0x7DCDCDC

// �l�c�a�̂h�c��z��ԍ��ɕϊ�����
//inline MINT MIDtoHN( MINT i_id) { return ( i_id - 1); }
#define MIDtoHN( id)  ( id - 1)
// �l�c�a�̔z��ԍ����h�c�ɕϊ�����
//inline MINT MHNtoID( MINT i_idS) { return ( i_idS + 1); }
#define MHNtoID( idS) ( idS + 1)

namespace MC
{

enum MDCONCTYPE {
	
};

//==========================================================================================
//class MdRelation
//{
//	MINT		type;
//	MdEnt*	pEntP;
//	MdEnt*	pEntC;
//};

//==========================================================================================
//	�e�q�֌W�̃Z�b�g
//	�E�Z�b�g�ƃZ�b�g�̊֌W
//	�E�Z�b�g�ƃG���e�B�e�B�̊֌W
//	�E�G���e�B�e�B�ƃZ�b�g�̊֌W
//	�eID�ƎqID�g�ݍ��킹
//	(�Q�e�����֌W�̃Z�b�g�̒�`�Ɏg�p)
//==========================================================================================
class MdeCombPC
{
	MDID		m_idP;							// �eID
	MDID		m_idC;							// �qID

public:
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

//==========================================================================================
//	�֌W�̃Z�b�g
//	�E�G���e�B�e�B�ƃG���e�B�e�B�̊֌W
//	�֌W�R�[�h�Ƒ���1�A����2�A�qID�g�ݍ��킹
//==========================================================================================
class MdeRfC
{
	MUCHAR		m_iC;							// �֌W�R�[�h
	MUCHAR		m_iA;							// �����R�[�h
	MSHORT		m_iLp;							// ���[�v�R�[�h
	MDID		m_idC;							// �qID

public:
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

//	�g���[�X
inline void MdeRfC::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str,
			  Mstr( "�E%s < MdeRfC > ID = %d, �֌W�R�[�h = %d, �����R�[�h = %d, ���[�v�R�[�h = %d, �qID = %d\n"),
			  s, i_i, m_iC, m_iA, m_iLp, m_idC);
	MBLOGPRBF;
#endif
}

class MDIDSET : public MdAryH_S_I<MDID> 		// ID(MDID)�Z�b�g(�S)
{
public:
	MDIDSET() : MdAryH_S_I() {};
	MDIDSET( MUSHORT i_sz) : MdAryH_S_I( i_sz) {};
};

class MDRFCSET : public MdAryH_S_C<MdeRfC>		// �֌W�R�[�h�A�����R�[�h�A���[�v�R�[�h,�qID}�Z�b�g
{
public:
	MDRFCSET() : MdAryH_S_C<MdeRfC>() {};
	MDRFCSET( MUSHORT i_sz) : MdAryH_S_C<MdeRfC>( i_sz) {};
};

class MUBYTESET : public MdAryH_S_B<MUBYTE> 	// �E�B���h�E�\�����n���[�h�Z�b�g
{
public:
	MUBYTESET() : MdAryH_S_B<MUBYTE>() {};
	MUBYTESET( MUSHORT i_sz) : MdAryH_S_B<MUBYTE>( i_sz) {};
};

//class MDFIG : public MdAryH_S_I<MINT> 		// �}�`���(�ϒ����[�h(���ɐ����Œ�`))
//{
//public:
//	MUSHORT	m_isz;
//	MUSHORT	m_n;
//	MINT	m_pst[100];
//
//	MUSHORT	icdPrim( MINT iP)
//				{ return ((MUSHORT*)&m_pst[iP])[0];}
//	MUSHORT	Next( MINT iP)
//				{ return (iP + ((MUSHORT*)&m_pst[iP])[1]);}
//	MINT*	pPrim( MINT iP)
//				{ return &m_pst[iP + 1];}
//};

//==========================================================================================
//	�폜�f�[�^�����N�t���Z�b�g
template <typename T>
class MdAryH_F_D : public MdAryH_F<typename T>
{
public:
	MDID		m_idSpaceLast;					// (�폜�ɂ��)�ŏI�󂫃��R�[�hID
	MINT		m_nidSpace;						// (�폜�ɂ��)�󂫃��R�[�hID��

public:
	MdAryH_F_D() {
		m_idSpaceLast = 0;
		m_nidSpace = 0;
	}
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

//	�g���[�X
template <typename T>
inline void MdAryH_F_D<T>::Print( MCHAR* i_s, MINT i_i)
{
#ifdef _DEBUG
	if ( i_i == MDC_NONE_ID) {
		if ( m_idSpaceLast ==0 && m_nidSpace == 0) {
			Msprintf_s( mlLog::m_Str, Mstr( "%s < MdAryH_F_D >\n"), i_s);
		} else {
			Msprintf_s( mlLog::m_Str, Mstr( "%s < MdAryH_F_D > �ŏI�󂫃��R�[�hID = %d, �󂫃��R�[�hID�� = %d\n"),
											i_s, m_idSpaceLast, m_nidSpace);
		}
	} else {
		if ( m_idSpaceLast ==0 && m_nidSpace == 0) {
			Msprintf_s( mlLog::m_Str, Mstr( "%s < MdAryH_F_D > ID = %d\n"), i_s, i_i);
		} else {
			Msprintf_s( mlLog::m_Str, Mstr( "%s < MdAryH_F_D > ID = %d�C�ŏI�󂫃��R�[�hID = %d, �󂫃��R�[�hID�� = %d\n"),
											i_s, i_i, m_idSpaceLast, m_nidSpace);
		}
	}
	MBLOGPRBF;
	// �O���[�v(�Z�b�g)�L���f�[�^�o��
	int iG;
	for ( iG=1; iG<=m_n; iG++) {
		if ( MDSPACEID( &m_pst[MIDtoHN( iG)]) != MDID_DELETE)				// Valid�O���[�v�f�[�^
			m_pst[MIDtoHN( iG)].Print( Mstr( "���R�[�h"), iG);
	}

	// �O���[�v(�Z�b�g)�폜�f�[�^�̃����N���o��
	MDID	idDelTrc;
	MDIDSET	GidSpNext( 100);
	MDIDSET GidSpBefore( 100);

	idDelTrc =  m_idSpaceLast;

	if ( idDelTrc)
		MBLOGPRINTI( Mstr( "\tLAST�폜ID"), idDelTrc);

	for ( ; GidSpNext.m_n < m_nidSpace && idDelTrc; ) {
		GidSpNext += MDSPACENEXT( &m_pst[MIDtoHN( idDelTrc)]);
		GidSpBefore += MDSPACEBEFORE( &m_pst[MIDtoHN( idDelTrc)]);
		idDelTrc = MDSPACEBEFORE( &m_pst[MIDtoHN( idDelTrc)]);
	}

	if ( GidSpNext.m_n) {
		MBLOGPRINTIN( Mstr( "\t�폜NextID�Z�b�g"), GidSpNext.m_pst, GidSpNext.m_n);
		MBLOGPRINTIN( Mstr( "\t�폜BeforeID�Z�b�g"), GidSpBefore.m_pst, GidSpBefore.m_n);
	}
#endif
}

} // namespace MC
