#pragma once
//===================================================================
//		MdAryH
//
//		�\���̌Q 
//				�E�\���̂̏W�����`����ׂ̃x�[�X�N���X
//
//				�h���N���X
//
//					MdAryH_S:	�Œ蒷�̍\���̂ŊJ�����ɂ́A�eentity��Free�͍s��Ȃ�
//					MdAryH_F:	�ϒ��̍\���̂ŊJ�����ɂ́A�eentity��Free���s��
//

#include	"MdmDefine.h"

namespace MC
{

template <typename T> class MdAryH
{
												// �J�����Ɏq��FREE����
public:
	MUSHORT		m_sz;							// �ő�\���̐�
	MUSHORT		m_n;							// �\���̐�
	T*			m_pst;							// �\����
public:
	MdAryH()	
						{ m_sz = m_n = 0; m_pst = NULL;}
	MdAryH( MUSHORT i_sz);

	void Alloc( MUSHORT i_sz);									// �w��ő�\���̐��̗̈���m�ہA�G���[�\���p��Prog���̂����
	
	void ReSize( MUSHORT i_sz);									// �ő�\���̐��̕ύX�Ɨ̈�m�ہA�G���[�\���p��Prog���̂����

	void Init()			{ m_sz = m_n = 0; m_pst = NULL;}		// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p

	T& operator [] (MUSHORT idx)								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pst[MIDtoHN( idx)];}

	// �f�o�b�O�p�g���[�X�o��
	void PrintC( MCHAR* i_s);
};

//	�R���X�g���N�^
template <typename T> inline MdAryH<T>::MdAryH(
				MUSHORT		i_sz								// �\���̌Q�̏����Ɋm�ۂ���\���̂̐�
				)
{
	m_sz = i_sz;
	m_n = 0;
//E	MBMALLOC( m_pst, T, i_sz);
	MbAlloc<T>( m_pst, i_sz);
}

//	�\���̌Q�̈�̊m��
template <typename T> inline void MdAryH<T>::Alloc( MUSHORT i_sz)
{
	int isz = i_sz * sizeof( T);

//E	MBMALLOC( m_pst, T, i_sz);									//	�\���\���̗̂̈��malloc�Ŋm��
	MbAlloc<T>( m_pst, i_sz);
	memset( m_pst, 0, sizeof( T) * ( i_sz));
	m_sz = i_sz;
}

//	�\���̌Q�̈�̊g��
template <typename T> inline void MdAryH<T>::ReSize( MUSHORT i_sz)
{
	if ( i_sz > m_sz) {
		T	*stb = m_pst;
//E		MBMALLOC( m_pst, T, i_sz);		 						//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<T>( m_pst, i_sz);
		if ( m_sz)
			memcpy( m_pst, stb, m_sz * sizeof( T));				//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if ( stb)												//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)stb;									//
		memset( &m_pst[m_sz], 0, sizeof( T) * ( i_sz - m_sz));
		m_sz = i_sz;
	}
}

//	�g���[�X
template <typename T> inline void MdAryH<T>::PrintC(MCHAR* i_s)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	< MdAryH > �T�C�Y: %d�C���_��: %d\n"),
									i_s, m_sz, m_n);
	MBLOGPRBF;
	for ( MUSHORT iC=0; iC<m_n; iC++) {
		m_pst[iC].Print( i_s);
	}
#endif
}

//===================================================================
//		MdAryH_S
//
//		�\���̌Q 
//				�E�\����(�Œ蒷�N���X�f�[�^��entity)�̏W�����`����
//				�E�J�����ɑS�̂�free�����s���A�eentity����free�͍s��Ȃ�
//
template <typename T>
class MdAryH_S : public MdAryH<T>
{
public:
	MdAryH_S() : MdAryH() {};
	MdAryH_S( MUSHORT i_sz) : MdAryH( i_sz) {};
	~MdAryH_S();
	void Free();
	void operator += ( const T &i_st);							// �\���\���̂̒ǉ�	�\���̌Q += �\����
	void operator -= ( const T &i_st);							// �\���̌Q�̒ǉ�	�\���̌Q -= �\����
	void operator = ( const MdAryH_S<T> &i_Gst);				// ����				�\���̌Q = �\���̌Q
	void operator += ( const MdAryH_S<T> &i_Gst);				// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q
	void operator ++ ( int);									// �Ō�̂P�̍\���̂�ǉ�(���g����̍\���̂�ǉ�)
	T& operator () ( MUSHORT i_idx);							// �\���\���̂�()�Ŏw�肵�ēǂݏ�������
																// �ő吔�̎����w�肵���ꍇ�͗̈���g������
																// ����ɑ傫�Ȓl�̎w��̏ꍇ�̓I�[�o�t���[�G���[�Ƃ���
	//// �f�o�b�O�p�g���[�X�o��
	//void Print( MCHAR* i_s);
};

////	�R���X�g���N�^
//template <typename T> inline MdAryH_S<T>::MdAryH_S( MUSHORT i_sz) : base( 100) {}

//	�f�X�g���N�^
template <typename T> inline MdAryH_S<T>::~MdAryH_S()
{
	MBFREE( m_pst);
}

template <typename T> inline void MdAryH_S<T>::Free()
{
	if ( m_pst) {
		MBFREE( m_pst);
		m_sz = 0;
		m_n = 0;
	}
}

//	�\���\���̂̒ǉ�	�\���̌Q += �\����
template <typename T> inline void MdAryH_S<T>::operator += (const T &i_st)					// Gst -= st1
{
	if ( m_n >= m_sz)
		ReSize( m_sz + MGMAX( m_sz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_pst[m_n] = i_st;
	m_n++;
}

//	�\���\���̂̍폜	�\���̌Q -= �\����
template <typename T> inline void MdAryH_S<T>::operator -= (const T &i_st)
{
	MINT iC;
	bool bFnd = false;
	for ( iC=0; iC<m_n; iC++) {
		if ( m_pst[iC] == i_st) {
			for ( iC++; iC<m_n; iC++) {
				m_pst[iC-1] = m_pst[iC];
			}
			m_n --;
			bFnd = true;
			break;
		}
	}
	ASSERT( bFnd);
}

//	����				�\���̌Q = �\���̌Q
template <typename T> inline void MdAryH_S<T>::operator = (const MdAryH_S<T>& i_Gst)
{
	MUSHORT	nn = i_Gst.m_n;
	if ( nn > m_sz) {
			MBFREE( m_pst);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_pst, T, nn);									//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<T>( m_pst, nn);
		m_sz = nn;
	}
	memcpy( m_pst, i_Gst.m_pst, sizeof( T) * nn);
	m_n = nn;
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
template <typename T> inline void MdAryH_S<T>::operator += (const MdAryH_S<T>& i_Gst)			// Gst += Gst1
{
	MUSHORT	nn = m_n + i_Gst.m_n;
	if ( nn > sz)
		ReSize( nn, Mstr( "MdAryH_S += Gst"));
	memcpy( &st[m_n], i_Gst.st, sizeof( T) * i_Gst.m_n);
	m_n = nn;
}

//	��̍\���\���̂�ǉ�	�\���̌Q ++
template <typename T> inline void MdAryH_S<T>::operator ++ ( int)							// Gst ++
{
	if (m_n >= m_sz)
		ReSize( m_sz + MGMAX( m_sz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_n++;
}

//	�\���\���̂�()�Ŏw�肵�ēǂݏ�������
//	��@Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> inline T& MdAryH_S<T>::operator () (MUSHORT i_idx)
{
	if ( i_idx == m_sz) {
		ReSize( m_sz + MGMAX( m_sz, 4));							//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	} else if ( idx > m_sz) {
		MbSysError( MBCstr( "MdAryH()"), MC_ERR_OVERFLOW);
	}
	for (; m_n<=i_idx; n++) m_pst[m_n].SetInit();						// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_pst[i_idx];
}

//===================================================================
//===================================================================
//		MdAryH_S_C
//
//		�Œ蒷�̃N���X(�\����)�^�f�[�^�Z�b�g 
//
template <typename T>
class MdAryH_S_C : public MdAryH_S<T>
{
public:
	MdAryH_S_C() : MdAryH_S() {};
	MdAryH_S_C( MUSHORT i_sz) : MdAryH_S( i_sz) {};

	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

//	�g���[�X
template <typename T> inline void MdAryH_S_C<T>::Print(MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	if ( m_n) {
		if ( i_i == MDC_NONE_ID) {
			Msprintf_s( mlLog::m_Str, Mstr( "\t\t%s < MdAryH_S_C > �T�C�Y = %d�A�f�[�^�� = %d\n"),
											i_s, m_sz, m_n);
		} else {
			Msprintf_s( mlLog::m_Str, Mstr( "\t\t%s < MdAryH_S_C > ID = %d�C�T�C�Y = %d�A�f�[�^�� = %d\n"),
											i_s, i_i, m_sz, m_n);
		}
		MBLOGPRBF;
		for (MUSHORT iC=0; iC<m_n; iC++) {
			m_pst[iC].Print( i_s, iC);
		}
	}
#endif
}

//===================================================================
//===================================================================
//		MdAryH_S_I
//
//		�����^�f�[�^�Z�b�g 
//
template <typename T>
class MdAryH_S_I : public MdAryH_S<T>
{
public:
	MdAryH_S_I() : MdAryH_S() {};
	MdAryH_S_I( MUSHORT i_sz) : MdAryH_S( i_sz) {};

	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};

//	�g���[�X
template <typename T> inline void MdAryH_S_I<T>::Print(MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	if ( m_n) {
		if ( i_i == MDC_NONE_ID) {
			Msprintf_s( mlLog::m_Str, Mstr( "\t\t\t%s < MdAryH_S_I > �����^�f�[�^�Z�b�g�C�T�C�Y =%d�C�f�[�^�� = %d\n"),
											i_s, m_sz, m_n);
		} else {
			Msprintf_s( mlLog::m_Str, Mstr( "\t\t\t%s < MdAryH_S_I > ID = %d�C�����^�f�[�^�Z�b�g�C�T�C�Y =%d�C�f�[�^�� = %d\n"),
											i_s, i_i, m_sz, m_n);
		}
		MBLOGPRBF;
		if ( m_n)
			MBLOGPRINTIN( Mstr( "\t\t\t�f�[�^"), m_pst, m_n);
	}
#endif
}

//===================================================================
//===================================================================
//		MdAryH_S_B
//
//		�����^�f�[�^�Z�b�g 
//
template <typename T>
class MdAryH_S_B : public MdAryH_S<T>
{
public:
	MdAryH_S_B() : MdAryH_S() {};
	MdAryH_S_B( MUSHORT i_sz) : MdAryH_S( i_sz) {};

	// �f�o�b�O�p�g���[�X�o��
	void PrintB( MCHAR* i_s, MINT i_i);
};

//	�g���[�X
template <typename T> inline void MdAryH_S_B<T>::PrintB(MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	if ( i_i == MDC_NONE_ID) {
		Msprintf_s( mlLog::m_Str, Mstr( "\t\t\t%s < MdAryH_S_B > �����^�f�[�^�Z�b�g�C�T�C�Y: %d�C�f�[�^��: %d\n"),
										i_s, m_sz, m_n);
	} else {
		Msprintf_s( mlLog::m_Str, Mstr( "\t\t\t%s < MdAryH_S_B > ID = %d�C�����^�f�[�^�Z�b�g�C�T�C�Y: %d�C�f�[�^��: %d\n"),
										i_s, i_i, m_sz, m_n);
	}
	MBLOGPRBF;
	if ( m_n)
		MBLOGPRINTBN( Mstr( "			�f�[�^"), m_pst, m_n);
#endif
}

//===================================================================
//===================================================================
//		MdAryH_F
//
//		�\���̌Q 
//				�E�\����(�ϒ��N���X�f�[�^��entity)�̏W�����`����
//				�E�J�����ɑS�̂�free�����łȂ��A�eentity����free���s��
//
template <typename T>
class MdAryH_F : public MdAryH<T>
{
public:
	MdAryH_F() : MdAryH() {};
	MdAryH_F( MUSHORT i_sz) : MdAryH( i_sz) {};

	~MdAryH_F();
	void Free();
	void operator += (const T& i_st);							// �\���\���̂̒ǉ�	�\���̌Q += �\����
	void operator = (const MdAryH_F<T>& i_Gst);					// ����				�\���̌Q = �\���̌Q
	void operator += (const MdAryH_F<T>& i_Gst);				// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q
	void operator ++ ( int);									// �Ō�̂P�̍\���̂�ǉ�(���g����̍\���̂�ǉ�)
	T& operator () ( MUSHORT i_idx);							// �\���\���̂�()�Ŏw�肵�ēǂݏ�������
																// �ő吔�̎����w�肵���ꍇ�͗̈���g������
																// ����ɑ傫�Ȓl�̎w��̏ꍇ�̓I�[�o�t���[�G���[�Ƃ���
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* i_s, MINT i_i);
};

//	�f�X�g���N�^
template <typename T> inline MdAryH_F<T>::~MdAryH_F()
{
	MUSHORT	ic;
	if ( m_pst) {
		for( ic=0; ic<m_n; ic++)									// MdAryH_S�@�ɁA�q�̍\���̗̂̈�J����ǉ� 
			if ( MDSPACEID( &m_pst[ic]) != MDID_DELETE)			//
				delete [] &m_pst[ic];							//	�̈�J��
		MBFREE( m_pst);
	}
}

//	�̈�J��
template <typename T> inline void MdAryH_F<T>::Free()
{
	MUSHORT	ic;
	if ( m_pst) {
		for( ic=0; ic<m_n; ic++) {
			if ( MDSPACEID( &m_pst[ic]) != MDID_DELETE)
				m_pst[ic].Free();								// �̈�J��
		}
		MBFREE( m_pst);
		m_sz = 0;
		m_n = 0;
	}
}

//	�\���\���̂̒ǉ�	�\���̌Q += �\����
template <typename T> inline void MdAryH_F<T>::operator += (const T& i_st)					// Gst += i_st
{
	if (m_n >= m_sz)
		ReSize( m_sz + MGMAX( m_sz, 4), Mstr( "MdAryH_F += i_st"));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_pst[n].Init();
	m_pst[n] = i_st;
	m_n++;
}

//	����				�\���̌Q = �\���̌Q
template <typename T> inline void MdAryH_F<T>::operator = (const MdAryH_F<T>& i_Gst)
{
	MUSHORT	iC;
	MUSHORT	nn = i_Gst.m_n;
	if ( nn > m_sz) {
			MBFREE( m_pst);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_pst, T, nn);									//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<T>( m_pst, nn);
		m_sz = nn;
	}
//	memcpy( st, i_Gst.st, sizeof( T) * nn);
	for ( iC=0; iC<i_Gst.m_n; iC++) {
		m_pst[m_n].Init();
		m_pst[iC] = i_Gst.m_pst[iC];
	}
	m_n = nn;
}

//	�\���̌Q�̒ǉ�		�\���̌Q += �\���̌Q
template <typename T> inline void MdAryH_F<T>::operator += (const MdAryH_F<T>& i_Gst)			// Gst += i_Gst
{
	MUSHORT	nn = n + Gst.n;
	if ( nn > sz)
		ReSize( nn, Mstr( "MdAryH_F += Gst"));

	for ( iC=0; iC<Gst.n; iC++) {
		st[iC+n].Init();
		st[iC+n] = Gst.m_pst[iC];
	}
	n = nn;
}

//	��̍\���\���̂�ǉ�	�\���̌Q ++
template <typename T> inline void MdAryH_F<T>::operator ++ ( int)							// Gst ++
{
	if (m_n >= m_sz)
		ReSize( m_sz + MGMAX( m_sz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	m_pst[m_n].Init();
	m_n++;
}

//	�\���\���̂�()�Ŏw�肵�ēǂݏ�������
//	��@Gst1(n).p, Gst1(n).i1, Gst1(n).i2
template <typename T> inline T& MdAryH_F<T>::operator () (MUSHORT i_idx)
{
	if ( idx == m_sz) {
		ReSize( m_sz + MGMAX( m_sz, 4));	//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	} else if ( i_idx > m_sz) {
		MbSysError( MBCstr( "MdAryH_F()"), MC_ERR_OVERFLOW);
	}
	for (; m_n<=i_idx; n++)										// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
		m_pst[m_n].SetInit();
	return m_pst[i_idx];
}

//	�g���[�X
template <typename T> inline void MdAryH_F<T>::Print(MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	MBLOGPRBF;
	for (MUSHORT ic=0; ic<m_n; ic++) {
		m_pst[ic].Print( i_s, i_i, ic);
	}
#endif
}

} // namespace MC
