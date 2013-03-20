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

//	�X�L�[�}�̎qID�Z�b�g
class MdmSetSCM
{
public:
	MDID		m_idP;							// �eID
	MCHAR*		m_sName;						// �X�L�[�}����
	MDIDSET		m_GidC;							// �q���C���[ID�Q

public:
	MdmSetSCM()		{ Init();}
	~MdmSetSCM()	{ Free();}
	void Init()
	{
		m_sName = NULL;
		m_GidC.Init();
	}
	void Free()
	{
		MBFREE( m_sName);
		m_GidC.Free();
	}
	// �X�L�[�}�̎qID�Z�b�g����
	//	�ő�w�萔��(�q��)ID�������̈���m�ۂ���
	void* operator new( size_t i_sz);			// �����̍ő�qID��
	////	�̈���J������
	//void* operator delete();
	// �X�L�[�}�̎qID��ǉ�����
	void operator += ( MDID i_idMd);
	// �X�L�[�}�̎qID���폜����
	void operator -= ( MDID i_idMd);
	// �X�L�[�}�ɏ����l��ݒ肷��
	void SetInit(
						MDID	i_idP,			// �eID
						MCHAR*	i_psName		// �O���[�v�̎qID�Z�b�g��
				);
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

// �X�L�[�}�̎qID�Z�b�g����
//	�ő�w�萔��(�q��)ID�������̈���m��
inline void* MdmSetSCM::operator new( size_t i_sz)
{
	MdmSetSCM* pSetSCM = (MdmSetSCM*)DEBUG_NEW char[sizeof( MdmSetSCM)];
	pSetSCM->m_idP = 0;
	pSetSCM->m_sName = NULL;
	pSetSCM->m_GidC.Alloc( (int)i_sz);
	return pSetSCM;
}

// �X�L�[�}�̎qID�Z�b�g�ɎqID��ǉ�����
inline void MdmSetSCM::operator += (MDID i_idMd)
{
	m_GidC += i_idMd;
}

// �X�L�[�}�̎qID�Z�b�g�̎qID���폜����
inline void MdmSetSCM::operator -= (MDID i_idMd)
{
	//MINT iC;
	//bool bFnd = false;
	//for ( iC=0; iC<m_GidC.m_n; iC++) {
	//	if ( m_GidC.m_st[iC] == i_idMd) {
	//		for ( iC++; iC<m_GidC.m_n; iC++) {
	//			m_GidC.m_st[iC-1] = m_GidC.m_st[iC];
	//		}
	//		m_GidC.m_n --;
	//		bFnd = true;
	//		break;
	//	}
	//}
	//ASSERT( bFnd);
	m_GidC -= i_idMd;
}

// �X�L�[�}�ɏ����l��ݒ肷��
inline void MdmSetSCM::SetInit(
						MDID	i_idP,			// �eID
						MCHAR*	i_psName		// �qID�Z�b�g��
				)
{
	m_idP = i_idP;
	m_sName = (MCHAR*)DEBUG_NEW char[(Mstrlen( i_psName) + 1) * sizeof( MCHAR)];
	Mstrcpy_s( m_sName, 256, i_psName);
}

//	�g���[�X
inline void MdmSetSCM::Print( MCHAR* s, MINT i_i)
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "\t%3d: %s	< MdmSetSCM > �eID = %d\n"),
									i_i, m_sName, m_idP);
	MBTRCPRBF;
	m_GidC.Print( Mstr( "�q���C���[ID�Q"), MDC_NONE_ID);
#endif
}

} // namespace MC