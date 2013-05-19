//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolygon.cpp
//		
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_POLYGON_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgDefine.h"
#include "MgPlane.h"
#include "MgPolygon.h"

namespace MC
{

//
//======================( �Q���� )==============================
//		���p�`�i�_�Q�j
//
//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgPolyg2D::MgPolyg2D( MINT sz1)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgPolyg2D::MgPolyg2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint2D& MgPolyg2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( "MgPolyg2D ()");
	return m_p[idx];
}

MgPoint2D& MgPolyg2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( "MgPolyg2D ()");
	return m_p[idx];
}

//	����
void MgPolyg2D::operator = ( const MgPolyg2D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	memcpy( m_p, Pg.m_p, sizeof( MgPoint2D) * nn);
}

void MgPolyg2D::operator = ( const MgPolyg3D& Pg)
{
	MINT	ic1;
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint2DC( Pg.m_P[ic1]);  
}

//	�\���_�̒ǉ�
void MgPolyg2D::operator += ( const MgPoint2D& p1)				// Pg += Pt1
{
	MgPoint2D	p1sv;
	if ( m_n >= m_isz) {
//		p1sv = p1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( (MINT)m_isz, 4));				// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
//		m_p[n++] = p1sv;
		m_p[m_n++] = p1;
	} else {
		m_p[m_n++] = p1;
	}
}

//	���p�`�i�_�Q�j�̒ǉ�
void MgPolyg2D::operator += ( const MgPolyg2D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	�R�����̑��p�`���Q�����̑��p�`���쐬
void MgPolyg2D::Set( const MgPolyg3D &Pg)
{
	MINT	ic1;
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint2DC( Pg.m_P[ic1]);  
}

//	��]�����𓾂�(MC_LEFT_ROT:����], MC_RIGHT_ROT:�E��])
MINT MgPolyg2D::Rotation() const
{
	MINT	ist = 0;
	MINT	ic;
	MgPoint2D	Pb;
	MgPoint2D	Pc;
//
	MINT	irot = 0;
	MREAL	s = 0.;
	Pb = m_p[m_n-1];
	for ( ic=0; ic<m_n; ic++) {
		Pc = m_p[ic];											// ���_����e���_�ւ̃x�N�g���̊O�ς̍��v������
		s += (Pb ^ Pc);											// ��]�������l���������p�`�̖ʐ�*2�����߂�
		Pb = Pc;
	}
	if (s > MGPTOL->D_2) {
		ist = MC_LEFT_ROT;
	} else if (s < -MGPTOL->D_2) {
		ist = MC_RIGHT_ROT;
	}							
	return ist;
}

//	���p�`�̉�]�����̔��]
void MgPolyg2D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	���p�`�̈�̊g��
void MgPolyg2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( p, MgPoint2D, szn);						//		�\���_�̗̈��remalloc�Ŋg��
	//	} else {												//	�\���_�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPoint2D		*pb = p;
	//		MBMALLOC( p, MgPoint2D, szn);  						//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint2D) * n);	//	�\���_�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint2D*	pb = m_p;
//E		MBMALLOC( m_p, MgPoint2D, szn);		 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, szn);
		if ( m_n)
			 memcpy( m_p, pb, m_n * sizeof( MgPoint2D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if ( m_fa && pb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	���p�`�̈�̖ʐ�
MREAL MgPolyg2D::Area()
{
	MINT	ic1;
	MgVect2D	v1, v2;
	MREAL	rArea = 0;

	for ( ic1=2; ic1<m_n; ic1++) {
		v1 = m_p[ic1-1] - m_p[0];
		v2 = m_p[ic1] - m_p[0];
		rArea += (v1 ^ v2);
	}
	return rArea / 2;
}

//	�ő�ŏ������߂�
MgMinMaxR2D MgPolyg2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgPolyg2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	�T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f)\n"),
						  ic, m_p[ic].x, m_p[ic].y);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �R���� )==============================
//		���p�`�i�_�Q�j
//
//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgPolyg3D::MgPolyg3D( MINT sz1)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_P, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_P, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgPolyg3D::MgPolyg3D( MINT i_isz1, MgPoint3D *i_pP2)
{
	m_tp = MGTP_POLYG3;
	m_isz = i_isz1;
	m_n = 0;
	m_fa = 0;
	m_P = i_pP2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint3D& MgPolyg3D::operator () (MINT idx) const
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgPolyg3D ()"));
	return m_P[idx];
}

MgPoint3D& MgPolyg3D::operator () (MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgPolyg3D ()"));
	return m_P[idx];
}

//	����
void MgPolyg3D::operator = ( const MgPolyg3D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	memcpy( m_P, Pg.m_P, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgPolyg3D::operator = (const MgPolyg2D &pg)				// �Q�������R���� (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_P);									//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_P[ic1] = MgPoint3DC( pg.m_p[ic1], 0.);  
}

//	�\���_�̒ǉ�
void MgPolyg3D::operator += ( const MgPoint3D& i_P1)			// Pg += Pt1
{
	MgPoint3D	P1sv;
	if (m_n >= m_isz) {
		P1sv = i_P1;											// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));						// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		m_P[m_n++] = P1sv;
	} else {
		m_P[m_n++] = i_P1;
	}
}

//	���p�`�i�_�Q�j�̒ǉ�
void MgPolyg3D::operator += ( const MgPolyg3D &i_Pg)			// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + i_Pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);					//
	for ( ic=0; ic<i_Pg.m_n; ic++)
		m_P[m_n++] = i_Pg.m_P[ic];
}

//	�Q�����̑��p�`���R�����̑��p�`���쐬
void MgPolyg3D::Set( const MgPolyg2D &i_pg, MREAL z)			// �Q�������R��������p (z = 0.)
{
	MINT	ic1;
	MINT	nn = i_pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
//		m_P[ic1].Set( i_pg.m_p[ic1], z);  
		m_P[ic1] = MgPoint3D( i_pg.m_p[ic1], z);  
}

void MgPolyg3D::Set( const MgPolyg2D &i_pg, const MgPlane3D& o_pPly)// �Q�������R��������p
{
	MINT	ic1;
	MINT	nn = i_pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_P);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_P, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_P, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_P[ic1].Set( i_pg.m_p[ic1], o_pPly);  
}

//	���p�`�̉�]�����̔��]
void MgPolyg3D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_P[ic1], m_P[ic2]);
		ic2--;
	}
}

//	���p�`�̈�̊g��
void MgPolyg3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( p, MgPoint3D, szn);						//		�\���_�̗̈��remalloc�Ŋg��
	//	} else {												//	�\���_�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPoint3D	*pb = p;
	//		MBMALLOC( p, MgPoint3D, szn);		 				//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint3D) * n);	//	�\���_�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint3D	*pb = m_P;
//E		MBMALLOC( m_P, MgPoint3D, szn);		 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_P, szn);
		if ( m_n)
			memcpy( m_P, pb, sizeof( MgPoint3D) * m_n);			//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pb)											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	�ő�ŏ������߂�
MgMinMaxR3D MgPolyg3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_P[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgPolyg3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg3D �T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f,%7.1f)\n"),
									ic, m_P[ic].x, m_P[ic].y, m_P[ic].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �Q���� )==============================
//		���p�`�Q
//
//	�\�����p�`�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPolyg2D::MgGPolyg2D( MINT sz1)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyg2D, sz1);
	MbAlloc<MgPolyg2D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyg2D) * sz1);
}

//	�\�����p�`�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPolyg2D::MgGPolyg2D( MINT sz1, MgPolyg2D *pg2)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyg2D) * sz1);
}

//	�f�X�g���N�^
MgGPolyg2D::~MgGPolyg2D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	�̈�J��
void MgGPolyg2D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;
}

//	�\�����p�`��()�Ŏw�肵�ǂݏ�������
const MgPolyg2D& MgGPolyg2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg2D ()"));
	return m_pg[idx];
}

MgPolyg2D& MgGPolyg2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg2D ()"));
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_pg[idx];
}

//	����
void MgGPolyg2D::operator = ( const MgGPolyg2D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyg2D::operator = (const MgGPolyg3D &GPg)				// �R�������Q����
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

//	�\�����p�`�̒ǉ�
void MgGPolyg2D::operator += ( const MgPolyg2D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	���p�`�Q�̒ǉ�
void MgGPolyg2D::operator += ( const MgGPolyg2D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}


//	�R�����̑��p�`���Q�����̑��p�`���쐬
void MgGPolyg2D::Set( const MgGPolyg3D &GPg)					// �R�������Q��������p
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

//	�󑽊p�`�̒ǉ�
void MgGPolyg2D::AddPolyg()
{
	MINT	nn = m_n++;
	if ( nn > m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		Resize( m_isz + sza);
		memset( &m_pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
	}
	m_n = nn;
}

//	�S�Ă̑��p�`�̉�]�����̔��]
void MgGPolyg2D::Rev()
{
	MINT	ic1, ic2, ic3;
	MgPolyg2D*	pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	���p�`�Q�̈�̊g��(�g�������͖��N���A)
void MgGPolyg2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	�\�����p�`�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( pg, MgPolyg2D, szn);						//		�\�����p�`�̗̈��realloc�Ŋg��
	//	} else {												//	�\�����p�`�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPolyg2D		*pgb = pg;
	//		MBMALLOC( pg, MgPolyg2D, szn);						//		�\�����p�`�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyg2D) * n);	//	�\�����p�`�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyg2D*	pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyg2D, szn);			 			//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPolyg2D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyg2D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pgb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGPolyg2D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyg2D	�T�C�Y: %d, �|���S����: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyg2D"));
#endif
}

//
//======================( �R���� )==============================
//		���p�`�Q
//
//	�\�����p�`�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPolyg3D::MgGPolyg3D( MINT sz1)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_Pg, MgPolyg3D, sz1);
	MbAlloc<MgPolyg3D>( m_Pg, sz1);
	memset( m_Pg, 0, sizeof( MgPolyg3D) * sz1);
}

//	�\�����p�`�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPolyg3D::MgGPolyg3D( MINT sz1, MgPolyg3D *pg2)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_Pg = pg2;
	memset( m_Pg, 0, sizeof( MgPolyg3D) * sz1);
}

//	�f�X�g���N�^
MgGPolyg3D::~MgGPolyg3D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_Pg[ic].Free();
	if ( m_fa)
		MBFREE( m_Pg);
}

//	�̈�J��
void MgGPolyg3D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_Pg[ic].Free();
	if ( m_fa)
		MBFREE( m_Pg);
	m_isz = m_n = m_fa = 0;

}

//	�\�����p�`��()�Ŏw�肵�ǂݏ�������
const MgPolyg3D& MgGPolyg3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr("MgGPolyg3D ()"));
	return m_Pg[idx];
};

MgPolyg3D& MgGPolyg3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPolyg3D ()"));
	for (; m_n<=idx; m_n++)
		m_Pg[m_n].SetInit();									//  �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_Pg[idx];
};

//	����
void MgGPolyg3D::operator = ( const MgGPolyg3D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic] = GPg.m_Pg[ic];
	m_n = nn;
}

void MgGPolyg3D::operator = (const MgGPolyg2D &Gpg)				// �Q�������R���� (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic] = Gpg.m_pg[ic];
	m_n = nn;
}

//	�\�����p�`�̒ǉ�
void MgGPolyg3D::operator += ( const MgPolyg3D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	m_Pg[m_n++] = Pg1;
}

//	���p�`�Q�̒ǉ�
void MgGPolyg3D::operator += ( const MgGPolyg3D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_Pg[m_n++] = GPg.m_Pg[ic];
}

//	�Q�����̑��p�`�Q���R�����̑��p�`�Q���쐬
void MgGPolyg3D::Set( const MgGPolyg2D &Gpg, MREAL z)			// �Q�������R��������p (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic].Set( Gpg.m_pg[ic], z);
	m_n = nn;
}

void MgGPolyg3D::Set( const MgGPolyg2D &Gpg, const MgPlane3D& Pln)	// �Q�������R��������p
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_Pg[ic].Set( Gpg.m_pg[ic], Pln);
	m_n = nn;
}

//	�󑽊p�`�̒ǉ�
void MgGPolyg3D::AddPolyg()
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_Pg[szb], 0, sizeof( MgPolyg3D) * sza);		//	.Init
	}
	m_n++;
}

//	�S�Ă̑��p�`�̉�]�����̔��]
void MgGPolyg3D::Rev()
{
	MINT		ic1, ic2, ic3;
	MgPolyg3D*	Pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		Pg1 = &m_Pg[ic1];
		ic3 = Pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( Pg1->m_P[ic2], Pg1->m_P[ic3]);
			ic3--;
		}
	}
}

//	���p�`�Q�̈�̊g��
void MgGPolyg3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	�\�����p�`�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( pg, MgPolyg3D, szn);						//		�\�����p�`�̗̈��remalloc�Ŋg��
	//	} else {												//	�\�����p�`�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPolyg3D*	pgb = pg;
	//		MBMALLOC( pg, MgPolyg3D, szn);						//		�\�����p�`�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyg3D) * n);	//	�\�����p�`�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyg3D*	pgb = m_Pg;
//E		MBMALLOC( m_Pg, MgPolyg3D, szn);		 				//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPolyg3D>( m_Pg, szn);
		if ( m_n)
			 memcpy( m_Pg, pgb, m_n * sizeof( MgPolyg3D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pgb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGPolyg3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyg3D	�T�C�Y: %d, �|���S����: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_Pg[ic].Print( Mstr( "MgGPolyg3D"));
#endif
}

//
//======================( �Q���� )==============================
//		�����Q
//
//	�\�������̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGLine2D::MgGLine2D( MINT sz1)
{
	m_tp = MGTP_GLINE; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_ln, MgLine2D, sz1);
	MbAlloc<MgLine2D>( m_ln, sz1);
}

//	�\�������̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGLine2D::MgGLine2D( MINT sz1, MgLine2D *ln2)
{
	m_tp = MGTP_GLINE; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_ln = ln2;
}

//	�\��������()�Ŏw�肵�ēǂݏ�������
const MgLine2D& MgGLine2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine2D ()"));
	return m_ln[idx];
}

MgLine2D& MgGLine2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine2D ()"));
	return m_ln[idx];
}

//	����
void MgGLine2D::operator = ( const MgGLine2D& GLn)
{
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_ln, GLn.m_ln, sizeof( MgLine2D) * nn);
	m_n = nn;
}

void MgGLine2D::operator = ( const MgGLine3D &GLn)				// �R�������Q����
{
	MINT	ic;
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine2DC( GLn.m_ln[ic]);
	m_n = nn;
}

//	�\�������̒ǉ�
void MgGLine2D::operator += ( const MgLine2D& Ln1)				// GLn += Ln1
{
	MgLine2D	Ln1sv;
	if (m_n >= m_isz) {
		Ln1sv = Ln1;											// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_ln[m_n++] = Ln1sv;
	} else {
		m_ln[m_n++] = Ln1;
	}
}

//	�\�������Q�̒ǉ�
void MgGLine2D::operator += ( const MgGLine2D &GLn)				// GLn += GLn1
{
	MINT	nn = m_n + GLn.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_ln[m_n], GLn.m_ln, sizeof( MgLine2D) * GLn.m_n);
	m_n = nn;
}

//	�R�����̐����Q���Q�����̐����Q���쐬
void MgGLine2D::Set( const MgGLine3D &GLn)						// �R�������Q��������p
{
	MINT	ic;
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine2D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine2D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine2DC( GLn.m_ln[ic]);
	m_n = nn;
}

//	�S�����̔��]
void MgGLine2D::Rev()
{
	MINT	ic1;
	for ( ic1=0; ic1<m_n; ic1++) {
		msSwap( m_ln[ic1].p[0], m_ln[ic1].p[1]);
	}
}

//	�����Q�̈�̊g��
void MgGLine2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && ln) {											//	�\�������̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( ln, MgLine2D, szn);						//		�\�������̗̈��remalloc�Ŋg��
	//	} else {												//	�\�������̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgLine2D		*lnb = ln;
	//		MBMALLOC( ln, MgLine2D, szn);						//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( ln, lnb, sizeof( MgLine2D) * n);	//	�\�������̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgLine2D	*lnb = m_ln;
//E		MBMALLOC( m_ln, MgLine2D, szn);			 				//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgLine2D>( m_ln, szn);
		if ( m_n)
			 memcpy( m_ln, lnb, m_n * sizeof( MgLine2D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && lnb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)lnb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGLine2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGLine2D	�T�C�Y: %d, ������: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			ln[%2d]: (%7.1f,%7.1f,%7.1f,%7.1f)\n"),
						  ic, m_ln[ic].p[0].x, m_ln[ic].p[0].y,
						      m_ln[ic].p[1].x, m_ln[ic].p[1].y);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �R���� )==============================
//		�����Q
//

//	�\�����p�`�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGLine3D::MgGLine3D( MINT sz1)
{
	m_tp = MGTP_GLINE3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_ln, MgLine3D, sz1);
	MbAlloc<MgLine3D>( m_ln, sz1);
}

//	�\�������̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGLine3D::MgGLine3D( MINT sz1, MgLine3D *ln2)
{
	m_tp = MGTP_GLINE3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_ln = ln2;
}

//	�\��������()�Ŏw�肵�ēǂݏ�������
const MgLine3D& MgGLine3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine3D ()"));
	return m_ln[idx];
};

MgLine3D& MgGLine3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGLine3D ()"));
	return m_ln[idx];
};

//	����
void MgGLine3D::operator = ( const MgGLine3D& GLn)
{
	MINT	nn = GLn.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_ln, GLn.m_ln, sizeof( MgLine3D) * nn);
	m_n = nn;
}

//	�Q�����̒����Q���R�����̒����Q���쐬
void MgGLine3D::operator = (const MgGLine2D &Gln)				// �Q�������R���� (z = 0.)
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic] = MgLine3DC( Gln.m_ln[ic]);
	m_n = nn;
}

//	�\�������̒ǉ�
void MgGLine3D::operator += ( const MgLine3D& Ln1)				// GLn += Ln1
{
	MgLine3D	Ln1sv;
	if (m_n >= m_isz) {
		Ln1sv = Ln1;											// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_ln[m_n++] = Ln1sv;
	} else {
		m_ln[m_n++] = Ln1;
	}
}

//	�\�������Q�̒ǉ�
void MgGLine3D::operator += ( const MgGLine3D &GLn)				// GLn += GLn1
{
	MINT	nn = m_n + GLn.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_ln[m_n], GLn.m_ln, sizeof( MgLine3D) * GLn.m_n);
	m_n = nn;
}

//	�Q�����̐����Q���R�����̐����Q���쐬
void MgGLine3D::Set( const MgGLine2D &Gln, const MgPlane3D& Pln)	// �Q�������R��������p
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic].Set( Gln.m_ln[ic], Pln);
	m_n = nn;
}

void MgGLine3D::Set( const MgGLine2D &Gln, MREAL z)				// �Q�������R��������p (z = 0.)
{
	MINT	ic;
	MINT	nn = Gln.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_ln);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_ln, MgLine3D, nn);							//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MgLine3D>( m_ln, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_ln[ic].Set( Gln.m_ln[ic], z);
	m_n = nn;
}

//	�S�����̔��]
void MgGLine3D::Rev()
{
	MINT	ic1;
	for ( ic1=0; ic1<m_n; ic1++) {
		msSwap( m_ln[ic1].p[0], m_ln[ic1].p[1]);
	}
}

//	�����Q�̈�̊g��
void MgGLine3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && ln) {											//	�\�������̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( ln, MgLine3D, szn);						//		�\�������̗̈��remalloc�Ŋg��
	//	} else {												//	�\�������̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgLine3D	*lnb = ln;
	//		MBMALLOC( ln, MgLine3D, szn);						//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( ln, lnb, sizeof( MgLine3D) * n);	//	�\�������̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgLine3D	*lnb = m_ln;
//E		MBMALLOC( m_ln, MgLine3D, szn);		 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgLine3D>( m_ln, szn);
		if ( m_n)
			 memcpy( m_ln, lnb, m_n * sizeof( MgLine3D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && lnb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)lnb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGLine3D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGLine3D	�T�C�Y: %d, ������: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			ln[%2d]: (%7.1f,%7.1f,%7.1f),(%7.1f,%7.1f,%7.1f)\n"),
						  ic, m_ln[ic].p[0].x, m_ln[ic].p[0].y, m_ln[ic].p[0].z,
						      m_ln[ic].p[1].x, m_ln[ic].p[1].y, m_ln[ic].p[1].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �P���� )==============================
//		�����Q
//

//	�\�������̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGInt::MgGInt( MINT sz1)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_i, MINT, sz1);
	MbAlloc<MINT>( m_i, sz1);
}

//	�\�������̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGInt::MgGInt( MINT sz1, MINT *i2)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_i = i2;
}

//	�\��������()�Ŏw�肵�ēǂݏ�������
const MINT& MgGInt::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGInt ()"));
	return m_i[idx];
};

MINT& MgGInt::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGInt ()"));
	return m_i[idx];
};

//	����
void MgGInt::operator = ( const MgGInt& GI)
{
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_i, MINT, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_i, GI.m_i, sizeof( MINT) * nn);
	m_n = nn;
}

void MgGInt::operator = (const MgGReal &GR)						// �����Q �� �����Q
{
	MINT	ic;
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_i, MINT, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_i[ic] = (MINT)GR.m_r[ic];
	m_n = nn;
}

//	�\�������̒ǉ�
void MgGInt::operator += ( MINT i1)								// GPt += i1
{
	MINT	i1sv;
	if (m_n >= m_isz) {
		i1sv = i1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_i[m_n++] = i1sv;
	} else {
		m_i[m_n++] = i1;
	}
}

//	�����Q�̒ǉ�
void MgGInt::operator += ( const MgGInt &GI)					// GPt += GI
{
	MINT	nn = m_n + GI.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_i[m_n], GI.m_i, sizeof( MINT) * GI.m_n);
	m_n = nn;
}

//	�����Q�̑��
void MgGInt::Set( const MgGReal &GR)							// �����Q�������Q ����p
{
	MINT	ic;
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_i);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_i, MINT, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MINT>( m_i, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_i[ic] = (MINT)GR.m_r[ic];
	m_n = nn;
}

//	�����Q�̈�̊g��
void MgGInt::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && i) {											//	�\�������̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( i, MINT, szn);							//		�\�������̗̈��remalloc�Ŋg��
	//	} else {												//	�\�������̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MINT*		pb = i;
	//		MBMALLOC( i, MINT, szn);							//		�\�������̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( i, pb, sizeof( MINT) * n);			//	�\�������̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MINT	*ib = m_i;
//E		MBMALLOC( m_i, MINT, szn);			 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MINT>( m_i, szn);
		if ( m_n)
			 memcpy( m_i, ib, m_n * sizeof( MINT));				//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && ib)											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)ib;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGInt::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGInt	�T�C�Y: %d, �����̐�: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: %d\n"),
						  ic, m_i[ic]);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �P���� )==============================
//		�����Q
//

//	�\�������̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGReal::MgGReal( MINT sz1)
{
	m_tp = MGTP_GREAL;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_r, MREAL, sz1);
	MbAlloc<MREAL>( m_r, sz1);
}

//	�\�������̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGReal::MgGReal( MINT sz1, MREAL* r2)
{
	m_tp = MGTP_GINT;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_r = r2;
}

//	�\��������()�Ŏw�肵�ēǂݏ�������
const MREAL& MgGReal::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGReal ()"));
	return m_r[idx];
};

MREAL& MgGReal::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGReal ()"));
	return m_r[idx];
};

//	����
void MgGReal::operator = ( const MgGReal& GR)
{
	MINT	nn = GR.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_r, MREAL, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_r, GR.m_r, sizeof( MREAL) * nn);
	m_n = nn;
}

void MgGReal::operator = (const MgGInt &GI)						// �����Q �� �����Q
{
	MINT	ic;
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_r, MREAL, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_r[ic] = (MREAL)GI.m_i[ic];
	m_n = nn;
}

//	�\�������̒ǉ�
void MgGReal::operator += ( MREAL r1)							// GPt += i1
{
	MREAL	r1sv;
	if (m_n >= m_isz) {
		r1sv = r1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_r[m_n++] = r1sv;
	} else {
		m_r[m_n++] = r1;
	}
}

//	�����Q�̒ǉ�
void MgGReal::operator += ( const MgGReal &GR)					// GPt += GI
{
	MINT	nn = m_n + GR.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_r[m_n], GR.m_r, sizeof( MREAL) * GR.m_n);
	m_n = nn;
}

//	�����Q�̑��
void MgGReal::Set( const MgGInt &GI)							// �����Q�������Q ����p
{
	MINT	ic;
	MINT	nn = GI.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_r);								//	�\�������̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_r, MREAL, nn);								//	�\�������̗̈��malloc�Ŋm��
		MbAlloc<MREAL>( m_r, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_r[ic] = (MREAL)GI.m_i[ic];
	m_n = nn;
}

//	�����Q�̈�̊g��
void MgGReal::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && r) {											//	�\�������̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( r, MREAL, szn);							//		�\�������̗̈��remalloc�Ŋg��
	//	} else {												//	�\�������̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MREAL		*pb = r;
	//		MBMALLOC( r, MREAL, szn);							//		�\�������̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( r, pb, sizeof( MREAL) * n);		//	�\�������̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MREAL	*rb = m_r;
//E		MBMALLOC( m_r, MREAL, szn);				 				//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MREAL>( m_r, szn);
		if ( m_n)
			 memcpy( m_r, rb, m_n * sizeof( MREAL));			//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && rb)											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)rb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGReal::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGReal	�T�C�Y: %d, �����̐�: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d] = %f\n"),
						  ic, m_r[ic]);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �Q���� )==============================
//		�_�Q
//

//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPoint2D::MgGPoint2D( MINT sz1)
{
	m_tp = MGTP_GPOINT2;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPoint2D::MgGPoint2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_GPOINT2;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint2D& MgGPoint2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint2D ()"));
	return m_p[idx];
};

MgPoint2D& MgGPoint2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint2D ()"));
	return m_p[idx];
};

//	����
void MgGPoint2D::operator = ( const MgGPoint2D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_p, Pg.m_p, sizeof( MgPoint2D) * nn);
	m_n = nn;
}

void MgGPoint2D::operator = (const MgGPoint3D &GPt)				// �R�������Q����
{
	MINT	ic;
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint2DC( GPt.m_p[ic]);
	m_n = nn;
}

//	�\���_�̒ǉ�
void MgGPoint2D::operator += ( const MgPoint2D& p1)				// GPt += Pt1
{
	MgPoint2D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	�_�Q�̒ǉ�
void MgGPoint2D::operator += ( const MgGPoint2D &GPt)			// GPt += GPt1
{
	MINT	nn = m_n + GPt.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_p[m_n], GPt.m_p, sizeof( MgPoint2D) * GPt.m_n);
	m_n = nn;
}

//	�R�����̓_�Q���Q�����̓_�Q���쐬
void MgGPoint2D::Set( const MgGPoint3D &GPt)					// �R�������Q��������p
{
	MINT	ic;
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint2D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint2DC( GPt.m_p[ic]);
	m_n = nn;
}

//	�_�Q�̈�̊g��
void MgGPoint2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( p, MgPoint2D, szn);						//		�\���_�̗̈��remalloc�Ŋg��
	//	} else {												//	�\���_�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPoint2D		*pb = p;
	//		MBMALLOC( p, MgPoint2D, szn);						//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint2D) * n);	//	�\���_�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint2D*	pb = m_p;
//E		MBMALLOC( m_p, MgPoint2D, szn);			 				//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPoint2D>( m_p, szn);
		if ( m_n)
			 memcpy( m_p, pb, m_n * sizeof( MgPoint2D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if ( m_fa && pb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�ő�ŏ������߂�
MgMinMaxR2D MgGPoint2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgGPoint2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	�T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f)\n"),
						  ic, m_p[ic].x, m_p[ic].y);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �R���� )==============================
//		�_�Q
//

//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPoint3D::MgGPoint3D( MINT sz1)
{
	m_tp = MGTP_GPOINT3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_p, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPoint3D::MgGPoint3D( MINT sz1, MgPoint3D *p2)
{
	m_tp = MGTP_GPOINT3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint3D& MgGPoint3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint3D ()"));
	return m_p[idx];
};

MgPoint3D& MgGPoint3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		RETURN_OVERFLOW_ERR_S( MBCstr( "MgGPoint3D ()"));
	return m_p[idx];
};

//	����
void MgGPoint3D::operator = ( const MgGPoint3D& GPt)
{
	MINT	nn = GPt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	memcpy( m_p, GPt.m_p, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgGPoint3D::operator = ( const MgGPoint2D& Gpt)
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint3DC( Gpt.m_p[ic]);
	m_n = nn;
}

//	�\���_�̒ǉ�
void MgGPoint3D::operator += ( const MgPoint3D& p1)				// GPt += Pt1
{
	MgPoint3D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));
																//	�Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	�_�Q�̒ǉ�
void MgGPoint3D::operator += ( const MgGPoint3D &GPt)			// GPt += GPt1
{
	MINT	nn = m_n + GPt.m_n;
	if ( nn > m_isz)
		Resize( nn);
	memcpy( &m_p[m_n], GPt.m_p, sizeof( MgPoint3D) * GPt.m_n);
	m_n = nn;
}

//	�Q�����̓_�Q���R�����̓_�Q���쐬
void MgGPoint3D::Set( const MgGPoint2D &Gpt, const MgPlane3D& Pln)	// �Q�������R��������p
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic].Set( Gpt.m_p[ic], Pln);
	m_n = nn;
}

void MgGPoint3D::Set( const MgGPoint2D &Gpt, MREAL z)			// �Q�������R��������p (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpt.m_n;
	if ( nn > m_isz) {
		if ( m_fa)
			MBFREE( m_p);										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
		m_fa = 1;
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_p[ic] = MgPoint3D( Gpt.m_p[ic], z);
	m_n = nn;
}

//	�_�Q�̈�̊g��
void MgGPoint3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && p) {											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( p, MgPoint3D, szn);						//		�\���_�̗̈��remalloc�Ŋg��
	//	} else {												//	�\���_�̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPoint3D	*pb = p;
	//		MBMALLOC( p, MgPoint3D, szn);						//		�\���_�̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( p, pb, sizeof( MgPoint3D) * n);	//	�\���_�̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPoint3D	*pb = m_p;
//E		MBMALLOC( m_p, MgPoint3D, szn);							//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, szn);
		if ( m_n)
			memcpy( m_p, pb, sizeof( MgPoint3D) * m_n);			//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if ( m_fa && pb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	�ő�ŏ������߂�
MgMinMaxR3D MgGPoint3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_p[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgGPoint3D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyg2D	�T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f)\n"),
						  ic, m_p[ic].x, m_p[ic].y);
		MBLOGPRBF;
	}
#endif
}

} // namespace MC
