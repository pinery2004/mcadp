#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolyline.h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "mdPlex.h"
#include "MsDefArea.h"

//
//	MgPolyg.h 
//	Copyright;
// 
//	����
//
//	MgPolyl2D�͂Q�����̐܂�����AMgPolyl3D�͂R�����̐܂�����`����B
//	MgGPolyl2D�͂Q�����̐܂���Q���AMgGPolyl3D�͂R�����̐܂���Q���`����B
//	MgGLine2D�͂Q�����̐����Q���AMgGPolyl3D�͂R�����̐����Q���`����B
//	MgGInt�͐����Q���AMgGReal�͎����Q���`����B
//	MgGPoint2D�͂Q�����̓_�Q���AMgGPoint3D�͂R�����̓_�Q���`����B
//	�I�[�o���C�֐����`����B
//
#include "MgPlane.h"
#include "MgRect.h"

#ifdef DLL_EXPORT_POLILINE
	#undef DLL_EXPORT_POLILINE
#endif

#ifdef DLL_EXPORT_POLYLINE_DO
	#pragma message( "<<< MgPolyline�Edll_EXport >>>")
	#define DLL_EXPORT_POLILINE							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_POLILINE
		#else
//			#pragma message( "=== MgPolyline�Edll_IMport ===")
			#define DLL_EXPORT_POLILINE						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_POLILINE
	#endif
#endif

namespace MC
{

//class MgGPoint2D;
//class MgGPoint3D;
//class MgGPolyl2D;
//class MgGPolyl3D;
//class MgGLine2D;
//class MgGLine3D;
//class MgGReal;
class MgPolyl3D;
class MgGPolyl3D;
//
//======================( �Q���� )==============================
//		�܂��
class DLL_EXPORT_POLILINE MgPolyl2D						// �Q�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint2D* 	m_p;
public:
	MgPolyl2D()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl2D( MINT sz);
	MgPolyl2D( MINT sz1, MgPoint2D *p2);
	~MgPolyl2D()			{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}	// �̈揉����
	void Free()			{ if ( m_fa) MBFREE( m_p); m_isz = m_n = m_fa = 0;}			// �̈�J��
//	
	const MgPoint2D& operator () ( MINT idx) const;
	MgPoint2D& operator () ( MINT idx);
	const MgPoint2D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint2D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgPolyl2D &pg);
	void operator = (const MgPolyl3D &Pg);										// �R�������Q����
	void operator += (const MgPoint2D& pt);										// �|���S���ɓ_��ǉ�		Pg1 += Pt2
	void operator += (const MgPolyl2D &pg);										// �|���S���Ƀ|���S����ǉ�	Pg1 += Pg2
	void operator -= (MINT dn)													// �|���S���̍ŏI���_���폜
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()															// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)														// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyl3D &Pg);												// �R�������Q��������p
	MINT Rotation() const;
	void Rev();
	void Resize( MINT szn);
	MREAL Area();
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};
//
//======================( �R���� )==============================
//		�܂��
//
class DLL_EXPORT_POLILINE MgPolyl3D						// �R�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint3D*	m_p;
public:
	MgPolyl3D()			{ m_tp = MGTP_POLYG3; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl3D( MINT sz1);
	MgPolyl3D( MINT sz1, MgPoint3D *p2);
	~MgPolyl3D()			{ if ( m_fa) MBFREE( m_p);}							// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}// �̈揉����
	void Free()	
				{
					if ( m_fa)
						MBFREE( m_p);
					m_isz = m_n = m_fa = 0;
				}					// �̈�J��
//
	const MgPoint3D& operator () ( MINT idx) const;
	MgPoint3D& operator () ( MINT idx);
	const MgPoint3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgPolyl3D &Pg);
	void operator = (const MgPolyl2D &pg);										// �Q�������R���� (z = 0.)
//						{ *this = MgPolyl3D( pg);}
	void operator += (const MgPoint3D& Pt);										// Pg1 += Pt2
	void operator += (const MgPolyl3D &Pg);										// Pg1 += Pg2
	void operator -= (MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyl2D &pg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgPolyl2D &pg, const MgPlane3D& Ply);						// �Q�������R��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( �Q���� )==============================
//		�܂���Q
//
class DLL_EXPORT_POLILINE MgGPolyl2D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyl2D*	m_pg;							// �|���S������ь�
public:
	MgGPolyl2D()			{ m_tp = MGTP_GPOLYG; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl2D( MINT sz);
	MgGPolyl2D( MINT sz1, MgPolyl2D *pg2);
	~MgGPolyl2D();
//
	void Free();																// �̈�J��
//
	const MgPolyl2D& operator () ( MINT idx) const;
	MgPolyl2D& operator () ( MINT idx);
	const MgPolyl2D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyl2D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl2D &Gpg);
	void operator = (const MgGPolyl3D &GPg);									// �R�������Q����
	void operator += (const MgPolyl2D &pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl2D &Gpg);									// GPg1 += GPg2
	void operator -= (MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if (m_n>0) { --m_n; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if (m_n>0) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl3D &GPg);											// �R�������Q��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( �R���� )==============================
//		�܂���Q
//
class DLL_EXPORT_POLILINE MgGPolyl3D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyl3D*	m_pg;							// �|���S������ь�
public:
	MgGPolyl3D()	
						{ m_tp = MGTP_GPOLYG3; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl3D( MINT sz1);
	MgGPolyl3D( MINT sz1, MgPolyl3D *Pg2);
	~MgGPolyl3D();
//
	void Free();																// �̈�J��
//
	const MgPolyl3D& operator () ( MINT idx) const; 
	MgPolyl3D& operator () ( MINT idx);
	const MgPolyl3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyl3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl3D &GPg);
	void operator = (const MgGPolyl2D &Gpg);									// �Q�������R���� (z = 0.)
	void operator += (const MgPolyl3D &Pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl3D &GPg);									// GPg1 += GPg2
	void operator -= (MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if ( m_n>0) { --m_n; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if ( m_n>0) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl2D &Gpg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgGPolyl2D &Gpg, const MgPlane3D& Pln);						// �Q�������R��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

} // namespace MC
