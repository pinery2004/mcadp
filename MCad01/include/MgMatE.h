#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgMat.h
//
//		�}�g���b�N�X
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//

//
#include "MgRect.h"

class MgMat3E;
class MgGPoint2;
class MgGPoint3;
class MgPolyg2;
class MgGPolyg2;
class MgGPolyg3;
class MgGLine2;
class MgGLine3;

#include "mdPlex.h"

#ifdef DLL_EXPORT_MAT
	#undef DLL_EXPORT_MAT
#endif

#ifdef DLL_EXPORT_MAT_DO
	#pragma message( "<<< MgMat�Edll_EXport >>>")
	#define DLL_EXPORT_MAT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_MAT
		#else
//			#pragma message( "=== MgMat�Edll_IMport ===")
			#define DLL_EXPORT_MAT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_MAT
	#endif
#endif

namespace MC
{

//
//======================( �Q���� )==============================
//	�Q�������W�v�Z�p�R�����}�g���b�N�X
class DLL_EXPORT_MAT MgMat2E
{
public:
	MREAL m[3][3];
//
public:
	MgMat2E() {}
	MgMat2E( MREAL i_m11, MREAL i_m12,
		    MREAL i_m21, MREAL i_m22,
		    MREAL i_m31, MREAL i_m32) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = 0.;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = 0.;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = 1.;}
	MgMat2E( MREAL i_m[3][2]) {
		memcpy( m[0], i_m[0], SZMREAL( 2)); i_m[0][2] = 0.;
		memcpy( m[1], i_m[1], SZMREAL( 2)); i_m[1][2] = 0.;
		memcpy( m[2], i_m[2], SZMREAL( 2)); i_m[2][2] = 1.;}
	MgMat2E( MREAL i_m[6]) {
		memcpy( m[0], &i_m[0], SZMREAL( 2)); m[0][2] = 0.;
		memcpy( m[1], &i_m[2], SZMREAL( 2)); m[1][2] = 0.;
		memcpy( m[2], &i_m[4], SZMREAL( 2)); m[2][2] = 1.;}
	void SetUnit();																// �P�ʍs���ݒ肷��
	friend MgMat2E operator + ( const MgMat2E& m1, const MgMat2E& m2);			// +
	friend MgMat2E operator += ( MgMat2E&, const MgMat2E&);						// +=
	friend MgMat2E operator - ( const MgMat2E&);								// -
	friend MgMat2E operator - ( const MgMat2E&, const MgMat2E&);				// -
	friend MgMat2E operator -= ( MgMat2E&, const MgMat2E&);						// -=
	friend MgMat2E operator * ( const MgMat2E&, const MgMat2E&);				// *
	friend MgMat2E operator *= ( MgMat2E&, const MgMat2E&);						// *=

	friend MgMat2E operator + ( const MgMat2E &Mat, const MgVect2& Pt);			// +	���s�ړ�
	friend MgMat2E operator + ( const MgMat2E &Mat, const MgPoint2& Pt)			// +	���s�ړ�
						{ return Mat + (MgVect2&)Pt;}
	friend MgMat2E operator += ( MgMat2E &Mat, const MgVect2& Pt);				// +=	���s�ړ�
	friend MgMat2E operator += ( MgMat2E &Mat, const MgPoint2& Pt)				// +=	���s�ړ�
						{ return Mat += (MgVect2&)Pt;}

	friend MgMat2E operator - ( const MgMat2E &Mat, const MgVect2& Pt);			// -	���s�ړ�
	friend MgMat2E operator - ( const MgMat2E &Mat, const MgPoint2& Pt)			// -	���s�ړ�
						{ return Mat - (MgVect2&)Pt;}
	friend MgMat2E operator -= ( MgMat2E &Mat, const MgVect2& Pt);				// -=	���s�ړ�
	friend MgMat2E operator -= ( MgMat2E &Mat, const MgPoint2& Pt)				// -=	���s�ړ�
						{ return Mat -= (MgVect2&)Pt;}
//	�Q�c
	friend MgVect2 operator * ( const MgVect2& v, const MgMat2E& Mat);			// *	���W�ϊ�
	friend MgPoint2 operator * ( const MgPoint2& Pt, const MgMat2E& Mat)		// *	���W�ϊ�
						{ return (MgPoint2&)((MgVect2&)Pt * Mat);}

	friend MgVect2 operator *= ( MgVect2& V, const MgMat2E& Mat);				// *=	���W�ϊ�
	friend MgPoint2 operator *= ( MgPoint2& Pt, const MgMat2E& Mat)				// *=	���W�ϊ�
						{ return (MgPoint2&)((MgVect2&)Pt *= Mat);}

	friend MgULine2 operator * ( const MgULine2&, const MgMat2E&);				// *	���W�ϊ�
	friend MgULine2 operator *= ( MgULine2&, const MgMat2E&);					// *=	���W�ϊ�

	friend MgLine2 operator * ( const MgLine2& Ln1, const MgMat2E &Mat);		// *	���W�ϊ�
	friend MgLine2 operator *= ( MgLine2& Ln, const MgMat2E &Mat);				// *=	���W�ϊ�
//	�R�c
	friend MgVect3 operator * ( const MgVect3& Vt, const MgMat2E& Mat);			// *	���W�ϊ�
	friend MgPoint3 operator * ( const MgPoint3& Pt, const MgMat2E& Mat)		// *	���W�ϊ�
						{ return (MgPoint3&)((MgVect3&)Pt * Mat);}

	friend MgVect3 operator *= ( MgVect3& Vt, const MgMat2E& Mat);				// *=	���W�ϊ�
	friend MgPoint3 operator *= ( MgPoint3& Pt, const MgMat2E& Mat)				// *=	���W�ϊ�
						{ return (MgPoint3&)((MgVect3&)Pt *= Mat);}

	friend MgULine3 operator * ( const MgULine3&, const MgMat2E&);				// *	���W�ϊ�
	friend MgULine3 operator *= ( MgULine3&, const MgMat2E&);					// *=	���W�ϊ�

	friend MgLine3 operator * ( const MgLine3& Ln1, const MgMat2E &Mat);		// *	���W�ϊ�
	friend MgLine3 operator *= ( MgLine3& Ln, const MgMat2E &Mat);				// *=	���W�ϊ�
//
	void Print( MCHAR* s);														// print
	void MgMatPrint2(MCHAR* s);
};

inline	MgMat2E operator += ( MgMat2E &m1, const MgVect2& Pt)					// +=	���s�ړ�
						{ m1.m[2][0] += Pt.x; m1.m[2][1] += Pt.y;
						  return m1;}
inline	MgMat2E operator + ( const MgMat2E &m1, const MgVect2& Pt)				// +	���s�ړ�
						{ MgMat2E mw = m1; mw += Pt; return mw;}
inline	MgMat2E operator -= ( MgMat2E &m1, const MgVect2& Pt)					// -=	���s�ړ�
						{ m1.m[2][0] -= Pt.x; m1.m[2][1] -= Pt.y;}
inline	MgMat2E operator - ( const MgMat2E &m1, const MgVect2& Pt)				// -	���s�ړ�
						{ MgMat2E mw = m1; mw -= Pt; return mw;}
inline	MgLine2 operator * ( const MgLine2& Ln1, const MgMat2E& m2)				// *	���W�ϊ�
						{ MgLine2 Ln;
						  Ln.p[0] = Ln1.p[0] * m2; Ln.p[1] = Ln1.p[1] * m2;
						  return Ln;}
inline	MgLine2 operator *= ( MgLine2& Ln, const MgMat2E &m2)					// *=	���W�ϊ�
						{ Ln.p[0] *= m2; Ln.p[1] *= m2;}
inline	MgLine3 operator * ( const MgLine3& Ln1, const MgMat2E &Mat)			// *	���W�ϊ�
						{ MgLine3 Ln;
						  Ln.p[0] = Ln1.p[0] * Mat; Ln.p[1] = Ln1.p[1] * Mat;
						  return Ln;}
inline	MgLine3 operator *= ( MgLine3& Ln, const MgMat2E &Mat)					// *=	���W�ϊ�
						{ Ln.p[0] *= Mat; Ln.p[1] *= Mat;}

inline	void MgMat2E::Print( MCHAR* s)											// print
						{ MgMatPrint2( s);}
//
//======================( �R���� )==============================
//	�R�������W�v�Z�p�S�����}�g���b�N�X
//
class DLL_EXPORT_MAT MgMat3E
{
public:
	MREAL m[4][4];

public:
	MgMat3E() {}
	MgMat3E( MREAL i_m11, MREAL i_m12, MREAL i_m13,
		     MREAL i_m21, MREAL i_m22, MREAL i_m23,
		     MREAL i_m31, MREAL i_m32, MREAL i_m33,
		     MREAL i_m41, MREAL i_m42, MREAL i_m43) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13; m[0][3] = 0.0;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23; m[1][3] = 0.0;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33; m[2][3] = 0.0;
		m[3][0] = i_m41; m[3][1] = i_m42; m[3][2] = i_m43; m[3][3] = 1.0;}
	MgMat3E( MREAL i_m[4][3]) {
		memcpy( m[0], i_m[0], SZMREAL( 3)); m[0][3] = 0.0;
		memcpy( m[1], i_m[1], SZMREAL( 3)); m[1][3] = 0.0;
		memcpy( m[2], i_m[2], SZMREAL( 3)); m[2][3] = 0.0;
		memcpy( m[3], i_m[3], SZMREAL( 3)); m[3][3] = 1.0;}
	MgMat3E( MREAL i_m[16]) {
		memcpy( m[0], &i_m[0], SZMREAL( 3)); m[0][3] = 0.0;
		memcpy( m[1], &i_m[3], SZMREAL( 3)); m[1][3] = 0.0;
		memcpy( m[2], &i_m[6], SZMREAL( 3)); m[2][3] = 0.0;
		memcpy( m[3], &i_m[9], SZMREAL( 3)); m[3][3] = 1.0;}
	MgMat3E( MgVect3 i_V1, MgVect3 i_V2, MgVect3 i_V3) {
		m[0][0] = i_V1.x; m[0][1] = i_V2.x; m[0][2] = i_V3.x; m[0][3] = 0.0;
		m[1][0] = i_V1.y; m[1][1] = i_V2.y; m[1][2] = i_V3.y; m[1][3] = 0.0;
		m[2][0] = i_V1.z; m[2][1] = i_V2.z; m[2][2] = i_V3.z; m[2][3] = 0.0;
		m[3][0] = 0.0;	  m[3][1] = 0.0;	m[3][2] = 0.0;	  m[3][3] = 1.0;}
	void SetUnit();																// �P�ʍs���ݒ肷��
	friend MgMat3E operator + ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator += ( MgMat3E&, const MgMat3E&);
	friend MgMat3E operator - ( const MgMat3E&);
	friend MgMat3E operator - ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator -= ( MgMat3E&, const MgMat3E&);
	friend MgMat3E operator * ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator *= ( MgMat3E&, const MgMat3E&);

	friend MgMat3E operator + ( const MgMat3E &Mat, const MgVect3& Pt);			// +	���s�ړ�
	friend MgMat3E operator + ( const MgMat3E &Mat, const MgPoint3& Pt)			// +	���s�ړ�
							{ return Mat + (MgVect3&)Pt;}

	friend MgMat3E operator += ( MgMat3E &Mat, const MgVect3& Pt);				// +=	���s�ړ�
	friend MgMat3E operator += ( MgMat3E &Mat, const MgPoint3& Pt)				// +=	���s�ړ�
							{ return Mat +=(MgVect3&)Pt;}

	friend MgMat3E operator - ( const MgMat3E &Mat, const MgVect3& Pt);			// -	���s�ړ�
	friend MgMat3E operator - ( const MgMat3E &Mat, const MgPoint3& Pt)			// -	���s�ړ�
							{ return Mat - (MgVect3&)Pt;}

	friend MgMat3E operator -= ( MgMat3E &Mat, const MgVect3& Pt);				// -=	���s�ړ�
	friend MgMat3E operator -= ( MgMat3E &Mat, const MgPoint3& Pt)				// -=	���s�ړ�
							{ return Mat -=(MgVect3&)Pt;}

	friend MgVect2 operator * ( const MgVect2& Vt, const MgMat3E& Mat);			// *	���W�ϊ�
	friend MgPoint2 operator * ( const MgPoint2& Pt, const MgMat3E& Mat)		// *	���W�ϊ�
							{ return (MgPoint2&)((MgVect2&)Pt * Mat);}

	friend MgVect2 operator *= ( MgVect2& Vt, const MgMat3E& Mat);				// *=	���W�ϊ�
	friend MgPoint2 operator *= ( MgPoint2& Pt, const MgMat3E& Mat)				// *=	���W�ϊ�
							{ return (MgPoint2&)((MgVect2&)Pt *= Mat);}

	friend MgVect3 operator * ( const MgVect3& Vt, const MgMat3E& Mat);			// *	���W�ϊ�
	friend MgPoint3 operator * ( const MgPoint3& Pt, const MgMat3E& Mat)		// *	���W�ϊ�
							{ return (MgPoint3&)((MgVect3&)Pt * Mat);}

	friend MgVect3 operator *= ( MgVect3& Vt, const MgMat3E& Mat);				// *=	���W�ϊ�
	friend MgPoint3 operator *= ( MgPoint3& Pt, const MgMat3E& Mat)				// *=	���W�ϊ�
							{ return (MgPoint3&)((MgVect3&)Pt *= Mat);}

	friend MgULine3 operator * ( const MgULine3& uL, const MgMat3E& Mat);		// *	���W�ϊ�
	friend MgULine3 operator *= ( MgULine3& uL, const MgMat3E& Mat);			// *=	���W�ϊ�

	friend MgLine3 operator * ( const MgLine3& Ln, const MgMat3E& Mat);			// *	���W�ϊ�
	friend MgLine3 operator *= ( MgLine3& Ln, const MgMat3E& Mat);				// *=	���W�ϊ�
//
	void Print( MCHAR* s);														// print
	void MgMatPrint3(MCHAR* s);
};

inline MgMat3E operator += ( MgMat3E &m1, const MgVect3& Pt)					// +=	���s�ړ�
						{ m1.m[3][0] += Pt.x; m1.m[3][1] += Pt.y;
						  m1.m[3][2] += Pt.z; return m1;} 
inline MgMat3E operator + ( const MgMat3E &m1, const MgVect3& Pt)				// +	���s�ړ�
						{ MgMat3E mw = m1; mw += Pt; return mw;}
inline MgMat3E operator -= ( MgMat3E &m1, const MgVect3& Pt)					// -=	���s�ړ�
						{ m1.m[3][0] -= Pt.x; m1.m[3][1] -= Pt.y;
						  m1.m[3][2] -= Pt.z; return m1;} 
inline MgMat3E operator - ( const MgMat3E &m1, const MgVect3& Pt)				// -	���s�ړ�
						{ MgMat3E mw = m1; mw -= Pt; return mw;}
inline MgLine3 operator * ( const MgLine3& Ln1, const MgMat3E &m2)				// ���W�ϊ�
						{ MgLine3 Ln; Ln.p[0] = Ln1.p[0] * m2;
						  Ln.p[1] = Ln1.p[1] * m2; return Ln;}
inline MgLine3 operator *= ( MgLine3& Ln1, const MgMat3E &m2)					// ���W�ϊ�
						{ Ln1.p[0] *= m2; Ln1.p[1] *= m2;}
inline	void MgMat3E::Print( MCHAR* s)											// print
						{ MgMatPrint3( s);}

} // namespace MC