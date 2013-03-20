#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmLyr.h
//
//		�l�b�`�c���f��
//						���C���[
//
//==========================================================================================
//	�Q�e�����qID�Z�b�g
#include	"MdmFig.h"

namespace MC
{

class MdmSetLYR
{
public:
	MDID		m_idP1;							// �eID1	�O���[�vId ( >=0)	( -1: �폜���������C���[)
	MDID		m_idP2;							// �eID2	�X�L�[�}Id
	MDIDSET		m_GidC;							// �qID�Q
	MUBYTESET	m_GaWD;							// �E�B���h�E�\�����n���[�h(�E�B���h�E���ݒ�)
												//		0: �\�� OFF	���n OFF
												//		1: �\�� ON	���n OFF
												//		2: �\�� ON	���n ON
												//		3: �\�� OFF	���n OFF	Lock
												//		4: �\�� ON	���n OFF	Lock
												//		5: �\�� ON	���n ON		Lock
	MDFIG		m_DfltFig;						// �f�t�H���g�\������
	MDFIG		m_CurFig;						// �J�����g�\������

public:
	MdmSetLYR()		{ Init();}					// 2008/05/05 add
	~MdmSetLYR()		{ Free();}					// 2008/05/05 add
	void Init()
	{
		m_GidC.Init();
		m_GaWD.Init();
		//m_DfltFig.Alloc();
		//m_CurFig.Alloc();
	}
	void Free()
	{
		m_GidC.Free();
		m_GaWD.Free();
		m_DfltFig.Free();
		m_CurFig.Free();
	}
	// �qID�Z�b�g����
	//	�ő�w�萔��(�q��)ID�������̈���m�ۂ���
	void* operator new( size_t i_sz);			// �����̍ő�qID��
	////	�̈���J������
	//void* operator delete();
	// �qID��ǉ�����
	void operator += ( MDID i_idMd);
	// �qID���폜����
	void operator -= ( MDID i_idMd);
	// �qID�Z�b�g�ɏ����l��ݒ肷��
	void SetInit(
						MDID	i_idP1,			// �eID1
						MDID	i_idP2,			// �eID2
						MINT	i_szCID,		// �qID�G���A�T�C�Y
						MINT	i_szMdD		// �\�����m���[�h�ݒ�E�B���h�E��
				);
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

// �Q�e�����qID�Z�b�g����
//	�ő�w�萔��(�q��)ID�������̈���m��
inline void* MdmSetLYR::operator new( size_t i_sz)
{
	MdmSetLYR* pSetLC = (MdmSetLYR*)DEBUG_NEW char[sizeof( MdmSetLYR)];
	pSetLC->m_idP1 = 0;
	pSetLC->m_idP2 = 0;
	pSetLC->m_GidC.Alloc( (int)i_sz);
	return pSetLC;
}

// �Q�e�����qID�Z�b�g�ɎqID��ǉ�����
inline void MdmSetLYR::operator += (MDID i_idMd)
{
	m_GidC += i_idMd;
}

// �Q�e�����qID�Z�b�g�̎qID���폜����
inline void MdmSetLYR::operator -= (MDID i_idMd)
{
	MINT iC;
	bool bFnd = false;
	for ( iC=0; iC<m_GidC.m_n; iC++) {
		if ( m_GidC.m_st[iC] == i_idMd) {
			for ( iC++; iC<m_GidC.m_n; iC++) {
				m_GidC.m_st[iC-1] = m_GidC.m_st[iC];
			}
			m_GidC.m_n --;
			bFnd = true;
			break;
		}
	}
	ASSERT( bFnd);
}

// �Q�e�����qID�Z�b�g�ɏ����l��ݒ肷��
inline void MdmSetLYR::SetInit(
						MDID	i_idP1,			// �eID1
						MDID	i_idP2,			// �eID2
						MINT	i_szCID,		// �qID�G���A�T�C�Y
						MINT	i_szMdD			// �\�����m���[�h�ݒ�E�B���h�E��
				)
{
	m_idP1 = i_idP1;
	m_idP2 = i_idP2;
	m_GidC.Alloc( i_szCID);					// �qID�G���A
	m_GaWD.Alloc( i_szMdD);					// �E�B���h�E���̕\���E���m���[�h(������4�E�B���h�E)
	m_DfltFig.SetpPmtl( NULL);
	m_CurFig.SetpPmtl( NULL);
}

//	�g���[�X
inline void MdmSetLYR::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "\t%3d: %s < MdmSetLYR > �eID1 = %d, �eID2 = %d\n"), i_i, s, m_idP1, m_idP2);
	MBTRCPRBF;
	m_GidC.Print( Mstr( "�qID�Q"), MDC_NONE_ID);
	m_GaWD.PrintB( Mstr( "�E�B���h�E�\�����n���[�h"), MDC_NONE_ID);
#endif
}

} // namespace MC