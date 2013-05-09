#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgMatA.h
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
			#define DLL_EXPORT_MAT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_MAT
	#endif
#endif

namespace MC
{
//
//======================( ２Ｄ )==============================
//	2次元座標変換マトリックス
class DLL_EXPORT_MAT MgMat2D
{
public:
	MREAL m[3][3];
//
public:
	MgMat2D() {}
	MgMat2D( MREAL i_m11, MREAL i_m12, MREAL i_m13,
		     MREAL i_m21, MREAL i_m22, MREAL i_m23,
		     MREAL i_m31, MREAL i_m32, MREAL i_m33) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33;}
	MgMat2D( MREAL i_m[3][3]) {
		memcpy( m, i_m[0], SZMREAL( 9));}
	MgMat2D( MREAL i_m[9]) {
		memcpy( m, i_m, SZMREAL( 9));}
	void SetUnit();																// 単位行列を設定する
	friend MgMat2D operator +  ( const MgMat2D& m1, const MgMat2D& m2);			// +
	friend MgMat2D operator += ( MgMat2D&,			const MgMat2D&);			// +=
	friend MgMat2D operator -  ( const MgMat2D&);								// -
	friend MgMat2D operator -  ( const MgMat2D&,	const MgMat2D&);			// -
	friend MgMat2D operator -= ( MgMat2D&,			const MgMat2D&);			// -=
	friend MgMat2D operator *  ( const MgMat2D&,	const MgMat2D&);			// *
	friend MgMat2D operator *= ( MgMat2D&,			const MgMat2D&);			// *=

	friend MgMat2D operator +  ( const MgMat2D& m1, const MgVect2D& Pt);		// +	平行移動
	friend MgMat2D operator +  ( const MgMat2D& m1, const MgPoint2D& Pt);		// +	平行移動
	friend MgMat2D operator += ( MgMat2D& m1,		 const MgVect2D& Pt);		// +=	平行移動
	friend MgMat2D operator += ( MgMat2D& m1,		 const MgPoint2D& Pt);		// +=	平行移動

	friend MgMat2D operator -  ( const MgMat2D& m1, const MgVect2D& Pt);		// -	平行移動
	friend MgMat2D operator -  ( const MgMat2D& m1, const MgPoint2D& Pt);		// -	平行移動
	friend MgMat2D operator -= ( MgMat2D& m1,		 const MgVect2D& Pt);		// -=	平行移動
	friend MgMat2D operator -= ( MgMat2D& m1,		 const MgPoint2D& Pt);		// -=	平行移動
//	２Ｄ
	friend MgPoint2D operator *  ( const MgPoint2D& Pt, const MgMat2D& m1);		// *	座標変換
	friend MgVect2D operator  *  ( const MgVect2D& v,	const MgMat2D& m1);		// *	座標変換
	friend MgULine2D operator *  ( const MgULine2D&,	const MgMat2D& m1);		// *	座標変換
	friend MgLine2D operator  *  ( const MgLine2D& Ln1, const MgMat2D& m1);		// *	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt,		const MgMat2D& m1);		// *=	座標変換
	friend MgVect2D operator  *= ( MgVect2D& V,			const MgMat2D& m1);		// *=	座標変換
	friend MgULine2D operator *= ( MgULine2D&,			const MgMat2D& m1);		// *=	座標変換
	friend MgLine2D operator  *= ( MgLine2D& Ln,		const MgMat2D& m1);		// *=	座標変換
//	３Ｄ
	friend MgPoint3D operator *  ( const MgPoint3D& Pt,	const MgMat2D& m1);		// *	座標変換
	friend MgVect3D operator  *  ( const MgVect3D& Vt,	const MgMat2D& m1);		// *	座標変換
	friend MgULine3D operator *  ( const MgULine3D&,	const MgMat2D& m1);		// *	座標変換
	friend MgLine3D operator  *  ( const MgLine3D& Ln1, const MgMat2D& m1);		// *	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt,		const MgMat2D& m1);		// *=	座標変換
	friend MgVect3D operator  *= ( MgVect3D& Vt,		const MgMat2D& m1);		// *=	座標変換
	friend MgULine3D operator *= ( MgULine3D&,			const MgMat2D& m1);		// *=	座標変換
	friend MgLine3D operator  *= ( MgLine3D& Ln,		const MgMat2D& m1);		// *=	座標変換
//
	void Print( MCHAR* s);														// print
	void MgMatPrint3(MCHAR* s);
};

//inline	MgMat2D operator + ( const MgMat2D& i_m1, const MgVect2D& i_pt)			// +	平行移動
//{ 
//	MgMat2D mw;
//	mw = i_m1;
//	mw += i_pt;
//	return mw;
//}
//inline	MgMat2D operator +  ( const MgMat2D& i_m1, const MgPoint2D& i_pt)		// +	平行移動
//{
//	return i_m1 + (MgVect2D&)i_pt;
//}
//inline	MgMat2D operator += ( MgMat2D& i_m1, const MgVect2D& i_pt)				// +=	平行移動
//{
//	i_m1.m[2][0] += i_pt.x;
//	i_m1.m[2][1] += i_pt.y;
//	return i_m1;
//}
//inline	MgMat2D operator += ( MgMat2D& i_m1, const MgPoint2D& i_pt)				// +=	平行移動
//{
//	return i_m1 += (MgVect2D&)i_pt;
//}
//inline	MgMat2D operator - ( const MgMat2D& i_m1, const MgVect2D& i_pt)			// -	平行移動
//{
//	MgMat2D mw = i_m1;
//	mw -= i_pt;
//	return mw;
//}
//inline	MgMat2D operator -  ( const MgMat2D& i_m1, const MgPoint2D& i_pt)		// -	平行移動
//{
//	return i_m1 - (MgVect2D&)i_pt;
//}
//inline	MgMat2D operator -= ( MgMat2D& i_m1, const MgVect2D& i_pt)				// -=	平行移動
//{
//	i_m1.m[2][0] -= i_pt.x;
//	i_m1.m[2][1] -= i_pt.y;
//	return i_m1;
//}
//inline	MgMat2D operator -= ( MgMat2D& i_m1, const MgPoint2D& i_pt)				// -=	平行移動
//{
//	return i_m1 -= (MgVect2D&)i_pt;
//}

inline	MgLine2D operator * ( const MgLine2D& Ln1, const MgMat2D& m2)			// *	座標変換
{
	MgLine2D Ln;
	Ln.p[0] = Ln1.p[0] * m2;
	Ln.p[1] = Ln1.p[1] * m2;
	return Ln;
}
inline	MgLine2D operator *= ( MgLine2D& Ln, const MgMat2D&m2)					// *=	座標変換
{
	Ln.p[0] *= m2;
	Ln.p[1] *= m2;
	return Ln;
}
inline	MgLine3D operator * ( const MgLine3D& Ln1, const MgMat2D& m1)			// *	座標変換
{
	MgLine3D Ln;
	Ln.p[0] = Ln1.p[0] * m1;
	Ln.p[1] = Ln1.p[1] * m1;
	return Ln;
}
inline	MgLine3D operator *= ( MgLine3D& Ln, const MgMat2D& m1)					// *=	座標変換
{
	Ln.p[0] *= m1;
	Ln.p[1] *= m1;
	return Ln;
}

inline	void MgMat2D::Print( MCHAR* s)											// print
{
#ifdef LOGOUT
	MgMatPrint3( s);
#endif
}
//
//======================( ３Ｄ )==============================
//	3次元座標変換マトリックス
//
class DLL_EXPORT_MAT MgMat3D
{
public:
	MREAL m[4][4];

public:
	MgMat3D() {}
	MgMat3D( MREAL i_m11, MREAL i_m12, MREAL i_m13, MREAL i_m14,
		     MREAL i_m21, MREAL i_m22, MREAL i_m23, MREAL i_m24,
		     MREAL i_m31, MREAL i_m32, MREAL i_m33, MREAL i_m34,
		     MREAL i_m41, MREAL i_m42, MREAL i_m43, MREAL i_m44) {
		m[0][0] = i_m11; m[0][1] = i_m12; m[0][2] = i_m13; m[0][3] = i_m14;
		m[1][0] = i_m21; m[1][1] = i_m22; m[1][2] = i_m23; m[1][3] = i_m24;
		m[2][0] = i_m31; m[2][1] = i_m32; m[2][2] = i_m33; m[2][3] = i_m34;
		m[3][0] = i_m41; m[3][1] = i_m42; m[3][2] = i_m43; m[3][3] = i_m44;}
	MgMat3D( MREAL i_m[4][4]) {
		memcpy( m, i_m[0], SZMREAL( 16));}
	MgMat3D( MREAL i_m[16]) {
		memcpy( m, i_m, SZMREAL( 16));}
	MgMat3D( MgVect3D i_V1, MgVect3D i_V2, MgVect3D i_V3) {
		m[0][0] = i_V1.x; m[0][1] = i_V2.x; m[0][2] = i_V3.x; m[0][3] = 0.0;
		m[1][0] = i_V1.y; m[1][1] = i_V2.y; m[1][2] = i_V3.y; m[1][3] = 0.0;
		m[2][0] = i_V1.z; m[2][1] = i_V2.z; m[2][2] = i_V3.z; m[2][3] = 0.0;
		m[3][0] = 0.0;	  m[3][1] = 0.0;	m[3][2] = 0.0;	  m[3][3] = 1.0;}
	void SetUnit();																// 単位行列を設定する
	friend MgMat3D operator +  ( const MgMat3D&, const MgMat3D&);				// +
	friend MgMat3D operator += ( MgMat3D&,		 const MgMat3D&);				// +=
	friend MgMat3D operator -  ( const MgMat3D&);								// -
	friend MgMat3D operator -  ( const MgMat3D&, const MgMat3D&);				// -
	friend MgMat3D operator -= ( MgMat3D&,		 const MgMat3D&);				// -=
	friend MgMat3D operator *  ( const MgMat3D&, const MgMat3D&);				// *
	friend MgMat3D operator *= ( MgMat3D&,		 const MgMat3D&);				// *=

	friend MgMat3D operator +  ( const MgMat3D& M1, const MgVect3D& Vt);		// +	平行移動
	friend MgMat3D operator +  ( const MgMat3D& M1, const MgPoint3D& Pt)		// +	平行移動
							{ return M1 + (MgVect3D&)Pt;}
	friend MgMat3D operator += ( MgMat3D& M1,		const MgVect3D& Vt);		// +=	平行移動
	friend MgMat3D operator += ( MgMat3D& M1,		const MgPoint3D& Pt)		// +=	平行移動
							{ return M1 += (MgVect3D&)Pt;}

	friend MgMat3D operator -  ( const MgMat3D& M1, const MgVect3D& Pt);		// -	平行移動
	friend MgMat3D operator -  ( const MgMat3D& M1, const MgPoint3D& Pt)		// -	平行移動
							{ return M1 - (MgVect3D&)Pt;}
	friend MgMat3D operator -= ( MgMat3D& M1, const MgVect3D& Pt);				// -=	平行移動
	friend MgMat3D operator -= ( MgMat3D& M1, const MgPoint3D& Pt)				// -=	平行移動
							{ return M1 -= (MgVect3D&)Pt;}
	//	２Ｄ
	friend MgPoint2D operator *  ( const MgPoint2D& Pt, const MgMat3D& M1);		// *	座標変換
	friend MgVect2D operator  *	 ( const MgVect2D& Vt,	const MgMat3D& M1);		// *	座標変換
	friend MgULine2D operator *  ( const MgULine2D& uL, const MgMat3D& M1);		// *	座標変換
	friend MgLine2D operator  *	 ( const MgLine2D& Ln,	const MgMat3D& M1);		// *	座標変換
	friend MgPoint2D operator *= ( MgPoint2D& Pt,		const MgMat3D& M1);		// *=	座標変換
	friend MgVect2D operator  *= ( MgVect2D& Vt,		const MgMat3D& M1);		// *=	座標変換
	friend MgULine2D operator *= ( MgULine2D& uL,		const MgMat3D& M1);		// *=	座標変換
	friend MgLine2D operator  *= ( MgLine2D& Ln,		const MgMat3D& M1);		// *=	座標変換
	//	３Ｄ
	friend MgPoint3D operator *  ( const MgPoint3D& Pt, const MgMat3D& M1);		// *	座標変換
	friend MgVect3D operator  *	 ( const MgVect3D& Vt,	const MgMat3D& M1);		// *	座標変換
	friend MgULine3D operator *  ( const MgULine3D& uL, const MgMat3D& M1);		// *	座標変換
	friend MgLine3D operator  *	 ( const MgLine3D& Ln,	const MgMat3D& M1);		// *	座標変換
	friend MgPoint3D operator *= ( MgPoint3D& Pt,		const MgMat3D& M1);		// *=	座標変換
	friend MgVect3D operator  *= ( MgVect3D& Vt,		const MgMat3D& M1);		// *=	座標変換
	friend MgULine3D operator *= ( MgULine3D& uL,		const MgMat3D& M1);		// *=	座標変換
	friend MgLine3D operator  *= ( MgLine3D& Ln,		const MgMat3D& M1);		// *=	座標変換

	void Print( MCHAR* s);														// print
	void MgMatPrint4(MCHAR* s);
};

inline MgMat3D operator + ( const MgMat3D& i_M1, const MgVect3D& i_Vt)			// +	平行移動
{
	MgMat3D mw;
	mw = i_M1;
	mw += i_Vt;
	return mw;
}
inline MgMat3D operator += ( MgMat3D& i_M1, const MgVect3D& i_Vt)				// +=	平行移動
{ 
	i_M1.m[3][0] += i_Vt.x;
	i_M1.m[3][1] += i_Vt.y;
	i_M1.m[3][2] += i_Vt.z;
	return i_M1;
} 
inline MgMat3D operator -= ( MgMat3D& i_M1, const MgVect3D& i_Vt)				// -=	平行移動
{
	i_M1.m[3][0] -= i_Vt.x;
	i_M1.m[3][1] -= i_Vt.y;
	i_M1.m[3][2] -= i_Vt.z;
	return i_M1;
} 
inline MgMat3D operator - ( const MgMat3D& i_M1, const MgVect3D& i_Vt)			// -	平行移動
{
	MgMat3D mw = i_M1;
	mw -= i_Vt;
	return mw;
}
inline MgLine3D operator * ( const MgLine3D& i_Ln1, const MgMat3D& i_M2)		// 座標変換
{
	MgLine3D Ln;
	Ln.p[0] = i_Ln1.p[0] * i_M2;
	Ln.p[1] = i_Ln1.p[1] * i_M2;
	return Ln;
}
inline MgLine3D operator *= ( MgLine3D& i_Ln1, const MgMat3D& i_M2)				// 座標変換
{
	i_Ln1.p[0] *= i_M2;
	i_Ln1.p[1] *= i_M2;
	return i_Ln1;
}
inline	void MgMat3D::Print( MCHAR* s)											// print
{
#ifdef LOGOUT
	MgMatPrint4( s);
#endif
}

} // namespace MC
