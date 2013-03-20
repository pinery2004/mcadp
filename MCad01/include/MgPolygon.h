#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPolygon.h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

//#include "mdPlex.h"

//
//	MgPolyg.h 
//	Copyright;
// 
//	����
//
//	MgPolyg2�͂Q�����̑��p�`���AMgPolyg3�͂R�����̑��p�`���`����B
//	MgGPolyg2�͂Q�����̑��p�`�Q���AMgGPolyg3�͂R�����̑��p�`�Q���`����B
//	MgGLine2�͂Q�����̐����Q���AMgGPolyg3�͂R�����̐����Q���`����B
//	MgGInt�͐����Q���AMgGReal�͎����Q���`����B
//	MgGPoint2�͂Q�����̓_�Q���AMgGPoint3�͂R�����̓_�Q���`����B
//	�I�[�o���C�֐����`����B
//
#include "MgPlane.h"
#include "MgRect.h"
#include "MgPolyline.h"

#ifdef DLL_EXPORT_POLYGON
	#undef DLL_EXPORT_POLYGON
#endif

#ifdef DLL_EXPORT_POLYGON_DO
	#pragma message( "<<< MgPolyg�Edll_EXport >>>")
	#define DLL_EXPORT_POLYGON							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_POLYGON
		#else
//			#pragma message( "=== MgPolyg�Edll_IMport ===")
			#define DLL_EXPORT_POLYGON						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_POLYGON
	#endif
#endif

namespace MC
{

class MgGPoint2;
class MgGPoint3;
class MgGPolyg2;
class MgGPolyg3;
class MgPolyg3;
class MgGLine2;
class MgGLine3;
class MgGReal;

//======================( �Q���� )==============================
//		���p�`
class DLL_EXPORT_POLYGON MgPolyg2						// �Q�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint2* 	m_p;
public:
	MgPolyg2()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyg2( MINT sz);
	MgPolyg2( MINT sz1, MgPoint2 *p2);
	~MgPolyg2()			{ if ( m_fa) MBFREE( m_p);}									// �̈�J��
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
	void operator = (const MgPolyg2 &pg);
	void operator = (const MC::MgPolyg3 &Pg);										// �R�������Q����
	void operator += (const MgPoint2& pt);										// �|���S���ɓ_��ǉ�		Pg1 += Pt2
	void operator += (const MgPolyg2 &pg);										// �|���S���Ƀ|���S����ǉ�	Pg1 += Pg2
	void operator -= (const MINT dn)											// �|���S���̍ŏI���_���폜
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()															// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)														// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyg3 &Pg);												// �R�������Q��������p
	MINT Rotation() const;
	void Rev();
	void Resize( MINT szn);
	MREAL Area();
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		���p�`
//
class DLL_EXPORT_POLYGON MgPolyg3						// �R�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint3*	m_P;
public:
	MgPolyg3()			{ m_tp = MGTP_POLYG3; m_isz = m_n = m_fa = 0; m_P = NULL;}
	MgPolyg3( MINT sz1);
	MgPolyg3( MINT sz1, MgPoint3 *p2);
	~MgPolyg3()			{ if ( m_fa) MBFREE( m_P);}								// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_P = NULL;}// �̈揉����
	void Free()	
				{
					if ( m_fa)
						MBFREE( m_P);
					m_isz = m_n = m_fa = 0;
				}					// �̈�J��
//
	const MgPoint3& operator () ( MINT idx) const;
	MgPoint3& operator () ( MINT idx);
	const MgPoint3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_P[idx];}
	MgPoint3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_P[idx];}
	void operator = (const MgPolyg3 &Pg);
	void operator = (const MgPolyg2 &pg);										// �Q�������R���� (z = 0.)
//						{ *this = MgPolyg3( pg);}
	void operator += (const MgPoint3& Pt);										// Pg1 += Pt2
	void operator += (const MgPolyg3 &Pg);										// Pg1 += Pg2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_P = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyg2 &pg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgPolyg2 &pg, const MgPlane3& Ply);							// �Q�������R��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �Q���� )==============================
//		���p�`�Q
//
class DLL_EXPORT_POLYGON MgGPolyg2
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyg2*	m_pg;							// �|���S������ь�
public:
	MgGPolyg2()			{ m_tp = MGTP_GPOLYG; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyg2( MINT sz);
	MgGPolyg2( MINT sz1, MgPolyg2 *pg2);
	~MgGPolyg2();
//
	void Free();																// �̈�J��
//
	const MgPolyg2& operator () ( MINT idx) const;
	MgPolyg2& operator () ( MINT idx);
	const MgPolyg2& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyg2& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyg2 &gpg);
	void operator = (const MgGPolyg3 &gPg);										// �R�������Q����
	void operator += (const MgPolyg2 &pg);										// GPg1 += Pg2
	void operator += (const MgGPolyg2 &gpg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if (m_n>0) { --m_n; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if (m_n>0) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyg3 &GPg);											// �R�������Q��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		���p�`�Q
//
class DLL_EXPORT_POLYGON MgGPolyg3
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyg3*	m_Pg;							// �|���S������ь�
public:
	MgGPolyg3()	
						{ m_tp = MGTP_GPOLYG3; m_isz = m_n = m_fa = 0; m_Pg = NULL;}
	MgGPolyg3( MINT sz1);
	MgGPolyg3( MINT sz1, MgPolyg3 *Pg2);
	~MgGPolyg3();
//
	void Free();																// �̈�J��
//
	const MgPolyg3& operator () ( MINT idx) const; 
	MgPolyg3& operator () ( MINT idx);
	const MgPolyg3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_Pg[idx];}
	MgPolyg3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_Pg[idx];}
	void operator = (const MgGPolyg3 &GPg);
	void operator = (const MgGPolyg2 &Gpg);										// �Q�������R���� (z = 0.)
	void operator += (const MgPolyg3 &Pg);										// GPg1 += Pg2
	void operator += (const MgGPolyg3 &GPg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
	void operator -- ()
						{ if ( m_n>0) { --m_n; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
	void operator -- (int)
						{ if ( m_n>0) { m_n--; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyg2 &Gpg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgGPolyg2 &Gpg, const MgPlane3& Pln);						// �Q�������R��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �Q���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGLine2
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GLINE
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő������
	MSHORT		m_n;							// ������
	MgLine2*	m_ln;							// ����
public:
	MgGLine2()			{ m_tp = MGTP_GLINE; m_isz = m_n = m_fa = 0; m_ln = NULL;}
	MgGLine2( MINT sz);
	MgGLine2( MINT sz1, MgLine2 *ln2);
	~MgGLine2()			{ if ( m_fa) MBFREE( m_ln);}							// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_ln); m_isz = m_n = m_fa = 0;}		// �̈�J��
//
	const MgLine2& operator () (MINT idx) const;
	MgLine2& operator () ( MINT idx);
	const MgLine2& operator [] (MINT idx) const									// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	MgLine2& operator [] (MINT idx)												// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	void operator = (const MgGLine2 &Gln);
	void operator = (const MgGLine3 &GLn);										// �R�������Q����
	void operator += (const MgLine2& ln);										// GLn1 += ln2
	void operator += (const MgGLine2 &Gln);										// GLn1 += GLn2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_ln = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGLine3 &GLn);												// �R�������Q��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};

MINT DLL_EXPORT_POLYGON MgMergeGLine2( const MgGLine2 &gln1);							// �����̏d�Ȃ���܂Ƃ߈�{�ɂ���
MINT DLL_EXPORT_POLYGON MgCutGLine2( const MgGLine2 &gln1);								// �������������ŕ�������

//======================( �R���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGLine3
{
public:
	MUBYTE		m_tp;						// �f�[�^�^�C�v�@MGTP_GLINE3
	MUBYTE		m_fa;						// �A���P�[�V�����t���O(0:�z��, 1:malloc)
											// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;						// �ő������
	MSHORT		m_n;						// ������
	MgLine3*	m_ln;							// ����
public:
	MgGLine3()			{ m_tp = MGTP_GLINE3; m_isz = m_n = m_fa = 0; m_ln = NULL;}
	MgGLine3( MINT sz);
	MgGLine3( MINT sz1, MgLine3 *Ln3);
	~MgGLine3()			{ if ( m_fa) MBFREE( m_ln);}							// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_ln); m_isz = m_n = m_fa = 0;}		// �̈�J��
//
	const MgLine3& operator () ( MINT idx) const;
	MgLine3& operator () ( MINT idx);
	const MgLine3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	MgLine3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	void operator = (const MgGLine3 &GLn);
	void operator = (const MgGLine2 &Gln);										// �Q�������R���� (z = 0.)
	void operator += (const MgLine3& Ln);										// GLn1 += Ln2
	void operator += (const MgGLine3 &GLn);										// GLn1 += GLn2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_ln = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGLine2 &Gln2, const MgPlane3& Pln);						// �Q�������R��������p
	void Set( const MgGLine2 &Gln2, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �P���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGInt
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GINT
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő吮����
	MSHORT		m_n;							// ������
	MINT*		m_i;							// ����
public:
	MgGInt()			{ m_tp = MGTP_GINT; m_isz = m_n = m_fa = 0; m_i = NULL;}
	MgGInt( MINT sz);
	MgGInt( MINT sz1, MINT *i2);
	~MgGInt()			{ if ( m_fa) MBFREE( m_i);}								// �̈�J��
//
	void Init()			{ m_tp = MGTP_GINT; m_isz = m_n = m_fa = 0; m_i = NULL;}
	void Free()	
						{
							if ( m_fa) 
								MBFREE( m_i);
							m_isz = m_n = m_fa = 0;
							m_i = NULL;
						}														// �̈�J��
//
	const MINT& operator () ( MINT idx) const;
	MINT& operator () ( MINT idx);
	const MINT& operator [] ( MINT idx) const									// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_i[idx];}
	MINT& operator [] ( MINT idx)												// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_i[idx];}
	void operator = (const MgGInt &GI);
	void operator = (const MgGReal &GR);										// �����Q �� �����Q
	void operator += (const MINT &i);											// GPt1 += i2
	void operator += (const MgGInt &GI);										// GPt1 += GI2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_i = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGReal &GR);												// �����Q �� �����Q����p
	void Rev();
	void Resize( MINT szn);
	void Print( MCHAR* s) const;												// Print
};

//======================( �P���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGReal
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GREAL
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő������
	MSHORT		m_n;							// ������
	MREAL*		m_r;							// ����
public:
	MgGReal()			{ m_tp = MGTP_GREAL; m_isz = m_n = m_fa = 0; m_r = NULL;}
	MgGReal( MINT sz);
	MgGReal( MINT sz1, MREAL* r2);
	~MgGReal()			{ if ( m_fa) MBFREE( m_r);}								// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_r);	m_isz = m_n = m_fa = 0;}		// �̈�J��
//
	const MREAL& operator () ( MINT idx) const;
	MREAL& operator () ( MINT idx);
	const MREAL& operator [] ( MINT idx) const									// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_r[idx];}
	MREAL& operator [] ( MINT idx)												// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_r[idx];}
	void operator = (const MgGReal &GR);
	void operator = (const MgGInt &GI);											// �����Q �� �����Q
	void operator += (const MREAL &r);											// GPt1 += r2
	void operator += (const MgGReal &GR);										// GPt1 += GR2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_r = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const  MgGInt &GI);												// �����Q �� �����Q����p
	void Rev();
	void Resize( MINT szn);
	void Print( MCHAR* s) const;												// Print
};

//======================( �Q���� )==============================
//		�_�Q
//
class DLL_EXPORT_POLYGON MgGPoint2
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOINT2
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�_��
	MSHORT		m_n;							// �_��
	MgPoint2*	m_p;							// �_
public:
	MgGPoint2()			{ m_tp = MGTP_GPOINT2; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgGPoint2( MINT sz);
	MgGPoint2( MINT sz1, MgPoint2 *pt2);
	~MgGPoint2()		{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_p);  m_isz = m_n = m_fa = 0;}		// �̈�J��
//
	const MgPoint2& operator () ( MINT idx) const;
	MgPoint2& operator () ( MINT idx);
	const MgPoint2& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint2& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgGPoint2 &Gpt);
	void operator = (const MgGPoint3 &GPt);										// �R�������Q����
	void operator += (const MgPoint2& pt);										// GPt1 += Pt2
	void operator += (const MgGPoint2 &Gpt);									// GPt1 += GPt2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}							// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGPoint3 &GPt);											// �R�������Q��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2 MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		�_�Q
//
class DLL_EXPORT_POLYGON MgGPoint3
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOINT3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�_��
	MSHORT		m_n;							// �_��
	MgPoint3*	m_p;							// �_
public:
	MgGPoint3()			{ m_tp = MGTP_GPOINT3; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgGPoint3( MINT sz);
	MgGPoint3( MINT sz1, MgPoint3 *pt2);
	~MgGPoint3()		{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_p);  m_isz = m_n = m_fa = 0;}		// �̈�J��
//
	const MgPoint3& operator () ( MINT idx) const;
	MgPoint3& operator () ( MINT idx);
	const MgPoint3& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint3& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgGPoint3 &Pt);
	void operator = (const MgGPoint2 &Gpt);										// �Q�������R���� (z = 0.)	
	void operator += (const MgPoint3& Pt);										// GPt1 += Pt2
	void operator += (const MgGPoint3 &GPt);									// GPt1 += GPt2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGPoint2 &Gpt, const MgPlane3& Pln);						// �Q�������R��������p
	void Set( const MgGPoint2 &Gpt, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3 MinMax();
	void Print( MCHAR* s) const;												// Print
};

} // namespace MC