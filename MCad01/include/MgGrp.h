#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgGrp.h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
//
//	MgGrp �́A�\���̂̌Q���`����e���v���[�g�ł���B
//
//	�I�[�o���C�֐����`����B
//
//
#include	"MlLog.h"

#define		MGTP_GROUP	100

namespace MC
{

//
//===================================================================
//		MgGrp 
//
//				�E�\����(�ϒ��N���X�f�[�^��entity)�̏W�����`����
//
//				�h���N���X
//
//					MgGrpS:	�Œ蒷�̍\���̂ŊJ�����ɂ́A�eentity��Free�͍s��Ȃ�
//					MgGrpF:	�ϒ��̍\���̂ŊJ�����ɂ́A�eentity��Free���s��
//

template <typename T> class MgGrp
{
												// G == 1: �q��MEMALOC����ŊJ�����Ɏq��FREE����
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GROUP
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�\���̐�
	MSHORT		m_n;							// �\���̐�
	T*			m_st;							// �\����
public:
	MgGrp()	
						{ m_tp = MGTP_GROUP;
						  m_isz = m_n = m_fa = 0;
						  m_st = NULL;}
	//MgGrp( MINT tp1)	
	//					{ tp = tp1;
	//					  sz = n = fa = 0;
	//					  st = NULL;}
	MgGrp( MINT sz1, MINT tp1 = MGTP_GROUP);

	MgGrp( MINT sz1, T *st2, MINT tp1 = MGTP_GROUP);

	void Init()													// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
						{ m_tp = MGTP_GROUP;
						  m_isz = m_n = m_fa = 0;
						  m_st = NULL;}
	T& operator [] (MINT idx)									// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_st[idx];}
	void operator -= (const MINT dn)							// �Ō��dn�̍\���̂��폜
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()											// �Ō�̂P�̍\���̂��폜
						{ if ( m_n>0) -- n;}
	void operator -- (int)										// �Ō�̂P�̍\���̂��폜
						{ if ( m_n>0) n --;}
	void ReSize( MINT szn);										// �ő�\���̐��̕ύX�Ɨ̈�m�ہA�G���[�\���p��Prog���̂����

	void Print( MCHAR* s);										// �g���[�X
};

//	�\����(�_����������)�Q�̈���m�ۂ���ꍇ�̃R���X�g���N�^
template <typename T> MgGrp<T>::MgGrp(
				MINT		sz1,								// �\���̌Q�̏����Ɋm�ۂ���\���̂̐�
				MINT		tp1 = MGTP_GROUP					// �\���̌Q�̃^�C�v�R�[�h
				)
{
	m_tp = MGTP_GROUP;
	m_fa = 1;
	
	m_isz = sz1;
	m_n = 0;
	MBMALLOC( m_st, T, sz1);
}

//	�\����(�_����������)�Q�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
template <typename T> MgGrp<T>::MgGrp(
				MINT		sz1,								// �\���̂̔z��̃T�C�Y
				T			*st2,								// �\���̂̔z��(��)
				MINT		tp1 = MGTP_GROUP					// �\���̌Q�̃^�C�v�R�[�h
				)
{
	m_tp = MGTP_GROUP;
	m_fa = 0;
	
	m_isz = sz1;
	m_n = 0;
	m_st = st2;
}


//	�\���̌Q�̈�̊g��
template <typename T> void MgGrp<T>::ReSize( MINT i_sz)
{
	//if (szn > sz) {
	//	if (fa && st) {											//	�\���\���̗̂̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( st, T, szn);								//		�\���\���̗̂̈��remalloc�Ŋg��
	//	} else {												//	�\���\���̗̂̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		T	*stb = st;
	//		MBMALLOC( st, T, szn);								//		�\���\���̗̂̈��malloc�Ŋm��
	//		if (!fa)
	//			memcpy( st, stb, sizeof( T) * n);				//	�\���\���̗̂̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if ( i_sz > m_isz) {
		T	*stb = m_st;
//E		MBMALLOC( m_st, T, i_sz);		 						//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<T>( m_st, i_sz);
		if ( m_isz)
			memcpy( m_st, stb, m_isz * sizeof( T));				//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if ( m_fa && stb)												//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)stb;									//
		else
			m_fa = 1;
		m_isz = i_sz;
	}
}

//	�g���[�X
template <typename T> void MgGrp<T>::Print(MCHAR* s)
{
	Msprintf_s( mlLog::m_Str, Mstr( "%s < MgGrp > �T�C�Y = %d�A���_�� = %d\n"), s, m_isz, m_n);
	MBTRCPRBF;
	for (int ic=0; ic<m_n; ic++) {
		m_st[ic].Print( s, ic);
	}
}

//
//===================================================================
//		MgGrpS
//
//		�\���̌Q 
//				�E�\����(�Œ蒷�N���X�f�[�^��entity)�̏W�����`����
//				�E�J�����ɑS�̂�free�����s���A�eentity����free�͍s��Ȃ�
//
template <typename T>
class MgGrpS : public MgGrp<T>
{
public:
	~MgGrpS();
	void Free();
	void operator += (const T &st);								// �\���\���̂̒ǉ�	�\���̌Q += �\����
	void operator = (const MgGrpS<T> &Gst);					// ����				�\���̌Q = �\���̌Q
	void operator += (const MgGrpS<T> &Gst);					// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q
	void operator ++ ( int);									// �Ō�̂P�̍\���̂�ǉ�(���g����̍\���̂�ǉ�)
	T& operator () ( MINT idx);									// �\���\���̂�()�Ŏw�肵�ēǂݏ�������
																// �ő吔�̎����w�肵���ꍇ�͗̈���g������
																// ����ɑ傫�Ȓl�̎w��̏ꍇ�̓I�[�o�t���[�G���[�Ƃ���
};

//	�f�X�g���N�^
template <typename T> MgGrpS<T>::~MgGrpS()
{
	if ( m_st) {
		if ( m_fa)
			MBFREE( m_st);
	}
}

template <typename T> void MgGrpS<T>::Free()
{
	if ( m_st) {
		if ( m_fa) {
			MBFREE( m_st);
			m_fa = 0;
			m_isz = 0;
		}
		m_n = 0;
	}
}

//	�\���\���̂̒ǉ�	�\���̌Q += �\����
template <typename T> void MgGrpS<T>::operator += (const T &st1)					// Gst += st1
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_st[m_n] = st1;
	m_n++;
}

//	����				�\���̌Q = �\���̌Q
template <typename T> void MgGrpS<T>::operator = (const MgGrpS<T>& Gst)
{
	MINT	nn = Gst.n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_st);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		MBMALLOC( m_st, T, nn);									//	�\���_�̗̈��malloc�Ŋm��
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_st, Gst.m_st, nn * sizeof( T));
	m_n = nn;
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
template <typename T> void MgGrpS<T>::operator += (const MgGrpS<T> &Gst)			// Gst += Gst1
{
	MINT	nn = m_n + Gst.m_n;
	if ( nn > m_isz)
		ReSize( nn);
	memcpy( &m_st[n], Gst.m_st, sizeof( T) * Gst.m_n);
	m_n = nn;
}

//	��̍\���\���̂�ǉ�	�\���̌Q ++
template <typename T> void MgGrpS<T>::operator ++ ( int)							// Gst ++
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_n++;
}

//	�\���\���̂�()�Ŏw�肵�ēǂݏ�������
//	��@Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> T& MgGrpS<T>::operator () (MINT idx)
{
	if ( idx == m_isz) {
		ReSize( sz + MGMAX( m_isz, 4));							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	} else if ( idx > m_isz) {
		msSysError( MBCstr( "MgGrpS()"), MC_ERR_OVERFLOW);
	}
	//for (; m_n<=idx; m_n++)					
	memset( &m_st[n], 0, (idx-m_n) * sizeof(m_st));				// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_st[idx];
};

//
//===================================================================
//		MgGrpF
//
//		�\���̌Q 
//				�E�\����(�ϒ��N���X�f�[�^��entity)�̏W�����`����
//				�E�J�����ɑS�̂�free�����łȂ��A�eentity����free���s��
//
template <typename T>
class MgGrpF : public MgGrp<T>
{
public:
	~MgGrpF();
	void Free();
	void operator += (const T &st);								// �\���\���̂̒ǉ�	�\���̌Q += �\����
	void operator = (const MgGrpF<T> &Gst);					// ����				�\���̌Q = �\���̌Q
	void operator += (const MgGrpF<T> &Gst);					// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q
	void operator ++ ( int);									// �Ō�̂P�̍\���̂�ǉ�(���g����̍\���̂�ǉ�)
	T& operator () ( MINT idx);									// �\���\���̂�()�Ŏw�肵�ēǂݏ�������
																// �ő吔�̎����w�肵���ꍇ�͗̈���g������
																// ����ɑ傫�Ȓl�̎w��̏ꍇ�̓I�[�o�t���[�G���[�Ƃ���
};

//	�f�X�g���N�^
template <typename T> MgGrpF<T>::~MgGrpF()
{
	MINT	ic;
	if ( m_st) {
		for(ic=0; ic<m_n; ic++) 
			m_st[ic].Free();									// �̈�J��
		if ( m_fa)
			MBFREE( m_st);
	}
}

template <typename T> void MgGrpF<T>::Free()
{
	MINT	ic;
	if ( m_st) {
		for(ic=0; ic<m_n; ic++) 
			m_st[ic].Free();									// �̈�J��
		if ( m_fa) {
			MBFREE( m_st);
			m_fa = 0;
			m_isz = 0;
		}
		m_n = 0;
	}
}

//	�\���\���̂̒ǉ�	�\���̌Q += �\����
template <typename T> void MgGrpF<T>::operator += (const T &st1)					// Gst += st1
{
	if (m_n >= m_isz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_st[m_n].Init();
	m_st[m_n] = st1;
	m_n++;
}

//	����				�\���̌Q = �\���̌Q
template <typename T> void MgGrpF<T>::operator = (const MgGrpF<T>& Gst)
{
	MINT	nn = Gst.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_st);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		MBMALLOC( m_st, T, nn);									//	�\���_�̗̈��malloc�Ŋm��
		m_fa = 1;
		m_isz = nn;
	}
//	memcpy( st, Gst.st, sizeof( T) * nn);
	for ( iC=0; iC<Gst.m_n; iC++) {
		m_st[iC].Init();
		m_st[iC] = Gst.m_st[iC];
	}
	m_n = nn;
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
template <typename T> void MgGrpF<T>::operator += (const MgGrpF<T> &Gst)		// Gst += Gst1
{
	MINT	nn = m_n + Gst.m_n;
	if ( nn > m_isz)
		ReSize( nn);
//	memcpy( &st[n], Gst.st, sizeof( T) * Gst.n);
	for ( iC=0; iC<Gst.m_n; iC++) {
		m_st[iC+n].Init();
		m_st[iC+n] = Gst.m_st[iC];
	}
	m_n = nn;
}

//	��̍\���\���̂�ǉ�	�\���̌Q ++
template <typename T> void MgGrpF<T>::operator ++ ( int)							// Gst ++
{
	if ( n >= sz)
		ReSize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_st[n].Init();
	m_n++;
}

//	�\���\���̂�()�Ŏw�肵�ēǂݏ�������
//	��@Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> T& MgGrpF<T>::operator () (MINT idx)
{
	if ( idx == m_isz) {
		ReSize( m_isz + MGMAX( m_isz, 4));							//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	} else if ( idx > sz) {
		msSysError( MBCstr( "MgGrpF()"), MC_ERR_OVERFLOW);
	}
	for (; m_n<=idx; m_n++)											// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
		 m_st[n].SetInit();
	return m_st[idx];
};

} // namespace MC
