#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgMat.h
//
//		マトリックス
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
	#pragma message( "<<< MgMat・dll_EXport >>>")
	#define DLL_EXPORT_MAT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_MAT
		#else
//			#pragma message( "=== MgMat・dll_IMport ===")
			#define DLL_EXPORT_MAT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_MAT
	#endif
#endif

namespace MC
{

//
//======================( ２次元 )==============================
//	２次元座標計算用３次元マトリックス
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
	void SetUnit();																// 単位行列を設定する
	friend MgMat2E operator + ( const MgMat2E& m1, const MgMat2E& m2);		// +
	friend MgMat2E operator += ( MgMat2E&, const MgMat2E&);					// +=
	friend MgMat2E operator - ( const MgMat2E&);								// -
	friend MgMat2E operator - ( const MgMat2E&, const MgMat2E&);				// -
	friend MgMat2E operator -= ( MgMat2E&, const MgMat2E&);					// -=
	friend MgMat2E operator * ( const MgMat2E&, const MgMat2E&);				// *
	friend MgMat2E operator *= ( MgMat2E&, const MgMat2E&);					// *=

	friend MgMat2E operator + ( const MgMat2E &Mat, const MgVect2D& Pt);		// +	平行移動
	friend MgMat2E operator + ( const MgMat2E &Mat, const MgPoint2D& Pt)		// +	平行移動
						{ return Mat + (MgVect2D&)Pt;}
	friend MgMat2E operator += ( MgMat2E &Mat, const MgVect2D& Pt);			// +=	平行移動
	friend MgMat2E operator += ( MgMat2E &Mat, const MgPoint2D& Pt)			// +=	平行移動
						{ return Mat += (MgVect2D&)Pt;}

	friend MgMat2E operator - ( const MgMat2E &Mat, const MgVect2D& Pt);		// -	平行移動
	friend MgMat2E operator - ( const MgMat2E &Mat, const MgPoint2D& Pt)		// -	平行移動
						{ return Mat - (MgVect2D&)Pt;}
	friend MgMat2E operator -= ( MgMat2E &Mat, const MgVect2D& Pt);			// -=	平行移動
	friend MgMat2E operator -= ( MgMat2E &Mat, const MgPoint2D& Pt)			// -=	平行移動
						{ return Mat -= (MgVect2D&)Pt;}
//	２Ｄ
	friend MgVect2D operator * ( const MgVect2D& v, const MgMat2E& Mat);		// *	座標変換
	friend MgPoint2D operator * ( const MgPoint2D& Pt, const MgMat2E& Mat)		// *	座標変換
						{ return (MgPoint2D&)((MgVect2D&)Pt * Mat);}

	friend MgVect2D operator *= ( MgVect2D& V, const MgMat2E& Mat);			// *=	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt, const MgMat2E& Mat)			// *=	座標変換
						{ return (MgPoint2D&)((MgVect2D&)Pt *= Mat);}

	friend MgULine2D operator * ( const MgULine2D&, const MgMat2E&);			// *	座標変換
	friend MgULine2D operator *= ( MgULine2D&, const MgMat2E&);				// *=	座標変換

	friend MgLine2D operator * ( const MgLine2D& Ln1, const MgMat2E &Mat);		// *	座標変換
	friend MgLine2D operator *= ( MgLine2D& Ln, const MgMat2E &Mat);			// *=	座標変換
//	３Ｄ
	friend MgVect3D operator * ( const MgVect3D& Vt, const MgMat2E& Mat);		// *	座標変換
	friend MgPoint3D operator * ( const MgPoint3D& Pt, const MgMat2E& Mat)		// *	座標変換
						{ return (MgPoint3D&)((MgVect3D&)Pt * Mat);}

	friend MgVect3D operator *= ( MgVect3D& Vt, const MgMat2E& Mat);			// *=	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt, const MgMat2E& Mat)			// *=	座標変換
						{ return (MgPoint3D&)((MgVect3D&)Pt *= Mat);}

	friend MgULine3D operator * ( const MgULine3D&, const MgMat2E&);			// *	座標変換
	friend MgULine3D operator *= ( MgULine3D&, const MgMat2E&);				// *=	座標変換

	friend MgLine3D operator * ( const MgLine3D& Ln1, const MgMat2E &Mat);		// *	座標変換
	friend MgLine3D operator *= ( MgLine3D& Ln, const MgMat2E &Mat);			// *=	座標変換
//
	void Print( MCHAR* s);														// print
	void MgMatPrint2(MCHAR* s);
};

inline	MgMat2E operator += ( MgMat2E &m1, const MgVect2D& Pt)				// +=	平行移動
						{ m1.m[2][0] += Pt.x; m1.m[2][1] += Pt.y;
						  return m1;}
inline	MgMat2E operator + ( const MgMat2E &m1, const MgVect2D& Pt)			// +	平行移動
						{ MgMat2E mw = m1; mw += Pt; return mw;}
inline	MgMat2E operator -= ( MgMat2E &m1, const MgVect2D& Pt)				// -=	平行移動
						{ m1.m[2][0] -= Pt.x; m1.m[2][1] -= Pt.y;}
inline	MgMat2E operator - ( const MgMat2E &m1, const MgVect2D& Pt)			// -	平行移動
						{ MgMat2E mw = m1; mw -= Pt; return mw;}
inline	MgLine2D operator * ( const MgLine2D& Ln1, const MgMat2E& m2)			// *	座標変換
						{ MgLine2D Ln;
						  Ln.p[0] = Ln1.p[0] * m2; Ln.p[1] = Ln1.p[1] * m2;
						  return Ln;}
inline	MgLine2D operator *= ( MgLine2D& Ln, const MgMat2E &m2)				// *=	座標変換
						{ Ln.p[0] *= m2; Ln.p[1] *= m2;}
inline	MgLine3D operator * ( const MgLine3D& Ln1, const MgMat2E &Mat)			// *	座標変換
						{ MgLine3D Ln;
						  Ln.p[0] = Ln1.p[0] * Mat; Ln.p[1] = Ln1.p[1] * Mat;
						  return Ln;}
inline	MgLine3D operator *= ( MgLine3D& Ln, const MgMat2E &Mat)				// *=	座標変換
						{ Ln.p[0] *= Mat; Ln.p[1] *= Mat;}

inline	void MgMat2E::Print( MCHAR* s)											// print
						{
#ifdef LOGOUT
							MgMatPrint2( s);
#endif
						}
//
//======================( ３次元 )==============================
//	３次元座標計算用４次元マトリックス
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
	MgMat3E( MgVect3D i_V1, MgVect3D i_V2, MgVect3D i_V3) {
		m[0][0] = i_V1.x; m[0][1] = i_V2.x; m[0][2] = i_V3.x; m[0][3] = 0.0;
		m[1][0] = i_V1.y; m[1][1] = i_V2.y; m[1][2] = i_V3.y; m[1][3] = 0.0;
		m[2][0] = i_V1.z; m[2][1] = i_V2.z; m[2][2] = i_V3.z; m[2][3] = 0.0;
		m[3][0] = 0.0;	  m[3][1] = 0.0;	m[3][2] = 0.0;	  m[3][3] = 1.0;}
	void SetUnit();																// 単位行列を設定する
	friend MgMat3E operator + ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator += ( MgMat3E&, const MgMat3E&);
	friend MgMat3E operator - ( const MgMat3E&);
	friend MgMat3E operator - ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator -= ( MgMat3E&, const MgMat3E&);
	friend MgMat3E operator * ( const MgMat3E&, const MgMat3E&);
	friend MgMat3E operator *= ( MgMat3E&, const MgMat3E&);

	friend MgMat3E operator + ( const MgMat3E &Mat, const MgVect3D& Pt);		// +	平行移動
	friend MgMat3E operator + ( const MgMat3E &Mat, const MgPoint3D& Pt)		// +	平行移動
							{ return Mat + (MgVect3D&)Pt;}

	friend MgMat3E operator += ( MgMat3E &Mat, const MgVect3D& Pt);			// +=	平行移動
	friend MgMat3E operator += ( MgMat3E &Mat, const MgPoint3D& Pt)			// +=	平行移動
							{ return Mat +=(MgVect3D&)Pt;}

	friend MgMat3E operator - ( const MgMat3E &Mat, const MgVect3D& Pt);		// -	平行移動
	friend MgMat3E operator - ( const MgMat3E &Mat, const MgPoint3D& Pt)		// -	平行移動
							{ return Mat - (MgVect3D&)Pt;}

	friend MgMat3E operator -= ( MgMat3E &Mat, const MgVect3D& Pt);			// -=	平行移動
	friend MgMat3E operator -= ( MgMat3E &Mat, const MgPoint3D& Pt)			// -=	平行移動
							{ return Mat -=(MgVect3D&)Pt;}

	friend MgVect2D operator * ( const MgVect2D& Vt, const MgMat3E& Mat);		// *	座標変換
	friend MgPoint2D operator * ( const MgPoint2D& Pt, const MgMat3E& Mat)		// *	座標変換
							{ return (MgPoint2D&)((MgVect2D&)Pt * Mat);}

	friend MgVect2D operator *= ( MgVect2D& Vt, const MgMat3E& Mat);			// *=	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt, const MgMat3E& Mat)			// *=	座標変換
							{ return (MgPoint2D&)((MgVect2D&)Pt *= Mat);}

	friend MgVect3D operator * ( const MgVect3D& Vt, const MgMat3E& Mat);		// *	座標変換
	friend MgPoint3D operator * ( const MgPoint3D& Pt, const MgMat3E& Mat)		// *	座標変換
							{ return (MgPoint3D&)((MgVect3D&)Pt * Mat);}

	friend MgVect3D operator *= ( MgVect3D& Vt, const MgMat3E& Mat);			// *=	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt, const MgMat3E& Mat)			// *=	座標変換
							{ return (MgPoint3D&)((MgVect3D&)Pt *= Mat);}

	friend MgULine3D operator * ( const MgULine3D& uL, const MgMat3E& Mat);	// *	座標変換
	friend MgULine3D operator *= ( MgULine3D& uL, const MgMat3E& Mat);			// *=	座標変換

	friend MgLine3D operator * ( const MgLine3D& Ln, const MgMat3E& Mat);		// *	座標変換
	friend MgLine3D operator *= ( MgLine3D& Ln, const MgMat3E& Mat);			// *=	座標変換
//
	void Print( MCHAR* s);														// print
	void MgMatPrint3(MCHAR* s);
};

inline MgMat3E operator += ( MgMat3E &m1, const MgVect3D& Pt)					// +=	平行移動
						{ m1.m[3][0] += Pt.x; m1.m[3][1] += Pt.y;
						  m1.m[3][2] += Pt.z; return m1;} 
inline MgMat3E operator + ( const MgMat3E &m1, const MgVect3D& Pt)			// +	平行移動
						{ MgMat3E mw = m1; mw += Pt; return mw;}
inline MgMat3E operator -= ( MgMat3E &m1, const MgVect3D& Pt)					// -=	平行移動
						{ m1.m[3][0] -= Pt.x; m1.m[3][1] -= Pt.y;
						  m1.m[3][2] -= Pt.z; return m1;} 
inline MgMat3E operator - ( const MgMat3E &m1, const MgVect3D& Pt)			// -	平行移動
						{ MgMat3E mw = m1; mw -= Pt; return mw;}
inline MgLine3D operator * ( const MgLine3D& Ln1, const MgMat3E &m2)			// 座標変換
						{ MgLine3D Ln; Ln.p[0] = Ln1.p[0] * m2;
						  Ln.p[1] = Ln1.p[1] * m2; return Ln;}
inline MgLine3D operator *= ( MgLine3D& Ln1, const MgMat3E &m2)				// 座標変換
						{ Ln1.p[0] *= m2; Ln1.p[1] *= m2;}
inline	void MgMat3E::Print( MCHAR* s)											// print
						{
#ifdef LOGOUT
							MgMatPrint3( s);
#endif
						}

} // namespace MC
