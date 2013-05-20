#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.h
//
//		点とベクトルの定義、編集
//
//
//  K.Matsu           13/01/24    Created.
//==========================================================================================
//

namespace MC
{

class MgVect2D;
class MgPoint2D;

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
//======================( ２次元 )==============================
//		２次元の点
//
class DLL_EXPORT_POINT MgPoint2D
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// コンストラクタ/デストラクタ
	MgPoint2D()			{}

	// コピーコンストラクタ
	MgPoint2D( MREAL x1, MREAL y2);
	MgPoint2D( const CPoint& pt);
	MgPoint2D( const class MgPoint3D& pt);											// ３次元→２次元

//S	MgPoint2D( const MgVect2D& pt);

	// 演算
//	MgPoint2D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// 原点から点方向の単位ベクトルを求める
	MgPoint2D RotR90() const;													// 原点を中心に右に９０度回転した点の位置を求める
	MgPoint2D RotL90() const;													// 原点を中心に左に９０度回転した点の位置を求める
	MgPoint2D Rot180() const;													// 原点を中心に１８０度回転した点の位置を求める
	MgPoint2D Rot( const MgVect2D& v) const;									// 原点を中心に単位ベクトル方向に回転した点の位置を求める
	MgPoint2D Rot( MREAL ang);													// 原点を中心に指定角度で左回転した点の位置を求める

	// 変換
//	MgPoint2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 原点から点方向の単位ベクトルに変換する
	MgPoint2D SetRotR90();														// 原点を中心に右に９０度回転する
	MgPoint2D SetRotL90();														// 原点を中心に左に９０度回転する
	MgPoint2D SetRot180();														// 原点を中心に１８０度回転する
	MgPoint2D SetRot( const MgVect2D& v);										// 原点を中心に単位ベクトル方向に回転する
	MgPoint2D SetRot( MREAL ang);												// 原点を中心に指定角度で左回転する

	// 属性値の取得
	void Get( MREAL* rP) const;

	// 属性値の設定
	MgPoint2D& operator = ( const CPoint &pt);
	MgPoint2D& operator = ( const MREAL* pt);

	// 演算オペレータ
	MgPoint2D operator + ( const MgPoint2D& v) const;							// p3 = p1 + p2
	MgPoint2D operator + ( const MgVect2D& v) const;							// p3 = p1 + v2
	MgVect2D operator - ( const MgPoint2D& v) const;							// v3 = p1 - p2
	MgPoint2D operator - ( const MgVect2D& v) const;							// p3 = p1 - v2
	friend	MgPoint2D operator - ( const MgPoint2D& p);							// p2 = - p1
	MgPoint2D& operator += ( const MgPoint2D& v);								// p1 += p2
	MgPoint2D& operator += ( const MgVect2D& v);								// p1 += v2
	MgPoint2D& operator -= ( const MgPoint2D& v);								// p1 -= p2
	MgPoint2D& operator -= ( const MgVect2D& v);								// p1 -= v2
	friend	MgPoint2D operator * ( MREAL r, const MgPoint2D& v);				// p2 = r * p1
	MgPoint2D operator * ( MREAL r) const;										// p2 = p1 * r
	MgPoint2D operator / ( MREAL r) const;										// p2 = p1 / r
	MgPoint2D& operator *= ( MREAL r);											// p1 *= r
	MgPoint2D& operator /= ( MREAL r);											// p1 /= r
	MREAL operator * ( const MgPoint2D& v) const;								// r = p1 * p2 (内積 cos)
	MREAL operator * ( const MgVect2D& v) const;								// r = p1 * v2 (内積 cos)
	MREAL operator ^ ( const MgPoint2D& v) const;								// p3 = p1 ^ p2 (外積 sin)
	MgPoint2D operator & ( const MgPoint2D& v) const;							// p3 = p1 & p2 (rotation)
	bool operator == (const MgPoint2D& v) const;								// b = (p1 == p2) 判定
	bool operator != (const MgPoint2D& v) const;								// b = (p1 != p2) 判定

	// トレース
	void Print(MCHAR* s) const;
};

//======================( ２次元 )==============================
//		２次元のベクトル
//
class DLL_EXPORT_POINT MgVect2D
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
	// コンストラクタ/デストラクタ
	MgVect2D()			{}

	// コピーコンストラクタ
	MgVect2D( MREAL x1, MREAL y2);												// 成分が(X,Y)方向のベクトル
	MgVect2D( const CPoint& pt);												// CPointの原点から点までの方向のベクトル
	MgVect2D( const class MgVect3D& Vt);												// 3Dベクトルの(X,Y)方向のベクトル
	MgVect2D( const class MgLine2D& ln);										// 線分の終点から終点方向のベクトル
	MgVect2D( const class MgULine2D& uln);										// 直線の方向ベクトル
	MgVect2D( const	MgPoint2D& p1, const MgPoint2D& p2);						// 始点から終点方向のベクトル

//	MgVect2D( const MgPoint2D& pt);

	// 演算
	MgVect2D Unitize() const;													// 単位ベクトルを求める

	MgVect2D RotR90() const;													// 右に９０度回転したベクトルを求める
	MgVect2D RotL90() const;													// 左に９０度回転したベクトルを求める
	MgVect2D Rot180() const;													// １８０度回転したベクトルを求める
	MgVect2D Rot( const MgVect2D& v) const;										// 単位ベクトル方向に回転したベクトルを求める
	MgVect2D Rot( MREAL ang);													// 指定角度で左回転したベクトルを求める
	MREAL AngleX();																// 水平線(X方向)とベクトル方向との角度を求める 
	MREAL AngleY();																// 垂直線(Y方向)とベクトル方向との角度を求める
	MREAL Abs();																// ベクトルの長さ
	MREAL SqAbs();																// ベクトルの長さの２乗

	// 変換
	MgVect2D SetUnitize();														// 単位ベクトルに変換する
	
	MgVect2D SetRotR90();														// 右に９０度回転したベクトルに変換する
	MgVect2D SetRotL90();														// 左に９０度回転したベクトルに変換する
	MgVect2D SetRot180();														// １８０度回転したベクトルに変換する
	MgVect2D SetRot( const MgVect2D& v);										// 単位ベクトル方向に回転したベクトルに変換する
	MgVect2D SetRot( MREAL ang);												// 指定角度(ラジアン)で左回転したベクトルに変換する
	MgVect2D SetAngleX( MREAL ang);												// 水平線(X方向)から指定角度方向の単位ベクトルに変換する 
	MgVect2D SetAngleY( MREAL ang);												// 垂直線(Y方向)から指定角度方向の単位ベクトルに変換する 

	// 属性値の取得
	void Get( MREAL* rP) const;													// MREAL[2] = v1

	// 属性値の設定
	MgVect2D& operator = ( const CPoint &pt);									// v1 = CPoint 
	MgVect2D& operator = ( const MREAL* pt);									// v1 = MREAL[2]


	// 演算オペレータ
	MgVect2D operator + ( const MgVect2D& v) const;								// v3 = v1 + v2
	MgVect2D operator - ( const MgVect2D& v) const;								// v3 = v1 - v2
	friend	MgVect2D operator - ( const MgVect2D& p);							// v2 = - v1
	MgVect2D& operator += ( const MgVect2D& v);									// v1 += v2
	MgVect2D& operator -= ( const MgVect2D& v);									// v1 -= v2
	friend	MgVect2D operator * ( MREAL r, const MgVect2D& v);					// v1 = r * v2
	MgVect2D operator * ( MREAL r) const;										// v2 = v1 * r
	MgVect2D operator / ( MREAL r) const;										// v2 = v1 / r
	MgVect2D& operator *= ( MREAL r);											// v1 *= r
	MgVect2D& operator /= ( MREAL r);											// v1 /= r
	MREAL operator * ( const MgVect2D& v) const;								// r = v1 * v2 (内積 cos)
	MREAL operator * ( const MgPoint2D& v) const;								// r = v1 * p2 (内積 cos)
	MREAL operator ^ ( const MgVect2D& v) const;								// v3 = P1 ^ P2 (外積 sin)
	MgVect2D operator & ( const MgVect2D& v) const;								// v3 = v1 & v2 (rotation)
	bool operator == (const MgVect2D& v) const;									// b = (v1 == v2) 判定
	bool operator != (const MgVect2D& v) const;									// b = (v1 != v2) 判定

	// トレース
	void Print(MCHAR* s) const;
};

// サイズ
inline int SZMgPoint2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint2D));}
inline int SZMgPoint2D()			{ return  (int)sizeof( MgPoint2D);}
inline int SZMgVect2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect2D));}
inline int SZMgVect2D()				{ return  (int)sizeof( MgVect2D);}
inline int WSZMgPoint2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPoint2D) / SZMINT());}
inline int WSZMgPoint2D()			{ return  (int)sizeof( MgPoint2D) / SZMINT();}
inline int WSZMgVect2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgVect2D) / SZMINT());}
inline int WSZMgVect2D()			{ return  (int)sizeof( MgVect2D) / SZMINT();}

} // namespace MC
