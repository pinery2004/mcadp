#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPointDf.h
//
//		点とベクトルの編集	inline関数
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "MsDefConst.h"
#include "MgAngle.h"
#include "MgPoint2D.h"
#include "MgPoint3D.h"
#include "MsDefCheck.h"
#include "MsDefFunc.h"
//#include "mdPlex.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		２次元点	ベクトル演算
//
// コピーコンストラクタ
inline MgPoint2D::MgPoint2D( MREAL x1, MREAL y2)
{
	x = x1; y = y2;
}
inline MgPoint2D::MgPoint2D( const CPoint& pt)
{
	x = MREAL(pt.x);
	y = MREAL(pt.y);
}
inline MgPoint2D::MgPoint2D( const MgPoint3D& pt)
						{ x = pt.x; y = pt.y;}

//inline MgPoint2D::MgPoint2D( const MgVect2D& pt)
//						{ x = pt.x; y = pt.y;}


// 演算
inline MgPoint2D MgPoint2D::RotR90() const						// 原点を中心に右に９０度回転した点の位置を求める
{
	return MgPoint2D( y, -x);
}
inline MgPoint2D MgPoint2D::RotL90() const						// 原点を中心に左に９０度回転した点の位置を求める
{
	return MgPoint2D( -y, x);
}
inline MgPoint2D MgPoint2D::Rot180() const						// 原点を中心に１８０度回転した点の位置を求める
{
	return MgPoint2D( -x, -y);
}
inline MgPoint2D MgPoint2D::Rot( const MgVect2D& v) const		// 原点を中心に単位ベクトル方向に回転した点の位置を求める
{
	return MgPoint2D( x * v.x - y * v.y, x * v.y + y * v.x);
}
inline MgPoint2D MgPoint2D::Rot( MREAL ang)						// 原点を中心に指定角度で左回転した点の位置を求める
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	MgPoint2D pt;
	pt.x = x * v.x -  y * v.y;
	pt.y = x * v.y +  y * v.x;
	return pt;
}

// 変換
inline MgPoint2D MgPoint2D::SetRotR90()							// 原点を中心に右に９０度回転する
{
	MREAL xs = x;
	x = y;
	y = -xs;
	return *this;
}
inline MgPoint2D MgPoint2D::SetRotL90()							// 原点を中心に左に９０度回転する
{
	MREAL xs = x;
	x = -y;
	y = xs;
	return *this;
}
inline MgPoint2D MgPoint2D::SetRot180()							// 原点を中心に１８０度回転する
{
	x = -x;
	y = -y;
	return *this;
}
inline MgPoint2D MgPoint2D::SetRot( const MgVect2D& v)			// 原点を中心に単位ベクトル方向に回転する
{
	*this = Rot( v);
	return *this;
}
inline MgPoint2D MgPoint2D::SetRot( MREAL ang)					// 原点を中心に指定角度で左回転する
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	*this = Rot( v);
	return *this;
}


// 属性値の取得
inline void MgPoint2D::Get( MREAL* rP) const
{
	rP[0] = x;
	rP[1] = y;
}

// 属性値の設定
inline MgPoint2D& MgPoint2D::operator = ( const CPoint &pt)
{
	x = MREAL(pt.x);
	y = MREAL(pt.y);
	return *this;
}
inline MgPoint2D& MgPoint2D::operator = ( const MREAL* pt)
{
	x = pt[0];
	y = pt[1];
	return *this;
}

// 演算オペレータ
inline MgPoint2D MgPoint2D::operator + ( const MgPoint2D& p) const				// p3 = p1 + p2
{
	return MgPoint2D( x + p.x, y + p.y);
}
inline MgPoint2D MgPoint2D::operator + ( const MgVect2D& v) const				// p3 = p1 + v2
{
	return MgPoint2D( x + v.x, y + v.y);
}
inline MgVect2D MgPoint2D::operator - ( const MgPoint2D& p) const				// v3 = p1 - p2
{
	return MgVect2D( x - p.x, y - p.y);
}
inline MgPoint2D MgPoint2D::operator - ( const MgVect2D& v) const				// P3 = p1 - v2
{
	return MgPoint2D( x - v.x, y - v.y);
}
inline MgPoint2D operator - ( const MgPoint2D& p)								// p2 = - p1
{
	MgPoint2D vto;
	vto.x = -p.x;
	vto.y = -p.y;
	return vto;
}
inline MgPoint2D& MgPoint2D::operator += ( const MgPoint2D& p)					// p1 += p2
{
	x += p.x;
	y += p.y;
	return *this;
}
inline MgPoint2D& MgPoint2D::operator += ( const MgVect2D& v)					// p1 += v2
{
	x += v.x;
	y += v.y;
	return *this;
}
inline MgPoint2D& MgPoint2D::operator -= ( const MgPoint2D& p)					// p1 -= p2
{
	x -= p.x;
	y -= p.y;
	return *this;
}
inline MgPoint2D& MgPoint2D::operator -= ( const MgVect2D& v)					// p1 -= v2
{
	x -= v.x;
	y -= v.y;
	return *this;
}
inline MgPoint2D operator * ( MREAL r, const MgPoint2D& v)						// p2 = r * p1
{
	MgPoint2D vto;
	vto.x = r * v.x;
	vto.y = r * v.y;
	return vto;
}
inline MgPoint2D MgPoint2D::operator * ( MREAL r) const							// p2 = p1 * r
{
	return MgPoint2D( x * r, y * r);
}
inline MgPoint2D MgPoint2D::operator / ( MREAL r) const							// p2 = p1 / r
{
	return MgPoint2D( x / r, y / r);
}
inline MgPoint2D& MgPoint2D::operator *= ( MREAL r)								// p1 *= r
{
	x *= r;
	y *= r;
	return *this;
}
inline MgPoint2D& MgPoint2D::operator /= ( MREAL r)								// p1 /= r
{
	x /= r;
	y /= r;
	return *this;
}
inline MREAL MgPoint2D::operator * ( const MgPoint2D& p) const					// r = p1 * p2 (内積 cos)
{
	return ( x * p.x + y * p.y);
}
inline MREAL MgPoint2D::operator * ( const MgVect2D& v) const					// r = p1 * v2 (内積 cos)
{
	return ( x * v.x + y * v.y);
}
inline MREAL MgPoint2D::operator ^ ( const MgPoint2D& p) const					// r = p1 ^ p2 (外積 sin)
{
	return ( x * p.y -  y * p.x);
}
inline MgPoint2D MgPoint2D::operator & ( const MgPoint2D& p) const				// p3 = p1 & p2 (rotation)
{
	return MgPoint2D( x * p.x -  y * p.y, x * p.y +  y * p.x);
}
inline bool MgPoint2D::operator == (const MgPoint2D& p) const					// b = (p1 == p2) 判定
{
	MgVect2D v1 = p - *this;
	return (v1 * v1) <= MGPTOL->D_2;
}
inline bool MgPoint2D::operator != (const MgPoint2D& p) const					// b = (p1 != p2) 判定
{
	return !((*this) == p);
}
// 演算
inline MgPoint2D MgPoint2DC( const MgPoint3D& v)								// ３次元(x,y)→２次元
{
	MgPoint2D vto;
	vto.x = v.x;
	vto.y = v.y;
	return vto;
}
inline MgPoint2D MgPoint2DC( const CPoint &cp)									// CPoint→２次元
{
	MgPoint2D vto;
	vto.x = MREAL( cp.x);
	vto.y = MREAL( cp.y);
	return vto;
}
inline CPoint MgCPointC(MgPoint2D& p)											// ２次元→CPoint
{
	CPoint cp;
	cp.x = MINT( p.x + 0.5);
	cp.y = MINT( p.y + 0.5);
	return cp;
}

//======================( ２次元 )==============================
//		２次元ベクトル　ベクトル演算
//
// コピーコンストラクタ
inline MgVect2D::MgVect2D( MREAL x1, MREAL y2)									// 成分が(X,Y)方向のベクトル
{
	x = x1;
	y = y2;
}
inline MgVect2D::MgVect2D( const CPoint& pt)									// CPointの原点から点までの方向のベクトル
{
	x = MREAL(pt.x);
	y = MREAL(pt.y);
}
inline MgVect2D::MgVect2D( const MgVect3D& V)									// 3Dベクトルの(X,Y)方向のベクトル
{
	x = V.x;
	y = V.y;
}
inline MgVect2D::MgVect2D( const MgPoint2D& i_p1, const MgPoint2D& i_p2)		// 始点から終点方向のベクトル
{
	*this = i_p2 - i_p1;
}


// 演算

inline MgVect2D MgVect2D::RotR90() const										// 右に９０度回転したベクトルを求める
{
	return MgVect2D( y, -x);
}
inline MgVect2D MgVect2D::RotL90() const										// 左に９０度回転したベクトルを求める
{
	return MgVect2D( -y, x);
}
inline MgVect2D MgVect2D::Rot180() const										// １８０度回転したベクトルを求める
{
	return MgVect2D( -x, -y);
}
inline MgVect2D MgVect2D::Rot( const MgVect2D& v) const							// 単位ベクトル方向に回転したベクトルを求める
{
	return MgVect2D( x * v.x - y * v.y, x * v.y + y * v.x);
}
inline MgVect2D MgVect2D::Rot( MREAL ang)										// 指定角度で左回転したベクトルを求める
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	return Rot( v);
}
inline MREAL MgVect2D::AngleX()													// 水平線(X方向)とベクトル方向との角度を求める 
{
	if ( ( (*this) * (*this)) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	return MREAL( atan2( y, x));
}
inline MREAL MgVect2D::AngleY()													// 垂直線(Y方向)とベクトル方向との角度を求める
{
	if ( ( (*this) * (*this)) < MGPTOL->D_2)
		RETURN_VECT_ZERO_ERR();
	return MREAL( atan2( -x, y));
}

// 変換
inline MgVect2D MgVect2D::SetRotR90()											// 右に９０度回転したベクトルに変換する
{
	MREAL xs = x;
	x = y;
	y = -xs;
	return *this;
}
inline MgVect2D MgVect2D::SetRotL90()											// 左に９０度回転したベクトルに変換する
{
	MREAL xs = x;
	x = -y;
	y = xs;
	return *this;
}
inline MgVect2D MgVect2D::SetRot180()											// １８０度回転したベクトルに変換する
{
	x = -x;
	y = -y;
	return *this;
}
inline MgVect2D MgVect2D::SetRot( const MgVect2D& v)							// 単位ベクトル方向に回転したベクトルに変換する
{
	*this = Rot( v);
	return *this;
}
inline MgVect2D MgVect2D::SetRot( MREAL ang)									// 指定角度で左回転したベクトルに変換する
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
  *this = Rot( v);
  return *this;
}
inline MgVect2D MgVect2D::SetAngleX( MREAL ang)									// 水平線(X方向)から指定角度方向の単位ベクトルに変換する 
{
	*this = MgVect2D( cos( ang), sin( ang));
	return *this;
}
inline MgVect2D MgVect2D::SetAngleY( MREAL ang)									// 垂直線(Y方向)から指定角度方向の単位ベクトルに変換する 
{
	*this = MgVect2D( -sin( ang), cos( ang));
	return *this;
}
inline MREAL MgVect2D::Abs()													// 2Dベクトルの長さを求める
{
	return sqrt( (*this) * (*this));
}
inline MREAL MgVect2D::SqAbs()													// 2Dベクトルの長さの２乗を求める
{
	return ( (*this) * (*this));
}

// 属性値の取得
inline void MgVect2D::Get( MREAL* rP) const										// MREAL[2] = v1
{
	rP[0] = x;
	rP[1] = y;
}

// 属性値の設定	
inline MgVect2D& MgVect2D::operator = ( const CPoint &pt)						// v1 = CPoint 
{
	x = MREAL(pt.x);
	y = MREAL(pt.y);
	return *this;
}
inline MgVect2D& MgVect2D::operator = ( const MREAL* pt)						// v1 = MREAL[2]
{
	x = pt[0];
	y = pt[1];
	return *this;
}

// 演算オペレータ
inline MgVect2D MgVect2D::operator + ( const MgVect2D& v) const					// v3 = v1 + v2
{
	return MgVect2D( x + v.x, y + v.y);
}
inline MgVect2D MgVect2D::operator - ( const MgVect2D& v) const					// v3 = v1 - v2
{
	return MgVect2D( x - v.x, y - v.y);
}
inline MgVect2D operator - ( const MgVect2D& p)									// v2 = - v1
{
	MgVect2D vto;
	vto.x = -p.x;
	vto.y = -p.y;
	return vto;
}
inline MgVect2D& MgVect2D::operator += ( const MgVect2D& v)						// v1 += v2
{
	x += v.x;
	y += v.y;
	return *this;
}
inline MgVect2D& MgVect2D::operator -= ( const MgVect2D& v)						// v1 -= v2
{
	x -= v.x;
	y -= v.y;
	return *this;
}
inline MgVect2D operator * ( MREAL r, const MgVect2D& v)						// v1 = r * v2
{
	MgVect2D vto;
	vto.x = r * v.x;
	vto.y = r * v.y;
	return vto;
}
inline MgVect2D MgVect2D::operator * ( MREAL r) const							// v2 = v1 * r
{
	return MgVect2D( x * r, y * r);
}
inline MgVect2D MgVect2D::operator / ( MREAL r) const							// v2 = v1 / r
{
	return MgVect2D( x / r, y / r);
}
inline MgVect2D& MgVect2D::operator *= ( MREAL r)								// v1 *= r
{
	x *= r;
	y *= r;
	return *this;
}
inline MgVect2D& MgVect2D::operator /= ( MREAL r)								// v1 /= r
{
	x /= r;
	y /= r;
	return *this;
}
inline MREAL MgVect2D::operator * ( const MgVect2D& v) const					// r = v1 * v2 (内積 cos)
{
	return ( x * v.x + y * v.y);
}
inline MREAL MgVect2D::operator * ( const MgPoint2D& v) const					// r = v1 * p2 (内積 cos)
{
	return ( x * v.x + y * v.y);
}
inline MREAL MgVect2D::operator ^ ( const MgVect2D& v) const					// r = v1 ^ v2 (外積 sin)
{
	return ( x * v.y -  y * v.x);
}
inline MgVect2D MgVect2D::operator & ( const MgVect2D& v) const					// v3 = v1 & v2 (rotation)
{
	return MgVect2D( x * v.x - y * v.y, x * v.y +  y * v.x);
}
inline bool MgVect2D::operator == (const MgVect2D& v) const						// b = (v1 == v2) 判定
{
	MgVect2D v1 = v - *this;
	return (v1 * v1) <= MGPTOL->D_2;
}
inline bool MgVect2D::operator != (const MgVect2D& v) const						// b = (v1 != v2) 判定
{
	return !((*this) == v);
}

// 変換
inline MgVect2D MgVect2DC( const MgVect3D& v)									// ３次元(x,y)→２次元
{
	MgVect2D vto;
	vto.x=v.x;
	vto.y=v.y;
	return vto;
}
inline MgVect2D MgVect2DC( const CPoint &cp)									// CPoint→２次元
{
	MgVect2D vto; vto.x = MREAL( cp.x);
	vto.y = MREAL( cp.y);
	return vto;
}

inline CPoint MgCPointC(MgVect2D& v)
{
	CPoint cp;
	cp.x = MINT( v.x + 0.5);
	cp.y = MINT( v.y + 0.5);
	return cp;
}

inline MgVect2D MgVect2DAngR( MREAL rad)
{
	return MgVect2D( cos( rad), sin( rad));
}

inline MgVect2D MgVect2DAngD( MREAL deg)
{
	MREAL rad = deg * MC_DTR;
	return MgVect2D( cos( rad), sin( rad));
}

//======================( ３次元 )==============================
//		３次元点	(ベクトル演算)
//
// コピーコンストラクタ
inline MgPoint3D::MgPoint3D( MREAL x1, MREAL y2, MREAL z3)
{
	x = x1;
	y = y2;
	z = z3;
}
inline MgPoint3D::MgPoint3D( MgPoint2D v1, MREAL z3)
{
	x = v1.x;
	y = v1.y;
	z = z3;
}
inline MgVect3D::MgVect3D( const MgPoint3D& i_p1, const MgPoint3D& i_p2)		// 始点から終点方向のベクトル
{
	*this = i_p2 - i_p1;
}

// 演算
inline MgPoint3D MgPoint3D::RotR90() const										// Z軸を中心軸として右に９０度回転した点の位置を求める
{
	return MgPoint3D( y, -x, z);
}
inline MgPoint3D MgPoint3D::RotL90() const										// Z軸を中心軸として左に９０度回転した点の位置を求める
{
	return MgPoint3D( -y, x, z);
}
inline MgPoint3D MgPoint3D::Rot180() const										// Z軸を中心軸として１８０度回転した点の位置を求める
{
	return MgPoint3D( -x, -y, z);
}
inline MgPoint3D MgPoint3D::Rot( const MgVect2D& v) const						// Z軸を中心軸として単位ベクトル方向に回転した点の位置を求める
{
	return MgPoint3D( x * v.x - y * v.y, x * v.y + y * v.x, z);
}
inline MgPoint3D MgPoint3D::Rot( MREAL ang) const								// Z軸を中心軸として指定角度で左回転した点の位置を求める
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	return Rot( v);
}

// 変換
inline MgPoint3D& MgPoint3D::operator = ( const MREAL* pt)
						{ x = pt[0]; y = pt[1]; z = pt[2]; return *this;}
inline MgPoint3D MgPoint3D::SetRotR90()											// Z軸を中心軸として右に９０度回転する
						{ MREAL xs = x; x = y; y = -xs; return *this;}
inline MgPoint3D MgPoint3D::SetRotL90()											// Z軸を中心軸として左に９０度回転する
						{ MREAL xs = x; x = -y; y = xs; return *this;}
inline MgPoint3D MgPoint3D::SetRot180()											// Z軸を中心軸として１８０度回転する
						{ x = -x; y = -y; return *this;}
//u inline MgPoint3D MgPoint3D::SetRot( const MgVect2D& v);						// Z軸を中心軸として単位ベクトル方向に回転する

//u inline MgPoint3D MgPoint3D::SetRot( MREAL ang);								// Z軸を中心軸として指定角度で左回転する

inline MgPoint3D MgPoint3D::SetRot( const MgVect2D& v)							// Z軸を中心軸として単位ベクトル方向に回転する
{
	*this = Rot( v);
	return *this;
}
inline MgPoint3D MgPoint3D::SetRot( MREAL ang)									// Z軸を中心軸として指定角度で左回転する
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	*this = Rot( v);
	return *this;
}

// 属性値の取得
inline void	MgPoint3D::Get( MREAL* rP) const
{
	rP[0] = x;
	rP[1] = y;
	rP[2] = z;
}
inline MgPoint2D MgPoint3D::To2D() const										// 3D Point → 2D Point
{
	return MgPoint2D( x, y);
}

// 演算オペレータ
inline MgPoint3D MgPoint3DC( const MgPoint2D& v1, MREAL z2 = 0.)				// ２次元→３次元　(Z省略0.)
{
	MgPoint3D Pto;
	Pto.x = v1.x;
	Pto.y = v1.y;
	Pto.z = z2;
	return Pto;
} 
inline MgPoint3D MgPoint3DC( const MgPoint2D& v1, const MgPlane3D& Pln3);		// ２次元→３次元

inline MgPoint3D MgPoint3D::operator + ( const MgPoint3D& P) const				// P3 = P1 + p2
{
	return MgPoint3D( x + P.x, y + P.y, z + P.z);
}
inline MgPoint3D MgPoint3D::operator + ( const MgVect3D& V) const				// P3 = P1 + p2
{
	return MgPoint3D( x + V.x, y + V.y, z + V.z);
}
inline MgVect3D MgPoint3D::operator - ( const MgPoint3D& P) const				// P3 = P1 - P2
{
	return MgVect3D(x - P.x, y - P.y, z - P.z);
}
inline MgPoint3D MgPoint3D::operator - ( const MgVect3D& P) const				// P3 = P1 - P2
{
	return MgPoint3D(x - P.x, y - P.y, z - P.z);
}
inline MgPoint3D operator - ( const MgPoint3D& P)								// P1 = - P2
{
	MgPoint3D Vto;
	Vto.x =-P.x;
	Vto.y = -P.y;
	Vto.z = -P.z;
	return Vto;
}
inline MgPoint3D& MgPoint3D::operator += ( const MgVect3D& V)					// P1 += P2
{
	x += V.x;
	y += V.y;
	z += V.z;
	return *this;
}
inline MgPoint3D& MgPoint3D::operator -= ( const MgPoint3D& P)					// P1 -= P2
{
	x += P.x;
	y += P.y;
	z += P.z;
	return *this;
}
inline MgPoint3D& MgPoint3D::operator -= ( const MgVect3D& V)					// P1 -= P2
{
	x -= V.x;
	y -= V.y;
	z -= V.z;
	return *this;
}
inline MgPoint3D operator * ( MREAL r, const MgPoint3D& P)						// P2 = r * P1
{
	MgPoint3D Vto;
	Vto.x =r * P.x;
	Vto.y = r * P.y;
	Vto.z = r * P.z;
	return Vto;
}
inline MgPoint3D MgPoint3D::operator * (  MREAL r)	const						// P2 = P1 * r
{
	return MgPoint3D( x * r, y * r, z * r);
}
inline MgPoint3D MgPoint3D::operator / (  MREAL r) const						// P2 = P1 / r
{
	return MgPoint3D( x / r, y / r, z / r);
}
inline MgPoint3D& MgPoint3D::operator *= ( MREAL r)								// P1 *= r
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}
inline MgPoint3D& MgPoint3D::operator /= ( MREAL r)								// P1 /= r
{
	x /= r;
	y /= r;
	z /= r;
	return *this;
}
inline MREAL MgPoint3D::operator * ( const MgPoint3D& P) const					// r = P1 * P2 (内積 cos)
{
	return ( x * P.x + y * P.y + z * P.z);
}
inline MREAL MgPoint3D::operator * ( const MgVect3D& V) const					// r = P1 * V2 (内積 cos)
{
	return ( x * V.x + y * V.y + z * V.z);
}
inline MgVect3D MgPoint3D::operator ^ ( const MgPoint3D& P) const				// P3 = P1 ^ P2 (外積 sin)
{
	return MgVect3D( y * P.z - z * P.y, z * P.x - x * P.z, x * P.y - y * P.x);
}
inline bool MgPoint3D::operator == ( const MgPoint3D& P) const					// b = (P1 == P2) 判定
{
	MgVect3D v1 = P - *this;
	return ((v1 * v1) <= MGPTOL->D_2);
}
inline bool MgPoint3D::operator != ( const MgPoint3D& P) const					// b = (P1 != P2) 判定
{
	return !((*this) == P);
}

//======================( ３次元 )==============================
//		３次元ベクトル	ベクトル演算
//
// コピーコンストラクタ
inline MgVect3D::MgVect3D( MREAL x1, MREAL y2, MREAL z3)
						{ x = x1; y = y2; z = z3;}
inline MgVect3D::MgVect3D( MgVect2D v1, MREAL z3)
						{ x = v1.x; y = v1.y; z = z3;}
//inline MgVect3D::MgVect3D( const MgPoint3D& v1)
//						{ x = v1.x; y = v1.y; z = v1.z;}

// 属性値の取得
inline void	MgVect3D::Get( MREAL* rP) const
{ rP[0] = x; rP[1] = y; rP[2] = z;}

// 演算
inline MgVect2D	MgVect3D::To2D() const											// 3D Point → 2D Point
{
	return MgVect2D( x, y);
}
//	MgVect3D Unitize( MREAL i_tol = MgTol_Dt::D) const;							// 単位ベクトルを求める

inline MgVect3D MgVect3D::RotR90() const										// Z軸を中心軸として右に９０度回転したベクトルを求める
{
	return MgVect3D( y, -x, z);
}

inline MgVect3D MgVect3D::RotL90() const										// Z軸を中心軸として左に９０度回転したベクトルを求める
{
	return MgVect3D( -y, x, z);
}

inline MgVect3D MgVect3D::Rot180() const										// Z軸を中心軸として１８０度回転したベクトルを求める
{
	return MgVect3D( -x, -y, z);
}
inline MgVect3D MgVect3D::Rot( const MgVect2D& v) const							// Z軸を中心軸として単位ベクトル方向に回転したベクトルを求める
{
	return MgVect3D( x * v.x - y * v.y, x * v.y + y * v.x, z);
}
inline MgVect3D MgVect3D::Rot( MREAL ang) const									// Z軸を中心軸として指定角度で左回転した点の位置を求める
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	return Rot( v);
}
inline MREAL MgVect3D::AngleX()													// 水平線(X方向)と水平面に投影したベクトル方向との角度を求める 投影ベクトルの長さが0の場合は0
{
	MREAL rAng;
	if ( x * x + y * y >= MGPTOL->D_2) {
		rAng = MREAL( atan2( y, x));
	} else {
		rAng = 0.;
	}
	return rAng;
}
inline MREAL MgVect3D::AngleY()													// 垂直線(Y方向)とベクトル方向との角度を求める
{
	MREAL rAng;
	if ( x * x + y * y >= MGPTOL->D_2) {
		rAng = MREAL( atan2( -x, y));
	} else {
		rAng = 0.;
	}
	return rAng;
}
inline MREAL MgVect3D::AngleZ()													// 水平面とベクトル方向との角度を求める(-π/2～π/2) 投影ベクトルの長さが0の場合はπ/2
{
	MREAL rAng;
	MREAL rLen = sqrt( x * x + y * y);
	if (rLen >= MGPTOL->D) {
		rAng = MREAL( atan2( z, rLen));
	} else {
		rAng = MREAL( MC_PIE / 2.);
	}
	return rAng;
}
inline MREAL MgVect3D::Abs()													// 3Dベクトルの長さ
{
	return sqrt( (*this) * (*this));
}
inline MREAL MgVect3D::SqAbs()													// 3Dベクトルの長さの２乗
{
	return ( (*this) * (*this));
}

// 変換

inline MgVect3D& MgVect3D::operator = ( const MREAL* pt)
{
	x = pt[0];
	y = pt[1];
	z = pt[2];
	return *this;
}
//inline MgVect3D MgVect3D::Set( const MgPoint2D& v1, const MgPlane3D& Pln3);	// ２次元→３次元

inline MgVect3D MgVect3D::SetRotR90()											// Z軸を中心軸として右に９０度回転する
{
	MREAL xs = x;
	x = y;
	y = -xs;
	return *this;
}
inline MgVect3D MgVect3D::SetRotL90()											// Z軸を中心軸として左に９０度回転する
{
	MREAL xs = x;
	x = -y;
	y = xs;
	return *this;
}
inline MgVect3D MgVect3D::SetRot180()											// Z軸を中心軸として１８０度回転する
{
	x = -x;
	y = -y;
	return *this;
}
inline MgVect3D MgVect3D::SetRot( const MgVect2D& v)							// Z軸を中心軸として単位ベクトル方向に回転する
{
	*this = Rot( v);
	return *this;
}
inline MgVect3D MgVect3D::SetRot( MREAL ang)									// Z軸を中心軸として指定角度で左回転する
{
	MgVect2D v = MgVect2D( cos( ang), sin( ang));
	*this = Rot( v);
	return *this;
}
inline MgVect2D MgVect3D::SetAngleX( MREAL ang)									// 水平線(X方向)から指定角度方向の単位ベクトルに変換する 
{
	x = cos( ang);
	y = sin( ang);
	z = 0;
	return *this;
}
inline MgVect2D MgVect3D::SetAngleY( MREAL ang)									// 垂直線(Y方向)から指定角度方向の単位ベクトルに変換する 
{
	x = -sin( ang);
	y = cos( ang);
	z = 0;
	return *this;
}
inline MgVect2D MgVect3D::SetAngleXZ( MREAL angx, MREAL angz)					// 水平線(X方向)から指定角度X方向で水平面から指定角度Z方向のの単位ベクトルに変換する 
{
	MREAL rSinh = sin( angz);
	x = cos( angx) * rSinh;
	y = sin( angx) * rSinh;
	z = cos( angz);
	return *this;
}

// 演算オペレータ
inline MgVect3D MgVect3DC( const MgVect2D& v1, MREAL z2 = 0.)					// ２次元→３次元　(Z省略0.)
{
	MgVect3D vto;
	vto.x = v1.x;
	vto.y = v1.y;
	vto.z = z2;
	return vto;
} 
inline MgVect3D MgVect3DC( const MgVect2D& v1, const MgPlane3D& Pln3);			// ２次元→３次元

inline MgVect3D MgVect3D::operator + ( const MgVect3D& V) const					// V3 = V1 + V2
{
	return MgVect3D( x + V.x, y + V.y, z + V.z);
}
inline MgVect3D MgVect3D::operator - ( const MgVect3D& P) const					// V3 = V1 - V2
{
	return MgVect3D(x - P.x, y - P.y, z - P.z);
}
inline MgVect3D operator - ( const MgVect3D& V)									// P1 = - P2
{
	MgVect3D Vto;
	Vto.x =-V.x;
	Vto.y = -V.y;
	Vto.z = -V.z;
	return Vto;
}
inline MgVect3D& MgVect3D::operator += ( const MgVect3D& V)						// V1 += V2
{
	x += V.x;
	y += V.y;
	z += V.z;
	return *this;
}
inline MgVect3D& MgVect3D::operator -= ( const MgVect3D& V)						// V1 -= V2
{
	x -= V.x;
	y -= V.y;
	z -= V.z;
	return *this;
}
inline MgVect3D operator * ( MREAL r, const MgVect3D& V)						// P1 = r * P2
{
	MgVect3D Vto;
	Vto.x =r * V.x;
	Vto.y = r * V.y;
	Vto.z = r * V.z;
	return Vto;
}
inline MgVect3D MgVect3D::operator * (  MREAL r)	const						// V2 = V1 * r
{
	return MgVect3D( x * r, y * r, z * r);
}
inline MgVect3D MgVect3D::operator / (  MREAL r) const							// V2 = V1 / r
{
	return MgVect3D( x / r, y / r, z / r);
}
inline MgVect3D& MgVect3D::operator *= ( MREAL r)								// V1 *= r
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}
inline MgVect3D& MgVect3D::operator /= ( MREAL r)								// V1 /= r
{
	x /= r;
	y /= r;
	z /= r;
	return *this;
}
inline MREAL MgVect3D::operator * ( const MgVect3D& V) const					// r = V1 * V2 (内積 cos)
{
	return ( x * V.x + y * V.y + z * V.z);
}
inline MREAL MgVect3D::operator * ( const MgPoint3D& P) const					// r = V1 * P2 (内積 cos)
{
	return ( x * P.x + y * P.y + z * P.z);
}
inline MgVect3D MgVect3D::operator ^ ( const MgVect3D& V) const					// V3 = V1 ^ V2 (外積 sin)
{
	return MgVect3D( y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
}
inline bool MgVect3D::operator == ( const MgVect3D& V) const					// b = (V1 == V2) 判定
{
	MgVect3D V1 = V - *this;
	return ((V1 * V1) <= MGPTOL->D_2);
}
inline bool MgVect3D::operator != ( const MgVect3D& V) const					// b = (V1 != V2) 判定
{
	return !((*this) == V);
}

} // namespace MC
