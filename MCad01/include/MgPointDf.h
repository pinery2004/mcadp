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
//#include "mdPlex.h"

namespace MC
{

//
//======================( ２次元 )==============================
//		２次元点	ベクトル演算
//
// コピーコンストラクタ
inline MgPoint2::MgPoint2( const MgPoint3& pt)
						{ x = pt.x; y = pt.y;}
//inline MgPoint2::MgPoint2( const MgVect2& pt)
//						{ x = pt.x; y = pt.y;}

// 演算
inline MgPoint2 MgPoint2C( const MgPoint3& v)									// ３次元(x,y)→２次元
						{ MgPoint2 vto; vto.x=v.x; vto.y=v.y; return vto;}
inline MgPoint2 MgPoint2C( const CPoint &cp)									// CPoint→２次元
						{ MgPoint2 vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}
inline CPoint MgCPointC(MgPoint2& v)
						{ CPoint cp; cp.x = MINT( v.x + 0.5);
						  cp.y = MINT( v.y + 0.5); return cp;}
inline MgPoint2 MgPoint2AngR( MREAL rad)
						{ return MgPoint2( cos( rad), sin( rad));}
inline MgPoint2 MgPoint2AngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR; return MgPoint2( cos( rad), sin( rad));}
inline MgPoint2 MgPoint2::Rot( const MgVect2& v) const							// 原点を中心に単位ベクトル方向に回転した点の位置を求める
						{ return MgPoint2( x * v.x -  y * v.y,
		 			               		   x * v.y +  y * v.x);}
inline MgPoint2	MgPoint2::Rot( MREAL ang)										// 原点を中心に指定角度で左回転した点の位置を求める
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
						  MgPoint2 pt;
						  pt.x = x * v.x -  y * v.y;
						  pt.y = x * v.y +  y * v.x;
						  return pt;}

// 変換
inline MgPoint2 MgPoint2::SetRot( const MgVect2& v)								// 原点を中心に単位ベクトル方向に回転する
//S						{ MgPoint2 pt = *this; 
//						  x = pt.x * v.x -  pt.y * v.y;
//						  y = pt.x * v.y +  pt.y * v.x;
						{ *this = Rot( v);
						  return *this;}
inline MgPoint2 MgPoint2::SetRot( MREAL ang)									// 原点を中心に指定角度で左回転する
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
//S						  MgPoint2 pt = *this;
//						  x = pt.x * v.x -  pt.y * v.y;
//						  y = pt.x * v.y +  pt.y * v.x;
						  *this = Rot( v);
						  return *this;}
// 演算オペレータ
inline MgPoint2 MgPoint2::operator + ( const MgPoint2& v) const					// P1 = P2 + p3
				 		{ return MgPoint2( x + v.x, y + v.y);}
inline MgPoint2 MgPoint2::operator + ( const MgVect2& v) const					// P1 = P2 + p3
				 		{ return MgPoint2( x + v.x, y + v.y);}
inline MgVect2 MgPoint2::operator - ( const MgPoint2& v) const					// P1 = P2 - P3
				 		{ return MgVect2( x - v.x, y - v.y);}
inline MgPoint2 MgPoint2::operator - ( const MgVect2& v) const					// P1 = P2 - P3
				 		{ return MgPoint2( x - v.x, y - v.y);}
inline MgPoint2 MgPoint2::operator += ( const MgPoint2& v)						// P1 += P2
				 		{ return MgPoint2( x += v.x, y += v.y);}
inline MgPoint2 MgPoint2::operator += ( const MgVect2& v)						// P1 += P2
				 		{ return MgPoint2( x += v.x, y += v.y);}
inline MgPoint2 MgPoint2::operator -= ( const MgPoint2& v)						// P1 -= P2
				 		{ return MgPoint2( x -= v.x, y -= v.y);}
inline MgPoint2 MgPoint2::operator -= ( const MgVect2& v)						// P1 -= P2
				 		{ return MgPoint2( x -= v.x, y -= v.y);}
inline MgPoint2 MgPoint2::operator * ( MREAL r) const							// P1 = P2 * r
				 		{ return MgPoint2( x * r, y * r);}
inline MgPoint2 MgPoint2::operator / ( MREAL r) const							// P1 = P2 / r
				 		{ return MgPoint2( x / r, y / r);}
inline MgPoint2 MgPoint2::operator *= ( MREAL r)								// P1 *= r
				 		{ return MgPoint2( x *= r, y *= r);}
inline MgPoint2 MgPoint2::operator /= ( MREAL r)								// P1 /= r
				 		{ return MgPoint2( x /= r, y /= r);}
inline MREAL MgPoint2::operator * ( const MgPoint2& v) const					// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgPoint2::operator * ( const MgVect2& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgPoint2::operator ^ ( const MgPoint2& v) const					// r = P2 ^ P3 (外積 sin)
				 		{ return ( x * v.y -  y * v.x);}
inline MgPoint2 MgPoint2::operator & ( const MgPoint2& v) const					// P1 = P2 & P3 (rotation)
				 		{ return MgPoint2( x * v.x -  y * v.y,
		 			               		   x * v.y +  y * v.x);}
inline bool MgPoint2::operator == (const MgPoint2& v) const						// b = (P1 == P2) 判定
				 		{ MgVect2 v1 = v - *this; return (v1 * v1) <= g_gTol.D_2;}
inline bool MgPoint2::operator != (const MgPoint2& v) const						// b = (P1 != P2) 判定
				 		{ return !((*this) == v);}
//
//======================( ２次元 )==============================
//		２次元ベクトル　ベクトル演算
//
// コピーコンストラクタ
inline MgVect2::MgVect2( const MgVect3& pt)
						{ x = pt.x; y = pt.y;}
//inline MgVect2::MgVect2( const MgPoint2& pt)
//						{ x = pt.x; y = pt.y;}

// 演算

inline MgVect2 MgVect2C( const MgVect3& v)										// ３次元(x,y)→２次元
						{ MgVect2 vto; vto.x=v.x; vto.y=v.y; return vto;}

inline MgVect2 MgVect2C( const CPoint &cp)										// CPoint→２次元
						{ MgVect2 vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}

inline CPoint MgCPointC(MgVect2& v)
						{ CPoint cp; cp.x = MINT( v.x + 0.5);
						  cp.y = MINT( v.y + 0.5); return cp;}

inline MgVect2 MgVect2AngR( MREAL rad)
						{ return MgVect2( cos( rad), sin( rad));}

inline MgVect2 MgVect2AngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR; return MgVect2( cos( rad), sin( rad));}

// 演算オペレータ
inline MgVect2 MgVect2::operator + ( const MgVect2& v) const					// P1 = P2 + p3
				 		{ return MgVect2( x + v.x, y + v.y);}
inline MgVect2 MgVect2::operator - ( const MgVect2& v) const					// P1 = P2 - P3
				 		{ return MgVect2( x - v.x, y - v.y);}
inline MgVect2 MgVect2::operator += ( const MgVect2& v)							// P1 += P2
				 		{ return MgVect2( x += v.x, y += v.y);}
inline MgVect2 MgVect2::operator -= ( const MgVect2& v)							// P1 -= P2
				 		{ return MgVect2( x -= v.x, y -= v.y);}
inline MgVect2 MgVect2::operator * ( MREAL r) const								// P1 = P2 * r
				 		{ return MgVect2( x * r, y * r);}
inline MgVect2 MgVect2::operator / ( MREAL r) const								// P1 = P2 / r
				 		{ return MgVect2( x / r, y / r);}
inline MgVect2 MgVect2::operator *= ( MREAL r)									// P1 *= r
				 		{ return MgVect2( x *= r, y *= r);}
inline MgVect2 MgVect2::operator /= ( MREAL r)									// P1 /= r
				 		{ return MgVect2( x /= r, y /= r);}
inline MREAL MgVect2::operator * ( const MgVect2& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2::operator * ( const MgPoint2& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2::operator ^ ( const MgVect2& v) const						// r = P2 ^ P3 (外積 sin)
				 		{ return ( x * v.y -  y * v.x);}
inline MgVect2 MgVect2::operator & ( const MgVect2& v) const					// P1 = P2 & P3 (rotation)
				 		{ return MgVect2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}
inline bool MgVect2::operator == (const MgVect2& v) const						// b = (P1 == P2) 判定
				 		{ MgVect2 v1 = v - *this; return (v1 * v1) <= g_gTol.D_2;}
inline bool MgVect2::operator != (const MgVect2& v) const						// b = (P1 != P2) 判定
				 		{ return !((*this) == v);}
//
//======================( ３次元 )==============================
//		３次元点	ベクトル演算
//
// コピーコンストラクタ
//inline MgPoint3::MgPoint3( const MgPoint2& v1, const MgPlane3& Pln3)			// ２次元→３次元
//inline MgPoint3::MgPoint3( const MgVect3& v1)
//						{x = v1.x; y = v1.y; z = v1.z;}

// 演算
inline MgPoint3 MgPoint3::Rot( const MgVect2& v) const							// Z軸を中心軸として単位ベクトル方向に回転した点の位置を求める
						{ return MgPoint3( x * v.x -  y * v.y,
		 			               		   x * v.y +  y * v.x, z);}
inline MgPoint3 MgPoint3::Rot( MREAL ang) const									// Z軸を中心軸として指定角度で左回転した点の位置を求める
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
//S						  return MgPoint3( x * v.x -  y * v.y,
//		 			               		   x * v.y +  y * v.x, z);}
						  return Rot( v);}

// 変換
inline MgPoint3 MgPoint3::SetRot( const MgVect2& v)								// Z軸を中心軸として単位ベクトル方向に回転する
//S						{ MgPoint2 pt; 
//						  pt.x = x * v.x -  y * v.y;
//						  pt.y = x * v.y +  y * v.x;
//						  x = pt.x;
//						  y = pt.y;
						{ *this = Rot( v);
						  return *this;}
inline MgPoint3 MgPoint3::SetRot( MREAL ang)									// Z軸を中心軸として指定角度で左回転する
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
//S						  MgPoint2 pt;
//						  pt.x = x * v.x -  y * v.y;
//						  pt.y = x * v.y +  y * v.x;
//						  x = pt.x;
//						  y = pt.y;
						  *this = Rot( v);
						  return *this;}

// 演算オペレータ
inline MgPoint3 MgPoint3C( const MgPoint2& v1, MREAL z2 = 0.)					// ２次元→３次元　(Z省略0.)
						{ MgPoint3 vto; vto.x = v1.x; vto.y = v1.y;
						  vto.z = z2; return vto;} 
inline MgPoint3 MgPoint3C( const MgPoint2& v1, const MgPlane3& Pln3);			// ２次元→３次元

inline MgPoint3 MgPoint3::operator + ( const MgPoint3& v) const					// P1 = P2 + p3
				 		{ return MgPoint3( x + v.x, y + v.y, z + v.z);}
inline MgPoint3 MgPoint3::operator + ( const MgVect3& v) const					// P1 = P2 + p3
				 		{ return MgPoint3( x + v.x, y + v.y, z + v.z);}
inline MgVect3 MgPoint3::operator - ( const MgPoint3& p) const					// P1 = P2 - P3
						{ return MgVect3(x - p.x, y - p.y, z - p.z);}
inline MgPoint3 MgPoint3::operator - ( const MgVect3& p) const					// P1 = P2 - P3
				 		{ return MgPoint3(x - p.x, y - p.y, z - p.z);}
inline MgPoint3 MgPoint3::operator += ( const MgPoint3& v)						// P1 += P2
				 		{ return MgPoint3( x += v.x, y += v.y, z += v.z);}
inline MgPoint3 MgPoint3::operator += ( const MgVect3& v)						// P1 += P2
				 		{ return MgPoint3( x += v.x, y += v.y, z += v.z);}
inline MgPoint3 MgPoint3::operator -= ( const MgPoint3& v)						// P1 -= P2
				 		{ return MgPoint3( x -= v.x, y -= v.y, z -= v.z);}
inline MgPoint3 MgPoint3::operator -= ( const MgVect3& v)						// P1 -= P2
				 		{ return MgPoint3( x -= v.x, y -= v.y, z -= v.z);}
inline MgPoint3 MgPoint3::operator * (  MREAL r)	const						// P1 = P2 * r
				 		{ return MgPoint3( x * r, y * r, z * r);}
inline MgPoint3 MgPoint3::operator / (  MREAL r) const							// P1 = P2 / r
				 		{ return MgPoint3( x / r, y / r, z / r);}
inline MgPoint3 MgPoint3::operator *= ( MREAL r)								// P1 *= r
				 		{ return MgPoint3( x *= r, y *= r, z *= r);}
inline MgPoint3 MgPoint3::operator /= ( MREAL r)								// P1 /= r
				 		{ return MgPoint3( x /= r, y /= r, z /= r);}
inline MREAL MgPoint3::operator * ( const MgPoint3& v) const					// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MREAL MgPoint3::operator * ( const MgVect3& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MgVect3 MgPoint3::operator ^ ( const MgPoint3& v) const					// P1 = P2 ^ P3 (外積 sin)
				 		{ return MgVect3( y * v.z - z * v.y,
						                  z * v.x - x * v.z,
								          x * v.y - y * v.x);}
inline bool MgPoint3::operator == ( const MgPoint3& v) const					// b = (P1 == P2) 判定
				 		{ MgVect3 v1 = v - *this; return ((v1 * v1) <= g_gTol.D_2);}
inline bool MgPoint3::operator != ( const MgPoint3& v) const					// b = (P1 != P2) 判定
				 		{ return !((*this) == v);}
//
//======================( ３次元 )==============================
//		３次元ベクトル	ベクトル演算
//
// コピーコンストラクタ
//inline MgVect3::MgVect3( const MgPoint3& v1)
//						{ x = v1.x; y = v1.y; z = v1.z;}

// 演算
inline MgVect3 MgVect3::Rot( const MgVect2& v) const							// Z軸を中心軸として単位ベクトル方向に回転したベクトルを求める
						{ return MgVect3( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x, z);}
inline MgVect3 MgVect3::Rot( MREAL ang) const									// Z軸を中心軸として指定角度で左回転した点の位置を求める
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
//S						  return MgVect3( x * v.x -  y * v.y,
//		 			               		   x * v.y +  y * v.x, z);}
						  return Rot( v);}
// 変換
inline MgVect3 MgVect3::SetRot( const MgVect2& v)								// Z軸を中心軸として単位ベクトル方向に回転する
						{ *this = Rot( v);
						  return *this;}
inline MgVect3 MgVect3::SetRot( MREAL ang)										// Z軸を中心軸として指定角度で左回転する
						{ MgVect2 v = MgVect2( cos( ang), sin( ang));
						  *this = Rot( v);
						  return *this;}


// 演算オペレータ
inline MgVect3 MgVect3C( const MgVect2& v1, MREAL z2 = 0.)						// ２次元→３次元　(Z省略0.)
						{ MgVect3 vto; vto.x = v1.x; vto.y = v1.y;
						  vto.z = z2; return vto;} 
inline MgVect3 MgVect3C( const MgVect2& v1, const MgPlane3& Pln3);				// ２次元→３次元

inline MgVect3 MgVect3::operator + ( const MgVect3& v) const					// P1 = P2 + p3
				 		{ return MgVect3( x + v.x, y + v.y, z + v.z);}
inline MgVect3 MgVect3::operator - ( const MgVect3& p) const					// P1 = P2 - P3
				 		{ return MgVect3(x - p.x, y - p.y, z - p.z);}
inline MgVect3 MgVect3::operator += ( const MgVect3& v)							// P1 += P2
				 		{ return MgVect3( x += v.x, y += v.y, z += v.z);}
inline MgVect3 MgVect3::operator -= ( const MgVect3& v)							// P1 -= P2
				 		{ return MgVect3( x -= v.x, y -= v.y, z -= v.z);}
inline MgVect3 MgVect3::operator * (  MREAL r)	const							// P1 = P2 * r
				 		{ return MgVect3( x * r, y * r, z * r);}
inline MgVect3 MgVect3::operator / (  MREAL r) const							// P1 = P2 / r
				 		{ return MgVect3( x / r, y / r, z / r);}
inline MgVect3 MgVect3::operator *= ( MREAL r)									// P1 *= r
				 		{ return MgVect3( x *= r, y *= r, z *= r);}
inline MgVect3 MgVect3::operator /= ( MREAL r)									// P1 /= r
				 		{ return MgVect3( x /= r, y /= r, z /= r);}
inline MREAL MgVect3::operator * ( const MgVect3& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MREAL MgVect3::operator * ( const MgPoint3& v) const						// r = P1 * P2 (内積 cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MgVect3 MgVect3::operator ^ ( const MgVect3& v) const					// P1 = P2 ^ P3 (外積 sin)
				 		{ return MgVect3( y * v.z - z * v.y,
						                  z * v.x - x * v.z,
								          x * v.y - y * v.x);}
inline bool MgVect3::operator == ( const MgVect3& v) const						// b = (P1 == P2) 判定
				 		{ MgVect3 v1 = v - *this; return ((v1 * v1) <= g_gTol.D_2);}
inline bool MgVect3::operator != ( const MgVect3& v) const						// b = (P1 != P2) 判定
				 		{ return !((*this) == v);}

} // namespace MC
