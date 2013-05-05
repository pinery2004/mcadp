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
#include "MgAngle.h"

namespace MC
{

class MgVect2D;
class MgVect3D;
class MgPoint2D;
class MgPoint3D;
class MgPlane3D;

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
	MgPoint2D( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgPoint2D( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgPoint2D( const MgPoint3D& pt);

//	MgPoint2D( const MgVect2D& pt);

	// 演算
//	MgPoint2D Unitize( MREAL i_tol = MgTol_Dt::D) const;						// 原点から点方向の単位ベクトルを求める

	MgPoint2D RotR90() const													// 原点を中心に右に９０度回転した点の位置を求める
						{ return MgPoint2D( y, -x);}
	MgPoint2D RotL90() const													// 原点を中心に左に９０度回転した点の位置を求める
						{ return MgPoint2D( -y, x);}
	MgPoint2D Rot180() const													// 原点を中心に１８０度回転した点の位置を求める
						{ return MgPoint2D( -x, -y);}
	MgPoint2D Rot( const MgVect2D& v) const;									// 原点を中心に単位ベクトル方向に回転した点の位置を求める

	MgPoint2D Rot( MREAL ang);													// 原点を中心に指定角度で左回転した点の位置を求める

//S	MREAL Ang() const															// 原点から点方向のX軸からの半時計方向角度


	// 変換
//	MgPoint2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 原点から点方向の単位ベクトルに変換する
	
	MgPoint2D SetRotR90()														// 原点を中心に右に９０度回転する
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgPoint2D SetRotL90()														// 原点を中心に左に９０度回転する
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgPoint2D SetRot180()														// 原点を中心に１８０度回転する
						{ x = -x; y = -y; return *this;}
	MgPoint2D SetRot( const MgVect2D& v);										// 原点を中心に単位ベクトル方向に回転する

	MgPoint2D SetRot( MREAL ang);												// 原点を中心に指定角度で左回転する

	// 属性値の取得
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgPoint2D& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgPoint2D& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// 演算オペレータ
	MgPoint2D operator + ( const MgPoint2D& v) const;							// p3 = p1 + p2
	MgPoint2D operator + ( const MgVect2D& v) const;							// p3 = p1 + v2

	MgVect2D operator - ( const MgPoint2D& v) const;							// p3 = p1 - p2
	MgPoint2D operator - ( const MgVect2D& v) const;							// p3 = p1 - v2

	friend	MgPoint2D operator - ( const MgPoint2D& p)							// p2 = - p1
				 		{ MgPoint2D vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgPoint2D operator += ( const MgPoint2D& v);								// p1 += p2
	MgPoint2D operator += ( const MgVect2D& v);									// p1 += v2

	MgPoint2D operator -= ( const MgPoint2D& v);								// p1 -= p2
	MgPoint2D operator -= ( const MgVect2D& v);									// p1 -= v2

	friend	MgPoint2D operator * ( MREAL r, const MgPoint2D& v)					// p2 = r * p1
				 		{ MgPoint2D vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgPoint2D operator * ( MREAL r) const;										// p2 = p1 * r

	MgPoint2D operator / ( MREAL r) const;										// p2 = p1 / r

	MgPoint2D operator *= ( MREAL r);											// p1 *= r

	MgPoint2D operator /= ( MREAL r);											// p1 /= r

	MREAL operator * ( const MgPoint2D& v) const;								// r = p1 * p2 (内積 cos)
	MREAL operator * ( const MgVect2D& v) const;								// r = p1 * v2 (内積 cos)

	MREAL operator ^ ( const MgPoint2D& v) const;								// p3 = p1 ^ p2 (外積 sin)

	MgPoint2D operator & ( const MgPoint2D& v) const;							// p3 = p1 & p2 (rotation)

	bool operator == (const MgPoint2D& v) const;								// b = (p1 == p2) 判定

	bool operator != (const MgPoint2D& v) const;								// b = (p1 != p2) 判定


	// トレース
	void Print(MCHAR* s) const;
};
//
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
	MgVect2D( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgVect2D( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgVect2D( const MgVect3D& pt);

//	MgVect2D( const MgPoint2D& pt);

	// 演算
	MgVect2D Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 単位ベクトルを求める

	MgVect2D RotR90() const														// 右に９０度回転したベクトルを求める
						{ return MgVect2D( y, -x);}

	MgVect2D RotL90() const														// 左に９０度回転したベクトルを求める
						{ return MgVect2D( -y, x);}

	MgVect2D Rot180() const														// １８０度回転したベクトルを求める
						{ return MgVect2D( -x, -y);}

	MgVect2D Rot( const MgVect2D& v) const										// 単位ベクトル方向に回転したベクトルを求める
						{ return MgVect2D( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}

	MgVect2D Rot( MREAL ang)													// 指定角度で左回転したベクトルを求める
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  return Rot( v);}

	// 変換
	MgVect2D SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 単位ベクトルに変換する
	
	MgVect2D SetRotR90()														// 右に９０度回転したベクトルに変換する
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgVect2D SetRotL90()														// 左に９０度回転したベクトルに変換する
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgVect2D SetRot180()														// １８０度回転したベクトルに変換する
						{ x = -x; y = -y; return *this;}
	MgVect2D SetRot( const MgVect2D& v)											// 単位ベクトル方向に回転したベクトルに変換する
//S						{ MgVect2D vt = *this; 
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						{ *this = Rot( v);
						  return *this;}
	MgVect2D SetRot( MREAL ang)													// 指定角度で左回転したベクトルに変換する
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
//S						  MgVect2D vt = *this;
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						  *this = Rot( v);
						  return *this;}

	// 属性値の取得
	void Get( MREAL* rP) const													// MREAL[2] = v1
						{ rP[0] = x; rP[1] = y;}

	
	MgVect2D& operator = ( const CPoint &pt)									// v1 = CPoint 
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgVect2D& operator = ( const MREAL* pt)										// v1 = MREAL[2]
						{ x = pt[0]; y = pt[1]; return *this;}

	// 演算オペレータ
	MgVect2D operator + ( const MgVect2D& v) const;								// v3 = v1 + v2

	MgVect2D operator - ( const MgVect2D& v) const;								// v3 = v1 - v2

	friend	MgVect2D operator - ( const MgVect2D& p)							// v2 = - v1
				 		{ MgVect2D vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgVect2D operator += ( const MgVect2D& v);									// v1 += v2

	MgVect2D operator -= ( const MgVect2D& v);									// v1 -= v2

	friend	MgVect2D operator * ( MREAL r, const MgVect2D& v)					// v1 = r * v2
				 		{ MgVect2D vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgVect2D operator * ( MREAL r) const;										// v2 = v1 * r

	MgVect2D operator / ( MREAL r) const;										// v2 = v1 / r

	MgVect2D operator *= ( MREAL r);											// v1 *= r

	MgVect2D operator /= ( MREAL r);											// v1 /= r

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
inline MINT SZMgPoint2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2D));}
inline MINT SZMgVect2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2D));}
inline MINT WSZMgPoint2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2D) / SZMINT());}
inline MINT WSZMgVect2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2D) / SZMINT());}

} // namespace MC
