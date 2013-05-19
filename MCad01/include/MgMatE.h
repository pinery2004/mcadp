#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgMatD.h
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
class MgGPoint2D;
class MgGPoint3D;
class MgPolyg2D;
class MgGPolyg2D;
class MgGPolyg3D;
class MgGLine2D;
class MgGLine3D;

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
	MREAL m[3][2];
//
public:
	MgMat2E() {}
	MgMat2E( MREAL i_m11, MREAL i_m12,
		    MREAL i_m21, MREAL i_m22,
		    MREAL i_m31, MREAL i_m32) {
		m[0][0] = i_m11; m[0][1] = i_m12;
		m[1][0] = i_m21; m[1][1] = i_m22;
		m[2][0] = i_m31; m[2][1] = i_m32;}
	MgMat2E( MREAL i_m[3][2]) {
		memcpy_s( &m[0][0], 6*sizeof(MREAL), &i_m[0][0], 6*sizeof(MREAL));}
	MgMat2E( MREAL i_m[6]) {
		memcpy_s( &m[0][0], 6*sizeof(MREAL), i_m, 6*sizeof(MREAL));}
	void SetUnit();																// �P�ʍs���ݒ肷��
	friend MgMat2E operator +  ( const MgMat2E& m1, const MgMat2E& m2);			// +
	friend MgMat2E operator += ( MgMat2E& m1,		const MgMat2E& m2);			// +=
	friend MgMat2E operator -  ( const MgMat2E& m1);							// -
	friend MgMat2E operator -  ( const MgMat2E& m1, const MgMat2E& m2);			// -
	friend MgMat2E operator -= ( MgMat2E& m1,		const MgMat2E& m2);			// -=
	friend MgMat2E operator *  ( const MgMat2E& m1, const MgMat2E& m2);			// *
	friend MgMat2E operator *= ( MgMat2E& m1,		const MgMat2E& m2);			// *=

	friend MgMat2E operator +  ( const MgMat2E& m1, const MgVect2D& v);			// +	���s�ړ�
	friend MgMat2E operator +  ( const MgMat2E& m1, const MgPoint2D& pt);		// +	���s�ړ�	//E
	friend MgMat2E operator += ( MgMat2E& m1,		const MgVect2D& v);			// +=	���s�ړ�
	friend MgMat2E operator += ( MgMat2E& m1,		const MgPoint2D& pt);		// +=	���s�ړ�	//E
	friend MgMat2E operator -  ( const MgMat2E& m1, const MgVect2D& v);			// -	���s�ړ�
	friend MgMat2E operator -  ( const MgMat2E& m1, const MgPoint2D& pt);		// -	���s�ړ�	//E
	friend MgMat2E operator -= ( MgMat2E& m1, const MgVect2D& v);				// -=	���s�ړ�
	friend MgMat2E operator -= ( MgMat2E& m1, const MgPoint2D& pt);				// -=	���s�ړ�	//E

	//	�Q�c
	friend MgPoint2D operator * ( const MgPoint2D& pt,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgVect2D  operator * ( const MgVect2D& v,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgLine2D  operator * ( const MgLine2D& ln,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgULine2D operator * ( const MgULine2D& uln, const MgMat2E& m1);		// *	���W�ϊ�

	friend MgPoint2D operator *= ( MgPoint2D& pt,		const MgMat2E& m1);		// *=	���W�ϊ�
	friend MgVect2D  operator *= ( MgVect2D& v,			const MgMat2E& m1);		// *=	���W�ϊ�
	friend MgLine2D  operator *= ( MgLine2D& ln,		const MgMat2E& m1);		// *=	���W�ϊ�
	friend MgULine2D operator *= ( MgULine2D& uln,		const MgMat2E& m1);		// *=	���W�ϊ�
	//	�R�c
	friend MgPoint3D operator * ( const MgPoint3D& Pt,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgVect3D  operator * ( const MgVect3D& V,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgLine3D  operator * ( const MgLine3D& Ln,	const MgMat2E& m1);		// *	���W�ϊ�
	friend MgULine3D operator * ( const MgULine3D& ULn,	const MgMat2E& m1);		// *	���W�ϊ�

	friend MgPoint3D operator *= ( MgPoint3D& Pt,		const MgMat2E& Mat);	// *=	���W�ϊ�
	friend MgVect3D  operator *= ( MgVect3D& V,			const MgMat2E& Mat);	// *=	���W�ϊ�
	friend MgLine3D operator  *= ( MgLine3D& Ln,		const MgMat2E &Mat);	// *=	���W�ϊ�
	friend MgULine3D operator *= ( MgULine3D& ULn,		const MgMat2E& Mat);	// *=	���W�ϊ�

	void Print( MCHAR* s);														// print
	void MgMatPrint2(MCHAR* s);
};


//======================( �R���� )==============================
//	�R�������W�v�Z�p�S�����}�g���b�N�X
//
class DLL_EXPORT_MAT MgMat3E
{
public:
	MREAL m[4][3];

public:
	MgMat3E() {}
	MgMat3E( MREAL i_m11, MREAL i_m12, MREAL i_m13,
		      MREAL i_m21, MREAL i_m22, MREAL i_m23,
		      MREAL i_m31, MREAL i_m32, MREAL i_m33,
		      MREAL i_m41, MREAL i_m42, MREAL i_m43) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33;
		m[3][0] = i_m41; m[3][1] = i_m42; m[3][2] = i_m43;}
	MgMat3E( MREAL i_m[4][3]) {
		memcpy_s( &m[0][0], 6*sizeof(MREAL), &i_m[0][0], 6*sizeof(MREAL));}
	MgMat3E( MREAL i_m[12]) {
		memcpy_s( &m[0][0], 12*sizeof(MREAL), i_m, 12*sizeof(MREAL));}
	MgMat3E( MgVect3D i_V1, MgVect3D i_V2, MgVect3D i_V3) {
		m[0][0] = i_V1.x; m[0][1] = i_V2.x; m[0][2] = i_V3.x;
		m[1][0] = i_V1.y; m[1][1] = i_V2.y; m[1][2] = i_V3.y;
		m[2][0] = i_V1.z; m[2][1] = i_V2.z; m[2][2] = i_V3.z;
		m[3][0] = 0.0;	  m[3][1] = 0.0;	m[3][2] = 0.0;}
	void SetUnit();																// �P�ʍs���ݒ肷��
	friend MgMat3E operator +  ( const MgMat3E& M1, const MgMat3E& M2);			// +
	friend MgMat3E operator += ( MgMat3E& M1,		const MgMat3E& M2);			// +=
	friend MgMat3E operator -  ( const MgMat3E& M1);							// -
	friend MgMat3E operator -  ( const MgMat3E& M1, const MgMat3E& M2);			// -
	friend MgMat3E operator -= ( MgMat3E& M1,		const MgMat3E& M2);			// -=
	friend MgMat3E operator *  ( const MgMat3E& M1, const MgMat3E& M2);			// *
	friend MgMat3E operator *= ( MgMat3E& M1,		const MgMat3E& M2);			// *=

	friend MgMat3E operator +  ( const MgMat3E& M1, const MgVect3D& Vt);		// +	���s�ړ�
	friend MgMat3E operator +  ( const MgMat3E& M1, const MgPoint3D& Pt);		// +	���s�ړ�
	friend MgMat3E operator += ( MgMat3E& M1,		const MgVect3D& Vt);		// +=	���s�ړ�
	friend MgMat3E operator += ( MgMat3E& M1,		const MgPoint3D& Pt);		// +=	���s�ړ�
	friend MgMat3E operator -  ( const MgMat3E& M1, const MgVect3D& Vt);		// -	���s�ړ�
	friend MgMat3E operator -  ( const MgMat3E& M1, const MgPoint3D& Pt);		// -	���s�ړ�
	friend MgMat3E operator -= ( MgMat3E& M1,		const MgVect3D& Vt);		// -=	���s�ړ�
	friend MgMat3E operator -= ( MgMat3E& M1,		const MgPoint3D& Pt);		// -=	���s�ړ�
	//	�Q�c
	friend MgPoint2D operator *  ( const MgPoint2D& Pt, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgVect2D operator  *  ( const MgVect2D& Vt, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgULine2D operator *  ( const MgULine2D& uL, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgLine2D operator  *  ( const MgLine2D& Ln, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgPoint2D operator *= ( MgPoint2D& Pt, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgVect2D operator  *= ( MgVect2D& Vt, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgULine2D operator *= ( MgULine2D& uL, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgLine2D operator  *= ( MgLine2D& Ln, const MgMat3E& M1);			// *=	���W�ϊ�
	//	�R�c
	friend MgPoint3D operator *  ( const MgPoint3D& Pt, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgVect3D operator  *  ( const MgVect3D& Vt, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgULine3D operator *  ( const MgULine3D& uL, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgLine3D operator  *  ( const MgLine3D& Ln, const MgMat3E& M1);		// *	���W�ϊ�
	friend MgPoint3D operator *= ( MgPoint3D& Pt, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgVect3D operator  *= ( MgVect3D& Vt, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgULine3D operator *= ( MgULine3D& uL, const MgMat3E& M1);			// *=	���W�ϊ�
	friend MgLine3D operator  *= ( MgLine3D& Ln, const MgMat3E& M1);			// *=	���W�ϊ�

	void Print( MCHAR* s);														// print
	void MgMatPrint3(MCHAR* s);
};

inline	void MgMat3E::Print( MCHAR* s)											// print
{
#ifdef LOGOUT
	MgMatPrint3( s);
#endif
}

} // namespace MC
