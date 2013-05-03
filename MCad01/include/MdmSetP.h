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

//	�eID�Z�b�g
class MdmSetP
{
	MDID		m_idC;							// �qID
	MDIDSET		m_GidP;							// �eID�Q
public:
	// �eID�Z�b�g����
	//	�ő�w�萔��(�e��)ID�������̈���m�ۂ���
	void* operator new( size_t i_sz);			// �����̍ő�eID��
	// �eID��ǉ�����
	void operator += ( MDID i_idMd);
	// �eID���폜����
	void operator -= ( MDID i_idMd);
	// �eID�Z�b�g�������ݒ肷��
	void initialize(
						MDID	i_idC			// �qID
				);
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s);
};

// �eID�Z�b�g����
//	�ő�w�萔��(�e��)ID�������̈���m��
inline void* MdmSetP::operator new( size_t i_sz)
{
	MdmSetP* pSetP = (MdmSetP*)DEBUG_NEW char[sizeof( MdmSetP)];
	pSetP->m_idC = 0;
	pSetP->m_GidP.Alloc( (int)i_sz);
	return pSetP;
}

// �eID�Z�b�g�ɐeID��ǉ�����
inline void MdmSetP::operator += (MDID i_idMd)
{
	m_GidP += i_idMd;
}

// �eID�Z�b�g�̐eID���폜����
inline void MdmSetP::operator -= (MDID i_idMd)
{
	ASSERT(i_idMd >0 && i_idMd <= m_GidP.n);
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

// �eID�Z�b�g�������ݒ肷��
inline void MdmSetP::initialize(
						MDID	i_idC			// �qID
				)
{
	m_idC = i_idC;
}

//	�g���[�X
inline void MdmSetP::Print( MCHAR* s, MINT i_i)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s < MdmSetP > ID = %d, �qID = %d\n"), s, i_i, m_idC);
	MBLOGPRBF;
	m_GidP.Print( Mstr( "�eID�Q"));
#endif
}

} // namespace MC
