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
//======================( ２次元 )==============================
//		２次元の点
//
class DLL_EXPORT_POINT MgPoint2
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// コンストラクタ/デストラクタ
	MgPoint2()			{}

	// コピーコンストラクタ
	MgPoint2( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgPoint2( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgPoint2( const MgPoint3& pt);

//	MgPoint2( const MgVect2& pt);

	// 演算
//	MgPoint2 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 原点から点方向の単位ベクトルを求める

	MgPoint2 RotR90() const														// 原点を中心に右に９０度回転した点の位置を求める
						{ return MgPoint2( y, -x);}
	MgPoint2 RotL90() const														// 原点を中心に左に９０度回転した点の位置を求める
						{ return MgPoint2( -y, x);}
	MgPoint2 Rot180() const														// 原点を中心に１８０度回転した点の位置を求める
						{ return MgPoint2( -x, -y);}
	MgPoint2 Rot( const MgVect2& v) const;										// 原点を中心に単位ベクトル方向に回転した点の位置を求める

	MgPoint2 Rot( MREAL ang);													// 原点を中心に指定角度で左回転した点の位置を求める

	// 変換
//	MgPoint2 SetUnitize( MREAL i_tol = MgTol_Dt::D);							// 原点から点方向の単位ベクトルに変換する
	
	MgPoint2 SetRotR90()														// 原点を中心に右に９０度回転する
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgPoint2 SetRotL90()														// 原点を中心に左に９０度回転する
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgPoint2 SetRot180()														// 原点を中心に１８０度回転する
						{ x = -x; y = -y; return *this;}
	MgPoint2 SetRot( const MgVect2& v);											// 原点を中心に単位ベクトル方向に回転する

	MgPoint2 SetRot( MREAL ang);												// 原点を中心に指定角度で左回転する

	// 属性値の取得
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgPoint2& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgPoint2& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// 演算オペレータ
	MgPoint2 operator + ( const MgPoint2& v) const;								// P1 = P2 + p3
	MgPoint2 operator + ( const MgVect2& v) const;								// P1 = P2 + p3

	MgVect2 operator - ( const MgPoint2& v) const;								// P1 = P2 - P3
	MgPoint2 operator - ( const MgVect2& v) const;								// P1 = P2 - P3

	friend	MgPoint2 operator - ( const MgPoint2& p)							// P1 = - P2
				 		{ MgPoint2 vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgPoint2 operator += ( const MgPoint2& v);									// P1 += P2
	MgPoint2 operator += ( const MgVect2& v);									// P1 += P2

	MgPoint2 operator -= ( const MgPoint2& v);									// P1 -= P2
	MgPoint2 operator -= ( const MgVect2& v);									// P1 -= P2

	friend	MgPoint2 operator * ( MREAL r, const MgPoint2& v)					// P1 = r * P2
				 		{ MgPoint2 vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgPoint2 operator * ( MREAL r) const;										// P1 = P2 * r

	MgPoint2 operator / ( MREAL r) const;										// P1 = P2 / r

	MgPoint2 operator *= ( MREAL r);											// P1 *= r

	MgPoint2 operator /= ( MREAL r);											// P1 /= r

	MREAL operator * ( const MgPoint2& v) const;								// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgVect2& v) const;									// r = P1 * P2 (内積 cos)

	MREAL operator ^ ( const MgPoint2& v) const;								// P1 = P2 ^ P3 (外積 sin)

	MgPoint2 operator & ( const MgPoint2& v) const;								// P1 = P2 & P3 (rotation)

	bool operator == (const MgPoint2& v) const;									// b = (P1 == P2) 判定

	bool operator != (const MgPoint2& v) const;									// b = (P1 != P2) 判定


	// トレース
	void Print(MCHAR* s) const;
};
//
//======================( ２次元 )==============================
//		２次元のベクトル
//
class DLL_EXPORT_POINT MgVect2
{
public:
	union{
		MREAL v[1];
		MREAL x;
	};
	MREAL y;

public:
// コンストラクタ/デストラクタ
	MgVect2()			{}

	// コピーコンストラクタ
	MgVect2( MREAL x1, MREAL y2)
						{ x = x1; y = y2;}
	MgVect2( const CPoint& pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y);}
	MgVect2( const MgVect3& pt);

//	MgVect2( const MgPoint2& pt);

	// 演算
	MgVect2 Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 単位ベクトルを求める

	MgVect2 RotR90() const														// 右に９０度回転したベクトルを求める
						{ return MgVect2( y, -x);}

	MgVect2 RotL90() const														// 左に９０度回転したベクトルを求める
						{ return MgVect2( -y, x);}

	MgVect2 Rot180() const														// １８０度回転したベクトルを求める
						{ return MgVect2( -x, -y);}

	MgVect2 Rot( const MgVect2& v) const										// 単位ベクトル方向に回転したベクトルを求める
						{ return MgVect2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}

	MgVect2 Rot( MREAL ang)														// 指定角度で左回転したベクトルを求める
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
						  return Rot( v);}

	// 変換
	MgVect2 SetUnitize( MREAL i_tol = MgTol_Dt::D);								// 単位ベクトルに変換する
	
	MgVect2 SetRotR90()															// 右に９０度回転したベクトルに変換する
						{ MREAL xs = x; x = y; y = -xs; return *this;}
	MgVect2 SetRotL90()															// 左に９０度回転したベクトルに変換する
						{ MREAL xs = x; x = -y; y = xs; return *this;}
	MgVect2 SetRot180()															// １８０度回転したベクトルに変換する
						{ x = -x; y = -y; return *this;}
	MgVect2 SetRot( const MgVect2& v)											// 単位ベクトル方向に回転したベクトルに変換する
//S						{ MgVect2 vt = *this; 
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						{ *this = Rot( v);
						  return *this;}
	MgVect2 SetRot( MREAL ang)													// 指定角度で左回転したベクトルに変換する
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
//S						  MgVect2 vt = *this;
//						  x = vt.x * v.x -  vt.y * v.y;
//						  y = vt.x * v.y +  vt.y * v.x;
						  *this = Rot( v);
						  return *this;}

	// 属性値の取得
	void Get( MREAL* rP) const
						{ rP[0] = x; rP[1] = y;} 
	MgVect2& operator = ( const CPoint &pt)
						{ x = MREAL(pt.x); y = MREAL(pt.y); return *this;}
	MgVect2& operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; return *this;}

	// 演算オペレータ
	MgVect2 operator + ( const MgVect2& v) const;								// P1 = P2 + p3

	MgVect2 operator - ( const MgVect2& v) const;								// P1 = P2 - P3

	friend	MgVect2 operator - ( const MgVect2& p)								// P1 = - P2
				 		{ MgVect2 vto; vto.x = -p.x;
						  vto.y = -p.y; return vto;}
	MgVect2 operator += ( const MgVect2& v);									// P1 += P2

	MgVect2 operator -= ( const MgVect2& v);									// P1 -= P2

	friend	MgVect2 operator * ( MREAL r, const MgVect2& v)						// P1 = r * P2
				 		{ MgVect2 vto;vto.x = r * v.x;
						  vto.y = r * v.y; return vto;}
	MgVect2 operator * ( MREAL r) const;										// P1 = P2 * r

	MgVect2 operator / ( MREAL r) const;										// P1 = P2 / r

	MgVect2 operator *= ( MREAL r);												// P1 *= r

	MgVect2 operator /= ( MREAL r);												// P1 /= r

	MREAL operator * ( const MgVect2& v) const;									// r = P1 * P2 (内積 cos)
	MREAL operator * ( const MgPoint2& v) const;								// r = P1 * P2 (内積 cos)

	MREAL operator ^ ( const MgVect2& v) const;									// P1 = P2 ^ P3 (外積 sin)

	MgVect2 operator & ( const MgVect2& v) const;								// P1 = P2 & P3 (rotation)

	bool operator == (const MgVect2& v) const;									// b = (P1 == P2) 判定

	bool operator != (const MgVect2& v) const;									// b = (P1 != P2) 判定


	// トレース
	void Print(MCHAR* s) const;
};

// サイズ
inline MINT SZMgPoint2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2));}
inline MINT SZMgVect2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2));}
inline MINT WSZMgPoint2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPoint2) / SZMINT());}
inline MINT WSZMgVect2( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgVect2) / SZMINT());}

} // namespace MC
