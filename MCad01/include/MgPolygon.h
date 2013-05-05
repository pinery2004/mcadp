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
//	MgPolyg2D�͂Q�����̑��p�`���AMgPolyg3D�͂R�����̑��p�`���`����B
//	MgGPolyg2D�͂Q�����̑��p�`�Q���AMgGPolyg3D�͂R�����̑��p�`�Q���`����B
//	MgGLine2D�͂Q�����̐����Q���AMgGPolyg3D�͂R�����̐����Q���`����B
//	MgGInt�͐����Q���AMgGReal�͎����Q���`����B
//	MgGPoint2D�͂Q�����̓_�Q���AMgGPoint3D�͂R�����̓_�Q���`����B
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

class MgGPoint2D;
class MgGPoint3D;
class MgGPolyg2D;
class MgGPolyg3D;
class MgPolyg3D;
class MgGLine2D;
class MgGLine3D;
class MgGReal;

//======================( �Q���� )==============================
//		���p�`
class DLL_EXPORT_POLYGON MgPolyg2D						// �Q�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint2D* 	m_p;
public:
	MgPolyg2D()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgPolyg2D( MINT sz);
	MgPolyg2D( MINT sz1, MgPoint2D *p2);
	~MgPolyg2D()			{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
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
	void operator = (const MgPolyg2D &pg);
	void operator = (const MC::MgPolyg3D &Pg);									// �R�������Q����
	void operator += (const MgPoint2D& pt);										// �|���S���ɓ_��ǉ�		Pg1 += Pt2
	void operator += (const MgPolyg2D &pg);										// �|���S���Ƀ|���S����ǉ�	Pg1 += Pg2
	void operator -= (const MINT dn)											// �|���S���̍ŏI���_���폜
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()															// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)														// �|���S���̍ŏI�_���폜
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyg3D &Pg);												// �R�������Q��������p
	MINT Rotation() const;
	void Rev();
	void Resize( MINT szn);
	MREAL Area();
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		���p�`
//
class DLL_EXPORT_POLYGON MgPolyg3D						// �R�c�|���S��
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_POLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő咸�_��
	MSHORT		m_n;							// ���_��
	MgPoint3D*	m_P;
public:
	MgPolyg3D()			{ m_tp = MGTP_POLYG3; m_isz = m_n = m_fa = 0; m_P = NULL;}
	MgPolyg3D( MINT sz1);
	MgPolyg3D( MINT sz1, MgPoint3D *p2);
	~MgPolyg3D()			{ if ( m_fa) MBFREE( m_P);}								// �̈�J��
//
	void Init()			{ m_tp = MGTP_POLYG; m_isz = m_n = m_fa = 0; m_P = NULL;}// �̈揉����
	void Free()	
				{
					if ( m_fa)
						MBFREE( m_P);
					m_isz = m_n = m_fa = 0;
				}					// �̈�J��
//
	const MgPoint3D& operator () ( MINT idx) const;
	MgPoint3D& operator () ( MINT idx);
	const MgPoint3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_P[idx];}
	MgPoint3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_P[idx];}
	void operator = (const MgPolyg3D &Pg);
	void operator = (const MgPolyg2D &pg);										// �Q�������R���� (z = 0.)
//						{ *this = MgPolyg3D( pg);}
	void operator += (const MgPoint3D& Pt);										// Pg1 += Pt2
	void operator += (const MgPolyg3D &Pg);										// Pg1 += Pg2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_P = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgPolyg2D &pg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgPolyg2D &pg, const MgPlane3D& Ply);						// �Q�������R��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �Q���� )==============================
//		���p�`�Q
//
class DLL_EXPORT_POLYGON MgGPolyg2D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyg2D*	m_pg;							// �|���S������ь�
public:
	MgGPolyg2D()			{ m_tp = MGTP_GPOLYG; m_isz = m_n = m_fa = 0; m_pg = NULL;}
	MgGPolyg2D( MINT sz);
	MgGPolyg2D( MINT sz1, MgPolyg2D *pg2);
	~MgGPolyg2D();
//
	void Free();																// �̈�J��
//
	const MgPolyg2D& operator () ( MINT idx) const;
	MgPolyg2D& operator () ( MINT idx);
	const MgPolyg2D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	MgPolyg2D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_pg[idx];}
	void operator = (const MgGPolyg2D &gpg);
	void operator = (const MgGPolyg3D &gPg);									// �R�������Q����
	void operator += (const MgPolyg2D &pg);										// GPg1 += Pg2
	void operator += (const MgGPolyg2D &gpg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- ()
						{ if (m_n>0) { --m_n; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
	void operator -- (int)
						{ if (m_n>0) { m_n--; if (m_pg[m_n].m_fa) MBFREE( m_pg[m_n].m_p);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyg3D &GPg);											// �R�������Q��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		���p�`�Q
//
class DLL_EXPORT_POLYGON MgGPolyg3D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOLYG3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�|���S��+������
	MSHORT		m_n;							// �|���S��+����
	MgPolyg3D*	m_Pg;							// �|���S������ь�
public:
	MgGPolyg3D()	
						{ m_tp = MGTP_GPOLYG3; m_isz = m_n = m_fa = 0; m_Pg = NULL;}
	MgGPolyg3D( MINT sz1);
	MgGPolyg3D( MINT sz1, MgPolyg3D *Pg2);
	~MgGPolyg3D();
//
	void Free();																// �̈�J��
//
	const MgPolyg3D& operator () ( MINT idx) const; 
	MgPolyg3D& operator () ( MINT idx);
	const MgPolyg3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_Pg[idx];}
	MgPolyg3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_Pg[idx];}
	void operator = (const MgGPolyg3D &GPg);
	void operator = (const MgGPolyg2D &Gpg);									// �Q�������R���� (z = 0.)
	void operator += (const MgPolyg3D &Pg);										// GPg1 += Pg2
	void operator += (const MgGPolyg3D &GPg);									// GPg1 += GPg2
	void operator -= (const MINT dn)
						{ int ict; for ( ict=0; ict<dn && m_n>0; ict--) { m_n--; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
	void operator -- ()
						{ if ( m_n>0) { --m_n; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
	void operator -- (int)
						{ if ( m_n>0) { m_n--; if ( m_Pg[m_n].m_fa) MBFREE( m_Pg[m_n].m_P);}}
//
	void SetCount0()
						{ Free();}
	void Set( const MgGPolyg2D &Gpg, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Set( const MgGPolyg2D &Gpg, const MgPlane3D& Pln);						// �Q�������R��������p
	void AddPolyg();
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �Q���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGLine2D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GLINE
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő������
	MSHORT		m_n;							// ������
	MgLine2D*	m_ln;							// ����
public:
	MgGLine2D()			{ m_tp = MGTP_GLINE; m_isz = m_n = m_fa = 0; m_ln = NULL;}
	MgGLine2D( MINT sz);
	MgGLine2D( MINT sz1, MgLine2D *ln2);
	~MgGLine2D()			{ if ( m_fa) MBFREE( m_ln);}						// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_ln); m_isz = m_n = m_fa = 0;}	// �̈�J��
//
	const MgLine2D& operator () (MINT idx) const;
	MgLine2D& operator () ( MINT idx);
	const MgLine2D& operator [] (MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	MgLine2D& operator [] (MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	void operator = (const MgGLine2D &Gln);
	void operator = (const MgGLine3D &GLn);										// �R�������Q����
	void operator += (const MgLine2D& ln);										// GLn1 += ln2
	void operator += (const MgGLine2D &Gln);									// GLn1 += GLn2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_ln = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGLine3D &GLn);											// �R�������Q��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

MINT DLL_EXPORT_POLYGON MgMergeGLine2D( const MgGLine2D &gln1);					// �����̏d�Ȃ���܂Ƃ߈�{�ɂ���
MINT DLL_EXPORT_POLYGON MgCutGLine2D( const MgGLine2D &gln1);					// �������������ŕ�������

//======================( �R���� )==============================
//		�����Q
//
class DLL_EXPORT_POLYGON MgGLine3D
{
public:
	MUBYTE		m_tp;						// �f�[�^�^�C�v�@MGTP_GLINE3
	MUBYTE		m_fa;						// �A���P�[�V�����t���O(0:�z��, 1:malloc)
											// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;						// �ő������
	MSHORT		m_n;						// ������
	MgLine3D*	m_ln;							// ����
public:
	MgGLine3D()			{ m_tp = MGTP_GLINE3; m_isz = m_n = m_fa = 0; m_ln = NULL;}
	MgGLine3D( MINT sz);
	MgGLine3D( MINT sz1, MgLine3D *Ln3);
	~MgGLine3D()			{ if ( m_fa) MBFREE( m_ln);}						// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_ln); m_isz = m_n = m_fa = 0;}	// �̈�J��
//
	const MgLine3D& operator () ( MINT idx) const;
	MgLine3D& operator () ( MINT idx);
	const MgLine3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	MgLine3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_ln[idx];}
	void operator = (const MgGLine3D &GLn);
	void operator = (const MgGLine2D &Gln);										// �Q�������R���� (z = 0.)
	void operator += (const MgLine3D& Ln);										// GLn1 += Ln2
	void operator += (const MgGLine3D &GLn);									// GLn1 += GLn2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_ln = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGLine2D &Gln2, const MgPlane3D& Pln);						// �Q�������R��������p
	void Set( const MgGLine2D &Gln2, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
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
	void Free()			{ if ( m_fa) MBFREE( m_r);	m_isz = m_n = m_fa = 0;}	// �̈�J��
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
class DLL_EXPORT_POLYGON MgGPoint2D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOINT2
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�_��
	MSHORT		m_n;							// �_��
	MgPoint2D*	m_p;							// �_
public:
	MgGPoint2D()			{ m_tp = MGTP_GPOINT2; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgGPoint2D( MINT sz);
	MgGPoint2D( MINT sz1, MgPoint2D *pt2);
	~MgGPoint2D()		{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_p);  m_isz = m_n = m_fa = 0;}	// �̈�J��
//
	const MgPoint2D& operator () ( MINT idx) const;
	MgPoint2D& operator () ( MINT idx);
	const MgPoint2D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint2D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgGPoint2D &Gpt);
	void operator = (const MgGPoint3D &GPt);									// �R�������Q����
	void operator += (const MgPoint2D& pt);										// GPt1 += Pt2
	void operator += (const MgGPoint2D &Gpt);									// GPt1 += GPt2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					// ���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGPoint3D &GPt);											// �R�������Q��������p
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR2D MinMax();
	void Print( MCHAR* s) const;												// Print
};

//======================( �R���� )==============================
//		�_�Q
//
class DLL_EXPORT_POLYGON MgGPoint3D
{
public:
	MUBYTE		m_tp;							// �f�[�^�^�C�v�@MGTP_GPOINT3
	MUBYTE		m_fa;							// �A���P�[�V�����t���O(0:�z��, 1:malloc)
												// 		=1�̏ꍇ�͎g�p�I������free�ŗ̈�̊J����K�v�Ƃ���
	MSHORT		m_isz;							// �ő�_��
	MSHORT		m_n;							// �_��
	MgPoint3D*	m_p;							// �_
public:
	MgGPoint3D()			{ m_tp = MGTP_GPOINT3; m_isz = m_n = m_fa = 0; m_p = NULL;}
	MgGPoint3D( MINT sz);
	MgGPoint3D( MINT sz1, MgPoint3D *pt2);
	~MgGPoint3D()		{ if ( m_fa) MBFREE( m_p);}								// �̈�J��
//
	void Free()			{ if ( m_fa) MBFREE( m_p);  m_isz = m_n = m_fa = 0;}	// �̈�J��
//
	const MgPoint3D& operator () ( MINT idx) const;
	MgPoint3D& operator () ( MINT idx);
	const MgPoint3D& operator [] ( MINT idx) const								// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	MgPoint3D& operator [] ( MINT idx)											// ()�̃`�F�b�N�@�\�Ɨ̈�g���@�\�����O��������	
						{ return m_p[idx];}
	void operator = (const MgGPoint3D &Pt);
	void operator = (const MgGPoint2D &Gpt);									// �Q�������R���� (z = 0.)	
	void operator += (const MgPoint3D& Pt);										// GPt1 += Pt2
	void operator += (const MgGPoint3D &GPt);									// GPt1 += GPt2
	void operator -= (const MINT dn)
						{ m_n = max( m_n -= dn, 0);}
	void operator -- ()
						{ if ( m_n>0) -- m_n;}
	void operator -- (int)
						{ if ( m_n>0) m_n --;}
//
	void SetInit()		{ m_isz = m_n = m_fa = 0; m_p = NULL;}					//���̌Q������ɌQ�ɂȂ����ꍇ�̍ŏI�f�[�^����̃f�[�^�̃N���A�p
	void Set( const MgGPoint2D &Gpt, const MgPlane3D& Pln);						// �Q�������R��������p
	void Set( const MgGPoint2D &Gpt, MREAL z = 0.);								// �Q�������R��������p (z = 0.)
	void Rev();
	void Resize( MINT szn);
	MgMinMaxR3D MinMax();
	void Print( MCHAR* s) const;												// Print
};

} // namespace MC
