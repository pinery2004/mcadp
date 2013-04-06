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
//	MgPolyl2�͂Q�����̐܂�����AMgPolyl3�͂R�����̐܂�����`����B
//	MgGPolyl2�͂Q�����̐܂���Q���AMgGPolyl3�͂R�����̐܂���Q���`����B
//	MgGLine2�͂Q�����̐����Q���AMgGPolyl3�͂R�����̐����Q���`����B
//	MgGInt�͐����Q���AMgGReal�͎����Q���`����B
//	MgGPoint2�͂Q�����̓_�Q���AMgGPoint3�͂R�����̓_�Q���`����B
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

//class MgGPoint2;
//class MgGPoint3;
//class MgGPolyl2;
//class MgGPolyl3;
//class MgGLine2;
//class MgGLine3;
//class MgGReal;
class MgPolyl3;
class MgGPolyl3;
//
//======================( �Q���� )==============================
//		�܂��
class DLL_EXPORT_POLILINE MgPolyl2						// �Q�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint2* 	m_p;
public:
	MgPolyl2()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl2( MINT sz);
	MgPolyl2( MINT sz1, MgPoint2 *p2);
	~MgPolyl2()			{ if ( m_fa) MBFREE( m_p);}									// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}	// �̈揉����
	void Free()			{ if ( m_fa) MBFREE( m_p); m_isz = m_n = m_fa = 0;}			// �̈�J��
//	
	const MgPoint2& operator () ( MINT idx) const;
	MgPoint2& operator () ( MINT idx);
	const MgPoint2& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint2& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgPolyl2 &pg);
	void operator = (const MgPolyl3 &Pg);										// �R�������Q����
	void operator += (const MgPoint2& pt);										// �|���S���ɓ_��ǉ�		Pg1 += Pt2
	void operator += (const MgPolyl2 &pg);										// �|���S���Ƀ|���S����ǉ�	Pg1 += Pg2
	void operator -= (const MINT dn)											// �|���S���̍ŏI���_���폜
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()															// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)														// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyl3 &Pg);												// �R�������Q��������p
	MINT Rotation() const;
	void Rev();
	void Resize( MINT szn);
	MREAL Area();
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};
//
//======================( �R���� )==============================
//		�܂��
//
class DLL_EXPORT_POLILINE MgPolyl3						// �R�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint3*	m_p;
public:
	MgPolyl3()			{ m_tp = MGTP_POLYG3; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyl3( MINT sz1);
	MgPolyl3( MINT sz1, MgPoint3 *p2);
	~MgPolyl3()			{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}// �̈揉����
	void Free()	
				{
					if ( m_fa)
						MBFREE( m_p);
					m_isz = m_n = m_fa = 0;
				}					// �̈�J��
//
	const MgPoint3& operator () ( MINT idx) const;
	MgPoint3& operator () ( MINT idx);
	const MgPoint3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgPolyl3 &Pg);
	void operator = (const MgPolyl2 &pg);										// �Q�������R���� (z = 0.)
//						{ *this = MgPolyl3( pg);}
	void operator += (const MgPoint3& Pt);										// Pg1 += Pt2
	void operator += (const MgPolyl3 &Pg);										// Pg1 += Pg2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyl2 &pg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgPolyl2 &pg, const MgPlane3& Ply);							// �Q�������R��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( �Q���� )==============================
//		�܂���Q
//
class DLL_EXPORT_POLILINE MgGPolyl2
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyl2*	m_pg;							// �|���S������ь�
public:
	MgGPolyl2()			{ m_tp = MGTP_GPOLYG; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl2( MINT sz);
	MgGPolyl2( MINT sz1, MgPolyl2 *pg2);
	~MgGPolyl2();
//
	void Free();																// �̈�J��
//
	const MgPolyl2& operator () ( MINT idx) const;
	MgPolyl2& operator () ( MINT idx);
	const MgPolyl2& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyl2& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl2 &Gpg);
	void operator = (const MgGPolyl3 &GPg);										// �R�������Q����
	void operator += (const MgPolyl2 &pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl2 &Gpg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if (m_n>0) { --m_n; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if (m_n>0) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl3 &GPg);											// �R�������Q��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//
//======================( �R���� )==============================
//		�܂���Q
//
class DLL_EXPORT_POLILINE MgGPolyl3
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyl3*	m_pg;							// �|���S������ь�
public:
	MgGPolyl3()	
						{ m_tp = MGTP_GPOLYG3; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyl3( MINT sz1);
	MgGPolyl3( MINT sz1, MgPolyl3 *Pg2);
	~MgGPolyl3();
//
	void Free();																// �̈�J��
//
	const MgPolyl3& operator () ( MINT idx) const; 
	MgPolyl3& operator () ( MINT idx);
	const MgPolyl3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyl3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyl3 &GPg);
	void operator = (const MgGPolyl2 &Gpg);										// �Q�������R���� (z = 0.)
	void operator += (const MgPolyl3 &Pg);										// GPg1 += Pg2
	void operator += (const MgGPolyl3 &GPg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if ( m_n>0) { --m_n; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if ( m_n>0) { m_n--; if ( m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyl2 &Gpg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgGPolyl2 &Gpg, const MgPlane3& Pln);						// �Q�������R��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

} // namespace MC
