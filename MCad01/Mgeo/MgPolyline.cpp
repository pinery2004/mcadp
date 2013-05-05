//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolyline.cpp
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_POLYLINE_DO

#include "MgDefine.h"
#include "MgTol.h"
#include "MgDefine.h"
#include "MgPlane.h"
#include "MgPolyline.h"

namespace MC
{

//
//======================( �Q���� )==============================
//		�܂���i�_�Q�j
//
//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgPolyl2D::MgPolyl2D( MINT sz1)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint2D, sz1);
	MbAlloc<MgPoint2D>( m_p, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgPolyl2D::MgPolyl2D( MINT sz1, MgPoint2D *p2)
{
	m_tp = MGTP_POLYG;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint2D& MgPolyl2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

MgPoint2D& MgPolyl2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

//	����
void MgPolyl2D::operator = ( const MgPolyl2D& Pg)
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

void MgPolyl2D::operator = ( const MgPolyl3D& Pg)
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
		m_p[ic1] = MgPoint2DC( Pg.m_p[ic1]);  
}

//	�\���_�̒ǉ�
void MgPolyl2D::operator += ( const MgPoint2D& p1)				// Pg += Pt1
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

//	�܂���i�_�Q�j�̒ǉ�
void MgPolyl2D::operator += ( const MgPolyl2D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	�R�����̐܂�����Q�����̐܂�����쐬
void MgPolyl2D::Set( const MgPolyl3D &Pg)
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
		m_p[ic1] = MgPoint2DC( Pg.m_p[ic1]);  
}

//	��]�����𓾂�(MC_LEFT_ROT:����], MC_RIGHT_ROT:�E��])
MINT MgPolyl2D::Rotation() const
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
		s += (Pb ^ Pc);											// ��]�������l�������܂���̖ʐ�*2�����߂�
		Pb = Pc;
	}
	if (s > MGPTOL->D_2) {
		ist = MC_LEFT_ROT;
	} else if (s < -MGPTOL->D_2) {
		ist = MC_RIGHT_ROT;
	}							
	return ist;
}

//	�܂���̉�]�����̔��]
void MgPolyl2D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	�܂���̈�̊g��
void MgPolyl2D::Resize( MINT szn)
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

//	�܂���̈�̖ʐ�
MREAL MgPolyl2D::Area()
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
MgMinMaxR2D MgPolyl2D::MinMax()
{
	MINT	ic1;
	MgMinMaxR2D	mm = MgMinMaxR2D( MREALMAX, MREALMAX, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins2( m_p[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgPolyl2D::Print( MCHAR* s) const
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr("%s	MgPolyl2D	�T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
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
//		�܂���i�_�Q�j
//
//	�\���_�̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgPolyl3D::MgPolyl3D( MINT sz1)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_p, MgPoint3D, sz1);
	MbAlloc<MgPoint3D>( m_p, sz1);
}

//	�\���_�̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgPolyl3D::MgPolyl3D( MINT sz1, MgPoint3D *p2)
{
	m_tp = MGTP_POLYG3;
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_p = p2;
}

//	�\���_��()�Ŏw�肵�ēǂݏ�������
const MgPoint3D& MgPolyl3D::operator () (MINT idx) const
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

MgPoint3D& MgPolyl3D::operator () (MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_p[idx];
}

//	����
void MgPolyl3D::operator = ( const MgPolyl3D& Pg)
{
	MINT	nn = Pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	memcpy( m_p, Pg.m_p, sizeof( MgPoint3D) * nn);
	m_n = nn;
}

void MgPolyl3D::operator = (const MgPolyl2D &pg)				// �Q�������R���� (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if (m_fa) MBFREE( m_p);									//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1] = MgPoint3DC( pg.m_p[ic1], 0.);  
}

//	�\���_�̒ǉ�
void MgPolyl3D::operator += ( const MgPoint3D& p1)				// Pg += Pt1
{
	MgPoint3D	p1sv;
	if (m_n >= m_isz) {
		p1sv = p1;												// �\�[�X�����T�C�Y���錳�̗̈�ɂ���f�[�^�̏ꍇ���l��
		Resize( m_isz + MGMAX( m_isz, 4));						// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		m_p[m_n++] = p1sv;
	} else {
		m_p[m_n++] = p1;
	}
}

//	�܂���i�_�Q�j�̒ǉ�
void MgPolyl3D::operator += ( const MgPolyl3D &pg)				// Pg += Pt1
{
	MINT	ic;
	MINT	nn = m_n + pg.m_n;
	if ( nn >= m_isz)
		Resize( nn);					//
	for ( ic=0; ic<pg.m_n; ic++)
		m_p[m_n++] = pg.m_p[ic];
}

//	�Q�����̐܂�����R�����̐܂�����쐬
void MgPolyl3D::Set( const MgPolyl2D &pg, MREAL z)				// �Q�������R��������p (z = 0.)
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
//		m_p[ic1].Set( pg.m_p[ic1], z);  
		m_p[ic1] = MgPoint3D( pg.m_p[ic1], z);  
}

void MgPolyl3D::Set( const MgPolyl2D &pg, const MgPlane3D& Ply)	// �Q�������R��������p
{
	MINT	ic1;
	MINT	nn = pg.m_n;
	if ( nn > m_isz) {
		if ( m_fa) MBFREE( m_p);								//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͈�Ufree
		m_isz = nn;
		m_fa = 1;
//E		MBMALLOC( m_p, MgPoint3D, nn);							//	�\���_�̗̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, nn);
	}
	m_n = nn;
	for ( ic1 = 0; ic1<nn; ic1++)
		m_p[ic1].Set( pg.m_p[ic1], Ply);  
}

//	�܂���̉�]�����̔��]
void MgPolyl3D::Rev()
{
	MINT	ic1, ic2;
	ic2 = m_n - 1;
	for ( ic1=0; ic1<ic2; ic1++) {
		msSwap( m_p[ic1], m_p[ic2]);
		ic2--;
	}
}

//	�܂���̈�̊g��
void MgPolyl3D::Resize( MINT szn)
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
		MgPoint3D	*pb = m_p;
//E		MBMALLOC( m_p, MgPoint3D, szn);		 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPoint3D>( m_p, szn);
		if ( m_n)
			memcpy( m_p, pb, sizeof( MgPoint3D) * m_n);			//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pb)											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pb;									//
		m_fa = 1;
		m_isz = szn;
	}
}

//	�ő�ŏ������߂�
MgMinMaxR3D MgPolyl3D::MinMax()
{
	MINT	ic1;
	MgMinMaxR3D	mm = MgMinMaxR3D( MREALMAX, MREALMAX, MREALMAX, MREALMIN, MREALMIN, MREALMIN);

	for ( ic1=0; ic1<m_n; ic1++) {
		mm.Ins3( m_p[ic1]);
	}
	return mm;
}

//	�g���[�X
void MgPolyl3D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgPolyl3D �T�C�Y: %d, ���_��: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++) {
		Msprintf_s( mlLog::m_Str, Mstr( "			P[%2d]: (%7.1f,%7.1f,%7.1f)\n"),
									ic, m_p[ic].x, m_p[ic].y, m_p[ic].z);
		MBLOGPRBF;
	}
#endif
}

//
//======================( �Q���� )==============================
//		�܂���Q
//
//	�\���܂���̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPolyl2D::MgGPolyl2D( MINT sz1)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyl2D, sz1);
	MbAlloc<MgPolyl2D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyl2D) * sz1);
}

//	�\���܂���̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPolyl2D::MgGPolyl2D( MINT sz1, MgPolyl2D *pg2)
{
	m_tp = MGTP_GPOLYG; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyl2D) * sz1);
}

//	�f�X�g���N�^
MgGPolyl2D::~MgGPolyl2D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	�̈�J��
void MgGPolyl2D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;
}

//	�\���܂����()�Ŏw�肵�ǂݏ�������
const MgPolyl2D& MgGPolyl2D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgGPolyl2D ()"), MC_ERR_OVERFLOW);
	return m_pg[idx];
}

MgPolyl2D& MgGPolyl2D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgGPolyl2D ()"), MC_ERR_OVERFLOW);
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									// �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_pg[idx];
}

//	����
void MgGPolyl2D::operator = ( const MgGPolyl2D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyl2D::operator = (const MgGPolyl3D &GPg)				// �R�������Q����
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

//	�\���܂���̒ǉ�
void MgGPolyl2D::operator += ( const MgPolyl2D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	�܂���Q�̒ǉ�
void MgGPolyl2D::operator += ( const MgGPolyl2D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}


//	�R�����̐܂�����Q�����̐܂�����쐬
void MgGPolyl2D::Set( const MgGPolyl3D &GPg)					// �R�������Q��������p
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

//	��܂���̒ǉ�
void MgGPolyl2D::AddPolyg()
{
	MINT	nn = m_n++;
	if ( nn > m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		Resize( m_isz + sza);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
	}
	m_n = nn;
}

//	�S�Ă̐܂���̉�]�����̔��]
void MgGPolyl2D::Rev()
{
	MINT	ic1, ic2, ic3;
	MgPolyl2D	*pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	�܂���Q�̈�̊g��(�g�������͖��N���A)
void MgGPolyl2D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	�\���܂���̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( pg, MgPolyl2D, szn);						//		�\���܂���̗̈��realloc�Ŋg��
	//	} else {												//	�\���܂���̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPolyl2D		*pgb = pg;
	//		MBMALLOC( pg, MgPolyl2D, szn);						//		�\���܂���̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyl2D) * n);	//	�\���܂���̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyl2D	*pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyl2D, szn);			 			//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPolyl2D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyl2D));		//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pgb)										//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pgb;									//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGPolyl2D::Print( MCHAR* s) const							// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyl2D	�T�C�Y: %d, �|���S����: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyl2D"));
#endif
}

//
//======================( �R���� )==============================
//		�܂���Q
//
//	�\���܂���̗̈��malloc�Ŋm�ۂ���ꍇ�̃R���X�g���N�^
MgGPolyl3D::MgGPolyl3D( MINT sz1)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 1;
//E	MBMALLOC( m_pg, MgPolyl3D, sz1);
	MbAlloc<MgPolyl3D>( m_pg, sz1);
	memset( m_pg, 0, sizeof( MgPolyl3D) * sz1);
}

//	�\���܂���̗̈��z��ŗ^����ꍇ�̃R���X�g���N�^
MgGPolyl3D::MgGPolyl3D( MINT sz1, MgPolyl3D *pg2)
{
	m_tp = MGTP_GPOLYG3; 
	m_isz = sz1;
	m_n = 0;
	m_fa = 0;
	m_pg = pg2;
	memset( m_pg, 0, sizeof( MgPolyl3D) * sz1);
}

//	�f�X�g���N�^
MgGPolyl3D::~MgGPolyl3D()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
}

//	�̈�J��
void MgGPolyl3D::Free()
{
	MINT	ic;
	for ( ic=0; ic<m_n; ic++)
		m_pg[ic].Free();
	if ( m_fa)
		MBFREE( m_pg);
	m_isz = m_n = m_fa = 0;

}

//	�\���܂����()�Ŏw�肵�ǂݏ�������
const MgPolyl3D& MgGPolyl3D::operator () ( MINT idx) const
{
	if ( idx >= m_n)
		ms::SysError( MBCstr( "MgGPolyl3D ()"), MC_ERR_OVERFLOW);
	return m_pg[idx];
};

MgPolyl3D& MgGPolyl3D::operator () ( MINT idx)
{
	if ( idx >= m_isz)
		ms::SysError( MBCstr( "MgGPolyl3D ()"), MC_ERR_OVERFLOW);
	for (; m_n<=idx; m_n++)
		m_pg[m_n].SetInit();									//  �ŏI�f�[�^����̃f�[�^�̓N���A���An = idx+1�@�ɂ���
	return m_pg[idx];
};

//	����
void MgGPolyl3D::operator = ( const MgGPolyl3D &GPg)
{
	MINT	ic;
	MINT	nn = GPg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = GPg.m_pg[ic];
	m_n = nn;
}

void MgGPolyl3D::operator = (const MgGPolyl2D &Gpg)				// �Q�������R���� (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic] = Gpg.m_pg[ic];
	m_n = nn;
}

//	�\���܂���̒ǉ�
void MgGPolyl3D::operator += ( const MgPolyl3D &Pg1)			// GPg += Pg1
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	m_pg[m_n++] = Pg1;
}

//	�܂���Q�̒ǉ�
void MgGPolyl3D::operator += ( const MgGPolyl3D &GPg)			// GPg += GPg1
{
	MINT	ic;
	MINT	nn = m_n + GPg.m_n;
//
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	for ( ic=0; ic<GPg.m_n; ic++)
		m_pg[m_n++] = GPg.m_pg[ic];
}

//	�Q�����̐܂���Q���R�����̐܂���Q���쐬
void MgGPolyl3D::Set( const MgGPolyl2D &Gpg, MREAL z)			// �Q�������R��������p (z = 0.)
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic].Set( Gpg.m_pg[ic], z);
	m_n = nn;
}

void MgGPolyl3D::Set( const MgGPolyl2D &Gpg, const MgPlane3D& Pln)	// �Q�������R��������p
{
	MINT	ic;
	MINT	nn = Gpg.m_n;
	if ( nn > m_isz) {
		MINT	szb = m_isz;
		MINT	sza = nn - m_isz;
		Resize( nn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl2D) * sza);		//	.Init
		m_isz = nn;
	}
	for ( ic=0; ic<nn; ic++)
		m_pg[ic].Set( Gpg.m_pg[ic], Pln);
	m_n = nn;
}

//	��܂���̒ǉ�
void MgGPolyl3D::AddPolyg()
{
	if (m_n >= m_isz) {
		MINT	sza = MGMAX( m_isz, 4);							// �Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S)
		MINT	szb = m_isz;
		MINT	szn = m_isz + sza;
		Resize( szn);
		memset( &m_pg[szb], 0, sizeof( MgPolyl3D) * sza);		//	.Init
	}
	m_n++;
}

//	�S�Ă̐܂���̉�]�����̔��]
void MgGPolyl3D::Rev()
{
	MINT		ic1, ic2, ic3;
	MgPolyl3D	*pg1;
	for ( ic1=0; ic1<m_n; ic1++) {
		pg1 = &m_pg[ic1];
		ic3 = pg1->m_n - 1;
		for ( ic2=0; ic2<ic3; ic2++) {
			msSwap( pg1->m_p[ic2], pg1->m_p[ic3]);
			ic3--;
		}
	}
}

//	�܂���Q�̈�̊g��
void MgGPolyl3D::Resize( MINT szn)
{
	//if (szn > sz) {
	//	if (fa && pg) {											//	�\���܂���̗̈��malloc�Ŋm�ۂ��Ă���ꍇ
	//		MGREALLOC( pg, MgPolyl3D, szn);						//		�\���܂���̗̈��remalloc�Ŋg��
	//	} else {												//	�\���܂���̗̈�𖢊m�ۂ܂��͔z��̏ꍇ
	//		MgPolyl3D	*pgb = pg;
	//		MBMALLOC( pg, MgPolyl3D, szn);						//		�\���܂���̗̈��malloc�Ŋm��
	//		if (!fa) memcpy( pg, pgb, sizeof( MgPolyl3D) * n);	//	�\���܂���̗̈悪�z��ł������ꍇ��malloc�̈�փR�s�[����
	//		fa = 1;                                             
	//	}
	//	sz = szn;
	//}

	if (szn > m_isz) {
		MgPolyl3D	*pgb = m_pg;
//E		MBMALLOC( m_pg, MgPolyl3D, szn);		 					//	�\���_�̐V�̈��malloc�Ŋm��
		MbAlloc<MgPolyl3D>( m_pg, szn);
		if ( m_n)
			 memcpy( m_pg, pgb, m_n * sizeof( MgPolyl3D));			//	�\���_�̗̈�Ƀf�[�^���������ꍇ�͐V�̈�փR�s�[����
		if (m_fa && pgb)											//	�\���_�̗̈��malloc�Ŋm�ۂ��Ă����ꍇ�͂��̗̈���J������
			delete (char*)pgb;										//	
		m_fa = 1;
		m_isz = szn;
	}
}

//	�g���[�X
void MgGPolyl3D::Print( MCHAR* s) const								// Print
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgGPolyl3D	�T�C�Y: %d, �|���S����: %d\n"), s, m_isz, m_n);
	MBLOGPRBF;
	for (int ic=0; ic<m_n; ic++)
		m_pg[ic].Print( Mstr( "MgGPolyl3D"));
#endif
}

} // namespace MC
