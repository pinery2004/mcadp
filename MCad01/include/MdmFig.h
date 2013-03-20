#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmFig.h
//
//		�}�`���
//
//

#include	"MdmDefine.h"
#include	"MdAry.h"
#include	"MdAryH.h"
#include	"MdZukei.h"

#ifdef DLL_EXPORT_FIG
	#undef DLL_EXPORT_FIG
#endif

#ifdef DLL_EXPORT_MDFIG_DO
	#pragma message( "<<< MdFig�Edll_EXport >>>")
	#define DLL_EXPORT_FIG							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT_FIG
		#else
//			#pragma message( "=== MdFig�Edll_IMport ===")
			#define DLL_EXPORT_FIG						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_FIG
	#endif
#endif

//==========================================================================================
//	�}�`���
//	�E
//
//==========================================================================================

#define MP_SZ_MDFIG		10
#define MP_MXSZ_MDFIG	0xffff
#define MP_SZ_MDHDR		1
#define MP_EOF_MDFIG	-1

#define MC_INTRGB		0x80			// 4�o�C�g�^��	A,R,G,B

#define MC_AMBIENT		1				// ����
#define MC_DIFFUSE		2				// �g�U��
#define MC_SPECULAR		3				// ���ʌ�
#define MC_EMISSION		4				// ���ˌ�
#define MC_AMBIENT_AND_DIFFUSE	5		// �����Ɗg�U��

typedef	MREAL		MDPMTDT;

namespace MC
{

// ��{�v�f
class MINT1 {
public:
	MINT i[1];

//	MINT1() {}
	MINT1( MINT i_i)
		{ i[0] = i_i;}
	MINT1& operator = ( const MINT i_i)
						{ i[0] = i_i; return *this;}
	MINT1& operator = ( const MINT i_i[1])
						{ i[0] = i_i[0]; return *this;}
};

class MINT2
{
public:
	MINT i[2];

//	MINT2() {}
	MINT2( MINT i_i1, MINT i_i2)
		{ i[0] = i_i1; i[1] = i_i2;}
	MINT2& operator = ( const MINT i_i[2])
						{ i[0] = i_i[0]; i[1] = i_i[1]; return *this;}
};

class MINT3
{
public:
	MINT i[3];

//	MINT3() {}
	MINT3( MINT i_i1, MINT i_i2, MINT i_i3)
		{ i[0] = i_i1; i[1] = i_i2; i[2] = i_i3;}
	MINT3& operator = ( const MINT i_i[3])
						{ i[0] = i_i[0]; i[1] = i_i[1]; i[2] = i_i[2]; return *this;}
};

class MINT4 { MINT i[4];};
class MINT5 { MINT i[5];};
class MINT6 { MINT i[6];};
class MINT7 { MINT i[7];};
class MINT8 { MINT i[8];};
class MINT9 { MINT i[9];};
class MINT10 { MINT i[10];};

class MREAL1
{
public:
	MREAL r[1];

//	MREAL1() {}
	MREAL1( MREAL i_r)
		{ r[0] = i_r;}
	MREAL1& operator = ( const MREAL i_r)
						{ r[0] = i_r; return *this;}
	MREAL1& operator = ( const MREAL i_r[1])
						{ r[0] = i_r[0]; return *this;}
};

class MREAL2
{
public:
	MREAL r[2];

//	MREAL2() {}
	MREAL2( MREAL i_r1, MREAL i_r2)
		{ r[0] = i_r1; r[1] = i_r2;}
	MREAL2& operator = ( const MREAL i_r[2])
						{ r[0] = i_r[0]; r[1] = i_r[1]; return *this;}
};

class MREAL3 
{
public:
	MREAL r[3];

//	MREAL3() {}
	MREAL3( MREAL i_r1, MREAL i_r2, MREAL i_r3)
		{ r[0] = i_r1; r[1] = i_r2; r[2] = i_r3;}
	MREAL3& operator = ( const MREAL i_r[3])
						{ r[0] = i_r[0]; r[1] = i_r[1]; r[2] = i_r[2]; return *this;}
};
class MREAL4 { MREAL r[4];};
class MREAL5 { MREAL r[5];};
class MREAL6 { MREAL r[6];};
class MREAL7 { MREAL r[7];};
class MREAL8 { MREAL r[8];};
class MREAL9 { MREAL r[9];};
class MREAL10 { MREAL r[10];};

class FLOAT1
{
public:
	float f[1];

//	FLOAT1() {}
	FLOAT1( float i_f)
		{ f[0] = i_f;}
	FLOAT1& operator = ( const float i_f)
						{ f[0] = i_f; return *this;}
	FLOAT1& operator = ( const float i_f[1])
						{ f[0] = i_f[0]; return *this;}
};
class FLOAT2
{
public:
	float f[2];

//	FLOAT2() {}
	FLOAT2( float i_f1, float i_f2)
		{ f[0] = i_f1; f[1] = i_f2;}
	FLOAT2& operator = ( const float i_f[2])
						{ f[0] = i_f[0]; f[1] = i_f[1]; return *this;}
};
class FLOAT3
{
public:
	float f[3];

//	FLOAT3() {}
	FLOAT3( float i_f1, float i_f2, float i_f3)
		{ f[0] = i_f1; f[1] = i_f2; f[2] = i_f3;}
	FLOAT3& operator = ( const float i_f[3])
						{ f[0] = i_f[0]; f[1] = i_f[1]; f[2] = i_f[2]; return *this;}
};
class FLOAT4 { float f[4];};
class FLOAT5 { float f[5];};
class FLOAT6 { float f[6];};
class FLOAT7 { float f[7];};
class FLOAT8 { float f[8];};
class FLOAT9 { float f[9];};
class FLOAT10 { float i[10];};

class DOUBLE1
{
public:
	double d[1];

//	DOUBLE1() {}
	DOUBLE1( double i_d)
						{ d[0] = i_d;}
	DOUBLE1& operator = ( const double i_d)
						{ d[0] = i_d; return *this;}
	DOUBLE1& operator = ( const double i_d[1])
						{ d[0] = i_d[0]; return *this;}
};
class DOUBLE2
{
public:
	double d[2];

//	DOUBLE2() {}
	DOUBLE2( double i_d1, double i_d2)
						{ d[0] = i_d1; d[1] = i_d2;}
	DOUBLE2& operator = ( const double i_d[2])
						{ d[0] = i_d[0]; d[1] = i_d[1]; return *this;}
};
class DOUBLE3 {
public:
	double d[3];

//	DOUBLE3() {}
	DOUBLE3( double i_d1, double i_d2, double i_d3)
						{ d[0] = i_d1; d[1] = i_d2; d[2] = i_d3;}
	DOUBLE3& operator = ( const double i_d[3])
						{ d[0] = i_d[0]; d[1] = i_d[1]; d[2] = i_d[2]; return *this;}
};
class DOUBLE4 { double d[4];};
class DOUBLE5 { double d[5];};
class DOUBLE6 { double d[6];};
class DOUBLE7 { double d[7];};
class DOUBLE8 { double d[8];};
class DOUBLE9 { double d[9];};
class DOUBLE10 { double d[10];};

class MHALF {
public:
	MSHORT	m_iH1;
	MSHORT	m_iH2;

	MHALF( MSHORT i_iH1, MSHORT i_iH2) { m_iH1 = i_iH1; m_iH2 = i_iH2;}
	MHALF& operator = ( const MUINT i_i)
						{ *(UINT*)this = i_i; return *this;}
	MUINT& operator = ( const MHALF i_h)
						{ return *(UINT*)this;}
};

class MUHALF {
public:
	MUSHORT	m_iH1;
	MUSHORT	m_iH2;

	MUHALF( MUSHORT i_iH1, MUSHORT i_iH2) { m_iH1 = i_iH1; m_iH2 = i_iH2;}
	MUHALF& operator = ( const MUINT i_i)
						{ *(UINT*)this = i_i; return *this;}
	MUINT& operator = ( const MUHALF i_h)
						{ return *(UINT*)this;}
};

class MQUARTER {
public:
	MBYTE	m_iQ4;
	MBYTE	m_iQ3;
	MBYTE	m_iQ2;
	MBYTE	m_iQ1;

	MQUARTER( MBYTE i_iQ1, MBYTE i_iQ2, MBYTE i_iQ3, MBYTE i_iQ4)
					{ m_iQ1 = i_iQ1; m_iQ2 = i_iQ2; m_iQ3 = i_iQ3; m_iQ4 = i_iQ4;}
	MQUARTER& operator = ( const MUINT i_i)
						{ *(UINT*)this = i_i; return *this;}
	MUINT& operator = ( const MQUARTER i_h)
						{ return *(UINT*)this;}
};

class MUQUARTER {
public:
	MUBYTE	m_iQ4;
	MUBYTE	m_iQ3;
	MUBYTE	m_iQ2;
	MUBYTE	m_iQ1;

	MUQUARTER( MUBYTE i_iQ1, MUBYTE i_iQ2, MUBYTE i_iQ3, MUBYTE i_iQ4)
					{ m_iQ1 = i_iQ1; m_iQ2 = i_iQ2; m_iQ3 = i_iQ3; m_iQ4 = i_iQ4;}
	MUQUARTER& operator = ( const MUINT i_i)
						{ *(UINT*)this = i_i; return *this;}
	MUINT& operator = ( const MUQUARTER i_h)
						{ return *(UINT*)this;}
};

inline MINT MNWORD( MCHAR* i_pcStr)
					{ return ( (int)Mstrlen( i_pcStr) * sizeof( MCHAR) / SZMINT() + 1);}
inline MINT MNWORD( char* i_pcStr)
					{ return ( (int)strlen( i_pcStr) * sizeof( char) / SZMINT() + 1);}

// �J���[�}�b�v��
typedef struct _pgrgbquad {
	MBYTE		Blue;																	// �װϯ�ߴ��؂̐̒l
	MBYTE		Green;																	// �װϯ�ߴ��؂̗΂̒l
	MBYTE		Red;																	// �װϯ�ߴ��؂̐Ԃ̒l
	MBYTE		Reserved;																// ���0
} MGRGBQUAD;

//// short �f�[�^
//class MSHORT2
//{
//	MUSHORT		S2;
//	MUSHORT		S1;
//public:
//	MSHORT2( MUSHORT s1, MUSHORT s2) { S1 = s1; S2 = s2;}
//};

//==========================================================================================

// �}�`�v�f�w�b�_
class DLL_EXPORT_FIG MDPHD
{
public:
	MUBYTE		m_icd;							// �}�`�R�[�h(icd)
	MUBYTE		m_itp;							// �}�`�^�C�v			BIT(0,1,2,3,4,5,6,7)�P�ʂŒ�`
												// �}�`���[�h			BIT(1,2,3,4,5,6,7)
												// �}�`����(idim)		BIT(0):	0:3D�f�[�^�A1:2D�f�[�^
	MUSHORT		m_n;								// �}�`�f�[�^�T�C�Y(�w�b�_��������)
};

///////////////////////////////////////////////////////////////////////////////
// �}�`�v�f(�ϒ����[�h(���ɐ����Œ�`))
class DLL_EXPORT_FIG MDPMT							// �T�C�Y�w�肪�ő�2**16-1�܂ł̌`��
{
	friend	class	MDFIG;

	MDPHD		m_hd;							// �}�`�v�f�w�b�_
	union {
		MDPMTDT	m_dt[MP_SZ_MDFIG - 1];				// �}�`���(�}�`�v�f�S)
		MINT	m_i[MP_SZ_MDFIG - 1];					// �f�o�b�O�Q�Ɨp
		MDPHD	m_h[MP_SZ_MDFIG - 1];
	};

public:
	// Head
	MINT	GetCd() const	{ return m_hd.m_icd;}			// �v���~�e�B�u�R�[�h���擾
	MINT	GetDm() const	{ return (m_hd.m_itp & 0x80);}	// �v���~�e�B�u�̎������擾 ( 0;�R����, 1:�Q����)
	MINT	GetMd() const	{ return (m_hd.m_itp & 0x7F);}	// �v���~�e�B�u�̃��[�h
	MINT	GetTp() const	{ return m_hd.m_itp;}			// �v���~�e�B�u�̃^�C�v�R�[�h
	MINT	GetN()	const	{ return m_hd.m_n;}				// �v���~�e�B�u�f�[�^�����擾

	void SetHd( MINT i_icd, MINT i_idm, MINT i_n)
							{ m_hd.m_icd = i_icd;
							  m_hd.m_itp = i_idm;
							  m_hd.m_n = i_n;}
	void SetCd( MINT i_icd)	{ m_hd.m_icd = i_icd;}			// �v���~�e�B�u�R�[�h��ݒ�
	void SetDm( MINT i_idm)	{ m_hd.m_itp = ( m_hd.m_itp & 0x7F) | i_idm;}
															// �v���~�e�B�u�̎�����ݒ� ( 0;�R����, 1:�Q����)
	void SetMd( MINT i_imd)	{ m_hd.m_itp = ( m_hd.m_itp & 0x80) | i_imd;}
															// �v���~�e�B�u�̃��[�h��ݒ� ( 0 �` 0x3F)
	void SetTp( MINT i_itp)	{ m_hd.m_itp = i_itp;}
															// �v���~�e�B�u�̃^�C�v�R�[�h��ݒ�
	void SetN( MINT i_n)	{ m_hd.m_n = i_n;}				// �v���~�e�B�u�f�[�^����ݒ�

	// Data
	MDPMTDT	GetDt( MINT i_ip)
							{ return m_dt[i_ip];}			// �v���~�e�B�u�f�[�^�v�f
	MDPMTDT	*GetpDt( MINT i_ip)
							{ return &m_dt[i_ip];}			// �v���~�e�B�u�f�[�^�v�f�ւ̃|�C���^
	void SetDt( MINT i_ip, MDPMTDT i_dt)
							{ m_dt[i_ip] = i_dt;}			// �v���~�e�B�u�f�[�^�v�f

	// MDPMT
	void zPush( void);
	void zPull( void);
	void zMarker( MINT i_iTp, MREAL i_rSz);					// �}�[�J
	void zPaint( MINT i_iTp, MINT i_iId, MINT i_iEdg);		// �h��Ԃ�
	void zLineTp( MINT i_iTp);								// ����
	void zColorRGB( MUQUARTER i_iRgb);						// �F( RGB) ( byte * 3)
	void zColorRGB( FLOAT3& i_fRgb);						// �F( RGB) ( float * 3)
	void zColorPlt( MINT i_iPltN);							// �F(�p���b�gNo)
	void zTransmissivity( MFLOAT i_fTransm);				// ���ߗ� ( 0. �` 1.)
	void zLineWd( MFLOAT i_rLWd);							// ����
	void zMaterialRGBA( MINT i_iMtN, MUQUARTER i_iRgb);		// �ގ�( RGB) ( byte * 3)
	void zMaterialRGBA( MINT i_iMtN, FLOAT3& i_f3Rgb,
						MFLOAT i_fAlpha = 1);				// �ގ�( RGB) ( float * 3)
	void zMaterialShininess( MREAL i_rShns);						// �ގ����ʌ�(����)�W��
	void zTexture( MINT i_iTxtrId);							// �e�N�X�`��
	void zTextureCoordinate(
						MINT		i_iMdCA,
						MINT		i_iMdCB = 0,
				const	MgVect2*	i_vszimg = 0,
				const	MgMat3E*		i_matH = 0);			// �e�N�X�`�����W
	void zTextureParam( MINT i_iTp, MINT i_iPxLap,
					    MINT i_iPyLap, MINT i_iFltEx,
					    MINT i_iFltRd, MREAL3& i_fColBlc1,
					    MREAL3& i_fColBlc2);				// �e�N�X�`���p�����[�^
	void zShininess( MREAL i_fShns);						// ���ʔ��˗� ( 0. �` 1.)
	void zPovRay( MCHAR* i_pcStr);							// PovRay�o�͑���

	void Point3( const MgPoint3&	i_Pt);
	void Line3( const MgLine3&		i_Ln);
	void ULine3( const MgULine3&	i_uLn);
	void HLine3( const MgHLine3&	i_hLn);
	void Polyl3( const MgPolyl3&	i_Ply);
	void Polyg3( const MgPolyg3&	i_Pgn);
	void Cir3( const MgCir3&		i_Cir);
	void Arc3( const MgArc3&		i_Arc);
//U	void Elps3( const MgElps3&		i_Elps);
//U	void Ela3( const MgEla3&		i_Ela);
	void Plane3( const MgPlane3&	i_Pln);
	void IPlane3( const MgPlane3&	i_iPln);
//U	void Cyl3( const MgCly3&		i_Cly);
//U	void SLine3( const MgSLine3&	i_sLn);
};

// �}�`���
class MDFIG;

///////////////////////////////////////////////////////////////////////////////
// �}�`�v�f�S(�ϒ����[�h(���ɐ����Œ�`))
class DLL_EXPORT_FIG MDPMTL
{
	friend class MDFIG;
	MUSHORT		m_sz;							// �o�b�t�@�T�C�Y
	MUSHORT		m_n;							// �f�[�^�T�C�Y(�w�b�_��������)
//	MgMinMaxR3	m_Mmx;

	union {
		MDPMTDT	m_dt[MP_SZ_MDFIG];				// �}�`���(�}�`�v�f�S)
		MINT	m_i[MP_SZ_MDFIG];				// �f�o�b�O�Q�Ɨp
		MDPHD	m_h[MP_SZ_MDFIG - 1];
	};

public:
	MDPMTL*	New( MINT i_sz);

	MINT	GetSz() const;						// �}�`���o�b�t�@�T�C�Y
	MINT	GetN() const;						// �}�`���T�C�Y
	MDPMT*	GetpPmt( MINT i_ip);				// �}�`���|�C���^

	void	SetSz( MINT i_sz);					// �}�`���o�b�t�@�T�C�Y
	void	SetN( MINT i_n);					// �}�`���T�C�Y
};

inline MINT	MDPMTL::GetSz()	const				// �}�`���o�b�t�@�T�C�Y
{ 
	return m_sz;
}
inline MINT	MDPMTL::GetN() const				// �}�`���T�C�Y
{
	return m_n;
}
inline MDPMT*	MDPMTL::GetpPmt( MINT i_ip)		// �}�`���|�C���^
{
	return (MDPMT*)&m_dt[i_ip];
}

inline void	MDPMTL::SetSz( MINT i_sz)			// �}�`���o�b�t�@�T�C�Y
{
	m_sz = i_sz;
}
inline void	MDPMTL::SetN( MINT i_n)				// �}�`���T�C�Y
{
	m_n = i_n;
}

///////////////////////////////////////////////////////////////////////////////
// �}�`���
class DLL_EXPORT_FIG MDFIG
{
	MDPMTL*		m_pPmtl;						// �}�`���

public:
	// �R���X�g���N�^			�����̓T�C�Y�w�肪�ő�255�܂ł̌`��
	MDFIG();									
	MDFIG( MINT i_sz);
	~MDFIG()			{ Free();}

	void 	Free()		{ MBFREE( m_pPmtl);}

	MINT	GetSz() const;						// �}�`���o�b�t�@�T�C�Y
	MINT	GetN() const;						// �}�`���T�C�Y
	MDPMTL*	GetpPmtl();							// �}�`���̃|�C���^

	void	SetSz( MINT i_sz);					// �}�`���o�b�t�@�T�C�Y
	void	SetN( MINT i_n);					// �}�`���T�C�Y
	void	SetpPmtl( MDPMTL* i_pPmts);			// �}�`���̃|�C���^

	// �}�`�v�f
	MDPMT*	GetpPmt( MDID i_idl);				// �}�`�v�f�̃|�C���^���擾
	MINT	GetPmtCd( MDID i_idl);				// �}�`�v�f�̃R�[�h
	MINT	GetPmtDm( MDID i_idl);				// �}�`�v�f�̎���
	MINT	GetPmtTp( MDID i_idl);				// �}�`�v�f�̃^�C�v
	MINT	GetPmtN( MDID i_idl);				// �}�`�v�f�̃T�C�Y
	MDID	GetNextPmt( MDID i_idl);			// ���̐}�`�v�f��IDL(�z��ԍ�)

	void	SetHd( MDID i_idl, MINT i_icd,
				   MINT i_idm, MINT i_n);		// �}�`�v�f�̃R�[�h�A�����A�T�C�Y
	void	SetPmtCd( MDID i_idl, MINT i_icd);	// �}�`�v�f�̃R�[�h
	void	SetPmtDm( MDID i_idl, MINT i_idm);	// �}�`�v�f�̎���
	void	SetPmtTp( MDID i_idl, MINT i_itp);	// �}�`�v�f�̃^�C�v
	void	SetPmtN( MDID i_idl, MINT i_n);		// �}�`�v�f�̃T�C�Y

	// �}�`���̍Ō�ɗv�f��ǉ�
	//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	void operator += ( const MREAL i_r); 		// �}�`���S�ɐ}�`���v�f�̒ǉ�	�}�`��� += �v�f
	void operator += ( const MINT i_i)			// �}�`���S�ɐ}�`���v�f�̒ǉ�	�}�`��� += �v�f
				{ *this += *(MREAL*)&i_i;}

	// �}�`�����R�s�[
	void operator = ( const MDFIG& i_Fig);		// ����		�\���̌Q = �\���̌Q
	void operator = ( const MDPMT& i_Pmt);		// ����		�\���̌Q = �\���̌Q

	// �}�`���ɐ}�`����ǉ�
	//	�o�b�t�@�T�C�Y���s������ꍇ�͂Q�{�ɗ̈�g��(�g����̍Œ�̈�T�C�Y�͂S�Ƃ���)
	void operator += ( const MDFIG& i_Fig);		// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q
	void operator += ( const MDPMT& i_Pmt);		// �\���̌Q�̒ǉ�	�\���̌Q += �\���̌Q

	// �}�`���𓾂�
	MDFIG& operator () ( MINT i_idx);			// �}�`���S����w��Ԗڂ̐}�`�v�f��ǂݏ�������

	// �̈�m�ۂƃT�C�Y�ύX
	void Alloc( MINT i_sz);						// �}�`���S�̗̈�T�C�Y�̗̈�m��
	void ReSize( MINT i_sz);					// �}�`���S�̗̈�T�C�Y�̕ύX�Ɨ̈�m��
	void IncrN( MINT i_n);						// �}�`���S�̗̈�T�C�Y�̊g���Ɨ̈�m��
	MDPMT* PmtAlloc( MINT i_n);					// �v���~�e�B�u�̈���m��

	// �}�`����
	void zPush( void);
	void zPull( void);
	void zMarker( MINT i_iTp, MREAL	i_rSz);					// �}�[�J
	void zPaint( MINT i_iTp, MINT i_iId, MINT i_iEdg);		// �h��Ԃ�
	void zLineTp( MINT i_iTp);								// ����
	void zColorRGB(	MUQUARTER i_iRgb);						// �F(RGB) {byte} ( 0, r, g, b)
	void zColorRGB(	FLOAT3& i_f3Rgb);						// �F(RGB) {float} ( 1., 1., 1.) (1.)
	void zColorPlt( MINT i_iPltN);							// �F(�p���b�g)
	void zTransmissivity( MFLOAT i_fTransm);				// ���ߗ� ( 0. �` 1.)
	void zLineWd( MFLOAT i_rLWd);							// ����
	void zMaterialRGBA( MINT i_iMtN, MUQUARTER i_iRgb);		// �ގ�(RGB) {byte} ( A{���ߗ�}, R, G, B)
	void zMaterialRGBA( MINT i_iMtN,						// �ގ�(RGB) {float}
						FLOAT3& i_f3Rgb, MFLOAT i_fAlpha);	// A ���ߗ�	( 0. �` 1.)
	void zMaterialShininess( MREAL i_rShns);				// �ގ����ʌ�(����)�W�� ( 0. �` 128.)
	void zTexture( MINT i_iTxtrId);							// �e�N�X�`��
	void zTextureCoordinate(
						MINT		i_iMdCA,
						MINT		i_iMdCB, 
				const	MgVect2*	i_vszimg,
				const	MgMat3E*		i_matH);				// �e�N�X�`�����W
	void zTextureParam( MINT i_iTp, MINT i_iPxLap,
						MINT i_iPyLap, MINT i_iFltEx,
						MINT i_iFltRd, MREAL3& i_fColBlc1,
						MREAL3& i_fColBlc2);				// �e�N�X�`���p�����[�^
	void zShininess( MREAL i_fShns);						// ���ʔ��˗� ( 0. �` 1.)
	void zPovRay( MCHAR* i_pcStr);							// PovRay�o�͑��� ������

	// �}�`�v�f
	void Point3( const MgPoint3&	i_Pt);
	void Line3( const MgLine3&		i_Ln);
	void ULine3( const MgULine3&	i_uLn);
	void HLine3( const MgHLine3&	i_hLn);
	void Polyl3( const MgPolyl3&	i_Ply);
	void Polyg3( const MgPolyg3&	i_Pgn);
	void Cir3( const MgCir3&		i_Cir);
	void Arc3( const MgArc3&		i_Arc);
//U	void Elps3( const MgElps3&		i_Elps);
//U	void Ela3( const MgEla3&		i_Ela);
	void Plane3( const MgPlane3&	i_Pln);
	void IPlane3( const MgPlane3&	i_iPln);
//U	void Cyl3( const MgCly3&		i_Cly);
//U	void SLine3( const MgSLine3&	i_sLn);

	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* i_s);

};

//	�R���X�g���N�^
inline MDFIG::MDFIG()									
{
	m_pPmtl = 0;
}

inline MDFIG::MDFIG(
						MINT	i_sz			// �}�`���T�C�Y
				)
{
	MBMALLOCF( MDPMTL, m_pPmtl, MINT, i_sz);
	m_pPmtl->SetSz( i_sz);
	m_pPmtl->SetN( 0);
}

} // namespace MC