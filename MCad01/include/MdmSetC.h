#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		�l�b�`�c���f��
//
//
//==========================================================================================
namespace MC
{

//	�qID�Z�b�g
//
//					�eID - {�qID}n
//
#undef new

class MdmSetC
{
public:
	MDID		m_idP;							// �eID
	MDIDSET		m_GidC;							// �qID�Z�b�g

public:
	void Init()		{ m_GidC.Init();}
	void Free()		{ m_GidC.Free();}
	// �qID�Z�b�g����
	//	�ő�w�萔��(�q��)ID�������̈���m�ۂ���
	void* operator new( size_t i_sz);			// �����̍ő�qID��
	// �̈���m�ۂ���
	void Alloc( MINT i_szC)	
						{ m_GidC.Alloc( i_szC);}
	////	�̈���J������
	//void* operator delete();
	// �qID�Z�b�g�ɎqID��ǉ�����
	void operator += ( MDID i_idMd);
	// �qID�Z�b�g�̎qID���폜����
	void operator -= ( MDID i_idMd);
	// �qID�Z�b�g�������ݒ肷��
	void initialize(
						MDID	i_idP			// �eID
					);
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

// �qID�Z�b�g����
//	�ő�w�萔��(�q��)ID�������̈���m��
inline void* MdmSetC::operator new( size_t i_sz)
{
	MdmSetC* pSetC = (MdmSetC*)DEBUG_NEW char[sizeof( MdmSetC)];
	pSetC->m_idP = 0;
	pSetC->m_GidC.Alloc( (MINT) i_sz);
	return pSetC;
}

// �qID�Z�b�g�ɎqID��ǉ�����
inline void MdmSetC::operator += (MDID i_idMd)
{
	m_GidC += i_idMd;
}

// �qID�Z�b�g�̎qID���폜����
inline void MdmSetC::operator -= (MDID i_idMd)
{
	MINT iC;

	ASSERT(i_idMd >0 && i_idMd <= m_GidC.m_n);
	for ( iC=0; iC<m_GidC.m_n; iC++) {
		if ( m_GidC.m_st[iC] == i_idMd) {
			for ( iC++; iC<m_GidC.m_n; iC++) {
				m_GidC.m_st[iC-1] = m_GidC.m_st[iC];
			}
			m_GidC.m_n --;
			break;
		}
	}
}

// �qID�Z�b�g�������ݒ肷��
inline void MdmSetC::initialize(
						MDID	i_idP			// �eID
				)
{
	m_idP = i_idP;
}

//	�g���[�X
inline void MdmSetC::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "\t\t%s < MdmSetC > ID = %d�A�eID = %d\n"), s, i_i, m_idP);
	MBTRCPRBF;
	m_GidC.Print( Mstr( "�qID�Z�b�g"), MDC_NONE_ID);
#endif
}

//���̒ǉ����K�v;
//==========================================================================================
//	�q�֌W�Z�b�g
//
//					�eID - {�֌W�R�[�h�A�����R�[�h�A���[�v�R�[�h,�qID}n
//
//MDCPCSET;

} // namespace MC