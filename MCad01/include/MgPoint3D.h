#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.h
//
//		点またはベクトルの定義、編集
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "MgAngle.h"

namespace MC
{

class MgVect2;
class MgVect3;
class MgPoint2;
class MgPoint3;
class MgPlane3;

//#include "mdPlex.h"

#ifdef DLL_EXPORT_POINT
	#undef DLL_EXPORT_POINT
#endif

#ifdef DLL_EXPORT_POINT_DO
	#pragma message( "<<< MgPoint・dll_EXport >>>")
	#define DLL_EXPORT_POINT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_GEO_DO
//			#pragma message( "=== MgPoint・dll ===")
			#define DLL_EXPORT_POINT
		#else
//			#pragma message( "=== MgPoint・dll_IMport ===")
			#define DLL_EXPORT_POINT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_POINT
	#endif
#endif

//
//======================( ３次元 )==============================
//		３次元の点
//
class DLL_EXPORT_POINT MgPoint3
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;
	MREAL z;

public:
// コンストラクタ
	MgPoint3()			{}

	// コピーコンストラクタ
	MgPoint3( MREAL x1, MREAL y2, MREAL z3)
						{ x = x1; y = y2; z = z3;}
	MgPoint3( MgPoint2 v1, MREAL z3)
						{ x = v1.x; y = v1.y; z = z3;}
	MgPoint3( const MgPoint2& v1, const MgPlane3& Pln3);						// ２次元→３次元

//	MgPoint3( const MgVect3& v1);

	// 属性値の設定
	MgPoint3 Set( const MgPoint2& v1, const MgPlane3& Pln3);					// ２次元→３次元

	MgPoint3 SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)に変更する
	MgPoint3 SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 単位ベクトルに変換する

	MgPoint3& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; z = pt[2]; return *this;}

	// 属性値の取得
	void	Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgPoint2	To2D() const	{ return MgPoint2( x, y);}						// 3D Point → 2D Point

	// 演算オペレータ
	MgPoint3 operator + ( const MgPoint3& v) const;								// P1 = P2 + p3
	MgPoint3 operator + ( const MgVect3& v) const;								// P1 = P2 + p3

	MgVect3 operator - ( const MgPoint3& p) const;								// P1 = P2 - P3
	MgPoint3 operator - ( const MgVect3& p) const;								// P1 = P2 - P3

	friend	MgPoint3 operator - ( const MgPoint3& v)							// P1 = - P2
				 		{ MgPoint3 Vto; Vto.x =-v.x; Vto.y = -v.y;
						  Vto.z = -v.z; return Vto;}
	MgPoint3 operator += ( const MgPoint3& v);									// P1 += P2
	MgPoint3 operator += ( const MgVect3& v);									// P1 += P2

	MgPoint3 operator -= ( const MgPoint3& v);									// P1 -= P2
	MgPoint3 operator -= ( const MgVect3& v);									// P1 -= P2

	friend	MgPoint3 operator * ( MREAL r, const MgPoint3& v)					// P1 = r * P2
				 		{ MgPoint3 Vto; Vto.x =r * v.x; Vto.y = r * v.y;
						  Vto.z = r * v.z; return Vto;}
	MgPoint3 operator * (  MREAL r)	const;										// P1 = P2 * r

	MgPoint3 operator / (  MREAL r) const;										// P1 = P2 / r

	MgPoint3 operator *= ( MREAL r);											// P1 *= r

	MgPoint3 operator /= ( MREAL r);											// P1 /= r

	MREAL operator * ( const MgPoint3& v) const;								// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgVect3& v) const;									// r = P1 * P2 (内積 cos)

	MgVect3 operator ^ ( const MgPoint3& v) const;								// P1 = P2 ^ P3 (外積 sin)

	bool operator == ( const MgPoint3& v) const;								// b = (P1 == P2) 判定

	bool operator != ( const MgPoint3& v) const;								// b = (P1 != P2) 判定

	MgPoint3 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 単位ベクトルを求める

	MgPoint3 RotR90() const;													// Z軸を中心軸として右に９０度回転したベクトルを求める

	MgPoint3 RotL90() const;													// Z軸を中心軸として左に９０度回転したベクトルを求める

	MgPoint3 Rot180() const;													// Z軸を中心軸として１８０度回転したベクトルを求める

	MgPoint3 Rot( const MgVect2& v) const;										// 単位ベクトル方向に回転したベクトルを求める

	// トレース
	void	Print(MCHAR* s) const;
};

//
//======================( ３次元 )==============================
//		３次元の点（ベクトル）
//
class DLL_EXPORT_POINT MgVect3
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;
	MREAL z;

public:
// コンストラクタ/デストラクタ
	MgVect3()			{}

	// コピーコンストラクタ
	MgVect3( MREAL x1, MREAL y2, MREAL z3)
						{ x = x1; y = y2; z = z3;}
	MgVect3( MgVect2 v1, MREAL z3)
						{ x = v1.x; y = v1.y; z = z3;}
//	MgVect3( const MgPoint3& v1);


	// 属性値の設定
//	MgVect3 Set( const MgPoint2& v1, const MgPlane3& Pln3);						// ２次元→３次元

	MgVect3 SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)に変更する
	MgVect3 SetUnitize( MREAL i_tol = MgTol_Dt::D);								// 単位ベクトルに変換する

	MgVect3& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; z = pt[2]; return *this;}

	// 属性値の取得
	void	Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgVect2	To2D() const	{ return MgVect2( x, y);}							// 3D Point → 2D Point

	// 演算オペレータ
	MgVect3 operator + ( const MgVect3& v) const;								// P1 = P2 + p3

	MgVect3 operator - ( const MgVect3& p) const;								// P1 = P2 - P3

	friend	MgVect3 operator - ( const MgVect3& v)								// P1 = - P2
				 		{ MgVect3 Vto; Vto.x =-v.x; Vto.y = -v.y;
						  Vto.z = -v.z; return Vto;}
	MgVect3 operator += ( const MgVect3& v);									// P1 += P2

	MgVect3 operator -= ( const MgVect3& v);									// P1 -= P2

	friend	MgVect3 operator * ( MREAL r, const MgVect3& v)						// P1 = r * P2
				 		{ MgVect3 Vto; Vto.x =r * v.x; Vto.y = r * v.y;
						  Vto.z = r * v.z; return Vto;}
	MgVect3 operator * (  MREAL r)	const;										// P1 = P2 * r

	MgVect3 operator / (  MREAL r) const;										// P1 = P2 / r

	MgVect3 operator *= ( MREAL r);												// P1 *= r

	MgVect3 operator /= ( MREAL r);												// P1 /= r

	MREAL operator * ( const MgVect3& v) const;									// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgPoint3& v) const;								// r = P1 * P2 (内積 cos)

	MgVect3 operator ^ ( const MgVect3& v) const;								// P1 = P2 ^ P3 (外積 sin)

	bool operator == ( const MgVect3& v) const;									// b = (P1 == P2) 判定

	bool operator != ( const MgVect3& v) const;									// b = (P1 != P2) 判定

	MgVect3 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 単位ベクトルを求める

	MgVect3 RotR90() const;														// Z軸を中心軸として右に９０度回転したベクトルを求める

	MgVect3 RotL90() const;														// Z軸を中心軸として左に９０度回転したベクトルを求める

	MgVect3 Rot180() const;														// Z軸を中心軸として１８０度回転したベクトルを求める

	MgVect3 Rot( const MgVect2& v) const;										// 単位ベクトル方向に回転したベクトルを求める

	// トレース
	void	Print(MCHAR* s) const;
};

// サイズ
inline MINT SZMgPoint3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint3));}
inline MINT SZMgVect3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect3));}
inline MINT WSZMgPoint3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint3) / SZMINT());}
inline MINT WSZMgVect3( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect3) / SZMINT());}

} // namespace MC