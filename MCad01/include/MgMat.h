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

class MgMat3DE;
class MgGPoint2D;
class MgGPoint3D;
class MgPolyg2D;
class MgGPolyg2D;
class MgGPolyg3D;
class MgGLine2D;
class MgGLine3D;

#include "mdPlex.h"

#include "MgMatE.h"

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
//======================( ３Ｄ )==============================
//	３Ｄマトリックス
class DLL_EXPORT_MAT MgMat3D
{
public:
	MREAL m[3][3];
//
public:
	MgMat3D() {}
	MgMat3D( MREAL i_m11, MREAL i_m12, MREAL i_m13,
		    MREAL i_m21, MREAL i_m22, MREAL i_m23,
		    MREAL i_m31, MREAL i_m32, MREAL i_m33) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33;}
	MgMat3D( MREAL i_m[3][3]) {
		memcpy( m, i_m[0], SZMREAL( 9));}
	MgMat3D( MREAL i_m[9]) {
		memcpy( m, i_m, SZMREAL( 9));}
	void SetUnit();																// 単位行列を設定する
	friend MgMat3D operator + ( const MgMat3D& m1, const MgMat3D& m2);			// +
	friend MgMat3D operator += ( MgMat3D&, const MgMat3D&);						// +=
	friend MgMat3D operator - ( const MgMat3D&);								// -
	friend MgMat3D operator - ( const MgMat3D&, const MgMat3D&);				// -
	friend MgMat3D operator -= ( MgMat3D&, const MgMat3D&);						// -=
	friend MgMat3D operator * ( const MgMat3D&, const MgMat3D&);				// *
	friend MgMat3D operator *= ( MgMat3D&, const MgMat3D&);						// *=

	friend MgMat3D operator + ( const MgMat3D &Mat, const MgVect2D& Pt);		// +	平行移動
	friend MgMat3D operator + ( const MgMat3D &Mat, const MgPoint2D& Pt)		// +	平行移動
						{ return Mat + (MgVect2D&)Pt;}
	friend MgMat3D operator += ( MgMat3D &Mat, const MgVect2D& Pt);				// +=	平行移動
	friend MgMat3D operator += ( MgMat3D &Mat, const MgPoint2D& Pt)				// +=	平行移動
						{ return Mat += (MgVect2D&)Pt;}

	friend MgMat3D operator - ( const MgMat3D &Mat, const MgVect2D& Pt);		// -	平行移動
	friend MgMat3D operator - ( const MgMat3D &Mat, const MgPoint2D& Pt)		// -	平行移動
						{ return Mat - (MgVect2D&)Pt;}
	friend MgMat3D operator -= ( MgMat3D &Mat, const MgVect2D& Pt);				// -=	平行移動
	friend MgMat3D operator -= ( MgMat3D &Mat, const MgPoint2D& Pt)				// -=	平行移動
						{ return Mat -= (MgVect2D&)Pt;}
//	２Ｄ
	friend MgVect2D operator * ( const MgVect2D& v, const MgMat3D& Mat);		// *	座標変換
	friend MgPoint2D operator * ( const MgPoint2D& Pt, const MgMat3D& Mat)		// *	座標変換
						{ return (MgPoint2D&)((MgVect2D&)Pt * Mat);}

	friend MgVect2D operator *= ( MgVect2D& V, const MgMat3D& Mat);				// *=	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt, const MgMat3D& Mat)			// *=	座標変換
						{ return (MgPoint2D&)((MgVect2D&)Pt *= Mat);}

	friend MgULine2D operator * ( const MgULine2D&, const MgMat3D&);			// *	座標変換
	friend MgULine2D operator *= ( MgULine2D&, const MgMat3D&);					// *=	座標変換

	friend MgLine2D operator * ( const MgLine2D& Ln1, const MgMat3D &Mat);		// *	座標変換
	friend MgLine2D operator *= ( MgLine2D& Ln, const MgMat3D &Mat);			// *=	座標変換
//	３Ｄ
	friend MgVect3D operator * ( const MgVect3D& Vt, const MgMat3D& Mat);		// *	座標変換
	friend MgPoint3D operator * ( const MgPoint3D& Pt, const MgMat3D& Mat)		// *	座標変換
						{ return (MgPoint3D&)((MgVect3D&)Pt * Mat);}

	friend MgVect3D operator *= ( MgVect3D& Vt, const MgMat3D& Mat);			// *=	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt, const MgMat3D& Mat)			// *=	座標変換
						{ return (MgPoint3D&)((MgVect3D&)Pt *= Mat);}

	friend MgULine3D operator * ( const MgULine3D&, const MgMat3D&);			// *	座標変換
	friend MgULine3D operator *= ( MgULine3D&, const MgMat3D&);					// *=	座標変換

	friend MgLine3D operator * ( const MgLine3D& Ln1, const MgMat3D &Mat);		// *	座標変換
	friend MgLine3D operator *= ( MgLine3D& Ln, const MgMat3D &Mat);			// *=	座標変換
//
	void Print( MCHAR* s);														// print
	void MgMatPrint3(MCHAR* s);
};

inline	MgMat3D operator += ( MgMat3D &m1, const MgVect2D& Pt)					// +=	平行移動
						{ m1.m[2][0] += Pt.x; m1.m[2][1] += Pt.y;
						  return m1;}
inline	MgMat3D operator + ( const MgMat3D &m1, const MgVect2D& Pt)				// +	平行移動
						{ MgMat3D mw = m1; mw += Pt; return mw;}
inline	MgMat3D operator -= ( MgMat3D &m1, const MgVect2D& Pt)					// -=	平行移動
						{ m1.m[2][0] -= Pt.x; m1.m[2][1] -= Pt.y;}
inline	MgMat3D operator - ( const MgMat3D &m1, const MgVect2D& Pt)				// -	平行移動
						{ MgMat3D mw = m1; mw -= Pt; return mw;}
inline	MgLine2D operator * ( const MgLine2D& Ln1, const MgMat3D& m2)			// *	座標変換
						{ MgLine2D Ln;
						  Ln.p[0] = Ln1.p[0] * m2; Ln.p[1] = Ln1.p[1] * m2;
						  return Ln;}
inline	MgLine2D operator *= ( MgLine2D& Ln, const MgMat3D &m2)					// *=	座標変換
						{ Ln.p[0] *= m2; Ln.p[1] *= m2;}
inline	MgLine3D operator * ( const MgLine3D& Ln1, const MgMat3D &Mat)			// *	座標変換
						{ MgLine3D Ln;
						  Ln.p[0] = Ln1.p[0] * Mat; Ln.p[1] = Ln1.p[1] * Mat;
						  return Ln;}
inline	MgLine3D operator *= ( MgLine3D& Ln, const MgMat3D &Mat)				// *=	座標変換
						{ Ln.p[0] *= Mat; Ln.p[1] *= Mat;}

inline	void MgMat3D::Print( MCHAR* s)											// print
						{
#ifdef LOGOUT
							MgMatPrint3( s);
#endif
						}
//
//======================( ４Ｄ )==============================
//	４Ｄマトリックス
//
class DLL_EXPORT_MAT MgMat4D
{
public:
	MREAL m[4][4];

public:
	MgMat4D() {}
	MgMat4D( MREAL i_m11, MREAL i_m12, MREAL i_m13, MREAL i_m14,
		    MREAL i_m21, MREAL i_m22, MREAL i_m23, MREAL i_m24,
		    MREAL i_m31, MREAL i_m32, MREAL i_m33, MREAL i_m34,
		    MREAL i_m41, MREAL i_m42, MREAL i_m43, MREAL i_m44) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13; m[0][3] = i_m14;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23; m[1][3] = i_m24;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33; m[2][3] = i_m34;
		m[3][0] = i_m41; m[3][1] = i_m42; m[3][2] = i_m43; m[3][3] = i_m44;}
	MgMat4D( MREAL i_m[4][4]) {
		memcpy( m, i_m[0], SZMREAL( 16));}
	MgMat4D( MREAL i_m[16]) {
		memcpy( m, i_m, SZMREAL( 16));}
	MgMat4D( MgVect3D i_V1, MgVect3D i_V2, MgVect3D i_V3) {
		m[0][0] = i_V1.x; m[0][1] = i_V2.x; m[0][2] = i_V3.x; m[0][3] = 0.0;
		m[1][0] = i_V1.y; m[1][1] = i_V2.y; m[1][2] = i_V3.y; m[1][3] = 0.0;
		m[2][0] = i_V1.z; m[2][1] = i_V2.z; m[2][2] = i_V3.z; m[2][3] = 0.0;
		m[3][0] = 0.0;	  m[3][1] = 0.0;	m[3][2] = 0.0;	  m[3][3] = 1.0;}
	void SetUnit();																// 単位行列を設定する
	friend MgMat4D operator + ( const MgMat4D&, const MgMat4D&);
	friend MgMat4D operator += ( MgMat4D&, const MgMat4D&);
	friend MgMat4D operator - ( const MgMat4D&);
	friend MgMat4D operator - ( const MgMat4D&, const MgMat4D&);
	friend MgMat4D operator -= ( MgMat4D&, const MgMat4D&);
	friend MgMat4D operator * ( const MgMat4D&, const MgMat4D&);
	friend MgMat4D operator *= ( MgMat4D&, const MgMat4D&);

	friend MgMat4D operator + ( const MgMat4D &Mat, const MgVect3D& Pt);		// +	平行移動
	friend MgMat4D operator + ( const MgMat4D &Mat, const MgPoint3D& Pt)		// +	平行移動
							{ return Mat + (MgVect3D&)Pt;}

	friend MgMat4D operator += ( MgMat4D &Mat, const MgVect3D& Pt);				// +=	平行移動
	friend MgMat4D operator += ( MgMat4D &Mat, const MgPoint3D& Pt)				// +=	平行移動
							{ return Mat += (MgVect3D&)Pt;}

	friend MgMat4D operator - ( const MgMat4D &Mat, const MgVect3D& Pt);		// -	平行移動
	friend MgMat4D operator - ( const MgMat4D &Mat, const MgPoint3D& Pt)		// -	平行移動
							{ return Mat - (MgVect3D&)Pt;}

	friend MgMat4D operator -= ( MgMat4D &Mat, const MgVect3D& Pt);				// -=	平行移動
	friend MgMat4D operator -= ( MgMat4D &Mat, const MgPoint3D& Pt)				// -=	平行移動
							{ return Mat -= (MgVect3D&)Pt;}

	friend MgVect2D operator * ( const MgVect2D& Vt, const MgMat4D& Mat);		// *	座標変換
	friend MgPoint2D operator * ( const MgPoint2D& Pt, const MgMat4D& Mat)		// *	座標変換
							{ return (MgPoint2D&)((MgVect2D&)Pt * Mat);}

	friend MgVect2D operator *= ( MgVect2D& Vt, const MgMat4D& Mat);			// *=	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt, const MgMat4D& Mat)			// *=	座標変換
							{ return (MgPoint2D&)((MgVect2D&)Pt *= Mat);}

	friend MgVect3D operator * ( const MgVect3D& Vt, const MgMat4D& Mat);		// *	座標変換
	friend MgPoint3D operator * ( const MgPoint3D& Pt, const MgMat4D& Mat)		// *	座標変換
							{ return (MgPoint3D&)((MgVect3D&)Pt * Mat);}

	friend MgVect3D operator *= ( MgVect3D& Vt, const MgMat4D& Mat);			// *=	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt, const MgMat4D& Mat)			// *=	座標変換
							{ return (MgPoint3D&)((MgVect3D&)Pt *= Mat);}

	friend MgULine3D operator * ( const MgULine3D& uL, const MgMat4D& Mat);		// *	座標変換
	friend MgULine3D operator *= ( MgULine3D& uL, const MgMat4D& Mat);			// *=	座標変換

	friend MgLine3D operator * ( const MgLine3D& Ln, const MgMat4D& Mat);		// *	座標変換
	friend MgLine3D operator *= ( MgLine3D& Ln, const MgMat4D& Mat);			// *=	座標変換

	void Print( MCHAR* s);														// print
	void MgMatPrint4(MCHAR* s);
};

inline MgMat4D operator += ( MgMat4D &m1, const MgVect3D& Pt)					// +=	平行移動
						{ m1.m[3][0] += Pt.x; m1.m[3][1] += Pt.y;
						  m1.m[3][2] += Pt.z; return m1;} 
inline MgMat4D operator + ( const MgMat4D &m1, const MgVect3D& Pt)				// +	平行移動
						{ MgMat4D mw = m1; mw += Pt; return mw;}
inline MgMat4D operator -= ( MgMat4D &m1, const MgVect3D& Pt)					// -=	平行移動
						{ m1.m[3][0] -= Pt.x; m1.m[3][1] -= Pt.y;
						  m1.m[3][2] -= Pt.z; return m1;} 
inline MgMat4D operator - ( const MgMat4D &m1, const MgVect3D& Pt)				// -	平行移動
						{ MgMat4D mw = m1; mw -= Pt; return mw;}
inline MgLine3D operator * ( const MgLine3D& Ln1, const MgMat4D &m2)			// 座標変換
						{ MgLine3D Ln; Ln.p[0] = Ln1.p[0] * m2;
						  Ln.p[1] = Ln1.p[1] * m2; return Ln;}
inline MgLine3D operator *= ( MgLine3D& Ln1, const MgMat4D &m2)					// 座標変換
						{ Ln1.p[0] *= m2; Ln1.p[1] *= m2;}
inline	void MgMat4D::Print( MCHAR* s)											// print
						{
#ifdef LOGOUT
							MgMatPrint4( s);
#endif
						}

} // namespace MC
