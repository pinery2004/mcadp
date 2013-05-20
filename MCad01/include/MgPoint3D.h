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

namespace MC
{

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

//======================( ３次元 )==============================
//		３次元の点
//
class DLL_EXPORT_POINT MgPoint3D
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
	MgPoint3D()			{}

	// コピーコンストラクタ
	MgPoint3D( MREAL x1, MREAL y2, MREAL z3);
	MgPoint3D( MgPoint2D v1, MREAL z3);
	MgPoint3D( const MgPoint2D& v1, const class MgPlane3D& Pln3);				// ２次元→３次元

//	MgPoint3D( const MgVect3D& v1);

	// 演算
//	MgPoint3D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// 単位ベクトルを求める
	MgPoint3D RotR90() const;													// Z軸を中心軸として右に９０度回転した点の位置を求める
	MgPoint3D RotL90() const;													// Z軸を中心軸として左に９０度回転した点の位置を求める
	MgPoint3D Rot180() const;													// Z軸を中心軸として１８０度回転した点の位置を求める
	MgPoint3D Rot( const MgVect2D& v) const;									// Z軸を中心軸として単位ベクトル方向に回転した点の位置を求める
	MgPoint3D Rot( MREAL ang) const;											// Z軸を中心軸として指定角度で左回転した点の位置を求める

	// 変換
	MgPoint3D Set( const MgPoint2D& v1, const MgPlane3D& Pln3);					// ２次元→３次元
	MgPoint3D SetUnit()
						{ x = 1; y = 0; z = 0; return *this;}					// (1., 0., 0.)に変更する
//	MgPoint3D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 単位ベクトルに変換する
	MgPoint3D& operator = ( const MREAL* pt);
	MgPoint3D SetRotR90();														// Z軸を中心軸として右に９０度回転する
	MgPoint3D SetRotL90();														// Z軸を中心軸として左に９０度回転する
	MgPoint3D SetRot180();														// Z軸を中心軸として１８０度回転する
	MgPoint3D SetRot( const MgVect2D& v);										// Z軸を中心軸として単位ベクトル方向に回転する
	MgPoint3D SetRot( MREAL ang);												// Z軸を中心軸として指定角度で左回転する

	// 属性値の取得
	void Get( MREAL* rP) const;
//S						{ rP[0] = x; rP[1] = y; rP[2] = z;}
	MgPoint2D To2D() const;//	{ return MgPoint2D( x, y);}						// 3D Point → 2D Point

	// 演算オペレータ
	MgPoint3D operator + ( const MgPoint3D& P) const;							// P3 = P1 + p2
	MgPoint3D operator + ( const MgVect3D& V) const;							// P3 = P1 + p2
	MgVect3D operator - ( const MgPoint3D& P) const;							// P3 = P1 - P2
	MgPoint3D operator - ( const MgVect3D& P) const;							// P3 = P1 - P2
	friend	MgPoint3D operator - ( const MgPoint3D& P);							// P1 = - P2
//	MgPoint3D& operator += ( const MgPoint3D& P);								// P1 += P2
	MgPoint3D& operator += ( const MgVect3D& V);								// P1 += V2
	MgPoint3D& operator -= ( const MgPoint3D& P);								// P1 -= P2
	MgPoint3D& operator -= ( const MgVect3D& V);								// P1 -= V2
	friend	MgPoint3D operator * ( MREAL r, const MgPoint3D& P);				// P2 = r * P1
	MgPoint3D operator * (  MREAL r)	const;									// P2 = P1 * r
	MgPoint3D operator / (  MREAL r) const;										// P2 = P1 / r
	MgPoint3D& operator *= ( MREAL r);											// P1 *= r
	MgPoint3D& operator /= ( MREAL r);											// P1 /= r
	MREAL operator * ( const MgPoint3D& P) const;								// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgVect3D& V) const;								// r = P1 * P2 (内積 cos)
	MgVect3D operator ^ ( const MgPoint3D& P) const;							// V3 = P1 ^ P2 (外積 sin)
	bool operator == ( const MgPoint3D& P) const;								// b = (P1 == P2) 判定
	bool operator != ( const MgPoint3D& P) const;								// b = (P1 != P2) 判定

	// トレース
	void	Print(MCHAR* s) const;
};

//======================( ３次元 )==============================
//		３次元の点（ベクトル）
//
class DLL_EXPORT_POINT MgVect3D
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
	MgVect3D()			{}

	// コピーコンストラクタ
	MgVect3D( MREAL x1, MREAL y2, MREAL z3);
	MgVect3D( MgVect2D v1, MREAL z3);
	MgVect3D( const class MgLine3D& ln);										// 2D線分の方向を表す2Dベクトルを求める
	MgVect3D( const class MgULine3D& uln);										// 2D直線の方向を表す2Dベクトルを求める
	MgVect3D( const	MgPoint3D& P1, const MgPoint3D& P2);						// 始点から終点方向のベクトル

//	MgVect3D( const MgPoint3D& v1);

	// 属性値の設定

	// 属性値の取得
	void	Get( MREAL* rP) const;

	// 演算
	MgVect2D	To2D() const;													// 3D Point → 2D Point

	MgVect3D Unitize() const;													// 単位ベクトルを求める

	MgVect3D RotR90() const;													// Z軸を中心軸として右に９０度回転したベクトルを求める
	MgVect3D RotL90() const;													// Z軸を中心軸として左に９０度回転したベクトルを求める
	MgVect3D Rot180() const;													// Z軸を中心軸として１８０度回転したベクトルを求める
	MgVect3D Rot( const MgVect2D& v) const;										// Z軸を中心軸として単位ベクトル方向に回転したベクトルを求める
	MgVect3D Rot( MREAL ang) const;												// Z軸を中心軸として指定角度で左回転した点の位置を求める
	MREAL AngleX();																// 水平線(X方向)とベクトル方向との角度を求める 
	MREAL AngleY();																// 垂直線(Y方向)とベクトル方向との角度を求める
	MREAL AngleZ();																// 水平面とベクトル方向との角度を求める(-π/2～π/2)
	MREAL Abs();																// ベクトルの長さ
	MREAL SqAbs();																// ベクトルの長さの２乗

	// 変換
	MgVect3D SetUnitize();														// 単位ベクトルに変換する
	MgVect3D& operator = ( const MREAL* pt);
	MgVect3D Set( const MgPoint2D& v1, const MgPlane3D& Pln3);					// ２次元→３次元
	MgVect3D SetRotR90();														// Z軸を中心軸として右に９０度回転する
	MgVect3D SetRotL90();														// Z軸を中心軸として左に９０度回転する
	MgVect3D SetRot180();														// Z軸を中心軸として１８０度回転する
	MgVect3D SetRot( const MgVect2D& v);										// Z軸を中心軸として単位ベクトル方向に回転する
	MgVect3D SetRot( MREAL ang);												// Z軸を中心軸として指定角度で左回転する
	MgVect2D SetAngleX( MREAL ang);												// 水平線(X方向)から指定角度方向の単位ベクトルに変換する 
	MgVect2D SetAngleY( MREAL ang);												// 垂直線(Y方向)から指定角度方向の単位ベクトルに変換する 
	MgVect2D SetAngleXZ( MREAL angx, MREAL angz);								// 水平線(X方向)から指定角度X方向で水平面から指定角度Z方向のの単位ベクトルに変換する 

	// 演算オペレータ
	MgVect3D operator + ( const MgVect3D& V) const;								// P1 = P2 + p3
	MgVect3D operator - ( const MgVect3D& V) const;								// P1 = P2 - P3
	friend	MgVect3D operator - ( const MgVect3D& V);							// P1 = - P2
	MgVect3D& operator += ( const MgVect3D& V);									// P1 += P2
	MgVect3D& operator -= ( const MgVect3D& V);									// P1 -= P2
	friend	MgVect3D operator * ( MREAL r, const MgVect3D& V);					// P1 = r * P2
	MgVect3D operator * (  MREAL r)	const;										// P1 = P2 * r
	MgVect3D operator / (  MREAL r) const;										// P1 = P2 / r
	MgVect3D& operator *= ( MREAL r);											// P1 *= r
	MgVect3D& operator /= ( MREAL r);											// P1 /= r
	MREAL operator * ( const MgVect3D& V) const;								// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgPoint3D& P) const;								// r = P1 * P2 (内積 cos)
	MgVect3D operator ^ ( const MgVect3D& V) const;								// P1 = P2 ^ P3 (外積 sin)
	bool operator == ( const MgVect3D& V) const;								// b = (P1 == P2) 判定
	bool operator != ( const MgVect3D& V) const;								// b = (P1 != P2) 判定

	// トレース
	void	Print(MCHAR* s) const;
};

// サイズ
inline int SZMgPoint3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint3D));}
inline int SZMgPoint3D()			{ return  (int)sizeof( MgPoint3D);}
inline int SZMgVect3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect3D));}
inline int SZMgVect3D()				{ return  (int)sizeof( MgVect3D);}
inline int WSZMgPoint3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint3D) / SZMINT());}
inline int WSZMgPoint3D()			{ return  (int)sizeof( MgPoint3D) / SZMINT();}
inline int WSZMgVect3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect3D) / SZMINT());}
inline int WSZMgVect3D()			{ return  (int)sizeof( MgVect3D) / SZMINT();}

} // namespace MC
